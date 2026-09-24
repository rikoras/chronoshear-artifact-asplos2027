// Architecture trace ABI shared by the independent RTL runner and native
// model runner. No generated consumer or oracle image is read here.
#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace chisa::rocket_architecture {

inline constexpr uint64_t kHashOffset = UINT64_C(14695981039346656037);
inline constexpr const char* kLockedFirrtlSha256 = "5b8dc10f26513d19f50d8f185aabb2b648d2f7f535e9414d181a0e4e1d56f6b8";
struct Writeback { bool valid = false; uint8_t rd = 0; uint64_t value = 0; };
struct Sample {
  uint64_t cycle = 0;
  bool reset = false, retired = false, trapped = false, debug_mode = false;
  bool environment_debug = false;
  uint64_t pc = 0, cause = 0;
  uint32_t instruction = 0, expanded_instruction = 0;
  uint8_t privilege = 0;
  bool x_write = false, x_value_valid = false, fp_write = false;
  uint8_t xrd = 0, frd = 0;
  uint64_t xvalue = 0, store_address = 0, store_value = 0;
  Writeback late_x;
  std::array<Writeback, 2> fp{};
};

struct Configuration {
  std::string role, firrtl_sha256;
  uint64_t program_begin = 0x80000000, program_end = 0;
  uint64_t tohost = 0x80001000;
  uint64_t image_bytes = 0, image_fnv64 = 0;
};

inline std::string hex(uint64_t value) {
  std::ostringstream out; out << "0x" << std::hex << value; return out.str();
}
inline uint64_t hash_byte(uint64_t hash, uint8_t value) {
  return (hash ^ value) * UINT64_C(1099511628211);
}
inline uint64_t hash_word(uint64_t hash, uint64_t value) {
  for (unsigned i = 0; i < 8; ++i) hash = hash_byte(hash, static_cast<uint8_t>(value >> (i * 8)));
  return hash;
}
inline uint64_t hash_bytes(const uint8_t* data, size_t bytes) {
  uint64_t hash = kHashOffset;
  for (size_t i = 0; i < bytes; ++i) hash = hash_byte(hash, data[i]);
  return hash;
}

// Retirements are emitted in order after their architectural results resolve.
// Completion order across different registers need not equal retirement order.
class Recorder {
 public:
  Recorder(Configuration config, const std::string& path) : config_(std::move(config)), trace_(path) {
    if (!trace_) throw std::runtime_error("cannot create architecture trace " + path);
    if (config_.program_begin >= config_.program_end) throw std::invalid_argument("empty program PC range");
    trace_ << "{\"type\":\"header\",\"schema\":\"chisa-architecture-v1\",\"role\":\"" << config_.role
           << "\",\"firrtl_sha256\":\"" << config_.firrtl_sha256 << "\",\"program_begin\":\"" << hex(config_.program_begin)
           << "\",\"program_end\":\"" << hex(config_.program_end) << "\",\"tohost\":\"" << hex(config_.tohost)
           << "\",\"image_bytes\":" << config_.image_bytes << ",\"image_fnv64\":\"" << hex(config_.image_fnv64)
           << "\",\"endpoint\":\"retired-tohost-store\",\"confirmation\":\"coherent-dmi-read\",\"initial_registers\":\"unwritten-not-compared\"}\n";
  }

  void observe(const Sample& s) {
    if (finished_) throw std::logic_error("architecture recorder already finished");
    if (s.reset) {
      if (started_) throw std::runtime_error("reset inside a recorded program epoch");
      return;
    }
    const bool target = s.pc >= config_.program_begin && s.pc < config_.program_end && !s.debug_mode;
    if (!cut_ && started_ && s.retired && !target && !s.debug_mode) ++outside_retirements_;
    if (!cut_ && target && s.trapped) {
      if (s.environment_debug && (s.cause & 63) == 14) ++environment_traps_;
      else ++unsupported_traps_;
    }
    if (!cut_ && target && s.retired) {
      started_ = true;
      Record r;
      r.seq = next_seq_++; r.cycle = s.cycle; r.pc = s.pc; r.instruction = s.instruction;
      r.expanded = s.expanded_instruction; r.privilege = s.privilege;
      r.has_x = s.x_write && s.xrd != 0; r.xrd = s.xrd;
      r.x_ready = !r.has_x || s.x_value_valid; r.xvalue = s.xvalue;
      r.has_f = s.fp_write; r.frd = s.frd; r.f_ready = !r.has_f;
      if ((r.has_x && r.xrd >= 32) || (r.has_f && r.frd >= 32)) throw std::runtime_error("retired register index");
      const unsigned opcode = r.expanded & 0x7f;
      r.store = opcode == 0x23 || opcode == 0x27;
      if (opcode == 0x2f) ++unsupported_atomics_;
      if (r.store) {
        const unsigned size = (r.expanded >> 12) & 7;
        if (size >= 4) throw std::runtime_error("unsupported ordinary-store width");
        r.store_bytes = static_cast<uint8_t>(1u << size);
        r.store_address = s.store_address;
        r.store_value = size == 3 ? s.store_value : s.store_value & ((UINT64_C(1) << (8u << size)) - 1);
        if (r.store_address == config_.tohost && r.store_bytes != 8)
          throw std::runtime_error("tohost endpoint requires a complete 64-bit store");
      }
      records_.push_back(r);
      if (r.has_x && !r.x_ready) pending_x_[r.xrd].push_back(r.seq);
      if (r.has_f) pending_f_[r.frd].push_back(r.seq);
      if (r.store && r.store_address == config_.tohost && r.store_bytes == 8 &&
          (r.store_value & 1) && (r.store_value >> 48) == 0) {
        cut_ = true; cutoff_cycle_ = s.cycle; cutoff_seq_ = r.seq; exit_value_ = r.store_value;
      }
    }
    if (s.late_x.valid && s.late_x.rd != 0) resolve(s.late_x, false, s.debug_mode, s.cycle);
    for (const auto& write : s.fp) if (write.valid) resolve(write, true, s.debug_mode, s.cycle);
    flush_ready();
    last_cycle_ = s.cycle;
  }

