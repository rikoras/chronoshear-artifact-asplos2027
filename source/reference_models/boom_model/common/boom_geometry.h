#pragma once

// Index geometry shared by the legacy backend and compact model migrations.
// A queue's pointer bit width is not its capacity: Large's 5-bit LSQ pointers
// wrap at 24, and its 7-bit ROB indices encode 32 rows with three banks plus
// one unused bank code per row.
namespace boomcfg::geometry {

constexpr int index_width(int entries) {
    int width = 0;
    for (int value = entries - 1; value > 0; value >>= 1) ++width;
    return width;
}

template <int Entries>
struct Ring {
    static_assert(Entries > 0, "a queue must have at least one entry");
    static constexpr int entries = Entries;
    static constexpr int index_bits = index_width(Entries);
    static constexpr unsigned index_mask = (1u << index_bits) - 1u;
    static constexpr bool power_of_two = (Entries & (Entries - 1)) == 0;

    static constexpr bool valid(int index) {
        return index >= 0 && index < Entries;
    }

    // Arithmetic on a physical queue pointer, including backwards rewind.
    // Do not use this to decode an incoming RTL tag: invalid tag codes are
    // not aliases for live entries and must be checked with valid().
    static constexpr int wrap(int index) {
        if constexpr (power_of_two)
            return static_cast<unsigned>(index) & (Entries - 1u);
        const int remainder = index % Entries;
        return remainder < 0 ? remainder + Entries : remainder;
    }
};

template <int Rows, int Banks>
struct BankedRob {
    static_assert(Rows > 0 && (Rows & (Rows - 1)) == 0,
                  "the BOOM ROB has a power-of-two row count");
    static_assert(Banks > 0, "the ROB must have at least one bank");
    static constexpr int rows = Rows;
    static constexpr int banks = Banks;
    static constexpr int bank_bits = index_width(Banks);
    static constexpr int bank_mask = (1u << bank_bits) - 1u;
    static constexpr int entry_count = Rows * Banks;
    static constexpr int wire_count = Rows << bank_bits;

    // These are bit-field operations, not dense-array indexing. In
    // particular, Large (row=31, bank=2) is wire index 126, not 95.
    static constexpr int row(int wire_index) { return wire_index >> bank_bits; }
    static constexpr int bank(int wire_index) { return wire_index & bank_mask; }
    static constexpr int encode(int row_index, int bank_index) {
        return (row_index << bank_bits) | bank_index;
    }
    static constexpr bool valid(int wire_index) {
        return wire_index >= 0 && wire_index < wire_count &&
               bank(wire_index) < Banks;
    }

    // A compact model can store only real entries while keeping the RTL
    // encoding at every seam. Invalid wire/dense codes return an explicit
    // sentinel instead of silently aliasing bank 0 of another row.
    static constexpr int dense_from_wire(int wire_index) {
        return valid(wire_index) ? row(wire_index) * Banks + bank(wire_index) : -1;
    }
    static constexpr int wire_from_dense(int dense_index) {
        return dense_index >= 0 && dense_index < entry_count
                   ? encode(dense_index / Banks, dense_index % Banks)
                   : -1;
    }
};

}  // namespace boomcfg::geometry
