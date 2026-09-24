#!/usr/bin/env python3
"""Write the ordered register-oracle names used to anchor wider emits."""

from __future__ import annotations

import argparse
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--expect-regs", type=int, default=92,
                        help="expected register-stream count (92 for the "
                             "all-registers release contract; 0 = any)")
    args = parser.parse_args()
    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    entries = manifest.get("oracles") or manifest.get("streams")
    names = [entry["flat"] for entry in entries if entry["kind"] == "reg"]
    if (args.expect_regs and len(names) != args.expect_regs) or \
            len(names) != len(set(names)):
        raise SystemExit(
            f"ERROR: expected {args.expect_regs} unique Sodor register streams, got {len(names)}"
        )
    args.output.write_text("".join(f"{name}\n" for name in names),
                           encoding="utf-8")
    print(f"Wrote {len(names)} register names -> {args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
