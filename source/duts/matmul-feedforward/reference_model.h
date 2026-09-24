#pragma once
// Independent mathematical checker. No DUT type, RTL header or trace input.
#include <cstdint>
namespace chisa::matmul_model {
template<unsigned N,unsigned Frames>
void fill_expected(const std::uint8_t (&left)[N*N][Frames],
                   const std::uint8_t (&right)[N*N][Frames],
                   std::uint32_t (&result)[Frames][N*N]) {
  for(unsigned frame=0;frame<Frames;++frame)
    for(unsigned row=0;row<N;++row)
      for(unsigned column=0;column<N;++column) {
        std::uint32_t sum=0;
        for(unsigned k=0;k<N;++k) sum+=std::uint32_t(left[row*N+k][frame])*right[k*N+column][frame];
        result[frame][row*N+column]=sum;
      }
}
} // namespace chisa::matmul_model
