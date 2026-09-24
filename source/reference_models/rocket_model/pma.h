// Physical memory attributes of the locked Rocket DefaultConfig.
//
// Written from the design's address map and device parameters (the TileLink
// manager parameters of each device): which address ranges exist, and which
// of them support full/partial puts, atomics, execution, and carry side
// effects.  The TLB (TLB.scala) combines these with the legality test the
// same way; the PTW (PTW.scala) needs page-granularity homogeneity per
// page-table level.
#pragma once
#include <cstdint>

namespace chisa::rocket_model {

struct Pma {
  bool legal;        // inside one of the seven device ranges
  bool homogeneous;  // the page around the address lies inside one device
  bool cacheable;    // DRAM (supports Acquire through the broadcast hub)
  bool w;            // supports PutFull
  bool pp;           // supports PutPartial
  bool al;           // supports logical atomics (control-bus devices behind the atomics automaton)
  bool aa;           // supports arithmetic atomics
  bool x;            // executable
  bool eff;          // reads or writes have side effects
};

struct PmaDevice {
  uint64_t base, size;
  bool cacheable, w, pp, al, aa, x, eff;
};

// debug module, error device, boot ROM, CLINT, PLIC, MMIO port, DRAM.
inline constexpr PmaDevice kPmaDevices[7] = {
    {0x00000000, 0x00001000, false, true, true, true, true, true, true},    // debug
    {0x00003000, 0x00001000, false, true, true, true, true, true, false},   // error device
    {0x00010000, 0x00010000, false, false, false, false, false, true, false},  // boot ROM
    {0x02000000, 0x00010000, false, true, true, true, true, false, true},   // CLINT
    {0x0c000000, 0x04000000, false, true, true, true, true, false, true},   // PLIC
    {0x60000000, 0x20000000, false, true, true, false, false, true, true},  // MMIO port (AXI4)
    {0x80000000, 0x10000000, true, true, true, false, false, true, false},  // DRAM
};

inline const PmaDevice* pma_device(uint64_t addr) {
  for (const PmaDevice& d : kPmaDevices) if (addr >= d.base && addr < d.base + d.size) return &d;
  return nullptr;
}

// `addr` is the full physical address the TLB forms (up to 40 bits).
inline Pma pma_lookup(uint64_t addr) {
  Pma p{};
  const PmaDevice* d = pma_device(addr);
  if (!d) return p;
  p.legal = true;
  p.homogeneous = true;  // every device is at least page sized and page aligned
  p.cacheable = d->cacheable;
  p.w = d->w; p.pp = d->pp; p.al = d->al; p.aa = d->aa; p.x = d->x; p.eff = d->eff;
  return p;
}

// PTW page-granularity homogeneity per page-table level (level 0 = 1 GiB,
// 1 = 2 MiB, 2 = 4 KiB): the page containing the address lies inside one
// device.  Chisel indexes its three-entry table with the two-bit level, so
// level 3 reads the last entry.
inline bool pma_level_homogeneous(uint64_t pte_addr, unsigned level) {
  const uint64_t page = level == 0 ? (UINT64_C(1) << 30) : level == 1 ? (UINT64_C(1) << 21) : (UINT64_C(1) << 12);
  const uint64_t start = pte_addr & ~(page - 1);
  for (const PmaDevice& d : kPmaDevices)
    if (start >= d.base && start + page <= d.base + d.size) return true;
  return false;
}

}  // namespace chisa::rocket_model
