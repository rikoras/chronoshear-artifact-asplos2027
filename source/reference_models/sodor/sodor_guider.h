#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace sodor {

static constexpr uint32_t kStartAddr = 0x80000000u;
static constexpr uint32_t kBubble = 0x00004033u;

enum : uint8_t {
  PC_4 = 0, PC_BRJMP = 1, PC_JALR = 2, PC_EXC = 3,
  BR_N = 0, BR_NE = 1, BR_EQ = 2, BR_GE = 3, BR_GEU = 4,
  BR_LT = 5, BR_LTU = 6, BR_J = 7, BR_JR = 8,
  OP1_RS1 = 0, OP1_PC = 1, OP1_IMZ = 2,
  OP2_RS2 = 0, OP2_ITYPE = 1, OP2_STYPE = 2,
  OP2_SBTYPE = 3, OP2_UTYPE = 4, OP2_UJTYPE = 5,
  ALU_ADD = 0, ALU_SUB = 1, ALU_SLL = 2, ALU_SRL = 3,
  ALU_SRA = 4, ALU_AND = 5, ALU_OR = 6, ALU_XOR = 7,
  ALU_SLT = 8, ALU_SLTU = 9, ALU_COPY_1 = 10, ALU_COPY_2 = 11,
  WB_ALU = 0, WB_MEM = 1, WB_PC4 = 2, WB_CSR = 3,
  M_XRD = 0, M_XWR = 1,
  MT_X = 0, MT_B = 1, MT_H = 2, MT_W = 3, MT_D = 4,
  MT_BU = 5, MT_HU = 6, MT_WU = 7,
  CSR_N = 0, CSR_W = 1, CSR_S = 2, CSR_C = 3,
  CSR_I = 4, CSR_R = 5,
};

struct Inputs {
  bool reset = false;
  bool imem_req_ready = true;
  bool imem_resp_valid = true;
  uint32_t imem_resp_data = 0;
  bool dmem_req_ready = true;
  bool dmem_resp_valid = true;
  uint32_t dmem_resp_data = 0;
  uint32_t rf_rs1_data = 0;
  uint32_t rf_rs2_data = 0;
};

struct Outputs {
  bool imem_req_valid = true;
  uint32_t imem_req_addr = 0;
  uint32_t imem_req_data = 0;
  uint8_t imem_req_fcn = M_XRD;
  uint8_t imem_req_typ = MT_WU;

  bool dmem_req_valid = false;
  uint32_t dmem_req_addr = 0;
  uint32_t dmem_req_data = 0;
  uint8_t dmem_req_fcn = M_XRD;
  uint8_t dmem_req_typ = MT_X;

  uint8_t rf_rs1_addr = 0;
  uint8_t rf_rs2_addr = 0;
  bool rf_wen = false;
  uint8_t rf_waddr = 0;
  uint32_t rf_wdata = 0;
};

struct Decoded {
  bool valid = false;
  uint8_t br_type = BR_N;
  uint8_t op1_sel = OP1_RS1;
  uint8_t op2_sel = OP2_RS2;
  bool rs1_oen = false;
  bool rs2_oen = false;
  uint8_t alu_fun = ALU_ADD;
  uint8_t wb_sel = WB_ALU;
  bool rf_wen = false;
  bool mem_en = false;
  uint8_t mem_fcn = M_XRD;
  uint8_t mem_typ = MT_X;
  uint8_t csr_cmd = CSR_N;
  bool fence_i = false;
};

struct CtlState {
  // Names mirror CtlPath registers.  The duplicated hazard pipeline is real
  // Sodor RTL state, separate from the datapath pipeline.
  bool ifkill_REG = false;
  uint8_t exe_reg_wbaddr = 0;
  uint8_t mem_reg_wbaddr = 0;
  uint8_t wb_reg_wbaddr = 0;
  bool exe_reg_ctrl_rf_wen = false;
  bool mem_reg_ctrl_rf_wen = false;
  bool wb_reg_ctrl_rf_wen = false;
  bool exe_reg_exception = false;
  bool exe_reg_is_csr = false;
  bool exe_inst_is_load = false;
  bool io_ctl_fencei_REG = false;
  bool io_ctl_mem_exception_REG = false;
};

struct CSRState {
  // Only architectural state that can affect the core boundary is modeled
  // semantically.  Counter representation is kept separately from pipeline
  // timing and is not used as an oracle for ordinary RV32I workloads.
  uint8_t prv = 3;
  uint8_t mpp = 3;
  bool mpie = false;
  bool mie = false;
  uint32_t mepc = 0;
  uint32_t mcause = 0;
  uint32_t mtval = 0;
  uint32_t mscratch = 0;
  uint32_t medeleg = 0;
  bool mip_mtip = false;
  bool mip_msip = false;
  bool mie_mtip = false;
  bool mie_msip = false;
  uint32_t dpc = 0;
  uint32_t dscratch = 0;
  bool dcsr_ebreakm = false;
  bool dcsr_step = false;
  uint64_t cycle = 0;
  uint64_t instret = 0;
};

struct DPathState {
  uint32_t if_reg_pc = kStartAddr;

  bool dec_reg_valid = false;
  uint32_t dec_reg_inst = kBubble;
  uint32_t dec_reg_pc = 0;

