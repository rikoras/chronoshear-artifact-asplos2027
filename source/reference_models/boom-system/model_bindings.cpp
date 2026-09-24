#if defined(CHISA_WIDE_MODEL)
#include "../boom_model/wide/oracle_bindings.h"
// Native Large's registration is compiled from its own generated source.
#else
// Which manifest streams the model currently claims to predict.
//
// Binding source is part of the correctness claim. Dynamic streams come from
// model state, structural constants require a configuration/topology proof,
// and the remaining reserve_constant calls are explicitly profile-derived
// debt until their owning subsystem is modeled or proven unreachable.

#include "model_bindings.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <string>
#include <string_view>

#include "generated/system_probe_registry.inc"
#include "system_guider.h"

namespace chisa::boom_system {

#include "generated/watch_bindings_decl.inc"

namespace {

OracleKind manifest_kind_for_binding(std::string_view key) {
  for (const SystemProbeManifestRow& row : kSystemProbeManifest)
    if (key == row.key) return row.kind;
#if 0 || defined(CHISA_SUBSET_CONTRACT_EXPERIMENT)
  // In-migration configuration (or a subset-contract experiment build):
  // registrations carry streams this contract does not have. They land on
  // the pad lane and are never compared; treat them as plain registers.
  return OracleKind::Register;
#else
  std::fprintf(stderr, "[BIND] key absent from manifest timing table: %.*s\n",
               static_cast<int>(key.size()), key.data());
  std::abort();
#endif
}

/** Adapter for generated batches whose expressions are deliberately sampled
  * at cycle start. Register rows retain PRE timing; combinational rows carry
  * the explicit proof that their POST value is reconstructed from the PRE
  * memory/state image. */
class ManifestTimedSampledBindings {
 public:
  explicit ManifestTimedSampledBindings(ModelBindings& bindings)
      : bindings_(bindings) {}

  int reserve_sampled(const char* key) {
    return manifest_kind_for_binding(key) == OracleKind::Combinational
               ? bindings_.reserve_sampled_combinational(key)
               : bindings_.reserve_sampled(key);
  }
  // A batch slot whose key is owned by the image (written by the model
  // itself): the batch keeps its numbering, the store is discarded.
  int reserve_batch_scratch() { return bindings_.reserve_batch_scratch(); }

  void add_batch_sampler(ModelBindings::BatchSampleFn fn, int base,
                         SamplePlacement placement = SamplePlacement::PreStep,
                         ModelBindings::WatchFn watch = nullptr) {
    bindings_.add_batch_sampler(fn, base, placement, watch);
  }

 private:
  ModelBindings& bindings_;
};

uint64_t predict_bypass_stall_counter(const SystemGuider& model) {
  return model.debug().bypass_stall_beats_left;
}

uint64_t predict_error_beats_left(const SystemGuider& model) {
  return model.debug().error_arbiter_beats_left;
}

uint64_t predict_error_idle(const SystemGuider& model) {
  return model.debug().error_idle_observed;
}

uint64_t predict_xbar_beats_left(const SystemGuider& model) {
  return model.debug().xbar_beats_left;
}

uint64_t predict_dmactive(const SystemGuider& model) {
  return model.debug().dmactive_observed;
}

uint64_t predict_bypass_reg(const SystemGuider& model) {
  return model.debug().bypass_reg_observed;
}

uint64_t predict_clock_en(const SystemGuider& model) {
  return model.debug().clock_en_observed;
}

uint64_t predict_inner_dmactive_inactive(const SystemGuider& model) {
  return model.debug().inner_dmactive_inactive;
}

uint64_t predict_inner_ctrl_source_ready_reg(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::OuterInnerCtrlReadyReg);
}

uint64_t predict_debug_outer_xbar_readys_mask(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::OuterXbarReadysMask);
}

uint64_t predict_debug_outer_a_source_widx_bin(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::OuterASourceWidxBin);
}

uint64_t predict_debug_outer_d_sink_valid_reg(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::OuterDSinkValidReg);
}

uint64_t predict_debug_inner_ctrl_state(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::InnerCtrlState);
}

uint64_t predict_debug_inner_ctrl_sink_valid_reg(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::InnerCtrlSinkValidReg);
}

uint64_t predict_debug_inner_d_source_ready_reg(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::InnerDSourceReadyReg);
}

uint64_t predict_debug_inner_a_sink_cdc_reg(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::InnerASinkCdcReg);
}

uint64_t predict_debug_inner_a_sink_valid_reg(const SystemGuider& model) {
  return model.debug_stream(SystemGuider::DebugStream::InnerASinkValidReg);
}

uint64_t predict_ndmreset_delay(const SystemGuider& model) {
  return model.reset_clock().ndmreset_delay_observed;
}

uint64_t predict_plic_pending_0(const SystemGuider& model) {
  return model.interrupts().plic_pending_0_observed;
}

uint64_t predict_plic_pending_1(const SystemGuider& model) {
  return model.interrupts().plic_pending_1_observed;
}

void register_debug_invariant_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  bindings.bind_register_snapshot(
      "ldut_debug_1_dmOuter_dmiBypass_bar_stall_counter",
      predict_bypass_stall_counter);
  bindings.bind_register_snapshot(
      "ldut_debug_1_dmOuter_dmiBypass_error_beatsLeft",
      predict_error_beats_left);
  bindings.bind_register_snapshot(
      "ldut_debug_1_dmOuter_dmiBypass_error_idle", predict_error_idle);
  bindings.bind_register_snapshot(
      "ldut_debug_1_dmOuter_dmiXbar_beatsLeft", predict_xbar_beats_left);
}

void register_debug_activation_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  bindings.bind_register_snapshot(
      "ldut_debug_1_dmOuter_dmOuter_DMCONTROLReg_dmactive",
      predict_dmactive);
  bindings.bind_register_snapshot(
      "ldut_debug_1_dmOuter_dmiBypass_bar_bypass_reg", predict_bypass_reg);
  bindings.bind_register_snapshot("clock_en", predict_clock_en);
  bindings.bind("ldut_debug_1_dmInner_dmInner__T_1",
                predict_inner_dmactive_inactive);
  bindings.bind_sampled(
      "ldut_debug_1_dmOuter_io_innerCtrl_source_ready_reg",
      predict_inner_ctrl_source_ready_reg);
  bindings.bind_sampled(
      "ldut_debug_1_dmOuter_dmiXbar_readys_mask",
      predict_debug_outer_xbar_readys_mask);
  bindings.bind_sampled(
      "ldut_debug_1_dmOuter_asource_bundleOut_0_a_source_widx_widx_bin",
      predict_debug_outer_a_source_widx_bin);
  bindings.bind_sampled(
      "ldut_debug_1_dmOuter_asource_bundleIn_0_d_sink_valid_reg",
      predict_debug_outer_d_sink_valid_reg);
  bindings.bind_sampled("ldut_debug_1_dmInner_dmInner_ctrlStateReg",
                        predict_debug_inner_ctrl_state);
  bindings.bind_sampled(
      "ldut_debug_1_dmInner_dmactive_synced_dmInner_io_innerCtrl_sink_valid_reg",
      predict_debug_inner_ctrl_sink_valid_reg);
  bindings.bind_sampled(
      "ldut_debug_1_dmInner_dmiXing_bundleIn_0_d_source_ready_reg",
      predict_debug_inner_d_source_ready_reg);
  bindings.bind_sampled(
      "ldut_debug_1_dmInner_dmiXing_bundleOut_0_a_sink_io_deq_bits_deq_bits_reg_cdc_reg",
      predict_debug_inner_a_sink_cdc_reg);
  bindings.bind_sampled(
      "ldut_debug_1_dmInner_dmiXing_bundleOut_0_a_sink_valid_reg",
      predict_debug_inner_a_sink_valid_reg);
}

void register_reset_and_interrupt_invariant_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  bindings.bind_register_snapshot("ldut_reset_reg_reg",
                                  predict_ndmreset_delay);
  bindings.bind_register_snapshot("ldut_plicDomainWrapper_plic_pending_0",
                                  predict_plic_pending_0);
  bindings.bind_register_snapshot("ldut_plicDomainWrapper_plic_pending_1",
                                  predict_plic_pending_1);

}

// ---- live core pipeline slice --------------------------------------------
// The first core streams promoted from the bring-up probes after the live
// model matched the complete TestHarness over the full 200,000-cycle window:
// F0-F2, the FetchBuffer and FTQ pointers, the I-cache s2 stage, the ROB
// pointers and the debug interrupt crossing.  All go through the pre-step
// sample buffer (see bind_sampled): the RTL PRE tap wants the value from
// before the model's step, and the first cycle is the zero image.

void sample_batch_core_pipeline(const SystemGuider& m, BatchSlots slots) {
  (void)m; (void)slots;
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
}

