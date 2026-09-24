# ChronoShear Artifact

This is the artifact for **ChronoShear**, formerly named **CHISA**. ChronoShear
is an RTL simulator. Its key idea is to use a microarchitectural reference
model to supply oracle values for selected critical states, breaking
loop-carried dependencies so that multiple simulation cycles can be evaluated
independently. The compiler maps these cycles onto SIMD instructions to
execute them in parallel and accelerate RTL simulation.

## Access to the prepared host

1. **Tailscale:** Install Tailscale, sign in, and accept [this invitation](https://login.tailscale.com/admin/invite/D3mSr6UGjtckUk5XjGg621). Then run:

   ```bash
   ssh user1@100.94.25.12
   ```

2. **SSH jump host (no Tailscale required):** Please send us your SSH public key, and we will set up access for you. Once it is ready, run:

   ```bash
   ssh -J ae-jump@43.110.144.168 -p 22022 user1@127.0.0.1
   ```

Accounts **`user1` through `user8`** are all available. Please replace `user1` in either command with your assigned account and enter the T550 password when prompted: **`asplos27_chisa`** (the same for all eight accounts).

## Directory overview

```text
source/                 ChronoShear source code
  compiler/             FIRRTL-to-C++ compiler
  reference_models/     Software microarchitectural reference models
  runtime/              C++ and SIMD runtime support
  harnesses/            Baseline simulation drivers
  duts/                 Online simulation drivers and model/RTL connections
inputs/<dut>/           Original FIRRTL, workload and generation settings
  design.fir            Hardware design consumed by both compilation flows
  *.riscv or *.bin       Processor workload; AES/MatMul generate inputs in code
generated/<dut>/        Regenerable compilation output
  w4/, w8/, w16/, w32/  ChronoShear C++ RTL and reference-model bindings
  mt6-w16/              Six-partition Large BOOM C++ RTL
  verilog/              FIRRTL lowered to Verilog for the baseline
  verilator1/,          Verilator-generated C++ for one or four threads
  verilator4/
bin/                    Precompiled simulation executables
tools/                  Precompiled ChronoShear compiler and Verilator
deps/                   Offline compiler, plotting and native dependencies
scripts/                Experiment, plotting and clean/rebuild scripts
results/                Measurements, CSV summaries and figures
.build/                 Objects and build logs, created when rebuilding
BUILD.json              Compilation commands and compiler settings
EXPERIMENTS.json        Workloads, simulation commands and checking criteria
```

The DUT directory names are `aes`, `matmul`, `sodor`, `rocket`, `boom-small`,
`boom-medium` and `boom-large`. Each `inputs/<dut>/` holds its design, oracle
selection and any workload or external RTL modules required to regenerate it.
Each `generated/<dut>/` holds its generated C++ and Verilog. Model bindings
connect software reference-model state to the selected RTL oracle signals.

## Compilation flow

We provide **precompiled executables and generated C++**, so the experiments
below can run immediately. To clean or regenerate selected components, run
this command from the artifact directory:

```sh
bash scripts/chronoshear_maintenance.sh
```

Select **Clean only**, **Rebuild**, or **Clean and rebuild**, then choose one or
more DUTs and the components to process. Enter comma-separated menu numbers or
`all` at the DUT and component prompts. The two compilation flows are:

```text
inputs/<dut>/design.fir
  -> ChronoShear compiler
  -> generated/<dut>/w*/ C++ RTL and model bindings
  -> C++ compilation with reference model, runtime and harness
  -> bin/chronoshear-<dut>-w*

inputs/<dut>/design.fir
  -> FIRRTL-to-Verilog lowering
  -> generated/<dut>/verilog/
  -> Verilator
  -> generated/<dut>/verilator1/ or verilator4/
  -> C++ compilation with baseline harness
  -> bin/<dut>-verilator-1t or -4t
```

| Menu component | Reads | Cleans or regenerates |
| --- | --- | --- |
| 1. ChronoShear FIRRTL compilation | `inputs/<dut>/`, `tools/chronoshear.jar` | `generated/<dut>/w*/`, model bindings, and `mt6-w16/` for Large BOOM |
| 2. ChronoShear backend compilation | Generated C++, `source/reference_models/`, runtime and harness | Selected `.build/` objects and `bin/chronoshear-*` |
| 3. Verilator generation | `inputs/<dut>/design.fir`, external RTL modules, compiler tools | `generated/<dut>/verilog/`, `verilator1/`, `verilator4/` |
| 4. Verilator backend compilation | Verilator-generated C++, runtime and baseline harness | Selected `.build/` objects and `bin/*-verilator-*` |
| 5. ChronoShear compiler | `source/compiler/` and bundled Scala dependencies | `.build/compiler/` and `tools/chronoshear.jar` |
| 6. Reference-model architectural checks | Original RTL, reference models and check harnesses | Generated check code, `.build/` objects and `bin/chronoshear-architecture-*` |

For example, to rebuild MatMul from FIRRTL through both executable backends,
choose action **3**, DUT **2**, and components **1,2,3,4**. After editing only a
reference model or harness, choose action **2** and component **2** for that DUT.
Choose component **5** to rebuild the ChronoShear compiler itself.
Components **2** and **4** also update the corresponding architectural-check
programs; choose component **6** to rebuild those programs separately.

Regenerating C++ also removes its old objects and executables, so include the
matching backend component when you need runnable programs. Missing generated
inputs are produced before backend compilation. Cleaning preserves `inputs/`,
`source/` and all experiment results. ESSENT and RepCut are provided as
precompiled baselines; this script rebuilds ChronoShear and Verilator.

## Cleaning experiment results

To remove previous experiment outputs, run:

```sh
bash scripts/chronoshear_clean_results.sh
```

This empties the artifact's `results/` directory, including all logs, CSV files,
figures and custom subdirectories such as `results/my-main/`. Source, inputs,
generated C++ and binaries are preserved. Output directories outside `results/`
are unaffected. Run cleanup before starting experiments.

To regenerate the results and figures, rerun the experiment scripts:

```sh
bash scripts/chronoshear_main.sh
bash scripts/chronoshear_width.sh
bash scripts/chronoshear_threads.sh
```

No recompilation is needed. Each command recreates its own result directory.
The main experiment also reruns the reference-model architectural checks below.

## Experiments

We evaluate **AES, MatMul, Sodor, RocketChip, SmallBOOM, MediumBOOM and
LargeBOOM**, as described in Section **5.1** of the paper. Run the following
commands from the artifact directory:

```sh
cd ~/chronoshear-artifact
```

The experiment scripts read executable and workload selections from
`EXPERIMENTS.json`, run the programs in `bin/`, and load processor workloads from
`inputs/<dut>/`. AES and MatMul generate cipher inputs and matrices inside their
drivers. Experiments write only their selected result directories; they do not
recompile or change source, inputs or binaries. Plotting uses the paper's
plotting functions, fonts and colors, with all dependencies included offline.

### Overall performance — Figure 6

The main experiment measures simulation throughput for every DUT under
ChronoShear, Verilator with one and four threads, ESSENT, and RepCut with four
threads. It also computes performance relative to **single-threaded Verilator**
on the same host. Throughput is reported in kHz, or thousands of simulated
cycles per second. ChronoShear measurements include the online reference model,
oracle transport and synchronization, as well as checked RTL evaluation.

Each DUT has a separate script that measures ChronoShear at **W=4,8,16,32**
and all four baseline configurations, including both Verilator thread counts.
The summary selects the fastest passing ChronoShear width from that run on
the current host. With repeated samples, selection uses each width's median
time per cycle. All four widths' measurements and logs are retained.
Rocket and BOOM scripts first check the reference model against independently
executed original RTL; a failed check stops the measurement. These check logs
and their summary are saved under the selected output directory's `reference/`.

| DUT | Script |
| --- | --- |
| AES | `scripts/chronoshear_aes.sh` |
| MatMul | `scripts/chronoshear_matmul.sh` |
| Sodor | `scripts/chronoshear_sodor.sh` |
| RocketChip | `scripts/chronoshear_rocket.sh` |
| SmallBOOM | `scripts/chronoshear_boom_small.sh` |
| MediumBOOM | `scripts/chronoshear_boom_medium.sh` |
| LargeBOOM | `scripts/chronoshear_boom_large.sh` |

Run all seven scripts, summarize their measurements and draw the main figure:

```sh
bash scripts/chronoshear_main.sh results/my-main
```

The one-click script runs all seven DUT scripts, then runs summarization and
plotting. It produces:

| Output under `results/my-main/` | Contents |
| --- | --- |
| `*.log` | Simulator output for each measurement |
| `samples.csv` | All width candidates and baseline measurements, with pass/fail status |
| `summary.csv` | Selected width, throughput in kHz and speedup over Verilator 1T |
| `throughput.pdf`, `.svg`, `.png` | Main comparison figure |

Bar heights show absolute throughput; labels above ChronoShear bars give
speedup over single-threaded Verilator. With no output-directory argument, the
script uses `results/main/`.

To measure only one DUT, for example MatMul, and then draw its comparison:

```sh
bash scripts/chronoshear_matmul.sh --output results/my-matmul
python3 scripts/chronoshear_summarize.py results/my-matmul
python3 scripts/chronoshear_plot.py results/my-matmul
```

Individual DUT scripts accept `--repetitions N`. Reusing an output directory
replaces the samples for the configurations being run and regenerated
summaries/figures; choose a new directory to retain an earlier run.

If you use the supplied **Xeon host**, expect lower absolute throughput than
on the internal **Ryzen 5** machine used in the paper. In addition to differences
between Intel and AMD processors, the Xeon uses **DDR4** memory whereas the Ryzen
machine uses **DDR5**. These memory-system differences matter substantially for
memory-intensive RTL simulation. Use the same-host Verilator-normalized results
when comparing relative performance.

### Reference-model architectural checks

These checks run the reference model and original Verilator RTL independently,
without oracle injection. Rocket compares the complete retirement sequence and
final PC, integer registers and floating-point registers. Per-instruction value
comparison covers immediate integer writes; individual delayed writebacks are
not compared at retirement, while final register values are checked.

BOOM compares ordered retirement, written register state and the committed-store
memory footprint of the deterministic Dhrystone computation. Timer and HTIF
polling are excluded from exact sequence matching. Both independent executions
also complete and check the full workload results.

To run these checks separately for all four processors, or only one DUT:

```sh
bash scripts/chronoshear_reference_check.sh
bash scripts/chronoshear_reference_check.sh --dut boom-large
```

The scripts read the supplied processor workloads and write logs and
`summary.csv` to `results/reference/`. Each `REFERENCE ARCHITECTURE ... PASS`
reports the architectural comparison for that workload and scope.

### Sensitivity to lane width — Table 5

This experiment runs each of the seven DUTs with SIMD lane widths
**W=4,8,16,32**. W specifies how many simulation cycles are evaluated together
using SIMD. This shows how increasing inter-cycle parallelism changes throughput.

```sh
bash scripts/chronoshear_width.sh results/my-width
```

The script first measures single-threaded Verilator for each DUT, then runs
the four precompiled ChronoShear width variants using the same workloads as the
main experiment. It writes 28 width measurements, seven baseline measurements
and their logs to `results/my-width/`. The resulting `summary.csv` contains
throughput in kHz and speedup over each DUT's same-host Verilator baseline, as
reported in Table 5. The figure is `throughput.{pdf,svg,png}`; each color denotes
a lane width.

### Two-level parallelism — Figure 9

This experiment combines ChronoShear's SIMD inter-cycle execution with RTL
partition parallelism on LargeBOOM at **W=16**. The online artifact places the
six RTL partitions on **2,4,6 RTL cores**, with **four additional cores** for
reference-model work and oracle expansion: six, eight and ten physical cores
in total. A single-threaded Verilator run supplies the speedup denominator.
The measured total throughput includes online reference-model execution and
oracle delivery.

```sh
bash scripts/chronoshear_threads.sh results/my-threads
```

The script reads the LargeBOOM workload, its partitioned ChronoShear executable
and its single-threaded Verilator baseline. It writes logs, measured throughput
and normalized performance to `results/my-threads/summary.csv`; the figure is
`results/my-threads/throughput.{pdf,svg,png}`. The left axis is throughput and the
right axis is speedup over single-threaded Verilator. 

### Plot existing measurements

To regenerate a summary and figure from an existing run, without executing a
simulator:

```sh
python3 scripts/chronoshear_summarize.py results/my-main
python3 scripts/chronoshear_plot.py results/my-main
```

Summarization reads `samples.csv` and replaces `summary.csv`. Plotting reads
`summary.csv` and replaces the PDF/SVG/PNG figure files in that directory.
Plotting may also create its font cache in `~/.cache/chronoshear-matplotlib/`.

## Reading the logs

`PASS` means the run met its configured stopping and checking criteria.
ChronoShear main runs require successful workload completion. BOOM width and thread
timing runs stop earlier, so `program_done=0` is expected there.
`architecture_status` describes the optional comparator within the timed run;
the independent architectural checks are reported separately in `reference/`.
Counters marked `_supported=0` are unavailable.

`ns_per_cycle` is the measured time per simulated cycle; throughput in kHz
is `1,000,000 / ns_per_cycle`.

`differing_signals=A/B` reports distinct mismatching RTL signals among the
`B` checked signal identities. A signal contributes at most once per run,
including repeated checks across cycles and words. The log fields are
`oracle_mismatch_signals` and `oracle_checked_signals`. With repeated samples,
`summary.csv` reports the range of individual runs' counts. All repeated events
remain recorded in `ORACLE_MISMATCH_DETAIL raw_events=...` and the raw-event
column of `samples.csv`.

Nonzero oracle-mismatch counts are handled according to the benign-mismatch
discussion in Section 3.5 of the paper. Micro-Lockstep verification remains
active and its cost is included in the measurement, but oracle mismatches do
not abort the program. A program failure or external-boundary error is still
reported as `FAIL` and retained in the log.
