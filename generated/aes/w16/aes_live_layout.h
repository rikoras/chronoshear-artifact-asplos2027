#pragma once
#include <cstddef>
inline constexpr std::size_t aes_offsets[18] = {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,480,512,544};
inline constexpr std::size_t aes_block_bytes = 576;
inline constexpr int aes_width = 16;
inline constexpr bool aes_mirrored = true;
