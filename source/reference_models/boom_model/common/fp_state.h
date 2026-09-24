#pragma once
// Existing FP value carriers and branch-queue storage shared by both cores.
#include "micro_op.h"

#if defined(BOOM_GUIDER_FP)
struct FpInflight {
    bool     v;
    MicroOp  uop;
    uint8_t  left;        // cycles until response
    uint8_t  exec_cycles; // deferred variable-latency body (FDivSqrt only)
    uint64_t ieee;        // result (FLEN view, singles NaN-boxed)
    uint8_t  flags;       // fflags of the op
    // Exact HardFloat request retained across the wrapper input buffer.
    // rec_hi bit 0/1 is rec_a[64]/rec_b[64].
    uint64_t rec_a, rec_b;
    uint8_t  rec_hi, rm;
    bool     sqrt;
    void clear() {
        v=false; uop.clear(); left=0; exec_cycles=0; ieee=0; flags=0;
        rec_a=rec_b=0; rec_hi=rm=0; sqrt=false;
    }
};

struct FpQEntry {
    bool     v;
    MicroOp  uop;
    uint64_t data;        // ieee payload (f2i result / store data / i2f result)
    uint8_t  flags;
    void clear() { v=false; uop.clear(); data=0; flags=0; }
};

template <int Entries, bool FflagsRobFromUop>
struct FpBranchQueueMirror {
    FpQEntry ram[Entries];
    MicroOp  uops[Entries];
    uint8_t  fflags_rob_idx[Entries];
    bool     valids[Entries];
    uint8_t  enq_ptr;
    uint8_t  deq_ptr;
    bool     maybe_full;

    void clear() {
        for (int i = 0; i < Entries; ++i) {
            ram[i].clear();
            uops[i].clear();
            fflags_rob_idx[i] = 0;
            valids[i] = false;
        }
        enq_ptr = 0;
        deq_ptr = 0;
        maybe_full = false;
    }

    bool empty() const { return enq_ptr == deq_ptr && !maybe_full; }
    bool full() const { return enq_ptr == deq_ptr && maybe_full; }
    bool enq_ready() const { return !full(); }

    bool deq_valid(bool enq_valid, boomcfg::br_mask_t mispredict_mask,
                   bool flush) const {
        if (empty()) return enq_valid;
        return valids[deq_ptr] &&
               !(uops[deq_ptr].br_mask & mispredict_mask) && !flush;
    }

    FpQEntry deq_bits(bool enq_valid, const FpQEntry& enq,
                      boomcfg::br_mask_t resolve_mask) const {
        FpQEntry out = empty() ? enq : ram[deq_ptr];
        if (!empty()) out.uop = uops[deq_ptr];
        // With flow=true the invalid empty-queue payload is still io.enq.bits.
        // Keep that payload even when enq_valid is false.
        (void)enq_valid;
        out.uop.br_mask &= static_cast<boomcfg::br_mask_t>(~resolve_mask);
        return out;
    }

    void step(bool enq_valid, const FpQEntry& enq, bool deq_ready,
              boomcfg::br_mask_t resolve_mask, boomcfg::br_mask_t mispredict_mask, bool flush) {
        const bool was_empty = empty();
        bool do_enq = enq_valid && enq_ready();
        bool do_deq = (deq_ready || !valids[deq_ptr]) && !was_empty;

        // flow=true bypass: an empty queue consumed this cycle performs no
        // RAM write and advances neither pointer.
        if (was_empty) {
            do_deq = false;
            if (deq_ready) do_enq = false;
        }

        // Default per-entry updates precede the enqueue/dequeue overrides in
        // the Chisel source.  A killed entry still gets its resolved bit
        // cleared because the `when(valids(i))` guard reads the old register.
        for (int i = 0; i < Entries; ++i) {
            if (!valids[i]) continue;
            if ((uops[i].br_mask & mispredict_mask) || flush)
                valids[i] = false;
            uops[i].br_mask &=
                static_cast<boomcfg::br_mask_t>(~resolve_mask);
        }

        if (do_enq) {
            ram[enq_ptr] = enq;
            uops[enq_ptr] = enq.uop;
            uops[enq_ptr].br_mask &=
                static_cast<boomcfg::br_mask_t>(~resolve_mask);
            fflags_rob_idx[enq_ptr] =
                FflagsRobFromUop ? static_cast<uint8_t>(enq.uop.rob_idx & (boomcfg::ROB_FLAT - 1))
                                 : 0;
            valids[enq_ptr] = true;
        }
        if (do_deq) valids[deq_ptr] = false;

        if (do_enq) enq_ptr = static_cast<uint8_t>((enq_ptr + 1) % Entries);
        if (do_deq) deq_ptr = static_cast<uint8_t>((deq_ptr + 1) % Entries);
        if (do_enq != do_deq) maybe_full = do_enq;
    }

    uint64_t packed_br_masks_bank(unsigned bank) const {
        constexpr unsigned kMaskBits = boomcfg::MAX_BR_COUNT;
        constexpr unsigned kPerWord = 64 / kMaskBits;
        const unsigned first = bank * kPerWord;
        const unsigned limit = first + kPerWord < Entries
                                   ? first + kPerWord
                                   : Entries;
        uint64_t packed = 0;
        for (unsigned i = first; i < limit; ++i)
            packed = (packed << kMaskBits) |
                     (static_cast<uint64_t>(uops[i].br_mask) &
                      ((UINT64_C(1) << kMaskBits) - 1));
        return packed;
    }

    uint64_t packed_br_masks() const { return packed_br_masks_bank(0); }

    uint64_t packed_valids() const {
        uint64_t packed = 0;
        for (int i = 0; i < Entries; ++i)
            packed = (packed << 1) | (valids[i] ? 1u : 0u);
        return packed;
    }

    uint8_t ram_fflags_rob_idx_at_deq() const {
        return fflags_rob_idx[deq_ptr] & (boomcfg::ROB_FLAT - 1);
    }
};
#endif  // BOOM_GUIDER_FP
