#!/usr/bin/env python3
"""Stream a Rocket JSONL trace into manifest-driven CHISA v2 oracle arrays."""

from __future__ import annotations

import argparse
from array import array as elem_array
import json
import os
import re
import shutil
import struct
import sys
import tempfile
from pathlib import Path


# These arrays are owned by the Rocket harness rather than oracle selection.
# Keep the names stable: generated harnesses refer to them directly.
EXT_FIELDS = (
    ("trace_ext_imem_resp_valid", "imem_resp_valid"),
    ("trace_ext_imem_resp_bits_pc", "imem_resp_bits_pc"),
    ("trace_ext_imem_resp_bits_data", "imem_resp_bits_data"),
    ("trace_ext_imem_resp_bits_mask", "imem_resp_bits_mask"),
    ("trace_ext_imem_npc", "imem_npc"),
    ("trace_ext_dmem_s2_paddr", "dmem_s2_paddr"),
    ("trace_ext_dmem_resp_valid", "dmem_resp_valid"),
    ("trace_ext_dmem_resp_bits_addr", "dmem_resp_bits_addr"),
    ("trace_ext_dmem_resp_bits_tag", "dmem_resp_bits_tag"),
    ("trace_ext_dmem_resp_bits_cmd", "dmem_resp_bits_cmd"),
    ("trace_ext_dmem_resp_bits_size", "dmem_resp_bits_size"),
    ("trace_ext_dmem_resp_bits_signed", "dmem_resp_bits_signed"),
    ("trace_ext_dmem_resp_bits_dprv", "dmem_resp_bits_dprv"),
    ("trace_ext_dmem_resp_bits_mask", "dmem_resp_bits_mask"),
    ("trace_ext_dmem_resp_bits_data", "dmem_resp_bits_data"),
    ("trace_ext_dmem_resp_bits_data_word_bypass", "dmem_resp_bits_data_word_bypass"),
    ("trace_ext_dmem_resp_bits_data_raw", "dmem_resp_bits_data_raw"),
    ("trace_ext_dmem_resp_bits_replay", "dmem_resp_bits_replay"),
    ("trace_ext_dmem_resp_bits_has_data", "dmem_resp_bits_has_data"),
    ("trace_ext_rf_rs1_addr", "rf_rs1_addr"),
    ("trace_ext_rf_rs2_addr", "rf_rs2_addr"),
    ("trace_ext_rf_rs1_data", "rf_rs1_data"),
    ("trace_ext_rf_rs2_data", "rf_rs2_data"),
)

OUT_FIELDS = (
    ("trace_out_imem_req_valid", "imem_req_valid"),
    ("trace_out_imem_req_bits_pc", "imem_req_bits_pc"),
    ("trace_out_imem_resp_ready", "imem_resp_ready"),
    ("trace_out_dmem_req_valid", "dmem_req_valid"),
    ("trace_out_dmem_req_bits_tag", "dmem_req_bits_tag"),
    ("trace_out_dmem_req_bits_cmd", "dmem_req_bits_cmd"),
    ("trace_out_dmem_req_bits_addr", "dmem_req_bits_addr"),
    ("trace_out_dmem_req_bits_data", "dmem_req_bits_data"),
    ("trace_out_dmem_req_bits_mask", "dmem_req_bits_mask"),
    ("trace_out_dmem_req_bits_size", "dmem_req_bits_size"),
    ("trace_out_dmem_req_bits_signed", "dmem_req_bits_signed"),
    ("trace_out_dmem_req_bits_dprv", "dmem_req_bits_dprv"),
    ("trace_out_rf_wen", "rf_wen"),
    ("trace_out_rf_waddr", "rf_waddr"),
    ("trace_out_rf_wdata", "rf_wdata"),
)

IDENTIFIER_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")

