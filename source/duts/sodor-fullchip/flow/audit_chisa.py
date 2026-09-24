#!/usr/bin/env python3
"""Fail-closed audit of one locked Sodor full-chip CHISA build."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
import re
import sys


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def fail(message: str) -> None:
    raise ValueError(message)


def run() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--lock", type=Path, required=True)
    parser.add_argument("--compiler-jar", type=Path, required=True)
    parser.add_argument("--firrtl", type=Path)
    parser.add_argument("--dir", type=Path, required=True)
    parser.add_argument("--width", type=int, required=True)
    args = parser.parse_args()

    lock = json.loads(args.lock.read_text(encoding="utf-8"))
    firrtl = args.firrtl or args.lock.parent / "generated/SodorFullChip.fir"
    if not firrtl.is_file() or firrtl.stat().st_size == 0:
        fail(f"missing locked FIRRTL: {firrtl}")
    if digest(firrtl) != lock["sourceFirrtlSha256"]:
        fail("source FIRRTL hash differs from CHISA_LOCK.json")
    if not args.compiler_jar.is_file() or args.compiler_jar.stat().st_size == 0:
        fail(f"missing compiler jar: {args.compiler_jar}")
    if digest(args.compiler_jar) != lock["compilerJarSha256"]:
        fail("compiler jar hash differs from CHISA_LOCK.json")
    width_lock = lock["widths"].get(str(args.width))
    if width_lock is None:
        fail(f"width {args.width} is not locked")

    manifest_path = args.dir / "oracle_manifest.json"
    header_path = args.dir / "SodorFullChip.h"
    state_path = args.dir / "state_array_manifest.json"
    serial_path = args.dir / "serial_region_audit.json"
    dead_path = args.dir / "dead_state_manifest.json"
    bank_path = args.dir / "register_bank_manifest.json"
    ext_path = args.dir / "extmodule_manifest.json"
    clock_path = args.dir / "clock_domain_manifest.json"
    log_path = args.dir / "v2_simd_emit.log"
    for path in (manifest_path, header_path, state_path, serial_path,
                 dead_path, bank_path, ext_path, clock_path, log_path):
        if not path.is_file() or path.stat().st_size == 0:
            fail(f"missing generated artifact: {path}")

    if digest(manifest_path) != width_lock["oracleManifestSha256"]:
        fail("oracle manifest hash differs from CHISA_LOCK.json")
    if digest(header_path) != width_lock["headerSha256"]:
        fail("generated header hash differs from CHISA_LOCK.json")

    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    entries = manifest.get("oracles") or manifest.get("streams")
    contract = lock["contract"]
    actual_streams = [[entry["kind"], entry["flat"]] for entry in entries]
    if actual_streams != contract["streams"]:
        fail("ordered oracle stream contract changed")
    if manifest.get("layout") != "window-major-v4m":
        fail(f"unexpected oracle layout: {manifest.get('layout')}")
    if manifest.get("blockBytes") != width_lock["blockBytes"]:
        fail("oracle block size changed")
    if len(entries) != contract["streamCount"]:
        fail("oracle stream count changed")
    if sum(entry["kind"] == "reg" for entry in entries) != \
            contract["registerStreams"]:
        fail("register oracle count changed")
    if sum(entry["kind"] == "comb" for entry in entries) != \
            contract["combinationStreams"]:
        fail("combination oracle count changed")
    if sum(bool(entry.get("verified")) for entry in entries) != \
            contract["verifiedStreams"]:
        fail("an oracle is no longer Micro-Lockstep verified")
    if any(entry.get("word") != 0 or entry.get("words") != 1
           for entry in entries):
        fail("Sodor contract unexpectedly contains a wide split stream")

    state = json.loads(state_path.read_text(encoding="utf-8"))
    actual_arrays = []
    for array in state.get("arrays", []):
        actual_arrays.append({key: array[key] for key in (
            "source", "depth", "packedWidth", "readPorts", "writePorts",
            "fullyExternal", "storageMaterialized", "verification")})
    if actual_arrays != contract["stateArrays"]:
        fail(f"chronological array contract changed: {actual_arrays}")
    memory = next(
        (array for array in state.get("arrays", [])
         if array.get("source") == "memory.bytes"), None)
    if memory is None or not memory.get("fullyExternal") or \
            memory.get("storageMaterialized"):
        fail("2 MiB memory.bytes storage was rematerialized in the consumer")
    if len(memory.get("readAccess", [])) != 16 or \
            len(memory.get("writeAccess", [])) != 8:
        fail("memory access-trace port inventory changed")
    if any(set(port) != {"dataOracle", "addressOracle"}
           for port in memory["readAccess"]):
        fail("a memory read port lost its data/address oracle pair")
    if any(set(port) != {"port", "enableOracle", "addressOracle", "dataOracle"}
           for port in memory["writeAccess"]):
        fail("a memory write port lost its ordered access oracle tuple")
    if state.get("packedRegisters"):
        fail("unexpected register bank in Sodor full-chip build")

    serial = json.loads(serial_path.read_text(encoding="utf-8"))
    if serial.get("regionCount") != width_lock["serialRegions"]:
        fail("serial-region count changed")
    if serial.get("templateCount") != width_lock["serialRegions"]:
        fail("serial-template count changed")

    dead = json.loads(dead_path.read_text(encoding="utf-8"))
    if dead.get("removedCount") != 0 or dead.get("sourceRegisterCount") != 93:
        fail("dead-state inventory changed")
    banks = json.loads(bank_path.read_text(encoding="utf-8"))
    if banks.get("banks") not in ([], None):
        fail("register-bank inventory changed")
    ext = json.loads(ext_path.read_text(encoding="utf-8"))
    if ext.get("instances") not in ([], None):
        fail("Sodor full-chip unexpectedly gained an ExtModule instance")
    clock = json.loads(clock_path.read_text(encoding="utf-8"))
    if clock.get("gatedRegisters") not in ([], None) or \
            clock.get("gatedMemoryWrites") not in ([], None):
        fail("Sodor full-chip unexpectedly gained a derived clock")

    log = log_path.read_text(encoding="utf-8", errors="replace")
    match = re.search(
        r"templates=2541 regs=93 oracles=92 serialTemplates=0 "
        r"schedUnits=(\d+)", log)
    if not match or int(match.group(1)) != width_lock["scheduleUnits"]:
        fail("schedule census changed")
    if ("extern arrays: 1 array(s), 16 read-data stream(s), "
            "40 verified access stream(s)") not in log:
        fail("fully external array census changed")
    if "extern read ports: 3 read stream(s) externalized" not in log:
        fail("extern-read census changed")

    print(
        f"PASS Sodor full-chip CHISA W={args.width}: "
        f"streams={len(entries)} (reg=92 comb=59) "
        f"memory=external/access-verified rf=local serial=0 "
        f"block={manifest['blockBytes']}"
    )
    return 0


def main() -> int:
    try:
        return run()
    except (OSError, KeyError, TypeError, ValueError, json.JSONDecodeError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
