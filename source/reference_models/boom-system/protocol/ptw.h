#pragma once
#include <array>
#include <cstdint>
namespace chisa::boom_system::protocol {
struct PtwRequest {
  bool valid = false;
  bool payload_valid = false;
  std::uint32_t vpn = 0;

  bool operator==(const PtwRequest& other) const {
    return valid == other.valid && payload_valid == other.payload_valid &&
           vpn == other.vpn;
  }
  bool operator!=(const PtwRequest& other) const { return !(*this == other); }
};

struct PtwPte {
  std::uint64_t ppn = 0;
  std::uint8_t reserved_for_software = 0;
  bool d = false;
  bool a = false;
  bool g = false;
  bool u = false;
  bool x = false;
  bool w = false;
  bool r = false;
  bool v = false;
};

struct PtwResponse {
  bool valid = false;
  bool access_exception = false;
  PtwPte pte{};
  std::uint8_t level = 0;
  bool fragmented_superpage = false;
  bool homogeneous = false;
};

struct PtwStatus {
  bool debug = false;
  bool cease = false;
  bool wfi = false;
  std::uint32_t isa = 0;
  std::uint8_t dprv = 3;
  std::uint8_t prv = 3;
  bool sd = false;
  std::uint32_t zero2 = 0;
  std::uint8_t sxl = 2;
  std::uint8_t uxl = 2;
  bool sd_rv32 = false;
  std::uint8_t zero1 = 0;
  bool tsr = false;
  bool tw = false;
  bool tvm = false;
  bool mxr = false;
  bool sum = false;
  bool mprv = false;
  std::uint8_t xs = 0;
  std::uint8_t fs = 0;
  std::uint8_t mpp = 3;
  std::uint8_t vs = 0;
  bool spp = false;
  bool mpie = false;
  bool hpie = false;
  bool spie = false;
  bool upie = false;
  bool mie = false;
  bool hie = false;
  bool sie = false;
  bool uie = false;

  bool operator==(const PtwStatus& o) const {
    return debug == o.debug && cease == o.cease && wfi == o.wfi &&
           isa == o.isa && dprv == o.dprv && prv == o.prv && sd == o.sd &&
           zero2 == o.zero2 && sxl == o.sxl && uxl == o.uxl &&
           sd_rv32 == o.sd_rv32 && zero1 == o.zero1 && tsr == o.tsr &&
           tw == o.tw && tvm == o.tvm && mxr == o.mxr && sum == o.sum &&
           mprv == o.mprv && xs == o.xs && fs == o.fs && mpp == o.mpp &&
           vs == o.vs && spp == o.spp && mpie == o.mpie &&
           hpie == o.hpie && spie == o.spie && upie == o.upie &&
           mie == o.mie && hie == o.hie && sie == o.sie && uie == o.uie;
  }
  bool operator!=(const PtwStatus& other) const { return !(*this == other); }
};

struct PtwPmp {
  bool locked = false;
  std::uint8_t reserved = 0;
  std::uint8_t address_mode = 0;
  bool execute = false;
  bool write = false;
  bool read = false;
  std::uint32_t address = 0;
  std::uint32_t mask = 0;

  bool operator==(const PtwPmp& o) const {
    return locked == o.locked && reserved == o.reserved &&
           address_mode == o.address_mode && execute == o.execute &&
           write == o.write && read == o.read && address == o.address &&
           mask == o.mask;
  }
  bool operator!=(const PtwPmp& other) const { return !(*this == other); }
};

struct PtwMemoryResponse {
  bool valid = false;
  std::uint64_t address = 0;
  std::uint8_t tag = 0;
  std::uint8_t command = 0;
  std::uint8_t size = 0;
  bool is_signed = false;
  std::uint8_t dprv = 0;
  std::uint64_t data = 0;
  std::uint8_t mask = 0;
  bool replay = false;
  bool has_data = false;
  std::uint64_t data_word_bypass = 0;
  std::uint64_t data_raw = 0;
  std::uint64_t store_data = 0;

  bool operator==(const PtwMemoryResponse& o) const {
    return valid == o.valid && address == o.address && tag == o.tag &&
           command == o.command && size == o.size &&
           is_signed == o.is_signed && dprv == o.dprv && data == o.data &&
           mask == o.mask && replay == o.replay && has_data == o.has_data &&
           data_word_bypass == o.data_word_bypass &&
           data_raw == o.data_raw && store_data == o.store_data;
  }
  bool operator!=(const PtwMemoryResponse& other) const {
    return !(*this == other);
  }
};

struct PtwMemoryInputs {
  bool request_ready = false;
  bool s2_nack = false;
  bool s2_nack_cause_raw = false;
  bool s2_uncached = false;
  std::uint32_t s2_paddr = 0;
  PtwMemoryResponse response{};
  bool replay_next = false;
  bool s2_xcpt_ma_ld = false;
  bool s2_xcpt_ma_st = false;
  bool s2_xcpt_pf_ld = false;
  bool s2_xcpt_pf_st = false;
  bool s2_xcpt_ae_ld = false;
  bool s2_xcpt_ae_st = false;
  bool ordered = true;
  bool perf_acquire = false;
  bool perf_release = false;
  bool perf_grant = false;
  bool perf_tlb_miss = false;
  bool perf_blocked = false;
  bool perf_can_accept_store_then_load = false;
  bool perf_can_accept_store_then_rmw = false;
  bool perf_can_accept_load_then_load = false;
  bool perf_store_buffer_empty_after_load = false;
  bool perf_store_buffer_empty_after_store = false;
  bool clock_enabled = true;