void register_live_core_pipeline_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
    const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_core_pipeline, base, ModelBindings::SamplePlacement::End, watch_sample_batch_core_pipeline);
}

// ---- frontend register slice (mass-binding wave A) -----------------------
// Promoted after a 50k strict-lockstep run with zero mismatches on every
// stream below.  Ghist pipelines, S2 flags, F3 queue payloads, the F4
// occupancy bit, the F3 assembler's trailing-half registers, the I-cache
// refill registers and two RAS registers ride the pre-step sample buffer.
// The frontend TLB block is predicted zero: this harness never leaves bare
// machine mode (no satp write exists in the workload path), the bare-mode
// ITLB component models exactly that regime, and any future VM activity
// would surface as a REAL mismatch on these very streams.

void sample_batch_frontend_wave_a(const SystemGuider& m, BatchSlots slots) {
  (void)m; (void)slots;
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
  {
  }
}

void sample_batch_itlb_state(const SystemGuider& m, BatchSlots slots) {
  (void)m; (void)slots;  // the ITLB streams are image-owned (frontend_export.inc)
}

void register_itlb_state_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  static constexpr std::array<const char*, 44> kItlbStateBindingKeys = {
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_r_refill_tag",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_r_sectored_hit",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_r_sectored_hit_addr",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_r_sectored_repl_addr",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_r_superpage_repl_addr",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_0_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_0_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_0_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_0_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_1_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_1_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_1_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_1_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_2_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_2_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_2_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_2_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_3_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_3_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_3_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_3_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_4_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_4_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_4_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_4_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_5_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_5_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_5_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_5_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_6_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_6_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_6_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_6_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_7_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_7_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_7_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_sectored_entries_0_7_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_special_entry_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_special_entry_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_state",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_superpage_entries_0_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_superpage_entries_1_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_superpage_entries_2_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_tlb_superpage_entries_3_valid_0",
  };
  // Image-owned (frontend_export.inc): the batch keeps its slot count.
  (void)kItlbStateBindingKeys;
  const int base = bindings.reserve_batch_scratch();
  for (std::size_t i = 1; i < kItlbStateBindingKeys.size(); ++i)
    bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_itlb_state, base, ModelBindings::SamplePlacement::Frontend, watch_sample_batch_itlb_state);
}

void register_frontend_wave_a_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
    const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_frontend_wave_a, base, ModelBindings::SamplePlacement::Frontend, watch_sample_batch_frontend_wave_a);
}

// ---- CSR file slice (mass-binding wave B) --------------------------------
// Promoted after a 50k strict-lockstep run with zero mismatches: the
// architectural CSR fields the guider owns (RTL reset values MPP=3,
// dcsr.prv=3, PRV=M), the wide cycle/instret counters (cycle freezes during
// reg_wfi exactly as rocket's csr_stall does; minstret's architectural
// register lags the commit by one edge), and zero predictions for the CSRs
// this workload never writes: the S-mode file, PMP, HPM, satp and the custom
// register.  Any write to one of those would surface as a REAL mismatch on
// the stream itself.

// ---- rename + ROB slice (mass-binding wave C) ----------------------------

// Promoted after a 50k strict-lockstep run with zero mismatches: the rename
// map table and per-branch allocation lists, every ROB row's branch mask,
// and the ROB bookkeeping mirrors (PNR, occupancy, registered exception
// valid) that the OracleMirror was built to carry.

// ---- LSU slice (mass-binding wave D) -------------------------------------
// Promoted after a 50k strict-lockstep run with zero mismatches on all 276
// streams: every LDQ and STQ entry field the manifest selects (valids,
// addresses, data, status bits and the resident micro-op fields), the queue
// pointers and live-store mask, the store clear-busy delay stage, the
// registered memory paddr mirror, and zero predictions for the D-side TLB
// (bare machine mode, same argument as the I-side) plus the unused
// hella-cache FSM.

void sample_batch_dtlb_state(const SystemGuider& m, BatchSlots slots) {
  (void)m; (void)slots;  // image-owned (memory_export.inc)
}

void register_dtlb_state_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  static constexpr std::array<const char*, 30> kDtlbStateBindingKeys = {
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_r_refill_tag",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_r_superpage_repl_addr",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_data_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_data_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_data_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_tag",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_0_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_data_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_data_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_data_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_tag",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_valid_1",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_valid_2",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_sectored_entries_1_valid_3",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_special_entry_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_special_entry_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_0_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_0_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_1_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_1_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_2_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_2_valid_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_3_data_0",
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_dtlb_superpage_entries_3_valid_0",
  };
  (void)kDtlbStateBindingKeys;  // image-owned (memory_export.inc)
  const int base = bindings.reserve_batch_scratch();
  for (std::size_t i = 1; i < kDtlbStateBindingKeys.size(); ++i)
    bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_dtlb_state, base, ModelBindings::SamplePlacement::Core, watch_sample_batch_dtlb_state);
}

void register_structural_constant_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
#include "structural_constant_bindings.inc"
}

}  // namespace

// ==========================================================================
// Bank folds, wave 2 (2026-08-23): partially-covered banks completed by
// supplying the missing sibling members straight from model state (LSU entry
// fields, stq_head, int map_table index holes). Two banks stay out: their
// members include registered retry/wakeup pick indices the model does not
// yet compute. Layout comes from register_bank_manifest.json.
// ==========================================================================

// The eight DRAM-chain streams that were previously profile-derived zeros.
// The other 36 selected `mem.*` streams live in active_face_bindings.inc but
// read the same snapshot; keeping this small batch separate avoids changing
// that generated batch's slot numbering.

void sample_batch_mbus_memory_extras(const SystemGuider& m,
                                     BatchSlots slots) {
  (void)slots;
  const auto& mem = m.fabric().mbus_memory_oracles();
  (void)mem;
}

void register_mbus_memory_extra_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_mbus_memory_extras, base, ModelBindings::SamplePlacement::PreStep, watch_sample_batch_mbus_memory_extras);
}

void sample_batch_tile_buffer_extras(const SystemGuider& m,
                                     BatchSlots slots) {
  (void)slots;
  const auto& queue =
      m.memory().fabric_for_diagnostic().b_queue_for_diagnostic();
  (void)queue;
}

void register_tile_buffer_extra_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_tile_buffer_extras, base, ModelBindings::SamplePlacement::PreStep, watch_sample_batch_tile_buffer_extras);
}

// Two surviving pieces of the system-bus D-channel arbiter that were not in
// the original active-face batch.  Its other state (winner 0/1 and beatsLeft)
// is already sourced from the same AxiChainMirror instance there.

void sample_batch_sbus_d_arbiter_extras(const SystemGuider& m,
                                        BatchSlots slots) {
  const auto& system_bus = m.fabric().system_bus_oracles();

  batch_store(slots, 0, system_bus[88]);  // system_bus_xbar.readys_mask_4
  batch_store(slots, 1, system_bus[93]);  // system_bus_xbar.state_4_2

}

void register_sbus_d_arbiter_extra_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_sbus_d_arbiter_extras, base, ModelBindings::SamplePlacement::PreStep, watch_sample_batch_sbus_d_arbiter_extras);
}

#include "generated/system_bus_oracle_bindings.inc"

#include "generated/periphery_bus_oracle_bindings.inc"

// Sparse D-cache payloads that the early-load profile never exercised.  The
// hot cache already owns these registers; expose them instead of treating a
// quiet Dhrystone prefix as proof that they are constant.

void sample_batch_dcache_sparse_state(const SystemGuider& m,
                                      BatchSlots slots) {
  (void)slots;
  const auto& dcache = m.memory().dcache_for_diagnostic();
  // BranchKillableQueue uses an asynchronous Mem read at deq_ptr.  The port
  // therefore exposes the addressed RAM word even while the queue is empty;
  // it is not a valid-gated/held replay payload.
  const auto& mshr0 = dcache.mshr_for_diagnostic(0);
  (void)mshr0;
  const auto& mshr1 = dcache.mshr_for_diagnostic(1);
  (void)mshr1;
  const auto& prober = dcache.prober_for_diagnostic();
  (void)prober;
}

void register_dcache_sparse_state_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_dcache_sparse_state, base, ModelBindings::SamplePlacement::Memory, watch_sample_batch_dcache_sparse_state);
}

// Exact RPQ payload storage plus the line-buffer's asynchronous read face.
// These are cold observability details owned by the D-cache model; keeping
// them out of its functional request path avoids paying for them anywhere
// except the oracle sampler.

void sample_batch_dcache_observable_storage(const SystemGuider& m,
                                            BatchSlots slots) {
  (void)slots;
  const auto& dcache = m.memory().dcache_for_diagnostic();
  (void)dcache;
}

void register_dcache_observable_storage_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_dcache_observable_storage, base, ModelBindings::SamplePlacement::Memory, watch_sample_batch_dcache_observable_storage);
}

