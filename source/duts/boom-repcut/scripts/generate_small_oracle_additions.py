#!/usr/bin/env python3
"""Bind the Small cut experiment's added registers to independent model state."""

import argparse
import hashlib
import json
from pathlib import Path
import re

import generate_dram_access_profile as dram
from prepare_oracle_cut_experiment import TILE, ISSUE, FRONT, ROB


IQ_LAYOUTS = {
    "Integer": "is_rvc:1:60 fu_code:10:50 is_br:1:49 is_jalr:1:48 is_jal:1:47 is_sfb:1:46 br_tag:3:43 ftq_idx:4:39 edge_inst:1:38 pc_lob:6:32 taken:1:31 imm_packed:20:11 rob_idx:5:6 ldq_idx:3:3 stq_idx:3:0",
    "Memory": "fu_code:10:54 imm_packed:20:34 rob_idx:5:29 ldq_idx:3:26 stq_idx:3:23 prs1:6:17 prs2:6:11 prs3:6:5 mem_cmd:5:0",
    "Floating": "fu_code:10:52 imm_packed:20:32 rob_idx:5:27 stq_idx:3:24 prs1:6:18 prs2:6:12 prs3:6:6 mem_cmd:5:1 is_amo:1:0",
}


def mask(width):
    return f"UINT64_C(0x{(1 << width) - 1:x})"


def frontend_field(source):
    local = source.removeprefix(TILE + "frontend.")
    group, field = local.split(".ram_", 1)
    obj = {"f3": "main", "f3_bpd_resp": "bpd", "f4": "f4"}.get(group)
    if not obj:
        raise ValueError(f"unsupported frontend bank source: {source}")
    if field.startswith("ghist_"):
        suffix = field.removeprefix("ghist_")
        if suffix not in ("current_saw_branch_not_taken", "new_saw_branch_not_taken",
                          "new_saw_branch_taken", "ras_idx"):
            raise ValueError(f"unsupported history field: {source}")
        return obj + ".ghist." + suffix
    pred = re.fullmatch(r"preds_([0-3])_(taken|predicted_pc_valid|predicted_pc_bits)", field)
    if pred and group == "f3_bpd_resp":
        member = pred[2].removesuffix("_bits")
        return f"bpd.preds[{pred[1]}].{member}"
    bit = re.fullmatch(r"(sfbs|shadowed_mask|bp_debug_if_oh|bp_xcpt_if_oh)_([0-3])", field)
    if bit and group == "f4":
        member = {"sfbs": "sfb_mask", "shadowed_mask": "shadowed_mask",
                  "bp_debug_if_oh": "bp_debug_mask", "bp_xcpt_if_oh": "bp_xcpt_mask"}[bit[1]]
        return f"((f4.{member} >> {bit[2]}u) & 1u)"
    aliases = {"xcpt_pf_inst": "xcpt_pf_if", "xcpt_ae_inst": "xcpt_ae_if",
               "cfi_idx_valid": "cfi_valid", "cfi_idx_bits": "cfi_idx"}
    allowed = {"mask", "br_mask", "xcpt_pf_if", "xcpt_ae_if", "cfi_type",
               "cfi_is_call", "cfi_is_ret", "ras_top", *aliases}
    if field not in allowed:
        raise ValueError(f"unsupported frontend field: {source}")
    return obj + "." + aliases.get(field, field)


def source_expression(row, banks):
    name, word, width = row["flat"], row.get("word", 0), row["width"]
    if row["kind"] != "reg":
        raise ValueError(f"additional oracle must be a register: {name}")
    if ISSUE.fullmatch(name):
        queue = "Floating" if ".fp_issue_unit." in name else "Memory" if ".mem_issue_unit." in name else "Integer"
        bank = banks[name]
        actual = [(f["source"].split("slot_uop_")[-1], f["width"], f["low"]) for f in bank["fields"]]
        expected = [(f, int(w), int(lo)) for f, w, lo in
                    (item.split(":") for item in IQ_LAYOUTS[queue].split())]
        if actual != expected or width != bank["width"] or word != 0:
            raise ValueError(f"Small IQ bank layout changed: {name}")
        slot = re.search(r"\.slots_([0-7])\.", name)[1]
        return f"core.oracle_issue_bank0(chisa::boom_model::Core::OracleIssueQueue::{queue}, {slot})"
    if name == ROB:
        bank = banks[name]
        expected = [(f"rob_val_{i}", 1, i) for i in range(31, -1, -1)]
        actual = [(f["source"].split(".")[-1], f["width"], f["low"]) for f in bank["fields"]]
        if actual != expected or width != 32 or word:
            raise ValueError("Small ROB bitset layout changed")
        return "core.oracle_rob_valid()"
    if FRONT.fullmatch(name):
        if name in banks:
            bank = banks[name]
            if width != bank["width"] or word:
                raise ValueError(f"frontend bank shape changed: {name}")
            return " | ".join(
                f"((std::uint64_t({frontend_field(f['source'])}) & {mask(f['width'])}) << {f['low']}u)"
                for f in bank["fields"])
        if word not in (0, 1) or width != (64 if word == 0 else 56):
            raise ValueError(f"frontend metadata word shape changed: {name}")
        obj = "bpd.meta" if ".f3_bpd_resp." in name else "f4.bpd_meta" if ".f4." in name else "update.meta"
        return f"std::uint64_t({obj}[{word * 2}]) | (std::uint64_t({obj}[{word * 2 + 1}]) << 32u)"
    divider = TILE + "core.csr_exe_unit.div.div.remainder"
    sqrt_mul = TILE + "core.fp_pipeline.fpiu_unit.fdivsqrt.divsqrt.mul.reg_result_s3"
    fp_mu = TILE + "core.fp_pipeline.fpiu_unit.fpu.fpu.fpmu.io_out_b_data"
    if name == divider and word in (0, 1, 2) and width == (64 if word < 2 else 2):
        return f"core.oracle_div_remainder({word})"
    if name == sqrt_mul and word in (0, 1) and width == (64 if word == 0 else 41):
        return f"model.fabric().fdivsqrt_oracles()[{37 + word}]"
    if name == fp_mu and word in (0, 1) and width == (64 if word == 0 else 1):
        return f"model.fabric().fpu_oracles()[{59 + word}]"
    raise ValueError(f"no independent Small model source for added oracle: {name}, word {word}")


