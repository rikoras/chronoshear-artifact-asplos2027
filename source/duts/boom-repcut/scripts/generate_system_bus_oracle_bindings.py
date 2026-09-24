#!/usr/bin/env python3
"""Generate the exact SystemBus sidecar-to-manifest oracle contract.

The extracted scalar module keeps ordinary registers as nested C++ members,
but lowered memory read ports are expressions rather than stored members.
This generator records that distinction once: PRE register streams read the
current scalar state, while POST MPORT streams index the owning RAM with its
current dequeue pointer.
"""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


PREFIX = "ldut.subsystem_sbus."

# These eight streams were already state-derived before the complete sidecar
# landed.  Their existing batch slots are retained to avoid renumbering the
# large active-face batch, but their values are now read from this same exact
# SystemBus snapshot.  Every other SystemBus stream is registered by the new
# generated batch below.
LEGACY_KEYS = {
    "ldut_subsystem_sbus_system_bus_xbar_beatsLeft_4",
    "ldut_subsystem_sbus_system_bus_xbar_readys_mask",
    "ldut_subsystem_sbus_system_bus_xbar_readys_mask_1",
    "ldut_subsystem_sbus_system_bus_xbar_readys_mask_4",
    "ldut_subsystem_sbus_system_bus_xbar_state_4_0",
    "ldut_subsystem_sbus_system_bus_xbar_state_4_1",
    "ldut_subsystem_sbus_system_bus_xbar_state_4_2",
    "ldut_subsystem_sbus_system_bus_xbar_state__1",
}



def _load_banks(path):
    if path is None:
        return None
    import json
    with open(path) as handle:
        data = json.load(handle)
    return {b["traceKey"]: b for b in data.get("banks", [])}

def load_entries(path: Path, expected=173) -> list[dict]:
    manifest = json.loads(path.read_text(encoding="utf-8"))
    entries = [
        entry for entry in manifest.get("oracles", [])
        if str(entry.get("flat", "")).startswith(PREFIX)
    ]
    if len(entries) != expected:
        raise ValueError(
            f"expected the locked contract's 173 SystemBus streams, got {len(entries)}"
        )
    keys = [entry["traceKey"] for entry in entries]
    if len(set(keys)) != len(keys):
        raise ValueError("duplicate SystemBus trace key in manifest")
    missing_legacy = sorted(LEGACY_KEYS.difference(keys))
    if missing_legacy:
        raise ValueError("legacy SystemBus keys disappeared: " + ", ".join(missing_legacy))
    kinds = {entry.get("kind") for entry in entries}
    if not kinds.issubset({"reg", "comb"}):
        raise ValueError(f"unsupported SystemBus oracle kinds: {sorted(kinds)}")
    return entries


def mport_expression(relative: str) -> str | None:
    match = re.fullmatch(r"(.+)\.(ram_[^.]+)\.io_deq_bits_MPORT", relative)
    if match is None:
        return None
    queue_path, ram_name = match.groups()
    pointer = "value_1" if ".axi4buf." in relative else "deq_ptr_value"
    ram = f"state.{queue_path}.{ram_name}"
    index = f"word(state.{queue_path}.{pointer})"
    return f"word({ram}[{index} % (sizeof({ram}) / sizeof({ram}[0]))])"


def capture_expression(entry: dict, banks: dict | None = None) -> str:
    relative = entry["flat"].removeprefix(PREFIX)
    if relative == "fixer.flight__v2_bank_0_0":
        terms = [
            f"(word(state.fixer.flight__{index}) << {15 - index})"
            for index in range(16)
        ]
        return " | ".join(terms)
    mport = mport_expression(relative)
    if mport is not None:
        if entry.get("kind") != "comb":
            raise ValueError(f"MPORT is not combinational: {entry['flat']}")
        return mport
    if entry.get("kind") != "reg":
        raise ValueError(f"unsupported non-register SystemBus expression: {entry['flat']}")
    if banks is not None:
        bank = banks.get(entry["traceKey"])
        if bank is not None:
            terms = []
            for fld in bank["fields"]:
                src = fld["source"]
                rel = src.removeprefix(PREFIX)
                if rel == src:
                    raise ValueError(f"bank field outside module: {src}")
                width = fld["high"] - fld["low"] + 1
                mask = (1 << width) - 1
                terms.append(
                    f"((word(state.{rel}) & {hex(mask)}u) << {fld['low']})")
            return " | ".join(terms) if terms else "0"
        m = re.fullmatch(r"(.+)__w(\d+)", relative)
        if m is not None:
            base, wi = m.group(1), int(m.group(2))
            hi = 64 * wi + 63
            if wi > 0:
                return (f"static_cast<std::uint64_t>(state.{base}"
                        f".template bits<{hi}, {64 * wi}>().as_single_word())")
    # Wide scalar registers keep the unsuffixed member path in `flat`; the
    # manifest distinguishes their 64-bit trace streams with `word`.  Looking
    # only for a synthetic __wN suffix therefore aliases every upper word to
    # word zero (first exposed by Large's 128-bit TileLink C repeater data).
    word_index = int(entry.get("word", 0))
    if word_index > 0:
        hi = 64 * word_index + 63
        return (f"static_cast<std::uint64_t>(state.{relative}"
                f".template bits<{hi}, {64 * word_index}>().as_single_word())")
    return f"word(state.{relative})"


