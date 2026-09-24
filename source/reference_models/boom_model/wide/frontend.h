#pragma once
#include "../common/frontend_contract.h"
#include "contract.h"
#include "../common/predictor_bank.h"
#include "../common/fetch_queues.h"
#include "../../boom-system/components/small_f3_assembler.h"
#include "frontend_update.h"
#include "../../boom-system/components/small_ftq.h"
#include <array>

namespace chisa::boom_model::wide {
namespace components = chisa::boom_system::components;
using chisa::boom_system::FrontendInputs;
using chisa::boom_system::HeldFetch;
using chisa::boom_system::FrontendHandoff;
using chisa::boom_system::BackendFrontendControl;
using chisa::boom_system::BackendFrontendFeedback;
contract::Image& system_record();

struct FrontendEvaluation {
  bool reset = false, run = false, clear = false;
  components::SmallTlbCycleInputs itlb_input{};
  components::SmallFrontendTlbResponse itlb{};
  components::SmallTlbSfence next_itlb_sfence{};
  components::SmallF0F2Inputs f0_input{};
  components::SmallF0F2Evaluation f0_f2{};
  components::SmallICacheInputs icache_input{};
  components::SmallICacheOutputs icache{};
  components::SmallFtqInputs ftq_input{};
  components::SmallFtqOutputs ftq_output{};
  components::SmallF3AssemblerInputs assembler_input{};
  const components::SmallFtqBpdUpdate* update = nullptr;
  bool update_valid = false, f3_fire = false;
  std::array<fe::BpdIn,boomcfg::NBANKS> bank_input{};
  std::array<components::SmallFtqBpdUpdate,boomcfg::NBANKS> bank_update{};
  bool f4_enq_valid = false, f4_enq_ready = false, f4_deq_ready = false;
  bool fb_enq_valid = false, fb_deq_ready = false;
  std::uint8_t fb_ftq_idx = 0;
  bool main_enq_ready = false, bpd_enq_valid = false, bpd_enq_ready = false, bpd_deq_valid = false;
  std::uint8_t ras_read_idx = 0, ras_write_idx = 0;
  bool ras_write_valid = false;
  std::uint64_t ras_write_addr = 0;
};

class FrontendState {
 public:
  FrontendState();
  HeldFetch held_fetch(bool reset) const;
  void evaluate_into(FrontendEvaluation& output, const FrontendInputs& input,
                     const BackendFrontendFeedback& feedback);
  // All evaluation except the I-cache's current TileLink feedback is
  // independent of the memory fabric. Both phases use the same evaluation.
  void evaluate_independent(FrontendEvaluation& output, const FrontendInputs& input,
                            const BackendFrontendFeedback& feedback);
  void evaluate_memory(FrontendEvaluation& output,
                       const components::SmallICacheMemoryInputs& memory);
  void commit(const FrontendEvaluation& evaluation);
  // The same edge in two halves.  commit_early applies every component whose
  // next state is fixed by the evaluation alone (predictors, F0-F3, I-cache,
  // ITLB, RAS); commit_late applies the FetchBuffer dequeue, the FTQ and F4
  // (they read the backend's same-edge dequeue/get_pc/fetch_ready links) and
  // then publishes the record.  commit_early(e); commit_late(e); is the same
  // transition as commit(e); a worker thread runs the early half while the
  // backend edge is still being evaluated.
  void commit_early(const FrontendEvaluation& evaluation);
  void commit_independent(const FrontendEvaluation& evaluation);
  void commit_memory(const FrontendEvaluation& evaluation);
  // write_lanes = false leaves the record lanes to write_late_record_lanes,
  // which a worker thread calls after signalling the commit (the calling
  // thread's next edge reads only the handoff).
  void commit_late(const FrontendEvaluation& evaluation, bool write_lanes = true);
  void write_late_record_lanes(const FrontendEvaluation& evaluation) { write_record_lanes(evaluation); }
  void held_itlb_cycle_inputs_into(const FrontendInputs& input,
                                  components::SmallTlbCycleInputs& output) const;
  components::SmallTlbCycleInputs held_itlb_cycle_inputs(const FrontendInputs& input) const {
    components::SmallTlbCycleInputs output;held_itlb_cycle_inputs_into(input,output);return output;
  }
  components::SmallICache::AcquireOffer held_icache_acquire() const {
    return icache_.held_acquire_offer(f0_f2_.held_s2_kill());
  }
  // What the next edge reads from this committed state (FrontendHandoff),
  // filled by the thread that committed; the edge builds its ITLB request
  // face from the handoff instead of reading S1 here.
  void fill_handoff(FrontendHandoff& handoff) const;
  static void itlb_cycle_inputs_from(const FrontendHandoff& handoff, const FrontendInputs& input,
                                     components::SmallTlbCycleInputs& output);
  const components::SmallFtqGetPcResponse& ftq_get_pc(unsigned port) const { return ftq_ports_[port]; }
  const components::SmallF0F2& f0_f2_for_diagnostic() const { return f0_f2_; }
  const components::SmallICache& icache_for_diagnostic() const { return icache_; }
  const components::SmallInstructionTlb& itlb_for_diagnostic() const { return itlb_.state_for_diagnostic(); }
  const components::SmallFtqState& ftq_for_diagnostic() const { return ftq_; }
  const components::SmallFetchBuffer& fetch_buffer_for_diagnostic() const { return fetch_buffer_; }
  const fe::F3Queues& f3_queues_for_diagnostic() const { return queues_; }
  const components::SmallF3Assembler& f3_assembler_for_diagnostic() const { return assembler_; }
  const fe::F4Queue& f4_queue_for_diagnostic() const { return f4_; }
  const BpdUpdatePath& bpd_update_path_for_diagnostic() const { return updates_; }
  const fe::Ras& ras_for_diagnostic() const { return ras_; }
  const fe::PredictorBank& predictor(unsigned bank) const { return banks_[bank]; }
  const PredictorBankRegisters& predictor_registers(unsigned bank) const { return record_.r.frontendBpd.bank[bank]; }
  const PredictorBankPorts& predictor_ports(unsigned bank) const { return record_.c.frontendBpd.bank[bank]; }
  const components::SmallF3AssemblerOutputs& assembled() const { return assembled_; }
  const components::SmallBpdResponse& composed_prediction() const { return prediction_; }
  std::uint64_t composed_pc(unsigned stage) const { return predictor_pc_[stage]; }
 private:
  friend struct FrontendTest;
  static bool clear(const FrontendInputs& input) {
    return input.backend_control.sfence_valid || input.backend_control.redirect_flush;
  }
  void compose_predictions();
  void split_updates(FrontendEvaluation& output);
  void write_record_lanes(const FrontendEvaluation& output);
  contract::Image& record_;
 public:
  void set_cut_lanes(bool on) { cut_lanes_ = on; }
 private:
  bool cut_lanes_ = true;   // partition-cut lanes (SYSMODEL_CUT_LANES=0 turns them off)
  std::array<fe::PredictorBank,boomcfg::NBANKS> banks_;
  std::array<std::uint64_t,3> predictor_pc_{};
  std::array<std::uint8_t,boomcfg::NBANKS> predictor_valids_{};
  components::SmallFrontendPredictionResponse prediction_f1_{},prediction_f2_{};
  components::SmallBpdResponse prediction_{};
  components::SmallF0F2 f0_f2_;
  components::SmallICache icache_;
  components::SmallMachineItlb itlb_;
  components::SmallTlbSfence sfence_{};
  fe::F3Queues queues_;
  fe::F4Queue f4_;
  components::SmallF3Assembler assembler_;
  components::SmallF3AssemblerOutputs assembled_{};
  components::SmallFetchBuffer fetch_buffer_;
  components::SmallFtqState ftq_;
  BpdUpdatePath updates_;
  fe::Ras ras_;
  std::uint8_t ras_read_idx_ = 0;
  std::array<components::SmallFtqGetPcResponse,2> ftq_ports_{};
  mutable components::SmallFetchBufferOutputs fetch_offer_{};
  std::uint64_t cycle_ = 0, assemble_main_ = 0, assemble_bpd_ = 0, assemble_ras_ = 0;
  bool assembled_valid_ = false;
  std::uint64_t itlb_epoch_ = ~UINT64_C(0), icache_epoch_ = ~UINT64_C(0);
  std::uint64_t corr_epoch_ = ~UINT64_C(0), fb_epoch_ = 0, ftq_epoch_ = 0;
  std::array<std::uint64_t,boomcfg::NUM_FB_ENTRIES> fb_row_epoch_{};
  std::array<std::uint64_t,32> ftq_row_epoch_{};
};
}  // namespace chisa::boom_model::wide
