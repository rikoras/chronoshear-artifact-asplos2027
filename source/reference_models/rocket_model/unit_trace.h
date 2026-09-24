// Per-cycle record of every unit's inputs as sampled from the RTL
// environment by the co-simulation harness.  Lets the models be replayed,
// timed and differentially checked without Verilator.
#pragma once
#include <cstdint>

#include "core.h"
#include "dcache.h"
#include "fpu.h"
#include "frontend.h"
#include "ptw.h"
#include "tlb.h"

namespace chisa::rocket_model {

struct UnitTraceRecord {
  uint64_t cycle;
  uint8_t reset;
  uint8_t pad[7];
  RocketFullSystemInputs core_in;
  FrontendIn fe;
  DcacheIn dc;
  FpuIn fpu;
  TlbIn itlb;
  TlbIn dtlb;
  PtwIn ptw;
  PmpSet pmp;   // the pointer fields above are re-pointed at this copy on load
};

}  // namespace chisa::rocket_model
