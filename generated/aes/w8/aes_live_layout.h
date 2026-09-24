#pragma once
#include <cstddef>
inline constexpr std::size_t aes_offsets[18] = {0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,256,272};
inline constexpr std::size_t aes_block_bytes = 320;
inline constexpr int aes_width = 8;
inline constexpr bool aes_mirrored = true;
