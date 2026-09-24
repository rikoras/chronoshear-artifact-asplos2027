#pragma once
// rocket_model: hand-written, two-phase model of the DefaultConfig Rocket core.
//
// One cycle is evaluate() followed by commit().  evaluate() reads registers
// and the module inputs only and writes every combinational decision of the
// cycle into CoreWires, including the module outputs.  commit() reads
// CoreWires and applies the register updates.  Nothing is copied to emulate
// "read the old value": evaluate() never writes architectural state.
//
// State fields retain the established observation ABI. Instruction execution
// uses semantic decoding and native arithmetic; pipeline timing is explicit.
#include <cstdint>

#include "generated/image.h"
#include "seam.h"

namespace chisa::rocket_model {

// ---------------------------------------------------------------- state ----

struct Stage {
  bool        valid = false;
  uint64_t    pc = 0;
  uint32_t    inst = 0;
  uint32_t    raw_inst = 0;
  bool        rvc = false;
  uint8_t     hw_rs1_addr = 0;   // expanded-instruction rs1/rs2 (hazard checks)
  uint8_t     hw_rs2_addr = 0;
  uint8_t     raddr1 = 0;        // RVC expander read addresses (RF ports)
  uint8_t     raddr2 = 0;
  DecodedCtrl ctrl{};
  uint64_t    cause = 0;
  bool        xcpt = false;
  bool        xcpt_interrupt = false;
  bool        replay = false;
  bool        flush_pipe = false;
  bool        load_use = false;
  uint8_t     mem_size = 0;
  uint64_t    wdata = 0;
  uint64_t    rs2 = 0;
  bool        sfence = false;
  bool        slow_bypass = false;
  bool        store = false;
  bool        load = false;
  bool        br_taken = false;
  BtbResp     btb{};
  bool        wphit_0 = false;
  bool        rs_bypass[2] = {false, false};
  uint64_t    rs_lsb[2] = {0, 0};
  uint64_t    rs_msb[2] = {0, 0};
};

struct Csr {
  uint64_t mstatus_prv, mstatus_mpp, mstatus_mprv, mstatus_sum, mstatus_mxr,
           mstatus_tvm, mstatus_tw, mstatus_tsr, mstatus_sie, mstatus_spie,
           mstatus_spp, mstatus_mpie, mstatus_mie, mstatus_fs;
  uint64_t fflags, frm;
  uint64_t dcsr_ebreakm, dcsr_ebreaks, dcsr_ebreaku, dcsr_prv, dcsr_cause,
           dcsr_step, debug, dpc, dscratch, singleStepped;
  uint64_t bp_0_control_dmode, bp_0_control_action, bp_0_control_tmatch,
           bp_0_control_m, bp_0_control_s, bp_0_control_u, bp_0_control_x,
           bp_0_control_w, bp_0_control_r, bp_0_address;
  struct { uint64_t cfg_l, cfg_a, cfg_x, cfg_w, cfg_r, addr; } pmp[8];
  uint64_t mie, mideleg, medeleg, mip_ssip, mip_stip, mip_seip;
  uint64_t mepc, mcause, mtval, mscratch, mtvec, mcounteren, scounteren;
  uint64_t sepc, scause, stval, sscratch, stvec;
  uint64_t satp_mode, satp_asid, satp_ppn;
  uint64_t wfi, status_cease_r, mcountinhibit;
  uint64_t value_lo, value_hi, value_hi_1, mcycle_small;
  uint64_t misa, custom_0, custom_1, custom_2, custom_3;
  uint64_t status_dprv, rnmie;
};

struct IBuf {
  uint64_t nBufValid = 0;
  uint64_t buf_pc = 0;
  uint64_t buf_data = 0;
  uint64_t buf_xcpt_pf_inst = 0;
  uint64_t buf_xcpt_ae_inst = 0;
  uint64_t buf_replay = 0;
  BtbResp  btb{};
};

// MulDiv FSM state encoding (Multiplier.scala Enum(8)).
inline constexpr uint64_t DIV_S_READY = 0, DIV_S_NEG_INPUTS = 1, DIV_S_MUL = 2,
    DIV_S_DIV = 3, DIV_S_DUMMY = 4, DIV_S_NEG_OUTPUT = 5, DIV_S_DONE_MUL = 6,
    DIV_S_DONE_DIV = 7;

struct Div {
  uint64_t state = DIV_S_READY;
  uint64_t req_dw = 0;
  uint64_t req_tag = 0;
  uint64_t remainder = 0;   // remainder[63:0]
  uint64_t rem_hi = 0;      // remainder[127:64]
  uint8_t  rem_top = 0;     // remainder[129:128]
  uint64_t divisor_lo = 0;  // divisor[63:0]
  uint8_t  divisor_hi = 0;  // divisor[64]
  uint8_t  req_fn = 0;
  uint64_t count = 0;
  bool     cmdMul = false;
  bool     isHi = false;
  bool     neg_out = false;
  bool     resHi = false;
};

struct FpuCtrl {
  uint8_t ldst, wen, ren1, ren2, ren3, swap12, swap23, typeTagIn, typeTagOut,
          fromint, toint, fastpipe, fma, div, sqrt, wflags;
};

// ---------------------------------------------------------------- wires ----

struct BreakpointView {
  bool instruction = false, load = false, store = false;
  bool debug_instruction = false, debug_load = false, debug_store = false;
};

struct CoreWires {
  // cycle-start views
  uint64_t id_pc = 0;             // IBuf-visible PC (buffered halfword or response PC)
  bool     dmem_resp_valid = false;   // resp.valid && has_data
  // redirects
  uint64_t mem_npc = 0;
  bool     ex_pc_valid = false;
  bool     mem_pc_valid = false;
  bool     id_visible = false;    // ibuf.io.inst(0).valid
  bool     mem_wrong_npc = false;
  bool     take_pc_mem = false;
  bool     take_pc_wb = false;
  bool     take_pc_mem_wb = false;
  // WB view
  bool     wb_xcpt = false;
  uint64_t wb_cause = 0;
  bool     wb_system = false, wb_ecall = false, wb_ebreak = false, wb_sret = false,
           wb_mret = false, wb_dret = false, wb_return = false, wb_csr_eret = false,
           wb_csr_exception = false, wb_wfi = false, wb_cease = false;
  bool     replay_wb = false;
  bool     wb_valid_retire = false;
  uint64_t wb_evec = 0;
  // long-latency bypass
  bool     ll_wen_div_bypass = false, ll_wen_dmem_bypass = false;
  uint32_t ll_waddr_div_bypass = 0, ll_waddr_dmem_bypass = 0;
  // EX operands
  uint64_t ex_rs0 = 0, ex_rs1 = 0;
  // MEM -> WB
  bool     mem_xcpt = false;
  uint64_t mem_cause = 0;
  bool     mem_npc_misaligned = false;
  bool     mem_breakpoint = false, mem_debug_breakpoint = false;
  bool     dcache_kill_mem = false;
  bool     killm_common = false;
  bool     fpu_nack_mem = false, fpu_kill_mem = false;
  bool     ctrl_killm = false;
  uint64_t new_wb_wdata = 0;
  bool     new_wb_wphit = false;
  bool     new_wb_valid = false, new_wb_xcpt = false, new_wb_flush_pipe = false,
           new_wb_replay = false;
  // EX -> MEM
  bool     mem_flush_stall = false;
  bool     wb_dcache_miss = false;
  bool     replay_ex = false;
  bool     ctrl_killx = false;
  bool     new_mem_debug_fence = false;
  uint64_t new_mem_wdata = 0;
  bool     new_mem_br_taken = false, new_mem_store = false, new_mem_load = false,
           new_mem_slow_bypass = false;
  bool     new_mem_rs2_valid = false;
  uint64_t new_mem_rs2 = 0;
  bool     new_mem_valid = false, new_mem_replay = false, new_mem_xcpt = false,
           new_mem_xcpt_interrupt = false;
  uint64_t ex_adder = 0;
  // interrupts
  bool     csr_interrupt = false;
  uint64_t csr_interrupt_cause = 0;
  // ID
  bool     ctrl_killd = false;
  bool     ctrl_stalld = false;
  bool     ibuf_inst_valid = false;
  uint32_t id_inst = 0;
  uint32_t id_raw_inst = 0;
  uint16_t id_half = 0;
  bool     id_rvc = false;
  bool     id_replay = false;
  bool     id_xcpt0_pf = false, id_xcpt0_ae = false, id_xcpt1_pf = false, id_xcpt1_ae = false;
  BtbResp  id_btb{};
  DecodedCtrl id_ctrl{};      // decoded control before the ID rewrites
  FpuCtrl  id_fpu_dec{};
  uint64_t id_cause = 2;
  bool     id_illegal = false;
  bool     id_xcpt = false;
  BreakpointView id_bp{};
  bool     capture_killed_id = false;
  // the EX slot that commit installs (when !ctrl_killd)
  DecodedCtrl new_ex_ctrl{};
  uint8_t  new_ex_mem_size = 0;
  bool     new_ex_flush_pipe = false;
  bool     new_ex_sfence = false;
  uint8_t  new_ex_hw_rs1 = 0, new_ex_hw_rs2 = 0, new_ex_raddr1 = 0, new_ex_raddr2 = 0;
  bool     new_ex_rs_bypass[2] = {false, false};
  uint64_t new_ex_rs_lsb[2] = {0, 0};
  uint64_t new_ex_rs_msb[2] = {0, 0};
  bool     new_ex_load_use = false;
  bool     new_ex_valid = false, new_ex_replay = false, new_ex_xcpt_interrupt = false;
  // CSR
  bool     csr_single_step = false, csr_stall = false;
  uint64_t next_dprv = 0;
  bool     pending_interrupts = false;
  bool     pause_unpause = false;
  bool     disable_icache_clock_gate = false;
  bool     wb_csr_write = false;
  uint64_t wb_csr_wdata = 0;
  bool     fflags_accumulate = false;
  // divider
  bool     div_kill = false, div_resp_fire = false, div_req_fire = false;
  uint64_t div_lhs = 0, div_rhs = 0;
  bool     div_lhs_sign = false, div_rhs_sign = false;
  bool     div_cmd_hi = false, div_cmd_mul = false;
  uint8_t  div_req_dw = 0, div_req_fn = 0;
  uint32_t div_req_tag = 0;
  // register file write (write-through into this cycle's ID read)
  bool     rf_wen = false;
  uint32_t rf_waddr = 0;
  uint64_t rf_wdata = 0;
  // scoreboards
  bool     sb_dmem_clear = false, sb_div_clear = false, sb_set = false;
  uint32_t sb_dmem_addr = 0, sb_set_addr = 0;
  bool     fpsb_set = false, fpsb_dmem_clear = false, fpsb_clear = false;
  uint32_t fpsb_set_addr = 0, fpsb_dmem_addr = 0, fpsb_clear_addr = 0;
  // IBuf
  bool     ibuf_kill = false, ibuf_ready = false;
  bool     ibuf_consume = false;   // io.inst(0).ready and something to consume
  uint64_t ibuf_next_nbufvalid = 0;
  bool     ibuf_reload = false;
  uint64_t ibuf_reload_data = 0, ibuf_reload_pc = 0;
  bool     imem_ready = false;
  // misc next-state
  bool     next_id_reg_fence = false;
  bool     next_id_reg_pause = false;
  bool     next_blocked = false;
  bool     next_might_request = false;
};

// ----------------------------------------------------------------- core ----

struct CoreRetirement {
  bool retired = false;
  bool trapped = false;
  uint64_t pc = 0;
  uint32_t instruction = 0;
  uint8_t instruction_bytes = 0;
  uint8_t privilege = 0;
  bool debug_mode = false;
  uint64_t cause = 0;
  uint32_t expanded_instruction = 0;
  bool x_write = false, x_value_valid = false;
  uint8_t xrd = 0;
  uint64_t xvalue = 0;
  bool fp_write = false;
  uint8_t frd = 0;
  bool store = false;
  uint8_t store_bytes = 0;
  uint64_t store_address = 0, store_value = 0;
};

struct CoreIntegerWriteback {
  bool valid = false;
  uint8_t rd = 0;
  uint64_t value = 0;
};

class Core {
 public:
  static constexpr uint64_t kMisaFullSystem = 0x800000000094112dULL;

