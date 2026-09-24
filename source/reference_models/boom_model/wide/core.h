#pragma once
#include "image.h"
#include "contract.h"
#include "../common/execute.h"
#include "../common/csr_logic.h"
#include <stdexcept>

namespace chisa::boom_model::wide {
struct BranchUpdate {
  BranchMask resolved = 0, mispredicted = 0, surviving = 0;
  bool redirect = false;
  std::uint8_t tag = 0, rob = 0, load_tail = 0, store_tail = 0;
};
struct Completion {
  bool valid = false, clear_busy = false, writes_integer = false, writes_float = false;
  bool exception = false, tval_valid = false, floating_rec_valid = false;
  std::uint8_t rob = 0, pdst = 0, fflags = 0, floating_rec_hi = 0, source_port = 255;
  std::uint64_t data = 0, cause = 0, tval = 0, floating_rec_lo = 0;
};
struct Wakeup {
  bool valid = false, floating = false, speculative = false;
  std::uint8_t physical = 0;
};
struct IssueGrant {
  bool selected = false, valid = false, vacates = false, poisoned = false, squashed = false;
  int slot = -1;
  StageUop uop;
  std::uint8_t prs3 = 0;
};
struct IssueInputs {
  std::array<std::uint16_t, kWidth> integer_fu{};
  std::uint16_t memory_fu = 0, floating_fu = 0;
};
struct FtqResponse {
  bool next_valid = false, cfi_valid = false, start_bank = false;
  std::uint8_t cfi_index = 0;
  std::uint64_t next_pc = 0;
};
struct Redirect {
  bool valid = false, branch = false, taken = false, is_br = false, is_rvc = false, edge = false;
  std::uint8_t ftq = 0, pc_lob = 0, pc_select = 0;
  std::int32_t offset = 0;
  std::uint64_t pc = 0;
};
struct IntegerToFpRequest {
  bool valid = false;
  StageUop uop;
  std::uint64_t operand = 0;
};
struct CycleInputs {
  std::array<MicroOp, kWidth> decoded{};
  std::uint8_t decoded_valid = 0;
  bool debug = false, commit_allowed = true, load_miss = false;
  bool debug_interrupt = false, wfi_wakeup = false;
  // Filled from the native FP domain before integer issue arbitration.
  bool i2f_ready = false;
  FloatingInputs fp;
  MemoryInputs memory;
  FtqResponse ftq0;
  BranchUpdate branch;
  IssueInputs issue;
  std::array<Completion, 12> completions{};
  std::array<Wakeup, 12> wakeups{};
};
struct CycleOutputs {
  bool decode_accepted = false, exception = false, serializing = false, rollback_done = false;
  std::uint64_t exception_cause = 0;
  std::uint8_t exception_rob = 0, dispatched = 0;
  std::array<IssueGrant, kWidth> integer{};
  IssueGrant memory, floating;
  std::array<RetirementEvent, kWidth> retired{};
  FloatingPorts fp;
  MemoryPorts memory_ports;
  Redirect redirect;
  IntegerToFpRequest i2f;
  bool invalidate_icache = false;
  BranchUpdate branch;
  bool rob_flush = false, commit_ftq_valid = false, sys_pc2epc_valid = false;
  std::uint8_t commit_ftq = 0, sys_pc2epc = 0, flush_type = 0;
};

// Backend pipeline substrate built from Small's state-ownership and phase
// rules. Native integer/FP/LSU transitions share this image; frontend, cold
// unit binding and complete oracle integration are still separately gated.
class Core {
 public:
  Core() = delete;
  explicit Core(contract::Image& record);
  void reset();
  void begin_rollback(unsigned delay = 0);
  const GuiderCSR& csr() const { return state_.csr; }
  std::uint64_t cycle_count() const { return state_.cycle; }
  unsigned rob_head() const { return state_.rob.head; }
  unsigned rob_tail() const { return state_.rob.tail; }
  void latch_hpm_events(const HpmEventInputs& input);
  // The inputs are the caller's per-cycle object; the step patches its
  // arbitration fields in place instead of copying 1.2 KB first.
  const CycleOutputs& step(CycleInputs& input);
  const CycleOutputs& outputs() const { return output_; }
  bool rob_flush_now() const { return output_.rob_flush; }
  bool rob_exception_now() const { return output_.exception; }
  bool mem_agu_valid() const { return state_.memory.read[1].valid; }
  BranchMask pending_b1_mispredict_mask() const;
  const BranchEntry* oldest_b1_mispredict() const;
  // Side-effect-free copy of the branch resolution that prepare_execution
  // derives from this cycle's registered B1/B2 state.  A frontend thread
  // can consume it before step() runs; step() itself does not use it.
  void preview_branch(BranchUpdate& branch, Redirect& redirect) const;
  // Whether this cycle's retirement will reach a fence.i (commit() sets
  // invalidate_icache), decided from the same registered ROB state and the
  // previewed branch kill mask; no state changes.
  bool preview_fencei_retire(BranchMask killed) const;
  bool tag_live(const MemoryTag& tag, BranchMask killed, bool flush) const {
    return memory_tag_live(tag,killed,flush);
  }
  BranchMask b1_resolve_mask_now() const { return output_.branch.resolved; }
  BranchMask b1_mispred_mask_now() const { return output_.branch.mispredicted; }
  const RetirementEvent& retirement_event() const { return architectural_.event(); }
  struct SfenceRequest { bool valid, rs1, rs2; std::uint64_t address; };
  SfenceRequest sfence_request() const {
    const auto& port=output_.memory_ports;
    return {port.sfence,port.sfence_rs1,port.sfence_rs2,port.sfence_address};
  }
  MemoryPlan plan_memory(const MemoryControl& control, const BranchUpdate& branch = {}) const;
  MemoryRequest memory_request(const MemoryPlan& plan, const Translation& translation) const;
  // Static decoded metadata stays in its one ROB instruction record.
  const MicroOp& instruction(unsigned wire) const;
  const Image& image() const { return state_; }
  void export_oracles();
  const ArchitecturalState& architectural_state() const { return architectural_.state(); }
  static std::uint64_t execute_integer(const MicroOp& u, std::uint64_t a, std::uint64_t b) {
    return compute_int_result(u,a,b);
  }

