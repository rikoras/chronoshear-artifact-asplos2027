#pragma once
#include <array>
#include <cstdint>
#include "../common/core_types.h"
#include "../common/architectural_state.h"
#include "execution_state.h"
#include "fp_pipeline.h"
#include "memory_pipeline.h"
#include "memory_entry.h"
#include "../common/byte_columns.h"
#include "record_column.h"
#include "contract.h"
#include <type_traits>

namespace chisa::boom_model::wide {
using PhysicalMask = unsigned __int128;
using BranchMask = std::uint16_t;
using QueueMask = std::uint32_t;
using RobGeometry = boomcfg::RobGeometry;
using LsqGeometry = boomcfg::LdqGeometry;
inline constexpr unsigned kWidth=boomcfg::CORE_WIDTH, kRows=boomcfg::NUM_ROB_ROWS;
inline constexpr unsigned kRobEntries=boomcfg::NUM_ROB_ENTRIES, kBranches=boomcfg::MAX_BR_COUNT;
inline constexpr unsigned kLsq=boomcfg::NUM_LDQ, kIqCapacity=boomcfg::MAX_IQ_SLOTS;
inline constexpr unsigned kDispatchMask=(1u<<kWidth)-1, kBranchMask=(1u<<kBranches)-1;
inline constexpr unsigned kLsqMask=(1u<<kLsq)-1, kRobMask=RobGeometry::wire_count-1;
inline constexpr unsigned kWritebackPorts=kWidth+3;
static_assert(boomcfg::NUM_LDQ==boomcfg::NUM_STQ);

struct RenameDomain {
  std::array<std::uint8_t, 32> map{};
  std::array<std::array<std::uint8_t, 32>, kBranches> checkpoints{};
  PhysicalMask free = 0, busy = 0;
  std::array<PhysicalMask, kBranches> branch_allocations{};
  std::array<std::uint8_t, kWidth> selected{};
  std::array<std::uint8_t,kWidth> selected_valid{};
  // Map/free/checkpoint mutations patch their final packed fields directly.
};
struct RenameImage {
  RenameDomain integer, floating;
  std::array<MicroOp, kWidth> held{};
  std::array<std::uint8_t,kWidth> valid{};
  std::uint8_t pending_mask() const { std::uint8_t mask=0;for(unsigned i=0;i<kWidth;++i)mask|=valid[i]<<i;return mask; }
  void set_pending(std::uint8_t mask) { for(unsigned i=0;i<kWidth;++i)valid[i]=(mask>>i)&1u; }
  BranchMask branches = 0;
};

// One instruction record per real ROB entry. A wire tag's unused bank code
// never indexes this array; convert with RobGeometry::dense_from_wire.
struct Instruction {
  MicroOp decoded{};
  bool debug = false;
};
// Only the asynchronous read face is retained, not another ROB image.
struct RobReadPorts {
  std::uint32_t valid0 = 0, unsafe0 = 0, exception0 = 0;
  std::array<std::uint64_t,8> uop{};
  std::array<std::uint8_t,kWidth> fflags{};
  std::uint16_t busy = 0, busy_care = 0;
  std::uint8_t uop_care = 0, head_valid = 0, head = 0, pnr = 0;
  bool exception_unsafe = false, exception_unsafe_care = false;
};
struct RobImage {
  std::array<Instruction, kRobEntries> instructions{};
  std::array<std::uint32_t, kWidth> valid{}, busy{}, unsafe{}, exception{};
  std::array<std::uint8_t, kRobEntries> fflags{};
  std::array<std::uint64_t, kRobEntries> exception_cause{}, exception_tval{};
  std::array<bool, kRobEntries> exception_tval_valid{};
  std::array<BranchMask, kRobEntries> branch_mask{};
  std::array<std::uint64_t, kRobEntries> packed_uop{};
  RobReadPorts reads;
  std::uint32_t rows = 0;
  std::uint8_t head = 0, tail = 0;
  bool row_open = false, serializing = false, rolling_back = false;
  std::uint8_t pnr = 0, fsm = 0, head_lsb = 0, tail_lsb = 0;
  bool maybe_full = false, pnr_maybe_at_tail = false;
  bool exception_delay1 = false, exception_delay2 = false;
  bool rollback_pending = false;
  std::uint8_t rollback_row = 0, rollback_delay = 0;
};

enum class QueueKind : std::uint8_t { Integer, Memory, Floating };

// Control columns and selected packed words directly reference final record
// storage. Compact scheduling metadata remains native. Invalid operands still
// participate in wakeup CAMs, as in Small and the actual IssueSlot RTL.
struct IssueImage {
  QueueKind kind = QueueKind::Integer;
  unsigned capacity = 0, available = 0;
  RecordColumn<std::uint8_t> state,p1,p2,p3,ppred,poison1,poison2;
  std::array<std::uint8_t*,kWidth> ready{};
  RecordColumn<std::uint64_t> word0;
  RecordColumn<std::remove_extent_t<decltype(contract::CoreIntIq::slots_slot_uopbank_0_1)>> integer_word1;
  RecordColumn<std::uint16_t> word2,memory_word1;
  RecordColumn<std::uint8_t> floating_word1;
  RecordColumn<std::uint32_t> shape;
  QueueMask occupied_mask() const { return byte_columns::nonzero_mask(state.data(),capacity); }
  bool poisoned(unsigned i) const { return kind!=QueueKind::Floating && (poison1[i] || poison2[i]); }
  void set_available(unsigned count) {
    available=count;for(unsigned i=0;i<kWidth;++i)*ready[i]=count>i;
  }
  void clear_poison() {
    if (kind==QueueKind::Floating) return;
    byte_columns::clear(poison1.data(),capacity);byte_columns::clear(poison2.data(),capacity);
  }
  void squash_poison() {
    for(unsigned i=0;i<capacity;++i) {
      if(poison1[i]) p1[i]=0;
      if(poison2[i]) p2[i]=0;
    }
  }
  std::array<std::uint8_t, kIqCapacity> rob{}, prs1{}, prs2{}, prs3{}, rt1{}, rt2{};
  std::array<std::uint16_t, kIqCapacity> fu{};
  std::array<std::uint8_t,kIqCapacity> opcode{};
  std::array<BranchMask,kIqCapacity> branch_mask{};
  std::uint8_t uopc(unsigned slot) const {
    return opcode[slot];
  }
  BranchMask branch(unsigned slot) const {
    return branch_mask[slot];
  }
  void clear_branches(unsigned slot, BranchMask resolved) {
    if (!(branch_mask[slot] & resolved)) return;
    branch_mask[slot] &= static_cast<BranchMask>(~resolved);
    write_shape(slot);
  }
  void rewrite_shape(unsigned slot, std::uint8_t op, std::uint8_t r1, std::uint8_t r2) {
    opcode[slot] = op; rt1[slot] = r1; rt2[slot] = r2;
    write_shape(slot);
  }
  void write_shape(unsigned slot) {
    shape[slot] = kind==QueueKind::Floating
        ? (std::uint32_t(opcode[slot]&127u)<<kBranches) | branch_mask[slot]
        : (std::uint32_t(opcode[slot]&127u)<<(kBranches+4)) | (std::uint32_t(branch_mask[slot])<<4)
          | (std::uint32_t(rt1[slot]&3u)<<2) | (rt2[slot]&3u);
  }
};
struct LsqImage {
  // load_changed / store_changed name the rows touched this cycle (any flag
  // or value); load_values_changed / store_values_changed the rows whose
  // per-row values (address, dependencies, descriptor, data) moved.  At the
  // end of the step a touched row publishes only the flags that differ from
  // the copy the record holds, and only rows with moved values rewrite those
  // fields (Core::write_lsq_control).  Publishing a row's flags only when the
  // row is touched keeps the exact timing the RTL comparison was tuned
  // against.
  QueueMask load_changed=0,store_changed=0,load_descriptor_changed=0;
  QueueMask load_values_changed=0,store_values_changed=0;
  void set_load_mask(QueueMask& field,QueueMask value) { load_changed |= field^value;field=value; }
  void set_store_mask(QueueMask& field,QueueMask value) {
    auto changed=field^value;store_changed |= changed;
    if(&field==&store_exception) {
      store_values_changed |= changed;
      for(auto rows=changed;rows;rows&=rows-1) {
        const unsigned i=__builtin_ctz(rows);auto& word=stores[i].uop_word;
        const auto bit=UINT64_C(1)<<MemoryEntry::Word::kExc;
        word=(word&~bit)|((value&(QueueMask{1}<<i)) ? bit : 0);
      }
    }
    field=value;
  }
  template<class T,class V> void set_load_value(T& field,V value,unsigned row) {
    const T next=static_cast<T>(value);
    if(field!=next) { field=next;load_changed |= QueueMask{1}<<row;load_values_changed |= QueueMask{1}<<row; }
  }
  template<class T,class V> void set_store_value(T& field,V value,unsigned row) {
    const T next=static_cast<T>(value);
    if(field!=next) { field=next;store_changed |= QueueMask{1}<<row;store_values_changed |= QueueMask{1}<<row; }
  }
  void touch_load_values(QueueMask rows) { load_changed |= rows;load_values_changed |= rows; }
  void touch_store_values(QueueMask rows) { store_changed |= rows;store_values_changed |= rows; }
  // Canonical descriptors and row controls. The setters above identify the
  // rows written once at the end of this LSU transition.
  std::array<MemoryEntry, kLsq> loads{}, stores{};
  std::array<QueueMask, kLsq> dependencies{};
  std::array<std::uint8_t, kLsq> youngest_store{};
  QueueMask load_valid = 0, load_address = 0, load_executed = 0, load_succeeded = 0;
  QueueMask store_valid = 0, store_address = 0, store_data = 0;
  QueueMask store_committed = 0, store_succeeded = 0;
  QueueMask load_virtual = 0, load_uncacheable = 0, load_exception = 0;
  QueueMask load_order_fail = 0, load_observed = 0, load_forwarded = 0;
  QueueMask store_virtual = 0, store_exception = 0;
  std::array<std::uint32_t,kLsq> load_generation{}, store_generation{};
  std::array<std::uint64_t,kLsq> load_ticket{}, store_ticket{};
  std::array<std::uint8_t,kLsq> forwarded_store{};
  std::uint8_t store_execute = 0, store_commit = 0;
  std::uint8_t load_head = 0, load_tail = 0, store_head = 0, store_tail = 0;
};

struct Image {
  // Native working state; selected contract fields are owned by module
  // transitions and the IQ/execute columns already reference the record.
  RenameImage rename;
  std::uint8_t decode_finished = 0;
  RobImage rob;
  IssueImage integer_issue, memory_issue, floating_issue;
  LsqImage lsu;
  std::array<std::uint64_t, 128> integer_registers{}, floating_registers{};
  // Early functional values are distinct from physical writeback values,
  // exactly as Small's prf_ and prf_landed views.
  std::array<std::uint64_t,128> integer_values{};
  ExecutionImage execution;
  FloatingImage floating;
  MemoryImage memory;
  std::array<std::uint64_t,boomcfg::NUM_FPREGS> floating_rec_lo{};
  std::array<std::uint8_t,boomcfg::NUM_FPREGS> floating_rec_hi{};
  GuiderCSR csr{};
  std::uint64_t retired_counter = 0, csr_flush_target = 0;
  bool trap_pending = false, trap_mini = false, trap_tval_valid = false;
  std::uint64_t trap_tval = 0;
  std::uint64_t trap_pc = 0, trap_cause = 0;
  std::uint32_t trap_instruction = 0;
  std::uint64_t cycle = 0;
};
// This is functional state, not an assertion that the retained RTL oracle
// transport layout has already been bound. That binding is a separate gate.
}  // namespace chisa::boom_model::wide
