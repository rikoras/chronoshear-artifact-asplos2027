#pragma once
#include "micro_op.h"

namespace chisa::boom_model {
// The current Small stage carrier, with its one geometry-dependent field typed.
template <class BranchMask>
struct BasicStageUop {
  uint64_t pc = 0;          // debug_pc (41 bits)
  uint32_t imm_packed = 0;
  uint16_t fu_code = 0;
  uint8_t rob = 0;
  BranchMask br_mask = 0;
  uint8_t br_tag = 0;
  uint8_t pdst = 0;
  uint8_t prs1 = 0, prs2 = 0;
  uint8_t dst_rtype = 0;
  uint8_t lrs1_rtype = 0, lrs2_rtype = 0;
  uint8_t uopc = 0;
  uint8_t csr_cmd = 0;
  uint8_t pc_lob = 0;
  uint8_t ftq_idx = 0;
  uint8_t ldq_idx = 0, stq_idx = 0;
  uint8_t mem_cmd = 0;
  // flag bits
  enum : uint16_t {
    kNull = 1u << 0,      // all-zero payload (NullMicroOp); live fields unreadable
    kIsAmo = 1u << 1,
    kUsesStq = 1u << 2,
    kUsesLdq = 1u << 3,
    kIsBr = 1u << 4,
    kIsJalr = 1u << 5,
    kIsJal = 1u << 6,
    kIsRvc = 1u << 7,
    kEdgeInst = 1u << 8,
    kIsLoad = 1u << 9,    // ctrl.is_load  (RegisterReadDecode)
    kIsSta = 1u << 10,    // ctrl.is_sta
    kIsStd = 1u << 11,    // ctrl.is_std
    kTaken = 1u << 12,
    kIsSfb = 1u << 13,
    kFpVal = 1u << 14,
    kBypassable = 1u << 15,
  };
  uint16_t flags = kNull;

  bool null() const { return (flags & kNull) != 0; }
  bool is_amo() const { return (flags & kIsAmo) != 0; }
  bool uses_stq() const { return (flags & kUsesStq) != 0; }
  bool uses_ldq() const { return (flags & kUsesLdq) != 0; }
  bool is_br() const { return (flags & kIsBr) != 0; }
  bool is_jalr() const { return (flags & kIsJalr) != 0; }
  bool is_jal() const { return (flags & kIsJal) != 0; }
  bool is_rvc() const { return (flags & kIsRvc) != 0; }
  bool edge_inst() const { return (flags & kEdgeInst) != 0; }
  bool is_load() const { return (flags & kIsLoad) != 0; }
  bool is_sta() const { return (flags & kIsSta) != 0; }
  bool is_std() const { return (flags & kIsStd) != 0; }
  bool taken() const { return (flags & kTaken) != 0; }
  bool is_sfb() const { return (flags & kIsSfb) != 0; }
  bool fp_val() const { return (flags & kFpVal) != 0; }
  bool bypassable() const { return (flags & kBypassable) != 0; }

  // MicroOp.clear(): every field zero.  Callers that model NullMicroOp set
  // dst_rtype = RT_X afterwards; a surviving br_mask may be reinstated.
  void clear() { *this = BasicStageUop{}; }

  static BasicStageUop from(const MicroOp& u) {
    BasicStageUop s;
    s.pc = u.debug_pc;
    s.imm_packed = u.imm_packed;
    s.fu_code = u.fu_code;
    s.rob = u.rob_idx;
    s.br_mask = u.br_mask;
    s.br_tag = u.br_tag;
    s.pdst = u.pdst;
    s.prs1 = u.prs1;
    s.prs2 = u.prs2;
    s.dst_rtype = u.dst_rtype;
    s.lrs1_rtype = u.lrs1_rtype;
    s.lrs2_rtype = u.lrs2_rtype;
    s.uopc = u.uopc;
    s.csr_cmd = u.ctrl.csr_cmd;
    s.pc_lob = u.pc_lob;
    s.ftq_idx = u.ftq_idx;
    s.ldq_idx = u.ldq_idx;
    s.stq_idx = u.stq_idx;
    s.mem_cmd = u.mem_cmd;
    uint16_t f = 0;
    if (u.is_amo) f |= kIsAmo;
    if (u.uses_stq) f |= kUsesStq;
    if (u.uses_ldq) f |= kUsesLdq;
    if (u.is_br) f |= kIsBr;
    if (u.is_jalr) f |= kIsJalr;
    if (u.is_jal) f |= kIsJal;
    if (u.is_rvc) f |= kIsRvc;
    if (u.edge_inst) f |= kEdgeInst;
    if (u.ctrl.is_load) f |= kIsLoad;
    if (u.ctrl.is_sta) f |= kIsSta;
    if (u.ctrl.is_std) f |= kIsStd;
    if (u.taken) f |= kTaken;
    if (u.is_sfb) f |= kIsSfb;
    if (u.fp_val) f |= kFpVal;
    if (u.bypassable) f |= kBypassable;
    s.flags = f;
    return s;
  }
};
using StageUop = BasicStageUop<boomcfg::br_mask_t>;
}  // namespace chisa::boom_model
