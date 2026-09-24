#pragma once
#include "../../boom_model/common/boom_config.h"
// ============================================================================
// Small BOOM F3 instruction assembly (nBanks=1, bankWidth=fetchWidth=4).
//
// This is the deterministic F3 combinational slice between the synchronized
// I-cache/BPD response queues and the F4 queue: halfword alignment, cross-fetch
// instruction stitching, RVC expansion, first-CFI truncation, and raw SFB
// detection.  Predictor, breakpoint, and redirect-source values remain
// explicit neighboring inputs; this component does not sample either
// implementation.
// ============================================================================

#include <array>
#include <cstdint>

#include "../../common/rvc_expand.h"
#include "small_f3_queues.h"
#include "small_fetch_buffer.h"

namespace chisa::boom_system::components {

struct SmallF3AssemblerInputs {
  bool reset = false;
  bool clear = false;
  bool deq_ready = false;
  bool main_valid = false;
  SmallFrontendResp main{};
  SmallBpdResponse bpd{};
  std::uint8_t bp_debug_mask = 0;
  std::uint8_t bp_xcpt_mask = 0;
  bool final_fsrc_valid = false;
  std::uint8_t final_fsrc = 0;
  std::uint64_t ras_read_addr = 0;
};

struct SmallF3AssemblerOutputs {
  bool enq_valid = false;
  SmallFetchBundle bundle{};
  bool trailing_half_valid = false;
  std::uint16_t trailing_half = 0;
  std::uint8_t btb_mispredicts = 0;
  std::uint8_t br_mask = 0;
  std::uint8_t cfi_type = 0;
  bool cfi_is_call = false;
  bool cfi_is_ret = false;
  bool cfi_npc_plus4 = false;
  std::uint64_t predicted_target = 0;
  SmallGlobalHistory predicted_ghist{};
  bool ras_write_valid = false;
  std::uint8_t ras_write_idx = 0;
  std::uint64_t ras_write_addr = 0;
};

class SmallF3Assembler {
 public:
  SmallF3AssemblerOutputs outputs(
      const SmallF3AssemblerInputs& input) const {

    SmallF3AssemblerOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallF3AssemblerInputs& input, SmallF3AssemblerOutputs& result) const {
    result = SmallF3AssemblerOutputs{};
    result.enq_valid = input.main_valid && !input.clear;
    result.bundle.pc = input.main.pc & kPcMask;
    result.bundle.edge_inst = prev_is_half_;
    result.bundle.edge_insts[0] = prev_is_half_;
    result.bundle.xcpt_pf_if = input.main.xcpt_pf_if;
    result.bundle.xcpt_ae_if = input.main.xcpt_ae_if;
    result.bundle.bp_debug_mask = input.bp_debug_mask & ((1u << boomcfg::FETCH_WIDTH) - 1u);
    result.bundle.bp_xcpt_mask = input.bp_xcpt_mask & ((1u << boomcfg::FETCH_WIDTH) - 1u);
    result.bundle.debug_fsrc =
        (input.final_fsrc_valid ? input.final_fsrc : input.main.fsrc) &
        0x03u;
    result.bundle.shadowed_mask = 0;  // enableSFBOpt=false
    result.bundle.ras_top = input.ras_read_addr & kPcMask;
    result.bundle.ghist = input.main.ghist;
    result.bundle.bpd_meta = input.bpd.meta;
    for (int b = 0; b < boomcfg::NBANKS; ++b) {
      result.bundle.bpd_meta[4 * b + 3] &= 0x00ffffffu;
    }
    result.bundle.ghist.ras_idx =
        static_cast<std::uint8_t>(result.bundle.ghist.ras_idx & 0x1fu);
    // Chisel's PriorityEncoder over the four redirect bits falls through to
    // the final Vec element when all inputs are false.  cfi_idx is then
    // semantically invalid, but the value 3 is still stored in the F4 RAM.
    result.bundle.cfi_idx = boomcfg::FETCH_WIDTH - 1;

    std::array<std::uint32_t, boomcfg::FETCH_WIDTH> raw{};
    std::array<bool, boomcfg::FETCH_WIDTH> slot_valid{};
    std::array<bool, boomcfg::FETCH_WIDTH> is_rvc{};
    std::array<std::uint8_t, boomcfg::FETCH_WIDTH> cfi_type{};
    std::array<bool, boomcfg::FETCH_WIDTH> is_call{};
    std::array<bool, boomcfg::FETCH_WIDTH> is_ret{};
    std::array<bool, boomcfg::FETCH_WIDTH> npc_plus4{};
    std::array<std::uint64_t, boomcfg::FETCH_WIDTH> targets{};
    bool redirect_found = false;
    const std::uint8_t f3_bank_mask =
        boomcfg::NBANKS == 1
            ? 1u
            : (boomcfg::fetch_may_not_be_dual_banked(input.main.pc) ? 1u
                                                                    : 3u);
    std::uint16_t bank_prev_half = prev_half_;
    bool bank_prev_is_half = prev_is_half_;
    for (int bank = 0; bank < boomcfg::NBANKS; ++bank) {
      const bool edge = bank_prev_is_half;
      result.bundle.edge_insts[bank] = edge;
      if (bank == 0) result.bundle.edge_inst = edge;
      const std::uint64_t bank_data = input.main.data_word(bank);
      const std::size_t bank_base =
          static_cast<std::size_t>(bank * boomcfg::BANK_WIDTH);

      for (int word = 0; word < boomcfg::BANK_WIDTH; ++word) {
        const std::size_t slot = bank_base + static_cast<std::size_t>(word);
        if (word == 0) {
          raw[slot] = edge
                          ? (static_cast<std::uint32_t>(bank_data & 0xffffu)
                             << 16) |
                                bank_prev_half
                          : static_cast<std::uint32_t>(
                                bank_data & UINT64_C(0xffffffff));
          slot_valid[slot] = true;
        } else if (word == boomcfg::BANK_WIDTH - 1) {
          raw[slot] = static_cast<std::uint32_t>(
              (bank_data >> (16 * word)) & UINT64_C(0xffff));
          const bool previous_consumes =
              bit(result.bundle.mask, slot - 1) && !is_rvc[slot - 1];
          slot_valid[slot] =
              !previous_consumes && ((raw[slot] & 0x03u) != 0x03u);
        } else {
          raw[slot] = static_cast<std::uint32_t>(
              bank_data >> (16 * word));
          const bool previous_consumes =
              bit(result.bundle.mask, slot - 1) && !is_rvc[slot - 1];
          slot_valid[slot] = !previous_consumes;
          if (word == 1) slot_valid[slot] = edge || slot_valid[slot];
        }

        is_rvc[slot] = (raw[slot] & 0x03u) != 0x03u;
        result.bundle.insts[slot] = raw[slot];
        result.bundle.expanded_insts[slot] = expand(raw[slot]);

        const bool selected =
            input.main_valid && bit(input.main.mask, slot) &&
            slot_valid[slot] && !redirect_found;
        if (selected)
          result.bundle.mask |= static_cast<std::uint8_t>(1u << slot);

        const std::uint32_t expanded = result.bundle.expanded_insts[slot];
        cfi_type[slot] = decode_cfi_type(expanded);
        is_call[slot] =
            (cfi_type[slot] == kCfiJal || cfi_type[slot] == kCfiJalr) &&
            ((expanded >> 7) & 0x1fu) == 1u;
        is_ret[slot] =
            cfi_type[slot] == kCfiJalr &&
            ((((expanded >> 15) & 0x1fu) == 1u) ||
             (((expanded >> 15) & 0x1fu) == 5u)) &&
            ((expanded >> 7) & 0x1fu) == 0u;
        npc_plus4[slot] = !is_rvc[slot] && !(word == 0 && edge);
        const std::uint64_t slot_pc =
            (boomcfg::fetch_bank_align(input.main.pc) +
             static_cast<std::uint64_t>(slot * 2u) -
             ((word == 0 && edge) ? UINT64_C(2) : UINT64_C(0))) &
            kPcMask;
        targets[slot] =
            cfi_type[slot] == kCfiJalr
                ? input.bpd.preds[slot].predicted_pc & kPcMask
                : direct_target(slot_pc, expanded, cfi_type[slot]);
        if (cfi_type[slot] == kCfiJal && slot_valid[slot] &&
            input.bpd.preds[slot].predicted_pc_valid &&
            (input.bpd.preds[slot].predicted_pc & kPcMask) != targets[slot])
          result.btb_mispredicts |=
              static_cast<std::uint8_t>(1u << slot);
        if (selected && cfi_type[slot] == kCfiBranch)
          result.br_mask |= static_cast<std::uint8_t>(1u << slot);
        const bool redirect =
            selected &&
            (cfi_type[slot] == kCfiJal || cfi_type[slot] == kCfiJalr ||
             (cfi_type[slot] == kCfiBranch &&
              input.bpd.preds[slot].taken));
        if (redirect && !result.bundle.cfi_valid) {
          result.bundle.cfi_valid = true;
          result.bundle.cfi_idx = static_cast<std::uint8_t>(slot);
        }
        if (selected &&
            is_short_forward_branch(expanded, slot, input.main.pc,
                                    word == 0 && edge))
          result.bundle.sfb_mask |= static_cast<std::uint8_t>(1u << slot);
        redirect_found = redirect_found || redirect;
      }

      if (((f3_bank_mask >> bank) & 1u) == 0) continue;
      const std::size_t last_slot = bank_base + boomcfg::BANK_WIDTH - 1;
      const std::uint16_t last_half = static_cast<std::uint16_t>(
          (bank_data >> 48) & 0xffffu);
      bank_prev_half = last_half;
      bank_prev_is_half =
          !(bit(result.bundle.mask, last_slot - 1) &&
            !is_rvc[last_slot - 1]) &&
          ((last_half & 0x03u) == 0x03u);
    }
    result.trailing_half = bank_prev_half;
    result.trailing_half_valid = bank_prev_is_half;

    const std::size_t cfi_index =
        result.bundle.cfi_idx & (boomcfg::FETCH_WIDTH - 1);
    result.cfi_type = cfi_type[cfi_index];
    result.cfi_is_call = is_call[cfi_index];
    result.cfi_is_ret = is_ret[cfi_index];
    result.cfi_npc_plus4 = npc_plus4[cfi_index];
    result.bundle.cfi_type = result.cfi_type;
    result.bundle.cfi_is_call = result.cfi_is_call;
    result.bundle.cfi_is_ret = result.cfi_is_ret;
    result.bundle.cfi_npc_plus4 = result.cfi_npc_plus4;
    result.bundle.br_mask = result.br_mask;
    result.predicted_target =
        result.bundle.cfi_valid
            ? (result.cfi_is_ret
                   ? input.ras_read_addr & kPcMask
                   : targets[cfi_index])
            : next_fetch(input.main.pc);
    result.predicted_ghist = update_history(
        input.main.ghist, result.br_mask, result.bundle.cfi_valid,
        result.cfi_type == kCfiBranch, result.bundle.cfi_idx,
        result.bundle.cfi_valid, result.cfi_is_call, result.cfi_is_ret,
        input.main.pc);
    result.ras_write_valid =
        result.bundle.cfi_valid && result.cfi_is_call;
    result.ras_write_idx = static_cast<std::uint8_t>(
        (input.main.ghist.ras_idx + 1u) & 0x1fu);
    result.ras_write_addr =
        (boomcfg::fetch_bank_align(input.main.pc) +
         static_cast<std::uint64_t>(cfi_index * 2u) +
         (result.cfi_npc_plus4 ? UINT64_C(4) : UINT64_C(2))) &
        kPcMask;
    return;
  }

