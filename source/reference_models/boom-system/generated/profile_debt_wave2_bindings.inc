// Generated: TAGE table SRAM read ports (tage.scala table(w).read), formerly profiled constants.
void sample_batch_profile_debt_wave2(const SystemGuider& m, BatchSlots slots) {
  (void)m; (void)slots;
}

void register_profile_debt_wave2_bindings() {
  ManifestTimedSampledBindings bindings(ModelBindings::instance());
  const int base = bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.reserve_batch_scratch();
  bindings.add_batch_sampler(sample_batch_profile_debt_wave2, base, ModelBindings::SamplePlacement::Frontend, watch_sample_batch_profile_debt_wave2);
}
