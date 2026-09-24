#pragma once
// Software Sv39 page-walk state machine with PTE and second-level TLB caches.
// This replaces the old optional protocol-model path; no RTL evaluator or
// generated implementation is included. Interface geometry is explicit.
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "../protocol/ptw.h"

namespace chisa::boom_system::components {
using namespace protocol;

class PageWalkerModel {
 public:
  PageWalkerModel() {
    refresh_outputs(last_inputs_);
    refresh_oracles();
  }

  const PtwOutputs& evaluate(const PtwInputs& inputs) {
    if (!active_ && inputs == last_inputs_) {
      ++evaluate_skipped_count_;
      return outputs_;
    }
    refresh_outputs(inputs);
    refresh_oracles();
    return outputs_;
  }

  void commit(const PtwInputs& inputs) {
    const bool inputs_changed = inputs != last_inputs_;
    if (!active_ && !inputs_changed) {
      ++skipped_count_;
      return;
    }
    if (inputs_changed) drain_cycles_ = kBoundaryDrainCycles;
    step_edge(inputs);
    refresh_outputs(inputs);
    refresh_oracles();
    if (drain_cycles_ != 0) --drain_cycles_;
    active_ = busy() || drain_cycles_ != 0;
    last_inputs_ = inputs;
    ++eval_count_;
  }

  const PtwOutputs& outputs() const { return outputs_; }
  const PtwOracleState& oracles() const { return oracles_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return eval_count_; }
  std::uint64_t skipped_count() const { return skipped_count_; }
  std::uint64_t evaluate_skipped_count() const {
    return evaluate_skipped_count_;
  }

 private:
  static constexpr std::uint8_t kBoundaryDrainCycles = 2;
  enum : std::uint8_t {
    kReady = 0,
    kReq = 1,
    kWait1 = 2,
    kDummy1 = 3,
    kWait2 = 4,
    kWait3 = 5,
    kDummy2 = 6,
    kFragment = 7,
  };

  // ---- wires recomputed from the current registers and one input image ----
  struct Comb {
    bool arb_out_valid = false;
    bool arb_out_bits_valid = false;
    std::uint8_t arb_chosen = 0;
    std::uint32_t arb_out_addr = 0;
    bool arb_ready = false;
    bool arb_fire = false;
    std::uint64_t pte_addr = 0;
    // decoded view of mem_resp_data_ (PTW.scala:145-158)
    std::uint64_t res_ppn = 0;  // 20 bits, superpage-LSB adjusted validity
    bool res_v = false, res_r = false, res_w = false, res_x = false;
    bool res_u = false, res_g = false, res_a = false, res_d = false;
    std::uint8_t res_sw = 0;
    bool invalid_paddr = false;
    bool traverse = false;
    std::uint8_t pc_hits = 0;
    bool pc_hit = false;
    std::uint32_t pc_hit_data = 0;
    bool pte_cache_hit = false;
    // l2 combinational view
    std::uint32_t r_tag = 0;   // 18 bits
    std::uint16_t r_idx = 0;   // 9 bits
    bool r_valid_vec = false;
    bool parity_err = false;
    std::uint32_t entry_tag = 0;
    std::uint64_t entry_ppn = 0;
    bool entry_d = false, entry_a = false, entry_u = false;
    bool entry_x = false, entry_w = false, entry_r = false;
    bool s2_error = false;
    bool s2_hit = false;
    bool l2_hit = false;
    bool homogeneous = false;
  };

  static std::uint64_t xor_reduce(std::uint64_t v) {
    v ^= v >> 32;
    v ^= v >> 16;
    v ^= v >> 8;
    v ^= v >> 4;
    v ^= v >> 2;
    v ^= v >> 1;
    return v & 1u;
  }

  static bool l2_bit(const std::array<std::uint64_t, 8>& bits,
                     std::uint16_t idx) {
    return (bits[idx >> 6] >> (idx & 63u)) & 1u;
  }
  static void l2_bit_set(std::array<std::uint64_t, 8>& bits,
                         std::uint16_t idx, bool value) {
    if (value)
      bits[idx >> 6] |= (std::uint64_t{1} << (idx & 63u));
    else
      bits[idx >> 6] &= ~(std::uint64_t{1} << (idx & 63u));
  }

