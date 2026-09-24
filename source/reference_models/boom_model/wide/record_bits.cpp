#include "record_bits.h"

namespace chisa::boom_model::wide {
void write_record_generic(contract::Image& record,const RecordField& field,std::uint64_t value) {
  write_record_fragments(record,field,value);
}
void write_record_generic(contract::Image& record,const RecordField& field,unsigned __int128 value) {
  write_record_fragments(record,field,value);
}
} // namespace chisa::boom_model::wide
