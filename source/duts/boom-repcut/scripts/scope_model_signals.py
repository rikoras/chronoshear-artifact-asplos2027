#!/usr/bin/env python3
"""Per-signal scoping report for the complete-Small system model.

`audit_model_coverage.py` answers "how many streams does each region owe?".
This answers the next question, the one you need before writing any struct:
*what state is each region actually made of?*

Every oracle stream is bucketed by owning subsystem, then by register family
(the leaf name with trailing indices folded), then annotated with a structural
guess at what kind of state it is.  The guess is a reading aid for scoping, not
a contract -- the contract is the RTL, and every family is printed with its
FIRRTL source line so it can be read there.

The kind taxonomy follows docs/GUIDER_PARADIGM.md section 1:

  handshake  valid/ready/CDC registers -- one-cycle images of combinational
             signals.  Cheap: model the producer, the register follows.
  queue      enqueue/dequeue pointers and maybe_full.  Cheap once the
             transaction flow above them is modeled; meaningless before that.
  counter    beat/burst counters.  Derived from a request's size and progress.
  fsm        explicit state registers.  Needs the real state machine.
  payload    data carried alongside a valid bit.  Often liftable into
             compiler-owned storage instead of being predicted at all.
  other      everything the patterns do not recognize; read the RTL.

Usage:
  scope_model_signals.py --manifest <oracle_manifest.json> [--fir <pristine.fir>]
                         [--subsystem lsu] [--json out.json]
"""

from __future__ import annotations

import argparse
import collections
import json
import re
import sys
from pathlib import Path

# Hierarchy prefix -> subsystem key. Longest prefix wins, so the tile's
# children are named before the tile itself.
SUBSYSTEM_PREFIXES = [
    ("ldut.tile_prci_domain.tile_reset_domain.boom_tile.core", "core"),
    ("ldut.tile_prci_domain.tile_reset_domain.boom_tile.frontend", "frontend"),
    ("ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu", "lsu"),
    ("ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache", "dcache"),
    ("ldut.tile_prci_domain.tile_reset_domain.boom_tile.ptw", "ptw"),
    ("ldut.tile_prci_domain", "tile-shell"),
    ("ldut.debug_1", "debug"),
    ("ldut.intsource", "interrupts"),
    ("ldut_reset_reg", "reset-shell"),
    ("ldut.plicDomainWrapper", "plic"),
    ("ldut.clintDomainWrapper", "clint"),
    ("ldut.subsystem_l2_wrapper", "coherence"),
    ("ldut.subsystem_mbus", "mbus"),
    ("ldut.subsystem_fbus", "fbus"),
    ("ldut.subsystem_sbus", "sbus"),
    ("ldut.subsystem_cbus", "cbus"),
    ("ldut.subsystem_pbus", "pbus"),
    ("mem", "axi-memory"),
    ("mmio_mem", "mmio-memory"),
]

# Ordered: the first pattern that matches the family name wins.
KIND_PATTERNS = [
    ("handshake", re.compile(
        r"(valid_reg|ready_reg|cdc_reg|_sync|synced|widx|ridx|sink|source)$|"
        r"^(REG(_\d+)?)$")),
    ("queue", re.compile(r"(enq_ptr|deq_ptr|maybe_full|_ptr_value|full|empty)$")),
    ("counter", re.compile(r"(count|counter|beats|cnt|num_\w+)$")),
    ("fsm", re.compile(r"(state|_state|phase|mode|ctrlStateReg)$")),
    ("payload", re.compile(
        r"(addr|data|opcode|param|size|source|sink|mask|tag|way|pc|inst|uop|"
        r"bits|idx|entries)")),
]


def subsystem_of(flat: str) -> str:
    for prefix, key in SUBSYSTEM_PREFIXES:
        if flat == prefix or flat.startswith(prefix + "."):
            return key
    return "unclassified"


def family_of(flat: str, subsystem: str) -> tuple[str, str]:
    """Split a flat name into (module path within the subsystem, register family).

    Trailing numeric suffixes are folded so `count_1 .. count_128` collapse to a
    single family; a bare `_N` marker records that the family is replicated.
    """
    prefix = next((p for p, k in SUBSYSTEM_PREFIXES if k == subsystem
                   and (flat == p or flat.startswith(p + "."))), "")
    rest = flat[len(prefix):].lstrip(".") if prefix else flat
    parts = rest.split(".")
    leaf = parts[-1] if parts else rest
    module = ".".join(parts[:-1])
    folded = re.sub(r"_\d+$", "_N", leaf)
    # Chisel dedup suffixes (`Foo_12`, `Foo$$inst`) inside the module path too.
    module = re.sub(r"_\d+(?=\.|$)", "_N", module)
    module = module.replace("$$inst", "")
    return module, folded


