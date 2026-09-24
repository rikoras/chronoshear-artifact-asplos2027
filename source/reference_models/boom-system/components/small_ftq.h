#pragma once
// ============================================================================
// Small BOOM Fetch Target Queue (ftqSz=16, nBanks=1).
//
// This slice owns the queue/control pointers, the complete logical FTQBundle
// RAM, its global-history snapshots, the registered redirect-repair path, and
// the complete branch-predictor update pipeline.
//
// Transcribed from fetch-target-queue.scala in the locked BOOM elaboration.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "small_fetch_buffer.h"

namespace chisa::boom_system::components {

struct SmallFtqEntry {
  bool cfi_valid = false;
  std::uint8_t cfi_idx = 0;
  bool cfi_taken = false;
  bool cfi_mispredicted = false;
  std::uint8_t cfi_type = 0;
  std::uint8_t br_mask = 0;
  bool cfi_is_call = false;
  bool cfi_is_ret = false;
  bool cfi_npc_plus4 = false;
  std::uint64_t ras_top = 0;
  std::uint8_t ras_idx = 0;
  bool start_bank = false;
};

struct SmallFtqGetPcResponse {
  SmallFtqEntry entry{};
  SmallGlobalHistory ghist{};
  std::uint64_t pc = 0;
  std::uint64_t next_pc = 0;
  bool next_valid = false;
  std::uint64_t commit_pc = 0;
};

struct SmallFtqBpdUpdate {
  bool is_mispredict_update = false;
  bool is_repair_update = false;
  std::uint8_t btb_mispredicts = 0;
  std::uint64_t pc = 0;
  std::uint8_t br_mask = 0;
  bool cfi_valid = false;
  std::uint8_t cfi_idx = 0;
  bool cfi_taken = false;
  bool cfi_mispredicted = false;
  bool cfi_is_br = false;
  bool cfi_is_jal = false;
  bool cfi_is_jalr = false;
  SmallGlobalHistory ghist{};
  bool lhist = false;
  std::uint64_t target = 0;
  std::array<std::uint32_t, boomcfg::BPD_META_WORDS> meta{};
};

struct SmallFtqInputs {
  bool reset = false;

  bool enq_valid = false;
  SmallFetchBundle enq{};

  bool deq_valid = false;
  std::uint8_t deq_idx = 0;

  bool redirect_valid = false;
  std::uint8_t redirect_idx = 0;

  bool brupdate_mispredict = false;
  std::uint8_t brupdate_ftq_idx = 0;
  std::uint8_t brupdate_pc_lob = 0;
  bool brupdate_taken = false;

  std::array<std::uint8_t, 2> get_pc_idx{};
  // When set, the enqueued bundle is read from the caller's evaluation
  // object instead of the copy in `enq`.
  const SmallFetchBundle* enq_ref = nullptr;
};

struct SmallFtqOutputs {
  bool enq_ready = false;
  std::uint8_t enq_idx = 1;
  bool full = false;
  bool do_commit_update = false;
  bool bpdupdate_valid = false;
  SmallFtqBpdUpdate bpdupdate{};
  bool ras_update = false;
  std::uint8_t ras_update_idx = 0;
  std::uint64_t ras_update_pc = 0;
  std::array<SmallFtqGetPcResponse, 2> get_pc{};
};

class SmallFtqState {
 public:
  SmallFtqOutputs outputs(const SmallFtqInputs& input) const {

    SmallFtqOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallFtqInputs& input, SmallFtqOutputs& result) const {
    result = SmallFtqOutputs{};
    result.enq_ready = ready_reg_;
    result.enq_idx = enq_ptr_;
    result.full = increment(increment(enq_ptr_)) == bpd_ptr_ ||
                  increment(enq_ptr_) == bpd_ptr_;
    result.do_commit_update = do_commit_update(input);
    result.bpdupdate_valid =
        bpdupdate_pipe_valid_ && !first_empty_ &&
        (bpd_entry_.cfi_valid || bpd_entry_.br_mask != 0) &&
        !(bpdupdate_pipe_repair_ && bpd_pc_ == bpd_repair_pc_);
    result.bpdupdate.is_mispredict_update =
        bpdupdate_pipe_mispredict_;
    result.bpdupdate.is_repair_update = bpdupdate_pipe_repair_;
    result.bpdupdate.pc = bpd_pc_ & kPcMask;
    result.bpdupdate.br_mask = bpd_entry_.cfi_valid
                                   ? static_cast<std::uint8_t>(
                                         mask_lower(bpd_entry_.cfi_idx) &
                                         bpd_entry_.br_mask)
                                   : bpd_entry_.br_mask;
    result.bpdupdate.cfi_valid = bpd_entry_.cfi_valid;
    result.bpdupdate.cfi_idx =
        static_cast<std::uint8_t>(bpd_entry_.cfi_idx &
                                  (boomcfg::FETCH_WIDTH - 1));
    result.bpdupdate.cfi_taken = bpd_entry_.cfi_taken;
    result.bpdupdate.cfi_mispredicted = bpd_entry_.cfi_mispredicted;
    result.bpdupdate.cfi_is_br =
        ((bpd_entry_.br_mask >> result.bpdupdate.cfi_idx) & 1u) != 0;
    result.bpdupdate.cfi_is_jal =
        bpd_entry_.cfi_type == 2 || bpd_entry_.cfi_type == 3;
    // The locked SmallBoom elaboration has useLHist=false and leaves the
    // separately declared cfi_is_jalr field at its elaborated zero value.
    result.bpdupdate.ghist = bpd_ghist_;
    result.bpdupdate.target = bpd_target_ & kPcMask;
    result.bpdupdate.meta = bpd_meta_;
    result.ras_update = ras_update_;
    result.ras_update_idx = ras_update_idx_;
    result.ras_update_pc = ras_update_pc_;
    result.get_pc = get_pc_;
    return;
  }

