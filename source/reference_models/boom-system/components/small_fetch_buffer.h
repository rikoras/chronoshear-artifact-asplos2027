#pragma once
// ============================================================================
// Small BOOM FetchBuffer (fetchWidth=4, coreWidth=1, numEntries=8).
//
// This is the exact F4-to-F5 queue in the locked Small full-chip elaboration.
// It is intentionally not an ordinary FIFO: one enqueue can compact any
// subset of four halfword slots, while one MicroOp is dequeued per cycle.  The
// one-hot tail is also kept at least three free positions away from the head,
// so `enq.ready` guarantees room for the worst-case four-uop packet.
//
// Transcribed from third_party/riscv-boom/src/main/scala/ifu/fetch-buffer.scala.
// The diagnostic full-chip audit supplies only the module's raw IO boundary;
// neither the RTL RAM nor its converted `in_uops` wires are inputs here.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

#include "../../boom_model/common/core_types.h"
#include "small_f3_queues.h"

namespace chisa::boom_system::components {

struct SmallFetchBundle {
  std::uint64_t pc = 0;  // vaddrBitsExtended=40 in the locked elaboration
  std::array<std::uint32_t, boomcfg::FETCH_WIDTH> insts{};
  std::array<std::uint32_t, boomcfg::FETCH_WIDTH> expanded_insts{};
  std::uint8_t mask = 0;

  // One edge marker per fetch bank.  Keep the historical scalar alias for
  // bank 0 so the Small-only tests and callers stay source-compatible; Large
  // has a second independently generated marker for a 32-bit instruction
  // that straddles the two 8-byte banks inside one fetch packet.
  bool edge_inst = false;
  std::array<bool, boomcfg::NBANKS> edge_insts{};
  std::uint8_t sfb_mask = 0;
  std::uint8_t shadowed_mask = 0;

  bool cfi_valid = false;
  std::uint8_t cfi_idx = 0;
  // The FetchBuffer conversion does not consume the following predictor
  // snapshot, but the parallel FTQ enqueue does.  Keeping it in the same
  // packet is important: F4 may hold for an arbitrary number of cycles.
  std::uint8_t cfi_type = 0;
  bool cfi_is_call = false;
  bool cfi_is_ret = false;
  bool cfi_npc_plus4 = false;
  std::uint8_t br_mask = 0;
  SmallGlobalHistory ghist{};
  // nBanks=1, bpdMaxMetaLength=120.  The top byte of word 3 is unused.
  std::array<std::uint32_t, boomcfg::BPD_META_WORDS> bpd_meta{};  // sized by meta width; 2-bank layout lands with the bank batch
  std::uint64_t ras_top = 0;
  std::uint8_t ftq_idx = 0;

  bool xcpt_pf_if = false;
  bool xcpt_ae_if = false;
  std::uint8_t bp_debug_mask = 0;
  std::uint8_t bp_xcpt_mask = 0;
  std::uint8_t debug_fsrc = 0;
};

struct SmallFetchBufferInputs {
  bool reset = false;
  bool clear = false;
  bool enq_valid = false;
  bool deq_ready = false;
  SmallFetchBundle enq{};
};

struct SmallFetchBufferOutputs {
  bool enq_ready = false;
  bool deq_valid = false;
  bool uop_valid = false;    // dequeue slot 0 (the historical single-uop face)
  MicroOp uop{};
  std::array<MicroOp, boomcfg::MAX_CORE_WIDTH> uops_g{};
  std::array<bool, boomcfg::MAX_CORE_WIDTH> uop_valids_g{};
};

class SmallFetchBuffer {
 public:
  // Geometry follows the configuration (fetch-buffer.scala): a row holds one
  // dequeue group; head is a ROW-level one-hot, tail an ENTRY-level one-hot.
  // At CORE_WIDTH=1 rows == entries and everything below reduces bit-for-bit
  // to the historical single-uop queue.
  static constexpr std::size_t kEntries = boomcfg::NUM_FB_ENTRIES;
  static constexpr std::size_t kFetchWidth = boomcfg::FETCH_WIDTH;
  static constexpr std::size_t kDeqWidth = boomcfg::FB_DEQ_WIDTH;
  static constexpr std::size_t kRows = kEntries / kDeqWidth;
  static_assert(kEntries % kDeqWidth == 0, "rows must tile the buffer");
  static_assert(kFetchWidth <= 8,
      "slot masks in the buffer and the bundle are uint8_t bitmaps");

