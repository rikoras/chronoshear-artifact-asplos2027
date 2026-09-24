#!/usr/bin/env python3
"""Generate the manifest-exact Sodor full-chip live oracle writer."""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys


for parent in Path(__file__).resolve().parents:
    tools = parent / "benchmarks" / "rocket"
    if tools.is_dir():
        sys.path.insert(0, str(tools))
        break
else:
    raise SystemExit("ERROR: cannot locate the shared v4 oracle ABI tools")

import gen_oracle_data_rocket as common  # noqa: E402


REG_MAPPINGS = {
    "tile.core.c.exe_inst_is_load": "g.ctl().exe_inst_is_load",
    "tile.core.c.exe_reg_exception": "g.ctl().exe_reg_exception",
    "tile.core.c.exe_reg_is_csr": "g.ctl().exe_reg_is_csr",
    "tile.core.c.exe_reg_wbaddr": "g.ctl().exe_reg_wbaddr",
    "tile.core.c.ifkill_REG": "g.ctl().ifkill_REG",
    "tile.core.c.io_ctl_fencei_REG": "g.ctl().io_ctl_fencei_REG",
    "tile.core.c.io_ctl_mem_exception_REG":
        "g.ctl().io_ctl_mem_exception_REG",
    "tile.core.d.brjmp_offset": "g.dpath().exe_reg_op2_data",
    "tile.core.d.csr.reg_dcsr_step": "g.dpath().csr.dcsr_step",
    "tile.core.d.csr.reg_dcsr_ebreakm":
        "g.dpath().csr.dcsr_ebreakm",
    "tile.core.d.csr.reg_dpc": "g.dpath().csr.dpc",
    "tile.core.d.csr.reg_dscratch": "g.dpath().csr.dscratch",
    "tile.core.d.csr.reg_mcause": "g.dpath().csr.mcause",
    "tile.core.d.csr.reg_medeleg": "g.dpath().csr.medeleg",
    "tile.core.d.csr.reg_mepc": "g.dpath().csr.mepc",
    "tile.core.d.csr.reg_mie_msip": "g.dpath().csr.mie_msip",
    "tile.core.d.csr.reg_mie_mtip": "g.dpath().csr.mie_mtip",
    "tile.core.d.csr.reg_mip_msip": "g.dpath().csr.mip_msip",
    "tile.core.d.csr.reg_mscratch": "g.dpath().csr.mscratch",
    "tile.core.d.csr.reg_mstatus_mie": "g.dpath().csr.mie",
    "tile.core.d.csr.reg_mstatus_mpie": "g.dpath().csr.mpie",
    "tile.core.d.csr.reg_mtval": "g.dpath().csr.mtval",
    "tile.core.d.csr.large": "(g.dpath().csr.cycle >> 6)",
    "tile.core.d.csr.large_1": "(g.dpath().csr.instret >> 6)",
    "tile.core.d.csr.small": "(g.dpath().csr.cycle & 0x3f)",
    "tile.core.d.csr.small_1": "(g.dpath().csr.instret & 0x3f)",
    "tile.core.d.dec_reg_inst": "g.dpath().dec_reg_inst",
    "tile.core.d.dec_reg_pc": "g.dpath().dec_reg_pc",
    "tile.core.d.dec_reg_valid": "g.dpath().dec_reg_valid",
    "tile.core.d.exe_alu_op1": "g.dpath().exe_reg_op1_data",
    "tile.core.d.exe_reg_ctrl_alu_fun":
        "g.dpath().exe_reg_ctrl_alu_fun",
    "tile.core.d.exe_reg_ctrl_br_type":
        "g.dpath().exe_reg_ctrl_br_type",
    "tile.core.d.exe_reg_ctrl_csr_cmd":
        "g.dpath().exe_reg_ctrl_csr_cmd",
    "tile.core.d.exe_reg_ctrl_mem_fcn":
        "g.dpath().exe_reg_ctrl_mem_fcn",
    "tile.core.d.exe_reg_ctrl_mem_typ":
        "g.dpath().exe_reg_ctrl_mem_typ",
    "tile.core.d.exe_reg_ctrl_mem_val":
        "g.dpath().exe_reg_ctrl_mem_val",
    "tile.core.d.exe_reg_ctrl_rf_wen":
        "g.dpath().exe_reg_ctrl_rf_wen",
    "tile.core.d.exe_reg_ctrl_wb_sel":
        "g.dpath().exe_reg_ctrl_wb_sel",
    "tile.core.d.exe_reg_inst": "g.dpath().exe_reg_inst",
    "tile.core.d.exe_reg_pc": "g.dpath().exe_reg_pc",
    "tile.core.d.exe_reg_rs2_data": "g.dpath().exe_reg_rs2_data",
    "tile.core.d.exe_reg_valid": "g.dpath().exe_reg_valid",
    "tile.core.d.exe_reg_wbaddr": "g.dpath().exe_reg_wbaddr",
    "tile.core.d.if_reg_pc": "g.dpath().if_reg_pc",
    "tile.core.d.mem_reg_alu_out": "g.dpath().mem_reg_alu_out",
    "tile.core.d.mem_reg_ctrl_csr_cmd":
        "g.dpath().mem_reg_ctrl_csr_cmd",
    "tile.core.d.mem_reg_ctrl_mem_fcn":
        "g.dpath().mem_reg_ctrl_mem_fcn",
    "tile.core.d.mem_reg_ctrl_mem_typ":
        "g.dpath().mem_reg_ctrl_mem_typ",
    "tile.core.d.mem_reg_ctrl_mem_val":
        "g.dpath().mem_reg_ctrl_mem_val",
    "tile.core.d.mem_reg_ctrl_rf_wen":
        "g.dpath().mem_reg_ctrl_rf_wen",
    "tile.core.d.mem_reg_ctrl_wb_sel":
        "g.dpath().mem_reg_ctrl_wb_sel",
    "tile.core.d.mem_reg_inst": "g.dpath().mem_reg_inst",
    "tile.core.d.mem_reg_pc": "g.dpath().mem_reg_pc",
    "tile.core.d.mem_reg_rs2_data": "g.dpath().mem_reg_rs2_data",
    "tile.core.d.mem_reg_valid": "g.dpath().mem_reg_valid",
    "tile.core.d.mem_reg_wbaddr": "g.dpath().mem_reg_wbaddr",
    "tile.core.d.wb_reg_ctrl_rf_wen":
        "g.dpath().wb_reg_ctrl_rf_wen",
    "tile.core.d.wb_reg_valid": "g.dpath().wb_reg_valid",
    "tile.core.d.wb_reg_wbaddr": "g.dpath().wb_reg_wbaddr",
    "tile.core.d.wb_reg_wbdata": "g.dpath().wb_reg_wbdata",
}

