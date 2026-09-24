#!/usr/bin/env python3
"""Final record schema only: no model reads, samplers, caches or coverage.

Uses the same field grouping as Small without invoking gen_image.main(), whose
Small reset/ownership rules and shared predictor-file outputs do not apply.
Consumer lane identity and expansion offsets are preserved verbatim.
"""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import re
import sys

sys.dont_write_bytecode = True
import gen_image as schema
from generate_system_oracle_record import render_header
from generate_system_oracle_writer import layout_hash


def write_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def predictor_layouts():
    root = Path(__file__).resolve().parents[3]
    small = (root / "reference_models/boom_model/small/generated/image.h").read_text()
    native = (root / "reference_models/boom_model/common/predictor_bank_image.h").read_text()
    sizes = {name: int(size) for name, size in re.findall(r"sizeof\((\w+)\) == (\d+)", small)}
    bases = {}
    for section, kind in (("Regs", "reg"), ("Combs", "comb")):
        body = re.search(r"struct alignas\(64\) " + section + r" \{(.*?)\n\};", small, re.S)[1]
        offset = 0 if kind == "reg" else sizes["Regs"]
        for typename, member in re.findall(r"\b(\w+) (\w+);", body):
            if member == "frontendBpd": bases[kind] = offset
            offset += sizes[typename]
    result = {}
    for kind, name in (("reg", "PredictorBankRegisters"), ("comb", "PredictorBankPorts")):
        body = re.search(r"struct " + name + r" \{(.*?)\n\};", native, re.S)[1]
        fields, offset = {}, 0
        for bits, member, count in re.findall(r"std::uint(8|16|32|64)_t (\w+)(?:\[(\d+)\])?;", body):
            width = int(bits)//8; number = int(count) if count else 1
            for i in range(number): fields[offset+i*width] = (member+(f"[{i}]" if count else ""), width)
            offset += number*width
        expected = sizes["FrontendBpd" + ("C" if kind == "comb" else "")]
        if offset != expected: raise ValueError("predictor native layout changed")
        matches = {}
        for off, elem, width, key in re.findall(r"\{(\d+)u, (\d+)u, (\d+)u, \d+u\},\s*// \d+ (\S+)", small):
            if "_frontend_bpd_banked_predictors_0_" not in key: continue
            local = int(off)-bases[kind]
            if local not in fields or fields[local][1] != int(elem): continue
            matches[key] = (local, fields[local][0], int(elem), int(width))
        result[kind] = (name, expected, matches)
    return result


def fold_record(fields):
    # Large integer IQ has two equally wide pieces in bank 0. The generic
    # Small folder groups those pieces per slot; keep each piece a column
    # here so hot issue movement can address typed arrays without scatter.
    remaining, columns = [], {}
    for field in fields:
        match = re.fullmatch(r"(fp_issue_unit_)?slots_(\d+)_(slot_uopbank_.+)", field.name)
        if not match:
            remaining.append(field)
            continue
        prefix, index, suffix = match.groups()
        name = (prefix or "") + "slots_" + suffix
        key = (name, field.elem)
        index = int(index)
        array = columns.setdefault(key, schema.ArrayField(name, field.elem, 0))
        if index in array.members:
            raise ValueError("duplicate IQ slot field: " + field.name)
        array.count = max(array.count, index + 1)
        array.members[index] = field
    result = schema.fold(remaining) + list(columns.values())
    result.sort(key=lambda field: (-field.elem, schema.natural_key(field.name)))
    # A Large packed bank may have both u64 and u32 pieces with one base
    # name. Keep distinct C++ columns instead of emitting duplicate members.
    counts = collections.Counter(field.name for field in result)
    for field in result:
        if counts[field.name] > 1:
            field.name += f"_u{8*field.elem}"
    if len({field.name for field in result}) != len(result):
        raise ValueError("folded record field collision")
    return result


def native_predictor_field(entry, native_banks):
    key=entry['traceKey']
    bank_match=re.search(r'_banked_predictors_([01])_',key)
    original=re.sub(r'_banked_predictors_[01]_','_banked_predictors_0_',key)
    native=native_banks[entry['kind']][2].get(original)
    sized_index=native and native[3]==entry['width']+1 and any(
        marker in original for marker in ('_s1_idx','_s1_update_idx','_components_3_meta__v2_bank_',
                                          '_components_2_meta_','_columns_'))
    if bank_match and native and native[2]==entry['elemBytes'] and (native[3]==entry['width'] or sized_index):
        return int(bank_match[1]),native
    return None


