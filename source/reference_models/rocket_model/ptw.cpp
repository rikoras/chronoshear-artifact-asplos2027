#include "ptw.h"

#include "plru.h"
#include "pma.h"

namespace chisa::rocket_model {

namespace {

inline PteBits decode_pte(uint64_t raw) {
  PteBits p;
  p.ppn = (raw >> 10) & ((UINT64_C(1) << 54) - 1);
  p.d = (raw >> 7) & 1; p.a = (raw >> 6) & 1; p.g = (raw >> 5) & 1; p.u = (raw >> 4) & 1;
  p.x = (raw >> 3) & 1; p.w = (raw >> 2) & 1; p.r = (raw >> 1) & 1; p.v = raw & 1;
  return p;
}

}  // namespace

void Ptw::reset() { *this = Ptw{}; }

void Ptw::evaluate(const PtwIn& in, PtwWires& w) const {
  // Arbiter: requestor 0 has priority.
  const bool arb_valid = in.req_valid[0] || in.req_valid[1];
  const unsigned chosen = in.req_valid[0] ? 0 : 1;
  const bool arb_ready = state_ == PTW_S_READY && !l2_refill_;
  w.req_ready[0] = arb_ready;
  w.req_ready[1] = arb_ready && !in.req_valid[0];
  w.arb_fire = arb_valid && arb_ready;
  w.arb_chosen = chosen;
  w.arb_bits_valid = in.req_bits_valid[chosen];
  w.arb_addr = in.req_addr[chosen];

  // Decode the registered memory response.
  const PteBits tmp = decode_pte(mem_resp_data_);
  PteBits pte = tmp;
  pte.ppn = tmp.ppn & 0xFFFFF;
  if (tmp.r || tmp.w || tmp.x) {
    if (count_ <= 0 && ((tmp.ppn >> 9) & 0x1ff) != 0) pte.v = false;
    if (count_ <= 1 && (tmp.ppn & 0x1ff) != 0) pte.v = false;
  }
  const bool invalid_paddr = (tmp.ppn >> 20) != 0;
  const bool table = pte.v && !pte.r && !pte.w && !pte.x;
  const bool traverse = table && !invalid_paddr && count_ < 2;
  w.pte = pte;
  w.invalid_paddr = invalid_paddr;
  w.traverse = traverse;

  // Next PTE address: Cat(r_pte.ppn, vpn_idx) << 3.
  const unsigned lvl = count_ > 2 ? 2 : count_;
  const uint32_t vpn_idx = (r_req_addr_ >> ((2 - lvl) * 9)) & 0x1ff;
  const bool ppn_hi_zero = (r_pte_.ppn >> 20) == 0;
  const uint64_t pte_addr = ((r_pte_.ppn & ((UINT64_C(1) << 52) - 1)) << 12) | (static_cast<uint64_t>(vpn_idx) << 3);
  const bool ppn_fits_64 = (r_pte_.ppn >> 52) == 0;
  w.pte_addr_lo = static_cast<uint32_t>(pte_addr);
  w.mem_req_addr = pte_addr & ((UINT64_C(1) << 40) - 1);

  // PTE cache lookup (32-bit tags against the full-width address).
  uint8_t hits = 0;
  uint32_t data = 0;
  if (ppn_hi_zero) {
    for (unsigned i = 0; i < 8; ++i)
      if (((pc_valid_ >> i) & 1) && pc_tags_[i] == w.pte_addr_lo) { hits |= 1u << i; data |= pc_data_[i]; }
  }
  w.pte_cache_hits = hits;
  w.pte_cache_hit = hits != 0 && count_ < 2;
  w.pte_cache_data = data;

  // Homogeneity of the page the walk currently addresses.
  const bool pma_h = ppn_fits_64 && pma_level_homogeneous(pte_addr, count_);
  const bool pmp_h = pmp_homogeneous(*in.pmp, ppn_fits_64 ? (pte_addr & ~UINT64_C(0xfff)) : ~UINT64_C(0), count_);
  w.resp_homogeneous = pma_h && pmp_h;

  w.resp_valid[0] = resp_valid_[0];
  w.resp_valid[1] = resp_valid_[1];
  w.resp_ae = resp_ae_;
  w.resp_pte = r_pte_;
  w.resp_level = count_;
  w.mem_req_valid = state_ == PTW_S_REQ || state_ == PTW_S_DUMMY1;
  w.mem_s1_kill = state_ != PTW_S_WAIT1;
}

void Ptw::commit(const PtwIn& in, const PtwWires& w) {
  const uint8_t state = state_;
  uint8_t next = state;
  uint8_t count = count_;
  bool resp_valid[2] = {false, false};
  bool resp_ae = false;
  bool pte_hit = false;
  bool l2_refill = false;

  const bool mem_resp_valid = mem_resp_valid_;  // registered response used this cycle

  switch (state) {
    case PTW_S_READY:
      if (w.arb_fire) next = w.arb_bits_valid ? PTW_S_REQ : PTW_S_READY;
      count = 0;
      break;
    case PTW_S_REQ:
      if (w.pte_cache_hit) { count = (count_ + 1) & 3; pte_hit = true; }
      else next = in.mem_req_ready ? PTW_S_WAIT1 : PTW_S_REQ;
      break;
    case PTW_S_WAIT1:
      next = PTW_S_WAIT2;
      break;
    case PTW_S_WAIT2:
      next = PTW_S_WAIT3;
      if (in.mem_s2_xcpt_ae_ld) { resp_ae = true; next = PTW_S_READY; resp_valid[r_req_dest_ & 1] = true; }
      break;
    default:
      break;
  }

  // r_pte
  if (mem_resp_valid) r_pte_ = w.pte;
  else if (state == PTW_S_REQ && w.pte_cache_hit) r_pte_ = PteBits{w.pte_cache_data, false, false, false, false, false, false, false, false};
  else if (w.arb_fire) r_pte_.ppn = in.ptbr_ppn & ((UINT64_C(1) << 44) - 1);

  if (mem_resp_valid) {
    if (w.traverse) { next = PTW_S_REQ; count = (count_ + 1) & 3; }
    else {
      l2_refill = w.pte.v && !w.invalid_paddr && count_ == 2;
      resp_ae = w.pte.v && w.invalid_paddr;
      next = PTW_S_READY;
      resp_valid[r_req_dest_ & 1] = true;
    }
  }
  if (in.mem_s2_nack) next = PTW_S_REQ;

  // PTE cache (reads the old `invalidated`).
  const bool inval_old = invalidated_;
  if (mem_resp_valid && w.traverse && w.pte_cache_hits == 0 && !inval_old) {
    const uint32_t r = pc_valid_ == 0xff ? plru_replace_way(pc_plru_, 8) : priority_encoder(~pc_valid_ & 0xffu);
    pc_valid_ |= static_cast<uint8_t>(1u << r);
    pc_tags_[r] = w.pte_addr_lo;
    pc_data_[r] = static_cast<uint32_t>(w.pte.ppn) & 0xFFFFF;
  }
  if (w.pte_cache_hits != 0 && state == PTW_S_REQ)
    pc_plru_ = static_cast<uint8_t>(plru_next_state(pc_plru_, oh_to_uint(w.pte_cache_hits, 8), 8));
  if (in.sfence_valid && !in.sfence_rs1) pc_valid_ = 0;
  invalidated_ = in.sfence_valid || (inval_old && state != PTW_S_READY);

  if (w.arb_fire) { r_req_addr_ = w.arb_addr; r_req_dest_ = static_cast<uint8_t>(w.arb_chosen); }

  mem_resp_valid_ = in.mem_resp_valid;
  mem_resp_data_ = in.mem_resp_data;
  resp_valid_[0] = resp_valid[0];
  resp_valid_[1] = resp_valid[1];
  resp_ae_ = resp_ae;
  pte_hit_ = pte_hit;
  l2_refill_ = l2_refill;
  count_ = count;
  state_ = next;

  if (in.reset) {
    state_ = PTW_S_READY;
    pc_valid_ = 0;
    pc_plru_ = 0;
  }
}

}  // namespace chisa::rocket_model