for hpm_index in range(32):
    REG_MAPPINGS[f"tile.core.d.csr.small_{hpm_index + 2}"] = (
        f"g.hpm()[{hpm_index}]"
    )


MEMORY_READ_DATA_NAMES = (
    "memory.bytes.draw_MPORT",
    "memory.bytes.draw_MPORT_1",
    "memory.bytes.draw_MPORT_2",
    "memory.bytes.draw_MPORT_3",
    "memory.bytes.io_core_1_resp_bits_data_MPORT",
    "memory.bytes.io_core_1_resp_bits_data_MPORT_1",
    "memory.bytes.io_core_1_resp_bits_data_MPORT_2",
    "memory.bytes.io_core_1_resp_bits_data_MPORT_3",
    "memory.bytes.io_host_rdata_MPORT",
    "memory.bytes.io_host_rdata_MPORT_1",
    "memory.bytes.io_host_rdata_MPORT_2",
    "memory.bytes.io_host_rdata_MPORT_3",
    "memory.bytes.io_tohost_MPORT",
    "memory.bytes.io_tohost_MPORT_1",
    "memory.bytes.io_tohost_MPORT_2",
    "memory.bytes.io_tohost_MPORT_3",
)


COMB_MAPPINGS = {
    "regfile.regfile.io_dm_rdata_MPORT": "env.raw_reg(0)",
    "regfile.regfile.io_rs1_data_MPORT":
        "env.raw_reg(g.outputs().rf_rs1_addr)",
    "regfile.regfile.io_rs2_data_MPORT":
        "env.raw_reg(g.outputs().rf_rs2_addr)",
}


for read_port, data_name in enumerate(MEMORY_READ_DATA_NAMES):
    COMB_MAPPINGS[data_name] = f"memory_access.reads[{read_port}].data"
    COMB_MAPPINGS[data_name + "__access_address"] = (
        f"memory_access.reads[{read_port}].address"
    )

for write_port in range(8):
    port_name = "MPORT" if write_port == 0 else f"MPORT_{write_port}"
    base = f"memory.bytes.__access_write_{write_port}_{port_name}"
    COMB_MAPPINGS[base + "_enable"] = (
        f"memory_access.writes[{write_port}].enable"
    )
    COMB_MAPPINGS[base + "_address"] = (
        f"memory_access.writes[{write_port}].address"
    )
    COMB_MAPPINGS[base + "_data"] = (
        f"memory_access.writes[{write_port}].data"
    )


