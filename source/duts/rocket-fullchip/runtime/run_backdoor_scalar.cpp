#ifndef ROCKET_DMI_LIBRARY_ONLY
#include "VTestHarness.h"
#include "VTestHarness___024root.h"
#endif

#include "dmi_host_api.h"

#include <cerrno>
#include <chrono>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

constexpr std::uint64_t kMemoryBase = UINT64_C(0x80000000);
constexpr std::uint64_t kMemoryBytes = UINT64_C(0x10000000);
constexpr std::uint64_t kDefaultTohost = UINT64_C(0x80001000);
constexpr std::uint64_t kDefaultFromhost = UINT64_C(0x80001040);
// The locked Dhrystone image uses the standard riscv-tests HTIF putchar
// wait loop, but places fromhost one 64-byte cache line after tohost.
constexpr std::uint64_t kConsoleWaitPc0 = UINT64_C(0x80001634);
constexpr std::uint64_t kConsoleWaitPc1 = UINT64_C(0x80001636);
constexpr std::uint64_t kConsoleWaitPc2 = UINT64_C(0x80001716);
constexpr std::uint64_t kConsoleWaitPc3 = UINT64_C(0x80001718);
constexpr std::uint64_t kTohostExitParkPc = UINT64_C(0x800016ae);
constexpr std::uint64_t kTrapParkPc = UINT64_C(0x800016be);
constexpr std::uint64_t kPcTriggerStableCycles = 8;

struct Options {
  std::string image;
  std::uint64_t load_address = kMemoryBase;
  std::uint64_t tohost_address = kDefaultTohost;
  std::uint64_t fromhost_address = kDefaultFromhost;
  std::uint64_t max_cycles = UINT64_C(2000000);
  std::uint64_t reset_cycles = 10;
  std::uint64_t progress_cycles = 0;
  std::uint64_t console_wait_pc0 = kConsoleWaitPc0;
  std::uint64_t console_wait_pc1 = kConsoleWaitPc1;
  std::uint64_t console_wait_pc2 = kConsoleWaitPc2;
  std::uint64_t console_wait_pc3 = kConsoleWaitPc3;
  std::uint64_t exit_park_pc = kTohostExitParkPc;
  std::uint64_t trap_park_pc = kTrapParkPc;
  std::uint64_t memory_check_address = kMemoryBase;
  std::uint64_t memory_check_bytes = UINT64_C(2) * 1024 * 1024;
  std::uint64_t expected_memory_hash = 0;
  std::uint64_t finish_alignment = 1;
};

struct DmiRequest {
  std::uint32_t address = 0;
  std::uint32_t operation = 0;
  std::uint32_t data = 0;
};

class DmiBootstrap {
 public:
  void tick(bool request_ready, bool response_valid,
            std::uint32_t response_status, std::uint32_t response_data) {
    ++ticks_;
    last_request_ready_ = request_ready;
    last_response_valid_ = response_valid;
    last_response_status_ = response_status;
    last_response_data_ = response_data;
    if (transport_ == Transport::kDone ||
        transport_ == Transport::kFailed)
      return;

    // SimDTM registers both request-valid and response-ready at the next
    // posedge.  After consuming a response at one negedge, keep the next
    // request suppressed until the old response-valid has visibly dropped;
    // otherwise the previous read data can be attributed to the new request.
    if (transport_ == Transport::kDraining) {
      if (response_valid) return;
      transport_ = Transport::kSending;
      // debug_tick will expose request-valid immediately after this return;
      // mark that presentation now so the next negedge can withdraw it in
      // time for exactly one target posedge acceptance.
      request_age_ = 1;
      return;
    }

    if (transport_ == Transport::kSending) {
      // Keep response-ready low until this request has been presented for a
      // complete registered SimDTM cycle.  A one-beat target may replace
      // req_ready with resp_valid immediately; either signal then proves the
      // request reached the target, but the response is consumed only from
      // kWaiting so it cannot be mistaken for the preceding transaction.
      if (request_age_ != 0 && response_valid) {
        accept_response(response_status, response_data);
        return;
      }
      if (request_age_ != 0 && request_ready)
        transport_ = Transport::kWaiting;
      ++request_age_;
      return;
    }
    if (transport_ != Transport::kWaiting || !response_valid) return;

    accept_response(response_status, response_data);
  }

  void accept_response(std::uint32_t response_status,
                       std::uint32_t response_data) {

    if (std::getenv("ROCKET_DMI_DEBUG") != nullptr) {
      std::fprintf(stderr,
                   "ROCKET_DMI_RESPONSE stage=%s request=%02" PRIx32
                   "/%" PRIu32 "/%08" PRIx32 " status=%" PRIu32
                   " data=%08" PRIx32 " ticks=%" PRIu64 "\n",
                   stage_name(), request_.address, request_.operation,
                   request_.data, response_status, response_data, ticks_);
    }

    if (response_status == 1 || response_status == 3) {
      // Rocket's DMIToTL encodes a temporarily denied TileLink response as
      // 1.  This occurs while dmInner's asynchronous crossing leaves reset;
      // 3 is the standard DMI busy response.  Retry either, but never allow
      // a bad address to spin forever.
      if (++transport_retries_ > 4096) {
        fail("DMI retry limit exceeded");
        return;
      }
      transport_ = Transport::kDraining;
      request_age_ = 0;
      return;
    }
    if (response_status != 0) {
      char detail[192];
      std::snprintf(
          detail, sizeof(detail),
          "DMI response failure stage=%s status=%" PRIu32
          " data=0x%08" PRIx32 " request={addr=0x%02" PRIx32
          " op=%" PRIu32 " data=0x%08" PRIx32 "} ticks=%" PRIu64,
          stage_name(), response_status, response_data, request_.address,
          request_.operation, request_.data, ticks_);
      fail(detail);
      return;
    }
    transport_retries_ = 0;
    ++completed_transactions_;
    accepting_response_ = true;
    complete_stage(response_data);
    accepting_response_ = false;
  }

