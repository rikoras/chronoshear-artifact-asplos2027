#pragma once
// Oracle-window transport, consumer side.  The producer writes one block
// per window: the record at position 0 and, per position, the list of lanes
// whose value moved during that cycle, with their new values (format in
// system_oracle_writer_logic.h).  The consumer expands into one hot
// reusable buffer whose byte layout is exactly the historical window-major
// block, so every generated injection/verify path is unchanged.
//
// Decode is O(changes) with one byte of state per lane: the expansion
// buffer keeps the previous window's values; an entry writes its element
// and fills the positions since the lane's previous entry with the value
// read back from the buffer; the end of the window completes each moved
// lane's tail and levels the lanes carried over from the previous window
// that did not move.  Destinations travel in the entries.
//
// Include after the (width-selected) system_oracle_writer inc: the codec is
// defined entirely in terms of kSystemOracleStreams and the record.

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <x86intrin.h>
#if defined(__AVX512BW__)
#include <immintrin.h>
#endif

namespace chisa::boom_system {

class OracleDeltaDecoder {
 public:
  OracleDeltaDecoder() : last_pos_(kSystemOracleModeledStreams, kNone) {
    touched_.reserve(kSystemOracleModeledStreams);
    carry_.reserve(kSystemOracleModeledStreams);
    for (int p = 0; p < kSystemOracleCyclesPerWindow; ++p)
      elem_of_[p] = static_cast<std::uint8_t>(
          p < kSystemOracleWidth ? p : 3 * kSystemOracleWidth - 1 - p);
    // Row transport: the lanes of each 64-byte record row, in record order.
    std::vector<std::vector<RowLane>> rows(kRows);
    for (std::uint32_t lane = 0; lane < kSystemOracleModeledStreams; ++lane) {
      const OracleRecordLane& d = kOracleRecordLane[lane];
      RowLane rl;
      rl.block_offset = kSystemOracleStreams[lane].block_offset;
      rl.lane = static_cast<std::uint16_t>(lane);
      rl.in_row = static_cast<std::uint8_t>(d.offset % kOracleRecordChunkBytes);
      rl.bytes = d.bytes;
      rl.byte_mask = (std::uint64_t{1} << d.bytes) - 1u;
      rows[d.offset / kOracleRecordChunkBytes].push_back(rl);
    }
    for (std::uint32_t r = 0; r < kRows; ++r) {
      row_begin_[r] = static_cast<std::uint32_t>(row_lanes_.size());
      row_lanes_.insert(row_lanes_.end(), rows[r].begin(), rows[r].end());
    }
    row_begin_[kRows] = static_cast<std::uint32_t>(row_lanes_.size());
  }