# The dense ABI needs the same byte values and canonical write tuples, but
# does not need an intermediate array of port records on the producer.
DENSE_COMB_MAPPINGS = dict(COMB_MAPPINGS)
read_words = ("dmem_word", "imem_word", "host_word", "tohost_word")
read_addresses = ("o.dmem_req_addr", "o.imem_req_addr", "env.host().addr",
                  "sodor::sidecar::kTohost")
for read_port, data_name in enumerate(MEMORY_READ_DATA_NAMES):
    group, byte = divmod(read_port, 4)
    offset = 3 - byte
    DENSE_COMB_MAPPINGS[data_name] = (
        f"static_cast<uint8_t>(memory_access.{read_words[group]} >> {8 * offset})"
    )
    DENSE_COMB_MAPPINGS[data_name + "__access_address"] = (
        f"env.memory().index({read_addresses[group]} + {offset}u)"
    )
for write_port in range(8):
    port_name = "MPORT" if write_port == 0 else f"MPORT_{write_port}"
    base = f"memory.bytes.__access_write_{write_port}_{port_name}"
    byte = write_port % 4
    enabled = f"sw_core_write_{byte}" if write_port < 4 else "sw_host_write"
    address = "o.dmem_req_addr" if write_port < 4 else "env.host().addr"
    data = "o.dmem_req_data" if write_port < 4 else "env.host().wdata"
    DENSE_COMB_MAPPINGS[base + "_enable"] = enabled
    DENSE_COMB_MAPPINGS[base + "_address"] = (
        f"({enabled} ? env.memory().index({address} + {byte}u) : 0u)"
    )
    DENSE_COMB_MAPPINGS[base + "_data"] = (
        f"({enabled} ? static_cast<uint8_t>({data} >> {8 * byte}) : uint8_t{{0}})"
    )


CTYPE = {1: "uint8_t", 2: "uint16_t", 4: "uint32_t", 8: "uint64_t"}


def load_register_mappings(path: Path) -> dict[str, str]:
    """Replace scalar model fields with manifest-defined packed banks.

    Register banking is a storage-only compiler rewrite.  The reference model
    continues to expose the source RTL fields, so the producer reconstructs
    each bank mechanically from the manifest's exact bit positions.  Failing
    closed here prevents a compiler layout change from silently changing the
    oracle ABI.
    """
    data = json.loads(path.read_text(encoding="utf-8"))
    banks = data.get("banks")
    if not isinstance(banks, list):
        raise ValueError(f"{path}: missing register bank list")
    if int(data.get("bankCount", -1)) != len(banks):
        raise ValueError(f"{path}: register bank count mismatch")

    mappings = dict(REG_MAPPINGS)
    consumed: set[str] = set()
    bank_names: set[str] = set()
    pending: list[tuple[str, str, list[str]]] = []
    for bank in banks:
        if not isinstance(bank, dict):
            raise ValueError(f"{path}: malformed register bank entry")
        name = str(bank.get("name", ""))
        width = int(bank.get("width", 0))
        fields = bank.get("fields")
        if not name or name in bank_names or name in REG_MAPPINGS:
            raise ValueError(f"{path}: invalid or duplicate bank name {name!r}")
        if width < 1 or width > 64 or not isinstance(fields, list) or not fields:
            raise ValueError(f"{path}: invalid bank shape for {name}")

        covered = 0
        parts: list[str] = []
        sources: list[str] = []
        for field in fields:
            if not isinstance(field, dict):
                raise ValueError(f"{path}: malformed field in {name}")
            source = str(field.get("source", ""))
            field_width = int(field.get("width", 0))
            high = int(field.get("high", -1))
            low = int(field.get("low", -1))
            if source not in REG_MAPPINGS:
                raise ValueError(f"{path}: no model mapping for bank field {source}")
            if source in consumed:
                raise ValueError(f"{path}: bank field appears twice: {source}")
            if (field_width < 1 or high - low + 1 != field_width or
                    low < 0 or high >= width):
                raise ValueError(f"{path}: invalid bit range for {source} in {name}")
            field_mask = ((1 << field_width) - 1) << low
            if covered & field_mask:
                raise ValueError(f"{path}: overlapping fields in {name}")
            covered |= field_mask

            expression = f"static_cast<uint64_t>({REG_MAPPINGS[source]})"
            if field_width < 64:
                expression = (
                    f"({expression} & 0x{(1 << field_width) - 1:x}ULL)"
                )
            if low:
                expression = f"({expression} << {low})"
            parts.append(expression)
            sources.append(source)
            consumed.add(source)

        if covered != (1 << width) - 1:
            raise ValueError(f"{path}: bank {name} does not cover all {width} bits")
        pending.append((name, " | ".join(parts), sources))
        bank_names.add(name)

    for name, expression, sources in pending:
        for source in sources:
            mappings.pop(source)
        mappings[name] = f"({expression})"
    return mappings


