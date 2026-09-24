#pragma once
#include "generated/image.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <stdexcept>
#include <vector>
#if defined(__SSE2__)
#include <emmintrin.h>
#endif

namespace chisa::rocket_model {
template<unsigned W> constexpr unsigned window_offset(const StreamInfo& stream) {
  static_assert(W == 4 || W == 8 || W == 16 || W == 32);
  if constexpr (W == 4) return stream.block_offset_w4;
  if constexpr (W == 8) return 2 * stream.block_offset_w4;
  if constexpr (W == 16) return stream.block_offset_w16;
  return stream.block_offset_w32;
}

// Build the geometry once. Like BOOM's image decoder, group equal-width
// fields and load eight adjacent byte fields together. Every selected byte
// is still written, including invalid payloads and the reversed half-window.
template<unsigned W> class OracleWindowExpander {
  static_assert(W == 4 || W == 8 || W == 16 || W == 32);
  struct Lane { uint32_t source, destination; };
  struct ByteTile { uint32_t source; std::array<uint32_t,8> destination; };
  std::vector<Lane> bytes_, halfwords_, words_, doublewords_;
  std::vector<ByteTile> tiles_;

  template<class T>
  static void transpose(const std::vector<Lane>& lanes, const char* images, char* block) {
    for(const auto& lane:lanes) {
      const char* source=images+lane.source;
      char* destination=block+lane.destination;
      for(unsigned p=0;p<W;++p)
        std::memcpy(destination+p*sizeof(T),source+p*sizeof(Image),sizeof(T));
      for(unsigned p=W;p<2*W;++p)
        std::memcpy(destination+(3*W-1-p)*sizeof(T),source+p*sizeof(Image),sizeof(T));
    }
  }
#if defined(__SSE2__)
  template<bool Reverse>
  void transpose_tiles(const char* images,char* block) const {
    for(const auto& tile:tiles_) {
      for(unsigned p=Reverse?W:0;p<(Reverse?2*W:W);p+=8) {
        __m128i rows[8];
        for(unsigned i=0;i<8;++i) {
          const unsigned source=p+(Reverse?7-i:i);
          rows[i]=_mm_loadl_epi64(reinterpret_cast<const __m128i*>(images+source*sizeof(Image)+tile.source));
        }
        const __m128i a0=_mm_unpacklo_epi8(rows[0],rows[1]);
        const __m128i a1=_mm_unpacklo_epi8(rows[2],rows[3]);
        const __m128i a2=_mm_unpacklo_epi8(rows[4],rows[5]);
        const __m128i a3=_mm_unpacklo_epi8(rows[6],rows[7]);
        const __m128i b0=_mm_unpacklo_epi16(a0,a1),b1=_mm_unpackhi_epi16(a0,a1);
        const __m128i b2=_mm_unpacklo_epi16(a2,a3),b3=_mm_unpackhi_epi16(a2,a3);
        const __m128i columns[]={_mm_unpacklo_epi32(b0,b2),_mm_unpackhi_epi32(b0,b2),
                                _mm_unpacklo_epi32(b1,b3),_mm_unpackhi_epi32(b1,b3)};
        const unsigned destination=Reverse?3*W-p-8:p;
        for(unsigned i=0;i<4;++i) {
          _mm_storel_epi64(reinterpret_cast<__m128i*>(block+tile.destination[2*i]+destination),columns[i]);
          _mm_storel_epi64(reinterpret_cast<__m128i*>(block+tile.destination[2*i+1]+destination),_mm_srli_si128(columns[i],8));
        }
      }
    }
  }
#endif
 public:
  OracleWindowExpander() {
    for(const auto& stream:kStreams) {
      if(stream.image_offset+stream.elem_bytes>sizeof(Image))
        throw std::logic_error("oracle source outside image");
      const Lane lane{stream.image_offset,window_offset<W>(stream)};
      switch(stream.elem_bytes) {
        case 1: bytes_.push_back(lane); break;
        case 2: halfwords_.push_back(lane); break;
        case 4: words_.push_back(lane); break;
        case 8: doublewords_.push_back(lane); break;
        default: throw std::logic_error("unsupported oracle element width");
      }
    }
#if defined(__SSE2__)
    if constexpr (W%8==0) {
      std::sort(bytes_.begin(),bytes_.end(),[](const Lane& a,const Lane& b){return a.source<b.source;});
      std::vector<Lane> remaining;
      for(size_t i=0;i<bytes_.size();) {
        bool contiguous=i+8<=bytes_.size();
        for(unsigned j=1;contiguous && j<8;++j) contiguous=bytes_[i+j].source==bytes_[i].source+j;
        if(!contiguous) { remaining.push_back(bytes_[i++]); continue; }
        ByteTile tile{};tile.source=bytes_[i].source;
        for(unsigned j=0;j<8;++j) tile.destination[j]=bytes_[i+j].destination;
        tiles_.push_back(tile);i+=8;
      }
      bytes_.swap(remaining);
    }
#endif
  }
  size_t byte_tile_count() const { return tiles_.size(); }
  void expand(const std::array<Image,2*W>& images,char* block) const {
    const char* source=reinterpret_cast<const char*>(images.data());
#if defined(__SSE2__)
    if constexpr (W%8==0) { transpose_tiles<false>(source,block);transpose_tiles<true>(source,block); }
#endif
    transpose<uint8_t>(bytes_,source,block);
    transpose<uint16_t>(halfwords_,source,block);
    transpose<uint32_t>(words_,source,block);
    transpose<uint64_t>(doublewords_,source,block);
  }
};

// Compatibility entry for callers that do not retain an explicit plan. Live
// drivers should construct their expander before starting the timed loop.
template<unsigned W> void expand_window(const std::array<Image,2*W>& images,char* block) {
  static const OracleWindowExpander<W> expander;
  expander.expand(images,block);
}
}  // namespace chisa::rocket_model
