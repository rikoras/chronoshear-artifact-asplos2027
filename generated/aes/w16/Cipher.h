#ifndef CIPHER_H_
#define CIPHER_H_

#include <array>
#include <cassert>
#include <cstdint>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif
#include <memory>
#include "sint_pod_v2.h"
#include "oracle_data.h"
#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)
#if defined(__clang__) || defined(__INTEL_LLVM_COMPILER)
#define ESSENT_LANE_LOOP _Pragma("clang loop vectorize(assume_safety)")
#define ESSENT_TAIL_LOOP _Pragma("clang loop vectorize(assume_safety) vectorize_width(16) vectorize_predicate(enable) unroll(disable)")
#elif defined(__GNUC__)
#define ESSENT_LANE_LOOP _Pragma("GCC ivdep")
#define ESSENT_TAIL_LOOP _Pragma("GCC ivdep")
#else
#define ESSENT_LANE_LOOP
#define ESSENT_TAIL_LOOP
#endif
template <typename E>
static inline uint64_t essent_oracle_load(const E* p, int64_t i) {
  return (uint64_t)p[i];
}
#define ESSENT_ORACLE_LOAD(name, idx) essent_oracle_load((name), (idx))
#if defined(__GNUC__) || defined(__clang__)
#define ESSENT_COLD_NOINLINE __attribute__((cold, noinline))
#define ESSENT_NOINLINE __attribute__((noinline))
#else
#define ESSENT_COLD_NOINLINE
#define ESSENT_NOINLINE
#endif
#ifndef ESSENT_ORACLE_VERIFY
#define ESSENT_ORACLE_VERIFY 1
#endif
template <int W>
static inline uint64_t essent_to_u64(const UInt<W>& v) {
  if constexpr (W <= 64) return v.as_single_word();
  else return v.template bits<63,0>().as_single_word();
}
template <int W>
static inline uint64_t essent_to_u64(const SInt<W>& v) {
  if constexpr (W <= 64) return (uint64_t)v.as_single_word();
  else return v.template bits<63,0>().as_single_word();
}
template <int W>
static inline typename UInt<W>::scalar_t essent_raw(const UInt<W>& v) { return v.val; }
template <int W>
static inline typename UInt<W>::scalar_t essent_raw(const SInt<W>& v) { return v.ui.val; }
#ifndef ESSENT_VERIFY_PACKED
#define ESSENT_VERIFY_PACKED 1
#endif
#if ESSENT_VERIFY_PACKED && defined(__AVX512F__) && defined(__AVX512BW__)
template <int Lanes, int ElemBytes, typename A, typename B>
static inline __m512i essent_verify_block(const A* a, const B* b) {
  static_assert(sizeof(A) == ElemBytes && sizeof(B) == ElemBytes, "oracle POD storage has padding");
  constexpr int bytes = Lanes * ElemBytes;
  const char* pa = reinterpret_cast<const char*>(a);
  const char* pb = reinterpret_cast<const char*>(b);
  __m512i diff = _mm512_setzero_si512();
  for (int offset = 0; offset < (bytes / 64) * 64; offset += 64) {
    diff = _mm512_or_si512(diff, _mm512_xor_si512(_mm512_loadu_si512(pa + offset), _mm512_loadu_si512(pb + offset)));
  }
  if constexpr (bytes % 64 != 0) {
    constexpr __mmask64 mask = (__mmask64)((uint64_t(1) << (bytes % 64)) - 1);
    diff = _mm512_or_si512(diff, _mm512_xor_si512(_mm512_maskz_loadu_epi8(mask, pa + (bytes / 64) * 64), _mm512_maskz_loadu_epi8(mask, pb + (bytes / 64) * 64)));
  }
  return diff;
}
#endif
template <int C, int W>
static inline UInt<W> essent_mux(UInt<C> c, UInt<W> t, UInt<W> f) {
  if constexpr (!UInt<W>::kWide) {
    using S = typename UInt<W>::scalar_t;
    const S m = (S)0 - (S)(c.val != 0);
    UInt<W> r;
    r.val = (S)((t.val & m) | (f.val & (S)~m));
    return r;
  } else {
    return bool(c) ? t : f;
  }
}
template <int C, int W>
static inline SInt<W> essent_mux(UInt<C> c, SInt<W> t, SInt<W> f) {
  return SInt<W>(essent_mux(c, t.ui, f.ui));
}
template <int W, typename T, typename E>
static inline void essent_inject_fwd(T* __restrict dst, const E* __restrict src) {
  if constexpr (sizeof(T) == sizeof(E)) memcpy(dst, src, W * sizeof(T));
  else {
    ESSENT_LANE_LOOP
    for (int L = 0; L < W; L++) dst[L] = T(ESSENT_ORACLE_LOAD(src, L));
  }
}
template <int W, typename T, typename E>
static inline void essent_inject_rev(T* __restrict dst, const E* __restrict src) {
  if constexpr (sizeof(T) == sizeof(E)) memcpy(dst, src + W, W * sizeof(T));
  else {
    ESSENT_LANE_LOOP
    for (int L = 0; L < W; L++) dst[L] = T(ESSENT_ORACLE_LOAD(src, W + L));
  }
}
template <int W, typename T>
static inline void essent_commit_lanes(T* __restrict dst, const T* __restrict src) {
  memcpy(dst, src, W * sizeof(T));
}
template <int W, int I, typename T, typename E>
static inline void essent_inject_word_fwd(T* __restrict dst, const E* __restrict src) {
  ESSENT_LANE_LOOP
  for (int L = 0; L < W; L++) dst[L].val[I] = (uint64_t)ESSENT_ORACLE_LOAD(src, L);
}
template <int W, int I, typename T, typename E>
static inline void essent_inject_word_rev(T* __restrict dst, const E* __restrict src) {
  ESSENT_LANE_LOOP
  for (int L = 0; L < W; L++) dst[L].val[I] = (uint64_t)ESSENT_ORACLE_LOAD(src, W + L);
}
static constexpr int64_t ORACLE_BLOCK_BYTES = 576LL;
static constexpr int ORACLE_KERNEL_MIRRORED = 1;

template <int W>
static inline uint64_t essent_lane_all() { return W >= 64 ? ~0ull : ((1ull << W) - 1ull); }
template <int W>
static inline uint64_t essent_lane_mask(const uint8_t* t) {
#if defined(__AVX2__)
  if constexpr (W == 32) {
    const __m256i v = _mm256_load_si256(reinterpret_cast<const __m256i*>(t));
    return static_cast<uint32_t>(_mm256_movemask_epi8(_mm256_cmpgt_epi8(v, _mm256_setzero_si256())));
  } else if constexpr (W == 16) {
    const __m128i v = _mm_load_si128(reinterpret_cast<const __m128i*>(t));
    return static_cast<uint32_t>(_mm_movemask_epi8(_mm_cmpgt_epi8(v, _mm_setzero_si128())));
  } else if constexpr (W == 64) {
    return essent_lane_mask<32>(t) | (essent_lane_mask<32>(t + 32) << 32);
  } else
#endif
  {
    uint64_t m = 0;
    for (int i = 0; i < W; i++) m |= static_cast<uint64_t>(t[i] != 0) << i;
    return m;
  }
}

template <int W>
static inline void essent_condhold_index_fwd(int16_t* __restrict idx, const UInt<1>* __restrict wen) {
  static_assert(W < 32768, "cond-hold index type is too narrow");
#if defined(__AVX512F__) && defined(__AVX512CD__) && defined(__AVX512BW__) && defined(__AVX512VL__) && !defined(CHISA_NO_FAST_HOLD_INDEX)
  if constexpr ((W == 16 || W == 32) && sizeof(UInt<1>) == 1) {
    uint32_t mask;
    if constexpr (W == 16)
      mask = static_cast<uint32_t>(_mm_cmpneq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wen)), _mm_setzero_si128()));
    else
      mask = static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen)), _mm256_setzero_si256()));
    const __m512i bits = _mm512_set1_epi32(static_cast<int>(mask));
    const __m512i one = _mm512_set1_epi32(1);
    const __m512i lanes = _mm512_setr_epi32(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    for (int B = 0; B < W; B += 16) {
      const __m512i lane = _mm512_add_epi32(lanes, _mm512_set1_epi32(B));
      const __m512i prefix = _mm512_sub_epi32(_mm512_sllv_epi32(one, lane), one);
      const __m512i last = _mm512_sub_epi32(_mm512_set1_epi32(31), _mm512_lzcnt_epi32(_mm512_and_si512(bits, prefix)));
      _mm256_storeu_si256(reinterpret_cast<__m256i*>(idx + B), _mm512_cvtepi32_epi16(last));
    }
    return;
  }
#endif
  int last = -1;
  idx[0] = -1;
  for (int L = 1; L < W; L++) {
    if (essent_to_u64(wen[L - 1])) last = L - 1;
    idx[L] = static_cast<int16_t>(last);
  }
}
template <int W>
static inline void essent_condhold_index_rev(int16_t* __restrict idx, const UInt<1>* __restrict wen) {
  static_assert(W < 32768, "cond-hold index type is too narrow");
#if defined(__AVX512F__) && defined(__AVX512CD__) && defined(__AVX512BW__) && defined(__AVX512VL__) && !defined(CHISA_NO_FAST_HOLD_INDEX)
  if constexpr ((W == 16 || W == 32) && sizeof(UInt<1>) == 1) {
    uint32_t mask;
    if constexpr (W == 16)
      mask = static_cast<uint32_t>(_mm_cmpneq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wen)), _mm_setzero_si128()));
    else
      mask = static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen)), _mm256_setzero_si256()));
    const __m512i bits = _mm512_set1_epi32(static_cast<int>(mask));
    const __m512i zero = _mm512_setzero_si512();
    const __m512i lanes = _mm512_setr_epi32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
    for (int B = 0; B < W; B += 16) {
      const __m512i above = _mm512_add_epi32(lanes, _mm512_set1_epi32(B));
      const __m512i suffix = _mm512_sllv_epi32(_mm512_set1_epi32(-1), above);
      const __m512i candidates = _mm512_and_si512(bits, suffix);
      const __m512i firstBit = _mm512_and_si512(candidates, _mm512_sub_epi32(zero, candidates));
      const __m512i first = _mm512_sub_epi32(_mm512_set1_epi32(31), _mm512_lzcnt_epi32(firstBit));
      _mm256_storeu_si256(reinterpret_cast<__m256i*>(idx + B), _mm512_cvtepi32_epi16(first));
    }
    return;
  }
#endif
  int last = -1;
  idx[W - 1] = -1;
  for (int L = W - 2; L >= 0; L--) {
    if (essent_to_u64(wen[L + 1])) last = L + 1;
    idx[L] = static_cast<int16_t>(last);
  }
}
template <int W, typename T>
static ESSENT_NOINLINE void essent_condhold_apply_fwd(T* __restrict r, const int16_t* __restrict idx, const T* __restrict wdata) {
  const T seed = r[0];
  if (idx[W - 1] < 0) { for (int L = 1; L < W; ++L) r[L] = seed; return; }

  ESSENT_LANE_LOOP
  for (int L = 1; L < W; L++) {
    const int I = idx[L];
    r[L] = I < 0 ? seed : wdata[I];
  }
}
template <int W, typename T>
static ESSENT_NOINLINE void essent_condhold_apply_rev(T* __restrict r, const int16_t* __restrict idx, const T* __restrict wdata) {
  const T seed = r[W - 1];
  if (idx[0] < 0) { for (int L = 0; L < W - 1; ++L) r[L] = seed; return; }

  ESSENT_LANE_LOOP
  for (int L = W - 2; L >= 0; L--) {
    const int I = idx[L];
    r[L] = I < 0 ? seed : wdata[I];
  }
}
template <int W, int BW>
static inline void essent_condhold_scan_fwd(UInt<BW>* __restrict r, const UInt<1>* __restrict wen, const UInt<BW>* __restrict wdata) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 8 && BW <= 8) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;
    __m128i val = _mm_slli_si128(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(wdata)), 1);
    val = _mm_insert_epi8(val, static_cast<int>(r[0].val), 0);
    __mmask16 take = static_cast<__mmask16>((~valid) & ((valid << 1) & 0xffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 1)); valid |= (valid << 1) & 0xffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 2) & 0xffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 2)); valid |= (valid << 2) & 0xffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 4) & 0xffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 4));
    _mm_storel_epi64(reinterpret_cast<__m128i*>(r), val);
    return;
  } else if constexpr (W == 8 && BW > 8 && BW <= 16) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;
    __m128i val = _mm_slli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 2);
    val = _mm_insert_epi16(val, static_cast<int>(r[0].val), 0);
    __mmask8 take = static_cast<__mmask8>((~valid) & ((valid << 1) & 0xffu));
    val = _mm_mask_mov_epi16(val, take, _mm_slli_si128(val, 2)); valid |= (valid << 1) & 0xffu;
    take = static_cast<__mmask8>((~valid) & ((valid << 2) & 0xffu));
    val = _mm_mask_mov_epi16(val, take, _mm_slli_si128(val, 4)); valid |= (valid << 2) & 0xffu;
    take = static_cast<__mmask8>((~valid) & ((valid << 4) & 0xffu));
    val = _mm_mask_mov_epi16(val, take, _mm_slli_si128(val, 8));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);
    return;
  } else if constexpr (W == 8 && BW > 16 && BW <= 32) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;
    const __m256i wd = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wdata));
    __m256i val = _mm256_permutevar8x32_epi32(wd, _mm256_setr_epi32(0,0,1,2,3,4,5,6));
    val = _mm256_mask_mov_epi32(val, static_cast<__mmask8>(0x01), _mm256_set1_epi32(static_cast<int>(r[0].val)));
    __mmask8 take = static_cast<__mmask8>((~valid) & ((valid << 1) & 0xffu));
    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(0,0,1,2,3,4,5,6))); valid |= (valid << 1) & 0xffu;
    take = static_cast<__mmask8>((~valid) & ((valid << 2) & 0xffu));
    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(0,0,0,1,2,3,4,5))); valid |= (valid << 2) & 0xffu;
    take = static_cast<__mmask8>((~valid) & ((valid << 4) & 0xffu));
    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(0,0,0,0,0,1,2,3)));
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(r), val);
    return;
  } else if constexpr (W == 8 && BW > 32 && BW <= 64) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;
    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));
    __m512i val = _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,1,2,3,4,5,6), wd);
    val = _mm512_mask_mov_epi64(val, static_cast<__mmask8>(0x01), _mm512_set1_epi64(static_cast<long long>(r[0].val)));
    __mmask8 take = static_cast<__mmask8>((~valid) & ((valid << 1) & 0xffu));
    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,1,2,3,4,5,6), val)); valid |= (valid << 1) & 0xffu;
    take = static_cast<__mmask8>((~valid) & ((valid << 2) & 0xffu));
    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,0,1,2,3,4,5), val)); valid |= (valid << 2) & 0xffu;
    take = static_cast<__mmask8>((~valid) & ((valid << 4) & 0xffu));
    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,0,0,0,1,2,3), val));
    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);
    return;
  } else if constexpr (W == 16 && BW <= 8) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = ((_mm_cmpneq_epi8_mask(wb, zero) << 1) & 0xfffeu) | 1u;
    __m128i val = _mm_slli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 1);
    val = _mm_insert_epi8(val, static_cast<int>(r[0].val), 0);
    __mmask16 take = static_cast<__mmask16>((~valid) & ((valid << 1) & 0xffffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 1)); valid |= (valid << 1) & 0xffffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 2) & 0xffffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 2)); valid |= (valid << 2) & 0xffffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 4) & 0xffffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 4)); valid |= (valid << 4) & 0xffffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 8) & 0xffffu));
    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 8));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);
    return;
  } else if constexpr (W == 16 && BW > 16 && BW <= 32) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = ((_mm_cmpneq_epi8_mask(wb, zero) << 1) & 0xfffeu) | 1u;
    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));
    __m512i val = _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14), wd);
    val = _mm512_mask_mov_epi32(val, static_cast<__mmask16>(0x0001), _mm512_set1_epi32(static_cast<int>(r[0].val)));
    __mmask16 take = static_cast<__mmask16>((~valid) & ((valid << 1) & 0xffffu));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14), val)); valid |= (valid << 1) & 0xffffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 2) & 0xffffu));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13), val)); valid |= (valid << 2) & 0xffffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 4) & 0xffffu));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11), val)); valid |= (valid << 4) & 0xffffu;
    take = static_cast<__mmask16>((~valid) & ((valid << 8) & 0xffffu));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7), val));
    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);
    return;
  } else if constexpr (W == 32 && BW > 8 && BW <= 16) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m256i zero = _mm256_setzero_si256();
    const __m256i wb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen));
    uint32_t valid = (static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(wb, zero)) << 1) | 1u;
    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));
    const __m512i lane = _mm512_set_epi16(31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
    __m512i val = _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(1)), wd);
    val = _mm512_mask_mov_epi16(val, static_cast<__mmask32>(0x00000001u), _mm512_set1_epi16(static_cast<short>(r[0].val)));
    __mmask32 take = static_cast<__mmask32>((~valid) & (valid << 1));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(1)), val)); valid |= valid << 1;
    take = static_cast<__mmask32>((~valid) & (valid << 2));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(2)), val)); valid |= valid << 2;
    take = static_cast<__mmask32>((~valid) & (valid << 4));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(4)), val)); valid |= valid << 4;
    take = static_cast<__mmask32>((~valid) & (valid << 8));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(8)), val)); valid |= valid << 8;
    take = static_cast<__mmask32>((~valid) & (valid << 16));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(16)), val));
    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);
    return;
  }