  bool request_valid() const { return transport_ == Transport::kSending; }
  bool response_ready() const {
    return transport_ == Transport::kSending ||
           transport_ == Transport::kWaiting ||
           transport_ == Transport::kDraining;
  }
  const DmiRequest& request() const { return request_; }
  bool done() const { return transport_ == Transport::kDone; }
  bool bootstrap_complete() const { return bootstrap_complete_; }
  bool failed() const { return transport_ == Transport::kFailed; }
  const std::string& error() const { return error_; }
  std::uint64_t completed_transactions() const {
    return completed_transactions_;
  }
  std::uint32_t last_dmstatus() const { return last_dmstatus_; }
  std::uint64_t ticks() const { return ticks_; }
  bool last_request_ready() const { return last_request_ready_; }
  bool last_response_valid() const { return last_response_valid_; }
  std::uint32_t last_response_status() const {
    return last_response_status_;
  }
  std::uint32_t last_response_data() const { return last_response_data_; }
  std::uint64_t console_acks_completed() const {
    return console_acks_completed_;
  }
  std::uint64_t tohost_reads_completed() const {
    return tohost_reads_completed_;
  }
  std::uint64_t last_tohost_read() const { return last_tohost_read_; }
  std::uint32_t last_tohost_data0() const { return service_read_low_; }
  std::uint32_t last_tohost_data1() const { return service_read_high_; }

  void configure_addresses(std::uint64_t entry, std::uint64_t tohost,
                           std::uint64_t fromhost) {
    if (ticks_ != 0)
      throw std::logic_error("DMI addresses must be configured before eval");
    if (fromhost - tohost != 64)
      throw std::invalid_argument(
          "the cache-coherent HTIF ack program requires fromhost=tohost+64");
    entry_address_ = entry;
    tohost_address_ = tohost;
    fromhost_address_ = fromhost;
  }

  void request_console_ack() {
    require_idle("console acknowledgement");
    job_ = Job::kConsoleAck;
    service_address_ = fromhost_address_;
    start(Stage::kServiceHalt, kDmcontrol, kDmiWrite,
          UINT32_C(0x80000001));
  }

  void request_tohost_read() {
    require_idle("tohost read");
    job_ = Job::kReadTohost;
    service_address_ = tohost_address_;
    start(Stage::kServiceHalt, kDmcontrol, kDmiWrite,
          UINT32_C(0x80000001));
  }

  const char* stage_name() const {
    switch (stage_) {
      case Stage::kActivate: return "activate";
      case Stage::kHalt: return "halt";
      case Stage::kPollHalted: return "poll-halted";
      case Stage::kWriteData0: return "write-data0";
      case Stage::kWriteData1: return "write-data1";
      case Stage::kWriteGprCommand: return "write-gpr-command";
      case Stage::kPollGprCommand: return "poll-gpr-command";
      case Stage::kWriteProgbuf0: return "write-progbuf0";
      case Stage::kWriteProgbuf1: return "write-progbuf1";
      case Stage::kWritePostexecCommand: return "write-postexec-command";
      case Stage::kPollPostexecCommand: return "poll-postexec-command";
      case Stage::kResume: return "resume";
      case Stage::kPollResumeAck: return "poll-resume-ack";
      case Stage::kClearResume: return "clear-resume";
      case Stage::kPollRunning: return "poll-running";
      case Stage::kServiceHalt: return "service-halt";
      case Stage::kServicePollHalted: return "service-poll-halted";
      case Stage::kServiceWriteAddressData0: return "service-address-data0";
      case Stage::kServiceWriteAddressData1: return "service-address-data1";
      case Stage::kServiceWriteAddressCommand: return "service-address-command";
      case Stage::kServicePollAddressCommand: return "service-poll-address";
      case Stage::kAckWriteValueData0: return "ack-value-data0";
      case Stage::kAckWriteValueData1: return "ack-value-data1";
      case Stage::kAckWriteValueCommand: return "ack-value-command";
      case Stage::kAckPollValueCommand: return "ack-poll-value";
      case Stage::kAckWriteProgbuf0: return "ack-progbuf0";
      case Stage::kAckWriteProgbuf1: return "ack-progbuf1";
      case Stage::kAckWriteProgbuf2: return "ack-progbuf2";
      case Stage::kAckWriteProgbuf3: return "ack-progbuf3";
      case Stage::kAckWriteProgbuf4: return "ack-progbuf4";
      case Stage::kAckWriteProgbuf5: return "ack-progbuf5";
      case Stage::kAckWriteCommand: return "ack-command";
      case Stage::kAckPollCommand: return "ack-poll-command";
      case Stage::kAckResume: return "ack-resume";
      case Stage::kAckPollResumeAck: return "ack-poll-resume-ack";
      case Stage::kAckClearResume: return "ack-clear-resume";
      case Stage::kAckPollRunning: return "ack-poll-running";
      case Stage::kReadWriteProgbuf0: return "read-progbuf0";
      case Stage::kReadWriteProgbuf1: return "read-progbuf1";
      case Stage::kReadWriteCommand: return "read-load-command";
      case Stage::kReadPollCommand: return "read-poll-load";
      case Stage::kReadWriteGprCommand: return "read-gpr-command";
      case Stage::kReadPollGprCommand: return "read-poll-gpr";
      case Stage::kReadData0: return "read-data0";
      case Stage::kReadData1: return "read-data1";
      case Stage::kIdle: return "idle";
    }
    return "invalid";
  }

 private:
  enum class Transport { kSending, kWaiting, kDraining, kDone, kFailed };
  enum class Job { kBootstrap, kConsoleAck, kReadTohost, kIdle };
  enum class Stage {
    kActivate,
    kHalt,
    kPollHalted,
    kWriteData0,
    kWriteData1,
    kWriteGprCommand,
    kPollGprCommand,
    kWriteProgbuf0,
    kWriteProgbuf1,
    kWritePostexecCommand,
    kPollPostexecCommand,
    kResume,
    kPollResumeAck,
    kClearResume,
    kPollRunning,
    kServiceHalt,
    kServicePollHalted,
    kServiceWriteAddressData0,
    kServiceWriteAddressData1,
    kServiceWriteAddressCommand,
    kServicePollAddressCommand,
    kAckWriteValueData0,
    kAckWriteValueData1,
    kAckWriteValueCommand,
    kAckPollValueCommand,
    kAckWriteProgbuf0,
    kAckWriteProgbuf1,
    kAckWriteProgbuf2,
    kAckWriteProgbuf3,
    kAckWriteProgbuf4,
    kAckWriteProgbuf5,
    kAckWriteCommand,
    kAckPollCommand,
    kAckResume,
    kAckPollResumeAck,
    kAckClearResume,
    kAckPollRunning,
    kReadWriteProgbuf0,
    kReadWriteProgbuf1,
    kReadWriteCommand,
    kReadPollCommand,
    kReadWriteGprCommand,
    kReadPollGprCommand,
    kReadData0,
    kReadData1,
    kIdle,
  };