  /** Expand one complete window into the historical window-major layout.
    * Per lane the only state kept is one byte: the position of its latest
    * entry in this window, or "carry" (it moved inside the previous window
    * and its elements are not uniform), or "none".  An entry stores its
    * element and fills the positions since the lane's previous entry with
    * that entry's value (read back from the buffer); the end of the window
    * completes every lane's tail and levels the carried lanes that did not
    * move.  Every destination comes from the entry itself.  Returns false
    * on a malformed block (magic / counts / destination out of range). */
  bool decode(const char* block, char* expanded) {
    std::uint32_t magic = 0, positions = 0, list_end = 0;
    std::memcpy(&magic, block, 4);
    std::memcpy(&positions, block + 4, 4);
    std::memcpy(&list_end, block + 8, 4);
    if (magic != kOracleCompactMagic ||
        positions != static_cast<std::uint32_t>(kSystemOracleCyclesPerWindow))
      return false;
    const unsigned char* base =
        reinterpret_cast<const unsigned char*>(block + kOracleCompactBaseOffset);
    const char* area = block + kOracleCompactListOffset;
    const char* index = block + kOracleCompactHeaderBytes;
    const std::uint64_t t0 = stats_ ? __rdtsc() : 0;
    if (!carry_valid_) {
      // First window: every owned lane from the base record, which is also
      // what the row transport's shadow starts from.
      for (std::uint32_t lane = lane_lo_; lane < lane_hi_; ++lane)
        splat_lane(lane, base, expanded);
      std::memcpy(shadow_, base, kOracleRecordPaddedBytes);
      releveled_lanes_ += lane_hi_ - lane_lo_;
      carry_valid_ = true;
    }
    touched_.clear();
    std::uint32_t begin = 0;
    for (std::uint32_t p = 0; p < positions; ++p) {
      std::uint32_t end = 0;
      std::memcpy(&end, index + 4 * p, 4);
      if (end < begin || end > list_end) return false;
      const char* entry = area + begin;
      const char* stop = area + end;
      if (entry != stop) {
        std::uint16_t first_lane;
        std::memcpy(&first_lane, entry + 4, 2);
        if (first_lane == kOracleChangeOverflowLane) {
          // Overflowed position: a whole record image follows the marker;
          // every lane holds it from here to the end of the window.
          if (stop - entry != static_cast<std::ptrdiff_t>(
                                  kOracleChangeEntryBytes + kOracleRecordPaddedBytes))
            return false;
          // From here on it is as if every lane had an entry at p.
          const unsigned char* image = reinterpret_cast<const unsigned char*>(
              entry + kOracleChangeEntryBytes);
          touched_.clear();
          for (std::uint32_t lane = lane_lo_; lane < lane_hi_; ++lane) {
            fill_positions(lane, static_cast<int>(p), kSystemOracleCyclesPerWindow - 1,
                           load_lane(image, lane), expanded);
            last_pos_[lane] = static_cast<std::uint8_t>(p);
            touched_.push_back(lane);
          }
          releveled_lanes_ += lane_hi_ - lane_lo_;
          begin = end;
          continue;
        }
      }
      while (entry < stop) {
        if (stop - entry < static_cast<std::ptrdiff_t>(kOracleChangeEntryBytes)) return false;
        std::uint32_t dst;
        std::uint16_t lane;
        std::memcpy(&dst, entry, 4);
        std::memcpy(&lane, entry + 4, 2);
        if (lane == kOracleRowLane) {
          // One record row: resolve it into the lanes whose bytes moved.
          if (stop - entry < static_cast<std::ptrdiff_t>(kOracleRowEntryBytes) ||
              (dst % kOracleRecordChunkBytes) != 0 ||
              dst + kOracleRecordChunkBytes > kOracleRecordPaddedBytes)
            return false;
          apply_row(dst, reinterpret_cast<const unsigned char*>(entry + kOracleChangeEntryBytes),
                    p, expanded);
          entry += kOracleRowEntryBytes;
          continue;
        }
        std::uint64_t value;
        std::memcpy(&value, entry + 8, 8);
        entry += kOracleChangeEntryBytes;
        if (lane >= kSystemOracleModeledStreams) return false;
        if (lane < lane_lo_ || lane >= lane_hi_) continue;  // another decoder's lane
        if (!apply_lane(lane, dst & 0xffffffu, dst >> 24, value, p, expanded)) return false;
      }
      begin = end;
    }
    const std::uint64_t t1 = stats_ ? __rdtsc() : 0;
    // Tails: every lane moved in this window holds its last value to the
    // end; those that moved after position 0 carry into the next window.
    const int last = kSystemOracleCyclesPerWindow - 1;
    // Carried lanes that did not move this window (still marked carry):
    // level them with the value they held at the previous window's end.
    // Before the tails below re-mark this window's movers as carried.
    for (const std::uint32_t lane : carry_) {
      if (last_pos_[lane] != kCarry) continue;
      char* region = expanded + lane_offset(lane);
      const std::uint32_t bytes = lane_bytes(lane);
      fill_run(region, bytes, 0, last, load_element(region, bytes, last));
      last_pos_[lane] = kNone;
      ++releveled_lanes_;
    }
    std::vector<std::uint32_t>& next_carry = carry_scratch_;
    next_carry.clear();
    for (const std::uint32_t lane : touched_) {
      const std::uint8_t q = last_pos_[lane];
      const std::uint32_t offset = lane_offset(lane);
      const std::uint32_t bytes = lane_bytes(lane);
      char* region = expanded + offset;
      if (static_cast<int>(q) < last)
        fill_run(region, bytes, static_cast<int>(q) + 1, last, load_element(region, bytes, q));
      if (q != 0) {
        last_pos_[lane] = kCarry;
        next_carry.push_back(lane);
      } else {
        last_pos_[lane] = kNone;
      }
    }
    carry_.swap(next_carry);
    if (stats_) {
      const std::uint64_t t2 = __rdtsc();
      stat_entries_ += t1 - t0; stat_tail_ += t2 - t1; ++stat_windows_;
      if ((stat_windows_ & 8191) == 0)
        std::fprintf(stderr, "[DECODE] windows=%llu entries=%.0f tail=%.0f ticks/window changes/window=%.1f carry=%zu\n",
                     (unsigned long long)stat_windows_, double(stat_entries_) / stat_windows_,
                     double(stat_tail_) / stat_windows_, double(changed_lanes_) / stat_windows_, carry_.size());
    }
    return true;
  }