  // A page is homogeneous when it fits inside one memory-map region.
  static bool pma_page(std::uint64_t address,unsigned page_bits) {
    struct Region { std::uint64_t begin,size; };
    static constexpr Region regions[]={{0,0x1000},{0x3000,0x1000},{0x10000,0x10000},
      {0x2000000,0x10000},{0xc000000,0x4000000},{0x60000000,0x20000000},{0x80000000,0x10000000}};
    const auto bytes=UINT64_C(1)<<page_bits;const auto first=address&~(bytes-1);
    for (const auto& region:regions) if (first>=region.begin && bytes<=region.size && first-region.begin<=region.size-bytes) return true;
    return false;
  }
  static bool pma_level2(std::uint64_t address) { return pma_page(address,12); }
  static bool pma_level1(std::uint64_t address) { return pma_page(address,21); }

  // Tree replacement policy: each node names the less-recently-used half.
  // Postorder node numbering retains the published seven-bit encoding.
  std::uint8_t plru_way() const {
    unsigned base=0,width=8,way=0;
    while (width>1) {
      const unsigned half=width/2,direction=(pc_plru_>>(base+width-2))&1;
      way+=direction*half;base+=direction*(half-1);width=half;
    }
    return static_cast<std::uint8_t>(way);
  }
  void plru_touch(std::uint8_t way) {
    unsigned base=0,width=8;
    while (width>1) {
      const unsigned half=width/2,direction=(way&half)!=0,bit=base+width-2;
      pc_plru_=static_cast<std::uint8_t>((pc_plru_&~(1u<<bit))|((1u-direction)<<bit));
      base+=direction*(half-1);width=half;
    }
  }

  // PMPHomogeneityChecker (PMP.scala:98-143) for pmpGranularity=4:
  // comparand = addr << 2, mask comes in from the CSR file.  An OFF entry
  // (a=0) is trivially homogeneous, so no special casing is needed.
  static bool pmp_homogeneous(const PtwInputs& in, std::uint64_t page,
                              std::uint8_t level) {
    const unsigned idx_bits = level >= 2 ? 12u : level == 1 ? 21u : 30u;
    const std::uint64_t pg_mask =
        (UINT64_C(0xffffffff) << idx_bits) & UINT64_C(0xffffffff);
    bool homogeneous = true;
    std::uint64_t prev_comparand = 0;
    for (const PtwPmp& p : in.pmp) {
      const bool napot = (p.address_mode >> 1) & 1u;
      const bool tor_not_napot = p.address_mode & 1u;
      const std::uint64_t comparand =
          (static_cast<std::uint64_t>(p.address) << 2) & UINT64_C(0xffffffff);
      bool h;
      if (napot) {
        const bool mask_h = (p.mask >> (idx_bits - 1)) & 1u;
        h = mask_h || (((page ^ comparand) >> idx_bits) != 0);
      } else if (!tor_not_napot) {
        h = true;
      } else {
        const bool begins_after_lower = page >= prev_comparand;
        const bool begins_after_upper = page >= comparand;
        const bool ends_before_lower =
            (page & pg_mask) < (prev_comparand & pg_mask);
        const bool ends_before_upper =
            (page & pg_mask) < (comparand & pg_mask);
        h = ends_before_lower || begins_after_upper ||
            (begins_after_lower && ends_before_upper);
      }
      homogeneous = homogeneous && h;
      prev_comparand = comparand;
    }
    return homogeneous;
  }