// D-cache pipeline shadow, MSHR coherence registers and the tl_out.c arbiter
// counter.  Each slot is one manifest stream; the RTL line is given next to
// the expression that reproduces it.

void sample_batch_dcache_pipeline_shadow(const SystemGuider& m,
                                         BatchSlots slots) {
  const auto& dcache = m.memory().dcache_for_diagnostic();
  const auto& s1 = dcache.bus_s1_oracle();
  (void)s1;
  const auto& s2 = dcache.bus_s2_oracle();
  // dcache.scala:598/631 s1_req/s2_req latch the s0 request-bus mux.
  // dcache.scala:603 s1_valid(0), 633 s2_valid(0).
  // dcache.scala:717 RegNext(replacer.way); 732 RegNext(s1_send_resp_or_nack).
  // mshrs.scala:694 mshr_alloc_idx; 411 IOMSHR grant_word.
  // mshrs.scala:138 grantack.valid; 118/171/343 new_coh; handle_pri_req old_meta.
  // Scratch: the SDQ MPORT needs both cycle-start state and same-cycle kill
  // inputs. SmallDcache captures that POST projection during step(); it is
  // bound directly below rather than reconstructed at either edge.
  // Scratch: PTW owns mem_resp_data as part of its complete 25-register
  // sidecar image below.
  batch_store(slots, 24, 0);
  batch_store(slots, 25, s2.is_hella ? 1u : 0u);
}

uint64_t predict_dcache_sdq_port(const SystemGuider& m) {
  return m.memory().dcache_for_diagnostic().sdq_port_cycle_oracle();
}

void register_dcache_pipeline_shadow_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_sdq_MPORT_3",
      predict_dcache_sdq_port);
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_dcache_pipeline_shadow, base, ModelBindings::SamplePlacement::Memory, watch_sample_batch_dcache_pipeline_shadow);
}

void sample_batch_ptw_state(const SystemGuider& m, BatchSlots slots) {
  (void)m; (void)slots;  // image-owned (memory_export.inc)
}

void register_ptw_state_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_ptw_state, base, ModelBindings::SamplePlacement::Core, watch_sample_batch_ptw_state);

}

#include "generated/profile_debt_wave1_bindings.inc"

#include "generated/profile_debt_wave2_bindings.inc"

template <std::size_t Port>
uint64_t predict_rob_read_busy(const SystemGuider& m) {

  return m.backend().core().img().c.coreRob.state_rob_bsy_r[3 + Port];

}

template <std::size_t Port>
uint64_t predict_rob_read_uop(const SystemGuider& m) {

  return m.backend().core().img().c.coreRob.state_rob_uop_r[2 + Port];

}

template <std::size_t Port>
uint64_t predict_ftq_ram_read(const SystemGuider& m) {
  return m.frontend().ftq_for_diagnostic().oracle_ram_read(Port);
}

uint64_t sample_ftq_enq_ready(const SystemGuider& m) {
  return m.frontend().ftq_for_diagnostic().enq_ready() ? 1u : 0u;
}

uint64_t predict_lsu_will_fire_load_wakeup(const SystemGuider& m) {

  return m.backend().core().img().c.lsu.will_fire_load_wakeup_0;

}

uint64_t predict_lsu_can_fire_load_incoming(const SystemGuider& m) {

  return m.backend().core().img().c.lsu.can_fire_load_incoming_0;

}

// Streams left unbound by the generators: anonymous registers, packed ROB/FTQ
// read ports and a few frontend/LSU wires, each read from existing model
// state (the manifest key names the RTL register/port on each line).

void sample_batch_unbound_regs(const SystemGuider& m, BatchSlots slots) {
  const auto& fe = m.frontend();
  (void)fe;  // frontend_ftq___v2_state_ram_r0  // frontend_ftq___v2_state_ram_r1  // frontend_ftq___v2_state_ram_r2  // frontend_ftq___v2_state_ram_r3  // frontend_REG_4  // frontend_REG_5  // frontend_ftq_REG_18  // frontend_s2_tlb_resp_ae_inst
  batch_store(slots, 41, 0);
}

void register_unbound_regs_bindings() {
  ModelBindings& bindings = ModelBindings::instance();
  // fetch-target-queue.scala:308: io.enq.ready is itself a RegNext.  Sample
  // the existing FTQ register image at cycle start; a quiet Dhrystone prefix
  // is not evidence that this bit is constant.
  bindings.bind_sampled(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq_REG_12",
      sample_ftq_enq_ready);
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r3",
      predict_rob_read_busy<0>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r4",
      predict_rob_read_busy<1>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r5",
      predict_rob_read_busy<2>);
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r2",
      predict_rob_read_uop<0>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r3",
      predict_rob_read_uop<1>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r4",
      predict_rob_read_uop<2>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r0",
      predict_ftq_ram_read<0>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r1",
      predict_ftq_ram_read<1>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r2",
      predict_ftq_ram_read<2>);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r3",
      predict_ftq_ram_read<3>);
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_can_fire_load_incoming_0",
      predict_lsu_can_fire_load_incoming);
  bindings.reserve_batch_scratch();
  bindings.bind(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_will_fire_load_wakeup_0",
      predict_lsu_will_fire_load_wakeup);
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_unbound_regs, base, ModelBindings::SamplePlacement::End, watch_sample_batch_unbound_regs);
}

#include "generated/active_face_bindings.inc"

