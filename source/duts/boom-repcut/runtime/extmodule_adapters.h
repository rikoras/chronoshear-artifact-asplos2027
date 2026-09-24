#pragma once

#include <array>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace chisa::boom_repcut {

inline uint64_t width_mask(unsigned width) {
  if (width == 0 || width > 64)
    throw std::invalid_argument("plusarg width must be in 1..64");
  return width == 64 ? std::numeric_limits<uint64_t>::max()
                     : ((uint64_t{1} << width) - 1);
}

/** Exact `%d` plusarg reader used by this locked Rocket-Chip artifact.
  * The generated field inventory supplies FORMAT/DEFAULT/WIDTH directly from
  * FIRRTL, so a future artifact with a different contract fails instead of
  * silently inheriting `tilelink_timeout` assumptions. */
inline uint64_t resolve_decimal_plusarg(
    int argc, char** argv, const char* format, int64_t default_value,
    unsigned width) {
  const std::string fmt(format);
  const auto marker = fmt.find("%d");
  if (marker == std::string::npos || fmt.find('%', marker + 2) != std::string::npos)
    throw std::invalid_argument("only one %d plusarg conversion is supported");
  const std::string prefix = "+" + fmt.substr(0, marker);
  // RepCut bundles Verilator 4.226.  Its
  // VerilatedContextImp::argPlusMatch walks m_argVec from front to back and
  // returns immediately, so duplicate plusargs are first-match-wins.  Its
  // VL_VALUEPLUSARGS_INW then uses sscanf on the text after the prefix: a
  // decimal prefix is accepted, trailing text is ignored, and an invalid
  // conversion produces zero.  Preserve that behavior exactly rather than
  // imposing command-line parsing rules of our own.
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);
    if (arg.size() < prefix.size() ||
        arg.compare(0, prefix.size(), prefix) != 0)
      continue;
    const std::string digits = arg.substr(
      prefix.size(), arg.size() - prefix.size());
    int64_t parsed = 0;
    (void)std::sscanf(digits.c_str(), "%30" SCNd64, &parsed);
    return static_cast<uint64_t>(parsed) & width_mask(width);
  }
  return static_cast<uint64_t>(default_value) & width_mask(width);
}

struct DmiFeedback {
  bool req_ready = false;
  bool resp_valid = false;
  uint32_t resp = 0;
  uint32_t data = 0;

  friend bool operator==(const DmiFeedback& a, const DmiFeedback& b) {
    return a.req_ready == b.req_ready && a.resp_valid == b.resp_valid &&
      a.resp == b.resp && a.data == b.data;
  }
  friend bool operator!=(const DmiFeedback& a, const DmiFeedback& b) {
    return !(a == b);
  }
};

struct DtmOutputs {
  bool req_valid = false;
  uint32_t req_addr = 0;
  uint32_t req_op = 0;
  uint32_t req_data = 0;
  bool resp_ready = false;
  uint32_t exit = 0;
};

template <typename UIntLike>
inline uint64_t port_value(const UIntLike& value) {
  return static_cast<uint64_t>(value.as_single_word());
}

template <typename Field>
inline void assign_port(Field& field, uint64_t value) {
  using T = std::remove_cv_t<std::remove_reference_t<Field>>;
  field = T(value);
}

/** Stateful adapter for the exact artifact `dtm_t` API and SimDTM edge order.
  *
  * A lane consumes the outputs latched by the preceding cycle.  Its DMI
  * feedback is then presented to `dtm_t::tick` at the following negedge and
  * the resulting request is latched for the next lane's posedge.  `r_reset`
  * intentionally keeps the outputs zero for one extra negedge after reset is
  * deasserted, matching SimDTM.v rather than the older approximate ESSENT
  * helper.  SimDTM clears valid/ready/exit during that reset interval but
  * deliberately leaves the invalid request payload registers unchanged.
  *
  * `prepare_half` advances the one shared `dtm_t` sequentially from predicted
  * feedback.  It must never be called once per SIMD lane on independent DTM
  * copies.  After RTL evaluation, `verify_half` checks every prediction; a
  * live system-sidecar should abort the window on the first mismatch.
  */
template <typename Dtm>
class FesvrDtmAdapter {
 public:
  explicit FesvrDtmAdapter(Dtm& dtm) : dtm_(dtm) {}

  const DtmOutputs& outputs() const { return current_; }
  bool reset_delay() const { return r_reset_; }
  uint64_t advanced_cycles() const { return advanced_cycles_; }

