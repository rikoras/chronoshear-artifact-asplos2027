#pragma once
// The 64-bit packed form of a ROB micro-op used by the oracle export (the
// RTL's rob_uop bank word).  Every field packed here is fixed at enqueue:
// br_mask, the only ROB uop field rewritten later, is not part of it, so
// the core caches the packed word next to the entry when it enqueues.
#include <cstdint>

#include "boom_config.h"

template <class U>
inline uint64_t pack_rob_uop(const U& u) {
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC) || defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    // Large widens ftq_idx by one bit and pdst/stale_pdst by one bit each.
    // The low control tail is unchanged; all fields above it move by three.
    return ((uint64_t(u.uopc) & 0x7f) << 41) |
           ((uint64_t(u.is_rvc) & 1) << 40) |
           ((uint64_t(u.ftq_idx) & 0x1f) << 35) |
           ((uint64_t(u.edge_inst) & 1) << 34) |
           ((uint64_t(u.pc_lob) & 0x3f) << 28) |
           ((uint64_t(u.pdst) & 0x7f) << 21) |
           ((uint64_t(u.stale_pdst) & 0x7f) << 14) |
           ((uint64_t(u.is_fencei) & 1) << 13) |
           ((uint64_t(u.uses_ldq) & 1) << 12) |
           ((uint64_t(u.uses_stq) & 1) << 11) |
           ((uint64_t(u.is_sys_pc2epc) & 1) << 10) |
           ((uint64_t(u.flush_on_commit) & 1) << 9) |
           ((uint64_t(u.ldst) & 0x3f) << 3) |
           ((uint64_t(u.ldst_val) & 1) << 2) |
           (uint64_t(u.dst_rtype) & 3);
#else
  return ((uint64_t(u.uopc) & 0x7f) << 38) | ((uint64_t(u.is_rvc) & 1) << 37) |
         ((uint64_t(u.ftq_idx) & 0xf) << 33) |
         ((uint64_t(u.edge_inst) & 1) << 32) |
         ((uint64_t(u.pc_lob) & 0x3f) << 26) |
         ((uint64_t(u.pdst) & 0x3f) << 20) |
         ((uint64_t(u.stale_pdst) & 0x3f) << 14) |
         ((uint64_t(u.is_fencei) & 1) << 13) |
         ((uint64_t(u.uses_ldq) & 1) << 12) |
         ((uint64_t(u.uses_stq) & 1) << 11) |
         ((uint64_t(u.is_sys_pc2epc) & 1) << 10) |
         ((uint64_t(u.flush_on_commit) & 1) << 9) |
         ((uint64_t(u.ldst) & 0x3f) << 3) | ((uint64_t(u.ldst_val) & 1) << 2) |
         (uint64_t(u.dst_rtype) & 3);
#endif
}
