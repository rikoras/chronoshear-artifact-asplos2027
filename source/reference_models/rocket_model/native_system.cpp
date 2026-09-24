#include "native_system.h"

#include <cstring>
#include <stdexcept>
#include <string>
#include <tuple>

namespace chisa::rocket_model {
namespace {

bool btb_equal(const RocketSystemBtbResponse& a, const RocketSystemBtbResponse& b) {
  return std::tie(a.cfi_type,a.taken,a.mask,a.bridx,a.target,a.entry,a.bht_history,a.bht_value) ==
         std::tie(b.cfi_type,b.taken,b.mask,b.bridx,b.target,b.entry,b.bht_history,b.bht_value);
}
bool core_feedback_equal(const RocketFullSystemInputs& a, const RocketFullSystemInputs& b, bool fp_candidate) {
#define EQ(field) if (a.field != b.field) return false
  EQ(reset); EQ(interrupt_debug); EQ(interrupt_mtip); EQ(interrupt_msip); EQ(interrupt_meip); EQ(interrupt_seip);
  // The native core consumes the response, not Frontend's NPC/perf/debug ports.
  EQ(imem.resp_valid);
  if (a.imem.resp_valid) {
    EQ(imem.resp_pc); EQ(imem.resp_data); EQ(imem.resp_xcpt_pf_inst); EQ(imem.resp_xcpt_ae_inst); EQ(imem.resp_replay);
    if (!btb_equal(a.imem.resp_btb, b.imem.resp_btb)) return false;
  }
  EQ(dmem.req_ready); EQ(dmem.s2_nack); EQ(dmem.resp.valid);
  EQ(dmem.replay_next); EQ(dmem.s2_xcpt_ma_ld); EQ(dmem.s2_xcpt_ma_st); EQ(dmem.s2_xcpt_pf_ld);
  EQ(dmem.s2_xcpt_pf_st); EQ(dmem.s2_xcpt_ae_ld); EQ(dmem.s2_xcpt_ae_st); EQ(dmem.ordered); EQ(dmem.clock_enabled);
  EQ(dmem.perf_release); EQ(dmem.perf_grant);
  if (a.dmem.resp.valid) {
    EQ(dmem.resp.tag); EQ(dmem.resp.size); EQ(dmem.resp.replay); EQ(dmem.resp.has_data);
    if (a.dmem.resp.has_data) { EQ(dmem.resp.data); EQ(dmem.resp.data_word_bypass); }
  }
  // ID decode is consumed for FP candidates even when FPU valid is false.
  EQ(fpu.fcsr_flags_valid); if (a.fpu.fcsr_flags_valid) { EQ(fpu.fcsr_flags); }
  EQ(fpu.store_data); EQ(fpu.toint_data); EQ(fpu.fcsr_ready); EQ(fpu.nack_mem);
  EQ(fpu.sboard_set); EQ(fpu.sboard_clear); if (a.fpu.sboard_clear) { EQ(fpu.sboard_clear_addr); }
  if (fp_candidate) {
    EQ(fpu.illegal_rm);
    EQ(fpu.dec_ldst); EQ(fpu.dec_wen); EQ(fpu.dec_ren1); EQ(fpu.dec_ren2); EQ(fpu.dec_ren3);
    EQ(fpu.dec_swap12); EQ(fpu.dec_swap23); EQ(fpu.dec_type_tag_in); EQ(fpu.dec_type_tag_out);
    EQ(fpu.dec_fromint); EQ(fpu.dec_toint); EQ(fpu.dec_fastpipe); EQ(fpu.dec_fma); EQ(fpu.dec_div); EQ(fpu.dec_sqrt); EQ(fpu.dec_wflags);
  }
#undef EQ
  return true;
}
bool pte_equal(const PteBits& a, const PteBits& b) {
  return std::tie(a.ppn,a.d,a.a,a.g,a.u,a.x,a.w,a.r,a.v) == std::tie(b.ppn,b.d,b.a,b.g,b.u,b.x,b.w,b.r,b.v);
}
bool ptw_feedback_equal(const PtwWires& a, const PtwWires& b) {
  if (a.req_ready[0] != b.req_ready[0] || a.req_ready[1] != b.req_ready[1] ||
      a.resp_valid[0] != b.resp_valid[0] || a.resp_valid[1] != b.resp_valid[1] ||
      a.mem_req_valid != b.mem_req_valid || a.mem_s1_kill != b.mem_s1_kill) return false;
  if (a.mem_req_valid && a.mem_req_addr != b.mem_req_addr) return false;
  return !(a.resp_valid[0] || a.resp_valid[1]) ||
      (a.resp_ae == b.resp_ae && a.resp_level == b.resp_level && a.resp_homogeneous == b.resp_homogeneous && pte_equal(a.resp_pte,b.resp_pte));
}
bool fabric_feedback_equal(const uncore::UncoreOut& a, const uncore::UncoreOut& b) {
#define EQ(field) if (a.field != b.field) return false
  EQ(dc_a_ready); EQ(dc_c_ready); EQ(dc_e_ready); EQ(ic_a_ready); EQ(dc_b_valid); EQ(dc_d_valid); EQ(ic_d_valid);
  if (a.dc_b_valid) { EQ(dc_b.opcode); EQ(dc_b.param); EQ(dc_b.size); EQ(dc_b.source); EQ(dc_b.address); EQ(dc_b.mask); EQ(dc_b.data); EQ(dc_b.corrupt); }
  if (a.dc_d_valid) { EQ(dc_d.opcode); EQ(dc_d.param); EQ(dc_d.size); EQ(dc_d.source); EQ(dc_d.sink); EQ(dc_d.denied); EQ(dc_d.data); EQ(dc_d.corrupt); }
  if (a.ic_d_valid) { EQ(ic_d.opcode); EQ(ic_d.param); EQ(ic_d.size); EQ(ic_d.source); EQ(ic_d.sink); EQ(ic_d.denied); EQ(ic_d.data); EQ(ic_d.corrupt); }
#undef EQ
  return true;
}
PtwToTlb tlb_response(const PtwWires& w, unsigned requester) {
  return PtwToTlb{w.req_ready[requester], w.resp_valid[requester], w.resp_ae,
                 w.resp_pte, w.resp_level, false, w.resp_homogeneous};
}
}

NativeSystem::NativeSystem(uint32_t reset_vector, unsigned feedback_limit, NativeExecutionMode mode)
    : reset_vector_(reset_vector), feedback_limit_(feedback_limit), mode_(mode) {
  if (feedback_limit_ == 0) throw std::invalid_argument("native feedback limit must be positive");
  const bool architectural = mode_ == NativeExecutionMode::Architectural;
  core_.bind(image_.core);
  core_.set_architectural_mode(architectural);
  fpu_.set_architectural_mode(architectural);
  frontend_.set_architectural_mode(architectural);
  dcache_.set_architectural_mode(architectural);
  // Oracle mode starts with the scalar simulator's cold-zero state. Actual
  // reset values arrive on reset edges, not before cycle zero is published.
  if (architectural) core_.reset(reset_vector_);
  frontend_.icache.lfsr_ = 0;
  frontend_.s2_replay_reg_ = false;
  dcache_.lfsr_ = 0; dcache_.flushCounter_ = 0;
  fpu_.divS_.inReady = fpu_.divD_.inReady = false;
  fpu_.divSqrt_killed_ = false;
  core_input_.reset_vector = reset_vector_;
}
void NativeSystem::attach_memory(uint8_t* memory, uint64_t bytes) { uncore_.attach_memory(memory, bytes); }

void NativeSystem::capture_pmp() {
  pmp_.any_enabled = false;
  for (unsigned i = 0; i < 8; ++i) {
    const auto& p = core_output_.pmp[i];
    pmp_.e[i] = PmpEntry{p.addr,p.mask,p.cfg_l,p.cfg_r,p.cfg_w,p.cfg_x,p.cfg_a};
    pmp_.any_enabled |= p.cfg_a != 0;
  }
}
void NativeSystem::evaluate_fpu(bool reset) {
  const auto& f = core_output_.fpu;
  fpu_input_ = FpuIn{f.inst,f.fromint_data,f.fcsr_rm,f.dmem_resp_valid,
      f.dmem_resp_type,f.dmem_resp_tag,f.dmem_resp_data,f.valid,f.killx,f.killm,reset};
  fpu_.evaluate_inputs(fpu_input_, fpu_wires_);
}
void NativeSystem::evaluate_memory(bool reset, const PtwWires& p, const uncore::UncoreOut& fabric) {
  const auto& c = core_output_;
  const auto& f = c.imem;
  frontend_input_ = FrontendIn{};
  auto& fi = frontend_input_;
  fi.exact_seam = publishes_oracles();
  fi.reset = reset; fi.reset_vector = reset_vector_; fi.might_request = f.might_request;
  fi.req_valid = f.req_valid; fi.req_pc = f.req_pc; fi.req_speculative = f.req_speculative;
  fi.sfence_valid = f.sfence_valid; fi.sfence_rs1 = f.sfence_rs1; fi.sfence_rs2 = f.sfence_rs2; fi.sfence_addr = f.sfence_addr;
  fi.resp_ready = f.resp_ready; fi.flush_icache = f.flush_icache;
  fi.btb_update = BtbUpdate{f.btb_update_valid,f.btb_prediction.entry,f.btb_pc,f.btb_branch_pc,f.btb_is_valid,f.btb_cfi_type};
  fi.bht_update = BhtUpdate{f.bht_update_valid,f.bht_prediction_history,f.bht_pc,f.bht_branch,f.bht_taken,f.bht_mispredict};
  fi.chicken = static_cast<uint32_t>(c.custom_csr_value[0]);
  fi.prv = c.status.prv; fi.debug = c.status.debug; fi.ptbr_mode = c.ptbr_mode; fi.pmp = &pmp_;
  fi.ptw = tlb_response(p, 1);
  fi.a_ready = fabric.ic_a_ready; fi.d_valid = fabric.ic_d_valid;
  fi.d_opcode = fabric.ic_d.opcode; fi.d_size = fabric.ic_d.size; fi.d_data = fabric.ic_d.data; fi.d_corrupt = fabric.ic_d.corrupt;
  frontend_.evaluate(fi, frontend_wires_);

  const auto& d = c.dmem;
  dcache_input_ = DcacheIn{};
  auto& di = dcache_input_;
  di.exact_seam = publishes_oracles();
  di.reset = reset; di.pmp = &pmp_; di.ptbr_mode = c.ptbr_mode;
  di.dprv = c.status.dprv; di.debug = c.status.debug; di.sum = c.status.sum; di.mxr = c.status.mxr;
  di.ptw = tlb_response(p, 0);
  di.req_valid = p.mem_req_valid || d.req_valid;
  if (p.mem_req_valid) {
    di.req.addr = p.mem_req_addr; di.req.tag = 0; di.req.cmd = M_XRD; di.req.size = 3;
    di.req.dprv = 1; di.req.phys = true;
  } else {
    di.req = HellaReq{d.req_addr, static_cast<uint8_t>(((d.req_tag << 1) | 1) & 127),
      d.req_cmd,d.req_size,d.req_signed,d.req_dprv,d.req_phys,d.req_no_alloc,d.req_no_xcpt,d.req_data,d.req_mask};
  }
  di.s1_kill = s1_owner_ == 0 ? p.mem_s1_kill : d.s1_kill;
  di.s1_data = s1_owner_ == 0 ? 0 : d.s1_data;
  di.s1_mask = s1_owner_ == 0 ? 0 : d.s1_mask;
  di.s2_kill = s2_owner_ == 0 ? false : d.s2_kill;
  di.a_ready = fabric.dc_a_ready; di.c_ready = fabric.dc_c_ready; di.e_ready = fabric.dc_e_ready;
  di.b_valid = fabric.dc_b_valid; di.b_address = fabric.dc_b.address; di.b_param = fabric.dc_b.param;
  di.b_size = fabric.dc_b.size; di.b_source = static_cast<uint8_t>(fabric.dc_b.source);
  di.d_valid = fabric.dc_d_valid; di.d_opcode = fabric.dc_d.opcode; di.d_param = fabric.dc_d.param;
  di.d_size = fabric.dc_d.size; di.d_source = static_cast<uint8_t>(fabric.dc_d.source); di.d_sink = fabric.dc_d.sink;
  di.d_denied = fabric.dc_d.denied; di.d_corrupt = fabric.dc_d.corrupt; di.d_data = fabric.dc_d.data;
  dcache_.evaluate(di, dcache_wires_);
}
void NativeSystem::evaluate_ptw(bool reset) {
  ptw_input_ = PtwIn{};
  auto& p = ptw_input_;
  const auto& d = dcache_wires_;
  const auto& f = frontend_wires_;
  p.reset = reset; p.pmp = &pmp_; p.ptbr_ppn = core_output_.ptbr_ppn; p.ptbr_mode = core_output_.ptbr_mode;
  p.sfence_valid = core_output_.imem.sfence_valid; p.sfence_rs1 = core_output_.imem.sfence_rs1;
  p.req_valid[0] = d.ptw_req_valid; p.req_bits_valid[0] = !dcache_input_.s2_kill; p.req_addr[0] = d.ptw_req_addr;
  p.req_valid[1] = f.ptw_req_valid; p.req_bits_valid[1] = f.ptw_req_bits_valid; p.req_addr[1] = f.ptw_req_addr;
  p.mem_req_ready = d.req_ready;
  p.mem_resp_valid = d.resp_valid && !(d.resp_tag & 1);
  p.mem_resp_data = p.mem_resp_valid ? d.resp_data : 0;
  p.mem_s2_nack = d.s2_nack && s2_owner_ == 0;
  p.mem_s2_xcpt_ae_ld = d.xcpt_ae_ld;
  if (ptw_idle_skip_enabled_ && ptw_.state_ == PTW_S_READY && !ptw_.l2_refill_ && !ptw_.mem_resp_valid_ &&
      !ptw_.resp_valid_[0] && !ptw_.resp_valid_[1] && !p.req_valid[0] && !p.req_valid[1] &&
      !p.mem_resp_valid && !p.mem_s2_nack && !p.sfence_valid) {
    // No walk, response or fence can consume the PTE-cache/PMP calculation.
    // This is also valid for strict register oracles: commit still advances
    // every request/response register once; no retained payload is skipped.
    ptw_wires_ = PtwWires{};
    ptw_wires_.req_ready[0] = ptw_wires_.req_ready[1] = true;
    ptw_wires_.mem_s1_kill = true;
    return;
  }
  ptw_.evaluate(p, ptw_wires_);
}
void NativeSystem::evaluate_uncore(const NativeSystemInputs& in) {
  uncore_input_ = uncore::UncoreIn{};
  auto& u = uncore_input_;
  const auto& d = dcache_wires_;
  const auto& f = frontend_wires_;
  u.reset = in.reset; u.dmi_req_valid = in.dmi_req_valid; u.dmi_req_addr = in.dmi_req_addr;
  u.dmi_req_data = in.dmi_req_data; u.dmi_req_op = in.dmi_req_op; u.dmi_resp_ready = in.dmi_resp_ready;
  u.dc_a_valid = d.a.valid;
  u.dc_a = uncore::TlA{d.a.opcode,d.a.param,d.a.size,d.a.source,d.a.address,d.a.mask,d.a.data,d.a.corrupt};
  u.dc_c_valid = d.c.valid;
  u.dc_c = uncore::TlC{d.c.opcode,d.c.param,d.c.size,d.c.source,d.c.address,d.c.data,d.c.corrupt};
  u.dc_e_valid = d.e_valid; u.dc_e.sink = d.e_sink; u.dc_b_ready = d.b_ready; u.dc_d_ready = d.d_ready;
  u.ic_a_valid = f.a_valid;
  u.ic_a = uncore::TlA{uncore::A_Get,0,6,0,f.a_address,255,0,false};
  u.ic_d_ready = true;
  uncore_.evaluate(u, uncore_output_);
}

RocketFullSystemInputs NativeSystem::feedback(bool reset) const {
  RocketFullSystemInputs in{};
  in.reset = reset; in.reset_vector = reset_vector_;
  in.interrupt_debug = uncore_.tile_debug_int_sync.out();
  in.interrupt_msip = uncore_.int_clint_reg[0]; in.interrupt_mtip = uncore_.int_clint_reg[1];
  in.interrupt_meip = uncore_.int_plic_reg[0]; in.interrupt_seip = uncore_.int_plic_reg[1];
  const auto& f = frontend_wires_;
  auto& im = in.imem;
  im.clock_enabled = frontend_.clock_en_reg_ || core_output_.imem.might_request;
  im.resp_valid = f.resp_valid; im.npc = f.npc;
  im.perf_acquire = f.a_valid && uncore_output_.ic_a_ready;
  im.perf_tlb_miss = f.ptw_req_valid && ptw_wires_.req_ready[1];
  if (f.resp_valid || publishes_oracles()) {
    im.resp_pc = f.resp.pc; im.resp_data = f.resp.data; im.resp_mask = f.resp.mask;
    im.resp_replay = f.resp.replay; im.resp_xcpt_pf_inst = f.resp.pf_inst; im.resp_xcpt_ae_inst = f.resp.ae_inst;
    im.resp_btb = RocketSystemBtbResponse{f.resp.btb_cfi_type,f.resp.btb_taken,f.resp.btb_mask,
      f.resp.btb_bridx != 0,f.resp.btb_target,f.resp.btb_entry,f.resp.bht_history,f.resp.bht_value != 0};
  }
  const auto& d = dcache_wires_;
  auto& dm = in.dmem;
  dm.req_ready = d.req_ready && !ptw_wires_.mem_req_valid;
  dm.s2_nack = d.s2_nack && s2_owner_ == 1; dm.s2_nack_cause_raw = d.s2_nack_cause_raw;
  dm.s2_uncached = d.s2_uncached; dm.s2_paddr = d.s2_paddr;
  dm.replay_next = d.replay_next; dm.ordered = d.ordered; dm.clock_enabled = dcache_.clock_en_reg_;
  dm.s2_xcpt_ma_ld = d.xcpt_ma_ld; dm.s2_xcpt_ma_st = d.xcpt_ma_st;
  dm.s2_xcpt_pf_ld = d.xcpt_pf_ld; dm.s2_xcpt_pf_st = d.xcpt_pf_st;
  dm.s2_xcpt_ae_ld = d.xcpt_ae_ld; dm.s2_xcpt_ae_st = d.xcpt_ae_st;
  dm.perf_acquire = d.perf_acquire; dm.perf_release = d.perf_release; dm.perf_grant = d.perf_grant;
  dm.perf_tlb_miss = d.perf_tlb_miss; dm.perf_blocked = d.perf_blocked;
  dm.perf_can_accept_store_then_load = d.perf_can_accept_store_then_load;
  dm.perf_can_accept_store_then_rmw = d.perf_can_accept_store_then_rmw;
  dm.perf_can_accept_load_then_load = d.perf_can_accept_load_then_load;
  dm.perf_store_buffer_empty_after_load = d.perf_store_buffer_empty_after_load;
  dm.perf_store_buffer_empty_after_store = d.perf_store_buffer_empty_after_store;
  dm.resp.valid = d.resp_valid && (d.resp_tag & 1);
  if (dm.resp.valid || publishes_oracles()) {
    dm.resp.addr = d.resp_addr; dm.resp.tag = d.resp_tag >> 1; dm.resp.cmd = d.resp_cmd;
    dm.resp.size = d.resp_size; dm.resp.signed_data = d.resp_signed; dm.resp.dprv = dcache_.s2_req_.dprv;
    dm.resp.mask = dcache_.s2_req_.mask; dm.resp.replay = d.resp_replay; dm.resp.has_data = d.resp_has_data;
    dm.resp.data = d.resp_data; dm.resp.data_word_bypass = d.resp_data_word_bypass;
    dm.resp.data_raw = d.resp_data_raw; dm.resp.store_data = d.resp_store_data;
  }
  in.ptw_perf_pte_hit = ptw_.state_ == PTW_S_REQ && ptw_wires_.pte_cache_hit;
  in.ptw_perf_pte_miss = ptw_.state_ == PTW_S_WAIT2 && ptw_.count_ < 2;
  in.ptw_clock_enabled = ptw_.state_ != PTW_S_READY || ptw_.l2_refill_ ||
      frontend_wires_.ptw_req_valid || dcache_wires_.ptw_req_valid || core_output_.imem.sfence_valid || (core_output_.custom_csr_value[0] & 1);
  const auto& fp = fpu_wires_;
  auto& fi = in.fpu;
  fi.fcsr_flags_valid = fp.fcsr_flags_valid; fi.fcsr_flags = fp.fcsr_flags;
  fi.store_data = fp.store_data; fi.toint_data = fp.toint_data;
  fi.fcsr_ready = fp.fcsr_rdy; fi.nack_mem = fp.nack_mem; fi.illegal_rm = fp.illegal_rm;
  fi.sboard_set = fp.sboard_set; fi.sboard_clear = fp.sboard_clr; fi.sboard_clear_addr = fp.sboard_clra;
#define DEC(field) fi.dec_##field = fp.dec.field
  DEC(ldst); DEC(wen); DEC(ren1); DEC(ren2); DEC(ren3); DEC(swap12); DEC(swap23);
  DEC(fromint); DEC(toint); DEC(fastpipe); DEC(fma); DEC(div); DEC(sqrt); DEC(wflags);
#undef DEC
  fi.dec_type_tag_in = fp.dec.typeTagIn; fi.dec_type_tag_out = fp.dec.typeTagOut;
  return in;
}

NativeSystemOutputs NativeSystem::step(const NativeSystemInputs& input, Image* oracle) {
  if (oracle && !publishes_oracles())
    throw std::logic_error("oracle export requires Oracle mode from construction");
  const bool reset = input.reset || uncore_.ldut_reset_reg;
  fpu_.evaluate_state(fpu_wires_);
  core_input_.reset = reset; core_input_.reset_vector = reset_vector_;
  core_input_.interrupt_debug = uncore_.tile_debug_int_sync.out();
  core_input_.interrupt_msip = uncore_.int_clint_reg[0]; core_input_.interrupt_mtip = uncore_.int_clint_reg[1];
  core_input_.interrupt_meip = uncore_.int_plic_reg[0]; core_input_.interrupt_seip = uncore_.int_plic_reg[1];
  unsigned iterations = 0;
  bool closed = false;
  for (; iterations < feedback_limit_; ++iterations) {
    const PtwWires prior_ptw = ptw_wires_;
    const uncore::UncoreOut prior_fabric = uncore_output_;
    core_.evaluate(core_input_, core_wires_, core_output_);
    evaluate_fpu(reset);
    // PMP outputs depend only on Core PRE CSR registers. None of the valid
    // protocol feedback rounds commits those registers, so one snapshot
    // serves Frontend, Dcache and PTW for the complete common edge.
    if (iterations == 0) capture_pmp();
    evaluate_memory(reset, prior_ptw, prior_fabric);
    evaluate_ptw(reset);
    evaluate_uncore(input);
    const auto next = feedback(reset);
    closed = core_feedback_equal(core_input_, next, core_wires_.id_ctrl.fp) && ptw_feedback_equal(prior_ptw, ptw_wires_) &&
             fabric_feedback_equal(prior_fabric, uncore_output_);
    if (closed) { ++iterations; break; }
    core_input_ = next;
  }
  if (!closed) throw std::runtime_error("native system valid-protocol feedback did not close at cycle " + std::to_string(cycles_));
  if (oracle) {
    // Only Core owns persistent fields in image_. Every other component
    // exports its complete selected fields below, so copying their stale
    // image_ bytes first is redundant. Core's copy still precedes commit.
    oracle->core = image_.core;
    frontend_.export_image(oracle->frontend);
    dcache_.export_image(oracle->dcache);
    ptw_.export_image(oracle->ptw);
    fpu_.export_image(oracle->fpu);
    uncore_.export_image(*oracle);
  }
  const uint8_t owner = ptw_wires_.mem_req_valid ? 0 : 1;
  const bool fp_load_write = !reset && fpu_.load_wb_;
  const bool fp_pipe_write = !reset && fpu_wires_.regfile_write_pipe;
  const uint8_t fp_load_reg = fpu_.load_wb_tag_ & 31;
  const uint8_t fp_pipe_reg = fpu_wires_.waddr & 31;
  // Both ports can target the same register. Preserve the earlier load value
  // independently, because the later pipeline port wins in the final RF.
  const uint64_t fp_load_value = !fp_load_write ? 0 : (fpu_.load_wb_typeTag_ & 1) ?
      fpu_.load_wb_data_ : (UINT64_C(0xffffffff00000000) | uint32_t(fpu_.load_wb_data_));
  // Every component commits its captured PRE inputs exactly once. The PMP
  // snapshot is owned here, so Core CSR updates cannot change another commit.
  core_.commit(core_input_, core_wires_);
  fpu_.commit(fpu_input_, fpu_wires_);
  frontend_.commit(frontend_input_, frontend_wires_);
  dcache_.commit(dcache_input_, dcache_wires_);
  ptw_.commit(ptw_input_, ptw_wires_);
  uncore_.commit();
  if (oracle) uncore_.export_post_image(*oracle);
  s2_owner_ = s1_owner_; s1_owner_ = owner;
  NativeSystemOutputs out;
  out.cycle = cycles_++;
  out.dmi_req_ready = uncore_output_.dmi_req_ready; out.dmi_resp_valid = uncore_output_.dmi_resp_valid;
  out.dmi_resp_data = uncore_output_.dmi_resp_data; out.dmi_resp_resp = uncore_output_.dmi_resp_resp;
  out.interrupt_debug = core_input_.interrupt_debug; out.interrupt_msip = core_input_.interrupt_msip;
  out.interrupt_mtip = core_input_.interrupt_mtip; out.interrupt_meip = core_input_.interrupt_meip; out.interrupt_seip = core_input_.interrupt_seip;
  out.core_reset = reset; out.feedback_iterations = iterations; out.retirement = core_.retirement();
  if (fp_load_write) out.fp_writes[out.fp_write_count++] = NativeFloatWrite{fp_load_reg, fp_load_value};
  if (fp_pipe_write) out.fp_writes[out.fp_write_count++] = NativeFloatWrite{fp_pipe_reg, fpu_.architectural_rf(fp_pipe_reg)};
  return out;
}

uint64_t NativeSystem::read_integer_register(unsigned index) const {
  if (index >= 32) throw std::out_of_range("native integer register index");
  return core_.rf(index);
}
uint64_t NativeSystem::read_float_register(unsigned index) const { return fpu_.architectural_rf(index); }
hf::u128 NativeSystem::read_float_recoded(unsigned index) const {
  if (index >= 32) throw std::out_of_range("native floating register index");
  return fpu_.regfile_[index] & hf::mask128(65);
}
uint64_t NativeSystem::read_memory_word(uint64_t address) const {
  // Validate the complete range and seed the unaligned fallback from backing.
  uint64_t result = uncore_.read_memory_word(address);
  if ((address & 7) == 0) {
    const unsigned set = (address >> 6) & 63;
    const uint32_t tag = static_cast<uint32_t>(address >> 12) & 0xfffff;
    for (unsigned way = 0; way < 4; ++way) {
      const uint32_t metadata = dcache_.tag_[set][way];
      if ((metadata >> 20) && (metadata & 0xfffff) == tag) {
        std::memcpy(&result, &dcache_.data_[way][set][address & 63], sizeof result);
        break;
      }
    }
    return result;
  }
  for (unsigned byte = 0; byte < 8; ++byte) {
    const uint64_t a = address + byte;
    const unsigned set = (a >> 6) & 63;
    const uint32_t tag = static_cast<uint32_t>(a >> 12) & 0xfffff;
    for (unsigned way = 0; way < 4; ++way) {
      const uint32_t metadata = dcache_.tag_[set][way];
      if ((metadata >> 20) && (metadata & 0xfffff) == tag) {
        const unsigned shift = 8 * byte;
        result = (result & ~(UINT64_C(255) << shift)) | (uint64_t(dcache_.data_[way][set][a & 63]) << shift);
        break;
      }
    }
  }
  return result;
}

}  // namespace chisa::rocket_model