# Oracle data format v4 (window-major): injected streams are stored as one
# contiguous block per 2W-cycle super-window (each stream's 2W values at its
# manifest blockOffset, keeping the v3 width-honest elemBytes tiers), so a
# window's injection reads ONE sequential block instead of touching one
# scattered cache line per stream, and the kernel addresses streams as
# `oracle_win_base + constant` with no per-stream pointer loads.
# ext/out harness arrays stay stream-major u64 after the kernel section: the
# generated harness reads them once per cycle through a (uint64_t) cast.
ELEM_CTYPE = {1: "uint8_t", 2: "uint16_t", 4: "uint32_t", 8: "uint64_t"}
ARRAY_TYPECODE = {1: "B", 2: "H", 4: "I", 8: "Q"}
ELEM_STRUCT = {1: "<B", 2: "<H", 4: "<I", 8: "<Q"}
ORACLE_FORMAT_VERSION = 4


def align64(n: int) -> int:
    """64-byte-align a byte offset (ext/out region bases)."""
    return (n + 63) & ~63


def elem_bytes_for_width(width: int) -> int:
    if width <= 8:
        return 1
    if width <= 16:
        return 2
    if width <= 32:
        return 4
    return 8


def parse_value(value: object) -> int:
    if isinstance(value, str):
        return int(value, 0)
    if isinstance(value, (int, bool)):
        return int(value)
    raise ValueError(f"oracle value is not an integer: {value!r}")


def load_manifest(path: Path) -> tuple[list[tuple[str, str, int]], dict[str, int], int, bool]:
    with path.open(encoding="utf-8") as stream:
        data = json.load(stream)
    if not isinstance(data, dict) or data.get("version") != 2:
        raise ValueError(f"{path}: expected oracle manifest version 2")
    # v4m: rev half of each stream slot pre-mirrored (kernel rev pass reads
    # element W+L). Unknown tags die here — see gen_oracle_data_boom.py.
    layout = data.get("layout")
    if layout not in ("window-major-v4", "window-major-v4m"):
        raise ValueError(f"{path}: unknown kernel layout {layout!r} (stale compiler emit?)")
    mirrored = layout == "window-major-v4m"
    block_bytes = data.get("blockBytes")
    if not isinstance(block_bytes, int) or block_bytes < 0 or block_bytes % 64:
        raise ValueError(f"{path}: invalid blockBytes {block_bytes!r}")
    raw_entries = data.get("oracles")
    if not isinstance(raw_entries, list):
        raise ValueError(f"{path}: 'oracles' must be an array")

    triples: list[tuple[str, str, int]] = []
    block_offs: dict[str, int] = {}
    arrays: set[str] = set()
    keys: set[str] = set()
    for index, entry in enumerate(raw_entries):
        if not isinstance(entry, dict):
            raise ValueError(f"{path}: oracles[{index}] must be an object")
        array = entry.get("array")
        trace_key = entry.get("traceKey")
        if not isinstance(array, str) or not IDENTIFIER_RE.fullmatch(array):
            raise ValueError(f"{path}: invalid oracles[{index}].array: {array!r}")
        if not isinstance(trace_key, str) or not trace_key:
            raise ValueError(f"{path}: invalid oracles[{index}].traceKey: {trace_key!r}")
        if array in arrays:
            raise ValueError(f"{path}: duplicate oracle array {array!r}")
        if trace_key in keys:
            raise ValueError(f"{path}: duplicate oracle traceKey {trace_key!r}")
        # elemBytes is the storage tier chosen by the compiler (single source
        # of truth; the compiler forces u64 for SInt streams because the trace
        # serializes them sign-extended). The width fallback below exists only
        # for pre-elemBytes manifests and cannot know signedness — an SInt
        # stream under such a manifest fails the tier range check loudly at
        # pack time; regenerate the manifest with the current compiler.
        elem = entry.get("elemBytes")
        if elem is None:
            width = entry.get("width")
            if not isinstance(width, int) or width <= 0:
                raise ValueError(
                    f"{path}: oracles[{index}] has neither elemBytes nor a valid width"
                )
            elem = elem_bytes_for_width(width)
        if elem not in ELEM_CTYPE:
            raise ValueError(f"{path}: invalid oracles[{index}].elemBytes: {elem!r}")
        boff = entry.get("blockOffset")
        if not isinstance(boff, int) or boff < 0 or boff % elem:
            raise ValueError(f"{path}: invalid oracles[{index}].blockOffset: {boff!r}")
        arrays.add(array)
        keys.add(trace_key)
        triples.append((array, trace_key, elem))
        block_offs[array] = boff
    return triples, block_offs, block_bytes, mirrored