def generate(base, candidate, state, bank_manifest, width):
    base_keys = set(dram.streams(base))
    # DRAM has its existing independent adapter. This file only supplies new registers.
    additions = [r for r in candidate["oracles"] if r["traceKey"] not in base_keys and r["kind"] == "reg"]
    banks = {b["name"]: b for b in bank_manifest["banks"]}
    expressions = [source_expression(row, banks) for row in additions]
    profile = dram.generate(base, candidate, state, width, additions)
    lines = ["#pragma once", "#include <array>", "#include <cstdint>", "#include <cstring>",
             "#include <stdexcept>", "#include \"system_guider.h\"",
             "namespace chisa::boom_system::small_additional_oracles {",
             f"inline constexpr unsigned kCount = {len(additions)};",
             f"inline constexpr unsigned kWidth = {width};",
             "using Snapshot = std::array<std::uint64_t, kCount>;",
             "inline void capture(void* context, const SystemGuider& model, SystemGuider::PublishPhase phase) {",
             "  if (phase != SystemGuider::PublishPhase::Registers) return;",
             "  auto& values = *static_cast<Snapshot*>(context);",
             "  const auto& core = model.backend().core();",
             "  const auto& front = model.frontend();",
             "  [[maybe_unused]] const auto& main = front.f3_queues_for_diagnostic().main_payload();",
             "  [[maybe_unused]] const auto& bpd = front.f3_queues_for_diagnostic().bpd_payload();",
             "  [[maybe_unused]] const auto& f4 = front.f4_queue_for_diagnostic().payload();",
             "  [[maybe_unused]] const auto& update = front.bpd_for_diagnostic().registered_update();"]
    for i, (row, expression) in enumerate(zip(additions, expressions)):
        lines += [f"  // {row['traceKey']}", f"  values[{i}] = ({expression}) & {mask(row['width'])};"]
    lines += ["}", "struct Placement { std::uint32_t offset; unsigned bytes; };",
              "inline constexpr Placement kPlacement[] = {"]
    lines += [f"  {{{r['blockOffset']}u, {r['elemBytes']}u}}," for r in additions]
    lines += ["};", "inline void inject(const Snapshot* cycles, char* expanded) {",
              "  for (unsigned lane = 0; lane < kCount; ++lane)",
              "    for (unsigned p = 0; p < 2 * kWidth; ++p) {",
              "      const unsigned element = p < kWidth ? p : 3 * kWidth - 1 - p;",
              "      const auto& out = kPlacement[lane];",
              "      std::memcpy(expanded + out.offset + element * out.bytes, &cycles[p][lane], out.bytes);",
              "    }", "}", "} // namespace chisa::boom_system::small_additional_oracles", ""]
    return "\n".join(lines), profile, {"oracles": additions, "expressions": expressions,
                                         "samplingPhase": "Registers/PRE", "qualification": "pending runtime validation"}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", required=True, type=Path)
    parser.add_argument("--candidate", required=True, type=Path)
    parser.add_argument("--width", required=True, type=int)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    paths = [args.base, args.candidate / "oracle_manifest.json", args.candidate / "state_array_manifest.json",
             args.candidate / "register_bank_manifest.json"]
    data = [p.read_bytes() for p in paths]
    header, profile, report = generate(*(json.loads(p) for p in data), args.width)
    report["inputs"] = [{"path": str(p), "sha256": hashlib.sha256(content).hexdigest()} for p, content in zip(paths, data)]
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "small_additional_oracles.h").write_text(header)
    (args.output / "dram_access_profile.inc").write_text(profile)
    (args.output / "additional-oracles.json").write_text(json.dumps(report, indent=2) + "\n")
    print(f"SMALL_ADDITIONAL_ORACLES sources={len(report['oracles'])} unmodeled=0 qualification=pending")


if __name__ == "__main__":
    main()
