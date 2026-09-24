// Inspect software FPU controls for instruction words; no circuit equations.
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include "fpu.h"
int main(int argc,char** argv) {
  for (int i=1;i<argc;++i) {
    char* end=nullptr; errno=0;
    const auto inst=std::strtoull(argv[i],&end,0);
    if (errno || end==argv[i] || *end || inst>UINT32_MAX) return 2;
    const auto c=chisa::rocket_model::Fpu::decode(uint32_t(inst));
    std::printf("inst=%08x ldst=%u wen=%u reads=%u%u%u swap=%u%u type=%u/%u fromint=%u toint=%u fast=%u fma=%u div=%u sqrt=%u flags=%u\n",
      unsigned(inst),unsigned(c.ldst),unsigned(c.wen),unsigned(c.ren1),unsigned(c.ren2),unsigned(c.ren3),
      unsigned(c.swap12),unsigned(c.swap23),unsigned(c.typeTagIn),unsigned(c.typeTagOut),
      unsigned(c.fromint),unsigned(c.toint),unsigned(c.fastpipe),unsigned(c.fma),unsigned(c.div),unsigned(c.sqrt),unsigned(c.wflags));
  }
  return 0;
}
