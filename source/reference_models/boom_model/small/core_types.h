#pragma once
// ==========================================================================
// model core: shared types.
//
// The model's registers live in the contract image (generated/image.h).
// Everything here is either a compact pipeline-register record (StageUop:
// the RTL rewrites only a few fields of a uop per stage, so a stage holds
// those fields plus the ROB index of the instruction and reads the rest from
// the per-instruction record), a queue entry as a bit column, or a packer for
// the RTL's bank words.
// ==========================================================================
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <utility>

#include "../common/boom_config.h"
#include "../common/core_types.h"
#include "../common/pipeline_uop.h"       // MicroOp, uop constants, boom_decode, GuiderCSR
#include "../common/boom_lsu_scheduler.h"
#include "../common/memory_data.h"
#include "../common/boom_uop_pack.h"
#include "../common/lsu_uop_word.h"
#include "generated/image.h"

static_assert(boomcfg::CORE_WIDTH == 1 && boomcfg::INT_ISSUE_WIDTH == 1,
              "model is the Small (1-wide) core");
static_assert(boomcfg::NUM_ROB_ROWS == 32 && boomcfg::NUM_LDQ == 8 &&
              boomcfg::NUM_STQ == 8 && boomcfg::NUM_INT_IQ_SLOTS == 8 &&
              boomcfg::NUM_MEM_IQ_SLOTS == 8 && boomcfg::MAX_BR_COUNT == 8,
              "image field packing below is written for the Small geometry");