  bool do_commit_update(const SmallFtqInputs& input) const {
    return !bpd_update_mispredict_ && !bpd_update_repair_ &&
           bpd_ptr_ != deq_ptr_ && enq_ptr_ != increment(bpd_ptr_) &&
           !input.brupdate_mispredict && !input.redirect_valid &&
           !prev_redirect_;
  }

  void commit(const SmallFtqInputs& input,
              const SmallFtqOutputs& output) {
    const SmallFetchBundle& enq_bundle = input.enq_ref != nullptr ? *input.enq_ref : input.enq;
    oracle_do_commit_ = output.do_commit_update ||
                        bpd_update_repair_ || bpd_update_mispredict_;
    const bool do_enq = input.enq_valid && output.enq_ready;
    const SmallFtqEntry enqueued_entry = make_entry(enq_bundle);
    const SmallGlobalHistory enqueued_ghist =
        enq_bundle.ghist.current_saw_branch_not_taken
            ? normalized_history(enq_bundle.ghist)
            : update_history(prev_ghist_, prev_entry_, prev_pc_);

    const std::uint8_t bpd_idx = input.redirect_valid
                                     ? mask_index(input.redirect_idx)
                                     : ((bpd_update_repair_ ||
                                         bpd_update_mispredict_)
                                            ? bpd_repair_idx_
                                            : bpd_ptr_);
    // Oracle exports: remember this step's combinational read-port indices.
    oracle_ram_idx_[0] = bpd_idx;
    oracle_ghist0_ = ghists_[bpd_idx];
    oracle_ram_idx_[1] = mask_index(input.redirect_idx);

    // All reads below see the cycle-start Reg(Vec)/SyncReadMem contents.
    // Capture them before either the enqueue or redirect-repair write.
    const SmallFtqEntry next_bpd_entry = entries_[bpd_idx];
    const SmallGlobalHistory next_bpd_ghist = ghists_[bpd_idx];
    const std::array<std::uint32_t, boomcfg::BPD_META_WORDS> next_bpd_meta =
        metas_[bpd_idx];
    const std::uint64_t next_bpd_pc = pcs_[bpd_idx];
    const std::uint64_t next_bpd_target = pcs_[increment(bpd_idx)];

    const std::uint8_t redirect_idx = mask_index(input.redirect_idx);
    const SmallFtqEntry redirect_entry = entries_[redirect_idx];
    SmallFtqEntry redirect_new_entry = redirect_entry;
    if (input.redirect_valid && input.brupdate_mispredict) {
      const std::uint8_t bank_xor =
          redirect_entry.start_bank ? std::uint8_t{8} : std::uint8_t{0};
      const std::uint8_t new_cfi_idx = static_cast<std::uint8_t>(
          ((input.brupdate_pc_lob ^ bank_xor) >> 1u) &
          (boomcfg::FETCH_WIDTH - 1));
      redirect_new_entry.cfi_valid = true;
      redirect_new_entry.cfi_idx = new_cfi_idx;
      redirect_new_entry.cfi_mispredicted = true;
      redirect_new_entry.cfi_taken = input.brupdate_taken;
      redirect_new_entry.cfi_is_call =
          redirect_entry.cfi_is_call &&
          redirect_entry.cfi_idx == new_cfi_idx;
      redirect_new_entry.cfi_is_ret =
          redirect_entry.cfi_is_ret &&
          redirect_entry.cfi_idx == new_cfi_idx;
    }

    const std::uint64_t next_ras_update_pc =
        input.redirect_valid ? redirect_entry.ras_top : 0;
    const std::uint8_t next_ras_update_idx =
        input.redirect_valid ? redirect_entry.ras_idx : 0;
    const bool next_ready = !output.full || output.do_commit_update;
    const bool next_first_empty =
        bpdupdate_pipe_valid_ ? false : first_empty_;
    const bool next_bpdupdate_pipe_valid =
        output.do_commit_update || bpd_update_repair_ ||
        bpd_update_mispredict_;
    const bool next_bpdupdate_pipe_mispredict =
        bpd_update_mispredict_;
    const bool next_bpdupdate_pipe_repair = bpd_update_repair_;

    // Both core lookup ports are registered.  Port 1's history comes from a
    // synchronous memory with the same one-cycle address-to-data latency;
    // port 0 history is DontCare in the source and is left zero here.  The
    // explicit next-PC forwarding is the source's same-edge enqueue bypass.
    std::array<SmallFtqGetPcResponse, 2> next_get_pc{};
    const std::uint8_t commit_idx = mask_index(
        input.deq_valid ? input.deq_idx : deq_ptr_);
    for (std::size_t port = 0; port < next_get_pc.size(); ++port) {
      const std::uint8_t index = mask_index(input.get_pc_idx[port]);
      const std::uint8_t next_index = increment(index);
      const bool next_is_enq = next_index == enq_ptr_ && do_enq;
      next_get_pc[port].entry = entries_[index];
      oracle_ram_idx_[2 + port] = index;
      if (port == 1)
        oracle_getpc1_ghist_ =
            do_enq && index == enq_ptr_ ? enqueued_ghist : ghists_[index];
      if (port == 1) {
        // The locked Verilator SyncReadMem implementation registers the
        // address and then observes the post-edge memory array.  A read and
        // enqueue write to the same address therefore returns the new value.
        next_get_pc[port].ghist =
            do_enq && index == enq_ptr_ ? enqueued_ghist : ghists_[index];
      }
      next_get_pc[port].pc = pcs_[index];
      next_get_pc[port].next_pc =
          next_is_enq ? enq_bundle.pc & kPcMask : pcs_[next_index];
      next_get_pc[port].next_valid =
          next_index != enq_ptr_ || next_is_enq;
      next_get_pc[port].commit_pc = pcs_[commit_idx];
    }

    // W=1 ESSENT has no same-lane state-array forwarding: every FTQ read tap
    // sees the cycle-start array, even when this edge writes the same row.
    for (std::size_t p = 0; p < 4; ++p)
      oracle_ram_read_[p] = pack_entry(entries_[oracle_ram_idx_[p]]);

    std::uint8_t next_enq_ptr = enq_ptr_;
    std::uint8_t next_deq_ptr = deq_ptr_;
    std::uint8_t next_bpd_ptr = bpd_ptr_;
    bool next_update_mispredict = bpd_update_mispredict_;
    bool next_update_repair = bpd_update_repair_;
    std::uint8_t next_repair_idx = bpd_repair_idx_;
    std::uint8_t next_end_idx = bpd_end_idx_;
    std::uint64_t next_repair_pc = bpd_repair_pc_;
    SmallFtqEntry next_prev_entry = prev_entry_;
    SmallGlobalHistory next_prev_ghist = prev_ghist_;
    std::uint64_t next_prev_pc = prev_pc_;

    if (do_enq) {
      pcs_[enq_ptr_] = enq_bundle.pc & kPcMask;
      entries_[enq_ptr_] = enqueued_entry;
      ++entry_epochs_[enq_ptr_];
      ++entry_epoch_;
      oracle_written_ |= std::uint8_t(1u << (enq_ptr_ & 7));
      {
        static const bool dbg = getenv("SYSFTQ_DEBUG") != nullptr;
        static unsigned long long n2 = 0;
        if (dbg && ++n2 <= 4)
          fprintf(stderr, "[FTQENQ] ptr=%u packed=%llx\n", (unsigned)enq_ptr_,
                  (unsigned long long)pack_entry(enqueued_entry));
      }
      ghists_[enq_ptr_] = enqueued_ghist;
      metas_[enq_ptr_] = enq_bundle.bpd_meta;
      for (int b = 0; b < boomcfg::NBANKS; ++b) {
        metas_[enq_ptr_][4 * b + 3] &= 0x00ffffffu;
      }
      next_prev_pc = enq_bundle.pc & kPcMask;
      next_prev_entry = enqueued_entry;
      next_prev_ghist = enqueued_ghist;
      next_enq_ptr = increment(enq_ptr_);
    }
    if (input.deq_valid) next_deq_ptr = mask_index(input.deq_idx);

    // BPD update state machine.  Every RegNext operand below is represented
    // by an explicit old-state pipeline register.
    if (input.redirect_valid) {
      next_update_mispredict = false;
      next_update_repair = false;
    } else if (prev_brupdate_mispredict_) {
      next_update_mispredict = true;
      next_repair_idx = prev_brupdate_ftq_idx_;
      next_end_idx = prev_enq_ptr_;
    } else if (bpd_update_mispredict_) {
      next_update_mispredict = false;
      next_update_repair = true;
      next_repair_idx = increment(bpd_repair_idx_);
    } else if (bpd_update_repair_ && prev_bpd_update_mispredict_) {
      next_repair_pc = bpd_pc_;
      next_repair_idx = increment(bpd_repair_idx_);
    } else if (bpd_update_repair_) {
      next_repair_idx = increment(bpd_repair_idx_);
      if (increment(bpd_repair_idx_) == bpd_end_idx_ ||
          bpd_pc_ == bpd_repair_pc_) {
        next_update_repair = false;
      }
    }

    if (output.do_commit_update) next_bpd_ptr = increment(bpd_ptr_);
    // The redirect assignment appears later than do_enq in Chisel and wins.
    if (input.redirect_valid) next_enq_ptr = increment(input.redirect_idx);

    // The `elsewhen (RegNext(io.redirect.valid))` repair is one cycle late.
    // It appears after the ordinary enqueue writes, so it wins on collision.
    if (!input.redirect_valid && prev_redirect_) {
      entries_[prev_redirect_idx_] = redirect_entry_pipe_;
      ++entry_epochs_[prev_redirect_idx_];
      ++entry_epoch_;
      next_prev_entry = redirect_entry_pipe_;
      next_prev_ghist = bpd_ghist_;
      next_prev_pc = bpd_pc_;
    }

    // Plain RegNext state advances even while synchronous reset is asserted.
    ready_reg_ = next_ready;
    prev_redirect_ = input.redirect_valid;
    prev_redirect_idx_ = redirect_idx;
    redirect_entry_pipe_ = redirect_new_entry;
    prev_brupdate_mispredict_ = input.brupdate_mispredict;
    prev_brupdate_ftq_idx_ = mask_index(input.brupdate_ftq_idx);
    prev_bpd_update_mispredict_ = bpd_update_mispredict_;
    prev_enq_ptr_ = enq_ptr_;
    bpd_entry_ = next_bpd_entry;
    bpd_ghist_ = next_bpd_ghist;
    bpd_meta_ = next_bpd_meta;
    bpd_pc_ = next_bpd_pc;
    bpd_target_ = next_bpd_target;
    ras_update_ = input.redirect_valid;
    ras_update_idx_ = next_ras_update_idx;
    ras_update_pc_ = next_ras_update_pc;
    get_pc_ = next_get_pc;
    first_empty_ = next_first_empty;
    bpdupdate_pipe_valid_ = next_bpdupdate_pipe_valid;
    bpdupdate_pipe_mispredict_ = next_bpdupdate_pipe_mispredict;
    bpdupdate_pipe_repair_ = next_bpdupdate_pipe_repair;

    enq_ptr_ = next_enq_ptr;
    deq_ptr_ = next_deq_ptr;
    bpd_ptr_ = next_bpd_ptr;
    bpd_update_mispredict_ = next_update_mispredict;
    bpd_update_repair_ = next_update_repair;
    bpd_repair_idx_ = next_repair_idx;
    bpd_end_idx_ = next_end_idx;
    bpd_repair_pc_ = next_repair_pc;
    prev_entry_ = next_prev_entry;
    prev_ghist_ = next_prev_ghist;
    prev_pc_ = next_prev_pc;

    if (input.reset) {
      bpd_ptr_ = 0;
      deq_ptr_ = 0;
      enq_ptr_ = 1;
      bpd_update_mispredict_ = false;
      bpd_update_repair_ = false;
      first_empty_ = true;
      prev_entry_ = SmallFtqEntry{};
      prev_ghist_ = SmallGlobalHistory{};
      prev_pc_ = 0;
    }
  }

