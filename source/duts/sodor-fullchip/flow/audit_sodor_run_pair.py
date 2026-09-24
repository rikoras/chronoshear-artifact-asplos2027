#!/usr/bin/env python3
"""Verify that Sodor CHISA and Verilator executed the same workload state."""

from __future__ import annotations

import argparse
from pathlib import Path


def fields(line: str) -> dict[str, str]:
    result: dict[str, str] = {}
    for token in line.split():
        if "=" in token:
            key, value = token.split("=", 1)
            result[key] = value
    return result


def unique(path: Path, predicate) -> tuple[str, dict[str, str]]:
    matches = [line for line in path.read_text(encoding="utf-8").splitlines()
               if predicate(line)]
    if len(matches) != 1:
        raise ValueError(f"{path}: expected one run record, found {len(matches)}")
    return matches[0], fields(matches[0])


def run() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--chisa", type=Path, required=True)
    parser.add_argument("--verilator", type=Path, required=True)
    args = parser.parse_args()
    chisa_line, chisa = unique(
        args.chisa, lambda line: line.endswith("FULLCHIP_SIDECAR")
    )
    _, verilator = unique(
        args.verilator,
        lambda line: line.startswith("SODOR_FULLCHIP_VERILATOR "),
    )
    if "(PASS)" not in chisa_line or verilator.get("status") != "pass":
        raise ValueError("one side did not pass")
    for key in ("oracle_mismatches", "output_mismatches", "rf_mismatches",
                "final_mismatches", "sentinel_failures"):
        if int(chisa.get(key, "-1"), 0) != 0:
            raise ValueError(f"CHISA {key} is nonzero")
    pairs = (
        ("pass", "cycles"),
        ("tohost", "tohost"),
        ("memory_hash", "memory_hash"),
    )
    mismatches = []
    for left, right in pairs:
        if left not in chisa or right not in verilator or \
                int(chisa[left], 0) != int(verilator[right], 0):
            mismatches.append(f"{left}={chisa.get(left)}/{verilator.get(right)}")
    if mismatches:
        raise ValueError("CHISA/Verilator run contract differs: " +
                         ", ".join(mismatches))
    print(
        "PASS Sodor CHISA/Verilator run pair: "
        f"cycles={chisa['pass']} memory={chisa['memory_hash']}"
    )
    return 0


def main() -> int:
    try:
        return run()
    except (OSError, TypeError, ValueError) as error:
        print(f"ERROR: {error}")
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
