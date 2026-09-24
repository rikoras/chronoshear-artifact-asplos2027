// Rocket page-table walker (rocket/PTW.scala) for the locked DefaultConfig:
// two requestors (0 = data TLB, 1 = instruction TLB), an 8-entry PTE cache,
// no L2 TLB, Sv39 (pgLevels = 3), pmpGranularity below the page size.
#pragma once
#include <cstdint>

#include "pmp.h"
#include "tlb.h"

namespace chisa::rocket_model {

enum : uint8_t {
  PTW_S_READY = 0, PTW_S_REQ = 1, PTW_S_WAIT1 = 2, PTW_S_DUMMY1 = 3,
  PTW_S_WAIT2 = 4, PTW_S_WAIT3 = 5, PTW_S_DUMMY2 = 6, PTW_S_FRAGMENT_SUPERPAGE = 7
};

struct PtwIn {
  bool req_valid[2];
  bool req_bits_valid[2];
  uint32_t req_addr[2];       // vpn, 27 bits
  bool mem_req_ready;
  bool mem_resp_valid;
  uint64_t mem_resp_data;
  bool mem_s2_nack;
  bool mem_s2_xcpt_ae_ld;
  uint64_t ptbr_ppn;          // 44 bits
  uint8_t ptbr_mode;
  bool sfence_valid, sfence_rs1;
  const PmpSet* pmp;
  bool reset;
};

struct PtwWires {
  // outputs
  bool req_ready[2];
  bool resp_valid[2];
  bool resp_ae;
  PteBits resp_pte;
  uint8_t resp_level;
  bool resp_homogeneous;
  bool mem_req_valid;
  uint64_t mem_req_addr;      // 40 bits
  bool mem_s1_kill;
  // internals used by commit
  bool arb_fire, arb_bits_valid;
  unsigned arb_chosen;
  uint32_t arb_addr;
  bool pte_cache_hit;
  uint8_t pte_cache_hits;
  uint32_t pte_cache_data;
  bool traverse, invalid_paddr;
  PteBits pte;                // decoded response with ppn truncated and v fixed up
  uint32_t pte_addr_lo;       // low 32 bits of pte_addr
};

class Ptw {
 public:
  void reset();
  void evaluate(const PtwIn& in, PtwWires& w) const;
  void commit(const PtwIn& in, const PtwWires& w);
  template <class S> void export_image(S& s) const;

  uint8_t state_ = PTW_S_READY;
  bool resp_valid_[2] = {false, false};
  bool invalidated_ = false;
  uint8_t count_ = 0;
  bool resp_ae_ = false;
  uint32_t r_req_addr_ = 0;
  uint8_t r_req_dest_ = 0;
  PteBits r_pte_ = {};
  bool mem_resp_valid_ = false;
  uint64_t mem_resp_data_ = 0;
  uint8_t pc_valid_ = 0;
  uint32_t pc_tags_[8] = {};
  uint32_t pc_data_[8] = {};
  uint8_t pc_plru_ = 0;       // 7 bits
  bool pte_hit_ = false;
  bool l2_refill_ = false;
};

template <class S>
void Ptw::export_image(S& s) const {
  s.r_pte_ppn = r_pte_.ppn;
  s.r_req_addr = r_req_addr_;
  s.tags_0 = pc_tags_[0]; s.tags_1 = pc_tags_[1]; s.tags_2 = pc_tags_[2]; s.tags_3 = pc_tags_[3];
  s.tags_4 = pc_tags_[4]; s.tags_5 = pc_tags_[5]; s.tags_6 = pc_tags_[6]; s.tags_7 = pc_tags_[7];
  s.count = count_;
  s.r_pte_a = r_pte_.a; s.r_pte_d = r_pte_.d; s.r_pte_g = r_pte_.g; s.r_pte_r = r_pte_.r;
  s.r_pte_u = r_pte_.u; s.r_pte_v = r_pte_.v; s.r_pte_w = r_pte_.w; s.r_pte_x = r_pte_.x;
  s.resp_valid_0 = resp_valid_[0];
  s.resp_valid_1 = resp_valid_[1];
  s.state = state_;
  s.valid = pc_valid_;
}

}  // namespace chisa::rocket_model
