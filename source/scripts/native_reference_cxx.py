#!/usr/bin/env python3
"""Compiler front end enforcing native-only dependencies for reference TUs."""
import argparse
import hashlib
import json
from pathlib import Path
import shlex
import subprocess
import sys
from audit_reference_inputs import ROOT, enforce_reference_inputs


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", required=True)
    parser.add_argument("--reference-source", type=Path, action="append", default=[],
                        help="explicit model source/header when the final TU also contains a DUT")
    parser.add_argument("arguments", nargs=argparse.REMAINDER)
    options = parser.parse_args()
    arguments = options.arguments
    if arguments[:1] == ["--"]:
        arguments = arguments[1:]
    compiler = shlex.split(options.compiler)
    sources = [Path(arg).resolve() for arg in arguments if not arg.startswith("-") and Path(arg).suffix in {".cpp", ".cc", ".cxx", ".c"}]
    references = [source for source in sources if source.is_relative_to(ROOT / "guiders")
                  and not {"tests", "tools", "cosim"}.intersection(source.parts)
                  and not source.name.startswith(("test_", "bench_", "benchmark_"))]
    if options.reference_source:
        references = [source.resolve() for source in options.reference_source]
    if references:
        flags, skip = [], False
        for arg in arguments:
            if skip:
                skip = False
                continue
            if arg in {"-o", "-MF", "-MT", "-MQ"}:
                skip = True
                continue
            if arg in {"-c", "-MD", "-MMD", "-MP"} or arg.startswith(("-Wl,", "-l", "-L")):
                continue
            if not arg.startswith("-") and Path(arg).suffix in {".cpp", ".cc", ".cxx", ".c", ".o", ".a", ".so"}:
                continue
            flags.append(arg)
        reports = []
        for source in references:
            command = [*compiler, *flags, "-Wno-unused-command-line-argument", "-x", "c++", "-M", "-MT", "reference", str(source)]
            result = subprocess.run(command, check=True, text=True, stdout=subprocess.PIPE)
            paths = shlex.split(result.stdout.replace("\\\n", "").split(":", 1)[1])
            report = enforce_reference_inputs(paths)
            report["source"] = str(source)
            reports.append(report)
        identity = hashlib.sha256(json.dumps([compiler, arguments], sort_keys=True).encode()).hexdigest()
        directory = ROOT / "out/native-reference-audits"
        directory.mkdir(parents=True, exist_ok=True)
        (directory / (identity + ".json")).write_text(json.dumps({"compiler": compiler, "arguments": arguments, "references": reports}, indent=2) + "\n")
    return subprocess.call([*compiler, *arguments])


if __name__ == "__main__":
    raise SystemExit(main())