  bool cutoff_seen() const { return cut_; }
  bool done() const { return cut_ && records_.empty(); }
  uint64_t cutoff_cycle() const { return cutoff_cycle_; }
  uint64_t exit_value() const { return exit_value_; }
  uint64_t unresolved_records() const { return records_.size(); }
  void confirm_tohost(uint64_t value) {
    if (!cut_) throw std::logic_error("tohost confirmation precedes the retirement cutoff");
    confirmation_received_ = true; observed_tohost_ = value;
  }
  bool tohost_confirmed() const { return confirmation_received_ && observed_tohost_ == exit_value_; }

  bool finish(const std::string& summary_path) {
    if (finished_) throw std::logic_error("architecture recorder already finished");
    finished_ = true;
    const bool complete = done() && tohost_confirmed() && exit_value_ == 1 && unsupported_traps_ == 0 && unsupported_atomics_ == 0 && orphan_writes_ == 0 && outside_retirements_ == 0;
    std::ostringstream summary;
    summary << "{\"type\":\"summary\",\"schema\":\"chisa-architecture-v1\",\"status\":\"" << (complete ? "complete" : "incomplete")
            << "\",\"role\":\"" << config_.role << "\",\"cutoff_seen\":" << (cut_ ? "true" : "false")
            << ",\"cutoff_cycle\":" << cutoff_cycle_ << ",\"cutoff_sequence\":" << cutoff_seq_
            << ",\"observed_cycle\":" << last_cycle_ << ",\"tohost\":\"" << hex(exit_value_)
            << "\",\"tohost_confirmed\":" << (tohost_confirmed() ? "true" : "false")
            << ",\"observed_tohost\":\"" << hex(observed_tohost_) << "\",\"retired\":" << emitted_ << ",\"unresolved_records\":" << records_.size()
            << ",\"integer_results\":" << x_results_ << ",\"fp_results\":" << f_results_ << ",\"ordinary_stores\":" << stores_
            << ",\"unsupported_atomic_instructions\":" << unsupported_atomics_ << ",\"unsupported_traps\":" << unsupported_traps_
            << ",\"environment_debug_traps\":" << environment_traps_ << ",\"orphan_writebacks\":" << orphan_writes_
            << ",\"outside_program_retirements\":" << outside_retirements_
            << ",\"x_written_mask\":\"" << hex(x_mask_) << "\",\"f_written_mask\":\"" << hex(f_mask_)
            << "\",\"record_hash\":\"" << hex(record_hash_) << "\",\"store_hash\":\"" << hex(store_hash_) << "\",\"x\":[";
    for (unsigned i = 0; i < 32; ++i) { if (i) summary << ','; summary << '"' << hex(x_[i]) << '"'; }
    summary << "],\"f\":[";
    for (unsigned i = 0; i < 32; ++i) { if (i) summary << ','; summary << '"' << hex(f_[i]) << '"'; }
    summary << "],\"coverage\":[\"retired-pc-instruction-privilege\",\"integer-results\",\"ieee-fp-results\",\"ordinary-stores\"],"
            << "\"uncovered\":[\"unwritten-initial-registers\",\"full-csr-state\",\"atomic-memory-side-effects\",\"non-environment-traps\",\"other-device-side-effects\"]}";
    trace_ << summary.str() << '\n'; trace_.flush();
    std::ofstream file(summary_path); file << summary.str() << '\n';
    if (!trace_ || !file) throw std::runtime_error("architecture trace/summary write failed");
    return complete;
  }