def capture_text(entries: list[dict], banks: dict | None = None) -> str:
    lines = [
        "// Auto-generated by generate_system_bus_oracle_bindings.py.",
        "// Manifest order is the public index contract.",
    ]
    for index, entry in enumerate(entries):
        lines.append(f"// [{index:3d}] {entry['traceKey']}")
        lines.append(
            f"system_bus_oracles[{index}] = {capture_expression(entry, banks)};"
        )
    return "\n".join(lines) + "\n"


def native_state_field(relative: str, wide: bool, word_index: int = 0) -> str:
    """Map an observation to software state. No RTL computation is imported."""
    relative = relative.replace("$$inst", "")
    suffix = re.fullmatch(r"(.+)__w(\d+)", relative)
    if suffix:
        relative, word_index = suffix[1], int(suffix[2])
    if word_index:
        if word_index != 1 or not relative.endswith("saved_data"):
            raise ValueError("unsupported upper-word native binding: " + relative)
        return native_state_field(relative, wide).removesuffix("data") + "data_hi"
    mmio = "coupler_to_port_named_mmio_port_axi4."
    if relative.startswith(mmio):
        member = relative[len(mmio):]
        match = re.fullmatch(r"tl2axi4\.count_(\d+)", member)
        if match: return f"s.t_count[{int(match[1])-1}]"
        match = re.fullmatch(r"tl2axi4\.write_(\d+)", member)
        if match: return f"s.t_write[{int(match[1])}]"
        fixed = {"tl2axi4.counter": "t_counter", "tl2axi4.doneAW": "t_doneAW",
                 "tl2axi4.r_holds_d": "t_r_holds_d", "tl2axi4.b_delay": "t_b_delay",
                 "tl2axi4.deq.maybe_full": "t_w_full", "tl2axi4.queue_arw_deq.maybe_full": "t_arw_full",
                 "axi4deint.deq_id": "d_deq_id", "axi4deint.locked": "d_locked"}
        if member in fixed: return "s." + fixed[member]
        match = re.fullmatch(r"axi4deint\.pending_count(?:_(\d+))?", member)
        if match: return f"s.d_pending[{int(match[1] or 0)}]"
        payload = {"addr": "addr", "burst": "burst", "cache": "cache", "id": "id", "len": "len",
                   "lock": "lock", "prot": "prot", "qos": "qos", "size": "size", "data": "data",
                   "last": "last", "resp": "resp", "strb": "strb", "wen": "wen",
                   "echo_tl_state_size": "echo_size", "echo_tl_state_source": "echo_source",
                   "tl_state_size": "size", "tl_state_source": "source"}
        for name, state in [("tl2axi4.deq.ram_", "t_w_ram"), ("tl2axi4.queue_arw_deq.ram_", "t_arw_ram")]:
            if member.startswith(name) and member[len(name):] in payload:
                return f"s.{state}.{payload[member[len(name):]]}"
        queue = None
        match = re.fullmatch(r"axi4buf\.bundle(?:In|Out)_0_(aw|ar|w|r|b)_deq\.(.+)", member)
        if match:
            queue, field, pointer = "s.b_" + match[1], match[2], "value_1"
        match = re.fullmatch(r"axi4deint\.qs_queue_(\d+)\.(.+)", member)
        if match:
            queue, field, pointer = f"s.d_qs[{int(match[1])}]", match[2], "deq_ptr"
        match = re.fullmatch(r"axi4yank\.QueueCompatibility(?:_(\d+))?\.(.+)", member)
        if match:
            index, ids = int(match[1] or 0), 9 if wide else 7
            queue, field, pointer = f"s.y_{'r' if index<ids else 'w'}q[{index%ids}]", match[2], "deq_ptr"
        if queue:
            control = {"maybe_full": "maybe_full", "value": "value", "value_1": "value_1",
                       "enq_ptr_value": "enq_ptr", "deq_ptr_value": "deq_ptr"}
            if field in control: return queue + "." + control[field]
            match = re.fullmatch(r"ram_(.+)\.io_deq_bits_MPORT", field)
            if match and match[1] in payload:
                return f"{queue}.ram[{queue}.{pointer}].{payload[match[1]]}"
            if member.startswith("axi4yank.") and field.startswith("ram_") and field[4:] in payload:
                return f"{queue}.ram[{queue}.{pointer}].{payload[field[4:]]}"
    match = re.fullmatch(r"fixer\.flight__(\d+)", relative)
    if match: return f"((s.fx_flight >> {int(match[1])}) & 1u)"
    fixed = {"fixer.a_first_counter": "fx_a_first_counter", "fixer.d_first_counter": "fx_d_first_counter",
             "fixer.stalls_id": "fx_stalls_id", "fixer.stalls_id_1": "fx_stalls_id_1"}
    if relative in fixed: return "s." + fixed[relative]
    match = re.fullmatch(r"system_bus_xbar\.(beatsLeft|readys_mask)(?:_(\d+))?", relative)
    if match:
        index=int(match[2] or 0)
        if index>4: raise ValueError("unknown arbiter index")
        return f"s.{'xa' if index<3 else 'xd'}[{index if index<3 else index-3}].{'beats_left' if match[1]=='beatsLeft' else 'mask'}"
    match = re.fullmatch(r"system_bus_xbar\.state_(\d*)_(\d+)", relative)
    if match:
        index=int(match[1] or 0)
        if index>4: raise ValueError("unknown arbiter state")
        return f"((s.{'xa' if index<3 else 'xd'}[{index if index<3 else index-3}].state >> {int(match[2])}) & 1u)"
    match = re.fullmatch(r"coupler_(from_bus_named_subsystem_fbus|to_bus_named_subsystem_cbus|to_bus_named_subsystem_l2|to_port_named_mmio_port_axi4)\.widget\.(.+)", relative)
    if match and wide:
        port, field = match.groups()
        if port.startswith("from_"):
            split, merge = "s.fbus_d_width", "s.fbus_a_width"
        else:
            index={"to_bus_named_subsystem_cbus":0,"to_bus_named_subsystem_l2":1,"to_port_named_mmio_port_axi4":2}[port]
            split,merge=f"s.a_width[{index}]",f"s.d_width[{index}]"
        if field == "count": return merge+".second"
        if field == "repeat_count": return split+".second"
        if field.startswith("repeated_repeater_1."):
            split="s.c_width";field=field.replace("repeated_repeater_1.","repeated_repeater.")
        if field=="repeated_repeater.full": return split+".holding"
        if field.startswith("repeated_repeater.saved_"):
            leaf=field.removeprefix("repeated_repeater.saved_")
            if leaf in {"address","data","opcode","size","source","param","mask","corrupt","denied","sink"}:
                return split+".saved."+leaf
            protection=leaf.removeprefix("user_amba_prot_")
            if leaf != protection and protection in {"bufferable","modifiable","readalloc","writealloc","privileged","secure","fetch"}:
                return split+".saved."+protection
        if field.endswith("_bits_data_rdata_0"): return merge+".lower"
        if field.endswith("_bits_data_rdata_written_once"): return merge+".lower_written"
        if port.startswith("from_"):
            if field=="bundleOut_0_a_bits_mask_rdata_0": return merge+".lower_mask"
            # Mask and data are saved on the same accepted first beat.
            if field=="bundleOut_0_a_bits_mask_rdata_written_once": return merge+".lower_written"
    raise ValueError("SystemBus field has no native binding: " + relative)