def validate_header(
    top_h: Path,
    manifest_pairs: list[tuple[str, str, int]],
    width: int,
    block_offs: dict[str, int],
    block_bytes: int,
    mirrored: bool,
) -> int:
    text = top_h.read_text(encoding="utf-8")
    # v4: every kernel stream access is emitted as
    # `(const uintN_t*)(oracle_win_base + <off>L) /* trace_x */` — require the
    # (stream, offset) pairs to agree exactly with the manifest layout, plus
    # the baked block size constant.
    header_pairs = {
        name: int(off)
        for off, name in re.findall(
            r"oracle_win_base \+ (\d+)L\) /\* (trace_[A-Za-z0-9_]+) \*/", text
        )
    }
    if header_pairs != block_offs:
        problems = []
        missing = sorted(set(header_pairs) - set(block_offs))
        extra = sorted(set(block_offs) - set(header_pairs))
        moved = sorted(
            n for n in set(header_pairs) & set(block_offs)
            if header_pairs[n] != block_offs[n]
        )
        if missing:
            problems.append("missing from manifest: " + ", ".join(missing[:12]))
        if extra:
            problems.append("not loaded by Top.h: " + ", ".join(extra[:12]))
        if moved:
            problems.append("blockOffset disagrees: " + ", ".join(moved[:12]))
        raise ValueError("Top.h/manifest oracle mismatch (" + "; ".join(problems) + ")")
    m = re.search(r"ORACLE_BLOCK_BYTES = (\d+)LL;", text)
    if not m or int(m.group(1)) != block_bytes:
        raise ValueError(
            f"Top.h ORACLE_BLOCK_BYTES {m.group(1) if m else 'missing'} "
            f"!= manifest blockBytes {block_bytes}"
        )
    mm = re.search(r"ORACLE_KERNEL_MIRRORED = (\d);", text)
    header_mirrored = bool(int(mm.group(1))) if mm else False
    if header_mirrored != mirrored:
        raise ValueError(
            f"Top.h ORACLE_KERNEL_MIRRORED={int(header_mirrored)} disagrees "
            f"with manifest layout {'v4m' if mirrored else 'v4'} — stale emit?"
        )

    port_widths = {
        int(match)
        for match in re.findall(
            r"(?m)^\s*(?:alignas\(\d+\)\s+)?(?:UInt|SInt)<\d+>\s+"
            r"io_[A-Za-z0-9_]+\[(\d+)\]\s*;",
            text,
        )
    }
    if not port_widths:
        raise ValueError(f"{top_h}: no v2 array ports found")
    if len(port_widths) != 1:
        raise ValueError(f"{top_h}: inconsistent v2 array widths: {sorted(port_widths)}")
    detected = next(iter(port_widths))
    if width and detected != width:
        raise ValueError(f"{top_h}: width is {detected}, but --width={width}")
    return detected


def region_offsets(array_len: int, metadata: list[tuple[str, str, str, int]]) -> tuple[list[int], int]:
    """Byte offset of each stream region (after the 64 B file header) and the
    total payload size. Every region is padded to a 64 B multiple so every
    stream base satisfies the __builtin_assume_aligned(64) load contract."""
    offsets: list[int] = []
    off = 0
    for _, _, _, elem in metadata:
        offsets.append(off)
        off += align64(array_len * elem)
    return offsets, off


