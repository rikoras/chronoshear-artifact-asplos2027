#pragma once
#include "../boom_model/common/core_types.h"

// The system consumes the rewritten core interface. No legacy type dispatch.
namespace chisa::boom_system::core_access {
template <class Core> const GuiderCSR& csr(const Core& core) { return core.csr(); }
template <class Core> int rob_head(const Core& core) { return core.rob_head(); }
template <class Core> int rob_tail(const Core& core) { return core.rob_tail(); }
template <class Core> bool rob_flush(const Core& core) { return core.rob_flush_now(); }
template <class Core> bool rob_exception(const Core& core) { return core.rob_exception_now(); }
template <class Core> bool mem_agu_valid(const Core& core) { return core.mem_agu_valid(); }
template <class Core> boomcfg::br_mask_t b1_resolve(const Core& core) { return core.b1_resolve_mask_now(); }
template <class Core> boomcfg::br_mask_t b1_mispredict(const Core& core) { return core.b1_mispred_mask_now(); }
struct SfenceRequest { bool valid, rs1, rs2; std::uint64_t address; };
template <class Core> SfenceRequest sfence(const Core& core) {
  const auto request = core.sfence_request();
  return {request.valid, request.rs1, request.rs2, request.address};
}
}  // namespace chisa::boom_system::core_access