  // Select before execution. Architectural mode drops inactive payload
  // obligations; it cannot reconstruct those residuals when switched back.
  void set_architectural_mode(bool enabled) { architectural_mode_ = enabled; pre_derived_valid_ = false; }
  bool architectural_mode() const { return architectural_mode_; }

  void bind(Image::Core& image) {
    I_ = &image;
    csr_export_dirty_ = pmp_export_dirty_ = true;
  }
  void reset(uint32_t reset_vector);

  void evaluate(const RocketFullSystemInputs& in, CoreWires& w,
                RocketFullSystemOutputs& out) const;
  void commit(const RocketFullSystemInputs& in, const CoreWires& w);

  // Observers used by the runtime and the replay harness.
  uint64_t rf(unsigned i) const { return i == 0 ? 0 : rf_[i & 31]; }
  const CoreRetirement& retirement() const { return retirement_; }
  const CoreIntegerWriteback& late_integer_write() const { return late_integer_write_; }
  uint64_t committed_pc() const { return committed_pc_; }
  uint64_t wb_pc() const { return wb_.pc & 0xffffffffffULL; }
  const Stage& ex() const { return ex_; }
  const Stage& mem() const { return mem_; }
  const Stage& wb() const { return wb_; }
  const Csr& csr() const { return csr_; }
  const Div& div() const { return div_; }
  const IBuf& ibuf() const { return ibuf_; }
  uint32_t sboard() const { return sboard_; }
  uint32_t fp_sboard() const { return fp_sboard_; }
  bool blocked() const { return blocked_; }
  bool id_reg_fence() const { return id_reg_fence_; }
  bool id_reg_pause() const { return id_reg_pause_; }

