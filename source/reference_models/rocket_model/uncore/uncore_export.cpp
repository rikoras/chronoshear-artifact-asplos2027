#include <stdexcept>
#include "generated/image.h"
#include "uncore/uncore.h"
#include "uncore/uncore_wires.h"

namespace chisa::rocket_model::uncore {

// The generated audit names every unprojected obligation. These routines do
// not fill such fields, and do not authorize suppressing their RTL checks.
// Only the parent qualified contract may select a proven valid-domain view.
void Uncore::export_image(Image& image) const {
  if (!evaluated_) throw std::logic_error("uncore PRE export requires evaluate");
#define UNC_PRE(group, member, bits, value) \
  image.group.member = static_cast<decltype(image.group.member)>(uint64_t(value) & (UINT64_MAX >> (64 - bits)));
#define UNC_POST(group, member, bits, value)
#include "uncore/generated/uncore_oracles.inc"
#undef UNC_POST
#undef UNC_PRE
}

void Uncore::export_post_image(Image& image) const {
#define UNC_PRE(group, member, bits, value)
#define UNC_POST(group, member, bits, value) \
  image.group.member = static_cast<decltype(image.group.member)>(uint64_t(value) & (UINT64_MAX >> (64 - bits)));
#include "uncore/generated/uncore_oracles.inc"
#undef UNC_POST
#undef UNC_PRE
}

}  // namespace chisa::rocket_model::uncore