  Comb comb(const PtwInputs& in) const {
    Comb c;
    // requestor arbiter (index 0 wins)
    c.arb_out_valid = in.requestors[0].valid || in.requestors[1].valid ||
                      in.requestors[2].valid;
    c.arb_chosen = in.requestors[0].valid ? 0u
                   : in.requestors[1].valid ? 1u
                                            : 2u;
    c.arb_out_bits_valid = in.requestors[c.arb_chosen].payload_valid;
    c.arb_out_addr = in.requestors[c.arb_chosen].vpn & UINT32_C(0x7ffffff);
    c.arb_ready = (state_ == kReady) && !l2_refill_;
    c.arb_fire = c.arb_out_valid && c.arb_ready;

    // pte_addr from the registered walk position
    const std::uint32_t vpn_idx =
        count_ == 0 ? ((r_req_addr_ >> 18) & 0x1ffu)
        : count_ == 1 ? ((r_req_addr_ >> 9) & 0x1ffu)
                      : (r_req_addr_ & 0x1ffu);
    c.pte_addr = ((r_pte_ppn_ << 9) | vpn_idx) << 3;

    // decode of the (un-gated) memory response payload
    const std::uint64_t raw = mem_resp_data_;
    // Upper/reserved PTE bits must also make an out-of-range physical page
    // fail validation; truncating to the architectural PPN hides that error.
    const std::uint64_t tmp_ppn = raw >> 10;
    c.res_v = raw & 1u;
    c.res_r = (raw >> 1) & 1u;
    c.res_w = (raw >> 2) & 1u;
    c.res_x = (raw >> 3) & 1u;
    c.res_u = (raw >> 4) & 1u;
    c.res_g = (raw >> 5) & 1u;
    c.res_a = (raw >> 6) & 1u;
    c.res_d = (raw >> 7) & 1u;
    c.res_sw = static_cast<std::uint8_t>((raw >> 8) & 3u);
    c.res_ppn = tmp_ppn & UINT64_C(0xfffff);
    if (c.res_r || c.res_w || c.res_x) {
      // superpage PPN LSBs must be zero (PTW.scala:150-153)
      if (count_ <= 0 && ((tmp_ppn >> 9) & 0x1ffu) != 0) c.res_v = false;
      if (count_ <= 1 && (tmp_ppn & 0x1ffu) != 0) c.res_v = false;
    }
    c.invalid_paddr = (tmp_ppn >> 20) != 0;
    const bool res_table = c.res_v && !c.res_r && !c.res_w && !c.res_x;
    c.traverse = res_table && !c.invalid_paddr && count_ < 2;

    // 8-entry PTE cache lookup
    const std::uint32_t pa32 = static_cast<std::uint32_t>(c.pte_addr);
    c.pc_hits = 0;
    for (std::size_t i = 0; i < 8; ++i)
      if (((pc_valid_ >> i) & 1u) && pc_tags_[i] == pa32)
        c.pc_hits |= static_cast<std::uint8_t>(1u << i);
    c.pc_hit = c.pc_hits != 0;
    c.pc_hit_data = 0;
    for (std::size_t i = 0; i < 8; ++i)
      if ((c.pc_hits >> i) & 1u) c.pc_hit_data |= pc_data_[i];
    c.pte_cache_hit = c.pc_hit && count_ < 2;

    // L2 TLB s2 view (decode of the s1 read register)
    c.r_tag = (r_req_addr_ >> 9) & UINT32_C(0x3ffff);
    c.r_idx = static_cast<std::uint16_t>(r_req_addr_ & 0x1ffu);
    c.r_valid_vec = l2_bit(l2_valid_, c.r_idx);
    c.parity_err = xor_reduce(r_1_ & UINT64_C(0x1fffffffffff)) != 0;
    const std::uint64_t payload = r_1_ & UINT64_C(0xfffffffffff);
    c.entry_tag = static_cast<std::uint32_t>((payload >> 26) & 0x3ffffu);
    c.entry_ppn = (payload >> 6) & UINT64_C(0xfffff);
    c.entry_d = (payload >> 5) & 1u;
    c.entry_a = (payload >> 4) & 1u;
    c.entry_u = (payload >> 3) & 1u;
    c.entry_x = (payload >> 2) & 1u;
    c.entry_w = (payload >> 1) & 1u;
    c.entry_r = payload & 1u;
    c.s2_error = s2_valid_vec_ && c.parity_err;
    const bool s2_hit_vec = s2_valid_vec_ && (c.r_tag == c.entry_tag);
    c.s2_hit = s2_valid_ && s2_hit_vec;
    c.l2_hit = c.s2_hit;

    const std::uint64_t page = c.pte_addr & ~UINT64_C(0xfff);
    const bool pma = count_ >= 2   ? pma_level2(c.pte_addr)
                     : count_ == 1 ? pma_level1(c.pte_addr)
                                   : false;
    c.homogeneous = pma && pmp_homogeneous(in, page, count_);
    return c;
  }

