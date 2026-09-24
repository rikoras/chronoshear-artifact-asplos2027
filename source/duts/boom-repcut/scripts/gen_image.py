#!/usr/bin/env python3
"""Contract image for the rewritten reference model (model).

Reads the oracle manifest and emits a C++ header:
  * one struct per component group, register streams and combinational
    streams in separate structs (`CoreRob` / `CoreRobC`), so the two
    sections of the image are each contiguous: after step t the register
    section is the record of cycle t+1 and the combinational section is
    the record of cycle t;
  * fields at their natural element width with the RTL packing kept;
    per-entry families (`slots_3_p1`, `state_rob_exception_r12`,
    `stq_4_bits_addr_bits`, ...) are folded into index-ordered arrays so
    the model can treat them as columns (holes for indices the manifest
    does not select stay as unmapped bytes);
  * the `Image` struct (`r` = registers, `c` = combinational) and the
    per-manifest-index table the transposer needs.

usage: gen_image.py MANIFEST OUT.h

With --record-view --configuration small|large --record-layout image|packed,
emit named, typed fields over an existing OracleRecord instead. This mode
allocates no state and emits no ownership registration or reset logic.
"""
import argparse, json, re, sys, collections, os, pathlib
BANK_STRUCTS = []

GROUPS = [
    ("core.rob", "CoreRob"), ("core.int_issue_unit", "CoreIntIq"), ("core.mem_issue_unit", "CoreMemIq"),
    ("core.rename_stage", "CoreRename"), ("core.fp_rename_stage", "CoreFpRename"), ("core.csr_exe_unit", "CoreCsrExe"),
    ("core.iregister_read", "CoreIregRead"), ("core.csr", "CoreCsr"), ("core.fp_pipeline", "CoreFp"), ("core", "CoreMisc"),
    ("lsu.dtlb", "LsuDtlb"), ("lsu", "Lsu"),
    ("frontend.bpd", "FrontendBpd"), ("frontend.tlb", "FrontendTlb"), ("frontend.ftq", "FrontendFtq"),
    ("frontend.f4_btb_corrections", "FrontendF4Corr"), ("frontend.icache", "FrontendIcache"), ("frontend", "FrontendMisc"),
    ("dcache.mshrs", "DcacheMshrs"), ("dcache", "Dcache"),
    ("ldut.subsystem_mbus", "UncoreMbus"), ("ldut.subsystem_sbus", "UncoreSbus"), ("ldut.subsystem_fbus", "UncoreFbus"),
    ("ldut.subsystem_cbus", "UncoreCbus"), ("ldut.subsystem_l2_wrapper", "UncoreL2"), ("ldut.debug", "UncoreDebug"),
    ("ldut.tile_prci_domain", "UncoreTile"), ("ldut", "UncoreMisc"),
    ("mem", "MemAxi"), ("mmio_mem", "MmioAxi"), ("ptw", "Ptw"), ("tlMasterXbar", "Xbar"), ("", "Top"),
]

def tail_of(flat):
    return flat.split("boom_tile.")[-1] if "boom_tile." in flat else flat

def group_of(tail):
    for prefix, name in GROUPS:
        if prefix == "":
            return prefix, name
        if tail == prefix or tail.startswith(prefix + "."):
            return prefix, name
    return "", "Top"

def sanitize(s):
    s = s.replace("$$inst", "inst").replace("__v2_bank_", "bank_").replace("__v2_state_", "state_")
    s = re.sub(r"[^A-Za-z0-9_]", "_", s)
    s = re.sub(r"_+", "_", s).strip("_")
    if not s or s[0].isdigit(): s = "f_" + s
    return s

def ctype(b):
    return {1: "std::uint8_t", 2: "std::uint16_t", 4: "std::uint32_t", 8: "std::uint64_t"}[b]

