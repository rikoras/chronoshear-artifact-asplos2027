#pragma once
#include <array>
#include <cstdint>
#include "backend_contract.h"
#include "../../boom-system/components/small_icache.h"
#include "../../boom-system/components/small_machine_itlb.h"
#include "../../boom-system/components/small_tlb.h"

namespace chisa::boom_system {
struct FrontendInputs {
  bool reset = false;
  bool run = false;
  bool debug_mode = false;
  bool itlb_vm_enabled = false;
  std::uint8_t itlb_privilege = 3;
  bool itlb_dynamic_execute_permission = false;
  bool itlb_ptw_request_ready = false;
  components::SmallTlbRefill itlb_refill{};
  components::SmallICacheMemoryInputs icache_memory{};
  bool fetch_ready = false;
  BackendFrontendControl backend_control{};
};
struct HeldFetch {
  bool enq_ready = false;
  bool deq_valid = false;
  bool uop_valid = false;
  const MicroOp* uop = nullptr;
  std::array<const MicroOp*,boomcfg::MAX_CORE_WIDTH> group{};
  std::uint8_t group_valid = 0;
};
/** What the calling thread reads from the committed frontend for the next
  * edge, gathered once by whoever committed it (the frontend worker or the
  * calling thread itself), so the edge never touches frontend state: the
  * dequeue row already unpacked and decoded, the two FTQ get-pc ports, the
  * S1 fields behind the ITLB request and the registered I-cache acquire
  * offer.  Two buffers alternate: the producer fills the one the calling
  * thread is not reading (SystemGuider::frontend_handoff_). */
struct FrontendHandoff {
  alignas(64) std::array<MicroOp, boomcfg::MAX_CORE_WIDTH> uops{};
  std::uint8_t uop_valids = 0;   // per dequeue slot, before the reset gate
  bool deq_valid = false;
  struct FtqPort {
    std::uint64_t pc = 0, next_pc = 0;
    std::uint8_t cfi_idx = 0, start_bank = 0;
    bool next_valid = false, cfi_valid = false;
  };
  std::array<FtqPort, 2> ftq{};
  struct S1 {
    std::uint64_t vpc = 0;
    bool valid = false, is_replay = false, is_sfence = false;
  };
  S1 s1{};
  components::SmallTlbSfence sfence{};
  components::SmallICache::AcquireOffer icache_acquire{};
  // The image position the committing thread copied the frontend's record
  // runs into right after its commit (nullptr: not copied; the publisher
  // copies the whole record).
  char* image_runs_copied_to = nullptr;
};
}  // namespace chisa::boom_system
