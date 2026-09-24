#pragma once
// Oracle-window transport, image form, consumer side.  The producer
// writes one block per window: a 64-byte header followed by 2W complete
// record images (one per position, kOracleRecordPaddedBytes each,
// format in system_oracle_writer_logic.h).  The consumer transposes the
// images into the historical window-major expansion buffer, so every
// generated injection/verify path is unchanged.
//
// Every element of every retained lane is written for every window: there is
// no per-lane state, no carry between windows and no copy-forward. A layout
// may explicitly omit lanes absent from its consumer contract; the model's
// record and underlying state are still maintained.
//
// Include after the (width-selected) system_oracle_writer inc: the codec is
// defined entirely in terms of kSystemOracleStreams and the record.

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <array>
#include "../boom_model/common/diagnostic_monitor.h"
#if defined(__SSE2__)
#include <emmintrin.h>
#endif

namespace chisa::boom_system {

class OracleImageDecoder {
 public:
  static constexpr std::uint32_t kOmittedOffset = UINT32_MAX;

  OracleImageDecoder() : OracleImageDecoder(nullptr, 0) {}

  // A consumer may retain the model's exact signals while placing them at
  // different offsets alongside additional access-proof streams.  Transpose
  // directly into that layout instead of copying an intermediate window.
  OracleImageDecoder(const std::uint32_t* block_offsets, std::size_t count,
                     std::size_t group_lanes = 32) {
    if (!group_lanes) throw std::invalid_argument("empty oracle decode group");
    if ((block_offsets != nullptr && count != kSystemOracleModeledStreams) ||
        (block_offsets == nullptr && count != 0))
      throw std::invalid_argument("oracle image destination layout size");
    for (std::size_t lane = 0; lane < kSystemOracleModeledStreams; ++lane) {
      // Only an explicitly remapped consumer layout can omit a source lane.
      if (block_offsets != nullptr && block_offsets[lane] == kOmittedOffset) continue;
      const SystemOracleStreamSpec& spec = kSystemOracleStreams[lane];
      CHISA_DIAG(diagnostic_lanes_.push_back({kOracleRecordLane[lane].offset,
          block_offsets == nullptr ? spec.block_offset : block_offsets[lane],
          spec.elem_bytes, lane}));
      Lane l{kOracleRecordLane[lane].offset,
             block_offsets == nullptr ? spec.block_offset : block_offsets[lane]};
      switch (spec.elem_bytes) {
        case 1: lanes1_.push_back(l); break;
        case 2: lanes2_.push_back(l); break;
        case 4: lanes4_.push_back(l); break;
        default: lanes8_.push_back(l); break;
      }
    }
    // Eight adjacent byte fields can share one load from each source image.
    // Output offsets remain arbitrary: the consumer layout need not match
    // record order. Isolated fields retain the generic transpose below.
#if defined(__SSE2__)
    if constexpr (kSystemOracleWidth % 8 == 0) {
      std::sort(lanes1_.begin(), lanes1_.end(), [](const Lane& a, const Lane& b) {
        return a.record_offset < b.record_offset;
      });
      std::vector<Lane> remaining;
      for (std::size_t i = 0; i < lanes1_.size();) {
        bool contiguous = i + 8 <= lanes1_.size();
        for (unsigned j = 1; contiguous && j < 8; ++j)
          contiguous = lanes1_[i + j].record_offset == lanes1_[i].record_offset + j;
        if (!contiguous) { remaining.push_back(lanes1_[i++]); continue; }
        ByteTile tile{}; tile.record_offset = lanes1_[i].record_offset;
        for (unsigned j = 0; j < 8; ++j) tile.block_offset[j] = lanes1_[i + j].block_offset;
        byte_tiles_.push_back(tile); i += 8;
      }
      lanes1_.swap(remaining);
    }
#endif
    // Retain complete SIMD byte tiles. Each output lane belongs to exactly
    // one group; groups have no carry and may run in any order.
    add_groups(Kind::Bytes, byte_tiles_.size(), std::max<std::size_t>(1, group_lanes / 8));
    add_groups(Kind::U8, lanes1_.size(), group_lanes);
    add_groups(Kind::U16, lanes2_.size(), group_lanes);
    add_groups(Kind::U32, lanes4_.size(), group_lanes);
    add_groups(Kind::U64, lanes8_.size(), group_lanes);
  }

  struct Window { const char* images = nullptr; char* expanded = nullptr; };
  bool validate_window(const char* block, char* expanded, Window& window) const {
    window = {};
    std::uint32_t magic = 0, positions = 0, image_bytes = 0;
    std::memcpy(&magic, block, 4);
    std::memcpy(&positions, block + 4, 4);
    std::memcpy(&image_bytes, block + 8, 4);
    if (magic != kOracleImageMagic || positions != kSystemOracleCyclesPerWindow ||
        image_bytes != kOracleRecordPaddedBytes) return false;
    window = {block + kOracleImageHeaderBytes, expanded};
    return true;
  }
  std::size_t group_count() const { return groups_.size(); }
  std::uint64_t group_readers(std::size_t group) const { return groups_.at(group).readers; }