  void refresh_outputs(const PtwInputs& in) {
    const Comb c = comb(in);
    outputs_.request_ready[0] = c.arb_ready;
    outputs_.request_ready[1] = c.arb_ready && !in.requestors[0].valid;
    outputs_.request_ready[2] =
        c.arb_ready && !in.requestors[0].valid && !in.requestors[1].valid;
    for (std::size_t i = 0; i < 3; ++i) {
      PtwResponse& r = outputs_.responses[i];
      r.valid = resp_valid_[i];
      r.access_exception = resp_ae_;
      r.pte.ppn = r_pte_ppn_;
      r.pte.reserved_for_software = r_pte_sw_;
      r.pte.d = r_pte_d_;
      r.pte.a = r_pte_a_;
      r.pte.g = r_pte_g_;
      r.pte.u = r_pte_u_;
      r.pte.x = r_pte_x_;
      r.pte.w = r_pte_w_;
      r.pte.r = r_pte_r_;
      r.pte.v = r_pte_v_;
      r.level = count_;
      r.homogeneous = c.homogeneous;
      r.fragmented_superpage = false;  // pageGranularityPMPs == false
    }
    PtwMemoryRequest& m = outputs_.memory_request;
    m.valid = state_ == kReq || state_ == kDummy1;
    m.address = c.pte_addr & UINT64_C(0xffffffffff);
    m.tag = 0;      // hella tag is DontCare/0 in the lowered design
    m.command = 0;  // M_XRD
    m.size = 3;
    m.is_signed = false;
    m.dprv = 1;  // PRV.S
    m.physical = true;
    m.no_allocate = false;
    m.no_exception = false;
    m.data = 0;
    m.mask = 0;
    outputs_.memory_s1_kill = c.l2_hit || state_ != kWait1;
    outputs_.memory_s1_data = 0;
    outputs_.memory_s1_mask = 0;
    outputs_.memory_s2_kill = false;
    const bool clock_en = state_ != kReady || l2_refill_ ||
                          c.arb_out_valid || in.sfence_valid || (in.custom_csr_value&1);
    outputs_.memory_keep_clock_enabled = false;
    outputs_.clock_enabled = clock_en;
    outputs_.perf_l2_hit = c.s2_hit;
    outputs_.perf_l2_miss = s2_valid_ && !c.s2_hit;
    outputs_.perf_pte_hit = pte_hit_ && (state_ == kReq) && !c.s2_hit;
    // A lower-level cache miss is counted when its external PTE request
    // reaches the second memory stage. The terminal leaf is not a PTE-cache lookup.
    outputs_.perf_pte_miss = state_ == kWait2 && count_ < 2;
  }

