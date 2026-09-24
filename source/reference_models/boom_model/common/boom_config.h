#pragma once
// Compile-time hardware geometry. Medium/Large use the shared wide pipeline;
// Small retains its existing implementation and types.
#include <cstdint>
#include <type_traits>
#include "boom_geometry.h"

#if (defined(BOOM_GUIDER_CFG_SMALLBOOM_RC) + defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC) + defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)) > 1
#error "select exactly one BOOM configuration"
#endif

namespace boomcfg {

#if defined(BOOM_GUIDER_FP)
static constexpr bool HAS_FP = true;
#else
static constexpr bool HAS_FP = false;
#endif

#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
static constexpr int NUM_FPREGS   = 96;   // numFpPhysRegisters (LargeBoom)
static constexpr int NUM_FP_IQ_SLOTS = 24; // FP IssueParams numEntries=24
#elif defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
static constexpr int NUM_FPREGS = 64;
static constexpr int NUM_FP_IQ_SLOTS = 16;
#else
static constexpr int NUM_FPREGS   = 48;   // numFpPhysRegisters (upstream SmallBoom)
static constexpr int NUM_FP_IQ_SLOTS = 8; // FP IssueParams numEntries=8
#endif

#if defined(BOOM_GUIDER_CFG_SMALLBOOM_RC)
static constexpr int CORE_WIDTH   = 1;    // decodeWidth
static constexpr int NUM_ROB_ROWS = 32;   // numRobEntries=32 (rob_idx : UInt<5>)
static constexpr int NUM_PREGS    = 52;   // numIntPhysRegisters=52 (pdst : UInt<6>)
static constexpr int NUM_LDQ      = 8;    // ldq_idx : UInt<3>
static constexpr int NUM_STQ      = 8;    // stq_idx : UInt<3>
static constexpr int NUM_INT_IQ_SLOTS = 8; // int IssueParams numEntries=8
static constexpr int NUM_MEM_IQ_SLOTS = 8; // mem IssueParams numEntries=8
static constexpr int MAX_BR_COUNT = 8;    // br_mask : UInt<8>, br_tag : UInt<3>
static constexpr int NUM_FTQ      = 16;   // ftq_idx : UInt<4> (external frontend)
static constexpr int INT_ISSUE_WIDTH = 1;
static constexpr int FETCH_WIDTH  = 4;
static constexpr int MAX_IQ_SLOTS = 8;
#elif defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
static constexpr int CORE_WIDTH = 2;
static constexpr int NUM_ROB_ROWS = 32;
static constexpr int NUM_PREGS = 80;
static constexpr int NUM_LDQ = 16;
static constexpr int NUM_STQ = 16;
static constexpr int NUM_INT_IQ_SLOTS = 20;
static constexpr int NUM_MEM_IQ_SLOTS = 12;
static constexpr int MAX_BR_COUNT = 12;
static constexpr int NUM_FTQ = 32;
static constexpr int INT_ISSUE_WIDTH = 2;
static constexpr int FETCH_WIDTH = 4;
static constexpr int MAX_IQ_SLOTS = 24;
#elif defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
static constexpr int CORE_WIDTH   = 3;    // decodeWidth
static constexpr int NUM_ROB_ROWS = 32;   // numRobEntries=96 / coreWidth=3 (rob.scala:124)
static constexpr int NUM_PREGS    = 100;  // numIntPhysRegisters=100 (pdst : UInt<7>)
static constexpr int NUM_LDQ      = 24;   // NON-power-of-2: wraps must be modular
static constexpr int NUM_STQ      = 24;
static constexpr int NUM_INT_IQ_SLOTS = 32; // int IssueParams numEntries=32, issueWidth=3
static constexpr int NUM_MEM_IQ_SLOTS = 16; // mem IssueParams numEntries=16, issueWidth=1
static constexpr int MAX_BR_COUNT = 16;   // br_mask : UInt<16>, br_tag : UInt<4>
static constexpr int NUM_FTQ      = 32;   // ftq_idx : UInt<5>
static constexpr int INT_ISSUE_WIDTH = 3;
static constexpr int FETCH_WIDTH  = 8;
static constexpr int MAX_IQ_SLOTS = 32;
#else
static constexpr int CORE_WIDTH   = 1;    // decode/dispatch/commit width (fetchpacket uops[1])
static constexpr int NUM_ROB_ROWS = 16;   // numRobEntries=16 (rob_idx : UInt<4>)
static constexpr int NUM_PREGS    = 40;   // numIntPhysRegisters=40 (pdst/prs* : UInt<6>, log2Ceil(40)=6)
static constexpr int NUM_LDQ      = 4;    // ldq_idx : UInt<2>
static constexpr int NUM_STQ      = 4;    // stq_idx : UInt<2>
static constexpr int NUM_INT_IQ_SLOTS = 4; // int_issue_unit slots_0..3
static constexpr int NUM_MEM_IQ_SLOTS = 4; // mem_issue_unit slots_0..3
static constexpr int MAX_BR_COUNT = 4;    // br_mask : UInt<4>, br_tag : UInt<2>
static constexpr int NUM_FTQ      = 8;    // ftq_idx : UInt<3> (external frontend)
static constexpr int INT_ISSUE_WIDTH = 1;
static constexpr int FETCH_WIDTH  = 4;
static constexpr int MAX_IQ_SLOTS = 8;
#endif

static constexpr int index_width_for_entries(int entries) {
    return geometry::index_width(entries);
}
using LdqGeometry = geometry::Ring<NUM_LDQ>;
using StqGeometry = geometry::Ring<NUM_STQ>;
using RobGeometry = geometry::BankedRob<NUM_ROB_ROWS, CORE_WIDTH>;
static constexpr int LDQ_IDX_WIDTH = LdqGeometry::index_bits;
static constexpr int STQ_IDX_WIDTH = StqGeometry::index_bits;
static constexpr unsigned LDQ_IDX_MASK = LdqGeometry::index_mask;
static constexpr unsigned STQ_IDX_MASK = StqGeometry::index_mask;

static constexpr int MEM_ISSUE_WIDTH = 1;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
static constexpr int NUM_HPM = 6;
#else
static constexpr int NUM_HPM = 2;
#endif
// execution-units.scala assigns each capability modulo integer issue width.
static constexpr unsigned JMP_PORT = 0;
static constexpr unsigned CSR_PORT = 1 % INT_ISSUE_WIDTH;
static constexpr unsigned MUL_PORT = 2 % INT_ISSUE_WIDTH;
static constexpr unsigned DIV_PORT = 3 % INT_ISSUE_WIDTH;
static constexpr unsigned I2F_PORT = 4 % INT_ISSUE_WIDTH;
static constexpr unsigned alu_latency(unsigned port) { return port == MUL_PORT ? 3 : 1; }
static constexpr int NUM_LREGS    = 32;   // architectural integer registers
static constexpr int IRF_READ_PORTS  = (MEM_ISSUE_WIDTH + INT_ISSUE_WIDTH) * 2;
static constexpr int IRF_WRITE_PORTS = MEM_ISSUE_WIDTH + INT_ISSUE_WIDTH;
static constexpr int MAX_CORE_WIDTH = 3;
// Fetch buffer geometry (fetch-buffer.scala): numEntries scales with the
// configuration; the dequeue width is the core width.
static constexpr int NUM_FB_ENTRIES = (CORE_WIDTH == 3) ? 24 : (CORE_WIDTH == 2) ? 16 : 8;
static constexpr int FB_DEQ_WIDTH   = CORE_WIDTH;
// Fetch group byte span (fetchWidth halfwords; banking folded in later).
static constexpr int FETCH_BYTES = FETCH_WIDTH * 2;
// D-cache geometry (sets are 64 in both locked configurations).
static constexpr int DCACHE_WAYS  = (CORE_WIDTH == 3) ? 8 : 4;
static constexpr int DCACHE_MSHRS = (CORE_WIDTH == 3) ? 4 : 2;
// I-cache ways and dTLB sectored entries (iTLB stays 8 sectors in both).
static constexpr int ICACHE_WAYS  = (CORE_WIDTH == 3) ? 8 : 4;
static constexpr int DTLB_SECTORS = (CORE_WIDTH == 3) ? 4 : 2;
// Frontend predictor banks (frontend.scala nBanks; bank width stays 4).
static constexpr int NBANKS = (CORE_WIDTH == 3) ? 2 : 1;
static constexpr int BANK_BYTES = FETCH_BYTES / NBANKS;
static constexpr int BANK_WIDTH = FETCH_WIDTH / NBANKS;
static constexpr int ICACHE_BLOCK_BYTES = 64;

// HasBoomFrontendParameters address geometry.  Keeping these operations in
// one configuration-owned place prevents the Small identity
// (bankBytes == fetchBytes) from leaking back into the two-bank model.
static inline constexpr std::uint64_t fetch_bank_align(std::uint64_t address) {
    return address & ~static_cast<std::uint64_t>(BANK_BYTES - 1);
}
static inline constexpr bool fetch_bank_one(std::uint64_t address) {
    return NBANKS == 2 && (address & static_cast<std::uint64_t>(BANK_BYTES)) != 0;
}
static inline constexpr bool fetch_may_not_be_dual_banked(
    std::uint64_t address) {
    if constexpr (NBANKS == 1) return false;
    return (fetch_bank_align(address) &
            static_cast<std::uint64_t>(ICACHE_BLOCK_BYTES - 1)) ==
           static_cast<std::uint64_t>(ICACHE_BLOCK_BYTES - BANK_BYTES);
}
static inline constexpr std::uint64_t fetch_next_bank(std::uint64_t address) {
    return fetch_bank_align(address) + static_cast<std::uint64_t>(BANK_BYTES);
}
static inline constexpr std::uint64_t fetch_next(std::uint64_t address) {
    if constexpr (NBANKS == 1)
        return fetch_next_bank(address);
    return fetch_bank_align(address) +
           static_cast<std::uint64_t>(fetch_may_not_be_dual_banked(address)
                                          ? BANK_BYTES
                                          : FETCH_BYTES);
}
static inline constexpr std::uint8_t fetch_mask(std::uint64_t address) {
    constexpr unsigned all = (1u << FETCH_WIDTH) - 1u;
    if constexpr (NBANKS == 1) {
        const unsigned shift =
            static_cast<unsigned>((address >> 1u) & (FETCH_WIDTH - 1));
        return static_cast<std::uint8_t>((all << shift) & all);
    } else {
        const unsigned shift =
            static_cast<unsigned>((address >> 1u) & (BANK_WIDTH - 1));
        constexpr unsigned one_bank = (1u << BANK_WIDTH) - 1u;
        const unsigned end_mask =
            fetch_may_not_be_dual_banked(address) ? one_bank : all;
        return static_cast<std::uint8_t>((all << shift) & end_mask);
    }
}
// Composed branch-predictor metadata: one 4-word (120-bit meaningful) slice
// per bank, banks concatenated (composer order within a slice unchanged).
static constexpr int BPD_META_WORDS = 4 * NBANKS;
// frontend.scala fetchIdx: predictor rows index by the fetch-group address
// (addr >> log2(fetchBytes); 3 on Small, 4 on Large).
static constexpr int FETCH_IDX_SHIFT = (FETCH_BYTES == 16) ? 4 : 3;
// Tile TileLink beat: 8 bytes on Small, 16 on Large (128-bit D data).
static constexpr int TILE_BEAT_BYTES = (CORE_WIDTH == 3) ? 16 : 8;
static constexpr int TILE_BEAT_SHIFT = (TILE_BEAT_BYTES == 16) ? 4 : 3;
static constexpr int ICACHE_REFILL_BEATS = 64 / TILE_BEAT_BYTES;
static constexpr int ICACHE_BEAT_WORDS = TILE_BEAT_BYTES / 8;
static constexpr int DCACHE_LINE_BYTES = 64;
static constexpr int DCACHE_LINE_WORDS = DCACHE_LINE_BYTES / 8;
static constexpr int DCACHE_REFILL_BEATS =
    DCACHE_LINE_BYTES / TILE_BEAT_BYTES;
static constexpr int DCACHE_BEAT_WORDS = TILE_BEAT_BYTES / 8;
// Local backing-memory response startup: the Large bus path (wider beats,
// deeper crossbars) adds cycles the Small calibration did not carry.
static constexpr int LOCAL_RESPONSE_STARTUP = 0;  // recalibrate with seam evidence; 3 showed no effect at 2k
// Tile TileLink source map, measured against the generated Large SystemBus
// (map(9)=1 matches the RTL's cbus-side origin): the I-cache client id is
// 9 on Large (after the eight D-cache MSHRs and their sibling), 4 on Small;
// D-cache A sources span 0..7 on Large, 0..3 on Small.
static constexpr int ICACHE_TL_SOURCE = (CORE_WIDTH == 3) ? 8 : 4;
static constexpr int DCACHE_SOURCE_MASK = (CORE_WIDTH == 3) ? 0x7 : 0x3;
static constexpr int TILE_SOURCE_MASK = (CORE_WIDTH == 3) ? 0xF : 0x7;

// ---- Width-generic helpers (from guiders/boom-mw; identical semantics for
// the 1-wide configurations) ----
static constexpr int NUM_ROB_BANKS  = CORE_WIDTH;
static constexpr int NUM_ROB_ENTRIES = RobGeometry::entry_count;
static constexpr int ROB_BANK_SHIFT = RobGeometry::bank_bits;
// Legacy arrays are indexed by the RTL wire code, including unused banks.
// NUM_ROB_ENTRIES is the real capacity; ROB_FLAT must keep its existing ABI.
static constexpr int ROB_FLAT = RobGeometry::wire_count;
static inline constexpr int rob_row(int idx) { return RobGeometry::row(idx); }
static inline constexpr int rob_bank(int idx) { return RobGeometry::bank(idx); }
static inline constexpr int rob_mk(int row, int bank) { return RobGeometry::encode(row, bank); }
static inline constexpr bool rob_flat_ok(int idx) { return RobGeometry::valid(idx); }

// Physical-register bitmap: uint64_t while every configuration in the build
// fits (Small: 52 pregs), 128-bit for Large (100). The Small producer keeps
// its exact current types and code paths.
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC) || defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
using preg_mask_t = unsigned __int128;
#else
using preg_mask_t = std::uint64_t;
#endif
static constexpr preg_mask_t PM_ONE = 1;
static inline preg_mask_t pm_bit(int p) { return PM_ONE << p; }
static inline preg_mask_t pm_all(int n) {
    return (n >= (int)(sizeof(preg_mask_t) * 8)) ? ~(preg_mask_t)0 : (PM_ONE << n) - 1;
}
static inline int pm_popcount(preg_mask_t m) {
    if constexpr (sizeof(preg_mask_t) == 8) return __builtin_popcountll((unsigned long long)m);
    else return __builtin_popcountll((unsigned long long)m) +
                __builtin_popcountll((unsigned long long)((unsigned __int128)m >> 64));
}
static inline int pm_ctz(preg_mask_t m) {   // undefined for m==0 (callers guard)
    unsigned long long lo = (unsigned long long)m;
    if (lo || sizeof(preg_mask_t) == 8) return __builtin_ctzll(lo);
    return 64 + __builtin_ctzll((unsigned long long)((unsigned __int128)m >> 64));
}
using br_mask_t  = std::conditional_t<(MAX_BR_COUNT <= 8),  std::uint8_t,  std::uint16_t>;
using iq_mask_t  = std::conditional_t<(MAX_IQ_SLOTS  <= 8), std::uint8_t,  std::uint32_t>;
using lsq_mask_t = std::conditional_t<(NUM_LDQ <= 8 && NUM_STQ <= 8), std::uint8_t, std::uint32_t>;