def dense_group(name: str) -> str | None:
    """Return the exact change guard for a producer-cold stream.

    Unclassified streams stay on the ordinary per-cycle writer path.  Every
    group key below is an over-approximation: a key may move without one of
    its streams moving, but no stream can move while its key stays fixed.
    """
    if ".csr." in name:
        leaf = name.rsplit(".", 1)[-1]
        if leaf.startswith("reg_"):
            return "csr"
        if leaf.startswith("small_"):
            try:
                if int(leaf.removeprefix("small_")) >= 2:
                    return "csr"
            except ValueError:
                pass
        if leaf in {"large", "large_1"}:
            return "counter"
    if name.startswith("memory.bytes.io_host_rdata"):
        return "host"
    if name.startswith("memory.bytes.io_tohost"):
        return "tohost"
    if name.startswith("memory.bytes.__access_write_"):
        try:
            port = int(name.removeprefix(
                "memory.bytes.__access_write_").split("_", 1)[0])
        except ValueError:
            port = -1
        # Core stores can change on adjacent cycles.  Rewriting the entire
        # remaining window at each transition makes this group quadratic in
        # the lane width.  Emit its proof tuples once per lane instead; host
        # writes retain the cold-group path and the dense ABI is unchanged.
        return None if 0 <= port < 4 else "host"
    if name == "regfile.regfile.io_dm_rdata_MPORT":
        return "constant"
    return None


def load_entries(path: Path) -> list[dict[str, object]]:
    data = json.loads(path.read_text(encoding="utf-8"))
    entries = data.get("oracles") or data.get("streams")
    if not isinstance(entries, list):
        raise ValueError(f"{path}: missing oracle entry list")
    return entries


def validate_entries(entries: list[dict[str, object]], width: int,
                     block_bytes: int, reg_mappings: dict[str, str],
                     allow_mapping_subset: bool = False) -> None:
    names = [str(entry.get("flat")) for entry in entries]
    if len(names) != len(set(names)):
        raise ValueError("duplicate flat name in full-chip oracle manifest")
    expected = set(reg_mappings) | set(COMB_MAPPINGS)
    if set(names) != expected and not (
        allow_mapping_subset and set(names).issubset(expected)
    ):
        missing = sorted(expected - set(names))
        extra = sorted(set(names) - expected)
        raise ValueError(f"manifest mapping mismatch: missing={missing} extra={extra}")

    coverage = bytearray(block_bytes)
    for entry in entries:
        name = str(entry["flat"])
        kind = str(entry["kind"])
        if (kind == "reg") != (name in reg_mappings):
            raise ValueError(f"kind/mapping mismatch for {name}: {kind}")
        elem = int(entry.get("elemBytes", 0))
        offset = int(entry.get("blockOffset", -1))
        if elem not in CTYPE:
            raise ValueError(f"invalid elemBytes={elem} for {name}")
        end = offset + 2 * width * elem
        if offset < 0 or offset % elem or end > block_bytes:
            raise ValueError(f"invalid block slot [{offset}, {end}) for {name}")
        if any(coverage[offset:end]):
            raise ValueError(f"overlapping block slot for {name}")
        coverage[offset:end] = b"\x01" * (end - offset)
    if not all(coverage):
        first_hole = coverage.index(0)
        if any(coverage[first_hole:]) or block_bytes - first_hole >= 64:
            raise ValueError("oracle block contains a non-terminal layout hole")