namespace {

constexpr std::size_t kNoColdSelector =
    std::numeric_limits<std::size_t>::max();
constexpr std::size_t kTrackerFields = 11;
constexpr std::size_t kTrackerBase = 0;
constexpr std::size_t kBroadcastBase = kTrackerBase + 4 * kTrackerFields;
constexpr std::size_t kBroadcastFields = 6;
constexpr std::size_t kYankerBase = kBroadcastBase + kBroadcastFields;
constexpr std::size_t kYankerFields = 6;
constexpr std::size_t kTl2AxiBase = kYankerBase + 32 * kYankerFields;
constexpr std::size_t kTl2AxiFields = 5;
constexpr std::size_t kPlicQueueSelector = kTl2AxiBase + kTl2AxiFields;
constexpr std::size_t kMmioBufBBase = 0;
constexpr std::size_t kMmioBufBFields = 6;
constexpr std::size_t kMmioBufRBase = kMmioBufBBase + kMmioBufBFields;
constexpr std::size_t kMmioBufRFields = 8;
constexpr std::size_t kMmioBufArBase = kMmioBufRBase + kMmioBufRFields;
constexpr std::size_t kMmioBufArFields = 6;
constexpr std::size_t kMmioBufAwBase = kMmioBufArBase + kMmioBufArFields;
constexpr std::size_t kMmioBufAwFields = 5;
constexpr std::size_t kMmioBufWBase = kMmioBufAwBase + kMmioBufAwFields;
constexpr std::size_t kMmioBufWFields = 5;
constexpr std::size_t kMmioFragmenterBase = kMmioBufWBase + kMmioBufWFields;
constexpr std::size_t kMmioFragmenterFields = 11;
constexpr std::size_t kMmioRamBase =
    kMmioFragmenterBase + kMmioFragmenterFields;
constexpr std::size_t kMmioRamFields = 6;
constexpr std::size_t kBpdTageUsefulnessBase = 18;
constexpr std::size_t kBpdTageUsefulnessFields = 6 * 2 * 4;
constexpr std::size_t kBpdCorrectionBase =
    kBpdTageUsefulnessBase + kBpdTageUsefulnessFields;
constexpr std::size_t kBpdCorrectionFields = 11;

// Streams whose owners already exist in BoomGuider.  The generated selector
// list names them; SelectorBindingRegistrar resolves each name to a sampled
// model binding through the tables below.
constexpr std::size_t kCoreIregBrMask = 0;
constexpr std::size_t kCoreFpRenBase = 1;
constexpr std::size_t kCoreFpRenFields = 5;
constexpr std::size_t kCoreFpBrAllocBase =
    kCoreFpRenBase + kCoreFpRenFields;
constexpr std::size_t kCoreFpBrAllocFields = 7;
constexpr std::size_t kCoreFpMapBase =
    kCoreFpBrAllocBase + kCoreFpBrAllocFields;
constexpr std::size_t kCoreFpMapFields = 4;
constexpr std::size_t kCoreMemSlotBase = kCoreFpMapBase + kCoreFpMapFields;
constexpr std::size_t kCoreMemSlotFields = 5;
constexpr std::size_t kCoreRenameEdgeInst =
    kCoreMemSlotBase + 8 * kCoreMemSlotFields;
constexpr std::size_t kCoreRobFpValBank = kCoreRenameEdgeInst + 1;
constexpr std::size_t kCoreLsuWbForwardValid = kCoreRobFpValBank + 1;
constexpr std::size_t kCoreLsuWbForwardStq = kCoreLsuWbForwardValid + 1;
constexpr std::size_t kCoreLsuStoreBlockedCounter =
    kCoreLsuWbForwardStq + 1;
constexpr std::size_t kCoreFpLlWriteValid =
    kCoreLsuStoreBlockedCounter + 1;
constexpr std::size_t kCoreCommitEdgeInst = kCoreFpLlWriteValid + 1;
constexpr std::size_t kCoreLsuBlockP1Base = kCoreCommitEdgeInst + 1;
constexpr std::size_t kCoreLsuBlockP1Fields = 8;
constexpr std::size_t kCoreIntP2PoisonedBase =
    kCoreLsuBlockP1Base + kCoreLsuBlockP1Fields;
constexpr std::size_t kCoreIntP2PoisonedFields = 7;
constexpr std::size_t kCoreIntSlot7P1Poisoned =
    kCoreIntP2PoisonedBase + kCoreIntP2PoisonedFields;
constexpr std::size_t kCoreLsuExceptionBrMask =
    kCoreIntSlot7P1Poisoned + 1;
constexpr std::size_t kCoreLsuClrBsyBrMask =
    kCoreLsuExceptionBrMask + 1;
constexpr std::size_t kCoreIntIssueReady = kCoreLsuClrBsyBrMask + 1;
constexpr std::size_t kCoreMemIssueReady = kCoreIntIssueReady + 1;
constexpr std::size_t kCoreFpIssueReady = kCoreMemIssueReady + 1;
constexpr std::size_t kCoreFpSlotBase = kCoreFpIssueReady + 1;
constexpr std::size_t kCoreFpSlotFields = 6;
constexpr std::size_t kCoreFpRegisterReadBase =
    kCoreFpSlotBase + 8 * kCoreFpSlotFields;
constexpr std::size_t kCoreFpRegisterReadFields = 18;
constexpr std::size_t kCoreB4IsAmo =
    kCoreFpRegisterReadBase + kCoreFpRegisterReadFields;
constexpr std::size_t kCoreB4UsesStq = kCoreB4IsAmo + 1;
constexpr std::size_t kCoreRobHeadFflags = kCoreB4UsesStq + 1;
constexpr std::size_t kCoreLsuDtlbMissReady = kCoreRobHeadFflags + 1;
constexpr std::size_t kCoreLsuExceptionValid = kCoreLsuDtlbMissReady + 1;
constexpr std::size_t kCoreLsuStdfBrMask = kCoreLsuExceptionValid + 1;
constexpr std::size_t kCoreLsuStdfRobIdx = kCoreLsuStdfBrMask + 1;
constexpr std::size_t kCoreLsuStdfValid = kCoreLsuStdfRobIdx + 1;

std::size_t field_index(
    std::string_view field,
    const std::initializer_list<std::string_view>& names) {
  std::size_t index = 0;
  for (const std::string_view name : names) {
    if (field == name) return index;
    ++index;
  }
  return kNoColdSelector;
}

std::size_t mmio_memory_profile_selector(std::string_view key) {
  constexpr std::string_view b_prefix =
      "mmio_mem_axi4buf_bundleIn_0_b_deq_";
  if (key.rfind(b_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(b_prefix.size()),
        {"maybe_full", "value", "value_1",
         "ram_echo_real_last_io_deq_bits_MPORT",
         "ram_id_io_deq_bits_MPORT", "ram_resp_io_deq_bits_MPORT"});
    if (field != kNoColdSelector) return kMmioBufBBase + field;
  }

  constexpr std::string_view r_prefix =
      "mmio_mem_axi4buf_bundleIn_0_r_deq_";
  if (key.rfind(r_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(r_prefix.size()),
        {"maybe_full", "value", "value_1", "ram_data_io_deq_bits_MPORT",
         "ram_echo_real_last_io_deq_bits_MPORT",
         "ram_id_io_deq_bits_MPORT", "ram_last_io_deq_bits_MPORT",
         "ram_resp_io_deq_bits_MPORT"});
    if (field != kNoColdSelector) return kMmioBufRBase + field;
  }

  constexpr std::string_view ar_prefix =
      "mmio_mem_axi4buf_bundleOut_0_ar_deq_";
  if (key.rfind(ar_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(ar_prefix.size()),
        {"maybe_full", "value", "value_1", "ram_addr_io_deq_bits_MPORT",
         "ram_echo_real_last_io_deq_bits_MPORT",
         "ram_id_io_deq_bits_MPORT"});
    if (field != kNoColdSelector) return kMmioBufArBase + field;
  }

  constexpr std::string_view aw_prefix =
      "mmio_mem_axi4buf_bundleOut_0_aw_deq_";
  if (key.rfind(aw_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(aw_prefix.size()),
        {"maybe_full", "value_1", "ram_addr_io_deq_bits_MPORT",
         "ram_echo_real_last_io_deq_bits_MPORT",
         "ram_id_io_deq_bits_MPORT"});
    if (field != kNoColdSelector) return kMmioBufAwBase + field;
  }

  constexpr std::string_view w_prefix =
      "mmio_mem_axi4buf_bundleOut_0_w_deq_";
  if (key.rfind(w_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(w_prefix.size()),
        {"maybe_full", "value", "ram_data_io_deq_bits_MPORT",
         "ram_last_io_deq_bits_MPORT", "ram_strb_io_deq_bits_MPORT"});
    if (field != kNoColdSelector) return kMmioBufWBase + field;
  }

  constexpr std::string_view fragmenter_prefix = "mmio_mem_axi4frag_";
  if (key.rfind(fragmenter_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(fragmenter_prefix.size()),
        {"deq_maybe_full", "deq_1_maybe_full", "in_w_deq_maybe_full",
         "in_w_deq_ram_data", "in_w_deq_ram_strb", "r_addr", "r_addr_1",
         "r_len", "r_len_1", "w_counter", "wbeats_latched"});
    if (field != kNoColdSelector) return kMmioFragmenterBase + field;
  }

  constexpr std::string_view ram_prefix = "mmio_mem_srams_";
  if (key.rfind(ram_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(ram_prefix.size()),
        {"mem_7_rdata_MPORT_addr_pipe_0", "r_full", "r_id",
         "w_echo_real_last", "w_full", "w_id"});
    if (field != kNoColdSelector) return kMmioRamBase + field;
  }
  return kNoColdSelector;
}

std::size_t cold_profile_selector(std::string_view key) {
  if (key == "ldut_plicDomainWrapper_plic_out_back_maybe_full")
    return kPlicQueueSelector;

  constexpr std::string_view tracker_prefix =
      "ldut_subsystem_l2_wrapper_broadcast_1_TLBroadcastTracker";
  if (key.rfind(tracker_prefix, 0) == 0) {
    std::string_view rest = key.substr(tracker_prefix.size());
    std::size_t tracker = 0;
    if (rest.rfind("$$inst_", 0) == 0) {
      rest.remove_prefix(7);
    } else if (!rest.empty() && rest.front() == '_') {
      rest.remove_prefix(1);
      std::size_t digits = 0;
      while (digits < rest.size() && rest[digits] >= '0' &&
             rest[digits] <= '9') {
        tracker = tracker * 10 + static_cast<std::size_t>(rest[digits] - '0');
        ++digits;
      }
      if (digits == 0 || tracker >= 4) return kNoColdSelector;
      rest.remove_prefix(digits);
      if (rest.rfind("$$inst_", 0) != 0) return kNoColdSelector;
      rest.remove_prefix(7);
    } else {
      return kNoColdSelector;
    }
    const std::size_t field = field_index(
        rest, {"address", "count", "got_e", "o_data_maybe_full",
               "o_data_value", "o_data_value_1", "opcode", "sent_d",
               "shared", "size", "source"});
    return field == kNoColdSelector
               ? field
               : kTrackerBase + tracker * kTrackerFields + field;
  }

  constexpr std::string_view broadcast_prefix =
      "ldut_subsystem_l2_wrapper_broadcast_1_";
  if (key.rfind(broadcast_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(broadcast_prefix.size()),
        {"REG", "counter_2", "state_1_2", "state_1_3", "state_1_4",
         "state__0"});
    if (field != kNoColdSelector) return kBroadcastBase + field;
  }

  constexpr std::string_view yank_prefix =
      "ldut_subsystem_mbus_coupler_to_memory_controller_port_named_axi4_"
      "axi4yank_QueueCompatibility";
  if (key.rfind(yank_prefix, 0) == 0) {
    std::string_view rest = key.substr(yank_prefix.size());
    std::size_t queue = 0;
    if (rest.rfind("$$inst_", 0) == 0) {
      rest.remove_prefix(7);
    } else if (!rest.empty() && rest.front() == '_') {
      rest.remove_prefix(1);
      std::size_t digits = 0;
      while (digits < rest.size() && rest[digits] >= '0' &&
             rest[digits] <= '9') {
        queue = queue * 10 + static_cast<std::size_t>(rest[digits] - '0');
        ++digits;
      }
      if (digits == 0 || queue >= 32) return kNoColdSelector;
      rest.remove_prefix(digits);
      if (rest.rfind("$$inst", 0) == 0) rest.remove_prefix(6);
      if (rest.empty() || rest.front() != '_') return kNoColdSelector;
      rest.remove_prefix(1);
    } else {
      return kNoColdSelector;
    }
    const std::size_t field = field_index(
        rest, {"deq_ptr_value", "enq_ptr_value", "maybe_full",
               "ram_extra_id_io_deq_bits_MPORT",
               "ram_tl_state_size_io_deq_bits_MPORT",
               "ram_tl_state_source_io_deq_bits_MPORT"});
    return field == kNoColdSelector
               ? field
               : kYankerBase + queue * kYankerFields + field;
  }

  constexpr std::string_view tl2axi_prefix =
      "ldut_subsystem_mbus_coupler_to_memory_controller_port_named_axi4_"
      "tl2axi4_";
  if (key.rfind(tl2axi_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(tl2axi_prefix.size()),
        {"b_delay", "deq_maybe_full", "deq_ram_data", "deq_ram_strb",
         "queue_arw_deq_maybe_full"});
    if (field != kNoColdSelector) return kTl2AxiBase + field;
  }
  return kNoColdSelector;
}

std::size_t bpd_profile_selector(std::string_view key) {
  // F4's two-entry BTB-correction queue is already modeled by
  // SmallBpdUpdatePath.  The lifted MPORT streams are the payload RAM word at
  // the queue's current dequeue pointer, even while the queue is empty; do not
  // replace those stale-but-real words with loading-profile zeroes.
  constexpr std::string_view correction_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_"
      "f4_btb_corrections_ram_";
  if (key.rfind(correction_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(correction_prefix.size()),
        {"br_mask_io_deq_bits_MPORT",
         "cfi_idx_bits_io_deq_bits_MPORT",
         "cfi_idx_valid_io_deq_bits_MPORT",
         "cfi_is_br_io_deq_bits_MPORT",
         "cfi_is_jal_io_deq_bits_MPORT",
         "cfi_mispredicted_io_deq_bits_MPORT",
         "cfi_taken_io_deq_bits_MPORT",
         "ghist_old_history_io_deq_bits_MPORT",
         "is_mispredict_update_io_deq_bits_MPORT",
         "is_repair_update_io_deq_bits_MPORT",
         "target_io_deq_bits_MPORT"});
    if (field != kNoColdSelector) return kBpdCorrectionBase + field;
  }

  constexpr std::string_view prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_bpd_"
      "banked_predictors_0_";
  if (key.rfind(prefix, 0) != 0) return kNoColdSelector;
  const std::string_view rest = key.substr(prefix.size());
  if (rest == "components_3_btb__v2_bank_0_6") return 0;
  if (rest == "components_3_meta__v2_bank_6_0") return 1;
  if (rest == "components_2_meta_0_0_MPORT_2") return 2;
  if (rest == "components_2_REG_3") return 3;
  if (rest == "components_2_btb_0_1_MPORT") return 4;
  if (rest == "components_2_btb_0_2_MPORT") return 5;
  if (rest == "components_2_btb_0_3_MPORT") return 6;
  if (rest == "components_2_btb_1_1_MPORT_1") return 7;
  if (rest == "components_2_btb_1_3_MPORT_1") return 8;
  if (rest == "components_2_meta_0_1_MPORT_2") return 9;
  if (rest == "components_2_meta_0_2_MPORT_2") return 10;
  if (rest == "components_2_meta_0_3_MPORT_2") return 11;
  if (rest == "components_2_meta_1_1_MPORT_3") return 12;
  if (rest == "components_2_meta_1_3_MPORT_3") return 13;
  if (rest == "components_3_REG_2_predicted_pc_valid") return 14;
  if (rest == "components_3_REG_6_predicted_pc_valid") return 15;
  // BTB f2 is_br pipeline registers for fetch slots 1 and 3.  Slots 0/2
  // already live in the active-face batch; these two were only quiet in the
  // loading profile and must not remain workload-specific constants.
  if (rest == "components_2_REG_15") return 16;
  if (rest == "components_2_REG_39") return 17;

  // Every TAGE usefulness SRAM has four one-bit read ports for each half.
  // Most were classified as profile constants only because the loading trace
  // never set them. They are ordinary reads of state already owned by the
  // predictor, so promote the whole family instead of patching individual
  // streams as workloads wake them up.
  constexpr std::string_view tage_prefix = "components_1_tables_";
  if (rest.rfind(tage_prefix, 0) == 0) {
    std::string_view tail = rest.substr(tage_prefix.size());
    if (tail.size() >= 2 && tail[0] >= '0' && tail[0] <= '5' &&
        tail[1] == '_') {
      const std::size_t table = static_cast<std::size_t>(tail[0] - '0');
      tail.remove_prefix(2);
      bool high = false;
      if (tail.rfind("hi_us_", 0) == 0) {
        high = true;
        tail.remove_prefix(6);
      } else if (tail.rfind("lo_us_", 0) == 0) {
        tail.remove_prefix(6);
      } else {
        return kNoColdSelector;
      }
      if (tail.size() >= 2 && tail[0] >= '0' && tail[0] <= '3' &&
          tail[1] == '_') {
        const std::size_t slot = static_cast<std::size_t>(tail[0] - '0');
        tail.remove_prefix(2);
        const std::string_view expected =
            high ? "s2_req_rhius" : "s2_req_rlous";
        if (tail == expected)
          return kBpdTageUsefulnessBase + table * 8 +
                 (high ? 4 : 0) + slot;
      }
    }
  }
  return kNoColdSelector;
}

std::size_t core_profile_selector(std::string_view key) {
  constexpr std::string_view lsu_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_";
  if (key.rfind(lsu_prefix, 0) == 0) {
    const std::string_view field = key.substr(lsu_prefix.size());
    if (field == "REG" || field == "REG_1")
      return kCoreLsuDtlbMissReady;
    if (field == "r_xcpt_valid") return kCoreLsuExceptionValid;
    if (field == "stdf_clr_bsy_brmask") return kCoreLsuStdfBrMask;
    if (field == "stdf_clr_bsy_rob_idx") return kCoreLsuStdfRobIdx;
    if (field == "stdf_clr_bsy_valid") return kCoreLsuStdfValid;
  }

  constexpr std::string_view alu_b4_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "csr_exe_unit_alu_REG_1_2_";
  constexpr std::string_view imul_b4_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "csr_exe_unit_imul_REG_1_2_";
  if (key.rfind(alu_b4_prefix, 0) == 0 ||
      key.rfind(imul_b4_prefix, 0) == 0) {
    const std::string_view prefix =
        key.rfind(alu_b4_prefix, 0) == 0 ? alu_b4_prefix : imul_b4_prefix;
    const std::string_view field = key.substr(prefix.size());
    if (field == "is_amo") return kCoreB4IsAmo;
    if (field == "uses_stq") return kCoreB4UsesStq;
  }
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "rob_rob_fflags_MPORT_4")
    return kCoreRobHeadFflags;

  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "iregister_read_REG_1_br_mask")
    return kCoreIregBrMask;

  constexpr std::string_view fp_ren_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "fp_rename_stage_REG_1_";
  if (key.rfind(fp_ren_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(fp_ren_prefix.size()),
        {"is_sfb", "prs1", "prs2", "prs3", "stale_pdst"});
    if (field != kNoColdSelector) return kCoreFpRenBase + field;
  }

  constexpr std::string_view fp_alloc_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "fp_rename_stage_freelist_br_alloc_lists_";
  if (key.rfind(fp_alloc_prefix, 0) == 0) {
    const std::string_view suffix = key.substr(fp_alloc_prefix.size());
    if (suffix.size() == 1 && suffix.front() >= '1' && suffix.front() <= '7')
      return kCoreFpBrAllocBase +
             static_cast<std::size_t>(suffix.front() - '1');
  }

  constexpr std::string_view fp_map_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "fp_rename_stage_maptable_map_table__v2_bank_0_";
  if (key.rfind(fp_map_prefix, 0) == 0) {
    const std::string_view suffix = key.substr(fp_map_prefix.size());
    if (suffix.size() == 1 && suffix.front() >= '0' && suffix.front() <= '3')
      return kCoreFpMapBase +
             static_cast<std::size_t>(suffix.front() - '0');
  }

  constexpr std::string_view mem_slot_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "mem_issue_unit_slots_";
  if (key.rfind(mem_slot_prefix, 0) == 0) {
    std::string_view rest = key.substr(mem_slot_prefix.size());
    if (rest.size() >= 3 && rest.front() >= '0' && rest.front() <= '7' &&
        rest[1] == '_') {
      const std::size_t slot = static_cast<std::size_t>(rest.front() - '0');
      rest.remove_prefix(2);
      const std::size_t field = field_index(
          rest, {"p1_poisoned", "p2_poisoned", "ppred",
                 "slot_uop__v2_bank_2_0", "state"});
      if (field != kNoColdSelector)
        return kCoreMemSlotBase + slot * kCoreMemSlotFields + field;
    }
  }

  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "fp_pipeline_fp_issue_unit_REG")
    return kCoreFpIssueReady;

  constexpr std::string_view fp_register_read_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_";
  if (key.rfind(fp_register_read_prefix, 0) == 0) {
    const std::size_t field = field_index(
        key.substr(fp_register_read_prefix.size()),
        {"REG",
         "fregfile_read_addrs_0", "fregfile_read_addrs_1",
         "fregfile_read_addrs_2", "fregister_read_REG_1_br_mask",
         "fregister_read_REG_2", "fregister_read_REG_3",
         "fregister_read_REG_4",
         "fregister_read_exe_reg_uops_0_fu_code",
         "fregister_read_exe_reg_uops_0_is_amo",
         "fregister_read_exe_reg_uops_0_pdst",
         "fregister_read_exe_reg_uops_0_rob_idx",
         "fregister_read_exe_reg_uops_0_stq_idx",
         "fregister_read_exe_reg_uops_0_uopc",
         "fregister_read_exe_reg_uops_0_uses_stq",
         "fregister_read_exe_reg_valids_0",
         "fpiu_unit_fpu_REG_1_3_fu_code",
         "fpiu_unit_fpu_REG__3"});
    if (field != kNoColdSelector) return kCoreFpRegisterReadBase + field;
  }

  constexpr std::string_view fp_slot_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "fp_pipeline_fp_issue_unit_slots_";
  if (key.rfind(fp_slot_prefix, 0) == 0) {
    std::string_view rest = key.substr(fp_slot_prefix.size());
    if (rest.size() >= 3 && rest.front() >= '0' && rest.front() <= '7' &&
        rest[1] == '_') {
      const std::size_t slot = static_cast<std::size_t>(rest.front() - '0');
      rest.remove_prefix(2);
      const std::size_t field = field_index(
          rest, {"p1", "p2", "p3", "ppred",
                 "slot_uop__v2_bank_2_0", "state"});
      if (field != kNoColdSelector)
        return kCoreFpSlotBase + slot * kCoreFpSlotFields + field;
    }
  }

  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "rename_stage_REG_1_edge_inst")
    return kCoreRenameEdgeInst;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "rob_rob_uop__v2_bank_1_0")
    return kCoreRobFpValBank;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_"
      "wb_forward_valid_0")
    return kCoreLsuWbForwardValid;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_"
      "wb_forward_stq_idx_0")
    return kCoreLsuWbForwardStq;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_REG_63")
    return kCoreLsuStoreBlockedCounter;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "fp_pipeline_REG_1_valid")
    return kCoreFpLlWriteValid;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_REG_9")
    return kCoreCommitEdgeInst;

  constexpr std::string_view lsu_block_p1_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_"
      "p1_block_load_mask_";
  if (key.rfind(lsu_block_p1_prefix, 0) == 0) {
    const std::string_view suffix = key.substr(lsu_block_p1_prefix.size());
    if (suffix.size() == 1 && suffix.front() >= '0' &&
        suffix.front() <= '7')
      return kCoreLsuBlockP1Base +
             static_cast<std::size_t>(suffix.front() - '0');
  }

  constexpr std::string_view int_slot_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "int_issue_unit_slots_";
  if (key.rfind(int_slot_prefix, 0) == 0) {
    const std::string_view rest = key.substr(int_slot_prefix.size());
    if (rest.size() == 13 && rest.front() >= '1' && rest.front() <= '7' &&
        rest.substr(1) == "_p2_poisoned")
      return kCoreIntP2PoisonedBase +
             static_cast<std::size_t>(rest.front() - '1');
    if (rest == "7_p1_poisoned") return kCoreIntSlot7P1Poisoned;
  }
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_"
      "r_xcpt_uop_br_mask")
    return kCoreLsuExceptionBrMask;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_"
      "clr_bsy_brmask_0")
    return kCoreLsuClrBsyBrMask;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "int_issue_unit_REG")
    return kCoreIntIssueReady;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_"
      "mem_issue_unit_REG")
    return kCoreMemIssueReady;
  return kNoColdSelector;
}