static inline constexpr int ldq_wrap(int i) { return LdqGeometry::wrap(i); }
static inline constexpr int stq_wrap(int i) { return StqGeometry::wrap(i); }

static_assert(CORE_WIDTH >= 1 && CORE_WIDTH <= MAX_CORE_WIDTH,
    "group arrays are sized by MAX_CORE_WIDTH");
static_assert(NUM_INT_IQ_SLOTS <= MAX_IQ_SLOTS && NUM_MEM_IQ_SLOTS <= MAX_IQ_SLOTS,
    "IssueQueue::slot[] / collapse scratch arrays cap at MAX_IQ_SLOTS");
static_assert(NUM_PREGS <= (int)(sizeof(preg_mask_t) * 8),
    "free_list / busy_table / br_alloc_lists bitmaps must cover NUM_PREGS");
static_assert((NUM_ROB_ROWS & (NUM_ROB_ROWS - 1)) == 0,
    "rob ROW pointer wrap uses & (NUM_ROB_ROWS-1) (rows are pow2 in all configs)");
static_assert((NUM_FTQ & (NUM_FTQ - 1)) == 0,
    "harness ftq_pc[] indexing masks with NUM_FTQ-1");
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC) && !defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
static_assert(CORE_WIDTH == 1,
    "model control flow is structurally 1-wide (see out/phaseB/GUIDER_PARADIGM.md #6)");