def write_writer(output: Path, entries: list[dict[str, object]], width: int,
                 block_bytes: int, mirrored: bool,
                 reg_mappings: dict[str, str]) -> None:
    uses_memory_access = any(
        str(entry["flat"]).startswith("memory.bytes.") for entry in entries
    )
    lines = [
        "// AUTO-GENERATED by gen_sidecar_writer.py. DO NOT EDIT.",
        "#pragma once",
        "#include <array>",
        "#include <cstddef>",
        "#include <cstdint>",
        "#include <cstring>",
        "#include \"fullchip_env.h\"",
        "",
        f"static constexpr int SW_WIDTH = {width};",
        f"static constexpr int SW_CPW = {2 * width};",
        f"static constexpr int64_t SW_BLOCK_BYTES = {block_bytes}LL;",
        f"static constexpr int SW_MIRRORED = {1 if mirrored else 0};",
        f"static constexpr int SW_NUM_STREAMS = {len(entries)};",
        "",
        "template <typename T>",
        "static inline void sw_store(char* block, uint32_t offset, int element,",
        "                            uint64_t value) {",
        "  const T narrowed = static_cast<T>(value);",
        "  std::memcpy(block + offset + element * sizeof(T), &narrowed, sizeof(T));",
        "}",
        "",
        "static inline void sw_write_cycle_baseline(",
        "    const sodor::fullchip::FullChipEnv& env, char* block, int element) {",
        "  const sodor::SodorGuider& g = env.guider();",
    ]
    if uses_memory_access:
        lines.append(
            "  const sodor::fullchip::MemoryAccessTrace& memory_access = "
            "env.memory_access_trace();"
        )
    for entry in entries:
        name = str(entry["flat"])
        expr = reg_mappings.get(name, COMB_MAPPINGS.get(name))
        elem = int(entry["elemBytes"])
        offset = int(entry["blockOffset"])
        lines.append(
            f"  sw_store<{CTYPE[elem]}>(block, {offset}u, element, "
            f"static_cast<uint64_t>({expr}));  // {name}"
        )
    lines.extend([
        "}",
        "",
        "// Dense release writer.  The memory access bundle is constructed once",
        "// per cycle, then all read-data and access-proof streams copy from it.",
        "static inline void sw_write_cycle_optimized(",
        "    const sodor::fullchip::FullChipEnv& env, char* block, int element) {",
        "  const sodor::SodorGuider& g = env.guider();",
        "  const sodor::Outputs& o = env.outputs();",
    ])
    if uses_memory_access:
        lines.append(
            "  const sodor::fullchip::MemoryAccessTrace& memory_access = "
            "env.memory_access_trace();"
        )
    for entry in entries:
        name = str(entry["flat"])
        expr = reg_mappings.get(name, COMB_MAPPINGS.get(name))
        assert expr is not None
        expr = expr.replace("g.outputs()", "o")
        elem = int(entry["elemBytes"])
        offset = int(entry["blockOffset"])
        lines.append(
            f"  sw_store<{CTYPE[elem]}>(block, {offset}u, element, "
            f"static_cast<uint64_t>({expr}));  // {name}"
        )
    lines.extend([
        "}",
        "",
        "// BOOM-style dense hot/cold writer.  Hot streams write one element",
        "// per cycle.  A cold group is sampled through one exact activity key;",
        "// when that key moves, its current values overwrite the chronological",
        "// tail of the stream-major block.  The resulting block is byte-for-byte",
        "// the ordinary dense ABI, so the consumer needs no decoder.",
        "template <typename T>",
        "static inline void sw_fill_tail(char* block, uint32_t offset,",
        "                                int position, uint64_t value) {",
        "  const int first = !SW_MIRRORED || position < SW_WIDTH",
        "                        ? position : SW_WIDTH;",
        "  const int last = !SW_MIRRORED || position < SW_WIDTH",
        "                       ? SW_CPW : 3 * SW_WIDTH - position;",
        "  for (int element = first; element < last; ++element)",
        "    sw_store<T>(block, offset, element, value);",
        "}",
        "",
        "// A ring slot keeps its dense cold fields between uses.  Remember",
        "// whether each group still contains one uniform value, so an",
        "// unchanged group can be reused without exporting it every window.",
        "struct SodorDenseOracleBlockCache {",
    ])
    signatures = {
        "csr": ["g.csr_epoch()"],
        "counter": ["(g.dpath().csr.cycle >> 6)",
                    "(g.dpath().csr.instret >> 6)"],
        "host": [
            "(static_cast<uint64_t>(env.host().addr) | "
            "(static_cast<uint64_t>(env.host().valid) << 32) | "
            "(static_cast<uint64_t>(env.host().write) << 33))",
            "(static_cast<uint64_t>(env.host().wdata) | "
            "(static_cast<uint64_t>(memory_access.host_word) << 32))",
        ],
        "tohost": ["memory_access.tohost_word"],
        "core_write": ["memory_access.core_write_control",
                       "memory_access.core_write_data"],
    }
    group_order = ("csr", "counter", "host", "tohost", "core_write",
                   "constant")
    grouped: dict[str, list[dict[str, object]]] = {}
    for entry in entries:
        group = dense_group(str(entry["flat"]))
        if group is not None:
            grouped.setdefault(group, []).append(entry)
    for group in group_order:
        if not grouped.get(group):
            continue
        for index in range(len(signatures.get(group, []))):
            lines.append(f"  uint64_t {group}_sig{index} = 0;")
        lines.append(f"  bool {group}_valid = false;")
        lines.append(f"  bool {group}_uniform = false;")
    lines.extend([
        "};",
        "",
        "class SodorDenseOracleWriter {",
        " public:",
        "  void begin_window(char*, SodorDenseOracleBlockCache* cache = nullptr) {",
        "    block_cache_ = cache;",
        "  }",
        "",
        "  void write_cycle(const sodor::fullchip::FullChipEnv& env,",
        "                   char* block, int position, int element) {",
        "    const sodor::SodorGuider& g = env.guider();",
        "    const sodor::Outputs& o = env.outputs();",
    ])
    if uses_memory_access:
        lines.append(
            "    const sodor::fullchip::MemoryAccessSnapshot& memory_access = "
            "env.memory_access_snapshot();"
        )

    if uses_memory_access:
        lines.extend([
            "    const bool sw_core_store = !env.host().valid && o.dmem_req_valid && o.dmem_req_fcn == sodor::M_XWR;",
            "    const unsigned sw_core_bytes = o.dmem_req_typ == sodor::MT_B ? 1u : o.dmem_req_typ == sodor::MT_H ? 2u : 4u;",
            "    const bool sw_host_write = env.host().valid && env.host().write;",
        ])
        for byte in range(4):
            lines.append(f"    const bool sw_core_write_{byte} = sw_core_store && {byte}u < sw_core_bytes;")

    grouped = {}
    for entry in entries:
        name = str(entry["flat"])
        group = dense_group(name)
        if group is not None:
            grouped.setdefault(group, []).append(entry)
            continue
        expr = reg_mappings.get(name, DENSE_COMB_MAPPINGS.get(name))
        assert expr is not None
        expr = expr.replace("g.outputs()", "o")
        elem = int(entry["elemBytes"])
        offset = int(entry["blockOffset"])
        lines.append(
            f"    sw_store<{CTYPE[elem]}>(block, {offset}u, element, "
            f"static_cast<uint64_t>({expr}));  // hot: {name}"
        )

    for group in group_order:
        members = grouped.get(group, [])
        if not members:
            continue
        sigs = signatures.get(group, [])
        for index, expr in enumerate(sigs):
            lines.append(
                f"    const uint64_t sw_{group}_sig{index} = "
                f"static_cast<uint64_t>({expr});"
            )
        if sigs:
            comparisons = " || ".join(
                f"sw_{group}_sig{i} != {group}_sig{i}_"
                for i in range(len(sigs))
            )
            cache_comparisons = " && ".join(
                f"sw_{group}_sig{i} == block_cache_->{group}_sig{i}"
                for i in range(len(sigs))
            )
            lines.append(
                f"    const bool sw_{group}_changed = !{group}_valid_ || "
                f"{comparisons};"
            )
            lines.append(
                f"    const bool sw_{group}_cache_match = block_cache_ && "
                f"block_cache_->{group}_valid && "
                f"block_cache_->{group}_uniform && {cache_comparisons};"
            )
            lines.append(
                f"    if ((position == 0 && !sw_{group}_cache_match) || "
                f"(position != 0 && sw_{group}_changed)) {{"
            )
        else:
            lines.append(
                f"    const bool sw_{group}_cache_match = block_cache_ && "
                f"block_cache_->{group}_valid && "
                f"block_cache_->{group}_uniform;"
            )
            lines.append(
                f"    if (position == 0 && !sw_{group}_cache_match) {{"
            )
        for entry in members:
            name = str(entry["flat"])
            expr = reg_mappings.get(name, DENSE_COMB_MAPPINGS.get(name))
            assert expr is not None
            expr = expr.replace("g.outputs()", "o")
            elem = int(entry["elemBytes"])
            offset = int(entry["blockOffset"])
            lines.append(
                f"      sw_fill_tail<{CTYPE[elem]}>(block, {offset}u, "
                f"position, static_cast<uint64_t>({expr}));  // cold: {name}"
            )
        lines.append("    }")
        if sigs:
            lines.append(f"    if (sw_{group}_changed) {{")
            for index in range(len(sigs)):
                lines.append(f"      {group}_sig{index}_ = sw_{group}_sig{index};")
            lines.append(f"      {group}_valid_ = true;")
            lines.append("    }")
        lines.append("    if (block_cache_) {")
        lines.append("      if (position == 0) {")
        for index in range(len(sigs)):
            lines.append(
                f"        block_cache_->{group}_sig{index} = "
                f"sw_{group}_sig{index};"
            )
        lines.append(f"        block_cache_->{group}_valid = true;")
        lines.append(f"        block_cache_->{group}_uniform = true;")
        if sigs:
            lines.append(f"      }} else if (sw_{group}_changed) {{")
            for index in range(len(sigs)):
                lines.append(
                    f"        block_cache_->{group}_sig{index} = "
                    f"sw_{group}_sig{index};"
                )
            lines.append(f"        block_cache_->{group}_valid = true;")
            lines.append(f"        block_cache_->{group}_uniform = false;")
        lines.append("      }")
        lines.append("    }")
    lines.extend([
        "  }",
        "",
        " private:",
    ])
    for group in ("csr", "counter", "host", "tohost", "core_write"):
        if group not in grouped:
            continue
        sigs = signatures[group]
        for index in range(len(sigs)):
            lines.append(f"  uint64_t {group}_sig{index}_ = 0;")
        lines.append(f"  bool {group}_valid_ = false;")
    lines.extend([
        "  SodorDenseOracleBlockCache* block_cache_ = nullptr;",
        "};",
        "",
        "// BOOM-style change transport.  The producer records only streams that",
        "// move.  Kept as --producer=sparse for experiments on this small ABI;",
        "// the consumer expands changes before evaluating a window.",
        "struct SodorOracleDelta {",
        "  std::array<uint8_t, SW_NUM_STREAMS> count{};",
        "  std::array<std::array<uint8_t, SW_CPW>, SW_NUM_STREAMS> position{};",
        "  std::array<std::array<uint64_t, SW_CPW>, SW_NUM_STREAMS> value{};",
        "};",
        "",
        "class SodorOracleWriter {",
        " public:",
        "  void begin_window(SodorOracleDelta& delta) {",
        "    delta.count.fill(0);",
        "  }",
        "",
        "  void write_cycle(const sodor::fullchip::FullChipEnv& env,",
        "                   SodorOracleDelta& delta, int position) {",
        "    const sodor::SodorGuider& g = env.guider();",
        "    const sodor::Outputs& o = env.outputs();",
    ])
    if uses_memory_access:
        lines.append(
            "    const sodor::fullchip::MemoryAccessTrace& memory_access = "
            "env.memory_access_trace();"
        )
    for lane, entry in enumerate(entries):
        name = str(entry["flat"])
        expr = reg_mappings.get(name, COMB_MAPPINGS.get(name))
        assert expr is not None
        expr = expr.replace("g.outputs()", "o")
        elem = int(entry["elemBytes"])
        offset = int(entry["blockOffset"])
        lines.append(
            f"    store_changed<{CTYPE[elem]}>({lane}u, delta, position, "
            f"static_cast<uint64_t>({expr}));  // {name}"
        )
    lines.extend([
        "    initialized_ = true;",
        f"    sampled_ += {len(entries)}u;",
        "  }",
        "",
        "  uint64_t sampled() const { return sampled_; }",
        "  uint64_t stored() const { return stored_; }",
        "",
        " private:",
        "  template <typename T>",
        "  void store_changed(uint32_t lane, SodorOracleDelta& delta,",
        "                     int position, uint64_t value) {",
        "    const T narrowed = static_cast<T>(value);",
        "    const uint64_t canonical = static_cast<uint64_t>(narrowed);",
        "    if (initialized_ && last_[lane] == canonical) return;",
        "    const uint8_t index = delta.count[lane]++;",
        "    delta.position[lane][index] = static_cast<uint8_t>(position);",
        "    delta.value[lane][index] = canonical;",
        "    last_[lane] = canonical;",
        "    ++stored_;",
        "  }",
        "",
        "  std::array<uint64_t, SW_NUM_STREAMS> last_{};",
        "  bool initialized_ = false;",
        "  uint64_t sampled_ = 0;",
        "  uint64_t stored_ = 0;",
        "};",
        "",
        "class SodorOracleDecoder {",
        " public:",
        "  bool decode(const SodorOracleDelta& delta, char* block) {",
    ])
    for lane, entry in enumerate(entries):
        elem = int(entry["elemBytes"])
        offset = int(entry["blockOffset"])
        lines.append(
            f"    if (!decode_lane<{CTYPE[elem]}>({lane}u, {offset}u, delta, "
            f"block)) return false;"
        )
    lines.extend([
        "    initialized_ = true;",
        "    return true;",
        "  }",
        "",
        "  uint64_t expanded_stores() const { return expanded_stores_; }",
        "",
        " private:",
        "  template <typename T>",
        "  void fill_range(char* block, uint32_t offset, int begin, int end,",
        "                  uint64_t value) {",
        "    const T narrowed = static_cast<T>(value);",
        "    for (int position = begin; position < end; ++position) {",
        "      const int element = !SW_MIRRORED || position < SW_WIDTH",
        "                              ? position",
        "                              : 3 * SW_WIDTH - 1 - position;",
        "      std::memcpy(block + offset + element * sizeof(T), &narrowed,",
        "                  sizeof(T));",
        "      ++expanded_stores_;",
        "    }",
        "  }",
        "",
        "  template <typename T>",
        "  bool decode_lane(uint32_t lane, uint32_t offset,",
        "                   const SodorOracleDelta& delta, char* block) {",
        "    const uint8_t count = delta.count[lane];",
        "    if (count > SW_CPW) return false;",
        "    if (count == 0) {",
        "      if (nonuniform_[lane])",
        "        fill_range<T>(block, offset, 0, SW_CPW, last_[lane]);",
        "      nonuniform_[lane] = false;",
        "      return initialized_;",
        "    }",
        "    uint64_t value = initialized_ ? last_[lane] : 0;",
        "    int begin = 0;",
        "    for (uint8_t index = 0; index < count; ++index) {",
        "      const int position = delta.position[lane][index];",
        "      if (position < begin || position >= SW_CPW) return false;",
        "      fill_range<T>(block, offset, begin, position, value);",
        "      value = delta.value[lane][index];",
        "      begin = position;",
        "    }",
        "    fill_range<T>(block, offset, begin, SW_CPW, value);",
        "    last_[lane] = value;",
        "    nonuniform_[lane] = count > 1 || delta.position[lane][0] != 0;",
        "    return true;",
        "  }",
        "",
        "  std::array<uint64_t, SW_NUM_STREAMS> last_{};",
        "  std::array<bool, SW_NUM_STREAMS> nonuniform_{};",
        "  bool initialized_ = false;",
        "  uint64_t expanded_stores_ = 0;",
        "};",
        "",
    ])
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text("\n".join(lines), encoding="utf-8")


