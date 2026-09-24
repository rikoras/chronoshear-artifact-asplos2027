#include "tlb.h"

#include "isa.h"
#include "plru.h"
#include "pma.h"

namespace chisa::rocket_model {

namespace {

constexpr unsigned kEntries = 13;            // 8 sectored + 4 superpage + 1 special
constexpr uint32_t kPhys = 1u << kEntries;   // the "!vm_enabled" pseudo entry
constexpr uint32_t kAll = (1u << (kEntries + 1)) - 1;
constexpr uint32_t kVpnMask = (1u << 27) - 1;

constexpr uint8_t M_WOK = 23;

inline bool is_amo_logical(uint8_t c) { return c == M_XA_SWAP || c == M_XA_XOR || c == M_XA_OR || c == M_XA_AND; }
inline bool is_amo_arith(uint8_t c) { return c == M_XA_ADD || c == M_XA_MIN || c == M_XA_MAX || c == M_XA_MINU || c == M_XA_MAXU; }
inline bool is_amo(uint8_t c) { return is_amo_logical(c) || is_amo_arith(c); }
inline bool is_read(uint8_t c) { return c == M_XRD || c == M_XLR || c == M_XSC || is_amo(c); }
inline bool is_write(uint8_t c) { return c == M_XWR || c == M_PWR || c == M_XSC || is_amo(c); }

// superpage entry (superpageOnly): j = 0 always compared, j = 1 when level >= 1, j = 2 ignored.
inline bool superpage_hit(const TlbEntry& e, uint32_t vpn) {
  if (!(e.valid & 1)) return false;
  if (((e.tag ^ vpn) >> 18) != 0) return false;
  return e.level >= 1 ? ((((e.tag ^ vpn) >> 9) & 0x1ff) == 0) : true;
}
inline bool special_hit(const TlbEntry& e, uint32_t vpn) {
  if (!(e.valid & 1)) return false;
  if (((e.tag ^ vpn) >> 18) != 0) return false;
  if (e.level >= 1 && ((((e.tag ^ vpn) >> 9) & 0x1ff) != 0)) return false;
  if (e.level >= 2 && (((e.tag ^ vpn) & 0x1ff) != 0)) return false;
  return true;
}
inline uint32_t superpage_ppn(const TlbEntry& e, uint32_t vpn, uint64_t data, bool superpage_only) {
  const uint32_t ppn = tlbe_ppn(data);
  uint32_t res = ppn >> 18;
  const bool ignore1 = e.level < 1;
  res = (res << 9) | ((((ignore1 ? vpn : 0u) | ppn) >> 9) & 0x1ff);
  const bool ignore2 = superpage_only || e.level < 2;
  res = (res << 9) | (((ignore2 ? vpn : 0u) | ppn) & 0x1ff);
  return res & 0xFFFFF;
}
inline bool sector_tag_match(const TlbEntry& e, uint32_t vpn) { return ((e.tag ^ vpn) >> 2) == 0; }

inline uint32_t replacement_entry(const TlbEntry* set, unsigned n, uint32_t alt) {
  uint32_t valids = 0;
  for (unsigned i = 0; i < n; ++i) if (set[i].valid) valids |= 1u << i;
  return valids == (1u << n) - 1 ? alt : priority_encoder(~valids & ((1u << n) - 1));
}

}  // namespace

void Tlb::reset() {
  state_ = TLB_S_READY;
  r_refill_tag_ = 0;
  r_superpage_repl_addr_ = r_sectored_repl_addr_ = r_sectored_hit_addr_ = 0;
  r_sectored_hit_ = false;
  for (auto& e : sectored_) e = TlbEntry{};
  for (auto& e : superpage_) e = TlbEntry{};
  special_ = TlbEntry{};
  sectored_plru_ = superpage_plru_ = 0;
}

void Tlb::evaluate(const TlbIn& in, TlbWires& w) const {
  const uint32_t vpn = static_cast<uint32_t>(in.vaddr >> 12) & kVpnMask;
  const unsigned priv = instruction_ ? in.prv : in.dprv;
  const bool priv_s = priv & 1;
  const bool priv_uses_vm = priv <= 1;
  const bool vm_enabled = ((in.ptbr_mode >> 3) & 1) && priv_uses_vm && !in.passthrough;
  const bool do_refill = in.ptw.resp_valid;
  const bool invalidate_refill = state_ == TLB_S_REQUEST || state_ == TLB_S_WAIT_INVALIDATE || in.sfence_valid;
  const uint32_t refill_ppn = static_cast<uint32_t>(in.ptw.pte.ppn) & 0xFFFFF;

  // Physical memory attributes of the address the MPU sees this cycle.
  uint64_t mpu_ppn;
  if (do_refill) mpu_ppn = refill_ppn;
  else if (vm_enabled) mpu_ppn = superpage_ppn(special_, vpn, special_.data[0], false);
  else mpu_ppn = (in.vaddr >> 12) & ((UINT64_C(1) << 28) - 1);
  const uint64_t mpu_physaddr = (mpu_ppn << 12) | (in.vaddr & 0xfff);
  const unsigned mpu_priv = (do_refill || in.passthrough) ? 1 : ((in.debug ? 4 : 0) | priv);
  const Pma pma = pma_lookup(mpu_physaddr);
  const PmpResult pmp = pmp_check(*in.pmp, static_cast<uint32_t>(mpu_physaddr), in.size, lg_max_size_, mpu_priv);
  const bool deny_debug = mpu_priv <= 3 && mpu_physaddr < 0x1000;
  const bool cacheable = pma.cacheable;
  const bool prot_r = pma.legal && !deny_debug && pmp.r;
  const bool prot_w = pma.w && !deny_debug && pmp.w;
  const bool prot_pp = pma.pp;
  const bool prot_al = pma.al;
  const bool prot_aa = pma.aa;
  const bool prot_x = pma.x && !deny_debug && pmp.x;
  const bool prot_eff = pma.eff;

  const uint8_t cmd = in.cmd;
  const bool cmd_lrsc = cmd == M_XLR || cmd == M_XSC;
  const bool cmd_amo_logical = is_amo_logical(cmd);
  const bool cmd_amo_arith = is_amo_arith(cmd);
  const bool cmd_put_partial = cmd == M_PWR;
  const bool cmd_read = is_read(cmd);
  const bool cmd_write = is_write(cmd);
  const bool cmd_write_perms = cmd_write || cmd == M_FLUSH_ALL || cmd == M_WOK;
  const bool misaligned = (in.vaddr & ((UINT64_C(1) << in.size) - 1)) != 0;

  w.req_ready = state_ == TLB_S_READY;
  w.ptw_req_valid = state_ == TLB_S_REQUEST;
  w.ptw_req_bits_valid = !in.kill;
  w.ptw_req_addr = r_refill_tag_;
  w.vm_enabled = vm_enabled;
  w.do_refill = do_refill;
  w.invalidate_refill = invalidate_refill;
  w.vpn = vpn;
  w.prefetchable = false;  // no manager supports hints
  w.new_entry = 0;

  if (!vm_enabled && !do_refill) {
    // Physical access: only the physical pseudo-entry contributes.
    w.tlb_miss = false;
    w.multiple_hits = false;
    w.sector_hits = 0;
    w.superpage_hits = 0;
    const bool ae_common = (misaligned && prot_eff) || (cmd_lrsc && !cacheable);
    w.pf_ld = false; w.pf_st = false; w.pf_inst = false;
    w.ae_ld = cmd_read && (ae_common || !prot_r);
    w.ae_st = (cmd_write_perms && (ae_common || !prot_w)) || (cmd_put_partial && !(prot_pp || cacheable)) ||
              (cmd_amo_logical && !(prot_al || cacheable)) || (cmd_amo_arith && !(prot_aa || cacheable));
    w.ae_inst = !prot_x;
    w.ma_ld = misaligned && cmd_read && !prot_eff;
    w.ma_st = misaligned && cmd_write && !prot_eff;
    w.cacheable = cacheable;
    w.must_alloc = (cmd_put_partial && !prot_pp) || (cmd_amo_logical && !prot_aa) || (cmd_amo_arith && !prot_al) || cmd_lrsc;
    w.miss = false;
    w.paddr = (static_cast<uint32_t>(vpn & 0xFFFFF) << 12) | static_cast<uint32_t>(in.vaddr & 0xfff);
    return;
  }

  // Hits.
  uint32_t sector_hits = 0, superpage_hits = 0, real_hits = 0;
  uint32_t ppn = 0;
  uint64_t sel[kEntries];
  if (vm_enabled) {
    for (unsigned i = 0; i < 8; ++i) {
      const TlbEntry& e = sectored_[i];
      const bool tag_match = sector_tag_match(e, vpn);
      if (e.valid && tag_match) sector_hits |= 1u << i;
      sel[i] = e.data[vpn & 3];
      if (((e.valid >> (vpn & 3)) & 1) && tag_match) { real_hits |= 1u << i; ppn |= tlbe_ppn(sel[i]); }
    }
    for (unsigned i = 0; i < 4; ++i) {
      const TlbEntry& e = superpage_[i];
      sel[8 + i] = e.data[0];
      if (superpage_hit(e, vpn)) {
        superpage_hits |= 1u << i;
        real_hits |= 1u << (8 + i);
        ppn |= superpage_ppn(e, vpn, e.data[0], true);
      }
    }
    sel[12] = special_.data[0];
    if (special_hit(special_, vpn)) { real_hits |= 1u << 12; ppn |= superpage_ppn(special_, vpn, special_.data[0], false); }
  } else {
    for (unsigned i = 0; i < 8; ++i) {
      const TlbEntry& e = sectored_[i];
      if (e.valid && sector_tag_match(e, vpn)) sector_hits |= 1u << i;
      sel[i] = e.data[vpn & 3];
    }
    for (unsigned i = 0; i < 4; ++i) {
      sel[8 + i] = superpage_[i].data[0];
      if (superpage_hit(superpage_[i], vpn)) superpage_hits |= 1u << i;
    }
    sel[12] = special_.data[0];
    ppn = vpn & 0xFFFFF;
  }
  const uint32_t hits = real_hits | (vm_enabled ? 0 : kPhys);

  // Permission arrays (bit 13 = physical access, bit 12 = special entry).
  uint32_t u = 0, ae = 0, sr = 0, sw = 0, sx = 0, pr = 0, pw = 0, px = 0, eff = 0, c = 0, ppp = 0, pal = 0, paa = 0;
  for (unsigned i = 0; i < kEntries; ++i) {
    const uint64_t d = sel[i];
    const uint32_t b = 1u << i;
    if (tlbe_bit(d, TLBE_U)) u |= b;
    if (tlbe_bit(d, TLBE_AE)) ae |= b;
    if (tlbe_bit(d, TLBE_SR)) sr |= b;
    if (tlbe_bit(d, TLBE_SW)) sw |= b;
    if (tlbe_bit(d, TLBE_SX)) sx |= b;
    if (i < 12) {
      if (tlbe_bit(d, TLBE_PR)) pr |= b;
      if (tlbe_bit(d, TLBE_PW)) pw |= b;
      if (tlbe_bit(d, TLBE_PX)) px |= b;
      if (tlbe_bit(d, TLBE_EFF)) eff |= b;
      if (tlbe_bit(d, TLBE_C)) c |= b;
      if (tlbe_bit(d, TLBE_PPP)) ppp |= b;
      if (tlbe_bit(d, TLBE_PAL)) pal |= b;
      if (tlbe_bit(d, TLBE_PAA)) paa |= b;
    }
  }
  const uint32_t entry_mask = (1u << kEntries) - 1;
  const uint32_t phys2 = 3u << 12;  // special entry + physical
  const uint32_t ptw_ae_array = ae;
  const uint32_t priv_rw_ok = ((!priv_s || in.sum) ? u : 0) | (priv_s ? (~u & entry_mask) : 0);
  const uint32_t priv_x_ok = priv_s ? (~u & entry_mask) : u;
  const uint32_t r_array = kPhys | (priv_rw_ok & (sr | (in.mxr ? sx : 0)));
  const uint32_t w_array = kPhys | (priv_rw_ok & sw);
  const uint32_t x_array = kPhys | (priv_x_ok & sx);
  const uint32_t pr_array = ((prot_r ? phys2 : 0) | pr) & ~ptw_ae_array;
  const uint32_t pw_array = ((prot_w ? phys2 : 0) | pw) & ~ptw_ae_array;
  const uint32_t px_array = ((prot_x ? phys2 : 0) | px) & ~ptw_ae_array;
  const uint32_t eff_array = (prot_eff ? phys2 : 0) | eff;
  const uint32_t c_array = (cacheable ? phys2 : 0) | c;
  const uint32_t ppp_array = (prot_pp ? phys2 : 0) | ppp;
  const uint32_t paa_array = (prot_aa ? phys2 : 0) | paa;
  const uint32_t pal_array = (prot_al ? phys2 : 0) | pal;
  const uint32_t ppp_if_cached = ppp_array | c_array;
  const uint32_t paa_if_cached = paa_array | c_array;
  const uint32_t pal_if_cached = pal_array | c_array;

  const uint64_t va_hi = (in.vaddr >> 38) & 3;
  const bool bad_va = vm_enabled && !(va_hi == 0 || va_hi == 3);

  const uint32_t lrsc_allowed = c_array;
  const uint32_t ae_array = (misaligned ? eff_array : 0) | (cmd_lrsc ? (~lrsc_allowed & kAll) : 0);
  const uint32_t ae_ld_array = cmd_read ? (ae_array | (~pr_array & kAll)) : 0;
  const uint32_t ae_st_array = (cmd_write_perms ? (ae_array | (~pw_array & kAll)) : 0) |
                               (cmd_put_partial ? (~ppp_if_cached & kAll) : 0) |
                               (cmd_amo_logical ? (~pal_if_cached & kAll) : 0) |
                               (cmd_amo_arith ? (~paa_if_cached & kAll) : 0);
  const uint32_t must_alloc_array = (cmd_put_partial ? (~ppp_array & kAll) : 0) |
                                    (cmd_amo_logical ? (~paa_array & kAll) : 0) |
                                    (cmd_amo_arith ? (~pal_array & kAll) : 0) |
                                    (cmd_lrsc ? kAll : 0);
  const uint32_t ma_ld_array = (misaligned && cmd_read) ? (~eff_array & kAll) : 0;
  const uint32_t ma_st_array = (misaligned && cmd_write) ? (~eff_array & kAll) : 0;
  const uint32_t pf_ld_array = cmd_read ? (~(r_array | ptw_ae_array) & kAll) : 0;
  const uint32_t pf_st_array = cmd_write_perms ? (~(w_array | ptw_ae_array) & kAll) : 0;
  const uint32_t pf_inst_array = ~(x_array | ptw_ae_array) & kAll;

  const bool tlb_hit = real_hits != 0;
  const bool tlb_miss = vm_enabled && !bad_va && !tlb_hit;
  const bool multiple_hits = __builtin_popcount(real_hits) >= 2;

  w.pf_ld = (bad_va && cmd_read) || (pf_ld_array & hits);
  w.pf_st = (bad_va && cmd_write_perms) || (pf_st_array & hits);
  w.pf_inst = bad_va || (pf_inst_array & hits);
  w.ae_ld = (ae_ld_array & hits) != 0;
  w.ae_st = (ae_st_array & hits) != 0;
  w.ae_inst = (~px_array & hits) != 0;
  w.ma_ld = (ma_ld_array & hits) != 0;
  w.ma_st = (ma_st_array & hits) != 0;
  w.cacheable = (c_array & hits) != 0;
  w.must_alloc = (must_alloc_array & hits) != 0;
  w.miss = do_refill || tlb_miss || multiple_hits;
  w.paddr = (ppn << 12) | static_cast<uint32_t>(in.vaddr & 0xfff);
  w.tlb_miss = tlb_miss;
  w.multiple_hits = multiple_hits;
  w.sector_hits = static_cast<uint8_t>(sector_hits);
  w.superpage_hits = static_cast<uint8_t>(superpage_hits);

  if (do_refill) {
    const PteBits& p = in.ptw.pte;
    const bool leaf = p.v && (p.r || (p.x && !p.w)) && p.a;
    uint64_t e = static_cast<uint64_t>(refill_ppn) << TLBE_PPN_SHIFT;
    if (p.u) e |= UINT64_C(1) << TLBE_U;
    if (p.g && p.v) e |= UINT64_C(1) << TLBE_G;
    if (in.ptw.resp_ae) e |= UINT64_C(1) << TLBE_AE;
    if (leaf && p.r) e |= UINT64_C(1) << TLBE_SR;
    if (leaf && p.w && p.d) e |= UINT64_C(1) << TLBE_SW;
    if (leaf && p.x) e |= UINT64_C(1) << TLBE_SX;
    if (prot_r) e |= UINT64_C(1) << TLBE_PR;
    if (prot_w) e |= UINT64_C(1) << TLBE_PW;
    if (prot_x) e |= UINT64_C(1) << TLBE_PX;
    if (prot_pp) e |= UINT64_C(1) << TLBE_PPP;
    if (prot_al) e |= UINT64_C(1) << TLBE_PAL;
    if (prot_aa) e |= UINT64_C(1) << TLBE_PAA;
    if (prot_eff) e |= UINT64_C(1) << TLBE_EFF;
    if (cacheable) e |= UINT64_C(1) << TLBE_C;
    if (in.ptw.fragmented_superpage) e |= UINT64_C(1) << TLBE_FRAG;
    w.new_entry = e;
  }
}

void Tlb::commit(const TlbIn& in, const TlbWires& w) {
  const uint32_t vpn = w.vpn;
  const bool sfence = in.sfence_valid;
  // Nothing changes without a refill, a virtual access, a fence, a kill of a
  // pending request, a multiple hit, or reset.
  if (!w.do_refill && !(in.req_valid && w.vm_enabled) && !sfence && state_ == TLB_S_READY && !w.multiple_hits && !in.reset) return;

  // Replacement-policy reads happen before this cycle's updates.
  const uint32_t sectored_way = plru_replace_way(sectored_plru_, 8);
  const uint32_t superpage_way = plru_replace_way(superpage_plru_, 4);

  // Refill.
  if (w.do_refill) {
    const uint8_t level = in.ptw.level;
    if (!in.ptw.homogeneous) {
      TlbEntry& e = special_;
      e.tag = r_refill_tag_;
      e.level = level & 3;
      e.valid = 1;
      e.data[0] = w.new_entry;
      if (w.invalidate_refill) e.valid = 0;
    } else if (level < 2) {
      TlbEntry& e = superpage_[r_superpage_repl_addr_ & 3];
      e.tag = r_refill_tag_;
      e.level = level & 1;
      e.valid = 1;
      e.data[0] = w.new_entry;
      if (w.invalidate_refill) e.valid = 0;
    } else {
      const uint32_t waddr = r_sectored_hit_ ? r_sectored_hit_addr_ : r_sectored_repl_addr_;
      TlbEntry& e = sectored_[waddr & 7];
      if (!r_sectored_hit_) e.valid = 0;
      e.tag = r_refill_tag_;
      e.level = 0;
      const unsigned idx = r_refill_tag_ & 3;
      e.valid |= 1u << idx;
      e.data[idx] = w.new_entry;
      if (w.invalidate_refill) e.valid = 0;
    }
  }

  // PLRU updates.
  if (in.req_valid && w.vm_enabled) {
    if (w.sector_hits) sectored_plru_ = static_cast<uint8_t>(plru_next_state(sectored_plru_, oh_to_uint(w.sector_hits, 8), 8));
    if (w.superpage_hits) superpage_plru_ = static_cast<uint8_t>(plru_next_state(superpage_plru_, oh_to_uint(w.superpage_hits, 4), 4));
  }

  // Miss bookkeeping and state machine.
  uint8_t state = state_;
  if (in.req_valid && state_ == TLB_S_READY && w.tlb_miss) {
    state = TLB_S_REQUEST;
    r_refill_tag_ = vpn;
    r_superpage_repl_addr_ = static_cast<uint8_t>(replacement_entry(superpage_, 4, superpage_way));
    r_sectored_repl_addr_ = static_cast<uint8_t>(replacement_entry(sectored_, 8, sectored_way));
    r_sectored_hit_addr_ = static_cast<uint8_t>(oh_to_uint(w.sector_hits, 8));
    r_sectored_hit_ = w.sector_hits != 0;
  }
  if (state_ == TLB_S_REQUEST) {
    if (sfence) state = TLB_S_READY;
    if (in.ptw.req_ready) state = sfence ? TLB_S_WAIT_INVALIDATE : TLB_S_WAIT;
    if (in.kill) state = TLB_S_READY;
  }
  if (state_ == TLB_S_WAIT && sfence) state = TLB_S_WAIT_INVALIDATE;
  if (in.ptw.resp_valid) state = TLB_S_READY;
  state_ = state;

  // SFENCE invalidations.
  if (sfence) {
    if (in.sfence_rs1) {
      for (TlbEntry& e : sectored_) {
        if (sector_tag_match(e, vpn)) e.valid &= ~(1u << (vpn & 3));
        if (((e.tag ^ vpn) >> 18) == 0)
          for (unsigned s = 0; s < 4; ++s) if (tlbe_bit(e.data[s], TLBE_FRAG)) e.valid &= ~(1u << s);
      }
      for (TlbEntry& e : superpage_) if (superpage_hit(e, vpn)) e.valid = 0;
      if (special_hit(special_, vpn)) special_.valid = 0;
    } else if (in.sfence_rs2) {
      for (TlbEntry& e : sectored_)
        for (unsigned s = 0; s < 4; ++s) if (!tlbe_bit(e.data[s], TLBE_G)) e.valid &= ~(1u << s);
      for (TlbEntry& e : superpage_) if (!tlbe_bit(e.data[0], TLBE_G)) e.valid = 0;
      if (!tlbe_bit(special_.data[0], TLBE_G)) special_.valid = 0;
    } else {
      for (TlbEntry& e : sectored_) e.valid = 0;
      for (TlbEntry& e : superpage_) e.valid = 0;
      special_.valid = 0;
    }
  }
  if (w.multiple_hits || in.reset) {
    for (TlbEntry& e : sectored_) e.valid = 0;
    for (TlbEntry& e : superpage_) e.valid = 0;
    special_.valid = 0;
  }
  if (in.reset) state_ = TLB_S_READY;
}

}  // namespace chisa::rocket_model
