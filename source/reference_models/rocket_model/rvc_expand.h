#pragma once

#include <cstdint>

namespace chisa::rocket_model {

// RV64C instruction expansion by ISA fields. Reserved encodings return zero,
// which the main semantic decoder rejects. Hint encodings remain harmless ops.
// Returns the expanded 32-bit instruction; sets *is_rvc=true if input was 16-bit.

inline uint32_t rvc_expand(uint16_t cinst, bool* is_rvc) {
    uint8_t op = cinst & 0x3;
    if (op == 0x3) {
        *is_rvc = false;
        return cinst; // not compressed (only lower 16 bits passed)
    }
    *is_rvc = true;

    uint8_t funct3 = (cinst >> 13) & 0x7;
    uint32_t expanded = 0; // illegal unless an ISA operation is recognized

    switch (op) {
    case 0x0: { // Quadrant 0
        switch (funct3) {
        case 0: { // C.ADDI4SPN -> addi rd', x2, imm
            uint32_t nzuimm = ((cinst >> 5) & 0x1) << 3 |
                              ((cinst >> 6) & 0x1) << 2 |
                              ((cinst >> 7) & 0xF) << 6 |
                              ((cinst >> 11) & 0x3) << 4;
            uint8_t rd = ((cinst >> 2) & 0x7) + 8;
            if (!nzuimm) return 0;
            expanded = (nzuimm << 20) | (2 << 15) | (rd << 7) | 0x13;
            break;
        }
        case 1: { // C.FLD -> fld rd', offset(rs1')
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            uint8_t rd  = ((cinst >> 2) & 0x7) + 8;
            uint32_t off = ((cinst >> 5) & 0x3) << 6 |
                           ((cinst >> 10) & 0x7) << 3;
            expanded = (off << 20) | (rs1 << 15) | (3 << 12) | (rd << 7) | 0x07;
            break;
        }
        case 2: { // C.LW -> lw rd', offset(rs1')
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            uint8_t rd  = ((cinst >> 2) & 0x7) + 8;
            uint32_t off = ((cinst >> 5) & 0x1) << 6 |
                           ((cinst >> 6) & 0x1) << 2 |
                           ((cinst >> 10) & 0x7) << 3;
            expanded = (off << 20) | (rs1 << 15) | (2 << 12) | (rd << 7) | 0x03;
            break;
        }
        case 3: { // C.LD -> ld rd', offset(rs1')
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            uint8_t rd  = ((cinst >> 2) & 0x7) + 8;
            uint32_t off = ((cinst >> 5) & 0x3) << 6 |
                           ((cinst >> 10) & 0x7) << 3;
            expanded = (off << 20) | (rs1 << 15) | (3 << 12) | (rd << 7) | 0x03;
            break;
        }
        case 4: return 0; // reserved quadrant-0 encoding
        case 5: { // C.FSD -> fsd rs2', offset(rs1')
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            uint8_t rs2 = ((cinst >> 2) & 0x7) + 8;
            uint32_t off = ((cinst >> 5) & 0x3) << 6 |
                           ((cinst >> 10) & 0x7) << 3;
            expanded = (((off >> 5) & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) |
                       (3 << 12) | ((off & 0x1F) << 7) | 0x27;
            break;
        }
        case 6: { // C.SW -> sw rs2', offset(rs1')
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            uint8_t rs2 = ((cinst >> 2) & 0x7) + 8;
            uint32_t off = ((cinst >> 5) & 0x1) << 6 |
                           ((cinst >> 6) & 0x1) << 2 |
                           ((cinst >> 10) & 0x7) << 3;
            uint32_t imm115 = (off >> 5) & 0x7F;
            uint32_t imm40  = off & 0x1F;
            expanded = (imm115 << 25) | (rs2 << 20) | (rs1 << 15) | (2 << 12) | (imm40 << 7) | 0x23;
            break;
        }
        case 7: { // C.SD -> sd rs2', offset(rs1')
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            uint8_t rs2 = ((cinst >> 2) & 0x7) + 8;
            uint32_t off = ((cinst >> 5) & 0x3) << 6 |
                           ((cinst >> 10) & 0x7) << 3;
            uint32_t imm115 = (off >> 5) & 0x7F;
            uint32_t imm40  = off & 0x1F;
            expanded = (imm115 << 25) | (rs2 << 20) | (rs1 << 15) | (3 << 12) | (imm40 << 7) | 0x23;
            break;
        }
        }
        break;
    }
    case 0x1: { // Quadrant 1
        switch (funct3) {
        case 0: { // C.ADDI / C.NOP -> addi rd, rd, imm
            uint8_t rd = (cinst >> 7) & 0x1F;
            int32_t imm = ((cinst >> 12) & 0x1) ? -32 : 0;
            imm |= (cinst >> 2) & 0x1F;
            if ((cinst >> 12) & 0x1) imm |= ~0x1F; // sign extend
            expanded = ((imm & 0xFFF) << 20) | (rd << 15) | (0 << 12) | (rd << 7) | 0x13;
            break;
        }
        case 1: { // C.ADDIW -> addiw rd, rd, imm
            uint8_t rd = (cinst >> 7) & 0x1F;
            int32_t imm = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) ? (~0x1F) : 0);
            if (!rd) return 0;
            expanded = (uint32_t(imm & 0xFFF) << 20) | (rd << 15) | (rd << 7) | 0x1B;
            break;
        }
        case 2: { // C.LI -> addi rd, x0, imm
            uint8_t rd = (cinst >> 7) & 0x1F;
            int32_t imm = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) ? (~0x1F) : 0);
            expanded = ((imm & 0xFFF) << 20) | (0 << 15) | (0 << 12) | (rd << 7) | 0x13;
            break;
        }
        case 3: { // C.LUI / C.ADDI16SP
            uint8_t rd = (cinst >> 7) & 0x1F;
            // Zero immediate is reserved for both LUI and ADDI16SP.
            uint32_t nzbits = ((cinst >> 12) & 0x1) | ((cinst >> 2) & 0x1F);
            if (!nzbits) return 0;
            if (rd == 2) { // C.ADDI16SP
                int32_t imm = ((cinst >> 12) & 0x1) ? -512 : 0;
                imm |= ((cinst >> 3) & 0x3) << 7;
                imm |= ((cinst >> 5) & 0x1) << 6;
                imm |= ((cinst >> 2) & 0x1) << 5;
                imm |= ((cinst >> 6) & 0x1) << 4;
                if ((cinst >> 12) & 0x1) imm |= ~0x1FF;
                expanded = ((imm & 0xFFF) << 20) | ((uint32_t)rd << 15) | (0 << 12) |
                           ((uint32_t)rd << 7) | 0x13;
            } else {
                // C.LUI; rd=x0 is a hint with no architectural write
                int32_t imm = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) ? (~0x1F) : 0);
                uint32_t uimm = static_cast<uint32_t>(imm) & 0xFFFFF;
                expanded = (uimm << 12) | (rd << 7) | 0x37;
            }
            break;
        }
        case 4: { // Misc ALU
            uint8_t funct2 = (cinst >> 10) & 0x3;
            uint8_t rd = ((cinst >> 7) & 0x7) + 8;
            switch (funct2) {
            case 0: { // C.SRLI
                uint8_t shamt = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) << 5);
                expanded = (shamt << 20) | (rd << 15) | (5 << 12) | (rd << 7) | 0x13;
                break;
            }
            case 1: { // C.SRAI
                uint8_t shamt = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) << 5);
                expanded = (0x20 << 25) | (shamt << 20) | (rd << 15) | (5 << 12) | (rd << 7) | 0x13;
                break;
            }
            case 2: { // C.ANDI
                int32_t imm = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) ? (~0x1F) : 0);
                expanded = ((imm & 0xFFF) << 20) | (rd << 15) | (7 << 12) | (rd << 7) | 0x13;
                break;
            }
            case 3: {
                uint8_t rs2 = ((cinst >> 2) & 0x7) + 8;
                uint8_t funct1 = (cinst >> 12) & 0x1;
                uint8_t funct2b = (cinst >> 5) & 0x3;
                if (funct1 == 0) {
                    switch (funct2b) {
                    case 0: // C.SUB
                        expanded = (0x20 << 25) | (rs2 << 20) | (rd << 15) | (0 << 12) | (rd << 7) | 0x33;
                        break;
                    case 1: // C.XOR
                        expanded = (rs2 << 20) | (rd << 15) | (4 << 12) | (rd << 7) | 0x33;
                        break;
                    case 2: // C.OR
                        expanded = (rs2 << 20) | (rd << 15) | (6 << 12) | (rd << 7) | 0x33;
                        break;
                    case 3: // C.AND
                        expanded = (rs2 << 20) | (rd << 15) | (7 << 12) | (rd << 7) | 0x33;
                        break;
                    }
                } else {
                    switch (funct2b) {
                    case 0: // C.SUBW
                        expanded = (0x20 << 25) | (rs2 << 20) | (rd << 15) | (0 << 12) | (rd << 7) | 0x3B;
                        break;
                    case 1: // C.ADDW
                        expanded = (rs2 << 20) | (rd << 15) | (0 << 12) | (rd << 7) | 0x3B;
                        break;
                    case 2: case 3: return 0;
                    }
                }
                break;
            }
            }
            break;
        }
        case 5: { // C.J -> jal x0, offset
            uint32_t b = cinst;
            int32_t off = 0;
            off |= ((b >> 3) & 0x7) << 1;
            off |= ((b >> 11) & 0x1) << 4;
            off |= ((b >> 2) & 0x1) << 5;
            off |= ((b >> 7) & 0x1) << 6;
            off |= ((b >> 6) & 0x1) << 7;
            off |= ((b >> 9) & 0x3) << 8;
            off |= ((b >> 8) & 0x1) << 10;
            off |= ((b >> 12) & 0x1) << 11;
            if ((b >> 12) & 0x1) off |= ~0x7FF; // sign extend
            // J-type encoding: imm[20|10:1|11|19:12]
            uint32_t jimm = ((off >> 20) & 0x1) << 31 |
                            ((off >> 1) & 0x3FF) << 21 |
                            ((off >> 11) & 0x1) << 20 |
                            ((off >> 12) & 0xFF) << 12;
            expanded = jimm | (0 << 7) | 0x6F;
            break;
        }
        case 6: { // C.BEQZ -> beq rs1', x0, offset
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            int32_t off = 0;
            off |= ((cinst >> 3) & 0x3) << 1;
            off |= ((cinst >> 10) & 0x3) << 3;
            off |= ((cinst >> 2) & 0x1) << 5;
            off |= ((cinst >> 5) & 0x3) << 6;
            off |= ((cinst >> 12) & 0x1) << 8;
            if ((cinst >> 12) & 0x1) off |= ~0xFF;
            uint32_t imm12 = (off >> 12) & 0x1;
            uint32_t imm105 = (off >> 5) & 0x3F;
            uint32_t imm41 = (off >> 1) & 0xF;
            uint32_t imm11 = (off >> 11) & 0x1;
            expanded = (imm12 << 31) | (imm105 << 25) | (0 << 20) | (rs1 << 15) |
                       (0 << 12) | (imm41 << 8) | (imm11 << 7) | 0x63;
            break;
        }
        case 7: { // C.BNEZ -> bne rs1', x0, offset
            uint8_t rs1 = ((cinst >> 7) & 0x7) + 8;
            int32_t off = 0;
            off |= ((cinst >> 3) & 0x3) << 1;
            off |= ((cinst >> 10) & 0x3) << 3;
            off |= ((cinst >> 2) & 0x1) << 5;
            off |= ((cinst >> 5) & 0x3) << 6;
            off |= ((cinst >> 12) & 0x1) << 8;
            if ((cinst >> 12) & 0x1) off |= ~0xFF;
            uint32_t imm12 = (off >> 12) & 0x1;
            uint32_t imm105 = (off >> 5) & 0x3F;
            uint32_t imm41 = (off >> 1) & 0xF;
            uint32_t imm11 = (off >> 11) & 0x1;
            expanded = (imm12 << 31) | (imm105 << 25) | (0 << 20) | (rs1 << 15) |
                       (1 << 12) | (imm41 << 8) | (imm11 << 7) | 0x63;
            break;
        }
        }
        break;
    }
    case 0x2: { // Quadrant 2
        switch (funct3) {
        case 0: { // C.SLLI -> slli rd, rd, shamt
            uint8_t rd = (cinst >> 7) & 0x1F;
            uint8_t shamt = ((cinst >> 2) & 0x1F) | (((cinst >> 12) & 0x1) << 5);
            expanded = (shamt << 20) | (rd << 15) | (1 << 12) | (rd << 7) | 0x13;
            break;
        }
        case 1: { // C.FLDSP -> fld rd, offset(x2)
            uint8_t rd = (cinst >> 7) & 0x1F;
            uint32_t off = ((cinst >> 2) & 0x7) << 6 |
                           ((cinst >> 12) & 0x1) << 5 |
                           ((cinst >> 5) & 0x3) << 3;
            expanded = (off << 20) | (2 << 15) | (3 << 12) | (rd << 7) | 0x07;
            break;
        }
        case 2: { // C.LWSP -> lw rd, offset(x2)
            uint8_t rd = (cinst >> 7) & 0x1F;
            uint32_t off = ((cinst >> 2) & 0x3) << 6 |
                           ((cinst >> 12) & 0x1) << 5 |
                           ((cinst >> 4) & 0x7) << 2;
            if (!rd) return 0;
            expanded = (off << 20) | (2 << 15) | (2 << 12) | (rd << 7) | 0x03;
            break;
        }
        case 3: { // C.LDSP -> ld rd, offset(x2)
            uint8_t rd = (cinst >> 7) & 0x1F;
            uint32_t off = ((cinst >> 2) & 0x7) << 6 |
                           ((cinst >> 12) & 0x1) << 5 |
                           ((cinst >> 5) & 0x3) << 3;
            if (!rd) return 0;
            expanded = (off << 20) | (2 << 15) | (3 << 12) | (rd << 7) | 0x03;
            break;
        }
        case 4: { // C.MV / C.ADD / C.JR / C.JALR / C.EBREAK
            uint8_t rs2 = (cinst >> 2) & 0x1F;
            uint8_t rd = (cinst >> 7) & 0x1F;
            uint8_t bit12 = (cinst >> 12) & 0x1;
            if (bit12 == 0) {
                if (rs2 == 0) {
                    if (!rd) return 0;
                    expanded = (rd << 15) | 0x67; // C.JR -> jalr x0, rs1, 0
                } else {
                    // C.MV -> add rd, x0, rs2
                    expanded = (rs2 << 20) | (0 << 15) | (0 << 12) | (rd << 7) | 0x33;
                }
            } else {
                if (rs2 == 0 && rd == 0) {
                    // C.EBREAK
                    expanded = 0x00100073;
                } else if (rs2 == 0) {
                    // C.JALR -> jalr x1, rs1, 0
                    expanded = (rd << 15) | (0 << 12) | (1 << 7) | 0x67;
                } else {
                    // C.ADD -> add rd, rd, rs2
                    expanded = (rs2 << 20) | (rd << 15) | (0 << 12) | (rd << 7) | 0x33;
                }
            }
            break;
        }
        case 5: { // C.FSDSP -> fsd rs2, offset(x2)
            uint8_t rs2 = (cinst >> 2) & 0x1F;
            uint32_t off = ((cinst >> 7) & 0x7) << 6 |
                           ((cinst >> 10) & 0x7) << 3;
            expanded = (((off >> 5) & 0x7F) << 25) | (rs2 << 20) | (2 << 15) |
                       (3 << 12) | ((off & 0x1F) << 7) | 0x27;
            break;
        }
        case 6: { // C.SWSP -> sw rs2, offset(x2)
            uint8_t rs2 = (cinst >> 2) & 0x1F;
            uint32_t off = ((cinst >> 7) & 0x3) << 6 |
                           ((cinst >> 9) & 0xF) << 2;
            uint32_t imm115 = (off >> 5) & 0x7F;
            uint32_t imm40  = off & 0x1F;
            expanded = (imm115 << 25) | (rs2 << 20) | (2 << 15) | (2 << 12) | (imm40 << 7) | 0x23;
            break;
        }
        case 7: { // C.SDSP -> sd rs2, offset(x2)
            uint8_t rs2 = (cinst >> 2) & 0x1F;
            uint32_t off = ((cinst >> 7) & 0x7) << 6 |
                           ((cinst >> 10) & 0x7) << 3;
            uint32_t imm115 = (off >> 5) & 0x7F;
            uint32_t imm40  = off & 0x1F;
            expanded = (imm115 << 25) | (rs2 << 20) | (2 << 15) | (3 << 12) | (imm40 << 7) | 0x23;
            break;
        }
        }
        break;
    }
    }

    return expanded;
}

}  // namespace chisa::rocket_model