  static constexpr std::uint32_t kDmcontrol = 0x10;
  static constexpr std::uint32_t kDmstatus = 0x11;
  static constexpr std::uint32_t kAbstractcs = 0x16;
  static constexpr std::uint32_t kCommand = 0x17;
  static constexpr std::uint32_t kData0 = 0x04;
  static constexpr std::uint32_t kData1 = 0x05;
  static constexpr std::uint32_t kProgbuf0 = 0x20;
  static constexpr std::uint32_t kProgbuf1 = 0x21;
  static constexpr std::uint32_t kProgbuf2 = 0x22;
  static constexpr std::uint32_t kProgbuf3 = 0x23;
  static constexpr std::uint32_t kProgbuf4 = 0x24;
  static constexpr std::uint32_t kProgbuf5 = 0x25;
  static constexpr std::uint32_t kDmiRead = 1;
  static constexpr std::uint32_t kDmiWrite = 2;
  // The Rocket debug module implements abstract register access only for
  // GPRs.  Put the entry address in t0, then execute `csrw dpc, t0` from the
  // program buffer.  An explicit ebreak returns the hart to halted state.
  static constexpr std::uint32_t kWriteT0Command = UINT32_C(0x00331005);
  static constexpr std::uint32_t kCsrwDpcT0 = UINT32_C(0x7b129073);
  static constexpr std::uint32_t kEbreak = UINT32_C(0x00100073);
  static constexpr std::uint32_t kPostexecCommand = UINT32_C(0x00040000);
  static constexpr std::uint32_t kWriteT1Command = UINT32_C(0x00331006);
  static constexpr std::uint32_t kReadT1Command = UINT32_C(0x00321006);
  static constexpr std::uint32_t kAddiT0Minus64 = UINT32_C(0xfc028293);
  static constexpr std::uint32_t kStoreZeroAtT0 = UINT32_C(0x0002b023);
  static constexpr std::uint32_t kAddiT0Plus64 = UINT32_C(0x04028293);
  static constexpr std::uint32_t kStoreT1AtT0 = UINT32_C(0x0062b023);
  static constexpr std::uint32_t kLoadT1AtT0 = UINT32_C(0x0002b303);
  static constexpr std::uint32_t kFence = UINT32_C(0x0ff0000f);
  static constexpr std::uint32_t kMaxAbstractPolls = 4096;

  void start(Stage stage, std::uint32_t address, std::uint32_t operation,
             std::uint32_t data = 0) {
    stage_ = stage;
    request_ = DmiRequest{address, operation, data};
    transport_ = accepting_response_ ? Transport::kDraining
                                     : Transport::kSending;
    request_age_ = 0;
  }

  void fail(const std::string& message) {
    error_ = message;
    transport_ = Transport::kFailed;
  }

  void require_idle(const char* operation) const {
    if (!bootstrap_complete_ || transport_ != Transport::kDone ||
        job_ != Job::kIdle) {
      throw std::logic_error(std::string("cannot start DMI ") + operation +
                             " while another job is active");
    }
  }

  void finish_job() {
    job_ = Job::kIdle;
    stage_ = Stage::kIdle;
    transport_ = Transport::kDone;
  }

  void begin_abstract_poll(Stage stage) {
    abstract_busy_seen_ = false;
    abstract_poll_reads_ = 0;
    start(stage, kAbstractcs, kDmiRead);
  }

  bool abstract_complete(std::uint32_t response_data, const char* command) {
    ++abstract_poll_reads_;
    const std::uint32_t command_error = (response_data >> 8) & 7;
    if (command_error != 0) {
      char detail[160];
      std::snprintf(detail, sizeof(detail),
                    "%s returned abstract cmderr=%" PRIu32,
                    command, command_error);
      fail(detail);
      return false;
    }

    const bool busy = (response_data & (UINT32_C(1) << 12)) != 0;
    abstract_busy_seen_ = abstract_busy_seen_ || busy;
    if (busy || !abstract_busy_seen_) {
      if (abstract_poll_reads_ >= kMaxAbstractPolls) {
        fail(std::string(command) + " never completed a busy/idle handshake");
        return false;
      }
      start(stage_, kAbstractcs, kDmiRead);
      return false;
    }
    return true;
  }