  ~OracleDeltaDecoder() {
    if (lane_hist_path_ == nullptr || lane_hist_.empty()) return;
    if (std::FILE* f = std::fopen(lane_hist_path_, "w")) {
      for (std::size_t lane = 0; lane < lane_hist_.size(); ++lane)
        std::fprintf(f, "%zu %u\n", lane, lane_hist_[lane]);
      std::fclose(f);
    }
  }

  /** Restrict this decoder to lanes [lo, hi) (default: every lane). Must be
    * set before the first decode(); two decoders on disjoint ranges can then
    * expand one window into the same buffer from two threads. */
  void set_lane_range(std::uint32_t lo, std::uint32_t hi) { lane_lo_ = lo; lane_hi_ = hi; }

  /** Cumulative count of whole-lane re-fills performed by decode(). */
  std::uint64_t releveled_lanes() const { return releveled_lanes_; }
  /** Cumulative count of (lane, position >= 1) entries applied by decode(). */
  std::uint64_t changed_lanes() const { return changed_lanes_; }
  std::size_t base_bytes() const { return kOracleRecordBytes; }

  /** One change of one lane at position p: store its element and level the
    * positions since the lane's previous entry (see decode()). */
  bool apply_lane(std::uint32_t lane, std::uint32_t offset, std::uint32_t bytes,
                  std::uint64_t value, std::uint32_t p, char* expanded) {
    if ((bytes != 1 && bytes != 2 && bytes != 4 && bytes != 8) ||
        offset > kSystemOracleBlockBytes ||
        static_cast<std::size_t>(bytes) * kSystemOracleCyclesPerWindow >
            kSystemOracleBlockBytes - offset)
      return false;
    char* region = expanded + offset;
    const std::uint8_t q = last_pos_[lane];
    if (q == kCarry) {
      // Moved inside the previous window: level the positions before
      // this one with the value at the previous window's end.
      if (p != 0)
        fill_run(region, bytes, 0, static_cast<int>(p) - 1,
                 load_element(region, bytes, kSystemOracleCyclesPerWindow - 1));
    } else if (q != kNone && static_cast<std::uint32_t>(q) + 1 < p) {
      fill_run(region, bytes, static_cast<int>(q) + 1, static_cast<int>(p) - 1,
               load_element(region, bytes, q));
    }
    store_element(region, bytes, p, value);
    if (q == kNone || q == kCarry) touched_.push_back(lane);
    last_pos_[lane] = static_cast<std::uint8_t>(p);
    if (p != 0) ++changed_lanes_;
    if (lane_hist_path_ != nullptr) {
      if (lane_hist_.empty()) lane_hist_.assign(kSystemOracleModeledStreams, 0);
      ++lane_hist_[lane];
    }
    return true;
  }
  /** A shipped record row at position p: every lane of the row whose bytes
    * differ from this decoder's shadow takes the row's value; the shadow
    * then holds the row. */
  void apply_row(std::uint32_t row_offset, const unsigned char* data, std::uint32_t p,
                 char* expanded) {
    unsigned char* sh = shadow_ + row_offset;
#if defined(__AVX512BW__)
    const __m512i a = _mm512_loadu_si512(reinterpret_cast<const void*>(data));
    const __m512i b = _mm512_load_si512(reinterpret_cast<const void*>(sh));
    const std::uint64_t moved = _mm512_cmpneq_epi8_mask(a, b);
    if (moved == 0) return;
    _mm512_store_si512(reinterpret_cast<void*>(sh), a);
#else
    std::uint64_t moved = 0;
    for (unsigned k = 0; k < kOracleRecordChunkBytes; ++k)
      if (data[k] != sh[k]) moved |= std::uint64_t{1} << k;
    if (moved == 0) return;
    std::memcpy(sh, data, kOracleRecordChunkBytes);
#endif
    const std::uint32_t row = row_offset / kOracleRecordChunkBytes;
    for (std::uint32_t i = row_begin_[row]; i < row_begin_[row + 1]; ++i) {
      const RowLane& rl = row_lanes_[i];
      if (rl.lane < lane_lo_ || rl.lane >= lane_hi_) continue;
      if (((moved >> rl.in_row) & rl.byte_mask) == 0) continue;
      std::uint64_t value = 0;
      std::memcpy(&value, data + rl.in_row, rl.bytes);
      apply_lane(rl.lane, rl.block_offset, rl.bytes, value, p, expanded);
    }
  }
  /** Fill all 2W elements of a lane with its value in `rec`. */
  void splat_lane(std::uint32_t lane, const unsigned char* rec,
                  char* expanded) const {
    const auto& spec = kSystemOracleStreams[lane];
    fill_bytes(spec, 0,
               static_cast<std::size_t>(kSystemOracleCyclesPerWindow) *
                   spec.elem_bytes,
               load_lane(rec, lane), expanded);
  }