 private:
  struct Record {
    uint64_t seq = 0, cycle = 0, pc = 0;
    uint32_t instruction = 0, expanded = 0;
    uint8_t privilege = 0, xrd = 0, frd = 0, store_bytes = 0;
    bool has_x = false, x_ready = true, has_f = false, f_ready = true, store = false;
    uint64_t xvalue = 0, fvalue = 0, store_address = 0, store_value = 0;
  };

  void resolve(const Writeback& write, bool floating, bool debug, uint64_t cycle) {
    if (write.rd >= 32) throw std::runtime_error("architectural writeback register index");
    auto& pending = floating ? pending_f_[write.rd] : pending_x_[write.rd];
    if (pending.empty()) {
      // Outside-program debug/bootstrap writes and younger-than-cutoff writes
      // do not belong to this epoch. An unexplained in-program write fails.
      if (started_ && (!cut_ || cycle <= cutoff_cycle_) && !debug) ++orphan_writes_;
      return;
    }
    const uint64_t sequence = pending.front(); pending.pop_front();
    if (records_.empty() || sequence < records_.front().seq || sequence - records_.front().seq >= records_.size())
      throw std::runtime_error("writeback has no pending retirement");
    Record& record = records_[static_cast<size_t>(sequence - records_.front().seq)];
    if (floating) { record.fvalue = write.value; record.f_ready = true; }
    else { record.xvalue = write.value; record.x_ready = true; }
  }

  void flush_ready() {
    while (!records_.empty() && records_.front().x_ready && records_.front().f_ready) {
      const Record r = records_.front(); records_.pop_front();
      trace_ << "{\"type\":\"retire\",\"sequence\":" << r.seq << ",\"cycle\":" << r.cycle
             << ",\"pc\":\"" << hex(r.pc) << "\",\"instruction\":\"" << hex(r.instruction)
             << "\",\"expanded_instruction\":\"" << hex(r.expanded) << "\",\"privilege\":" << unsigned(r.privilege) << ",\"x\":";
      if (r.has_x) {
        trace_ << "{\"rd\":" << unsigned(r.xrd) << ",\"value\":\"" << hex(r.xvalue) << "\"}";
        x_[r.xrd] = r.xvalue; x_mask_ |= UINT32_C(1) << r.xrd; ++x_results_;
      } else trace_ << "null";
      trace_ << ",\"f\":";
      if (r.has_f) {
        trace_ << "{\"rd\":" << unsigned(r.frd) << ",\"value\":\"" << hex(r.fvalue) << "\"}";
        f_[r.frd] = r.fvalue; f_mask_ |= UINT32_C(1) << r.frd; ++f_results_;
      } else trace_ << "null";
      trace_ << ",\"store\":";
      if (r.store) {
        trace_ << "{\"address\":\"" << hex(r.store_address) << "\",\"bytes\":" << unsigned(r.store_bytes)
               << ",\"value\":\"" << hex(r.store_value) << "\"}";
        store_hash_ = hash_word(hash_word(hash_word(store_hash_, r.store_address), r.store_bytes), r.store_value); ++stores_;
      } else trace_ << "null";
      trace_ << "}\n";
      for (uint64_t value : {r.pc, uint64_t(r.instruction), uint64_t(r.expanded), uint64_t(r.privilege),
                            uint64_t(r.has_x), r.has_x ? uint64_t(r.xrd) : 0, r.has_x ? r.xvalue : 0,
                            uint64_t(r.has_f), r.has_f ? uint64_t(r.frd) : 0, r.has_f ? r.fvalue : 0,
                            uint64_t(r.store), r.store ? r.store_address : 0, uint64_t(r.store_bytes), r.store ? r.store_value : 0})
        record_hash_ = hash_word(record_hash_, value);
      ++emitted_;
    }
  }

  Configuration config_;
  std::ofstream trace_;
  std::deque<Record> records_;
  std::array<std::deque<uint64_t>, 32> pending_x_, pending_f_;
  std::array<uint64_t, 32> x_{}, f_{};
  uint32_t x_mask_ = 0, f_mask_ = 0;
  uint64_t next_seq_ = 0, emitted_ = 0, cutoff_seq_ = 0, cutoff_cycle_ = 0, last_cycle_ = 0, exit_value_ = 0;
  uint64_t unsupported_traps_ = 0, unsupported_atomics_ = 0, environment_traps_ = 0, orphan_writes_ = 0;
  uint64_t outside_retirements_ = 0;
  uint64_t x_results_ = 0, f_results_ = 0, stores_ = 0;
  uint64_t record_hash_ = kHashOffset, store_hash_ = kHashOffset;
  bool started_ = false, cut_ = false, finished_ = false;
  bool confirmation_received_ = false;
  uint64_t observed_tohost_ = 0;
};
}  // namespace chisa::rocket_architecture