static_assert(NUM_INT_IQ_SLOTS <= 8 && NUM_MEM_IQ_SLOTS <= 8,
    "int_iq_start_valid / mem_iq_start_valid are uint8_t bitmaps");
static_assert(MAX_BR_COUNT <= 8,
    "br_mask / branch_mask / br_alloc bookkeeping are uint8_t");
static_assert(NUM_LDQ <= 8 && NUM_STQ <= 8,
    "st_dep_mask / live_store_mask / ldq_block_* are uint8_t bitmaps");
static_assert(NUM_PREGS <= 64,
    "free_list / busy_table / br_alloc_lists are uint64_t bitmaps; BoomPRF::regs[64]");
static_assert((NUM_LDQ & (NUM_LDQ - 1)) == 0 && (NUM_STQ & (NUM_STQ - 1)) == 0,
    "ldq/stq pointer wrap uses & (N-1); non-power-of-2 (e.g. Large's 24) needs modular wrap");
#endif

} // namespace boomcfg
#if defined(BOOM_GUIDER_CFG_SMALLBOOM_RC)
#define BOOMCFG_ROB_FOREACH(M)      M(0) M(1) M(2) M(3) M(4) M(5) M(6) M(7) \
                                    M(8) M(9) M(10) M(11) M(12) M(13) M(14) M(15) \
                                    M(16) M(17) M(18) M(19) M(20) M(21) M(22) M(23) \
                                    M(24) M(25) M(26) M(27) M(28) M(29) M(30) M(31)
#define BOOMCFG_IQ_FOREACH(M)       M(0) M(1) M(2) M(3) M(4) M(5) M(6) M(7)
#define BOOMCFG_LSQ_FOREACH(M)      M(0) M(1) M(2) M(3) M(4) M(5) M(6) M(7)
#define BOOMCFG_LSQ_FOREACH_F(M, f) M(0,f) M(1,f) M(2,f) M(3,f) M(4,f) M(5,f) M(6,f) M(7,f)
#else
#define BOOMCFG_ROB_FOREACH(M)      M(0) M(1) M(2) M(3) M(4) M(5) M(6) M(7) \
                                    M(8) M(9) M(10) M(11) M(12) M(13) M(14) M(15)
#define BOOMCFG_IQ_FOREACH(M)       M(0) M(1) M(2) M(3)
#define BOOMCFG_LSQ_FOREACH(M)      M(0) M(1) M(2) M(3)
#define BOOMCFG_LSQ_FOREACH_F(M, f) M(0,f) M(1,f) M(2,f) M(3,f)
#endif
