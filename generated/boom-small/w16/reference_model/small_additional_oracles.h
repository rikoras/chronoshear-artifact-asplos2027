#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include "system_guider.h"
namespace chisa::boom_system::small_additional_oracles {
inline constexpr unsigned kCount = 45;
inline constexpr unsigned kWidth = 16;
using Snapshot = std::array<std::uint64_t, kCount>;
inline void capture(void* context, const SystemGuider& model, SystemGuider::PublishPhase phase) {
  if (phase != SystemGuider::PublishPhase::Registers) return;
  auto& values = *static_cast<Snapshot*>(context);
  const auto& core = model.backend().core();
  const auto& front = model.frontend();
  [[maybe_unused]] const auto& main = front.f3_queues_for_diagnostic().main_payload();
  [[maybe_unused]] const auto& bpd = front.f3_queues_for_diagnostic().bpd_payload();
  [[maybe_unused]] const auto& f4 = front.f4_queue_for_diagnostic().payload();
  [[maybe_unused]] const auto& update = front.bpd_for_diagnostic().registered_update();
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_csr_exe_unit_div_div_remainder__w0
  values[0] = (core.oracle_div_remainder(0)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_csr_exe_unit_div_div_remainder__w1
  values[1] = (core.oracle_div_remainder(1)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_csr_exe_unit_div_div_remainder__w2
  values[2] = (core.oracle_div_remainder(2)) & UINT64_C(0x3);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_0_slot_uop__v2_bank_0_0
  values[3] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 0)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_1_slot_uop__v2_bank_0_0
  values[4] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 1)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_2_slot_uop__v2_bank_0_0
  values[5] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 2)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_3_slot_uop__v2_bank_0_0
  values[6] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 3)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_4_slot_uop__v2_bank_0_0
  values[7] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 4)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_5_slot_uop__v2_bank_0_0
  values[8] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 5)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_6_slot_uop__v2_bank_0_0
  values[9] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 6)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fp_issue_unit_slots_7_slot_uop__v2_bank_0_0
  values[10] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Floating, 7)) & UINT64_C(0x3fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fpiu_unit_fdivsqrt_divsqrt_mul_reg_result_s3__w0
  values[11] = (model.fabric().fdivsqrt_oracles()[37]) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fpiu_unit_fdivsqrt_divsqrt_mul_reg_result_s3__w1
  values[12] = (model.fabric().fdivsqrt_oracles()[38]) & UINT64_C(0x1ffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fpiu_unit_fpu_fpu_fpmu_io_out_b_data__w0
  values[13] = (model.fabric().fpu_oracles()[59]) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_fp_pipeline_fpiu_unit_fpu_fpu_fpmu_io_out_b_data__w1
  values[14] = (model.fabric().fpu_oracles()[60]) & UINT64_C(0x1);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_0_slot_uop__v2_bank_0_0
  values[15] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 0)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_1_slot_uop__v2_bank_0_0
  values[16] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 1)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_2_slot_uop__v2_bank_0_0
  values[17] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 2)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_3_slot_uop__v2_bank_0_0
  values[18] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 3)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_4_slot_uop__v2_bank_0_0
  values[19] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 4)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_5_slot_uop__v2_bank_0_0
  values[20] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 5)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_6_slot_uop__v2_bank_0_0
  values[21] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 6)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_int_issue_unit_slots_7_slot_uop__v2_bank_0_0
  values[22] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Integer, 7)) & UINT64_C(0x1fffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_0_slot_uop__v2_bank_0_0
  values[23] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 0)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_1_slot_uop__v2_bank_0_0
  values[24] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 1)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_2_slot_uop__v2_bank_0_0
  values[25] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 2)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_3_slot_uop__v2_bank_0_0
  values[26] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 3)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_4_slot_uop__v2_bank_0_0
  values[27] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 4)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_5_slot_uop__v2_bank_0_0
  values[28] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 5)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_6_slot_uop__v2_bank_0_0
  values[29] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 6)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_mem_issue_unit_slots_7_slot_uop__v2_bank_0_0
  values[30] = (core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::Memory, 7)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_bitset_rob_val_bank_0
  values[31] = (core.oracle_rob_valid()) & UINT64_C(0xffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_bpd_banked_predictors_0_components_0_s1_update__bits_meta__w0
  values[32] = (std::uint64_t(update.meta[0]) | (std::uint64_t(update.meta[1]) << 32u)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_bpd_banked_predictors_0_components_0_s1_update__bits_meta__w1
  values[33] = (std::uint64_t(update.meta[2]) | (std::uint64_t(update.meta[3]) << 32u)) & UINT64_C(0xffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_ram__v2_bank_0_0
  values[34] = (((std::uint64_t(main.mask) & UINT64_C(0xf)) << 2u) | ((std::uint64_t(main.xcpt_pf_if) & UINT64_C(0x1)) << 1u) | ((std::uint64_t(main.xcpt_ae_if) & UINT64_C(0x1)) << 0u)) & UINT64_C(0x3f);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_ram__v2_bank_0_1
  values[35] = (((std::uint64_t(main.ghist.current_saw_branch_not_taken) & UINT64_C(0x1)) << 7u) | ((std::uint64_t(main.ghist.new_saw_branch_not_taken) & UINT64_C(0x1)) << 6u) | ((std::uint64_t(main.ghist.new_saw_branch_taken) & UINT64_C(0x1)) << 5u) | ((std::uint64_t(main.ghist.ras_idx) & UINT64_C(0x1f)) << 0u)) & UINT64_C(0xff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_bpd_resp_ram__v2_bank_0_0
  values[36] = (((std::uint64_t(bpd.preds[0].taken) & UINT64_C(0x1)) << 43u) | ((std::uint64_t(bpd.preds[0].predicted_pc_valid) & UINT64_C(0x1)) << 42u) | ((std::uint64_t(bpd.preds[0].predicted_pc) & UINT64_C(0xffffffffff)) << 2u) | ((std::uint64_t(bpd.preds[1].taken) & UINT64_C(0x1)) << 1u) | ((std::uint64_t(bpd.preds[1].predicted_pc_valid) & UINT64_C(0x1)) << 0u)) & UINT64_C(0xfffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_bpd_resp_ram__v2_bank_0_1
  values[37] = (((std::uint64_t(bpd.preds[1].predicted_pc) & UINT64_C(0xffffffffff)) << 2u) | ((std::uint64_t(bpd.preds[2].taken) & UINT64_C(0x1)) << 1u) | ((std::uint64_t(bpd.preds[2].predicted_pc_valid) & UINT64_C(0x1)) << 0u)) & UINT64_C(0x3ffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_bpd_resp_ram__v2_bank_0_2
  values[38] = (((std::uint64_t(bpd.preds[2].predicted_pc) & UINT64_C(0xffffffffff)) << 2u) | ((std::uint64_t(bpd.preds[3].taken) & UINT64_C(0x1)) << 1u) | ((std::uint64_t(bpd.preds[3].predicted_pc_valid) & UINT64_C(0x1)) << 0u)) & UINT64_C(0x3ffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_bpd_resp_ram_meta_0__w0
  values[39] = (std::uint64_t(bpd.meta[0]) | (std::uint64_t(bpd.meta[1]) << 32u)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f3_bpd_resp_ram_meta_0__w1
  values[40] = (std::uint64_t(bpd.meta[2]) | (std::uint64_t(bpd.meta[3]) << 32u)) & UINT64_C(0xffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f4_ram__v2_bank_0_5
  values[41] = (((std::uint64_t(((f4.sfb_mask >> 0u) & 1u)) & UINT64_C(0x1)) << 63u) | ((std::uint64_t(((f4.sfb_mask >> 1u) & 1u)) & UINT64_C(0x1)) << 62u) | ((std::uint64_t(((f4.sfb_mask >> 2u) & 1u)) & UINT64_C(0x1)) << 61u) | ((std::uint64_t(((f4.sfb_mask >> 3u) & 1u)) & UINT64_C(0x1)) << 60u) | ((std::uint64_t(((f4.shadowed_mask >> 0u) & 1u)) & UINT64_C(0x1)) << 59u) | ((std::uint64_t(((f4.shadowed_mask >> 1u) & 1u)) & UINT64_C(0x1)) << 58u) | ((std::uint64_t(((f4.shadowed_mask >> 2u) & 1u)) & UINT64_C(0x1)) << 57u) | ((std::uint64_t(((f4.shadowed_mask >> 3u) & 1u)) & UINT64_C(0x1)) << 56u) | ((std::uint64_t(f4.cfi_valid) & UINT64_C(0x1)) << 55u) | ((std::uint64_t(f4.cfi_idx) & UINT64_C(0x3)) << 53u) | ((std::uint64_t(f4.cfi_type) & UINT64_C(0x7)) << 50u) | ((std::uint64_t(f4.cfi_is_call) & UINT64_C(0x1)) << 49u) | ((std::uint64_t(f4.cfi_is_ret) & UINT64_C(0x1)) << 48u) | ((std::uint64_t(f4.ras_top) & UINT64_C(0xffffffffff)) << 8u) | ((std::uint64_t(f4.mask) & UINT64_C(0xf)) << 4u) | ((std::uint64_t(f4.br_mask) & UINT64_C(0xf)) << 0u)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f4_ram__v2_bank_0_6
  values[42] = (((std::uint64_t(f4.ghist.current_saw_branch_not_taken) & UINT64_C(0x1)) << 17u) | ((std::uint64_t(f4.ghist.new_saw_branch_not_taken) & UINT64_C(0x1)) << 16u) | ((std::uint64_t(f4.ghist.new_saw_branch_taken) & UINT64_C(0x1)) << 15u) | ((std::uint64_t(f4.ghist.ras_idx) & UINT64_C(0x1f)) << 10u) | ((std::uint64_t(f4.xcpt_pf_if) & UINT64_C(0x1)) << 9u) | ((std::uint64_t(f4.xcpt_ae_if) & UINT64_C(0x1)) << 8u) | ((std::uint64_t(((f4.bp_debug_mask >> 0u) & 1u)) & UINT64_C(0x1)) << 7u) | ((std::uint64_t(((f4.bp_debug_mask >> 1u) & 1u)) & UINT64_C(0x1)) << 6u) | ((std::uint64_t(((f4.bp_debug_mask >> 2u) & 1u)) & UINT64_C(0x1)) << 5u) | ((std::uint64_t(((f4.bp_debug_mask >> 3u) & 1u)) & UINT64_C(0x1)) << 4u) | ((std::uint64_t(((f4.bp_xcpt_mask >> 0u) & 1u)) & UINT64_C(0x1)) << 3u) | ((std::uint64_t(((f4.bp_xcpt_mask >> 1u) & 1u)) & UINT64_C(0x1)) << 2u) | ((std::uint64_t(((f4.bp_xcpt_mask >> 2u) & 1u)) & UINT64_C(0x1)) << 1u) | ((std::uint64_t(((f4.bp_xcpt_mask >> 3u) & 1u)) & UINT64_C(0x1)) << 0u)) & UINT64_C(0x3ffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f4_ram_bpd_meta_0__w0
  values[43] = (std::uint64_t(f4.bpd_meta[0]) | (std::uint64_t(f4.bpd_meta[1]) << 32u)) & UINT64_C(0xffffffffffffffff);
  // ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_f4_ram_bpd_meta_0__w1
  values[44] = (std::uint64_t(f4.bpd_meta[2]) | (std::uint64_t(f4.bpd_meta[3]) << 32u)) & UINT64_C(0xffffffffffffff);
}
struct Placement { std::uint32_t offset; unsigned bytes; };
inline constexpr Placement kPlacement[] = {
  {13824u, 8u},
  {14080u, 8u},
  {127168u, 1u},
  {55296u, 8u},
  {55552u, 8u},
  {55808u, 8u},
  {56064u, 8u},
  {56320u, 8u},
  {56576u, 8u},
  {56832u, 8u},
  {57088u, 8u},
  {17664u, 8u},
  {17920u, 8u},
  {15616u, 8u},
  {128000u, 1u},
  {59392u, 8u},
  {59648u, 8u},
  {59904u, 8u},
  {60160u, 8u},
  {60416u, 8u},
  {60672u, 8u},
  {60928u, 8u},
  {61184u, 8u},
  {57344u, 8u},
  {57600u, 8u},
  {57856u, 8u},
  {58112u, 8u},
  {58368u, 8u},
  {58624u, 8u},
  {58880u, 8u},
  {59136u, 8u},
  {86656u, 4u},
  {4864u, 8u},
  {5120u, 8u},
  {143936u, 1u},
  {143968u, 1u},
  {53760u, 8u},
  {54016u, 8u},
  {54272u, 8u},
  {11776u, 8u},
  {12032u, 8u},
  {54528u, 8u},
  {89472u, 4u},
  {12288u, 8u},
  {12544u, 8u},
};
inline void inject(const Snapshot* cycles, char* expanded) {
  for (unsigned lane = 0; lane < kCount; ++lane)
    for (unsigned p = 0; p < 2 * kWidth; ++p) {
      const unsigned element = p < kWidth ? p : 3 * kWidth - 1 - p;
      const auto& out = kPlacement[lane];
      std::memcpy(expanded + out.offset + element * out.bytes, &cycles[p][lane], out.bytes);
    }
}
} // namespace chisa::boom_system::small_additional_oracles
