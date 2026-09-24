#pragma once
// One-entry AXI transactions backed by caller-owned sparse memory. The
// synchronous read address also exposes the live memory observation port.
#include "../protocol/axi_memory.h"
namespace chisa::boom_system::components {
using protocol::SparseAxiRamInputs;
using protocol::SparseAxiRamOutputs;
using protocol::AxiRamAccess;
class SparseAxiRam {
 public:
  explicit SparseAxiRam(std::uint32_t read_address_mask = UINT32_C(0x1ffffff))
      : read_address_mask_(read_address_mask) {}

  SparseAxiRamOutputs outputs(const SparseAxiRamInputs& input) const {
    SparseAxiRamOutputs result;
    result.b.valid = w_full_;
    result.b.id = w_id_;
    result.b.response = w_selected_ ? 0 : 3;
    result.b.echo_real_last = w_echo_real_last_;
    const bool write_slot = input.b_ready || !w_full_;
    result.aw_ready = input.w.valid && write_slot;
    result.w_ready = input.aw.valid && write_slot;

    result.r.valid = r_full_;
    result.r.id = r_id_;
    result.r.data = r_data_;
    result.r.response = r_selected_ ? 0 : 3;
    result.r.echo_real_last = r_echo_real_last_;
    result.r.last = true;
    result.ar_ready = input.r_ready || !r_full_;
    return result;
  }

  template <class Read64>
  AxiRamAccess access_trace(const SparseAxiRamInputs& input,
                           const Read64& read64) const {
    AxiRamAccess access;
    access.read_address = read_address_pipe_;
    // The SRAM node is an unconditional read at the registered address.  It
    // can change after a write even while r_data_ holds an older AXI beat.
    access.read_data = read64(UINT32_C(0x80000000) |
                              (read_address_pipe_ << 3));
    const bool write_fire = input.aw.valid && input.w.valid &&
                            (input.b_ready || !w_full_);
    if (write_fire && selected(input.aw.address)) {
      access.write_mask = input.w.strobe;
      access.write_address = (input.aw.address >> 3) & read_address_mask_;
      access.write_data = input.w.data;
    }
    return access;
  }

  template <class Read64, class Write64Masked>
  void commit(const SparseAxiRamInputs& input, const Read64& read64,
              const Write64Masked& write64_masked) {
    const SparseAxiRamOutputs current = outputs(input);
    const bool write_fire = input.aw.valid && current.aw_ready;
    const bool b_fire = current.b.valid && input.b_ready;
    const bool read_fire = input.ar.valid && current.ar_ready;
    const bool r_fire = current.r.valid && input.r_ready;

    // The synchronous SRAM read produces the newly addressed beat directly
    // after this edge; a holding register preserves it on following cycles.
    if (read_fire) {
      read_address_pipe_ =
          (input.ar.address >> 3) & read_address_mask_;
      r_id_ = input.ar.id & 0xf;
      r_echo_real_last_ = input.ar.echo_real_last;
      r_selected_ = selected(input.ar.address);
      // The RTL always enables its SRAM read port.  Address decode changes
      // RESP but does not gate DATA, and the 256 MiB array indexes only the
      // low 28 address bits.  Preserve that otherwise-don't-care payload too.
      r_data_ = read64(storage_address(input.ar.address));
    }

    // FIRRTL's read-under-write mode is undefined.  The harness traffic does
    // not collide; applying the read above before the write makes that choice
    // explicit and deterministic for the software shell.
    if (write_fire) {
      w_id_ = input.aw.id & 0xf;
      w_echo_real_last_ = input.aw.echo_real_last;
      w_selected_ = selected(input.aw.address);
      if (w_selected_)
        write64_masked(storage_address(input.aw.address), input.w.data,
                       input.w.strobe);
    }

    bool next_w_full = (w_full_ && !b_fire) || write_fire;
    bool next_r_full = (r_full_ && !r_fire) || read_fire;
    if (input.reset) {
      next_w_full = false;
      next_r_full = false;
    }
    w_full_ = next_w_full;
    r_full_ = next_r_full;
  }

  bool active() const { return w_full_ || r_full_; }
  bool w_full() const { return w_full_; }
  std::uint8_t w_id() const { return w_id_; }
  bool w_echo_real_last() const { return w_echo_real_last_; }
  bool r_full() const { return r_full_; }
  std::uint8_t r_id() const { return r_id_; }
  std::uint32_t read_address_pipe() const { return read_address_pipe_; }

 private:
  static bool selected(std::uint32_t address) {
    return (address & UINT32_C(0xf0000000)) == UINT32_C(0x80000000);
  }
  static std::uint32_t storage_address(std::uint32_t address) {
    return UINT32_C(0x80000000) |
           (address & UINT32_C(0x0ffffff8));
  }

  bool w_full_ = false;
  std::uint8_t w_id_ = 0;
  bool w_echo_real_last_ = false;
  bool w_selected_ = false;
  bool r_full_ = false;
  std::uint8_t r_id_ = 0;
  bool r_echo_real_last_ = false;
  bool r_selected_ = false;
  std::uint64_t r_data_ = 0;
  std::uint32_t read_address_mask_ = UINT32_C(0x1ffffff);
  std::uint32_t read_address_pipe_ = 0;
};

}
