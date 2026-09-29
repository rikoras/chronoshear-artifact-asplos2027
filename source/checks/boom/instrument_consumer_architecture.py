#!/usr/bin/env python3
"""Observe actual emitted RTL values before scratch/commit can overwrite them.

This is a validation-only source transform of the locked generated C++ shape.
It adds read-only captures to assignments/injections and real PRF writes. It
does not read model values or change an RTL assignment or any oracle check.
"""
import argparse
import json
from pathlib import Path
import re

TILE = "ldut.tile_prci_domain.tile_reset_domain.boom_tile."


GEOMETRY = {
    "small": dict(commit=1, integer=52, floating=48, integer_ports=2, floating_ports=2,
                  ftq=16, stores=8, pdst_bits=6, ftq_bits=4, store_bits=3),
    "medium": dict(commit=2, integer=80, floating=64, integer_ports=3, floating_ports=2,
                   ftq=32, stores=16, pdst_bits=7, ftq_bits=5, store_bits=4),
    "large": dict(commit=3, integer=100, floating=96, integer_ports=4, floating_ports=2,
                  ftq=32, stores=24, pdst_bits=7, ftq_bits=5, store_bits=5),
}


def geometry_for(configuration):
    if configuration in GEOMETRY: return GEOMETRY[configuration]
    raise ValueError("unsupported BOOM geometry: " + configuration)

def fields(configuration="small"):
    geometry = geometry_for(configuration)
    result = []
    def add(label, suffix, width, kind="comb", full=False):
        result.append(dict(label=label, flat=suffix if full else TILE + suffix, width=width, kind=kind))
    for bank in range(geometry["commit"]):
        # Keep Small's names and complete enum order unchanged. Other BOOM
        # banks repeat the same field order at a fixed stride.
        bank_suffix = str(bank) if bank else ""
        for label, suffix, width in (
            ("RetireValid", "io_commit_arch_valids", 1),
            ("RetireRd", "io_commit_uops_{bank}_ldst", 6),
            ("RetireRdValid", "io_commit_uops_{bank}_ldst_val", 1),
            ("RetireRdType", "io_commit_uops_{bank}_dst_rtype", 2),
            ("RetirePdst", "io_commit_uops_{bank}_pdst", geometry["pdst_bits"]),
            ("RetireFtq", "io_commit_uops_{bank}_ftq_idx", geometry["ftq_bits"]),
            ("RetirePcLow", "io_commit_uops_{bank}_pc_lob", 6),
            ("RetireEdge", "io_commit_uops_{bank}_edge_inst", 1),
            ("RetireStore", "io_commit_uops_{bank}_uses_stq", 1),
            ("EnqueueValid", "io_enq_valids", 1),
        ):
            suffix = suffix.format(bank=bank) if "{bank}" in suffix else f"{suffix}_{bank}"
            add(label + bank_suffix, "core.rob." + suffix, width)
        if configuration != "small":
            add("CommitValid" + bank_suffix, f"core.rob.io_commit_valids_{bank}", 1)
    add("StoreCommitHead", "lsu.stq_commit_head", geometry["store_bits"])
    add("CoreClock", "clock_en", 1, "reg", True)
    add("RobHead", "core.rob.rob_head", 5, "reg")
    add("RobTail", "core.rob.rob_tail", 5, "reg")
    add("DebugMode", "core.csr.reg_debug", 1, "reg")
    for i in range(geometry["ftq"]): add(f"FtqPc{i}", f"frontend.ftq.pcs_{i}", 40, "reg")
    for label, suffix, width, kind in (
        ("StoreAddress", "addr_bits", 40, "reg"),
        ("StoreData", "data_bits", 64, "reg"),
        ("StoreCommand", "uop_mem_cmd", 5, "comb"),
        ("StoreSize", "uop_mem_size", 2, "comb"),
    ):
        for i in range(geometry["stores"]): add(f"{label}{i}", f"lsu.stq_{i}_bits_{suffix}", width, kind)
    return result