  // Build once, before any window is used. Preserve complete SIMD tiles,
  // group outputs by their actual readers, then prioritize the requested
  // partitions. This changes neither source nor destination byte layouts.
  void partition_groups(const std::uint64_t* readers, std::size_t count,
                        unsigned partitions, const std::vector<int>& priority,
                        std::size_t group_lanes = 32, bool regroup = false) {
    if (count != kSystemOracleModeledStreams || !readers || !partitions || partitions > 63 || !group_lanes)
      throw std::invalid_argument("invalid partition reader contract");
    CHISA_DIAG(lane_readers_.assign(readers, readers + count));
    const auto all = (UINT64_C(1) << partitions) - 1;
    for (std::size_t lane=0;lane<count;++lane) {
      const auto mask=readers[lane];
      if (!mask || (mask & ~all)) throw std::invalid_argument("missing or invalid lane reader");
    }
    std::vector<std::pair<std::uint32_t,std::uint64_t>> by_offset;
    for (std::size_t lane=0;lane<count;++lane)
      by_offset.emplace_back(kSystemOracleStreams[lane].block_offset,readers[lane]);
    std::sort(by_offset.begin(),by_offset.end());
    const auto mask_for = [&](std::uint32_t offset) {
      const auto it=std::lower_bound(by_offset.begin(),by_offset.end(),std::make_pair(offset,UINT64_C(0)));
      if (it!=by_offset.end() && it->first==offset) return it->second;
      throw std::invalid_argument("partition delivery requires the audited destination layout");
    };
    const auto lane_mask=[&](const Lane& lane) { return mask_for(lane.block_offset); };
    const auto tile_mask=[&](const ByteTile& tile) {
      std::uint64_t mask=0;for (auto offset : tile.block_offset) mask |= mask_for(offset);return mask;
    };
    if (regroup) {
      for (auto* lanes : {&lanes1_, &lanes2_, &lanes4_, &lanes8_})
        std::stable_sort(lanes->begin(),lanes->end(),[&](const Lane& a,const Lane& b) { return lane_mask(a)<lane_mask(b); });
      std::stable_sort(byte_tiles_.begin(),byte_tiles_.end(),[&](const ByteTile& a,const ByteTile& b) { return tile_mask(a)<tile_mask(b); });
    }
    groups_.clear();
    const auto grouped = [&](Kind kind, const auto& lanes, std::size_t size, const auto& get_mask) {
      for (std::size_t begin=0;begin<lanes.size();) {
        std::size_t end=begin+1;
        auto mask=get_mask(lanes[begin]);
        while (end<lanes.size() && end-begin<size && (!regroup || get_mask(lanes[end])==mask))
          mask |= get_mask(lanes[end++]);
        groups_.push_back({kind,begin,end,mask});begin=end;
      }
    };
    grouped(Kind::Bytes,byte_tiles_,std::max<std::size_t>(1,group_lanes/8),tile_mask);
    grouped(Kind::U8,lanes1_,group_lanes,lane_mask);grouped(Kind::U16,lanes2_,group_lanes,lane_mask);
    grouped(Kind::U32,lanes4_,group_lanes,lane_mask);grouped(Kind::U64,lanes8_,group_lanes,lane_mask);
    std::array<unsigned,64> rank{};
    std::uint64_t seen=0;unsigned next=0;
    for (int p : priority) {
      if (p<0 || static_cast<unsigned>(p)>=partitions || (seen & (UINT64_C(1)<<p)))
        throw std::invalid_argument("invalid partition decode priority");
      rank[p]=next++;seen |= UINT64_C(1)<<p;
    }
    for (unsigned p=0;p<partitions;++p) if (!(seen & (UINT64_C(1)<<p))) rank[p]=next++;
    const auto first_rank = [&](std::uint64_t mask) {
      unsigned result=partitions;
      for (unsigned p=0;p<partitions;++p) if (mask & (UINT64_C(1)<<p)) result=std::min(result,rank[p]);
      return result;
    };
    if (!priority.empty()) std::stable_sort(groups_.begin(),groups_.end(),[&](const Group& a,const Group& b) {
      return first_rank(a.readers)<first_rank(b.readers);
    });
  }
  bool decode_group(const Window& window, std::size_t index) const {
    if (!window.images || !window.expanded || index >= groups_.size()) return false;
    const auto& group = groups_[index];
    switch (group.kind) {
#if defined(__SSE2__)
      case Kind::Bytes:
        transpose_bytes<false>(window.images, window.expanded, group.begin, group.end);
        transpose_bytes<true>(window.images, window.expanded, group.begin, group.end);
        break;
#else
      case Kind::Bytes: return false;
#endif
      case Kind::U8: transpose<std::uint8_t>(lanes1_, window.images, window.expanded, group.begin, group.end); break;
      case Kind::U16: transpose<std::uint16_t>(lanes2_, window.images, window.expanded, group.begin, group.end); break;
      case Kind::U32: transpose<std::uint32_t>(lanes4_, window.images, window.expanded, group.begin, group.end); break;
      case Kind::U64: transpose<std::uint64_t>(lanes8_, window.images, window.expanded, group.begin, group.end); break;
    }
    return true;
  }

