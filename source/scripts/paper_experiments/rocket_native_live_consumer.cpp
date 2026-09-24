#include "TestHarness.h"
#include "rocket_trace_support.h"
#include "rocket_native_live_consumer.h"
#if !defined(ESSENT_ORACLE_VERIFY) || !ESSENT_ORACLE_VERIFY
#error "native online execution requires all original oracle checks"
#endif
#if !ROCKET_CONSUMER_EXTERNAL_DRAM
#error "native online execution requires the complete external DRAM contract"
#endif
namespace rocket_native_live {
namespace {
constexpr unsigned W = CHISA_CONSUMER_WIDTH;
static_assert(ORACLE_STREAM_COUNT == 1092 && ORACLE_DATA_MIRRORED == 1);
using chisa::rocket_trace::assign;
using chisa::rocket_trace::value;
template<class Ports> void drive(Ports& p, unsigned lane, const Cycle& c) {
  assign(p.debug_req_valid[lane], c.request_valid);
  assign(p.debug_req_bits_addr[lane], c.request_address);
  assign(p.debug_req_bits_op[lane], c.request_operation);
  assign(p.debug_req_bits_data[lane], c.request_data);
  assign(p.debug_resp_ready[lane], c.response_ready);
  assign(p.exit[lane], 0);
}
template<class Ports> void check(const TestHarness& rtl, const Ports& p, unsigned lane, const Cycle& c, uint64_t cycle) {
  if (value(p.debug_req_ready[lane]) == c.request_ready && value(p.debug_resp_valid[lane]) == c.response_valid &&
      value(p.debug_resp_bits_resp[lane]) == c.response_status && value(p.debug_resp_bits_data[lane]) == c.response_data &&
      value(rtl.io_success[lane]) == 0) return;
  std::fprintf(stderr, "ROCKET_NATIVE_BOUNDARY_MISMATCH cycle=%llu lane=%u\n", (unsigned long long)cycle, lane);
  throw std::runtime_error("native/RTL DMI boundary differs");
}
}
Consumer::Consumer(int argc, char** argv, bool oracle_mismatches_fatal, uint64_t mismatch_log_limit)
    : impl_(new TestHarness), oracle_mismatches_fatal_(oracle_mismatches_fatal) {
  auto& rtl = *static_cast<TestHarness*>(impl_);
  chisa::rocket_trace::initialize_plusargs<W>(rtl, argc, argv);
  rtl.checks_enabled = true; rtl.verify_mismatches = 0;
  rtl.set_oracle_mismatch_policy(oracle_mismatches_fatal, mismatch_log_limit);
}
Consumer::~Consumer() { delete static_cast<TestHarness*>(impl_); }
void Consumer::evaluate(const char* block, const Cycle* records, uint64_t first, bool reset) {
  auto& rtl = *static_cast<TestHarness*>(impl_);
  rtl.oracle_win_base = block; oracle_kernel_base = block;
  auto& ports = chisa::rocket_trace::dmi_ports(rtl);
  assign(rtl.reset, reset);
  for (unsigned lane = 0; lane < W; ++lane) drive(ports, lane, records[lane]);
  rtl.eval_forward(true, false, !reset);
  for (unsigned lane = 0; lane < W; ++lane) check(rtl, ports, lane, records[lane], first+lane);
  for (unsigned step = 0; step < W; ++step) drive(ports, W-1-step, records[W+step]);
  rtl.eval_reverse(true, false, !reset);
  for (unsigned step = 0; step < W; ++step) check(rtl, ports, W-1-step, records[W+step], first+W+step);
  if (rtl.assert_triggered || (!reset && oracle_mismatches_fatal_ && rtl.verify_mismatches))
    throw std::runtime_error("checked native prediction differs from RTL at window " + std::to_string(first));
}
Endpoint Consumer::endpoint() const {
  const auto& rtl = *static_cast<TestHarness*>(impl_);
  const auto& core = rtl.ldut.tile_prci_domain.tile_reset_domain.tile.core;
  Endpoint result{}; result.pc = value(core.wb_reg_pc[0]);
  for (unsigned index = 0; index < 32; ++index) {
    result.x[index] = index ? value(core.rf[31-index]) : 0;
    const auto& f = rtl.ldut.tile_prci_domain.tile_reset_domain.tile.fpuOpt.regfile[index];
    result.f_low[index] = f.val[0]; result.f_high[index] = f.val[1] & 1;
  }
  return result;
}
uint64_t Consumer::mismatches() const { return static_cast<TestHarness*>(impl_)->verify_mismatches; }
uint64_t Consumer::oracle_mismatch_signals() const { return static_cast<TestHarness*>(impl_)->oracle_mismatch_signal_count(); }
uint64_t Consumer::oracle_checked_signals() const { return TestHarness::oracle_checked_signal_count(); }
uint64_t Consumer::block_bytes() const { return ORACLE_DATA_BLOCK_BYTES; }
}
