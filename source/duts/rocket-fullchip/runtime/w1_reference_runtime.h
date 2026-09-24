#pragma once

#include "TestHarness.h"

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace chisa::rocket_fullchip {

enum class HalfDirection : std::uint8_t { forward, reverse };
enum class TapPhase : std::uint8_t {
  pre_eval_register,
  post_eval_combinational,
};

inline const char* direction_name(HalfDirection direction) {
  return direction == HalfDirection::forward ? "forward" : "reverse";
}

inline const char* phase_name(TapPhase phase) {
  return phase == TapPhase::pre_eval_register ? "pre" : "post";
}

inline constexpr std::size_t exact_register_tap_count() {
  std::size_t count = 0;
#define REG_ORACLE(expr, name) ++count
#define REG_ORACLE_WORD(expr, i, name) ++count
#include "exact_reg_oracle_fields.inc"
#undef REG_ORACLE
#undef REG_ORACLE_WORD
  return count;
}

inline constexpr std::size_t exact_combinational_tap_count() {
  std::size_t count = 0;
#define PUSH_AS(expr, name) ++count
#include "exact_probe_fields_v2.inc"
#undef PUSH_AS
  return count;
}

inline constexpr std::size_t kExactRegisterTapCount =
    exact_register_tap_count();
inline constexpr std::size_t kExactCombinationalTapCount =
    exact_combinational_tap_count();

template <typename Observer>
inline void sample_exact_register_tap(
    TestHarness& t, Observer& observer, std::uint64_t cycle,
    HalfDirection direction) {
#define REG_ORACLE(expr, name)                                                \
  do {                                                                        \
    observer.observe(cycle, direction, TapPhase::pre_eval_register, (name),   \
                     essent_to_u64((expr)[0]));                               \
  } while (false)
#define REG_ORACLE_WORD(expr, i, name)                                        \
  do {                                                                        \
    observer.observe(cycle, direction, TapPhase::pre_eval_register, (name),   \
                     static_cast<std::uint64_t>((expr)[0].val[(i)]));          \
  } while (false)
#include "exact_reg_oracle_fields.inc"
#undef REG_ORACLE
#undef REG_ORACLE_WORD
}

template <typename Observer>
inline void sample_exact_combinational_tap(
    Observer& observer, std::uint64_t cycle, HalfDirection direction) {
#define CHISA_TAP_CAT_INNER(a, b) a##b
#define CHISA_TAP_CAT(a, b) CHISA_TAP_CAT_INNER(a, b)
#define CHISA_TAP_SCRATCH(expr) CHISA_TAP_CAT(_s_, expr)
#define PUSH_AS(expr, name)                                                   \
  do {                                                                        \
    observer.observe(cycle, direction, TapPhase::post_eval_combinational,    \
                     (name), essent_to_u64(CHISA_TAP_SCRATCH(expr)[0]));      \
  } while (false)
#include "exact_probe_fields_v2.inc"
#undef PUSH_AS
#undef CHISA_TAP_SCRATCH
#undef CHISA_TAP_CAT
#undef CHISA_TAP_CAT_INNER
}

inline std::uint64_t width_mask(unsigned width) {
  if (width == 0 || width > 64)
    throw std::invalid_argument("bit width must be in 1..64");
  return width == 64 ? std::numeric_limits<std::uint64_t>::max()
                     : ((std::uint64_t{1} << width) - 1);
}

inline std::uint64_t resolve_decimal_plusarg(
    int argc, char** argv, const char* format, std::int64_t default_value,
    unsigned width) {
  const std::string fmt(format);
  const auto marker = fmt.find("%d");
  if (marker == std::string::npos ||
      fmt.find('%', marker + 2) != std::string::npos)
    throw std::invalid_argument("only one %d plusarg conversion is supported");
  const std::string prefix = "+" + fmt.substr(0, marker);
  for (int index = 1; index < argc; ++index) {
    const std::string argument(argv[index]);
    if (argument.compare(0, prefix.size(), prefix) != 0) continue;
    std::int64_t parsed = 0;
    (void)std::sscanf(argument.c_str() + prefix.size(), "%30" SCNd64,
                      &parsed);
    return static_cast<std::uint64_t>(parsed) & width_mask(width);
  }
  return static_cast<std::uint64_t>(default_value) & width_mask(width);
}

template <typename UIntLike>
inline std::uint64_t port_value(const UIntLike& value) {
  return static_cast<std::uint64_t>(value.as_single_word());
}

template <typename Field>
inline void assign_port(Field& field, std::uint64_t value) {
  using T = std::remove_cv_t<std::remove_reference_t<Field>>;
  field = T(value);
}

template <typename Dut>
inline void initialize_plusarg_readers(Dut& dut, int argc, char** argv) {
#define CHISA_EXT_PLUSARG_READER(PATH, OUT, FORMAT, DEFAULT, WIDTH)           \
  do {                                                                        \
    const std::uint64_t value = resolve_decimal_plusarg(                      \
        argc, argv, FORMAT, static_cast<std::int64_t>(DEFAULT),               \
        static_cast<unsigned>(WIDTH));                                        \
    assign_port(dut.PATH.OUT[0], value);                                      \
  } while (false);
#define CHISA_EXT_SIMDTM(PATH)
#define CHISA_EXT_EICG_LOWERED(PATH)
#define CHISA_EXT_UNIMPLEMENTED(PATH, DEFNAME)                                \
  static_assert(sizeof(Dut) == 0, "unimplemented ExtModule: " DEFNAME);
#include "extmodule_fields.inc"
#undef CHISA_EXT_PLUSARG_READER
#undef CHISA_EXT_SIMDTM
#undef CHISA_EXT_EICG_LOWERED
#undef CHISA_EXT_UNIMPLEMENTED
}

template <typename Dut>
inline decltype(auto) simdtm_ports(Dut& dut) {
#define CHISA_EXT_PLUSARG_READER(PATH, OUT, FORMAT, DEFAULT, WIDTH)
#define CHISA_EXT_SIMDTM(PATH) return (dut.PATH);
#define CHISA_EXT_EICG_LOWERED(PATH)
#define CHISA_EXT_UNIMPLEMENTED(PATH, DEFNAME)                                \
  static_assert(sizeof(Dut) == 0, "unimplemented ExtModule: " DEFNAME);
#include "extmodule_fields.inc"
#undef CHISA_EXT_PLUSARG_READER
#undef CHISA_EXT_SIMDTM
#undef CHISA_EXT_EICG_LOWERED
#undef CHISA_EXT_UNIMPLEMENTED
}

}  // namespace chisa::rocket_fullchip