  void complete_stage(std::uint32_t response_data) {
    switch (stage_) {
      case Stage::kActivate:
        start(Stage::kHalt, kDmcontrol, kDmiWrite, UINT32_C(0x80000001));
        return;
      case Stage::kHalt:
        start(Stage::kPollHalted, kDmstatus, kDmiRead);
        return;
      case Stage::kPollHalted:
        last_dmstatus_ = response_data;
        if ((response_data & (UINT32_C(1) << 7)) == 0) {
          fail("debug module is not authenticated");
          return;
        }
        if ((response_data & (UINT32_C(1) << 9)) == 0) {
          start(Stage::kPollHalted, kDmstatus, kDmiRead);
          return;
        }
        start(Stage::kWriteData0, kData0, kDmiWrite,
              static_cast<std::uint32_t>(entry_address_));
        return;
      case Stage::kWriteData0:
        start(Stage::kWriteData1, kData1, kDmiWrite,
              static_cast<std::uint32_t>(entry_address_ >> 32));
        return;
      case Stage::kWriteData1:
        // Access Register: aarsize=64, transfer=1, write=1, regno=x5/t0.
        start(Stage::kWriteGprCommand, kCommand, kDmiWrite,
              kWriteT0Command);
        return;
      case Stage::kWriteGprCommand:
        begin_abstract_poll(Stage::kPollGprCommand);
        return;
      case Stage::kPollGprCommand:
        if (!abstract_complete(response_data, "abstract t0 write")) return;
        start(Stage::kWriteProgbuf0, kProgbuf0, kDmiWrite, kCsrwDpcT0);
        return;
      case Stage::kWriteProgbuf0:
        start(Stage::kWriteProgbuf1, kProgbuf1, kDmiWrite, kEbreak);
        return;
      case Stage::kWriteProgbuf1:
        start(Stage::kWritePostexecCommand, kCommand, kDmiWrite,
              kPostexecCommand);
        return;
      case Stage::kWritePostexecCommand:
        begin_abstract_poll(Stage::kPollPostexecCommand);
        return;
      case Stage::kPollPostexecCommand:
        if (!abstract_complete(response_data, "program-buffer dpc write"))
          return;
        start(Stage::kResume, kDmcontrol, kDmiWrite,
              UINT32_C(0x40000001));
        return;
      case Stage::kResume:
        start(Stage::kPollResumeAck, kDmstatus, kDmiRead);
        return;
      case Stage::kPollResumeAck:
        last_dmstatus_ = response_data;
        if ((response_data & (UINT32_C(1) << 17)) == 0) {
          start(Stage::kPollResumeAck, kDmstatus, kDmiRead);
          return;
        }
        start(Stage::kClearResume, kDmcontrol, kDmiWrite, 1);
        return;
      case Stage::kClearResume:
        start(Stage::kPollRunning, kDmstatus, kDmiRead);
        return;
      case Stage::kPollRunning:
        last_dmstatus_ = response_data;
        if ((response_data & (UINT32_C(1) << 11)) == 0) {
          start(Stage::kPollRunning, kDmstatus, kDmiRead);
          return;
        }
        bootstrap_complete_ = true;
        finish_job();
        return;

      case Stage::kServiceHalt:
        start(Stage::kServicePollHalted, kDmstatus, kDmiRead);
        return;
      case Stage::kServicePollHalted:
        last_dmstatus_ = response_data;
        if ((response_data & (UINT32_C(1) << 9)) == 0) {
          start(Stage::kServicePollHalted, kDmstatus, kDmiRead);
          return;
        }
        start(Stage::kServiceWriteAddressData0, kData0, kDmiWrite,
              static_cast<std::uint32_t>(service_address_));
        return;
      case Stage::kServiceWriteAddressData0:
        start(Stage::kServiceWriteAddressData1, kData1, kDmiWrite,
              static_cast<std::uint32_t>(service_address_ >> 32));
        return;
      case Stage::kServiceWriteAddressData1:
        start(Stage::kServiceWriteAddressCommand, kCommand, kDmiWrite,
              kWriteT0Command);
        return;
      case Stage::kServiceWriteAddressCommand:
        begin_abstract_poll(Stage::kServicePollAddressCommand);
        return;
      case Stage::kServicePollAddressCommand:
        if (!abstract_complete(response_data, "service address write"))
          return;
        if (job_ == Job::kConsoleAck) {
          start(Stage::kAckWriteValueData0, kData0, kDmiWrite, 1);
          return;
        }
        if (job_ == Job::kReadTohost) {
          start(Stage::kReadWriteProgbuf0, kProgbuf0, kDmiWrite,
                kLoadT1AtT0);
          return;
        }
        fail("invalid DMI service job after address write");
        return;

      case Stage::kAckWriteValueData0:
        start(Stage::kAckWriteValueData1, kData1, kDmiWrite, 0);
        return;
      case Stage::kAckWriteValueData1:
        start(Stage::kAckWriteValueCommand, kCommand, kDmiWrite,
              kWriteT1Command);
        return;
      case Stage::kAckWriteValueCommand:
        begin_abstract_poll(Stage::kAckPollValueCommand);
        return;
      case Stage::kAckPollValueCommand:
        if (!abstract_complete(response_data, "console ack value write"))
          return;
        // t0 initially contains fromhost.  The program clears tohost one
        // cache line below it, restores t0, writes fromhost=1, fences, and
        // returns to Debug Mode.  These stores run through the real D-cache.
        start(Stage::kAckWriteProgbuf0, kProgbuf0, kDmiWrite,
              kAddiT0Minus64);
        return;
      case Stage::kAckWriteProgbuf0:
        start(Stage::kAckWriteProgbuf1, kProgbuf1, kDmiWrite,
              kStoreZeroAtT0);
        return;
      case Stage::kAckWriteProgbuf1:
        start(Stage::kAckWriteProgbuf2, kProgbuf2, kDmiWrite,
              kAddiT0Plus64);
        return;
      case Stage::kAckWriteProgbuf2:
        start(Stage::kAckWriteProgbuf3, kProgbuf3, kDmiWrite,
              kStoreT1AtT0);
        return;
      case Stage::kAckWriteProgbuf3:
        start(Stage::kAckWriteProgbuf4, kProgbuf4, kDmiWrite, kFence);
        return;
      case Stage::kAckWriteProgbuf4:
        start(Stage::kAckWriteProgbuf5, kProgbuf5, kDmiWrite, kEbreak);
        return;
      case Stage::kAckWriteProgbuf5:
        start(Stage::kAckWriteCommand, kCommand, kDmiWrite,
              kPostexecCommand);
        return;
      case Stage::kAckWriteCommand:
        begin_abstract_poll(Stage::kAckPollCommand);
        return;
      case Stage::kAckPollCommand:
        if (!abstract_complete(response_data, "console ack program")) return;
        start(Stage::kAckResume, kDmcontrol, kDmiWrite,
              UINT32_C(0x40000001));
        return;
      case Stage::kAckResume:
        start(Stage::kAckPollResumeAck, kDmstatus, kDmiRead);
        return;
      case Stage::kAckPollResumeAck:
        last_dmstatus_ = response_data;
        if ((response_data & (UINT32_C(1) << 17)) == 0) {
          start(Stage::kAckPollResumeAck, kDmstatus, kDmiRead);
          return;
        }
        start(Stage::kAckClearResume, kDmcontrol, kDmiWrite, 1);
        return;
      case Stage::kAckClearResume:
        start(Stage::kAckPollRunning, kDmstatus, kDmiRead);
        return;
      case Stage::kAckPollRunning:
        last_dmstatus_ = response_data;
        if ((response_data & (UINT32_C(1) << 11)) == 0) {
          start(Stage::kAckPollRunning, kDmstatus, kDmiRead);
          return;
        }
        ++console_acks_completed_;
        finish_job();
        return;

      case Stage::kReadWriteProgbuf0:
        start(Stage::kReadWriteProgbuf1, kProgbuf1, kDmiWrite, kEbreak);
        return;
      case Stage::kReadWriteProgbuf1:
        start(Stage::kReadWriteCommand, kCommand, kDmiWrite,
              kPostexecCommand);
        return;
      case Stage::kReadWriteCommand:
        begin_abstract_poll(Stage::kReadPollCommand);
        return;
      case Stage::kReadPollCommand:
        if (!abstract_complete(response_data, "tohost load program")) return;
        start(Stage::kReadWriteGprCommand, kCommand, kDmiWrite,
              kReadT1Command);
        return;
      case Stage::kReadWriteGprCommand:
        begin_abstract_poll(Stage::kReadPollGprCommand);
        return;
      case Stage::kReadPollGprCommand:
        if (!abstract_complete(response_data, "tohost result read")) return;
        start(Stage::kReadData0, kData0, kDmiRead);
        return;
      case Stage::kReadData0:
        service_read_low_ = response_data;
        start(Stage::kReadData1, kData1, kDmiRead);
        return;
      case Stage::kReadData1:
        service_read_high_ = response_data;
        last_tohost_read_ = service_read_low_ |
                            (static_cast<std::uint64_t>(response_data) << 32);
        ++tohost_reads_completed_;
        finish_job();
        return;

      case Stage::kIdle:
        fail("DMI response arrived while idle");
        return;
    }
  }