  void commit(const SmallF3AssemblerInputs& input,
              const SmallF3AssemblerOutputs& output) {
    const bool fire = input.main_valid && input.deq_ready;
    if (fire) {
      prev_is_half_ = output.trailing_half_valid;
      prev_half_ = output.trailing_half;
    }
    if (input.reset || input.clear) prev_is_half_ = false;
    if (fire && output.bundle.cfi_valid) prev_is_half_ = false;
  }

  void step(const SmallF3AssemblerInputs& input) {
    commit(input, outputs(input));
  }

  bool previous_is_half() const { return prev_is_half_; }
  std::uint16_t previous_half() const { return prev_half_; }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);
  static constexpr std::uint8_t kCfiNone = 0;
  static constexpr std::uint8_t kCfiBranch = 1;
  static constexpr std::uint8_t kCfiJal = 2;
  static constexpr std::uint8_t kCfiJalr = 3;

  static bool bit(std::uint8_t value, std::size_t index) {
    return ((value >> index) & 1u) != 0;
  }

  static std::uint32_t expand(std::uint32_t raw) {
    if ((raw & 0x03u) == 0x03u) return raw;
    bool is_rvc = false;
    return rvc_expand(static_cast<std::uint16_t>(raw), &is_rvc);
  }

  static std::uint8_t decode_cfi_type(std::uint32_t instruction) {
    const std::uint8_t opcode = instruction & 0x7fu;
    const std::uint8_t funct3 =
        static_cast<std::uint8_t>((instruction >> 12) & 0x07u);
    if (opcode == 0x67u && funct3 == 0) return kCfiJalr;
    if (opcode == 0x6fu) return kCfiJal;
    if (opcode == 0x63u &&
        (funct3 <= 1u || (funct3 >= 4u && funct3 <= 7u)))
      return kCfiBranch;
    return kCfiNone;
  }