  // Memory-unit callbacks carry independently computed model responses.
  void load_address(unsigned index, std::uint64_t address);
  void store_address(unsigned index, std::uint64_t address);
  void store_data(unsigned index, std::uint64_t data);
  void load_finished(unsigned index);
  void store_finished(unsigned index);
  bool drain_store(bool ordered);
  int forward_store(unsigned load, std::uint64_t address, unsigned size) const;

 private:
  friend struct CoreTestAccess;
  // Deferred record publication. The ROB row, rename lane and CSR record
  // writers read only the core state as it stands after this step, so their
  // calls are recorded as marks and replayed by publish_record(): on the
  // model's thread right after the step (equivalence mode) or from a worker
  // thread while the memory side of the cycle runs. Execute-stage and issue
  // payload writers stay inline: the record is their storage.
 public:
  void set_record_deferred(bool on) { record_deferred_ = on; }
  bool record_deferred() const { return record_deferred_; }
  void publish_record();
  // Partition-cut lanes: registers the partitioned consumer kernels read
  // across partition boundaries (per-entry ROB uop fields, STQ data words,
  // ...). Layouts without them compile these writes to no-ops; the switch
  // skips the work entirely (SYSMODEL_CUT_LANES=0).
  void set_cut_lanes(bool on) { cut_lanes_ = on; }
  bool cut_lanes() const { return cut_lanes_; }
 private:
  void finish_step_record();
  void write_rob_uop_fields(unsigned bank, unsigned row);
  void mark_rob_uop(unsigned bank, unsigned row) {
    if (record_deferred_) rob_uop_dirty_[bank] |= UINT64_C(1) << row; else write_rob_uop_fields(bank, row);
  }
  bool cut_lanes_ = true;
  std::array<std::uint64_t, kWidth> rob_uop_dirty_{};
  // The per-row LSQ flag masks as the record last received them
  // (write_lsq_control publishes the bits that differ).
  struct LsqFlags {
    QueueMask load_valid=0,load_address=0,load_virtual=0,load_uncacheable=0,load_executed=0,
        load_succeeded=0,load_order_fail=0,load_observed=0,load_forwarded=0;
    QueueMask store_valid=0,store_address=0,store_virtual=0,store_data=0,store_committed=0,store_succeeded=0;
  } lsq_flags_{};
  void write_cut_step_lanes();
  std::uint64_t oldest_exception_cause(bool& any) const;
  bool sys_pc2epc_r_ = false, exception_rr_ = false;
  std::uint64_t exc_cause_hold_ = 0, tlb_vaddr_r_ = 0, lcam_prev_addr_ = 0;
  std::uint8_t lcam_prev_rob_ = 0;
  std::uint8_t dprv_prev_ = 0, retired_count_ = 0;
  // core.scala:406 RegNext(RegNext(csr.io.evec)): the CSR unit's system
  // instruction of the cycle and the vector one cycle back.
  bool sys_insn_now_ = false;
  std::uint16_t sys_insn_addr_ = 0;
  std::uint64_t evec_r1_ = 0;
  void mark_rob_row(unsigned bank, unsigned row) {
    if (record_deferred_) rob_rows_dirty_[bank] |= UINT64_C(1) << row; else write_rob_row(bank, row);
  }
  void mark_rob_branch(unsigned bank, unsigned row) {
    if (record_deferred_) rob_branch_dirty_[bank] |= UINT64_C(1) << row; else write_rob_branch(bank, row);
  }
  void mark_rename_uop(unsigned lane) {
    if (record_deferred_) rename_dirty_ |= static_cast<std::uint8_t>(1u << lane); else write_rename_uop(lane);
  }
  void mark_csr_record() { if (record_deferred_) csr_dirty_ = true; else write_csr_record(); }
  static_assert(kRows <= 64, "ROB row dirty masks are 64-bit");
  bool record_deferred_ = false;
  std::array<std::uint64_t, kWidth> rob_rows_dirty_{}, rob_branch_dirty_{};
  std::uint8_t rename_dirty_ = 0;
  bool csr_dirty_ = false, step_batch_pending_ = false;
  contract::Image* record_ = nullptr;
  Image state_;
  CycleOutputs output_;
  ArchitecturalRetirement architectural_;
  bool held_debug_ = false;
  DividerStateView divider_state();
  void write_integer_read(unsigned port, unsigned stage, bool payload);
  void write_integer_result(unsigned port, bool payload);
  void write_branch_info(unsigned port, bool payload);
  void write_divider_uop();
  std::array<std::uint16_t,kWidth> integer_availability(bool i2f_ready) const;
  void prepare_execution(CycleInputs& input, CycleOutputs& output);
  void launch_execution(const CycleInputs& input, CycleOutputs& output);
  void publish_completion(CycleInputs& input, const Completion& completion) const;
  void publish_fp(CycleInputs& input, const FpValue& value, unsigned source_port = kWritebackPorts-1) const;
  void floating_availability(CycleInputs& input) const;
  void prepare_floating(CycleInputs& input, CycleOutputs& output, bool flush = false);
  void launch_floating(const CycleInputs& input, const CycleOutputs& output);
  void flush_floating();
  MemoryTag memory_tag(bool load, unsigned index) const;
  bool memory_tag_live(const MemoryTag& tag, BranchMask killed, bool flush) const;
  void prepare_memory(CycleInputs& input, CycleOutputs& output, bool flush = false);
  void launch_memory(const CycleInputs& input, const CycleOutputs& output);
  void flush_memory_pipeline();
  void reset_csr();
  bool csr_cycle_start();
  void csr_cycle_end(const CycleInputs& input, CycleOutputs& output);
  static unsigned dense(unsigned wire);
  static QueueMask bit(unsigned index) { return QueueMask{1} << index; }
  static QueueMask slot_mask(unsigned count) { return count == 32 ? ~QueueMask{} : bit(count)-1; }
  static bool test(QueueMask mask, unsigned index) { return (mask & bit(index)) != 0; }
  static void assign(QueueMask& mask, unsigned index, bool value) {
    mask = value ? mask | bit(index) : mask & ~bit(index);
  }
  static unsigned first(PhysicalMask mask);
  void map_write(RenameDomain& domain, unsigned logical, unsigned physical, bool floating);
  void write_rename_uop(unsigned lane);
  void write_rename_valids();
  void rename_bypass_lane(unsigned lane,bool publish=true);
  void write_rob_row(unsigned bank,unsigned row);
  void write_rob_branch(unsigned bank,unsigned row);
  void write_rob_ports();
  void write_csr_record();
  void write_core_control();
  void write_lsq_load(unsigned row,bool descriptor=false);
  void write_lsq_store(unsigned row,bool descriptor=false);
  void write_lsq_control();
  void write_fp_record();
  void write_ifpu_input();
  void write_flush_record(const MicroOp& u);
  void reset_domain(RenameDomain& domain, unsigned physical_count);
  bool accept_decode(const std::array<MicroOp,kWidth>& group, std::uint8_t mask,
                     BranchMask allocation_view, bool debug);
  void rename_dispatch(MicroOp& u, unsigned lane);
  void rename_bypass_held();
  void preselect(RenameDomain& domain, PhysicalMask pre_free, std::uint8_t consumed);
  void restore_rename(unsigned tag);
  void return_register(const MicroOp& u, bool rollback);