  SmallFetchBuffer() = default;

  // RegInit affects only the pointers/full bit.  fb_uop_ram is deliberately
  // not cleared by reset in the RTL, so reset_state() preserves the payload.
  void reset_state() {
    head_ = 0x01;
    tail_ = 0x01;
    maybe_full_ = false;
  }

  const std::uint32_t& head() const { return head_; }
  const std::uint32_t& tail() const { return tail_; }
  const bool& maybe_full() const { return maybe_full_; }
#if defined(CHISA_WIDE_MODEL)
  // Diagnostics materialize a value; publication reads the functional RAM word.
  MicroOp ram(std::size_t index) const {
    MicroOp result;
    unpack_into(ram_[index], result);
    return result;
  }
  std::uint64_t packed_ram(std::size_t index) const {
    return ram_[index].oracle_and_raw & kOracleMask;
  }
  // The record masks off the raw-instruction tail above the 51-bit oracle.
  const std::uint64_t& packed_ram_storage(std::size_t index) const {
    return ram_[index].oracle_and_raw;
  }
#else
  const MicroOp& ram(std::size_t index) const { return ram_[index]; }
#endif
  const std::uint64_t& ram_epoch_for_diagnostic() const {
    return ram_epoch_;
  }
  const std::uint64_t& ram_entry_epoch_for_diagnostic(
      std::size_t index) const {
    return ram_entry_epochs_[index];
  }

  bool enq_ready() const {
    // do_enq = !(at_head && maybe_full || might_hit_head): only the row-first
    // tail bits collide with the row-level head (fetch-buffer.scala:78-82).
    if (at_head_of(tail_) && maybe_full_) return false;
    for (unsigned distance = 1; distance < kFetchWidth; ++distance) {
      if (at_head_of(rotate_entries(tail_, distance))) return false;
    }
    return true;
  }

  bool deq_valid() const {
    bool valids[kDeqWidth];
    return any_deq_valids(valids);
  }

  SmallFetchBufferOutputs outputs(bool reset_asserted = false) const {
    SmallFetchBufferOutputs result;
    outputs_into(reset_asserted, result);
    return result;
  }

  void outputs_into(bool reset_asserted, SmallFetchBufferOutputs& result) const {
#if !defined(CHISA_WIDE_MODEL)
    result = SmallFetchBufferOutputs{};
#endif
    result.enq_ready = enq_ready();
    bool valids[kDeqWidth];
    result.deq_valid = any_deq_valids(valids);
    // Only the per-uop valid is reset-gated; the outer valid uses the pointers.
    const std::size_t row_base = row_index(head_) * kDeqWidth;
    result.uop_valid = valids[0] && !reset_asserted;
#if defined(CHISA_WIDE_MODEL)
    // Expand only the dequeue row. Each destination is initialized once,
    // rather than clearing a whole output bundle before overwriting it.
    for (std::size_t w = 0; w < kDeqWidth; ++w) {
      unpack_into(ram_[row_base + w], result.uops_g[w]);
      result.uop_valids_g[w] = valids[w] && !reset_asserted;
    }
    result.uop = result.uops_g[0];
    for (std::size_t w = kDeqWidth; w < boomcfg::MAX_CORE_WIDTH; ++w) {
      result.uops_g[w].clear();
      result.uop_valids_g[w] = false;
    }
#else
    result.uop = ram_[row_base];
    for (std::size_t w = 0; w < kDeqWidth; ++w) {
      result.uops_g[w] = ram_[row_base + w];
      result.uop_valids_g[w] = valids[w] && !reset_asserted;
    }
#endif
  }

#if defined(CHISA_WIDE_MODEL)
  /** The dequeue row unpacked into `uops` (slots below kDeqWidth; the rest
    * cleared) with the per-slot valids before the reset gate; returns
    * whether any slot is valid (FrontendHandoff). */
  bool dequeue_row_into(std::array<MicroOp, boomcfg::MAX_CORE_WIDTH>& uops,
                        std::uint8_t& valid_mask) const {
    bool valids[kDeqWidth];
    const bool any = any_deq_valids(valids);
    const std::size_t row_base = row_index(head_) * kDeqWidth;
    valid_mask = 0;
    for (std::size_t w = 0; w < kDeqWidth; ++w) {
      unpack_into(ram_[row_base + w], uops[w]);
      if (valids[w]) valid_mask |= static_cast<std::uint8_t>(1u << w);
    }
    for (std::size_t w = kDeqWidth; w < boomcfg::MAX_CORE_WIDTH; ++w) uops[w].clear();
    return any;
  }
#endif

