#pragma once
// Software beat packing. One saved upper half supports a two-beat split;
// one saved lower half supports a merge. The same transaction metadata stays
// with both halves and only accepted transfers advance either cursor.
#include <cstdint>
#include <type_traits>
#include "../protocol/coherence.h"

namespace chisa::boom_system::components {
template<class Packet> inline bool tl_data(const Packet& packet) {
  if constexpr(std::is_same_v<Packet,protocol::MbusTlA>) return packet.opcode<4;
  else return (packet.opcode&1)!=0;
}
inline std::uint16_t tl_mask16(std::uint32_t address,unsigned size) {
  if(size>=4) return UINT16_MAX;
  const unsigned bytes=1u<<size;
  return static_cast<std::uint16_t>(((1u<<bytes)-1)<<(address&(16-bytes)));
}
template<class Packet> struct WidthTransfer {Packet output{};bool input_ready=false,last=false;};

template<class Packet> class TlSplit {
 public:
  bool second=false,holding=false;
  Packet saved{};
  WidthTransfer<Packet> evaluate(const Packet& input,bool ready,bool select_upper) const {
    WidthTransfer<Packet> transfer;
    auto& output=transfer.output;output=holding?saved:input;
    output.valid=holding || input.valid;
    transfer.last=!tl_data(output) || second==(output.size>=4);
    transfer.input_ready=ready && !holding;
    const bool upper=second || select_upper;
    output.data=upper ? output.data_hi:input.data;
    output.data_hi=0;
    if constexpr(std::is_same_v<Packet,protocol::MbusTlA>) output.mask=(output.mask>>(upper?8:0))&255;
    return transfer;
  }
  void commit(const Packet& input,bool ready,const WidthTransfer<Packet>& transfer,bool reset) {
    if(input.valid && transfer.input_ready && !transfer.last) {saved=input;holding=true;}
    if(transfer.output.valid && ready) {second=transfer.last?false:!second;if(transfer.last) holding=false;}
    if(reset) second=holding=false;
  }
};

template<class Packet> class TlMerge {
 public:
  bool second=false,corrupt=false,lower_written=false;
  std::uint64_t lower=0;
  std::uint8_t lower_mask=0;
  WidthTransfer<Packet> evaluate(const Packet& input,bool ready) const {
    WidthTransfer<Packet> transfer;auto& output=transfer.output;output=input;
    transfer.last=!tl_data(input) || second==(input.size>=4);
    transfer.input_ready=ready || !transfer.last;
    output.valid=input.valid && transfer.last;
    const bool saved_lower=second && input.size>=4 && lower_written;
    output.data=saved_lower?lower:input.data;output.data_hi=input.data;
    output.corrupt=input.corrupt || corrupt;
    if constexpr(std::is_same_v<Packet,protocol::MbusTlA>) {
      const unsigned payload_mask=((input.mask&255)<<8)|(saved_lower?lower_mask:input.mask&255);
      output.mask=(tl_data(input)?payload_mask:UINT16_MAX)&tl_mask16(input.address,input.size);
    }
    return transfer;
  }
  void commit(const Packet& input,const WidthTransfer<Packet>& transfer,bool reset) {
    if(input.valid && transfer.input_ready) {
      if(!transfer.last) {
        lower=transfer.output.data;
        if constexpr(std::is_same_v<Packet,protocol::MbusTlA>)
          if(!(second && input.size>=4 && lower_written)) lower_mask=input.mask&255;
        lower_written=true;
      }
      second=transfer.last?false:!second;corrupt=transfer.last?false:transfer.output.corrupt;
    }
    if(reset) second=corrupt=lower_written=false;
  }
};
} // namespace chisa::boom_system::components