  IssueImage& queue(QueueKind kind);
  void bind_issue_columns();
  void write_issue_payload(IssueImage& queue, unsigned slot, const MicroOp& u);
  void select_queue(IssueImage& queue, const std::uint16_t* fu, unsigned ports, IssueGrant* grants);
  static unsigned vacancies(const IssueImage& queue);
  void wake(IssueImage& queue, const Wakeup& wakeup);
  void resolve_issue(IssueImage& queue, const BranchUpdate& update);
  // One PRE arbitration; grants survive kill/poison handling and collapse.
  void prepare_issue(CycleInputs& input, CycleOutputs& output);
  void select_issue(const CycleInputs& input, CycleOutputs& output);
  void collapse(IssueImage& queue, QueueMask pre_occupied,
                const IssueGrant* grants, unsigned ports,
                const std::array<MicroOp,kWidth>& dispatch, std::uint8_t dispatch_mask);
  void install(IssueImage& queue, unsigned slot, const MicroOp& u);
  void copy_slot(IssueImage& queue, unsigned destination, unsigned source);

  bool rob_can_dispatch() const;
  void update_rob_control(QueueMask unsafe_pre, bool empty_pre,
                          std::uint8_t head_pre, std::uint8_t tail_pre);
  void rob_enqueue(const MicroOp& u, unsigned bank, bool debug);
  void rob_close_row();
  void begin_rob_reads();
  void capture_rob_writeback_reads(const CycleInputs& input);
  bool complete(const Completion& completion);
  bool rollback_row();
  void resolve_rob(const BranchUpdate& update);
  void commit(const std::array<QueueMask,kWidth>& busy_before, bool allowed, CycleOutputs& out);
  void allocate_memory(MicroOp& u);
  bool memory_available(const MicroOp& u, unsigned load_head, unsigned store_head) const;
  void resolve_memory(const BranchUpdate& update);
  void commit_memory(const MicroOp& u, RetirementEvent& event);
};
}  // namespace chisa::boom_model::wide
