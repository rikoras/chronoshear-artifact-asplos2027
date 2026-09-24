#!/usr/bin/env python3
"""Generate the qualified SystemGuider slice of a W=4 oracle-block writer."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path
from typing import Any


STREAM_FIELDS = (
    "flat", "traceKey", "array", "width", "elemBytes", "blockOffset", "kind"
)


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def load_object(path: Path) -> dict[str, Any]:
    value = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(value, dict):
        raise ValueError(f"{path}: expected a JSON object")
    return value


def qualified_streams(
    manifest_path: Path, qualification_path: Path, width: int,
    layout_variant: bool = False,
) -> tuple[dict[str, Any], dict[str, Any], list[dict[str, Any]]]:
    if width <= 0:
        raise ValueError("width must be positive")
    manifest = load_object(manifest_path)
    qualification = load_object(qualification_path)
    if manifest.get("layout") != "window-major-v4m":
        raise ValueError(f"unsupported manifest layout: {manifest.get('layout')!r}")
    entries = manifest.get("oracles")
    if not isinstance(entries, list):
        raise ValueError("manifest has no oracle list")
    by_key = {entry.get("traceKey"): (index, entry)
              for index, entry in enumerate(entries) if isinstance(entry, dict)}
    if len(by_key) != len(entries) or None in by_key:
        raise ValueError("manifest trace keys are missing or duplicated")

    source = qualification.get("sourceManifest", {})
    if layout_variant:
        # Width-variant layout: the qualification stays anchored on the W4
        # contract; this manifest only supplies the wider block layout. Every
        # qualified key must exist here (contracts are width-monotone), and
        # both hashes are recorded in the metadata.
        qualified_keys = {s["traceKey"] for s in qualification.get("streams", [])}
        missing = sorted(qualified_keys - set(by_key))
        if missing:
            raise ValueError(
                "layout manifest lacks qualified streams: " + ", ".join(missing[:4]))
        # The consumer injects every stream in its manifest.  A stream the
        # qualification does not name has no producer source and would be
        # injected as zero, so a wider layout must not carry extra streams.
        extra = sorted(set(by_key) - qualified_keys)
        if extra:
            raise ValueError(
                "layout manifest carries unqualified streams: " + ", ".join(extra[:4]))
    elif source.get("sha256") != sha256(manifest_path):
        raise ValueError("qualification does not name this manifest")
    if not layout_variant and source.get("oracleCount") != len(entries):
        raise ValueError("qualification oracle count does not match")
    if not layout_variant and source.get("blockBytes") != manifest.get("blockBytes"):
        raise ValueError("qualification block size does not match")
    gate = qualification.get("qualification", {})
    if qualification.get("status") != "lockstep-qualified":
        raise ValueError("model qualification is not lockstep-qualified")
    if not gate.get("strict") or gate.get("cycles", 0) < 50_000:
        raise ValueError("model qualification is not a 50k strict gate")
    if any(gate.get(field) != 0 for field in
           ("realMismatches", "sentinelFailures", "stepFailures")):
        raise ValueError("model qualification contains a failure")

    streams = qualification.get("streams")
    if not isinstance(streams, list) or not streams:
        raise ValueError("qualification has no modeled streams")
    if gate.get("modeledStreams") != len(streams):
        raise ValueError("qualification modeled-stream count does not match")

    seen: set[str] = set()
    block_bytes = manifest.get("blockBytes")
    if not isinstance(block_bytes, int) or block_bytes <= 0:
        raise ValueError("manifest has an invalid block size")
    selected: list[dict[str, Any]] = []
    for entry in streams:
        if not isinstance(entry, dict):
            raise ValueError("qualification stream is not an object")
        key = entry.get("traceKey")
        if not isinstance(key, str) or not key or key in seen:
            raise ValueError(f"invalid or duplicate qualification key: {key!r}")
        seen.add(key)
        found = by_key.get(key)
        if found is None:
            raise ValueError(f"qualified stream is absent from manifest: {key}")
        manifest_index, original = found
        # blockOffset/manifestIndex are layout facts and legitimately differ
        # in a width-variant layout; identity fields must always agree.
        layout_fields = {"blockOffset"} if layout_variant else set()
        for field in STREAM_FIELDS:
            if field in layout_fields:
                continue
            if entry.get(field) != original.get(field):
                raise ValueError(f"qualified stream {key} has {field} drift")
        if not layout_variant and entry.get("manifestIndex") != manifest_index:
            raise ValueError(f"qualified stream {key} has manifest-index drift")
        # `SystemGuider::step()` snapshots PRE register predictions before it
        # advances state and also records POST combinational predictions from
        # that same pre-edge state.  Both kinds therefore belong to one
        # chronological row and can be packed by the same writer.
        if entry.get("kind") not in ("reg", "comb"):
            raise ValueError(f"qualified stream {key} has an invalid tap kind")
        shape_source = original if layout_variant else entry
        elem_bytes = shape_source.get("elemBytes")
        bit_width = shape_source.get("width")
        offset = shape_source.get("blockOffset")
        if elem_bytes not in (1, 2, 4, 8) or not isinstance(bit_width, int):
            raise ValueError(f"qualified stream {key} has an invalid shape")
        if bit_width < 1 or bit_width > 64 or bit_width > 8 * elem_bytes:
            raise ValueError(f"qualified stream {key} width does not fit its element")
        end = offset + 2 * width * elem_bytes if isinstance(offset, int) else -1
        if not isinstance(offset, int) or offset < 0 or offset % elem_bytes or end > block_bytes:
            raise ValueError(f"qualified stream {key} has an invalid block slot")
        selected.append(dict(shape_source))
    return manifest, qualification, selected


def layout_hash(selected: list[dict[str, Any]]) -> int:
    """Identity of the per-cycle record layout (key, element size, width,
    kind of every lane in order); must equal the record generator's."""
    digest = hashlib.sha256()
    for entry in selected:
        digest.update(
            f"{entry['traceKey']} {entry['elemBytes']} {entry['width']} "
            f"{entry['kind']}\n".encode("utf-8"))
    return int.from_bytes(digest.digest()[:8], "big")