def write_header(
    path: Path,
    num_cycles: int,
    array_len: int,
    metadata: list[tuple[str, str, str, int]],
    block_bytes: int,
    cpw: int,
    mirrored: bool,
) -> None:
    extout = [m for m in metadata if m[1] != "micro"]
    num_blocks = array_len // cpw
    kernel_size = num_blocks * block_bytes
    offsets, payload = region_offsets(array_len, extout)
    with path.open("w", encoding="utf-8") as out:
        out.write("#pragma once\n")
        out.write("// Oracle data format v4: window-major kernel section (one block per\n")
        out.write("// 2W-cycle super-window, streams at their manifest blockOffset), then\n")
        out.write("// stream-major ext/out harness traces. The kernel addresses streams\n")
        out.write("// as oracle_win_base + constant; only ext/out keep named pointers.\n")
        out.write("#include <cstddef>\n")
        out.write("#include <cstdint>\n")
        out.write("#include <cstdio>\n")
        out.write("#include <sys/mman.h>\n")
        out.write("#include <sys/stat.h>\n")
        out.write("#include <fcntl.h>\n")
        out.write("#include <unistd.h>\n\n")
        out.write(f"constexpr int ORACLE_NUM_CYCLES = {num_cycles};\n")
        out.write(f"constexpr int ORACLE_ARRAY_LEN = {array_len};\n")
        out.write(f"constexpr int ORACLE_NUM_ARRAYS = {len(metadata)};\n")
        out.write(f"constexpr uint32_t ORACLE_FORMAT_VERSION = {ORACLE_FORMAT_VERSION};\n")
        out.write(f"constexpr int64_t ORACLE_DATA_BLOCK_BYTES = {block_bytes}LL;\n")
        out.write(f"constexpr int64_t ORACLE_DATA_NUM_BLOCKS = {num_blocks}LL;\n")
        out.write(f"constexpr int ORACLE_DATA_MIRRORED = {1 if mirrored else 0};\n")
        out.write(f"constexpr size_t ORACLE_PAYLOAD_BYTES = {kernel_size + payload}ULL;\n\n")
        out.write("inline const char* oracle_kernel_base = nullptr;\n")
        for array, _, _, elem in extout:
            out.write(f"inline const {ELEM_CTYPE[elem]}* {array} = nullptr;\n")
        out.write("\ninline int _oracle_fd = -1;\n")
        out.write("inline void* _oracle_map = nullptr;\n")
        out.write("inline size_t _oracle_map_size = 0;\n\n")
        out.write("inline void oracle_unload() {\n")
        out.write("    if (_oracle_map && _oracle_map != MAP_FAILED) ")
        out.write("munmap(_oracle_map, _oracle_map_size);\n")
        out.write("    if (_oracle_fd >= 0) close(_oracle_fd);\n")
        out.write("    _oracle_map = nullptr;\n")
        out.write("    _oracle_map_size = 0;\n")
        out.write("    _oracle_fd = -1;\n")
        out.write("    oracle_kernel_base = nullptr;\n")
        for array, _, _, _ in extout:
            out.write(f"    {array} = nullptr;\n")
        out.write("}\n\n")
        out.write("inline bool oracle_load(const char* bin_path) {\n")
        out.write("    oracle_unload();\n")
        out.write("    _oracle_fd = open(bin_path, O_RDONLY);\n")
        out.write("    if (_oracle_fd < 0) { perror(bin_path); return false; }\n")
        out.write("    struct stat st;\n")
        out.write("    if (fstat(_oracle_fd, &st) != 0) { perror(\"fstat\"); ")
        out.write("oracle_unload(); return false; }\n")
        out.write("    _oracle_map_size = static_cast<size_t>(st.st_size);\n")
        out.write("    const size_t expected = 64ULL + ORACLE_PAYLOAD_BYTES;\n")
        out.write("    if (_oracle_map_size != expected) {\n")
        out.write("        fprintf(stderr, \"oracle size mismatch: got %zu expected %zu ")
        out.write("(stale oracle_data.bin? repack with gen_oracle_data_rocket.py)\\n\", ")
        out.write("_oracle_map_size, expected);\n")
        out.write("        oracle_unload(); return false;\n")
        out.write("    }\n")
        out.write("    uint32_t header[6] = {0, 0, 0, 0, 0, 0};\n")
        out.write("    if (pread(_oracle_fd, header, sizeof(header), 0) != ")
        out.write("static_cast<ssize_t>(sizeof(header))) {\n")
        out.write("        perror(\"pread oracle header\"); oracle_unload(); return false;\n")
        out.write("    }\n")
        out.write("    if (header[0] != ORACLE_NUM_CYCLES || ")
        out.write("header[1] != ORACLE_ARRAY_LEN || header[2] != ORACLE_NUM_ARRAYS || ")
        out.write("header[3] != ORACLE_FORMAT_VERSION || ")
        out.write("header[4] != (uint32_t)ORACLE_DATA_BLOCK_BYTES || ")
        out.write("header[5] != (uint32_t)ORACLE_DATA_NUM_BLOCKS) {\n")
        out.write("        fprintf(stderr, \"oracle header mismatch: cycles=%u len=%u arrays=%u fmt=%u\\n\", ")
        out.write("header[0], header[1], header[2], header[3]);\n")
        out.write("        oracle_unload(); return false;\n")
        out.write("    }\n")
        out.write("    _oracle_map = mmap(nullptr, _oracle_map_size, PROT_READ, ")
        out.write("MAP_PRIVATE, _oracle_fd, 0);\n")
        out.write("    if (_oracle_map == MAP_FAILED) { perror(\"mmap\"); ")
        out.write("_oracle_map = nullptr; oracle_unload(); return false; }\n")
        out.write("    // Window blocks are consumed strictly sequentially; huge pages\n")
        out.write("    // cut TLB pressure on the multi-GB map.\n")
        out.write("    madvise(_oracle_map, _oracle_map_size, MADV_SEQUENTIAL);\n")
        out.write("#ifdef MADV_HUGEPAGE\n")
        out.write("    madvise(_oracle_map, _oracle_map_size, MADV_HUGEPAGE);\n")
        out.write("#endif\n")
        out.write("    oracle_kernel_base = static_cast<const char*>(_oracle_map) + 64;\n")
        out.write(f"    const char* extout_base = static_cast<const char*>(_oracle_map) + 64 + {kernel_size}ULL;\n")
        for (array, _, _, elem), offset in zip(extout, offsets):
            out.write(f"    {array} = reinterpret_cast<const {ELEM_CTYPE[elem]}*>(extout_base + {offset}ULL);\n")
        out.write("    return true;\n")
        out.write("}\n")