  Stage stage_ = Stage::kActivate;
  Transport transport_ = Transport::kSending;
  Job job_ = Job::kBootstrap;
  DmiRequest request_{kDmcontrol, kDmiWrite, 1};
  std::string error_;
  std::uint64_t completed_transactions_ = 0;
  std::uint32_t last_dmstatus_ = 0;
  std::uint64_t ticks_ = 0;
  bool last_request_ready_ = false;
  bool last_response_valid_ = false;
  std::uint32_t last_response_status_ = 0;
  std::uint32_t last_response_data_ = 0;
  std::uint64_t request_age_ = 0;
  std::uint32_t transport_retries_ = 0;
  bool accepting_response_ = false;
  bool abstract_busy_seen_ = false;
  std::uint32_t abstract_poll_reads_ = 0;
  bool bootstrap_complete_ = false;
  std::uint64_t service_address_ = 0;
  std::uint64_t entry_address_ = kMemoryBase;
  std::uint64_t tohost_address_ = kDefaultTohost;
  std::uint64_t fromhost_address_ = kDefaultFromhost;
  std::uint64_t console_acks_completed_ = 0;
  std::uint64_t tohost_reads_completed_ = 0;
  std::uint32_t service_read_low_ = 0;
  std::uint32_t service_read_high_ = 0;
  std::uint64_t last_tohost_read_ = 0;
};

DmiBootstrap g_dmi_bootstrap;

}  // namespace

namespace chisa::rocket_fullchip {

void dmi_host_configure(std::uint64_t entry, std::uint64_t tohost,
                        std::uint64_t fromhost) {
  g_dmi_bootstrap.configure_addresses(entry, tohost, fromhost);
}

void dmi_host_advance(bool request_ready, bool response_valid,
                      std::uint32_t response_status,
                      std::uint32_t response_data) {
  g_dmi_bootstrap.tick(request_ready, response_valid, response_status,
                       response_data);
}

DmiHostOutputs dmi_host_outputs() {
  const DmiRequest& request = g_dmi_bootstrap.request();
  return DmiHostOutputs{g_dmi_bootstrap.request_valid(), request.address,
                        request.operation, request.data,
                        g_dmi_bootstrap.response_ready()};
}

bool dmi_host_bootstrap_complete() {
  return g_dmi_bootstrap.bootstrap_complete();
}
bool dmi_host_idle() { return g_dmi_bootstrap.done(); }
bool dmi_host_failed() { return g_dmi_bootstrap.failed(); }
const char* dmi_host_error() { return g_dmi_bootstrap.error().c_str(); }
const char* dmi_host_stage() { return g_dmi_bootstrap.stage_name(); }
std::uint64_t dmi_host_transactions() {
  return g_dmi_bootstrap.completed_transactions();
}
std::uint64_t dmi_host_console_acks() {
  return g_dmi_bootstrap.console_acks_completed();
}
std::uint64_t dmi_host_tohost_reads() {
  return g_dmi_bootstrap.tohost_reads_completed();
}
std::uint64_t dmi_host_last_tohost() {
  return g_dmi_bootstrap.last_tohost_read();
}
void dmi_host_request_console_ack() {
  g_dmi_bootstrap.request_console_ack();
}
void dmi_host_request_tohost_read() {
  g_dmi_bootstrap.request_tohost_read();
}

}  // namespace chisa::rocket_fullchip

#ifndef ROCKET_DMI_LIBRARY_ONLY