def generate(manifest, output, configuration='large', geometry=None, base_manifest=None):
    if geometry is None:
        raise ValueError('record generation requires the compiled model geometry')
    bank_count = geometry['banks']
    entries = json.loads(manifest.read_text())["oracles"]
    schema.validate_oracles(entries)
    schema.BANK_STRUCTS.clear()
    schema.LVALUES.clear()
    schema.LNAMES.clear()
    groups = collections.OrderedDict(
        ((name, kind), []) for _, name in schema.GROUPS for kind in ("reg", "comb"))
    # A contract that extends a base contract (a partition kernel's, or the
    # union of several) keeps the base's members exactly: the base lanes are
    # folded in the base's own order, and every lane the base does not carry
    # goes to a <Group>Cut struct appended after the base members. Model code
    # that names base members compiles unchanged against every such layout;
    # the added lanes are written by bit address.
    # A base lane the contract does not carry keeps its member as a hole: the
    # model still writes it, no consumer lane reads it.
    base_order, entries_all, holes = None, list(entries), 0
    if base_manifest is not None:
        base_entries = json.loads(base_manifest.read_text())["oracles"]
        base_order = {(e["flat"], e.get("word", 0)): i for i, e in enumerate(base_entries)}
        present = {(e["flat"], e.get("word", 0)): (e["elemBytes"], e["width"], e["kind"]) for e in entries}
        for e in base_entries:
            key = (e["flat"], e.get("word", 0))
            if key not in present:
                entries_all.append(dict(e)); holes += 1
            elif present[key] != (e["elemBytes"], e["width"], e["kind"]):
                raise ValueError("contract reshapes the base lane " + e["flat"])
    cut_groups = collections.OrderedDict(
        ((name, kind), []) for _, name in schema.GROUPS for kind in ("reg", "comb"))
    for lane, entry in enumerate(entries_all):
        tail = schema.tail_of(entry["flat"])
        prefix, group = schema.group_of(tail)
        rest = tail[len(prefix):].lstrip(".") if prefix else tail
        field = schema.Field(schema.sanitize(rest), entry["elemBytes"], entry["width"], entry["flat"], lane)
        key = (entry["flat"], entry.get("word", 0))
        if base_order is not None and key not in base_order:
            cut_groups[group, entry["kind"]].append(field)
        else:
            groups[group, entry["kind"]].append(field)
    if base_order is not None:
        for fields in groups.values():
            fields.sort(key=lambda f: base_order[(entries_all[f.idx]["flat"], entries_all[f.idx].get("word", 0))])
    for fields in list(groups.values()) + list(cut_groups.values()):
        names = collections.Counter(f.name for f in fields)
        serial = collections.Counter()
        for field in fields:
            if names[field.name] > 1:
                serial[field.name] += 1
                field.name += "_" + str(serial[field.name])
    native_banks = predictor_layouts()
    native_cut_aliases=[]
    # The complete native bank is already part of the record even when a
    # particular contract does not read all of it. A new cut can retain an
    # existing native field: bind that same storage, rather than allocating
    # an unwritten duplicate in FrontendBpdCut.
    for kind in ('reg','comb'):
        remaining=[]
        for field in cut_groups['FrontendBpd',kind]:
            entry=entries_all[field.idx]
            match=native_predictor_field(entry,native_banks)
            if match is None:remaining.append(field);continue
            groups['FrontendBpd',kind].append(field)
            native_cut_aliases.append({'traceKey':entry['traceKey'],'bank':match[0],
                                      'member':match[1][1],'native_offset':match[1][0]})
        cut_groups['FrontendBpd',kind]=remaining
    lines = [
        "// Generated final record layout; owns no provider coverage claim.",
        "#pragma once", "#include <cstddef>", "#include <cstdint>",
        f'#if !defined(BOOM_GUIDER_CFG_{configuration.upper()}BOOM_RC)',
        '#error "record/configuration mismatch"', '#endif',
        '#include "predictor_bank_image.h"',
        "namespace chisa::boom_model::wide::contract {",
        f"inline constexpr std::size_t kLanes = {len(entries)};",
    ]
    offsets, members, bases, sizes = {}, {"reg": [], "comb": []}, {}, {}
    for (group, kind), fields in groups.items():
        if not fields:
            continue
        name = group + ("C" if kind == "comb" else "")
        if group == "FrontendBpd":
            typename, bank_size, matches = native_banks[kind]
            extra = []
            for field in fields:
                entry = entries_all[field.idx]
                match=native_predictor_field(entry,native_banks)
                if match is not None:
                    bank,native=match;local,member,_,_=native
                    if bank >= bank_count: raise ValueError('predictor bank exceeds model geometry')
                    offsets[field.idx] = ((group,kind),bank*bank_size+local)
                    schema.LVALUES[field.idx] = f"bank[{bank}].{member}"
                else: extra.append(field)
            extra_offsets = {}
            extra_size = schema.emit_struct(lines, name+"Extra", fold_record(extra), extra_offsets, (group,kind)) if extra else 0
            for lane, (gk, local) in extra_offsets.items():
                offsets[lane] = (gk,bank_count*bank_size+local)
                schema.LVALUES[lane] = "extra." + schema.LVALUES[lane]
            size = bank_count*bank_size+extra_size
            extra_member = f" {name}Extra extra;" if extra else ""
            lines += [f"struct {name} {{ chisa::boom_model::{typename} bank[{bank_count}];{extra_member} }};",
                      f"static_assert(sizeof({name}) == {size});"]
        else:
            size = schema.emit_struct(lines, name, fold_record(fields), offsets, (group, kind))
        members[kind].append((group, name, group[0].lower() + group[1:], size))
    for (group, kind), fields in cut_groups.items():
        if not fields:
            continue
        cut = group + "Cut"
        name = cut + ("C" if kind == "comb" else "")
        size = schema.emit_struct(lines, name, fold_record(fields), offsets, (cut, kind))
        members[kind].append((cut, name, cut[0].lower() + cut[1:], size))
    if schema.BANK_STRUCTS:
        raise ValueError("Wide schema unexpectedly selected Small's complete predictor alias")
    # Groups are laid out in runs by the thread that writes them: the core
    # (Core*, Lsu*), the frontend (Frontend*) and the memory side (the rest),
    # base groups first and then the partition-cut groups in the same order.
    # Each run starts on a 64-byte line, so no cache line is written by two
    # threads (a frontend worker commits its lanes while the calling thread
    # publishes the core's and the memory side's) and a run can be copied
    # into the image by its own thread (see FrontendHandoff).
    def owner_of(group):
        base = group[:-3] if group.endswith("Cut") else group
        if base.startswith("Core") or base.startswith("Lsu"): return "Core"
        if base.startswith("Frontend"): return "Frontend"
        return "Memory"
    runs = {}
    for kind, name in (("reg", "Registers"), ("comb", "Combinational")):
        lines.append(f"struct alignas(64) {name} {{")
        offset, run, pads = 0, None, 0
        for group, typename, member, size in members[kind]:
            this_run = (owner_of(group), group.endswith("Cut"))
            if this_run != run:
                if run is not None:
                    runs[kind, run] = (runs[kind, run][0], offset)
                    padding = -offset % 64
                    if padding:
                        lines.append(f"  std::uint8_t pad_{pads}[{padding}];")
                        pads += 1
                        offset += padding
                run = this_run
                runs[kind, run] = (offset, offset)
            bases[group, kind] = offset
            lines.append(f"  {typename} {member};")
            offset += size
        if run is not None:
            runs[kind, run] = (runs[kind, run][0], offset)
        padding = -offset % 64
        if padding:
            lines.append(f"  std::uint8_t padding[{padding}];")
        sizes[kind] = offset + padding
        lines.extend(["};", f"static_assert(sizeof({name}) == {sizes[kind]});"])
    run_names = [("reg", ("Core", False)), ("reg", ("Frontend", False)), ("reg", ("Memory", False)),
                 ("reg", ("Core", True)), ("reg", ("Frontend", True)), ("reg", ("Memory", True)),
                 ("comb", ("Core", False)), ("comb", ("Frontend", False)), ("comb", ("Memory", False))]
    run_begin, run_end = [], []
    for kind, run in run_names:
        begin, end = runs.get((kind, run), (0, 0))
        shift = sizes["reg"] if kind == "comb" else 0
        run_begin.append(begin + shift if begin != end else 0)
        run_end.append(end + shift if begin != end else 0)
    lines += ["struct alignas(64) Image { Registers r; Combinational c; };",
              "// Image byte ranges written by one thread each (64-byte aligned; empty runs are 0..0).",
              "enum OwnerRun : unsigned { kRegCore, kRegFrontend, kRegMemory, kRegCoreCut, kRegFrontendCut,",
              "                           kRegMemoryCut, kCombCore, kCombFrontend, kCombMemory, kOwnerRunCount };",
              "inline constexpr std::size_t kOwnerRunBegin[kOwnerRunCount] = {" + ", ".join(map(str, run_begin)) + "};",
              "inline constexpr std::size_t kOwnerRunEnd[kOwnerRunCount] = {" + ", ".join(map(str, run_end)) + "};",
              f"inline constexpr std::size_t kRegBytes = {sizes['reg']};",
              f"inline constexpr std::size_t kBytes = {sum(sizes.values())};",
              "static_assert(sizeof(Image) == kBytes);",
              "struct Lane { std::uint16_t offset; std::uint8_t bytes, width; std::uint32_t block; };",
              "inline constexpr Lane lanes[kLanes] = {"]
    layout = {"offsets": [0] * len(entries), "hash": layout_hash(entries)}
    lanes = []
    for lane, entry in enumerate(entries):
        (group, kind), local = offsets[lane]
        offset = bases[group, kind] + local + (sizes["reg"] if kind == "comb" else 0)
        layout["offsets"][lane] = offset
        member = group[0].lower() + group[1:]
        lvalue = f"{'r' if kind == 'reg' else 'c'}.{member}.{schema.LVALUES[lane]}"
        lines.append(f"  {{{offset}, {entry['elemBytes']}, {entry['width']}, {entry['blockOffset']}}},")
        lanes.append(dict(entry, lane=lane, recordOffset=offset, recordField=lvalue))
    lines += ["};", "#ifdef CHISA_RECORD_LAYOUT_CHECK"]
    for lane in lanes:
        lines.append(f"static_assert(offsetof(Image, {lane['recordField']}) == {lane['recordOffset']}, \"lane {lane['lane']} storage\");")
    lines += ["#endif", "}  // namespace chisa::boom_model::wide::contract", ""]
    layout["bytes"] = layout["padded"] = sum(sizes.values())
    layout["chunks"] = layout["padded"] // 64
    layout["byteToLane"] = [0xffff] * layout["padded"]
    for lane, entry in enumerate(entries):
        for byte in range(entry["elemBytes"]):
            offset = layout["offsets"][lane] + byte
            if layout["byteToLane"][offset] != 0xffff:
                raise ValueError("overlapping record field: " + entry["traceKey"])
            layout["byteToLane"][offset] = lane
    layout["chunkFirstLane"], layout["chunkLastLane"] = [], []
    for start in range(0, layout["padded"], 64):
        chunk = [lane for lane in layout["byteToLane"][start:start+64] if lane != 0xffff]
        layout["chunkFirstLane"].append(min(chunk) if chunk else 0xffff)
        layout["chunkLastLane"].append(max(chunk) if chunk else 0xffff)
    output.mkdir(parents=True, exist_ok=True)
    write_changed(output/'native-cut-aliases.json',json.dumps(native_cut_aliases,indent=2)+'\n')
    typed = "\n".join(lines)
    # The shared divider transition takes a bool reference for this actual
    # one-bit state. Keep it in the final record, with its natural byte size.
    typed = re.sub(r'std::uint8_t (\w*div_div_neg_out);', r'bool \1;', typed)
    write_changed((output / "contract.h"), typed)
    write_changed((output / "system_oracle_record.h"), render_header(entries, layout))
    write_changed((output / "contract-layout.json"), json.dumps({
        "schema": 1, "purpose": "final-record-layout-only", "providerCoverage": "not-claimed",
        "configuration": configuration, "geometry": geometry,
        "manifestSha256": hashlib.sha256(manifest.read_bytes()).hexdigest(),
        "lanes": len(entries), "registerBytes": sizes["reg"], "bytes": sum(sizes.values()),
        "oracles": lanes,
    }, indent=2) + "\n")
    print(f"{configuration} final record: {len(entries)} lanes, {sum(sizes.values())} bytes; coverage not claimed"
          + (f"; base members kept, {holes} base lanes absent, {sum(len(v) for v in cut_groups.values())} cut lanes appended" if base_order is not None else ""))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--config", choices=['medium','large'], required=True)
    parser.add_argument("--geometry", type=Path, required=True)
    parser.add_argument("--base-manifest", type=Path, help="base contract whose members this layout keeps verbatim")
    args = parser.parse_args()
    generate(args.manifest, args.output, args.config, json.loads(args.geometry.read_text()), args.base_manifest)