def kind_of(family: str) -> str:
    for kind, pattern in KIND_PATTERNS:
        if pattern.search(family):
            return kind
    return "other"


def load_fir_lines(fir: Path | None) -> dict[str, str]:
    """Map a register's bare name to the `@[File.scala line:col]` it came from.

    The pristine FIRRTL keeps source locators on every `reg`, which is the only
    honest way to point a model author at the semantics. Ambiguous names (the
    same bare name declared in several modules) map to the empty string rather
    than to a guess.
    """
    if not fir or not fir.exists():
        return {}
    locator = re.compile(r"^\s*reg\s+([A-Za-z_][\w$]*)\s*:.*?(@\[[^\]]+\])\s*$")
    found: dict[str, set[str]] = collections.defaultdict(set)
    with fir.open(errors="replace") as handle:
        for line in handle:
            match = locator.match(line)
            if match:
                found[match.group(1)].add(match.group(2))
    return {name: (next(iter(where)) if len(where) == 1 else "")
            for name, where in found.items()}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--manifest", required=True, type=Path)
    parser.add_argument("--fir", type=Path,
                        help="pristine aggregate FIRRTL, for source locators")
    parser.add_argument("--subsystem", help="print families for this subsystem only")
    parser.add_argument("--min-streams", type=int, default=1,
                        help="hide families below this stream count")
    parser.add_argument("--json", type=Path, help="also write the full report here")
    args = parser.parse_args()

    manifest = json.loads(args.manifest.read_text())
    oracles = manifest.get("oracles")
    if not oracles:
        print(f"ERROR: {args.manifest} has no oracles", file=sys.stderr)
        return 2

    locators = load_fir_lines(args.fir)

    records = []
    for entry in oracles:
        flat = entry["flat"]
        subsystem = subsystem_of(flat)
        module, family = family_of(flat, subsystem)
        bare = flat.split(".")[-1]
        records.append({
            "flat": flat,
            "subsystem": subsystem,
            "module": module,
            "family": family,
            "kind": kind_of(family),
            "width": entry.get("width"),
            "bytes": entry.get("elemBytes"),
            "at": locators.get(bare, ""),
        })

    by_subsystem: dict[str, list[dict]] = collections.defaultdict(list)
    for record in records:
        by_subsystem[record["subsystem"]].append(record)

    total_bytes = sum(r["bytes"] or 0 for r in records)
    print(f"{len(records)} streams, {total_bytes} B/cycle, "
          f"{len(by_subsystem)} subsystems\n")

    header = f"{'subsystem':<14}{'streams':>9}{'B/cycle':>9}   kinds"
    print(header)
    print("-" * len(header))
    for name, group in sorted(by_subsystem.items(),
                              key=lambda kv: -len(kv[1])):
        kinds = collections.Counter(r["kind"] for r in group)
        spread = " ".join(f"{k}:{v}" for k, v in kinds.most_common())
        print(f"{name:<14}{len(group):>9}"
              f"{sum(r['bytes'] or 0 for r in group):>9}   {spread}")

    if args.subsystem:
        group = by_subsystem.get(args.subsystem)
        if group is None:
            print(f"\nno such subsystem: {args.subsystem}", file=sys.stderr)
            return 2
        print(f"\n=== {args.subsystem}: register families ===")
        families: dict[tuple[str, str], list[dict]] = collections.defaultdict(list)
        for record in group:
            families[(record["module"], record["family"])].append(record)
        rows = sorted(families.items(), key=lambda kv: (-len(kv[1]), kv[0]))
        print(f"{'n':>5}  {'kind':<10}{'bits':>6}  family / module")
        for (module, family), members in rows:
            if len(members) < args.min_streams:
                continue
            widths = {m["width"] for m in members}
            width = str(next(iter(widths))) if len(widths) == 1 else "mixed"
            at = next((m["at"] for m in members if m["at"]), "")
            where = f"  {at}" if at else ""
            print(f"{len(members):>5}  {members[0]['kind']:<10}{width:>6}  "
                  f"{family}   [{module or '-'}]{where}")

    if args.json:
        args.json.write_text(json.dumps({
            "manifest": str(args.manifest),
            "streamCount": len(records),
            "bytesPerCycle": total_bytes,
            "records": records,
        }, indent=2))
        print(f"\nwrote {args.json}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
