#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

#include "generated/system_oracle_record.h"

namespace chisa::boom_system::record_view {

enum class Kind : std::uint8_t { Register, Combinational };

struct LaneSpec {
  std::uint16_t offset;
  std::uint8_t bytes;
  std::uint8_t width;
  Kind kind;
  std::uint8_t word;
  std::uint8_t words;
  std::uint64_t identity;
};

template <class Contract>
constexpr bool compatible() {
  if (Contract::lanes != kOracleRecordLanes ||
      Contract::bytes != kOracleRecordBytes ||
      Contract::padded_bytes != kOracleRecordPaddedBytes ||
      Contract::layout_hash != kOracleRecordLayoutHash)
    return false;
  for (std::size_t i = 0; i < Contract::lanes; ++i) {
    const auto& field = Contract::lane[i];
    const auto& record = kOracleRecordLane[i];
    const auto& identity = kOracleRecordLaneIdentity[i];
    if (field.offset != record.offset || field.bytes != record.bytes ||
        field.width != record.width ||
        field.identity != identity.hash ||
        static_cast<std::uint8_t>(field.kind) != identity.kind ||
        field.word != identity.word || field.words != identity.words ||
        field.words == 0 || field.word >= field.words ||
        (field.bytes != 1 && field.bytes != 2 && field.bytes != 4 && field.bytes != 8) ||
        field.width == 0 || field.width > 8 * field.bytes ||
        record.mask != (1u << field.bytes) - 1u ||
        field.offset + field.bytes > Contract::bytes)
      return false;
    for (std::size_t byte = field.offset; byte < field.offset + field.bytes; ++byte)
      if (kOracleRecordByteLane[byte] != i) return false;
  }
  for (std::size_t byte = 0; byte < Contract::padded_bytes; ++byte) {
    const auto lane = kOracleRecordByteLane[byte];
    if (lane == kOracleRecordPadLane) continue;
    if (lane >= Contract::lanes || byte < Contract::lane[lane].offset ||
        byte >= Contract::lane[lane].offset + Contract::lane[lane].bytes)
      return false;
  }
  return true;
}

template <class Contract, std::size_t Lane>
struct Field {
  static_assert(Lane < Contract::lanes, "record field lane is out of range");
  inline static constexpr std::size_t lane = Lane;
  inline static constexpr LaneSpec spec = Contract::lane[Lane];
  using value_type = std::conditional_t<spec.bytes == 1, std::uint8_t,
      std::conditional_t<spec.bytes == 2, std::uint16_t,
      std::conditional_t<spec.bytes == 4, std::uint32_t, std::uint64_t>>>;
};

// A single pointer to existing storage. This never creates, resets, or
// samples model state and makes no claim that any field has a live producer.
// memcpy is required: packed Large lanes may be unaligned (e.g. offset 3).
template <class Contract>
class BasicView {
 public:
  static_assert(compatible<Contract>(), "record view contract mismatch");
  explicit BasicView(OracleRecord& record) : record_(&record) {}

  template <std::size_t Lane>
  typename Field<Contract, Lane>::value_type get(Field<Contract, Lane>) const {
    using F = Field<Contract, Lane>;
    typename F::value_type value;
    std::memcpy(&value, record_->bytes + F::spec.offset, F::spec.bytes);
    return value;
  }

  template <std::size_t Lane>
  void set(Field<Contract, Lane>, typename Field<Contract, Lane>::value_type value) {
    using F = Field<Contract, Lane>;
    constexpr auto mask = ~std::uint64_t{0} >> (64 - F::spec.width);
    value = static_cast<typename F::value_type>(value & mask);
    std::memcpy(record_->bytes + F::spec.offset, &value, F::spec.bytes);
  }

 private:
  OracleRecord* record_;
};

}  // namespace chisa::boom_system::record_view
