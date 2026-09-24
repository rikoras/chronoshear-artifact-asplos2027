#pragma once
#include <cstdint>

constexpr int ORACLE_NUM_CYCLES = 1 << 30;
constexpr int ORACLE_ARRAY_LEN = 1 << 30;
constexpr int64_t ORACLE_DATA_BLOCK_BYTES = 1472LL;
constexpr int ORACLE_DATA_MIRRORED = 1;
inline const char* oracle_kernel_base = nullptr;