std::size_t fdivsqrt_profile_selector(std::string_view key) {
  constexpr std::string_view ds_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_"
      "fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_";
  if (key.rfind(ds_prefix, 0) == 0) {
    const std::string_view field = key.substr(ds_prefix.size());
    // These counters are not selected by the Small contract, so append them
    // after the original 35-slot layout rather than perturbing its indices.
    if (field == "cycleNum_B") return 35;
    if (field == "cycleNum_C") return 36;
    return field_index(
        field,
        {"E_E_div", "cycleNum_A", "fractA_PA", "fractB_PA",
         "fractR0_A", "hiSqrR0_A_sqrt", "isInf_PA", "isInf_PB",
         "isInf_PC", "isNaN_PA", "isNaN_PB", "isNaN_PC",
         "isNegRemT_E", "isZeroRemT_E", "isZero_PA", "isZero_PB",
         "isZero_PC", "majorExc_PC", "nextMulAdd9A_A",
         "nextMulAdd9B_A", "partNegSigma0_A", "roundingMode_PA",
         "sExp_PA", "sigT_E", "sigXN_C", "sign_PC", "sqrtOp_PA",
         "sqrtOp_PB", "sqrtOp_PC", "valid_PA", "valid_PB", "valid_PC"});
  }
  constexpr std::string_view mul_prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_"
      "fpiu_unit_fdivsqrt_divsqrt_mul_";
  if (key.rfind(mul_prefix, 0) == 0) {
    const std::string_view field_name = key.substr(mul_prefix.size());
    if (field_name == "reg_result_s3__w0") return 37;
    if (field_name == "reg_result_s3__w1") return 38;
    const std::size_t field = field_index(
        field_name,
        {"reg_a_s1", "reg_b_s1", "val_s1"});
    return field == kNoColdSelector ? field : 32 + field;
  }
  return kNoColdSelector;
}

