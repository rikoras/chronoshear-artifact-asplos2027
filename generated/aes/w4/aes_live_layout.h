#pragma once
#include <cstddef>
inline constexpr std::size_t aes_offsets[18] = {0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136};
inline constexpr std::size_t aes_block_bytes = 192;
inline constexpr int aes_width = 4;
inline constexpr bool aes_mirrored = true;