  void step(const SmallFetchBufferInputs& input) {
    const bool do_enq = enq_ready();
    bool valids[kDeqWidth];
    any_deq_valids(valids);
    // RTL advances the row only when its tail collision mask is empty.
    // A partial row remains visible while decode remembers consumed lanes.
    const bool do_deq = input.deq_ready && valids[kDeqWidth - 1];

    std::uint32_t next_tail = tail_;
    bool any_input_uop = false;
    for (std::size_t slot = 0; slot < kFetchWidth; ++slot) {
      const bool selected =
          input.enq_valid && ((input.enq.mask >> slot) & 1u) != 0;
      const std::uint32_t write_index = next_tail;
      if (selected) {
        any_input_uop = true;
        next_tail = rotate_entries(next_tail, 1);
      }
      // The RAM is an unreset Reg(Vec(...)); its write is not suppressed by
      // module reset.  Pointer reset is applied below with RegInit priority.
      if (do_enq && selected) {
        const std::size_t index = entry_index(write_index);
        ram_[index] = convert(input.enq, slot);
        ++ram_entry_epochs_[index];
        ++ram_epoch_;
      }
    }

    // These are Chisel last-connect priorities: dequeue wins over enqueue for
    // maybe_full, clear wins over both, and synchronous RegInit reset wins over
    // the ordinary update logic.  RAM writes above still survive clear.
    if (do_enq) {
      tail_ = next_tail;
      if (any_input_uop) maybe_full_ = true;
    }
    if (do_deq) {
      head_ = rotate_rows(head_, 1);
      maybe_full_ = false;
    }
    if (input.clear) reset_state();
    if (input.reset) reset_state();
  }

  bool pointers_are_one_hot() const {
    return is_one_hot(head_) && is_one_hot(tail_);
  }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);
#if defined(CHISA_WIDE_MODEL)
  // 125 meaningful bits:
  // oracle_and_raw[50:0] = the exact selected Large fb_uop RAM bank;
  // oracle_and_raw[63:51] = raw instruction[12:0];
  // debug[39:0] = debug_pc, [58:40] = raw instruction[31:13],
  // debug[60:59] = debug_fsrc. Other MicroOp fields are always zero here.
  struct PackedEntry {
    std::uint64_t oracle_and_raw;
    std::uint64_t debug;
  };
  static constexpr std::uint64_t kOracleMask =
      (UINT64_C(1) << 51) - UINT64_C(1);
  static_assert(sizeof(PackedEntry) == 16, "compact fetch-entry size");
  static_assert(sizeof(PackedEntry) < sizeof(MicroOp), "fetch RAM must shrink");
  static_assert(boomcfg::NUM_FTQ == 32, "Large fetch oracle has a five-bit FTQ index");
#endif

  static std::uint32_t rotate(std::uint32_t value, unsigned amount, unsigned width) {
    const std::uint32_t mask = (width >= 32) ? 0xffffffffu : ((1u << width) - 1u);
    amount %= width;
    if (amount == 0) return value & mask;
    return ((value << amount) | (value >> (width - amount))) & mask;
  }
  static std::uint32_t rotate_entries(std::uint32_t v, unsigned k) {
    return rotate(v, k, static_cast<unsigned>(kEntries));
  }
  static std::uint32_t rotate_rows(std::uint32_t v, unsigned k) {
    return rotate(v, k, static_cast<unsigned>(kRows));
  }

  // head (row one-hot) hits the row of an entry-level one-hot's ROW-FIRST bit.
  bool at_head_of(std::uint32_t entries_oh) const {
    for (std::size_t i = 0; i < kEntries; i += kDeqWidth)
      if (((entries_oh >> i) & 1u) && ((head_ >> (i / kDeqWidth)) & 1u)) return true;
    return false;
  }

