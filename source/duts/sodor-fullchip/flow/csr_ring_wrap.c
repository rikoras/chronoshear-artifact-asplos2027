#include <stdint.h>

// Exercise the dense producer's per-ring-slot cold-stream cache after every
// one of its 32 slots has been reused.  Each iteration changes both an
// ordinary CSR and an HPM counter; 512 iterations cover hundreds of W=16
// windows and many complete ring wraps.
int main(void) {
  uint32_t seen = 0;

  for (uint32_t i = 0; i < 512; ++i) {
    const uint32_t scratch = 0x13579bdfu ^ (i * 0x10204081u);
    const uint32_t hpm_low = 0x89abcdefu + i * 0x01010101u;

    __asm__ volatile("csrw mscratch, %0" :: "r"(scratch));
    __asm__ volatile("csrr %0, mscratch" : "=r"(seen));
    if (seen != scratch)
      return 1;

    __asm__ volatile("csrw 0xb03, %0" :: "r"(hpm_low));
    __asm__ volatile("csrr %0, 0xb03" : "=r"(seen));
    if (seen != hpm_low)
      return 2;
  }

  return 0;
}