  static std::int64_t sign_extend(std::uint64_t value, unsigned bits) {
    const unsigned shift = 64u - bits;
    return static_cast<std::int64_t>(value << shift) >> shift;
  }

  static std::uint64_t direct_target(std::uint64_t pc,
                                     std::uint32_t instruction,
                                     std::uint8_t cfi_type) {
    std::uint64_t immediate = 0;
    unsigned bits = 1;
    if (cfi_type == kCfiBranch) {
      immediate =
          (((instruction >> 31) & 0x1u) << 12) |
          (((instruction >> 7) & 0x1u) << 11) |
          (((instruction >> 25) & 0x3fu) << 5) |
          (((instruction >> 8) & 0x0fu) << 1);
      bits = 13;
    } else if (cfi_type == kCfiJal) {
      immediate =
          (((instruction >> 31) & 0x1u) << 20) |
          (((instruction >> 12) & 0xffu) << 12) |
          (((instruction >> 20) & 0x1u) << 11) |
          (((instruction >> 21) & 0x3ffu) << 1);
      bits = 21;
    }
    return (pc + static_cast<std::uint64_t>(sign_extend(immediate, bits))) &
           kPcMask;
  }

  static std::uint64_t next_fetch(std::uint64_t pc) {
    return boomcfg::fetch_next(pc) & kPcMask;
  }

