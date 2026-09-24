#pragma once
#include <cstdint>
#include "micro_op.h"
namespace chisa::boom_model {
std::uint64_t decode_imm(const MicroOp& u);
std::uint64_t alu_op(std::uint8_t fn, std::uint8_t dw, std::uint64_t a, std::uint64_t b);
std::uint64_t mul_op(std::uint8_t fn, std::uint64_t a, std::uint64_t b, bool word);
std::uint64_t div_op(std::uint8_t fn, std::uint64_t a, std::uint64_t b, bool word);
std::uint8_t branch_pc_sel(std::uint8_t kind, std::uint64_t a, std::uint64_t b);
std::uint8_t div_latency(std::uint8_t fn, std::uint8_t dw, std::uint64_t a, std::uint64_t b);
std::uint64_t compute_int_result(const MicroOp& u, std::uint64_t a, std::uint64_t b);
}
