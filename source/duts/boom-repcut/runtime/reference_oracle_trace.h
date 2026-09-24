#pragma once

#include <array>
#include <cstdint>

#include "extmodule_adapters.h"

namespace chisa::boom_repcut {

inline constexpr std::array<char, 8> kReferenceOracleTraceMagic{
    'C', 'H', 'W', '4', 'T', 'R', 'C', '1'};
inline constexpr std::uint32_t kReferenceOracleTraceVersion = 1;

struct ReferenceOracleTraceHeader {
  std::array<char, 8> magic = kReferenceOracleTraceMagic;
  std::uint32_t version = kReferenceOracleTraceVersion;
  std::uint32_t width = 4;
  std::uint32_t cycle_record_bytes = 0;
  std::uint32_t reserved = 0;
  std::uint64_t cycles = 0;
  std::uint64_t reset_cycles = 0;
  std::uint64_t oracle_blocks = 0;
  std::uint64_t oracle_block_bytes = 0;
  std::uint64_t oracle_streams = 0;
};

struct ReferenceOracleCycleRecord {
  std::uint32_t req_addr = 0;
  std::uint32_t req_op = 0;
  std::uint32_t req_data = 0;
  std::uint32_t exit = 0;
  std::uint32_t feedback_resp = 0;
  std::uint32_t feedback_data = 0;
  std::uint8_t req_valid = 0;
  std::uint8_t resp_ready = 0;
  std::uint8_t feedback_req_ready = 0;
  std::uint8_t feedback_resp_valid = 0;
  std::uint8_t io_success = 0;
  std::uint8_t reset = 0;
  std::array<std::uint8_t, 2> reserved{};
};

inline ReferenceOracleCycleRecord make_reference_oracle_cycle(
    const DtmOutputs& outputs, const DmiFeedback& feedback, bool io_success,
    bool reset) {
  return ReferenceOracleCycleRecord{
      outputs.req_addr,
      outputs.req_op,
      outputs.req_data,
      outputs.exit,
      feedback.resp,
      feedback.data,
      static_cast<std::uint8_t>(outputs.req_valid),
      static_cast<std::uint8_t>(outputs.resp_ready),
      static_cast<std::uint8_t>(feedback.req_ready),
      static_cast<std::uint8_t>(feedback.resp_valid),
      static_cast<std::uint8_t>(io_success),
      static_cast<std::uint8_t>(reset),
      {}};
}

inline DtmOutputs trace_dtm_outputs(const ReferenceOracleCycleRecord& record) {
  return DtmOutputs{
      record.req_valid != 0,
      record.req_addr,
      record.req_op,
      record.req_data,
      record.resp_ready != 0,
      record.exit};
}

inline DmiFeedback trace_dmi_feedback(
    const ReferenceOracleCycleRecord& record) {
  return DmiFeedback{
      record.feedback_req_ready != 0,
      record.feedback_resp_valid != 0,
      record.feedback_resp,
      record.feedback_data};
}

}  // namespace chisa::boom_repcut
