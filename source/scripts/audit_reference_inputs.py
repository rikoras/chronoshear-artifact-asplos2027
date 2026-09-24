#!/usr/bin/env python3
"""Reject RTL implementations in compiled reference-model dependency closures.

Run on reference translation units, not on a joint executable's DUT objects.
Observation layouts, bindings and immutable firmware remain legitimate inputs.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
RETIRED = {"rtl_decode_slice.inc", "rtl_decode_slice_fp.inc", "rocket_decode_fix.h",
           "hardfloat.h", "decode_logic.h", "hardfloat_scalar_reference.h"}
MARKERS = {
    "retired RTL decoder minimizer": re.compile(r"\bdecode_logic\s*::\s*(?:Term|term_of|simplify_dc|eval)\b"),
    "generated RTL evaluator": re.compile(r"\b(?:void\s+)?EVAL_\d+\s*\("),
    "generated RTL oracle load": re.compile(r"^\s*#\s*define\s+ESSENT_ORACLE_LOAD\b", re.M),
    "generated instance execution": re.compile(r"\bgenerated_\s*\.\s*(?:eval|eval_with_cache)\s*\("),
    "Verilator execution dependency": re.compile(r"#\s*include\s*[<\"](?:[^>\"]*/)?(?:verilated(?:_[^>\"]*)?\.h|VTestHarness[^>\"]*\.h)[>\"]"),
}


def audit_paths(paths) -> dict:
    files, failures = {}, []
    for value in sorted(set(map(str, paths))):
        path = Path(value).resolve()
        if not path.is_file():
            failures.append({"path": str(path), "reason": "missing reference dependency"})
            continue
        data = path.read_bytes()
        files[str(path)] = hashlib.sha256(data).hexdigest()
        reason = None
        if "/test_support/rtl/" in path.as_posix():
            reason = "external RTL test adapter in reference closure"
        elif path.suffix.lower() in {".v", ".sv", ".fir"}:
            reason = "RTL source in reference closure"
        elif path.name in RETIRED:
            reason = "retired RTL-derived reference implementation"
        if reason:
            failures.append({"path": str(path), "reason": reason})
        if path.suffix in {".h", ".hpp", ".cpp", ".cc", ".inc"}:
            text = data.decode("utf-8", errors="replace")
            for label, pattern in MARKERS.items():
                found = pattern.search(text)
                if found:
                    failures.append({"path": str(path), "reason": label,
                                     "line": text.count("\n", 0, found.start()) + 1})
    report = {"schema": 1, "scope": "compiled reference translation-unit inputs; DUT/test objects excluded",
              "files": files, "failures": failures, "status": "pass" if not failures else "fail"}
    return report


def enforce_reference_inputs(paths) -> dict:
    report = audit_paths(paths)
    if report["failures"]:
        details = "; ".join(row["path"] + ": " + row["reason"] for row in report["failures"])
        raise ValueError("native-reference dependency gate rejected: " + details)
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--receipt", type=Path, help="build receipt with per-object dependency identities")
    parser.add_argument("--path", type=Path, action="append", default=[])
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    paths = list(args.path)
    units = []
    if args.receipt:
        receipt = json.loads(args.receipt.read_text())
        for obj, row in receipt.get("object_receipts", {}).items():
            source = Path(row["identity"]["source"])
            if not source.resolve().is_relative_to(ROOT / "guiders"):
                continue
            units.append({"source": str(source), "object": obj, "object_sha256": row["object_sha256"]})
            paths.extend(row["inputs"])
    if not paths:
        parser.error("no reference-model inputs selected")
    report = audit_paths(paths)
    report["translation_units"] = units
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({"status": report["status"], "files": len(report["files"]), "reference_units": len(units), "failures": report["failures"]}))
    return 0 if report["status"] == "pass" else 1


if __name__ == "__main__":
    raise SystemExit(main())
