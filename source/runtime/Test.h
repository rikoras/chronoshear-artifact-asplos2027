#ifndef TEST_H_
#define TEST_H_

#include <array>
#include <cassert>
#include <cstdint>
#include <cinttypes>
#include <cstdlib>
#include "sint.h"
#include "oracle_data.h"
#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)
#define ESSENT_ORACLE_LOAD(name, idx) (((const uint64_t*)__builtin_assume_aligned((name), 64))[(idx)])
#define ESSENT_NOINLINE __attribute__((noinline))
template <int W>
static inline uint64_t essent_to_u64(const UInt<W>& v) {
  if constexpr (W <= 64) return v.as_single_word();
  else return v.template bits<63,0>().as_single_word();
}
template <int W>
static inline uint64_t essent_to_u64(const SInt<W>& v) {
  if constexpr (W <= 64) return (uint64_t)v.as_single_word();
  else return v.template bits<63,0>().as_single_word();
}

typedef struct pipeline {
  alignas(64) UInt<8> stage1[4];
  alignas(64) UInt<8> stage2[4];
  alignas(64) UInt<8> stage3[4];
  alignas(64) UInt<8> io_in[4];
  alignas(64) UInt<8> io_bias[4];
  alignas(64) UInt<8> io_out[4];

  pipeline() {
    for (int _i=0; _i<4; _i++) stage1[_i].rand_init();
    for (int _i=0; _i<4; _i++) stage2[_i].rand_init();
    for (int _i=0; _i<4; _i++) stage3[_i].rand_init();
  }
} pipeline;

typedef struct Test {
  UInt<1> clock;
  UInt<1> reset;
  alignas(64) UInt<8> io_in[4];
  alignas(64) UInt<8> io_bias[4];
  alignas(64) UInt<8> io_out[4];
  pipeline p;

  Test() {
    reset.rand_init();
    for (int _i=0; _i<4; _i++) io_in[_i].rand_init();
    for (int _i=0; _i<4; _i++) io_bias[_i].rand_init();
    for (int _i=0; _i<4; _i++) io_out[_i].rand_init();
  }

  int oracle_cycle = 0;

  void eval_forward(bool update_registers, bool verbose, bool done_reset) {
    { // Forward pass
      UInt<8> _s_p$stage1$oracle[4];
      UInt<8> _s_p$stage3$next[4];
      UInt<8> _s_p$io_out[4];
      UInt<8> _s_p$io_bias[4];
      UInt<8> _s_p$io_in[4];
      UInt<8> _s_p$stage2$next[4];
      UInt<8> io_out[4];
      UInt<9> _s_p$_stage1_T[4];
      UInt<8> _s_p$_stage1_T_1[4];
      UInt<9> _s_p$_stage1_T_2[4];
      UInt<8> _s_p$stage1$next[4];
      
// ---- ATOM [PARALLEL] parallel_p.stage1_lane_STAR$oracle (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage1$oracle[L] = UInt<8>(done_reset ? ESSENT_ORACLE_LOAD(trace_micro_stage1, (oracle_cycle + L)) : (uint64_t)essent_to_u64(p.stage1[L]));
      }
      
// ---- ATOM [PARALLEL] parallel_p.stage3_lane_STAR$next (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage3$next[L] = p.stage2[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.io_STAR_out (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$io_out[L] = p.stage3[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.io_STAR_bias (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$io_bias[L] = io_bias[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.io_STAR_in (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$io_in[L] = io_in[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.stage2_lane_STAR$next (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage2$next[L] = _s_p$stage1$oracle[L];
      }
      
// ---- ATOM [COMMIT] commit_p.stage3_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        p.stage3[L] = _s_p$stage3$next[L];
      }
      
// ---- ATOM [PARALLEL] parallel_io_STAR_out (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        io_out[L] = _s_p$io_out[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p._stage1_T_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$_stage1_T[L] = p.stage3[L] + _s_p$io_in[L];
      }
      
// ---- ATOM [COMMIT] commit_p.stage2_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        p.stage2[L] = _s_p$stage2$next[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p._stage1_T_1_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$_stage1_T_1[L] = _s_p$_stage1_T[L].tail<1>();
      }
      
// ---- ATOM [PARALLEL] parallel_p._stage1_T_2_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$_stage1_T_2[L] = _s_p$_stage1_T_1[L] + _s_p$io_bias[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.stage1_lane_STAR$next (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage1$next[L] = _s_p$_stage1_T_2[L].tail<1>();
      }
      
