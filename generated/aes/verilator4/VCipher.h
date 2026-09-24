// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VCIPHER_H_
#define VERILATED_VCIPHER_H_  // guard

#include "verilated.h"
#include "verilated_threads.h"

class VCipher__Syms;
class VCipher___024root;

// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) VCipher VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    VCipher__Syms* const vlSymsp;

  public:

    // CONSTEXPR CAPABILITIES
    // Verilated with --trace?
    static constexpr bool traceCapable = false;

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&io_plaintext_3,7,0);
    VL_IN8(&io_roundKey_3,7,0);
    VL_IN8(&io_plaintext_9,7,0);
    VL_IN8(&io_roundKey_9,7,0);
    VL_IN8(&io_plaintext_8,7,0);
    VL_IN8(&io_roundKey_8,7,0);
    VL_IN8(&io_plaintext_14,7,0);
    VL_IN8(&io_roundKey_14,7,0);
    VL_IN8(&io_plaintext_13,7,0);
    VL_IN8(&io_roundKey_13,7,0);
    VL_IN8(&io_plaintext_12,7,0);
    VL_IN8(&io_roundKey_12,7,0);
    VL_IN8(&io_plaintext_10,7,0);
    VL_IN8(&io_roundKey_10,7,0);
    VL_IN8(&io_plaintext_11,7,0);
    VL_IN8(&io_roundKey_11,7,0);
    VL_IN8(&io_plaintext_15,7,0);
    VL_IN8(&io_roundKey_15,7,0);
    VL_IN8(&reset,0,0);
    VL_IN8(&io_start,0,0);
    VL_OUT8(&io_state_out_0,7,0);
    VL_OUT8(&io_state_out_1,7,0);
    VL_OUT8(&io_state_out_2,7,0);
    VL_OUT8(&io_state_out_3,7,0);
    VL_OUT8(&io_state_out_4,7,0);
    VL_OUT8(&io_state_out_5,7,0);
    VL_OUT8(&io_state_out_6,7,0);
    VL_OUT8(&io_state_out_7,7,0);
    VL_OUT8(&io_state_out_8,7,0);
    VL_OUT8(&io_state_out_9,7,0);
    VL_OUT8(&io_state_out_10,7,0);
    VL_OUT8(&io_state_out_11,7,0);
    VL_OUT8(&io_state_out_12,7,0);
    VL_OUT8(&io_state_out_13,7,0);
    VL_OUT8(&io_state_out_14,7,0);
    VL_OUT8(&io_state_out_15,7,0);
    VL_OUT8(&io_state_out_valid,0,0);
    VL_IN8(&io_plaintext_1,7,0);
    VL_IN8(&io_roundKey_1,7,0);
    VL_IN8(&io_plaintext_0,7,0);
    VL_IN8(&io_roundKey_0,7,0);
    VL_IN8(&io_plaintext_4,7,0);
    VL_IN8(&io_roundKey_4,7,0);
    VL_IN8(&io_plaintext_2,7,0);
    VL_IN8(&io_roundKey_2,7,0);
    VL_IN8(&io_plaintext_6,7,0);
    VL_IN8(&io_roundKey_6,7,0);
    VL_IN8(&io_plaintext_5,7,0);
    VL_IN8(&io_roundKey_5,7,0);
    VL_IN8(&io_plaintext_7,7,0);
    VL_IN8(&io_roundKey_7,7,0);
    VL_IN8(&clock,0,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    VCipher___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit VCipher(VerilatedContext* contextp, const char* name = "TOP");
    explicit VCipher(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~VCipher();
  private:
    VL_UNCOPYABLE(VCipher);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0) { contextp()->trace(tfp, levels, options); }
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
  private:
    // Internal functions - trace registration
    void traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options);
};

#endif  // guard