  void step_edge(const PtwInputs& in) {
    const Comb c = comb(in);

    // ---- next-value computation from the pre-edge image ----
    std::uint8_t next_state = state_;
    std::uint8_t next_count = count_;
    bool next_resp_valid[3] = {false, false, false};
    bool next_resp_ae = false;
    bool next_pte_hit = false;
    bool next_l2_refill = false;

    switch (state_) {
      case kReady:
        if (c.arb_fire) next_state = c.arb_out_bits_valid ? kReq : kReady;
        next_count = 0;  // pgLevels - minPgLevels - additionalPgLevels
        break;
      case kReq:
        if (c.pte_cache_hit) {
          next_count = static_cast<std::uint8_t>((count_ + 1u) & 3u);
          next_pte_hit = true;
        } else {
          next_state = in.memory.request_ready ? kWait1 : kReq;
        }
        break;
      case kWait1:
        next_state = c.l2_hit ? kReq : kWait2;
        break;
      case kWait2:
        next_state = kWait3;
        if (in.memory.s2_xcpt_ae_ld) {
          next_resp_ae = true;
          next_state = kReady;
          next_resp_valid[r_req_dest_] = true;
        }
        break;
      default:
        break;  // kWait3 handled by the mem_resp override below
    }
    if (c.l2_hit && !c.s2_error) {
      next_state = kReady;
      next_resp_valid[r_req_dest_] = true;
      next_resp_ae = false;
      next_count = 2;
    }
    if (mem_resp_valid_) {
      if (c.traverse) {
        next_state = kReq;
        next_count = static_cast<std::uint8_t>((count_ + 1u) & 3u);
      } else {
        next_l2_refill = c.res_v && !c.invalid_paddr && count_ == 2;
        next_resp_ae = c.res_v && c.invalid_paddr;
        next_state = kReady;
        next_resp_valid[r_req_dest_] = true;
      }
    }
    if (in.memory.s2_nack) next_state = kReq;

    // r_pte priority mux (PTW.scala:372-379)
    std::uint64_t next_r_pte_ppn = r_pte_ppn_;
    std::uint8_t next_r_pte_sw = r_pte_sw_;
    bool next_d = r_pte_d_, next_a = r_pte_a_, next_g = r_pte_g_;
    bool next_u = r_pte_u_, next_x = r_pte_x_, next_w = r_pte_w_;
    bool next_r = r_pte_r_, next_v = r_pte_v_;
    if (mem_resp_valid_) {
      next_r_pte_ppn = c.res_ppn;
      next_r_pte_sw = c.res_sw;
      next_d = c.res_d;
      next_a = c.res_a;
      next_g = c.res_g;
      next_u = c.res_u;
      next_x = c.res_x;
      next_w = c.res_w;
      next_r = c.res_r;
      next_v = c.res_v;
    } else if (c.l2_hit && !c.s2_error) {
      next_r_pte_ppn = c.entry_ppn;
      next_r_pte_sw = 0;
      next_d = c.entry_d;
      next_a = c.entry_a;
      next_g = s2_g_vec_;
      next_u = c.entry_u;
      next_x = c.entry_x;
      next_w = c.entry_w;
      next_r = c.entry_r;
      next_v = true;
    } else if (state_ == kReq && c.pte_cache_hit) {
      // makePTE(pte_cache_data, l2_pte): flags come from the l2 decode
      next_r_pte_ppn = c.pc_hit_data;
      next_r_pte_sw = 0;
      next_d = c.entry_d;
      next_a = c.entry_a;
      next_g = s2_g_vec_;
      next_u = c.entry_u;
      next_x = c.entry_x;
      next_w = c.entry_w;
      next_r = c.entry_r;
      next_v = true;
    } else if (c.arb_fire) {
      // makePTE(ptbr.ppn, r_pte): only the ppn changes
      next_r_pte_ppn = in.ptbr_ppn & UINT64_C(0xfffffffffff);
    }

    // PTE cache insert / touch / sfence clear (pre-edge image)
    std::uint8_t next_pc_valid = pc_valid_;
    if (mem_resp_valid_ && c.traverse && !c.pc_hit && !invalidated_) {
      std::uint8_t way;
      if (pc_valid_ == 0xffu) {
        way = plru_way();
      } else {
        way = 0;
        while ((pc_valid_ >> way) & 1u) ++way;
      }
      next_pc_valid |= static_cast<std::uint8_t>(1u << way);
      pc_tags_[way] = static_cast<std::uint32_t>(c.pte_addr);
      pc_data_[way] = static_cast<std::uint32_t>(c.res_ppn);
    }
    if (c.pc_hit && state_ == kReq) {
      std::uint8_t touched = 0;
      while (!((c.pc_hits >> touched) & 1u)) ++touched;
      plru_touch(touched);
    }
    if (in.sfence_valid && !in.sfence_rs1) next_pc_valid = 0;
    pc_valid_ = next_pc_valid;

    // L2 pipeline registers (reads use the pre-write RAM image)
    const bool s0_ren = c.arb_ready && c.arb_out_valid;
    const bool s0_valid = !l2_refill_ && c.arb_fire;
    const std::uint64_t next_r_1 = s1_valid_ ? l2_ram_[s1_addr_pipe_] : r_1_;
    const bool next_s2_valid = s1_valid_;
    const bool next_s2_valid_vec =
        s1_valid_ ? c.r_valid_vec : s2_valid_vec_;
    const bool next_s2_g_vec = s1_valid_ ? l2_bit(l2_g_, c.r_idx) : s2_g_vec_;
    const std::uint16_t next_s1_addr =
        s0_ren ? static_cast<std::uint16_t>(c.arb_out_addr & 0x1ffu)
               : s1_addr_pipe_;
    const bool next_s1_valid = s0_valid && c.arb_out_bits_valid;

    // Invalidation wins over a concurrent refill, and tests the old global
    // bitmap. In particular an address-specific fence cannot preserve a new
    // refill at some other index on the same edge.
    if (in.sfence_valid) {
      if (in.sfence_rs1) {
        const auto idx=static_cast<std::uint16_t>((in.sfence_address>>12)&0x1ffu);
        l2_bit_set(l2_valid_,idx,false);
      } else if (in.sfence_rs2) {
        for (std::size_t i=0;i<8;++i) l2_valid_[i]&=l2_g_[i];
      } else {
        l2_valid_.fill(0);
      }
    }

    // L2 refill write and valid/g update (uses pre-edge r_pte/r_req)
    if (l2_refill_ && !invalidated_) {
      const std::uint64_t payload =
          (static_cast<std::uint64_t>(c.r_tag) << 26) |
          ((r_pte_ppn_ & UINT64_C(0xfffff)) << 6) |
          (static_cast<std::uint64_t>(r_pte_d_) << 5) |
          (static_cast<std::uint64_t>(r_pte_a_) << 4) |
          (static_cast<std::uint64_t>(r_pte_u_) << 3) |
          (static_cast<std::uint64_t>(r_pte_x_) << 2) |
          (static_cast<std::uint64_t>(r_pte_w_) << 1) |
          static_cast<std::uint64_t>(r_pte_r_);
      l2_ram_[c.r_idx] = (xor_reduce(payload) << 44) | payload;
      if (!in.sfence_valid) l2_bit_set(l2_valid_, c.r_idx, true);
      l2_bit_set(l2_g_, c.r_idx, r_pte_g_);
    }
    if (s2_valid_ && c.s2_error) l2_valid_.fill(0);

    // request capture and the un-gated response latch
    if (c.arb_fire) {
      r_req_addr_ = c.arb_out_addr;
      r_req_dest_ = c.arb_chosen;
    }
    const bool next_mem_resp_valid = in.memory.response.valid;
    const std::uint64_t next_mem_resp_data = in.memory.response.data;

    invalidated_ = in.sfence_valid || (invalidated_ && state_ != kReady);

    // ---- register commit ----
    state_ = next_state;
    count_ = next_count;
    l2_refill_ = next_l2_refill;
    resp_valid_[0] = next_resp_valid[0];
    resp_valid_[1] = next_resp_valid[1];
    resp_valid_[2] = next_resp_valid[2];
    resp_ae_ = next_resp_ae;
    pte_hit_ = next_pte_hit;
    r_pte_ppn_ = next_r_pte_ppn;
    r_pte_sw_ = next_r_pte_sw;
    r_pte_d_ = next_d;
    r_pte_a_ = next_a;
    r_pte_g_ = next_g;
    r_pte_u_ = next_u;
    r_pte_x_ = next_x;
    r_pte_w_ = next_w;
    r_pte_r_ = next_r;
    r_pte_v_ = next_v;
    mem_resp_valid_ = next_mem_resp_valid;
    mem_resp_data_ = next_mem_resp_data;
    r_1_ = next_r_1;
    s1_addr_pipe_ = next_s1_addr;
    s1_valid_ = next_s1_valid;
    s2_valid_ = next_s2_valid;
    s2_valid_vec_ = next_s2_valid_vec;
    s2_g_vec_ = next_s2_g_vec;
    // Reset controls the walker FSM and cache-valid/replacement state.
    // Pipeline payloads, response capture and RAM writes still follow their
    // normal edge behavior; they are not reset storage.
    if (in.reset) { state_=kReady;pc_valid_=0;pc_plru_=0;l2_valid_.fill(0); }
  }