namespace chisa::boom_model {

using br_mask_t = boomcfg::br_mask_t;   // uint8
using lsq_mask_t = boomcfg::lsq_mask_t;  // uint8
using preg_mask_t = boomcfg::preg_mask_t;

constexpr int kRob = boomcfg::NUM_ROB_ROWS;   // 32 rows, one bank
constexpr int kLdq = boomcfg::NUM_LDQ;
constexpr int kStq = boomcfg::NUM_STQ;
constexpr int kIq = 8;
constexpr int kBr = boomcfg::MAX_BR_COUNT;
constexpr int kPregs = boomcfg::NUM_PREGS;
constexpr uint64_t kPc40 = (UINT64_C(1) << 40) - 1;

inline constexpr uint8_t bit(bool b) { return b ? 1u : 0u; }
inline int ldq_wrap(int i) { return i & (kLdq - 1); }
inline int stq_wrap(int i) { return i & (kStq - 1); }
inline int rob_wrap(int i) { return i & (kRob - 1); }
struct IqMovement {
  std::uint8_t shifted_sources = 0, live_after = 0, available = 8;
  bool enqueue = false;
};
// Preserve IssueUnitCollapsing's maxShift=1: only entries above the first
// PRE vacancy move, even if this cycle's grant creates another vacancy.
inline IqMovement iq_movement(std::uint8_t live, std::uint8_t removed, bool dispatch) {
  const unsigned kept = live & ~unsigned(removed);
  const unsigned holes = ~unsigned(live) & 255u;
  const unsigned moving = holes ? kept & ~((1u << __builtin_ctz(holes)) - 1u) : 0;
  IqMovement result;
  result.shifted_sources = moving;
  result.enqueue = dispatch && holes;
  result.live_after = (kept & ~moving) | (moving >> 1u) | (result.enqueue ? 128u : 0u);
  result.available = 8u - static_cast<unsigned>(__builtin_popcount(unsigned(result.live_after)));
  return result;
}
inline std::uint8_t lsq_age_pick(std::uint8_t eligible, std::uint8_t head) {
  const unsigned start = head < 8 ? head : 0;
  const unsigned above = eligible & (255u << start);
  // Bit 7 preserves the original empty-mask fall-through and makes ctz total.
  return static_cast<std::uint8_t>(__builtin_ctz((above ? above : eligible) | 128u));
}
// Rotate an STQ candidate mask so the nearest predecessor of youngest is
// the highest bit. This preserves the LSQ's circular youngest-first scan.
inline std::uint8_t stq_age_order(std::uint8_t candidates, unsigned youngest) {
  youngest &= kStq - 1;
  return static_cast<std::uint8_t>((unsigned(candidates) >> youngest) |
                                 (unsigned(candidates) << (kStq - youngest)));
}
inline unsigned stq_age_pop(std::uint8_t& ordered, unsigned youngest) {
  const unsigned rank = 31u - static_cast<unsigned>(__builtin_clz(unsigned(ordered)));
  ordered &= static_cast<std::uint8_t>(~(1u << rank));
  return (rank + youngest) & (kStq - 1);
}
// IsOlder (util.scala): is index i0 older than i1, given the queue head.
inline bool lsq_is_older(int i0, int i1, int head) {
  return ((i0 < i1) ^ (i0 < head) ^ (i1 < head)) != 0;
}

// The RTL's NullMicroOp as it reaches the oracle: every field zero and
// dst_rtype = RT_X.  Stage records that hold "nothing" read through this.
struct NullInst {
  static const MicroOp& get() {
    static const MicroOp z = [] { MicroOp u; u.clear(); u.dst_rtype = RT_X; return u; }();
    return z;
  }
};

// --------------------------------------------------------------------------
// StageUop: a pipeline-register copy of a uop.  A stage register in the RTL
// is a full bundle, but only the fields listed here are either rewritten by
// some stage (br_mask, the split-store shape, csr_cmd, the RegisterReadDecode
// ctrl bits) or observed by the contract while the instruction may already
// be dead and its ROB row reused (dst_rtype, pdst, is_amo, uses_stq, fu_code,
// imm_packed, pc, pc_lob, ftq_idx, is_rvc, edge_inst, is_br).  Every other
// field is read from the live instruction record via `rob`.
// --------------------------------------------------------------------------


// A stage register: valid + payload.
struct Stage {
  bool v = false;
  StageUop u;
};

// Branch-resolution pipeline entry (issue+1..+4).
struct BrStage {
  bool v = false;
  uint8_t tag = 0;
  bool mispredict = false;
  bool taken = false;
  uint64_t target = 0;
  uint8_t ftq_idx = 0, rob_idx = 0, ldq_idx = 0, stq_idx = 0, pc_lob = 0;
  br_mask_t br_mask = 0;
  bool is_jalr = false;
  void clear() { *this = BrStage{}; }
};

// ALU BrResolutionInfo payload (registered through brinfos and b2).
struct BrPayload {
  uint8_t pc_sel = PC_PLUS4;
  uint8_t cfi_type = 0;
  bool taken = false;
  int32_t target_offset = 0;
  uint64_t jalr_target = 0;
};

// Pending functional-unit writeback.
struct Wb {
  uint8_t rob = 0;
  uint8_t pdst = 0;
  uint8_t left = 0;
  bool slow_wake = false;
  bool drives_port = false;
  bool is_div = false;
  bool is_mul = false;
  br_mask_t br_mask = 0;
  uint64_t data = 0;
};

// Deferred CSR-file write (armed at issue, fires at the registered response).
struct CsrWrite {
  bool v = false;
  uint8_t left = 0;
  uint8_t rob = 0;      // the CSR instruction (unique: its row stays live)
  uint8_t csr_cmd = 0;  // RegisterRead-transformed command
  uint64_t r1 = 0;
};

struct SpecWake {
  bool v = false;
  uint8_t pdst = 0;
  br_mask_t br_mask = 0;
  uint8_t ldq_idx = 0;
};
struct ClrBsy {
  bool v = false;
  uint8_t rob = 0;
  br_mask_t br_mask = 0;
};
struct FwdWb {
  bool v = false;
  uint8_t ldq_idx = 0;
  uint8_t stq_idx = 0;
};
// One registered exception record (LSU r_xcpt / ROB r_xcpt / mem_xcpt).
struct XcptRec {
  bool v = false;
  bool uses_ldq = false;
  uint8_t rob = 0;
  uint8_t ldq_idx = 0, stq_idx = 0;
  br_mask_t br_mask = 0;
  uint8_t cause = 0;
  uint64_t vaddr = 0;
  uint64_t exc_cause = 0;   // ROB-side 64-bit cause
};

// The four fields the commit-port RegNext observes of the ROB head/tail uop,
// captured at cycle start (the row may be re-dispatched this same edge).
struct CommitSnap {
  uint8_t pc_lob = 0, ftq_idx = 0;
  bool is_rvc = false, edge_inst = false;
};

// func-unit-decode.scala:348-349: CSRRS/CSRRC with a p0 source read only.
inline constexpr uint8_t csr_register_read_cmd(uint8_t cmd, uint8_t prs1) {
  return prs1 == 0 && (cmd == 6 || cmd == 7) ? 2 : cmd;
}

// --------------------------------------------------------------------------
// Contract bank words.
// --------------------------------------------------------------------------
// Issue slot: slot_uop__v2_bank_2_0 = uopc7 | br_mask8 | lrs1_rtype2 | lrs2_rtype2.
inline uint32_t pack_iq_slot(uint8_t uopc, uint8_t br_mask, uint8_t rt1, uint8_t rt2) {
  return ((uint32_t(uopc) & 0x7f) << 12) | (uint32_t(br_mask) << 4) |
         ((uint32_t(rt1) & 3) << 2) | (uint32_t(rt2) & 3);
}
inline uint16_t pack_fp_iq_slot(uint8_t uopc, uint8_t br_mask) {
  return static_cast<uint16_t>(((uint32_t(uopc) & 0x7f) << 8) | br_mask);
}

// STQ per-entry word (the fields of stq__v2_bank_0_* other than valid and
// the four status bits, in the RTL's field order, 40 bits):
//   br_mask8 rob5 ldq3 stq3 pdst6 exception1 mem_cmd5 mem_size2 mem_signed1
//   is_fence1 is_amo1 uses_ldq1 uses_stq1 dst_rtype2
using StqWord = LsuUopWord<8,5,3,6>;

// Physical register file shadow (52 pregs, indexed with the 6-bit field).
struct Prf {
  uint64_t regs[64];
  void clear() { std::memset(regs, 0, sizeof(regs)); }
  uint64_t rd(uint32_t p) const { return regs[p & 63]; }
  void wr(uint32_t p, uint64_t d) { regs[p & 63] = d; }
};

}  // namespace chisa::boom_model
