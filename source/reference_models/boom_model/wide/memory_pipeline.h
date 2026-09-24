#pragma once
#include "../common/pipeline_uop.h"
#include "../common/memory_contract.h"
#include "../common/boom_lsu_scheduler.h"
#include <array>
#include <cstdint>

namespace chisa::boom_model::wide {
struct MemoryTag {
  std::uint8_t rob = 0, pdst = 0, load = 0, store = 0, size = 0, command = 0;
  boomcfg::br_mask_t branch = 0;
  std::uint32_t generation = 0;
  std::uint64_t ticket = 0;
  bool uses_load = false, uses_store = false, amo = false;
  bool floating = false, single = false, signed_load = false;
};
struct MemoryRequest {
  bool valid = false;
  MemoryTag tag;
  std::uint64_t address = 0, data = 0;
};
struct MemoryResponse {
  bool valid = false, exception = false;
  MemoryTag tag;
  std::uint64_t data = 0, cause = 0;
};
struct MemoryNack {
  bool valid = false;
  MemoryTag tag;
};
struct MemoryControl {
  bool request_ready = false, ordered = true, release_valid = false;
  bool tlb_miss_ready = true, passthrough = false;
  bool hella_incoming = false, hella_wakeup = false;
  std::uint64_t release_address = 0;
};
struct Translation {
  // No supplied translation means a retry, not an implicit identity map.
  bool passthrough = false, miss = true, uncacheable = false;
  bool page_fault_load = false, page_fault_store = false;
  bool access_fault_load = false, access_fault_store = false;
  std::uint64_t physical = 0;
};
struct MemoryPlan {
  const void* owner = nullptr;
  std::uint64_t cycle = 0;
  MemoryControl control;
  boom_lsu::Candidates candidates;
  boom_lsu::Schedule schedule;
  DtlbLookupCandidate translation;
  MemoryTag translated, cache;
  StageUop incoming;
  std::uint64_t virtual_address = 0, cache_address = 0, store_data = 0, incoming_data = 0;
  bool flush = false;
};
struct MemoryInputs {
  MemoryControl control;
  Translation translation;
  MemoryResponse response;
  MemoryNack nack;
  // A system may compute each once while evaluating TLB/cache ports, then
  // pass the same PRE plan/request to step. Null uses the standalone path.
  const MemoryPlan* prepared_plan = nullptr;
  const MemoryRequest* prepared_request = nullptr;
};
struct MemoryWriteback {
  bool valid = false;
  MemoryTag tag;
  std::uint64_t data = 0;
};
struct MemoryPorts {
  boom_lsu::Schedule schedule;
  DtlbLookupCandidate translation;
  MemoryRequest request;
  bool fired = false, s1_kill = false, release_ready = false;
  bool integer_response = false, speculative_wakeup = false, load_miss = false;
  std::uint8_t speculative_pdst = 0;
  MemoryWriteback floating_response;
  bool sfence = false, sfence_rs1 = false, sfence_rs2 = false;
  std::uint64_t sfence_address = 0;
};
struct MemoryReadStage {
  bool valid = false;
  StageUop uop;
  std::uint64_t rs1 = 0, rs2 = 0;
};
struct MemorySearch {
  bool valid = false, load = false, fired = false;
  MemoryTag tag;
  std::uint64_t address = 0;
};
struct ForwardedLoad {
  bool valid = false;
  MemoryTag load;
  std::uint8_t store = 0;
  std::uint32_t store_generation = 0;
};
struct MemoryFault {
  bool valid = false;
  MemoryTag tag;
  std::uint64_t cause = 0, address = 0;
};
struct StoreCompletion {
  bool valid = false;
  MemoryTag tag;
  std::uint64_t due = 0;
  bool floating_data = false;
};
struct SpeculativeLoad {
  bool valid = false;
  MemoryTag tag;
};
struct MemoryImage {
  std::array<MemoryReadStage,2> read{};
  MemoryRequest pending;
  bool pending_fault = false;
  std::uint64_t next_ticket = 1;
  MemorySearch search;
  ForwardedLoad forward;
  std::array<SpeculativeLoad,2> speculative{};
  std::array<StoreCompletion,4> clear_store{};
  StoreCompletion fp_store;
  MemoryFault translation_fault, exception;
  std::uint32_t block1 = 0, block2 = 0, nacks = 0;
  std::uint8_t load_retry = boomcfg::NUM_LDQ-1, load_wakeup = boomcfg::NUM_LDQ-1, store_retry = boomcfg::NUM_STQ-1;
  std::uint8_t store_blocked = 0, load_issue_count = 0, incoming_load_index = 0;
  bool issued_load = false;
  bool block_wakeup = false, release = false, commit_load_head = false;
  std::uint64_t release_address = 0;
};
}  // namespace chisa::boom_model::wide
