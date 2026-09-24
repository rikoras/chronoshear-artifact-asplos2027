#pragma once
inline constexpr unsigned kCommit = 3, kInteger = 100, kFloating = 96, kFtq = 32, kStores = 24;
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
  auto& valid1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_arch_valids_1; }
  auto& commit1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_valids_1; }
  auto& enq1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_enq_valids_1; }
  auto& rd1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_ldst; }
  auto& rdvalid1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_ldst_val; }
  auto& rdtype1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_dst_rtype; }
  auto& pdst1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_pdst; }
  auto& ftq1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_ftq_idx; }
  auto& pclow1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_pc_lob; }
  auto& edge1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_edge_inst; }
  auto& store1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_1_uses_stq; }
  auto& valid2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_arch_valids_2; }
  auto& commit2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_valids_2; }
  auto& enq2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_enq_valids_2; }
  auto& rd2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_ldst; }
  auto& rdvalid2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_ldst_val; }
  auto& rdtype2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_dst_rtype; }
  auto& pdst2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_pdst; }
  auto& ftq2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_ftq_idx; }
  auto& pclow2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_pc_lob; }
  auto& edge2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_edge_inst; }
  auto& store2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__io_commit_uops_2_uses_stq; }
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
  auto& ftqpc16() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_16; }
  auto& ftqpc17() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_17; }
  auto& ftqpc18() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_18; }
  auto& ftqpc19() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_19; }
  auto& ftqpc20() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_20; }
  auto& ftqpc21() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_21; }
  auto& ftqpc22() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_22; }
  auto& ftqpc23() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_23; }
  auto& ftqpc24() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_24; }
  auto& ftqpc25() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_25; }
  auto& ftqpc26() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_26; }
  auto& ftqpc27() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_27; }
  auto& ftqpc28() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_28; }
  auto& ftqpc29() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_29; }
  auto& ftqpc30() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_30; }
  auto& ftqpc31() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_31; }
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
  auto& stqaddress8() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_addr_bits; }
  auto& stqdata8() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_data_bits; }
  auto& stqcommand8() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_uop_mem_cmd; }
  auto& stqsize8() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_uop_mem_size; }
  auto& stqaddress9() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_addr_bits; }
  auto& stqdata9() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_data_bits; }
  auto& stqcommand9() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_uop_mem_cmd; }
  auto& stqsize9() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_uop_mem_size; }
  auto& stqaddress10() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_addr_bits; }
  auto& stqdata10() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_data_bits; }
  auto& stqcommand10() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_uop_mem_cmd; }
  auto& stqsize10() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_uop_mem_size; }
  auto& stqaddress11() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_addr_bits; }
  auto& stqdata11() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_data_bits; }
  auto& stqcommand11() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_uop_mem_cmd; }
  auto& stqsize11() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_uop_mem_size; }
  auto& stqaddress12() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_addr_bits; }
  auto& stqdata12() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_data_bits; }
  auto& stqcommand12() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_uop_mem_cmd; }
  auto& stqsize12() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_uop_mem_size; }
  auto& stqaddress13() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_addr_bits; }
  auto& stqdata13() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_data_bits; }
  auto& stqcommand13() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_uop_mem_cmd; }
  auto& stqsize13() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_uop_mem_size; }
  auto& stqaddress14() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_addr_bits; }
  auto& stqdata14() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_data_bits; }
  auto& stqcommand14() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_uop_mem_cmd; }
  auto& stqsize14() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_uop_mem_size; }
  auto& stqaddress15() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_addr_bits; }
  auto& stqdata15() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_data_bits; }
  auto& stqcommand15() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_uop_mem_cmd; }
  auto& stqsize15() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_uop_mem_size; }
  auto& stqaddress16() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_16_bits_addr_bits; }
  auto& stqdata16() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_16_bits_data_bits; }
  auto& stqcommand16() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_16_bits_uop_mem_cmd; }
  auto& stqsize16() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_16_bits_uop_mem_size; }
  auto& stqaddress17() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_17_bits_addr_bits; }
  auto& stqdata17() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_17_bits_data_bits; }
  auto& stqcommand17() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_17_bits_uop_mem_cmd; }
  auto& stqsize17() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_17_bits_uop_mem_size; }
  auto& stqaddress18() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_18_bits_addr_bits; }
  auto& stqdata18() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_18_bits_data_bits; }
  auto& stqcommand18() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_18_bits_uop_mem_cmd; }
  auto& stqsize18() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_18_bits_uop_mem_size; }
  auto& stqaddress19() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_19_bits_addr_bits; }
  auto& stqdata19() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_19_bits_data_bits; }
  auto& stqcommand19() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_19_bits_uop_mem_cmd; }
  auto& stqsize19() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_19_bits_uop_mem_size; }
  auto& stqaddress20() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_20_bits_addr_bits; }
  auto& stqdata20() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_20_bits_data_bits; }
  auto& stqcommand20() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_20_bits_uop_mem_cmd; }
  auto& stqsize20() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_20_bits_uop_mem_size; }
  auto& stqaddress21() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_21_bits_addr_bits; }
  auto& stqdata21() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_21_bits_data_bits; }
  auto& stqcommand21() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_21_bits_uop_mem_cmd; }
  auto& stqsize21() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_21_bits_uop_mem_size; }
  auto& stqaddress22() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_22_bits_addr_bits; }
  auto& stqdata22() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_22_bits_data_bits; }
  auto& stqcommand22() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_22_bits_uop_mem_cmd; }
  auto& stqsize22() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_22_bits_uop_mem_size; }
  auto& stqaddress23() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_23_bits_addr_bits; }
  auto& stqdata23() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_23_bits_data_bits; }
  auto& stqcommand23() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_23_bits_uop_mem_cmd; }
  auto& stqsize23() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_23_bits_uop_mem_size; }
  auto& integer(unsigned i) const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__regfile[i]; }
  auto& integerwritevalid0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_0_valid; }
  auto& integerwriteaddress0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_0_bits_addr; }
  auto& integerwritedata0() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_0_bits_data; }
  auto& integerwritevalid1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_1_valid; }
  auto& integerwriteaddress1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_1_bits_addr; }
  auto& integerwritedata1() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_1_bits_data; }
  auto& integerwritevalid2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_2_valid; }
  auto& integerwriteaddress2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_2_bits_addr; }
  auto& integerwritedata2() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_2_bits_data; }
  auto& integerwritevalid3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_3_valid; }
  auto& integerwriteaddress3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_3_bits_addr; }
  auto& integerwritedata3() const { return root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile__DOT__io_write_ports_3_bits_data; }
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
    case 1: return valid1();
    case 2: return valid2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t commit(unsigned i) const { switch(i) {
    case 0: return commit0();
    case 1: return commit1();
    case 2: return commit2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t enq(unsigned i) const { switch(i) {
    case 0: return enq0();
    case 1: return enq1();
    case 2: return enq2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t rd(unsigned i) const { switch(i) {
    case 0: return rd0();
    case 1: return rd1();
    case 2: return rd2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t rdvalid(unsigned i) const { switch(i) {
    case 0: return rdvalid0();
    case 1: return rdvalid1();
    case 2: return rdvalid2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t rdtype(unsigned i) const { switch(i) {
    case 0: return rdtype0();
    case 1: return rdtype1();
    case 2: return rdtype2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t pdst(unsigned i) const { switch(i) {
    case 0: return pdst0();
    case 1: return pdst1();
    case 2: return pdst2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t ftq(unsigned i) const { switch(i) {
    case 0: return ftq0();
    case 1: return ftq1();
    case 2: return ftq2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t pclow(unsigned i) const { switch(i) {
    case 0: return pclow0();
    case 1: return pclow1();
    case 2: return pclow2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t edge(unsigned i) const { switch(i) {
    case 0: return edge0();
    case 1: return edge1();
    case 2: return edge2();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t store(unsigned i) const { switch(i) {
    case 0: return store0();
    case 1: return store1();
    case 2: return store2();
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
    case 16: return ftqpc16();
    case 17: return ftqpc17();
    case 18: return ftqpc18();
    case 19: return ftqpc19();
    case 20: return ftqpc20();
    case 21: return ftqpc21();
    case 22: return ftqpc22();
    case 23: return ftqpc23();
    case 24: return ftqpc24();
    case 25: return ftqpc25();
    case 26: return ftqpc26();
    case 27: return ftqpc27();
    case 28: return ftqpc28();
    case 29: return ftqpc29();
    case 30: return ftqpc30();
    case 31: return ftqpc31();
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
    case 8: return stqaddress8();
    case 9: return stqaddress9();
    case 10: return stqaddress10();
    case 11: return stqaddress11();
    case 12: return stqaddress12();
    case 13: return stqaddress13();
    case 14: return stqaddress14();
    case 15: return stqaddress15();
    case 16: return stqaddress16();
    case 17: return stqaddress17();
    case 18: return stqaddress18();
    case 19: return stqaddress19();
    case 20: return stqaddress20();
    case 21: return stqaddress21();
    case 22: return stqaddress22();
    case 23: return stqaddress23();
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
    case 8: return stqdata8();
    case 9: return stqdata9();
    case 10: return stqdata10();
    case 11: return stqdata11();
    case 12: return stqdata12();
    case 13: return stqdata13();
    case 14: return stqdata14();
    case 15: return stqdata15();
    case 16: return stqdata16();
    case 17: return stqdata17();
    case 18: return stqdata18();
    case 19: return stqdata19();
    case 20: return stqdata20();
    case 21: return stqdata21();
    case 22: return stqdata22();
    case 23: return stqdata23();
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
    case 8: return stqcommand8();
    case 9: return stqcommand9();
    case 10: return stqcommand10();
    case 11: return stqcommand11();
    case 12: return stqcommand12();
    case 13: return stqcommand13();
    case 14: return stqcommand14();
    case 15: return stqcommand15();
    case 16: return stqcommand16();
    case 17: return stqcommand17();
    case 18: return stqcommand18();
    case 19: return stqcommand19();
    case 20: return stqcommand20();
    case 21: return stqcommand21();
    case 22: return stqcommand22();
    case 23: return stqcommand23();
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
    case 8: return stqsize8();
    case 9: return stqsize9();
    case 10: return stqsize10();
    case 11: return stqsize11();
    case 12: return stqsize12();
    case 13: return stqsize13();
    case 14: return stqsize14();
    case 15: return stqsize15();
    case 16: return stqsize16();
    case 17: return stqsize17();
    case 18: return stqsize18();
    case 19: return stqsize19();
    case 20: return stqsize20();
    case 21: return stqsize21();
    case 22: return stqsize22();
    case 23: return stqsize23();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t integer_write_valid(unsigned i) const { switch(i) {
    case 0: return integerwritevalid0();
    case 1: return integerwritevalid1();
    case 2: return integerwritevalid2();
    case 3: return integerwritevalid3();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t integer_write_address(unsigned i) const { switch(i) {
    case 0: return integerwriteaddress0();
    case 1: return integerwriteaddress1();
    case 2: return integerwriteaddress2();
    case 3: return integerwriteaddress3();
    default: throw std::runtime_error("architectural observation index out of range"); } }
  std::uint64_t integer_write_data(unsigned i) const { switch(i) {
    case 0: return integerwritedata0();
    case 1: return integerwritedata1();
    case 2: return integerwritedata2();
    case 3: return integerwritedata3();
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
