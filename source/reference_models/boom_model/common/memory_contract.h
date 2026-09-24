#pragma once
// Core-independent LSU/TLB boundary facts.
#include <cstdint>

struct DtlbLookupCandidate {
    bool     valid = false;
    uint64_t vaddr = 0;
    uint8_t  size = 0;
    uint8_t  cmd = 0;
    bool     passthrough = false;
    bool     is_hella = false;
};

struct LsuScheduleInputs {
    bool dmem_release_valid = false;
    bool hella_incoming = false;
    bool hella_wakeup = false;
    bool dtlb_miss_ready_registered = true;
    bool dmem_ordered = true;
};
