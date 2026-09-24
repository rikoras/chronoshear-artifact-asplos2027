#!/usr/bin/env python3
"""Bind an external-DRAM consumer to the unchanged BOOM model record.

The base manifest describes the existing writer. By default the candidate
preserves every base signal. A subset requires an exact removed-key declaration;
the model record and functional state are unchanged. The forty SRAM access
streams remain mandatory. This generates placement, not values or qualifications.
"""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path


ARRAYS = {f"mem.srams.mem_{bank}" for bank in range(8)}
FIELDS = (
    ("rdata_MPORT", "ReadData", 8, "access-trace-induction"),
    ("rdata_MPORT__access_address", "ReadAddress", 25, "direct-micro-lockstep"),
    ("__access_write_0_MPORT_enable", "WriteEnable", 1, "direct-micro-lockstep"),
    ("__access_write_0_MPORT_address", "WriteAddress", 25, "direct-micro-lockstep"),
    ("__access_write_0_MPORT_data", "WriteData", 8, "direct-micro-lockstep"),
)


def streams(manifest):
    entries = manifest.get("oracles")
    if not isinstance(entries, list) or not entries:
        raise ValueError("oracle manifest has no streams")
    # Wide registers produce multiple word streams with the same RTL name.
    # traceKey, including its word suffix, is the writer's unique identity.
    by_name = {entry["traceKey"]: entry for entry in entries}
    if len(by_name) != len(entries):
        raise ValueError("duplicate oracle trace key")
    return by_name


def geometry(manifest, width):
    if manifest.get("version") != 2 or manifest.get("layout") != "window-major-v4m":
        raise ValueError("expected the mirrored window-major-v4m ABI")
    if "width" in manifest and int(manifest["width"]) != width:
        raise ValueError("manifest width does not match the requested width")
    size = int(manifest.get("blockBytes", 0))
    if size <= 0:
        raise ValueError("invalid oracle block size")
    spans = []
    for name, entry in streams(manifest).items():
        bits, elem = int(entry["width"]), int(entry["elemBytes"])
        offset = int(entry["blockOffset"])
        if not 1 <= bits <= 64 or elem not in (1, 2, 4, 8) or bits > 8 * elem:
            raise ValueError(f"invalid scalar shape: {name}")
        end = offset + 2 * width * elem
        if offset < 0 or offset % elem or end > size:
            raise ValueError(f"out-of-bounds or unaligned oracle: {name}")
        spans.append((offset, end, name))
    spans.sort()
    for previous, current in zip(spans, spans[1:]):
        if current[0] < previous[1]:
            raise ValueError(f"overlapping oracles: {previous[2]}, {current[2]}")
    occupied = 0
    for start, end, name in spans:
        if start != occupied:
            raise ValueError(f"unexpected gap before oracle: {name}")
        occupied = end
    # EmitV2.computeV4Layout packs every stream densely, then rounds only
    # the block tail to 64 bytes. Narrow W4 windows can have a nonzero tail.
    # Internal model-writer layouts may omit that unused tail altogether.
    if size not in (occupied, (occupied + 63) & ~63):
        raise ValueError("block size is not dense coverage plus 64-byte tail alignment")
    return size


