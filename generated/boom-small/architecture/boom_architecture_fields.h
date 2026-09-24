#pragma once
inline constexpr unsigned kCommit = 1, kInteger = 52, kFloating = 48, kFtq = 16, kStores = 8;
struct RtlFields {
  VTestHarness___024root& root;
  auto& valid0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_arch_valids_0; }
  auto& commit0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_valids_0; }
  auto& enq0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_enq_valids_0; }
  auto& rd0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_ldst; }
  auto& rdvalid0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_ldst_val; }
  auto& rdtype0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_dst_rtype; }
  auto& pdst0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_pdst; }
  auto& ftq0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_ftq_idx; }
  auto& pclow0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_pc_lob; }
  auto& edge0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_edge_inst; }
  auto& store0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_0_uses_stq; }
  auto& rob_head() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_head; }
  auto& rob_tail() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_tail; }
  auto& debug() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_debug; }
  auto& core_clock() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_clock; }
  auto& store_head() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_commit_head; }
  auto& ftqpc0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_0; }
  auto& ftqpc1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_1; }
  auto& ftqpc2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_2; }
  auto& ftqpc3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_3; }
  auto& ftqpc4() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_4; }
  auto& ftqpc5() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_5; }
  auto& ftqpc6() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_6; }
  auto& ftqpc7() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_7; }
  auto& ftqpc8() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_8; }
  auto& ftqpc9() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_9; }
  auto& ftqpc10() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_10; }
  auto& ftqpc11() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_11; }
  auto& ftqpc12() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_12; }
  auto& ftqpc13() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_13; }
  auto& ftqpc14() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_14; }
  auto& ftqpc15() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_15; }
  auto& stqaddress0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_addr_bits; }
  auto& stqdata0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_data_bits; }
  auto& stqcommand0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_uop_mem_cmd; }
  auto& stqsize0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_uop_mem_size; }
  auto& stqaddress1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_addr_bits; }
  auto& stqdata1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_data_bits; }
  auto& stqcommand1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_mem_cmd; }
  auto& stqsize1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_mem_size; }
  auto& stqaddress2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_addr_bits; }
  auto& stqdata2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_data_bits; }
  auto& stqcommand2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_mem_cmd; }
  auto& stqsize2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_mem_size; }
  auto& stqaddress3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_addr_bits; }
  auto& stqdata3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_data_bits; }
  auto& stqcommand3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_uop_mem_cmd; }
  auto& stqsize3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_uop_mem_size; }
  auto& stqaddress4() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_addr_bits; }
  auto& stqdata4() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_data_bits; }
  auto& stqcommand4() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_uop_mem_cmd; }
  auto& stqsize4() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_uop_mem_size; }
  auto& stqaddress5() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_addr_bits; }
  auto& stqdata5() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_data_bits; }
  auto& stqcommand5() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_uop_mem_cmd; }
  auto& stqsize5() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_uop_mem_size; }
  auto& stqaddress6() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_addr_bits; }
  auto& stqdata6() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_data_bits; }
  auto& stqcommand6() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_uop_mem_cmd; }
  auto& stqsize6() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_uop_mem_size; }
  auto& stqaddress7() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_addr_bits; }
  auto& stqdata7() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_data_bits; }
  auto& stqcommand7() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_uop_mem_cmd; }
  auto& stqsize7() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_uop_mem_size; }
  auto& integer(unsigned i) const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__regfile[i]; }
  auto& integerwritevalid0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_0_valid; }
  auto& integerwriteaddress0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_0_bits_addr; }
  auto& integerwritedata0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_0_bits_data; }
  auto& integerwritevalid1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_1_valid; }
  auto& integerwriteaddress1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_1_bits_addr; }
  auto& integerwritedata1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_1_bits_data; }
  auto& floating(unsigned i) const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__regfile[i]; }
  auto& floatingwritevalid0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__io_write_ports_0_valid; }
  auto& floatingwriteaddress0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__io_write_ports_0_bits_addr; }
  auto& floatingwritedata0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__io_write_ports_0_bits_data; }
  auto& floatingwritevalid1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__io_write_ports_1_valid; }
  auto& floatingwriteaddress1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__io_write_ports_1_bits_addr; }
  auto& floatingwritedata1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregfile__DOT__io_write_ports_1_bits_data; }
  auto& debug_req_ready() const { return root.TestHarness__DOT__SimDTM_debug_req_ready; }
  auto& debug_resp_valid() const { return root.TestHarness__DOT__SimDTM_debug_resp_valid; }
  auto& debug_resp_bits_resp() const { return root.TestHarness__DOT__SimDTM_debug_resp_bits_resp; }
  auto& debug_resp_bits_data() const { return root.TestHarness__DOT__SimDTM_debug_resp_bits_data; }
  auto& debug_req_valid_reg() const { return root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg; }
  auto& debug_req_bits_addr_reg() const { return root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg; }
  auto& debug_req_bits_op_reg() const { return root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg; }
  auto& debug_req_bits_data_reg() const { return root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg; }
  auto& debug_resp_ready_reg() const { return root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg; }
  auto& exit_reg() const { return root.TestHarness__DOT__SimDTM__DOT__exit_reg; }
  std::uint64_t valid(unsigned i) const { switch(i) {
    case 0: return valid0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t commit(unsigned i) const { switch(i) {
    case 0: return commit0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t enq(unsigned i) const { switch(i) {
    case 0: return enq0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t rd(unsigned i) const { switch(i) {
    case 0: return rd0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t rdvalid(unsigned i) const { switch(i) {
    case 0: return rdvalid0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t rdtype(unsigned i) const { switch(i) {
    case 0: return rdtype0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t pdst(unsigned i) const { switch(i) {
    case 0: return pdst0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t ftq(unsigned i) const { switch(i) {
    case 0: return ftq0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t pclow(unsigned i) const { switch(i) {
    case 0: return pclow0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t edge(unsigned i) const { switch(i) {
    case 0: return edge0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t store(unsigned i) const { switch(i) {
    case 0: return store0();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t pc(unsigned i) const { switch(i) {
    case 0: return ftqpc0();
    case 1: return ftqpc1();
    case 2: return ftqpc2();
    case 3: return ftqpc3();
    case 4: return ftqpc4();
    case 5: return ftqpc5();
    case 6: return ftqpc6();
    case 7: return ftqpc7();
    case 8: return ftqpc8();
    case 9: return ftqpc9();
    case 10: return ftqpc10();
    case 11: return ftqpc11();
    case 12: return ftqpc12();
    case 13: return ftqpc13();
    case 14: return ftqpc14();
    case 15: return ftqpc15();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t stq_address(unsigned i) const { switch(i) {
    case 0: return stqaddress0();
    case 1: return stqaddress1();
    case 2: return stqaddress2();
    case 3: return stqaddress3();
    case 4: return stqaddress4();
    case 5: return stqaddress5();
    case 6: return stqaddress6();
    case 7: return stqaddress7();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t stq_data(unsigned i) const { switch(i) {
    case 0: return stqdata0();
    case 1: return stqdata1();
    case 2: return stqdata2();
    case 3: return stqdata3();
    case 4: return stqdata4();
    case 5: return stqdata5();
    case 6: return stqdata6();
    case 7: return stqdata7();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t stq_command(unsigned i) const { switch(i) {
    case 0: return stqcommand0();
    case 1: return stqcommand1();
    case 2: return stqcommand2();
    case 3: return stqcommand3();
    case 4: return stqcommand4();
    case 5: return stqcommand5();
    case 6: return stqcommand6();
    case 7: return stqcommand7();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t stq_size(unsigned i) const { switch(i) {
    case 0: return stqsize0();
    case 1: return stqsize1();
    case 2: return stqsize2();
    case 3: return stqsize3();
    case 4: return stqsize4();
    case 5: return stqsize5();
    case 6: return stqsize6();
    case 7: return stqsize7();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t integer_write_valid(unsigned i) const { switch(i) {
    case 0: return integerwritevalid0();
    case 1: return integerwritevalid1();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t integer_write_address(unsigned i) const { switch(i) {
    case 0: return integerwriteaddress0();
    case 1: return integerwriteaddress1();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t integer_write_data(unsigned i) const { switch(i) {
    case 0: return integerwritedata0();
    case 1: return integerwritedata1();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t floating_write_valid(unsigned i) const { switch(i) {
    case 0: return floatingwritevalid0();
    case 1: return floatingwritevalid1();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t floating_write_address(unsigned i) const { switch(i) {
    case 0: return floatingwriteaddress0();
    case 1: return floatingwriteaddress1();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  sfp::rec_t floating_write_data(unsigned i) const { switch(i) {
    case 0: return (sfp::rec_t(floatingwritedata0()[2]) << 64) | (std::uint64_t(floatingwritedata0()[1]) << 32) | floatingwritedata0()[0];
    case 1: return (sfp::rec_t(floatingwritedata1()[2]) << 64) | (std::uint64_t(floatingwritedata1()[1]) << 32) | floatingwritedata1()[0];
    default: throw std::runtime_error("architectural observation index out of range"); } }
};