 private:
  static constexpr std::uint8_t kNone = 0xff;
  static constexpr std::uint8_t kCarry = 0xfe;
  static std::uint32_t lane_offset(std::uint32_t lane) { return kSystemOracleStreams[lane].block_offset; }
  static std::uint32_t lane_bytes(std::uint32_t lane) { return kSystemOracleStreams[lane].elem_bytes; }
  static std::uint64_t load_lane(const unsigned char* rec, std::uint32_t lane) {
    const OracleRecordLane& d = kOracleRecordLane[lane];
    std::uint64_t v = 0;
    std::memcpy(&v, rec + d.offset, d.bytes);
    return v;
  }
  std::uint64_t load_element(const char* region, std::uint32_t bytes, std::uint32_t p) const {
    std::uint64_t v = 0;
    std::memcpy(&v, region + elem_of_[p] * bytes, bytes);
    return v;
  }
  /** One element of one lane: a masked store of the lane's element width. */
  void store_element(char* region, std::uint32_t bytes, std::uint32_t p, std::uint64_t value) const {
    char* dst = region + elem_of_[p] * bytes;
#if defined(__AVX512BW__) && defined(__AVX512VL__)
    _mm_mask_storeu_epi8(dst, static_cast<__mmask16>((1u << bytes) - 1u),
                         _mm_cvtsi64_si128(static_cast<long long>(value)));
#else
    switch (bytes) {
      case 1: { const std::uint8_t v = static_cast<std::uint8_t>(value); std::memcpy(dst, &v, 1); break; }
      case 2: { const std::uint16_t v = static_cast<std::uint16_t>(value); std::memcpy(dst, &v, 2); break; }
      case 4: { const std::uint32_t v = static_cast<std::uint32_t>(value); std::memcpy(dst, &v, 4); break; }
      default: std::memcpy(dst, &value, 8); break;
    }
#endif
  }
  /** Write one value over the inclusive POSITION range [a, b] of a lane
    * region (element width `bytes`); a range crossing W splits into two
    * contiguous element ranges. */
  static void fill_run(char* region, std::uint32_t bytes, int a, int b, std::uint64_t value) {
    if (a > b) return;
    if (b < kSystemOracleWidth) {
      fill_region(region, bytes, a, b, value);
    } else if (a >= kSystemOracleWidth) {
      fill_region(region, bytes, 3 * kSystemOracleWidth - 1 - b, 3 * kSystemOracleWidth - 1 - a, value);
    } else {
      fill_region(region, bytes, a, kSystemOracleWidth - 1, value);
      fill_region(region, bytes, 3 * kSystemOracleWidth - 1 - b, 2 * kSystemOracleWidth - 1, value);
    }
  }
  static void fill_region(char* region, std::uint32_t bytes, int first, int last, std::uint64_t value) {
    fill_bytes_at(region, bytes, static_cast<std::size_t>(first) * bytes,
                  static_cast<std::size_t>(last + 1) * bytes, value);
  }
  static void fill_positions(std::uint32_t lane, int a, int b, std::uint64_t value, char* expanded) {
    fill_run(expanded + lane_offset(lane), lane_bytes(lane), a, b, value);
  }
  /** Broadcast one element value over the byte range [lo, hi) of a lane's
    * region.  With AVX-512BW this is one masked 64-byte store per chunk;
    * the mask keeps neighbouring lanes' bytes untouched. */
  static void fill_bytes_at(char* dst, std::uint32_t elem_bytes, std::size_t lo, std::size_t hi,
                            std::uint64_t value) {
    if (lo >= hi) return;
#if defined(__AVX512BW__)
    __m512i pattern;
    switch (elem_bytes) {
      case 1: pattern = _mm512_set1_epi8(static_cast<char>(value)); break;
      case 2: pattern = _mm512_set1_epi16(static_cast<short>(value)); break;
      case 4: pattern = _mm512_set1_epi32(static_cast<int>(value)); break;
      default: pattern = _mm512_set1_epi64(static_cast<long long>(value)); break;
    }
    for (std::size_t c = lo & ~std::size_t{63}; c < hi; c += 64) {
      const std::size_t a = lo > c ? lo - c : 0;
      const std::size_t b = hi - c < 64 ? hi - c : 64;
      const std::uint64_t upto = b >= 64 ? ~std::uint64_t{0}
                                         : (std::uint64_t{1} << b) - 1u;
      const std::uint64_t from = ~((std::uint64_t{1} << a) - 1u);
      _mm512_mask_storeu_epi8(dst + c, static_cast<__mmask64>(upto & from),
                              pattern);
    }
#else
    switch (elem_bytes) {
      case 1:
        std::memset(dst + lo, static_cast<int>(value & 0xffu), hi - lo);
        break;
      case 2: {
        const std::uint16_t s = static_cast<std::uint16_t>(value);
        for (std::size_t o = lo; o < hi; o += 2) std::memcpy(dst + o, &s, 2);
        break;
      }
      case 4: {
        const std::uint32_t s = static_cast<std::uint32_t>(value);
        for (std::size_t o = lo; o < hi; o += 4) std::memcpy(dst + o, &s, 4);
        break;
      }
      default:
        for (std::size_t o = lo; o < hi; o += 8) std::memcpy(dst + o, &value, 8);
        break;
    }
#endif
  }
  static void fill_bytes(const SystemOracleStreamSpec& spec, std::size_t lo,
                         std::size_t hi, std::uint64_t value, char* expanded) {
    fill_bytes_at(expanded + spec.block_offset, spec.elem_bytes, lo, hi, value);
  }