def validate(base, candidate, state, width, extra_registers=(), removed_base=()):
    if width not in (4, 8, 16, 32):
        raise ValueError("supported widths are 4, 8, 16, 32")
    geometry(base, width)
    geometry(candidate, width)
    before, after = streams(base), streams(candidate)
    missing = set(before) - set(after)
    if any(not isinstance(name, str) or not name for name in removed_base):
        raise ValueError("removed-base keys must be nonempty strings")
    declared_removed = set(removed_base)
    if len(declared_removed) != len(removed_base):
        raise ValueError("duplicate removed-base oracle declaration")
    if missing and not declared_removed:
        raise ValueError("externalization removed a base oracle")
    if declared_removed != missing:
        raise ValueError("removed-base declaration must exactly match consumer omissions")
    def proof(entry):
        # Earlier v2 manifests recorded only verified=true, when all checked
        # streams used direct Micro-Lockstep.  Access-proof consumers write
        # the explicit verification field and are validated separately below.
        return entry.get("verification", "direct-micro-lockstep"
                         if entry.get("verified") is True else None)
    old_flats = Counter(row["flat"] for row in before.values())
    new_flats = Counter(row["flat"] for row in after.values())
    for name, old in before.items():
        if name in declared_removed:
            continue
        new = after[name]
        # Legacy scalar rows omitted both word fields. Accept the explicit
        # singleton spelling only when both manifests uniquely identify the
        # whole RTL value; split words and partial metadata remain exact.
        legacy_scalar = (
            "word" not in old and "words" not in old
            and type(new.get("word")) is int and type(new.get("words")) is int
            and new.get("word") == 0 and new.get("words") == 1
            and type(old["width"]) is int and 1 <= old["width"] <= 64
            and old_flats[old["flat"]] == new_flats[old["flat"]] == 1)
        fields = ("flat", "kind", "width", "elemBytes", "verified")
        if not legacy_scalar:
            fields += ("word", "words")
        for field in fields:
            if old.get(field) != after[name].get(field):
                raise ValueError(f"base oracle changed: {name}: {field}")
        if proof(old) != proof(after[name]):
            raise ValueError(f"base oracle changed: {name}: verification")
    expected = {
        f"mem.srams.mem_{bank}.{suffix}": (bank, kind, bits, proof)
        for bank in range(8) for suffix, kind, bits, proof in FIELDS
    }
    extra_keys = set(after) - set(before)
    declared = {row["traceKey"]: row for row in extra_registers}
    if len(declared) != len(extra_registers) or not set(declared) <= extra_keys:
        raise ValueError("extra register declaration duplicates or replaces an existing stream")
    for key, declaration in declared.items():
        actual = after[key]
        if (actual.get("kind"), actual.get("verified"), actual.get("verification")) != (
                "reg", True, "direct-micro-lockstep"):
            raise ValueError(f"extra source must be a register oracle: {key}")
        for field in ("flat", "kind", "width", "elemBytes", "word", "words", "verified", "verification"):
            if declaration.get(field) != actual.get(field):
                raise ValueError(f"extra register declaration changed: {key}: {field}")
    access_keys = extra_keys - set(declared)
    extra_by_flat = {after[key]["flat"]: key for key in access_keys}
    if set(extra_by_flat) != set(expected) or len(access_keys) != len(expected):
        raise ValueError("candidate must add exactly the forty DRAM access streams")
    for name, (_, _, bits, proof) in expected.items():
        entry = after[extra_by_flat[name]]
        if (entry.get("kind"), entry.get("width"), entry.get("verified"),
                entry.get("verification")) != ("comb", bits, True, proof):
            raise ValueError(f"invalid access proof: {name}")
    arrays = state.get("arrays", [])
    external = {a["source"]: a for a in arrays if a.get("fullyExternal")}
    if set(external) != ARRAYS or sum(bool(a.get("fullyExternal")) for a in arrays) != 8:
        raise ValueError("external arrays must be exactly the eight main-memory banks")
    for name, array in external.items():
        if (array.get("depth"), array.get("packedWidth"), array.get("readPorts"),
                array.get("writePorts"), array.get("storageMaterialized"),
                array.get("verification")) != (
                    33554432, 8, 1, 1, False, "read-data-oracle+ordered-access-trace"):
            raise ValueError(f"memory geometry or storage changed: {name}")
        read = [{"dataOracle": name + ".rdata_MPORT",
                 "addressOracle": name + ".rdata_MPORT__access_address"}]
        write = [{"port": "MPORT",
                  "enableOracle": name + ".__access_write_0_MPORT_enable",
                  "addressOracle": name + ".__access_write_0_MPORT_address",
                  "dataOracle": name + ".__access_write_0_MPORT_data"}]
        if array.get("readAccess") != read or array.get("writeAccess") != write:
            raise ValueError(f"memory access metadata changed: {name}")
    return before, after, {key: expected[name] for name, key in extra_by_flat.items()}