  bool exe_reg_valid = false;
  uint32_t exe_reg_inst = kBubble;
  uint32_t exe_reg_pc = 0;
  uint8_t exe_reg_wbaddr = 0;
  uint8_t exe_reg_rs1_addr = 0;
  uint8_t exe_reg_rs2_addr = 0;
  uint32_t exe_reg_op1_data = 0;
  uint32_t exe_reg_op2_data = 0;
  uint32_t exe_reg_rs2_data = 0;
  uint8_t exe_reg_ctrl_br_type = BR_N;
  uint8_t exe_reg_ctrl_op2_sel = OP2_RS2;
  uint8_t exe_reg_ctrl_alu_fun = ALU_ADD;
  uint8_t exe_reg_ctrl_wb_sel = WB_ALU;
  bool exe_reg_ctrl_rf_wen = false;
  bool exe_reg_ctrl_mem_val = false;
  uint8_t exe_reg_ctrl_mem_fcn = M_XRD;
  uint8_t exe_reg_ctrl_mem_typ = MT_X;
  uint8_t exe_reg_ctrl_csr_cmd = CSR_N;

  bool mem_reg_valid = false;
  uint32_t mem_reg_pc = 0;
  uint32_t mem_reg_inst = 0;
  uint32_t mem_reg_alu_out = 0;
  uint8_t mem_reg_wbaddr = 0;
  uint8_t mem_reg_rs1_addr = 0;
  uint8_t mem_reg_rs2_addr = 0;
  uint32_t mem_reg_op1_data = 0;
  uint32_t mem_reg_op2_data = 0;
  uint32_t mem_reg_rs2_data = 0;
  bool mem_reg_ctrl_rf_wen = false;
  bool mem_reg_ctrl_mem_val = false;
  uint8_t mem_reg_ctrl_mem_fcn = M_XRD;
  uint8_t mem_reg_ctrl_mem_typ = MT_X;
  uint8_t mem_reg_ctrl_wb_sel = WB_ALU;
  uint8_t mem_reg_ctrl_csr_cmd = CSR_N;

  bool wb_reg_valid = false;
  uint8_t wb_reg_wbaddr = 0;
  uint32_t wb_reg_wbdata = 0;
  bool wb_reg_ctrl_rf_wen = false;
  uint32_t wb_reg_inst = 0;

  CSRState csr;
};

struct CombState {
  Decoded dec;
  bool dec_stall = false;
  bool full_stall = false;
  uint8_t exe_pc_sel = PC_4;
  bool if_kill = false;
  bool dec_kill = false;
  bool pipeline_kill = false;
  bool mem_exception = false;
  uint8_t csr_cmd = CSR_N;
  bool fence_i = false;
  uint32_t exe_alu_out = 0;
  uint32_t mem_wbdata = 0;
  // dec_op1_data/dec_op2_data are copied into adjacent DPathState fields.
  // Keeping them non-adjacent here stops the compiler from merging the two
  // 32-bit copies into one 64-bit load that spans two fresh 32-bit stores,
  // which fails store-to-load forwarding on every cycle.
  uint32_t dec_op1_data = 0;
  uint32_t dec_rs2_data = 0;
  uint32_t dec_op2_data = 0;
  uint32_t csr_rdata = 0;
  uint32_t csr_evec = 0x80000004u;
  bool csr_eret = false;
};

class SodorGuider {
 public:
  SodorGuider();

  static Decoded decode(uint32_t inst);
  CombState comb(const Inputs& in) const;
  Outputs outputs() const;
  // Writes the same boundary values as outputs() straight into `o`, so a
  // caller that keeps a persistent Outputs does not copy a fresh temporary.
  void outputs_into(Outputs& o) const;
  void step(const Inputs& in);

  uint64_t cycle() const { return cycle_; }
  // Monotonic over-approximation of writes to the cold CSR bank.  It may
  // advance when a legal CSR/trap operation rewrites the same value, but it
  // never stays still across a possible cold-state change.  Oracle writers
  // use it only to skip redundant sampling.
  uint64_t csr_epoch() const { return csr_epoch_; }
  const CtlState& ctl() const { return c_; }
  const DPathState& dpath() const { return d_; }
  const std::array<uint64_t, 32>& hpm() const { return hpm_; }

  // Side-effect-free sentinels.  They diagnose model corruption but never
  // feed decisions back into the model.
  std::vector<std::string> sentinel_failures() const;

 private:
  static uint32_t alu(uint32_t a, uint32_t b, uint8_t fn,
                      uint32_t fallback_inst);
  static uint32_t imm_i(uint32_t inst);
  static uint32_t imm_s(uint32_t inst);
  static uint32_t imm_b(uint32_t inst);
  static uint32_t imm_u(uint32_t inst);
  static uint32_t imm_j(uint32_t inst);
  uint32_t csr_read(uint16_t addr) const;
  void csr_step(const Inputs& in, const CombState& cb,
                const DPathState& old_d, CSRState& next);

  CtlState c_{};
  DPathState d_{};
  // These counters are cold: their event inputs are tied to zero in this
  // configuration and only CSR writes change them.  Keep them out of
  // DPathState so the hot next-state path does not copy 256 bytes every cycle.
  std::array<uint64_t, 32> hpm_{};
  uint64_t cycle_ = 0;
  uint64_t csr_epoch_ = 0;
};

}  // namespace sodor
