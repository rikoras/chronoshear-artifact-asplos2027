#include "core.h"
#include "../common/boom_lsu_scheduler.h"

namespace chisa::boom_model::wide {
bool Core::memory_available(const MicroOp& u, unsigned load_head, unsigned store_head) const {
  const auto& q = state_.lsu;
  // Like Small, the circular queues reserve one slot: full is next tail ==
  // PRE head. Testing the tail's valid bit would incorrectly allow all kLsq.
  return (!u.uses_ldq || (LsqGeometry::wrap(q.load_tail+1)!=load_head && !test(q.load_valid,q.load_tail))) &&
         (!u.uses_stq || (LsqGeometry::wrap(q.store_tail+1)!=store_head && !test(q.store_valid,q.store_tail)));
}
void Core::allocate_memory(MicroOp& u) {
  auto& q = state_.lsu;
  u.ldq_idx = q.load_tail;u.stq_idx = q.store_tail;
  if (u.exception) return;
  if (u.uses_ldq) {
    if (test(q.load_valid,q.load_tail)) throw std::logic_error("LDQ over-allocation");
    const unsigned index = q.load_tail;
    // Inactive address/data payload holds until a real address/data update.
    q.loads[index].assign(u);q.loads[index].virtual_address=0;
    q.touch_load_values(bit(index));q.load_descriptor_changed |= bit(index);
    q.set_load_value(q.dependencies[index],q.store_valid,index);q.set_load_value(q.youngest_store[index],q.store_tail,index);
    ++q.load_generation[index];q.load_ticket[index]=0;
    q.set_load_mask(q.load_virtual,q.load_virtual&(~bit(index)));q.set_load_mask(q.load_uncacheable,q.load_uncacheable&(~bit(index)));
    q.set_load_mask(q.load_exception,q.load_exception&(~bit(index)));q.set_load_mask(q.load_order_fail,q.load_order_fail&(~bit(index)));
    q.set_load_mask(q.load_observed,q.load_observed&(~bit(index)));q.set_load_mask(q.load_forwarded,q.load_forwarded&(~bit(index)));
    q.set_load_mask(q.load_valid,q.load_valid|(bit(index)));
    q.set_load_mask(q.load_address,q.load_address&(~bit(index)));q.set_load_mask(q.load_executed,q.load_executed&(~bit(index)));q.set_load_mask(q.load_succeeded,q.load_succeeded&(~bit(index)));
    q.load_tail = static_cast<std::uint8_t>(LsqGeometry::wrap(index+1));
  }
  if (u.uses_stq) {
    if (test(q.store_valid,q.store_tail)) throw std::logic_error("STQ over-allocation");
    const unsigned index = q.store_tail;
    q.stores[index].assign(u);q.stores[index].virtual_address=0;
    q.touch_store_values(bit(index));
    ++q.store_generation[index];q.store_ticket[index]=0;
    q.set_store_mask(q.store_virtual,q.store_virtual&(~bit(index)));q.set_store_mask(q.store_exception,q.store_exception&(~bit(index)));
    q.set_store_mask(q.store_valid,q.store_valid|(bit(index)));q.set_store_mask(q.store_address,q.store_address&(~bit(index)));q.set_store_mask(q.store_data,q.store_data&(~bit(index)));
    q.set_store_mask(q.store_committed,q.store_committed&(~bit(index)));q.set_store_mask(q.store_succeeded,q.store_succeeded&(~bit(index)));
    q.store_tail = static_cast<std::uint8_t>(LsqGeometry::wrap(index+1));
  }
}
void Core::load_address(unsigned index, std::uint64_t address) {
  if (index >= kLsq || !test(state_.lsu.load_valid,index)) throw std::out_of_range("live LDQ address port");
  state_.lsu.set_load_value(state_.lsu.loads[index].address,address,index);state_.lsu.set_load_mask(state_.lsu.load_address,state_.lsu.load_address|(bit(index)));
}
void Core::store_address(unsigned index, std::uint64_t address) {
  if (index >= kLsq || !test(state_.lsu.store_valid,index)) throw std::out_of_range("live STQ address port");
  state_.lsu.set_store_value(state_.lsu.stores[index].address,address,index);state_.lsu.set_store_mask(state_.lsu.store_address,state_.lsu.store_address|(bit(index)));
}
void Core::store_data(unsigned index, std::uint64_t data) {
  if (index >= kLsq || !test(state_.lsu.store_valid,index)) throw std::out_of_range("live STQ data port");
  state_.lsu.stores[index].data = data;state_.lsu.touch_store_values(bit(index));   // the data lane is a per-row value
  state_.lsu.set_store_mask(state_.lsu.store_data,state_.lsu.store_data|(bit(index)));
}
void Core::load_finished(unsigned index) {
  if (index >= kLsq || !test(state_.lsu.load_valid,index)) throw std::out_of_range("live LDQ completion");
  state_.lsu.set_load_mask(state_.lsu.load_executed,state_.lsu.load_executed|(bit(index)));state_.lsu.set_load_mask(state_.lsu.load_succeeded,state_.lsu.load_succeeded|(bit(index)));
}
void Core::store_finished(unsigned index) {
  if (index >= kLsq || !test(state_.lsu.store_valid,index)) throw std::out_of_range("live STQ completion");
  state_.lsu.set_store_mask(state_.lsu.store_succeeded,state_.lsu.store_succeeded|(bit(index)));
}
void Core::resolve_memory(const BranchUpdate& update) {
  auto& q = state_.lsu;
  if (!update.resolved && !update.mispredicted && !update.redirect) return;
  for (unsigned index = 0; index < kLsq; ++index) {
    if (test(q.load_valid,index)) {
      if (q.loads[index].branch() & update.mispredicted) {
        q.set_load_mask(q.load_valid,q.load_valid&(~bit(index)));q.set_load_mask(q.load_address,q.load_address&(~bit(index)));
        q.set_load_mask(q.load_executed,q.load_executed&(~bit(index)));q.set_load_mask(q.load_succeeded,q.load_succeeded&(~bit(index)));
        q.set_load_mask(q.load_virtual,q.load_virtual&(~bit(index)));q.set_load_mask(q.load_uncacheable,q.load_uncacheable&(~bit(index)));
        q.set_load_mask(q.load_exception,q.load_exception&(~bit(index)));q.set_load_mask(q.load_order_fail,q.load_order_fail&(~bit(index)));
        q.set_load_mask(q.load_observed,q.load_observed&(~bit(index)));q.set_load_mask(q.load_forwarded,q.load_forwarded&(~bit(index)));q.load_ticket[index]=0;
      }
      if(q.loads[index].clear_branches(update.resolved)) { q.touch_load_values(bit(index));q.load_descriptor_changed |= bit(index); }
    }
    if (test(q.store_valid,index)) {
      if (q.stores[index].branch() & update.mispredicted) {
        if (test(q.store_committed,index)) throw std::logic_error("branch killed a committed store");
        q.set_store_mask(q.store_valid,q.store_valid&(~bit(index)));q.set_store_mask(q.store_address,q.store_address&(~bit(index)));
        q.set_store_mask(q.store_data,q.store_data&(~bit(index)));q.set_store_mask(q.store_succeeded,q.store_succeeded&(~bit(index)));
        q.set_store_mask(q.store_virtual,q.store_virtual&(~bit(index)));q.set_store_mask(q.store_exception,q.store_exception&(~bit(index)));q.store_ticket[index]=0;
      }
      if(q.stores[index].clear_branches(update.resolved)) { q.touch_store_values(bit(index)); }
    }
  }
  if (update.redirect) {
    if (update.load_tail >= kLsq || update.store_tail >= kLsq) throw std::out_of_range("branch LSQ rewind");
    q.load_tail = update.load_tail;q.store_tail = update.store_tail;
    if (!test(q.store_valid,q.store_execute)) q.store_execute=q.store_commit;
  }
}
void Core::commit_memory(const MicroOp& u, RetirementEvent& event) {
  auto& q = state_.lsu;
  if (u.uses_ldq) {
    const unsigned index = u.ldq_idx;
    if (index != q.load_head || !test(q.load_valid,index)) throw std::logic_error("LDQ retirement order");
    q.set_load_mask(q.load_valid,q.load_valid&(~bit(index)));q.set_load_mask(q.load_address,q.load_address&(~bit(index)));
    q.set_load_mask(q.load_executed,q.load_executed&(~bit(index)));q.set_load_mask(q.load_succeeded,q.load_succeeded&(~bit(index)));
    q.set_load_mask(q.load_virtual,q.load_virtual&(~bit(index)));q.set_load_mask(q.load_uncacheable,q.load_uncacheable&(~bit(index)));
    q.set_load_mask(q.load_exception,q.load_exception&(~bit(index)));q.set_load_mask(q.load_order_fail,q.load_order_fail&(~bit(index)));
    q.set_load_mask(q.load_observed,q.load_observed&(~bit(index)));q.set_load_mask(q.load_forwarded,q.load_forwarded&(~bit(index)));q.load_ticket[index]=0;
    q.load_head = static_cast<std::uint8_t>(LsqGeometry::wrap(index+1));
  }
  if (u.uses_stq) {
    const unsigned index = u.stq_idx;
    if (index >= kLsq || !test(q.store_valid,index)) throw std::logic_error("STQ retirement without allocation");
    if (index!=q.store_commit) throw std::logic_error("STQ commit pointer order");
    q.set_store_mask(q.store_committed,q.store_committed|(bit(index)));
    q.store_commit=static_cast<std::uint8_t>(LsqGeometry::wrap(index+1));
    if (u.mem_cmd == 1) {
      if (!test(q.store_address,index) || !test(q.store_data,index))
        throw std::logic_error("ordinary store retired before its data/address");
      event.memory_write = true;event.memory_size = u.mem_size;
      event.memory_address = q.stores[index].address;
      const unsigned bits = 8u << (u.mem_size&3u);
      event.memory_value = q.stores[index].data & (bits == 64 ? UINT64_MAX : (UINT64_C(1)<<bits)-1);
    }
  }
}
bool Core::drain_store(bool ordered) {
  auto& q = state_.lsu;const unsigned head = q.store_head;
  if (!boom_lsu::clear_store(test(q.store_valid,head),test(q.store_committed,head),
                            q.stores[head].fence(),test(q.store_succeeded,head),ordered)) return false;
  q.set_store_mask(q.store_valid,q.store_valid&(~bit(head)));q.set_store_mask(q.store_address,q.store_address&(~bit(head)));q.set_store_mask(q.store_data,q.store_data&(~bit(head)));
  q.set_store_mask(q.store_committed,q.store_committed&(~bit(head)));q.set_store_mask(q.store_succeeded,q.store_succeeded&(~bit(head)));
  q.set_store_mask(q.store_virtual,q.store_virtual&(~bit(head)));q.set_store_mask(q.store_exception,q.store_exception&(~bit(head)));q.store_ticket[head]=0;
  for(unsigned i=0;i<kLsq;++i)q.set_load_value(q.dependencies[i],q.dependencies[i]&~bit(head),i);
  q.store_head = static_cast<std::uint8_t>(LsqGeometry::wrap(head+1));return true;
}
int Core::forward_store(unsigned load, std::uint64_t address, unsigned size) const {
  const auto& q = state_.lsu;
  if (load >= kLsq || !test(q.load_valid,load)) throw std::out_of_range("LDQ forwarding lookup");
  const QueueMask eligible = q.dependencies[load] & q.store_valid;
  for (unsigned age = 1; age <= kLsq; ++age) {
    const unsigned index = static_cast<unsigned>(LsqGeometry::wrap(int(q.youngest_store[load])-int(age)));
    if (!test(eligible,index)) continue;
    if (q.stores[index].fence() || q.stores[index].amo()) return -2;
    if (!test(q.store_address,index) || test(q.store_virtual,index)) continue;
    if ((q.stores[index].address>>3) != (address>>3)) continue;
    const unsigned load_bytes = 1u << (size&3u), store_bytes = 1u << (q.stores[index].size()&3u);
    const unsigned load_mask = ((1u<<load_bytes)-1u) << (address&7u);
    const unsigned store_mask = ((1u<<store_bytes)-1u) << (q.stores[index].address&7u);
    if (!(load_mask & store_mask)) continue;
    if ((load_mask & store_mask) != load_mask || !test(q.store_data,index)) return -2;
    return static_cast<int>(index);
  }
  return -1;
}
}  // namespace chisa::boom_model::wide
