// model core: LSU (lsu.scala) over bit-column LDQ/STQ state.  The STQ
// address/data registers are the image fields; every other column is
// private and the RTL bank words are regenerated at the end of a step in
// which the queue changed.
#include <cstdio>
#include <cstdlib>
#include "core.h"
#include "env_knob.h"

namespace chisa::boom_model {

uint64_t decode_imm(const MicroOp& u);

namespace {
inline uint8_t byte_mask(uint64_t addr, uint8_t size) {
  return static_cast<uint8_t>(((1u << (1u << (size & 3u))) - 1u) << (addr & 7));
}
inline uint8_t bit8(int i) { return static_cast<uint8_t>(1u << i); }
}  // namespace

MemUop Core::ldq_uop(int idx) const {
  idx = ldq_wrap(idx);
  MemUop m = MemUop::from(inst_[lsq_.ld_rob[idx]], lsq_.ld_brmask[idx]);
  m.pdst = lsq_.ld_pdst[idx];
  m.exception = (lsq_.ld_exc >> idx) & 1u;
  return m;
}
MemUop Core::stq_uop(int idx) const {
  idx = stq_wrap(idx);
  MemUop m = MemUop::from_stq(lsq_.st_word[idx]);
  return m;
}

// Dispatch allocation (lsu.scala:305-345): only these fields are written;
// the address/forward payload registers hold.
void Core::lsq_dispatch(const MicroOp& du) {
  const bool dis_ld = du.uses_ldq && !du.exception;
  const bool dis_st = du.uses_stq && !du.exception;
  if (dis_ld) {
    const int i = lsq_.ldq_tail;
    const uint8_t b = bit8(i);
    lsq_.ld_valid |= b;
    lsq_.ld_addr_valid &= ~b; lsq_.ld_executed &= ~b; lsq_.ld_succeeded &= ~b;
    lsq_.ld_order_fail &= ~b; lsq_.ld_observed &= ~b; lsq_.ld_fwd_std_val &= ~b;
    lsq_.ld_exc = static_cast<uint8_t>((lsq_.ld_exc & ~b) | (du.exception ? b : 0));
    lsq_.ld_rob[i] = du.rob_idx;
    lsq_.ld_pdst[i] = du.pdst;
    lsq_.ld_brmask[i] = du.br_mask;
    lsq_.ld_youngest[i] = static_cast<uint8_t>(lsq_.stq_tail);
    lsq_.ld_stdep[i] = lsq_.live_store_mask;
    lsq_.ldq_tail = ldq_wrap(lsq_.ldq_tail + 1);
    ldq_dirty_ = true;
  } else if (dis_st) {
    const int i = lsq_.stq_tail;
    const uint8_t b = bit8(i);
    lsq_.st_valid |= b;
    lsq_.st_addr_valid &= ~b; lsq_.st_data_valid &= ~b;
    lsq_.st_committed &= ~b; lsq_.st_succeeded &= ~b;
    lsq_.st_word[i] = StqWord::make(du);
    lsq_.live_store_mask |= b;
    lsq_.stq_tail = stq_wrap(lsq_.stq_tail + 1);
    stq_dirty_ = true;
  }
}

boom_lsu::Candidates Core::lsu_schedule_candidates(const LsuScheduleInputs& input) const {
  boom_lsu::Candidates c;
  const StageUop& incoming = mem_agu_.u;
  br_mask_t b1_kill_mask = 0;
  if (br_pipe[2].v && br_pipe[2].mispredict) b1_kill_mask = static_cast<br_mask_t>(1u << br_pipe[2].tag);
  const auto survives = [&](br_mask_t mask) { return !redirect_pending && (mask & b1_kill_mask) == 0; };
  const bool incoming_valid = mem_agu_.v && survives(incoming.br_mask);
  c.load_incoming = incoming_valid && incoming.is_load();
  c.stad_incoming = incoming_valid && incoming.is_sta() && incoming.is_std();
  c.sta_incoming = incoming_valid && incoming.is_sta() && !incoming.is_std();
  c.std_incoming = incoming_valid && incoming.is_std() && !incoming.is_sta();
  c.sfence = incoming_valid && incoming.mem_cmd == 20;
  c.release = input.dmem_release_valid;
  c.hella_incoming = input.hella_incoming;
  c.hella_wakeup = input.hella_wakeup;

  const int oh = stq_wrap(lsq_.stq_head);
  const uint64_t ohw = lsq_.st_word[oh];
  const bool needs_order = boom_lsu::store_needs_order(
      (lsq_.st_valid >> oh) & 1u, (lsq_.st_committed >> oh) & 1u, StqWord::is_fence(ohw), input.dmem_ordered);

  const unsigned rl = ldq_wrap(ldq_retry_idx_);
  c.load_retry = ((lsq_.ld_valid >> rl) & 1u) && ((lsq_.ld_addr_valid >> rl) & 1u) &&
                 ((lsq_.ld_virtual >> rl) & 1u) &&
                 ((ldq_block_p1_ >> rl) & 1u) == 0 && ((ldq_block_p2_ >> rl) & 1u) == 0 &&
                 input.dtlb_miss_ready_registered && !needs_order &&
                 !((lsq_.ld_order_fail >> rl) & 1u);
  const unsigned rs = stq_wrap(stq_retry_idx_);
  c.sta_retry = ((lsq_.st_valid >> rs) & 1u) && ((lsq_.st_addr_valid >> rs) & 1u) &&
                ((lsq_.st_virtual >> rs) & 1u) && input.dtlb_miss_ready_registered;

  const unsigned wl = ldq_wrap(ldq_wakeup_idx_);
  const bool block_wakeup = store_blocked_counter_ == 15 || block_wakeup_next_ || needs_order;
  c.load_wakeup = ((lsq_.ld_valid >> wl) & 1u) && ((lsq_.ld_addr_valid >> wl) & 1u) &&
                  !((lsq_.ld_executed >> wl) & 1u) && !((lsq_.ld_succeeded >> wl) & 1u) &&
                  !((lsq_.ld_virtual >> wl) & 1u) && !((lsq_.ld_order_fail >> wl) & 1u) &&
                  ((ldq_block_p1_ >> wl) & 1u) == 0 && ((ldq_block_p2_ >> wl) & 1u) == 0 && !block_wakeup &&
                  (!((lsq_.ld_uncacheable >> wl) & 1u) ||
                   (commit_load_at_rob_head_ && wl == static_cast<unsigned>(lsq_.ldq_head) &&
                    lsq_.ld_stdep[wl] == 0));

  const int se = stq_wrap(lsq_.stq_execute_head);
  const uint64_t sew = lsq_.st_word[se];
  const bool sv = (lsq_.st_valid >> se) & 1u;
  c.store_commit = sv && !StqWord::is_fence(sew) && survives(StqWord::br_mask(sew)) &&
                   !mem_xcpt_.v && !StqWord::exception(sew) &&
                   (((lsq_.st_committed >> se) & 1u) ||
                    (StqWord::is_amo(sew) && ((lsq_.st_addr_valid >> se) & 1u) &&
                     !((lsq_.st_virtual >> se) & 1u) && ((lsq_.st_data_valid >> se) & 1u)));
  return c;
}

namespace {
struct LsuScheduleMemo {
  const void* owner = nullptr;
  uint64_t cycle = 0;
  LsuScheduleInputs in{};
  boom_lsu::Schedule out{};
  bool valid = false;
};
thread_local LsuScheduleMemo g_memo;
}  // namespace

boom_lsu::Schedule Core::compute_lsu_schedule(const LsuScheduleInputs& input) const {
  LsuScheduleMemo& m = g_memo;
  if (m.valid && m.owner == this && m.cycle == sched_epoch_ &&
      m.in.dmem_release_valid == input.dmem_release_valid &&
      m.in.hella_incoming == input.hella_incoming && m.in.hella_wakeup == input.hella_wakeup &&
      m.in.dtlb_miss_ready_registered == input.dtlb_miss_ready_registered &&
      m.in.dmem_ordered == input.dmem_ordered)
    return m.out;
  m.out = boom_lsu::schedule(lsu_schedule_candidates(input));
  m.in = input; m.owner = this; m.cycle = sched_epoch_; m.valid = true;
  return m.out;
}

DtlbLookupCandidate Core::dtlb_lookup_candidate(const boom_lsu::Schedule& s) const {
  DtlbLookupCandidate r;
  if (s.load_incoming || s.stad_incoming || s.sta_incoming || s.sfence) {
    const MicroOp& u = inst(mem_agu_.u);
    r.valid = true;
    r.vaddr = s.sfence ? mem_agu_rs1_ : mem_agu_rs1_ + decode_imm(u);
    r.size = u.mem_size; r.cmd = u.mem_cmd;
  } else if (s.load_retry) {
    const int i = ldq_wrap(ldq_retry_idx_);
    const MicroOp& u = inst_[lsq_.ld_rob[i]];
    r.valid = true; r.vaddr = lsq_.ld_addr[i]; r.size = u.mem_size; r.cmd = u.mem_cmd;
  } else if (s.sta_retry) {
    const int i = stq_wrap(stq_retry_idx_);
    r.valid = true; r.vaddr = img_->r.lsu.stq_bits_addr_bits[i];
    r.size = StqWord::mem_size(lsq_.st_word[i]); r.cmd = StqWord::mem_cmd(lsq_.st_word[i]);
  }
  return r;
}

// --------------------------------------------------------------------------
void Core::lsu_step() {
  auto& L = img_->r.lsu;
  XcptRec mem_xcpt_pre;
  if (kInternalSignalContract || mem_xcpt_.v) mem_xcpt_pre = mem_xcpt_;
  const br_mask_t mem_xcpt_brmask_pre = mem_xcpt_brmask_s_;
  const uint8_t ldq_retry_idx_pre = ldq_retry_idx_;
  const uint8_t stq_retry_idx_pre = stq_retry_idx_;
  const uint8_t ldq_wakeup_idx_pre = ldq_wakeup_idx_;
  const uint64_t* st_addr = L.stq_bits_addr_bits;
  uint64_t* st_data = L.stq_bits_data_bits;

  // stdf_clr_bsy register (FP store data): one edge after fired_stdf.
  stdf_clr_bsy_r_.v = fp_stdata_fire_s1_v_ && fp_stdata_stq_qual_start_ && !fp_stdata_fire_s1_killed_now_;
  stdf_clr_bsy_r_.rob = fp_stdata_fire_s1_v_ ? fp_stdata_fire_s1_rob_ : 0;
  stdf_clr_bsy_r_.br_mask = fp_stdata_fire_s1_v_ ? fp_stdata_fire_s1_brmask_ : 0;

  // Consume the PRE-edge exception conveyor (raw payload write, not valid-gated).
  if (mem_xcpt_.v) {
    if (mem_xcpt_.uses_ldq) { lsq_.ld_exc |= bit8(ldq_wrap(mem_xcpt_.ldq_idx)); }
    else { const int si = stq_wrap(mem_xcpt_.stq_idx); lsq_.st_word[si] = StqWord::set_exception(lsq_.st_word[si]); stq_dirty_ = true; }
  }

  const lsq_mask_t nacking_loads_now =
      (dmem_resp_nack && dmem_nack_uses_ldq) ? bit8(ldq_wrap(dmem_nack_ldq_idx)) : 0;
  out_dmem_release_ready = 0;

  if (release_search_s1_) {
    for (unsigned slots = ld_valid_s_ & ld_addr_valid_s_; slots; slots &= slots - 1u) {
      const unsigned i = __builtin_ctz(slots);
      if ((lsq_.ld_addr[i] >> 6) == (release_address_s1_ >> 6)) {
        lsq_.ld_observed |= bit8(i);
        ldq_dirty_ = true;
      }
    }
  }

  const bool memory_resp_fires = dmem_resp_valid &&
      (dmem_resp_uop_valid
          ? (dmem_resp_uop.uses_ldq || dmem_resp_uop.is_amo)
          : dmem_pending.valid && !dmem_pending_kill_ &&
              (dmem_pending.uop.uses_ldq || dmem_pending.uop.is_amo));
  wb_fwd_ldq_r_ = 0;
  wb_fwd_stq_r_ = 0;

  // Forwarded-load writeback scheduled by last cycle's s1 pick (s2).
  const FwdWb fwd_now = fwd_wb_;
  fwd_wb_.v = false;
  if (fwd_now.v && !memory_resp_fires) {
    const int li = ldq_wrap(fwd_now.ldq_idx), si = stq_wrap(fwd_now.stq_idx);
    if (((lsq_.ld_valid >> li) & 1u) && ((lsq_.st_valid >> si) & 1u) && ((lsq_.st_data_valid >> si) & 1u)) {
      const uint8_t rob = lsq_.ld_rob[li];
      const MicroOp& mu = inst_[rob];
      const uint64_t d = fwd_extract(lsq_.ld_addr[li], mu.mem_size, mu.mem_signed,
                                     StqWord::mem_size(lsq_.st_word[si]), st_data[si]);
      const uint8_t pdst = lsq_.ld_pdst[li];
      if (mu.dst_rtype == RT_FLT) {
        rob_read_bsy_now_[2] = (rob_busy_ >> rob) & 1u;
        rob_read_uop_packed_now_[2] = uop_packed_[rob];
        rob_busy_ &= ~(1u << rob); rob_unsafe_ &= ~(1u << rob);
        fp_ll_ld_v_ = true; fp_ll_ld_uop_ = ldq_uop(li); fp_ll_ld_data_ = d;
        fp_ll_now_v_ = true; fp_ll_now_rob_ = rob;
      } else {
        rob_read_port(0, rob, (rob_busy_start_ >> rob) & 1u);
        rob_busy_ &= ~(1u << rob); rob_unsafe_ &= ~(1u << rob);
        busy_ &= ~boomcfg::pm_bit(pdst);
        iq_wake(int_iq_, pdst);
        iq_wake(mem_iq_, pdst);
        if (pdst != 0) prf_.wr(pdst, d);
        out_ext_irf_write_valids[0] = 1;
        ll_now_v_ = true; ll_now_rob_ = rob;
        out_ext_irf_write_addrs[0] = pdst;
        out_ext_irf_write_datas[0] = d;
        prf_landed.wr(pdst, d);
      }
      lsq_.ld_succeeded |= bit8(li);
      lsq_.ld_fwd_std_val |= bit8(li);
      lsq_.ld_fwd_stq[li] = fwd_now.stq_idx;
      ldq_dirty_ = true;
    }
  }

  const bool dmem_port_free = dmem_req_ready && (dmem_pipelined_ || !dmem_pending.valid);
  const DmemPending dmem_out = dmem_pending;

  // (1) LCAM searches over the pre-edge LDQ/STQ face.
  bool lcam_match_nofwd = false;
  lsq_mask_t failed_load_mask = 0;
  const uint8_t ld_search_face = ld_valid_s_ & ld_addr_valid_s_ & static_cast<uint8_t>(~ld_virtual_s_);

  if (lcam_store_search_s1_) {
    const int sidx = stq_wrap(lcam_store_stq_s1_);
    const uint8_t store_mask = byte_mask(lcam_store_addr_s1_, lcam_store_size_s1_);
    for (uint8_t m = ld_search_face; m != 0; m &= static_cast<uint8_t>(m - 1)) {
      const int i = __builtin_ctz(m);
      const bool forwarding_now = fwd_now.v && ldq_wrap(fwd_now.ldq_idx) == i;
      if (!((lsq_.ld_stdep[i] >> sidx) & 1u)) continue;
      if (!(((ld_exsucc_s_ >> i) & 1u) || forwarding_now)) continue;
      if ((lsq_.ld_addr[i] >> 3) != (lcam_store_addr_s1_ >> 3)) continue;
      if ((byte_mask(lsq_.ld_addr[i], inst_[lsq_.ld_rob[i]].mem_size) & store_mask) == 0) continue;
      const uint8_t forwarded_stq = forwarding_now ? fwd_now.stq_idx : lsq_.ld_fwd_stq[i];
      const bool forwarded_is_older = lsq_is_older(forwarded_stq, sidx, lsq_.ld_youngest[i]);
      if (!((ld_fwd_std_val_s_ >> i) & 1u) || (forwarded_stq != sidx && forwarded_is_older)) {
        lsq_.ld_order_fail |= bit8(i);
        failed_load_mask |= bit8(i);
        ldq_dirty_ = true;
      }
    }
  }

  if (lcam_ldq_s1_ >= 0) {
    const int sidx = ldq_wrap(lcam_ldq_s1_);
    bool set_execute = lcam_fired_s1_;
    if (lcam_incoming_s1_ || fired_load_wakeup_r_) {
      const uint64_t saddr = lsq_.ld_addr[sidx];
      const uint8_t ssize = inst_[lsq_.ld_rob[sidx]].mem_size;
      const uint8_t lmask = byte_mask(saddr, ssize);
      bool ldq_kill = false;
      for (uint8_t m = ld_search_face & static_cast<uint8_t>(~bit8(sidx)); m != 0; m &= static_cast<uint8_t>(m - 1)) {
        const int i = __builtin_ctz(m);
        if ((lsq_.ld_addr[i] >> 3) != (saddr >> 3)) continue;
        if ((lmask & byte_mask(lsq_.ld_addr[i], inst_[lsq_.ld_rob[i]].mem_size)) == 0) continue;
        if (lsq_is_older(sidx, i, ldq_head_s_)) continue;
        if (!((ld_exsucc_s_ >> i) & 1u) || (((nacking_loads_now | nacking_loads_prev_) >> i) & 1u))
          ldq_kill = true;
      }
      bool match_any = false, fwd_ok = false;
      int fwd_idx = -1;
      const uint8_t dep = lsq_.ld_stdep[sidx];
      std::uint8_t candidates = stq_age_order(dep & st_valid_s_, lsq_.ld_youngest[sidx]);
      while (candidates) {
        const int i = static_cast<int>(stq_age_pop(candidates, lsq_.ld_youngest[sidx]));
        const uint64_t w = lsq_.st_word[i];
        if (StqWord::is_fence(w) || StqWord::is_amo(w)) { match_any = true; break; }
        if (!((st_addr_valid_s_ >> i) & 1u) || ((st_virtual_s_ >> i) & 1u)) continue;
        if ((st_addr[i] >> 3) != (saddr >> 3)) continue;
        const uint8_t wmask = byte_mask(st_addr[i], StqWord::mem_size(w));
        if ((lmask & wmask) == 0) continue;
        match_any = true;
        if ((lmask & wmask) == lmask) { fwd_ok = true; fwd_idx = i; }
        break;
      }
      if (ldq_kill) fwd_ok = false;
      if (lcam_incoming_s1_ ? mem_tlb_uncacheable_for_lcam : ((ld_uncacheable_s_ >> sidx) & 1u)) fwd_ok = false;
      if ((ldq_b1_killed_now_ >> sidx) & 1u) fwd_ok = false;
      wb_fwd_ldq_r_ = static_cast<uint8_t>(sidx);
      if (fwd_idx >= 0) wb_fwd_stq_r_ = static_cast<uint8_t>(fwd_idx);
      if (match_any || ldq_kill) {
        set_execute = false;
        if (lcam_fired_s1_ && dmem_pending.valid && dmem_pending.uop.uses_ldq &&
            ldq_wrap(dmem_pending.uop.ldq_idx) == sidx)
          dmem_pending_kill_ = true;
        if (fwd_ok) fwd_wb_ = FwdWb{true, static_cast<uint8_t>(sidx), static_cast<uint8_t>(fwd_idx)};
      }
      lcam_match_nofwd = match_any && !fwd_ok;
    }
    if (set_execute) { lsq_.ld_executed |= bit8(sidx); ldq_dirty_ = true; }
  }

  int stq_nack_rewind = -1;
  if (dmem_resp_nack) {
    if (dmem_nack_uses_ldq) {
      lsq_.ld_executed &= static_cast<uint8_t>(~bit8(ldq_wrap(dmem_nack_ldq_idx)));
      ldq_dirty_ = true;
    } else if (dmem_nack_uses_stq) {
      const int idx = stq_wrap(dmem_nack_stq_idx);
      if (lsq_is_older(idx, lsq_.stq_execute_head, lsq_.stq_head)) stq_nack_rewind = idx;
    }
    if (!dmem_pipelined_) { dmem_pending.valid = false; dmem_pending_kill_ = false; }
  }

  // (2) D-cache response.
  const bool untagged_response_valid = dmem_pending.valid && !dmem_pending_kill_;
  if (dmem_resp_valid && (dmem_resp_uop_valid || untagged_response_valid)) {
    const MemUop& mu = dmem_resp_uop_valid ? dmem_resp_uop : dmem_pending.uop;
    if (mu.uses_ldq && mu.dst_rtype == RT_FLT) {
      fp_ll_rob_r_ = mu.rob;
      rob_read_bsy_now_[2] = (rob_busy_ >> mu.rob) & 1u;
      rob_read_uop_packed_now_[2] = uop_packed_[mu.rob];
      rob_busy_ &= ~(1u << mu.rob); rob_unsafe_ &= ~(1u << mu.rob);
      fp_ll_ld_v_ = true; fp_ll_ld_uop_ = mu; fp_ll_ld_data_ = dmem_resp_data;
      fp_ll_now_v_ = true; fp_ll_now_rob_ = mu.rob;
      lsq_.ld_succeeded |= bit8(ldq_wrap(mu.ldq_idx));
      ldq_dirty_ = true;
      if (!dmem_resp_uop_valid) dmem_pending.valid = false;
    } else {
      // AMOs live in the STQ but return an integer result through ll_wbarb.
      // core.scala qualifies ROB writeback with !(uses_stq && !is_amo), so
      // treating every STQ response as an ordinary store loses the writeback
      // (and exposes the wrong asynchronous ROB row at this very cycle).
      if (mu.uses_ldq || mu.is_amo) {
        rob_read_port(0, mu.rob, (rob_busy_start_ >> mu.rob) & 1u);
        rob_busy_ &= ~(1u << mu.rob); rob_unsafe_ &= ~(1u << mu.rob);
        busy_ &= ~boomcfg::pm_bit(mu.pdst);
        iq_wake(int_iq_, mu.pdst);
        iq_wake(mem_iq_, mu.pdst);
        if (mu.pdst != 0) prf_.wr(mu.pdst, dmem_resp_data);
        out_ext_irf_write_valids[0] = 1;
        ll_now_v_ = true; ll_now_rob_ = mu.rob;
        out_ext_irf_write_addrs[0] = mu.pdst;
        out_ext_irf_write_datas[0] = dmem_resp_data;
        prf_landed.wr(mu.pdst, dmem_resp_data);
        if (mu.uses_ldq) {
          lsq_.ld_succeeded |= bit8(ldq_wrap(mu.ldq_idx));
          ldq_dirty_ = true;
        }
      }
      if (mu.uses_stq) {
        lsq_.st_succeeded |= bit8(stq_wrap(mu.stq_idx));
        stq_dirty_ = true;
      }
      if (!dmem_resp_uop_valid) dmem_pending.valid = false;
    }
  }

  // (3) Adapter output.
  out_dmem_s1_kill = dmem_pending_kill_ ? 1 : 0;
  if (dmem_pending_kill_) { dmem_pending.valid = false; dmem_pending_kill_ = false; }
  else if (dmem_pipelined_) dmem_pending.valid = false;
  (void)dmem_out;

  // (4) AGU cycle.
  int8_t fired_ldq = -1, attempt_ldq = -1;
  ClrBsy store_completed{};
  lsq_mask_t ldq_block_now = 0;
  bool tlb_load_search_now = false, tlb_store_search_now = false;
  uint8_t tlb_store_search_idx = 0, tlb_store_search_size = 0;
  uint64_t tlb_store_search_addr = 0;
  ldq_block_now_r_ = 0;
  const boom_lsu::Schedule& S = sched_s_;
  const bool incoming_load = S.load_incoming;
  const bool incoming_stad = S.stad_incoming;
  const bool incoming_sta_only = S.sta_incoming;
  const bool incoming_std_only = S.std_incoming;
  const bool incoming_sfence = S.sfence;
  const bool incoming_sta = incoming_stad || incoming_sta_only;
  const bool release_fire = S.release;
  out_dmem_release_ready = release_fire ? 1 : 0;
  canfire_load_incoming_ = incoming_load;
  mem_attempt_v = false; mem_attempt_addr = 0; mem_attempt_data = 0;
  mem_paddr_r_ = 0;
  if (incoming_load || incoming_sta || incoming_std_only || incoming_sfence) {
    // cycle-start payload/operands; the br_mask is the GetNewBrMask'd one.
    const StageUop& us = mem_agu_s_.u;
    const MicroOp& u = inst(us);
    const br_mask_t ubr = mem_agu_.u.br_mask;
    const bool incoming_killed = mem_agu_killed_;
    const uint64_t vaddr = mem_agu_rs1_s_ + decode_imm(u);
    const bool has_tlb_request = us.is_load() || us.is_sta();
    const bool tlb_miss = has_tlb_request && !dtlb_passthrough && dtlb_resp_miss;
    const uint64_t paddr = dtlb_passthrough ? vaddr : dtlb_resp_paddr;
    const bool uncacheable = has_tlb_request && !dtlb_passthrough && !tlb_miss && dtlb_resp_uncacheable;
    const uint64_t addr = tlb_miss ? vaddr : paddr;
    if (incoming_sfence) {
      store_completed = ClrBsy{true, us.rob, ubr};
    } else if (incoming_load) {
      mem_paddr_r_ = paddr;
      const int idx = ldq_wrap(us.ldq_idx);
      const uint8_t b = bit8(idx);
      lsq_.ld_addr_valid = static_cast<uint8_t>((lsq_.ld_addr_valid & ~b) | (incoming_killed ? 0 : b));
      lsq_.ld_addr[idx] = addr & kPc40;
      lsq_.ld_virtual = static_cast<uint8_t>((lsq_.ld_virtual & ~b) | (tlb_miss ? b : 0));
      lsq_.ld_uncacheable = static_cast<uint8_t>((lsq_.ld_uncacheable & ~b) | (uncacheable ? b : 0));
      ldq_dirty_ = true;
      ldq_block_now |= b;
      attempt_ldq = static_cast<int8_t>(idx);
      tlb_load_search_now = !tlb_miss && !incoming_killed;
      const bool dmem_req_valid = !tlb_miss && !uncacheable;
      if (dmem_req_valid) {
        mem_attempt_v = true;
        mem_attempt_uop = MemUop::from(u, mem_agu_s_.u.br_mask);  // request: pre-edge mask
        mem_attempt_addr = paddr;
      }
      if (dmem_req_valid && dmem_port_free) {
        dmem_pending.valid = true;
        dmem_pending.uop = MemUop::from(u, mem_agu_s_.u.br_mask);
        dmem_pending.addr = paddr;
        dmem_pending.data = 0;
        dmem_req_fired_now = true;
        dmem_req_mask_now = ubr;
        fired_ldq = static_cast<int8_t>(idx);
      }
    } else if (incoming_sta || incoming_std_only) {
      const int idx = stq_wrap(us.stq_idx);
      const uint8_t b = bit8(idx);
      store_completed.rob = us.rob;
      store_completed.br_mask = ubr;
      if (!incoming_std_only) {
        lsq_.st_addr_valid = static_cast<uint8_t>((lsq_.st_addr_valid & ~b) | (incoming_killed ? 0 : b));
        L.stq_bits_addr_bits[idx] = addr & kPc40;
        lsq_.st_virtual = static_cast<uint8_t>((lsq_.st_virtual & ~b) | (tlb_miss ? b : 0));
        tlb_store_search_now = !tlb_miss && !incoming_killed;
        tlb_store_search_idx = static_cast<uint8_t>(idx);
        tlb_store_search_addr = paddr;
        tlb_store_search_size = u.mem_size;
      }
      if (!incoming_sta_only) {
        lsq_.st_data_valid = static_cast<uint8_t>((lsq_.st_data_valid & ~b) | (incoming_killed ? 0 : b));
        st_data[idx] = mem_agu_rs2_s_;
      }
      stq_dirty_ = true;
      if (!incoming_killed && !us.is_amo() && ((lsq_.st_addr_valid >> idx) & 1u) &&
          ((lsq_.st_data_valid >> idx) & 1u) && !((lsq_.st_virtual >> idx) & 1u))
        store_completed.v = true;
    }
  }

  // (4.25) TLB-miss retries.
  if (S.load_retry) {
    const int idx = ldq_wrap(ldq_retry_idx_pre);
    const uint8_t b = bit8(idx);
    const bool killed = (b1_mispred_mask_now_ & lsq_.ld_brmask[idx]) != 0;
    const uint64_t vaddr = lsq_.ld_addr[idx];
    const bool tlb_miss = !dtlb_passthrough && dtlb_resp_miss;
    const uint64_t paddr = dtlb_passthrough ? vaddr : dtlb_resp_paddr;
    const bool uncacheable = !dtlb_passthrough && !tlb_miss && dtlb_resp_uncacheable;
    lsq_.ld_addr_valid = static_cast<uint8_t>((lsq_.ld_addr_valid & ~b) | (killed ? 0 : b));
    lsq_.ld_addr[idx] = (tlb_miss ? vaddr : paddr) & kPc40;
    lsq_.ld_virtual = static_cast<uint8_t>((lsq_.ld_virtual & ~b) | (tlb_miss ? b : 0));
    lsq_.ld_uncacheable = static_cast<uint8_t>((lsq_.ld_uncacheable & ~b) | (uncacheable ? b : 0));
    ldq_dirty_ = true;
    mem_paddr_r_ = paddr;
    ldq_block_now |= b;
    attempt_ldq = static_cast<int8_t>(idx);
    tlb_load_search_now = !tlb_miss && !killed;
    const bool dmem_req_valid = !tlb_miss && !uncacheable;
    MemUop ru = ldq_uop(idx);
    ru.br_mask = ld_brmask_s_[idx];  // request: pre-edge mask
    if (dmem_req_valid) { mem_attempt_v = true; mem_attempt_uop = ru; mem_attempt_addr = paddr; mem_attempt_data = 0; }
    if (dmem_req_valid && dmem_port_free) {
      dmem_pending.valid = true; dmem_pending.uop = ru; dmem_pending.addr = paddr; dmem_pending.data = 0;
      dmem_req_fired_now = true; dmem_req_mask_now = lsq_.ld_brmask[idx];
      fired_ldq = static_cast<int8_t>(idx);
    }
  }
  if (S.sta_retry) {
    const int idx = stq_wrap(stq_retry_idx_pre);
    const uint8_t b = bit8(idx);
    const uint64_t w = lsq_.st_word[idx];
    const bool killed = (b1_mispred_mask_now_ & StqWord::br_mask(w)) != 0;
    const uint64_t vaddr = st_addr[idx];
    const bool tlb_miss = !dtlb_passthrough && dtlb_resp_miss;
    const uint64_t paddr = dtlb_passthrough ? vaddr : dtlb_resp_paddr;
    lsq_.st_addr_valid = static_cast<uint8_t>((lsq_.st_addr_valid & ~b) | ((!dtlb_resp_pf_st && !killed) ? b : 0));
    L.stq_bits_addr_bits[idx] = (tlb_miss ? vaddr : paddr) & kPc40;
    lsq_.st_virtual = static_cast<uint8_t>((lsq_.st_virtual & ~b) | (tlb_miss ? b : 0));
    stq_dirty_ = true;
    store_completed.rob = StqWord::rob(w);
    store_completed.br_mask = StqWord::br_mask(w);
    store_completed.v = ((st_valid_s_ >> idx) & 1u) && ((st_data_valid_s_ >> idx) & 1u) && !tlb_miss &&
                        !StqWord::is_amo(w) && !killed;
    tlb_store_search_now = !tlb_miss && !killed;
    tlb_store_search_idx = static_cast<uint8_t>(idx);
    tlb_store_search_addr = paddr;
    tlb_store_search_size = StqWord::mem_size(w);
  }

  // (4.5) Load wakeup.
  bool wakeup_attempt = false;
  if (S.load_wakeup) {
    const int idx = ldq_wrap(ldq_wakeup_idx_pre);
    wakeup_attempt = true;
    fired_wakeup_now_ = true;
    mem_paddr_r_ = lsq_.ld_addr[idx];
    mem_attempt_v = true;
    mem_attempt_uop = ldq_uop(idx);
    mem_attempt_uop.br_mask = ld_brmask_s_[idx];  // request: pre-edge mask
    mem_attempt_addr = lsq_.ld_addr[idx];
    mem_attempt_data = 0;
    ldq_block_now |= bit8(idx);
    attempt_ldq = static_cast<int8_t>(idx);
    if (dmem_port_free) {
      fired_ldq = static_cast<int8_t>(idx);
      dmem_pending.valid = true;
      dmem_pending.uop = mem_attempt_uop;
      dmem_pending.addr = lsq_.ld_addr[idx];
      dmem_pending.data = 0;
      dmem_req_fired_now = true;
      dmem_req_mask_now = lsq_.ld_brmask[idx];
    }
  }
  (void)wakeup_attempt;
  ldq_block_now_r_ = ldq_block_now;

  // (5) Store commit -> memory.
  {
    const int ei = stq_wrap(lsq_.stq_execute_head);
    const uint64_t w = lsq_.st_word[ei];
    const bool sv = (st_valid_s_ >> ei) & 1u;
    const bool sc_can = sv && !StqWord::is_fence(w) && !mem_xcpt_.v && !((st_exc_s_ >> ei) & 1u) &&
                        (((st_committed_s_ >> ei) & 1u) ||
                         (StqWord::is_amo(w) && ((st_addr_valid_s_ >> ei) & 1u) &&
                          !((st_virtual_s_ >> ei) & 1u) && ((st_data_valid_s_ >> ei) & 1u)));
    const bool sc_will = S.store_commit;
    if (sc_will) {
      lsq_.st_succeeded &= static_cast<uint8_t>(~bit8(ei));
      stq_dirty_ = true;
      mem_paddr_r_ = st_addr[ei];
      mem_attempt_v = true;
      mem_attempt_uop = MemUop::from_stq(w);
      mem_attempt_uop.br_mask = st_brmask_s_[ei];
      mem_attempt_addr = st_addr[ei];
      mem_attempt_data = storegen_replicate(StqWord::mem_size(w), st_data[ei]);
    }
    if (sc_will && dmem_port_free) {
      dmem_pending.valid = true;
      dmem_pending.uop = MemUop::from_stq(w);
      dmem_pending.uop.br_mask = st_brmask_s_[ei];
      dmem_pending.addr = st_addr[ei];
      dmem_pending.data = storegen_replicate(StqWord::mem_size(w), st_data[ei]);
      dmem_req_fired_now = true;
      dmem_req_mask_now = StqWord::br_mask(w);
      lsq_.stq_execute_head = stq_wrap(ei + 1);
      {
        static bool dbg = false;
        static int dbg_gen = -1;
        if (dbg_gen != g_env_generation) { dbg_gen = g_env_generation; dbg = std::getenv("CHISA_NACK_DEBUG") != nullptr; }
        if (dbg) std::fprintf(stderr, "[STFIRE] core_cycle=%llu entry=%d addr=%llx head=%u tail=%u commit_head=%u\n",
                              static_cast<unsigned long long>(cycle_count_), ei, static_cast<unsigned long long>(dmem_pending.addr),
                              unsigned(lsq_.stq_head), unsigned(lsq_.stq_tail), unsigned(lsq_.stq_commit_head));
      }
    }
    if (sc_will || !sc_can) store_blocked_counter_ = 0;
    else store_blocked_counter_ = (store_blocked_counter_ == 15) ? 0 : 15;
  }
  if (stq_nack_rewind >= 0) {
    lsq_.stq_execute_head = stq_nack_rewind;
    static bool dbg = false;
    static int dbg_gen = -1;
    if (dbg_gen != g_env_generation) { dbg_gen = g_env_generation; dbg = std::getenv("CHISA_NACK_DEBUG") != nullptr; }
    if (dbg) std::fprintf(stderr, "[REWIND] core_cycle=%llu to=%d\n", static_cast<unsigned long long>(cycle_count_), stq_nack_rewind);
  }

  // (6) Store dealloc at the head (committed/succeeded read as registers).
  {
    const int h = lsq_.stq_head;
    const uint64_t w = lsq_.st_word[h];
    const bool fence_clear = StqWord::is_fence(w) && dmem_ordered;
    const bool clear_store = boom_lsu::clear_store(
        (lsq_.st_valid >> h) & 1u, (st_committed_s_ >> h) & 1u, StqWord::is_fence(w),
        (st_succeeded_s_ >> h) & 1u, dmem_ordered);
    if (clear_store) {
      const uint8_t keep = static_cast<uint8_t>(~bit8(h));
      lsq_.live_store_mask &= keep;
      for (unsigned live = kArchitecturalModel ? lsq_.ld_valid : 255u; live; live &= live - 1u)
        lsq_.ld_stdep[__builtin_ctz(live)] &= keep;
      lsq_.st_valid &= keep; lsq_.st_addr_valid &= keep; lsq_.st_data_valid &= keep;
      lsq_.st_committed &= keep; lsq_.st_succeeded &= keep;
      if (fence_clear) lsq_.stq_execute_head = stq_wrap(lsq_.stq_execute_head + 1);
      lsq_.stq_head = stq_wrap(lsq_.stq_head + 1);
      stq_dirty_ = true; ldq_dirty_ = true;
    }
  }

  // (6.5) Next cycle's selectors and the block delay line.
  const lsq_mask_t blocked_for_next = static_cast<lsq_mask_t>(ldq_block_now | ldq_block_p1_);
  {
    const uint8_t wake_next = lsq_age_pick(static_cast<lsq_mask_t>(ldq_elig_s_ & ~blocked_for_next), ldq_head_s_);
    const uint8_t retry_next = lsq_age_pick(static_cast<lsq_mask_t>(ldq_retry_elig_s_ & ~blocked_for_next), ldq_head_s_);
    // both indices sit in the LDQ bank word ldqbank_1_3
    if (wake_next != ldq_wakeup_idx_ || retry_next != ldq_retry_idx_) ldq_dirty_ = true;
    ldq_wakeup_idx_ = wake_next;
    ldq_retry_idx_ = retry_next;
  }
  stq_retry_idx_ = lsq_age_pick(stq_retry_elig_s_, stq_commit_head_s_);
  ldq_block_p2_ = ldq_block_p1_;
  ldq_block_p1_ = ldq_block_now;

  // Speculative-wakeup pipeline (uses mem_agu before it shifts).
  spec_s2_ = spec_s1_;
  {
    const StageUop& au = mem_agu_.u;
    spec_s1_.v = incoming_load && !au.fp_val() && au.pdst != 0;
    spec_s1_.pdst = au.pdst;
    spec_s1_.br_mask = au.br_mask;
    spec_s1_.ldq_idx = au.ldq_idx;
  }
  block_wakeup_next_ = lcam_match_nofwd;
  nacking_loads_prev_ = nacking_loads_now;
  wb_fwd_valid_r_ = fwd_wb_.v;
  {
  {
    const bool branch_killed = adp_valid_ && (b1_mispred_mask_now_ & adp_mask_) != 0;
    const bool exc_killed = adp_valid_ && flush_redirect_now_ && dmem_pending.uop.uses_ldq;
    const bool killed = branch_killed || exc_killed;
    const bool send_resp = adp_valid_ && dmem_resp_valid && !killed;
    const br_mask_t nres = static_cast<br_mask_t>(~b1_resolve_mask_now_);
    if (dmem_req_fired_now) adp_mask_ = dmem_req_mask_now & nres;
    else if (adp_valid_ && !killed) adp_mask_ &= nres;
    adp_valid_ = (killed || send_resp) ? false : (dmem_req_fired_now || adp_valid_);
  }
  spec_ld_ldq_r_ = mem_incoming_ldq_r_;
  mem_incoming_ldq_r_ = conv_exe_ldq_;
  {
    const bool ckill = flush_redirect_now_ || ((b1_mispred_mask_now_ & conv_rrd_mask_) != 0);
    conv_exe_ldq_ = ckill ? 0 : conv_rrd_ldq_;
    conv_rrd_ldq_ = mem_sel_now_ ? mem_sel_uop_now_.ldq_idx : 0;
    conv_rrd_mask_ = mem_sel_now_ ? mem_sel_uop_now_.br_mask : 0;
  }
  }
  // mem_xcpt conveyor: the exe_tlb_uop mux (incoming / retry) with the
  // misalignment / TLB fault decode.
  if (kInternalSignalContract || S.load_incoming || S.stad_incoming || S.sta_incoming ||
      S.load_retry || S.sta_retry) {
    StageUop selected;
    uint64_t vaddr = 0;
    bool has_exe_tlb_uop = false, is_load = false, is_store = false, incoming_address = false;
    br_mask_t selected_mask = 0;
    if (S.load_incoming || S.stad_incoming || S.sta_incoming || S.sfence) {
      selected = mem_agu_s_.u;
      has_exe_tlb_uop = true;
      is_load = S.load_incoming;
      is_store = S.stad_incoming || S.sta_incoming;
      incoming_address = is_load || is_store;
      vaddr = S.sfence ? mem_agu_rs1_s_ : mem_agu_rs1_s_ + decode_imm(inst(selected));
      selected_mask = selected.br_mask;
    } else if (S.load_retry) {
      const int i = ldq_wrap(ldq_retry_idx_pre);
      selected = StageUop::from(inst_[lsq_.ld_rob[i]]);
      selected_mask = lsq_.ld_brmask[i];
      vaddr = lsq_.ld_addr[i];
      has_exe_tlb_uop = true; is_load = true;
    } else if (S.sta_retry) {
      const int i = stq_wrap(stq_retry_idx_pre);
      const uint64_t w = lsq_.st_word[i];
      selected.rob = StqWord::rob(w); selected.ldq_idx = StqWord::ldq(w); selected.stq_idx = StqWord::stq(w);
      selected.flags = StageUop::kUsesStq;
      selected_mask = StqWord::br_mask(w);
      vaddr = st_addr[i];
      has_exe_tlb_uop = true; is_store = true;
    }
    const bool selected_killed = (selected_mask & b1_mispred_mask_now_) != 0;
    selected_mask &= static_cast<br_mask_t>(~b1_resolve_mask_now_);
    uint8_t size = 0;
    if (has_exe_tlb_uop) {
      if (S.sta_retry) size = StqWord::mem_size(lsq_.st_word[stq_wrap(stq_retry_idx_pre)]);
      else size = inst(selected).mem_size & 3u;
    }
    const bool misaligned = (size == 1 && (vaddr & 1u)) || (size == 2 && (vaddr & 3u)) || (size == 3 && (vaddr & 7u));
    const bool ma_ld = incoming_address && is_load && misaligned;
    const bool ma_st = incoming_address && is_store && misaligned;
    const bool pf_ld = is_load && dtlb_resp_pf_ld, pf_st = is_store && dtlb_resp_pf_st;
    const bool ae_ld = is_load && dtlb_resp_ae_ld, ae_st = is_store && dtlb_resp_ae_st;
    XcptRec next;
    next.v = (ma_ld || ma_st || pf_ld || pf_st || ae_ld || ae_st) && !flush_redirect_now_ && !selected_killed;
    if (has_exe_tlb_uop) {
      next.rob = selected.rob; next.ldq_idx = selected.ldq_idx; next.stq_idx = selected.stq_idx;
      next.uses_ldq = S.sta_retry ? false : inst(selected).uses_ldq != 0;
      next.br_mask = selected_mask;
    }
    next.cause = ma_ld ? 4 : ma_st ? 6 : pf_ld ? 13 : pf_st ? 15 : ae_ld ? 5 : 7;
    next.vaddr = vaddr;
    if constexpr (kArchitecturalModel) {
      mem_xcpt_.v = next.v;
      if (next.v) {
        mem_xcpt_ = next;
        mem_xcpt_rob_r_ = next.rob;
        mem_xcpt_brmask_r_ = next.br_mask;
      }
    } else {
      mem_xcpt_ = next;
      mem_xcpt_rob_r_ = has_exe_tlb_uop ? selected.rob : 0;
      mem_xcpt_brmask_r_ = has_exe_tlb_uop ? selected_mask : 0;
    }
  } else {
    mem_xcpt_.v = false;
  }
  {
  mem_incoming_rob_r_ = mem_agu_vmir_ ? mem_agu_.u.rob : 0;
  mem_incoming_brmask_r_ = mem_agu_vmir_ ? mem_agu_.u.br_mask : 0;
  mem_incoming_pdst_r_ = mem_agu_.u.pdst;
  }

  // One registered exception port: TLB/misalignment vs LCAM order failure.
  if (kArchitecturalModel && !failed_load_mask && !mem_xcpt_pre.v) {
    lsu_r_xcpt_.v = false;
  } else {
    const bool ld_xcpt_valid = failed_load_mask != 0;
    const uint8_t failed_idx = lsq_age_pick(failed_load_mask, ldq_head_s_);
    XcptRec ld;
    if (ld_xcpt_valid) {
      ld.rob = lsq_.ld_rob[failed_idx];
      ld.ldq_idx = static_cast<uint8_t>(failed_idx);
      ld.uses_ldq = true;
      ld.br_mask = lsq_.ld_brmask[failed_idx];
    }
    const bool use_mem_xcpt = !ld_xcpt_valid ||
                              (mem_xcpt_pre.v && lsq_is_older(mem_xcpt_pre.rob, ld.rob, rob_head_start_));
    XcptRec sel = use_mem_xcpt ? mem_xcpt_pre : ld;
    const br_mask_t selected_mask = use_mem_xcpt ? mem_xcpt_brmask_pre : sel.br_mask;
    const bool selected_killed = (b1_mispred_mask_now_ & selected_mask) != 0;
    sel.br_mask = static_cast<br_mask_t>(selected_mask & ~b1_resolve_mask_now_);
    lsu_r_xcpt_ = sel;
    lsu_r_xcpt_.v = (ld_xcpt_valid || mem_xcpt_pre.v) && !flush_redirect_now_ && !selected_killed;
    lsu_r_xcpt_.cause = use_mem_xcpt ? mem_xcpt_pre.cause : 16;
    lsu_r_xcpt_.vaddr = mem_xcpt_pre.vaddr;
    lsu_xcpt_rob_r_ = sel.rob;
    lsu_xcpt_brmask_r_ = sel.br_mask;
  }

  // (7) Advance the issue->AGU pipeline registers and the s1 records.
  mem_agu_ = mem_rrd_;
  mem_agu_rs1_ = mem_rrd_rs1_; mem_agu_rs2_ = mem_rrd_rs2_;
  if (mem_rrd_killed_) {
    const br_mask_t surviving = mem_rrd_.u.br_mask;
    mem_agu_.u.clear();
    mem_agu_.u.br_mask = surviving;
  } else if (flush_redirect_now_) {
    mem_agu_.u.flags &= static_cast<uint16_t>(~(StageUop::kIsLoad | StageUop::kIsSta | StageUop::kIsStd));
  }
  mem_agu_vmir_ = mem_rrd_vmir_ && !mem_rrd_killed_;
  mem_rrd_vmir_ = mem_iss_vmir_;
  mem_rrd_ = mem_iss_;
  mem_rrd_rs1_ = mem_iss_rs1_; mem_rrd_rs2_ = mem_iss_rs2_;
  // The pipeline moved: the next cycle's pre-step schedule query must not
  // reuse this cycle's memoized schedule.
  g_memo.valid = false;
  lcam_ldq_s1_ = attempt_ldq;
  lcam_incoming_s1_ = tlb_load_search_now;
  lcam_fired_s1_ = fired_ldq >= 0;
  lcam_store_search_s1_ = tlb_store_search_now;
  lcam_store_stq_s1_ = tlb_store_search_idx;
  lcam_store_addr_s1_ = tlb_store_search_addr;
  lcam_store_size_s1_ = tlb_store_search_size;
  release_search_s1_ = release_fire;
  release_address_s1_ = dmem_release_address;
  store_clr_bsy_s2_ = store_clr_bsy_s1_;
  store_clr_bsy_s1_ = store_completed;
}

// --------------------------------------------------------------------------
// Contract bank words of the LDQ/STQ.
// --------------------------------------------------------------------------
void Core::lsq_pack() {
  auto& L = img_->r.lsu;
  // The bank words also carry the queue pointers and selector indices; a
  // pointer move without an entry change (a nack rewind, a commit-head
  // advance) must regenerate them too.
  {
    const uint64_t sig = uint64_t(lsq_.stq_execute_head) | (uint64_t(lsq_.stq_commit_head) << 4) |
                         (uint64_t(lsq_.stq_head) << 8) | (uint64_t(stq_retry_idx_) << 12) |
                         (uint64_t(lsq_.stq_tail) << 16) | (uint64_t(lsq_.ldq_head) << 20) |
                         (uint64_t(lsq_.ldq_tail) << 24) | (uint64_t(ldq_wakeup_idx_) << 28) |
                         (uint64_t(ldq_retry_idx_) << 32);
    if (sig != lsq_ptr_sig_) { lsq_ptr_sig_ = sig; ldq_dirty_ = stq_dirty_ = true; }
  }
  if (ldq_dirty_) {
    const Lsq& q = lsq_;
    auto rec = [&](int i) -> uint64_t {   // 26-bit per-entry record
      return (uint64_t(q.ld_brmask[i]) << 18) | ((uint64_t(q.ld_pdst[i]) & 0x3f) << 12) |
             (uint64_t((q.ld_succeeded >> i) & 1u) << 11) | (uint64_t((q.ld_order_fail >> i) & 1u) << 10) |
             (uint64_t((q.ld_observed >> i) & 1u) << 9) | (uint64_t(q.ld_stdep[i]) << 1) |
             uint64_t((q.ld_fwd_std_val >> i) & 1u);
    };
    const uint64_t r0 = rec(0), r1 = rec(1), r2 = rec(2), r3 = rec(3), r4 = rec(4), r5 = rec(5), r6 = rec(6), r7 = rec(7);
    L.ldqbank_1[0] = (r0 << 34) | (r1 << 8) | (r2 >> 18);
    L.ldqbank_1[1] = ((r2 & ((UINT64_C(1) << 18) - 1)) << 43) | (r3 << 17) | (r4 >> 9);
    L.ldqbank_1[2] = ((r4 & 0x1ff) << 52) | (r5 << 26) | r6;
    L.ldqbank_1_3 = static_cast<uint32_t>((r7 << 6) | ((uint64_t(ldq_wakeup_idx_) & 7) << 3) | (uint64_t(ldq_retry_idx_) & 7));
    auto addr_word = [&](int i) { return (q.ld_addr[i] << 1) | uint64_t((q.ld_uncacheable >> i) & 1u); };
    L.ldqbank_3_0 = addr_word(0); L.ldqbank_5_0 = addr_word(1); L.ldqbank_7_0 = addr_word(2);
    L.ldqbank_9_0 = addr_word(3); L.ldqbank_11_0 = addr_word(4);
    L.ldqbank_15[0] = ((uint64_t(q.ld_fwd_stq[0]) & 7) << 56) | ((uint64_t(q.ld_fwd_stq[1]) & 7) << 53) |
                      ((uint64_t(q.ld_fwd_stq[2]) & 7) << 50) | ((uint64_t(q.ld_fwd_stq[3]) & 7) << 47) |
                      ((uint64_t(q.ld_fwd_stq[4]) & 7) << 44) | (q.ld_addr[5] << 4) |
                      (uint64_t((q.ld_uncacheable >> 5) & 1u) << 3) | (uint64_t(q.ld_fwd_stq[5]) & 7);
    L.ldqbank_15[1] = (q.ld_addr[6] << 4) | (uint64_t((q.ld_uncacheable >> 6) & 1u) << 3) | (uint64_t(q.ld_fwd_stq[6]) & 7);
    L.ldqbank_15[2] = (q.ld_addr[7] << 10) | (uint64_t((q.ld_uncacheable >> 7) & 1u) << 9) |
                      ((uint64_t(q.ld_fwd_stq[7]) & 7) << 6) | ((uint64_t(q.ldq_head) & 7) << 3) | (uint64_t(q.ldq_tail) & 7);
    uint32_t w0 = 0;
    for (int i = 0; i < kLdq; ++i)
      w0 = (w0 << 3) | (uint32_t((q.ld_valid >> i) & 1u) << 2) | (uint32_t((q.ld_addr_valid >> i) & 1u) << 1) |
           uint32_t((q.ld_executed >> i) & 1u);
    L.ldqbank_0_0 = w0;
    for (int i = 0; i < kLdq; ++i) L.ldq_bits_addr_is_virtual[i] = (q.ld_virtual >> i) & 1u;
    ldq_dirty_ = false;
  }
  if (stq_dirty_) {
    const Lsq& q = lsq_;
    // 45-bit per-entry record: valid1 + word40 + addr_valid data_valid committed succeeded.
    auto rec = [&](int i) -> uint64_t {
      return (uint64_t((q.st_valid >> i) & 1u) << 44) | (q.st_word[i] << 4) |
             (uint64_t((q.st_addr_valid >> i) & 1u) << 3) | (uint64_t((q.st_data_valid >> i) & 1u) << 2) |
             (uint64_t((q.st_committed >> i) & 1u) << 1) | uint64_t((q.st_succeeded >> i) & 1u);
    };
    const uint64_t r0 = rec(0), r1 = rec(1), r2 = rec(2), r3 = rec(3), r4 = rec(4), r5 = rec(5), r6 = rec(6);
    L.stqbank_0[0] = (r0 << 17) | (r1 >> 28);
    L.stqbank_0[1] = ((r1 & ((UINT64_C(1) << 28) - 1)) << 36) | (r2 >> 9);
    L.stqbank_0[2] = ((r2 & 0x1ff) << 54) | (r3 << 9) | (r4 >> 36);
    L.stqbank_0[3] = ((r4 & ((UINT64_C(1) << 36) - 1)) << 27) | (r5 >> 18);
    L.stqbank_0[4] = ((r5 & 0x3ffff) << 46) | (r6 << 1) | uint64_t((q.st_valid >> 7) & 1u);
    const uint64_t w7 = q.st_word[7];
    L.stqbank_0[5] = (uint64_t(StqWord::br_mask(w7)) << 49) | ((uint64_t(StqWord::rob(w7)) & 0x1f) << 44) |
                     ((uint64_t(StqWord::ldq(w7)) & 7) << 41) | ((uint64_t(StqWord::stq(w7)) & 7) << 38) |
                     ((uint64_t(StqWord::pdst(w7)) & 0x3f) << 32) | (uint64_t(StqWord::exception(w7)) << 31) |
                     ((uint64_t(StqWord::mem_cmd(w7)) & 0x1f) << 26) | ((uint64_t(StqWord::mem_size(w7)) & 3) << 24) |
                     (uint64_t(StqWord::mem_signed(w7)) << 23) | (uint64_t(StqWord::is_fence(w7)) << 22) |
                     (uint64_t(StqWord::is_amo(w7)) << 21) | (uint64_t(StqWord::uses_ldq(w7)) << 20) |
                     (uint64_t(StqWord::uses_stq(w7)) << 19) | ((uint64_t(StqWord::dst_rtype(w7)) & 3) << 17) |
                     (uint64_t((q.st_addr_valid >> 7) & 1u) << 16) | (uint64_t((q.st_virtual >> 7) & 1u) << 15) |
                     (uint64_t((q.st_data_valid >> 7) & 1u) << 14) | (uint64_t((q.st_committed >> 7) & 1u) << 13) |
                     (uint64_t((q.st_succeeded >> 7) & 1u) << 12) | ((uint64_t(q.stq_head) & 7) << 9) |
                     ((uint64_t(q.stq_commit_head) & 7) << 6) | ((uint64_t(q.stq_execute_head) & 7) << 3) |
                     (uint64_t(stq_retry_idx_) & 7);
    for (int i = 0; i < 7; ++i) L.stq_bits_addr_is_virtual[i] = (q.st_virtual >> i) & 1u;
    L.stq_tail = static_cast<uint8_t>(q.stq_tail & 7);
    stq_dirty_ = false;
  }
}

}  // namespace chisa::boom_model
