#pragma once
#include <cstddef>
inline constexpr std::size_t aes_offsets[18] = {0,64,128,192,256,320,384,448,512,576,640,704,768,832,896,960,1024,1088};
inline constexpr std::size_t aes_block_bytes = 1152;
inline constexpr int aes_width = 32;
inline constexpr bool aes_mirrored = true;