def write_shim(shim_dir: Path, top_h: Path, block_bytes: int,
               mirrored: bool) -> None:
    shim_dir.mkdir(parents=True, exist_ok=True)
    kernel_link = shim_dir / "SodorFullChip.h"
    # The public re-emission recipe writes the shim beside its input header.
    # Resolve before changing the destination so that case keeps the header
    # instead of replacing it with a symlink to itself.
    source_header = top_h.resolve(strict=True)
    if kernel_link.resolve() != source_header:
        if kernel_link.exists() or kernel_link.is_symlink():
            kernel_link.unlink()
        kernel_link.symlink_to(source_header)
    (shim_dir / "oracle_data.h").write_text(
        "#pragma once\n#include <cstdint>\n\n"
        "constexpr int ORACLE_NUM_CYCLES = 1 << 30;\n"
        "constexpr int ORACLE_ARRAY_LEN = 1 << 30;\n"
        f"constexpr int64_t ORACLE_DATA_BLOCK_BYTES = {block_bytes}LL;\n"
        f"constexpr int ORACLE_DATA_MIRRORED = {1 if mirrored else 0};\n"
        "inline const char* oracle_kernel_base = nullptr;\n",
        encoding="utf-8",
    )


def run() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument(
        "--register-bank-manifest",
        type=Path,
        help="defaults to register_bank_manifest.json beside --manifest",
    )
    parser.add_argument("--top-h", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--shim-dir", type=Path, required=True)
    parser.add_argument("--width", type=int, default=0)
    parser.add_argument(
        "--allow-mapping-subset",
        action="store_true",
        help="accept a manifest that uses a strict subset of known mappings",
    )
    args = parser.parse_args()

    pairs, offsets, block_bytes, mirrored = common.load_manifest(args.manifest)
    width = common.validate_header(
        args.top_h, pairs, args.width, offsets, block_bytes, mirrored
    )
    entries = load_entries(args.manifest)
    bank_manifest = args.register_bank_manifest or (
        args.manifest.parent / "register_bank_manifest.json"
    )
    reg_mappings = load_register_mappings(bank_manifest)
    validate_entries(
        entries, width, block_bytes, reg_mappings,
        allow_mapping_subset=args.allow_mapping_subset,
    )
    write_writer(
        args.output, entries, width, block_bytes, mirrored, reg_mappings
    )
    write_shim(args.shim_dir, args.top_h, block_bytes, mirrored)
    print(
        f"FULLCHIP_SIDECAR_WRITER_OK streams={len(entries)} "
        f"reg_mappings={len(reg_mappings)} W={width} "
        f"block={block_bytes} mirrored={int(mirrored)}"
    )
    return 0


def main() -> int:
    try:
        return run()
    except (OSError, ValueError, KeyError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
