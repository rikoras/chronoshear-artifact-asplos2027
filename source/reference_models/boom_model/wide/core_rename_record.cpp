#include "core.h"
#include "record_fields.h"
namespace chisa::boom_model::wide {
void Core::write_rename_uop(unsigned lane) {
  const auto& u=state_.rename.held[lane];
#define FIELD(name) for(unsigned domain=0;domain<2;++domain) write_record(*record_,fields::rename_uop_##name[domain][lane],u.name)
  // Medium carries these five fields in its single-thread contract; the Large
  // partition-cut contracts carry them too. A layout without them makes the
  // writes no-ops. rename-stage.scala:117-135 writes the whole entry every
  // edge and r_valid gates its use, so a valid memory entry's command, size,
  // sign and atomic flag are read downstream.
  FIELD(br_mask);FIELD(mem_cmd);FIELD(mem_size);FIELD(mem_signed);FIELD(is_amo);
  FIELD(br_tag);FIELD(dst_rtype);FIELD(edge_inst);FIELD(exception);FIELD(flush_on_commit);
  FIELD(fp_val);FIELD(ftq_idx);FIELD(fu_code);FIELD(imm_packed);FIELD(iq_type);
  FIELD(is_br);FIELD(is_fence);FIELD(is_fencei);FIELD(is_jal);FIELD(is_jalr);FIELD(is_rvc);
  FIELD(is_sfb);FIELD(is_sys_pc2epc);FIELD(is_unique);FIELD(ldst);FIELD(ldst_val);
  FIELD(lrs1);FIELD(lrs1_rtype);FIELD(lrs2);FIELD(lrs2_rtype);FIELD(lrs3);FIELD(pc_lob);
  FIELD(prs1);FIELD(prs2);FIELD(prs3);FIELD(stale_pdst);FIELD(taken);FIELD(uopc);FIELD(uses_ldq);FIELD(uses_stq);
#undef FIELD
}
void Core::write_rename_valids() {
  for(unsigned lane=0;lane<kWidth;++lane) write_record(*record_,fields::rename_valid[lane],state_.rename.valid[lane]);
  if (cut_lanes_) {
    write_record(*record_,fields::rename_busy[0],state_.rename.integer.busy);
    write_record(*record_,fields::rename_busy[1],state_.rename.floating.busy);
  }
}
}  // namespace chisa::boom_model::wide
