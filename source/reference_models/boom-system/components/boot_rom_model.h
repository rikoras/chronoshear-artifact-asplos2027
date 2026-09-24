#pragma once
#include "../firmware/boot_rom_images.h"
#include "../protocol/peripheral.h"
#include <cstddef>
#include <cstdint>

namespace chisa::boom_system::protocol {
struct RomInputs {
  bool reset=false;
  PeripheralTlA a{};
  bool d_ready=false;
  bool operator==(const RomInputs& other) const {
    return reset==other.reset && a==other.a && d_ready==other.d_ready;
  }
  bool operator!=(const RomInputs& other) const { return !(*this==other); }
};
}
namespace chisa::boom_system::components {
class BootRomModel {
 public:
  static const std::array<std::uint64_t,512>& default_image() {
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    return firmware::large;
#elif defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    return firmware::medium;
#else
    return firmware::small;
#endif
  }
  explicit BootRomModel(const std::array<std::uint64_t,512>& image=default_image()) : image_(image) {
    evaluate({});evaluations_=0;
  }
  const protocol::PeripheralManagerInputs& evaluate(const protocol::RomInputs& input) {
    if (valid_ && input==last_) { ++skipped_;return output_; }
    last_=input;valid_=true;++evaluations_;
    output_.a_ready=input.d_ready;
    output_.d.valid=input.a.valid;output_.d.opcode=1;
    output_.d.size=input.a.size&3;output_.d.source=input.a.source&511;
    // The bus has already selected the 64-KiB device region. Only its first
    // 4 KiB contain firmware; the remaining addresses read as zero.
    const auto offset=input.a.address&65535u;
    output_.d.data=offset<image_.size()*8 ? image_[offset/8] : 0;
    return output_;
  }
  const protocol::PeripheralManagerInputs& outputs() const { return output_; }
  bool active() const { return false; }
  std::uint64_t eval_count() const { return evaluations_; }
  std::uint64_t skipped_count() const { return skipped_; }
 private:
  const std::array<std::uint64_t,512>& image_;
  protocol::RomInputs last_{};
  protocol::PeripheralManagerInputs output_{};
  std::uint64_t evaluations_=0,skipped_=0;
  bool valid_=false;
};
}