namespace {

[[noreturn]] void usage(const char* program) {
  std::fprintf(
      stderr,
      "usage: %s --image PATH [--max-cycles N] [--reset-cycles N] "
      "[--progress-cycles N] [--load-address N] [--tohost-address N] "
      "[--fromhost-address N] [--console-wait-pc0 N] "
      "[--console-wait-pc1 N] [--console-wait-pc2 N] "
      "[--console-wait-pc3 N] [--exit-park-pc N] [--trap-park-pc N] "
      "[--memory-check-address N] [--memory-check-bytes N] "
      "[--expected-memory-hash N] [--finish-alignment N]\n",
      program);
  std::exit(2);
}

std::uint64_t parse_u64(const char* value, const char* option) {
  char* end = nullptr;
  errno = 0;
  const unsigned long long parsed = std::strtoull(value, &end, 0);
  if (errno != 0 || end == value || *end != '\0')
    throw std::invalid_argument(std::string("invalid ") + option + ": " + value);
  return static_cast<std::uint64_t>(parsed);
}

Options parse_options(int argc, char** argv) {
  Options options;
  for (int index = 1; index < argc; ++index) {
    const std::string option = argv[index];
    if (option == "--help") usage(argv[0]);
    if (index + 1 >= argc) usage(argv[0]);
    const char* value = argv[++index];
    if (option == "--image")
      options.image = value;
    else if (option == "--max-cycles")
      options.max_cycles = parse_u64(value, option.c_str());
    else if (option == "--reset-cycles")
      options.reset_cycles = parse_u64(value, option.c_str());
    else if (option == "--progress-cycles")
      options.progress_cycles = parse_u64(value, option.c_str());
    else if (option == "--load-address")
      options.load_address = parse_u64(value, option.c_str());
    else if (option == "--tohost-address")
      options.tohost_address = parse_u64(value, option.c_str());
    else if (option == "--fromhost-address")
      options.fromhost_address = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc0")
      options.console_wait_pc0 = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc1")
      options.console_wait_pc1 = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc2")
      options.console_wait_pc2 = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc3")
      options.console_wait_pc3 = parse_u64(value, option.c_str());
    else if (option == "--exit-park-pc")
      options.exit_park_pc = parse_u64(value, option.c_str());
    else if (option == "--trap-park-pc")
      options.trap_park_pc = parse_u64(value, option.c_str());
    else if (option == "--memory-check-address")
      options.memory_check_address = parse_u64(value, option.c_str());
    else if (option == "--memory-check-bytes")
      options.memory_check_bytes = parse_u64(value, option.c_str());
    else if (option == "--expected-memory-hash")
      options.expected_memory_hash = parse_u64(value, option.c_str());
    else if (option == "--finish-alignment")
      options.finish_alignment = parse_u64(value, option.c_str());
    else
      usage(argv[0]);
  }
  if (options.image.empty()) usage(argv[0]);
  if (options.max_cycles == 0)
    throw std::invalid_argument("--max-cycles must be positive");
  if (options.finish_alignment == 0 ||
      options.max_cycles % options.finish_alignment != 0)
    throw std::invalid_argument(
        "--finish-alignment must be positive and divide --max-cycles");
  if (options.memory_check_address < kMemoryBase ||
      options.memory_check_bytes == 0 ||
      options.memory_check_bytes > kMemoryBytes ||
      options.memory_check_address - kMemoryBase >
          kMemoryBytes - options.memory_check_bytes)
    throw std::invalid_argument("memory check range is outside SimAXIMem");
  return options;
}

std::vector<std::uint8_t> read_image(const std::string& path) {
  std::ifstream source(path, std::ios::binary | std::ios::ate);
  if (!source) throw std::runtime_error("cannot open image: " + path);
  const std::streamoff size = source.tellg();
  if (size < 0 || static_cast<std::uint64_t>(size) > kMemoryBytes)
    throw std::runtime_error("invalid or oversized image: " + path);
  source.seekg(0);
  std::vector<std::uint8_t> bytes(static_cast<std::size_t>(size));
  if (!bytes.empty()) {
    source.read(reinterpret_cast<char*>(bytes.data()), size);
    if (!source) throw std::runtime_error("short read from image: " + path);
  }
  return bytes;
}

std::size_t word_index(std::uint64_t address) {
  if (address < kMemoryBase || address >= kMemoryBase + kMemoryBytes)
    throw std::out_of_range("physical address is outside SimAXIMem");
  return static_cast<std::size_t>((address - kMemoryBase) >> 3);
}

#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
auto& memory_bank(VTestHarness___024root& root, unsigned bank) {
  switch (bank) {
    case 0: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_0;
    case 1: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_1;
    case 2: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_2;
    case 3: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_3;
    case 4: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_4;
    case 5: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_5;
    case 6: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_6;
    default: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_7;
  }
}

const auto& memory_bank(const VTestHarness___024root& root, unsigned bank) {
  switch (bank) {
    case 0: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_0;
    case 1: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_1;
    case 2: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_2;
    case 3: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_3;
    case 4: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_4;
    case 5: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_5;
    case 6: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_6;
    default: return root.TestHarness__DOT__mem__DOT__srams__DOT__mem_7;
  }
}
#else
auto& memory(VTestHarness___024root& root) {
  return root.TestHarness__DOT__mem__DOT__srams__DOT__mem__DOT__mem_ext__DOT__ram;
}

const auto& memory(const VTestHarness___024root& root) {
  return root.TestHarness__DOT__mem__DOT__srams__DOT__mem__DOT__mem_ext__DOT__ram;
}
#endif

std::uint64_t read_word(const VTestHarness___024root& root,
                        std::uint64_t address) {
  if ((address & 7) != 0)
    throw std::invalid_argument("unaligned 64-bit backdoor read");
#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
  std::uint64_t value = 0;
  const std::size_t index = word_index(address);
  for (unsigned bank = 0; bank < 8; ++bank)
    value |= static_cast<std::uint64_t>(memory_bank(root, bank)[index])
             << (8 * bank);
  return value;
#else
  return static_cast<std::uint64_t>(memory(root)[word_index(address)]);
#endif
}

void write_word(VTestHarness___024root& root, std::uint64_t address,
                std::uint64_t value) {
  if ((address & 7) != 0)
    throw std::invalid_argument("unaligned 64-bit backdoor write");
#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
  const std::size_t index = word_index(address);
  for (unsigned bank = 0; bank < 8; ++bank)
    memory_bank(root, bank)[index] =
        static_cast<std::uint8_t>(value >> (8 * bank));
#else
  memory(root)[word_index(address)] = value;
#endif
}

void load_image(VTestHarness___024root& root, std::uint64_t address,
                const std::vector<std::uint8_t>& bytes) {
  if (address < kMemoryBase || bytes.size() > kMemoryBytes ||
      address - kMemoryBase > kMemoryBytes - bytes.size())
    throw std::out_of_range("image does not fit in SimAXIMem");
  for (std::size_t byte = 0; byte < bytes.size(); ++byte) {
    const std::uint64_t physical = address + byte;
    const std::uint64_t aligned = physical & ~UINT64_C(7);
    const unsigned shift = static_cast<unsigned>((physical & 7) * 8);
    const std::uint64_t mask = UINT64_C(0xff) << shift;
    const std::uint64_t old = read_word(root, aligned);
    write_word(root, aligned,
               (old & ~mask) |
                   (static_cast<std::uint64_t>(bytes[byte]) << shift));
  }
}

std::uint64_t hash_memory(const VTestHarness___024root& root,
                          std::uint64_t address, std::uint64_t bytes) {
  std::uint64_t hash = UINT64_C(1469598103934665603);
  for (std::uint64_t offset = 0; offset < bytes; ++offset) {
    const std::uint64_t physical = address + offset;
    const std::size_t index = word_index(physical);
    const unsigned bank = static_cast<unsigned>(physical & 7);
#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
    hash ^= static_cast<std::uint64_t>(memory_bank(root, bank)[index]);
#else
    hash ^= (static_cast<std::uint64_t>(memory(root)[index]) >> (bank * 8)) &
            UINT64_C(0xff);
#endif
    hash *= UINT64_C(1099511628211);
  }
  return hash;
}

std::uint64_t observed_pc(const VTestHarness___024root& root) {
  return static_cast<std::uint64_t>(
#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc);
#else
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain_tile__DOT__core__DOT__wb_reg_pc);
#endif
}

std::uint64_t observed_dpc(const VTestHarness___024root& root) {
  return static_cast<std::uint64_t>(
#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dpc);
#else
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain_tile__DOT__core__DOT__csr__DOT__reg_dpc);
#endif
}

std::uint64_t observed_x(const VTestHarness___024root& root,
                         unsigned register_index) {
  if (register_index == 0) return 0;
  if (register_index >= 32)
    throw std::out_of_range("integer register index is outside x0..x31");
  return static_cast<std::uint64_t>(
#if defined(ROCKET_FIRRTL_VERILOG_LAYOUT)
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf[31 - register_index]);
#else
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain_tile__DOT__core__DOT__rf[31 - register_index]);
#endif
}

