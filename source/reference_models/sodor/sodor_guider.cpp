#include "sodor_guider.h"

#include <algorithm>
#include <cstdio>

namespace sodor {
namespace {

static inline uint8_t rd(uint32_t i) { return (i >> 7) & 31u; }
static inline uint8_t rs1(uint32_t i) { return (i >> 15) & 31u; }
static inline uint8_t rs2(uint32_t i) { return (i >> 20) & 31u; }
static inline uint8_t funct3(uint32_t i) { return (i >> 12) & 7u; }
static inline uint8_t funct7(uint32_t i) { return (i >> 25) & 0x7fu; }

static Decoded base_alu(uint8_t op2_sel, uint8_t alu_fun) {
  Decoded d;
  d.valid = true;
  d.op1_sel = OP1_RS1;
  d.op2_sel = op2_sel;
  d.rs1_oen = true;
  d.rs2_oen = op2_sel == OP2_RS2;
  d.alu_fun = alu_fun;
  d.wb_sel = WB_ALU;
  d.rf_wen = true;
  return d;
}

static uint32_t csr_rmw(uint8_t cmd, uint32_t rdata, uint32_t wdata) {
  uint32_t base = (cmd == CSR_S || cmd == CSR_C) ? rdata : 0;
  uint32_t clear = cmd == CSR_C ? wdata : 0;
  return (base | wdata) & ~clear;
}

}  // namespace

SodorGuider::SodorGuider() = default;

Decoded SodorGuider::decode(uint32_t inst) {
  const uint8_t opc = inst & 0x7f;
  const uint8_t f3 = funct3(inst);
  const uint8_t f7 = funct7(inst);
  Decoded d;

  switch (opc) {
    case 0x03: {  // loads
      uint8_t typ;
      switch (f3) {
        case 0: typ = MT_B; break;
        case 1: typ = MT_H; break;
        case 2: typ = MT_W; break;
        case 4: typ = MT_BU; break;
        case 5: typ = MT_HU; break;
        default: return d;
      }
      d = base_alu(OP2_ITYPE, ALU_ADD);
      d.rs2_oen = false;
      d.wb_sel = WB_MEM;
      d.mem_en = true;
      d.mem_fcn = M_XRD;
      d.mem_typ = typ;
      return d;
    }
    case 0x23: {  // stores
      uint8_t typ;
      switch (f3) {
        case 0: typ = MT_B; break;
        case 1: typ = MT_H; break;
        case 2: typ = MT_W; break;
        default: return d;
      }
      d = base_alu(OP2_STYPE, ALU_ADD);
      d.rs2_oen = true;
      d.rf_wen = false;
      d.mem_en = true;
      d.mem_fcn = M_XWR;
      d.mem_typ = typ;
      return d;
    }
    case 0x17:  // AUIPC
      d = base_alu(OP2_UTYPE, ALU_ADD);
      d.op1_sel = OP1_PC;
      d.rs1_oen = false;
      d.rs2_oen = false;
      return d;
    case 0x37:  // LUI
      d = base_alu(OP2_UTYPE, ALU_COPY_2);
      d.rs1_oen = false;
      d.rs2_oen = false;
      return d;
    case 0x13: {  // OP-IMM
      uint8_t fn;
      switch (f3) {
        case 0: fn = ALU_ADD; break;
        case 2: fn = ALU_SLT; break;
        case 3: fn = ALU_SLTU; break;
        case 4: fn = ALU_XOR; break;
        case 6: fn = ALU_OR; break;
        case 7: fn = ALU_AND; break;
        case 1:
          if (f7 != 0x00) return d;
          fn = ALU_SLL;
          break;
        case 5:
          if (f7 == 0x00) fn = ALU_SRL;
          else if (f7 == 0x20) fn = ALU_SRA;
          else return d;
          break;
        default: return d;
      }
      d = base_alu(OP2_ITYPE, fn);
      d.rs2_oen = false;
      return d;
    }
    case 0x33: {  // OP
      uint8_t fn;
      if (f7 == 0x20 && f3 == 0) fn = ALU_SUB;
      else if (f7 == 0x20 && f3 == 5) fn = ALU_SRA;
      else if (f7 != 0x00) return d;
      else {
        switch (f3) {
          case 0: fn = ALU_ADD; break;
          case 1: fn = ALU_SLL; break;
          case 2: fn = ALU_SLT; break;
          case 3: fn = ALU_SLTU; break;
          case 4: fn = ALU_XOR; break;
          case 5: fn = ALU_SRL; break;
          case 6: fn = ALU_OR; break;
          case 7: fn = ALU_AND; break;
          default: return d;
        }
      }
      return base_alu(OP2_RS2, fn);
    }
    case 0x6f:  // JAL
      d.valid = true;
      d.br_type = BR_J;
      d.op1_sel = OP1_RS1;
      d.op2_sel = OP2_UJTYPE;
      d.wb_sel = WB_PC4;
      d.rf_wen = true;
      return d;
    case 0x67:  // JALR
      if (f3 != 0) return d;
      d.valid = true;
      d.br_type = BR_JR;
      d.op1_sel = OP1_RS1;
      d.op2_sel = OP2_ITYPE;
      d.rs1_oen = true;
      d.wb_sel = WB_PC4;
      d.rf_wen = true;
      return d;
    case 0x63: {  // branches
      uint8_t br;
      switch (f3) {
        case 0: br = BR_EQ; break;
        case 1: br = BR_NE; break;
        case 4: br = BR_LT; break;
        case 5: br = BR_GE; break;
        case 6: br = BR_LTU; break;
        case 7: br = BR_GEU; break;
        default: return d;
      }
      d.valid = true;
      d.br_type = br;
      d.op1_sel = OP1_RS1;
      d.op2_sel = OP2_SBTYPE;
      d.rs1_oen = true;
      d.rs2_oen = true;
      return d;
    }
    case 0x73: {  // system / CSR
      if (inst == 0x00000073u || inst == 0x00100073u ||
          inst == 0x30200073u || inst == 0x7b200073u) {
        d.valid = true;
        d.csr_cmd = CSR_I;
        return d;
      }
      if (inst == 0x10500073u) {  // WFI is a NOP in this Sodor
        d.valid = true;
        return d;
      }
      uint8_t cmd;
      switch (f3) {
        case 1: case 5: cmd = CSR_W; break;
        case 2: case 6: cmd = CSR_S; break;
        case 3: case 7: cmd = CSR_C; break;
        default: return d;
      }
      d.valid = true;
      d.op1_sel = f3 >= 5 ? OP1_IMZ : OP1_RS1;
      d.rs1_oen = true;
      d.rs2_oen = true;
      d.alu_fun = ALU_COPY_1;
      d.wb_sel = WB_CSR;
      d.rf_wen = true;
      d.csr_cmd = cmd;
      return d;
    }
    case 0x0f:
      if (f3 == 0 || f3 == 1) {
        d.valid = true;
        d.fence_i = f3 == 1;
        d.mem_en = f3 == 0;
      }
      return d;
    default:
      return d;
  }
}

uint32_t SodorGuider::imm_i(uint32_t inst) {
  return static_cast<uint32_t>(static_cast<int32_t>(inst) >> 20);
}

uint32_t SodorGuider::imm_s(uint32_t inst) {
  uint32_t x = ((inst >> 25) << 5) | ((inst >> 7) & 0x1f);
  if (x & 0x800) x |= 0xfffff000u;
  return x;
}

uint32_t SodorGuider::imm_b(uint32_t inst) {
  uint32_t x = ((inst >> 31) << 12) |
               (((inst >> 7) & 1) << 11) |
               (((inst >> 25) & 0x3f) << 5) |
               (((inst >> 8) & 0xf) << 1);
  if (x & 0x1000) x |= 0xffffe000u;
  return x;
}

uint32_t SodorGuider::imm_u(uint32_t inst) { return inst & 0xfffff000u; }

uint32_t SodorGuider::imm_j(uint32_t inst) {
  uint32_t x = ((inst >> 31) << 20) |
               (((inst >> 12) & 0xff) << 12) |
               (((inst >> 20) & 1) << 11) |
               (((inst >> 21) & 0x3ff) << 1);
  if (x & 0x100000) x |= 0xffe00000u;
  return x;
}

uint32_t SodorGuider::alu(uint32_t a, uint32_t b, uint8_t fn,
                          uint32_t fallback_inst) {
  switch (fn) {
    case ALU_ADD: return a + b;
    case ALU_SUB: return a - b;
    case ALU_SLL: return a << (b & 31);
    case ALU_SRL: return a >> (b & 31);
    case ALU_SRA: return static_cast<uint32_t>(static_cast<int32_t>(a) >> (b & 31));
    case ALU_AND: return a & b;
    case ALU_OR: return a | b;
    case ALU_XOR: return a ^ b;
    case ALU_SLT: return static_cast<int32_t>(a) < static_cast<int32_t>(b);
    case ALU_SLTU: return a < b;
    case ALU_COPY_1: return a;
    case ALU_COPY_2: return b;
    default: return fallback_inst;
  }
}

uint32_t SodorGuider::csr_read(uint16_t addr) const {
  const auto& s = d_.csr;
  if (addr >= 0xb03 && addr < 0xb03 + hpm_.size())
    return static_cast<uint32_t>(hpm_[addr - 0xb03]);
  // This Sodor's read map aliases the high-half addresses to the same raw
  // WideCounter value, which is then truncated to XLEN by the CSR read port.
  if (addr >= 0xb83 && addr < 0xb83 + hpm_.size())
    return static_cast<uint32_t>(hpm_[addr - 0xb83]);
  switch (addr) {
    case 0x300:
      return (static_cast<uint32_t>(s.mpp & 3) << 11) |
             (static_cast<uint32_t>(s.mpie) << 7) |
             (static_cast<uint32_t>(s.mie) << 3);
    case 0xb00: return static_cast<uint32_t>(s.cycle);
    case 0xb80: return 0;
    case 0xb02: return static_cast<uint32_t>(s.instret);
    case 0xb82: return 0;
    case 0x301: return 1u << ('I' - 'A');
    case 0x305: return 0x100;
    case 0x340: return s.mscratch;
    case 0x341: return s.mepc;
    case 0x342: return s.mcause;
    case 0x343: return s.mtval;
    case 0x302: return s.medeleg;
    case 0x304:
      return (static_cast<uint32_t>(s.mie_mtip) << 7) |
             (static_cast<uint32_t>(s.mie_msip) << 3);
    case 0x344:
      return (static_cast<uint32_t>(s.mip_mtip) << 7) |
             (static_cast<uint32_t>(s.mip_msip) << 3);
    case 0x7b0:
      return (1u << 30) |
             (static_cast<uint32_t>(s.dcsr_ebreakm) << 15) |
             (static_cast<uint32_t>(s.dcsr_step) << 2) | 3u;
    case 0x7b1: return s.dpc;
    case 0x7b2: return s.dscratch;
    case 0xf13: return 0x8000;
    default: return 0;
  }
}

CombState SodorGuider::comb(const Inputs& in) const {
  CombState cb;
  cb.dec = decode(d_.dec_reg_inst);

  cb.mem_exception = c_.io_ctl_mem_exception_REG;

  const bool system_insn = d_.mem_reg_ctrl_csr_cmd == CSR_I;
  const uint16_t csr_addr = d_.mem_reg_inst >> 20;
  const uint8_t sys_bit = csr_addr & 7;
  cb.csr_eret = system_insn && (sys_bit == 0 || sys_bit == 1 || sys_bit == 2);
  cb.csr_evec = 0x80000004u;
  if (system_insn && sys_bit == 2) {
    cb.csr_evec = (csr_addr & (1u << 10)) ? d_.csr.dpc : d_.csr.mepc;
  }
  cb.pipeline_kill = cb.csr_eret || cb.mem_exception;

  const bool br_eq = d_.exe_reg_op1_data == d_.exe_reg_rs2_data;
  const bool br_lt = static_cast<int32_t>(d_.exe_reg_op1_data) <
                     static_cast<int32_t>(d_.exe_reg_rs2_data);
  const bool br_ltu = d_.exe_reg_op1_data < d_.exe_reg_rs2_data;
  if (cb.pipeline_kill) cb.exe_pc_sel = PC_EXC;
  else {
    switch (d_.exe_reg_ctrl_br_type) {
      case BR_NE: cb.exe_pc_sel = !br_eq ? PC_BRJMP : PC_4; break;
      case BR_EQ: cb.exe_pc_sel = br_eq ? PC_BRJMP : PC_4; break;
      case BR_GE: cb.exe_pc_sel = !br_lt ? PC_BRJMP : PC_4; break;
      case BR_GEU: cb.exe_pc_sel = !br_ltu ? PC_BRJMP : PC_4; break;
      case BR_LT: cb.exe_pc_sel = br_lt ? PC_BRJMP : PC_4; break;
      case BR_LTU: cb.exe_pc_sel = br_ltu ? PC_BRJMP : PC_4; break;
      case BR_J: cb.exe_pc_sel = PC_BRJMP; break;
      case BR_JR: cb.exe_pc_sel = PC_JALR; break;
      default: cb.exe_pc_sel = PC_4; break;
    }
  }
  cb.dec_kill = cb.exe_pc_sel != PC_4;
  cb.if_kill = cb.dec_kill || !in.imem_resp_valid ||
               cb.dec.fence_i || c_.ifkill_REG;

  cb.full_stall = !in.imem_resp_valid ||
                  (d_.mem_reg_ctrl_mem_val && !in.dmem_resp_valid);
  const bool dec_rs1_oen = !cb.dec_kill && cb.dec.rs1_oen;
  const bool dec_rs2_oen = !cb.dec_kill && cb.dec.rs2_oen;
  cb.dec_stall = c_.exe_reg_is_csr ||
      (c_.exe_inst_is_load && c_.exe_reg_wbaddr != 0 &&
       ((dec_rs1_oen && c_.exe_reg_wbaddr == rs1(d_.dec_reg_inst)) ||
        (dec_rs2_oen && c_.exe_reg_wbaddr == rs2(d_.dec_reg_inst))));
  cb.fence_i = cb.dec.fence_i || c_.io_ctl_fencei_REG;
  cb.csr_cmd = ((cb.dec.csr_cmd == CSR_S || cb.dec.csr_cmd == CSR_C) &&
                rs1(d_.dec_reg_inst) == 0) ? CSR_R : cb.dec.csr_cmd;

  cb.exe_alu_out = alu(d_.exe_reg_op1_data, d_.exe_reg_op2_data,
                       d_.exe_reg_ctrl_alu_fun, d_.exe_reg_inst);
  cb.csr_rdata = csr_read(csr_addr);
  switch (d_.mem_reg_ctrl_wb_sel) {
    case WB_MEM: cb.mem_wbdata = in.dmem_resp_data; break;
    case WB_CSR: cb.mem_wbdata = cb.csr_rdata; break;
    default: cb.mem_wbdata = d_.mem_reg_alu_out; break;
  }

  uint32_t dec_alu_op2 = 0;
  switch (cb.dec.op2_sel) {
    case OP2_RS2: dec_alu_op2 = in.rf_rs2_data; break;
    case OP2_ITYPE: dec_alu_op2 = imm_i(d_.dec_reg_inst); break;
    case OP2_STYPE: dec_alu_op2 = imm_s(d_.dec_reg_inst); break;
    case OP2_SBTYPE: dec_alu_op2 = imm_b(d_.dec_reg_inst); break;
    case OP2_UTYPE: dec_alu_op2 = imm_u(d_.dec_reg_inst); break;
    case OP2_UJTYPE: dec_alu_op2 = imm_j(d_.dec_reg_inst); break;
    default: dec_alu_op2 = 0; break;
  }

  const uint8_t r1 = rs1(d_.dec_reg_inst);
  const uint8_t r2 = rs2(d_.dec_reg_inst);
  if (cb.dec.op1_sel == OP1_IMZ) cb.dec_op1_data = r1;
  else if (cb.dec.op1_sel == OP1_PC) cb.dec_op1_data = d_.dec_reg_pc;
  else if (r1 != 0 && d_.exe_reg_ctrl_rf_wen && d_.exe_reg_wbaddr == r1)
    cb.dec_op1_data = cb.exe_alu_out;
  else if (r1 != 0 && d_.mem_reg_ctrl_rf_wen && d_.mem_reg_wbaddr == r1)
    cb.dec_op1_data = cb.mem_wbdata;
  else if (r1 != 0 && d_.wb_reg_ctrl_rf_wen && d_.wb_reg_wbaddr == r1)
    cb.dec_op1_data = d_.wb_reg_wbdata;
  else cb.dec_op1_data = in.rf_rs1_data;

  if (cb.dec.op2_sel == OP2_RS2 && r2 != 0 &&
      d_.exe_reg_ctrl_rf_wen && d_.exe_reg_wbaddr == r2)
    cb.dec_op2_data = cb.exe_alu_out;
  else if (cb.dec.op2_sel == OP2_RS2 && r2 != 0 &&
           d_.mem_reg_ctrl_rf_wen && d_.mem_reg_wbaddr == r2)
    cb.dec_op2_data = cb.mem_wbdata;
  else if (cb.dec.op2_sel == OP2_RS2 && r2 != 0 &&
           d_.wb_reg_ctrl_rf_wen && d_.wb_reg_wbaddr == r2)
    cb.dec_op2_data = d_.wb_reg_wbdata;
  else cb.dec_op2_data = dec_alu_op2;

  if (r2 != 0 && d_.exe_reg_ctrl_rf_wen && d_.exe_reg_wbaddr == r2)
    cb.dec_rs2_data = cb.exe_alu_out;
  else if (r2 != 0 && d_.mem_reg_ctrl_rf_wen && d_.mem_reg_wbaddr == r2)
    cb.dec_rs2_data = cb.mem_wbdata;
  else if (r2 != 0 && d_.wb_reg_ctrl_rf_wen && d_.wb_reg_wbaddr == r2)
    cb.dec_rs2_data = d_.wb_reg_wbdata;
  else cb.dec_rs2_data = in.rf_rs2_data;

  return cb;
}

Outputs SodorGuider::outputs() const {
  Outputs o;
  outputs_into(o);
  return o;
}

void SodorGuider::outputs_into(Outputs& o) const {
  o.imem_req_valid = true;
  o.imem_req_data = 0;
  o.imem_req_fcn = M_XRD;
  o.imem_req_typ = MT_WU;
  o.imem_req_addr = d_.if_reg_pc;
  o.dmem_req_valid = d_.mem_reg_ctrl_mem_val;
  o.dmem_req_addr = d_.mem_reg_alu_out;
  o.dmem_req_data = d_.mem_reg_rs2_data;
  o.dmem_req_fcn = d_.mem_reg_ctrl_mem_fcn;
  o.dmem_req_typ = d_.mem_reg_ctrl_mem_typ;
  o.rf_rs1_addr = rs1(d_.dec_reg_inst);
  o.rf_rs2_addr = rs2(d_.dec_reg_inst);
  o.rf_wen = d_.wb_reg_ctrl_rf_wen;
  o.rf_waddr = d_.wb_reg_wbaddr;
  o.rf_wdata = d_.wb_reg_wbdata;
}

void SodorGuider::csr_step(const Inputs& in, const CombState& cb,
                           const DPathState& old_d, CSRState& next) {
  if (in.reset) {
    next = CSRState{};
    next.prv = 3;
    next.mpp = 3;
  } else {
    next.cycle = old_d.csr.cycle + 1;
    next.instret = old_d.csr.instret + (old_d.wb_reg_valid ? 1 : 0);
  }

  const bool system = old_d.mem_reg_ctrl_csr_cmd == CSR_I;
  const uint16_t addr = old_d.mem_reg_inst >> 20;
  const uint8_t sys_bit = addr & 7;
  const bool call = system && sys_bit == 0;
  const bool brk = system && sys_bit == 1;
  const bool ret = system && sys_bit == 2;
  const uint8_t cmd = old_d.mem_reg_ctrl_csr_cmd;
  const bool csr_write = cmd != CSR_N && cmd != CSR_I && cmd != CSR_R;
  if (in.reset || cb.mem_exception || call || brk || ret || csr_write)
    ++csr_epoch_;

  if (!in.reset) {
    if (cb.mem_exception) next.mcause = 2;
    if (call) next.mcause = old_d.csr.prv + 8;
    if (brk) next.mcause = 3;
    if (cb.mem_exception || call || brk) next.mepc = old_d.mem_reg_pc;
    if (ret && !(addr & (1u << 10))) {
      next.mie = old_d.csr.mpie;
      next.mpie = true;
      next.prv = old_d.csr.mpp;
    }

    if (csr_write) {
      const uint32_t w = csr_rmw(cmd, csr_read(addr), old_d.mem_reg_alu_out);
      switch (addr) {
        case 0x300:
          next.mpie = (w >> 7) & 1;
          next.mie = (w >> 3) & 1;
          break;
        case 0xb00: next.cycle = (old_d.csr.cycle & 0xffffffff00000000ULL) | w; break;
        case 0xb80: next.cycle = (old_d.csr.cycle & 0xffffffffULL) |
                                (static_cast<uint64_t>(w) << 32); break;
        case 0xb02: next.instret = (old_d.csr.instret & 0xffffffff00000000ULL) | w; break;
        case 0xb82: next.instret = (old_d.csr.instret & 0xffffffffULL) |
                                  (static_cast<uint64_t>(w) << 32); break;
        case 0x304:
          next.mie_msip = (w >> 3) & 1;
          next.mie_mtip = (w >> 7) & 1;
          break;
        case 0x344: next.mip_msip = (w >> 3) & 1; break;
        case 0x340: next.mscratch = w; break;
        case 0x341: next.mepc = w & ~3u; break;
        case 0x342: next.mcause = w & 0x8000001fu; break;
        case 0x343: next.mtval = w; break;
        case 0x302: next.medeleg = w; break;
        case 0x7b0:
          next.dcsr_step = (w >> 2) & 1;
          next.dcsr_ebreakm = (w >> 15) & 1;
          break;
        case 0x7b1: next.dpc = w; break;
        case 0x7b2: next.dscratch = w; break;
        default:
          if (addr >= 0xb03 && addr < 0xb03 + hpm_.size()) {
            const auto index = addr - 0xb03;
            hpm_[index] = ((hpm_[index] >> 32) << 32) | w;
            hpm_[index] &= 0xffffffffffULL;
          } else if (addr >= 0xb83 &&
                     addr < 0xb83 + hpm_.size()) {
            const auto index = addr - 0xb83;
            hpm_[index] =
                (static_cast<uint64_t>(w & 0xff) << 32) |
                (hpm_[index] & 0xffffffffULL);
          }
          break;
      }
    }
  }
}

void SodorGuider::step(const Inputs& in) {
  const CtlState old_c = c_;
  const DPathState& old_d = d_;
  const CombState cb = comb(in);

  // old_c is a complete copy, so the control registers can be updated in
  // place: comb() has already read them, and a stack temporary that is
  // written byte by byte and then copied back as a whole stalls on
  // store-to-load forwarding every cycle.
  CtlState& nc = c_;
  nc.ifkill_REG = cb.dec.fence_i;
  nc.io_ctl_fencei_REG = cb.dec.fence_i;
  nc.io_ctl_mem_exception_REG = old_c.exe_reg_exception;
  nc.mem_reg_wbaddr = old_c.exe_reg_wbaddr;
  nc.wb_reg_wbaddr = old_c.mem_reg_wbaddr;
  nc.mem_reg_ctrl_rf_wen = old_c.exe_reg_ctrl_rf_wen;
  nc.wb_reg_ctrl_rf_wen = old_c.mem_reg_ctrl_rf_wen;

  if (!cb.dec_stall && !cb.full_stall) {
    if (cb.dec_kill) {
      nc.exe_reg_wbaddr = 0;
      nc.exe_reg_ctrl_rf_wen = false;
      nc.exe_reg_is_csr = false;
      nc.exe_reg_exception = false;
    } else {
      nc.exe_reg_wbaddr = rd(old_d.dec_reg_inst);
      nc.exe_reg_ctrl_rf_wen = cb.dec.rf_wen;
      nc.exe_reg_is_csr = cb.dec.csr_cmd != CSR_N && cb.dec.csr_cmd != CSR_I;
      nc.exe_reg_exception = !cb.dec.valid && in.imem_resp_valid;
    }
  } else if (cb.dec_stall && !cb.full_stall) {
    nc.exe_reg_wbaddr = 0;
    nc.exe_reg_ctrl_rf_wen = false;
    nc.exe_reg_is_csr = false;
    nc.exe_reg_exception = false;
  }
  if (!cb.full_stall)
    nc.exe_inst_is_load = cb.dec.mem_en && cb.dec.mem_fcn == M_XRD;

  // Compute all cross-stage decisions before updating state.  Updating the
  // stages from writeback toward fetch keeps every source stage at its PRE
  // value until its consumer has sampled it, without copying DPathState.
  // Ordinary instructions and CSR reads change only the two counters.
  // Sample retirement before writeback advances; traps, writes and reset
  // retain the complete CSR update path and its epoch accounting.
  if (!in.reset && !cb.mem_exception &&
      (old_d.mem_reg_ctrl_csr_cmd == CSR_N ||
       old_d.mem_reg_ctrl_csr_cmd == CSR_R)) {
    ++d_.csr.cycle;
    d_.csr.instret += old_d.wb_reg_valid ? 1 : 0;
  } else {
    CSRState next_csr = old_d.csr;
    csr_step(in, cb, old_d, next_csr);
    d_.csr = next_csr;
  }
  DPathState& nd = d_;
  uint32_t if_pc_next;
  switch (cb.exe_pc_sel) {
    case PC_BRJMP: if_pc_next = old_d.exe_reg_pc + old_d.exe_reg_op2_data; break;
    case PC_JALR: if_pc_next = old_d.exe_reg_op1_data + old_d.exe_reg_op2_data; break;
    case PC_EXC: if_pc_next = cb.csr_evec; break;
    default: if_pc_next = old_d.if_reg_pc + 4; break;
  }
  if (cb.fence_i && cb.exe_pc_sel == PC_4 && !cb.dec_stall &&
      !cb.full_stall && !cb.pipeline_kill)
    if_pc_next = old_d.if_reg_pc;

  if (!cb.full_stall) {
    nd.wb_reg_valid = old_d.mem_reg_valid && !cb.mem_exception;
    nd.wb_reg_wbaddr = old_d.mem_reg_wbaddr;
    nd.wb_reg_wbdata = cb.mem_wbdata;
    nd.wb_reg_ctrl_rf_wen = cb.mem_exception ? false : old_d.mem_reg_ctrl_rf_wen;
  } else {
    nd.wb_reg_valid = false;
    nd.wb_reg_ctrl_rf_wen = false;
  }
  nd.wb_reg_inst = old_d.mem_reg_inst;

  if (cb.pipeline_kill) {
    nd.mem_reg_valid = false;
    nd.mem_reg_inst = kBubble;
    nd.mem_reg_ctrl_rf_wen = false;
    nd.mem_reg_ctrl_mem_val = false;
    nd.mem_reg_ctrl_csr_cmd = CSR_N;
  } else if (!cb.full_stall) {
    nd.mem_reg_valid = old_d.exe_reg_valid;
    nd.mem_reg_pc = old_d.exe_reg_pc;
    nd.mem_reg_inst = old_d.exe_reg_inst;
    nd.mem_reg_alu_out = old_d.exe_reg_ctrl_wb_sel == WB_PC4
                           ? old_d.exe_reg_pc + 4 : cb.exe_alu_out;
    nd.mem_reg_wbaddr = old_d.exe_reg_wbaddr;
    nd.mem_reg_rs1_addr = old_d.exe_reg_rs1_addr;
    nd.mem_reg_rs2_addr = old_d.exe_reg_rs2_addr;
    nd.mem_reg_op1_data = old_d.exe_reg_op1_data;
    nd.mem_reg_op2_data = old_d.exe_reg_op2_data;
    nd.mem_reg_rs2_data = old_d.exe_reg_rs2_data;
    nd.mem_reg_ctrl_rf_wen = old_d.exe_reg_ctrl_rf_wen;
    nd.mem_reg_ctrl_mem_val = old_d.exe_reg_ctrl_mem_val;
    nd.mem_reg_ctrl_mem_fcn = old_d.exe_reg_ctrl_mem_fcn;
    nd.mem_reg_ctrl_mem_typ = old_d.exe_reg_ctrl_mem_typ;
    nd.mem_reg_ctrl_wb_sel = old_d.exe_reg_ctrl_wb_sel;
    nd.mem_reg_ctrl_csr_cmd = old_d.exe_reg_ctrl_csr_cmd;
  }

  if ((cb.dec_stall && !cb.full_stall) || cb.pipeline_kill) {
    nd.exe_reg_valid = false;
    nd.exe_reg_inst = kBubble;
    nd.exe_reg_wbaddr = 0;
    nd.exe_reg_ctrl_rf_wen = false;
    nd.exe_reg_ctrl_mem_val = false;
    nd.exe_reg_ctrl_mem_fcn = M_XRD;
    nd.exe_reg_ctrl_csr_cmd = CSR_N;
    nd.exe_reg_ctrl_br_type = BR_N;
  } else if (!cb.dec_stall && !cb.full_stall) {
    nd.exe_reg_pc = old_d.dec_reg_pc;
    nd.exe_reg_rs1_addr = rs1(old_d.dec_reg_inst);
    nd.exe_reg_rs2_addr = rs2(old_d.dec_reg_inst);
    nd.exe_reg_op1_data = cb.dec_op1_data;
    nd.exe_reg_op2_data = cb.dec_op2_data;
    nd.exe_reg_rs2_data = cb.dec_rs2_data;
    nd.exe_reg_ctrl_op2_sel = cb.dec.op2_sel;
    nd.exe_reg_ctrl_alu_fun = cb.dec.alu_fun;
    nd.exe_reg_ctrl_wb_sel = cb.dec.wb_sel;
    if (cb.dec_kill) {
      nd.exe_reg_valid = false;
      nd.exe_reg_inst = kBubble;
      nd.exe_reg_wbaddr = 0;
      nd.exe_reg_ctrl_rf_wen = false;
      nd.exe_reg_ctrl_mem_val = false;
      nd.exe_reg_ctrl_mem_fcn = M_XRD;
      nd.exe_reg_ctrl_csr_cmd = CSR_N;
      nd.exe_reg_ctrl_br_type = BR_N;
    } else {
      nd.exe_reg_valid = old_d.dec_reg_valid;
      nd.exe_reg_inst = old_d.dec_reg_inst;
      nd.exe_reg_wbaddr = rd(old_d.dec_reg_inst);
      nd.exe_reg_ctrl_rf_wen = cb.dec.rf_wen;
      nd.exe_reg_ctrl_mem_val = cb.dec.mem_en;
      nd.exe_reg_ctrl_mem_fcn = cb.dec.mem_fcn;
      nd.exe_reg_ctrl_mem_typ = cb.dec.mem_typ;
      nd.exe_reg_ctrl_csr_cmd = cb.csr_cmd;
      nd.exe_reg_ctrl_br_type = cb.dec.br_type;
    }
  }

  if (cb.pipeline_kill) {
    nd.dec_reg_valid = false;
    nd.dec_reg_inst = kBubble;
  } else if (!cb.dec_stall && !cb.full_stall) {
    nd.dec_reg_valid = !cb.if_kill;
    nd.dec_reg_inst = cb.if_kill ? kBubble : in.imem_resp_data;
    nd.dec_reg_pc = old_d.if_reg_pc;
  }

  if ((!cb.dec_stall && !cb.full_stall) || cb.pipeline_kill)
    nd.if_reg_pc = if_pc_next;

  if (in.reset) {
    nd.if_reg_pc = kStartAddr;
    nd.dec_reg_valid = false;
    nd.dec_reg_inst = kBubble;
    nd.dec_reg_pc = 0;
    nd.exe_reg_valid = false;
    nd.exe_reg_inst = kBubble;
    nd.exe_reg_ctrl_br_type = BR_N;
    nd.exe_reg_ctrl_rf_wen = false;
    nd.exe_reg_ctrl_mem_val = false;
    nd.exe_reg_ctrl_mem_fcn = M_XRD;
    nd.exe_reg_ctrl_mem_typ = MT_X;
    nd.exe_reg_ctrl_csr_cmd = CSR_N;
    nd.mem_reg_valid = false;
    nd.mem_reg_ctrl_rf_wen = false;
    nd.mem_reg_ctrl_mem_val = false;
    nd.mem_reg_ctrl_mem_fcn = M_XRD;
    nd.mem_reg_ctrl_mem_typ = MT_X;
    nd.mem_reg_ctrl_csr_cmd = CSR_N;
    nd.wb_reg_valid = false;
    nd.wb_reg_ctrl_rf_wen = false;

    nc.exe_reg_ctrl_rf_wen = false;
    nc.mem_reg_ctrl_rf_wen = false;
    nc.wb_reg_ctrl_rf_wen = false;
    nc.exe_reg_exception = false;
    nc.exe_reg_is_csr = false;
    nc.exe_inst_is_load = false;
  }

  ++cycle_;
}

std::vector<std::string> SodorGuider::sentinel_failures() const {
  std::vector<std::string> out;
  if (d_.if_reg_pc & 3u) out.emplace_back("fetch PC is not 4-byte aligned");
  if (d_.exe_reg_ctrl_br_type > BR_JR)
    out.emplace_back("execute branch type is out of range");
  if (d_.exe_reg_ctrl_alu_fun > ALU_COPY_2)
    out.emplace_back("execute ALU function is out of range");
  const bool mem_is_fence = (d_.mem_reg_inst & 0x707f) == 0x000f;
  if (d_.mem_reg_ctrl_mem_val && !mem_is_fence &&
      !(d_.mem_reg_ctrl_mem_typ == MT_B || d_.mem_reg_ctrl_mem_typ == MT_H ||
        d_.mem_reg_ctrl_mem_typ == MT_W || d_.mem_reg_ctrl_mem_typ == MT_BU ||
        d_.mem_reg_ctrl_mem_typ == MT_HU))
    out.emplace_back("active data-memory request has an unsupported type");
  if (c_.exe_reg_ctrl_rf_wen != d_.exe_reg_ctrl_rf_wen ||
      c_.exe_reg_wbaddr != d_.exe_reg_wbaddr)
    out.emplace_back("control/datapath execute hazard shadows diverged");
  return out;
}

}  // namespace sodor