  void step(const SmallFtqInputs& input) {
    commit(input, outputs(input));
  }

  const std::uint8_t& enq_idx() const { return enq_ptr_; }
  std::uint8_t deq_idx() const { return deq_ptr_; }
  std::uint8_t bpd_idx() const { return bpd_ptr_; }
  bool enq_ready() const { return ready_reg_; }
  bool update_mispredict() const { return bpd_update_mispredict_; }
  bool update_repair() const { return bpd_update_repair_; }
  bool first_empty() const { return first_empty_; }
  bool bpdupdate_pipe_valid() const { return bpdupdate_pipe_valid_; }
  bool bpdupdate_pipe_mispredict() const {
    return bpdupdate_pipe_mispredict_;
  }
  const bool& bpdupdate_pipe_repair() const { return bpdupdate_pipe_repair_; }
  const std::uint8_t& repair_idx() const { return bpd_repair_idx_; }
  const std::uint8_t& end_idx() const { return bpd_end_idx_; }
  const std::uint64_t& bpd_pc() const { return bpd_pc_; }
  const bool& update_repair_flag() const { return bpd_update_repair_; }
  const bool& update_mispredict_flag() const { return bpd_update_mispredict_; }
  const std::uint8_t& bpd_read_ptr() const { return bpd_ptr_; }
  const std::uint64_t& oracle_ram_read(std::size_t port) const {
    return oracle_ram_read_[port];
  }
  const std::uint8_t& oracle_ram_idx(std::size_t port) const {
    return oracle_ram_idx_[port];
  }
  const SmallGlobalHistory& oracle_ghist0() const { return oracle_ghist0_; }
  const SmallGlobalHistory& oracle_getpc1_ghist() const {
    return oracle_getpc1_ghist_;
  }
  const bool& oracle_do_commit() const { return oracle_do_commit_; }
  bool oracle_written(std::size_t idx) const {
    return (oracle_written_ >> (idx & 7)) & 1u;
  }
  // Packed 61-bit FTQ entry, matching the v2 state-array layout.
  static std::uint64_t pack_entry(const SmallFtqEntry& e) {
    return (std::uint64_t(e.cfi_valid) << 60) |
           ((std::uint64_t(e.cfi_idx) & 3) << 58) |
           (std::uint64_t(e.cfi_taken) << 57) |
           (std::uint64_t(e.cfi_mispredicted) << 56) |
           ((std::uint64_t(e.cfi_type) & 7) << 53) |
           ((std::uint64_t(e.br_mask) & 0xf) << 49) |
           (std::uint64_t(e.cfi_is_call) << 48) |
           (std::uint64_t(e.cfi_is_ret) << 47) |
           (std::uint64_t(e.cfi_npc_plus4) << 46) |
           ((std::uint64_t(e.ras_top) & UINT64_C(0xffffffffff)) << 6) |
           ((std::uint64_t(e.ras_idx) & 0x1f) << 1) |
           (std::uint64_t(e.start_bank) & 1);
  }
  std::uint64_t bpd_target() const { return bpd_target_; }
  const std::uint64_t& repair_pc() const { return bpd_repair_pc_; }
  std::uint64_t pc(std::size_t index) const { return pcs_[index]; }
  const SmallFtqEntry& entry(std::size_t index) const {
    return entries_[index];
  }
  const std::uint64_t& entry_epoch_for_diagnostic() const {
    return entry_epoch_;
  }
  const std::uint64_t& entry_epoch_for_diagnostic(
      std::size_t index) const {
    return entry_epochs_[index];
  }
  const SmallGlobalHistory& ghist(std::size_t index) const {
    return ghists_[index];
  }
  const std::array<std::uint32_t, boomcfg::BPD_META_WORDS>& meta(
      std::size_t index) const {
    return metas_[index];
  }
  const SmallFtqEntry& bpd_entry() const { return bpd_entry_; }
  const SmallGlobalHistory& bpd_ghist() const { return bpd_ghist_; }
  const std::array<std::uint32_t, boomcfg::BPD_META_WORDS>& bpd_meta() const {
    return bpd_meta_;
  }
  const SmallFtqEntry& redirect_entry_pipeline() const {
    return redirect_entry_pipe_;
  }
  const SmallFtqEntry& previous_entry() const { return prev_entry_; }
  const SmallGlobalHistory& previous_ghist() const { return prev_ghist_; }
  std::uint64_t previous_pc() const { return prev_pc_; }
  std::uint64_t ras_top(std::size_t index) const {
    return entries_[index].ras_top;
  }
  std::uint8_t ras_idx(std::size_t index) const {
    return entries_[index].ras_idx;
  }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);

