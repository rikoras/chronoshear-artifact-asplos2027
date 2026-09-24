#pragma once
// ============================================================================
// Small BOOM instruction-TLB response for the qualified machine-mode path.
//
// The current debug bootstrap and Dhrystone execution keep satp in Bare mode,
// execute in M-mode, and leave the PMP entries unlocked/empty.  Rocket TLB's
// response therefore bypasses translation: the physical address is the low
// paddrBits=32 bits of the request VA, with no miss or instruction exception.
//
// This deliberately does not claim S/U-mode, Sv39, refill, or PMP coverage.
// Those require CSR/PTW/PMP state inputs and will replace this scoped slice.
// ============================================================================

#include <cstdint>

#include "small_f0_f2.h"
#include "small_tlb.h"

namespace chisa::boom_system::components {

class SmallMachineItlb {
 public:
  SmallFrontendTlbResponse outputs(const SmallTlbCycleInputs& input,
                                   bool debug_mode = false) const {
    if (!input.vm_enabled || input.passthrough)
      return outputs(input.virtual_address, input.request_valid, debug_mode);

    const SmallTlbCycleOutputs translated = state_.outputs(input);
    SmallFrontendTlbResponse result;
    result.paddr = translated.physical_address;
    result.miss = translated.miss;
    result.xcpt_pf_if = translated.bad_virtual_address;
    if (translated.hit && !translated.multiple_hits) {
      const bool privilege_ok =
          input.privilege == 1 ? !translated.data.u
                               : input.privilege == 0 && translated.data.u;
      const bool execute_allowed =
          translated.special_hit ? input.dynamic_execute_permission
                                 : translated.data.px;
      result.xcpt_ae_if = translated.data.ae || !execute_allowed;
      result.xcpt_pf_if |=
          !translated.data.ae && !(privilege_ok && translated.data.sx);
    }
    return result;
  }

  SmallFrontendTlbResponse outputs(std::uint64_t vaddr,
                                   bool lookup_valid,
                                   bool debug_mode = false) const {
    (void)lookup_valid;
    SmallFrontendTlbResponse result;
    result.paddr = vaddr & UINT64_C(0xffffffff);
    // In Bare mode ae.inst is the inverse of the manager/PMP execute check.
    // The exercised executable managers are Debug ROM, Boot ROM, and DRAM;
    // other legal MMIO managers are deliberately non-executable.
    result.xcpt_ae_if =
        !is_executable(result.paddr, debug_mode);
    return result;
  }

  void step(std::uint64_t vaddr, bool lookup_valid,
            bool reset_asserted = false) {
    SmallTlbCycleInputs input;
    input.reset = reset_asserted;
    input.request_valid = lookup_valid;
    input.virtual_address = vaddr;
    state_.step(input);
  }

  void step(const SmallTlbCycleInputs& input) { state_.step(input); }

  /** Registered Rocket-TLB state.  The existing functional response above
    * remains the qualified Bare-mode path; VM activation is connected through
    * the explicit lookup/PTW/refill/sfence contract in the next integration
    * layer instead of being hidden behind this compatibility API. */
  const SmallInstructionTlb& state_for_diagnostic() const { return state_; }

  SmallInstructionTlb& state_for_integration() { return state_; }

 private:
  static bool contains(std::uint64_t address, std::uint64_t base,
                       std::uint64_t size) {
    return address >= base && address - base < size;
  }

  static bool is_debug_address(std::uint64_t address) {
    return contains(address, UINT64_C(0x00000000), UINT64_C(0x00001000));
  }

  static bool is_executable(std::uint64_t address, bool debug_mode) {
    // The Debug address manager is executable exactly while the hart is in
    // Debug Mode.  Request valid is not a permission bit: on DRET the frontend
    // can still carry a valid Debug-ROM address after Debug Mode has cleared.
    const bool debug_access = is_debug_address(address) && debug_mode;
    return debug_access ||
           contains(address, UINT64_C(0x00010000), UINT64_C(0x00010000)) ||
           contains(address, UINT64_C(0x80000000), UINT64_C(0x10000000));
  }

  SmallInstructionTlb state_{};
};

}  // namespace chisa::boom_system::components