struct DmiFeedback {
  bool request_ready = false;
  bool response_valid = false;
  std::uint32_t response_status = 0;
  std::uint32_t response_data = 0;
};

void drive_verilator_dmi(
    VTestHarness___024root& root,
    const chisa::rocket_fullchip::DmiHostOutputs& outputs) {
  root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg =
      outputs.request_valid;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg =
      outputs.request_address;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg =
      outputs.request_operation;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg =
      outputs.request_data;
  root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg =
      outputs.response_ready;
  root.TestHarness__DOT__SimDTM__DOT__exit_reg = 0;
}

DmiFeedback verilator_dmi_feedback(const VTestHarness___024root& root) {
  return DmiFeedback{
      root.TestHarness__DOT__SimDTM_debug_req_ready != 0,
      root.TestHarness__DOT__SimDTM_debug_resp_valid != 0,
      static_cast<std::uint32_t>(
          root.TestHarness__DOT__SimDTM_debug_resp_bits_resp),
      static_cast<std::uint32_t>(
          root.TestHarness__DOT__SimDTM_debug_resp_bits_data)};
}

}  // namespace

// The public SimDTM output registers are driven by the same explicit DMI host
// used by the CHISA producer and W=1 differential.  Keep the DPI callback
// inert; otherwise its negedge state machine introduces a different input
// phase and makes the Verilator control execute a different cycle trace.
extern "C" int debug_tick(svBit* debug_req_valid, svBit debug_req_ready,
                          int* debug_req_bits_addr, int* debug_req_bits_op,
                          int* debug_req_bits_data, svBit debug_resp_valid,
                          svBit* debug_resp_ready, int debug_resp_bits_resp,
                          int debug_resp_bits_data) {
  (void)debug_req_ready;
  (void)debug_resp_valid;
  (void)debug_resp_bits_resp;
  (void)debug_resp_bits_data;
  *debug_req_valid = 0;
  *debug_req_bits_addr = 0;
  *debug_req_bits_op = 0;
  *debug_req_bits_data = 0;
  *debug_resp_ready = 0;
  return 0;
}

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);
    const auto total_begin = std::chrono::steady_clock::now();
    const std::vector<std::uint8_t> image = read_image(options.image);
    g_dmi_bootstrap.configure_addresses(
        options.load_address, options.tohost_address,
        options.fromhost_address);

    auto context = std::make_unique<VerilatedContext>();
#ifdef CHRONOSHEAR_BASELINE_THREADS
    context->threads(CHRONOSHEAR_BASELINE_THREADS);
