#pragma once
#include <cstddef>
#include <cstring>
#if defined(__AVX512F__)
#include <immintrin.h>
#endif

namespace chisa::boom_system {
// The destination is an initialized, exclusively owned image range. Avoid
// taking write ownership of lines whose complete bytes already match. No
// source snapshot, dirty bookkeeping or additional record is maintained.
inline void copy_changed_image_lines(char* dst,const unsigned char* src,std::size_t bytes) {
  std::size_t at=0;
#if defined(__AVX512F__)
  for (;at+64<=bytes;at+=64) {
    const auto value=_mm512_loadu_si512(src+at);
    const auto old=_mm512_loadu_si512(dst+at);
    if (_mm512_cmpneq_epi64_mask(value,old)) _mm512_storeu_si512(dst+at,value);
  }
#endif
  if (at<bytes && std::memcmp(dst+at,src+at,bytes-at)) std::memcpy(dst+at,src+at,bytes-at);
}
} // namespace chisa::boom_system