std::size_t fpu_profile_selector(std::string_view key) {
  constexpr std::string_view prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_"
      "fpiu_unit_fpu_fpu_";
  if (key.rfind(prefix, 0) != 0) return kNoColdSelector;
  const std::string_view rest = key.substr(prefix.size());
  if (rest == "fpiu_outPipe_bits_toint") return 10;

  // LargeBoom exposes the word-split registered payloads around the three
  // arithmetic sub-pipelines.  Their selector order is the append-only tail
  // of FpuOracleState (Small's 0..27 mapping remains unchanged).
  const std::size_t large_payload = field_index(
      rest,
      {"dfma_in_in1__w0", "dfma_in_in1__w1",
       "dfma_in_in2__w0", "dfma_in_in2__w1",
       "dfma_in_in3__w0", "dfma_in_in3__w1",
       "dfma_io_out_b_data__w0", "dfma_io_out_b_data__w1",
       "fpiu_in_in1__w0", "fpiu_in_in1__w1",
       "fpiu_in_in2__w0", "fpiu_in_in2__w1",
       "fpiu_outPipe_bits_2_toint",
       "fpmu_inPipe_bits_in1__w0", "fpmu_inPipe_bits_in1__w1",
       "fpmu_inPipe_bits_in2__w0", "fpmu_inPipe_bits_in2__w1",
       "fpmu_inPipe_bits_ren2", "fpmu_inPipe_bits_rm",
       "fpmu_inPipe_bits_typeTagOut", "fpmu_inPipe_bits_wflags",
       "fpmu_io_out_outPipe_bits_1_data__w0",
       "fpmu_io_out_outPipe_bits_1_data__w1",
       "sfma_in_in1__w0", "sfma_in_in1__w1",
       "sfma_in_in2__w0", "sfma_in_in2__w1",
       "sfma_in_in3__w0", "sfma_in_in3__w1",
       "sfma_io_out_b_data__w0", "sfma_io_out_b_data__w1"});
  if (large_payload != kNoColdSelector) return 28 + large_payload;

  constexpr std::string_view dfma_prefix = "dfma_fma_";
  if (rest.rfind(dfma_prefix, 0) == 0) {
    return field_index(
        rest.substr(dfma_prefix.size()),
        {"mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfA",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNC",
         "roundRawFNToRecFN_io_in_b_isZero",
         "roundRawFNToRecFN_io_in_b_sExp",
         "roundRawFNToRecFN_io_in_b_sig",
         "roundRawFNToRecFN_io_in_b_sign",
         "roundRawFNToRecFN_io_invalidExc_b"});
  }

  constexpr std::string_view sfma_prefix = "sfma_fma_";
  if (rest.rfind(sfma_prefix, 0) == 0) {
    const std::size_t field = field_index(
        rest.substr(sfma_prefix.size()),
        {"mulAddRecFNToRaw_postMul_io_fromPreMul_b_CDom_CAlignDist",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_bit0AlignedSigC",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_doSubMags",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_highAlignedSigC",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfA",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNC",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isSigNaNAny",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroA",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroB",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroC",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum",
         "mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd",
         "mulAddRecFNToRaw_postMul_io_mulAddResult_b"});
    return field == kNoColdSelector ? field : 11 + field;
  }
  return kNoColdSelector;
}

