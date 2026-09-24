#pragma once

#include "extmodule_adapters.h"

namespace chisa::boom_repcut {

/** Broadcast every plusarg_reader once during harness initialization.  The
  * generated X-macro file names all concrete members, so no per-window scan
  * or string lookup is paid in the hot path. */
template <int W, typename Dut>
void initialize_plusarg_readers(Dut& dut, int argc, char** argv) {
#define CHISA_EXT_PLUSARG_READER(PATH, OUT, FORMAT, DEFAULT, WIDTH) do {       \
    const uint64_t _chisa_value = resolve_decimal_plusarg(                   \
      argc, argv, FORMAT, static_cast<int64_t>(DEFAULT),                     \
      static_cast<unsigned>(WIDTH));                                         \
    for (int _chisa_lane = 0; _chisa_lane < W; ++_chisa_lane)                \
      assign_port(dut.PATH.OUT[_chisa_lane], _chisa_value);                   \
  } while (false);
#define CHISA_EXT_SIMDTM(PATH)
#define CHISA_EXT_EICG_LOWERED(PATH)
#define CHISA_EXT_UNIMPLEMENTED(PATH, DEFNAME)                                \
  static_assert(sizeof(Dut) == 0, "unimplemented ExtModule adapter: " DEFNAME);
#include "extmodule_fields.inc"
#undef CHISA_EXT_PLUSARG_READER
#undef CHISA_EXT_SIMDTM
#undef CHISA_EXT_EICG_LOWERED
#undef CHISA_EXT_UNIMPLEMENTED
}

/** Return the one locked TestHarness SimDTM member.  A missing or duplicated
  * SimDTM becomes a generated-code compile error instead of a runtime lookup. */
template <typename Dut>
decltype(auto) simdtm_ports(Dut& dut) {
#define CHISA_EXT_PLUSARG_READER(PATH, OUT, FORMAT, DEFAULT, WIDTH)
#define CHISA_EXT_SIMDTM(PATH) return (dut.PATH);
#define CHISA_EXT_EICG_LOWERED(PATH)
#define CHISA_EXT_UNIMPLEMENTED(PATH, DEFNAME)                                \
  static_assert(sizeof(Dut) == 0, "unimplemented ExtModule adapter: " DEFNAME);
#include "extmodule_fields.inc"
#undef CHISA_EXT_PLUSARG_READER
#undef CHISA_EXT_SIMDTM
#undef CHISA_EXT_EICG_LOWERED
#undef CHISA_EXT_UNIMPLEMENTED
}

} // namespace chisa::boom_repcut