def pack_trace(
    trace_path: Path,
    output_h: Path,
    width: int,
    manifest_pairs: list[tuple[str, str, int]],
    block_offs: dict[str, int],
    block_bytes: int,
    mirrored: bool,
) -> tuple[int, int, int]:
    # Injected streams carry their manifest elemBytes tier; ext/out harness
    # arrays stay u64 (see the comment on ELEM_CTYPE).
    metadata = (
        [(array, "micro", key, elem) for array, key, elem in manifest_pairs]
        + [(array, "ext", key, 8) for array, key in EXT_FIELDS]
        + [(array, "out", key, 8) for array, key in OUT_FIELDS]
    )
    array_names = [array for array, _, _, _ in metadata]
    if len(array_names) != len(set(array_names)):
        raise ValueError("manifest arrays collide with Rocket ext/out array names")

    output_h.parent.mkdir(parents=True, exist_ok=True)
    bin_path = output_h.with_suffix(".bin")
    num_cycles = 0
    zero_chunk = b"\x00" * (8192 * 8)

    with tempfile.TemporaryDirectory(
        prefix="rocket_oracle_", dir=output_h.parent
    ) as tmp_name:
        tmp_dir = Path(tmp_name)
        array_paths = [tmp_dir / f"array_{index:04d}.bin" for index in range(len(metadata))]
        writers = [path.open("wb") for path in array_paths]
        buffers = [bytearray() for _ in metadata]
        packers = [struct.Struct(ELEM_STRUCT[elem]).pack for _, _, _, elem in metadata]
        limits = [1 << (8 * elem) for _, _, _, elem in metadata]
        try:
            with trace_path.open(encoding="utf-8") as trace:
                for line_number, line in enumerate(trace, 1):
                    if not line.strip():
                        continue
                    try:
                        record = json.loads(line)
                    except json.JSONDecodeError as error:
                        raise ValueError(
                            f"{trace_path}:{line_number}: invalid JSON: {error}"
                        ) from error
                    if not isinstance(record, dict):
                        raise ValueError(f"{trace_path}:{line_number}: record is not an object")
                    if record.get("cycle") != num_cycles:
                        raise ValueError(
                            f"{trace_path}:{line_number}: expected cycle {num_cycles}, "
                            f"got {record.get('cycle')!r}"
                        )
                    sections = {}
                    for section_name in ("micro", "ext", "out"):
                        section = record.get(section_name)
                        if not isinstance(section, dict):
                            raise ValueError(
                                f"{trace_path}:{line_number}: missing object section "
                                f"{section_name!r}"
                            )
                        sections[section_name] = section
                    for buffer, pack_elem, limit, (array, section_name, key, _) in zip(
                        buffers, packers, limits, metadata
                    ):
                        section = sections[section_name]
                        if key not in section:
                            raise ValueError(
                                f"{trace_path}:{line_number}: missing required key "
                                f"{section_name}.{key} for {array}"
                            )
                        value = parse_value(section[key]) & 0xFFFFFFFFFFFFFFFF
                        # Loud width-contract check: a value that does not fit
                        # its storage tier means the trace and the manifest
                        # disagree about the signal width — packing it would
                        # silently truncate and surface later as an oracle
                        # verify mismatch, so fail here with the exact stream.
                        if value >= limit:
                            raise ValueError(
                                f"{trace_path}:{line_number}: value {value:#x} for "
                                f"{array} does not fit its storage tier "
                                f"({limit.bit_length() // 8} bytes) — trace and "
                                f"manifest disagree about the signal width"
                            )
                        buffer.extend(pack_elem(value))
                    num_cycles += 1
                    if num_cycles % 4096 == 0:
                        for writer, buffer in zip(writers, buffers):
                            writer.write(buffer)
                            buffer.clear()
                    if num_cycles % 100000 == 0:
                        print(f"  streamed {num_cycles} trace records...", file=sys.stderr)
            if num_cycles == 0:
                raise ValueError(f"{trace_path}: empty trace")
            for writer, buffer in zip(writers, buffers):
                if buffer:
                    writer.write(buffer)
                    buffer.clear()

            cycles_per_eval = 2 * width
            minimum_len = num_cycles + cycles_per_eval
            array_len = (
                (minimum_len + cycles_per_eval - 1) // cycles_per_eval
            ) * cycles_per_eval
            # v4: pad every stream temp to array_len + 1 raw elements (blocks
            # are phased at cycle 1, so the last block's final element is
            # cycle array_len). Region alignment happens at assembly time and
            # only for the stream-major ext/out section.
            for writer, (_, _, _, elem) in zip(writers, metadata):
                pad_bytes = (array_len + 1 - num_cycles) * elem
                while pad_bytes:
                    count = min(pad_bytes, len(zero_chunk))
                    writer.write(zero_chunk[:count])
                    pad_bytes -= count
        finally:
            for writer in writers:
                writer.close()

        fd, tmp_bin_name = tempfile.mkstemp(prefix=".oracle_data.", dir=output_h.parent)
        os.close(fd)
        tmp_bin = Path(tmp_bin_name)
        kernel = [
            (path, meta)
            for path, meta in zip(array_paths, metadata)
            if meta[1] == "micro"
        ]
        extout = [
            (path, meta)
            for path, meta in zip(array_paths, metadata)
            if meta[1] != "micro"
        ]
        cpw = 2 * width
        num_blocks = array_len // cpw
        try:
            with tmp_bin.open("wb") as out:
                out.write(
                    struct.pack(
                        "<IIIIII", num_cycles, array_len, len(metadata),
                        ORACLE_FORMAT_VERSION, block_bytes, num_blocks,
                    )
                )
                out.write(b"\x00" * (64 - 24))
                # Kernel section: window-major blocks, interleaved in groups.
                group = 256
                for b0 in range(0, num_blocks, group):
                    gsize = min(group, num_blocks - b0)
                    bufs: list[tuple[bytes, int, int]] = []
                    for path, (array, _, _, elem) in kernel:
                        start = (1 + b0 * cpw) * elem
                        length = gsize * cpw * elem
                        with path.open("rb") as source:
                            source.seek(start)
                            data = source.read(length)
                        if len(data) != length:
                            raise ValueError(f"short read from {path.name}")
                        bufs.append((data, block_offs[array], elem))
                    out_group = bytearray(gsize * block_bytes)
                    for data, boff, elem in bufs:
                        slot = cpw * elem
                        half = slot // 2
                        for bi in range(gsize):
                            dst = bi * block_bytes + boff
                            src = bi * slot
                            if mirrored:
                                # v4m: rev half element-reversed so the kernel
                                # rev pass is a straight copy (lane L at W+L).
                                out_group[dst : dst + half] = data[src : src + half]
                                rev = elem_array(ARRAY_TYPECODE[elem], data[src + half : src + slot])
                                rev.reverse()
                                out_group[dst + half : dst + slot] = rev.tobytes()
                            else:
                                out_group[dst : dst + slot] = data[src : src + slot]
                    out.write(out_group)
                # ext/out section: stream-major, align64 regions, first
                # array_len elements (the +1 padding element is kernel-only).
                for path, (_, _, _, elem) in extout:
                    region = align64(array_len * elem)
                    with path.open("rb") as array_data:
                        copied = 0
                        target = array_len * elem
                        while copied < target:
                            chunk = array_data.read(min(1024 * 1024, target - copied))
                            if not chunk:
                                raise ValueError(f"short read from {path.name}")
                            out.write(chunk)
                            copied += len(chunk)
                    if region != array_len * elem:
                        out.write(b"\x00" * (region - array_len * elem))
            os.replace(tmp_bin, bin_path)
        finally:
            if tmp_bin.exists():
                tmp_bin.unlink()

    fd, tmp_header_name = tempfile.mkstemp(prefix=".oracle_data.", dir=output_h.parent)
    os.close(fd)
    tmp_header = Path(tmp_header_name)
    try:
        write_header(tmp_header, num_cycles, array_len, metadata, block_bytes, 2 * width, mirrored)
        os.replace(tmp_header, output_h)
    finally:
        if tmp_header.exists():
            tmp_header.unlink()

    return num_cycles, array_len, len(metadata)