def native_capture_text(entries: list[dict], banks: dict | None = None) -> str:
    wide=any(".widget." in e["flat"] for e in entries)
    lines=["// Native software-state projection; observation geometry only."]
    for index,entry in enumerate(entries):
        relative=entry["flat"].removeprefix(PREFIX)
        bank=(banks or {}).get(entry["traceKey"])
        if relative=="fixer.flight__v2_bank_0_0":
            expression=" | ".join(f"(static_cast<std::uint64_t>((s.fx_flight >> {i}) & 1u) << {15-i})" for i in range(16))
        elif bank:
            expression=" | ".join(f"((static_cast<std::uint64_t>({native_state_field(f['source'].removeprefix(PREFIX),wide)}) & {hex((1<<(f['high']-f['low']+1))-1)}u) << {f['low']})" for f in bank['fields'])
            if not expression: raise ValueError("empty native observation bank")
        else:
            expression="static_cast<std::uint64_t>("+native_state_field(relative,wide,int(entry.get("word",0)))+")"
        lines += ["// "+entry["traceKey"],f"system_bus_oracles[{index}] = {expression};"]
    return "\n".join(lines)+"\n"


def bindings_text(entries: list[dict], expected_owned: int = 165) -> str:
    owned = [
        (index, entry) for index, entry in enumerate(entries)
        if entry["traceKey"] not in LEGACY_KEYS
    ]
    if len(owned) != expected_owned:
        raise ValueError(f"expected 165 newly owned SystemBus streams, got {len(owned)}")

    lines = [
        "// Auto-generated by generate_system_bus_oracle_bindings.py.",
        "// The eight pre-existing xbar slots remain in their original batches.",
        f"static constexpr std::array<std::size_t, {len(owned)}>",
        "    kSystemBusSidecarOracleIndices = {",
    ]
    for offset in range(0, len(owned), 12):
        values = ", ".join(str(index) for index, _ in owned[offset:offset + 12])
        lines.append(f"        {values},")
    lines += [
        "};",
        "",
        "void sample_batch_system_bus_sidecar(const SystemGuider& model,",
        "                                     BatchSlots slots) {",
        "  const auto& values = model.fabric().system_bus_oracles();",
        "  for (std::size_t index = 0; index < kSystemBusSidecarOracleIndices.size();",
        "       ++index)",
        "    batch_store(slots, index, values[kSystemBusSidecarOracleIndices[index]]);",
        "}",
        "",
        "void register_system_bus_sidecar_bindings() {",
        "  ModelBindings& bindings = ModelBindings::instance();",
    ]
    for owned_index, (_, entry) in enumerate(owned):
        method = (
            "reserve_sampled_combinational"
            if entry["kind"] == "comb" else "reserve_sampled"
        )
        prefix = "  const int base = " if owned_index == 0 else "  "
        lines.append(f"{prefix}bindings.{method}(")
        lines.append(f"      \"{entry['traceKey']}\");")
    lines += [
        "  bindings.add_batch_sampler(sample_batch_system_bus_sidecar, base);",
        "}",
    ]
    return "\n".join(lines) + "\n"