  /** True only at a workload-independent handoff point in fesvr's idle loop.
    *
    * `dtm_t::idle()` issues DMI NOPs with an all-zero request.  Seeing the
    * next such request while no earlier request is outstanding means fesvr is
    * not in the middle of a halt, abstract command, memory access, or resume
    * sequence.  The unaccepted NOP can therefore be replaced by the explicit
    * debugger-shutdown transaction below without abandoning a target-side
    * operation halfway through. */
  bool at_idle_nop_boundary() const {
    return quiesce_state_ == QuiesceState::kRunning && !r_reset_ &&
           !request_in_flight_ && current_.req_valid &&
           current_.req_addr == 0 && current_.req_op == 0 &&
           current_.req_data == 0;
  }

  /** Stop fesvr polling and deactivate the Debug Module for the target ROI.
    *
    * This is deliberately stricter than merely forcing req_valid low.  A
    * final legal DMI write clears DMCONTROL.dmactive, allowing the debug clock
    * crossings and generated cold sidecars to reach a real fixed point. */
  void begin_dmi_quiesce() {
    if (!at_idle_nop_boundary())
      throw std::logic_error(
          "DMI quiesce requires an idle NOP boundary with no request in flight");
    quiesce_state_ = QuiesceState::kDisableRequest;
    current_ = DtmOutputs{/*req_valid=*/true,
                          /*req_addr=*/0x10,
                          /*req_op=*/2,
                          /*req_data=*/0,
                          /*resp_ready=*/true,
                          /*exit=*/0};
  }

  bool dmi_quiescing() const {
    return quiesce_state_ != QuiesceState::kRunning &&
           quiesce_state_ != QuiesceState::kDone;
  }
  bool dmi_quiesced() const {
    return quiesce_state_ == QuiesceState::kDone;
  }

  template <typename SimDtmPorts>
  void drive_lane(SimDtmPorts& ports, int lane) const {
    assign_port(ports.debug_req_valid[lane], current_.req_valid);
    assign_port(ports.debug_req_bits_addr[lane], current_.req_addr);
    assign_port(ports.debug_req_bits_op[lane], current_.req_op);
    assign_port(ports.debug_req_bits_data[lane], current_.req_data);
    assign_port(ports.debug_resp_ready[lane], current_.resp_ready);
    assign_port(ports.exit[lane], current_.exit);
  }

  template <typename SimDtmPorts>
  static DmiFeedback feedback_lane(const SimDtmPorts& ports, int lane) {
    return DmiFeedback{
      port_value(ports.debug_req_ready[lane]) != 0,
      port_value(ports.debug_resp_valid[lane]) != 0,
      static_cast<uint32_t>(port_value(ports.debug_resp_bits_resp[lane])),
      static_cast<uint32_t>(port_value(ports.debug_resp_bits_data[lane]))};
  }

  void advance(bool reset, const DmiFeedback& feedback) {
    if (quiesce_state_ != QuiesceState::kRunning) {
      advance_quiesce(reset, feedback);
      ++advanced_cycles_;
      return;
    }

    const bool prior_reset = r_reset_;
    r_reset_ = reset;
    if (reset || prior_reset) {
      request_in_flight_ = false;
      current_.req_valid = false;
      current_.resp_ready = false;
      current_.exit = 0;
      idle_nop_hold_ = 0;
      suppressed_last_ = false;
    } else {
      // While the throttle suppressed last cycle's presentation, the model
      // never saw the request, so its req_ready must not reach dtm_t::tick:
      // tick treats req_ready alone as the handshake (dtm.cc:620-626) and
      // would drop the request, desynchronising the DMI protocol for good.
      const bool masked_req_ready = feedback.req_ready && !suppressed_last_;
      if (current_.req_valid && masked_req_ready)
        request_in_flight_ = true;
      if (current_.resp_ready && feedback.resp_valid)
        request_in_flight_ = false;
      typename Dtm::resp response{};
      response.resp = feedback.resp;
      response.data = feedback.data;
      dtm_.tick(masked_req_ready, feedback.resp_valid, response);
      const auto request = dtm_.req_bits();
      current_.req_valid = dtm_.req_valid();
      current_.req_addr = request.addr;
      current_.req_op = request.op;
      current_.req_data = request.data;
      current_.resp_ready = dtm_.resp_ready();
      // Rate-limit fesvr's DMI chatter.  Between operations dtm_t::idle()
      // hammers all-zero NOPs on a two-cycle period (measured), and
      // dtm_t::read_chunk halts and
      // resumes the hart around every poll, so each poll is a back-to-back
      // run of DMI reads -- DMSTATUS (0x11) halt/resume busy polls,
      // ABSTRACTCS (0x16) busy polls, DATA0 (0x04) results -- that restarts
      // the moment it completes, keeping the debug clock crossing (and the
      // coherent-memory fixed point it sits in) evaluating nearly every
      // cycle.  Holding each such read for kIdleNopInterval cycles spreads
      // the polls out.  Writes pass untouched, so the write-dominated
      // program load keeps its pace (its per-chunk halt/resume adds only a
      // few held reads per chunk).  The DMI stream is produced here and
      // replayed identically by the consumer and the lockstep reference,
      // so all sides stay in step.
      // The hold is wall-clock: it counts down every cycle and only gates
      // RELEASE of matching chatter.  It must not reset while no request is
      // pending -- dtm_t exposes each NOP on a two-cycle beat (one exposed
      // tick, one gap tick), and clearing the hold on the gap tick would
      // re-release every NOP immediately, neutralising the limiter.
      if (idle_nop_hold_ != 0) --idle_nop_hold_;
      if (current_.req_valid && !request_in_flight_ &&
          ((current_.req_op == 0 && current_.req_addr == 0) ||
           (current_.req_op == 1 &&
            (current_.req_addr == 0x16 || current_.req_addr == 0x04 ||
             current_.req_addr == 0x11)))) {
        if (idle_nop_hold_ != 0) {
          current_.req_valid = false;
          suppressed_last_ = true;
        } else {
          idle_nop_hold_ = kIdleNopInterval - 1;
          suppressed_last_ = false;
        }
      } else {
        suppressed_last_ = false;
      }
      current_.exit = dtm_.done() ? (dtm_.exit_code() << 1U) | 1U : 0U;
    }
    ++advanced_cycles_;
  }

