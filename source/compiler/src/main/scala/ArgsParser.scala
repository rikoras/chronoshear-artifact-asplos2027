package essent

import java.io.File

import scopt.OptionParser

case class OptFlags(
    firInputFile: File = null,
    vectorWidth: Int = 2,
    /** Comma-separated local-name prefixes of registers to exclude from FVS (freeze from oracle). */
    oracleFreeze: Seq[String] = Seq.empty,
    /** SIMD pipeline: template-graph SCC grouping, oracle manifest, no cycle breaker.
      * The former v1 pipeline (RegisterDependencyGraph + Vectorize + atoms) is retired;
      * --simd now selects this pipeline directly and --simd-v2 remains as an alias. */
    simdV2: Boolean = false,
    /** v2: oracle every register source inside an SCC (skip FVS minimization). */
    simdV2OracleAll: Boolean = false,
    /** v2: cap the number of injected oracle streams; -1 means unlimited. */
    simdV2OracleLimit: Int = -1,
    /** v2: max templates per fused lane loop (0 = unlimited). */
    simdV2FuseCap: Int = 0,
    /** v2: hoist produced local SIMD arrays into Top object storage. */
    simdV2MemberScratch: Boolean = false,
    /** v2: hoist produced local SIMD arrays into file-scope static storage. */
    simdV2StaticScratch: Boolean = false,
    /** v2: emit one merged eval_dir body instead of eval_forward/eval_reverse.
      * Halves kernel code size at the price of runtime direction branches:
      * measured slower on sodor (I$ not the bottleneck), intended for DUTs
      * whose duplicated bodies overflow the instruction cache. */
    simdV2MergeEval: Boolean = false,
    // Skip Micro-Lockstep verify emission entirely (no RVerify units, no
    // verify blocks in the header). For pure-performance runs with synthetic
    // (e.g. random) oracle data, and to shrink header size / host-compiler
    // time on very large DUTs. Injection and commit are unaffected.
    simdV2NoVerify: Boolean = false,
    dumpStats: Boolean = false,
    probeSignalsFile: String = "",
    checkpointSave: String = "",
    checkpointLoad: String = "",
    noDefaultMain: Boolean = false,
    defaultMainIters: Int = 20000000,
    numPartitions: Int = 1,
    removeFlatConnects: Boolean = true,
    regUpdates: Boolean = true,
    conditionalMuxes: Boolean = true,
    useCondParts: Boolean = true,
    /** Legacy scalar emitter: preserve the hierarchical Clock graph long
      * enough to lower recognized gated domains into explicit data enables.
      * This is required by full-chip cold sidecars; the historical default
      * remains available for older single-clock flows. */
    clockDomainLowering: Boolean = false,
    /** Legacy scalar zoning: on a false-to-true update transition, commit
      * cached next values for pure register partitions without recomputing
      * their combinational bodies.  Opt-in for full-chip cold sidecars. */
    scalarFastEdgeCommit: Boolean = false,
    /** Legacy scalar zoning diagnostic: count EVAL/COMMIT calls by partition.
      * Kept separate from the old JSON activity tracker so profiling a large
      * generated cold sidecar needs no external header or signal tracking. */
    scalarPartProfile: Boolean = false,
    /** Legacy scalar performance mode: discard source RTL Print/Stop effects
      * before the normal FIRRTL dead-code passes.  Full-chip reference
      * producers retain Micro-Lockstep/final-state checking in the consumer,
      * so assertion-only monitor cones need not run a second time here. */
    scalarDropSourceEffects: Boolean = false,
    writeHarness: Boolean = false,
    dumpLoFirrtl: Boolean = false,
    trackSigs: Boolean = false,
    trackParts: Boolean = false,
    trackExts: Boolean = false,
    partStats: Boolean = false,
    partCutoff: Int = 8,
    withVCD: Boolean = false,
    withFST: Boolean = false,
    essentLogLevel: String = "warn",
    firrtlLogLevel: String = "warn") {
  def inputFileDir() = firInputFile.getParent
  def outputDir() = if (inputFileDir() == null) "" else inputFileDir()
}