  /** Expand one complete window.  Returns false on a malformed block
    * (magic / position count / image size). */
  bool decode(const char* block, char* expanded, std::uint64_t first_cycle = UINT64_MAX) const {
    (void)first_cycle;
    Window window;
    if (!validate_window(block, expanded, window)) return false;
    const char* images = window.images;
#if defined(__SSE2__)
    transpose_bytes<false>(images, expanded);
    transpose_bytes<true>(images, expanded);
#endif
    transpose<std::uint8_t>(lanes1_, images, expanded);
    transpose<std::uint16_t>(lanes2_, images, expanded);
    transpose<std::uint32_t>(lanes4_, images, expanded);
    transpose<std::uint64_t>(lanes8_, images, expanded);
    CHISA_DIAG(diagnostic_verify(block, expanded, first_cycle));
    return true;
  }

#if defined(CHISA_MODEL_DIAGNOSTICS)
  // Also callable immediately before RTL evaluation, so corruption between
  // expansion and injection is distinguished from a codec error. Independent
  // scalar byte reads cover all retained streams and both lane directions.
  void diagnostic_verify(const char* block, const char* expanded,
                         std::uint64_t first_cycle, bool injection = false,
                         int partition = -1, bool aggregate = true) const {
    using namespace ::chisa::diagnostic;
    set_cycle(first_cycle);
    std::uint64_t bad = 0, first_lane = UINT64_MAX, first_position = UINT64_MAX;
    std::uint64_t expected = 0, actual = 0;
    std::size_t checked_lanes=0;
    for (const auto& lane : diagnostic_lanes_) {
      // A partition may now run while unrelated expansion groups are still
      // writing. Its injection probe checks exactly its audited read set.
      if (injection && partition>=0 && !lane_readers_.empty() &&
          !(lane_readers_[lane.index] & (UINT64_C(1)<<partition))) continue;
      ++checked_lanes;
      for (unsigned p = 0; p < kSystemOracleCyclesPerWindow; ++p) {
        const unsigned element = p < kSystemOracleWidth ? p : 3 * kSystemOracleWidth - 1 - p;
        std::uint64_t want = 0, got = 0;
        std::memcpy(&want, block + kOracleImageHeaderBytes + p * kOracleRecordPaddedBytes + lane.source, lane.bytes);
        std::memcpy(&got, expanded + lane.destination + element * lane.bytes, lane.bytes);
        if (want != got) {
          if (!bad) { first_lane = lane.index; first_position = p; expected = want; actual = got; }
          ++bad;
        }
      }
    }
    if (!injection || aggregate)
      require("transport", injection ? "expanded-to-injection" : "image-to-expanded", first_cycle,
      injection ? Layer::Injection : Layer::Transport, Phase::Window, !bad,
      {{"lanes", checked_lanes}, {"positions", kSystemOracleCyclesPerWindow},
       {"bad_elements", bad}, {"first_lane", first_lane}, {"first_position", first_position},
       {"expected", expected}, {"actual", actual}});
    if (injection && partition >= 0) {
      static constexpr const char* names[] = {"expanded-to-injection-p0","expanded-to-injection-p1",
        "expanded-to-injection-p2","expanded-to-injection-p3","expanded-to-injection-p4","expanded-to-injection-p5"};
      if (static_cast<std::size_t>(partition) >= std::size(names))
        throw std::out_of_range("diagnostic injection partition");
      require("transport",names[partition],first_cycle,Layer::Injection,Phase::Window,!bad,
          {{"partition",static_cast<std::uint64_t>(partition)},{"bad_elements",bad},
           {"first_lane",first_lane},{"first_position",first_position},{"expected",expected},{"actual",actual}});
    }
    if (!injection)
      checkpoint("transport", "received-image", first_cycle, Layer::Transport,
        {{"bytes", kOracleImageHeaderBytes + kSystemOracleCyclesPerWindow * kOracleRecordPaddedBytes},
         {"digest", digest(block, kOracleImageHeaderBytes + kSystemOracleCyclesPerWindow * kOracleRecordPaddedBytes)}});
  }
#endif