  static std::uint8_t mask_index(std::uint8_t index) {
    return static_cast<std::uint8_t>(index & (boomcfg::NUM_FTQ - 1));
  }

  static std::uint8_t increment(std::uint8_t index) {
    return static_cast<std::uint8_t>((index + 1u) & (boomcfg::NUM_FTQ - 1));
  }

  static std::uint8_t mask_lower(std::uint8_t index) {
    return static_cast<std::uint8_t>(
        ((std::uint16_t{1} << ((index & (boomcfg::FETCH_WIDTH - 1)) + 1u)) - 1u) &
        ((1u << boomcfg::FETCH_WIDTH) - 1u));
  }

  static SmallGlobalHistory normalized_history(
      const SmallGlobalHistory& input) {
    SmallGlobalHistory result = input;
    result.ras_idx = static_cast<std::uint8_t>(result.ras_idx & 0x1fu);
    return result;
  }

  static SmallFtqEntry make_entry(const SmallFetchBundle& bundle) {
    SmallFtqEntry result;
    result.cfi_valid = bundle.cfi_valid;
    result.cfi_idx = static_cast<std::uint8_t>(
        bundle.cfi_idx & (boomcfg::FETCH_WIDTH - 1));
    result.cfi_taken = bundle.cfi_valid;
    result.cfi_mispredicted = false;
    result.cfi_type = static_cast<std::uint8_t>(bundle.cfi_type & 0x07u);
    result.br_mask = static_cast<std::uint8_t>(
        bundle.br_mask & bundle.mask & ((1u << boomcfg::FETCH_WIDTH) - 1u));
    result.cfi_is_call = bundle.cfi_is_call;
    result.cfi_is_ret = bundle.cfi_is_ret;
    result.cfi_npc_plus4 = bundle.cfi_npc_plus4;
    result.ras_top = bundle.ras_top & kPcMask;
    result.ras_idx = static_cast<std::uint8_t>(bundle.ghist.ras_idx & 0x1fu);
    result.start_bank = boomcfg::fetch_bank_one(bundle.pc);
    return result;
  }

