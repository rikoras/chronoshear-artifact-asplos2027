#pragma once
#include <cstdint>
namespace rocket_native_live {
struct Cycle {
  bool request_valid, response_ready;
  uint32_t request_address, request_operation, request_data;
  bool request_ready, response_valid;
  uint32_t response_status, response_data;
};
struct Endpoint { uint64_t pc, x[32], f_low[32]; uint8_t f_high[32]; };
class Consumer {
 public:
  Consumer(int argc, char** argv, bool oracle_mismatches_fatal = true,
           uint64_t mismatch_log_limit = 4);
  ~Consumer();
  Consumer(const Consumer&) = delete;
  Consumer& operator=(const Consumer&) = delete;
  void evaluate(const char* block, const Cycle* cycles, uint64_t first, bool reset);
  Endpoint endpoint() const;
  uint64_t mismatches() const;
  uint64_t oracle_mismatch_signals() const;
  uint64_t oracle_checked_signals() const;
  uint64_t block_bytes() const;
 private:
  void* impl_;
  bool oracle_mismatches_fatal_;
};
}