#if !defined(CHISA_NO_SCAN_COMPOSE)
  else if constexpr (W == 16 || W == 32) {
    constexpr int H = W / 2;
    essent_condhold_scan_fwd<H, BW>(r, wen, wdata);
    r[H] = essent_to_u64(wen[H - 1]) ? wdata[H - 1] : r[H - 1];
    essent_condhold_scan_fwd<H, BW>(r + H, wen + H, wdata + H);
    return;
  }
#endif
#endif
  for (int L = 1; L < W; L++) r[L] = essent_to_u64(wen[L - 1]) ? wdata[L - 1] : r[L - 1];
}

template <int W, int BW>
static inline void essent_condhold_scan_rev(UInt<BW>* __restrict r, const UInt<1>* __restrict wen, const UInt<BW>* __restrict wdata) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 8 && BW <= 8) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;
    __m128i val = _mm_srli_si128(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(wdata)), 1);
    val = _mm_insert_epi8(val, static_cast<int>(r[7].val), 7);
    __mmask16 take = static_cast<__mmask16>((~valid) & (valid >> 1));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 1)); valid |= valid >> 1;
    take = static_cast<__mmask16>((~valid) & (valid >> 2));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 2)); valid |= valid >> 2;
    take = static_cast<__mmask16>((~valid) & (valid >> 4));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 4));
    _mm_storel_epi64(reinterpret_cast<__m128i*>(r), val);
    return;
  } else if constexpr (W == 8 && BW > 8 && BW <= 16) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;
    __m128i val = _mm_srli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 2);
    val = _mm_insert_epi16(val, static_cast<int>(r[7].val), 7);
    __mmask8 take = static_cast<__mmask8>((~valid) & (valid >> 1));
    val = _mm_mask_mov_epi16(val, take, _mm_srli_si128(val, 2)); valid |= valid >> 1;
    take = static_cast<__mmask8>((~valid) & (valid >> 2));
    val = _mm_mask_mov_epi16(val, take, _mm_srli_si128(val, 4)); valid |= valid >> 2;
    take = static_cast<__mmask8>((~valid) & (valid >> 4));
    val = _mm_mask_mov_epi16(val, take, _mm_srli_si128(val, 8));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);
    return;
  } else if constexpr (W == 8 && BW > 16 && BW <= 32) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;
    const __m256i wd = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wdata));
    __m256i val = _mm256_permutevar8x32_epi32(wd, _mm256_setr_epi32(1,2,3,4,5,6,7,7));
    val = _mm256_mask_mov_epi32(val, static_cast<__mmask8>(0x80), _mm256_set1_epi32(static_cast<int>(r[7].val)));
    __mmask8 take = static_cast<__mmask8>((~valid) & (valid >> 1));
    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(1,2,3,4,5,6,7,7))); valid |= valid >> 1;
    take = static_cast<__mmask8>((~valid) & (valid >> 2));
    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(2,3,4,5,6,7,7,7))); valid |= valid >> 2;
    take = static_cast<__mmask8>((~valid) & (valid >> 4));
    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(4,5,6,7,7,7,7,7)));
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(r), val);
    return;
  } else if constexpr (W == 8 && BW > 32 && BW <= 64) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;
    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));
    __m512i val = _mm512_permutexvar_epi64(_mm512_setr_epi64(1,2,3,4,5,6,7,7), wd);
    val = _mm512_mask_mov_epi64(val, static_cast<__mmask8>(0x80), _mm512_set1_epi64(static_cast<long long>(r[7].val)));
    __mmask8 take = static_cast<__mmask8>((~valid) & (valid >> 1));
    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(1,2,3,4,5,6,7,7), val)); valid |= valid >> 1;
    take = static_cast<__mmask8>((~valid) & (valid >> 2));
    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(2,3,4,5,6,7,7,7), val)); valid |= valid >> 2;
    take = static_cast<__mmask8>((~valid) & (valid >> 4));
    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(4,5,6,7,7,7,7,7), val));
    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);
    return;
  } else if constexpr (W == 16 && BW <= 8) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = (_mm_cmpneq_epi8_mask(wb, zero) >> 1) | 0x8000u;
    __m128i val = _mm_srli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 1);
    val = _mm_insert_epi8(val, static_cast<int>(r[15].val), 15);
    __mmask16 take = static_cast<__mmask16>((~valid) & (valid >> 1));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 1)); valid |= valid >> 1;
    take = static_cast<__mmask16>((~valid) & (valid >> 2));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 2)); valid |= valid >> 2;
    take = static_cast<__mmask16>((~valid) & (valid >> 4));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 4)); valid |= valid >> 4;
    take = static_cast<__mmask16>((~valid) & (valid >> 8));
    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 8));
    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);
    return;
  } else if constexpr (W == 16 && BW > 16 && BW <= 32) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m128i zero = _mm_setzero_si128();
    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));
    uint32_t valid = (_mm_cmpneq_epi8_mask(wb, zero) >> 1) | 0x8000u;
    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));
    __m512i val = _mm512_permutexvar_epi32(_mm512_setr_epi32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15), wd);
    val = _mm512_mask_mov_epi32(val, static_cast<__mmask16>(0x8000), _mm512_set1_epi32(static_cast<int>(r[15].val)));
    __mmask16 take = static_cast<__mmask16>((~valid) & (valid >> 1));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15), val)); valid |= valid >> 1;
    take = static_cast<__mmask16>((~valid) & (valid >> 2));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,15), val)); valid |= valid >> 2;
    take = static_cast<__mmask16>((~valid) & (valid >> 4));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(4,5,6,7,8,9,10,11,12,13,14,15,15,15,15,15), val)); valid |= valid >> 4;
    take = static_cast<__mmask16>((~valid) & (valid >> 8));
    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(8,9,10,11,12,13,14,15,15,15,15,15,15,15,15,15), val));
    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);
    return;
  } else if constexpr (W == 32 && BW > 8 && BW <= 16) {
    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));
    const __m256i zero = _mm256_setzero_si256();
    const __m256i wb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen));
    uint32_t valid = (static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80000000u;
    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));
    const __m512i lane = _mm512_set_epi16(31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);
    const __m512i top = _mm512_set1_epi16(31);
    __m512i val = _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(1)), top), wd);
    val = _mm512_mask_mov_epi16(val, static_cast<__mmask32>(0x80000000u), _mm512_set1_epi16(static_cast<short>(r[31].val)));
    __mmask32 take = static_cast<__mmask32>((~valid) & (valid >> 1));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(1)), top), val)); valid |= valid >> 1;
    take = static_cast<__mmask32>((~valid) & (valid >> 2));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(2)), top), val)); valid |= valid >> 2;
    take = static_cast<__mmask32>((~valid) & (valid >> 4));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(4)), top), val)); valid |= valid >> 4;
    take = static_cast<__mmask32>((~valid) & (valid >> 8));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(8)), top), val)); valid |= valid >> 8;
    take = static_cast<__mmask32>((~valid) & (valid >> 16));
    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(16)), top), val));
    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);
    return;
  }
#if !defined(CHISA_NO_SCAN_COMPOSE)
  else if constexpr (W == 16 || W == 32) {
    constexpr int H = W / 2;
    essent_condhold_scan_rev<H, BW>(r + H, wen + H, wdata + H);
    r[H - 1] = essent_to_u64(wen[H]) ? wdata[H] : r[H];
    essent_condhold_scan_rev<H, BW>(r, wen, wdata);
    return;
  }
#endif
#endif
  for (int L = W - 2; L >= 0; L--) r[L] = essent_to_u64(wen[L + 1]) ? wdata[L + 1] : r[L + 1];
}

template <int W, int BW>
static inline void essent_condhold_scan_fwd(SInt<BW>* __restrict r, const UInt<1>* __restrict wen, const SInt<BW>* __restrict wdata) {
  for (int L = 1; L < W; L++) r[L] = essent_to_u64(wen[L - 1]) ? wdata[L - 1] : r[L - 1];
}
template <int W, int BW>
static inline void essent_condhold_scan_rev(SInt<BW>* __restrict r, const UInt<1>* __restrict wen, const SInt<BW>* __restrict wdata) {
  for (int L = W - 2; L >= 0; L--) r[L] = essent_to_u64(wen[L + 1]) ? wdata[L + 1] : r[L + 1];
}

template <int W>
static inline uint64_t essent_pack_u1(const UInt<1>* __restrict v) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 16) {
    return _mm_test_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(v)), _mm_set1_epi8(1));
  } else if constexpr (W == 32) {
    return _mm256_test_epi8_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(v)), _mm256_set1_epi8(1));
  }
#endif
  uint64_t m = 0;
  ESSENT_LANE_LOOP
  for (int L = 0; L < W; L++) m |= (uint64_t)(v[L].val & 1u) << L;
  return m;
}
template <int W>
static inline void essent_unpack_u1(UInt<1>* __restrict v, uint64_t m) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 16) {
    _mm_storeu_si128(reinterpret_cast<__m128i*>(v), _mm_maskz_set1_epi8(static_cast<__mmask16>(m), 1));
    return;
  } else if constexpr (W == 32) {
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(v), _mm256_maskz_set1_epi8(static_cast<__mmask32>(m), 1));
    return;
  }
#endif
  ESSENT_LANE_LOOP
  for (int L = 0; L < W; L++) v[L].val = (uint8_t)((m >> L) & 1u);
}
template <int W, typename S>
static inline uint64_t essent_pack_cmp_eq(const S* __restrict a, const S* __restrict b) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 16 && sizeof(S) == 1) {
    return _mm_cmpeq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(a)), _mm_loadu_si128(reinterpret_cast<const __m128i*>(b)));
  } else if constexpr (W == 16 && sizeof(S) == 2) {
    return _mm256_cmpeq_epi16_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(a)), _mm256_loadu_si256(reinterpret_cast<const __m256i*>(b)));
  } else if constexpr (W == 16 && sizeof(S) == 4) {
    return _mm512_cmpeq_epi32_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), _mm512_loadu_si512(reinterpret_cast<const void*>(b)));
  } else if constexpr (W == 16 && sizeof(S) == 8) {
    const __mmask8 lo = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), _mm512_loadu_si512(reinterpret_cast<const void*>(b)));
    const __mmask8 hi = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a + 8)), _mm512_loadu_si512(reinterpret_cast<const void*>(b + 8)));
    return (uint64_t)lo | ((uint64_t)hi << 8);
  }
#endif
  uint64_t m = 0;
  for (int L = 0; L < W; L++) m |= (uint64_t)(a[L] == b[L]) << L;
  return m;
}
template <int W, typename S>
static inline uint64_t essent_pack_cmp_eq_k(const S* __restrict a, uint64_t k) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 16 && sizeof(S) == 1) {
    return _mm_cmpeq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(a)), _mm_set1_epi8((char)k));
  } else if constexpr (W == 16 && sizeof(S) == 2) {
    return _mm256_cmpeq_epi16_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(a)), _mm256_set1_epi16((short)k));
  } else if constexpr (W == 16 && sizeof(S) == 4) {
    return _mm512_cmpeq_epi32_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), _mm512_set1_epi32((int)k));
  } else if constexpr (W == 16 && sizeof(S) == 8) {
    const __m512i kk = _mm512_set1_epi64((long long)k);
    const __mmask8 lo = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), kk);
    const __mmask8 hi = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a + 8)), kk);
    return (uint64_t)lo | ((uint64_t)hi << 8);
  }
#endif
  uint64_t m = 0;
  for (int L = 0; L < W; L++) m |= (uint64_t)(a[L] == (S)k) << L;
  return m;
}

