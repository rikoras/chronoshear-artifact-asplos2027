// model core: the two collapsing issue queues (IssueUnitCollapsing +
// IssueSlot, one dispatch port, one issue port each) and the integer
// issue/execute launch.  Slot status bits and the slot_uop bank word are the
// image fields; the private columns hold what select and wakeup need.
#include "core.h"
#include "../common/execute.h"
#include "../common/byte_columns.h"

namespace chisa::boom_model {

namespace {
constexpr uint16_t INT_FU = FU_ALU | FU_JMP | FU_MUL | FU_DIV | FU_CSR;
constexpr uint16_t MEM_FU = FU_MEM;
using byte_columns::kOnes;
using byte_columns::k7f;
using byte_columns::load8;
using byte_columns::store8;
using byte_columns::eq_bytes;

}  // namespace

// --------------------------------------------------------------------------
// Issue-queue column helpers.
// --------------------------------------------------------------------------
template <class G>
static void bind_iq_columns(Core::Iq& q, G& g) {
  q.state = g.slots_state; q.p1 = g.slots_p1; q.p2 = g.slots_p2; q.p3 = g.slots_p3;
  q.ppred = g.slots_ppred; q.p1_poison = g.slots_p1_poisoned; q.p2_poison = g.slots_p2_poisoned;
  q.packed = g.slots_slot_uopbank_2_0; q.ready = &g.REG;
}

void Core::iq_bind(Iq& q, bool is_int) {
  if (is_int) bind_iq_columns(q, img_->r.coreIntIq);
  else bind_iq_columns(q, img_->r.coreMemIq);
}

std::uint64_t Core::oracle_issue_bank0(OracleIssueQueue queue, unsigned slot) const {
  if (slot >= kIq) throw std::out_of_range("Small issue oracle slot");
  // Exact Small register_bank_manifest layouts. Assemble one host word;
  // no full MicroOp copy and no extra per-cycle slot mirror.
  if (queue == OracleIssueQueue::Floating) {
    const MicroOp& u = fp_iq_[slot].uop;
    return ((std::uint64_t(u.fu_code) & UINT64_C(0x3ff)) << 52u)
        | ((std::uint64_t(u.imm_packed) & UINT64_C(0xfffff)) << 32u)
        | ((std::uint64_t(u.rob_idx) & UINT64_C(0x1f)) << 27u)
        | ((std::uint64_t(u.stq_idx) & UINT64_C(0x7)) << 24u)
        | ((std::uint64_t(u.prs1) & UINT64_C(0x3f)) << 18u)
        | ((std::uint64_t(u.prs2) & UINT64_C(0x3f)) << 12u)
        | ((std::uint64_t(u.prs3) & UINT64_C(0x3f)) << 6u)
        | ((std::uint64_t(u.mem_cmd) & UINT64_C(0x1f)) << 1u)
        | ((std::uint64_t(u.is_amo) & UINT64_C(0x1)) << 0u);
  }
  const Iq& q = queue == OracleIssueQueue::Memory ? mem_iq_ : int_iq_;
  const MicroOp& u = inst(q.rob[slot]);
  if (queue == OracleIssueQueue::Memory)
    return ((std::uint64_t(q.fu[slot]) & UINT64_C(0x3ff)) << 54u)
        | ((std::uint64_t(u.imm_packed) & UINT64_C(0xfffff)) << 34u)
        | ((std::uint64_t(q.rob[slot]) & UINT64_C(0x1f)) << 29u)
        | ((std::uint64_t(u.ldq_idx) & UINT64_C(0x7)) << 26u)
        | ((std::uint64_t(u.stq_idx) & UINT64_C(0x7)) << 23u)
        | ((std::uint64_t(q.prs1[slot]) & UINT64_C(0x3f)) << 17u)
        | ((std::uint64_t(q.prs2[slot]) & UINT64_C(0x3f)) << 11u)
        | ((std::uint64_t(q.prs3[slot]) & UINT64_C(0x3f)) << 5u)
        | ((std::uint64_t(u.mem_cmd) & UINT64_C(0x1f)) << 0u);
  return ((std::uint64_t(u.is_rvc) & UINT64_C(0x1)) << 60u)
        | ((std::uint64_t(q.fu[slot]) & UINT64_C(0x3ff)) << 50u)
        | ((std::uint64_t(u.is_br) & UINT64_C(0x1)) << 49u)
        | ((std::uint64_t(u.is_jalr) & UINT64_C(0x1)) << 48u)
        | ((std::uint64_t(u.is_jal) & UINT64_C(0x1)) << 47u)
        | ((std::uint64_t(u.is_sfb) & UINT64_C(0x1)) << 46u)
        | ((std::uint64_t(u.br_tag) & UINT64_C(0x7)) << 43u)
        | ((std::uint64_t(u.ftq_idx) & UINT64_C(0xf)) << 39u)
        | ((std::uint64_t(u.edge_inst) & UINT64_C(0x1)) << 38u)
        | ((std::uint64_t(u.pc_lob) & UINT64_C(0x3f)) << 32u)
        | ((std::uint64_t(u.taken) & UINT64_C(0x1)) << 31u)
        | ((std::uint64_t(u.imm_packed) & UINT64_C(0xfffff)) << 11u)
        | ((std::uint64_t(q.rob[slot]) & UINT64_C(0x1f)) << 6u)
        | ((std::uint64_t(u.ldq_idx) & UINT64_C(0x7)) << 3u)
        | ((std::uint64_t(u.stq_idx) & UINT64_C(0x7)) << 0u);
}

void Core::iq_load_slot(Iq& q, int i, const MicroOp& du) {
  if constexpr (kArchitecturalModel) q.live |= static_cast<std::uint8_t>(1u << i);
  const bool two = (du.uopc == uopSTA && du.lrs2_rtype == RT_FIX) || du.uopc == uopAMO_AG;
  q.state[i] = two ? IS_VALID_2 : IS_VALID_1;
  q.rob[i] = du.rob_idx;
  q.prs1[i] = du.prs1; q.prs2[i] = du.prs2; q.prs3[i] = du.prs3;
  q.fu[i] = du.fu_code;
  q.uopc[i] = du.uopc; q.rt1[i] = du.lrs1_rtype; q.rt2[i] = du.lrs2_rtype;
  q.br_mask[i] = du.br_mask;
  q.iq_flags[i] = static_cast<uint8_t>(
      ((du.bypassable && du.dst_rtype == RT_FIX && du.ldst_val) ? 1u : 0u) |
      (du.uses_ldq ? 2u : 0u));
  q.p1[i] = bit(!du.prs1_busy); q.p2[i] = bit(!du.prs2_busy); q.p3[i] = bit(!du.prs3_busy);
  q.ppred[i] = bit(!du.ppred_busy);
  q.p1_poison[i] = 0; q.p2_poison[i] = 0;
  q.packed[i] = pack_iq_slot(du.uopc, du.br_mask, du.lrs1_rtype, du.lrs2_rtype);
}

void Core::iq_move_slot(Iq& q, int i, int s) {
  q.rob[i] = q.rob[s]; q.prs1[i] = q.prs1[s]; q.prs2[i] = q.prs2[s]; q.prs3[i] = q.prs3[s];
  q.fu[i] = q.fu[s]; q.uopc[i] = q.uopc[s]; q.rt1[i] = q.rt1[s]; q.rt2[i] = q.rt2[s];
  q.br_mask[i] = q.br_mask[s]; q.iq_flags[i] = q.iq_flags[s];
  q.p1[i] = q.p1[s]; q.p2[i] = q.p2[s]; q.p3[i] = q.p3[s]; q.ppred[i] = q.ppred[s];
  q.p1_poison[i] = q.p1_poison[s]; q.p2_poison[i] = q.p2_poison[s];
  q.packed[i] = q.packed[s];
  q.state[i] = q.state[s];
}

// Fast wakeup CAM: every slot (valid or not) whose prs matches sets its p-bit.
void Core::iq_wake(Iq& q, uint8_t p) {
  const uint64_t live = kArchitecturalModel ? ~eq_bytes(load8(q.state), IS_INVALID) : UINT64_MAX;
  const uint64_t m1 = eq_bytes(load8(q.prs1), p) & live;
  const uint64_t m2 = eq_bytes(load8(q.prs2), p) & live;
  const uint64_t m3 = eq_bytes(load8(q.prs3), p) & live;
  if (m1) store8(q.p1, load8(q.p1) | m1);
  if (m2) store8(q.p2, load8(q.p2) | m2);
  if (m3) store8(q.p3, load8(q.p3) | m3);
}

// Speculative load wakeup: sets and poisons p1/p2 of integer-typed operands.
bool Core::iq_spec_wake(Iq& q, uint8_t p) {
  const uint64_t live = kArchitecturalModel ? ~eq_bytes(load8(q.state), IS_INVALID) : UINT64_MAX;
  const uint64_t fix1 = eq_bytes(load8(q.rt1), RT_FIX);
  const uint64_t fix2 = eq_bytes(load8(q.rt2), RT_FIX);
  const uint64_t m1 = eq_bytes(load8(q.prs1), p) & fix1 & live;
  const uint64_t m2 = eq_bytes(load8(q.prs2), p) & fix2 & live;
  if (m1) { store8(q.p1, load8(q.p1) | m1); store8(q.p1_poison, load8(q.p1_poison) | m1); }
  if (m2) { store8(q.p2, load8(q.p2) | m2); store8(q.p2_poison, load8(q.p2_poison) | m2); }
  return (m1 | m2) != 0;
}

bool Core::iq_req(const Iq& q, int i) const {
  const uint8_t st = q.state[i];
  if (st == IS_INVALID) return false;
  return st == IS_VALID_1 ? (q.p1[i] && q.p2[i] && q.p3[i] && q.ppred[i])
                          : ((q.p1[i] || q.p2[i]) && q.ppred[i]);
}

// Age-order select: the oldest requesting slot whose fu matches the port.
int Core::iq_peek(const Iq& q, uint16_t port_fu) const {
  if (kArchitecturalModel && q.live == 0) return -1;
  if (port_fu == 0) return -1;
  const uint64_t p1 = load8(q.p1), p2 = load8(q.p2), p3 = load8(q.p3), pp = load8(q.ppred);
  const uint64_t st = load8(q.state);
  const uint64_t req = ((p1 & p2 & p3 & pp) & eq_bytes(st, IS_VALID_1)) |
                       (((p1 | p2) & pp) & eq_bytes(st, IS_VALID_2));
  for (uint64_t m = req; m != 0; m &= m - 1) {
    const int i = __builtin_ctzll(m) >> 3;
    if (q.fu[i] & port_fu) return i;
  }
  return -1;
}

// The uop the slot presents to the select network (IssueSlot.io.uop): the
// stored payload shaped to its ready half for a split store.
StageUop Core::iq_selected(const Iq& q, int i) const {
  StageUop s = StageUop::from(inst_[q.rob[i]]);
  s.uopc = q.uopc[i]; s.lrs1_rtype = q.rt1[i]; s.lrs2_rtype = q.rt2[i];
  s.br_mask = q.br_mask[i];
  s.prs1 = q.prs1[i]; s.prs2 = q.prs2[i];
  if (q.state[i] == IS_VALID_2) {
    if (q.p1[i] && q.p2[i] && q.ppred[i]) {
    } else if (q.p1[i] && q.ppred[i]) {
      s.lrs2_rtype = RT_X;
    } else if (q.p2[i] && q.ppred[i]) {
      s.uopc = uopSTD;
      s.lrs1_rtype = RT_X;
    }
  }
  return s;
}

void Core::iq_flush(Iq& q) {
  store8(q.state, 0);   // only the state FSM clears; payloads hold
  if constexpr (kArchitecturalModel) q.live = 0;
}

// Select/grant + collapse (IssueUnitCollapsing, maxShift = 1).
bool Core::iq_collapse(Iq& q, uint16_t port_fu, uint8_t start_valid, bool port_consumed,
                       bool disp_v, const MicroOp& du, int ghost_slot, int squash_slot,
                       int& grant_slot, StageUop& grant, int& avail) {
  const int N = kIq;
  grant_slot = -1;
  if (kArchitecturalModel && q.live == 0 && !disp_v) { avail = kIq; return false; }
  if (!port_consumed) {
    // A poisoned winner squashed by ld_miss has consumed the port already
    // (squash_slot): the queue then makes no second selection this cycle.
    grant_slot = iq_peek(q, port_fu);
    if (grant_slot == squash_slot) grant_slot = -1;
  }
  bool store_partial = false;
  if (grant_slot >= 0) {
    const int g = grant_slot;
    grant = StageUop::from(inst_[q.rob[g]]);
    grant.uopc = q.uopc[g]; grant.lrs1_rtype = q.rt1[g]; grant.lrs2_rtype = q.rt2[g];
    grant.br_mask = q.br_mask[g];
    grant.prs1 = q.prs1[g]; grant.prs2 = q.prs2[g];
    if (q.state[g] == IS_VALID_2) {
      if (q.p1[g] && q.p2[g] && q.ppred[g]) {
        // STAD: the whole store issues, the slot vacates.
      } else if (q.p1[g]) {
        grant.lrs2_rtype = RT_X;              // address half issues
        q.uopc[g] = uopSTD; q.rt1[g] = RT_X;
        q.state[g] = IS_VALID_1;
        q.packed[g] = pack_iq_slot(q.uopc[g], q.br_mask[g], q.rt1[g], q.rt2[g]);
        store_partial = true;
      } else {
        grant.uopc = uopSTD; grant.lrs1_rtype = RT_X;   // data half issues first
        q.rt2[g] = RT_X;
        q.state[g] = IS_VALID_1;
        q.packed[g] = pack_iq_slot(q.uopc[g], q.br_mask[g], q.rt1[g], q.rt2[g]);
        store_partial = true;
      }
    }
  }
  auto issued = [&](int i) { return i == grant_slot && !store_partial; };

  if constexpr (kArchitecturalModel) {
    const auto live = static_cast<std::uint8_t>(q.live & start_valid);
    const auto removed = static_cast<std::uint8_t>(
        grant_slot >= 0 && !store_partial ? 1u << grant_slot : 0u);
    const auto movement = iq_movement(live, removed, disp_v);
    for (unsigned moving = movement.shifted_sources; moving; moving &= moving - 1u) {
      const unsigned source = __builtin_ctz(moving);
      iq_move_slot(q, source - 1, source);
    }
    if (movement.enqueue) iq_load_slot(q, kIq - 1, du);
    for (unsigned cleared = live & ~unsigned(movement.live_after); cleared; cleared &= cleared - 1u)
      q.state[__builtin_ctz(cleared)] = IS_INVALID;
    q.live = movement.live_after;
    avail = movement.available;
    return grant_slot >= 0;
  }

  bool vac[kIq + 1], wbv[kIq + 1], shamt[kIq + 1], killed[kIq + 1];
  for (int i = 0; i < N; ++i) {
    const bool was_valid = ((start_valid >> i) & 1) &&
                           (kInternalSignalContract || q.state[i] != IS_INVALID);
    vac[i] = !was_valid;
    killed[i] = was_valid && q.state[i] == IS_INVALID;
    wbv[i] = was_valid && !issued(i) && i != ghost_slot;
  }
  vac[N] = !disp_v; wbv[N] = disp_v; killed[N] = false;
  shamt[0] = false;
  for (int i = 1; i <= N; ++i) shamt[i] = shamt[i - 1] || vac[i - 1];

  avail = 0;
  for (int i = 0; i < N; ++i) {
    const bool recv_in = shamt[i + 1] && wbv[i + 1];
    if ((!wbv[i] || shamt[i]) && !recv_in) ++avail;
    if (recv_in) {
      if (i + 1 == N) {
        iq_load_slot(q, i, du);
      } else {
        const int s = i + 1;
        q.rob[i] = q.rob[s]; q.prs1[i] = q.prs1[s]; q.prs2[i] = q.prs2[s]; q.prs3[i] = q.prs3[s];
        q.fu[i] = q.fu[s]; q.uopc[i] = q.uopc[s]; q.rt1[i] = q.rt1[s]; q.rt2[i] = q.rt2[s];
        q.br_mask[i] = q.br_mask[s]; q.iq_flags[i] = q.iq_flags[s];
        q.p1[i] = q.p1[s]; q.p2[i] = q.p2[s]; q.p3[i] = q.p3[s]; q.ppred[i] = q.ppred[s];
        q.p1_poison[i] = q.p1_poison[s]; q.p2_poison[i] = q.p2_poison[s];
        q.packed[i] = q.packed[s];
        q.state[i] = killed[s] ? IS_INVALID : q.state[s];
      }
    } else if (shamt[i]) {
      q.state[i] = IS_INVALID;
    } else if (issued(i)) {
      q.state[i] = IS_INVALID;
    }
  }
  return grant_slot >= 0;
}

// --------------------------------------------------------------------------
// issue_step
// --------------------------------------------------------------------------
void Core::issue_step() {
  // Load data delivered on this edge (lsu_step runs after issue).
  resp_byp_v_ = false;
  if (dmem_resp_valid && (dmem_resp_uop_valid || (dmem_pending.valid && !dmem_pending_kill_))) {
    const MemUop& mu = dmem_resp_uop_valid ? dmem_resp_uop : dmem_pending.uop;
    if (mu.uses_ldq && mu.dst_rtype == RT_FIX && mu.pdst != 0) {
      resp_byp_v_ = true; resp_byp_pdst_ = mu.pdst; resp_byp_data_ = dmem_resp_data;
    }
  }
  br_inject_.clear();

  const bool pause_mem = pause_mem_r_ && sat_loads_ctr_ == 31;
  const uint16_t mem_fu_now = pause_mem ? 0 : MEM_FU;

  // Same-cycle load-forward bypass candidate.
  bool spec_bypass_valid = false;
  uint8_t spec_bypass_pdst = 0;
  uint64_t spec_bypass_data = 0;
  bool spec_hit = false;
  if (spec_s2_.v && dmem_resp_valid) {
    const MemUop* response_uop = nullptr;
    if (dmem_resp_uop_valid) response_uop = &dmem_resp_uop;
    else if (dmem_pending.valid && !dmem_pending_kill_) response_uop = &dmem_pending.uop;
    spec_hit = response_uop && response_uop->uses_ldq &&
               ldq_wrap(response_uop->ldq_idx) == ldq_wrap(spec_s2_.ldq_idx);
  }
  if (!spec_hit && spec_s2_.v && fwd_wb_.v && ldq_wrap(fwd_wb_.ldq_idx) == ldq_wrap(spec_s2_.ldq_idx)) {
    const int li = ldq_wrap(fwd_wb_.ldq_idx), si = stq_wrap(fwd_wb_.stq_idx);
    const bool memory_resp_fires = dmem_resp_valid &&
        (dmem_resp_uop_valid
            ? (dmem_resp_uop.uses_ldq || dmem_resp_uop.is_amo)
            : dmem_pending.valid && !dmem_pending_kill_ &&
                (dmem_pending.uop.uses_ldq || dmem_pending.uop.is_amo));
    const bool le_valid = (lsq_.ld_valid >> li) & 1;
    const bool se_valid = (lsq_.st_valid >> si) & 1, se_data = (lsq_.st_data_valid >> si) & 1;
    spec_hit = le_valid && se_valid && se_data && !memory_resp_fires;
    if (spec_hit) {
      const MicroOp& lu = inst_[lsq_.ld_rob[li]];
      if (lu.dst_rtype == RT_FIX && lsq_.ld_pdst[li] != 0) {
        spec_bypass_valid = true;
        spec_bypass_pdst = lsq_.ld_pdst[li];
        spec_bypass_data = fwd_extract(lsq_.ld_addr[li], lu.mem_size, lu.mem_signed,
                                       StqWord::mem_size(lsq_.st_word[si]), img_->r.lsu.stq_bits_data_bits[si]);
      }
    }
  }
  auto issue_prf_read = [&](uint8_t prs, uint8_t rtype) -> uint64_t {
    if (spec_bypass_valid && rtype == RT_FIX && prs == spec_bypass_pdst) return spec_bypass_data;
    if (resp_byp_v_ && rtype == RT_FIX && prs == resp_byp_pdst_) return resp_byp_data_;
    return prf_.rd(prs);
  };
  const bool ld_miss = spec_s2_.v && !spec_hit;
  ld_miss_now_ = ld_miss;
  int int_squash_slot = -1, mem_squash_slot = -1;
  if (ld_miss) {
    const int gi = iq_peek(int_iq_, cur_int_fu_);
    if (gi >= 0 && (int_iq_.p1_poison[gi] || int_iq_.p2_poison[gi])) {
      int_port_consumed_ = true;
      int_squash_slot = gi;
      int_squash_grant_ = true;
    }
    const int mi = iq_peek(mem_iq_, mem_fu_now);
    if (mi >= 0 && (mem_iq_.p1_poison[mi] || mem_iq_.p2_poison[mi])) {
      mem_port_consumed_ = true;
      mem_squash_slot = mi;
    }
  }

  // Register-read addresses from THIS cycle's select (ghost and squashed
  // winners included); the IO shows the registered addresses.
  {
    const int wi = iq_peek(int_iq_, cur_int_fu_);
    const int wm = iq_peek(mem_iq_, mem_fu_now);
    uint8_t i1 = 0, i2 = 0, m1 = 0, m2 = 0;
    if (ghost_int_v_) { i1 = ghost_int_uop_.prs1; i2 = ghost_int_uop_.prs2; }
    else if (wi >= 0) { i1 = int_iq_.prs1[wi]; i2 = int_iq_.prs2[wi]; }
    if (ghost_mem_v_) { m1 = ghost_mem_uop_.prs1; m2 = ghost_mem_uop_.prs2; }
    else if (wm >= 0) { m1 = mem_iq_.prs1[wm]; m2 = mem_iq_.prs2[wm]; }
    for (int k = 0; k < boomcfg::IRF_READ_PORTS; ++k) out_ext_irf_read_addrs[k] = rd_addr_reg[k];
    rd_addr_reg[0] = m1; rd_addr_reg[1] = m2; rd_addr_reg[2] = i1; rd_addr_reg[3] = i2;
    if (ghost_int_v_) { int_sel_now_ = true; int_sel_uop_now_ = ghost_int_uop_; }
    else if (wi >= 0) { int_sel_now_ = true; int_sel_uop_now_ = iq_selected(int_iq_, wi); }
    else { int_sel_now_ = false; int_sel_uop_now_.clear(); }
    if (int_sel_now_)
      int_sel_uop_now_.csr_cmd = csr_register_read_cmd(int_sel_uop_now_.csr_cmd, int_sel_uop_now_.prs1);
    if (ghost_mem_v_) { mem_sel_now_ = true; mem_sel_uop_now_ = ghost_mem_uop_; }
    else if (wm >= 0) { mem_sel_now_ = true; mem_sel_uop_now_ = iq_selected(mem_iq_, wm); }
    else { mem_sel_now_ = false; mem_sel_uop_now_.clear(); }
  }

  // Dispatch copies for the two queues (the MEM copy of an FP store waits
  // only on its address operand).
  const MicroOp& du = disp_;
  const bool disp_v = dis_fire_ && !du.exception && !du.is_fence && !du.is_fencei;
  const bool to_mem = disp_v && (du.iq_type & IQT_MEM);
  const bool int_disv = disp_v && !to_mem && (du.iq_type & IQT_INT);
  const bool mem_disv = to_mem;
  MicroOp mem_du_storage;
  const MicroOp* mem_du = &du;
  if (to_mem && du.uopc == uopSTA && du.lrs2_rtype == RT_FLT) {
    mem_du_storage = du;
    mem_du_storage.lrs2_rtype = RT_X;
    mem_du_storage.prs2_busy = 0;
    mem_du = &mem_du_storage;
  }

  // A killed partial-store ghost still rewrites the stored payload (unless
  // an ld_miss squash cancels the grant mutation).
  auto apply_ghost_partial = [&](Iq& q, int slot, bool poison) {
    if (slot < 0) return;
    if (ld_miss && poison) return;
    if (q.p1[slot]) { q.uopc[slot] = uopSTD; q.rt1[slot] = RT_X; }
    else q.rt2[slot] = RT_X;
    q.packed[slot] = pack_iq_slot(q.uopc[slot], q.br_mask[slot], q.rt1[slot], q.rt2[slot]);
  };
  if constexpr (kInternalSignalContract) {
    apply_ghost_partial(int_iq_, ghost_int_partial_slot_, ghost_int_poison_);
    apply_ghost_partial(mem_iq_, ghost_mem_partial_slot_, ghost_mem_poison_);
  }
  const int int_ghost_vacate = (ghost_int_v_ && !(ld_miss && ghost_int_poison_)) ? ghost_int_slot_ : -1;
  const int mem_ghost_vacate = (ghost_mem_v_ && !(ld_miss && ghost_mem_poison_)) ? ghost_mem_slot_ : -1;

  int int_grant_slot = -1, mem_grant_slot = -1, int_avail = 0, mem_avail = 0;
  StageUop int_grant, mem_grant;
  const bool int_iss = iq_collapse(int_iq_, cur_int_fu_, int_iq_start_valid_, int_port_consumed_,
                                   int_disv, du, int_ghost_vacate, int_squash_slot,
                                   int_grant_slot, int_grant, int_avail);
  if (int_iss) int_grant.csr_cmd = csr_register_read_cmd(int_grant.csr_cmd, int_grant.prs1);
  int_iss_fired_ = int_iss;
  const bool mem_iss = iq_collapse(mem_iq_, mem_fu_now, mem_iq_start_valid_, mem_port_consumed_,
                                   mem_disv, *mem_du, mem_ghost_vacate, mem_squash_slot,
                                   mem_grant_slot, mem_grant, mem_avail);
  mem_iss_fired_ = mem_iss;
  mem_iss_load_now_ = (mem_iss || mem_port_consumed_) && mem_sel_now_ && mem_sel_uop_now_.uses_ldq();
  mem_iss_vmir_ = mem_iss;
  *int_iq_.ready = bit(int_avail > 0);
  *mem_iq_.ready = bit(mem_avail > 0);

  const bool fp_disp_v = dis_fire_ && !du.exception && !du.is_fence && !du.is_fencei &&
                         (du.iq_type & IQT_FP);
  fp_issue_step(fp_disp_v);

  // Fast wakeup of a bypassable ALU op at issue (takes effect next edge).
  bool fast = false;
  if (int_iss) {
    const MicroOp& g = inst_[int_grant.rob];
    if (g.bypassable && g.dst_rtype == RT_FIX && g.ldst_val) {
      fast = true;
      busy_ &= ~boomcfg::pm_bit(g.pdst);
      iq_wake(int_iq_, g.pdst);
      iq_wake(mem_iq_, g.pdst);
    }
  }
  if (kInternalSignalContract && ghost_fast_wake_pdst_ && !(ld_miss && ghost_int_poison_)) {
    const uint8_t p = ghost_fast_wake_pdst_;
    busy_ &= ~boomcfg::pm_bit(p);
    iq_wake(int_iq_, p);
    iq_wake(mem_iq_, p);
  }
  // ldspec-miss revert; poison lives one cycle.
  if (iq_any_poison_) {
    for (Iq* q : {&int_iq_, &mem_iq_}) {
      if (ld_miss) {
        const uint64_t m1 = load8(q->p1_poison), m2 = load8(q->p2_poison);
        store8(q->p1, load8(q->p1) & ~m1);
        store8(q->p2, load8(q->p2) & ~m2);
      }
      store8(q->p1_poison, 0);
      store8(q->p2_poison, 0);
    }
    iq_any_poison_ = false;
  }
  if (spec_s1_.v) {
    iq_any_poison_ |= iq_spec_wake(int_iq_, spec_s1_.pdst);
    iq_any_poison_ |= iq_spec_wake(mem_iq_, spec_s1_.pdst);
  }
  spec_bcast_now_ = spec_s1_.v;

  // Integer execute launch.
  if (int_iss) {
    const MicroOp& g = inst_[int_grant.rob];
    if (g.fu_code & FU_I2F) {
      fp_i2f_launch(g, issue_prf_read(int_grant.prs1, int_grant.lrs1_rtype));
    } else {
      const uint64_t r1 = issue_prf_read(int_grant.prs1, int_grant.lrs1_rtype);
      const uint64_t r2 = issue_prf_read(int_grant.prs2, int_grant.lrs2_rtype);
      uint64_t result;
      if (g.fu_code & FU_CSR) {
        result = compute_csr_rdata(g.csr_addr);
        // The CSR file write rides the exe unit's registered response: the
        // MUL-padded Small port responds at issue+5 (int_fixed_wb_latency).
        csr_wr_pend_.v = true;
        csr_wr_pend_.left = 5;
        csr_wr_pend_.rob = int_grant.rob;
        csr_wr_pend_.csr_cmd = int_grant.csr_cmd;
        csr_wr_pend_.r1 = r1;
      } else {
        result = compute_int_result(g, r1, r2);
      }
      if (g.ldst_val && g.pdst != 0) prf_.wr(g.pdst, result);
      int_iss_result_ = (g.fu_code & FU_CSR) ? compute_int_result(g, r1, r2) : result;
      uint8_t lat = 5;   // ALU responses are padded to the MUL latency of the port
      const bool is_div = (g.fu_code & FU_DIV) != 0;
      if (g.fu_code & FU_MUL)
        mul_req_ = MulReq{true, 2, r1, r2, g.ctrl.op_fcn, g.ctrl.fcn_dw, int_grant.br_mask};
      if (is_div) {
        div_req_ = DivReq{true, 2, r1, r2, g.ctrl.op_fcn, g.ctrl.fcn_dw, int_grant};
        lat = div_latency(g.ctrl.op_fcn, g.ctrl.fcn_dw, r1, r2);
        div_block_from_ = cycle_count_ + 1;
        div_block_until_ = cycle_count_ + lat;
      }
      wb_schedule(int_grant.rob, g.pdst, lat, !fast, result, int_grant.br_mask,
                  g.dst_rtype == RT_FIX, is_div, (g.fu_code & FU_MUL) != 0);
      if (g.is_br || g.is_jalr) {
        const uint8_t sel = branch_pc_sel(g.ctrl.br_type, r1, r2);
        const uint64_t seq = g.debug_pc + (g.is_rvc ? 2 : 4);
        uint64_t target; bool mispredict;
        if (sel == PC_JALR) { target = (r1 + decode_imm(g)) & ~1ULL; mispredict = target != seq; }
        else if (sel == PC_BRJMP) { target = g.debug_pc + decode_imm(g); mispredict = !g.taken; }
        else { target = seq; mispredict = g.taken; }
        br_inject_.v = true;
        br_inject_.tag = g.br_tag;
        br_inject_.mispredict = mispredict;
        br_inject_.taken = sel != PC_PLUS4;
        br_inject_.target = target;
        br_inject_.ftq_idx = g.ftq_idx;
        br_inject_.rob_idx = int_grant.rob;
        br_inject_.ldq_idx = g.ldq_idx;
        br_inject_.stq_idx = g.stq_idx;
        br_inject_.br_mask = int_grant.br_mask;
        br_inject_.pc_lob = g.pc_lob;
        br_inject_.is_jalr = g.is_jalr;
      }
    }
  }

  // MEM-issued uop -> issue->AGU pipeline (payload follows the select mux).
  mem_iss_.v = mem_iss;
  if (mem_iss) mem_iss_.u = mem_grant;
  else if (mem_sel_now_) mem_iss_.u = mem_sel_uop_now_;
  else mem_iss_.u.clear();
  if (mem_iss) {
    mem_iss_rs1_ = issue_prf_read(mem_grant.prs1, mem_grant.lrs1_rtype);
    mem_iss_rs2_ = issue_prf_read(mem_grant.prs2, mem_grant.lrs2_rtype);
  } else {
    mem_iss_rs1_ = mem_iss_rs2_ = 0;
  }
  // RegisterReadDecode recomputes the ctrl bits from the selected copy and
  // zeroes the immediate of AMO address generation / LR.
  {
    StageUop& s = mem_iss_.u;
    uint16_t f = s.flags & ~(StageUop::kIsLoad | StageUop::kIsSta | StageUop::kIsStd);
    if (s.uopc == uopLD) f |= StageUop::kIsLoad;
    const bool sta = s.uopc == uopSTA || s.uopc == uopAMO_AG;
    if (sta) f |= StageUop::kIsSta;
    if (s.uopc == uopSTD || (sta && s.lrs2_rtype == RT_FIX)) f |= StageUop::kIsStd;
    s.flags = f;
    if (s.uopc == uopAMO_AG || (s.uopc == uopLD && s.mem_cmd == 6)) s.imm_packed = 0;
  }
}

}  // namespace chisa::boom_model
