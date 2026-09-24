#!/usr/bin/env python3
"""Prepare explicit Small BOOM oracle additions from the residual SCC audit.

This selects an experiment, not a qualified provider contract. Existing streams
remain forced/anchored; every added field must subsequently get a model source.
"""

import argparse
import hashlib
import json
from pathlib import Path
import re


TILE = "ldut.tile_prci_domain.tile_reset_domain.boom_tile."
ISSUE = re.compile(
    re.escape(TILE) + r"core\.(?:int_issue_unit|mem_issue_unit|fp_pipeline\.fp_issue_unit)"
    r"\.slots_[0-7]\.slot_uop__v2_bank_0_0$")
FRONT = re.compile(
    re.escape(TILE) + r"frontend\.(?:f3\.ram__v2_bank_0_[01]|"
    r"f3_bpd_resp\.ram__v2_bank_0_[012]|f4\.ram__v2_bank_0_[56]|"
    r"f3_bpd_resp\.ram_meta_0|f4\.ram_bpd_meta_0|"
    r"bpd\.banked_predictors_0\.components_0\.s1_update__bits_meta)$")
ROB = TILE + "core.rob.__v2_bitset_rob_val_bank_0"


def identity(path):
    return {"path": str(path.resolve()), "sha256": hashlib.sha256(path.read_bytes()).hexdigest()}


def prepare(base, output, groups):
    manifest_path = base / "oracle_manifest.json"
    serial_path = base / "serial_region_audit.json"
    banks_path = base / "register_bank_manifest.json"
    manifest = json.loads(manifest_path.read_text())
    serial = json.loads(serial_path.read_text())
    banks = {bank["name"]: bank for bank in json.loads(banks_path.read_text())["banks"]}
    original = {row["flat"] for row in manifest["oracles"] if row["kind"] == "reg"}
    additions = {}
    for region in serial["regions"]:
        for member in region["members"]:
            if member["role"] != "register-source":
                continue
            name = member["flat"]
            group = ("issue" if ISSUE.fullmatch(name) else
                     "frontend" if FRONT.fullmatch(name) else
                     "rob" if name == ROB else None)
            if group not in groups or name in original:
                continue
            bank = banks.get(name)
            width = bank["width"] if bank else 120  # three explicit frontend metadata registers
            if group == "issue":
                expected = 64 if ".mem_issue_unit." in name else 62 if ".fp_issue_unit." in name else 61
                if width != expected:
                    raise ValueError(f"not the locked Small issue-bank geometry: {name} ({width})")
            additions[name] = {
                "flat": name, "group": group, "width": width,
                "wordStreams": (width + 63) // 64,
                "region": region["id"], "regionTemplates": region["templateCount"],
                "fields": bank["fields"] if bank else [],
                "providerStatus": "requires binding and validation; not qualified by this selector",
            }
    if not additions:
        raise ValueError("no matching residual Small BOOM cut points")
    output.mkdir(parents=True, exist_ok=False)
    anchor = sorted(original | additions.keys())
    (output / "base-registers.txt").write_text("".join(name + "\n" for name in sorted(original)))
    (output / "candidate-registers.txt").write_text("".join(name + "\n" for name in anchor))
    (output / "serial-prefixes.txt").write_text(",".join(sorted(additions)) + "\n")
    report = {
        "scope": "Small BOOM consumer cut experiment; no provider qualification",
        "inputs": [identity(p) for p in (manifest_path, serial_path, banks_path)],
        "width": serial["width"], "baseStreams": len(manifest["oracles"]),
        "baseRegisterStreams": len(original), "baseSerialTemplates": serial["templateCount"],
        "groups": sorted(groups), "requestedRegisters": len(additions),
        "requestedWordStreams": sum(row["wordStreams"] for row in additions.values()),
        "additions": [additions[name] for name in sorted(additions)],
        "candidateSettings": {"V2_WIDE_ORACLE": "1", "V2_ORACLE_SERIAL_PARTIAL": "1"},
        "note": "Re-emission decides the actual set and savings. Do not equate requested cuts or template counts with speedup.",
    }
    (output / "cuts.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--groups", default="issue,frontend")
    args = parser.parse_args()
    groups = set(args.groups.split(","))
    if not groups <= {"issue", "frontend", "rob"}:
        parser.error("groups must be drawn from issue,frontend,rob")
    report = prepare(args.base, args.output, groups)
    print(f"Prepared {report['requestedRegisters']} register cuts / "
          f"{report['requestedWordStreams']} possible word streams; provider validation pending")


if __name__ == "__main__":
    main()
