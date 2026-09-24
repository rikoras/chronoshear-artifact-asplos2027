#include "core.h"
#include "record_fields.h"
#include "../common/diagnostic_monitor.h"
#include "diagnostics/record_dump.h"
#include <algorithm>

namespace chisa::boom_model::wide {

unsigned Core::first(PhysicalMask mask) {
  const auto low = static_cast<std::uint64_t>(mask);
  if (low) return static_cast<unsigned>(__builtin_ctzll(low));
  const auto high = static_cast<std::uint64_t>(mask >> 64);
  if (!high) throw std::logic_error("empty physical-register selection");
  return 64u + static_cast<unsigned>(__builtin_ctzll(high));
}
void Core::reset_domain(RenameDomain& domain, unsigned count) {
  domain = {};
  domain.free = ((PhysicalMask{1} << count) - 1) & ~PhysicalMask{1};
  write_record(*record_,fields::rename_free[count==boomcfg::NUM_FPREGS],domain.free);
}
void Core::map_write(RenameDomain& domain, unsigned logical, unsigned physical, bool floating) {
  logical &= 31u;
  if (!floating && logical == 0) return;
  if (physical >= (floating ? unsigned(boomcfg::NUM_FPREGS) : unsigned(boomcfg::NUM_PREGS))) throw std::out_of_range("physical map value");
  if (domain.map[logical] == physical) return;
  domain.map[logical] = static_cast<std::uint8_t>(physical);
  write_record(*record_,fields::rename_map[floating][logical],physical);

}
void Core::preselect(RenameDomain& domain, PhysicalMask pre_free, std::uint8_t consumed) {
  // SelectFirstN observes PRE free-list bits. A port retains its selection
  // until consumed; returns and branch recovery on this edge are not inputs
  // to this combinational selection, matching the Small implementation.
  PhysicalMask candidates = pre_free & ~PhysicalMask{1};
  const unsigned type=&domain==&state_.rename.floating;
  const auto old_free=domain.free;
  for (unsigned lane = 0; lane < kWidth; ++lane) {
    const bool available = candidates != 0;
    unsigned physical = 0;
    if (available) { physical = first(candidates); candidates &= candidates - 1; }
    const bool held = domain.selected_valid[lane];
    const bool request = (consumed >> lane) & 1u;
    if ((!held || request) && available) {
      domain.selected[lane] = static_cast<std::uint8_t>(physical);
      write_record(*record_,fields::rename_selected[type][lane],physical);
      domain.free &= ~(PhysicalMask{1} << physical);
    }
    const auto valid=static_cast<std::uint8_t>((held && !request) || available);
    if(domain.selected_valid[lane]!=valid) write_record(*record_,fields::rename_selection_valid[type][lane],valid);
    domain.selected_valid[lane]=valid;
  }
  if(domain.free!=old_free) write_record(*record_,fields::rename_free[type],domain.free);
}
void Core::restore_rename(unsigned tag) {
  if (tag >= kBranches) throw std::out_of_range("branch checkpoint");
  for (unsigned type = 0; type < 2; ++type) {
    auto& domain = type ? state_.rename.floating : state_.rename.integer;
    domain.map = domain.checkpoints[tag];
    for(unsigned i=0;i<32;++i) write_record(*record_,fields::rename_map[type][i],domain.map[i]);
    const PhysicalMask returned = domain.branch_allocations[tag];
    domain.free |= returned;write_record(*record_,fields::rename_free[type],domain.free);
    for(unsigned t=0;t<kBranches;++t) {
      auto& allocated=domain.branch_allocations[t];const auto next=allocated&~returned;
      if(next!=allocated) { allocated=next;write_record(*record_,fields::rename_alloc[type][t],next); }
    }
  }
  state_.rename.valid.fill(0);
}
void Core::return_register(const MicroOp& u, bool rollback) {
  const bool floating = u.dst_rtype == RT_FLT;
  if (!u.ldst_val || (!floating && (u.dst_rtype != RT_FIX || u.ldst == 0))) return;
  auto& domain = floating ? state_.rename.floating : state_.rename.integer;
  const unsigned physical = rollback ? u.pdst : u.stale_pdst;
  if (physical) { domain.free |= PhysicalMask{1} << physical;write_record(*record_,fields::rename_free[floating],domain.free); }
  if (rollback) map_write(domain,u.ldst,u.stale_pdst,floating);
}
bool Core::accept_decode(const std::array<MicroOp,kWidth>& group, std::uint8_t mask,
                         BranchMask allocation_view, bool debug) {
  mask &= kDispatchMask;
  if (state_.rename.pending_mask() || !mask) return false;
  BranchMask allocated=allocation_view,current=state_.rename.branches;
  std::uint8_t accepted=0;
  const auto remaining=static_cast<std::uint8_t>(mask&~state_.decode_finished);
  for (unsigned lane=0;lane<kWidth;++lane) {
    if (!(remaining&(1u<<lane))) continue;
    auto u=group[lane];
    const auto free=static_cast<BranchMask>(~allocated&kBranchMask);
    if ((u.is_br || u.is_jalr) && !free) break;
    u.br_tag=free ? static_cast<std::uint8_t>(__builtin_ctz(unsigned(free))) : 0;
    u.br_mask=current;
    CHISA_DIAG(
      using namespace ::chisa::diagnostic;
      if (RecordDump::instance().selected(state_.cycle))
        checkpoint("rename","branch-mask-assign",state_.cycle,Layer::Internal,
            {{"lane",lane},{"assigned",u.br_mask},{"branches",state_.rename.branches},
             {"allocation_view",allocation_view},{"tag",u.br_tag},{"is_br",u.is_br},
             {"is_jalr",u.is_jalr},{"accepted_so_far",accepted}});
    );
    if (u.is_br || u.is_jalr) {
      allocated |= BranchMask{1}<<u.br_tag;current |= BranchMask{1}<<u.br_tag;
    }
    state_.rename.held[lane]=u;
    rename_bypass_lane(lane,false);mark_rename_uop(lane);
    accepted |= 1u<<lane;
  }
  state_.rename.set_pending(accepted);state_.rename.branches=current;
  state_.decode_finished |= accepted;held_debug_=debug;
  // dec_ready is the final lane's fire, not completion of a partial prefix.
  const bool complete=(state_.decode_finished&kDispatchMask)==kDispatchMask;
  if(complete)state_.decode_finished=0;
  return complete;
}
void Core::rename_bypass_lane(unsigned lane,bool publish) {
  auto& u=state_.rename.held[lane];
  const auto& integer=state_.rename.integer;const auto& floating=state_.rename.floating;
  const auto& a=u.lrs1_rtype==RT_FLT ? floating : integer;
  const auto& b=u.lrs2_rtype==RT_FLT ? floating : integer;
  const auto p1=a.map[u.lrs1&31u],p2=b.map[u.lrs2&31u],p3=floating.map[u.lrs3&31u];
  const auto stale=(u.dst_rtype==RT_FLT ? floating : integer).map[u.ldst&31u];
  const bool moved=u.prs1!=p1 || u.prs2!=p2 || u.prs3!=p3 || u.stale_pdst!=stale;
  // The rename entry keeps the mapping, which is what its published field
  // holds. core.scala:690-692 then marks a source busy only for an integer or
  // floating type, so a pass-through or unused source is never busy.
  u.prs1=p1;u.prs2=p2;u.prs3=p3;u.stale_pdst=stale;
  u.prs1_busy=(u.lrs1_rtype==RT_FIX || u.lrs1_rtype==RT_FLT) && ((a.busy>>p1)&1u);
  u.prs2_busy=(u.lrs2_rtype==RT_FIX || u.lrs2_rtype==RT_FLT) && ((b.busy>>p2)&1u);
  u.prs3_busy=u.frs3_en && ((floating.busy>>p3)&1u);
  if(moved && publish) {
    for(unsigned d=0;d<2;++d) {
      write_record(*record_,fields::rename_uop_prs1[d][lane],p1);
      write_record(*record_,fields::rename_uop_prs2[d][lane],p2);
      write_record(*record_,fields::rename_uop_prs3[d][lane],p3);
      write_record(*record_,fields::rename_uop_stale_pdst[d][lane],stale);
    }
  }
}
void Core::rename_bypass_held() {
  for(unsigned lane=0;lane<kWidth;++lane) if(state_.rename.valid[lane]) rename_bypass_lane(lane);
}
void Core::rename_dispatch(MicroOp& u, unsigned lane) {
  if (lane >= kWidth) throw std::out_of_range("rename lane");
  // Refresh against maps after older lanes on this same edge. This supplies
  // cross-lane RAW/WAW forwarding, not three independent Small renamers.
  rename_bypass_lane(lane);
  u = state_.rename.held[lane];
  // core.scala:680 hands the dispatched uop the architectural field of a
  // source that is neither integer nor floating, and functional-unit.scala:315
  // reads a CSR immediate out of it. The rename entry itself keeps the mapping.
  if (u.lrs1_rtype!=RT_FIX && u.lrs1_rtype!=RT_FLT) u.prs1=static_cast<std::uint8_t>(u.lrs1);
  const bool floating = u.dst_rtype == RT_FLT;
  const bool writes = u.ldst_val && (floating || (u.dst_rtype == RT_FIX && u.ldst != 0));
  u.pdst = 0;
  if (writes) {
    auto& domain = floating ? state_.rename.floating : state_.rename.integer;
    if (!domain.selected_valid[lane]) throw std::logic_error("dispatch without allocation");
    u.pdst = domain.selected[lane];
    map_write(domain,u.ldst,u.pdst,floating);
    domain.busy |= PhysicalMask{1} << u.pdst;
    for(unsigned tag=0;tag<kBranches;++tag) {
      auto& list=domain.branch_allocations[tag];const auto next=list|(PhysicalMask{1}<<u.pdst);
      if(next!=list) { list=next;write_record(*record_,fields::rename_alloc[floating][tag],next); }
    }
  }
  if (u.is_br || u.is_jalr) {
    const unsigned tag = u.br_tag;
    state_.rename.integer.checkpoints[tag] = state_.rename.integer.map;
    state_.rename.integer.branch_allocations[tag] = 0;
    for(unsigned i=0;i<32;++i) write_record(*record_,fields::rename_checkpoint[0][tag][i],state_.rename.integer.map[i]);
    write_record(*record_,fields::rename_alloc[0][tag],PhysicalMask{0});
    if (!u.is_sfb || u.is_jalr) {
      state_.rename.floating.checkpoints[tag] = state_.rename.floating.map;
      state_.rename.floating.branch_allocations[tag] = 0;
      for(unsigned i=0;i<32;++i) write_record(*record_,fields::rename_checkpoint[1][tag][i],state_.rename.floating.map[i]);
      write_record(*record_,fields::rename_alloc[1][tag],PhysicalMask{0});
    }
  }
}
}  // namespace chisa::boom_model::wide