#endif
    context->randReset(0);
    context->commandArgs(argc, argv);
    auto dut = std::make_unique<VTestHarness>(context.get());

    load_image(*dut->rootp, options.load_address, image);
    write_word(*dut->rootp, options.tohost_address, 0);
    write_word(*dut->rootp, options.fromhost_address, 0);
    dut->clock = 0;
    dut->reset = 1;
    dut->eval();

    std::uint64_t final_tohost = 0;
    std::uint64_t executed_cycles = 0;
    std::uint64_t htif_acks = 0;
    std::uint64_t dmi_complete_cycle = 0;
    std::uint64_t terminal_read_cycle = 0;
    std::uint64_t console_wait_streak = 0;
    std::uint64_t terminal_streak = 0;
    std::uint64_t terminal_pc = 0;
    std::uint64_t terminal_x10 = 0;
    std::uint64_t backing_tohost = 0;
    bool console_ack_armed = true;
    bool terminal_read_requested = false;
    bool simdtm_reset_delay = false;
    const auto execution_begin = std::chrono::steady_clock::now();
    for (std::uint64_t cycle = 0; cycle < options.max_cycles; ++cycle) {
      const bool reset = cycle < options.reset_cycles;
      const bool simdtm_enabled = !reset && !simdtm_reset_delay;
      const chisa::rocket_fullchip::DmiHostOutputs outputs =
          simdtm_enabled ? chisa::rocket_fullchip::dmi_host_outputs()
                         : chisa::rocket_fullchip::DmiHostOutputs{};
      dut->reset = reset;
      drive_verilator_dmi(*dut->rootp, outputs);
      dut->clock = 0;
      dut->eval();
      context->timeInc(1);

      const DmiFeedback feedback = verilator_dmi_feedback(*dut->rootp);
      if (simdtm_enabled) {
        chisa::rocket_fullchip::dmi_host_advance(
            feedback.request_ready, feedback.response_valid,
            feedback.response_status, feedback.response_data);
      }
      simdtm_reset_delay = reset;

      dut->clock = 1;
      dut->eval();
      context->timeInc(1);
      executed_cycles = cycle + 1;

      if (g_dmi_bootstrap.failed())
        throw std::runtime_error(g_dmi_bootstrap.error());
      if (dmi_complete_cycle == 0 &&
          g_dmi_bootstrap.bootstrap_complete()) {
        dmi_complete_cycle = executed_cycles;
        std::fprintf(
            stderr,
            "ROCKET_FULLCHIP_DMI status=complete cycles=%" PRIu64
            " transactions=%" PRIu64 " dmstatus=0x%08" PRIx32
            " dpc=0x%016" PRIx64 "\n",
            dmi_complete_cycle, g_dmi_bootstrap.completed_transactions(),
            g_dmi_bootstrap.last_dmstatus(), observed_dpc(*dut->rootp));
      }

      if (reset) continue;
      backing_tohost = read_word(*dut->rootp, options.tohost_address);

      if (g_dmi_bootstrap.console_acks_completed() != htif_acks) {
        htif_acks = g_dmi_bootstrap.console_acks_completed();
        std::fprintf(stderr,
                     "ROCKET_FULLCHIP_HTIF_ACK count=%" PRIu64
                     " cycles=%" PRIu64 "\n",
                     htif_acks, executed_cycles);
      }
      if (g_dmi_bootstrap.tohost_reads_completed() != 0 &&
          final_tohost == 0) {
        final_tohost = g_dmi_bootstrap.last_tohost_read();
        terminal_read_cycle = executed_cycles;
        std::fprintf(
            stderr,
            "ROCKET_FULLCHIP_TOHOST_READ value=0x%016" PRIx64
            " data0=0x%08" PRIx32 " data1=0x%08" PRIx32
            " x5=0x%016" PRIx64 " x6=0x%016" PRIx64
            " dpc=0x%016" PRIx64 " cycles=%" PRIu64 "\n",
            final_tohost, g_dmi_bootstrap.last_tohost_data0(),
            g_dmi_bootstrap.last_tohost_data1(), observed_x(*dut->rootp, 5),
            observed_x(*dut->rootp, 6), observed_dpc(*dut->rootp),
            executed_cycles);
      }
      if (final_tohost != 0) {
        if (executed_cycles % options.finish_alignment == 0) break;
        continue;
      }

      const std::uint64_t pc = observed_pc(*dut->rootp);
      const bool console_wait =
          pc == options.console_wait_pc0 || pc == options.console_wait_pc1 ||
          pc == options.console_wait_pc2 || pc == options.console_wait_pc3;
      const bool terminal_wait =
          pc == options.exit_park_pc || pc == options.trap_park_pc;
      if (!console_wait) {
        console_wait_streak = 0;
        console_ack_armed = true;
      } else if (console_ack_armed) {
        ++console_wait_streak;
      }
      terminal_streak = terminal_wait ? terminal_streak + 1 : 0;

      if (g_dmi_bootstrap.bootstrap_complete() &&
          g_dmi_bootstrap.done()) {
        if (!terminal_read_requested &&
            terminal_streak >= kPcTriggerStableCycles) {
          terminal_pc = pc;
          terminal_x10 = observed_x(*dut->rootp, 10);
          terminal_read_requested = true;
          g_dmi_bootstrap.request_tohost_read();
        } else if (console_ack_armed &&
                   console_wait_streak >= kPcTriggerStableCycles) {
          console_ack_armed = false;
          console_wait_streak = 0;
          g_dmi_bootstrap.request_console_ack();
        }
      }

      if (options.progress_cycles != 0 &&
          executed_cycles % options.progress_cycles == 0) {
        std::fprintf(stderr,
                     "ROCKET_FULLCHIP_PROGRESS cycles=%" PRIu64
                     " pc=0x%016" PRIx64 " htif_acks=%" PRIu64
                     " backing_tohost=0x%" PRIx64
                     " dmi={stage=%s ticks=%" PRIu64 " transactions=%" PRIu64
                     " req=%u/%u resp=%u/%u status=%u data=%08" PRIx32 "}\n",
                     executed_cycles, pc, htif_acks, backing_tohost,
                     g_dmi_bootstrap.stage_name(), g_dmi_bootstrap.ticks(),
                     g_dmi_bootstrap.completed_transactions(),
                     static_cast<unsigned>(g_dmi_bootstrap.request_valid()),
                     static_cast<unsigned>(g_dmi_bootstrap.last_request_ready()),
                     static_cast<unsigned>(g_dmi_bootstrap.response_ready()),
                     static_cast<unsigned>(g_dmi_bootstrap.last_response_valid()),
                     g_dmi_bootstrap.last_response_status(),
                     g_dmi_bootstrap.last_response_data());
      }
    }
    const auto execution_end = std::chrono::steady_clock::now();

    const std::uint64_t memory_hash = hash_memory(
        *dut->rootp, options.memory_check_address, options.memory_check_bytes);
    const bool memory_clean = options.expected_memory_hash == 0 ||
                              memory_hash == options.expected_memory_hash;
    const char* status = final_tohost == 1 && memory_clean
                             ? "pass"
                             : (!memory_clean ? "memory-mismatch" :
                                (final_tohost == 0 ? "max-cycles" : "fail"));
    std::printf(
        "ROCKET_FULLCHIP_SCALAR status=%s cycles=%" PRIu64
        " reset_cycles=%" PRIu64 " image_bytes=%zu tohost=0x%" PRIx64
        " pc=0x%016" PRIx64 " x10=0x%016" PRIx64
        " backing_tohost=0x%" PRIx64 " htif_acks=%" PRIu64
        " dmi_complete_cycle=%" PRIu64 " dmi_transactions=%" PRIu64
        " terminal_read_cycle=%" PRIu64 " finish_alignment=%" PRIu64
        " memory_check=0x%016" PRIx64 "+0x%016" PRIx64
        " memory_hash=0x%016" PRIx64 "\n",
        status, executed_cycles, options.reset_cycles, image.size(),
        final_tohost, terminal_pc != 0 ? terminal_pc : observed_pc(*dut->rootp),
        terminal_x10, backing_tohost, htif_acks,
        dmi_complete_cycle, g_dmi_bootstrap.completed_transactions(),
        terminal_read_cycle, options.finish_alignment,
        options.memory_check_address, options.memory_check_bytes, memory_hash);
    dut->final();
    const double execution_ns = std::chrono::duration<double, std::nano>(
        execution_end - execution_begin).count();
    const double total_ns = std::chrono::duration<double, std::nano>(
        std::chrono::steady_clock::now() - total_begin).count();
    const double cycles = static_cast<double>(executed_cycles);
    std::printf(
        "ROCKET_VERILATOR_TIMING cycles=%" PRIu64
        " execution_ns_per_cycle=%.2f total_ns_per_cycle=%.2f"
        " execution_cycles_per_sec=%.2f total_cycles_per_sec=%.2f\n",
        executed_cycles, executed_cycles ? execution_ns / cycles : 0.0,
        executed_cycles ? total_ns / cycles : 0.0,
        execution_ns > 0.0 ? cycles * 1.0e9 / execution_ns : 0.0,
        total_ns > 0.0 ? cycles * 1.0e9 / total_ns : 0.0);
    if (final_tohost == 1 && memory_clean) return 0;
    return final_tohost == 0 ? 3 : 4;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "Rocket full-chip scalar error: %s\n", error.what());
    return 2;
  }
}

#endif  // ROCKET_DMI_LIBRARY_ONLY
