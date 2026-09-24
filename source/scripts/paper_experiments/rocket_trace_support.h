#pragma once
// The complete RTL trace harness's external ports. No model implementation or
// model-to-RTL adapter is included here.
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace chisa::rocket_trace {
inline std::uint64_t plusarg(int argc, char** argv, const char* format,
                             std::int64_t fallback, unsigned width) {
  if (width == 0 || width > 64) throw std::invalid_argument("invalid plusarg width");
  const std::string text(format);
  const auto marker = text.find("%d");
  if (marker == std::string::npos || text.find('%', marker + 2) != std::string::npos)
    throw std::invalid_argument("unsupported plusarg format");
  const auto prefix = "+" + text.substr(0, marker);
  const auto mask = width == 64 ? UINT64_MAX : ((UINT64_C(1) << width) - 1);
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);
    if (arg.compare(0, prefix.size(), prefix) != 0) continue;
    std::int64_t value = 0;
    (void)std::sscanf(arg.c_str() + prefix.size(), "%30" SCNd64, &value);
    return static_cast<std::uint64_t>(value) & mask;
  }
  return static_cast<std::uint64_t>(fallback) & mask;
}
template <typename T> inline std::uint64_t value(const T& field) {
  return static_cast<std::uint64_t>(field.as_single_word());
}
template <typename T> inline void assign(T& field, std::uint64_t v) {
  field = std::remove_cv_t<std::remove_reference_t<T>>(v);
}
template <int W, typename Dut> void initialize_plusargs(Dut& dut, int argc, char** argv) {
#define CHISA_EXT_PLUSARG_READER(PATH, OUT, FORMAT, DEFAULT, WIDTH) \
  do { const auto v = plusarg(argc, argv, FORMAT, DEFAULT, WIDTH); \
       for (int lane = 0; lane < W; ++lane) assign(dut.PATH.OUT[lane], v); } while (false);
#define CHISA_EXT_SIMDTM(PATH)
#define CHISA_EXT_EICG_LOWERED(PATH)
#define CHISA_EXT_ROCKET_MODEL(PATH) static_assert(sizeof(Dut) == 0, "trace requires complete RTL");
#define CHISA_EXT_ROCKET_FRONTEND_MODEL(PATH) CHISA_EXT_ROCKET_MODEL(PATH)
#define CHISA_EXT_ROCKET_DCACHE_MODEL(PATH) CHISA_EXT_ROCKET_MODEL(PATH)
#define CHISA_EXT_ROCKET_FPU_MODEL(PATH) CHISA_EXT_ROCKET_MODEL(PATH)
#define CHISA_EXT_UNIMPLEMENTED(PATH, DEFNAME) static_assert(sizeof(Dut) == 0, "unsupported ExtModule: " DEFNAME);
#include "extmodule_fields.inc"
#undef CHISA_EXT_PLUSARG_READER
#undef CHISA_EXT_SIMDTM
#undef CHISA_EXT_EICG_LOWERED
#undef CHISA_EXT_ROCKET_MODEL
#undef CHISA_EXT_ROCKET_FRONTEND_MODEL
#undef CHISA_EXT_ROCKET_DCACHE_MODEL
#undef CHISA_EXT_ROCKET_FPU_MODEL
#undef CHISA_EXT_UNIMPLEMENTED
}
template <typename Dut> decltype(auto) dmi_ports(Dut& dut) {
#define CHISA_EXT_PLUSARG_READER(PATH, OUT, FORMAT, DEFAULT, WIDTH)
#define CHISA_EXT_SIMDTM(PATH) return (dut.PATH);
#define CHISA_EXT_EICG_LOWERED(PATH)
#define CHISA_EXT_ROCKET_MODEL(PATH) static_assert(sizeof(Dut) == 0, "trace requires complete RTL");
#define CHISA_EXT_ROCKET_FRONTEND_MODEL(PATH) CHISA_EXT_ROCKET_MODEL(PATH)
#define CHISA_EXT_ROCKET_DCACHE_MODEL(PATH) CHISA_EXT_ROCKET_MODEL(PATH)
#define CHISA_EXT_ROCKET_FPU_MODEL(PATH) CHISA_EXT_ROCKET_MODEL(PATH)
#define CHISA_EXT_UNIMPLEMENTED(PATH, DEFNAME) static_assert(sizeof(Dut) == 0, "unsupported ExtModule: " DEFNAME);
#include "extmodule_fields.inc"
#undef CHISA_EXT_PLUSARG_READER
#undef CHISA_EXT_SIMDTM
#undef CHISA_EXT_EICG_LOWERED
#undef CHISA_EXT_ROCKET_MODEL
#undef CHISA_EXT_ROCKET_FRONTEND_MODEL
#undef CHISA_EXT_ROCKET_DCACHE_MODEL
#undef CHISA_EXT_ROCKET_FPU_MODEL
#undef CHISA_EXT_UNIMPLEMENTED
}
} // namespace chisa::rocket_trace