  bool busy() const {
    return state_ != 0 || l2_refill_ || resp_valid_[0] || resp_valid_[1] ||
           resp_valid_[2] || mem_resp_valid_ || s1_valid_ || s2_valid_ ||
           pte_hit_;
  }

  void refresh_oracles() {
    const std::uint64_t m20 = UINT64_C(0xfffff);
    oracles_[0] = count_;
    oracles_[1] = ((pc_data_[0] & m20) << 40) | ((pc_data_[1] & m20) << 20) |
                  (pc_data_[2] & m20);
    oracles_[2] = ((pc_data_[3] & m20) << 40) | ((pc_data_[4] & m20) << 20) |
                  (pc_data_[5] & m20);
    oracles_[3] = ((pc_data_[6] & m20) << 20) | (pc_data_[7] & m20);
    oracles_[4] = mem_resp_data_;
    oracles_[5] = mem_resp_valid_;
    oracles_[6] = r_1_;
    oracles_[7] = r_pte_a_;
    oracles_[8] = r_pte_d_;
    oracles_[9] = r_pte_g_;
    oracles_[10] = r_pte_ppn_;
    oracles_[11] = r_pte_r_;
    oracles_[12] = r_pte_u_;
    oracles_[13] = r_pte_v_;
    oracles_[14] = r_pte_w_;
    oracles_[15] = r_pte_x_;
    oracles_[16] = r_req_addr_;
    oracles_[17] = resp_ae_;
    oracles_[18] = resp_valid_[0];
    oracles_[19] = resp_valid_[1];
    oracles_[20] = s2_valid_;
    oracles_[21] = s2_valid_vec_;
    oracles_[22] = state_;
    oracles_[23] = pc_plru_;
    oracles_[24] = pc_valid_;
    oracles_[25] = s1_addr_pipe_;
    oracles_[26] = l2_refill_;
    oracles_[27] = s1_valid_;
    for (unsigned word=0;word<8;++word) oracles_[28+word]=l2_valid_[word];
  }