std::size_t dcache_profile_selector(std::string_view key) {
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_"
      "respq_uops__v2_bank_0_0")
    return 4;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_"
      "s2_req_0_uop_br_mask")
    return 3;
  if (key ==
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_"
      "s2_req_0_uop_is_amo")
    return 5;
  constexpr std::string_view prefix =
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_"
      "mmios_0_";
  if (key.rfind(prefix, 0) != 0) return kNoColdSelector;
  return field_index(key.substr(prefix.size()),
                     {"req_data", "req_uop_is_amo", "req_uop_ldq_idx"});
}

uint64_t sample_cold_profile_override(const SystemGuider& model,
                                      std::size_t selector) {
  const auto& state = model.fabric().coherent_memory_oracles();
  if (selector < kBroadcastBase) {
    const auto& tracker =
        state.trackers[(selector - kTrackerBase) / kTrackerFields];
    switch ((selector - kTrackerBase) % kTrackerFields) {
      case 0: return tracker.address;
      case 1: return tracker.count;
      case 2: return tracker.got_e;
      case 3: return tracker.o_maybe_full;
      case 4: return tracker.o_enq_ptr;
      case 5: return tracker.o_deq_ptr;
      case 6: return tracker.opcode;
      case 7: return tracker.sent_d;
      case 8: return tracker.shared;
      case 9: return tracker.size;
      case 10: return tracker.source;
    }
  }
  if (selector < kYankerBase) {
    switch (selector - kBroadcastBase) {
      case 0: return state.broadcast_reg;
      case 1: return state.broadcast_counter_2;
      case 2: return state.broadcast_state_1_2;
      case 3: return state.broadcast_state_1_3;
      case 4: return state.broadcast_state_1_4;
      case 5: return state.broadcast_state__0;
    }
  }
  if (selector < kTl2AxiBase) {
    const auto& queue =
        state.all_yank[(selector - kYankerBase) / kYankerFields];
    switch ((selector - kYankerBase) % kYankerFields) {
      case 0: return queue.deq_ptr;
      case 1: return queue.enq_ptr;
      case 2: return queue.maybe_full;
      case 3: return queue.extra_id;
      case 4: return queue.size;
      case 5: return queue.source;
    }
  }
  if (selector < kTl2AxiBase + kTl2AxiFields) {
    switch (selector - kTl2AxiBase) {
      case 0: return state.tl2axi4_b_delay;
      case 1: return state.tl2axi4_deq_maybe_full;
      case 2: return state.tl2axi4_deq_data;
      case 3: return state.tl2axi4_deq_strb;
      case 4: return state.tl2axi4_arw_maybe_full;
    }
  }
  if (selector == kPlicQueueSelector)
    return model.fabric().plic_out_back_maybe_full();
  return 0;
}

// Family batch samplers.  One call per subsystem fills every registered
// stream of that family with direct member stores; the (selector -> slot)
// mapping is fixed at registration.  A slot of -1 means the manifest never
// registered that selector, and the store is skipped.  These replace the
// per-stream selector ladders: same expressions, evaluated once per family
// call instead of once per stream behind an indirect call and a range-if
// chain.
struct FamilyEntry {
  uint32_t slot;
  uint32_t selector;
};

constexpr std::size_t kCoreSelectorSpace = kCoreLsuStdfValid + 1;
constexpr std::size_t kMmioSelectorSpace = kMmioRamBase + kMmioRamFields;
constexpr std::size_t kBpdSelectorSpace =
    kBpdCorrectionBase + kBpdCorrectionFields;

template <std::size_t N>
std::array<int32_t, N> make_slot_table() {
  std::array<int32_t, N> table{};
  table.fill(-1);
  return table;
}

std::array<int32_t, kCoreSelectorSpace> g_core_slots =
    make_slot_table<kCoreSelectorSpace>();
std::array<int32_t, kMmioSelectorSpace> g_mmio_slots =
    make_slot_table<kMmioSelectorSpace>();
std::array<int32_t, kBpdSelectorSpace> g_bpd_slots =
    make_slot_table<kBpdSelectorSpace>();
std::vector<FamilyEntry> g_fdivsqrt_entries;
std::vector<FamilyEntry> g_fpu_entries;
// Two manifest keys may resolve to one selector (lsu REG and REG_1 name the
// same registered value).  The table keeps the first slot; later keys land
// here and are filled by copying the primary slot after the family body ran.
std::vector<FamilyEntry> g_core_dup_entries;
std::vector<FamilyEntry> g_mmio_dup_entries;
std::vector<FamilyEntry> g_bpd_dup_entries;

inline void family_store(BatchSlots values, int32_t slot, uint64_t value) {
  if (slot < 0) return;
  batch_store(values, static_cast<std::size_t>(slot), value);
}
/** Read back a family's main slot (already stored this cycle) so a
  * duplicate key can be copied from it. */
inline uint64_t family_load(BatchSlots values, int32_t slot) {
  if (slot < 0) return 0;
  // Image mode keeps no slot shadow for claimed fields: read the record
  // through the slot's lane.  A check-mode scratch run (deferred view)
  // reads what the scratch run itself stored.
  if (!values.deferred && values.owner != nullptr && values.owner->image_mode())
    return values.owner->record().load(values.lanes[static_cast<std::size_t>(slot)]);
  return values.values[static_cast<std::size_t>(slot)];
}

void sample_batch_core_profile(const SystemGuider& model, BatchSlots v) {
  // Every other member of this family is an image-owned core stream now
  // (generated/image_owned_bindings.inc); the two RegNext(dtlb.io.miss_rdy)
  // copies belong to the memory side.
  const int32_t* t = g_core_slots.data();
  family_store(v, t[154], model.dtlb_miss_ready_registered());  // kCoreLsuDtlbMissReady
  for (const FamilyEntry& entry : g_core_dup_entries) {
    const int32_t primary = g_core_slots[entry.selector];
    if (primary < 0) continue;
    if (ModelBindings::instance().slot_is_gathered(primary)) continue;
    family_store(v, static_cast<int32_t>(entry.slot), family_load(v, primary));
  }
}

void sample_batch_mmio_memory_profile(const SystemGuider& model, BatchSlots v) {
  (void)model; (void)v;  // every stream of this family is image-owned (memory_export.inc)
}

void sample_batch_bpd_profile(const SystemGuider& model, BatchSlots v) {
  (void)model; (void)v;  // every stream of this family is image-owned (frontend_export.inc)
}

void sample_batch_fdivsqrt_profile(const SystemGuider& model, BatchSlots v) {
  const auto& oracles = model.fabric().fdivsqrt_oracles();
  for (const FamilyEntry& entry : g_fdivsqrt_entries)
    family_store(v, static_cast<int32_t>(entry.slot),
                 oracles[entry.selector]);
}

void sample_batch_fpu_profile(const SystemGuider& model, BatchSlots v) {
  const auto& oracles = model.fabric().fpu_oracles();
  for (const FamilyEntry& entry : g_fpu_entries)
    family_store(v, static_cast<int32_t>(entry.slot),
                 oracles[entry.selector]);
}

uint64_t sample_dcache_profile_override(const SystemGuider& model,
                                        std::size_t selector) {
  const auto& request =
      model.memory().debug_path_for_diagnostic().iomshr_active_oracle();
  switch (selector) {
    case 0: return request.data;
    case 1: return request.is_amo;
    case 2: return request.ldq_idx;
    case 3:
      return model.memory().dcache_for_diagnostic().bus_s2_oracle().br_mask;
    case 4:
      return model.memory()
          .dcache_for_diagnostic()
          .respq_br_mask_bank_oracle();
    case 5:
      return model.memory().dcache_for_diagnostic().bus_s2_oracle().is_amo;
  }
  return 0;
}

// The coherent-memory sidecar refreshes this compact oracle snapshot after
// every committed edge.  Sampling by its epoch is stronger than sampling by
// the previous edge's activity bit: a refresh that leaves the fabric idle
// still has to publish its final register image once.
static uint64_t coherent_memory_oracle_epoch(const SystemGuider& model) {
  return model.fabric().coherent_memory_oracle_version();
}