  // Combinational CSR helpers (pure functions of the CSR image).
  uint64_t csr_read(uint32_t addr, const RocketFullSystemInputs& in) const;
  bool csr_read_illegal(uint32_t addr) const;
  bool csr_write_illegal(uint32_t addr) const;
  bool csr_system_illegal(uint32_t encoded_system) const;
  uint64_t trap_vector(uint64_t cause) const;

 private:
  Image::Core* I_ = nullptr;
  bool architectural_mode_ = false;
  CoreRetirement retirement_;
  CoreIntegerWriteback late_integer_write_;
  uint64_t committed_pc_ = 0;
  uint64_t wb_store_data_ = 0;  // observer-only MEM->WB copy of the actual store bus

  Stage ex_, mem_, wb_;
  Csr csr_{};
  IBuf ibuf_;
  Div div_;
  uint64_t rf_[32] = {};

  bool     blocked_ = false;
  bool     id_reg_pause_ = false;
  bool     id_reg_fence_ = false;
  bool     clock_en_reg_ = false;
  bool     imem_might_request_reg_ = false;
  uint32_t sboard_ = 0;
  uint32_t fp_sboard_ = 0;
  bool     div_io_kill_reg_ = false;

  struct DecodeEntry {
    uint32_t inst = 0;
    bool valid = false;
    DecodedCtrl ctrl{};
  };
  static constexpr unsigned kDecodeCacheSize = 256;
  mutable DecodeEntry decode_cache_[kDecodeCacheSize];
  mutable bool rvc_cache_valid_ = false;
  mutable uint16_t rvc_cache_half_ = 0;
  mutable uint32_t rvc_cache_inst_ = 0;

