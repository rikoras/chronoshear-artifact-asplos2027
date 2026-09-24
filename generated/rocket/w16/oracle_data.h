#pragma once
#include <cstdint>
constexpr int ORACLE_NUM_CYCLES=1<<30, ORACLE_ARRAY_LEN=1<<30, ORACLE_STREAM_COUNT=1092;
constexpr int64_t ORACLE_DATA_BLOCK_BYTES=53120LL;
constexpr int ORACLE_DATA_MIRRORED=1;
#define ROCKET_CONSUMER_EXTERNAL_DRAM 1
inline const char* oracle_kernel_base=nullptr;