  static SmallGlobalHistory update_history(
      const SmallGlobalHistory& history, const SmallFtqEntry& entry,
      std::uint64_t pc = 0) {
    const unsigned cfi_fixed = entry.cfi_idx & (boomcfg::FETCH_WIDTH - 1);
    const std::uint8_t cfi_oh =
        static_cast<std::uint8_t>(1u << cfi_fixed);
    const std::uint8_t mask_lower =
        static_cast<std::uint8_t>((cfi_oh << 1u) - 1u);
    const std::uint8_t selected = static_cast<std::uint8_t>(
        entry.cfi_valid ? mask_lower : ((1u << boomcfg::FETCH_WIDTH) - 1u));
    const bool cfi_is_br = ((entry.br_mask >> cfi_fixed) & 1u) != 0;
    const std::uint8_t taken_cfi =
        cfi_is_br && entry.cfi_taken ? cfi_oh : 0u;
    const std::uint8_t not_taken = static_cast<std::uint8_t>(
        entry.br_mask & selected & static_cast<std::uint8_t>(~taken_cfi));

    SmallGlobalHistory result;
    advance_global_history(history, not_taken, cfi_is_br, entry.cfi_taken,
                           entry.cfi_valid, cfi_fixed, pc, result);
    if (entry.cfi_valid && entry.cfi_is_call)
      result.ras_idx =
          static_cast<std::uint8_t>((history.ras_idx + 1u) & 0x1fu);
    else if (entry.cfi_valid && entry.cfi_is_ret)
      result.ras_idx =
          static_cast<std::uint8_t>((history.ras_idx - 1u) & 0x1fu);
    else
      result.ras_idx = static_cast<std::uint8_t>(history.ras_idx & 0x1fu);
    return result;
  }