  struct PreDerived {
    uint64_t mem_target = 0, mem_npc = 0;
    uint64_t ex_rs[2] = {};
    uint64_t ex_wdata = 0, ex_adder = 0, ex_store_data = 0;
    bool ex_cold_rs[2] = {};
    bool ex_cold_alu = false, ex_br_taken = false, mem_npc_misaligned = false;
  };
  mutable PreDerived pre_derived_;
  mutable bool pre_derived_valid_ = false;
  mutable RocketSystemStatusOutputs status_cache_;
  mutable RocketSystemPmpOutput pmp_cache_[8];
  mutable bool status_cache_valid_ = false, pmp_cache_valid_ = false;
  bool csr_export_dirty_ = true, pmp_export_dirty_ = true;

  const DecodedCtrl& decode_cached(uint32_t inst) const;
  uint32_t expand_cached(uint16_t half) const;
  const PreDerived& pre_derived() const;
  void invalidate_csr_views() { status_cache_valid_ = false; csr_export_dirty_ = true; }
  void invalidate_pmp_views() { pmp_cache_valid_ = false; pmp_export_dirty_ = true; }
  bool csr_exists(uint32_t addr) const;
  uint64_t rmw_wdata(uint32_t address, uint8_t command, uint64_t wdata,
                     const RocketFullSystemInputs& in) const;
  bool stall_check(const CoreWires& w, const DecodedCtrl& id_ctrl,
                   const RocketFullSystemInputs& in) const;
  BreakpointView breakpoint_view(uint64_t pc, uint64_t ea) const;
  void update_csr(const Stage& s, uint64_t wdata);
  void handle_trap(uint64_t pc, uint32_t inst, uint8_t csr_cmd, uint64_t cause,
                   uint64_t tval_source);
  void div_step();
  void apply_reset_priority();
  void export_image();
};

// Pure helpers shared with other units.
FpuCtrl fpu_decode_from_inputs(const RocketSystemFpuInputs& input);
uint64_t decode_imm(uint32_t inst, uint8_t sel_imm);
uint64_t encode_virtual_address(uint64_t a0, uint64_t ea);

}  // namespace chisa::rocket_model