class SelectorBindingRegistrar {
 public:
  explicit SelectorBindingRegistrar(ModelBindings& bindings)
      : bindings_(bindings) {}

  void bind_selector(const char* key) {
    // Image-owned core streams were registered first; the locked promotion
    // list still names them.
    if (bindings_.find(key) != nullptr) return;
    const std::size_t fpu_selector = fpu_profile_selector(key);
    if (fpu_selector != kNoColdSelector) {
      g_fpu_entries.push_back(FamilyEntry{
          static_cast<uint32_t>(family_slot(key)),
          static_cast<uint32_t>(fpu_selector)});
      return;
    }
    const std::size_t fdivsqrt_selector = fdivsqrt_profile_selector(key);
    if (fdivsqrt_selector != kNoColdSelector) {
      g_fdivsqrt_entries.push_back(FamilyEntry{
          static_cast<uint32_t>(family_slot(key)),
          static_cast<uint32_t>(fdivsqrt_selector)});
      return;
    }
    const std::size_t dcache_selector = dcache_profile_selector(key);
    if (dcache_selector != kNoColdSelector) {
      promote(key, sample_dcache_profile_override, dcache_selector);
      return;
    }
    const std::size_t bpd_selector = bpd_profile_selector(key);
    if (bpd_selector != kNoColdSelector) {
      promote_table(key, g_bpd_slots.data(), g_bpd_slots.size(),
                    g_bpd_dup_entries, bpd_selector);
      return;
    }
    const std::size_t core_selector = core_profile_selector(key);
    if (core_selector != kNoColdSelector) {
      promote_table(key, g_core_slots.data(), g_core_slots.size(),
                    g_core_dup_entries, core_selector);
      return;
    }
    const std::size_t mmio_selector = mmio_memory_profile_selector(key);
    if (mmio_selector != kNoColdSelector) {
      promote_table(key, g_mmio_slots.data(), g_mmio_slots.size(),
                    g_mmio_dup_entries, mmio_selector);
      return;
    }
    const std::size_t selector = cold_profile_selector(key);
    if (selector != kNoColdSelector) {
      promote(key, sample_cold_profile_override, selector, nullptr,
              coherent_memory_oracle_epoch);
      return;
    }
    fprintf(stderr, "[BIND] no selector resolves %s\n", key);
    abort();
  }

 private:
  int family_slot(const char* key) {
    return manifest_kind_for_binding(key) == OracleKind::Combinational
               ? bindings_.reserve_sampled_combinational(key)
               : bindings_.reserve_sampled(key);
  }

  void promote_table(const char* key, int32_t* table, std::size_t size,
                     std::vector<FamilyEntry>& duplicates,
                     std::size_t selector) {
    if (std::getenv("SYSMODEL_DUMP_FAMILIES") != nullptr)
      fprintf(stderr, "[FAMILY] table=%p selector=%zu key=%s\n",
              static_cast<const void*>(table), selector, key);
    if (selector >= size) {
      fprintf(stderr, "[BIND] selector out of range for %s\n", key);
      abort();
    }
    const int slot = family_slot(key);
    if (table[selector] < 0) {
      table[selector] = slot;
    } else {
      duplicates.push_back(FamilyEntry{static_cast<uint32_t>(slot),
                                       static_cast<uint32_t>(selector)});
      bindings_.add_slot_alias(table[selector], slot);
    }
  }

  void promote(const char* key, IndexedSampleFn sample,
               std::size_t selector,
               IdlePredicate idle = nullptr,
               SampleEpochFn epoch = nullptr) {
    if (std::getenv("SYSMODEL_DUMP_FAMILIES") != nullptr)
      fprintf(stderr, "[PROMOTE] fn=%p selector=%zu key=%s\n",
              reinterpret_cast<const void*>(sample), selector, key);
    if (manifest_kind_for_binding(key) == OracleKind::Combinational)
      bindings_.bind_indexed_sampled_combinational(key, sample, selector, idle,
                                                   epoch);
    else
      bindings_.bind_indexed_sampled(key, sample, selector, idle, epoch);
  }

  ModelBindings& bindings_;
};

}  // namespace

void register_selector_bindings() {
  if (std::getenv("SYSMODEL_DUMP_FAMILIES") != nullptr) {
    fprintf(stderr, "[FAMILY-TABLE] bpd=%p core=%p mmio=%p\n",
            static_cast<const void*>(g_bpd_slots.data()), static_cast<const void*>(g_core_slots.data()),
            static_cast<const void*>(g_mmio_slots.data()));
    fprintf(stderr, "[PROMOTE-FN] dcache=%p cold=%p\n",
            reinterpret_cast<const void*>(&sample_dcache_profile_override),
            reinterpret_cast<const void*>(&sample_cold_profile_override));
  }
  SelectorBindingRegistrar bindings(ModelBindings::instance());
#include "generated/selector_bindings.inc"
  // selector_bindings.inc is the locked SmallBoom promotion list.  Pick up
  // append-only Large sidecar fields directly from the active manifest so a
  // new dynamic register cannot remain UNMODELED merely because it has no
  // Small-era row.
  for (const SystemProbeManifestRow& row : kSystemProbeManifest) {
    if (ModelBindings::instance().find(row.key) != nullptr) continue;
    if (fpu_profile_selector(row.key) != kNoColdSelector ||
        fdivsqrt_profile_selector(row.key) != kNoColdSelector)
      bindings.bind_selector(row.key);
  }

  // Family batches consume the tables the registrar just filled.  base=0
  // hands each batch the whole sample buffer; the tables carry the slots.
  ModelBindings::instance().add_batch_sampler(sample_batch_core_profile, 0, ModelBindings::SamplePlacement::Core, watch_sample_batch_core_profile);
  ModelBindings::instance().add_batch_sampler(sample_batch_mmio_memory_profile, 0, ModelBindings::SamplePlacement::PreStep, watch_sample_batch_mmio_memory_profile);
  ModelBindings::instance().add_batch_sampler(sample_batch_bpd_profile, 0, ModelBindings::SamplePlacement::Frontend, watch_sample_batch_bpd_profile);
  ModelBindings::instance().add_batch_sampler(sample_batch_fdivsqrt_profile, 0, ModelBindings::SamplePlacement::PreStep, watch_sample_batch_fdivsqrt_profile);
  ModelBindings::instance().add_batch_sampler(sample_batch_fpu_profile, 0, ModelBindings::SamplePlacement::PreStep, watch_sample_batch_fpu_profile);
}

#include "generated/image_owned_bindings.inc"

void register_model_bindings() {
  // Both the production join and the infrastructure self-test call this
  // entry point.  Idempotence makes their order explicit and avoids relying
  // on link-time static initialization.
  static bool registered = false;
  if (registered) return;
  registered = true;

  // Order of arrival, following duts/boom-repcut/MODEL.md:
  //
  //   register_uncore_bindings();     // Queue/Arbiter/Fragmenter/TLToAXI4/
  //                                   // Broadcast component library
  //   register_debug_bindings();      // remaining DMI shadow state
  //   register_frontend_bindings();   // fetch, TAGE-L, I-cache
  //   register_memory_bindings();     // D-cache, DTLB, PTW
  //   register_backend_bindings();    // rename/issue/ROB/LSU/commit + FP
  //
  // A subsystem is only listed once its differential passes; binding a stream
  // the model cannot actually predict turns an UNMODELED row, which reads as
  // work remaining, into a REAL mismatch row, which reads as a bug. Both are
  // true statements, but only the first one is useful before the subsystem
  // exists.

  register_image_owned_bindings();   // the core writes these into the record

  register_debug_invariant_bindings();
  register_debug_activation_bindings();
  register_reset_and_interrupt_invariant_bindings();
  register_structural_constant_bindings();
  register_live_core_pipeline_bindings();
  register_frontend_wave_a_bindings();
  register_itlb_state_bindings();
  register_dtlb_state_bindings();

  register_mbus_memory_extra_bindings();
  register_tile_buffer_extra_bindings();

  register_sbus_d_arbiter_extra_bindings();
  register_system_bus_sidecar_bindings();
  register_periphery_bus_sidecar_bindings();
  register_dcache_sparse_state_bindings();
  register_dcache_observable_storage_bindings();
  register_dcache_pipeline_shadow_bindings();

  register_ptw_state_bindings();
  register_unbound_regs_bindings();
  register_profile_debt_wave1_bindings();
  register_profile_debt_wave2_bindings();
  register_selector_bindings();
  register_active_face_bindings();

  register_core_bringup_probes_if_enabled();
}

#include "generated/watch_bindings.inc"

// Memory-side and uncore streams written straight into the model image
// (scripts/gen_memory_export.py); called by SystemGuider::step before the End
// samplers.

#include "generated/memory_export.inc"

}  // namespace chisa::boom_system

#endif