class ArgsParser {
  val parser = new OptionParser[OptFlags]("essent") {
    arg[File]("<file>").required().unbounded().action( (x, c) =>
      c.copy(firInputFile = x) ).text(".fir input file")
    
    opt[Unit]("simd").action( (_, c) => c.copy(
      simdV2 = true
    )).text("SIMD pipeline: post-optimization template graph, SCC grouping, oracle manifest (use with --width)")
    opt[Int]("width").action((x, c) => c.copy(
      vectorWidth = x
    ))
    opt[String]("oracle-freeze").action((x, c) => c.copy(
      oracleFreeze = x.split(',').map(_.trim).filter(_.nonEmpty).toSeq
    )).text("comma-separated register local-name prefixes to exclude from FVS oracle injection")
    opt[Unit]("simd-v2").action((_, c) => c.copy(
      simdV2 = true
    )).text("deprecated alias for --simd")
    opt[Unit]("simd-v2-oracle-all").action((_, c) => c.copy(
      simdV2OracleAll = true
    )).text("with --simd-v2: oracle every register source in each SCC (skip FVS minimization)")
    opt[Int]("simd-v2-oracle-limit").action((x, c) => c.copy(
      simdV2OracleLimit = x
    )).validate(x => if (x >= -1) success else failure("oracle limit must be >= -1"))
      .text("with --simd-v2: inject at most K oracle streams (-1 = unlimited)")
    opt[Int]("simd-v2-fuse-cap").action((x, c) => c.copy(
      simdV2FuseCap = x
    )).text("with --simd-v2: max templates per fused lane loop (0 = unlimited)")
    opt[Unit]("simd-v2-member-scratch").action((_, c) => c.copy(
      simdV2MemberScratch = true
    )).text("with --simd-v2: hoist local SIMD scratch arrays into Top object storage")
    opt[Unit]("simd-v2-static-scratch").action((_, c) => c.copy(
      simdV2StaticScratch = true
    )).text("with --simd-v2: hoist local SIMD scratch arrays into file-scope static storage")
    opt[Unit]("simd-v2-merge-eval").action((_, c) => c.copy(
      simdV2MergeEval = true
    )).text("with --simd-v2: emit one merged eval_dir body (halves code size, adds direction branches)")
    opt[Unit]("simd-v2-no-verify").action((_, c) => c.copy(
      simdV2NoVerify = true
    )).text("with --simd-v2: skip Micro-Lockstep verify emission (pure-performance builds, e.g. synthetic oracle data; also shrinks header size on large DUTs)")
    opt[Unit]("no-default-main").action((_, c) => c.copy(
      noDefaultMain = true
    )).text("do not emit a default main() function in the generated header")
    opt[Int]("default-main-iters").action((x, c) => c.copy(
      defaultMainIters = x
    )).text("iteration count for the default main() loop (default: 20000000)")
    opt[Int]("num-partitions").action((x, c) => c.copy(
      numPartitions = x
    )).text("split eval_direction into N partition functions (experimental, requires struct-level scalar promotion)")
    opt[String]("save-checkpoint").action((x, c) => c.copy(
      checkpointSave = x
    )).text("save pre-SplitRegUpdates checkpoint to file (skip downstream passes)")
    opt[String]("load-checkpoint").action((x, c) => c.copy(
      checkpointLoad = x
    )).text("load pre-SplitRegUpdates checkpoint from file (skip RDG/Vectorize)")
    opt[Unit]("dump-stats").action((_, c) => c.copy(
      dumpStats = true
    )).text("dump JSON statistics files")
    opt[String]("probe-signals").action((x, c) => c.copy(
      probeSignalsFile = x
    )).text("JSON file listing signals to promote to struct members (for trace recording)")

    opt[Unit]("O0").abbr("O0").action( (_, c) => c.copy(
        removeFlatConnects = false,
        regUpdates = false,
        conditionalMuxes = false,
        useCondParts=false)
    ).text("disable all optimizations")

    opt[Unit]("O1").abbr("O1").action( (_, c) => c.copy(
        removeFlatConnects = true,
        regUpdates = true,
        conditionalMuxes = false,
        useCondParts=false)
    ).text("enable only optimizations without conditionals")

    opt[Unit]("O2").abbr("O2").action( (_, c) => c.copy(
        removeFlatConnects = true,
        regUpdates = true,
        conditionalMuxes = true,
        useCondParts=false)
    ).text("enable conditional evaluation of mux inputs")

    opt[Unit]("O3").abbr("O3").action( (_, c) => c.copy(
        removeFlatConnects = true,
        regUpdates = true,
        conditionalMuxes = true,
        useCondParts=true)
    ).text("enable all optimizations (default)")

    opt[Unit]("clock-domain-lowering").action((_, c) => c.copy(
      clockDomainLowering = true
    )).text("with the legacy scalar emitter: lower recognized gated clocks to explicit state enables")

    opt[Unit]("scalar-fast-edge-commit").action((_, c) => c.copy(
      scalarFastEdgeCommit = true
    )).text("with the legacy scalar zoning emitter: commit cached pure-register partitions without recomputing them")

    opt[Unit]("scalar-part-profile").action((_, c) => c.copy(
      useCondParts = true,
      scalarPartProfile = true
    )).text("with the legacy scalar zoning emitter: count EVAL/COMMIT calls by partition")

    opt[Unit]("scalar-drop-source-effects").action((_, c) => c.copy(
      scalarDropSourceEffects = true
    )).text("with the legacy scalar emitter: remove source Print/Stop effects before dead-code elimination")

    opt[Unit]("dump").action( (_, c) => c.copy(
        dumpLoFirrtl = true)
    ).text("dump low-firrtl prior to essent executing")

    opt[Unit]('h', "harness").action( (_, c) => c.copy(
        writeHarness = true)
    ).text("generate harness for Verilator debug API")

    opt[String]("essent-log-level").abbr("ell").valueName("<Error|Warn|Info|Debug|Trace>")
    .validate { x =>
      if (Array("error", "warn", "info", "debug", "trace").contains(x.toLowerCase)) success
      else failure(s"$x bad value must be one of error|warn|info|debug|trace")
    }
    .action( (level, c) => c.copy(essentLogLevel = level ) )
    .text("logging level for essent processing after firrtl")

    opt[String]("firrtl-log-level").abbr("fll").valueName("<Error|Warn|Info|Debug|Trace>")
    .validate { x =>
      if (Array("error", "warn", "info", "debug", "trace").contains(x.toLowerCase)) success
      else failure(s"$x bad value must be one of error|warn|info|debug|trace")
    }
    .action( (level, c) => c.copy(firrtlLogLevel = level ) )
    .text("logging level for firrtl preprocessing")

    help("help").text("prints this usage text")

    opt[Unit]("activity-signal").action( (_, c) => c.copy(
        trackSigs = true)
    ).text("track individual signal activities")

    opt[Unit]("activity-parts").action( (_, c) => c.copy(
        useCondParts = true,
        trackParts = true)
    ).text("print out partition activity stats")

    opt[Unit]("activity-exts").action( (_, c) => c.copy(
        trackSigs = true,
        trackExts = true)
    ).text("track individual signal extinguishes (with activities)")

    opt[Unit]("stats-parts").action( (_, c) => c.copy(
        useCondParts = true,
        partStats = true)
    ).text("output topo information from partitioning")

    opt[Int]("part-cutoff").action( (x, c) => c.copy(
        partCutoff = x)
    ).text("parameter used for partitioning")

    opt[Unit]("withVCD").abbr("withVCD").action( (_, c) => c.copy(
        removeFlatConnects = false,
        withVCD = true)
    ).text("parameter used for vcd generation")

    opt[Unit]("withFST").abbr("withFST").action( (_, c) => c.copy(
        removeFlatConnects = false,
        withVCD = true,
        withFST = true)
    ).text("parameter used for vcd generation")
  }

  def getConfig(args: Seq[String]): Option[OptFlags] = parser.parse(args, OptFlags())
}

object TestFlags {
  def apply(inputFirFile: File): OptFlags = {
    OptFlags(firInputFile = inputFirFile, writeHarness = true)
  }
}