  std::array<std::uint64_t, boomcfg::NUM_FTQ> pcs_{};  // unreset RTL Reg(Vec(...))
  std::array<SmallFtqEntry, boomcfg::NUM_FTQ> entries_{};
  std::array<std::uint64_t, boomcfg::NUM_FTQ> entry_epochs_{};
  std::uint64_t entry_epoch_ = 0;
  std::array<SmallGlobalHistory, boomcfg::NUM_FTQ> ghists_{};
  std::array<std::array<std::uint32_t, boomcfg::BPD_META_WORDS>,
             boomcfg::NUM_FTQ> metas_{};

  std::uint8_t bpd_ptr_ = 0;
  std::array<std::uint64_t, 4> oracle_ram_read_{};
  std::array<std::uint8_t, 4> oracle_ram_idx_{};
  SmallGlobalHistory oracle_ghist0_{}, oracle_getpc1_ghist_{};
  bool oracle_do_commit_ = false;
  std::uint8_t oracle_written_ = 0;
  std::uint8_t deq_ptr_ = 0;
  std::uint8_t enq_ptr_ = 1;
  bool ready_reg_ = false;  // RegNext without reset

  SmallGlobalHistory prev_ghist_{};  // RegInit
  SmallFtqEntry prev_entry_{};       // RegInit
  std::uint64_t prev_pc_ = 0;        // RegInit

