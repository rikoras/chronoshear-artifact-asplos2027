#pragma once
// Boundary types of the locked artifact's TLDebugModuleInnerAsync block.
// Only the TileLink manager face (tl_*) is still driven: the Debug Module
// is hand-written in components/boom_uncached_path.h and native_fabric.cpp
// evaluates its CBus register-router face from these types.  The generated
// sidecar that once sat behind them was removed after de86af23.

#include <cstdint>

namespace chisa::boom_system::protocol {

struct DebugInnerInputs {
  bool clock_edge = true;
  bool reset = false;
  bool tl_reset = false;
  bool dmactive = false;
  bool debug_unavailable = false;
  bool hart_in_reset = false;

  // dmOuter -> dmInner TileLink A asynchronous crossing.
  std::uint8_t a_opcode = 0;
  std::uint8_t a_param = 0;
  std::uint8_t a_size = 0;
  bool a_source = false;
  std::uint16_t a_address = 0;
  std::uint8_t a_mask = 0;
  std::uint32_t a_data = 0;
  bool a_corrupt = false;
  bool a_widx = false;
  bool a_widx_valid = false;
  bool a_source_reset_n = false;

  // dmInner -> dmOuter TileLink D asynchronous crossing remote half.
  bool d_ridx = false;
  bool d_ridx_valid = false;
  bool d_sink_reset_n = false;

  // dmOuter -> dmInner control asynchronous crossing.
  bool inner_ctrl_resumereq = false;
  std::uint16_t inner_ctrl_hartsel = 0;
  bool inner_ctrl_ackhavereset = false;
  bool inner_ctrl_hasel = false;
  bool inner_ctrl_hamask = false;
  bool inner_ctrl_hrmask = false;
  bool inner_ctrl_widx = false;
  bool inner_ctrl_widx_valid = false;
  bool inner_ctrl_source_reset_n = false;

  // Tile-facing Debug Module manager port.
  bool tl_a_valid = false;
  std::uint8_t tl_a_opcode = 0;
  std::uint8_t tl_a_param = 0;
  std::uint8_t tl_a_size = 0;
  std::uint16_t tl_a_source = 0;
  std::uint16_t tl_a_address = 0;
  std::uint8_t tl_a_mask = 0;
  std::uint64_t tl_a_data = 0;
  bool tl_a_corrupt = false;
  bool tl_d_ready = true;

  bool operator==(const DebugInnerInputs& other) const {
    return clock_edge == other.clock_edge && reset == other.reset &&
           tl_reset == other.tl_reset && dmactive == other.dmactive &&
           debug_unavailable == other.debug_unavailable &&
           hart_in_reset == other.hart_in_reset &&
           a_opcode == other.a_opcode && a_param == other.a_param &&
           a_size == other.a_size && a_source == other.a_source &&
           a_address == other.a_address && a_mask == other.a_mask &&
           a_data == other.a_data && a_corrupt == other.a_corrupt &&
           a_widx == other.a_widx && a_widx_valid == other.a_widx_valid &&
           a_source_reset_n == other.a_source_reset_n &&
           d_ridx == other.d_ridx && d_ridx_valid == other.d_ridx_valid &&
           d_sink_reset_n == other.d_sink_reset_n &&
           inner_ctrl_resumereq == other.inner_ctrl_resumereq &&
           inner_ctrl_hartsel == other.inner_ctrl_hartsel &&
           inner_ctrl_ackhavereset == other.inner_ctrl_ackhavereset &&
           inner_ctrl_hasel == other.inner_ctrl_hasel &&
           inner_ctrl_hamask == other.inner_ctrl_hamask &&
           inner_ctrl_hrmask == other.inner_ctrl_hrmask &&
           inner_ctrl_widx == other.inner_ctrl_widx &&
           inner_ctrl_widx_valid == other.inner_ctrl_widx_valid &&
           inner_ctrl_source_reset_n ==
               other.inner_ctrl_source_reset_n &&
           tl_a_valid == other.tl_a_valid &&
           tl_a_opcode == other.tl_a_opcode &&
           tl_a_param == other.tl_a_param && tl_a_size == other.tl_a_size &&
           tl_a_source == other.tl_a_source &&
           tl_a_address == other.tl_a_address &&
           tl_a_mask == other.tl_a_mask && tl_a_data == other.tl_a_data &&
           tl_a_corrupt == other.tl_a_corrupt &&
           tl_d_ready == other.tl_d_ready;
  }
  bool operator!=(const DebugInnerInputs& other) const {
    return !(*this == other);
  }
};

struct DebugInnerOutputs {
  bool a_ridx = false;
  bool a_ridx_valid = false;
  bool a_sink_reset_n = false;

  std::uint8_t d_opcode = 0;
  std::uint8_t d_param = 0;
  std::uint8_t d_size = 0;
  bool d_source = false;
  bool d_sink = false;
  bool d_denied = false;
  std::uint32_t d_data = 0;
  bool d_corrupt = false;
  bool d_widx = false;
  bool d_widx_valid = false;
  bool d_source_reset_n = false;

  bool inner_ctrl_ridx = false;
  bool inner_ctrl_ridx_valid = false;
  bool inner_ctrl_sink_reset_n = false;
  bool debug_interrupt = false;

  bool tl_a_ready = false;
  bool tl_d_valid = false;
  std::uint8_t tl_d_opcode = 0;
  std::uint8_t tl_d_param = 0;
  std::uint8_t tl_d_size = 0;
  std::uint16_t tl_d_source = 0;
  bool tl_d_sink = false;
  bool tl_d_denied = false;
  std::uint64_t tl_d_data = 0;
  bool tl_d_corrupt = false;
};

}  // namespace chisa::boom_system::protocol