  std::uint32_t lane_lo_ = 0, lane_hi_ = kSystemOracleModeledStreams;
  bool carry_valid_ = false;
  // Row transport (see kOracleRowLane): the record as this decoder last saw
  // it, and the lanes of every row.
  static constexpr std::uint32_t kRows = kOracleRecordPaddedBytes / kOracleRecordChunkBytes;
  struct RowLane {
    std::uint32_t block_offset;
    std::uint16_t lane;
    std::uint8_t in_row;
    std::uint8_t bytes;
    std::uint64_t byte_mask;
  };
  std::vector<RowLane> row_lanes_;
  std::uint32_t row_begin_[kRows + 1] = {};
  alignas(64) unsigned char shadow_[kOracleRecordPaddedBytes] = {};
  const bool stats_ = std::getenv("SYSMODEL_DECODE_STATS") != nullptr;
  // SYSMODEL_DECODE_LANE_HIST=path: change entries per lane over the run
  // ("lane count" lines), for laying out the window block by activity.
  const char* lane_hist_path_ = std::getenv("SYSMODEL_DECODE_LANE_HIST");
  std::vector<std::uint32_t> lane_hist_;
  std::uint64_t stat_entries_ = 0, stat_tail_ = 0, stat_windows_ = 0;
  std::vector<std::uint8_t> last_pos_;
  std::vector<std::uint32_t> touched_, carry_, carry_scratch_;
  std::uint8_t elem_of_[kSystemOracleCyclesPerWindow] = {};
  std::uint64_t releveled_lanes_ = 0;
  std::uint64_t changed_lanes_ = 0;
};

}  // namespace chisa::boom_system
