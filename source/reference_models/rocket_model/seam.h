#pragma once
// rocket_model: the Rocket core module boundary (io.* of the DefaultConfig Rocket
// module), kept binary-identical to the validated hybrid producer's structs so
// recorded boundary traces replay without conversion.
#include <cstdint>
#include "isa.h"

namespace chisa::rocket_model {

struct RocketSystemBtbResponse {
    uint8_t  cfi_type = 0;
    bool     taken = false;
    uint8_t  mask = 0;
    bool     bridx = false;
    uint64_t target = 0;
    uint8_t  entry = 0;
    uint8_t  bht_history = 0;
    bool     bht_value = false;
};

struct RocketSystemImemInputs {
    bool     clock_enabled = false;
    bool     resp_valid = false;
    RocketSystemBtbResponse resp_btb{};
    uint64_t resp_pc = 0;
    uint32_t resp_data = 0;
    uint8_t  resp_mask = 0;
    bool     resp_xcpt_pf_inst = false;
    bool     resp_xcpt_ae_inst = false;
    bool     resp_replay = false;
    uint64_t npc = 0;
    bool     perf_acquire = false;
    bool     perf_tlb_miss = false;
};

struct RocketSystemDmemResponse {
    bool     valid = false;
    uint64_t addr = 0;
    uint8_t  tag = 0;
    uint8_t  cmd = 0;
    uint8_t  size = 0;
    bool     signed_data = false;
    uint8_t  dprv = 0;
    uint64_t data = 0;
    uint8_t  mask = 0;
    bool     replay = false;
    bool     has_data = false;
    uint64_t data_word_bypass = 0;
    uint64_t data_raw = 0;
    uint64_t store_data = 0;
};

struct RocketSystemDmemInputs {
    bool     req_ready = false;
    bool     s2_nack = false;
    bool     s2_nack_cause_raw = false;
    bool     s2_uncached = false;
    uint32_t s2_paddr = 0;
    RocketSystemDmemResponse resp{};
    bool     replay_next = false;
    bool     s2_xcpt_ma_ld = false;
    bool     s2_xcpt_ma_st = false;
    bool     s2_xcpt_pf_ld = false;
    bool     s2_xcpt_pf_st = false;
    bool     s2_xcpt_ae_ld = false;
    bool     s2_xcpt_ae_st = false;
    bool     ordered = false;
    bool     perf_acquire = false;
    bool     perf_release = false;
    bool     perf_grant = false;
    bool     perf_tlb_miss = false;
    bool     perf_blocked = false;
    bool     perf_can_accept_store_then_load = false;
    bool     perf_can_accept_store_then_rmw = false;
    bool     perf_can_accept_load_then_load = false;
    bool     perf_store_buffer_empty_after_load = false;
    bool     perf_store_buffer_empty_after_store = false;
    bool     clock_enabled = false;
};

struct RocketSystemFpuInputs {
    bool     fcsr_flags_valid = false;
    uint8_t  fcsr_flags = 0;
    uint64_t store_data = 0;
    uint64_t toint_data = 0;
    bool     fcsr_ready = false;
    bool     nack_mem = false;
    bool     illegal_rm = false;
    uint8_t  dec_ldst = 0;
    uint8_t  dec_wen = 0;
    uint8_t  dec_ren1 = 0;
    uint8_t  dec_ren2 = 0;
    uint8_t  dec_ren3 = 0;
    uint8_t  dec_swap12 = 0;
    uint8_t  dec_swap23 = 0;
    uint8_t  dec_type_tag_in = 0;
    uint8_t  dec_type_tag_out = 0;
    uint8_t  dec_fromint = 0;
    uint8_t  dec_toint = 0;
    uint8_t  dec_fastpipe = 0;
    uint8_t  dec_fma = 0;
    uint8_t  dec_div = 0;
    uint8_t  dec_sqrt = 0;
    uint8_t  dec_wflags = 0;
    bool     sboard_set = false;
    bool     sboard_clear = false;
    uint8_t  sboard_clear_addr = 0;
};

// DefaultConfig does not instantiate a RoCC accelerator, but Rocket still
// exposes every RoCCCoreIO leaf.  The parent drives the accelerator side to
// structural constants.  Carry those leaves explicitly so the hybrid seam
// can prove the constants instead of relying on invalid/default lowering.
struct RocketSystemRoccMemRequestInputs {
    bool     req_valid = false;
    uint64_t req_addr = 0;
    uint8_t  req_tag = 0;
    uint8_t  req_cmd = 0;
    uint8_t  req_size = 0;
    bool     req_signed = false;
    uint8_t  req_dprv = 0;
    bool     req_phys = false;
    bool     req_no_alloc = false;
    bool     req_no_xcpt = false;
    uint64_t req_data = 0;
    uint8_t  req_mask = 0;
    bool     s1_kill = false;
    uint64_t s1_data = 0;
    uint8_t  s1_mask = 0;
    bool     s2_kill = false;
    bool     keep_clock_enabled = false;
};

struct RocketSystemRoccMemResponseOutputs {
    bool     req_ready = false;
    bool     s2_nack = false;
    bool     s2_nack_cause_raw = false;
    bool     s2_uncached = false;
    uint32_t s2_paddr = 0;
    RocketSystemDmemResponse resp{};
    bool     replay_next = false;
    bool     s2_xcpt_ma_ld = false;
    bool     s2_xcpt_ma_st = false;
    bool     s2_xcpt_pf_ld = false;
    bool     s2_xcpt_pf_st = false;
    bool     s2_xcpt_ae_ld = false;
    bool     s2_xcpt_ae_st = false;
    bool     ordered = false;
    bool     perf_acquire = false;
    bool     perf_release = false;
    bool     perf_grant = false;
    bool     perf_tlb_miss = false;
    bool     perf_blocked = false;
    bool     perf_can_accept_store_then_load = false;
    bool     perf_can_accept_store_then_rmw = false;
    bool     perf_can_accept_load_then_load = false;
    bool     perf_store_buffer_empty_after_load = false;
    bool     perf_store_buffer_empty_after_store = false;
    bool     clock_enabled = false;
};

struct RocketSystemRoccInputs {
    bool     cmd_ready = false;
    bool     resp_valid = false;
    uint8_t  resp_rd = 0;
    uint64_t resp_data = 0;
    RocketSystemRoccMemRequestInputs mem{};
    bool     busy = false;
    bool     interrupt = false;
};

struct RocketFullSystemInputs {
    bool reset = false;
    uint64_t hartid = 0;
    uint32_t reset_vector = 0;
    bool interrupt_debug = false;
    bool interrupt_mtip = false;
    bool interrupt_msip = false;
    bool interrupt_meip = false;
    bool interrupt_seip = false;
    RocketSystemImemInputs imem{};
    RocketSystemDmemInputs dmem{};
    bool ptw_perf_l2miss = false;
    bool ptw_perf_l2hit = false;
    bool ptw_perf_pte_miss = false;
    bool ptw_perf_pte_hit = false;
    bool ptw_clock_enabled = false;
    RocketSystemFpuInputs fpu{};
    RocketSystemRoccInputs rocc{};
    bool trace_stall = false;
};

struct RocketSystemStatusOutputs {
    bool debug = false;
    bool cease = false;
    bool wfi = false;
    uint32_t isa = 0;
    uint8_t dprv = 0;
    uint8_t prv = 0;
    bool sd = false;
    uint32_t zero2 = 0;
    uint8_t sxl = 0;
    uint8_t uxl = 0;
    bool sd_rv32 = false;
    uint8_t zero1 = 0;
    bool tsr = false;
    bool tw = false;
    bool tvm = false;
    bool mxr = false;
    bool sum = false;
    bool mprv = false;
    uint8_t xs = 0;
    uint8_t fs = 0;
    uint8_t mpp = 0;
    uint8_t vs = 0;
    bool spp = false;
    bool mpie = false;
    bool hpie = false;
    bool spie = false;
    bool upie = false;
    bool mie = false;
    bool hie = false;
    bool sie = false;
    bool uie = false;
};

struct RocketSystemPmpOutput {
    bool cfg_l = false;
    uint8_t cfg_res = 0;
    uint8_t cfg_a = 0;
    bool cfg_x = false;
    bool cfg_w = false;
    bool cfg_r = false;
    uint32_t addr = 0;
    uint32_t mask = 0;
};

struct RocketSystemImemOutputs {
    bool     might_request = false;
    bool     resp_ready = false;
    bool     req_valid = false;
    uint64_t req_pc = 0;
    bool     req_speculative = false;
    bool     sfence_valid = false;
    bool     sfence_rs1 = false;
    bool     sfence_rs2 = false;
    uint64_t sfence_addr = 0;
    bool     sfence_asid = false;
    bool     btb_update_valid = false;
    RocketSystemBtbResponse btb_prediction{};
    uint64_t btb_pc = 0;
    uint64_t btb_target = 0;
    bool     btb_taken = false;
    bool     btb_is_valid = false;
    uint64_t btb_branch_pc = 0;
    uint8_t  btb_cfi_type = 0;
    bool     bht_update_valid = false;
    uint8_t  bht_prediction_history = 0;
    bool     bht_prediction_value = false;
    uint64_t bht_pc = 0;
    bool     bht_branch = false;
    bool     bht_taken = false;
    bool     bht_mispredict = false;
    bool     ras_update_valid = false;
    uint8_t  ras_cfi_type = 0;
    uint64_t ras_return_addr = 0;
    bool     flush_icache = false;
};

struct RocketSystemDmemOutputs {
    bool     req_valid = false;
    uint64_t req_addr = 0;
    uint8_t  req_tag = 0;
    uint8_t  req_cmd = 0;
    uint8_t  req_size = 0;
    bool     req_signed = false;
    uint8_t  req_dprv = 0;
    bool     req_phys = false;
    bool     req_no_alloc = false;
    bool     req_no_xcpt = false;
    uint64_t req_data = 0;
    uint8_t  req_mask = 0;
    bool     s1_kill = false;
    uint64_t s1_data = 0;
    uint8_t  s1_mask = 0;
    bool     s2_kill = false;
    bool     keep_clock_enabled = false;
};

struct RocketSystemFpuOutputs {
    uint64_t hartid = 0;
    uint64_t time = 0;
    uint32_t inst = 0;
    uint64_t fromint_data = 0;
    uint8_t  fcsr_rm = 0;
    bool     dmem_resp_valid = false;
    uint8_t  dmem_resp_type = 0;
    uint8_t  dmem_resp_tag = 0;
    uint64_t dmem_resp_data = 0;
    bool     valid = false;
    bool     killx = false;
    bool     killm = false;
    bool     keep_clock_enabled = false;
};

struct RocketSystemTraceOutput {
    bool valid = false;
    uint64_t iaddr = 0;
    uint32_t insn = 0;
    uint8_t priv = 0;
    bool exception = false;
    bool interrupt = false;
    uint64_t cause = 0;
    uint64_t tval = 0;
};

struct RocketSystemRoccInstructionOutputs {
    uint8_t funct = 0;
    uint8_t rs2 = 0;
    uint8_t rs1 = 0;
    bool xd = false;
    bool xs1 = false;
    bool xs2 = false;
    uint8_t rd = 0;
    uint8_t opcode = 0;
};

struct RocketSystemRoccOutputs {
    bool cmd_valid = false;
    RocketSystemRoccInstructionOutputs cmd_inst{};
    uint64_t cmd_rs1 = 0;
    uint64_t cmd_rs2 = 0;
    RocketSystemStatusOutputs cmd_status{};
    bool resp_ready = false;
    RocketSystemRoccMemResponseOutputs mem{};
    bool exception = false;
};

struct RocketFullSystemOutputs {
    RocketSystemImemOutputs imem{};
    RocketSystemDmemOutputs dmem{};
    uint8_t ptbr_mode = 0;
    uint16_t ptbr_asid = 0;
    uint64_t ptbr_ppn = 0;
    RocketSystemStatusOutputs status{};
    RocketSystemPmpOutput pmp[8]{};
    bool custom_csr_wen[4]{};
    uint64_t custom_csr_wdata[4]{};
    uint64_t custom_csr_value[4]{};
    RocketSystemFpuOutputs fpu{};
    RocketSystemRoccOutputs rocc{};
    RocketSystemTraceOutput trace{};
    bool bpwatch_valid = false;
    bool bpwatch_rvalid = false;
    bool bpwatch_wvalid = false;
    bool bpwatch_ivalid = false;
    uint8_t bpwatch_action = 0;
    bool cease = false;
    bool wfi = false;
};

}  // namespace chisa::rocket_model