  // tail_collisions / MaskUpper (fetch-buffer.scala:154-160): per dequeue
  // slot, whether the head row's slot has reached the tail; valids are the
  // slots BELOW the first collision.
  bool any_deq_valids(bool (&valids)[kDeqWidth]) const {
    std::uint32_t slot_hits = 0;
    const std::size_t row = row_index(head_);
    for (std::size_t w = 0; w < kDeqWidth; ++w) {
      const std::size_t i = row * kDeqWidth + w;
      const bool collide = ((tail_ >> i) & 1u) &&
                           (!maybe_full_ || (i % kDeqWidth) != 0);
      if (collide) slot_hits |= (1u << w);
    }
    bool below_first_hit = true;
    bool any = false;
    for (std::size_t w = 0; w < kDeqWidth; ++w) {
      if ((slot_hits >> w) & 1u) below_first_hit = false;
      valids[w] = below_first_hit;
      any = any || valids[w];
    }
    return any;
  }

  static bool is_one_hot(std::uint32_t value) {
    return value != 0 && (value & (value - 1)) == 0;
  }

  static std::size_t entry_index(std::uint32_t value) {
    for (std::size_t index = 0; index < kEntries; ++index)
      if (((value >> index) & 1u) != 0) return index;
    return 0;
  }
  static std::size_t row_index(std::uint32_t value) {
    for (std::size_t index = 0; index < kRows; ++index)
      if (((value >> index) & 1u) != 0) return index;
    return 0;
  }

#if defined(CHISA_WIDE_MODEL)
  static PackedEntry convert(const SmallFetchBundle& bundle, std::size_t slot) {
    const std::uint64_t aligned_pc =
        boomcfg::fetch_bank_align(bundle.pc) & kPcMask;
    const std::uint64_t slot_pc =
        (aligned_pc + static_cast<std::uint64_t>(slot * 2)) & kPcMask;
    const std::size_t bank = slot / boomcfg::BANK_WIDTH;
    const bool bank_edge =
        bank == 0 ? bundle.edge_inst : bundle.edge_insts[bank];
    const bool edge = (slot % boomcfg::BANK_WIDTH) == 0 && bank_edge;
    const std::uint64_t bank_pc =
        aligned_pc + static_cast<std::uint64_t>(bank * boomcfg::BANK_BYTES);
    const std::uint64_t debug_pc =
        edge ? ((bank_pc - UINT64_C(2)) & kPcMask) : slot_pc;
    const std::uint64_t pc_lob = (edge ? bank_pc : slot_pc) & UINT64_C(0x3f);
    const std::uint32_t raw = bundle.insts[slot];
    const std::uint64_t oracle =
        (std::uint64_t(bundle.expanded_insts[slot]) << 19) |
        (std::uint64_t((raw & 3u) != 3u) << 18) |
        (std::uint64_t(((bundle.sfb_mask | bundle.shadowed_mask) >> slot) & 1u) << 17) |
        (std::uint64_t(bundle.ftq_idx & (boomcfg::NUM_FTQ - 1)) << 12) |
        (std::uint64_t(edge) << 11) | (pc_lob << 5) |
        (std::uint64_t(bundle.cfi_valid &&
            ((bundle.cfi_idx & static_cast<unsigned>(boomcfg::FETCH_WIDTH - 1)) == slot)) << 4) |
        (std::uint64_t(bundle.xcpt_pf_if) << 3) |
        (std::uint64_t(bundle.xcpt_ae_if) << 2) |
        (std::uint64_t((bundle.bp_debug_mask >> slot) & 1u) << 1) |
        std::uint64_t((bundle.bp_xcpt_mask >> slot) & 1u);
    return PackedEntry{
        oracle | (std::uint64_t(raw & 0x1fffu) << 51),
        debug_pc | (std::uint64_t(raw >> 13) << 40) |
            (std::uint64_t(bundle.debug_fsrc & 3u) << 59)};
  }