def render_header(
    manifest: dict[str, Any], selected: list[dict[str, Any]], width: int
) -> str:
    block_bytes = int(manifest["blockBytes"])
    lines = [
        "// AUTO-GENERATED by generate_system_oracle_writer.py. DO NOT EDIT.",
        "#pragma once",
        "#include <algorithm>",
        "#include <array>",
        "#include <cstddef>",
        "#include <cstdint>",
        "#include <cstring>",
        "#include <iterator>",
        "#include <vector>",
        "#include <stdexcept>",
        "#include <string>",
        "#include <utility>",
        "#include \"model_bindings.h\"",
        "#include \"system_guider.h\"",
        "#include \"generated/system_oracle_record.h\"",
        "",
        "namespace chisa::boom_system {",
        "// The writer's lane order and element shapes are the record's; a writer",
        "// regenerated against another contract cannot link with a stale record.",
        f"inline constexpr std::uint64_t kSystemOracleWriterLayoutHash = "
        f"0x{layout_hash(selected):016x}ull;",
        "static_assert(kSystemOracleWriterLayoutHash == kOracleRecordLayoutHash,",
        "              \"system_oracle_writer and system_oracle_record disagree\");",
        f"inline constexpr int kSystemOracleWidth = {width};",
        f"inline constexpr int kSystemOracleCyclesPerWindow = {2 * width};",
        f"inline constexpr std::size_t kSystemOracleBlockBytes = {block_bytes}u;",
        f"inline constexpr std::size_t kSystemOracleModeledStreams = {len(selected)}u;",
        "",
        "// Masks for every manifest width; a 520-byte table the write loops keep",
        "// in L1 instead of an 8-byte mask load per lane spec.",
        "inline constexpr std::array<std::uint64_t, 65> kWidthMask = [] {",
        "  std::array<std::uint64_t, 65> table{};",
        "  for (int w = 0; w < 64; ++w)",
        "    table[static_cast<std::size_t>(w)] = (std::uint64_t{1} << w) - 1u;",
        "  table[64] = ~std::uint64_t{0};",
        "  return table;",
        "}();",
        "",
        "struct SystemOracleStreamSpec {",
        "  const char* trace_key;",
        "  const char* flat;",
        "  std::uint32_t block_offset;",
        "  std::uint8_t width;",
        "  std::uint8_t elem_bytes;",
        "  OracleKind kind;",
        "};",
        "",
        "inline constexpr SystemOracleStreamSpec kSystemOracleStreams[] = {",
    ]
    for entry in selected:
        lines.append(
            "  {" + ", ".join((
                json.dumps(entry["traceKey"]), json.dumps(entry["flat"]),
                f"{entry['blockOffset']}u", f"{entry['width']}u",
                f"{entry['elemBytes']}u",
                "OracleKind::Register" if entry["kind"] == "reg"
                else "OracleKind::Combinational",
            )) + "},"
        )
    lines.extend([
        "};",
        "",
        "}  // namespace chisa::boom_system",
        "",
        "#include \"system_oracle_writer_logic.h\"",
        "",
    ])
    return "\n".join(lines)


def generate_files(
    manifest_path: Path, qualification_path: Path, output_path: Path,
    metadata_path: Path, width: int, layout_variant: bool = False
) -> int:
    manifest, qualification, selected = qualified_streams(
        manifest_path, qualification_path, width, layout_variant=layout_variant
    )
    output_path.parent.mkdir(parents=True, exist_ok=True)
    metadata_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(render_header(manifest, selected, width), encoding="utf-8")
    metadata_path.write_text(json.dumps({
        "schemaVersion": 1,
        "sourceManifest": {
            "path": str(manifest_path.resolve()),
            "sha256": sha256(manifest_path),
            "oracleCount": len(manifest["oracles"]),
            "blockBytes": manifest["blockBytes"],
        },
        "sourceQualification": {
            "path": str(qualification_path.resolve()),
            "sha256": sha256(qualification_path),
            "cycles": qualification["qualification"]["cycles"],
            "modeledStreams": len(selected),
        },
        "layout": {
            "name": manifest["layout"],
            "width": width,
            "cyclesPerWindow": 2 * width,
            "mirroredSecondHalf": True,
            "recordLayoutHash": f"0x{layout_hash(selected):016x}",
        },
        "streams": selected,
    }, indent=2) + "\n", encoding="utf-8")
    return len(selected)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", required=True, type=Path)
    parser.add_argument("--qualification", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--metadata", required=True, type=Path)
    parser.add_argument("--width", required=True, type=int)
    parser.add_argument("--layout-variant", action="store_true")
    args = parser.parse_args()
    try:
        count = generate_files(
            args.manifest, args.qualification, args.output, args.metadata,
            args.width, layout_variant=args.layout_variant
        )
    except (OSError, ValueError, KeyError, json.JSONDecodeError) as error:
        print(f"SYSTEM_ORACLE_WRITER_FAIL: {error}")
        return 1
    print(f"SYSTEM_ORACLE_WRITER_OK streams={count} W={args.width} "
          f"output={args.output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