def instrument(header, output, width, configuration="small"):
    if width not in (4, 8, 16, 32): raise ValueError("unsupported observation width")
    geometry = geometry_for(configuration)
    source_payload = header.read_bytes()
    text = source_payload.decode()
    if header.resolve() == (output / "TestHarness.h").resolve() or \
            '#include "consumer_architecture_capture.h"' in text:
        raise ValueError("instrument a raw consumer into a separate output directory")
    rows = fields(configuration)
    probe_begin = len(rows)
    clock_observation = None
    # Capture the compiler's explicit PRE clock view in every configuration.
    clock_row = next(row for row in rows if row["label"] == "CoreClock")
    expected = "static_cast<typenameUInt<1>::scalar_t>((static_cast<uint8_t>(clock_en[L].val)&0x1u))"
    candidates = set()
    for match in re.finditer(r"(?m)^\s*(_s___chisa_clock_enable_\d+)\[L\]\.val\s*=\s*([^\n]+);\s*$", text):
        if re.sub(r"\s+", "", match[2]) == expected:
            candidates.add(match[1][3:])
    if len(candidates) != 1:
        raise ValueError("no unique generated PRE clock observation")
    enable = next(iter(candidates))
    clock_observation = {"sourceRegister": clock_row["flat"], "enableNode": enable,
                         "phase": "generated combinational PRE view"}
    clock_row.update(flat=enable, kind="comb")
    counts = {row["label"]: 0 for row in rows}
    assignments = {}
    wide_assignments = {}
    arrays = {}
    for row in rows:
        if row["kind"] == "comb":
            symbol = "_s_" + row["flat"].replace(".", "$")
            if not re.search(r"\bUInt<" + str(row["width"]) + r">\s+" + re.escape(symbol) + rf"\[{width}\];", text):
                raise ValueError(f"architectural comb field absent/wrong width: {row['flat']}")
            assignments[symbol] = row["label"]
            if row['width'] > 64: wide_assignments[symbol] = row['label']
        else:
            # Module paths refer to real register members. Capture immediately
            # after the injected/source scan has formed its PRE lane image.
            arrays[row["flat"]] = row["label"]
    writes = {"integer": 0, "floating": 0}
    # A loop-local value still exists at its assignment even when its former
    # scratch array is no longer written. Capture that value in the same lane.
    local_assignments = {}
    for flat, local in re.findall(r"// \[v2 lane-local\] (\S+) (\w+)", text):
        symbol = "_s_" + flat.replace(".", "$")
        if symbol in assignments:
            local_assignments[local] = assignments[symbol]
    local_assign_re = re.compile(r"^(\s*)(_v2_local_\w+)(?:\.val|\.ui\.val)?\s*=.*;\s*$")
    port_sites = {side: [0] * geometry[side + "_ports"] for side in writes}
    lines = []
    assign_re = re.compile(r"^(\s*)(_s_[^\s\[]+)\[(L|\d+)\](?:\.val|\.ui\.val)?\s*=.*;\s*$")
    for line in text.splitlines():
        if line.strip() == '#include "sint_pod_v2.h"':
            lines += [line, '#include "consumer_architecture_capture.h"']
            continue
        if wide_assignments and line.lstrip().startswith('{') and line.rstrip().endswith('}') and '.val[' in line:
            captures = []
            for symbol, label in wide_assignments.items():
                match = re.search(re.escape(symbol)+r'\[(L|\d+)\]\.val\[\d+\]\s*=', line)
                if match:
                    captures.append(f'CHISA_ARCH_SIGNAL({label}, {match[1]}, {symbol}[{match[1]}]);')
                    counts[label] += 1
            if captures:
                at = line.rfind('}')
                lines.append(line[:at]+' '.join(captures)+' '+line[at:])
                continue
        local_match = local_assign_re.match(line)
        if local_match and local_match[2] in local_assignments:
            label = local_assignments[local_match[2]]
            expression = line.strip().removesuffix(";")
            lines.append(f"{local_match[1]}({expression}, CHISA_ARCH_SIGNAL({label}, L, {local_match[2]}));")
            counts[label] += 1
            continue
        match = assign_re.match(line)
        if match and match[2] in assignments:
            label, lane = assignments[match[2]], match[3]
            expression = line.strip().removesuffix(";")
            lines.append(f"{match[1]}({expression}, CHISA_ARCH_SIGNAL({label}, {lane}, {match[2]}[{lane}]));")
            counts[label] += 1
            continue
        captured = False
        if "essent_inject_" in line or "essent_condhold_scan_" in line:
            for member, label in arrays.items():
                if re.search(r"(?:\(&|\()" + re.escape(member) + r"(?:\[0\],|,)", line):
                    stripped = line.strip()
                    if not stripped.endswith(";"): raise ValueError("unexpected source scan statement")
                    lines.append(line[:len(line)-len(line.lstrip())] +
                                 f"({stripped[:-1]}, CHISA_ARCH_ARRAY({label}, {member}));")
                    counts[label] += 1
                    captured = True
                    break
        if captured: continue
        # Capture only writes to persistent physical storage, not speculative
        # forwarding-image writes. The original guard and assignment remain.
        for floating, member in ((False, TILE + "core.iregfile.regfile"),
                                 (True, TILE + "core.fp_pipeline.fregfile.regfile")):
            pattern = (r"^(\s*if \(.*\) )(" + re.escape(member) +
                       r"\[essent_to_u64\((.+)\)\] = (.+));\s*$")
            write = re.match(pattern, line)
            if not write: continue
            if "[L]" not in write[3] or "[L]" not in write[4]:
                raise ValueError("unexpected register write lane expression")
            if configuration == "small":
                port = 0 if ("ll_wbarb" in write[3] or "REG_1_bits_addr" in write[3]) else 1
            else:
                # Use the real write-port identity, not its occurrence count.
                port_match = re.search(r"(?:\$|\.)[if]regfile(?:\$|\.)io_write_ports_(\d+)_(?:valid|bits_addr)", write[1]+" "+write[3])
                if port_match:
                    port = int(port_match[1])
                elif floating and ".fp_pipeline.REG_1_bits_addr[" in write[3]:
                    port = 0
                else:
                    raise ValueError(f"unrecognized physical write port: {line[:300]}")
            side = "floating" if floating else "integer"
            if port >= len(port_sites[side]):
                raise ValueError(f"physical write port outside {configuration} geometry")
            port_sites[side][port] += 1
            lines.append(f"{write[1]}(CHISA_ARCH_REGISTER_WRITE({str(floating).lower()}, {port}, L, "
                         f"essent_to_u64({write[3]}), {write[4]}), {write[2]});")
            writes["floating" if floating else "integer"] += 1
            captured = True
            break
        if not captured: lines.append(line)
    missing = [name for name, count in counts.items() if not count]
    expected_writes = {side: 2 * geometry[side + "_ports"] for side in writes}
    if missing or writes != expected_writes or any(count != 2 for ports in port_sites.values() for count in ports):
        raise ValueError(f"incomplete consumer architectural observations: missing={missing} writes={writes} ports={port_sites}")
    output.mkdir(parents=True, exist_ok=True)
    instrumented = "\n".join(lines) + "\n"
    (output / "TestHarness.h").write_text(instrumented)
    enum = "#pragma once\n#define CHISA_CONSUMER_ARCHITECTURE_SCHEMA 2\nnamespace chisa::boom_repcut::consumer_arch {\n"
    enum += f"inline constexpr unsigned kWidth = {width};\n"
    enum += f"inline constexpr unsigned kCapturedCommitWidth = {geometry['commit']};\n"
    enum += f"inline constexpr unsigned kCapturedRetirementFields = {11 if configuration != 'small' else 10};\n"
    enum += "enum Signal {\n"
    enum += "".join(f"  {row['label']} = {i},\n" for i, row in enumerate(rows))
    enum += f"  SignalCount = {len(rows)}\n}};\n}}\n"
    enum += 'namespace chisa::boom_repcut::consumer_arch {\n'
    enum += f'inline constexpr unsigned kObserverProbeBegin = {probe_begin}, kObserverProbeCount = {len(rows)-probe_begin};\n'
    enum += 'inline constexpr const char* kObserverProbeNames[] = {' + ', '.join(json.dumps(row['flat']) for row in rows[probe_begin:]) + ('""' if len(rows)==probe_begin else '') + '};\n}\n'
    (output / "consumer_architecture_fields.h").write_text(enum)
    (output / 'consumer_architecture_owners.h').write_text(
        '#pragma once\n#define CHISA_PARTITION_ARCHITECTURE_SCHEMA 0\n')
    report = {"scope": "actual consumer PRE/comb values and persistent PRF write operands",
              "configuration": configuration, "geometry": geometry, "width": width,
              "clockObservation": clock_observation,
              "sourceHeader": str(header), "sourceBytes": len(source_payload),
              "instrumentedBytes": len(instrumented),
              "fields": rows, "captureSites": counts, "physicalWriteSites": writes, "physicalWritePorts": port_sites,
              "modelValuesUsed": False, "runtimeValidation": "pending"}
    (output / "consumer-architecture-bindings.json").write_text(json.dumps(report, indent=2) + "\n")
    print(f"CONSUMER_ARCH_BINDINGS configuration={configuration} fields={len(rows)} PRF_write_sites={sum(writes.values())} missing=0")


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--header", type=Path, required=True)
    p.add_argument("--output", type=Path, required=True)
    p.add_argument("--width", type=int, required=True)
    p.add_argument("--configuration", choices=tuple(GEOMETRY), default="small")
    a = p.parse_args()
    instrument(a.header, a.output, a.width, a.configuration)


if __name__ == "__main__": main()