// ---- ATOM [ORACLE] oracle_p.stage1_lane_STAR (4 stmts) ----
      if (done_reset) {
      for (int L = 0; L < 4; L++) {
        p.stage1[L] = _s_p$stage1$next[L];
      }
      } else {
      for (int L = 0; L < 4; L++) {
        p.stage1[L] = _s_p$stage1$next[L];
      }
      }
      
// ---- ATOM [SCALAR] scalar_58 (1 stmts) ----
      if (verbose && update_registers && done_reset && !(p.stage1[0] == _s_p$stage1$oracle[1])) fprintf(stderr, "VERIFY FAIL [FWD]: p.stage1_lane_0 got=0x%lx expect=0x%lx cyc=%d\n", (uint64_t)essent_to_u64(p.stage1[0]), (uint64_t)essent_to_u64(_s_p$stage1$oracle[1]), oracle_cycle);
    }
  }

  void eval_reverse(bool update_registers, bool verbose, bool done_reset) {
    { // Reverse pass
      UInt<8> _s_p$stage1$oracle[4];
      UInt<8> _s_p$stage3$next[4];
      UInt<8> _s_p$io_out[4];
      UInt<8> _s_p$io_bias[4];
      UInt<8> _s_p$io_in[4];
      UInt<8> _s_p$stage2$next[4];
      UInt<8> io_out[4];
      UInt<9> _s_p$_stage1_T[4];
      UInt<8> _s_p$_stage1_T_1[4];
      UInt<9> _s_p$_stage1_T_2[4];
      UInt<8> _s_p$stage1$next[4];
      
// ---- ATOM [PARALLEL] parallel_p.stage1_lane_STAR$oracle (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage1$oracle[L] = UInt<8>(done_reset ? ESSENT_ORACLE_LOAD(trace_micro_stage1, (oracle_cycle + 7 - L)) : (uint64_t)essent_to_u64(p.stage1[L]));
      }
      
// ---- ATOM [PARALLEL] parallel_p.stage3_lane_STAR$next (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage3$next[L] = p.stage2[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.io_STAR_out (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$io_out[L] = p.stage3[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.io_STAR_bias (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$io_bias[L] = io_bias[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.io_STAR_in (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$io_in[L] = io_in[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.stage2_lane_STAR$next (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage2$next[L] = _s_p$stage1$oracle[L];
      }
      
// ---- ATOM [COMMIT] commit_p.stage3_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        p.stage3[L] = _s_p$stage3$next[L];
      }
      
// ---- ATOM [PARALLEL] parallel_io_STAR_out (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        io_out[L] = _s_p$io_out[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p._stage1_T_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$_stage1_T[L] = p.stage3[L] + _s_p$io_in[L];
      }
      
// ---- ATOM [COMMIT] commit_p.stage2_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        p.stage2[L] = _s_p$stage2$next[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p._stage1_T_1_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$_stage1_T_1[L] = _s_p$_stage1_T[L].tail<1>();
      }
      
// ---- ATOM [PARALLEL] parallel_p._stage1_T_2_lane_STAR (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$_stage1_T_2[L] = _s_p$_stage1_T_1[L] + _s_p$io_bias[L];
      }
      
// ---- ATOM [PARALLEL] parallel_p.stage1_lane_STAR$next (4 stmts) ----
      for (int L = 0; L < 4; L++) {
        _s_p$stage1$next[L] = _s_p$_stage1_T_2[L].tail<1>();
      }
      
// ---- ATOM [ORACLE] oracle_p.stage1_lane_STAR (4 stmts) ----
      if (done_reset) {
      for (int L = 0; L < 4; L++) {
        p.stage1[L] = _s_p$stage1$next[L];
      }
      } else {
      for (int L = 0; L < 4; L++) {
        p.stage1[L] = _s_p$stage1$next[L];
      }
      }
      
// ---- ATOM [SCALAR] scalar_61 (1 stmts) ----
      if (verbose && update_registers && done_reset && !(p.stage1[3] == _s_p$stage1$oracle[2])) fprintf(stderr, "VERIFY FAIL [REV]: p.stage1_lane_3 got=0x%lx expect=0x%lx cyc=%d\n", (uint64_t)essent_to_u64(p.stage1[3]), (uint64_t)essent_to_u64(_s_p$stage1$oracle[2]), oracle_cycle);
    }
    if (update_registers && done_reset) oracle_cycle += 8;
  }

  void eval(bool update_registers, bool verbose, bool done_reset) {
    eval_forward(update_registers, verbose, done_reset);
    eval_reverse(update_registers, verbose, done_reset);
  }


} Test;

int main() {
  Test t;
  for(int i=0; i<20000000; i++) {
    t.eval(true, false, true);
  }
  return 0;
}
#endif  // TEST_H_