  static void unpack_into(const PackedEntry& entry, MicroOp& uop) {
    uop.clear();
    const std::uint64_t word = entry.oracle_and_raw;
    uop.inst = static_cast<std::uint32_t>(word >> 19);
    uop.debug_inst = static_cast<std::uint32_t>(word >> 51) |
        (static_cast<std::uint32_t>((entry.debug >> 40) & UINT64_C(0x7ffff)) << 13);
    uop.is_rvc = static_cast<std::uint8_t>((word >> 18) & 1u);
    uop.debug_pc = entry.debug & kPcMask;
    uop.pc_lob = static_cast<std::uint8_t>((word >> 5) & 0x3fu);
    uop.is_sfb = static_cast<std::uint8_t>((word >> 17) & 1u);
    uop.edge_inst = static_cast<std::uint8_t>((word >> 11) & 1u);
    uop.ftq_idx = static_cast<std::uint8_t>((word >> 12) & 0x1fu);
    uop.taken = static_cast<std::uint8_t>((word >> 4) & 1u);
    uop.xcpt_pf_if = static_cast<std::uint8_t>((word >> 3) & 1u);
    uop.xcpt_ae_if = static_cast<std::uint8_t>((word >> 2) & 1u);
    uop.bp_debug_if = static_cast<std::uint8_t>((word >> 1) & 1u);
    uop.bp_xcpt_if = static_cast<std::uint8_t>(word & 1u);
    uop.debug_fsrc = static_cast<std::uint8_t>((entry.debug >> 59) & 3u);
  }
#else
  static MicroOp convert(const SmallFetchBundle& bundle, std::size_t slot) {
    MicroOp uop;
    uop.clear();

    const std::uint64_t aligned_pc =
        boomcfg::fetch_bank_align(bundle.pc) & kPcMask;
    const std::uint64_t slot_pc =
        (aligned_pc + static_cast<std::uint64_t>(slot * 2)) & kPcMask;

    uop.inst = bundle.expanded_insts[slot];
    uop.debug_inst = bundle.insts[slot];
    uop.is_rvc = (bundle.insts[slot] & 3u) != 3u;
    uop.debug_pc = slot_pc;
    uop.pc_lob = static_cast<std::uint8_t>(slot_pc & 0x3fu);
    uop.is_sfb = static_cast<std::uint8_t>(
        (((bundle.sfb_mask | bundle.shadowed_mask) >> slot) & 1u) != 0);

    const std::size_t bank = slot / boomcfg::BANK_WIDTH;
    const bool bank_edge =
        bank == 0 ? bundle.edge_inst : bundle.edge_insts[bank];
    if ((slot % boomcfg::BANK_WIDTH) == 0 && bank_edge) {
      uop.debug_pc = (aligned_pc - UINT64_C(2)) & kPcMask;
      const std::uint64_t bank_pc =
          aligned_pc + static_cast<std::uint64_t>(bank * boomcfg::BANK_BYTES);
      uop.debug_pc = (bank_pc - UINT64_C(2)) & kPcMask;
      uop.pc_lob = static_cast<std::uint8_t>(bank_pc & 0x3fu);
      uop.edge_inst = 1;
    }

    uop.ftq_idx = static_cast<std::uint8_t>(bundle.ftq_idx & (boomcfg::NUM_FTQ - 1));
    uop.taken = static_cast<std::uint8_t>(
        bundle.cfi_valid &&
        ((bundle.cfi_idx & static_cast<unsigned>(boomcfg::FETCH_WIDTH - 1)) == slot));
    uop.xcpt_pf_if = static_cast<std::uint8_t>(bundle.xcpt_pf_if);
    uop.xcpt_ae_if = static_cast<std::uint8_t>(bundle.xcpt_ae_if);
    uop.bp_debug_if = static_cast<std::uint8_t>(
        ((bundle.bp_debug_mask >> slot) & 1u) != 0);
    uop.bp_xcpt_if = static_cast<std::uint8_t>(
        ((bundle.bp_xcpt_mask >> slot) & 1u) != 0);
    uop.debug_fsrc = static_cast<std::uint8_t>(bundle.debug_fsrc & 3u);
    return uop;
  }
#endif

#if defined(CHISA_WIDE_MODEL)
  std::array<PackedEntry, kEntries> ram_{};
#else
  std::array<MicroOp, kEntries> ram_{};
#endif
  std::array<std::uint64_t, kEntries> ram_entry_epochs_{};
  std::uint64_t ram_epoch_ = 0;
  std::uint32_t head_ = 0x01;
  std::uint32_t tail_ = 0x01;
  bool maybe_full_ = false;
};

}  // namespace chisa::boom_system::components