 private:
  enum class Kind { Bytes, U8, U16, U32, U64 };
  struct Group { Kind kind; std::size_t begin, end; std::uint64_t readers=0; };
  std::vector<Group> groups_;
#if defined(CHISA_MODEL_DIAGNOSTICS)
  std::vector<std::uint64_t> lane_readers_;
#endif
  void add_groups(Kind kind, std::size_t count, std::size_t size) {
    for (std::size_t begin = 0; begin < count; begin += size)
      groups_.push_back({kind, begin, std::min(count, begin + size)});
  }
  struct Lane {
    std::uint32_t record_offset;
    std::uint32_t block_offset;
  };
  struct ByteTile {
    std::uint32_t record_offset;
    std::array<std::uint32_t, 8> block_offset;
  };
#if defined(__SSE2__)
  template <bool Reverse>
  void transpose_bytes(const char* images, char* expanded,
                       std::size_t begin = 0, std::size_t end = SIZE_MAX) const {
    constexpr unsigned W = kSystemOracleWidth;
    constexpr unsigned stride = kOracleRecordPaddedBytes;
    end = std::min(end, byte_tiles_.size());
    for (std::size_t index = begin; index < end; ++index) {
      const ByteTile& tile = byte_tiles_[index];
      for (unsigned p = Reverse ? W : 0; p < (Reverse ? 2 * W : W); p += 8) {
        __m128i rows[8];
        for (unsigned i = 0; i < 8; ++i) {
          const unsigned source = p + (Reverse ? 7 - i : i);
          rows[i] = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(
              images + source * stride + tile.record_offset));
        }
        const __m128i a0 = _mm_unpacklo_epi8(rows[0], rows[1]);
        const __m128i a1 = _mm_unpacklo_epi8(rows[2], rows[3]);
        const __m128i a2 = _mm_unpacklo_epi8(rows[4], rows[5]);
        const __m128i a3 = _mm_unpacklo_epi8(rows[6], rows[7]);
        const __m128i b0 = _mm_unpacklo_epi16(a0, a1);
        const __m128i b1 = _mm_unpackhi_epi16(a0, a1);
        const __m128i b2 = _mm_unpacklo_epi16(a2, a3);
        const __m128i b3 = _mm_unpackhi_epi16(a2, a3);
        const __m128i columns[4] = {
            _mm_unpacklo_epi32(b0, b2), _mm_unpackhi_epi32(b0, b2),
            _mm_unpacklo_epi32(b1, b3), _mm_unpackhi_epi32(b1, b3)};
        const unsigned destination = Reverse ? 3 * W - p - 8 : p;
        for (unsigned i = 0; i < 4; ++i) {
          _mm_storel_epi64(reinterpret_cast<__m128i*>(expanded + tile.block_offset[2 * i] + destination), columns[i]);
          _mm_storel_epi64(reinterpret_cast<__m128i*>(expanded + tile.block_offset[2 * i + 1] + destination),
                          _mm_srli_si128(columns[i], 8));
        }
      }
    }
  }
#endif
  /** Position p of the window is element p for p < W and element
    * 3W-1-p for p >= W (the reverse half is stored back to front). */
  template <class T>
  static void transpose(const std::vector<Lane>& lanes, const char* images,
                        char* expanded, std::size_t begin = 0, std::size_t end = SIZE_MAX) {
    constexpr int W = kSystemOracleWidth;
    constexpr std::size_t stride = kOracleRecordPaddedBytes;
    end = std::min(end, lanes.size());
    for (std::size_t index = begin; index < end; ++index) {
      const Lane& l = lanes[index];
      const char* src = images + l.record_offset;
      char* dst = expanded + l.block_offset;
      for (int p = 0; p < W; ++p)
        std::memcpy(dst + static_cast<std::size_t>(p) * sizeof(T),
                    src + static_cast<std::size_t>(p) * stride, sizeof(T));
      for (int p = W; p < 2 * W; ++p)
        std::memcpy(dst + static_cast<std::size_t>(3 * W - 1 - p) * sizeof(T),
                    src + static_cast<std::size_t>(p) * stride, sizeof(T));
    }
  }

  std::vector<Lane> lanes1_, lanes2_, lanes4_, lanes8_;
  std::vector<ByteTile> byte_tiles_;
#if defined(CHISA_MODEL_DIAGNOSTICS)
  struct DiagnosticLane { std::uint32_t source, destination; unsigned bytes; std::size_t index; };
  std::vector<DiagnosticLane> diagnostic_lanes_;
#endif
};

}  // namespace chisa::boom_system
