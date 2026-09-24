// Per-cycle wires of the uncore model: everything commit() needs from evaluate().
#pragma once

#include "uncore/uncore.h"

namespace chisa::rocket_model::uncore {

struct FragWires {
  bool in_valid = false; TlA in;          // fragmenter input (from the crossbar)
  bool rep_enq_fire = false, rep_deq_fire = false, repeat = false;
  bool out_fire = false; TlA out;         // to the device
  uint8_t new_gennum = 0; bool aFirst = false;
  bool d_valid = false; TlD d;            // device response (before the fragmenter)
  bool d_fire = false, dFirst = false; uint8_t dFirst_acknum = 0, ack_decrement = 0, dFirst_size = 0;
  bool up_valid = false; TlD up;          // response towards the crossbar
  bool device_a_ready = false;            // the device accepts out this cycle
};

struct AxiMemWires {
  // fragmenter
  bool ar_in_fire = false, aw_in_fire = false, w_in_fire = false; AxiA ar_in, aw_in; AxiW w_in;
  bool ar_out_fire = false, aw_out_fire = false, w_out_fire = false; AxiA ar_out, aw_out; AxiW w_out;
  bool ar_last = false, aw_last = false; uint32_t ar_mux_addr = 0, aw_mux_addr = 0; uint8_t ar_len = 0, aw_len = 0;
  bool wbeats_valid = false, wbeats_ready = false; uint16_t w_todo = 0;
  bool b_out_fire = false; AxiB b_out; bool b_last = false;   // b leaving the buffer towards the fragmenter
  bool r_out_fire = false; AxiR r_out;
  bool b_up_fire = false; AxiB b_up; bool r_up_fire = false; AxiR r_up;   // towards the yanker
  // buffer -> ram
  bool ram_aw_fire = false, ram_w_fire = false, ram_ar_fire = false, ram_b_fire = false, ram_r_fire = false;
  AxiA ram_aw, ram_ar; AxiW ram_w;
  bool ram_w_sel0 = false, ram_r_sel0 = false; uint32_t ram_w_index = 0, ram_r_index = 0;
  uint64_t ram_rdata_next = 0;
  uint64_t raw_read_data = 0;
  bool b_buf_valid = false, r_buf_valid = false; AxiB b_buf; AxiR r_buf;   // ram responses (into the buffer)
};

struct ToAxiWires {
  bool a_valid = false; TlA a; bool a_fire = false, a_first = false, a_last = false, is_put = false;
  bool stall = false;
  bool arw_valid = false, arw_fire = false; ToAxi4::Arw arw;
  bool w_valid = false, w_fire = false; AxiW w;
  bool q_arw_deq_fire = false, q_w_deq_fire = false;   // to the AXI side
  AxiA ar_out, aw_out; bool ar_out_valid = false, aw_out_valid = false; AxiW w_out; bool w_out_valid = false;
  bool r_valid = false, b_valid = false; AxiR r; AxiB b; bool r_fire = false, b_fire = false; bool r_wins = false;
  bool d_valid = false; TlD d; bool d_fire = false, d_last = false; uint8_t d_id = 0;
  uint8_t a_id = 0;
};

struct Uncore::Wires {
  // tile crossbar / buffers
  uint32_t tx_valids = 0; bool tx_sink_ready = false, tx_sink_fire = false; TlA tx_a; uint32_t tx_beats1 = 0;
  bool tb_a_deq_fire = false, tb_b_enq_fire = false, tb_b_deq_fire = false, tb_c_enq_fire = false, tb_c_deq_fire = false;
  bool tb_d_enq_fire = false, tb_d_deq_fire = false, tb_e_enq_fire = false, tb_e_deq_fire = false;
  TlB tb_b_enq; TlD tb_d_enq;
  // system bus
  bool tile_a_valid = false; TlA tile_a; unsigned tile_route = 0;
  uint32_t sb_a_valids[3] = {}; bool sb_a_ready[3] = {}, sb_a_fire[3] = {}; uint32_t sb_a_beats1[3] = {}; TlA sb_a_out[3];
  uint32_t sb_d_valids[2] = {}; bool sb_d_ready[2] = {}, sb_d_fire[2] = {}; uint32_t sb_d_beats1[2] = {};
  bool out_d_valid[3] = {}; TlD out_d[3]; bool out_d_ready[3] = {};
  // control bus
  bool cb_a_in_valid = false; TlA cb_a_in;   // sbus out0 a
  bool at_source_i_fire = false, at_source_c_fire = false, at_supported = true; uint32_t at_valids = 0; bool at_sink_ready = false, at_sink_fire = false; TlA at_out; uint32_t at_beats1 = 0;
  bool at_d_fire = false, at_d_first = false, at_d_sel = false; TlD at_d_out; bool at_d_drop = false; uint64_t at_d_beats1 = 0;
  bool cb_a_enq_fire = false, cb_a_deq_fire = false, cb_d_enq_fire = false, cb_d_deq_fire = false; TlD cb_d_enq; TlA cb_a_head;
  uint32_t cb_fixer_beats1 = 0;
  uint32_t cbd_valids = 0; bool cbd_sink_ready = false, cbd_sink_fire = false; uint32_t cbd_beats1 = 0;
  bool cb_d_valid_up = false; TlD cb_d_up;      // cbus D towards the sbus
  // error device
  bool er_bufa_enq_fire = false, er_bufa_deq_fire = false, er_a_enq_fire = false, er_a_deq_fire = false, er_bufd_enq_fire = false, er_bufd_deq_fire = false;
  TlD er_d; uint32_t er_a_beats1 = 0;
  FragWires fr[4];   // plic, clint, debug, rom
  bool plic_in_fire = false, plic_out_fire = false; RegMapperReq plic_req; uint32_t plic_claim_dev = 0; bool plic_claim = false;
  bool clint_write = false; uint32_t clint_index = 0; uint8_t clint_mask = 0; uint64_t clint_wdata = 0;
  bool rtc_tick = false;
  // debug TL side
  bool dbg_tl_fire = false, dbg_tl_read = false; uint32_t dbg_tl_index = 0; uint8_t dbg_tl_mask = 0; uint64_t dbg_tl_wdata = 0;
  // l2 hub
  bool l2_a_valid = false; TlA l2_a; bool l2_a_first = false; uint32_t l2_select = 0; bool l2_a_ready = false; bool l2_req_fire = false;
  bool l2_todo = false; unsigned l2_mshr = 0; bool l2_needT = false;
  bool trk_in_fire[4] = {}; bool trk_odata_enq[4] = {}, trk_odata_deq[4] = {}; bool trk_probe_valid[4] = {};
  bool trk_d_last[4] = {}, trk_e_last[4] = {}, trk_probenack[4] = {}, trk_probedack[4] = {}, trk_probesack[4] = {}; uint8_t trk_clearOH[4] = {};
  bool l2_b_fire = false;
  bool l2_c_valid = false; TlC l2_c; bool l2_c_fire = false;
  uint32_t l2a_valids = 0; bool l2a_sink_ready = false, l2a_sink_fire = false; uint32_t l2a_beats1 = 0; TlA l2_out_a;
  uint32_t l2d_valids = 0; bool l2d_sink_ready = false, l2d_sink_fire = false; uint32_t l2d_beats1 = 0;
  bool l2_outd_valid = false; TlD l2_outd; bool l2_outd_fire = false, l2_dnormal_fire = false, l2_d_first = false; uint8_t l2_trackerOH = 0; uint32_t l2_dn_beats1 = 0;
  bool l2_e_fire = false; uint8_t l2_e_sink = 0;
  // memory bus AXI
  ToAxiWires mb;
  bool mb_rq_enq[16] = {}, mb_rq_deq[16] = {}, mb_wq_enq[16] = {}, mb_wq_deq[16] = {}; YankEcho mb_rq_bits, mb_wq_bits;
  AxiMemWires mem;
  // mmio AXI
  ToAxiWires mm;
  bool mm_rq_enq[5] = {}, mm_rq_deq[5] = {}, mm_wq_enq[5] = {}, mm_wq_deq[5] = {}; YankEcho mm_rq_bits, mm_wq_bits;
  bool mm_deint_q_enq[5] = {}, mm_deint_q_deq[5] = {}; AxiR mm_deint_enq_bits; bool mm_deint_in_r_fire = false; uint32_t mm_deint_pending = 0; bool mm_deint_inc[5] = {}, mm_deint_dec[5] = {};
  bool mmb_aw_enq = false, mmb_aw_deq = false, mmb_w_enq = false, mmb_w_deq = false, mmb_ar_enq = false, mmb_ar_deq = false, mmb_b_enq = false, mmb_b_deq = false, mmb_r_enq = false, mmb_r_deq = false;
  AxiA mmb_aw_bits, mmb_ar_bits; AxiW mmb_w_bits; AxiB mmb_b_bits; AxiR mmb_r_bits;
  AxiMemWires mmio;
  // debug / DMI
  bool dmi_a_valid = false; TlA dmi_a; bool dmi_a_fire = false; bool dmi_to_outer = false;
  bool outer_fire = false, outer_read = false; uint32_t outer_wdata = 0; uint8_t outer_mask = 0; unsigned outer_index = 0;
  bool dmactiveWrEn = false, ndmresetWrEn = false, clrWrEn = false, setWrEn = false, ackWrEn = false, resumeWrEn = false, haltreqWrEn = false;
  bool innerCtrl_valid = false, innerCtrl_ready = false; bool ic_resumereq = false, ic_ackhavereset = false, ic_hrmask = false;
  bool bypass = false, bar_stall = false, bar_a_fire = false, bar_d_fire = false; uint8_t bar_flight_next = 0;
  bool err_a_fire = false, err_d_valid = false; TlD err_d; uint32_t errd_valids = 0; bool errd_sink_ready = false, errd_sink_fire = false;
  bool as_enq_fire = false; uint64_t as_bits = 0;   // asource A enq
  bool ds_deq_fire = false;                          // d_sink deq (D back into the DMI domain)
  bool ics_enq_fire = false; uint64_t ics_bits = 0;  // innerCtrl source enq
  uint32_t dx_valids = 0; bool dx_sink_ready = false, dx_sink_fire = false; TlD dx_d;   // dmiXbar in.d arbiter
  bool debug_clk = false;
  // debug clock domain
  bool a_sink_deq_fire = false; bool inner_dmi_fire = false, inner_dmi_read = false; unsigned inner_index = 0; uint32_t inner_wdata = 0; uint8_t inner_mask = 0;
  bool d_source_enq_fire = false; uint64_t d_source_bits = 0;
  bool ic_sink_deq_fire = false;
  bool goAbstract = false, errorBusy = false, errorException = false, errorUnsupported = false, errorHaltResume = false;
  uint8_t ctrlStateNxt = 0; bool cmderr_wr = false; uint8_t cmderr_wdata = 0;
  bool command_wr = false; uint32_t command_wdata = 0; bool autoexecdata_wr = false, autoexecprogbuf_wr = false; uint32_t auto_wdata = 0;
  uint8_t data_wr_mask = 0; uint8_t data_wr[8] = {}; uint64_t progbuf_wr_mask = 0; uint8_t progbuf_wr[64] = {};
  bool hartHaltedWrEn = false, hartGoingWrEn = false, hartResumingWrEn = false, hartExceptionWrEn = false;
  bool resumereq = false, ackhavereset_fire = false, ic_fire = false;
  uint64_t d_source_pack = 0;
  bool haltedBit_next = false;
};

void axi_mem_commit(AxiMem& m, const AxiMemWires& w, uint8_t* mem_bytes);
void commit_datapath(Uncore& u, const UncoreIn& in);

}  // namespace chisa::rocket_model::uncore