def run() -> int:
    parser = argparse.ArgumentParser(
        description="Pack Rocket CHISA v2 oracle data from a JSONL trace"
    )
    parser.add_argument("trace", type=Path, help="scalar trace JSONL")
    parser.add_argument("top_h", type=Path, help="v2 Top.h")
    parser.add_argument("output", type=Path, help="output oracle_data.h")
    parser.add_argument("--width", type=int, default=0, help="v2 width (0 = detect)")
    parser.add_argument(
        "--manifest",
        type=Path,
        required=True,
        help="v2 oracle_manifest.json; array/traceKey pairs are consumed verbatim",
    )
    args = parser.parse_args()

    manifest_pairs, block_offs, block_bytes, mirrored = load_manifest(args.manifest)
    width = validate_header(
        args.top_h, manifest_pairs, args.width, block_offs, block_bytes, mirrored
    )
    records, array_len, arrays = pack_trace(
        args.trace, args.output, width, manifest_pairs, block_offs, block_bytes, mirrored
    )
    bin_path = args.output.with_suffix(".bin")
    print(
        f"Manifest: {len(manifest_pairs)} exact oracle pairs; "
        f"Rocket ext/out: {len(EXT_FIELDS) + len(OUT_FIELDS)} arrays",
        file=sys.stderr,
    )
    print(
        f"Wrote {bin_path} ({bin_path.stat().st_size} bytes, "
        f"{records} records, padded to {array_len}, {arrays} arrays)",
        file=sys.stderr,
    )
    print(f"Wrote {args.output} (thin mmap header)", file=sys.stderr)
    return 0


def main() -> int:
    try:
        return run()
    except (OSError, ValueError, KeyError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
