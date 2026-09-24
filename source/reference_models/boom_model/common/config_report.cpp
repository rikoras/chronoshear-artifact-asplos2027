// Build-time geometry input for record layout generation. The C++ constants
// above remain the single model configuration definition.
#include "boom_config.h"
#include <cstdio>
int main() {
  using namespace boomcfg;
  std::printf("{\"width\":%d,\"rows\":%d,\"rob_entries\":%d,\"ldq\":%d,\"stq\":%d,"
              "\"int_iq\":%d,\"mem_iq\":%d,\"fp_iq\":%d,\"int_regs\":%d,\"fp_regs\":%d,"
              "\"branches\":%d,\"ftq\":%d,\"banks\":%d,\"fetch_width\":%d,\"fb\":%d,"
              "\"hpm\":%d,\"dcache_ways\":%d,\"mshrs\":%d,\"beat_bytes\":%d,"
              "\"mul_port\":%u,\"div_port\":%u,\"csr_port\":%u,\"i2f_port\":%u}\n",
              CORE_WIDTH,NUM_ROB_ROWS,NUM_ROB_ENTRIES,NUM_LDQ,NUM_STQ,NUM_INT_IQ_SLOTS,NUM_MEM_IQ_SLOTS,
              NUM_FP_IQ_SLOTS,NUM_PREGS,NUM_FPREGS,MAX_BR_COUNT,NUM_FTQ,NBANKS,FETCH_WIDTH,NUM_FB_ENTRIES,
              NUM_HPM,DCACHE_WAYS,DCACHE_MSHRS,TILE_BEAT_BYTES,MUL_PORT,DIV_PORT,CSR_PORT,I2F_PORT);
}
