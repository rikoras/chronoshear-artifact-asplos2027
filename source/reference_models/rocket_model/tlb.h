// Rocket TLB (rocket/TLB.scala) for the locked DefaultConfig:
// 1 set x 8 sectored entries x 4 sectors, 4 superpage entries, 1 special
// entry (pmpGranularity 4 < page size), Sv39, no ASIDs.
#pragma once
#include <cstdint>

#include "pmp.h"

namespace chisa::rocket_model {

enum : uint8_t { TLB_S_READY = 0, TLB_S_REQUEST = 1, TLB_S_WAIT = 2, TLB_S_WAIT_INVALIDATE = 3 };

// Packed TLBEntryData (35 bits): ppn[34:15] u g ae sw sx sr pw px pr ppp pal paa eff c frag.
enum : unsigned {
  TLBE_FRAG = 0, TLBE_C = 1, TLBE_EFF = 2, TLBE_PAA = 3, TLBE_PAL = 4, TLBE_PPP = 5, TLBE_PR = 6,
  TLBE_PX = 7, TLBE_PW = 8, TLBE_SR = 9, TLBE_SX = 10, TLBE_SW = 11, TLBE_AE = 12, TLBE_G = 13,
  TLBE_U = 14, TLBE_PPN_SHIFT = 15
};
inline uint32_t tlbe_ppn(uint64_t d) { return static_cast<uint32_t>(d >> TLBE_PPN_SHIFT) & 0xFFFFF; }
inline bool tlbe_bit(uint64_t d, unsigned b) { return (d >> b) & 1; }

struct TlbEntry {
  uint32_t tag = 0;      // vpn, 27 bits
  uint8_t level = 0;     // 2 bits (1 bit for superpage-only entries)
  uint8_t valid = 0;     // per sector
  uint64_t data[4] = {};  // per sector, 35 bits
};

struct PteBits {
  uint64_t ppn;  // 54 bits
  bool d, a, g, u, x, w, r, v;
};

struct PtwToTlb {
  bool req_ready;
  bool resp_valid;
  bool resp_ae;
  PteBits pte;
  uint8_t level;
  bool fragmented_superpage;
  bool homogeneous;
};

struct TlbIn {
  bool req_valid;
  uint64_t vaddr;      // 40 bits
  bool passthrough;
  uint8_t size;        // 2 bits
  uint8_t cmd;         // 5 bits
  bool sfence_valid, sfence_rs1, sfence_rs2;
  uint64_t sfence_addr;
  bool kill;
  PtwToTlb ptw;
  uint8_t prv, dprv;   // status
  bool debug, sum, mxr;
  uint8_t ptbr_mode;   // 4 bits
  const PmpSet* pmp;
  bool reset;
};

struct TlbWires {
  // outputs
  bool req_ready;
  bool miss;
  uint32_t paddr;
  bool pf_ld, pf_st, pf_inst, ae_ld, ae_st, ae_inst, ma_ld, ma_st;
  bool cacheable, must_alloc, prefetchable;
  bool ptw_req_valid, ptw_req_bits_valid;
  uint32_t ptw_req_addr;
  // internals used by commit
  bool vm_enabled, do_refill, invalidate_refill, tlb_miss, multiple_hits;
  uint32_t vpn;
  uint8_t sector_hits, superpage_hits;
  uint64_t new_entry;
};

class Tlb {
 public:
  Tlb(bool instruction, unsigned lg_max_size) : instruction_(instruction), lg_max_size_(lg_max_size) {}
  void reset();
  void evaluate(const TlbIn& in, TlbWires& w) const;
  void commit(const TlbIn& in, const TlbWires& w);

  // Export the manifest registers into a component image (Frontend/Dcache).
  template <class S> void export_image(S& s) const;

  uint8_t state_ = TLB_S_READY;
  uint32_t r_refill_tag_ = 0;
  uint8_t r_superpage_repl_addr_ = 0, r_sectored_repl_addr_ = 0, r_sectored_hit_addr_ = 0;
  bool r_sectored_hit_ = false;
  TlbEntry sectored_[8];
  TlbEntry superpage_[4];
  TlbEntry special_;
  uint8_t sectored_plru_ = 0;   // 7 bits
  uint8_t superpage_plru_ = 0;  // 3 bits

 private:
  bool instruction_;
  unsigned lg_max_size_;
};

template <class S>
void Tlb::export_image(S& s) const {
  s.tlb_r_refill_tag = r_refill_tag_;
  s.tlb_r_sectored_hit = r_sectored_hit_;
  s.tlb_r_sectored_hit_addr = r_sectored_hit_addr_;
  s.tlb_r_sectored_repl_addr = r_sectored_repl_addr_;
  s.tlb_r_superpage_repl_addr = r_superpage_repl_addr_;
  s.tlb_special_entry_data_0 = special_.data[0];
  s.tlb_special_entry_valid_0 = special_.valid & 1;
#define V(e, j) s.tlb_sectored_entries_0_##e##_valid_##j = (sectored_[e].valid >> j) & 1;
#define E(e) V(e, 0) V(e, 1) V(e, 2) V(e, 3)
  E(0) E(1) E(2) E(3) E(4) E(5) E(6) E(7)
#undef E
#undef V
  s.tlb_superpage_entries_0_valid_0 = superpage_[0].valid & 1;
  s.tlb_superpage_entries_1_valid_0 = superpage_[1].valid & 1;
  s.tlb_superpage_entries_2_valid_0 = superpage_[2].valid & 1;
  s.tlb_superpage_entries_3_valid_0 = superpage_[3].valid & 1;
}

}  // namespace chisa::rocket_model
