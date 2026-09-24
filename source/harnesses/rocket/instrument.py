#!/usr/bin/env python3
"""Expose only the Rocket state needed by the scalar benchmark harness.

The input remains the Verilog emitted directly from the locked FIRRTL.  This
adds observation metadata, not logic.  A global --public-flat-rw prevents
Verilator from optimizing every internal signal and substantially distorts
the control measurement, so the paper path exposes only SimAXIMem, integer
RF, PC, DPC, and the ten signals needed to drive SimDTM from the same explicit
DMI host as CHISA.  Exact replacement counts make source drift fail closed.
"""

from __future__ import annotations

import argparse
from pathlib import Path


ATTRIBUTE = "/* verilator public_flat_rw */"


def replace_once(text: str, old: str, new: str, subject: str) -> str:
    count = text.count(old)
    if count != 1:
        raise ValueError(f"{subject}: expected one declaration, found {count}")
    return text.replace(old, new, 1)


def run() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--simdtm-input", type=Path)
    parser.add_argument("--simdtm-output", type=Path)
    args = parser.parse_args()
    if (args.simdtm_input is None) != (args.simdtm_output is None):
        raise ValueError("--simdtm-input and --simdtm-output must be paired")
    text = args.input.read_text(encoding="utf-8")

    text = replace_once(
        text,
        "  reg [39:0] reg_dpc;",
        f"  reg [39:0] reg_dpc {ATTRIBUTE};",
        "Rocket CSR DPC",
    )
    text = replace_once(
        text,
        "  reg [63:0] rf [0:30];",
        f"  reg [63:0] rf [0:30] {ATTRIBUTE};",
        "Rocket integer RF",
    )
    text = replace_once(
        text,
        "  reg [39:0] wb_reg_pc;",
        f"  reg [39:0] wb_reg_pc {ATTRIBUTE};",
        "Rocket writeback PC",
    )
    for bank in range(8):
        declaration = f"  reg [7:0] mem_{bank} [0:33554431];"
        text = replace_once(
            text,
            declaration,
            f"  reg [7:0] mem_{bank} [0:33554431] {ATTRIBUTE};",
            f"SimAXIMem bank {bank}",
        )
    for declaration, subject in (
        ("  wire  SimDTM_debug_req_ready;", "SimDTM request-ready feedback"),
        ("  wire  SimDTM_debug_resp_valid;", "SimDTM response-valid feedback"),
        ("  wire [31:0] SimDTM_debug_resp_bits_data;", "SimDTM response data"),
        ("  wire [1:0] SimDTM_debug_resp_bits_resp;", "SimDTM response status"),
    ):
        text = replace_once(
            text, declaration, f"{declaration[:-1]} {ATTRIBUTE};", subject)

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(text, encoding="utf-8")

    if args.simdtm_input is not None:
        simdtm = args.simdtm_input.read_text(encoding="utf-8")
        for declaration, subject in (
            ("  reg        debug_req_valid_reg;", "SimDTM request valid"),
            ("  reg [ 6:0] debug_req_bits_addr_reg;", "SimDTM request address"),
            ("  reg [ 1:0] debug_req_bits_op_reg;", "SimDTM request operation"),
            ("  reg [31:0] debug_req_bits_data_reg;", "SimDTM request data"),
            ("  reg        debug_resp_ready_reg;", "SimDTM response ready"),
            ("  reg [31:0] exit_reg;", "SimDTM exit"),
        ):
            simdtm = replace_once(
                simdtm, declaration, f"{declaration[:-1]} {ATTRIBUTE};", subject)
        args.simdtm_output.parent.mkdir(parents=True, exist_ok=True)
        args.simdtm_output.write_text(simdtm, encoding="utf-8")
    print(
        "ROCKET_VERILATOR_PUBLIC_INSTRUMENT_OK "
        "signals=21 scope=memory8/rf/wbpc/dpc/dmi10 global_public=false"
    )
    return 0


def main() -> int:
    try:
        return run()
    except (OSError, ValueError) as error:
        print(f"ERROR: {error}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