  bool operator==(const PtwMemoryInputs& o) const {
    return request_ready == o.request_ready && s2_nack == o.s2_nack &&
           s2_nack_cause_raw == o.s2_nack_cause_raw &&
           s2_uncached == o.s2_uncached && s2_paddr == o.s2_paddr &&
           response == o.response && replay_next == o.replay_next &&
           s2_xcpt_ma_ld == o.s2_xcpt_ma_ld &&
           s2_xcpt_ma_st == o.s2_xcpt_ma_st &&
           s2_xcpt_pf_ld == o.s2_xcpt_pf_ld &&
           s2_xcpt_pf_st == o.s2_xcpt_pf_st &&
           s2_xcpt_ae_ld == o.s2_xcpt_ae_ld &&
           s2_xcpt_ae_st == o.s2_xcpt_ae_st && ordered == o.ordered &&
           perf_acquire == o.perf_acquire && perf_release == o.perf_release &&
           perf_grant == o.perf_grant && perf_tlb_miss == o.perf_tlb_miss &&
           perf_blocked == o.perf_blocked &&
           perf_can_accept_store_then_load ==
               o.perf_can_accept_store_then_load &&
           perf_can_accept_store_then_rmw ==
               o.perf_can_accept_store_then_rmw &&
           perf_can_accept_load_then_load ==
               o.perf_can_accept_load_then_load &&
           perf_store_buffer_empty_after_load ==
               o.perf_store_buffer_empty_after_load &&
           perf_store_buffer_empty_after_store ==
               o.perf_store_buffer_empty_after_store &&
           clock_enabled == o.clock_enabled;
  }
  bool operator!=(const PtwMemoryInputs& other) const {
    return !(*this == other);
  }
};

struct PtwInputs {
  bool reset = false;
  std::array<PtwRequest, 3> requestors{};  // DTLB, ITLB, core.
  std::uint8_t ptbr_mode = 0;
  std::uint16_t ptbr_asid = 0;
  std::uint64_t ptbr_ppn = 0;
  bool sfence_valid = false;
  bool sfence_rs1 = false;
  bool sfence_rs2 = false;
  std::uint64_t sfence_address = 0;
  bool sfence_asid = false;
  PtwStatus status{};
  std::array<PtwPmp, 8> pmp{};
  bool custom_csr_write_enable = false;
  std::uint64_t custom_csr_write_data = 0;
  std::uint64_t custom_csr_value = 0;
  PtwMemoryInputs memory{};

  bool operator==(const PtwInputs& o) const {
    return reset == o.reset && requestors == o.requestors &&
           ptbr_mode == o.ptbr_mode && ptbr_asid == o.ptbr_asid &&
           ptbr_ppn == o.ptbr_ppn && sfence_valid == o.sfence_valid &&
           sfence_rs1 == o.sfence_rs1 && sfence_rs2 == o.sfence_rs2 &&
           sfence_address == o.sfence_address &&
           sfence_asid == o.sfence_asid && status == o.status &&
           pmp == o.pmp &&
           custom_csr_write_enable == o.custom_csr_write_enable &&
           custom_csr_write_data == o.custom_csr_write_data &&
           custom_csr_value == o.custom_csr_value && memory == o.memory;
  }
  bool operator!=(const PtwInputs& other) const { return !(*this == other); }
};

struct PtwMemoryRequest {
  bool valid = false;
  std::uint64_t address = 0;
  std::uint8_t tag = 0;
  std::uint8_t command = 0;
  std::uint8_t size = 0;
  bool is_signed = false;
  std::uint8_t dprv = 0;
  bool physical = false;
  bool no_allocate = false;
  bool no_exception = false;
  std::uint64_t data = 0;
  std::uint8_t mask = 0;
};

struct PtwOutputs {
  std::array<bool, 3> request_ready{};
  std::array<PtwResponse, 3> responses{};
  PtwMemoryRequest memory_request{};
  bool memory_s1_kill = false;
  std::uint64_t memory_s1_data = 0;
  std::uint8_t memory_s1_mask = 0;
  bool memory_s2_kill = false;
  bool memory_keep_clock_enabled = false;
  bool perf_l2_miss = false;
  bool perf_l2_hit = false;
  bool perf_pte_miss = false;
  bool perf_pte_hit = false;
  bool clock_enabled = false;
};

// Exact order of the 25 Small PTW streams, followed by the Large-only lifted
// L2-TLB synchronous-read address register.
using PtwOracleState = std::array<std::uint64_t, 36>;   // 26..35: partition-cut l2_refill, s1_valid, valid_1_0 words

} // namespace chisa::boom_system::protocol