  // ---- registers ----
  std::uint8_t state_ = 0;
  std::uint8_t count_ = 0;
  bool l2_refill_ = false;
  bool resp_valid_[3] = {false, false, false};
  bool resp_ae_ = false;
  bool invalidated_ = false;
  bool pte_hit_ = false;
  std::uint32_t r_req_addr_ = 0;
  std::uint8_t r_req_dest_ = 0;
  std::uint64_t r_pte_ppn_ = 0;
  std::uint8_t r_pte_sw_ = 0;
  bool r_pte_d_ = false, r_pte_a_ = false, r_pte_g_ = false;
  bool r_pte_u_ = false, r_pte_x_ = false, r_pte_w_ = false;
  bool r_pte_r_ = false, r_pte_v_ = false;
  bool mem_resp_valid_ = false;
  std::uint64_t mem_resp_data_ = 0;
  std::uint8_t pc_valid_ = 0;
  std::array<std::uint32_t, 8> pc_tags_{};
  std::array<std::uint32_t, 8> pc_data_{};
  std::uint8_t pc_plru_ = 0;
  std::array<std::uint64_t, 512> l2_ram_{};
  std::array<std::uint64_t, 8> l2_valid_{};
  std::array<std::uint64_t, 8> l2_g_{};
  bool s1_valid_ = false, s2_valid_ = false;
  bool s2_valid_vec_ = false, s2_g_vec_ = false;
  std::uint16_t s1_addr_pipe_ = 0;
  std::uint64_t r_1_ = 0;

  PtwOutputs outputs_{};
  PtwOracleState oracles_{};
  PtwInputs last_inputs_{};
  bool active_ = false;
  std::uint8_t drain_cycles_ = 0;
  std::uint64_t eval_count_ = 0;
  std::uint64_t skipped_count_ = 0;
  std::uint64_t evaluate_skipped_count_ = 0;
};

}  // namespace chisa::boom_system::components
