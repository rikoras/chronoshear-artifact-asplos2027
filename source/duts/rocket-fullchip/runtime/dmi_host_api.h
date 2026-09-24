#pragma once

#include <cstdint>

namespace chisa::rocket_fullchip {

struct DmiHostOutputs {
  bool request_valid = false;
  std::uint32_t request_address = 0;
  std::uint32_t request_operation = 0;
  std::uint32_t request_data = 0;
  bool response_ready = false;
};

void dmi_host_configure(std::uint64_t entry, std::uint64_t tohost,
                        std::uint64_t fromhost);
void dmi_host_advance(bool request_ready, bool response_valid,
                      std::uint32_t response_status,
                      std::uint32_t response_data);
DmiHostOutputs dmi_host_outputs();

bool dmi_host_bootstrap_complete();
bool dmi_host_idle();
bool dmi_host_failed();
const char* dmi_host_error();
const char* dmi_host_stage();
std::uint64_t dmi_host_transactions();
std::uint64_t dmi_host_console_acks();
std::uint64_t dmi_host_tohost_reads();
std::uint64_t dmi_host_last_tohost();
void dmi_host_request_console_ack();
void dmi_host_request_tohost_read();

}  // namespace chisa::rocket_fullchip