  bool bpd_update_mispredict_ = false;
  bool bpd_update_repair_ = false;
  bool first_empty_ = true;
  bool bpdupdate_pipe_valid_ = false;
  bool bpdupdate_pipe_mispredict_ = false;
  bool bpdupdate_pipe_repair_ = false;
  std::uint8_t bpd_repair_idx_ = 0;
  std::uint8_t bpd_end_idx_ = 0;
  std::uint64_t bpd_repair_pc_ = 0;
  SmallFtqEntry bpd_entry_{};
  SmallGlobalHistory bpd_ghist_{};
  std::array<std::uint32_t, boomcfg::BPD_META_WORDS> bpd_meta_{};
  std::uint64_t bpd_pc_ = 0;
  std::uint64_t bpd_target_ = 0;

  bool prev_redirect_ = false;
  std::uint8_t prev_redirect_idx_ = 0;
  SmallFtqEntry redirect_entry_pipe_{};
  bool prev_brupdate_mispredict_ = false;
  std::uint8_t prev_brupdate_ftq_idx_ = 0;
  bool prev_bpd_update_mispredict_ = false;
  std::uint8_t prev_enq_ptr_ = 0;

  // io.ras_update{,_idx,_pc} are three unreset RegNext outputs.
  bool ras_update_ = false;
  std::uint8_t ras_update_idx_ = 0;
  std::uint64_t ras_update_pc_ = 0;
  std::array<SmallFtqGetPcResponse, 2> get_pc_{};

 public:
  /** The registered get_ftq_pc response (fetch-target-queue.scala:351-358),
    * i.e. what core.io.ifu.get_pc(port) shows on the current cycle. */
  const SmallFtqGetPcResponse& registered_get_pc(std::size_t port) const {
    return get_pc_[port];
  }

 private:
};

}  // namespace chisa::boom_system::components
