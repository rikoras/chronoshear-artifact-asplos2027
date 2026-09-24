#pragma once
// Architectural CSR storage and performance-event interface shared by BOOM cores.
#include "boom_config.h"
#include <type_traits>
#include <cstdint>
#include <cstring>

struct GuiderCSR {
    struct PmpEntry {
        uint32_t addr;       // paddrBits(32) - PMP.lgAlign(2) = 30 bits
        uint8_t  cfg_a;      // OFF/TOR/NA4/NAPOT
        bool     cfg_l;
        bool     cfg_r;
        bool     cfg_w;
        bool     cfg_x;
    };

    uint64_t mstatus;   // reset MPP=3 + UXL=2 (observed 0x200001800); csrs sets FS.
    uint64_t mtvec;
    uint64_t mepc;
    uint64_t mcause;
    uint64_t mtval;
    uint64_t mscratch;
    uint64_t mie;
    uint64_t mip;
    uint64_t misa;
    // Supervisor/VM state.  These are ordinary hot architectural registers;
    // keeping them here lets the same CSR execution path own both behavior
    // and oracle export instead of treating an idle boot profile as proof of
    // zero.
    uint64_t medeleg;
    uint64_t mideleg;
    uint64_t sepc;
    uint64_t scause;
    uint64_t stval;
    uint64_t stvec;
    uint64_t sscratch;
    uint32_t mcounteren;
    uint32_t scounteren;
    std::conditional_t<(boomcfg::NUM_HPM>5),uint16_t,uint8_t> mcountinhibit;
    uint8_t  satp_mode;
    uint64_t satp_ppn;       // architectural field is 44b; this SoC uses low 20b
    bool     mip_seip;
    bool     mip_ssip;
    bool     mip_stip;
    PmpEntry pmp[8];
    uint64_t hpmevent[boomcfg::NUM_HPM];
    uint64_t hpmcounter[boomcfg::NUM_HPM];  // implemented width is 40b
    bool     hpm_inc_r[boomcfg::NUM_HPM];   // RegNext(perfEvents.evaluate(...))
    uint64_t custom_0;       // Boom chicken CSR 0x7c1, writable mask bit 3
    bool     cease;
    bool     single_stepped;
    // Debug-mode state is architectural CSR state, not a harness-side hint.
    // DCSR is kept in its specified bit layout so CSR reads/writes and the
    // entry cause/prv updates share one representation.
    uint64_t dcsr;
    uint64_t dpc;
    uint64_t dscratch;  // Debug ROM saves/restores s0 across abstract commands.
    uint8_t  prv;       // Current privilege (PRV.U/S/M = 0/1/3).
    bool     debug;
    uint64_t fcsr;      // fflags(4:0)+frm(7:5); reset 0
    bool     wfi;
    // The free-running counters change every cycle; on their own cache
    // line so the sampler's line-level change detection of the other CSRs
    // is not woken by them.
    alignas(64) uint64_t mcycle;
    uint64_t minstret;
    void clear() { memset(this, 0, sizeof(*this)); }
};

struct HpmEventInputs {
    uint64_t selector[boomcfg::NUM_HPM]{};
    bool exception = false;
    bool flush = false;
    bool ifu_acquire = false;
    bool lsu_acquire = false;
    bool lsu_release = false;
    bool ifu_tlb_miss = false;
    bool lsu_tlb_miss = false;
    bool ptw_l2_miss = false;
};
