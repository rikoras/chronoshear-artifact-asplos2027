// Hand-reviewed structural constants for the fixed SmallBoom TestHarness.
//
// Core-local proof: SmallBoom has decode width one.  core.scala's
// dec_finished_mask transition writes zero on dec_fire/redirect and otherwise
// can only retain its old value, so reset zero is invariant.  SFB/predication
// is disabled in this configuration: ROB enqueue clears rob_predicated and
// both reachable predicated writeback sources come through
// BranchKillableQueue memories whose write data is tied to zero.  With the
// simulator's common zero-initial-state contract, the selected bank read is
// therefore invariant zero.  Neither claim depends on a workload profile.

#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  // Large has three decode lanes.  A prefix can enter rename while a younger
  // lane stalls, so this register is live state rather than the Small-only
  // zero invariant proved above.
  bindings.bind_sampled(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_dec_finished_mask",
      [](const SystemGuider& m) -> std::uint64_t {
        return m.backend().core().dec_finished_mask;
      });
#else
  bindings.reserve_structural_constant(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_dec_finished_mask", UINT64_C(0x0));
#endif
  bindings.reserve_structural_constant(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_predicated_r0", UINT64_C(0x0));

// Tile A-channel proof: the two MSHR AcquireBlock producers are header-only
// on A, while the IOMSHR is the only data-bearing producer and its size comes
// from the two-bit CPU mem_size (0..3, at most one 8-byte beat).  Thus the
// BoomMSHRFile A arbiter can never load a nonzero beatsLeft.  Its E-channel
// arbiter is one-beat by construction and also loads only zero.  The tile
// master Xbar sees the same D-cache A stream; its other input explicitly loads
// zero, so its A-channel beatsLeft is invariant zero as well.

  bindings.reserve_structural_constant(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_beatsLeft", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_beatsLeft_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_tile_prci_domain_tile_reset_domain_boom_tile_tlMasterXbar_beatsLeft", UINT64_C(0x0));
//
// Front-bus proof: TestHarness.scala:26 calls
// `ldut.l2_frontend_bus_axi4.foreach(_.tieoff)`. AXI4Bundle.tieoff in
// Bundles.scala:79-97 drives AR/AW/W.valid and R/B.ready low. Therefore no
// front-bus request or response handshake is reachable for any workload.
// Queue/payload writes, fragmenter transitions, and protocol-counter updates
// below are all handshake-gated. They remain at reset; AXI4ToTL's two-input
// arbiter mask resets to 0b11. This is a topology proof, not a trace profile.

#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  // Large folds several otherwise identical zero-valued payload registers
  // into banks and assigns two UserYanker queues different dedup suffixes.
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_buffer_bundleIn_0_d_q_value_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_deq_ram__v2_bank_0_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_ram__v2_bank_0_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_1_ram__v2_bank_0_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_in_w_deq_ram_data", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_addr", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_deq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_enq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_deq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_enq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_ram_extra_id_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_ram_real_last_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_ram_extra_id_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_ram_real_last_io_deq_bits_MPORT", UINT64_C(0x0));
#endif

  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_buffer_bundleIn_0_d_q_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_buffer_bundleIn_0_d_q_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_buffer_bundleOut_0_a_q_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_buffer_bundleOut_0_a_q_value_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_b_count_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_beatsLeft", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_deq_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_q_b_deq_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_q_b_deq_ram_id", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_r_count_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_r_count_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_readys_mask", UINT64_C(0x3));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_state_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_state_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_w_count_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_w_count_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_busy", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_busy_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_1_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_in_w_deq_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_in_w_deq_ram_strb", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_addr_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_len", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_len_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_w_counter", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_wbeats_latched", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_deq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_enq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1$$inst_deq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1$$inst_enq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1$$inst_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2_deq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2_enq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_deq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_enq_ptr_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_value_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_maybe_full", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_value", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_value_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_a_first_counter", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_flight__v2_bank_0_0", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_stalls_id", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_stalls_id_1", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_ram_extra_id_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_ram_real_last_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1$$inst_ram_extra_id_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1$$inst_ram_real_last_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2_ram_extra_id_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2_ram_real_last_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_ram_extra_id_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_ram_real_last_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_corrupt_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_data_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_denied_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_opcode_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_param_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_sink_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_size_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_source_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_address_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_corrupt_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_data_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_mask_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_opcode_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_param_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_size_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_source_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_bufferable_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_fetch_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_modifiable_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_privileged_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_readalloc_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_secure_io_deq_bits_MPORT", UINT64_C(0x0));
  bindings.reserve_structural_constant(
      "ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_writealloc_io_deq_bits_MPORT", UINT64_C(0x0));