#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__) && defined(__AVX512VBMI__)
#define ESSENT_AFFINE_SCAN_VECTOR 1
// ---- 512-bit lane ops (EB bytes per lane, N = 64 / EB lanes) ----
template <int EB> struct essent_zmm_ops;
template <> struct essent_zmm_ops<1> {
  using V = __m512i; using K = __mmask64; static constexpr int N = 64;
  static inline V iota() { alignas(64) static const uint8_t t[64] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi8(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi8(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi8(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi8(static_cast<char>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_subs_epu8(iota(), set1(static_cast<uint64_t>(s))); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epu8(_mm512_adds_epu8(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm512_loadu_si512(reinterpret_cast<const void*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm512_storeu_si512(reinterpret_cast<void*>(p), v); }
};
template <> struct essent_zmm_ops<2> {
  using V = __m512i; using K = __mmask32; static constexpr int N = 32;
  static inline V iota() { alignas(64) static const uint16_t t[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi16(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi16(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi16(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi16(static_cast<short>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_max_epi16(_mm512_sub_epi16(iota(), set1(static_cast<uint64_t>(s))), _mm512_setzero_si512()); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epi16(_mm512_add_epi16(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) {
    if constexpr (sizeof(S) == 2) return _mm512_loadu_si512(reinterpret_cast<const void*>(p));
    else return _mm512_cvtepu8_epi16(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
  }
  template <typename S> static inline void store(S* p, V v) {
    if constexpr (sizeof(S) == 2) _mm512_storeu_si512(reinterpret_cast<void*>(p), v);
    else _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), _mm512_cvtepi16_epi8(v));
  }
};
template <> struct essent_zmm_ops<4> {
  using V = __m512i; using K = __mmask16; static constexpr int N = 16;
  static inline V iota() { alignas(64) static const uint32_t t[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi32(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi32(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi32(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi32(static_cast<int>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_max_epi32(_mm512_sub_epi32(iota(), set1(static_cast<uint64_t>(s))), _mm512_setzero_si512()); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epi32(_mm512_add_epi32(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) {
    if constexpr (sizeof(S) == 4) return _mm512_loadu_si512(reinterpret_cast<const void*>(p));
    else if constexpr (sizeof(S) == 2) return _mm512_cvtepu16_epi32(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
    else return _mm512_cvtepu8_epi32(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p)));
  }
  template <typename S> static inline void store(S* p, V v) {
    if constexpr (sizeof(S) == 4) _mm512_storeu_si512(reinterpret_cast<void*>(p), v);
    else if constexpr (sizeof(S) == 2) _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), _mm512_cvtepi32_epi16(v));
    else _mm_storeu_si128(reinterpret_cast<__m128i*>(p), _mm512_cvtepi32_epi8(v));
  }
};
template <> struct essent_zmm_ops<8> {
  using V = __m512i; using K = __mmask8; static constexpr int N = 8;
  static inline V iota() { alignas(64) static const uint64_t t[8] = {0, 1, 2, 3, 4, 5, 6, 7}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi64(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi64(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi64(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi64(static_cast<long long>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_max_epi64(_mm512_sub_epi64(iota(), set1(static_cast<uint64_t>(s))), _mm512_setzero_si512()); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epi64(_mm512_add_epi64(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) {
    if constexpr (sizeof(S) == 8) return _mm512_loadu_si512(reinterpret_cast<const void*>(p));
    else if constexpr (sizeof(S) == 4) return _mm512_cvtepu32_epi64(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
    else if constexpr (sizeof(S) == 2) return _mm512_cvtepu16_epi64(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p)));
    else return _mm512_cvtepu8_epi64(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(p)));
  }
  template <typename S> static inline void store(S* p, V v) {
    if constexpr (sizeof(S) == 8) _mm512_storeu_si512(reinterpret_cast<void*>(p), v);
    else if constexpr (sizeof(S) == 4) _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), _mm512_cvtepi64_epi32(v));
    else if constexpr (sizeof(S) == 2) _mm_storeu_si128(reinterpret_cast<__m128i*>(p), _mm512_cvtepi64_epi16(v));
    else _mm_storel_epi64(reinterpret_cast<__m128i*>(p), _mm512_cvtepi64_epi8(v));
  }
};
// ---- 256-bit native-lane ops (EB bytes per lane, N = 32 / EB lanes) ----
template <int EB> struct essent_ymm_ops;
template <> struct essent_ymm_ops<1> {
  using V = __m256i; using K = __mmask32; static constexpr int N = 32;
  static inline V iota() { alignas(32) static const uint8_t t[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}; return _mm256_load_si256(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm256_permutexvar_epi8(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm256_mask_add_epi8(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm256_mask_mov_epi8(src, m, a); }
  static inline V set1(uint64_t v) { return _mm256_set1_epi8(static_cast<char>(v)); }
  static inline V and_(V a, V b) { return _mm256_and_si256(a, b); }
  static inline V idx_fwd(int s) { return _mm256_subs_epu8(iota(), set1(static_cast<uint64_t>(s))); }
  static inline V idx_rev(int s, int last) { return _mm256_min_epu8(_mm256_adds_epu8(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm256_loadu_si256(reinterpret_cast<const V*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm256_storeu_si256(reinterpret_cast<V*>(p), v); }
};
template <> struct essent_ymm_ops<2> {
  using V = __m256i; using K = __mmask16; static constexpr int N = 16;
  static inline V iota() { alignas(32) static const uint16_t t[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; return _mm256_load_si256(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm256_permutexvar_epi16(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm256_mask_add_epi16(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm256_mask_mov_epi16(src, m, a); }
  static inline V set1(uint64_t v) { return _mm256_set1_epi16(static_cast<short>(v)); }
  static inline V and_(V a, V b) { return _mm256_and_si256(a, b); }
  static inline V idx_fwd(int s) { return _mm256_max_epi16(_mm256_sub_epi16(iota(), set1(static_cast<uint64_t>(s))), _mm256_setzero_si256()); }
  static inline V idx_rev(int s, int last) { return _mm256_min_epi16(_mm256_add_epi16(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm256_loadu_si256(reinterpret_cast<const V*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm256_storeu_si256(reinterpret_cast<V*>(p), v); }
};
template <> struct essent_ymm_ops<4> {
  using V = __m256i; using K = __mmask8; static constexpr int N = 8;
  static inline V iota() { alignas(32) static const uint32_t t[8] = {0, 1, 2, 3, 4, 5, 6, 7}; return _mm256_load_si256(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm256_permutexvar_epi32(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm256_mask_add_epi32(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm256_mask_mov_epi32(src, m, a); }
  static inline V set1(uint64_t v) { return _mm256_set1_epi32(static_cast<int>(v)); }
  static inline V and_(V a, V b) { return _mm256_and_si256(a, b); }
  static inline V idx_fwd(int s) { return _mm256_max_epi32(_mm256_sub_epi32(iota(), set1(static_cast<uint64_t>(s))), _mm256_setzero_si256()); }
  static inline V idx_rev(int s, int last) { return _mm256_min_epi32(_mm256_add_epi32(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm256_loadu_si256(reinterpret_cast<const V*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm256_storeu_si256(reinterpret_cast<V*>(p), v); }
};
template <int W>
static inline uint64_t essent_keep_mask(const UInt<1>* keep) {
  static_assert(sizeof(UInt<1>) == 1);
  const void* p = reinterpret_cast<const void*>(keep);
  if constexpr (W == 64) { const __m512i v = _mm512_loadu_si512(p); return static_cast<uint64_t>(_mm512_test_epi8_mask(v, v)); }
  else if constexpr (W == 32) { const __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return static_cast<uint64_t>(_mm256_test_epi8_mask(v, v)); }
  else if constexpr (W == 16) { const __m128i v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p)); return static_cast<uint64_t>(_mm_test_epi8_mask(v, v)); }
  else { const __m128i v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(p)); return static_cast<uint64_t>(_mm_test_epi8_mask(v, v)) & 0xffull; }
}
// Quiet-window test: no lane adds anything (all add lanes zero).
static inline bool essent_vec_all_zero(__m512i v) { return _mm512_test_epi64_mask(v, v) == 0; }
static inline bool essent_vec_all_zero(__m256i v) { return _mm256_testz_si256(v, v) != 0; }
// Forward scan body: time order = increasing lane index, seed = r[0].
template <class O, int W, int BW, typename S>
static inline void essent_affine_scan_body_fwd(S* r, const UInt<1>* keep, const S* add) {
  using K = typename O::K;
  using V = typename O::V;
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
  constexpr uint64_t ALL = (W == 64) ? ~0ull : ((1ull << W) - 1ull);
  constexpr bool needMask = BW < 8 * (O::N == W ? static_cast<int>(sizeof(S)) : 64 / W);
  const V vm = O::set1(M);
  uint64_t k = essent_keep_mask<W>(keep);
  V a = O::template load<S>(add);
  const V vs = O::set1(static_cast<uint64_t>(r[0]));
  if (__builtin_expect(k == ALL, 1)) {
    // Plain prefix sum (no clear inside the window). Quiet window: hold.
    if (essent_vec_all_zero(a)) { O::template store<S>(r, vs); return; }
    for (int s = 1; s < W; s <<= 1) {
      const uint64_t low = (1ull << s) - 1ull;
      a = O::mask_add(a, static_cast<K>(ALL & ~low), a, O::perm(O::idx_fwd(s), a));
      if constexpr (needMask) a = O::and_(a, vm);
    }
    V out = O::mask_add(vs, static_cast<K>(ALL & ~1ull), vs, O::perm(O::idx_fwd(1), a));
    if constexpr (needMask) out = O::and_(out, vm);
    O::template store<S>(r, out);
    return;
  }
  for (int s = 1; s < W; s <<= 1) {
    const uint64_t low = (1ull << s) - 1ull;
    const V sh = O::perm(O::idx_fwd(s), a);
    a = O::mask_add(a, static_cast<K>(k & ~low), a, sh);
    if constexpr (needMask) a = O::and_(a, vm);
    k = k & ((k << s) | low) & ALL;
  }
  V out = O::perm(O::idx_fwd(1), a);
  out = O::mask_add(out, static_cast<K>((k << 1) & ALL), out, vs);
  if constexpr (needMask) out = O::and_(out, vm);
  out = O::mask_mov(out, static_cast<K>(1), vs);
  O::template store<S>(r, out);
}
// Reverse scan body: time order = decreasing lane index, seed = r[W-1].
template <class O, int W, int BW, typename S>
static inline void essent_affine_scan_body_rev(S* r, const UInt<1>* keep, const S* add) {
  using K = typename O::K;
  using V = typename O::V;
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
  constexpr uint64_t ALL = (W == 64) ? ~0ull : ((1ull << W) - 1ull);
  constexpr bool needMask = BW < 8 * (O::N == W ? static_cast<int>(sizeof(S)) : 64 / W);
  const V vm = O::set1(M);
  uint64_t k = essent_keep_mask<W>(keep);
  V a = O::template load<S>(add);
  const V vs = O::set1(static_cast<uint64_t>(r[W - 1]));
  if (__builtin_expect(k == ALL, 1)) {
    if (essent_vec_all_zero(a)) { O::template store<S>(r, vs); return; }
    for (int s = 1; s < W; s <<= 1) {
      const uint64_t high = ALL & ~((1ull << (W - s)) - 1ull);
      a = O::mask_add(a, static_cast<K>(ALL & ~high), a, O::perm(O::idx_rev(s, W - 1), a));
      if constexpr (needMask) a = O::and_(a, vm);
    }
    V out = O::mask_add(vs, static_cast<K>(ALL >> 1), vs, O::perm(O::idx_rev(1, W - 1), a));
    if constexpr (needMask) out = O::and_(out, vm);
    O::template store<S>(r, out);
    return;
  }
  for (int s = 1; s < W; s <<= 1) {
    const uint64_t high = ALL & ~((1ull << (W - s)) - 1ull);
    const V sh = O::perm(O::idx_rev(s, W - 1), a);
    a = O::mask_add(a, static_cast<K>(k & ~high), a, sh);
    if constexpr (needMask) a = O::and_(a, vm);
    k = k & ((k >> s) | high);
  }
  V out = O::perm(O::idx_rev(1, W - 1), a);
  out = O::mask_add(out, static_cast<K>(k >> 1), out, vs);
  if constexpr (needMask) out = O::and_(out, vm);
  out = O::mask_mov(out, static_cast<K>(1ull << (W - 1)), vs);
  O::template store<S>(r, out);
}
#endif

template <int W, int BW>
static inline void essent_affine_scan_fwd(UInt<BW>* __restrict r, const UInt<1>* __restrict keep, const UInt<BW>* __restrict add) {
  using S = typename UInt<BW>::scalar_t;
  static_assert(sizeof(UInt<BW>) == sizeof(S), "affine scan needs scalar register storage");
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
#if defined(ESSENT_AFFINE_SCAN_VECTOR)
  if constexpr (W * sizeof(S) == 32 && (W == 8 || W == 16 || W == 32)) {
    essent_affine_scan_body_fwd<essent_ymm_ops<32 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr ((W == 16 || W == 32 || W == 64) && sizeof(S) <= 64 / W) {
    essent_affine_scan_body_fwd<essent_zmm_ops<64 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr (W >= 16 && (W & (W - 1)) == 0) {
    constexpr int H = W / 2;
    essent_affine_scan_fwd<H, BW>(r, keep, add);
    r[H].val = static_cast<S>((keep[H - 1].val ? static_cast<S>(r[H - 1].val + add[H - 1].val) : add[H - 1].val) & M);
    essent_affine_scan_fwd<H, BW>(r + H, keep + H, add + H);
    return;
  }
#endif
  for (int L = 1; L < W; L++) r[L].val = static_cast<S>((keep[L - 1].val ? static_cast<S>(r[L - 1].val + add[L - 1].val) : add[L - 1].val) & M);
}

template <int W, int BW>
static inline void essent_affine_scan_rev(UInt<BW>* __restrict r, const UInt<1>* __restrict keep, const UInt<BW>* __restrict add) {
  using S = typename UInt<BW>::scalar_t;
  static_assert(sizeof(UInt<BW>) == sizeof(S), "affine scan needs scalar register storage");
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
#if defined(ESSENT_AFFINE_SCAN_VECTOR)
  if constexpr (W * sizeof(S) == 32 && (W == 8 || W == 16 || W == 32)) {
    essent_affine_scan_body_rev<essent_ymm_ops<32 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr ((W == 16 || W == 32 || W == 64) && sizeof(S) <= 64 / W) {
    essent_affine_scan_body_rev<essent_zmm_ops<64 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr (W >= 16 && (W & (W - 1)) == 0) {
    constexpr int H = W / 2;
    essent_affine_scan_rev<H, BW>(r + H, keep + H, add + H);
    r[H - 1].val = static_cast<S>((keep[H].val ? static_cast<S>(r[H].val + add[H].val) : add[H].val) & M);
    essent_affine_scan_rev<H, BW>(r, keep, add);
    return;
  }
#endif
  for (int L = W - 2; L >= 0; L--) r[L].val = static_cast<S>((keep[L + 1].val ? static_cast<S>(r[L + 1].val + add[L + 1].val) : add[L + 1].val) & M);
}

// v2 produced-local scratch, file-scope static (138 arrays).
// Not per-Top-instance; eval overwrites scratch before use.
alignas(16) static UInt<1> _s__T_248[16];
alignas(16) static UInt<1> _s__T_250[16];
alignas(16) static UInt<4> _s__T_253[16];
alignas(16) static UInt<1> _s__T_254[16];
alignas(16) static UInt<1> _s__T_259[16];
alignas(16) static UInt<1> _s__T_260[16];
alignas(16) static UInt<1> _s__T_335[16];
alignas(16) static UInt<1> _s__T_395[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_0[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_1[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_2[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_3[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_4[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_5[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_6[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_7[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_8[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_9[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_10[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_11[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_12[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_13[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_14[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_in_15[16];
alignas(16) static UInt<8> _s_state_0$next[16];
alignas(16) static UInt<8> _s_state_1$next[16];
alignas(16) static UInt<8> _s_state_2$next[16];
alignas(16) static UInt<8> _s_state_3$next[16];
alignas(16) static UInt<8> _s_state_4$next[16];
alignas(16) static UInt<8> _s_state_5$next[16];
alignas(16) static UInt<8> _s_state_6$next[16];
alignas(16) static UInt<8> _s_state_7$next[16];
alignas(16) static UInt<8> _s_state_8$next[16];
alignas(16) static UInt<8> _s_state_9$next[16];
alignas(16) static UInt<8> _s_state_10$next[16];
alignas(16) static UInt<8> _s_state_11$next[16];
alignas(16) static UInt<8> _s_state_12$next[16];
alignas(16) static UInt<8> _s_state_13$next[16];
alignas(16) static UInt<8> _s_state_14$next[16];
alignas(16) static UInt<8> _s_state_15$next[16];
alignas(16) static UInt<4> _s_rounds$next[16];
alignas(16) static UInt<2> _s_STM$next[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_0[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_1[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_2[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_3[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_4[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_5[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_6[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_7[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_8[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_9[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_10[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_11[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_12[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_13[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_14[16];
alignas(16) static UInt<8> _s_AddRoundKeyModule$io_state_out_15[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_0[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_1[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_2[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_3[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_4[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_5[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_6[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_7[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_8[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_9[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_10[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_11[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_12[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_13[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_14[16];
alignas(16) static UInt<8> _s_SubBytesModule$io_state_out_15[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_0[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_1[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_2[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_3[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_4[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_5[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_6[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_7[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_8[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_9[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_10[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_11[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_12[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_13[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_14[16];
alignas(16) static UInt<8> _s_MixColumnsModule$io_state_out_15[16];
alignas(16) static UInt<8> _s_lut$eq_0[16];
alignas(16) static UInt<8> _s_lut$eq_1[16];
alignas(16) static UInt<8> _s_lut$eq_2[16];
alignas(16) static UInt<8> _s_lut$eq_3[16];
alignas(16) static UInt<8> _s_lut$eq_4[16];
alignas(16) static UInt<8> _s_lut$eq_5[16];
alignas(16) static UInt<8> _s_lut$eq_6[16];
alignas(16) static UInt<8> _s_lut$eq_7[16];
alignas(16) static UInt<8> _s_lut$eq_8[16];
alignas(16) static UInt<8> _s_lut$eq_9[16];
alignas(16) static UInt<8> _s_lut$eq_10[16];
alignas(16) static UInt<8> _s_lut$eq_11[16];
alignas(16) static UInt<8> _s_lut$eq_12[16];
alignas(16) static UInt<8> _s_lut$eq_13[16];
alignas(16) static UInt<8> _s_lut$eq_14[16];
alignas(16) static UInt<8> _s_lut$eq_15[16];
alignas(16) static UInt<8> _s_lut$eq_16[16];
alignas(16) static UInt<8> _s_lut$eq_17[16];
alignas(16) static UInt<8> _s_lut$eq_18[16];
alignas(16) static UInt<8> _s_lut$eq_19[16];
alignas(16) static UInt<8> _s_lut$eq_20[16];
alignas(16) static UInt<8> _s_lut$eq_21[16];
alignas(16) static UInt<8> _s_lut$eq_22[16];
alignas(16) static UInt<8> _s_lut$eq_23[16];
alignas(16) static UInt<8> _s_lut$eq_24[16];
alignas(16) static UInt<8> _s_lut$eq_25[16];
alignas(16) static UInt<8> _s_lut$eq_26[16];
alignas(16) static UInt<8> _s_lut$eq_27[16];
alignas(16) static UInt<8> _s_lut$eq_28[16];
alignas(16) static UInt<8> _s_lut$eq_29[16];
alignas(16) static UInt<8> _s_lut$eq_30[16];
alignas(16) static UInt<8> _s_lut$eq_31[16];
alignas(16) static UInt<8> _s_lut$eq_32[16];
alignas(16) static UInt<8> _s_lut$eq_33[16];
alignas(16) static UInt<8> _s_lut$eq_34[16];
alignas(16) static UInt<8> _s_lut$eq_35[16];
alignas(16) static UInt<8> _s_lut$eq_36[16];
alignas(16) static UInt<8> _s_lut$eq_37[16];
alignas(16) static UInt<8> _s_lut$eq_38[16];
alignas(16) static UInt<8> _s_lut$eq_39[16];
alignas(16) static UInt<8> _s_lut$eq_40[16];
alignas(16) static UInt<8> _s_lut$eq_41[16];
alignas(16) static UInt<8> _s_lut$eq_42[16];
alignas(16) static UInt<8> _s_lut$eq_43[16];
alignas(16) static UInt<8> _s_lut$eq_44[16];
alignas(16) static UInt<8> _s_lut$eq_45[16];
alignas(16) static UInt<8> _s_lut$eq_46[16];
alignas(16) static UInt<8> _s_lut$eq_47[16];

// v2 lookup tables (48), file-scope constants shared by every lane and direction.
alignas(64) static const uint8_t _lut_lut$eq_0[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_1[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_2[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_3[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_4[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_5[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_6[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_7[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_8[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_9[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_10[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_11[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_12[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_13[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_14[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_15[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_16[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_17[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_18[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_19[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_20[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_21[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_22[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_23[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_24[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_25[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_26[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_27[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_28[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_29[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_30[] = {0x0U, 0x3U, 0x6U, 0x5U, 0xcU, 0xfU, 0xaU, 0x9U, 0x18U, 0x1bU, 0x1eU, 0x1dU, 0x14U, 0x17U, 0x12U, 0x11U, 0x30U, 0x33U, 0x36U, 0x35U, 0x3cU, 0x3fU, 0x3aU, 0x39U, 0x28U, 0x2bU, 0x2eU, 0x2dU, 0x24U, 0x27U, 0x22U, 0x21U, 0x60U, 0x63U, 0x66U, 0x65U, 0x6cU, 0x6fU, 0x6aU, 0x69U, 0x78U, 0x7bU, 0x7eU, 0x7dU, 0x74U, 0x77U, 0x72U, 0x71U, 0x50U, 0x53U, 0x56U, 0x55U, 0x5cU, 0x5fU, 0x5aU, 0x59U, 0x48U, 0x4bU, 0x4eU, 0x4dU, 0x44U, 0x47U, 0x42U, 0x41U, 0xc0U, 0xc3U, 0xc6U, 0xc5U, 0xccU, 0xcfU, 0xcaU, 0xc9U, 0xd8U, 0xdbU, 0xdeU, 0xddU, 0xd4U, 0xd7U, 0xd2U, 0xd1U, 0xf0U, 0xf3U, 0xf6U, 0xf5U, 0xfcU, 0xffU, 0xfaU, 0xf9U, 0xe8U, 0xebU, 0xeeU, 0xedU, 0xe4U, 0xe7U, 0xe2U, 0xe1U, 0xa0U, 0xa3U, 0xa6U, 0xa5U, 0xacU, 0xafU, 0xaaU, 0xa9U, 0xb8U, 0xbbU, 0xbeU, 0xbdU, 0xb4U, 0xb7U, 0xb2U, 0xb1U, 0x90U, 0x93U, 0x96U, 0x95U, 0x9cU, 0x9fU, 0x9aU, 0x99U, 0x88U, 0x8bU, 0x8eU, 0x8dU, 0x84U, 0x87U, 0x82U, 0x81U, 0x9bU, 0x98U, 0x9dU, 0x9eU, 0x97U, 0x94U, 0x91U, 0x92U, 0x83U, 0x80U, 0x85U, 0x86U, 0x8fU, 0x8cU, 0x89U, 0x8aU, 0xabU, 0xa8U, 0xadU, 0xaeU, 0xa7U, 0xa4U, 0xa1U, 0xa2U, 0xb3U, 0xb0U, 0xb5U, 0xb6U, 0xbfU, 0xbcU, 0xb9U, 0xbaU, 0xfbU, 0xf8U, 0xfdU, 0xfeU, 0xf7U, 0xf4U, 0xf1U, 0xf2U, 0xe3U, 0xe0U, 0xe5U, 0xe6U, 0xefU, 0xecU, 0xe9U, 0xeaU, 0xcbU, 0xc8U, 0xcdU, 0xceU, 0xc7U, 0xc4U, 0xc1U, 0xc2U, 0xd3U, 0xd0U, 0xd5U, 0xd6U, 0xdfU, 0xdcU, 0xd9U, 0xdaU, 0x5bU, 0x58U, 0x5dU, 0x5eU, 0x57U, 0x54U, 0x51U, 0x52U, 0x43U, 0x40U, 0x45U, 0x46U, 0x4fU, 0x4cU, 0x49U, 0x4aU, 0x6bU, 0x68U, 0x6dU, 0x6eU, 0x67U, 0x64U, 0x61U, 0x62U, 0x73U, 0x70U, 0x75U, 0x76U, 0x7fU, 0x7cU, 0x79U, 0x7aU, 0x3bU, 0x38U, 0x3dU, 0x3eU, 0x37U, 0x34U, 0x31U, 0x32U, 0x23U, 0x20U, 0x25U, 0x26U, 0x2fU, 0x2cU, 0x29U, 0x2aU, 0xbU, 0x8U, 0xdU, 0xeU, 0x7U, 0x4U, 0x1U, 0x2U, 0x13U, 0x10U, 0x15U, 0x16U, 0x1fU, 0x1cU, 0x19U, 0x1aU};
alignas(64) static const uint8_t _lut_lut$eq_31[] = {0x0U, 0x2U, 0x4U, 0x6U, 0x8U, 0xaU, 0xcU, 0xeU, 0x10U, 0x12U, 0x14U, 0x16U, 0x18U, 0x1aU, 0x1cU, 0x1eU, 0x20U, 0x22U, 0x24U, 0x26U, 0x28U, 0x2aU, 0x2cU, 0x2eU, 0x30U, 0x32U, 0x34U, 0x36U, 0x38U, 0x3aU, 0x3cU, 0x3eU, 0x40U, 0x42U, 0x44U, 0x46U, 0x48U, 0x4aU, 0x4cU, 0x4eU, 0x50U, 0x52U, 0x54U, 0x56U, 0x58U, 0x5aU, 0x5cU, 0x5eU, 0x60U, 0x62U, 0x64U, 0x66U, 0x68U, 0x6aU, 0x6cU, 0x6eU, 0x70U, 0x72U, 0x74U, 0x76U, 0x78U, 0x7aU, 0x7cU, 0x7eU, 0x80U, 0x82U, 0x84U, 0x86U, 0x88U, 0x8aU, 0x8cU, 0x8eU, 0x90U, 0x92U, 0x94U, 0x96U, 0x98U, 0x9aU, 0x9cU, 0x9eU, 0xa0U, 0xa2U, 0xa4U, 0xa6U, 0xa8U, 0xaaU, 0xacU, 0xaeU, 0xb0U, 0xb2U, 0xb4U, 0xb6U, 0xb8U, 0xbaU, 0xbcU, 0xbeU, 0xc0U, 0xc2U, 0xc4U, 0xc6U, 0xc8U, 0xcaU, 0xccU, 0xceU, 0xd0U, 0xd2U, 0xd4U, 0xd6U, 0xd8U, 0xdaU, 0xdcU, 0xdeU, 0xe0U, 0xe2U, 0xe4U, 0xe6U, 0xe8U, 0xeaU, 0xecU, 0xeeU, 0xf0U, 0xf2U, 0xf4U, 0xf6U, 0xf8U, 0xfaU, 0xfcU, 0xfeU, 0x1bU, 0x19U, 0x1fU, 0x1dU, 0x13U, 0x11U, 0x17U, 0x15U, 0xbU, 0x9U, 0xfU, 0xdU, 0x3U, 0x1U, 0x7U, 0x5U, 0x3bU, 0x39U, 0x3fU, 0x3dU, 0x33U, 0x31U, 0x37U, 0x35U, 0x2bU, 0x29U, 0x2fU, 0x2dU, 0x23U, 0x21U, 0x27U, 0x25U, 0x5bU, 0x59U, 0x5fU, 0x5dU, 0x53U, 0x51U, 0x57U, 0x55U, 0x4bU, 0x49U, 0x4fU, 0x4dU, 0x43U, 0x41U, 0x47U, 0x45U, 0x7bU, 0x79U, 0x7fU, 0x7dU, 0x73U, 0x71U, 0x77U, 0x75U, 0x6bU, 0x69U, 0x6fU, 0x6dU, 0x63U, 0x61U, 0x67U, 0x65U, 0x9bU, 0x99U, 0x9fU, 0x9dU, 0x93U, 0x91U, 0x97U, 0x95U, 0x8bU, 0x89U, 0x8fU, 0x8dU, 0x83U, 0x81U, 0x87U, 0x85U, 0xbbU, 0xb9U, 0xbfU, 0xbdU, 0xb3U, 0xb1U, 0xb7U, 0xb5U, 0xabU, 0xa9U, 0xafU, 0xadU, 0xa3U, 0xa1U, 0xa7U, 0xa5U, 0xdbU, 0xd9U, 0xdfU, 0xddU, 0xd3U, 0xd1U, 0xd7U, 0xd5U, 0xcbU, 0xc9U, 0xcfU, 0xcdU, 0xc3U, 0xc1U, 0xc7U, 0xc5U, 0xfbU, 0xf9U, 0xffU, 0xfdU, 0xf3U, 0xf1U, 0xf7U, 0xf5U, 0xebU, 0xe9U, 0xefU, 0xedU, 0xe3U, 0xe1U, 0xe7U, 0xe5U};
alignas(64) static const uint8_t _lut_lut$eq_32[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_33[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_34[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_35[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_36[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_37[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_38[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_39[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_40[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_41[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_42[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_43[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_44[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_45[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_46[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};
alignas(64) static const uint8_t _lut_lut$eq_47[] = {0x63U, 0x7cU, 0x77U, 0x7bU, 0xf2U, 0x6bU, 0x6fU, 0xc5U, 0x30U, 0x1U, 0x67U, 0x2bU, 0xfeU, 0xd7U, 0xabU, 0x76U, 0xcaU, 0x82U, 0xc9U, 0x7dU, 0xfaU, 0x59U, 0x47U, 0xf0U, 0xadU, 0xd4U, 0xa2U, 0xafU, 0x9cU, 0xa4U, 0x72U, 0xc0U, 0xb7U, 0xfdU, 0x93U, 0x26U, 0x36U, 0x3fU, 0xf7U, 0xccU, 0x34U, 0xa5U, 0xe5U, 0xf1U, 0x71U, 0xd8U, 0x31U, 0x15U, 0x4U, 0xc7U, 0x23U, 0xc3U, 0x18U, 0x96U, 0x5U, 0x9aU, 0x7U, 0x12U, 0x80U, 0xe2U, 0xebU, 0x27U, 0xb2U, 0x75U, 0x9U, 0x83U, 0x2cU, 0x1aU, 0x1bU, 0x6eU, 0x5aU, 0xa0U, 0x52U, 0x3bU, 0xd6U, 0xb3U, 0x29U, 0xe3U, 0x2fU, 0x84U, 0x53U, 0xd1U, 0x0U, 0xedU, 0x20U, 0xfcU, 0xb1U, 0x5bU, 0x6aU, 0xcbU, 0xbeU, 0x39U, 0x4aU, 0x4cU, 0x58U, 0xcfU, 0xd0U, 0xefU, 0xaaU, 0xfbU, 0x43U, 0x4dU, 0x33U, 0x85U, 0x45U, 0xf9U, 0x2U, 0x7fU, 0x50U, 0x3cU, 0x9fU, 0xa8U, 0x51U, 0xa3U, 0x40U, 0x8fU, 0x92U, 0x9dU, 0x38U, 0xf5U, 0xbcU, 0xb6U, 0xdaU, 0x21U, 0x10U, 0xffU, 0xf3U, 0xd2U, 0xcdU, 0xcU, 0x13U, 0xecU, 0x5fU, 0x97U, 0x44U, 0x17U, 0xc4U, 0xa7U, 0x7eU, 0x3dU, 0x64U, 0x5dU, 0x19U, 0x73U, 0x60U, 0x81U, 0x4fU, 0xdcU, 0x22U, 0x2aU, 0x90U, 0x88U, 0x46U, 0xeeU, 0xb8U, 0x14U, 0xdeU, 0x5eU, 0xbU, 0xdbU, 0xe0U, 0x32U, 0x3aU, 0xaU, 0x49U, 0x6U, 0x24U, 0x5cU, 0xc2U, 0xd3U, 0xacU, 0x62U, 0x91U, 0x95U, 0xe4U, 0x79U, 0xe7U, 0xc8U, 0x37U, 0x6dU, 0x8dU, 0xd5U, 0x4eU, 0xa9U, 0x6cU, 0x56U, 0xf4U, 0xeaU, 0x65U, 0x7aU, 0xaeU, 0x8U, 0xbaU, 0x78U, 0x25U, 0x2eU, 0x1cU, 0xa6U, 0xb4U, 0xc6U, 0xe8U, 0xddU, 0x74U, 0x1fU, 0x4bU, 0xbdU, 0x8bU, 0x8aU, 0x70U, 0x3eU, 0xb5U, 0x66U, 0x48U, 0x3U, 0xf6U, 0xeU, 0x61U, 0x35U, 0x57U, 0xb9U, 0x86U, 0xc1U, 0x1dU, 0x9eU, 0xe1U, 0xf8U, 0x98U, 0x11U, 0x69U, 0xd9U, 0x8eU, 0x94U, 0x9bU, 0x1eU, 0x87U, 0xe9U, 0xceU, 0x55U, 0x28U, 0xdfU, 0x8cU, 0xa1U, 0x89U, 0xdU, 0xbfU, 0xe6U, 0x42U, 0x68U, 0x41U, 0x99U, 0x2dU, 0xfU, 0xb0U, 0x54U, 0xbbU, 0x63U};

typedef struct AddRoundKey {

  void rand_init() {
  }
} AddRoundKey;

typedef struct SubBytes {

  void rand_init() {
  }
} SubBytes;

typedef struct ShiftRows {

  void rand_init() {
  }
} ShiftRows;

typedef struct MixColumns {

  void rand_init() {
  }
} MixColumns;

typedef struct Cipher {
  alignas(16) UInt<8> state_0[16];
  alignas(16) UInt<8> state_1[16];
  alignas(16) UInt<8> state_2[16];
  alignas(16) UInt<8> state_3[16];
  alignas(16) UInt<8> state_4[16];
  alignas(16) UInt<8> state_5[16];
  alignas(16) UInt<8> state_6[16];
  alignas(16) UInt<8> state_7[16];
  alignas(16) UInt<8> state_8[16];
  alignas(16) UInt<8> state_9[16];
  alignas(16) UInt<8> state_10[16];
  alignas(16) UInt<8> state_11[16];
  alignas(16) UInt<8> state_12[16];
  alignas(16) UInt<8> state_13[16];
  alignas(16) UInt<8> state_14[16];
  alignas(16) UInt<8> state_15[16];
  alignas(16) UInt<4> rounds[16];
  alignas(16) UInt<2> STM[16];
  AddRoundKey AddRoundKeyModule;
  SubBytes SubBytesModule;
  ShiftRows ShiftRowsModule;
  MixColumns MixColumnsModule;
  UInt<1> reset;
  alignas(16) UInt<8> io_plaintext_0[16];
  alignas(16) UInt<8> io_plaintext_1[16];
  alignas(16) UInt<8> io_plaintext_2[16];
  alignas(16) UInt<8> io_plaintext_3[16];
  alignas(16) UInt<8> io_plaintext_4[16];
  alignas(16) UInt<8> io_plaintext_5[16];
  alignas(16) UInt<8> io_plaintext_6[16];
  alignas(16) UInt<8> io_plaintext_7[16];
  alignas(16) UInt<8> io_plaintext_8[16];
  alignas(16) UInt<8> io_plaintext_9[16];
  alignas(16) UInt<8> io_plaintext_10[16];
  alignas(16) UInt<8> io_plaintext_11[16];
  alignas(16) UInt<8> io_plaintext_12[16];
  alignas(16) UInt<8> io_plaintext_13[16];
  alignas(16) UInt<8> io_plaintext_14[16];
  alignas(16) UInt<8> io_plaintext_15[16];
  alignas(16) UInt<8> io_roundKey_0[16];
  alignas(16) UInt<8> io_roundKey_1[16];
  alignas(16) UInt<8> io_roundKey_2[16];
  alignas(16) UInt<8> io_roundKey_3[16];
  alignas(16) UInt<8> io_roundKey_4[16];
  alignas(16) UInt<8> io_roundKey_5[16];
  alignas(16) UInt<8> io_roundKey_6[16];
  alignas(16) UInt<8> io_roundKey_7[16];
  alignas(16) UInt<8> io_roundKey_8[16];
  alignas(16) UInt<8> io_roundKey_9[16];
  alignas(16) UInt<8> io_roundKey_10[16];
  alignas(16) UInt<8> io_roundKey_11[16];
  alignas(16) UInt<8> io_roundKey_12[16];
  alignas(16) UInt<8> io_roundKey_13[16];
  alignas(16) UInt<8> io_roundKey_14[16];
  alignas(16) UInt<8> io_roundKey_15[16];
  alignas(16) UInt<1> io_start[16];
  alignas(16) UInt<8> io_state_out_0[16];
  alignas(16) UInt<8> io_state_out_1[16];
  alignas(16) UInt<8> io_state_out_2[16];
  alignas(16) UInt<8> io_state_out_3[16];
  alignas(16) UInt<8> io_state_out_4[16];
  alignas(16) UInt<8> io_state_out_5[16];
  alignas(16) UInt<8> io_state_out_6[16];
  alignas(16) UInt<8> io_state_out_7[16];
  alignas(16) UInt<8> io_state_out_8[16];
  alignas(16) UInt<8> io_state_out_9[16];
  alignas(16) UInt<8> io_state_out_10[16];
  alignas(16) UInt<8> io_state_out_11[16];
  alignas(16) UInt<8> io_state_out_12[16];
  alignas(16) UInt<8> io_state_out_13[16];
  alignas(16) UInt<8> io_state_out_14[16];
  alignas(16) UInt<8> io_state_out_15[16];
  alignas(16) UInt<1> io_state_out_valid[16];

  void rand_init() {
    for (int _i = 0; _i < 16; _i++) state_0[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_1[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_2[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_3[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_4[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_5[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_6[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_7[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_8[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_9[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_10[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_11[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_12[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_13[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_14[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) state_15[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) rounds[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) STM[_i].rand_init();
    AddRoundKeyModule.rand_init();
    SubBytesModule.rand_init();
    ShiftRowsModule.rand_init();
    MixColumnsModule.rand_init();
    reset.rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_0[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_1[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_2[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_3[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_4[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_5[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_6[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_7[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_8[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_9[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_10[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_11[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_12[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_13[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_14[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_plaintext_15[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_0[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_1[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_2[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_3[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_4[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_5[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_6[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_7[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_8[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_9[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_10[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_11[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_12[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_13[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_14[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_roundKey_15[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_start[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_0[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_1[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_2[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_3[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_4[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_5[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_6[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_7[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_8[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_9[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_10[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_11[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_12[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_13[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_14[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_15[_i].rand_init();
    for (int _i = 0; _i < 16; _i++) io_state_out_valid[_i].rand_init();
  }

  bool assert_triggered = false;
  int assert_exit_code = 0;
  uint64_t verify_mismatches = 0;
  bool oracle_mismatches_fatal = true;
  uint64_t oracle_mismatch_log_limit = 16;
  void set_oracle_mismatch_policy(bool fatal, uint64_t log_limit = 16) {
    oracle_mismatches_fatal = fatal; oracle_mismatch_log_limit = log_limit;
  }
  bool oracle_mismatch_should_log() const {
    return oracle_mismatches_fatal || verify_mismatches < oracle_mismatch_log_limit;
  }
  void record_oracle_mismatch() {
    ++verify_mismatches;
    if (oracle_mismatches_fatal) { assert_triggered = true; assert_exit_code = 42; }
  }
  bool checks_enabled = true;
  int oracle_cycle = 0;
  const char* oracle_win_base = nullptr;
  bool oracle_boundary_valid = false;
  // [boundary-verify] 18 carried next-state values
  UInt<8> _v2_bcarry_state_0;
  UInt<8> _v2_bcarry_state_1;
  UInt<8> _v2_bcarry_state_10;
  UInt<8> _v2_bcarry_state_11;
  UInt<8> _v2_bcarry_state_12;
  UInt<8> _v2_bcarry_state_13;
  UInt<8> _v2_bcarry_state_14;
  UInt<8> _v2_bcarry_state_15;
  UInt<8> _v2_bcarry_state_2;
  UInt<8> _v2_bcarry_state_3;
  UInt<8> _v2_bcarry_state_4;
  UInt<8> _v2_bcarry_state_5;
  UInt<8> _v2_bcarry_state_6;
  UInt<8> _v2_bcarry_state_7;
  UInt<8> _v2_bcarry_state_8;
  UInt<8> _v2_bcarry_state_9;
  UInt<2> _v2_bcarry_STM;
  UInt<4> _v2_bcarry_rounds;

  void eval_forward(bool update_registers, bool verbose, bool done_reset) {
    (void)verbose;
    // [v2 schedule] 209 units, 0 serial regions (0 templates x 16 lanes), 18 oracle streams
    // [boundary-verify] 18 register oracles: previous sweep's last-lane next-state vs this sweep's boundary injection (group 0)
    #if ESSENT_ORACLE_VERIFY
    if (done_reset && checks_enabled && update_registers && oracle_boundary_valid) {
      uint8_t _v2_vacc8 = 0;
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_0) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 0L) /* trace_state_0 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_1) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 32L) /* trace_state_1 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_10) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 320L) /* trace_state_10 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_11) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 352L) /* trace_state_11 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_12) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 384L) /* trace_state_12 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_13) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 416L) /* trace_state_13 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_14) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 448L) /* trace_state_14 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_15) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 480L) /* trace_state_15 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_2) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 64L) /* trace_state_2 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_3) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 96L) /* trace_state_3 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_4) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 128L) /* trace_state_4 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_5) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 160L) /* trace_state_5 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_6) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 192L) /* trace_state_6 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_7) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 224L) /* trace_state_7 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_8) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 256L) /* trace_state_8 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_9) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 288L) /* trace_state_9 */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_STM) ^ essent_raw(UInt<2>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 544L) /* trace_STM */), 0))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_rounds) ^ essent_raw(UInt<4>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 512L) /* trace_rounds */), 0))));
      if (UNLIKELY(((uint64_t)_v2_vacc8) != 0)) _v2_verify_boundary_rescan(0, true);
    }
    #endif
    // [vec oracle-inject] 18 templates x 16 lanes
    if (done_reset) {
      essent_inject_fwd<16>(&state_0[0], ((const uint8_t*)(oracle_win_base + 0L) /* trace_state_0 */));
      essent_inject_fwd<16>(&state_1[0], ((const uint8_t*)(oracle_win_base + 32L) /* trace_state_1 */));
      essent_inject_fwd<16>(&state_2[0], ((const uint8_t*)(oracle_win_base + 64L) /* trace_state_2 */));
      essent_inject_fwd<16>(&state_3[0], ((const uint8_t*)(oracle_win_base + 96L) /* trace_state_3 */));
      essent_inject_fwd<16>(&state_4[0], ((const uint8_t*)(oracle_win_base + 128L) /* trace_state_4 */));
      essent_inject_fwd<16>(&state_5[0], ((const uint8_t*)(oracle_win_base + 160L) /* trace_state_5 */));
      essent_inject_fwd<16>(&state_6[0], ((const uint8_t*)(oracle_win_base + 192L) /* trace_state_6 */));
      essent_inject_fwd<16>(&state_7[0], ((const uint8_t*)(oracle_win_base + 224L) /* trace_state_7 */));
      essent_inject_fwd<16>(&state_8[0], ((const uint8_t*)(oracle_win_base + 256L) /* trace_state_8 */));
      essent_inject_fwd<16>(&state_9[0], ((const uint8_t*)(oracle_win_base + 288L) /* trace_state_9 */));
      essent_inject_fwd<16>(&state_10[0], ((const uint8_t*)(oracle_win_base + 320L) /* trace_state_10 */));
      essent_inject_fwd<16>(&state_11[0], ((const uint8_t*)(oracle_win_base + 352L) /* trace_state_11 */));
      essent_inject_fwd<16>(&state_12[0], ((const uint8_t*)(oracle_win_base + 384L) /* trace_state_12 */));
      essent_inject_fwd<16>(&state_13[0], ((const uint8_t*)(oracle_win_base + 416L) /* trace_state_13 */));
      essent_inject_fwd<16>(&state_14[0], ((const uint8_t*)(oracle_win_base + 448L) /* trace_state_14 */));
      essent_inject_fwd<16>(&state_15[0], ((const uint8_t*)(oracle_win_base + 480L) /* trace_state_15 */));
      essent_inject_fwd<16>(&rounds[0], ((const uint8_t*)(oracle_win_base + 512L) /* trace_rounds */));
      essent_inject_fwd<16>(&STM[0], ((const uint8_t*)(oracle_win_base + 544L) /* trace_STM */));
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s__T_248[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0x0u) & 0x3u)) == (STM[L].val))) & 0x1u)) & 0x1u));
      _s__T_250[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0x1u) & 0x3u)) == (STM[L].val))) & 0x1u)) & 0x1u));
      _s__T_253[L].val = static_cast<typename UInt<4>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((static_cast<uint8_t>((static_cast<uint8_t>((static_cast<uint8_t>(rounds[L].val) + static_cast<uint8_t>((static_cast<uint8_t>(0x1u) & 0xfu)))) & 0x1fu)) & 0xfu)) & 0xfu)) & 0xfu));
      _s__T_254[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0x2u) & 0x3u)) == (STM[L].val))) & 0x1u)) & 0x1u));
      _s__T_259[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((rounds[L].val) == ((static_cast<uint8_t>(0xau) & 0xfu)))) & 0x1u)) & 0x1u));
      _s__T_260[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((STM[L].val) == ((static_cast<uint8_t>(0x1u) & 0x3u)))) & 0x1u)) & 0x1u));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s__T_335[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((STM[L].val) != ((static_cast<uint8_t>(0x0u) & 0x3u)))) & 0x1u)) & 0x1u));
      _s__T_395[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((rounds[L].val) == ((static_cast<uint8_t>(0xbu) & 0xfu)))) & 0x1u)) & 0x1u));
      io_state_out_0[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_0[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_1[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_1[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_2[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_2[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_3[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      io_state_out_4[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_4[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_5[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_5[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_6[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_7[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_7[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_8[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_9[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_9[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      io_state_out_10[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_10[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_11[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_11[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_12[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_12[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_13[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_14[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_15[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_15[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_32 _v2_local_12493_0
      UInt<8> _v2_local_12493_0;
      io_state_out_valid[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((rounds[L].val) == ((static_cast<uint8_t>(0xbu) & 0xfu)))) & 0x1u)) & 0x1u));
      _s_rounds$next[L].val = static_cast<typename UInt<4>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xfu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xfu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s__T_253[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s__T_253[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))) | ((rounds[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))))) & 0xfu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))))) & 0xfu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))))) & 0xfu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xfu)) & 0xfu));
      _s_STM$next[L].val = static_cast<typename UInt<2>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(((((static_cast<uint8_t>(0x1u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(io_start[L].val) & 0x1u)) != 0))) | ((STM[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(io_start[L].val) & 0x1u)) != 0))))) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(0x2u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((STM[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))) | ((STM[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))))) & 0x3u)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))))) & 0x3u)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))))) & 0x3u)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0x3u)) & 0x3u));
      _v2_local_12493_0 = UInt<8>(_lut_lut$eq_32[essent_to_u64(state_3[L])]);
      _s_SubBytesModule$io_state_out_3[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_3[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12493_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_3[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_11[L] = UInt<8>(_lut_lut$eq_11[essent_to_u64(_s_SubBytesModule$io_state_out_3[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s_lut$eq_13[L] = UInt<8>(_lut_lut$eq_13[essent_to_u64(_s_SubBytesModule$io_state_out_3[L])]);
      _s_lut$eq_33[L] = UInt<8>(_lut_lut$eq_33[essent_to_u64(state_4[L])]);
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_34 _v2_local_12495_0
      UInt<8> _v2_local_12495_0;
      _s_SubBytesModule$io_state_out_4[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_4[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_33[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_4[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_5[L] = UInt<8>(_lut_lut$eq_5[essent_to_u64(_s_SubBytesModule$io_state_out_4[L])]);
      _s_lut$eq_12[L] = UInt<8>(_lut_lut$eq_12[essent_to_u64(_s_SubBytesModule$io_state_out_4[L])]);
      _v2_local_12495_0 = UInt<8>(_lut_lut$eq_34[essent_to_u64(state_5[L])]);
      _s_SubBytesModule$io_state_out_5[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_5[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12495_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_5[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_17[L] = UInt<8>(_lut_lut$eq_17[essent_to_u64(_s_SubBytesModule$io_state_out_5[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_35 _v2_local_12496_0
      UInt<8> _v2_local_12496_0;
      _s_lut$eq_28[L] = UInt<8>(_lut_lut$eq_28[essent_to_u64(_s_SubBytesModule$io_state_out_5[L])]);
      _v2_local_12496_0 = UInt<8>(_lut_lut$eq_35[essent_to_u64(state_6[L])]);
      _s_SubBytesModule$io_state_out_6[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_6[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12496_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_6[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_26[L] = UInt<8>(_lut_lut$eq_26[essent_to_u64(_s_SubBytesModule$io_state_out_6[L])]);
      _s_lut$eq_27[L] = UInt<8>(_lut_lut$eq_27[essent_to_u64(_s_SubBytesModule$io_state_out_6[L])]);
      _s_lut$eq_36[L] = UInt<8>(_lut_lut$eq_36[essent_to_u64(state_7[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_37 _v2_local_12498_0
      UInt<8> _v2_local_12498_0;
      _s_SubBytesModule$io_state_out_7[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_7[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_36[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_7[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_20[L] = UInt<8>(_lut_lut$eq_20[essent_to_u64(_s_SubBytesModule$io_state_out_7[L])]);
      _s_lut$eq_22[L] = UInt<8>(_lut_lut$eq_22[essent_to_u64(_s_SubBytesModule$io_state_out_7[L])]);
      _v2_local_12498_0 = UInt<8>(_lut_lut$eq_37[essent_to_u64(state_8[L])]);
      _s_SubBytesModule$io_state_out_8[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_8[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12498_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_8[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_14[L] = UInt<8>(_lut_lut$eq_14[essent_to_u64(_s_SubBytesModule$io_state_out_8[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_38 _v2_local_12499_0
      UInt<8> _v2_local_12499_0;
      _s_lut$eq_21[L] = UInt<8>(_lut_lut$eq_21[essent_to_u64(_s_SubBytesModule$io_state_out_8[L])]);
      _v2_local_12499_0 = UInt<8>(_lut_lut$eq_38[essent_to_u64(state_0[L])]);
      _s_SubBytesModule$io_state_out_0[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_0[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12499_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_0[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_3[L] = UInt<8>(_lut_lut$eq_3[essent_to_u64(_s_SubBytesModule$io_state_out_0[L])]);
      _s_lut$eq_6[L] = UInt<8>(_lut_lut$eq_6[essent_to_u64(_s_SubBytesModule$io_state_out_0[L])]);
      _s_lut$eq_39[L] = UInt<8>(_lut_lut$eq_39[essent_to_u64(state_9[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_40 _v2_local_12501_0
      UInt<8> _v2_local_12501_0;
      _s_SubBytesModule$io_state_out_9[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_9[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_39[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_9[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_7[L] = UInt<8>(_lut_lut$eq_7[essent_to_u64(_s_SubBytesModule$io_state_out_9[L])]);
      _s_lut$eq_8[L] = UInt<8>(_lut_lut$eq_8[essent_to_u64(_s_SubBytesModule$io_state_out_9[L])]);
      _v2_local_12501_0 = UInt<8>(_lut_lut$eq_40[essent_to_u64(state_10[L])]);
      _s_SubBytesModule$io_state_out_10[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_10[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12501_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_10[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_0[L] = UInt<8>(_lut_lut$eq_0[essent_to_u64(_s_SubBytesModule$io_state_out_10[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s_lut$eq_1[L] = UInt<8>(_lut_lut$eq_1[essent_to_u64(_s_SubBytesModule$io_state_out_10[L])]);
      _s_lut$eq_41[L] = UInt<8>(_lut_lut$eq_41[essent_to_u64(state_11[L])]);
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_42 _v2_local_12503_0
      UInt<8> _v2_local_12503_0;
      _s_SubBytesModule$io_state_out_11[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_11[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_41[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_11[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_29[L] = UInt<8>(_lut_lut$eq_29[essent_to_u64(_s_SubBytesModule$io_state_out_11[L])]);
      _s_lut$eq_31[L] = UInt<8>(_lut_lut$eq_31[essent_to_u64(_s_SubBytesModule$io_state_out_11[L])]);
      _v2_local_12503_0 = UInt<8>(_lut_lut$eq_42[essent_to_u64(state_12[L])]);
      _s_SubBytesModule$io_state_out_12[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_12[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12503_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_12[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_23[L] = UInt<8>(_lut_lut$eq_23[essent_to_u64(_s_SubBytesModule$io_state_out_12[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_43 _v2_local_12504_0
      UInt<8> _v2_local_12504_0;
      _s_lut$eq_30[L] = UInt<8>(_lut_lut$eq_30[essent_to_u64(_s_SubBytesModule$io_state_out_12[L])]);
      _v2_local_12504_0 = UInt<8>(_lut_lut$eq_43[essent_to_u64(state_13[L])]);
      _s_SubBytesModule$io_state_out_13[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_13[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12504_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_13[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_15[L] = UInt<8>(_lut_lut$eq_15[essent_to_u64(_s_SubBytesModule$io_state_out_13[L])]);
      _s_lut$eq_16[L] = UInt<8>(_lut_lut$eq_16[essent_to_u64(_s_SubBytesModule$io_state_out_13[L])]);
      _s_lut$eq_44[L] = UInt<8>(_lut_lut$eq_44[essent_to_u64(state_14[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_4 _v2_local_104_0
      UInt<8> _v2_local_104_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_4 _v2_local_12392_0
      UInt<8> _v2_local_12392_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_4 _v2_local_70_0
      UInt<8> _v2_local_70_0;
      _s_SubBytesModule$io_state_out_14[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_14[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_44[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_14[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12392_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_5[L].val) ^ (_s_lut$eq_7[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_14[L].val) ^ (_s_SubBytesModule$io_state_out_3[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_70_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_4[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_4[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12392_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_104_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_70_0.val) ^ (io_roundKey_4[L].val))) & 0xffu)) & 0xffu));
      _s_state_4$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_104_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_MixColumnsModule$io_state_out_7[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_12[L].val) ^ (_s_SubBytesModule$io_state_out_9[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_14[L].val) ^ (_s_lut$eq_13[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_7 _v2_local_107_0
      UInt<8> _v2_local_107_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_5 _v2_local_12393_0
      UInt<8> _v2_local_12393_0;
      // [v2 lane-local] lut$eq_9 _v2_local_12470_0
      UInt<8> _v2_local_12470_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_7 _v2_local_73_0
      UInt<8> _v2_local_73_0;
      _v2_local_73_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_7[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_s_MixColumnsModule$io_state_out_7[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_107_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_73_0.val) ^ (io_roundKey_7[L].val))) & 0xffu)) & 0xffu));
      _s_state_7$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_107_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12470_0 = UInt<8>(_lut_lut$eq_9[essent_to_u64(_s_SubBytesModule$io_state_out_14[L])]);
      _v2_local_12393_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_4[L].val) ^ (_s_lut$eq_8[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_v2_local_12470_0.val) ^ (_s_SubBytesModule$io_state_out_3[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_in_5[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_5[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_9[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12393_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_5 _v2_local_105_0
      UInt<8> _v2_local_105_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_6 _v2_local_12394_0
      UInt<8> _v2_local_12394_0;
      // [v2 lane-local] lut$eq_10 _v2_local_12471_0
      UInt<8> _v2_local_12471_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_6 _v2_local_72_0
      UInt<8> _v2_local_72_0;
      _v2_local_105_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_s_AddRoundKeyModule$io_state_in_5[L].val) ^ (io_roundKey_5[L].val))) & 0xffu)) & 0xffu));
      _s_state_5$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_105_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12471_0 = UInt<8>(_lut_lut$eq_10[essent_to_u64(_s_SubBytesModule$io_state_out_14[L])]);
      _v2_local_12394_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_4[L].val) ^ (_s_SubBytesModule$io_state_out_9[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_v2_local_12471_0.val) ^ (_s_lut$eq_11[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_72_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12394_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_6[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_72_0.val) ^ (io_roundKey_6[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s_state_6$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_45[L] = UInt<8>(_lut_lut$eq_45[essent_to_u64(state_15[L])]);
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_0 _v2_local_100_0
      UInt<8> _v2_local_100_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_0 _v2_local_12388_0
      UInt<8> _v2_local_12388_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_0 _v2_local_66_0
      UInt<8> _v2_local_66_0;
      _s_SubBytesModule$io_state_out_15[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_15[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_45[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_15[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12388_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_6[L].val) ^ (_s_lut$eq_17[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_10[L].val) ^ (_s_SubBytesModule$io_state_out_15[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_66_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_0[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_0[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12388_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_100_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_66_0.val) ^ (io_roundKey_0[L].val))) & 0xffu)) & 0xffu));
      _s_state_0$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_100_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_MixColumnsModule$io_state_out_1[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_0[L].val) ^ (_s_lut$eq_28[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_0[L].val) ^ (_s_SubBytesModule$io_state_out_15[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_1 _v2_local_101_0
      UInt<8> _v2_local_101_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_2 _v2_local_12390_0
      UInt<8> _v2_local_12390_0;
      // [v2 lane-local] lut$eq_2 _v2_local_12463_0
      UInt<8> _v2_local_12463_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_1 _v2_local_67_0
      UInt<8> _v2_local_67_0;
      _v2_local_67_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_1[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_5[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_s_MixColumnsModule$io_state_out_1[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_101_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_67_0.val) ^ (io_roundKey_1[L].val))) & 0xffu)) & 0xffu));
      _s_state_1$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_101_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12463_0 = UInt<8>(_lut_lut$eq_2[essent_to_u64(_s_SubBytesModule$io_state_out_15[L])]);
      _v2_local_12390_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_0[L].val) ^ (_s_SubBytesModule$io_state_out_5[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_1[L].val) ^ (_v2_local_12463_0.val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_in_2[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_2[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_10[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12390_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_2 _v2_local_102_0
      UInt<8> _v2_local_102_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_3 _v2_local_12391_0
      UInt<8> _v2_local_12391_0;
      // [v2 lane-local] lut$eq_4 _v2_local_12465_0
      UInt<8> _v2_local_12465_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_3 _v2_local_69_0
      UInt<8> _v2_local_69_0;
      _v2_local_102_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_s_AddRoundKeyModule$io_state_in_2[L].val) ^ (io_roundKey_2[L].val))) & 0xffu)) & 0xffu));
      _s_state_2$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_102_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12465_0 = UInt<8>(_lut_lut$eq_4[essent_to_u64(_s_SubBytesModule$io_state_out_15[L])]);
      _v2_local_12391_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_3[L].val) ^ (_s_SubBytesModule$io_state_out_5[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_10[L].val) ^ (_v2_local_12465_0.val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_69_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_15[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12391_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_3[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_69_0.val) ^ (io_roundKey_3[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] MixColumnsModule.io_state_out_14 _v2_local_12402_0
      UInt<8> _v2_local_12402_0;
      // [v2 lane-local] lut$eq_46 _v2_local_12507_0
      UInt<8> _v2_local_12507_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_14 _v2_local_80_0
      UInt<8> _v2_local_80_0;
      _s_state_3$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12507_0 = UInt<8>(_lut_lut$eq_46[essent_to_u64(state_1[L])]);
      _s_SubBytesModule$io_state_out_1[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_1[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12507_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_1[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12402_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_12[L].val) ^ (_s_SubBytesModule$io_state_out_1[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_27[L].val) ^ (_s_lut$eq_29[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_80_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12402_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_14[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_80_0.val) ^ (io_roundKey_14[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_15 _v2_local_115_0
      UInt<8> _v2_local_115_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_15 _v2_local_12403_0
      UInt<8> _v2_local_12403_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_15 _v2_local_81_0
      UInt<8> _v2_local_81_0;
      _s_state_14$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12403_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_30[L].val) ^ (_s_SubBytesModule$io_state_out_1[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_6[L].val) ^ (_s_lut$eq_31[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_81_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_15[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_11[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12403_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_115_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_81_0.val) ^ (io_roundKey_15[L].val))) & 0xffu)) & 0xffu));
      _s_state_15$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_115_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_24[L] = UInt<8>(_lut_lut$eq_24[essent_to_u64(_s_SubBytesModule$io_state_out_1[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] MixColumnsModule.io_state_out_12 _v2_local_12400_0
      UInt<8> _v2_local_12400_0;
      _v2_local_12400_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_23[L].val) ^ (_s_lut$eq_24[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_6[L].val) ^ (_s_SubBytesModule$io_state_out_11[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_in_12[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_12[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_12[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12400_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    // [vec comb] 27 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_12 _v2_local_112_0
      UInt<8> _v2_local_112_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_13 _v2_local_12401_0
      UInt<8> _v2_local_12401_0;
      // [v2 lane-local] lut$eq_25 _v2_local_12486_0
      UInt<8> _v2_local_12486_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_13 _v2_local_79_0
      UInt<8> _v2_local_79_0;
      _v2_local_112_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_s_AddRoundKeyModule$io_state_in_12[L].val) ^ (io_roundKey_12[L].val))) & 0xffu)) & 0xffu));
      _s_state_12$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_112_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12486_0 = UInt<8>(_lut_lut$eq_25[essent_to_u64(_s_SubBytesModule$io_state_out_1[L])]);
      _v2_local_12401_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_12[L].val) ^ (_v2_local_12486_0.val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_26[L].val) ^ (_s_SubBytesModule$io_state_out_11[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_79_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_1[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12401_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_13[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_79_0.val) ^ (io_roundKey_13[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] MixColumnsModule.io_state_out_8 _v2_local_12396_0
      UInt<8> _v2_local_12396_0;
      // [v2 lane-local] lut$eq_47 _v2_local_12508_0
      UInt<8> _v2_local_12508_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_8 _v2_local_74_0
      UInt<8> _v2_local_74_0;
      _s_state_13$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12508_0 = UInt<8>(_lut_lut$eq_47[essent_to_u64(state_2[L])]);
      _s_SubBytesModule$io_state_out_2[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_2[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12508_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_2[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12396_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_14[L].val) ^ (_s_lut$eq_15[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_2[L].val) ^ (_s_SubBytesModule$io_state_out_7[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_74_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12396_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_8[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_74_0.val) ^ (io_roundKey_8[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_11 _v2_local_111_0
      UInt<8> _v2_local_111_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_11 _v2_local_12399_0
      UInt<8> _v2_local_12399_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_11 _v2_local_77_0
      UInt<8> _v2_local_77_0;
      _s_state_8$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12399_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_21[L].val) ^ (_s_SubBytesModule$io_state_out_13[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_2[L].val) ^ (_s_lut$eq_22[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_77_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_11[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_7[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12399_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_111_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_77_0.val) ^ (io_roundKey_11[L].val))) & 0xffu)) & 0xffu));
      _s_state_11$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_111_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_18[L] = UInt<8>(_lut_lut$eq_18[essent_to_u64(_s_SubBytesModule$io_state_out_2[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_9 _v2_local_109_0
      UInt<8> _v2_local_109_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_9 _v2_local_12397_0
      UInt<8> _v2_local_12397_0;
      // [v2 lane-local] lut$eq_19 _v2_local_12480_0
      UInt<8> _v2_local_12480_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_9 _v2_local_75_0
      UInt<8> _v2_local_75_0;
      _v2_local_12397_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_8[L].val) ^ (_s_lut$eq_16[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_18[L].val) ^ (_s_SubBytesModule$io_state_out_7[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_75_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_9[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12397_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_109_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_75_0.val) ^ (io_roundKey_9[L].val))) & 0xffu)) & 0xffu));
      _s_state_9$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_109_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12480_0 = UInt<8>(_lut_lut$eq_19[essent_to_u64(_s_SubBytesModule$io_state_out_2[L])]);
      _s_MixColumnsModule$io_state_out_10[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_8[L].val) ^ (_s_SubBytesModule$io_state_out_13[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_v2_local_12480_0.val) ^ (_s_lut$eq_20[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_10 _v2_local_110_0
      UInt<8> _v2_local_110_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_10 _v2_local_76_0
      UInt<8> _v2_local_76_0;
      _v2_local_76_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_10[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_2[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_s_MixColumnsModule$io_state_out_10[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_110_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_76_0.val) ^ (io_roundKey_10[L].val))) & 0xffu)) & 0xffu));
      _s_state_10$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_110_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    // [vec oracle-verify] 18 templates x 16 lanes
    #if ESSENT_ORACLE_VERIFY
    if (done_reset && checks_enabled && update_registers) {
      uint8_t _v2_vacc8 = 0;
      // [verify-reduction] u8: 18 fields, 4 accumulators
      uint8_t _v2_vacc8_p0 = 0;
      uint8_t _v2_vacc8_p1 = 0;
      uint8_t _v2_vacc8_p2 = 0;
      uint8_t _v2_vacc8_p3 = 0;
      ESSENT_TAIL_LOOP
      for (int L = 0; L < 15; L++) {
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_0$next[L]) ^ essent_raw(state_0[(L) + 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_1$next[L]) ^ essent_raw(state_1[(L) + 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_10$next[L]) ^ essent_raw(state_10[(L) + 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_11$next[L]) ^ essent_raw(state_11[(L) + 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_12$next[L]) ^ essent_raw(state_12[(L) + 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_13$next[L]) ^ essent_raw(state_13[(L) + 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_14$next[L]) ^ essent_raw(state_14[(L) + 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_15$next[L]) ^ essent_raw(state_15[(L) + 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_2$next[L]) ^ essent_raw(state_2[(L) + 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_3$next[L]) ^ essent_raw(state_3[(L) + 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_4$next[L]) ^ essent_raw(state_4[(L) + 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_5$next[L]) ^ essent_raw(state_5[(L) + 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_6$next[L]) ^ essent_raw(state_6[(L) + 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_7$next[L]) ^ essent_raw(state_7[(L) + 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_8$next[L]) ^ essent_raw(state_8[(L) + 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_9$next[L]) ^ essent_raw(state_9[(L) + 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_STM$next[L]) ^ essent_raw(STM[(L) + 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_rounds$next[L]) ^ essent_raw(rounds[(L) + 1]));
      }
      _v2_vacc8 = (uint8_t)(_v2_vacc8_p0 | _v2_vacc8_p1 | _v2_vacc8_p2 | _v2_vacc8_p3);
      if (UNLIKELY(((uint64_t)_v2_vacc8) != 0)) _v2_verify_rescan(0, true, 0, 15);
      // [boundary-carry] 18 last-lane next-state values
      _v2_bcarry_state_0 = _s_state_0$next[15];
      _v2_bcarry_state_1 = _s_state_1$next[15];
      _v2_bcarry_state_10 = _s_state_10$next[15];
      _v2_bcarry_state_11 = _s_state_11$next[15];
      _v2_bcarry_state_12 = _s_state_12$next[15];
      _v2_bcarry_state_13 = _s_state_13$next[15];
      _v2_bcarry_state_14 = _s_state_14$next[15];
      _v2_bcarry_state_15 = _s_state_15$next[15];
      _v2_bcarry_state_2 = _s_state_2$next[15];
      _v2_bcarry_state_3 = _s_state_3$next[15];
      _v2_bcarry_state_4 = _s_state_4$next[15];
      _v2_bcarry_state_5 = _s_state_5$next[15];
      _v2_bcarry_state_6 = _s_state_6$next[15];
      _v2_bcarry_state_7 = _s_state_7$next[15];
      _v2_bcarry_state_8 = _s_state_8$next[15];
      _v2_bcarry_state_9 = _s_state_9$next[15];
      _v2_bcarry_STM = _s_STM$next[15];
      _v2_bcarry_rounds = _s_rounds$next[15];
    }
    #endif
    // [vec commit] 18 templates x 16 lanes
    if (update_registers) {
      essent_commit_lanes<16>(&state_0[0], &_s_state_0$next[0]);
      essent_commit_lanes<16>(&state_1[0], &_s_state_1$next[0]);
      essent_commit_lanes<16>(&state_2[0], &_s_state_2$next[0]);
      essent_commit_lanes<16>(&state_3[0], &_s_state_3$next[0]);
      essent_commit_lanes<16>(&state_4[0], &_s_state_4$next[0]);
      essent_commit_lanes<16>(&state_5[0], &_s_state_5$next[0]);
      essent_commit_lanes<16>(&state_6[0], &_s_state_6$next[0]);
      essent_commit_lanes<16>(&state_7[0], &_s_state_7$next[0]);
      essent_commit_lanes<16>(&state_8[0], &_s_state_8$next[0]);
      essent_commit_lanes<16>(&state_9[0], &_s_state_9$next[0]);
      essent_commit_lanes<16>(&state_10[0], &_s_state_10$next[0]);
      essent_commit_lanes<16>(&state_11[0], &_s_state_11$next[0]);
      essent_commit_lanes<16>(&state_12[0], &_s_state_12$next[0]);
      essent_commit_lanes<16>(&state_13[0], &_s_state_13$next[0]);
      essent_commit_lanes<16>(&state_14[0], &_s_state_14$next[0]);
      essent_commit_lanes<16>(&state_15[0], &_s_state_15$next[0]);
      essent_commit_lanes<16>(&rounds[0], &_s_rounds$next[0]);
      essent_commit_lanes<16>(&STM[0], &_s_STM$next[0]);
    }
    if (update_registers) oracle_boundary_valid = done_reset && checks_enabled;
    if (done_reset && checks_enabled && update_registers && assert_triggered) exit(assert_exit_code);
    if (!done_reset || !checks_enabled) assert_triggered = false;
  }

  void eval_reverse(bool update_registers, bool verbose, bool done_reset) {
    (void)verbose;
    // [v2 schedule] 209 units, 0 serial regions (0 templates x 16 lanes), 18 oracle streams
    // [boundary-verify] 18 register oracles: previous sweep's last-lane next-state vs this sweep's boundary injection (group 0)
    #if ESSENT_ORACLE_VERIFY
    if (done_reset && checks_enabled && update_registers && oracle_boundary_valid) {
      uint8_t _v2_vacc8 = 0;
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_0) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 0L) /* trace_state_0 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_1) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 32L) /* trace_state_1 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_10) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 320L) /* trace_state_10 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_11) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 352L) /* trace_state_11 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_12) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 384L) /* trace_state_12 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_13) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 416L) /* trace_state_13 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_14) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 448L) /* trace_state_14 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_15) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 480L) /* trace_state_15 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_2) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 64L) /* trace_state_2 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_3) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 96L) /* trace_state_3 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_4) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 128L) /* trace_state_4 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_5) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 160L) /* trace_state_5 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_6) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 192L) /* trace_state_6 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_7) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 224L) /* trace_state_7 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_8) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 256L) /* trace_state_8 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_state_9) ^ essent_raw(UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 288L) /* trace_state_9 */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_STM) ^ essent_raw(UInt<2>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 544L) /* trace_STM */), 31))));
      _v2_vacc8 |= (uint8_t)(essent_raw(_v2_bcarry_rounds) ^ essent_raw(UInt<4>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 512L) /* trace_rounds */), 31))));
      if (UNLIKELY(((uint64_t)_v2_vacc8) != 0)) _v2_verify_boundary_rescan(0, false);
    }
    #endif
    // [vec oracle-inject] 18 templates x 16 lanes
    if (done_reset) {
      essent_inject_rev<16>(&state_0[0], ((const uint8_t*)(oracle_win_base + 0L) /* trace_state_0 */));
      essent_inject_rev<16>(&state_1[0], ((const uint8_t*)(oracle_win_base + 32L) /* trace_state_1 */));
      essent_inject_rev<16>(&state_2[0], ((const uint8_t*)(oracle_win_base + 64L) /* trace_state_2 */));
      essent_inject_rev<16>(&state_3[0], ((const uint8_t*)(oracle_win_base + 96L) /* trace_state_3 */));
      essent_inject_rev<16>(&state_4[0], ((const uint8_t*)(oracle_win_base + 128L) /* trace_state_4 */));
      essent_inject_rev<16>(&state_5[0], ((const uint8_t*)(oracle_win_base + 160L) /* trace_state_5 */));
      essent_inject_rev<16>(&state_6[0], ((const uint8_t*)(oracle_win_base + 192L) /* trace_state_6 */));
      essent_inject_rev<16>(&state_7[0], ((const uint8_t*)(oracle_win_base + 224L) /* trace_state_7 */));
      essent_inject_rev<16>(&state_8[0], ((const uint8_t*)(oracle_win_base + 256L) /* trace_state_8 */));
      essent_inject_rev<16>(&state_9[0], ((const uint8_t*)(oracle_win_base + 288L) /* trace_state_9 */));
      essent_inject_rev<16>(&state_10[0], ((const uint8_t*)(oracle_win_base + 320L) /* trace_state_10 */));
      essent_inject_rev<16>(&state_11[0], ((const uint8_t*)(oracle_win_base + 352L) /* trace_state_11 */));
      essent_inject_rev<16>(&state_12[0], ((const uint8_t*)(oracle_win_base + 384L) /* trace_state_12 */));
      essent_inject_rev<16>(&state_13[0], ((const uint8_t*)(oracle_win_base + 416L) /* trace_state_13 */));
      essent_inject_rev<16>(&state_14[0], ((const uint8_t*)(oracle_win_base + 448L) /* trace_state_14 */));
      essent_inject_rev<16>(&state_15[0], ((const uint8_t*)(oracle_win_base + 480L) /* trace_state_15 */));
      essent_inject_rev<16>(&rounds[0], ((const uint8_t*)(oracle_win_base + 512L) /* trace_rounds */));
      essent_inject_rev<16>(&STM[0], ((const uint8_t*)(oracle_win_base + 544L) /* trace_STM */));
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s__T_248[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0x0u) & 0x3u)) == (STM[L].val))) & 0x1u)) & 0x1u));
      _s__T_250[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0x1u) & 0x3u)) == (STM[L].val))) & 0x1u)) & 0x1u));
      _s__T_253[L].val = static_cast<typename UInt<4>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((static_cast<uint8_t>((static_cast<uint8_t>((static_cast<uint8_t>(rounds[L].val) + static_cast<uint8_t>((static_cast<uint8_t>(0x1u) & 0xfu)))) & 0x1fu)) & 0xfu)) & 0xfu)) & 0xfu));
      _s__T_254[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0x2u) & 0x3u)) == (STM[L].val))) & 0x1u)) & 0x1u));
      _s__T_259[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((rounds[L].val) == ((static_cast<uint8_t>(0xau) & 0xfu)))) & 0x1u)) & 0x1u));
      _s__T_260[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((STM[L].val) == ((static_cast<uint8_t>(0x1u) & 0x3u)))) & 0x1u)) & 0x1u));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s__T_335[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((STM[L].val) != ((static_cast<uint8_t>(0x0u) & 0x3u)))) & 0x1u)) & 0x1u));
      _s__T_395[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((rounds[L].val) == ((static_cast<uint8_t>(0xbu) & 0xfu)))) & 0x1u)) & 0x1u));
      io_state_out_0[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_0[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_1[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_1[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_2[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_2[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_3[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      io_state_out_4[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_4[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_5[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_5[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_6[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_7[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_7[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_8[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_9[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_9[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      io_state_out_10[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_10[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_11[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_11[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_12[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_12[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_13[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_14[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      io_state_out_15[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((state_15[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_395[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_32 _v2_local_12493_0
      UInt<8> _v2_local_12493_0;
      io_state_out_valid[L].val = static_cast<typename UInt<1>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((rounds[L].val) == ((static_cast<uint8_t>(0xbu) & 0xfu)))) & 0x1u)) & 0x1u));
      _s_rounds$next[L].val = static_cast<typename UInt<4>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xfu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xfu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s__T_253[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s__T_253[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))) | ((rounds[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))))) & 0xfu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))))) & 0xfu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))))) & 0xfu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xfu)) & 0xfu));
      _s_STM$next[L].val = static_cast<typename UInt<2>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(((((static_cast<uint8_t>(0x1u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(io_start[L].val) & 0x1u)) != 0))) | ((STM[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(io_start[L].val) & 0x1u)) != 0))))) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(0x2u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(((((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((STM[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0x3u)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))) | ((STM[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_254[L].val) & 0x1u)) != 0))))) & 0x3u)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_250[L].val) & 0x1u)) != 0))))) & 0x3u)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_248[L].val) & 0x1u)) != 0))))) & 0x3u)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0x3u)) & 0x3u));
      _v2_local_12493_0 = UInt<8>(_lut_lut$eq_32[essent_to_u64(state_3[L])]);
      _s_SubBytesModule$io_state_out_3[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_3[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12493_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_3[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_11[L] = UInt<8>(_lut_lut$eq_11[essent_to_u64(_s_SubBytesModule$io_state_out_3[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s_lut$eq_13[L] = UInt<8>(_lut_lut$eq_13[essent_to_u64(_s_SubBytesModule$io_state_out_3[L])]);
      _s_lut$eq_33[L] = UInt<8>(_lut_lut$eq_33[essent_to_u64(state_4[L])]);
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_34 _v2_local_12495_0
      UInt<8> _v2_local_12495_0;
      _s_SubBytesModule$io_state_out_4[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_4[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_33[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_4[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_5[L] = UInt<8>(_lut_lut$eq_5[essent_to_u64(_s_SubBytesModule$io_state_out_4[L])]);
      _s_lut$eq_12[L] = UInt<8>(_lut_lut$eq_12[essent_to_u64(_s_SubBytesModule$io_state_out_4[L])]);
      _v2_local_12495_0 = UInt<8>(_lut_lut$eq_34[essent_to_u64(state_5[L])]);
      _s_SubBytesModule$io_state_out_5[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_5[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12495_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_5[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_17[L] = UInt<8>(_lut_lut$eq_17[essent_to_u64(_s_SubBytesModule$io_state_out_5[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_35 _v2_local_12496_0
      UInt<8> _v2_local_12496_0;
      _s_lut$eq_28[L] = UInt<8>(_lut_lut$eq_28[essent_to_u64(_s_SubBytesModule$io_state_out_5[L])]);
      _v2_local_12496_0 = UInt<8>(_lut_lut$eq_35[essent_to_u64(state_6[L])]);
      _s_SubBytesModule$io_state_out_6[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_6[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12496_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_6[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_26[L] = UInt<8>(_lut_lut$eq_26[essent_to_u64(_s_SubBytesModule$io_state_out_6[L])]);
      _s_lut$eq_27[L] = UInt<8>(_lut_lut$eq_27[essent_to_u64(_s_SubBytesModule$io_state_out_6[L])]);
      _s_lut$eq_36[L] = UInt<8>(_lut_lut$eq_36[essent_to_u64(state_7[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_37 _v2_local_12498_0
      UInt<8> _v2_local_12498_0;
      _s_SubBytesModule$io_state_out_7[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_7[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_36[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_7[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_20[L] = UInt<8>(_lut_lut$eq_20[essent_to_u64(_s_SubBytesModule$io_state_out_7[L])]);
      _s_lut$eq_22[L] = UInt<8>(_lut_lut$eq_22[essent_to_u64(_s_SubBytesModule$io_state_out_7[L])]);
      _v2_local_12498_0 = UInt<8>(_lut_lut$eq_37[essent_to_u64(state_8[L])]);
      _s_SubBytesModule$io_state_out_8[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_8[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12498_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_8[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_14[L] = UInt<8>(_lut_lut$eq_14[essent_to_u64(_s_SubBytesModule$io_state_out_8[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_38 _v2_local_12499_0
      UInt<8> _v2_local_12499_0;
      _s_lut$eq_21[L] = UInt<8>(_lut_lut$eq_21[essent_to_u64(_s_SubBytesModule$io_state_out_8[L])]);
      _v2_local_12499_0 = UInt<8>(_lut_lut$eq_38[essent_to_u64(state_0[L])]);
      _s_SubBytesModule$io_state_out_0[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_0[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12499_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_0[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_3[L] = UInt<8>(_lut_lut$eq_3[essent_to_u64(_s_SubBytesModule$io_state_out_0[L])]);
      _s_lut$eq_6[L] = UInt<8>(_lut_lut$eq_6[essent_to_u64(_s_SubBytesModule$io_state_out_0[L])]);
      _s_lut$eq_39[L] = UInt<8>(_lut_lut$eq_39[essent_to_u64(state_9[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_40 _v2_local_12501_0
      UInt<8> _v2_local_12501_0;
      _s_SubBytesModule$io_state_out_9[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_9[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_39[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_9[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_7[L] = UInt<8>(_lut_lut$eq_7[essent_to_u64(_s_SubBytesModule$io_state_out_9[L])]);
      _s_lut$eq_8[L] = UInt<8>(_lut_lut$eq_8[essent_to_u64(_s_SubBytesModule$io_state_out_9[L])]);
      _v2_local_12501_0 = UInt<8>(_lut_lut$eq_40[essent_to_u64(state_10[L])]);
      _s_SubBytesModule$io_state_out_10[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_10[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12501_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_10[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_0[L] = UInt<8>(_lut_lut$eq_0[essent_to_u64(_s_SubBytesModule$io_state_out_10[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s_lut$eq_1[L] = UInt<8>(_lut_lut$eq_1[essent_to_u64(_s_SubBytesModule$io_state_out_10[L])]);
      _s_lut$eq_41[L] = UInt<8>(_lut_lut$eq_41[essent_to_u64(state_11[L])]);
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_42 _v2_local_12503_0
      UInt<8> _v2_local_12503_0;
      _s_SubBytesModule$io_state_out_11[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_11[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_41[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_11[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_29[L] = UInt<8>(_lut_lut$eq_29[essent_to_u64(_s_SubBytesModule$io_state_out_11[L])]);
      _s_lut$eq_31[L] = UInt<8>(_lut_lut$eq_31[essent_to_u64(_s_SubBytesModule$io_state_out_11[L])]);
      _v2_local_12503_0 = UInt<8>(_lut_lut$eq_42[essent_to_u64(state_12[L])]);
      _s_SubBytesModule$io_state_out_12[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_12[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12503_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_12[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_23[L] = UInt<8>(_lut_lut$eq_23[essent_to_u64(_s_SubBytesModule$io_state_out_12[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] lut$eq_43 _v2_local_12504_0
      UInt<8> _v2_local_12504_0;
      _s_lut$eq_30[L] = UInt<8>(_lut_lut$eq_30[essent_to_u64(_s_SubBytesModule$io_state_out_12[L])]);
      _v2_local_12504_0 = UInt<8>(_lut_lut$eq_43[essent_to_u64(state_13[L])]);
      _s_SubBytesModule$io_state_out_13[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_13[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12504_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_13[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_15[L] = UInt<8>(_lut_lut$eq_15[essent_to_u64(_s_SubBytesModule$io_state_out_13[L])]);
      _s_lut$eq_16[L] = UInt<8>(_lut_lut$eq_16[essent_to_u64(_s_SubBytesModule$io_state_out_13[L])]);
      _s_lut$eq_44[L] = UInt<8>(_lut_lut$eq_44[essent_to_u64(state_14[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_4 _v2_local_104_0
      UInt<8> _v2_local_104_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_4 _v2_local_12392_0
      UInt<8> _v2_local_12392_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_4 _v2_local_70_0
      UInt<8> _v2_local_70_0;
      _s_SubBytesModule$io_state_out_14[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_14[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_44[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_14[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12392_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_5[L].val) ^ (_s_lut$eq_7[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_14[L].val) ^ (_s_SubBytesModule$io_state_out_3[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_70_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_4[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_4[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12392_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_104_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_70_0.val) ^ (io_roundKey_4[L].val))) & 0xffu)) & 0xffu));
      _s_state_4$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_104_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_MixColumnsModule$io_state_out_7[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_12[L].val) ^ (_s_SubBytesModule$io_state_out_9[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_14[L].val) ^ (_s_lut$eq_13[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_7 _v2_local_107_0
      UInt<8> _v2_local_107_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_5 _v2_local_12393_0
      UInt<8> _v2_local_12393_0;
      // [v2 lane-local] lut$eq_9 _v2_local_12470_0
      UInt<8> _v2_local_12470_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_7 _v2_local_73_0
      UInt<8> _v2_local_73_0;
      _v2_local_73_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_7[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_s_MixColumnsModule$io_state_out_7[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_107_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_73_0.val) ^ (io_roundKey_7[L].val))) & 0xffu)) & 0xffu));
      _s_state_7$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_107_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12470_0 = UInt<8>(_lut_lut$eq_9[essent_to_u64(_s_SubBytesModule$io_state_out_14[L])]);
      _v2_local_12393_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_4[L].val) ^ (_s_lut$eq_8[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_v2_local_12470_0.val) ^ (_s_SubBytesModule$io_state_out_3[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_in_5[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_5[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_9[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12393_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_5 _v2_local_105_0
      UInt<8> _v2_local_105_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_6 _v2_local_12394_0
      UInt<8> _v2_local_12394_0;
      // [v2 lane-local] lut$eq_10 _v2_local_12471_0
      UInt<8> _v2_local_12471_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_6 _v2_local_72_0
      UInt<8> _v2_local_72_0;
      _v2_local_105_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_s_AddRoundKeyModule$io_state_in_5[L].val) ^ (io_roundKey_5[L].val))) & 0xffu)) & 0xffu));
      _s_state_5$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_105_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12471_0 = UInt<8>(_lut_lut$eq_10[essent_to_u64(_s_SubBytesModule$io_state_out_14[L])]);
      _v2_local_12394_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_4[L].val) ^ (_s_SubBytesModule$io_state_out_9[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_v2_local_12471_0.val) ^ (_s_lut$eq_11[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_72_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12394_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_6[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_72_0.val) ^ (io_roundKey_6[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      _s_state_6$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_45[L] = UInt<8>(_lut_lut$eq_45[essent_to_u64(state_15[L])]);
    }
    // [vec comb] 32 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_0 _v2_local_100_0
      UInt<8> _v2_local_100_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_0 _v2_local_12388_0
      UInt<8> _v2_local_12388_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_0 _v2_local_66_0
      UInt<8> _v2_local_66_0;
      _s_SubBytesModule$io_state_out_15[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_15[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_s_lut$eq_45[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_15[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12388_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_6[L].val) ^ (_s_lut$eq_17[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_10[L].val) ^ (_s_SubBytesModule$io_state_out_15[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_66_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_0[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_0[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12388_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_100_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_66_0.val) ^ (io_roundKey_0[L].val))) & 0xffu)) & 0xffu));
      _s_state_0$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_100_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_MixColumnsModule$io_state_out_1[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_0[L].val) ^ (_s_lut$eq_28[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_0[L].val) ^ (_s_SubBytesModule$io_state_out_15[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_1 _v2_local_101_0
      UInt<8> _v2_local_101_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_2 _v2_local_12390_0
      UInt<8> _v2_local_12390_0;
      // [v2 lane-local] lut$eq_2 _v2_local_12463_0
      UInt<8> _v2_local_12463_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_1 _v2_local_67_0
      UInt<8> _v2_local_67_0;
      _v2_local_67_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_1[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_5[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_s_MixColumnsModule$io_state_out_1[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_101_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_67_0.val) ^ (io_roundKey_1[L].val))) & 0xffu)) & 0xffu));
      _s_state_1$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_101_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12463_0 = UInt<8>(_lut_lut$eq_2[essent_to_u64(_s_SubBytesModule$io_state_out_15[L])]);
      _v2_local_12390_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_0[L].val) ^ (_s_SubBytesModule$io_state_out_5[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_1[L].val) ^ (_v2_local_12463_0.val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_in_2[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_2[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_10[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12390_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_2 _v2_local_102_0
      UInt<8> _v2_local_102_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_3 _v2_local_12391_0
      UInt<8> _v2_local_12391_0;
      // [v2 lane-local] lut$eq_4 _v2_local_12465_0
      UInt<8> _v2_local_12465_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_3 _v2_local_69_0
      UInt<8> _v2_local_69_0;
      _v2_local_102_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_s_AddRoundKeyModule$io_state_in_2[L].val) ^ (io_roundKey_2[L].val))) & 0xffu)) & 0xffu));
      _s_state_2$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_102_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12465_0 = UInt<8>(_lut_lut$eq_4[essent_to_u64(_s_SubBytesModule$io_state_out_15[L])]);
      _v2_local_12391_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_3[L].val) ^ (_s_SubBytesModule$io_state_out_5[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_10[L].val) ^ (_v2_local_12465_0.val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_69_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_15[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12391_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_3[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_69_0.val) ^ (io_roundKey_3[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] MixColumnsModule.io_state_out_14 _v2_local_12402_0
      UInt<8> _v2_local_12402_0;
      // [v2 lane-local] lut$eq_46 _v2_local_12507_0
      UInt<8> _v2_local_12507_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_14 _v2_local_80_0
      UInt<8> _v2_local_80_0;
      _s_state_3$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_3[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12507_0 = UInt<8>(_lut_lut$eq_46[essent_to_u64(state_1[L])]);
      _s_SubBytesModule$io_state_out_1[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_1[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12507_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_1[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12402_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_12[L].val) ^ (_s_SubBytesModule$io_state_out_1[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_27[L].val) ^ (_s_lut$eq_29[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_80_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_6[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12402_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_14[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_80_0.val) ^ (io_roundKey_14[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_15 _v2_local_115_0
      UInt<8> _v2_local_115_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_15 _v2_local_12403_0
      UInt<8> _v2_local_12403_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_15 _v2_local_81_0
      UInt<8> _v2_local_81_0;
      _s_state_14$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_14[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12403_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_30[L].val) ^ (_s_SubBytesModule$io_state_out_1[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_6[L].val) ^ (_s_lut$eq_31[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_81_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_15[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_11[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12403_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_115_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_81_0.val) ^ (io_roundKey_15[L].val))) & 0xffu)) & 0xffu));
      _s_state_15$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_115_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_24[L] = UInt<8>(_lut_lut$eq_24[essent_to_u64(_s_SubBytesModule$io_state_out_1[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] MixColumnsModule.io_state_out_12 _v2_local_12400_0
      UInt<8> _v2_local_12400_0;
      _v2_local_12400_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_23[L].val) ^ (_s_lut$eq_24[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_6[L].val) ^ (_s_SubBytesModule$io_state_out_11[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_in_12[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_12[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_12[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12400_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    // [vec comb] 27 templates x 16 lanes
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_12 _v2_local_112_0
      UInt<8> _v2_local_112_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_13 _v2_local_12401_0
      UInt<8> _v2_local_12401_0;
      // [v2 lane-local] lut$eq_25 _v2_local_12486_0
      UInt<8> _v2_local_12486_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_13 _v2_local_79_0
      UInt<8> _v2_local_79_0;
      _v2_local_112_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_s_AddRoundKeyModule$io_state_in_12[L].val) ^ (io_roundKey_12[L].val))) & 0xffu)) & 0xffu));
      _s_state_12$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_112_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12486_0 = UInt<8>(_lut_lut$eq_25[essent_to_u64(_s_SubBytesModule$io_state_out_1[L])]);
      _v2_local_12401_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_12[L].val) ^ (_v2_local_12486_0.val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_26[L].val) ^ (_s_SubBytesModule$io_state_out_11[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_79_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_1[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12401_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_13[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_79_0.val) ^ (io_roundKey_13[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] MixColumnsModule.io_state_out_8 _v2_local_12396_0
      UInt<8> _v2_local_12396_0;
      // [v2 lane-local] lut$eq_47 _v2_local_12508_0
      UInt<8> _v2_local_12508_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_8 _v2_local_74_0
      UInt<8> _v2_local_74_0;
      _s_state_13$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12508_0 = UInt<8>(_lut_lut$eq_47[essent_to_u64(state_2[L])]);
      _s_SubBytesModule$io_state_out_2[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x16u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_2[L].val))) & 0x1u)) & 0x1u)) != 0))) | ((_v2_local_12508_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(0xffu) & 0xffu)) == (state_2[L].val))) & 0x1u)) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12396_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_14[L].val) ^ (_s_lut$eq_15[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_2[L].val) ^ (_s_SubBytesModule$io_state_out_7[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_74_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12396_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_AddRoundKeyModule$io_state_out_8[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_74_0.val) ^ (io_roundKey_8[L].val))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_11 _v2_local_111_0
      UInt<8> _v2_local_111_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_11 _v2_local_12399_0
      UInt<8> _v2_local_12399_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_11 _v2_local_77_0
      UInt<8> _v2_local_77_0;
      _s_state_8$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_AddRoundKeyModule$io_state_out_8[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12399_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_lut$eq_21[L].val) ^ (_s_SubBytesModule$io_state_out_13[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_2[L].val) ^ (_s_lut$eq_22[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_77_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_11[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_7[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12399_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_111_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_77_0.val) ^ (io_roundKey_11[L].val))) & 0xffu)) & 0xffu));
      _s_state_11$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_111_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _s_lut$eq_18[L] = UInt<8>(_lut_lut$eq_18[essent_to_u64(_s_SubBytesModule$io_state_out_2[L])]);
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_9 _v2_local_109_0
      UInt<8> _v2_local_109_0;
      // [v2 lane-local] MixColumnsModule.io_state_out_9 _v2_local_12397_0
      UInt<8> _v2_local_12397_0;
      // [v2 lane-local] lut$eq_19 _v2_local_12480_0
      UInt<8> _v2_local_12480_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_9 _v2_local_75_0
      UInt<8> _v2_local_75_0;
      _v2_local_12397_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_8[L].val) ^ (_s_lut$eq_16[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_s_lut$eq_18[L].val) ^ (_s_SubBytesModule$io_state_out_7[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
      _v2_local_75_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_9[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_13[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_v2_local_12397_0.val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_109_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_75_0.val) ^ (io_roundKey_9[L].val))) & 0xffu)) & 0xffu));
      _s_state_9$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_109_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_12480_0 = UInt<8>(_lut_lut$eq_19[essent_to_u64(_s_SubBytesModule$io_state_out_2[L])]);
      _s_MixColumnsModule$io_state_out_10[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((static_cast<uint8_t>(((_s_SubBytesModule$io_state_out_8[L].val) ^ (_s_SubBytesModule$io_state_out_13[L].val))) & 0xffu)) ^ ((static_cast<uint8_t>(((_v2_local_12480_0.val) ^ (_s_lut$eq_20[L].val))) & 0xffu)))) & 0xffu)) & 0xffu));
    }
    ESSENT_LANE_LOOP
    for (int L = 0; L < 16; L++) {
      // [v2 lane-local] AddRoundKeyModule.io_state_out_10 _v2_local_110_0
      UInt<8> _v2_local_110_0;
      // [v2 lane-local] AddRoundKeyModule.io_state_in_10 _v2_local_76_0
      UInt<8> _v2_local_76_0;
      _v2_local_76_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>((((io_plaintext_10[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_s_SubBytesModule$io_state_out_2[L].val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))) | ((_s_MixColumnsModule$io_state_out_10[L].val) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_259[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_260[L].val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
      _v2_local_110_0.val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((_v2_local_76_0.val) ^ (io_roundKey_10[L].val))) & 0xffu)) & 0xffu));
      _s_state_10$next[L].val = static_cast<typename UInt<8>::scalar_t>((static_cast<uint8_t>((static_cast<uint8_t>(((((static_cast<uint8_t>(0x0u) & 0xffu)) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))) | (((static_cast<uint8_t>((((_v2_local_110_0.val) & ((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))) | (((static_cast<uint8_t>(0x0u) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(_s__T_335[L].val) & 0x1u)) != 0))))) & 0xffu)) & ~((uint8_t)0 - (uint8_t)(((static_cast<uint8_t>(reset.val) & 0x1u)) != 0))))) & 0xffu)) & 0xffu));
    }
    // [vec oracle-verify] 18 templates x 16 lanes
    #if ESSENT_ORACLE_VERIFY
    if (done_reset && checks_enabled && update_registers) {
      uint8_t _v2_vacc8 = 0;
      // [verify-reduction] u8: 18 fields, 4 accumulators
      uint8_t _v2_vacc8_p0 = 0;
      uint8_t _v2_vacc8_p1 = 0;
      uint8_t _v2_vacc8_p2 = 0;
      uint8_t _v2_vacc8_p3 = 0;
      ESSENT_TAIL_LOOP
      for (int L = 1; L < 16; L++) {
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_0$next[L]) ^ essent_raw(state_0[(L) - 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_1$next[L]) ^ essent_raw(state_1[(L) - 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_10$next[L]) ^ essent_raw(state_10[(L) - 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_11$next[L]) ^ essent_raw(state_11[(L) - 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_12$next[L]) ^ essent_raw(state_12[(L) - 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_13$next[L]) ^ essent_raw(state_13[(L) - 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_14$next[L]) ^ essent_raw(state_14[(L) - 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_15$next[L]) ^ essent_raw(state_15[(L) - 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_2$next[L]) ^ essent_raw(state_2[(L) - 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_3$next[L]) ^ essent_raw(state_3[(L) - 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_4$next[L]) ^ essent_raw(state_4[(L) - 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_5$next[L]) ^ essent_raw(state_5[(L) - 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_state_6$next[L]) ^ essent_raw(state_6[(L) - 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_state_7$next[L]) ^ essent_raw(state_7[(L) - 1]));
        _v2_vacc8_p2 |= (uint8_t)(essent_raw(_s_state_8$next[L]) ^ essent_raw(state_8[(L) - 1]));
        _v2_vacc8_p3 |= (uint8_t)(essent_raw(_s_state_9$next[L]) ^ essent_raw(state_9[(L) - 1]));
        _v2_vacc8_p0 |= (uint8_t)(essent_raw(_s_STM$next[L]) ^ essent_raw(STM[(L) - 1]));
        _v2_vacc8_p1 |= (uint8_t)(essent_raw(_s_rounds$next[L]) ^ essent_raw(rounds[(L) - 1]));
      }
      _v2_vacc8 = (uint8_t)(_v2_vacc8_p0 | _v2_vacc8_p1 | _v2_vacc8_p2 | _v2_vacc8_p3);
      if (UNLIKELY(((uint64_t)_v2_vacc8) != 0)) _v2_verify_rescan(0, false, 1, 16);
      // [boundary-carry] 18 last-lane next-state values
      _v2_bcarry_state_0 = _s_state_0$next[0];
      _v2_bcarry_state_1 = _s_state_1$next[0];
      _v2_bcarry_state_10 = _s_state_10$next[0];
      _v2_bcarry_state_11 = _s_state_11$next[0];
      _v2_bcarry_state_12 = _s_state_12$next[0];
      _v2_bcarry_state_13 = _s_state_13$next[0];
      _v2_bcarry_state_14 = _s_state_14$next[0];
      _v2_bcarry_state_15 = _s_state_15$next[0];
      _v2_bcarry_state_2 = _s_state_2$next[0];
      _v2_bcarry_state_3 = _s_state_3$next[0];
      _v2_bcarry_state_4 = _s_state_4$next[0];
      _v2_bcarry_state_5 = _s_state_5$next[0];
      _v2_bcarry_state_6 = _s_state_6$next[0];
      _v2_bcarry_state_7 = _s_state_7$next[0];
      _v2_bcarry_state_8 = _s_state_8$next[0];
      _v2_bcarry_state_9 = _s_state_9$next[0];
      _v2_bcarry_STM = _s_STM$next[0];
      _v2_bcarry_rounds = _s_rounds$next[0];
    }
    #endif
    // [vec commit] 18 templates x 16 lanes
    if (update_registers) {
      essent_commit_lanes<16>(&state_0[0], &_s_state_0$next[0]);
      essent_commit_lanes<16>(&state_1[0], &_s_state_1$next[0]);
      essent_commit_lanes<16>(&state_2[0], &_s_state_2$next[0]);
      essent_commit_lanes<16>(&state_3[0], &_s_state_3$next[0]);
      essent_commit_lanes<16>(&state_4[0], &_s_state_4$next[0]);
      essent_commit_lanes<16>(&state_5[0], &_s_state_5$next[0]);
      essent_commit_lanes<16>(&state_6[0], &_s_state_6$next[0]);
      essent_commit_lanes<16>(&state_7[0], &_s_state_7$next[0]);
      essent_commit_lanes<16>(&state_8[0], &_s_state_8$next[0]);
      essent_commit_lanes<16>(&state_9[0], &_s_state_9$next[0]);
      essent_commit_lanes<16>(&state_10[0], &_s_state_10$next[0]);
      essent_commit_lanes<16>(&state_11[0], &_s_state_11$next[0]);
      essent_commit_lanes<16>(&state_12[0], &_s_state_12$next[0]);
      essent_commit_lanes<16>(&state_13[0], &_s_state_13$next[0]);
      essent_commit_lanes<16>(&state_14[0], &_s_state_14$next[0]);
      essent_commit_lanes<16>(&state_15[0], &_s_state_15$next[0]);
      essent_commit_lanes<16>(&rounds[0], &_s_rounds$next[0]);
      essent_commit_lanes<16>(&STM[0], &_s_STM$next[0]);
    }
    if (update_registers) oracle_boundary_valid = done_reset && checks_enabled;
    if (done_reset && checks_enabled && update_registers && assert_triggered) exit(assert_exit_code);
    if (!done_reset || !checks_enabled) assert_triggered = false;
    if (update_registers && done_reset) { oracle_cycle += 32; oracle_win_base += ORACLE_BLOCK_BYTES; }
  }

  void eval(bool update_registers, bool verbose, bool done_reset) {
    eval_forward(update_registers, verbose, done_reset);
    eval_reverse(update_registers, verbose, done_reset);
  }
  static constexpr int ESSENT_PARTITIONS = 0;
  #if ESSENT_ORACLE_VERIFY
  #ifndef ESSENT_VERIFY_COUNT_ONLY
  #define ESSENT_VERIFY_COUNT_ONLY 1
  #endif
  #if ESSENT_VERIFY_COUNT_ONLY
  ESSENT_NOINLINE uint64_t _v2_verify_count(int _v2_group, bool _forward, int _lo, int _hi) const {
    switch (_v2_group) {
      case 0: {
        const int64_t _cycle = oracle_cycle;
        const int64_t _min = _forward ? 1 - _cycle : _cycle + 33 - (int64_t)ORACLE_NUM_CYCLES;
        const int64_t _max = _forward ? (int64_t)ORACLE_NUM_CYCLES - _cycle - 1 : _cycle + 31;
        const int64_t _begin = _min > _lo ? _min : _lo;
        const int64_t _end = _max < _hi ? _max : _hi;
        uint64_t _count = 0;
        ESSENT_LANE_LOOP
        for (int64_t L = _begin; L < _end; ++L) {
          const int64_t _other = L + (_forward ? 1 : -1);
          _count += (uint64_t)(!(_s_state_0$next[L] == state_0[_other]));
          _count += (uint64_t)(!(_s_state_1$next[L] == state_1[_other]));
          _count += (uint64_t)(!(_s_state_10$next[L] == state_10[_other]));
          _count += (uint64_t)(!(_s_state_11$next[L] == state_11[_other]));
          _count += (uint64_t)(!(_s_state_12$next[L] == state_12[_other]));
          _count += (uint64_t)(!(_s_state_13$next[L] == state_13[_other]));
          _count += (uint64_t)(!(_s_state_14$next[L] == state_14[_other]));
          _count += (uint64_t)(!(_s_state_15$next[L] == state_15[_other]));
          _count += (uint64_t)(!(_s_state_2$next[L] == state_2[_other]));
          _count += (uint64_t)(!(_s_state_3$next[L] == state_3[_other]));
          _count += (uint64_t)(!(_s_state_4$next[L] == state_4[_other]));
          _count += (uint64_t)(!(_s_state_5$next[L] == state_5[_other]));
          _count += (uint64_t)(!(_s_state_6$next[L] == state_6[_other]));
          _count += (uint64_t)(!(_s_state_7$next[L] == state_7[_other]));
          _count += (uint64_t)(!(_s_state_8$next[L] == state_8[_other]));
          _count += (uint64_t)(!(_s_state_9$next[L] == state_9[_other]));
          _count += (uint64_t)(!(_s_STM$next[L] == STM[_other]));
          _count += (uint64_t)(!(_s_rounds$next[L] == rounds[_other]));
        }
        return _count;
      }
      default: return 0;
    }
  }
  #endif
  ESSENT_COLD_NOINLINE void _v2_verify_rescan(int _v2_group, bool _forward, int _lo, int _hi) {
    #if ESSENT_VERIFY_COUNT_ONLY
    if (!oracle_mismatches_fatal && verify_mismatches >= oracle_mismatch_log_limit) {
      const uint64_t _count = _v2_verify_count(_v2_group, _forward, _lo, _hi);
      if (_count <= UINT64_MAX - verify_mismatches) { verify_mismatches += _count; return; }
    }
    #endif
    switch (_v2_group) {
      case 0: {
        for (int L = _lo; L < _hi; L++) {
          const int _v2_other = _forward ? L + 1 : L - 1;
          const int _v2_self_idx = oracle_cycle + (_forward ? L : 31 - L);
          const int _v2_cycle_idx = oracle_cycle + (_forward ? L + 1 : 32 - L);
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_0$next[L] == state_0[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_0 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_0$next[L]), essent_to_u64(state_0[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_1$next[L] == state_1[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_1 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_1$next[L]), essent_to_u64(state_1[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_10$next[L] == state_10[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_10 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_10$next[L]), essent_to_u64(state_10[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_11$next[L] == state_11[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_11 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_11$next[L]), essent_to_u64(state_11[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_12$next[L] == state_12[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_12 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_12$next[L]), essent_to_u64(state_12[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_13$next[L] == state_13[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_13 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_13$next[L]), essent_to_u64(state_13[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_14$next[L] == state_14[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_14 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_14$next[L]), essent_to_u64(state_14[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_15$next[L] == state_15[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_15 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_15$next[L]), essent_to_u64(state_15[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_2$next[L] == state_2[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_2 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_2$next[L]), essent_to_u64(state_2[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_3$next[L] == state_3[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_3 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_3$next[L]), essent_to_u64(state_3[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_4$next[L] == state_4[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_4 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_4$next[L]), essent_to_u64(state_4[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_5$next[L] == state_5[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_5 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_5$next[L]), essent_to_u64(state_5[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_6$next[L] == state_6[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_6 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_6$next[L]), essent_to_u64(state_6[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_7$next[L] == state_7[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_7 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_7$next[L]), essent_to_u64(state_7[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_8$next[L] == state_8[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_8 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_8$next[L]), essent_to_u64(state_8[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_state_9$next[L] == state_9[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_9 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_state_9$next[L]), essent_to_u64(state_9[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_STM$next[L] == STM[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=STM lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_STM$next[L]), essent_to_u64(STM[_v2_other]));
            record_oracle_mismatch();
          }
          if ((_v2_self_idx) >= 1 && (_v2_cycle_idx) < ORACLE_NUM_CYCLES && (!(_s_rounds$next[L] == rounds[_v2_other]))) {
            if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=rounds lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 "\n", (int)(L), (int)(_v2_cycle_idx), essent_to_u64(_s_rounds$next[L]), essent_to_u64(rounds[_v2_other]));
            record_oracle_mismatch();
          }
        }
        break;
      }
      default: break;
    }
  }
  #endif

  #if ESSENT_ORACLE_VERIFY
  ESSENT_COLD_NOINLINE void _v2_verify_boundary_rescan(int _v2_group, bool _forward) {
    const int _v2_lane = _forward ? 0 : 15;  // lane of the previous sweep that produced the value
    const int _v2_idx = _forward ? 0 : 31;
    const int _v2_cycle_idx = oracle_cycle + (_forward ? 0 : 16);
    if (_v2_cycle_idx - 1 < 1 || _v2_cycle_idx >= ORACLE_NUM_CYCLES) return;
    switch (_v2_group) {
      case 0: {
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 0L) /* trace_state_0 */), _v2_idx));
        if (!(_v2_bcarry_state_0 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_0 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_0), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 32L) /* trace_state_1 */), _v2_idx));
        if (!(_v2_bcarry_state_1 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_1 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_1), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 320L) /* trace_state_10 */), _v2_idx));
        if (!(_v2_bcarry_state_10 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_10 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_10), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 352L) /* trace_state_11 */), _v2_idx));
        if (!(_v2_bcarry_state_11 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_11 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_11), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 384L) /* trace_state_12 */), _v2_idx));
        if (!(_v2_bcarry_state_12 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_12 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_12), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 416L) /* trace_state_13 */), _v2_idx));
        if (!(_v2_bcarry_state_13 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_13 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_13), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 448L) /* trace_state_14 */), _v2_idx));
        if (!(_v2_bcarry_state_14 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_14 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_14), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 480L) /* trace_state_15 */), _v2_idx));
        if (!(_v2_bcarry_state_15 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_15 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_15), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 64L) /* trace_state_2 */), _v2_idx));
        if (!(_v2_bcarry_state_2 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_2 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_2), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 96L) /* trace_state_3 */), _v2_idx));
        if (!(_v2_bcarry_state_3 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_3 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_3), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 128L) /* trace_state_4 */), _v2_idx));
        if (!(_v2_bcarry_state_4 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_4 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_4), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 160L) /* trace_state_5 */), _v2_idx));
        if (!(_v2_bcarry_state_5 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_5 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_5), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 192L) /* trace_state_6 */), _v2_idx));
        if (!(_v2_bcarry_state_6 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_6 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_6), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 224L) /* trace_state_7 */), _v2_idx));
        if (!(_v2_bcarry_state_7 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_7 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_7), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 256L) /* trace_state_8 */), _v2_idx));
        if (!(_v2_bcarry_state_8 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_8 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_8), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<8> _v2_oracle = UInt<8>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 288L) /* trace_state_9 */), _v2_idx));
        if (!(_v2_bcarry_state_9 == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=state_9 lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_state_9), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<2> _v2_oracle = UInt<2>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 544L) /* trace_STM */), _v2_idx));
        if (!(_v2_bcarry_STM == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=STM lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_STM), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        { const UInt<4> _v2_oracle = UInt<4>(ESSENT_ORACLE_LOAD(((const uint8_t*)(oracle_win_base + 512L) /* trace_rounds */), _v2_idx));
        if (!(_v2_bcarry_rounds == _v2_oracle)) {
          if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH reg=rounds lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64 " [window-boundary]\n", _v2_lane, _v2_cycle_idx, essent_to_u64(_v2_bcarry_rounds), essent_to_u64(_v2_oracle));
          record_oracle_mismatch();
        } }
        break;
      }
      default: break;
    }
  }
  #endif

} Cipher;

#endif  // CIPHER_H_