  template <size_t W, typename SimDtmPorts>
  void prepare_half(SimDtmPorts& ports, bool forward, bool reset,
      const std::array<DmiFeedback, W>& predicted_chronological) {
    for (size_t step = 0; step < W; ++step) {
      const int lane = forward ? static_cast<int>(step)
                               : static_cast<int>(W - 1 - step);
      drive_lane(ports, lane);
      advance(reset, predicted_chronological[step]);
    }
  }

  template <size_t W, typename SimDtmPorts>
  static bool verify_half(const SimDtmPorts& ports, bool forward,
      const std::array<DmiFeedback, W>& predicted_chronological,
      FILE* diagnostics = stderr) {
    for (size_t step = 0; step < W; ++step) {
      const int lane = forward ? static_cast<int>(step)
                               : static_cast<int>(W - 1 - step);
      const DmiFeedback actual = feedback_lane(ports, lane);
      if (actual != predicted_chronological[step]) {
        if (diagnostics) {
          std::fprintf(diagnostics,
            "DMI SHADOW MISMATCH step=%zu lane=%d "
            "req_ready=%u/%u resp_valid=%u/%u resp=%u/%u data=%08x/%08x\n",
            step, lane,
            static_cast<unsigned>(actual.req_ready),
            static_cast<unsigned>(predicted_chronological[step].req_ready),
            static_cast<unsigned>(actual.resp_valid),
            static_cast<unsigned>(predicted_chronological[step].resp_valid),
            actual.resp, predicted_chronological[step].resp,
            actual.data, predicted_chronological[step].data);
        }
        return false;
      }
    }
    return true;
  }

 private:
  enum class QuiesceState {
    kRunning,
    kDisableRequest,
    kDisableResponse,
    kDone,
  };

  void advance_quiesce(bool reset, const DmiFeedback& feedback) {
    if (reset)
      throw std::logic_error("reset asserted after DMI quiesce began");

    switch (quiesce_state_) {
      case QuiesceState::kRunning:
        throw std::logic_error("invalid DMI quiesce state");

      case QuiesceState::kDisableRequest:
        if (feedback.resp_valid && !feedback.req_ready)
          throw std::logic_error(
              "DMI deactivate response arrived before request acceptance");
        if (!feedback.req_ready) return;
        if (feedback.resp_valid) {
          if (feedback.resp != 0)
            throw std::runtime_error("DMI deactivate request failed");
          quiesce_state_ = QuiesceState::kDone;
          current_ = DtmOutputs{};
          return;
        }
        quiesce_state_ = QuiesceState::kDisableResponse;
        current_ = DtmOutputs{/*req_valid=*/false,
                              /*req_addr=*/0,
                              /*req_op=*/0,
                              /*req_data=*/0,
                              /*resp_ready=*/true,
                              /*exit=*/0};
        return;

      case QuiesceState::kDisableResponse:
        if (!feedback.resp_valid) return;
        if (feedback.resp != 0)
          throw std::runtime_error("DMI deactivate response failed");
        quiesce_state_ = QuiesceState::kDone;
        current_ = DtmOutputs{};
        return;

      case QuiesceState::kDone:
        current_ = DtmOutputs{};
        return;
    }
  }

  Dtm& dtm_;
  bool r_reset_ = false;
  bool request_in_flight_ = false;
  static constexpr uint32_t kIdleNopInterval = 32;
  uint32_t idle_nop_hold_ = 0;
  bool suppressed_last_ = false;
  QuiesceState quiesce_state_ = QuiesceState::kRunning;
  DtmOutputs current_{};
  uint64_t advanced_cycles_ = 0;
};

} // namespace chisa::boom_repcut
