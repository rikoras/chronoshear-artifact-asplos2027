#include "dcache.h"

#include "isa.h"

// Event-driven blocking data cache.  An idle cache (no request in flight, no
// store buffered, no bus traffic, no probe or release outstanding) costs a
// few flag tests per cycle.  On active cycles only the stages that hold
// something are evaluated, and the expensive pieces (atomic ALU, load
// alignment, TileLink message formation) run only when their result is used.

namespace chisa::rocket_model {

namespace {

constexpr uint8_t M_WOK = 23;
constexpr uint64_t kVaMask40 = (UINT64_C(1) << 40) - 1;
constexpr unsigned kLrscCycles = 80, kLrscBackoff = 3, kBlockProbeAfterGrantCycles = 8;
constexpr uint8_t TL_A_PUTFULL = 0, TL_A_PUTPARTIAL = 1, TL_A_ARITH = 2, TL_A_LOGICAL = 3, TL_A_GET = 4, TL_A_ACQUIRE = 6;
constexpr uint8_t TL_C_PROBEACK = 4, TL_C_PROBEACKDATA = 5, TL_C_RELEASE = 6, TL_C_RELEASEDATA = 7;
constexpr uint8_t TL_D_ACCESSACK = 0, TL_D_ACCESSACKDATA = 1, TL_D_HINTACK = 2, TL_D_GRANT = 4, TL_D_GRANTDATA = 5, TL_D_RELEASEACK = 6;
constexpr uint8_t ST_NOTHING = 0, ST_BRANCH = 1, ST_TRUNK = 2, ST_DIRTY = 3;
constexpr uint8_t P_toT = 0, P_toB = 1, P_toN = 2;
constexpr uint8_t P_NtoB = 0, P_NtoT = 1, P_BtoT = 2;
constexpr uint8_t P_TtoB = 0, P_TtoN = 1, P_BtoN = 2, P_TtoT = 3, P_BtoB = 4, P_NtoN = 5;

inline bool is_amo_logical(uint8_t c) { return c == M_XA_SWAP || c == M_XA_XOR || c == M_XA_OR || c == M_XA_AND; }
inline bool is_amo_arith(uint8_t c) { return c == M_XA_ADD || c == M_XA_MIN || c == M_XA_MAX || c == M_XA_MINU || c == M_XA_MAXU; }
inline bool is_amo(uint8_t c) { return is_amo_logical(c) || is_amo_arith(c); }
inline bool is_read(uint8_t c) { return c == M_XRD || c == M_XLR || c == M_XSC || is_amo(c); }
inline bool is_write(uint8_t c) { return c == M_XWR || c == M_PWR || c == M_XSC || is_amo(c); }
inline bool needs_read(const HellaReq& req) { return is_read(req.cmd) || req.cmd == M_PWR; }
inline bool is_write_intent(uint8_t c) { return is_write(c) || c == M_PFW || c == M_XLR; }
inline unsigned categorize(uint8_t c) { return (is_write(c) ? 2 : 0) | (is_write_intent(c) ? 1 : 0); }

inline void grow_starter(uint8_t cmd, uint8_t state, bool& hit, uint8_t& param) {
  const unsigned c = categorize(cmd);
  hit = false; param = 0;
  if (c == 0) {
    if (state == ST_DIRTY) { hit = true; param = ST_DIRTY; }
    else if (state == ST_TRUNK) { hit = true; param = ST_TRUNK; }
    else if (state == ST_BRANCH) { hit = true; param = ST_BRANCH; }
    else { param = P_NtoB; }
  } else if (c == 1) {
    if (state == ST_DIRTY) { hit = true; param = ST_DIRTY; }
    else if (state == ST_TRUNK) { hit = true; param = ST_TRUNK; }
    else if (state == ST_BRANCH) { param = P_BtoT; }
    else { param = P_NtoT; }
  } else if (c == 3) {
    if (state == ST_DIRTY) { hit = true; param = ST_DIRTY; }
    else if (state == ST_TRUNK) { hit = true; param = ST_DIRTY; }
    else if (state == ST_BRANCH) { param = P_BtoT; }
    else { param = P_NtoT; }
  }
}
inline uint8_t grow_finisher(uint8_t cmd, uint8_t param) {
  const unsigned c = categorize(cmd);
  if (c == 0 && param == P_toB) return ST_BRANCH;
  if (c == 0 && param == P_toT) return ST_TRUNK;
  if (c == 1 && param == P_toT) return ST_TRUNK;
  if (c == 3 && param == P_toT) return ST_DIRTY;
  return ST_NOTHING;
}
inline void shrink_helper(uint8_t param, uint8_t state, bool& dirty, uint8_t& report, uint8_t& next) {
  dirty = false; report = 0; next = 0;
  switch (param) {
    case P_toT:
      if (state == ST_DIRTY) { dirty = true; report = P_TtoT; next = ST_TRUNK; }
      else if (state == ST_TRUNK) { report = P_TtoT; next = ST_TRUNK; }
      else if (state == ST_BRANCH) { report = P_BtoB; next = ST_BRANCH; }
      else { report = P_NtoN; next = ST_NOTHING; }
      break;
    case P_toB:
      if (state == ST_DIRTY) { dirty = true; report = P_TtoB; next = ST_BRANCH; }
      else if (state == ST_TRUNK) { report = P_TtoB; next = ST_BRANCH; }
      else if (state == ST_BRANCH) { report = P_BtoB; next = ST_BRANCH; }
      else { report = P_NtoN; next = ST_NOTHING; }
      break;
    case P_toN:
      if (state == ST_DIRTY) { dirty = true; report = P_TtoN; next = ST_NOTHING; }
      else if (state == ST_TRUNK) { report = P_TtoN; next = ST_NOTHING; }
      else if (state == ST_BRANCH) { report = P_BtoN; next = ST_NOTHING; }
      else { report = P_NtoN; next = ST_NOTHING; }
      break;
    default: break;
  }
}

inline uint8_t store_mask(uint8_t size, uint64_t addr) {
  static const uint8_t kSizeMask[4] = {0x01, 0x03, 0x0f, 0xff};
  return static_cast<uint8_t>(kSizeMask[size & 3] << (addr & 7 & ~((1u << (size & 3)) - 1)));
}

inline uint64_t load_gen(uint8_t size, bool sgn, uint64_t addr, uint64_t dat, bool zero, int log_min) {
  uint64_t res = dat;
  for (int i = 2; i >= log_min; --i) {
    const unsigned pos = 8u << i;
    const uint64_t lo_mask = (UINT64_C(1) << pos) - 1;
    const uint64_t shifted = ((addr >> i) & 1) ? ((res >> pos) & lo_mask) : (res & lo_mask);
    const bool do_zero = (i == 0) && zero;
    const uint64_t zeroed = do_zero ? 0 : shifted;
    const bool fill = sgn && ((zeroed >> (pos - 1)) & 1);
    const uint64_t hi = (size == i || do_zero) ? (fill ? (~UINT64_C(0) << pos) : 0) : (res & ~lo_mask);
    res = hi | zeroed;
  }
  return res;
}

inline uint64_t amoalu(uint8_t mask, uint8_t cmd, uint64_t lhs, uint64_t rhs) {
  const bool mx = cmd == M_XA_MAX || cmd == M_XA_MAXU;
  const bool mn = cmd == M_XA_MIN || cmd == M_XA_MINU;
  const bool add = cmd == M_XA_ADD;
  const bool logic_and = cmd == M_XA_OR || cmd == M_XA_AND;
  const bool logic_xor = cmd == M_XA_XOR || cmd == M_XA_OR;
  const uint64_t amask = ~((((mask >> 3) & 1) ? UINT64_C(0) : UINT64_C(1)) << 31);
  const uint64_t adder_out = (lhs & amask) + (rhs & amask);
  const bool sgn = !((cmd >> 1) & 1);
  auto is_less = [&](unsigned n) -> bool {
    const uint64_t x = n == 64 ? lhs : (lhs & 0xffffffffu), y = n == 64 ? rhs : (rhs & 0xffffffffu);
    const bool xs = (lhs >> (n - 1)) & 1, ys = (rhs >> (n - 1)) & 1;
    if (xs == ys) return x < y;
    return sgn ? xs : ys;
  };
  const bool less = ((mask >> 4) & 1) ? is_less(64) : is_less(32);
  const uint64_t minmax = (less ? mn : mx) ? lhs : rhs;
  const uint64_t logic = (logic_and ? (lhs & rhs) : 0) | (logic_xor ? (lhs ^ rhs) : 0);
  const uint64_t out = add ? adder_out : (logic_and || logic_xor) ? logic : minmax;
  uint64_t wmask = 0;
  for (unsigned i = 0; i < 8; ++i) if ((mask >> i) & 1) wmask |= UINT64_C(0xff) << (8 * i);
  return (wmask & out) | (~wmask & lhs);
}

inline uint8_t tl_mask(uint32_t addr, uint8_t size) {
  if (size >= 3) return 0xff;
  const unsigned bytes = 1u << size;
  return static_cast<uint8_t>(((1u << bytes) - 1) << (addr & 7 & ~(bytes - 1)));
}
inline uint32_t meta_pack(uint32_t tag, uint8_t state) { return ((state & 3u) << 20) | (tag & 0xFFFFF); }
inline uint16_t d_beats1_of(uint8_t opcode, uint8_t size) { return (opcode & 1) ? static_cast<uint16_t>(((1u << size) - 1) >> 3) : 0; }

}  // namespace

void Dcache::evaluate(const DcacheIn& in, DcacheWires& w) const {
  if (architectural_mode_) w = DcacheWires{};
  const bool exact = in.exact_seam && !architectural_mode_;
  // ---- activity ----
  const bool tlb_busy = tlb.state_ != TLB_S_READY;
  const bool work_pending = in.req_valid || s1_valid_ || s2_valid_ || s1_probe_ || s2_probe_ || release_state_ != DC_S_READY ||
                      cached_grant_wait_ || uncachedInFlight_ || pstore1_held_ || pstore2_valid_ || in.b_valid || in.d_valid ||
                      resetting_ || reset_next_ || s1_release_data_valid_ || s2_release_data_valid_ ||
                      doUncachedResp_ || tlb_busy || in.ptw.resp_valid || in.reset || grantInProgress_;
  const bool inactive_tail = lrscCount_ != 0 || blockProbeAfterGrantCount_ != 0 || blockUncachedGrant_ ||
                      s2_xcpt_reg_ || pstore_drain_on_miss_reg_ || !s2_not_nacked_in_s1_ || !clock_en_reg_;
  const bool active = work_pending || (!architectural_mode_ && inactive_tail);
  w.idle = !active;
  w.s2_nack_cause_raw = s2_nack_cause_raw_reg_;
  w.ptw_req_valid = false;
  w.ptw_req_addr = tlb.r_refill_tag_;
  w.tlb_used = false;
  if (!active && !exact) {
    const bool grantIsCached = in.d_opcode == TL_D_GRANT || in.d_opcode == TL_D_GRANTDATA;
    w.req_ready = true;
    w.s2_nack = false;
    w.resp_valid = false;
    w.replay_next = false;
    w.xcpt_ma_ld = w.xcpt_ma_st = w.xcpt_pf_ld = w.xcpt_pf_st = w.xcpt_ae_ld = w.xcpt_ae_st = false;
    w.ordered = true;
    w.perf_grant = w.perf_release = w.perf_acquire = false;
    w.a.valid = false;
    w.b_ready = blockProbeAfterGrantCount_ == 0 && lrscCount_ <= kLrscBackoff &&
        !(release_ack_wait_ && (((in.b_address ^ release_ack_addr_) >> 6) & ((1u << 15) - 1)) == 0);
    w.c.valid = false;
    w.d_ready = grantIsCached ? in.e_ready : true;
    w.e_valid = false;
    w.s2_uncached = false;
    w.s2_paddr = static_cast<uint32_t>(s2_req_.addr);
    return;
  }

  const bool s1_valid = s1_valid_;
  const HellaReq& s1_req = s1_req_;
  const bool s1_read = is_read(s1_req.cmd);
  const bool s1_write = is_write(s1_req.cmd);
  const bool s1_readwrite = s1_read || s1_write;
  const bool s1_sfence = s1_req.cmd == M_SFENCE;
  const bool s1_flush_line = s1_req.cmd == M_FLUSH_ALL && (s1_req.size & 1);
  const bool s1_cmd_uses_tlb = s1_readwrite || s1_flush_line || s1_req.cmd == M_WOK;
  const bool inWriteback = release_state_ == DC_S_VOLUNTARY_WRITEBACK || release_state_ == DC_S_PROBE_REP_DIRTY;
  const bool releaseInFlight = s1_probe_ || s2_probe_ || release_state_ != DC_S_READY;
  w.s1_write = s1_write; w.s1_sfence = s1_sfence;

  // ---- data TLB (needed for stage 1, refills and fences) ----
  const bool tlb_req_valid = s1_valid && !in.s1_kill && s1_cmd_uses_tlb;
  const bool tlb_sfence = s1_valid && !in.s1_kill && s1_sfence;
  const bool need_tlb = exact || s1_valid || s1_probe_ || tlb_busy || in.ptw.resp_valid || tlb_sfence || in.reset;
  uint32_t s1_paddr = static_cast<uint32_t>(s1_req.addr);
  if (need_tlb) {
    TlbIn& ti = w.tlb_in;
    ti.req_valid = tlb_req_valid;
    ti.vaddr = s1_tlb_req_vaddr_ & kVaMask40;
    ti.passthrough = s1_tlb_req_passthrough_;
    ti.size = s1_tlb_req_size_;
    ti.cmd = s1_tlb_req_cmd_;
    ti.sfence_valid = tlb_sfence;
    ti.sfence_rs1 = s1_req.size & 1;
    ti.sfence_rs2 = (s1_req.size >> 1) & 1;
    ti.sfence_addr = s1_req.addr & kVaMask40;
    ti.kill = in.s2_kill;
    ti.ptw = in.ptw;
    ti.prv = in.dprv; ti.dprv = in.dprv; ti.debug = in.debug; ti.sum = in.sum; ti.mxr = in.mxr;
    ti.ptbr_mode = in.ptbr_mode;
    ti.pmp = in.pmp;
    ti.reset = in.reset;
    tlb.evaluate(ti, w.tlb);
    w.tlb_used = true;
    s1_paddr = ((w.tlb.paddr >> 12) << 12) | static_cast<uint32_t>(s1_req.addr & 0xfff);
    w.ptw_req_valid = w.tlb.ptw_req_valid;
    w.ptw_req_addr = w.tlb.ptw_req_addr;
  }
  const bool tlb_ready = need_tlb ? w.tlb.req_ready : true;
  const bool tlb_miss = need_tlb ? w.tlb.miss : false;
  w.s1_paddr = s1_paddr;

  // ---- stage 1 tag compare (only when something is in stage 1) ----
  uint8_t s1_hit_way = 0, s1_hit_state = 0;
  const bool s1_meta_clk_en = false;  // set below
  (void)s1_meta_clk_en;
  if (exact || s1_valid || s1_probe_) {
    const uint32_t s1_tag = s1_paddr >> 12;
    const uint32_t* row = tag_[tag_rd_addr_];
    for (unsigned way = 0; way < 4; ++way) {
      const uint32_t m = row[way];
      const uint8_t coh = (m >> 20) & 3;
      if ((m & 0xFFFFF) == s1_tag) { s1_hit_state |= coh; if (coh != 0) s1_hit_way |= 1u << way; }
    }
  }
  w.s1_hit_way = s1_hit_way;
  w.s1_hit_state = s1_hit_state;
  const uint8_t s1_mask_xwr = store_mask(s1_req.size, s1_req.addr);
  w.s1_mask = s1_req.cmd == M_PWR ? in.s1_mask : s1_mask_xwr;

  // ---- stage 2 ----
  const HellaReq& s2_req = s2_req_;
  const bool s2_read = is_read(s2_req.cmd);
  const bool s2_write = is_write(s2_req.cmd);
  const bool s2_readwrite = s2_read || s2_write;
  const bool s2_cmd_flush_line = s2_req.cmd == M_FLUSH_ALL && (s2_req.size & 1);
  const bool xcpt_any = s2_xcpt_reg_ && (s2_tlb_pf_ld_ || s2_tlb_pf_st_ || s2_tlb_ae_ld_ || s2_tlb_ae_st_ || s2_tlb_ma_ld_ || s2_tlb_ma_st_);
  w.xcpt_ma_ld = s2_xcpt_reg_ && s2_tlb_ma_ld_; w.xcpt_ma_st = s2_xcpt_reg_ && s2_tlb_ma_st_;
  w.xcpt_pf_ld = s2_xcpt_reg_ && s2_tlb_pf_ld_; w.xcpt_pf_st = s2_xcpt_reg_ && s2_tlb_pf_st_;
  w.xcpt_ae_ld = s2_xcpt_reg_ && s2_tlb_ae_ld_; w.xcpt_ae_st = s2_xcpt_reg_ && s2_tlb_ae_st_;
  const bool s2_valid_no_xcpt = s2_valid_ && !xcpt_any;
  const bool s2_valid_masked = s2_valid_no_xcpt && s2_not_nacked_in_s1_;
  const bool s2_valid_not_killed = s2_valid_masked && !in.s2_kill;
  const uint64_t s2_vaddr = ((s2_vaddr_r_ >> 12) << 12) | (s2_req.addr & 0xfff);
  const bool s2_hit_valid = s2_hit_state_ != 0;
  bool s2_hit = false; uint8_t s2_grow_param = 0;
  grow_starter(s2_req.cmd, s2_hit_state_, s2_hit, s2_grow_param);
  const uint8_t s2_new_hit_state = s2_grow_param;
  const bool s2_valid_hit_maybe_flush = s2_valid_masked && s2_hit;
  const bool s2_valid_hit_pre = s2_valid_hit_maybe_flush && s2_readwrite;
  const bool s2_valid_flush_line = s2_valid_hit_maybe_flush && s2_cmd_flush_line;
  const bool s2_valid_hit = s2_valid_hit_pre;
  const bool s2_valid_miss = s2_valid_masked && s2_readwrite && !s2_hit;
  const bool s2_uncached = !s2_pma_cacheable_ || (s2_req.no_alloc && !s2_pma_must_alloc_ && !s2_hit_valid);
  const bool s2_valid_cached_miss = s2_valid_miss && !s2_uncached && !uncachedInFlight_;
  const bool s2_want_victimize = s2_valid_cached_miss || s2_valid_flush_line;
  const bool s2_victimize = s2_want_victimize && !in.s2_kill;
  const bool s2_valid_uncached_pending = s2_valid_miss && s2_uncached && !uncachedInFlight_;
  const uint8_t s2_victim_way = static_cast<uint8_t>(1u << (s2_victim_way_r_ & 3));
  const uint8_t s2_victim_or_hit_way = s2_hit_valid ? s2_hit_way_ : s2_victim_way;
  const uint32_t victim_meta = s2_meta_corrected_[s2_victim_way_r_ & 3];
  const uint32_t s2_victim_tag = s2_valid_flush_line ? static_cast<uint32_t>((s2_req.addr >> 12) & 0xFFFFF) : (victim_meta & 0xFFFFF);
  const uint8_t s2_victim_state = s2_hit_valid ? s2_hit_state_ : static_cast<uint8_t>((victim_meta >> 20) & 3);
  bool s2_prb_ack_data = false; uint8_t s2_report_param = 0, probeNewCoh = 0;
  if (s2_probe_ || release_state_ != DC_S_READY) shrink_helper(probe_bits_param_, s2_probe_state_, s2_prb_ack_data, s2_report_param, probeNewCoh);
  bool s2_victim_dirty = false; uint8_t s2_shrink_param = 0, voluntaryNewCoh = 0;
  shrink_helper(P_toN, s2_victim_state, s2_victim_dirty, s2_shrink_param, voluntaryNewCoh);
  const bool s2_update_meta = s2_hit_state_ != s2_new_hit_state;
  const bool s2_dont_nack_uncached = s2_valid_uncached_pending && in.a_ready;
  const bool s2_dont_nack_misc = s2_valid_masked && (s2_req.cmd == M_WOK);
  const bool s2_nack = s2_valid_no_xcpt && !s2_dont_nack_uncached && !s2_dont_nack_misc && !s2_valid_hit;
  w.s2_nack = s2_nack;
  const bool s2_lr = s2_req.cmd == M_XLR;
  const bool s2_sc = s2_req.cmd == M_XSC;
  const bool lrscValid = lrscCount_ > kLrscBackoff;
  const bool lrscBackingOff = lrscCount_ > 0 && !lrscValid;
  const bool s2_sc_fail = s2_sc && !(lrscValid && lrscAddr_ == (s2_req.addr >> 6));
  const bool s2_store_valid = s2_valid_hit && s2_write && !s2_sc_fail && !in.s2_kill;

  // ---- store buffer ----
  const bool pstore1_valid_likely = (s2_valid_ && s2_write) || pstore1_held_;
  const bool pstore1_valid = s2_store_valid || pstore1_held_;
  const bool cpu_likely_needs_read = !(in.req.cmd == M_XWR || in.req.cmd == M_PFW);
  const bool pstore_drain_opportunistic = !(in.req_valid && cpu_likely_needs_read);
  const bool pstore_drain_on_miss = releaseInFlight || pstore_drain_on_miss_reg_;
  const bool pstore_drain_structural = pstore1_valid_likely && pstore2_valid_ && ((s1_valid && s1_write) || pstore1_rmw_);
  auto should_drain = [&](bool truly) {
    const bool k = truly && in.s2_kill;
    const bool not_rmw = ((s2_valid_hit_pre && s2_write && !k) || pstore1_held_);
    return pstore_drain_structural || (((not_rmw && !pstore1_rmw_) || pstore2_valid_) && (pstore_drain_opportunistic || pstore_drain_on_miss));
  };
  const bool pstore_drain = should_drain(true);
  const bool advance_pstore1 = pstore1_valid && (pstore2_valid_ == pstore_drain);
  w.pstore_drain = pstore_drain;
  w.advance_pstore1 = advance_pstore1;
  w.s2_store_valid = s2_store_valid;
  if (advance_pstore1) w.pstore1_storegen_data = amoalu(pstore1_mask_, pstore1_cmd_, s2_data_, pstore1_data_);

  // ---- TileLink D ----
  const uint16_t d_beats1 = d_beats1_of(in.d_opcode, in.d_size);
  const bool d_first = d_counter_ == 0;
  const bool d_last = d_counter_ == 1 || d_beats1 == 0;
  const uint16_t d_count = static_cast<uint16_t>(d_beats1 & ~static_cast<uint16_t>((d_counter_ - 1) & 0x1ff) & 0x1ff);
  const uint8_t d_opc = in.d_opcode;
  const bool grantIsUncached = d_opc == TL_D_ACCESSACKDATA || d_opc == TL_D_ACCESSACK || d_opc == TL_D_HINTACK;
  const bool grantIsUncachedData = d_opc == TL_D_ACCESSACKDATA;
  const bool grantIsCached = d_opc == TL_D_GRANT || d_opc == TL_D_GRANTDATA;
  const bool grantIsVoluntary = d_opc == TL_D_RELEASEACK;
  const bool grantIsRefill = d_opc == TL_D_GRANTDATA;
  const bool canAcceptCachedGrant = !(release_state_ == DC_S_VOLUNTARY_WRITEBACK || release_state_ == DC_S_VOLUNTARY_WRITE_META || release_state_ == DC_S_VOLUNTARY_RELEASE);
  w.grantIsCached = grantIsCached; w.grantIsUncached = grantIsUncached; w.grantIsUncachedData = grantIsUncachedData;
  w.grantIsVoluntary = grantIsVoluntary; w.d_last = d_last;
  const bool uncachedRespSel = in.d_source == 1;
  w.uncachedResp_addr = uncachedRespSel ? uncachedReq_.addr : 0;
  w.uncachedResp_size = uncachedRespSel ? uncachedReq_.size : 0;
  w.uncachedResp_signed = uncachedRespSel ? uncachedReq_.signed_ : false;
  w.uncachedResp_tag = uncachedRespSel ? uncachedReq_.tag : 0;

  // ---- TileLink C and the release state machine ----
  TlC c{};
  c.opcode = TL_C_PROBEACK; c.param = P_NtoN; c.size = probe_bits_size_; c.source = probe_bits_source_;
  c.address = probe_bits_address_; c.data = s2_data_; c.corrupt = false;
  uint8_t newCoh = probeNewCoh;
  uint8_t releaseWay = s2_probe_way_;
  if (s2_probe_ && !s2_prb_ack_data && s2_probe_state_ != 0) { c.opcode = TL_C_PROBEACK; c.param = s2_report_param; }
  if (release_state_ == DC_S_PROBE_REP_CLEAN) { c.opcode = TL_C_PROBEACK; c.param = s2_report_param; }
  if (release_state_ == DC_S_PROBE_REP_DIRTY) { c.opcode = TL_C_PROBEACKDATA; c.param = s2_report_param; }
  const bool voluntary = release_state_ == DC_S_VOLUNTARY_WRITEBACK || release_state_ == DC_S_VOLUNTARY_WRITE_META || release_state_ == DC_S_VOLUNTARY_RELEASE;
  if (voluntary) {
    c.opcode = release_state_ == DC_S_VOLUNTARY_RELEASE ? TL_C_RELEASE : TL_C_RELEASEDATA;
    c.param = s2_shrink_param; c.size = 6;
    newCoh = voluntaryNewCoh;
    releaseWay = s2_victim_or_hit_way;
  }
  const bool c_first = c_counter_ == 0;
  {
    const bool base = s2_release_data_valid_ && !(c_first && release_ack_wait_);
    const bool forced = (s2_probe_ && !s2_prb_ack_data) || release_state_ == DC_S_PROBE_REP_MISS || release_state_ == DC_S_PROBE_REP_CLEAN;
    c.valid = forced || base;
  }
  const bool c_fire = c.valid && in.c_ready;
  const uint16_t c_beats1 = (c.opcode & 1) ? 7 : 0;
  const bool c_last = c_counter_ == 1 || c_beats1 == 0;
  const bool releaseDone = c_last && c_fire;
  const uint16_t c_count = static_cast<uint16_t>(c_beats1 & ~static_cast<uint16_t>((c_counter_ - 1) & 0x1ff) & 0x1ff);
  w.c = c; w.c_fire = c_fire; w.c_first = c_first;
  const bool releaseRejected = s2_release_data_valid_ && !c_fire;
  const uint16_t releaseDataBeat = static_cast<uint16_t>(c_count + (releaseRejected ? 0 : (s1_release_data_valid_ + s2_release_data_valid_)));

  uint8_t next_release_state = release_state_;
  bool release_state_set = false;
  bool probeNack = true;
  bool s1_probe_set = false;
  if (s2_victimize) {
    const bool discard_line = s2_valid_flush_line && ((s2_req.size >> 1) & 1);
    next_release_state = (s2_victim_dirty && !discard_line) ? DC_S_VOLUNTARY_WRITEBACK : DC_S_VOLUNTARY_WRITE_META;
    release_state_set = true;
  }
  if (s2_probe_) {
    if (s2_prb_ack_data) { next_release_state = DC_S_PROBE_REP_DIRTY; release_state_set = true; }
    else if (s2_probe_state_ != 0) { next_release_state = releaseDone ? DC_S_PROBE_WRITE_META : DC_S_PROBE_REP_CLEAN; release_state_set = true; }
    else { probeNack = !releaseDone; next_release_state = releaseDone ? DC_S_READY : DC_S_PROBE_REP_MISS; release_state_set = true; }
  }
  if (release_state_ == DC_S_PROBE_REP_MISS && releaseDone) { next_release_state = DC_S_READY; release_state_set = true; }
  if (release_state_ == DC_S_PROBE_REP_CLEAN && releaseDone) { next_release_state = DC_S_PROBE_WRITE_META; release_state_set = true; }
  if (release_state_ == DC_S_PROBE_REP_DIRTY && releaseDone) { next_release_state = DC_S_PROBE_WRITE_META; release_state_set = true; }
  if (voluntary && releaseDone) { next_release_state = DC_S_VOLUNTARY_WRITE_META; release_state_set = true; }

  // ---- data array arbiter ----
  const bool in0_valid = should_drain(false);
  const uint64_t in0_addr = pstore2_valid_ ? pstore2_addr_ : pstore1_addr_;
  const uint8_t in0_ecc = pstore2_valid_ ? pstore2_storegen_mask_ : pstore1_mask_;
  bool in1_valid = in.d_valid && grantIsRefill && canAcceptCachedGrant;
  bool in1_write = true;
  const bool in1_ready = !in0_valid;
  const bool in2_valid = inWriteback && releaseDataBeat < 8;
  const bool in3_valid = in.req_valid && cpu_likely_needs_read;

  // ---- TileLink D ready / E ----
  bool d_ready = grantIsCached ? ((!d_first || in.e_ready) && canAcceptCachedGrant) : true;
  bool e_valid = in.d_valid && d_first && grantIsCached && canAcceptCachedGrant;
  if (grantIsRefill && !in1_ready) { e_valid = false; d_ready = false; }
  bool cpu_req_ready = (release_state_ == DC_S_READY) && !cached_grant_wait_;
  bool force_in1_read = false;
  if (grantIsUncachedData && (blockUncachedGrant_ || s1_valid)) {
    d_ready = false;
    if (in.d_valid) { cpu_req_ready = false; force_in1_read = true; }
  }
  if (force_in1_read) { in1_valid = true; in1_write = false; }
  const bool in2_ready = !in0_valid && !in1_valid;
  const bool in3_ready = !in0_valid && !in1_valid && !in2_valid;
  const bool data_out_valid = in0_valid || in1_valid || in2_valid || in3_valid;
  w.blockUncachedGrant_next = force_in1_read ? !in1_ready : data_out_valid;
  const bool d_fire = in.d_valid && d_ready;
  const bool d_done = d_last && d_fire;
  w.d_ready = d_ready; w.d_fire = d_fire;
  w.e_valid = e_valid; w.e_sink = in.d_sink;
  const bool replay_next = d_fire && grantIsUncachedData;
  w.replay_next = replay_next;

  w.data_sram_valid = data_out_valid && (in0_valid ? (in0_ecc != 0) : true);
  if (in0_valid) {
    w.data_write = pstore_drain; w.data_row = static_cast<uint16_t>((in0_addr >> 3) & 0x1ff);
    w.data_wdata = pstore2_valid_ ? pstore2_storegen_data_ : pstore1_data_; w.data_eccmask = in0_ecc;
    w.data_way_en = pstore2_valid_ ? pstore2_way_ : pstore1_way_;
  } else if (in1_valid) {
    const uint64_t in1_addr = ((s2_vaddr >> 6) << 6) | (static_cast<uint32_t>(d_count) << 3);
    w.data_write = in1_write; w.data_row = static_cast<uint16_t>((in1_addr >> 3) & 0x1ff);
    w.data_wdata = in.d_data; w.data_eccmask = 0xff; w.data_way_en = refill_way_;
  } else if (in2_valid) {
    w.data_write = false; w.data_row = static_cast<uint16_t>((((probe_bits_address_ >> 6) & 63) << 3) | (releaseDataBeat & 7));
    w.data_eccmask = 0xff; w.data_way_en = 0xf;
  } else {
    w.data_write = false; w.data_row = static_cast<uint16_t>((in.req.addr >> 3) & 0x1ff);
    w.data_eccmask = 0xff; w.data_way_en = 0xf;
  }
  w.data_in2_fire = in2_valid && in2_ready;

  // ---- probes and the metadata arbiter ----
  const bool block_probe_for_core_progress = blockProbeAfterGrantCount_ > 0 || lrscValid;
  const bool block_probe_for_pending_release_ack = release_ack_wait_ && (((in.b_address ^ release_ack_addr_) >> 6) & ((1u << 15) - 1)) == 0;
  const bool block_probe_for_ordering = releaseInFlight || block_probe_for_pending_release_ack || grantInProgress_;
  bool meta6_valid = in.b_valid && (!block_probe_for_core_progress || lrscBackingOff);
  uint8_t meta6_idx = (in.b_address >> 6) & 63;
  uint64_t meta6_addr = ((in.req.addr >> 32) << 32) | in.b_address;
  if (release_state_ == DC_S_PROBE_RETRY) { meta6_valid = true; meta6_idx = (probe_bits_address_ >> 6) & 63; meta6_addr = ((in.req.addr >> 32) << 32) | probe_bits_address_; }
  const bool meta0_valid = resetting_;
  const bool meta2_valid = s2_valid_hit_pre && s2_update_meta;
  const bool meta3_valid = grantIsCached && d_done && !in.d_denied;
  const bool meta4_valid = release_state_ == DC_S_VOLUNTARY_WRITE_META || release_state_ == DC_S_PROBE_WRITE_META;
  const bool meta7_valid = in.req_valid;
  const bool meta_out_ready = clock_en_reg_;
  const bool meta4_ready = !meta0_valid && !meta2_valid && !meta3_valid && meta_out_ready;
  const bool meta6_ready = meta4_ready && !meta4_valid;
  const bool meta7_ready = meta6_ready && !meta6_valid;
  const bool meta_valid = meta0_valid || meta2_valid || meta3_valid || meta4_valid || meta6_valid || meta7_valid;
  bool meta_write = false; uint8_t meta_idx = 0, meta_way_en = 0; uint32_t meta_data = 0; uint64_t meta_addr = in.req.addr & kVaMask40;
  if (meta_valid) {
    const uint32_t meta4_data = meta_pack(c.address >> 12, newCoh);
    if (meta0_valid) { meta_write = true; meta_idx = flushCounter_ & 63; meta_way_en = 0xf; meta_data = 0; meta_addr = ((in.req.addr >> 12) << 12) | (static_cast<uint64_t>(flushCounter_ & 63) << 6); }
    else if (meta2_valid) { meta_write = !in.s2_kill; meta_idx = (s2_vaddr >> 6) & 63; meta_way_en = s2_victim_or_hit_way; meta_data = meta_pack(static_cast<uint32_t>(s2_req.addr >> 12), s2_new_hit_state); meta_addr = ((in.req.addr >> 12) << 12) | (s2_vaddr & 0xfff); }
    else if (meta3_valid) { meta_write = true; meta_idx = (s2_vaddr >> 6) & 63; meta_way_en = refill_way_; meta_data = meta_pack(static_cast<uint32_t>(s2_req.addr >> 12), grow_finisher(s2_req.cmd, in.d_param)); meta_addr = ((in.req.addr >> 12) << 12) | (s2_vaddr & 0xfff); }
    else if (meta4_valid) { meta_write = true; meta_idx = (probe_bits_address_ >> 6) & 63; meta_way_en = releaseWay; meta_data = meta4_data; meta_addr = ((in.req.addr >> 12) << 12) | (probe_bits_address_ & 0xfff); }
    else if (meta6_valid) { meta_write = false; meta_idx = meta6_idx; meta_addr = meta6_addr; }
    else { meta_write = false; meta_idx = (in.req.addr >> 6) & 63; }
  }
  w.meta_valid = meta_valid; w.meta_write = meta_write; w.meta_idx = meta_idx; w.meta_way_en = meta_way_en; w.meta_data = meta_data;
  w.s0_clk_en = meta_valid && !meta_write;
  if (meta4_valid && meta4_ready) { next_release_state = DC_S_READY; release_state_set = true; }
  if (release_state_ == DC_S_PROBE_RETRY && meta6_ready) { next_release_state = DC_S_READY; release_state_set = true; s1_probe_set = true; }
  w.next_release_state = next_release_state;
  w.release_state_set = release_state_set;
  w.s1_probe_set = s1_probe_set;
  const bool b_ready = meta6_ready && !(block_probe_for_core_progress || block_probe_for_ordering || s1_valid || s2_valid_);
  w.b_ready = b_ready;
  w.b_fire = in.b_valid && b_ready;

  // ---- stage 0 ----
  HellaReq s0_req = in.req;
  s0_req.addr = ((meta_addr >> 6) << 6) | (in.req.addr & 63);
  if (!meta7_ready) s0_req.phys = true;
  w.s0_req = s0_req;
  if (!in3_ready && is_read(in.req.cmd)) cpu_req_ready = false;
  if (!meta7_ready) cpu_req_ready = false;
  if (!tlb_ready && !in.ptw.resp_valid && !in.req.phys) cpu_req_ready = false;
  w.s1_did_read_next = in3_ready && (in.req_valid && (is_read(in.req.cmd) || in.req.cmd == M_PWR));

  // ---- stage 1 nack ----
  bool s1_nack = false;
  if (s1_valid && s1_cmd_uses_tlb && tlb_miss) s1_nack = true;
  if (s2_nack || (s2_valid_hit_pre && s2_update_meta)) s1_nack = true;
  bool s1_raw_hazard = false;
  if ((exact || s1_valid) && s1_read && (pstore1_valid_likely || pstore2_valid_)) {
    const uint64_t s1_vaddr = s1_req.addr & kVaMask40;
    auto depends = [&](uint64_t addr, uint8_t mask) { return ((addr >> 3) & 0x1ff) == ((s1_vaddr >> 3) & 0x1ff) && (mask & s1_mask_xwr) != 0; };
    s1_raw_hazard = (pstore1_valid_likely && depends(pstore1_addr_, pstore1_mask_)) || (pstore2_valid_ && depends(pstore2_addr_, pstore2_storegen_mask_));
    if (s1_valid && s1_raw_hazard) s1_nack = true;
  }
  if (s2_probe_ && probeNack) s1_nack = true;
  w.s1_raw_hazard = s1_raw_hazard;
  w.s1_nack = s1_nack;
  cpu_req_ready = cpu_req_ready && !s1_nack;
  w.req_ready = cpu_req_ready;
  const bool s1_valid_not_nacked = s1_valid && !s1_nack;
  w.s1_valid_not_nacked = s1_valid_not_nacked;
  w.s1_meta_clk_en = s1_valid_not_nacked || s1_probe_;
  w.s1_xcpt_valid = tlb_req_valid && !s1_req.no_xcpt && !s1_nack;

  // ---- s2 data capture ----
  {
    const bool en = s1_valid || inWriteback || replay_next;
    const bool word_en = inWriteback ? true : s1_did_read_;
    const bool s1_word_en = !replay_next ? word_en : true;
    uint8_t sel = inWriteback ? releaseWay : s1_hit_way;
    if (d_fire && grantIsUncachedData) sel = 0x10;
    w.s1_data_way_sel = s1_word_en ? sel : 0;
    w.s2_data_en = en;
  }

  // ---- TileLink A ----
  {
    const bool release_ack_conflict = release_ack_wait_ && ((((s2_req.addr ^ release_ack_addr_) >> 6) & ((UINT64_C(1) << 15) - 1)) == 0);
    w.a.valid = !in.s2_kill && (s2_valid_uncached_pending || (s2_valid_cached_miss && !release_ack_conflict && !s2_victim_dirty));
    if (exact || w.a.valid) {
      TlA& a = w.a;
      const uint32_t access_address = static_cast<uint32_t>(s2_req.addr);
      const uint8_t a_size = s2_req.size;
      const uint8_t uncached_source = uncachedInFlight_ ? 0 : 1;
      a.corrupt = false;
      if (!s2_uncached) {
        a.opcode = TL_A_ACQUIRE; a.param = s2_grow_param; a.size = 6; a.source = 0;
        a.address = access_address & ~UINT32_C(63); a.mask = 0xff; a.data = 0;
      } else if (!s2_write) {
        a.opcode = TL_A_GET; a.param = 0; a.size = a_size; a.source = uncached_source; a.address = access_address;
        a.mask = tl_mask(access_address, a_size); a.data = 0;
      } else if (s2_req.cmd == M_PWR) {
        a.opcode = TL_A_PUTPARTIAL; a.param = 0; a.size = a_size; a.source = uncached_source; a.address = access_address;
        a.mask = pstore1_mask_; a.data = pstore1_data_;
      } else if (!s2_read) {
        a.opcode = TL_A_PUTFULL; a.param = 0; a.size = a_size; a.source = uncached_source; a.address = access_address;
        a.mask = tl_mask(access_address, a_size); a.data = pstore1_data_;
      } else {
        a.size = a_size; a.source = uncached_source; a.address = access_address; a.mask = tl_mask(access_address, a_size); a.data = pstore1_data_;
        switch (s2_req.cmd) {
          case M_XA_SWAP: a.opcode = TL_A_LOGICAL; a.param = 3; break;
          case M_XA_XOR: a.opcode = TL_A_LOGICAL; a.param = 0; break;
          case M_XA_OR: a.opcode = TL_A_LOGICAL; a.param = 1; break;
          case M_XA_AND: a.opcode = TL_A_LOGICAL; a.param = 2; break;
          case M_XA_ADD: a.opcode = TL_A_ARITH; a.param = 4; break;
          case M_XA_MIN: a.opcode = TL_A_ARITH; a.param = 0; break;
          case M_XA_MAX: a.opcode = TL_A_ARITH; a.param = 1; break;
          case M_XA_MINU: a.opcode = TL_A_ARITH; a.param = 2; break;
          case M_XA_MAXU: a.opcode = TL_A_ARITH; a.param = 3; break;
          default: { const bool valid = a.valid; a = TlA{}; a.valid = valid; break; }
        }
      }
    }
    w.a_fire = w.a.valid && in.a_ready;
  }

  // ---- CPU response ----
  w.resp_valid = s2_valid_hit_pre || doUncachedResp_;
  if (exact || w.resp_valid) {
    const uint64_t s2_data_word = s2_data_;
    w.resp_addr = doUncachedResp_ ? s2_uncached_resp_addr_ : s2_req.addr;
    w.resp_tag = s2_req.tag; w.resp_cmd = s2_req.cmd; w.resp_size = s2_req.size; w.resp_signed = s2_req.signed_;
    w.resp_has_data = s2_read;
    w.resp_replay = doUncachedResp_;
    w.resp_data = load_gen(s2_req.size, s2_req.signed_, s2_req.addr, s2_data_word, s2_sc, 0) | (s2_sc_fail ? 1 : 0);
    w.resp_data_word_bypass = load_gen(s2_req.size, s2_req.signed_, s2_req.addr, s2_data_word, s2_sc, 2);
    w.resp_data_raw = s2_data_word;
    w.resp_store_data = pstore1_data_;
  }
  w.s2_uncached = s2_uncached && !s2_hit;
  w.s2_uncached_plain = s2_uncached;
  w.s2_paddr = static_cast<uint32_t>(s2_req.addr);
  w.ordered = !((s1_valid && !s1_req.no_xcpt) || (s2_valid_ && !s2_req.no_xcpt) || cached_grant_wait_ || uncachedInFlight_);
  w.perf_grant = in.d_valid && d_last;
  w.perf_release = c_fire && c_last;
  w.perf_acquire = w.a_fire;
  if (!architectural_mode_) {
  w.perf_tlb_miss = w.ptw_req_valid && in.ptw.req_ready;
  w.perf_blocked = cached_grant_wait_ && perf_refill_count_ < 6;
  // eccBytes == 1 makes both WAW hazards identically false in this circuit.
  const bool s1_store = s1_valid && s1_write;
  const bool s2_store = s2_valid_ && s2_write;
  const bool pending_store = s2_store || pstore1_held_;
  w.perf_store_buffer_empty_after_load = !(s1_store || pending_store || pstore2_valid_);
  w.perf_store_buffer_empty_after_store = !(s1_store || (s2_store && pstore1_rmw_) || (pending_store && pstore2_valid_));
  w.perf_can_accept_store_then_load = !((s2_store && pstore1_rmw_ && s1_store) ||
    (pstore2_valid_ && pstore1_valid_likely && s1_store));
  w.perf_can_accept_store_then_rmw = w.perf_can_accept_store_then_load && !pstore2_valid_;
  w.perf_can_accept_load_then_load = !(s1_store && needs_read(s1_req) && (pending_store || pstore2_valid_));
  }

  // stash decisions
  w.s2_valid_masked = s2_valid_masked;
  w.s2_valid_hit = s2_valid_hit;
  w.s2_valid_cached_miss = s2_valid_cached_miss;
  w.s2_victimize = s2_victimize;
  w.s2_hit = s2_hit; w.s2_lr = s2_lr;
  w.s2_victim_or_hit_way = s2_victim_or_hit_way;
  w.s2_victim_tag = s2_victim_tag;
  w.s1_release_data_valid_next = w.data_in2_fire;
  w.s2_release_data_valid_next = s1_release_data_valid_ && !releaseRejected;
  (void)s2_valid_not_killed;
}

void Dcache::commit(const DcacheIn& in, const DcacheWires& w) {
  if (!architectural_mode_ && in.d_valid && w.d_fire && in.d_opcode == TL_D_GRANTDATA) perf_refill_count_ = (perf_refill_count_ + 1) & 7;
  if (in.reset) perf_refill_count_ = 0;
  if (w.idle && (!in.exact_seam || architectural_mode_)) {
    if (architectural_mode_) {
      // The transaction state is quiescent; retain reservation/probe timing
      // without running the TLB, SRAM arbitration or response projection.
      if (lrscCount_ > 0) --lrscCount_;
      if (blockProbeAfterGrantCount_ > 0) --blockProbeAfterGrantCount_;
      blockUncachedGrant_ = false;
      s2_xcpt_reg_ = pstore_drain_on_miss_reg_ = s2_nack_cause_raw_reg_ = false;
      s2_not_nacked_in_s1_ = true;
    }
    clock_en_reg_ = true;
    return;
  }
  const bool s1_valid = s1_valid_;
  const HellaReq s1_req = s1_req_;
  const HellaReq s2_req_old = s2_req_;
  const uint16_t data_rd_addr_old = data_rd_addr_;
  const uint64_t pstore1_addr_old = pstore1_addr_;
  const uint8_t pstore1_way_old = pstore1_way_, pstore1_mask_old = pstore1_mask_;
  const bool pstore2_valid_old = pstore2_valid_, pstore1_held_old = pstore1_held_;
  const uint8_t release_state_old = release_state_;
  const uint32_t probe_bits_address_old = probe_bits_address_;
  const bool resetting_old = resetting_;
  const bool s1_probe_old = s1_probe_;
  const bool s2_valid_not_killed = w.s2_valid_masked && !in.s2_kill;
  const bool lrscValid = lrscCount_ > kLrscBackoff;

  uint32_t s1_meta_row[4];
  if (!architectural_mode_ || w.s1_meta_clk_en)
    std::memcpy(s1_meta_row, tag_[tag_rd_addr_], sizeof s1_meta_row);  // pre-edge tag read data
  if (w.tlb_used) tlb.commit(w.tlb_in, w.tlb);

  // ---- s2 data capture from the pre-edge array contents ----
  if (w.s2_data_en) {
    uint64_t d = 0;
    const unsigned set = data_rd_addr_old >> 3, word = data_rd_addr_old & 7;
    for (unsigned way = 0; way < 4; ++way) {
      if (!((w.s1_data_way_sel >> way) & 1)) continue;
      uint64_t v;
      std::memcpy(&v, &data_[way][set][word * 8], 8);
      d |= v;
    }
    if ((w.s1_data_way_sel >> 4) & 1) d |= in.d_data;
    s2_data_ = d;
  }

  // ---- arrays ----
  if (w.meta_valid) {
    if (w.meta_write) {
      for (unsigned way = 0; way < 4; ++way) if ((w.meta_way_en >> way) & 1) tag_[w.meta_idx][way] = w.meta_data & 0x3FFFFF;
    } else {
      tag_rd_addr_ = w.meta_idx;
    }
  }
  if (w.data_sram_valid) {
    if (w.data_write) {
      const unsigned set = w.data_row >> 3, word = w.data_row & 7;
      for (unsigned way = 0; way < 4; ++way) {
        if (!((w.data_way_en >> way) & 1)) continue;
        uint8_t* p = &data_[way][set][word * 8];
        if (w.data_eccmask == 0xff) { std::memcpy(p, &w.data_wdata, 8); }
        else for (unsigned b = 0; b < 8; ++b) if ((w.data_eccmask >> b) & 1) p[b] = static_cast<uint8_t>(w.data_wdata >> (8 * b));
      }
    } else {
      data_rd_addr_ = w.data_row;
    }
  }

  // ---- stage 1 -> 2 ----
  if (w.s1_valid_not_nacked) {
    s2_req_ = s1_req;
    s2_req_.addr = w.s1_paddr;
    s2_tlb_pf_ld_ = w.tlb.pf_ld; s2_tlb_pf_st_ = w.tlb.pf_st; s2_tlb_ae_ld_ = w.tlb.ae_ld; s2_tlb_ae_st_ = w.tlb.ae_st;
    s2_tlb_ma_ld_ = w.tlb.ma_ld; s2_tlb_ma_st_ = w.tlb.ma_st;
    s2_pma_cacheable_ = w.tlb.cacheable; s2_pma_must_alloc_ = w.tlb.must_alloc;
    s2_vaddr_r_ = s1_req.addr & kVaMask40;
    s2_hit_way_ = w.s1_hit_way;
    s2_hit_state_ = w.s1_hit_state;
    s2_victim_way_r_ = lfsr_ & 3;
  }
  if (w.s1_meta_clk_en) std::memcpy(s2_meta_corrected_, s1_meta_row, sizeof s2_meta_corrected_);
  if (s1_probe_old) { s2_probe_way_ = w.s1_hit_way; s2_probe_state_ = w.s1_hit_state; }
  s2_valid_ = s1_valid && !in.s1_kill && !w.s1_sfence;
  s2_probe_ = s1_probe_old;
  s2_not_nacked_in_s1_ = !w.s1_nack;
  s2_xcpt_reg_ = w.s1_xcpt_valid;
  pstore_drain_on_miss_reg_ = w.s2_nack;
  s2_nack_cause_raw_reg_ = w.s1_raw_hazard;

  // ---- lrsc ----
  {
    uint8_t cnt = lrscCount_;
    if (((w.s2_valid_hit && w.s2_lr && !cached_grant_wait_) || w.s2_valid_cached_miss) && !in.s2_kill) {
      cnt = w.s2_hit ? (kLrscCycles - 1) : 0;
      lrscAddr_ = s2_req_old.addr >> 6;
    }
    if (lrscCount_ > 0) cnt = lrscCount_ - 1;
    if (s2_valid_not_killed && lrscValid) cnt = kLrscBackoff;
    if (s1_probe_old) cnt = 0;
    lrscCount_ = cnt & 0x7f;
  }

  // ---- store buffer ----
  if (w.s1_valid_not_nacked && w.s1_write) {
    pstore1_cmd_ = s1_req.cmd;
    pstore1_addr_ = s1_req.addr & kVaMask40;
    pstore1_data_ = in.s1_data;
    pstore1_way_ = w.s1_hit_way;
    pstore1_mask_ = w.s1_mask;
    pstore1_rmw_ = is_read(s1_req.cmd) || s1_req.cmd == M_PWR;
  }
  pstore1_held_ = (w.s2_store_valid || pstore1_held_old) && pstore2_valid_old && !w.pstore_drain;
  pstore2_valid_ = (pstore2_valid_old && !w.pstore_drain) || w.advance_pstore1;
  if (w.advance_pstore1) {
    pstore2_addr_ = pstore1_addr_old;
    pstore2_way_ = pstore1_way_old;
    pstore2_storegen_data_ = w.pstore1_storegen_data;
    pstore2_storegen_mask_ = pstore1_mask_old;
  }

  // ---- TileLink A fire ----
  if (w.a_fire) {
    if (w.s2_uncached_plain) {
      uncachedInFlight_ = true;
      uncachedReq_ = s2_req_old;
      uncachedReq_.cmd = is_write(s2_req_old.cmd) ? (s2_req_old.cmd == M_PWR ? M_PWR : M_XWR) : M_XRD;
    } else {
      cached_grant_wait_ = true;
      refill_way_ = w.s2_victim_or_hit_way;
    }
  }

  // ---- TileLink D fire ----
  if (blockProbeAfterGrantCount_ > 0) --blockProbeAfterGrantCount_;
  if (w.d_fire) {
    if (w.grantIsCached) {
      grantInProgress_ = true;
      if (w.d_last) {
        cached_grant_wait_ = false;
        grantInProgress_ = false;
        blockProbeAfterGrantCount_ = kBlockProbeAfterGrantCycles - 1;
        const unsigned fb = ((lfsr_ >> 15) ^ (lfsr_ >> 13) ^ (lfsr_ >> 12) ^ (lfsr_ >> 10)) & 1;
        lfsr_ = static_cast<uint16_t>(((lfsr_ << 1) | fb) & 0xffff);
      }
    } else if (w.grantIsUncached) {
      if (in.d_source == 1 && w.d_last) uncachedInFlight_ = false;
      if (w.grantIsUncachedData) {
        s2_req_.cmd = M_XRD;
        s2_req_.size = w.uncachedResp_size;
        s2_req_.signed_ = w.uncachedResp_signed;
        s2_req_.tag = w.uncachedResp_tag;
        s2_req_.addr = ((static_cast<uint64_t>(w.s1_paddr) >> 3) << 3) | (w.uncachedResp_addr & 7);
        s2_uncached_resp_addr_ = w.uncachedResp_addr;
      }
    } else if (w.grantIsVoluntary) {
      release_ack_wait_ = false;
    }
    const uint16_t beats1 = d_beats1_of(in.d_opcode, in.d_size);
    d_counter_ = static_cast<uint16_t>((d_counter_ == 0 ? beats1 : d_counter_ - 1) & 0x1ff);
  }
  blockUncachedGrant_ = w.blockUncachedGrant_next;
  doUncachedResp_ = w.replay_next;
  if (w.replay_next) s2_uncached_data_word_ = in.d_data;
  if (w.c_fire) {
    const uint16_t beats1 = (w.c.opcode & 1) ? 7 : 0;
    c_counter_ = static_cast<uint16_t>((c_counter_ == 0 ? beats1 : c_counter_ - 1) & 0x1ff);
  }

  // ---- release / probe state ----
  s1_release_data_valid_ = w.s1_release_data_valid_next;
  s2_release_data_valid_ = w.s2_release_data_valid_next;
  if (w.b_fire) {
    probe_bits_address_ = in.b_address;
    probe_bits_param_ = in.b_param;
    probe_bits_size_ = in.b_size;
    probe_bits_source_ = in.b_source;
  }
  if (w.s2_victimize) {
    probe_bits_address_ = (static_cast<uint32_t>(w.s2_victim_tag) << 12) | (static_cast<uint32_t>(s2_req_old.addr) & 0xfc0);
    probe_bits_source_ = 0;
    probe_bits_param_ = 0;
    probe_bits_size_ = 0;
  }
  if (w.release_state_set) release_state_ = w.next_release_state;
  const bool voluntary_old = release_state_old == DC_S_VOLUNTARY_WRITEBACK || release_state_old == DC_S_VOLUNTARY_WRITE_META || release_state_old == DC_S_VOLUNTARY_RELEASE;
  if (voluntary_old && w.c_fire && w.c_first) { release_ack_wait_ = true; release_ack_addr_ = probe_bits_address_old; }
  s1_probe_ = w.b_fire || w.s1_probe_set;

  // ---- stage 0 -> 1 ----
  if (w.s0_clk_en) {
    s1_req_ = w.s0_req;
    s1_did_read_ = w.s1_did_read_next;
    s1_tlb_req_vaddr_ = w.s0_req.addr & kVaMask40;
    s1_tlb_req_passthrough_ = w.s0_req.phys;
    s1_tlb_req_size_ = w.s0_req.size;
    s1_tlb_req_cmd_ = w.s0_req.cmd;
  }
  s1_valid_ = in.req_valid && w.req_ready;

  // ---- reset sweep ----
  if (reset_next_) resetting_ = true;
  if (resetting_old) {
    const unsigned next = flushCounter_ + 1;
    flushCounter_ = static_cast<uint8_t>(next & 0xff);
    if ((next >> 6) == 4) resetting_ = false;
  }
  reset_next_ = in.reset;
  clock_en_reg_ = true;

  if (in.reset) {
    s1_valid_ = false; s1_probe_ = false; cached_grant_wait_ = false; resetting_ = false;
    flushCounter_ = 192; release_ack_wait_ = false; release_state_ = DC_S_READY; uncachedInFlight_ = false;
    s2_valid_ = false; s2_probe_ = false; lrscCount_ = 0; pstore2_valid_ = false; pstore1_held_ = false;
    d_counter_ = 0; c_counter_ = 0; grantInProgress_ = false; blockProbeAfterGrantCount_ = 0; lfsr_ = 1;
  }
}

}  // namespace chisa::rocket_model
