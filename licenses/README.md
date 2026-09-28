# Third-party licenses

ChronoShear's own code is licensed under the BSD 3-Clause License
([`LICENSE`](../LICENSE)). The ChronoShear compiler is derived from ESSENT and
also retains ESSENT's license. The third-party components included in this
artifact are distributed under their own licenses:

| Component | Location | License | Text |
| --- | --- | --- | --- |
| ESSENT and its firrtl-sig runtime headers | `source/compiler/`, `source/runtime/`, `tools/chronoshear.jar`, `bin/*-essent-1t` | BSD-3-Clause (LBNL) | `ESSENT.txt` |
| RepCut (H. Wang and S. Beamer, [doi:10.5281/zenodo.7707389](https://doi.org/10.5281/zenodo.7707389)) | `bin/*-repcut-*`, `generated/boom-large/repcut*/` | [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) | — |
| Verilator (upstream commit [`5cca1b101`](https://github.com/verilator/verilator/tree/5cca1b101)) | `tools/verilator/`, `generated/*/verilator*/`, `generated/*/architecture/`, `bin/*-verilator-*`, `bin/chronoshear-architecture-*` | Artistic-2.0 or LGPL-3.0-only | `Verilator-Artistic-2.0.txt`, `Verilator-LGPL-3.0.txt` |
| LLVM lld 19 | `tools/llvm/` | Apache-2.0 WITH LLVM-exception | `LLVM-lld.txt` |
| Scala 2.13 | `deps/scala/`, `deps/compiler-libraries.jar` | Apache-2.0 | `Scala.txt`, `Scala-NOTICE.txt` |
| FIRRTL, Chisel | `deps/compiler-libraries.jar` | Apache-2.0 | `FIRRTL.txt`, `Chisel.txt` |
| SnakeYAML, json4s, nscala-time, data-class | `deps/compiler-libraries.jar` | Apache-2.0 | `SnakeYAML.txt`, `json4s.txt`, `nscala-time.txt`, `data-class.txt` |
| Apache Commons Lang and Text, Joda-Time, Joda-Convert | `deps/compiler-libraries.jar` | Apache-2.0 | `META-INF/LICENSE_*.txt` and `META-INF/NOTICE_*.txt` in the jar |
| Protocol Buffers (Java), ANTLR 4 runtime, ParaNamer | `deps/compiler-libraries.jar` | BSD-3-Clause | `protobuf-java.txt`, `ANTLR4.txt`, `paranamer.txt` |
| os-lib, geny, scopt, moultingyaml | `deps/compiler-libraries.jar` | MIT | `os-lib.txt`, `geny.txt`, `scopt.txt`, `moultingyaml.txt` |
| Rocket Chip | `inputs/rocket/`, `inputs/boom-*/`, `source/harnesses/*/` | Apache-2.0 and BSD-3-Clause | `rocket-chip-SiFive.txt`, `rocket-chip-Berkeley.txt`, `rocket-chip-jtag.txt` |
| BOOM | `inputs/boom-*/` | BSD-3-Clause and Apache-2.0 | `riscv-boom.txt`, `riscv-boom-SiFive.txt` |
| Sodor | `inputs/sodor/` | Sodor license terms | `riscv-sodor.txt` |
| AES in Chisel (UVA HPLP) | `inputs/aes/` | Apache-2.0 | `aes_chisel.txt` |
| riscv-tests (Dhrystone) | `inputs/rocket/`, `inputs/boom-*/` workloads | BSD-3-Clause | `riscv-tests.txt` |
| RISC-V frontend server (fesvr) | `deps/fesvr/` | BSD-3-Clause | `riscv-isa-sim-fesvr.txt` |
| Berkeley SoftFloat 3 | `deps/softfloat/` | BSD-3-Clause | `berkeley-softfloat-3.txt` |
| NumPy, Matplotlib, Pillow and other Python packages | `deps/python/` | Various | Each package's `*.dist-info/` directory |
| Liberation Serif | `deps/fonts/` | SIL Open Font License 1.1 | `deps/fonts/LICENSE` |

Files in `source/harnesses/` that refer to `LICENSE.SiFive` or
`LICENSE.Berkeley` are covered by `rocket-chip-SiFive.txt` and
`rocket-chip-Berkeley.txt`.