def natural_key(s):
    return [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", s)]

def split_index(name, first=False):
    """(base, index) for a foldable family member, else (None, None).

    The index is the last numeric token (`slots_3_p1` -> slots_p1[3],
    `state_rob_exception_r12` -> ..._r[12]).  With `first`, the first
    numeric token that is followed by a non-numeric token is used instead
    (`slots_3_slot_uopbank_2_0` -> slots_slot_uopbank_2_0[3]); the caller
    falls back to it when the last-numeric grouping is a singleton."""
    toks = name.split("_")
    if first:
        for i in range(len(toks) - 1):
            t = toks[i]
            if t.isdigit() and not toks[i + 1].isdigit():
                if i > 0 and toks[i - 1] == "REG":
                    return None, None
                return "_".join(toks[:i] + toks[i + 1:]), int(t)
        return None, None
    for i in range(len(toks) - 1, -1, -1):
        t = toks[i]
        if t.isdigit():
            if i > 0 and toks[i - 1] == "REG":
                return None, None           # REG_<n> is a compiler counter, not an index
            base = "_".join(toks[:i] + toks[i + 1:])
            return base, int(t)
        m = re.fullmatch(r"r(\d+)", t)
        if m and i == len(toks) - 1:
            base = "_".join(toks[:i] + ["r"])
            return base, int(m.group(1))
    return None, None

class Field:
    def __init__(self, name, elem, width, flat, idx):
        self.name, self.elem, self.width, self.flat, self.idx = name, elem, width, flat, idx

class ArrayField:
    def __init__(self, base, elem, count):
        self.name, self.elem, self.count = base, elem, count
        self.members = {}   # index -> Field

def fold(items):
    """items: list of Field. Returns list of Field|ArrayField."""
    by_base = collections.defaultdict(list)
    scalars = []
    for f in items:
        base, index = split_index(f.name)
        if base is None:
            scalars.append(f)
        else:
            by_base[(base, f.elem)].append((index, f))
    # singleton last-numeric groups retry with the first numeric token
    retry = [(k, v) for k, v in by_base.items() if len(v) == 1]
    for k, v in retry:
        f = v[0][1]
        base, index = split_index(f.name, first=True)
        if base is None or (base, f.elem) == k:
            continue
        del by_base[k]
        by_base[(base, f.elem)].append((index, f))
    out = []
    used_scalar = set()
    scalar_by_name = {(f.name, f.elem): f for f in scalars}
    for (base, elem), members in by_base.items():
        indices = [i for i, _ in members]
        if len(members) >= 2 and max(indices) <= 63 and len(set(indices)) == len(indices):
            arr = ArrayField(base, elem, max(indices) + 1)
            for i, f in members: arr.members[i] = f
            # a scalar with the base's own name is index 0 (value_hi + value_hi_1..3)
            s = scalar_by_name.get((base, elem))
            if s is not None and 0 not in arr.members:
                arr.members[0] = s
                used_scalar.add(id(s))
            out.append(arr)
        else:
            out.extend(f for _, f in members)
    out.extend(s for s in scalars if id(s) not in used_scalar)
    out.sort(key=lambda f: (-f.elem, natural_key(f.name)))
    return out

LVALUES = {}   # lane index -> member expression inside its group struct
LNAMES = {}    # lane index -> the lane's own (pre-fold) field name

def emit_struct(lines, sname, fields, offsets, group_key):
    block_start = len(lines)
    lines.append(f"struct {sname} {{")
    off = 0
    for f in fields:
        if isinstance(f, ArrayField):
            present = sorted(f.members)
            lines.append(f"  {ctype(f.elem)} {f.name}[{f.count}];  // lanes at " +
                         (",".join(str(i) for i in present) if len(present) < f.count else "every index") +
                         f"; w={f.members[present[0]].width} {f.members[present[0]].flat}")
            for i, m in f.members.items():
                offsets[m.idx] = (group_key, off + i * f.elem)
                LVALUES[m.idx] = f"{f.name}[{i}]"
                LNAMES[m.idx] = m.name
            off += f.count * f.elem
        else:
            lines.append(f"  {ctype(f.elem)} {f.name};  // w={f.width} {f.flat}")
            offsets[f.idx] = (group_key, off)
            LVALUES[f.idx] = f.name
            LNAMES[f.idx] = f.name
            off += f.elem
    pad = (-off) % 8
    if pad: lines.append(f"  std::uint8_t pad_[{pad}];")
    off += pad
    lines.append("};")
    lines.append(f"static_assert(sizeof({sname}) == {off}, \"{sname} layout\");")
    lines.append("")
    if sname in ("FrontendBpd", "FrontendBpdC"):
        atoms = [m for f in fields for m in (f.members.values() if isinstance(f, ArrayField) else (f,))]
        if not any(".banked_predictors_1." in m.flat for m in atoms):
            shared = "PredictorBankRegisters" if sname == "FrontendBpd" else "PredictorBankPorts"
            BANK_STRUCTS.extend(line.replace(sname, shared) for line in lines[block_start:])
            lines[block_start:] = [f"using {sname} = {shared};",
                                  f'static_assert(sizeof({sname}) == {off}, "{sname} layout");', ""]
    return off

# Streams the model writes straight into the image (no sampler): the core
# groups, except the cold-FPU sidecar families, the memory-owned DTLB-ready
# copies, the two structural constants and the true-combinational read ports
# that are patched into the current position as predicted lanes.
OWNED_GROUPS = {"CoreRob", "CoreIntIq", "CoreMemIq", "CoreRename", "CoreFpRename", "CoreCsrExe",
                "CoreIregRead", "CoreCsr", "CoreFp", "CoreMisc", "Lsu"}
OWNED_EXCLUDE_SUBSTR = (".fpiu_unit.fdivsqrt.divsqrt.", ".fpiu_unit.fpu.fpu.")
OWNED_EXCLUDE_TAIL = {"lsu.REG", "lsu.REG_1", "core.dec_finished_mask",
                      "core.rob.__v2_state_rob_predicated.r0",
                      "core.rob.__v2_state_rob_bsy.r3", "core.rob.__v2_state_rob_bsy.r4",
                      "core.rob.__v2_state_rob_bsy.r5", "core.rob.__v2_state_rob_uop.r2",
                      "core.rob.__v2_state_rob_uop.r3", "core.rob.__v2_state_rob_uop.r4",
                      "lsu.can_fire_load_incoming_0", "lsu.will_fire_load_wakeup_0"}

def image_owned(flat, gname):
    if gname not in OWNED_GROUPS: return False
    if any(x in flat for x in OWNED_EXCLUDE_SUBSTR): return False
    if tail_of(flat) in OWNED_EXCLUDE_TAIL: return False
    return True

def validate_oracles(oracles):
    """Validate field identity before assigning any image/record bytes.

    Absent word metadata is the historical one-word Small schema. Wide
    streams must carry every word and identify it explicitly in traceKey.
    This describes storage only; it does not claim any model owns a lane.
    """
    if not isinstance(oracles, list) or not oracles or len(oracles) >= 0xffff:
        raise ValueError("image needs 1..65534 oracle lanes")
    keys, identities, words_by_field = set(), set(), collections.defaultdict(list)
    for o in oracles:
        for name in ("flat", "traceKey"):
            if not isinstance(o.get(name), str) or not o[name]:
                raise ValueError(f"invalid oracle {name}")
        key = o["traceKey"]
        if key in keys:
            raise ValueError(f"duplicate traceKey: {key}")
        keys.add(key)
        if o.get("kind") not in ("reg", "comb"):
            raise ValueError(f"invalid kind: {key}")
        eb, width = o.get("elemBytes"), o.get("width")
        if type(eb) is not int or eb not in (1, 2, 4, 8) or type(width) is not int or not 1 <= width <= 8 * eb:
            raise ValueError(f"invalid element size/width: {key}")
        word, words = o.get("word", 0), o.get("words", 1)
        if type(word) is not int or type(words) is not int or not 0 <= word < words <= 255:
            raise ValueError(f"invalid word/words: {key}")
        if words > 1:
            suffix = re.search(r"__w(\d+)$", key)
            if suffix is None or int(suffix[1]) != word:
                raise ValueError(f"word suffix disagrees with word index: {key}")
            if word < words - 1 and width != 64:
                raise ValueError(f"non-final wide word is not 64 bits: {key}")
        identity = (o["flat"], o["kind"], word)
        if identity in identities:
            raise ValueError(f"duplicate flat/kind/word: {key}")
        identities.add(identity)
        words_by_field[identity[:2]].append((word, words))
    for field, parts in words_by_field.items():
        count = parts[0][1]
        if any(n != count for _, n in parts) or sorted(i for i, _ in parts) != list(range(count)):
            raise ValueError(f"missing or inconsistent word family: {field}")

def compute_layout(oracles):
    """Lane -> (byte offset inside the image, elem bytes) plus the image size,
    by exactly the rules main() renders.  Used by generate_system_oracle_record.py
    so the bindings' record and the model image are one layout."""
    validate_oracles(oracles)
    groups = collections.OrderedDict(((name, kind), []) for _, name in GROUPS for kind in ("reg", "comb"))
    for idx, o in enumerate(oracles):
        tail = tail_of(o["flat"])
        prefix, gname = group_of(tail)
        rest = tail[len(prefix):].lstrip(".") if prefix else tail
        groups[(gname, o["kind"])].append(Field(sanitize(rest), o["elemBytes"], o["width"], o["flat"], idx))
    for key, items in groups.items():
        seen = collections.Counter(f.name for f in items)
        dup = collections.Counter()
        for f in items:
            if seen[f.name] > 1:
                dup[f.name] += 1
                f.name = f"{f.name}_{dup[f.name]}"
    offsets = {}
    sizes = {}
    order = []
    for (gname, kind), items in groups.items():
        if not items: continue
        lines = []
        size = emit_struct(lines, gname, fold(items), offsets, (gname, kind))
        sizes[(gname, kind)] = size
        order.append((gname, kind))
    section_offset = {}
    section_bytes = {}
    for kind in ("reg", "comb"):
        goff = 0
        for gk in order:
            if gk[1] != kind: continue
            section_offset[gk] = goff
            goff += sizes[gk]
        goff += (-goff) % 64
        section_bytes[kind] = goff
    lane_offset = {}
    for idx in range(len(oracles)):
        gk, off = offsets[idx]
        lane_offset[idx] = section_offset[gk] + (section_bytes["reg"] if gk[1] == "comb" else 0) + off
    return lane_offset, section_bytes["reg"] + section_bytes["comb"]

def render_record_view(oracles, configuration, layout_name):
    """Typed lane tags over the existing OracleRecord; no second state image."""
    from generate_system_oracle_record import record_layout, lane_identity_hash
    layout = record_layout(oracles, layout_name)
    macro = {"small": "BOOM_GUIDER_CFG_SMALLBOOM_RC",
             "large": "BOOM_GUIDER_CFG_LARGEBOOM_RC"}[configuration]
    fields = collections.OrderedDict()
    for idx, o in enumerate(oracles):
        tail = tail_of(o["flat"])
        prefix, group = group_of(tail)
        rest = tail[len(prefix):].lstrip(".") if prefix else tail
        name = sanitize(rest)
        if o.get("words", 1) > 1:
            name += f"_w{o['word']}"
        group_key = (o["kind"], group)
        members = fields.setdefault(group_key, {})
        if name in members:
            raise ValueError(f"record view field name collision: {group_key}.{name}")
        members[name] = idx
    lines = [
        "// AUTO-GENERATED by gen_image.py --record-view. DO NOT EDIT.",
        "// This view owns no state and claims no producer coverage.",
        "#pragma once", f"#if !defined({macro})",
        f'#error "{configuration} record view requires {macro}"', "#endif",
        '#include "../oracle_record_view_base.h"', "",
        f"namespace chisa::boom_system::record_view::{configuration} {{",
        "struct Contract {",
        f"  inline static constexpr std::size_t lanes = {len(oracles)};",
        f"  inline static constexpr std::size_t bytes = {layout['bytes']};",
        f"  inline static constexpr std::size_t padded_bytes = {layout['padded']};",
        f"  inline static constexpr std::uint64_t layout_hash = 0x{layout['hash']:016x}ull;",
        "  inline static constexpr LaneSpec lane[lanes] = {",
    ]
    for idx, o in enumerate(oracles):
        kind = "Kind::Register" if o["kind"] == "reg" else "Kind::Combinational"
        lines.append(f"    {{{layout['offsets'][idx]}, {o['elemBytes']}, {o['width']}, "
                     f"{kind}, {o.get('word', 0)}, {o.get('words', 1)}, "
                     f"0x{lane_identity_hash(o):016x}ull}},")
    lines += ["  };", "};", "static_assert(compatible<Contract>(),",
              '              "record view identity/word/offset/size disagrees with OracleRecord");',
              "using View = BasicView<Contract>;", "namespace fields {"]
    for kind in ("reg", "comb"):
        lines.append(f"namespace {kind} {{")
        for (k, group), members in fields.items():
            if k != kind:
                continue
            lines.append(f"struct {group} {{")
            for name, idx in members.items():
                lines.append(f"  inline static constexpr Field<Contract, {idx}> {name}{{}};")
            lines.append("};")
        lines.append(f"}}  // namespace {kind}")
    lines.append("}  // namespace fields")
    lines += ["#ifdef CHISA_ORACLE_RECORD_VIEW_TEST", "template <class Visitor>",
              "void visit_fields(Visitor&& visitor) {"]
    for (kind, group), members in fields.items():
        for name in members:
            lines.append(f"  visitor(fields::{kind}::{group}::{name});")
    lines += ["}", "#endif", f"}}  // namespace chisa::boom_system::record_view::{configuration}", ""]
    return "\n".join(lines)


def main():
    if "--record-view" in sys.argv:
        parser = argparse.ArgumentParser(description=__doc__)
        parser.add_argument("manifest")
        parser.add_argument("out")
        parser.add_argument("--record-view", action="store_true")
        parser.add_argument("--configuration", choices=("small", "large"), required=True)
        parser.add_argument("--record-layout", choices=("image", "packed"), required=True)
        args = parser.parse_args()
        oracles = json.load(open(args.manifest))["oracles"]
        result = render_record_view(oracles, args.configuration, args.record_layout)
        open(args.out, "w").write(result)
        print(f"{len(oracles)} typed record fields ({args.configuration}, {args.record_layout}) -> {args.out}")
        return
    manifest, out = sys.argv[1], sys.argv[2]
    owned_out = sys.argv[3] if len(sys.argv) > 3 else None
    lvalue_out = sys.argv[4] if len(sys.argv) > 4 else None
    extra_owned = set()
    if len(sys.argv) > 5:
        extra_owned = {l.strip() for l in open(sys.argv[5]) if l.strip()}
    m = json.load(open(manifest))
    oracles = m["oracles"]
    validate_oracles(oracles)
    groups = collections.OrderedDict(((name, kind), []) for _, name in GROUPS for kind in ("reg", "comb"))
    for idx, o in enumerate(oracles):
        tail = tail_of(o["flat"])
        prefix, gname = group_of(tail)
        rest = tail[len(prefix):].lstrip(".") if prefix else tail
        groups[(gname, o["kind"])].append(Field(sanitize(rest), o["elemBytes"], o["width"], o["flat"], idx))
    # unique names inside a struct
    for key, items in groups.items():
        seen = collections.Counter(f.name for f in items)
        dup = collections.Counter()
        for f in items:
            if seen[f.name] > 1:
                dup[f.name] += 1
                f.name = f"{f.name}_{dup[f.name]}"
    lines = []
    lines.append("// AUTO-GENERATED by duts/boom-repcut/scripts/gen_image.py from the oracle manifest.")
    lines.append("// The contract image of the rewritten model: every stream is a field at its")
    lines.append("// natural element width; the model's registers live here.  Do not edit.")
    lines.append("#pragma once")
    lines.append("#include <cstddef>")
    lines.append("#include <cstdint>")
    lines.append("")
    lines.append("namespace chisa::boom_model {")
    lines.append(f"inline constexpr std::size_t kLanes = {len(oracles)};")
    lines.append("")
    offsets = {}
    struct_size = {}
    section_members = {"reg": [], "comb": []}
    for (gname, kind), items in groups.items():
        if not items: continue
        sname = gname if kind == "reg" else gname + "C"
        size = emit_struct(lines, sname, fold(items), offsets, (gname, kind))
        struct_size[(gname, kind)] = size
        member = gname[0].lower() + gname[1:]
        section_members[kind].append((gname, sname, member, size))
    section_offset = {}
    section_bytes = {}
    for kind, sec in (("reg", "Regs"), ("comb", "Combs")):
        lines.append(f"struct alignas(64) {sec} {{")
        goff = 0
        for gname, sname, member, size in section_members[kind]:
            lines.append(f"  {sname} {member};")
            section_offset[(gname, kind)] = goff
            goff += size
        pad = (-goff) % 64
        if pad: lines.append(f"  std::uint8_t pad_[{pad}];")
        goff += pad
        lines.append("};")
        lines.append(f"static_assert(sizeof({sec}) == {goff}, \"{sec} layout\");")
        lines.append("")
        section_bytes[kind] = goff
    lines.append("struct alignas(64) Image {")
    lines.append("  Regs r;   // register streams: after step t this is the record of cycle t+1")
    lines.append("  Combs c;  // combinational streams: after step t this is the record of cycle t")
    lines.append("};")
    lines.append(f"inline constexpr std::size_t kRegBytes = {section_bytes['reg']};")
    lines.append(f"inline constexpr std::size_t kCombBytes = {section_bytes['comb']};")
    lines.append(f"inline constexpr std::size_t kImageBytes = {section_bytes['reg'] + section_bytes['comb']};")
    lines.append("static_assert(sizeof(Image) == kImageBytes, \"image layout\");")
    lines.append("")
    lines.append("struct LaneSpec {")
    lines.append("  std::uint16_t image_offset;   // byte offset of the field inside Image (comb lanes lie at >= kRegBytes)")
    lines.append("  std::uint8_t bytes;           // element size")
    lines.append("  std::uint8_t width;           // manifest bit width")
    lines.append("  std::uint32_t block_offset;   // the consumer's expansion-buffer offset (W-specific)")
    lines.append("};")
    lines.append("inline constexpr LaneSpec kLane[kLanes] = {")
    for idx, o in enumerate(oracles):
        gk, off = offsets[idx]
        base = section_offset[gk] + (section_bytes["reg"] if gk[1] == "comb" else 0)
        lines.append(f"  {{{base + off}u, {o['elemBytes']}u, {o['width']}u, {o['blockOffset']}u}},  // {idx} {o['traceKey']}")
    lines.append("};")
    lines.append("")
    # Zero exactly the image-owned bytes (the model's own registers) at
    # reset.  Streams inside the same structs that other samplers write are
    # left alone: their samplers only re-store a value that changed.
    ranges = []
    for idx, o in enumerate(oracles):
        tail = tail_of(o["flat"])
        _, gname = group_of(tail)
        if not (image_owned(o["flat"], gname) or o["traceKey"] in extra_owned): continue
        gk, off = offsets[idx]
        base = section_offset[gk] + (section_bytes["reg"] if gk[1] == "comb" else 0)
        ranges.append((base + off, base + off + o["elemBytes"]))
    ranges.sort()
    merged = []
    for lo, hi in ranges:
        if merged and lo <= merged[-1][1]: merged[-1][1] = max(merged[-1][1], hi)
        else: merged.append([lo, hi])
    lines.append("// Zero the image-owned streams (and nothing else) at reset.")
    lines.append("inline void reset_owned(Image& image) {")
    lines.append("  unsigned char* base = reinterpret_cast<unsigned char*>(&image);")
    for lo, hi in merged:
        lines.append(f"  __builtin_memset(base + {lo}, 0, {hi - lo});")
    lines.append("}")
    lines.append(f"inline constexpr std::size_t kOwnedRanges = {len(merged)};")
    lines.append("")
    lines.append("}  // namespace chisa::boom_model")
    if BANK_STRUCTS:
        shared_path = pathlib.Path(__file__).resolve().parents[3] / "reference_models/boom_model/common/predictor_bank_image.h"
        shared_path.parent.mkdir(parents=True, exist_ok=True)
        shared_path.write_text("// Generated predictor-bank register/port schema.\n#pragma once\n#include <cstdint>\nnamespace chisa::boom_model {\n" +
                               "\n".join(BANK_STRUCTS) + "\n}\n")
        include = os.path.relpath(shared_path, pathlib.Path(out).resolve().parent)
        lines.insert(lines.index("namespace chisa::boom_model {"), f'#include "{include}"')
    open(out, "w").write("\n".join(lines) + "\n")
    if lvalue_out:
        lv = {}
        for idx, o in enumerate(oracles):
            gk, _ = offsets[idx]
            gname, kind = gk
            member = gname[0].lower() + gname[1:]
            lv[o["traceKey"]] = {"lvalue": f"{'r' if kind == 'reg' else 'c'}.{member}.{LVALUES[idx]}",
                                 "elem": o["elemBytes"], "width": o["width"], "kind": kind, "flat": o["flat"],
                                 "group": gname, "name": LNAMES[idx], "idx": idx}
        json.dump(lv, open(lvalue_out, "w"), indent=0)
    if owned_out:
        ol = ["// AUTO-GENERATED by duts/boom-repcut/scripts/gen_image.py: streams the model",
              "// writes directly into the record (which is the model image).  Do not edit.",
              "void register_image_owned_bindings() {",
              "  ModelBindings& bindings = ModelBindings::instance();"]
        n = 0
        for idx, o in enumerate(oracles):
            tail = tail_of(o["flat"])
            _, gname = group_of(tail)
            if not (image_owned(o["flat"], gname) or o["traceKey"] in extra_owned): continue
            ol.append(f"  bindings.reserve_image_owned(\"{o['traceKey']}\", {'true' if o['kind'] == 'comb' else 'false'});")
            n += 1
        ol.append("}")
        ol.append(f"inline constexpr std::size_t kImageOwnedLanes = {n};")
        open(owned_out, "w").write("\n".join(ol) + "\n")
        print(f"{n} image-owned lanes -> {owned_out}")
    print(f"{len(oracles)} lanes, regs {section_bytes['reg']} B, combs {section_bytes['comb']} B; " +
          ", ".join(f"{g}{'' if k == 'reg' else 'C'}={s}" for (g, k), s in struct_size.items()))

if __name__ == "__main__":
    main()