def generate(base, candidate, state, width, extra_registers=(), removed_base=()):
    before, after, accesses = validate(base, candidate, state, width, extra_registers, removed_base)
    lines = [
        "// Generated by generate_dram_access_profile.py; placement only.",
        "#pragma once", "#include <cstddef>", "#include <cstdint>",
        "namespace chisa::boom_system::dram_profile {",
        f"inline constexpr unsigned kWidth = {width};",
        f"inline constexpr std::size_t kBaseBlockBytes = {base['blockBytes']};",
        f"inline constexpr std::size_t kBlockBytes = {candidate['blockBytes']};",
        f"inline constexpr std::size_t kAdditionalRegisterStreams = {len(extra_registers)};",
        "enum class Field { ReadData, ReadAddress, WriteEnable, WriteAddress, WriteData };",
        "struct BaseStream { const char* trace_key; const char* flat; std::uint32_t source, destination; unsigned width, bytes; };",
        "inline constexpr BaseStream kBaseStreams[] = {",
    ]
    if removed_base:
        # Only subset profiles change the legacy generated header spelling.
        lines.insert(4, f"#define CHISA_DRAM_PROFILE_CONSUMER_STREAM_COUNT {len(after)}")
    for name, old in sorted(before.items()):
        new = after.get(name)
        destination = new["blockOffset"] if new is not None else 0xffffffff
        lines.append(f"  {{{json.dumps(name)}, {json.dumps(old['flat'])}, {old['blockOffset']}u, "
                     f"{destination}u, {old['width']}u, {old['elemBytes']}u}},")
    lines += ["};",
              "struct AccessStream { Field field; unsigned bank, bytes; std::uint32_t offset; };",
              "inline constexpr AccessStream kAccessStreams[] = {"]
    for name, (bank, kind, _, _) in sorted(accesses.items()):
        entry = after[name]
        lines.append(f"  {{Field::{kind}, {bank}u, {entry['elemBytes']}u, {entry['blockOffset']}u}},")
    lines += ["};", "}  // namespace chisa::boom_system::dram_profile", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", type=Path, required=True)
    parser.add_argument("--candidate", type=Path, required=True)
    parser.add_argument("--state", type=Path, required=True)
    parser.add_argument("--width", type=int, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--extra-registers", type=Path,
                        help="explicit additional register stream declarations; requires a separate model provider")
    parser.add_argument("--removed-base-oracles", type=Path,
                        help="exact consumer-deleted base traceKeys; does not remove model state")
    args = parser.parse_args()
    paths = (args.base, args.candidate, args.state)
    data = [p.read_bytes() for p in paths]
    extra_payload = args.extra_registers.read_bytes() if args.extra_registers else None
    extra_registers = json.loads(extra_payload)["oracles"] if extra_payload else ()
    removed_payload = args.removed_base_oracles.read_bytes() if args.removed_base_oracles else None
    removed_base = json.loads(removed_payload)["traceKeys"] if removed_payload else ()
    header = generate(*(json.loads(payload) for payload in data), args.width, extra_registers, removed_base)
    provenance = "".join(f"// {label} sha256={hashlib.sha256(payload).hexdigest()}\n"
                         for label, payload in zip(("base", "candidate", "state"), data))
    if extra_payload:
        provenance += f"// extra-registers sha256={hashlib.sha256(extra_payload).hexdigest()}\n"
    if removed_payload:
        provenance += f"// removed-base-oracles sha256={hashlib.sha256(removed_payload).hexdigest()}\n"
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(provenance + header)
    print(f"DRAM_ACCESS_PROFILE_OK width={args.width} arrays=8 accesses=40 output={args.output}")


if __name__ == "__main__":
    main()