def write_or_check(path: Path, expected: str, check: bool) -> bool:
    actual = path.read_text(encoding="utf-8") if path.is_file() else None
    if actual == expected:
        return True
    if check:
        print(f"stale generated file: {path}")
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(expected, encoding="utf-8")
    print(f"wrote {path}")
    return True


def main() -> int:
    root = Path(__file__).resolve().parents[3]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--manifest", type=Path,
        default=root / "out/repcut-ae/chisa-small-v2-dead-pruned-extern/oracle_manifest.json",
    )
    parser.add_argument(
        "--capture-output", type=Path,
        default=root / "reference_models/boom-system/generated/system_bus_oracle_capture.inc",
    )
    parser.add_argument(
        "--bindings-output", type=Path,
        default=root / "reference_models/boom-system/generated/system_bus_oracle_bindings.inc",
    )
    parser.add_argument("--native-capture-output", type=Path,
                        default=root / "reference_models/boom-system/generated/system_bus_native_capture.inc")
    parser.add_argument("--expected-streams", type=int, default=173)
    parser.add_argument("--expected-owned", type=int, default=165)
    parser.add_argument("--bank-manifest", type=Path, default=None)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()

    try:
        entries = load_entries(args.manifest, args.expected_streams)
        good = write_or_check(
            args.capture_output, capture_text(entries, _load_banks(args.bank_manifest)), args.check
        )
        good &= write_or_check(args.native_capture_output,
                               native_capture_text(entries, _load_banks(args.bank_manifest)), args.check)
        good &= write_or_check(
            args.bindings_output, bindings_text(entries, args.expected_owned), args.check
        )
    except (OSError, KeyError, ValueError, json.JSONDecodeError) as error:
        parser.error(str(error))
    return 0 if good else 1


if __name__ == "__main__":
    raise SystemExit(main())