  static SmallGlobalHistory update_history(
      const SmallGlobalHistory& history, std::uint8_t branches,
      bool cfi_taken, bool cfi_is_br, std::uint8_t cfi_idx,
      bool cfi_valid, bool cfi_is_call, bool cfi_is_ret,
      std::uint64_t pc = 0) {
    const unsigned cfi_fixed = cfi_idx & (boomcfg::FETCH_WIDTH - 1);
    const std::uint8_t cfi_oh = static_cast<std::uint8_t>(1u << cfi_fixed);
    const std::uint8_t mask_lower =
        static_cast<std::uint8_t>((cfi_oh << 1) - 1u);
    const std::uint8_t selected = static_cast<std::uint8_t>(
        cfi_valid ? mask_lower : ((1u << boomcfg::FETCH_WIDTH) - 1u));
    const std::uint8_t taken_cfi =
        cfi_is_br && cfi_taken ? cfi_oh : 0u;
    const std::uint8_t not_taken =
        branches & selected & static_cast<std::uint8_t>(~taken_cfi);

    SmallGlobalHistory result;
    advance_global_history(history, not_taken, cfi_is_br, cfi_taken,
                           cfi_valid, cfi_fixed, pc, result);
    if (cfi_valid && cfi_is_call)
      result.ras_idx =
          static_cast<std::uint8_t>((history.ras_idx + 1u) & 0x1fu);
    else if (cfi_valid && cfi_is_ret)
      result.ras_idx =
          static_cast<std::uint8_t>((history.ras_idx - 1u) & 0x1fu);
    else
      result.ras_idx = history.ras_idx;
    return result;
  }

  bool is_short_forward_branch(std::uint32_t instruction,
                               std::size_t slot,
                               std::uint64_t fetch_pc,
                               bool edge) const {
    if (decode_cfi_type(instruction) != kCfiBranch ||
        ((instruction >> 31) & 1u) != 0)
      return false;
    const std::uint32_t branch_offset =
        (((instruction >> 7) & 0x1u) << 11) |
        (((instruction >> 25) & 0x3fu) << 5) |
        (((instruction >> 8) & 0x0fu) << 1);
    if (branch_offset == 0 ||
        branch_offset >= static_cast<std::uint32_t>(
                             boomcfg::ICACHE_BLOCK_BYTES))
      return false;
    const std::uint32_t packet_offset =
        static_cast<std::uint32_t>(slot * 2u) + branch_offset -
        (edge ? 2u : 0u);
    // frontend.scala bounds offset_from_aligned_pc by 2*fetchBytes normally,
    // but by fetchBytes+bankBytes for the final bank of an I-cache block.
    // Both are 16 B on single-bank Small; Large's ordinary two-bank window is
    // 32 B, so keeping the Small literal drops valid SFBs in the upper bank.
    const std::uint32_t packet_limit = static_cast<std::uint32_t>(
        boomcfg::fetch_may_not_be_dual_banked(fetch_pc)
            ? boomcfg::FETCH_BYTES + boomcfg::BANK_BYTES
            : 2 * boomcfg::FETCH_BYTES);
    return packet_offset <= packet_limit;
  }

  std::uint16_t prev_half_ = 0;  // unreset RTL register
  bool prev_is_half_ = false;

 public:
  const std::uint16_t& prev_half() const { return prev_half_; }
  const bool& prev_is_half() const { return prev_is_half_; }

 private:
};

}  // namespace chisa::boom_system::components
