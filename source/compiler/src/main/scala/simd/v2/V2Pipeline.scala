package essent.simd.v2

import essent.Extract._
import essent.Emitter.emitExpr
import essent.ir._

import firrtl._
import firrtl.ir._

import scala.collection.{IndexedSeq => CIndexedSeq}
import collection.mutable
import collection.mutable.ArrayBuffer

/** Builds the template graph from the flattened, fully-optimized scalar
  * design, selects oracles, groups, and schedules. No lane names, no Info
  * tags, no cross-namespace keys: one namespace, typed edges, object ids. */
object V2Pipeline {

  /** One scheduled unit: either a full-width vector group of a template, or
    * a single lane instance of a template inside a serial (SCC) region. */
  sealed trait SchedUnit { def tid: Int }
  case class UVec(tid: Int) extends SchedUnit
  case class ULane(tid: Int, lane: Int) extends SchedUnit

  case class RegInfo(
    name: String,          // flat register name ("tile.core.d.exe_reg_pc")
    tpe: Type,
    nextName: String,      // flat name of the $next DefNode
    plan: RegPlan,
    sourceId: Int,         // RRegSource or ROracleInject template
    commitId: Int,         // RRegCommit template
    verifyId: Option[Int]
  )

  /** Oracle ABI for one read port of a fully externalized persistent array.
    * The data stream feeds the RTL consumer; the address stream is computed by
    * both RTL and the reference model and compared every cycle. */
  case class StateArrayReadAccess(
    dataOracle: String,
    addressOracle: String)

  /** Canonical access ABI for one ordered write port.  Address and data are
    * zero when `enable` is false, so inactive FIRRTL payloads never become part
    * of the reference-model contract.  Sequence order is the original memory
    * writer order and therefore preserves same-address port priority. */
  case class StateArrayWriteAccess(
    portName: String,
    enableOracle: String,
    addressOracle: String,
    dataOracle: String)

  case class StateArrayInfo(
    name: String,          // flattened persistent memory name
    sourceRegister: String,// original Reg(Vec(...)) for lifted state, else the source memory
    tpe: Type,             // scalar payload type after LowerTypes
    depth: Int,
    fields: Seq[(String, Int)], // packed high-to-low: (source leaf, width)
    readIds: Seq[Int],     // RStateRead templates for every address family
    writePorts: Int,
    compilerLifted: Boolean,
    commitId: Int,         // one grouped RStateCommit template for all write ports
    fullyExternal: Boolean,
    readAccess: Seq[StateArrayReadAccess],
    writeAccess: Seq[StateArrayWriteAccess]
  )

  private def configuredExternalArrayFamilies: Seq[String] =
    sys.props.get("V2_EXTERN_ARRAY_FAMILIES")
      .orElse(sys.env.get("V2_EXTERN_ARRAY_FAMILIES")).toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty)

  /** Selectors are historical substring matches unless prefixed with '='.
    * Exact selectors keep a large DRAM bank such as `mem.srams.mem_0` from
    * also matching the distinct `mmio_mem.srams.mem_0` bank. */
  private[v2] def externalArrayFamilyMatches(
      array: String, selector: String): Boolean =
    if (selector.startsWith("=")) array == selector.drop(1)
    else array.contains(selector)

  private def accessNameToken(name: String): String =
    name.map(c => if (c.isLetterOrDigit || c == '_') c else '_')

  private def readAddressOracleName(dataName: String): String =
    dataName + "__access_address"

  private def writeAccessOracleNames(
      array: String, index: Int, portName: String): (String, String, String) = {
    val base = s"$array.__access_write_${index}_${accessNameToken(portName)}"
    (base + "_enable", base + "_address", base + "_data")
  }

  /** One compiler-created scalar register bank.  LowerTypes has already
    * flattened an aggregate register into independent leaves by the time the
    * v2 template graph is built.  Leaves with the same proven mux-hold enable
    * can be losslessly re-packed into a UInt <= 64 bits: the bank keeps the
    * physical state, while zero-cost slice nodes retain every original flat
    * name for the surrounding RTL logic.
    *
    * `fields` is ordered high-to-low and records the untouched scalar model's
    * register name together with the slice used by the SIMD bank.  EmitV2
    * serializes this mapping for full window-boundary differential checks.
    */
  case class RegisterBankField(source: String, width: Int, high: Int, low: Int)
  case class RegisterBankInfo(
    name: String,
    width: Int,
    fields: Seq[RegisterBankField],
    // Exact same-layout storage source for this bank's mux-hold wdata.  This
    // is physical provenance only: it permits the emitter to consume the
    // source lane array directly instead of materializing a copy.
    forwardSource: Option[String] = None,
    // At least one member's write payload reads the member itself, so the
    // packed bank is a genuine self-recurrence: it has no zipper/cond-hold
    // lowering and, unlike pure mux-hold banks, stays oracle-eligible.
    selfRecurrent: Boolean = false)

  /** Compile-time provenance for one selected oracle. This is diagnostic
    * only: it records why the existing selector chose the stream, without
    * participating in graph construction or scheduling. EmitV2 serializes
    * the records to oracle_audit.json after the packed storage layout is
    * known, so selection benefit and runtime byte cost can be joined exactly.
    */
  case class OracleAudit(
    flatName: String,
    kind: String,                 // reg or comb
    stage: String,                // phase1-comb-cut / phase2-fvs / phase3-*
    reason: String,
    basePlan: String,             // plan before oracle replacement
    widthBits: Int,
    sccKey: Int,                  // minimum template id; stable within one emit
    sccTemplates: Int,
    sccCombTemplates: Int,
    sccRegSources: Int,
    sccSelfSources: Int,
    groupOracleCandidates: Int,
    selectedRank: Int,
    benefitEstimate: Long,        // selector's scalar-op proxy, when applicable
    costEstimate: Long,           // selector's scalar-op proxy, when applicable
    cyclicRegDrop: Int,           // exact phase-1 trial result, else -1
    cyclicTemplateDrop: Int,      // exact phase-1 trial result, else -1
    matchedPrefix: String,
    condHoldCandidate: Boolean,
    forcedSerial: Boolean,
    phase3CondTrigger: Boolean = false,
    phase3ForcedTrigger: Boolean = false,
    phase3HeuristicTrigger: Boolean = false,
    muxHoldWen: String = "",
    muxHoldGroupSize: Int = 0
  )

  /** Machine-readable provenance for the performance-only register prune.
    *
    * The removed names are source scalar registers after clock lowering and
    * before register banking/oracle selection.  Keeping the complete sorted
    * set in Result lets EmitV2 publish an auditable contract instead of
    * leaving this semantics-changing optimization as an unstructured log
    * message. */
  case class DeadStatePruneReport(
    sourceEffectsKept: Boolean,
    enabled: Boolean,
    sourceRegisterCount: Int,
    removedRegisters: Seq[String]
  )

  case class Result(
    nodes: CIndexedSeq[TemplateNode],
    regs: Map[String, RegInfo],          // by register flat name
    stateArrays: Map[String, StateArrayInfo],
    registerBanks: Seq[RegisterBankInfo],
    combCuts: Map[String, Type],         // comb cut point -> value type
    oracles: Seq[OracleSpec],
    scheduleFwd: Seq[SchedUnit],         // topological, serial chains contiguous
    scheduleRev: Seq[SchedUnit],         // reverse (zig-zag) direction
    producesIdx: Map[String, Int],       // flat name -> defining template id
    sccOf: Map[Int, Int],                // template id -> scc id (serial regions only)
    serialTemplateCount: Int,
    condHoldGroupOf: Map[String, Int],   // final RPCondHold reg -> shared-wen group id (size >= 2)
    oracleAudit: Seq[OracleAudit],
    clockDomains: ClockDomainLowering.Report,
    deadStatePrune: DeadStatePruneReport,
    hostBoundaryInputs: Set[String],
    accessProofDataOracles: Set[String],
    partitions: Seq[Set[Int]] = Nil        // two-level parallelism: template ids per partition
  )

  // ------------------------------------------------------------------
  // Statement read-set: structural expression traversal only.
  // ------------------------------------------------------------------
  /** Public: EmitV2's oracle-commit planner needs the read set of serial
    * chains' folded expressions (see commitWanted). */
  def exprReads(e: Expression): Seq[String] = e match {
    case w: WRef => Seq(w.name)
    case w: WSubField => Seq(emitExpr(w)(null, essent.Emitter.DefaultContext))
    case m: Mux => exprReads(m.cond) ++ exprReads(m.tval) ++ exprReads(m.fval)
    case p: DoPrim => p.args.flatMap(exprReads)
    case v: ValidIf => exprReads(v.cond) ++ exprReads(v.value)
    case c: WSubAccess => exprReads(c.expr) ++ exprReads(c.index)
    case _ => Seq.empty
  }

  /** Names read by expr, following DefNode chains (bounded). */
  private def transitiveReads(e: Expression, nodeMap: Map[String, Expression]): Set[String] = {
    val seen = mutable.Set[String]()
    def walk(x: Expression, depth: Int): Unit = {
      if (depth > 40) return
      exprReads(x).foreach { n =>
        if (seen.add(n)) nodeMap.get(n).foreach(walk(_, depth + 1))
      }
    }
    walk(e, 0)
    seen.toSet
  }

  /** Pad/truncate expr to the register's width (extraction can yield either). */
  private def legalizeWidth(e: Expression, tpe: Type): Expression = {
    val w = firrtl.bitWidth(tpe)
    val ew = firrtl.bitWidth(e.tpe)
    if (ew > w) DoPrim(firrtl.PrimOps.Bits, Seq(e), Seq(w - 1, BigInt(0)), tpe)
    else if (ew < w) DoPrim(firrtl.PrimOps.Pad, Seq(e), Seq(w), tpe)
    else e
  }

  /** Bank storage is raw UInt bits. A signed member sign-extends in the SInt
    * domain first (Pad on SInt), then contributes its two's-complement bits. */
  private def bankWriteView(e: Expression, tpe: Type): Expression = tpe match {
    case _: SIntType =>
      val w = firrtl.bitWidth(tpe)
      val padded = legalizeWidth(e, tpe)
      DoPrim(firrtl.PrimOps.AsUInt, Seq(padded), Seq.empty, UIntType(IntWidth(w)))
    case _ => legalizeWidth(e, tpe)
  }

  /** Inline the self-tainted part of a register's $next cone into a single
    * expression (self-references stay as WRef(reg), resolved to lane k-1 at
    * emission). Returns None when the folded expression exceeds `cap` ops —
    * then serializing it per lane would cost more than an oracle stream. */
  /** Affine self-update recognition (RPAffineScan). Walks the $next cone
    * through the self-tainted part only (self-free subtrees stay opaque
    * leaves, so no cone is duplicated) and returns (keep, add) such that
    *   next ≡ keep ? (r + add) : add   (mod 2^w).
    * Shapes: r itself (1, 0); r + e / e + r with e self-free (1, e);
    * mux(c, A, B) with c self-free (mux(c, kA, kB), mux(c, aA, aB));
    * width-only wrappers tail/bits(...,0)/pad; any self-free value (0, v).
    * Requires at least one add on the self-tainted path (pure hold/set
    * shapes belong to the cond-hold machinery), a UInt register of at most
    * 64 bits, and a small cone. */
  private def affinePattern(nextExpr: Expression, rName: String,
      nodeMap: Map[String, Expression], rTpe: Type): Option[(Expression, Expression)] = {
    val w = firrtl.bitWidth(rTpe)
    if (w > 64 || !rTpe.isInstanceOf[UIntType]) return None
    val b1 = UIntType(IntWidth(1))
    val wT = UIntType(IntWidth(w))
    val one = UIntLiteral(1, IntWidth(1))
    val zero1 = UIntLiteral(0, IntWidth(1))
    val zeroW = UIntLiteral(0, IntWidth(w))
    def selfFree(e: Expression): Boolean = !transitiveReads(e, nodeMap).contains(rName)
    def isOne(e: Expression): Boolean = e match { case UIntLiteral(v, _) => v == 1; case _ => false }
    def isZero(e: Expression): Boolean = e match { case UIntLiteral(v, _) => v == 0; case _ => false }
    var sawAdd = false
    var budget = 64
    def go(e: Expression): Option[(Expression, Expression)] = {
      budget -= 1
      if (budget < 0) return None
      e match {
        case x: WRef if x.name == rName => Some((one, zeroW))
        case x: WRef if nodeMap.contains(x.name) && !selfFree(x) => go(nodeMap(x.name))
        // A view may be ignored only if it preserves every bit of the
        // register-width modular recurrence. A narrow tail followed by pad
        // wraps at the tail's width, not at the persistent register's width.
        case p @ DoPrim(firrtl.PrimOps.Tail | firrtl.PrimOps.Pad, Seq(x), _, _)
            if x.tpe.isInstanceOf[UIntType] && firrtl.bitWidth(x.tpe) >= w &&
              firrtl.bitWidth(p.tpe) >= w && !selfFree(x) => go(x)
        case DoPrim(firrtl.PrimOps.Bits, Seq(x), Seq(hi, lo), _)
            if lo == 0 && hi + 1 >= w && !selfFree(x) => go(x)
        case DoPrim(firrtl.PrimOps.Add, Seq(x, y), _, _) =>
          val xFree = selfFree(x)
          val yFree = selfFree(y)
          if (xFree == yFree) None
          else {
            val (selfSide, other) = if (xFree) (y, x) else (x, y)
            go(selfSide).flatMap { case (k, a) =>
              if (!isOne(k)) None
              else {
                sawAdd = true
                val sum = if (isZero(a)) legalizeWidth(other, rTpe)
                  else legalizeWidth(DoPrim(firrtl.PrimOps.Add, Seq(a, other), Seq.empty,
                    UIntType(IntWidth(w + 1))), rTpe)
                Some((one, sum))
              }
            }
          }
        case Mux(c, t, f, _) if selfFree(c) =>
          for ((kt, at) <- go(t); (kf, af) <- go(f))
            yield (Mux(c, kt, kf, b1),
                   Mux(c, legalizeWidth(at, rTpe), legalizeWidth(af, rTpe), wT))
        case other if selfFree(other) => Some((zero1, legalizeWidth(other, rTpe)))
        case _ => None
      }
    }
    val result = go(nextExpr)
    if (sawAdd) result else None
  }

  private def foldSelfNext(nextExpr: Expression, rName: String,
      nodeMap: Map[String, Expression], cap: Int,
      foldBarriers: Set[String] = Set.empty): Option[Expression] = {
    val taintMemo = mutable.Map[String, Boolean]()
    def tainted(n: String): Boolean = taintMemo.getOrElseUpdate(n,
      nodeMap.get(n).exists(e => transitiveReads(e, nodeMap).contains(rName)))
    var size = 0  // real operations only; leaf references cost nothing serially
    var ok = true
    def fold(e: Expression, depth: Int): Expression = {
      e match {
        case _: DoPrim | _: Mux | _: ValidIf | _: WSubAccess => size += 1
        case _ =>
      }
      if (size > cap || depth > 60) { ok = false; return e }
      e match {
        case wr: WRef if wr.name == rName => wr
        // A selected indexed-read root is an intentional graph boundary.
        // Inlining its cone into a register source would bypass the later
        // comb cut and recreate a private feedback path (observed for the
        // final nine TLToAXI4 count entries, whose suffix fit under `cap`).
        case wr: WRef if foldBarriers(wr.name) => wr
        case wr: WRef if tainted(wr.name) && nodeMap.contains(wr.name) =>
          fold(nodeMap(wr.name), depth + 1)
        case other => other.mapExpr(fold(_, depth + 1))
      }
    }
    val f = fold(nextExpr, 0)
    if (!ok && sys.env.contains("V2_DEBUG_FOLD"))
      println(s"[v2-debug] fold($rName) aborted: size=$size cap=$cap")
    if (ok) Some(f) else None
  }

  /** Public: EmitV2's zero-copy planner excludes registers read by cold
    * outline bodies (those helpers carry no direction parameter). */
  def stmtReads(s: Statement): Seq[String] = s match {
    case b: Block => b.stmts.flatMap(stmtReads)
    case d: DefNode => exprReads(d.value)
    case c: Connect => exprReads(c.expr)
    case p: Print => p.args.flatMap(exprReads) ++ exprReads(p.en)
    case st: Stop => exprReads(st.en)
    case mw: MemWrite => exprReads(mw.wrEn) ++ exprReads(mw.wrMask) ++
      exprReads(mw.wrAddr) ++ exprReads(mw.wrData)
    case lt: LookupTable => exprReads(lt.indexExpr)
    case _ => Seq.empty
  }

  /** Remove registers that become observationally dead after source
    * Print/Stop effects are omitted from a performance build.
    *
    * This runs on the clock-lowered flat scalar IR, before register banking
    * and oracle selection.  Starting from every host-visible port and every
    * persistent-memory write, it walks combinational definitions backwards.
    * Reaching a register also walks that register's canonical RegUpdate, so
    * the complete next-state cone (including self feedback) remains live.
    * A register outside that closure cannot affect a host boundary or stored
    * memory; retaining it would preserve only an omitted diagnostic effect.
    *
    * Memory writes are deliberately all roots, even when a later whole-memory
    * proof could show a memory unused.  The first version is intentionally
    * conservative: it removes dead scalar state without changing the
    * chronological-storage contract. */
  private case class DeadRegisterPrune(
      stmts: Seq[Statement], removed: Seq[String], sourceRegisters: Int)

  private def pruneDeadRegisters(
      stmts: Seq[Statement], circuit: Circuit): DeadRegisterPrune = {
    val registerNames = stmts.collect { case r: DefRegister => r.name }.toSet
    val updateReads = mutable.LinkedHashMap[String, Seq[String]]()
    val definitionReads = mutable.LinkedHashMap[String, Seq[String]]()

    stmts.foreach {
      case d: DefNode => definitionReads(d.name) = exprReads(d.value)
      case c: Connect =>
        definitionReads(emitExpr(c.loc)(null, essent.Emitter.DefaultContext)) =
          exprReads(c.expr)
      case u: RegUpdate =>
        updateReads(emitExpr(u.regRef)(null, essent.Emitter.DefaultContext)) =
          exprReads(u.expr)
      case _ =>
    }

    val work = mutable.Queue[String]()
    work ++= findExternalPorts(circuit).keys
    // A memory write changes persistent chronological state.  Keep every
    // operand feeding it.  V2 also deliberately schedules every factored
    // memory read through a custom chronological-state role, even when its
    // result has no ordinary combinational consumer, so its address operands
    // are roots here as well.  Pruning memories/read ports themselves is a
    // separate proof.
    stmts.foreach {
      case write: MemWrite => work ++= stmtReads(write)
      case read: DefNode => read.value match {
        case WSubAccess(WRef(_, _, MemKind, _), _, _, _) =>
          work ++= exprReads(read.value)
        case _ =>
      }
      case _ =>
    }

    val visited = mutable.Set[String]()
    val liveRegisters = mutable.Set[String]()
    while (work.nonEmpty) {
      val name = work.dequeue()
      if (visited.add(name)) {
        definitionReads.get(name).foreach(work ++= _)
        if (registerNames(name) && liveRegisters.add(name))
          updateReads.get(name).foreach(work ++= _)
      }
    }

    val removed = (registerNames -- liveRegisters).toSeq.sorted
    val removedSet = removed.toSet
    def updateTarget(update: RegUpdate): String =
      emitExpr(update.regRef)(null, essent.Emitter.DefaultContext)
    val retained = stmts.filterNot {
      case r: DefRegister => removedSet(r.name)
      case u: RegUpdate => removedSet(updateTarget(u))
      case _ => false
    }
    DeadRegisterPrune(retained, removed, registerNames.size)
  }

  // ------------------------------------------------------------------
  // Post-LowerTypes register banking.
  // ------------------------------------------------------------------

  private case class BankCandidate(
    reg: DefRegister,
    update: RegUpdate,
    next: DefNode,
    family: String,
    wen: Expression,
    wdata: Expression,
    width: Int)

  private[v2] case class RegisterBankRewrite(
    stmts: Seq[Statement],
    banks: Seq[RegisterBankInfo],
    eligibleLeaves: Int,
    packedLeaves: Int,
    fullBankForwards: Int = 0,
    maskedBankForwards: Int = 0,
    forwardedFields: Int = 0)

  private def configuredRegisterBankPrefixes: Seq[String] =
    sys.env.get("V2_REGISTER_BANK_PREFIXES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).distinct

  private def configuredRegisterBankExcludeSuffixes: Seq[String] =
    sys.env.get("V2_REGISTER_BANK_EXCLUDE_SUFFIXES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).distinct

  /** Opt-in families whose elaboration-expanded indexed reads may be used as
    * one combinational oracle boundary.  This is deliberately separate from
    * V2_INDEXED_STATE_FAMILIES: the latter rewrites the storage into a memory,
    * whereas this optimization leaves every source-RTL register and all of
    * its update/assert logic in CHISA and cuts only the selected read value.
    */
  private def configuredIndexedReadCutFamilies: Seq[String] =
    sys.env.get("V2_INDEXED_READ_CUT_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).distinct

  /** Opt-in packed bitset families whose maximal pure OR reductions may be
    * used as storage-read boundaries. */
  private def configuredBitsetReadCutFamilies: Seq[String] =
    sys.env.get("V2_BITSET_READ_CUT_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).distinct

  private[v2] case class IndexedReadCutCandidate(
    name: String,
    family: String,
    selector: String,
    leaves: Seq[String],
    reason: String = "indexed-storage-read")

  /** Recover the root of a RemoveAccesses-generated indexed-read mux chain.
    *
    * A valid chain has the exact form
    *
    *   n1 = mux(addr == 1, family_2, family_1)
    *   n2 = mux(addr == 2, family_3, n1)
    *   ...
    *
    * (zero-based literal ranges are accepted as well).  Every data leaf must
    * be a direct register read from one selected numbered family, every mux
    * must use the same selector expression, and the literal range must be
    * dense.  Consequently the root is storage selection only: no ready/valid,
    * retirement, arbitration, or other protocol semantics can be hidden in
    * the proposed cut.
    *
    * Only maximal roots are returned.  This matters for a 128-entry table:
    * the generic degree heuristic used to see 127 equally cheap candidates
    * and could choose an arbitrary middle node such as `_GEN_248`; this
    * recognizer returns the complete read (`_GEN_257`) instead.
    */
  private[v2] def findIndexedReadCutCandidates(
      statements: Seq[Statement],
      registerNames: Set[String],
      selectedFamilies: Seq[String],
      minimumDepth: Int = 16): Seq[IndexedReadCutCandidate] = {
    if (selectedFamilies.isEmpty) return Seq.empty
    require(minimumDepth >= 2,
      s"indexed read-cut minimum depth must be at least 2, got $minimumDepth")

    val definitions = statements.collect { case node: DefNode => node.name -> node }.toMap
    val requestedLeaves = selectedFamilies.map(_.split('.').last).distinct

    def matchingFamily(register: String): Option[String] = {
      val dot = register.lastIndexOf('.')
      val parent = if (dot < 0) "" else register.take(dot + 1)
      val leaf = if (dot < 0) register else register.drop(dot + 1)
      requestedLeaves.find { family =>
        leaf == family || (leaf.startsWith(family + "_") && {
          val suffix = leaf.drop(family.length + 1)
          suffix.nonEmpty && suffix.forall(_.isDigit)
        })
      }.map(parent + _)
    }

    def directRegister(value: Expression): Option[(String, String)] = value match {
      case WRef(name, _, _, _) if registerNames(name) =>
        matchingFamily(name).map(family => name -> family)
      // Compiler-packed indexed counters retain each source register name as
      // a one-bit slice node.  Accept that exact physical-storage projection
      // as a leaf, but no general DefNode: this keeps protocol logic outside
      // the storage-read proof boundary.
      case WRef(name, _, _, _) => matchingFamily(name).flatMap { family =>
        definitions.get(name).flatMap(_.value match {
          case DoPrim(firrtl.PrimOps.Bits,
              Seq(WRef(bank, _, _, _)), Seq(high, low), _)
              if high == low && registerNames(bank) => Some(name -> family)
          case _ => None
        })
      }
      case _ => None
    }

    def selectorAndLiteral(value: Expression): Option[(String, BigInt)] = value match {
      case DoPrim(firrtl.PrimOps.Eq, Seq(UIntLiteral(index, _), selector), _, _) =>
        Some(selector.serialize -> index)
      case DoPrim(firrtl.PrimOps.Eq, Seq(selector, UIntLiteral(index, _)), _, _) =>
        Some(selector.serialize -> index)
      case _ => None
    }

    case class Chain(family: String, selector: String, leaves: Vector[String],
        literals: Vector[BigInt], child: Option[String])
    val memo = mutable.Map[String, Option[Chain]]()
    val visiting = mutable.Set[String]()

    def parseReference(value: Expression): Option[Chain] = value match {
      case WRef(name, _, _, _) =>
        directRegister(value).map { case (register, family) =>
          Chain(family, "", Vector(register), Vector.empty, None)
        }.orElse(if (definitions.contains(name)) parseNode(name) else None)
      case _ => None
    }

    def parseNode(name: String): Option[Chain] = memo.getOrElseUpdate(name, {
      if (!visiting.add(name)) None
      else {
        val parsed = definitions.get(name).flatMap(_.value match {
          case Mux(condition, trueValue, falseValue, _) =>
            for {
              pair <- selectorAndLiteral(condition)
              (selector, literal) = pair
              selected <- directRegister(trueValue)
              (register, family) = selected
              tail <- parseReference(falseValue)
              if tail.family == family
              if tail.selector.isEmpty || tail.selector == selector
              if !tail.leaves.contains(register)
              if !tail.literals.contains(literal)
            } yield Chain(family, selector, tail.leaves :+ register,
              tail.literals :+ literal, falseValue match {
                case WRef(child, _, _, _) if definitions.contains(child) => Some(child)
                case _ => None
              })
          case _ => None
        })
        visiting -= name
        parsed
      }
    })

    val parsed = definitions.keysIterator.flatMap { name =>
      parseNode(name).filter { chain =>
        val n = chain.leaves.size
        if (n < minimumDepth || chain.literals.size != n - 1) false
        else {
          val sorted = chain.literals.sorted
          sorted == (1 until n).map(BigInt(_)).toVector ||
            sorted == (0 until n - 1).map(BigInt(_)).toVector
        }
      }.map(name -> _)
    }.toSeq
    val continued = parsed.iterator.flatMap { case (_, chain) => chain.child }.toSet
    parsed.collect {
      case (name, chain) if !continued(name) =>
        IndexedReadCutCandidate(name, chain.family, chain.selector, chain.leaves)
    }.sortBy(candidate => (-candidate.leaves.size, candidate.name))
  }

  /** Recover maximal OR reductions whose leaves are exclusively projections
    * of one compiler-owned packed bitset.  The result is a storage query such
    * as `flight[0] | ... | flight[7]`; it cannot contain FIFO-domain compare,
    * ready/valid, arbitration, or stall semantics because any non-OR,
    * non-projection leaf makes parsing fail.
    */
  private[v2] def findBitsetReadCutCandidates(
      statements: Seq[Statement],
      banks: Seq[RegisterBankInfo],
      selectedFamilies: Seq[String],
      minimumLeaves: Int = 4): Seq[IndexedReadCutCandidate] = {
    if (banks.isEmpty || selectedFamilies.isEmpty) return Seq.empty
    require(minimumLeaves >= 2,
      s"bitset read-cut minimum leaves must be at least 2, got $minimumLeaves")

    val requestedLeaves = selectedFamilies.map(_.split('.').last).distinct
    def matchingFamily(source: String): Option[String] = {
      val dot = source.lastIndexOf('.')
      val parent = if (dot < 0) "" else source.take(dot + 1)
      val leaf = if (dot < 0) source else source.drop(dot + 1)
      requestedLeaves.find { family =>
        if (!leaf.startsWith(family)) false
        else {
          val suffix = leaf.drop(family.length)
          val digits = suffix.dropWhile(_ == '_')
          suffix.nonEmpty && suffix.head == '_' && digits.nonEmpty && digits.forall(_.isDigit)
        }
      }.map(parent + _)
    }

    val sourceFamily = banks.iterator.flatMap(_.fields.iterator)
      .flatMap(field => matchingFamily(field.source).map(field.source -> _)).toMap
    val physicalFamily = banks.iterator.flatMap { bank =>
      bank.fields.iterator.flatMap(field => sourceFamily.get(field.source).map { family =>
        (bank.name, field.high, field.low) -> (field.source, family)
      })
    }.toMap
    if (sourceFamily.isEmpty) return Seq.empty

    val definitions = statements.collect { case node: DefNode => node.name -> node }.toMap
    case class Reduction(family: String, leaves: Vector[String], nodes: Set[String])
    val memo = mutable.Map[String, Option[Reduction]]()
    val visiting = mutable.Set[String]()

    def directLeaf(value: Expression): Option[(String, String)] = value match {
      case WRef(name, _, _, _) => sourceFamily.get(name).map(name -> _)
      case DoPrim(firrtl.PrimOps.Bits, Seq(WRef(bank, _, _, _)), Seq(high, low), _)
          if high == low => physicalFamily.get((bank, high.toInt, low.toInt))
      case _ => None
    }
    def mergeReductions(left: Reduction, right: Reduction): Option[Reduction] =
      if (left.family != right.family ||
          (left.leaves.toSet intersect right.leaves.toSet).nonEmpty) None
      else Some(Reduction(left.family, left.leaves ++ right.leaves,
        left.nodes ++ right.nodes))

    // LowForm is free to inline a DefNode-only OR chain into its consumer.
    // Accept that exact expression tree as well as WRef-linked chains.  The
    // recursion remains fail-closed: every interior operation must be OR and
    // every leaf must be a proven projection of one compiler-owned bank.
    def parseExpression(value: Expression): Option[Reduction] =
      directLeaf(value).map { case (leaf, family) =>
        Reduction(family, Vector(leaf), Set.empty)
      }.orElse(value match {
        case DoPrim(firrtl.PrimOps.Or, Seq(leftValue, rightValue), _, _) =>
          for {
            left <- parseExpression(leftValue)
            right <- parseExpression(rightValue)
            merged <- mergeReductions(left, right)
          } yield merged
        case WRef(name, _, _, _) if definitions.contains(name) => parseNode(name)
        case _ => None
      })

    def parseNode(name: String): Option[Reduction] = memo.getOrElseUpdate(name, {
      if (!visiting.add(name)) None
      else {
        val parsed = definitions.get(name).flatMap(_.value match {
          case DoPrim(firrtl.PrimOps.Or, Seq(leftValue, rightValue), _, _) =>
            for {
              left <- parseExpression(leftValue)
              right <- parseExpression(rightValue)
              merged <- mergeReductions(left, right)
            } yield merged.copy(nodes = merged.nodes + name)
          case _ => None
        })
        visiting -= name
        parsed
      }
    })

    val parsed = definitions.keysIterator.flatMap(name =>
      parseNode(name).filter(_.leaves.size >= minimumLeaves).map(name -> _)).toSeq
    val continuedByParsedTree = parsed.iterator.flatMap { case (root, reduction) =>
      reduction.nodes - root
    }.toSet
    // A pure prefix consumed by a larger mixed OR is not a stable semantic
    // boundary.  Reject it even though the mixed parent itself failed to
    // parse; only the last pure OR before non-OR protocol logic is eligible.
    def referencedUnderOr(value: Expression): Set[String] = value match {
      case WRef(child, _, _, _) if definitions.contains(child) => Set(child)
      case DoPrim(firrtl.PrimOps.Or, values, _, _) =>
        values.iterator.flatMap(referencedUnderOr).toSet
      case _ => Set.empty
    }
    val everyOrChild = definitions.valuesIterator.flatMap(node =>
      referencedUnderOr(node.value)).toSet
    val continued = continuedByParsedTree ++ everyOrChild
    parsed.collect {
      case (name, reduction) if !continued(name) =>
        IndexedReadCutCandidate(name, reduction.family, selector = "",
          reduction.leaves, reason = "bitset-reduction-read")
    }.sortBy(candidate => (-candidate.leaves.size, candidate.name))
  }

  /** Whether an extractable mux-hold register must retain its local
    * recurrence when the cond-hold oracle experiment is enabled.  In
    * particular, compiler-created banks are storage containers rather than
    * source-RTL observables, so injecting them would both duplicate their
    * member state and defeat banking.
    */
  private[v2] def keepMuxHoldLocal(
      name: String,
      width: BigInt,
      oracleCondhold: Boolean,
      compilerOwnedBanks: Set[String],
      freezePrefixes: Seq[String],
      oracleExceptPrefixes: Seq[String]): Boolean =
    !oracleCondhold || compilerOwnedBanks.contains(name) || width > 64 ||
      (freezePrefixes ++ oracleExceptPrefixes).exists(p =>
        name.startsWith(p) || name.split('.').last.startsWith(p))

  /** A prefix applies to the final flattened component, not to a hierarchy
    * path.  For example `slot_uop_` maps
    * `core.int_issue_unit.slots_3.slot_uop_prs1` to the logical family
    * `core.int_issue_unit.slots_3.slot_uop`.  Keeping the hierarchy in the
    * family prevents state from different IssueSlot instances being merged.
    */
  private def registerBankFamily(name: String, prefixes: Seq[String]): Option[String] = {
    val dot = name.lastIndexOf('.')
    val parent = if (dot < 0) "" else name.take(dot + 1)
    val leaf = if (dot < 0) name else name.drop(dot + 1)
    prefixes.find(leaf.startsWith).map(p => parent + p.stripSuffix("_"))
  }

  private def isZeroLiteral(e: Expression): Boolean = e match {
    case UIntLiteral(value, _) => value == 0
    case _ => false
  }

  private def packUInts(values: Seq[Expression]): Expression = {
    require(values.nonEmpty)
    values.tail.foldLeft(values.head) { (left, right) =>
      val width = firrtl.bitWidth(left.tpe) + firrtl.bitWidth(right.tpe)
      DoPrim(firrtl.PrimOps.Cat, Seq(left, right), Seq.empty,
        UIntType(IntWidth(width)))
    }
  }

  /** Re-pack low-form scalar register leaves that already have exactly the
    * same proven mux-hold enable.  Reset behavior needs no special case here:
    * LowForm has folded each source register's synchronous reset into its
    * `$next` mux, so reset-valued and reset-invalid leaves simply land in
    * different `wen.serialize` groups.  Reconstructing
    *
    *   bank' = wen ? cat(wdata_i) : bank
    *
    * is therefore bit-for-bit equivalent to all member recurrences.
    *
    * This is deliberately fail-closed.  A group is left untouched if a bank
    * member's enable/data reads any member of that same bank family, if the
    * old `$next` has a non-commit consumer, or if the original low-form
    * register still carries an active DefRegister reset.
    */
  private[v2] def packFlatRegisters(
      input: Seq[Statement], prefixes: Seq[String],
      excludeSuffixes: Seq[String] = Seq.empty): RegisterBankRewrite = {
    if (prefixes.isEmpty) return RegisterBankRewrite(input, Seq.empty, 0, 0)

    val regDefs = mutable.LinkedHashMap[String, DefRegister]()
    val nextDefs = mutable.LinkedHashMap[String, DefNode]()
    val updates = mutable.LinkedHashMap[String, RegUpdate]()
    input.foreach {
      case r: DefRegister => regDefs(r.name) = r
      case d: DefNode => nextDefs(d.name) = d
      case u: RegUpdate => u.regRef match {
        case WRef(name, _, _, _) => updates(name) = u
        case _ =>
      }
      case _ =>
    }
    val nodeMap = essent.passes.SplitRegUpdates.buildDefNodeMap(Block(input))

    // Find every statement that consumes an old $next.  Its own one-to-one
    // RegUpdate is expected; any additional consumer makes removal unsafe.
    val nextUsers = mutable.Map[String, mutable.Set[Int]]()
    input.zipWithIndex.foreach { case (stmt, index) =>
      val names = mutable.Set[String]()
      def walk(e: Expression): Unit = e match {
        case WRef(name, _, _, _) => names += name
        case other => other.foreachExpr(walk)
      }
      stmt.foreachExpr(walk)
      names.filter(_.endsWith("$next")).foreach { name =>
        nextUsers.getOrElseUpdate(name, mutable.Set()) += index
      }
    }
    val stmtIndex = input.iterator.zipWithIndex.map { case (s, i) => s -> i }.toMap

    val candidates = ArrayBuffer[BankCandidate]()
    // Rejection tally per (family-prefix, rule). V2_REGISTER_BANK_DIAG=1
    // prints it after packing so a family that silently fails eligibility is
    // one emit away from a named cause instead of a guess.
    val diag = sys.env.get("V2_REGISTER_BANK_DIAG").contains("1")
    val rejections = mutable.LinkedHashMap[(String, String), Int]()
    def reject(family: String, rule: String): Option[Nothing] = {
      if (diag) rejections((family, rule)) = rejections.getOrElse((family, rule), 0) + 1
      None
    }
    regDefs.values.foreach { reg =>
      registerBankFamily(reg.name, prefixes)
          .filterNot(_ => excludeSuffixes.exists(reg.name.endsWith))
          .foreach { family =>
        val prefix = prefixes.find(p => reg.name.split('.').last.startsWith(p))
          .getOrElse(family)
        val widthOpt = reg.tpe match {
          case _: UIntType => Some(firrtl.bitWidth(reg.tpe).toInt)
          case _: SIntType => Some(firrtl.bitWidth(reg.tpe).toInt)
          case _ => None
        }
        val nextName = reg.name + "$next"
        val candidate = for {
          width <- widthOpt.filter(w => w >= 1 && w <= 64)
            .orElse(reject(prefix, "not-uint-or-wide"))
          next <- nextDefs.get(nextName)
            .orElse(reject(prefix, "no-next-node"))
          update <- updates.get(reg.name)
            .orElse(reject(prefix, "no-reg-update"))
          _ <- (if (isZeroLiteral(reg.reset)) Some(()) else None)
            .orElse(reject(prefix, "nonzero-reset"))
          _ <- (update.expr match {
            case WRef(name, _, _, _) if name == nextName => Some(())
            case _ => None
          }).orElse(reject(prefix, "update-not-next-ref"))
          updateIndex <- stmtIndex.get(update)
          _ <- (if (nextUsers.getOrElse(nextName, mutable.Set.empty[Int]) == Set(updateIndex))
            Some(()) else None).orElse(reject(prefix, "next-has-other-users"))
          extracted <- essent.passes.SplitRegUpdates.extractMuxHoldPattern(
            next.value, reg.name, nodeMap, 0, serialOk = true)
            .orElse(reject(prefix, "not-mux-hold"))
          (wen, rawWdata) = extracted
          _ <- (if (!transitiveReads(wen, nodeMap).contains(reg.name)) Some(())
            else None).orElse(reject(prefix, "wen-reads-self"))
          // wdata reading the member itself is representable: the removed
          // member becomes a slice-alias DefNode of the packed bank, so a
          // self-read resolves to the bank's current (= old) value and the
          // bank update is one self-recurrence instead of N member
          // recurrences. Only reads of *other* members stay disqualifying
          // (enforced at grouping).
        } yield BankCandidate(reg, update, next, family, wen,
          bankWriteView(rawWdata, reg.tpe), width)
        candidate.foreach(candidates += _)
      }
    }

    val grouped = mutable.LinkedHashMap[(String, String, String), ArrayBuffer[BankCandidate]]()
    candidates.foreach { candidate =>
      val key = (candidate.family, candidate.reg.clock.serialize, candidate.wen.serialize)
      grouped.getOrElseUpdate(key, ArrayBuffer()) += candidate
    }

    // Greedy source-order packing.  It is optimal for the BOOM payload shape
    // (including its one dedicated 64-bit exception-cause leaf) and, more
    // importantly, stable across runs.  Singleton chunks stay as their
    // original register because replacing one leaf with one bank only adds a
    // slice node without reducing the recurrence count.
    val singletonPool =
      mutable.LinkedHashMap[(String, String), ArrayBuffer[BankCandidate]]()
    val selectedChunks = ArrayBuffer[(String, Int, Seq[BankCandidate])]()
    val familyGroupOrdinal = mutable.Map[String, Int]().withDefaultValue(0)
    grouped.foreach { case ((family, _, _), members) =>
      // Family-member reads no longer disqualify: every removed member is a
      // slice alias of its bank, so reads of packed siblings (same bank or a
      // sibling bank) resolve to old values exactly like self-reads. Banks
      // whose wdata ends up reading the bank itself are self-recurrent and
      // oracle-eligible.
      val independentMembers = members
      if (independentMembers.size == 1) {
        reject(family, "singleton-wen-group")
        // Leftover singleton: no sibling shares its write enable. Re-express
        // its contribution as the member's complete $next value under an
        // always-write enable; same-family singletons then merge into one
        // self-recurrent bank (one stream instead of one per member).
        val member = independentMembers.head
        singletonPool.getOrElseUpdate(
          (member.family, member.reg.clock.serialize), ArrayBuffer()) +=
          member.copy(wen = UIntLiteral(1, IntWidth(1)),
            wdata = bankWriteView(member.next.value, member.reg.tpe))
      }
      if (independentMembers.size >= 2) {
        val ordinal = familyGroupOrdinal(family)
        familyGroupOrdinal(family) = ordinal + 1
        val chunks = ArrayBuffer[ArrayBuffer[BankCandidate]]()
        var current = ArrayBuffer[BankCandidate]()
        var currentWidth = 0
        independentMembers.foreach { member =>
          if (current.nonEmpty && currentWidth + member.width > 64) {
            chunks += current
            current = ArrayBuffer[BankCandidate]()
            currentWidth = 0
          }
          current += member
          currentWidth += member.width
        }
        if (current.nonEmpty) chunks += current
        chunks.filter(_.size >= 2).foreach(chunk =>
          selectedChunks += ((family, ordinal, chunk.toSeq)))
      }
    }

    def printDiag(): Unit = if (diag && rejections.nonEmpty) {
      val byFamily = rejections.toSeq.groupBy(_._1._1)
      byFamily.toSeq.sortBy(-_._2.map(_._2).sum).foreach { case (fam, rows) =>
        val detail = rows.sortBy(-_._2).map { case ((_, rule), n) => s"$rule=$n" }.mkString(" ")
        println(s"[v2-reg-bank-diag] $fam: $detail")
      }
    }
    // Merge pooled singletons per (family, clock): they become always-write
    // banks whose wdata is each member's full old next expression, so member
    // self-reads resolve to bank slices exactly like other self-recurrent
    // banks; family-member reads resolve through slice aliases like all
    // other packed-member reads.
    singletonPool.foreach { case ((family, _), members) =>
      val mergeable = members
      if (mergeable.size >= 2) {
        val ordinal = familyGroupOrdinal(family)
        familyGroupOrdinal(family) = ordinal + 1
        val chunks = ArrayBuffer[ArrayBuffer[BankCandidate]]()
        var current = ArrayBuffer[BankCandidate]()
        var currentWidth = 0
        mergeable.foreach { member =>
          if (current.nonEmpty && currentWidth + member.width > 64) {
            chunks += current
            current = ArrayBuffer[BankCandidate]()
            currentWidth = 0
          }
          current += member
          currentWidth += member.width
        }
        if (current.nonEmpty) chunks += current
        chunks.filter(_.size >= 2).foreach(chunk =>
          selectedChunks += ((family, ordinal, chunk.toSeq)))
      }
    }

    val removedRegs = selectedChunks.iterator.flatMap(_._3.map(_.reg.name)).toSet
    if (removedRegs.isEmpty) {
      printDiag()
      return RegisterBankRewrite(input, Seq.empty, candidates.size, 0)
    }
    val removedNext = removedRegs.map(_ + "$next")
    val existingNames = mutable.Set[String]() ++ regDefs.keySet ++ nextDefs.keySet
    val chunkOrdinal = mutable.Map[(String, Int), Int]().withDefaultValue(0)

    // Allocate every bank and slice before constructing any next expression.
    // Issue queues move a payload from entry N+1 to entry N.  The scalar
    // leaves therefore refer to another family's registers; knowing only the
    // current chunk forces the old code to rebuild the payload as
    // cat(bits(sourceBank), ...).  A complete leaf -> physical-slice map lets
    // us retain that transfer as one bank reference (or one masked reference
    // plus the few fields that really change).
    case class SelectedBank(
      name: String,
      width: Int,
      tpe: UIntType,
      members: Seq[BankCandidate],
      fields: Seq[RegisterBankField])
    val selectedBanks = ArrayBuffer[SelectedBank]()

    selectedChunks.foreach { case (family, groupOrdinal, members) =>
      val ordinalKey = (family, groupOrdinal)
      val localOrdinal = chunkOrdinal(ordinalKey)
      chunkOrdinal(ordinalKey) = localOrdinal + 1
      val rawBase = s"${family}__v2_bank_${groupOrdinal}_$localOrdinal"
      var bankName = rawBase
      var collision = 0
      while (existingNames(bankName) || existingNames(bankName + "$next")) {
        collision += 1
        bankName = rawBase + "_" + collision
      }
      existingNames += bankName
      existingNames += bankName + "$next"

      val bankWidth = members.map(_.width).sum
      require(bankWidth >= 1 && bankWidth <= 64)
      val bankType = UIntType(IntWidth(bankWidth))
      var high = bankWidth - 1
      val fields = members.map { member =>
        val low = high - member.width + 1
        val field = RegisterBankField(member.reg.name, member.width, high, low)
        high = low - 1
        field
      }
      require(high == -1)
      selectedBanks += SelectedBank(bankName, bankWidth, bankType, members, fields)
    }

    case class PhysicalSlice(bank: SelectedBank, field: RegisterBankField)
    val physicalSliceByLeaf: Map[String, PhysicalSlice] = selectedBanks.iterator
      .flatMap(bank => bank.fields.iterator.map(field => field.source -> PhysicalSlice(bank, field)))
      .toMap

    def directLeafName(e: Expression): Option[String] = e match {
      case WRef(name, tpe, _, _) if firrtl.bitWidth(tpe) == firrtl.bitWidth(e.tpe) => Some(name)
      case _ => None
    }

    def placeAt(value: Expression, low: Int, bankWidth: Int,
        bankType: UIntType): Expression = {
      val valueWidth = firrtl.bitWidth(value.tpe).toInt
      val shiftedInputWidth = bankWidth - low
      val padded = if (valueWidth < shiftedInputWidth)
        DoPrim(firrtl.PrimOps.Pad, Seq(value), Seq(BigInt(shiftedInputWidth)),
          UIntType(IntWidth(shiftedInputWidth)))
      else value
      if (low == 0) padded
      else DoPrim(firrtl.PrimOps.Shl, Seq(padded), Seq(BigInt(low)), bankType)
    }

    var fullBankForwards = 0
    var maskedBankForwards = 0
    var forwardedFields = 0
    val fullForwardSource = mutable.Map[String, String]()

    /** Preserve cross-entry storage movement at bank granularity.  A hit is
      * valid only when source and destination slices have identical physical
      * offsets and bank widths; there is no field permutation or semantic
      * logic hidden here.  For a sparse mismatch, start from the dominant
      * source bank, mask off non-forwarded bits, and insert the original
      * scalar expressions for precisely those bits.
      */
    def forwardedWdata(bank: SelectedBank): Expression = {
      val hits = bank.members.zip(bank.fields).flatMap { case (member, dstField) =>
        directLeafName(member.wdata).flatMap(physicalSliceByLeaf.get).collect {
          case source if source.bank.name != bank.name &&
              source.bank.width == bank.width &&
              source.field.width == dstField.width &&
              source.field.high == dstField.high &&
              source.field.low == dstField.low =>
            (dstField, source.bank)
        }
      }
      val bySource = hits.groupBy(_._2.name).values.toSeq
      val dominant = bySource.sortBy(group =>
        (-group.map(_._1.width).sum, -group.size, group.head._2.name)).headOption

      dominant match {
        case Some(group) if group.size == bank.members.size =>
          fullBankForwards += 1
          forwardedFields += group.size
          fullForwardSource(bank.name) = group.head._2.name
          WRef(group.head._2.name, bank.tpe, RegKind, SourceFlow)

        case Some(group) =>
          val copied = group.iterator.map(_._1.source).toSet
          val changed = bank.members.zip(bank.fields).filterNot {
            case (_, field) => copied(field.source)
          }
          // One source mask, one OR per changed field, and at most pad+shift
          // per insertion.  Keep the original cat when this structural proxy
          // predicts no reduction; partial forwarding is an optimization,
          // never a mandatory lowering.
          val insertionOps = changed.map { case (_, field) =>
            (if (field.high == bank.width - 1) 0 else 1) +
              (if (field.low == 0) 0 else 1)
          }.sum
          val newOps = 1 + changed.size + insertionOps
          val oldOps = 2 * (bank.members.size - 1)
          if (group.size >= 2 && newOps < oldOps) {
            val sourceBank = group.head._2
            val copyMask = group.iterator.foldLeft(BigInt(0)) { case (mask, (field, _)) =>
              mask | (((BigInt(1) << field.width) - 1) << field.low)
            }
            val maskLiteral = UIntLiteral(copyMask, IntWidth(bank.width))
            val sourceRef = WRef(sourceBank.name, bank.tpe, RegKind, SourceFlow)
            val base = DoPrim(firrtl.PrimOps.And, Seq(sourceRef, maskLiteral), Seq.empty, bank.tpe)
            val merged = changed.foldLeft(base: Expression) {
              case (acc, (member, field)) =>
                val placed = placeAt(member.wdata, field.low, bank.width, bank.tpe)
                DoPrim(firrtl.PrimOps.Or, Seq(acc, placed), Seq.empty, bank.tpe)
            }
            maskedBankForwards += 1
            forwardedFields += group.size
            merged
          } else packUInts(bank.members.map(_.wdata))

        case None => packUInts(bank.members.map(_.wdata))
      }
    }

    val bankStatements = ArrayBuffer[Statement]()
    val bankInfos = ArrayBuffer[RegisterBankInfo]()
    selectedBanks.foreach { bank =>
      val bankRef = WRef(bank.name, bank.tpe, RegKind, SourceFlow)
      val first = bank.members.head
      bankStatements += DefRegister(first.reg.info, bank.name, bank.tpe,
        first.reg.clock, first.reg.reset, bankRef)
      bank.members.zip(bank.fields).foreach { case (member, field) =>
        val bits = DoPrim(firrtl.PrimOps.Bits, Seq(bankRef),
          Seq(BigInt(field.high), BigInt(field.low)),
          UIntType(IntWidth(member.width)))
        val slice = member.reg.tpe match {
          case _: SIntType =>
            DoPrim(firrtl.PrimOps.AsSInt, Seq(bits), Seq.empty, member.reg.tpe)
          case _ => DoPrim(firrtl.PrimOps.Bits, Seq(bankRef),
            Seq(BigInt(field.high), BigInt(field.low)), member.reg.tpe)
        }
        bankStatements += DefNode(member.reg.info, member.reg.name, slice)
      }
      val bankNextName = bank.name + "$next"
      val bankNext = Mux(first.wen, forwardedWdata(bank), bankRef, bank.tpe)
      bankStatements += DefNode(first.next.info, bankNextName, bankNext)
      bankStatements += RegUpdate(NoInfo, bankRef,
        WRef(bankNextName, bank.tpe, NodeKind, SourceFlow))
      val bankMemberNames = bank.members.iterator.map(_.reg.name).toSet
      // Bank-level: any member payload or enable reading any member of THIS
      // bank makes the packed next expression read the bank itself.
      val selfRecurrent = bank.members.exists(member =>
        (transitiveReads(member.wdata, nodeMap) ++
          transitiveReads(member.wen, nodeMap)).exists(bankMemberNames))
      bankInfos += RegisterBankInfo(bank.name, bank.width, bank.fields,
        fullForwardSource.get(bank.name), selfRecurrent)
    }

    def rewriteExpr(e: Expression): Expression = e match {
      case WRef(name, tpe, _, flow) if removedRegs(name) =>
        WRef(name, tpe, NodeKind, flow)
      case other => other.mapExpr(rewriteExpr)
    }
    val rewritten = input.flatMap {
      case r: DefRegister if removedRegs(r.name) => None
      case d: DefNode if removedNext(d.name) => None
      case u: RegUpdate if (u.regRef match {
        case WRef(name, _, _, _) => removedRegs(name)
        case _ => false
      }) => None
      case other => Some(other.mapExpr(rewriteExpr))
    }
    // Normalize member references inside the bank statements themselves:
    // a member name now resolves to its slice-alias DefNode, so any embedded
    // read (self-recurrent wdata included) must carry NodeKind like every
    // rewritten reader in `input`.
    val normalizedBankStatements = bankStatements.map(_.mapExpr(rewriteExpr))
    printDiag()
    RegisterBankRewrite(rewritten ++ normalizedBankStatements, bankInfos.toSeq,
      candidates.size, removedRegs.size, fullBankForwards, maskedBankForwards,
      forwardedFields)
  }

  // ------------------------------------------------------------------
  // Graph construction
  // ------------------------------------------------------------------

  def build(circuit: Circuit, W: Int, wantVerify: Boolean, freezePrefixes: Seq[String],
            oracleAll: Boolean, oracleLimit: Int = -1, fuseCap: Int = 32,
            stateArrayAnnotations: Seq[StateArrayStorageAnnotation] = Seq.empty,
            indexedCounterBankAnnotations: Seq[IndexedCounterBankStorageAnnotation] = Seq.empty,
            keepSourceEffects: Boolean = true): Result = {
    require(oracleLimit >= -1, s"[v2] oracleLimit must be >= -1, got $oracleLimit")
    // Resolve gated clocks while the intact hierarchical Clock connections
    // are still available.  The lowering returns the same clockless flattened
    // shape the template graph historically consumed, but gated state now has
    // explicit, dependency-visible hold semantics.
    val clockLowered = ClockDomainLowering.lower(circuit)
    val disableDeadStatePrune = sys.env.get("V2_DISABLE_DEAD_STATE_PRUNE")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    val deadState =
      if (!keepSourceEffects && !disableDeadStatePrune)
        pruneDeadRegisters(clockLowered.stmts, circuit)
      else DeadRegisterPrune(clockLowered.stmts, Seq.empty,
        clockLowered.stmts.count(_.isInstanceOf[DefRegister]))
    val rawFlatStmts = deadState.stmts
    if (!keepSourceEffects) {
      val monitorCount = deadState.removed.count(_.contains(".monitor."))
      val mode = if (disableDeadStatePrune) "disabled" else "enabled"
      println(s"[v2-dead-state] prune=$mode source-registers=${deadState.sourceRegisters} " +
        s"removed=${deadState.removed.size} monitor=$monitorCount " +
        s"retained=${deadState.sourceRegisters - deadState.removed.size}")
      if (deadState.removed.nonEmpty)
        println(s"[v2-dead-state] first removed: ${deadState.removed.take(8).mkString(", ")}")
    }
    val bankRewrite = packFlatRegisters(rawFlatStmts,
      configuredRegisterBankPrefixes,
      configuredRegisterBankExcludeSuffixes)
    val flatStmts = bankRewrite.stmts
    if (configuredRegisterBankPrefixes.nonEmpty)
      println(s"[v2-reg-bank] eligible=${bankRewrite.eligibleLeaves} " +
        s"packed=${bankRewrite.packedLeaves} banks=${bankRewrite.banks.size} " +
        s"forwardFull=${bankRewrite.fullBankForwards} " +
        s"forwardMasked=${bankRewrite.maskedBankForwards} " +
        s"forwardedFields=${bankRewrite.forwardedFields} " +
        s"prefixes=${configuredRegisterBankPrefixes.mkString(",")} " +
        s"excludeSuffixes=${configuredRegisterBankExcludeSuffixes.mkString(",")}")

    val moduleInstances = findAllModuleInstances(circuit)
    val extModules = circuit.modules.collect { case module: ExtModule =>
      module.name -> module
    }.toMap
    val hostBoundaryInputs = moduleInstances.flatMap { case (module, prefix) =>
      extModules.get(module).toSeq.flatMap(_.ports.collect {
        case Port(_, name, Input, tpe) if tpe != ClockType => prefix + name
      })
    }.toSet
    val annotatedIndexedBanks = indexedCounterBankAnnotations.flatMap { annotation =>
      moduleInstances.collect { case (module, prefix) if module == annotation.module => prefix }
        .flatMap { prefix =>
          annotation.banks.zipWithIndex.map { case (bank, bankIndex) =>
            val chunk = annotation.membersByIndex.slice(bankIndex * 64, bankIndex * 64 + 64)
            val fields = chunk.zipWithIndex.reverse.map { case (member, bit) =>
              RegisterBankField(prefix + member, 1, bit, bit)
            }
            RegisterBankInfo(prefix + bank, chunk.size, fields)
          }
        }
    }
    val survivingFlatRegisters = flatStmts.collect {
      case register: DefRegister => register.name
    }.toSet
    def statementReadsName(statement: Statement, name: String): Boolean = {
      var found = false
      def walk(value: Expression): Unit = if (!found) value match {
        case WRef(current, _, _, _) if current == name => found = true
        case other => other.foreachExpr(walk)
      }
      statement.foreachExpr(walk)
      found
    }
    val (indexedCounterBanks, eliminatedIndexedBanks) =
      annotatedIndexedBanks.partition(bank => survivingFlatRegisters(bank.name))
    if (eliminatedIndexedBanks.nonEmpty) {
      val referenced = eliminatedIndexedBanks.filter(bank =>
        flatStmts.exists(statement => statementReadsName(statement, bank.name)))
      require(referenced.isEmpty,
        s"[v2-indexed-bank] eliminated compiler banks still have references: " +
          s"${referenced.take(5).map(_.name).mkString(", ")}")
      println(s"[v2-indexed-bank] omitted ${eliminatedIndexedBanks.size} dead " +
        s"compiler bank(s), ${eliminatedIndexedBanks.map(_.fields.size).sum} source bit(s)")
    }
    // Compiler-created banks are physical storage synthesized from source RTL
    // leaves.  They are not independent architectural values and therefore
    // must never be turned back into oracle streams by the cond-hold
    // experiment.  Establish ownership before recurrence planning so the
    // banks keep their exact local semantics.
    val allRegisterBanks = bankRewrite.banks ++ indexedCounterBanks
    val compilerOwnedBankNames = allRegisterBanks.iterator.map(_.name).toSet
    // Self-recurrent banks cannot zipper (their wdata reads the bank), so
    // freezing them would strand a per-lane serial recurrence with no
    // injection escape. They stay oracle-eligible and are force-dissolved.
    val selfRecurrentBankNames = bankRewrite.banks.iterator
      .filter(_.selfRecurrent).map(_.name).toSet
    val frozenBankNames = compilerOwnedBankNames -- selfRecurrentBankNames
    if (selfRecurrentBankNames.nonEmpty)
      println(s"[v2-reg-bank] self-recurrent banks kept oracle-eligible: " +
        s"${selfRecurrentBankNames.size}")
    if (indexedCounterBanks.nonEmpty)
      println(s"[v2-indexed-bank] backend accepted ${indexedCounterBanks.size} " +
        s"packed register bank(s), ${indexedCounterBanks.map(_.fields.size).sum} source bit(s)")
    val annotatedStateNames = mutable.LinkedHashMap[String, StateArrayStorageAnnotation]()
    for (ann <- stateArrayAnnotations; (module, prefix) <- moduleInstances if module == ann.module) {
      val flatName = prefix + ann.memory
      require(!annotatedStateNames.contains(flatName),
        s"[v2-state-array] duplicate flattened storage annotation for '$flatName'")
      annotatedStateNames(flatName) = ann
    }

    val regDefs = mutable.LinkedHashMap[String, DefRegister]()
    val regCommitStmt = mutable.LinkedHashMap[String, RegUpdate]()
    val stateMemDefs = mutable.LinkedHashMap[String, DefMemory]()
    val stateWrites = mutable.LinkedHashMap[String, ArrayBuffer[MemWrite]]()
    val combStmts = ArrayBuffer[Statement]()
    val effectStmts = ArrayBuffer[Statement]()
    var removedSourceEffects = 0

    flatStmts.foreach {
      case r: DefRegister => regDefs(r.name) = r
      // Every lowered FIRRTL memory is persistent chronological state.  The
      // previous fail-closed rule accepted only compiler-created ROB arrays,
      // which made a complete TestHarness impossible: ordinary queues,
      // caches, register files, and AXI RAM all remain DefMemory after the
      // scalar transform stack.  Treat them through the same exact
      // read-before-write/window-forwarding contract; annotations add source
      // field metadata but no longer grant exclusive permission to exist.
      case m: DefMemory => stateMemDefs(m.name) = m
      case ru: RegUpdate => regCommitStmt(emitExpr(ru.regRef)(null, essent.Emitter.DefaultContext)) = ru
      case d: DefNode => combStmts += d
      case c: Connect => combStmts += c
      case p: Print =>
        if (keepSourceEffects) effectStmts += p else removedSourceEffects += 1
      case st: Stop =>
        if (keepSourceEffects) effectStmts += st else removedSourceEffects += 1
      case mw: MemWrite => stateWrites.getOrElseUpdate(mw.memName, ArrayBuffer()) += mw
      case EmptyStmt =>
      case _: WDefInstance | _: DefInstance =>  // hierarchy handled via name prefixes
      case dw: DefWire =>
        throw new IllegalStateException(s"[v2] unexpected DefWire '${dw.name}' after RemoveWires")
      case other =>
        throw new IllegalStateException(s"[v2] unhandled statement kind: ${other.getClass.getSimpleName}")
    }
    if (!keepSourceEffects)
      println(s"[v2] performance build: removed $removedSourceEffects source Print/Stop effect(s); " +
        "oracle Micro-Lockstep verification remains enabled")
    // Paper E1: graph size for oracle density (comb = lowered DefNode+Connect
    // before template pruning; regs = registers after dead-state prune, storage
    // lifts and bank packing).
    println(s"[v2] graph comb=${combStmts.size} regs=${regDefs.size} " +
      s"mems=${stateMemDefs.size} total=${combStmts.size + regDefs.size}")

    // Sanity: every register has exactly one commit statement.
    val missingCommit = regDefs.keySet -- regCommitStmt.keySet
    if (missingCommit.nonEmpty)
      throw new IllegalStateException(s"[v2] registers without RegUpdate: ${missingCommit.take(5).mkString(", ")}")
    val missingIndexedBanks = indexedCounterBanks.iterator.map(_.name).filterNot(regDefs.contains).toSeq
    if (missingIndexedBanks.nonEmpty)
      throw new IllegalStateException(
        s"[v2-indexed-bank] annotated banks not found: ${missingIndexedBanks.take(5).mkString(", ")}")
    val missingStateDefs = annotatedStateNames.keySet -- stateMemDefs.keySet
    if (missingStateDefs.nonEmpty) {
      val referenced = missingStateDefs.filter(name =>
        flatStmts.exists(statement => statementReadsName(statement, name)))
      if (referenced.nonEmpty)
        throw new IllegalStateException(
          s"[v2-state-array] annotated memories not found but still referenced: " +
            referenced.take(5).mkString(", "))
      val omittedFields = missingStateDefs.iterator
        .flatMap(name => annotatedStateNames.get(name).iterator)
        .map(_.fields.size).sum
      missingStateDefs.foreach(annotatedStateNames.remove)
      println(s"[v2-state-array] omitted ${missingStateDefs.size} dead " +
        s"compiler-lifted array instance(s), $omittedFields source field group(s)")
    }
    val unknownStateWrites = stateWrites.keySet -- stateMemDefs.keySet
    if (unknownStateWrites.nonEmpty)
      throw new IllegalStateException(
        s"[v2-state-array] factored writes without memory definitions: ${unknownStateWrites.take(5).mkString(", ")}")
    for ((name, mem) <- stateMemDefs) {
      val actual = stateWrites.getOrElse(name, ArrayBuffer()).size
      if (actual != mem.writers.size)
        throw new IllegalStateException(
          s"[v2-state-array] '$name' has $actual factored writes, expected ${mem.writers.size}")
    }

    // ---- template nodes ----
    val nodes = ArrayBuffer[TemplateNode]()
    def addNode(stmt: Statement, role: Role, produces: Option[String]): Int = {
      val id = nodes.size
      nodes += TemplateNode(id, stmt, role, produces)
      id
    }

    def stateReadArray(s: Statement): Option[String] = s match {
      case DefNode(_, _, WSubAccess(WRef(mem, _, MemKind, _), _, _, _))
          if stateMemDefs.contains(mem) => Some(mem)
      case _ => None
    }
    val stateReadIds = mutable.LinkedHashMap[String, ArrayBuffer[Int]]()
    combStmts.foreach { s =>
      val role = stateReadArray(s).map(RStateRead).getOrElse(RComb)
      val id = addNode(s, role, findResultName(s))
      stateReadArray(s).foreach(mem => stateReadIds.getOrElseUpdate(mem, ArrayBuffer()) += id)
    }
    effectStmts.foreach { s => addNode(s, REffect, None) }
    val stateCommitIds = mutable.LinkedHashMap[String, Int]()
    for ((name, _) <- stateMemDefs) {
      val writes = stateWrites.getOrElse(name, ArrayBuffer()).toSeq
      val grouped: Statement = writes.size match {
        case 0 => EmptyStmt
        case 1 => writes.head
        case _ => Block(writes)
      }
      stateCommitIds(name) = addNode(grouped, RStateCommit(name), None)
    }
    val externArrayFamilies = configuredExternalArrayFamilies
    val stateArrayInfos: Map[String, StateArrayInfo] = stateMemDefs.iterator.map {
      case (name, mem) =>
        val ann = annotatedStateNames.get(name)
        ann.foreach { a =>
          require(a.fields.size == a.fieldWidths.size,
            s"[v2-state-array] '${name}' field/width metadata size mismatch")
          require(name.endsWith(a.memory),
            s"[v2-state-array] flattened name '$name' does not end in '${a.memory}'")
        }
        val sourceRegister = ann
          .map(a => name.stripSuffix(a.memory) + a.register).getOrElse(name)
        val fields = ann.map(a => a.fields.zip(a.fieldWidths))
          .getOrElse(Seq("data" -> firrtl.bitWidth(mem.dataType).toInt))
        val reads = stateReadIds.getOrElse(name, ArrayBuffer()).toSeq
        val fullyExternal = externArrayFamilies.exists(
          externalArrayFamilyMatches(name, _))
        val readAccess = if (!fullyExternal) Seq.empty else reads.map { tid =>
          val dataName = nodes(tid).stmt match {
            case d: DefNode => d.name
            case other => throw new IllegalStateException(
              s"[v2-extern-array] read template $tid of '$name' is " +
                s"${other.getClass.getSimpleName}, expected DefNode")
          }
          StateArrayReadAccess(dataName, readAddressOracleName(dataName))
        }
        val writeAccess = if (!fullyExternal) Seq.empty else
          stateWrites.getOrElse(name, ArrayBuffer()).toSeq.zipWithIndex.map {
            case (write, index) =>
              val (enable, address, data) =
                writeAccessOracleNames(name, index, write.portName)
              StateArrayWriteAccess(write.portName, enable, address, data)
          }
        name -> StateArrayInfo(name, sourceRegister, mem.dataType, mem.depth.toInt,
          fields, reads, stateWrites.getOrElse(name, ArrayBuffer()).size,
          compilerLifted = ann.isDefined, commitId = stateCommitIds(name),
          fullyExternal = fullyExternal, readAccess = readAccess,
          writeAccess = writeAccess)
    }.toMap
    val unmatchedExternArrayFamilies = externArrayFamilies.filterNot(family =>
      stateArrayInfos.keysIterator.exists(
        externalArrayFamilyMatches(_, family)))
    require(unmatchedExternArrayFamilies.isEmpty,
      s"[v2-extern-array] configured family/families matched no persistent array: " +
        unmatchedExternArrayFamilies.mkString(", "))
    if (stateArrayInfos.nonEmpty)
      println(s"[v2-state-array] backend accepted ${stateArrayInfos.size} chronological array(s), " +
        s"${stateArrayInfos.values.count(_.compilerLifted)} compiler-lifted, " +
        s"${stateArrayInfos.values.map(_.readIds.size).sum} read port(s), " +
        s"${stateArrayInfos.values.map(_.writePorts).sum} write port(s), " +
        s"${stateArrayInfos.values.count(_.fullyExternal)} fully external")

    // Conditional-hold extraction: a register whose next-expression reads the
    // register itself (r' = wen ? wdata : r and generalizations) is lowered to
    // a per-lane serial source chain r[k] = wen[k-1] ? wdata[k-1] : r[k-1]
    // instead of demanding an oracle. In the template graph the serial part is
    // confined to the source template alone (self +1 edge => singleton SCC);
    // wen/wdata computation and every reader stay fully vectorized.
    val nodeMap = essent.passes.SplitRegUpdates.buildDefNodeMap(Block(combStmts.toSeq))
    val indexedStorageReadCutCandidates = findIndexedReadCutCandidates(
      combStmts.toSeq, regDefs.keySet.toSet, configuredIndexedReadCutFamilies)
    val bitsetReadCutCandidates = findBitsetReadCutCandidates(
      combStmts.toSeq, indexedCounterBanks, configuredBitsetReadCutFamilies)
    if (configuredBitsetReadCutFamilies.nonEmpty)
      println(s"[v2] bitset read-cut candidates: ${bitsetReadCutCandidates.size}" +
        bitsetReadCutCandidates.take(8).map(candidate =>
          s" ${candidate.name}[${candidate.leaves.size}]").mkString)
    val indexedReadCutCandidates = (
      indexedStorageReadCutCandidates ++ bitsetReadCutCandidates
      ).sortBy(candidate => (-candidate.leaves.size, candidate.name))
    val indexedReadFoldBarriers = indexedReadCutCandidates.iterator.map(_.name).toSet
    // State-array read results are materialized per lane by the dedicated
    // read machinery and must never be inlined into a folded serial-next
    // expression: the generic expression emitter has no rendering for a raw
    // array access, so an inlined WSubAccess crashes emission.  This was
    // masked for years by unlimited oracle budgets (the affected registers
    // were always oracled away before their folded plan could be emitted)
    // and surfaced on the first full-chip low-budget sweep.
    val stateReadFoldBarriers: Set[String] = combStmts.iterator
      .filter(s => stateReadArray(s).isDefined)
      .flatMap(findResultName)
      .toSet

    val regInfos = mutable.LinkedHashMap[String, RegInfo]()
    val condHold = mutable.LinkedHashMap[String, (Expression, Expression)]() // reg -> (wen, wdata)
    val guardWen = mutable.LinkedHashMap[String, Expression]() // reg -> self-free wen (RMW guard)
    val affineHold = mutable.LinkedHashMap[String, (Expression, Expression)]() // reg -> (keep, add)
    val affineScanEnabled = sys.env.get("V2_AFFINE_SCAN").forall(v =>
      v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    val selfRefRegs = mutable.Set[String]()  // $next cone reads the register itself
    // Preserve the exact write-enable expression for every extractable
    // mux-hold register, including candidates later forced through RPOracle.
    // LowerTypes flattens bundles field-by-field, so a raw oracle count hides
    // whether hundreds of streams are really one logical structure updated
    // by one shared enable. The audit report groups equal serialized wens.
    val muxHoldWenByReg = mutable.LinkedHashMap[String, String]()
    // Keep the extracted expressions for every eligible mux-hold register.
    // Under a finite oracle budget, V2_ORACLE_CONDHOLD initially presents
    // these as honest RPShift SCC candidates; any candidate not selected by
    // the budget must later fall back to RPCondHold, which needs the original
    // wen/wdata pair materialized as vector comb templates.
    val muxHoldExprByReg = mutable.LinkedHashMap[String, (Expression, Expression)]()
    // V2_ORACLE_CONDHOLD experiment: emit mux-hold registers as ordinary
    // oracled registers instead of condhold zipper chains. Motivation (BOOM
    // small): 1130 singleton zipper regions fragment the fused comb runs
    // (1283 runs of <=2 templates) and serialize W-deep scans; oracling them
    // trades that for one trace stream per register. Off by default.
    val oracleCondholdExp = sys.env.get("V2_ORACLE_CONDHOLD")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    // Bisection instrument: comma-separated prefixes exempted from the
    // condhold->oracle flip (they keep the zipper machinery under test);
    // every other selection decision stays identical, so each round's
    // manifest is a strict subset of the full-condoracle probe set.
    val condOracleExcept = sys.env.get("V2_ORACLE_CONDHOLD_EXCEPT")
      .map(_.split(',').toSeq.map(_.trim).filter(_.nonEmpty)).getOrElse(Seq.empty)
    val condOracleCands = mutable.Set[String]()
    for ((rName, rDef) <- regDefs) {
      val nextName = rName + "$next"
      val nextExpr = nodeMap.get(nextName)
      val selfRef = nextExpr.exists(e => transitiveReads(e, nodeMap).contains(rName))
      if (selfRef) selfRefRegs += rName
      val plan =
        if (!selfRef) RPShift
        else {
          val ext = essent.passes.SplitRegUpdates.extractMuxHoldPattern(
            nextExpr.get, rName, nodeMap, 0, serialOk = true)
          val extSelfFree = ext.exists { case (wen, wdata) =>
            !transitiveReads(wen, nodeMap).contains(rName) &&
            !transitiveReads(wdata, nodeMap).contains(rName)
          }
          if (extSelfFree) {
            muxHoldExprByReg(rName) = ext.get
            muxHoldWenByReg(rName) = ext.get._1.serialize
          }
          if (extSelfFree && keepMuxHoldLocal(rName, firrtl.bitWidth(rDef.tpe),
              oracleCondholdExp, compilerOwnedBankNames, freezePrefixes,
              condOracleExcept)) {
            // Frozen registers keep the zipper under V2_ORACLE_CONDHOLD, so a
            // freeze-prefix bisection exercises the original condhold
            // machinery for the frozen group instead of the honest per-lane
            // fallback (which would mask a zipper-family bug).
            condHold(rName) = ext.get
            RPCondHold
          } else if (extSelfFree) {
            // Experiment path: keep the honest singleton self-loop SCC; the
            // extended phase-3 dissolve oracles it (frozen regs stay serial).
            condOracleCands += rName
            RPShift
          } else if (affineScanEnabled && W >= 16 && (W & (W - 1)) == 0 &&
              affinePattern(nextExpr.get, rName, nodeMap, rDef.tpe).isDefined) {
            // W >= 16 only: below that the scan has no vector path, and the
            // scalar chain it would fall back to made clang scalarize the
            // producers of `add` as well (MatMul W8: 2x slower than the
            // serial-next chain, which stays in charge for narrow windows).
            // Accumulator / enabled counter: next ≡ keep ? r + add : add with
            // self-free keep/add. Materialized below; the source becomes a
            // parallel prefix scan instead of a per-lane serial chain.
            affineHold(rName) = affinePattern(nextExpr.get, rName, nodeMap, rDef.tpe).get
            RPAffineScan
          } else foldSelfNext(nextExpr.get, rName, nodeMap, cap = 32,
              foldBarriers =
                indexedReadFoldBarriers ++ stateReadFoldBarriers) match {
            // wen/wdata still read the register (counters, RMW CSRs): a
            // cond-hold lowering would drag the tainted cone into the SCC
            // per-lane, and oracling costs a memory stream per register
            // (measured net-negative on sodor). Fold the tainted cone into
            // one serial expression instead when it is small.
            case Some(folded) =>
              // RMW guard: next ≡ wen ? wdata : r with wen self-free (only
              // wdata reads r). Materialize wen as a vector template; the
              // emitter OR-reduces the window and broadcasts the boundary
              // lane when no lane writes (CSR-quiet window, common case).
              // A trivially-true wen (literal 1) guards nothing — skip.
              // (Soundness note, checked 2026-08-11: the serialOk identity
              // fallback yields wen=1 for non-hold shapes like BOOM's split
              // cycle counter, so their broadcast arm is dead code, never
              // wrong — the tautological guard is wasteful but harmless.)
              val wenGuard = ext.collect {
                case (wen, _) if !transitiveReads(wen, nodeMap).contains(rName) &&
                  !wen.isInstanceOf[UIntLiteral] => wen
              }
              wenGuard.foreach(guardWen(rName) = _)
              RPSerialNext(legalizeWidth(folded, rDef.tpe), guarded = wenGuard.isDefined)
            case None => RPShift  // big cone: honest SCC, phase 3 decides
          }
        }
      val sourceId = addNode(EmptyStmt, RRegSource(rName), Some(rName))
      val commitId = addNode(regCommitStmt(rName), RRegCommit(rName), None)
      regInfos(rName) = RegInfo(rName, rDef.tpe, nextName, plan, sourceId, commitId, None)
    }
    def planLabel(p: RegPlan): String = p match {
      case RPShift => "shift"
      case RPCondHold => "cond-hold"
      case RPSerialNext(_, guarded) => if (guarded) "serial-next-guarded" else "serial-next"
      case RPAffineScan => "affine-scan"
      case RPOracle => "oracle"
    }
    // Snapshot the pre-oracle lowering. Later phases mutate RegInfo.plan to
    // RPOracle, which otherwise erases whether a stream replaced an ordinary
    // shift, a cond-hold experiment, or a folded serial recurrence.
    val basePlanByReg: Map[String, String] =
      regInfos.iterator.map { case (r, ri) => r -> planLabel(ri.plan) }.toMap
    val muxHoldGroupSizeByWen: Map[String, Int] =
      muxHoldWenByReg.values.groupBy(identity).map { case (wen, regs) => wen -> regs.size }
    def muxHoldAudit(r: String): (String, Int) = muxHoldWenByReg.get(r) match {
      case Some(wen) => (wen, muxHoldGroupSizeByWen(wen))
      case None => ("", 0)
    }
    val oracleAudit = mutable.LinkedHashMap[String, OracleAudit]()
    def recordAudit(a: OracleAudit): Unit = {
      require(!oracleAudit.contains(a.flatName),
        s"[v2-audit] duplicate oracle provenance for ${a.flatName}")
      oracleAudit(a.flatName) = a
    }
    // Materialize wen/wdata as ordinary vectorized comb templates. Finite-
    // budget fallback calls the same helper after oracle selection, appending
    // only the nodes that the unlimited configuration never needs.
    def materializeCondHold(rName: String, wen: Expression, wdata: Expression): Unit = {
      val rTpe = regInfos(rName).tpe
      combStmts += DefNode(NoInfo, rName + "$wen", wen)
      combStmts += DefNode(NoInfo, rName + "$wdata", legalizeWidth(wdata, rTpe))
      addNode(combStmts(combStmts.size - 2), RComb, Some(rName + "$wen"))
      addNode(combStmts(combStmts.size - 1), RComb, Some(rName + "$wdata"))
    }
    for ((rName, (wen, wdata)) <- condHold)
      materializeCondHold(rName, wen, wdata)
    // Materialize the affine step operands as ordinary vectorized templates.
    for ((rName, (keep, add)) <- affineHold) {
      val rTpe = regInfos(rName).tpe
      combStmts += DefNode(NoInfo, rName + "$keep", keep)
      combStmts += DefNode(NoInfo, rName + "$add", legalizeWidth(add, rTpe))
      addNode(combStmts(combStmts.size - 2), RComb, Some(rName + "$keep"))
      addNode(combStmts(combStmts.size - 1), RComb, Some(rName + "$add"))
    }
    if (affineHold.nonEmpty)
      println(s"[v2] affine-scan registers: ${affineHold.size} (prefix scan of keep/add step functions, no oracle)")
    // Materialize RMW guard wen as a vectorized comb template.
    for ((rName, wen) <- guardWen) {
      combStmts += DefNode(NoInfo, rName + "$gwen", wen)
      addNode(combStmts(combStmts.size - 1), RComb, Some(rName + "$gwen"))
    }
    if (condHold.nonEmpty)
      println(s"[v2] conditional-hold registers: ${condHold.size} (serial source chain, no oracle)")
    if (guardWen.nonEmpty)
      println(s"[v2] guarded serial-next registers: ${guardWen.size} (window wen guard + broadcast fast path)")
    val combCutTypes = mutable.LinkedHashMap[String, Type]()
    val directBankWdataSource: Map[String, String] = bankRewrite.banks.iterator
      .flatMap(bank => bank.forwardSource.map(bank.name -> _)).toMap

    def buildEdges(infos: collection.Map[String, RegInfo]): IndexedSeq[TemplateEdge] = {
      val producesIdx: Map[String, Int] =
        nodes.iterator.flatMap(n => n.produces.map(_ -> n.id)).toMap
      val edges = ArrayBuffer[TemplateEdge]()
      for (n <- nodes) n.role match {
        case RComb | REffect =>
          for (read <- stmtReads(n.stmt).distinct) {
            producesIdx.get(read).foreach { defId =>
              if (defId != n.id) edges += TemplateEdge(defId, n.id, EData)
            }
            infos.get(read).foreach { ri =>            // reader of a register
              edges += TemplateEdge(n.id, ri.commitId, EWar)
            }
          }
        case RStateRead(array) =>
          // Same-cycle address operands are ordinary EData dependencies.
          for (read <- stmtReads(n.stmt).distinct if read != array) {
            producesIdx.get(read).foreach { defId =>
              if (defId != n.id) edges += TemplateEdge(defId, n.id, EData)
            }
            infos.get(read).foreach(ri => edges += TemplateEdge(n.id, ri.commitId, EWar))
          }
          // The read primitive forwards writes from chronologically earlier
          // lanes.  An EShift edge captures that cross-cycle dependence; the
          // emitter performs the full nearest-writer search, not just k-1.
          val si = stateArrayInfos(array)
          for (read <- stmtReads(nodes(si.commitId).stmt).distinct) {
            producesIdx.get(read).foreach { defId =>
              edges += TemplateEdge(defId, n.id, EShift)
            }
            infos.get(read).foreach(ri => edges += TemplateEdge(n.id, ri.commitId, EWar))
          }
          // Keep the physical pre-window image immutable until every port has
          // read it; forwarding supplies all within-window updates.
          edges += TemplateEdge(n.id, si.commitId, EWar)
        case RStateCommit(array) =>
          val si = stateArrayInfos(array)
          for (read <- stmtReads(n.stmt).distinct) {
            producesIdx.get(read).foreach { defId =>
              if (defId != n.id) edges += TemplateEdge(defId, n.id, EData)
            }
            // A direct register operand must be captured before its lane
            // array is overwritten by the normal register commit.
            infos.get(read).foreach(ri => edges += TemplateEdge(n.id, ri.commitId, EWar))
          }
          si.readIds.foreach(rid => edges += TemplateEdge(rid, n.id, EWar))
        case RRegSource(r) =>
          val ri = infos(r)
          ri.plan match {
            case RPCondHold =>
              producesIdx.get(r + "$wen").foreach(id => edges += TemplateEdge(id, ri.sourceId, EShift))
              producesIdx.get(r + "$wdata").foreach(id => edges += TemplateEdge(id, ri.sourceId, EShift))
              // A direct bank wdata alias removes the scratch snapshot that
              // otherwise survives a source-bank commit.  Keep the target
              // scan before that commit so it reads the source's cycle-lane
              // image, exactly as the materialized wdata node did.
              directBankWdataSource.get(r).flatMap(infos.get).foreach { sourceRi =>
                edges += TemplateEdge(ri.sourceId, sourceRi.commitId, EWar)
              }
              edges += TemplateEdge(ri.sourceId, ri.sourceId, EShift)  // serial chain
            case RPAffineScan =>
              // Both step operands are read at lane k-1 (whole window before
              // the scan); the self edge marks the source as a serial chain
              // that the emitter rolls into one prefix-scan call.
              producesIdx.get(r + "$keep").foreach(id => edges += TemplateEdge(id, ri.sourceId, EShift))
              producesIdx.get(r + "$add").foreach(id => edges += TemplateEdge(id, ri.sourceId, EShift))
              edges += TemplateEdge(ri.sourceId, ri.sourceId, EShift)
            case RPSerialNext(folded, guarded) =>
              // Operands are read at lane k-1: EShift from every producer.
              // Direct reads of OTHER registers need a WAR edge before their
              // commit clobbers the previous-lane value.
              for (read <- exprReads(folded).distinct if read != r) {
                producesIdx.get(read).foreach(id => edges += TemplateEdge(id, ri.sourceId, EShift))
                infos.get(read).foreach(ri2 => edges += TemplateEdge(ri.sourceId, ri2.commitId, EWar))
              }
              // Guard reduce reads the whole $gwen window before the chain.
              if (guarded)
                producesIdx.get(r + "$gwen").foreach(id => edges += TemplateEdge(id, ri.sourceId, EShift))
              edges += TemplateEdge(ri.sourceId, ri.sourceId, EShift)  // serial chain
            case _ =>
              producesIdx.get(ri.nextName).foreach { nid =>
                edges += TemplateEdge(nid, ri.sourceId, EShift)
              }
          }
          edges += TemplateEdge(ri.sourceId, ri.commitId, EWar)
        case ROracleInject(r) =>
          // register inject: WAR before commit; comb inject: no in-edges at all
          infos.get(r).foreach { ri =>
            edges += TemplateEdge(ri.sourceId, ri.commitId, EWar)
          }
        case RRegCommit(r) =>
          val ri = infos(r)
          producesIdx.get(ri.nextName).foreach { nid =>
            edges += TemplateEdge(nid, ri.commitId, EData)
          }
        case RVerify(r) =>
          infos.get(r) match {
            case Some(ri) =>
              producesIdx.get(ri.nextName).foreach { nid =>
                edges += TemplateEdge(nid, n.id, EData)
              }
              edges += TemplateEdge(ri.sourceId, n.id, EData)  // reads injected lanes
              edges += TemplateEdge(n.id, ri.commitId, EWar)   // before commit clobbers
            case None =>  // comb cut verify: reads computed $rtl and injected value
              producesIdx.get(r + "$rtl").foreach(nid => edges += TemplateEdge(nid, n.id, EData))
              producesIdx.get(r).foreach(oid => edges += TemplateEdge(oid, n.id, EData))
          }
      }
      // Effects on the same memory / all Print+Stop: keep program order per lane
      // via a chain (conservative; effects are rare and cheap).
      val effectIds: Seq[Int] = nodes.filter(_.role == REffect).map(_.id).toSeq
      effectIds.sliding(2).foreach { pair =>
        if (pair.size == 2) edges += TemplateEdge(pair(0), pair(1), EData)
      }
      edges.toIndexedSeq
    }

    // ---- oracle selection: Tarjan on the full template graph ----
    var edges = buildEdges(regInfos)
    var sccs = tarjan(nodes.size, edges)
    // A freeze prefix matches either the register's short name or its full
    // flattened path (e.g. "fpu." freezes every register under the FPU).
    val frozen = (r: String) =>
      frozenBankNames(r) ||
        freezePrefixes.exists(p => r.startsWith(p) || r.split('.').last.startsWith(p))

    // Phase 1 — combinational cut points. Cutting one high-fanout control
    // signal (e.g. stall) can break the cycles of MANY registers at the cost
    // of ONE trace stream, so comb cuts are tried before register FVS.
    // Mechanics (no name surgery): the computed DefNode is renamed to
    // `n$rtl`; a new injection template produces `n` with no in-edges;
    // readers rebind to the injection automatically when edges are rebuilt
    // from `produces`. A verify template compares n$rtl vs n per lane.
    // Objective: minimize the FINAL number of oracle streams. A cut is worth
    // taking iff it frees at least one register from the multi-node SCCs
    // (a register in such an SCC will otherwise cost one FVS oracle stream),
    // so the gain metric is the drop in cyclic-register count, mirroring the
    // v1 selector that this rework had not fully restored.
    val combCuts = mutable.LinkedHashSet[String]()
    // Extern read ports (V2_EXTERN_READ_FAMILIES), see phase 4b below.  With
    // V2_EXTERN_READ_FIRST=1 the same flip runs before the cut-point and FVS
    // phases, so every loop that closes only through an externalized array is
    // already open when register oracles are selected (experiment: fewer
    // register streams for the same family list; the register FVS then
    // depends on the family list, which the anchored wide emits preserve).
    val externReadFamilies = sys.env.get("V2_EXTERN_READ_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty)
    val externReadFirst = sys.env.get("V2_EXTERN_READ_FIRST")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    def externalizeReadPorts(stage: String): Unit = if (externReadFamilies.nonEmpty) {
      var flipped = 0
      var skippedWide = 0
      for ((array, tids) <- stateReadIds
           if externReadFamilies.exists(array.contains(_)) &&
             !stateArrayInfos(array).fullyExternal;
           tid <- tids) {
        val d = nodes(tid).stmt match {
          case dn: DefNode => dn
          case other => throw new IllegalStateException(
            s"[v2-extern-read] read template $tid of '$array' is ${other.getClass.getSimpleName}, expected DefNode")
        }
        if (firrtl.bitWidth(d.value.tpe) > 64) { skippedWide += 1 }
        else {
          nodes(tid) = nodes(tid).copy(
            stmt = d.copy(name = d.name + "$rtl"),
            produces = Some(d.name + "$rtl"))
          addNode(EmptyStmt, ROracleInject(d.name), Some(d.name))
          if (wantVerify) addNode(EmptyStmt, RVerify(d.name), None)
          combCuts += d.name
          combCutTypes(d.name) = d.value.tpe
          recordAudit(OracleAudit(
            flatName = d.name,
            kind = "comb",
            stage = stage,
            reason = "extern-read-family",
            basePlan = "state-read",
            widthBits = firrtl.bitWidth(d.value.tpe).toInt,
            sccKey = tid,
            sccTemplates = 1,
            sccCombTemplates = 0,
            sccRegSources = 0,
            sccSelfSources = 0,
            groupOracleCandidates = tids.size,
            selectedRank = flipped,
            benefitEstimate = 0L,
            costEstimate = 0L,
            cyclicRegDrop = -1,
            cyclicTemplateDrop = -1,
            matchedPrefix = externReadFamilies.find(array.contains(_)).getOrElse(""),
            condHoldCandidate = false,
            forcedSerial = false))
          flipped += 1
        }
      }
      println(s"[v2] extern read ports: $flipped read stream(s) externalized" +
        (if (skippedWide > 0) s", $skippedWide skipped (>64 bits)" else ""))
      if (flipped > 0) {
        edges = buildEdges(regInfos)
        sccs = tarjan(nodes.size, edges)
      }
    
    }
    if (externReadFirst) externalizeReadPorts("phase4-extern-read")
    // ClockDomainLowering creates shared enable aliases so hundreds of gated
    // next-state muxes do not duplicate one expression.  They are compiler
    // plumbing, not RTL observables: selecting one as a combinational oracle
    // produces a manifest path that no Verilator/source-RTL tap can resolve.
    // Leave the real cross-cycle feedback to register FVS selection instead.
    val compilerCombOracleExclusions = clockLowered.report.enableNodes.toSet
    // Lifting rewrites one module before RemoveAccesses/ExpandWhens, so that
    // module's compiler-generated _GEN numbering intentionally differs from
    // the untouched scalar trace compiler.  A comb oracle there would name a
    // probe that cannot exist in both images.  Register trace keys remain
    // stable, so keep comb cuts outside every lifted-state instance prefix.
    val liftedStatePrefixes: Set[String] = stateArrayInfos.keysIterator.map { name =>
      val dot = name.lastIndexOf('.')
      if (dot < 0) "" else name.substring(0, dot + 1)
    }.toSet
    def insideLiftedStateModule(name: String): Boolean =
      liftedStatePrefixes.exists(prefix => prefix.isEmpty || name.startsWith(prefix))
    def oracleBudgetLeft(chosenRegs: Int = 0): Int =
      if (oracleLimit < 0) Int.MaxValue
      else math.max(0, oracleLimit - combCuts.size - chosenRegs)
    // V2_WIDE_ORACLE=1: UInt registers wider than 64 bits may become oracles.
    // The manifest splits such a register into 64-bit word streams
    // (`<key>__w<i>`), injected into the wide POD's word array; verification
    // compares the whole value.  SInt registers stay excluded.
    val wideOracleEnabled = sys.env.get("V2_WIDE_ORACLE")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    def cyclicRegCount(es: CIndexedSeq[TemplateEdge]): Int =
      tarjan(nodes.size, es).filter(_.size > 1).flatten.count(id => nodes(id).role match {
        case RRegSource(_) => true
        case _ => false
      })
    // V2_NO_COMB_CUT: disable combinational cut-point injection entirely
    // (single-variable discrimination experiment for the cycle-534785 bug).
    val noCombCut = sys.env.get("V2_NO_COMB_CUT")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))

    // Prefer the complete output of a proven indexed storage-read mux over
    // an arbitrary high-degree node in its middle.  The recognizer is
    // opt-in and fail-closed; if the proposed root does not actually remove
    // at least two cyclic register sources, leave the graph untouched and
    // let the ordinary selector handle it.
    if (!oracleAll && !noCombCut && indexedReadCutCandidates.nonEmpty) {
      for ((candidate, rank) <- indexedReadCutCandidates.zipWithIndex
          if candidate.reason != "bitset-reduction-read" &&
            oracleBudgetLeft() > 0 && !combCuts(candidate.name)) {
        val idByName = nodes.iterator.flatMap(node => node.produces.map(_ -> node.id)).toMap
        idByName.get(candidate.name).foreach { id =>
          val currentSccs = tarjan(nodes.size, edges)
          currentSccs.find(scc => scc.size > 1 && scc.contains(id)).foreach { scc =>
            val eligible = nodes(id).role == RComb &&
              !compilerCombOracleExclusions(candidate.name) &&
              !insideLiftedStateModule(candidate.name) &&
              (nodes(id).stmt match {
                case d: DefNode => firrtl.bitWidth(d.value.tpe) <= 64
                case _ => false
              })
            if (eligible) {
              val baseCyclicRegs = cyclicRegCount(edges)
              val baseCyclicTpl = currentSccs.filter(_.size > 1).map(_.size).sum
              val trimmed = edges.filterNot(_.from == id)
              val regDrop = baseCyclicRegs - cyclicRegCount(trimmed)
              val tplDrop = baseCyclicTpl -
                tarjan(nodes.size, trimmed).filter(_.size > 1).map(_.size).sum
              if (regDrop >= 2) {
                val d = nodes(id).stmt.asInstanceOf[DefNode]
                nodes(id) = nodes(id).copy(
                  stmt = d.copy(name = d.name + "$rtl"),
                  produces = Some(d.name + "$rtl"))
                addNode(EmptyStmt, ROracleInject(d.name), Some(d.name))
                if (wantVerify) addNode(EmptyStmt, RVerify(d.name), None)
                combCuts += d.name
                combCutTypes(d.name) = d.value.tpe
                recordAudit(OracleAudit(
                  flatName = d.name,
                  kind = "comb",
                  stage = if (candidate.reason == "bitset-reduction-read")
                    "phase1-bitset-read-cut" else "phase1-indexed-read-cut",
                  reason = candidate.reason,
                  basePlan = "comb",
                  widthBits = firrtl.bitWidth(d.value.tpe).toInt,
                  sccKey = scc.min,
                  sccTemplates = scc.size,
                  sccCombTemplates = scc.count(x => nodes(x).role == RComb),
                  sccRegSources = scc.count(x => nodes(x).role match {
                    case RRegSource(_) => true
                    case _ => false
                  }),
                  sccSelfSources = scc.count(x => nodes(x).role match {
                    case RRegSource(r) => selfRefRegs.contains(r)
                    case _ => false
                  }),
                  groupOracleCandidates = candidate.leaves.size,
                  selectedRank = rank,
                  benefitEstimate = tplDrop.toLong,
                  costEstimate = 1L,
                  cyclicRegDrop = regDrop,
                  cyclicTemplateDrop = tplDrop,
                  matchedPrefix = candidate.family,
                  condHoldCandidate = false,
                  forcedSerial = false))
                edges = buildEdges(regInfos)
                println(s"[v2] storage read cut ${d.name}: " +
                  s"family=${candidate.family} entries=${candidate.leaves.size} " +
                  s"cyclicRegs=-$regDrop cyclicTemplates=-$tplDrop")
              }
            }
          }
        }
      }

      // One TLFIFOFixer bank can feed several independent FIFO-domain
      // reductions.  Cutting only one reduction leaves the recurrence alive
      // through its siblings, so a single-node benefit test rejects every
      // useful boundary.  Evaluate all proven bitset reads that share the
      // current SCC atomically; no protocol expression is added to the group,
      // because candidate recognition admitted only ORs of storage slices.
      val rankedBitsetCandidates = indexedReadCutCandidates.zipWithIndex.filter {
        case (candidate, _) => candidate.reason == "bitset-reduction-read"
      }
      if (rankedBitsetCandidates.nonEmpty) {
        val idByName = nodes.iterator.flatMap(node => node.produces.map(_ -> node.id)).toMap
        val currentSccs = tarjan(nodes.size, edges)
        val cyclicSccByNode = currentSccs.filter(_.size > 1).flatMap { scc =>
          scc.iterator.map(_ -> scc)
        }.toMap
        val groups = rankedBitsetCandidates.flatMap { case (candidate, rank) =>
          idByName.get(candidate.name).flatMap(id =>
            cyclicSccByNode.get(id).map(scc => scc.min -> (candidate, rank, id, scc)))
        }.groupBy(_._1).toSeq.sortBy(_._1)

        for ((_, entries) <- groups) {
          val members = entries.map(_._2).filter { case (candidate, _, id, _) =>
            !combCuts(candidate.name) && nodes(id).role == RComb &&
              !compilerCombOracleExclusions(candidate.name) &&
              !insideLiftedStateModule(candidate.name) &&
              (nodes(id).stmt match {
                case d: DefNode => firrtl.bitWidth(d.value.tpe) <= 64
                case _ => false
              })
          }
          if (members.nonEmpty && members.size <= oracleBudgetLeft()) {
            val cutIds = members.iterator.map(_._3).toSet
            val baseCyclicRegs = cyclicRegCount(edges)
            val baseCyclicTpl = currentSccs.filter(_.size > 1).map(_.size).sum
            val trimmed = edges.filterNot(edge => cutIds(edge.from))
            val regDrop = baseCyclicRegs - cyclicRegCount(trimmed)
            val tplDrop = baseCyclicTpl -
              tarjan(nodes.size, trimmed).filter(_.size > 1).map(_.size).sum
            println(s"[v2] bitset read-cut group probe: cuts=${members.size} " +
              s"cyclicRegs=-$regDrop cyclicTemplates=-$tplDrop")
            // At minimum the group must remove as many cyclic register
            // sources as oracle bits it costs.  The later global FVS can then
            // exploit any SCC fragmentation, while a locally loss-making
            // group remains untouched.
            if (regDrop >= members.size) {
              members.zipWithIndex.foreach {
                case ((candidate, rank, id, scc), memberIndex) =>
                  val d = nodes(id).stmt.asInstanceOf[DefNode]
                  nodes(id) = nodes(id).copy(
                    stmt = d.copy(name = d.name + "$rtl"),
                    produces = Some(d.name + "$rtl"))
                  addNode(EmptyStmt, ROracleInject(d.name), Some(d.name))
                  if (wantVerify) addNode(EmptyStmt, RVerify(d.name), None)
                  combCuts += d.name
                  combCutTypes(d.name) = d.value.tpe
                  recordAudit(OracleAudit(
                    flatName = d.name,
                    kind = "comb",
                    stage = "phase1-bitset-read-cut",
                    reason = candidate.reason,
                    basePlan = "comb",
                    widthBits = firrtl.bitWidth(d.value.tpe).toInt,
                    sccKey = scc.min,
                    sccTemplates = scc.size,
                    sccCombTemplates = scc.count(x => nodes(x).role == RComb),
                    sccRegSources = scc.count(x => nodes(x).role match {
                      case RRegSource(_) => true
                      case _ => false
                    }),
                    sccSelfSources = scc.count(x => nodes(x).role match {
                      case RRegSource(r) => selfRefRegs.contains(r)
                      case _ => false
                    }),
                    groupOracleCandidates = members.size,
                    selectedRank = rank,
                    benefitEstimate = if (memberIndex == 0) tplDrop.toLong else 0L,
                    costEstimate = 1L,
                    cyclicRegDrop = if (memberIndex == 0) regDrop else 0,
                    cyclicTemplateDrop = if (memberIndex == 0) tplDrop else 0,
                    matchedPrefix = candidate.family,
                    condHoldCandidate = false,
                    forcedSerial = false))
                  println(s"[v2] storage read cut ${d.name}: " +
                    s"family=${candidate.family} entries=${candidate.leaves.size} " +
                    s"groupCuts=${members.size}")
              }
              edges = buildEdges(regInfos)
            }
          }
        }
      }
      sccs = tarjan(nodes.size, edges)
    }

    if (!oracleAll && !noCombCut) {
      // Experiment knobs for the pre-selection cut sweep. Defaults reproduce
      // the historical behavior exactly; the sweep raises the evaluated pool
      // and lowers the acceptance threshold to measure how many register
      // oracles each additional comb cut can buy.
      val combCutCands = sys.env.get("V2_COMB_CUT_CANDS").map(_.toInt).getOrElse(32)
      val combCutMinRegDrop = sys.env.get("V2_COMB_CUT_MIN_REG_DROP").map(_.toInt).getOrElse(2)
      val combCutRounds = sys.env.get("V2_COMB_CUT_ROUNDS").map(_.toInt).getOrElse(96)
      val combCutReport = sys.env.get("V2_COMB_CUT_REPORT").contains("1")
      val combCutLog = new scala.collection.mutable.ArrayBuffer[String]()
      var changed = true
      var rounds = 0
      while (changed && rounds < combCutRounds && oracleBudgetLeft() > 0) {
        changed = false
        rounds += 1
        val baseCyclicRegs = cyclicRegCount(edges)
        val multiSccs = tarjan(nodes.size, edges).filter(_.size > 1)
        for (scc <- multiSccs if !changed && baseCyclicRegs > 0) {
          val adjIn = edges.filter(e => scc.contains(e.from) && scc.contains(e.to))
          val outDeg = adjIn.groupBy(_.from).map { case (k, v) => k -> v.size }
          val inDeg = adjIn.groupBy(_.to).map { case (k, v) => k -> v.size }
          val cands = scc.toSeq.filter { id =>
            nodes(id).role == RComb && nodes(id).produces.isDefined &&
            // synthetic v2 names ($wen/$wdata/$next/$rtl) do not exist in the
            // scalar emit and therefore cannot be traced — never cut those
            !nodes(id).produces.get.contains('$') &&
            !compilerCombOracleExclusions(nodes(id).produces.get) &&
            !insideLiftedStateModule(nodes(id).produces.get) &&
            (nodes(id).stmt match {
              case d: DefNode => firrtl.bitWidth(d.value.tpe) <= 64
              case _ => false   // ports (Connect) are pass-throughs; cut the source instead
            })
          }.sortBy(id => (
              -(outDeg.getOrElse(id, 0).toLong * inDeg.getOrElse(id, 0)),
              nodes(id).produces.getOrElse("")))
            .take(combCutCands)
          if (cands.nonEmpty) {
            val baseCyclicTpl = tarjan(nodes.size, edges).filter(_.size > 1).map(_.size).sum
            val evaluated = cands.map { id =>
              val trimmed = edges.filterNot(_.from == id)
              val regDrop = baseCyclicRegs - cyclicRegCount(trimmed)
              val tplDrop = baseCyclicTpl - tarjan(nodes.size, trimmed).filter(_.size > 1).map(_.size).sum
              (id, regDrop, tplDrop)
            }
            if (combCutReport) {
              for ((id, rd, td) <- evaluated)
                combCutLog += s"""{"round":$rounds,"name":"${nodes(id).produces.get}","regDrop":$rd,"tplDrop":$td}"""
            }
            val best = evaluated
              .maxBy(t => (t._2, t._3, nodes(t._1).produces.getOrElse("")))
            // one cut costs one oracle stream; measured on sodor, cutting for
            // cone de-serialization alone does not pay — require register gain
            // (V2_COMB_CUT_MIN_REG_DROP overrides for sweeps)
            if (best._2 >= combCutMinRegDrop) {
              val (id, regDrop, tplDrop) = best
              val d = nodes(id).stmt.asInstanceOf[DefNode]
              val name = d.name
              val sccRegSources = scc.count(x => nodes(x).role match {
                case RRegSource(_) => true
                case _ => false
              })
              val sccSelfSources = scc.count(x => nodes(x).role match {
                case RRegSource(r) => selfRefRegs.contains(r)
                case _ => false
              })
              nodes(id) = nodes(id).copy(
                stmt = d.copy(name = name + "$rtl"), produces = Some(name + "$rtl"))
              addNode(EmptyStmt, ROracleInject(name), Some(name))
              if (wantVerify) addNode(EmptyStmt, RVerify(name), None)
              combCuts += name
              combCutTypes(name) = d.value.tpe
              recordAudit(OracleAudit(
                flatName = name,
                kind = "comb",
                stage = "phase1-comb-cut",
                reason = "cyclic-register-drop",
                basePlan = "comb",
                widthBits = firrtl.bitWidth(d.value.tpe).toInt,
                sccKey = scc.min,
                sccTemplates = scc.size,
                sccCombTemplates = scc.count(x => nodes(x).role == RComb),
                sccRegSources = sccRegSources,
                sccSelfSources = sccSelfSources,
                groupOracleCandidates = cands.size,
                selectedRank = rounds - 1,
                benefitEstimate = tplDrop.toLong,
                costEstimate = 1L,
                cyclicRegDrop = regDrop,
                cyclicTemplateDrop = tplDrop,
                matchedPrefix = "",
                condHoldCandidate = false,
                forcedSerial = false))
              edges = buildEdges(regInfos)
              changed = true
            }
          }
        }
      }
      if (combCutReport && combCutLog.nonEmpty) {
        val f = new java.io.PrintWriter("comb_cut_sweep.jsonl")
        combCutLog.foreach(f.println)
        f.close()
        println(s"[v2] comb-cut sweep report: ${combCutLog.size} evaluations -> comb_cut_sweep.jsonl")
      }
      if (combCuts.nonEmpty)
        println(s"[v2] comb cut points: ${combCuts.size} (${combCuts.take(6).mkString(", ")}${if (combCuts.size > 6) ", ..." else ""})")
      require(combCuts.intersect(compilerCombOracleExclusions).isEmpty,
        "[v2-clock] compiler clock-enable node escaped as a combinational oracle")
      sccs = tarjan(nodes.size, edges)
    }

    // Phase 2 — register FVS on the residual SCCs.
    val chosen = mutable.LinkedHashSet[String]()

    // ---- Two-level parallelism (RepCut-style partitions x CHISA lanes) ----
    // V2_PARTITION_FILE: lines "<index> <flat-name prefix>". Registers, state
    // arrays and effects are owned by the longest matching prefix (default 0).
    // A partition evaluates the cone of its own registers' next state; every
    // register that cone reads from another partition is forced to an oracle
    // (the cut set), so partitions never exchange data inside a window and
    // each host thread can run its own harness instance.
    val partitionSpec: Seq[(Int, String)] =
      sys.env.get("V2_PARTITION_FILE").filter(_.nonEmpty).map { path =>
        val source = scala.io.Source.fromFile(path)
        try source.getLines().map(_.trim).filter(l => l.nonEmpty && !l.startsWith("#")).map { l =>
          val parts = l.split("\\s+", 2)
          require(parts.length == 2, s"[v2-partition] bad spec line: $l")
          (parts(0).toInt, parts(1))
        }.toList finally source.close()
      }.getOrElse(Nil)
    val partitionCount = if (partitionSpec.isEmpty) 0 else partitionSpec.map(_._1).max + 1
    def ownerOf(name: String): Int = {
      var best = 0; var bestLen = -1
      for ((idx, prefix) <- partitionSpec if name.startsWith(prefix) && prefix.length > bestLen) {
        best = idx; bestLen = prefix.length
      }
      best
    }
    def effectKey(n: TemplateNode): String = stmtReads(n.stmt).headOption.getOrElse("")
    val crossVia = mutable.HashMap[(Int, String), Int]()   // (partition, register) -> reading template
    // Reads of another partition's state array: an externalized read port
    // (V2_EXTERN_READ_FAMILIES, injected from the trace) stays a plain read;
    // any other foreign array is replicated — the partition also runs the
    // array's write cone, whose foreign register inputs join the cut.
    val partitionExternFamilies: Seq[String] =
      (sys.env.get("V2_EXTERN_READ_FAMILIES").toSeq
        .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty) ++
        externArrayFamilies).distinct
    // Mirrors phase 4 exactly: family substring match AND every read port of
    // the array narrower than 65 bits (wider reads stay local).
    def externalizedArray(a: String): Boolean =
      (stateArrayInfos.get(a).exists(_.fullyExternal) ||
        partitionExternFamilies.exists(externalArrayFamilyMatches(a, _))) &&
      stateArrayInfos.get(a).exists(si => si.readIds.nonEmpty && si.readIds.forall(t => nodes(t).stmt match {
        case dn: DefNode => firrtl.bitWidth(dn.value.tpe) <= 64
        case _ => false
      }))
    val coneParent = mutable.HashMap[(Int, Int), Int]()   // (partition, template) -> template that pulled it (-1 = seed)
    /** Per-partition template cones on the current graph: (cone template ids,
      * registers read from other partitions, state arrays read from other
      * partitions). Top-level sinks (harness outputs, extmodule inputs) are
      * seeded into partition 0; comb-cut and extern-read verifies follow
      * their own module prefix. */
    def partitionCones(edgesNow: IndexedSeq[TemplateEdge], infos: collection.Map[String, RegInfo])
        : (Seq[mutable.BitSet], Seq[mutable.LinkedHashSet[String]], Seq[mutable.LinkedHashSet[String]]) = {
      crossVia.clear()
      val producesNow: Map[String, Int] = nodes.iterator.flatMap(n => n.produces.map(_ -> n.id)).toMap
      // Harness sinks: top-level output ports and ExtModule inputs (the DMI
      // feedback the runner checks) are computed by partition 0.
      val topOutputs: Set[String] = circuit.modules.find(_.name == circuit.main).toSeq
        .flatMap(_.ports.collect { case Port(_, name, Output, _) => name }).toSet
      val sinkNames: Set[String] = hostBoundaryInputs ++ topOutputs
      val producersAll = Array.fill(nodes.size)(new ArrayBuffer[Int]())
      val producersData = Array.fill(nodes.size)(new ArrayBuffer[Int]())
      for (e <- edgesNow) {
        if (e.kind == EData) { producersAll(e.to) += e.from; producersData(e.to) += e.from }
        else if (e.kind == EShift) producersAll(e.to) += e.from
      }
      val cones = Seq.fill(partitionCount)(mutable.BitSet())
      val crossRegs = Seq.fill(partitionCount)(mutable.LinkedHashSet[String]())
      val crossArrays = Seq.fill(partitionCount)(mutable.LinkedHashSet[String]())
      coneParent.clear()
      for (p <- 0 until partitionCount) {
        val stack = new ArrayBuffer[Int]()
        var current = -1
        def push(id: Int): Unit = if (cones(p).add(id)) { stack += id; coneParent((p, id)) = current }
        for ((r, ri) <- infos if ownerOf(r) == p) {
          push(ri.commitId); push(ri.sourceId); ri.verifyId.foreach(push)
          producesNow.get(ri.nextName).foreach(push)
        }
        for ((a, si) <- stateArrayInfos if ownerOf(a) == p) push(si.commitId)
        for (n <- nodes) n.role match {
          case REffect if ownerOf(effectKey(n)) == p => push(n.id)
          case RVerify(x) if !infos.contains(x) && ownerOf(x) == p => push(n.id)   // comb-cut / extern-read verify
          case RComb if p == 0 && n.produces.exists(sinkNames.contains) => push(n.id)
          case _ =>
        }
        while (stack.nonEmpty) {
          val id = stack.remove(stack.size - 1)
          current = id
          // A read of another partition's state array stays in this cone (it
          // must be an externalized read port, checked at emission) but its
          // write-forwarding (EShift) producers belong to the owner.
          val foreignRead = nodes(id).role match {
            case RStateRead(a) => ownerOf(a) != p && externalizedArray(a)
            case _ => false
          }
          for (pr <- if (foreignRead) producersData(id) else producersAll(id)) nodes(pr).role match {
            case RRegSource(r) if ownerOf(r) != p =>
              crossRegs(p) += r
              if (!crossVia.contains((p, r))) crossVia((p, r)) = id
            case RStateRead(a) =>
              if (ownerOf(a) != p) {
                crossArrays(p) += a
                if (!externalizedArray(a)) push(stateArrayInfos(a).commitId)   // replicate the array
              }
              push(pr)
            case _ => push(pr)
          }
        }
      }
      (cones, crossRegs, crossArrays)
    }
    val partitionCutRegs: Seq[String] =
      if (partitionCount == 0) Nil
      else {
        val (cones, crossRegs, crossArrays) = partitionCones(edges, regInfos)
        for (p <- 0 until partitionCount)
          println(s"[v2-partition] pre-plan partition $p: cone=${cones(p).size} templates, " +
            s"cross-register reads=${crossRegs(p).size}, cross-array reads=${crossArrays(p).size}")
        val cut = crossRegs.flatMap(_.toSeq).distinct.sorted
        val ineligible = cut.filter(r => firrtl.bitWidth(regInfos(r).tpe) > 64 &&
          !(wideOracleEnabled && !regInfos(r).tpe.isInstanceOf[firrtl.ir.SIntType]))
        require(ineligible.isEmpty, "[v2-partition] cut registers wider than 64 bits " +
          s"(set V2_WIDE_ORACLE=1): ${ineligible.take(6).mkString(", ")}")
        val allCrossArrays = crossArrays.flatMap(_.toSeq).distinct
        val replicated = allCrossArrays.filterNot(externalizedArray)
        if (allCrossArrays.nonEmpty)
          println(s"[v2-partition] ${allCrossArrays.size} state array(s) read across partitions: " +
            s"${allCrossArrays.size - replicated.size} externalized, ${replicated.size} replicated " +
            s"(${replicated.take(4).mkString(", ")})")
        // V2_PARTITION_REPORT=<file>: the cut set per partition, for choosing
        // partition boundaries before a full emission. V2_PARTITION_REPORT_ONLY=1
        // stops after the report.
        sys.env.get("V2_PARTITION_REPORT").filter(_.nonEmpty).foreach { path =>
          val w = new java.io.PrintWriter(path)
          try {
            for (p <- 0 until partitionCount)
              w.println(s"partition $p cone=${cones(p).size} cross_regs=${crossRegs(p).size} cross_arrays=${crossArrays(p).size}")
            for (p <- 0 until partitionCount; r <- crossRegs(p))
              w.println(s"cut $p ${ownerOf(r)} $r ${firrtl.bitWidth(regInfos(r).tpe)}")
            for (p <- 0 until partitionCount; a <- crossArrays(p))
              w.println(s"array $p ${ownerOf(a)} $a ${if (externalizedArray(a)) "externalized" else "replicated"}")
          } finally w.close()
          if (sys.env.get("V2_PARTITION_REPORT_ONLY").contains("1")) {
            println(s"[v2-partition] report written to $path; stopping (V2_PARTITION_REPORT_ONLY)")
            sys.exit(0)
          }
        }
        cut
      }
    if (partitionCutRegs.nonEmpty) {
      for (r <- partitionCutRegs) {
        val ri = regInfos(r)
        nodes(ri.sourceId) = nodes(ri.sourceId).copy(role = ROracleInject(r))
        val vid = if (wantVerify) Some(addNode(EmptyStmt, RVerify(r), None)) else None
        regInfos(r) = ri.copy(plan = RPOracle, verifyId = vid)
        val (muxWen, muxGroupSize) = muxHoldAudit(r)
        recordAudit(OracleAudit(
          flatName = r, kind = "reg", stage = "partition-cut", reason = "cross-partition-read",
          basePlan = basePlanByReg(r), widthBits = firrtl.bitWidth(ri.tpe).toInt,
          sccKey = -1, sccTemplates = 0, sccCombTemplates = 0, sccRegSources = 0, sccSelfSources = 0,
          groupOracleCandidates = partitionCutRegs.size, selectedRank = 0,
          benefitEstimate = 0L, costEstimate = 1L, cyclicRegDrop = -1, cyclicTemplateDrop = -1,
          matchedPrefix = "partition", condHoldCandidate = false, forcedSerial = false,
          muxHoldWen = muxWen, muxHoldGroupSize = muxGroupSize))
      }
      chosen ++= partitionCutRegs
      edges = buildEdges(regInfos)
      sccs = tarjan(nodes.size, edges)
      println(s"[v2-partition] ${partitionCutRegs.size} cut register(s) forced to oracles " +
        s"(${partitionCutRegs.map(r => firrtl.bitWidth(regInfos(r).tpe).toInt).sum} bits)")
    }
    // V2_FORCE_ORACLE_FILE: one flattened register name per line, forced into
    // the oracle set before the register FVS (same mechanics as a partition
    // cut).  A wide emit given the scalar contract's register list reproduces
    // that contract exactly: the FVS then finds no residual cycle to cut, and
    // phase 3 stays anchored to the same set.  Names that are absent, frozen,
    // already chosen, or too wide are skipped with a note.
    val forcedOracleRegs: Seq[String] =
      sys.env.get("V2_FORCE_ORACLE_FILE").filter(_.nonEmpty).map { path =>
        val source = scala.io.Source.fromFile(path)
        try source.getLines().map(_.trim).filter(l => l.nonEmpty && !l.startsWith("#")).toSeq
        finally source.close()
      }.getOrElse(Nil)
    if (forcedOracleRegs.nonEmpty) {
      var skipped = 0
      var applied = 0
      for (r <- forcedOracleRegs.distinct) {
        regInfos.get(r) match {
          case Some(ri) if !chosen.contains(r) && !frozen(r) && ri.plan != RPOracle &&
              (firrtl.bitWidth(ri.tpe) <= 64 ||
                (wideOracleEnabled && !ri.tpe.isInstanceOf[firrtl.ir.SIntType])) =>
            nodes(ri.sourceId) = nodes(ri.sourceId).copy(role = ROracleInject(r))
            val vid = if (wantVerify) Some(addNode(EmptyStmt, RVerify(r), None)) else None
            regInfos(r) = ri.copy(plan = RPOracle, verifyId = vid)
            val (muxWen, muxGroupSize) = muxHoldAudit(r)
            recordAudit(OracleAudit(
              flatName = r, kind = "reg", stage = "forced-oracle", reason = "force-oracle-file",
              basePlan = basePlanByReg(r), widthBits = firrtl.bitWidth(ri.tpe).toInt,
              sccKey = -1, sccTemplates = 0, sccCombTemplates = 0, sccRegSources = 0, sccSelfSources = 0,
              groupOracleCandidates = forcedOracleRegs.size, selectedRank = applied,
              benefitEstimate = 0L, costEstimate = 1L, cyclicRegDrop = -1, cyclicTemplateDrop = -1,
              matchedPrefix = "force-file", condHoldCandidate = false, forcedSerial = false,
              muxHoldWen = muxWen, muxHoldGroupSize = muxGroupSize))
            chosen += r
            applied += 1
          case _ => skipped += 1
        }
      }
      edges = buildEdges(regInfos)
      sccs = tarjan(nodes.size, edges)
      println(s"[v2] force-oracle file: $applied register(s) forced to oracles, $skipped skipped")
    }
    case class FvsGroup(
      scc: Set[Int],
      allRegSources: Seq[String],
      candidates: Seq[String],
      fullPicks: Seq[String])
    // Under a finite budget, prioritize larger serial regions. Within each
    // region minimizeFvs returns a deterministic dependency-benefit order.
    // Leaving an SCC only partially cut is correct: it remains in the serial
    // template set and is emitted lane by lane below.
    val fvsGroups = sccs.filter(_.size > 1).map { scc =>
      val allRegSources = scc.toSeq.flatMap(id => nodes(id).role match {
        case RRegSource(r) => Some(r)
        case _ => None
      }).sorted
      // Oracle storage is one uint64_t per entry, so >64-bit registers can
      // never be oracles — exclude them from FVS candidates (they stay in the
      // serial region, same as frozen registers). Without this filter, name-
      // dependent FVS tie-breaking can select e.g. a 65-bit divider operand
      // and abort the emit (the dissolve phase below already checks widths).
      val cands = allRegSources.filter(r =>
        !frozen(r) && (firrtl.bitWidth(regInfos(r).tpe) <= 64 ||
          (wideOracleEnabled && !regInfos(r).tpe.isInstanceOf[firrtl.ir.SIntType])))
      val hasStateSource = scc.exists(id => nodes(id).role.isInstanceOf[RStateRead])
      if (allRegSources.isEmpty && !hasStateSource) {
        val sample = scc.take(8).map(id => describeNode(nodes(id))).mkString("; ")
        throw new IllegalStateException(
          s"[v2] SCC of size ${scc.size} with no register source — combinational loop: $sample")
      }
      val fullPicks = if (cands.isEmpty) Seq.empty
        else if (oracleAll) cands else minimizeFvs(cands, scc, nodes, edges, regInfos)
      FvsGroup(scc, allRegSources, cands, fullPicks)
    }
    val selectionGroups = if (oracleLimit < 0) fvsGroups
      else fvsGroups.sortBy(g => (-g.scc.size, g.scc.min))
    for (g <- selectionGroups) {
      // Reorder only the already-selected FVS set. This keeps the unlimited
      // configuration bit-for-bit compatible while giving finite budgets a
      // dependency-benefit prefix instead of lexicographic register names.
      val picks = if (oracleLimit < 0) g.fullPicks
        else orderFvsForBudget(g.fullPicks, g.scc, nodes, edges, regInfos)
      chosen ++= picks.take(oracleBudgetLeft(chosen.size))
    }

    // Apply oracles: source role flips to injection (drops its EShift in-edge
    // by construction of buildEdges), add verify nodes. Apply in the original
    // unlimited-plan order, filtered by the budgeted set. Thus K>=N emits the
    // exact same node layout as the unrestricted configuration.
    val canonicalChosenOrder = fvsGroups.flatMap(_.fullPicks).distinct
    for (g <- fvsGroups) {
      val sccComb = g.scc.count(id => nodes(id).role == RComb)
      val sccSelf = g.allRegSources.count(selfRefRegs.contains)
      for ((r, rank) <- g.fullPicks.zipWithIndex if chosen.contains(r)) {
        val ri = regInfos(r)
        val (muxWen, muxGroupSize) = muxHoldAudit(r)
        recordAudit(OracleAudit(
          flatName = r,
          kind = "reg",
          stage = if (oracleAll) "phase2-fvs-all" else "phase2-fvs",
          reason = if (oracleAll) "all-register-sources" else "feedback-vertex-set",
          basePlan = basePlanByReg(r),
          widthBits = firrtl.bitWidth(ri.tpe).toInt,
          sccKey = g.scc.min,
          sccTemplates = g.scc.size,
          sccCombTemplates = sccComb,
          sccRegSources = g.allRegSources.size,
          sccSelfSources = sccSelf,
          groupOracleCandidates = g.fullPicks.size,
          selectedRank = rank,
          benefitEstimate = 0L,
          costEstimate = 0L,
          cyclicRegDrop = -1,
          cyclicTemplateDrop = -1,
          matchedPrefix = "",
          condHoldCandidate = condOracleCands.contains(r),
          forcedSerial = false,
          muxHoldWen = muxWen,
          muxHoldGroupSize = muxGroupSize))
      }
    }
    for (r <- canonicalChosenOrder if chosen.contains(r)) {
      val ri = regInfos(r)
      nodes(ri.sourceId) = nodes(ri.sourceId).copy(role = ROracleInject(r))
      val vid = if (wantVerify) Some(addNode(EmptyStmt, RVerify(r), None)) else None
      regInfos(r) = ri.copy(plan = RPOracle, verifyId = vid)
    }
    edges = buildEdges(regInfos)
    sccs = tarjan(nodes.size, edges)

    // Phase 3 — serial-cone dissolution. A self-referencing register only
    // confines serialization to its source template when its wen/wdata/$next
    // cone does not read the register itself; otherwise the whole cone lands
    // in the SCC and is emitted per-lane (sodor: the CSR read-modify-write
    // cone alone is ~70% of all serial scalar statements). Account per
    // residual SCC, per 2W-cycle window:
    //   vectorizing its nComb templates saves ~2*nComb*(W-1) stmt executions;
    //   oracling its k self-ref regs costs k*(2W loads + 2(W-1) verifies) ~= 4kW.
    // Dissolve when benefit > 2x cost (margin for cache-missing trace loads).
    // This reproduces the v1-validated sodor choice of oracling all CSR regs.
    val serialOraclePrefixes: Seq[String] =
      sys.env.get("V2_ORACLE_SERIAL")
        .map(_.split(',').map(_.trim).filter(_.nonEmpty).toSeq).getOrElse(Nil)
    // --simd-v2-oracle-all normally makes phase 3 unnecessary: phase 2 has
    // already cut every eligible register source in a cyclic SCC.  Packed
    // compiler banks are deliberately frozen in phase 2, however, and an
    // explicitly requested V2_ORACLE_SERIAL prefix is their opt-in escape.
    // Honour that explicit request even in oracle-all mode; without it the
    // packed bank can strand the very serial source chain it was meant to
    // remove.
    if ((!oracleAll || serialOraclePrefixes.nonEmpty) &&
        oracleBudgetLeft(chosen.size) > 0) {
      case class DissolveGroup(
        scoreRatio: Long,
        scc: Set[Int],
        regs: Seq[String],
        nComb: Int,
        condTrigger: Boolean,
        forcedTrigger: Boolean,
        heuristicTrigger: Boolean)
      val dissolveGroups = ArrayBuffer[DissolveGroup]()
      def hasCondOracleCand(scc: Iterable[Int]): Boolean =
        oracleCondholdExp && scc.exists(id => nodes(id).role match {
          case RRegSource(r) => condOracleCands.contains(r)
          case _ => false
        })
      // V2_ORACLE_SERIAL: comma-separated name prefixes (matched against the
      // flat name's last segment, or the full path as a substring) whose
      // remaining serial regions are force-dissolved via reg oracles even
      // when the comb benefit model says no. The model above counts only
      // comb templates trapped in the SCC; for the OoO bookkeeping long tail
      // (single-register SCCs, nComb=0) the real cost is the per-lane
      // serialized source chain itself, and the 8W-per-oracle cost constant
      // predates the v4 window-major stream layout. Intended use: restrict
      // to microarchitecturally modelable families (rob_/stq_/ldq_/...).
      // V2_DISSOLVE_ANCHOR_FILE: one flattened register name per line.  When
      // set, phase-3 may dissolve a serial SCC only if every self-recurrent
      // register in it is listed.  The register FVS above is W-independent,
      // but this heuristic is not (the benefit model scales with W), so a
      // wide-W emit anchored to the W4 contract's register streams selects
      // exactly the contract the model was qualified against.  ORACLE_FREEZE
      // is not a substitute: it removes FVS candidates and changes the FVS
      // solution.
      val dissolveAnchor: Option[Set[String]] =
        sys.env.get("V2_DISSOLVE_ANCHOR_FILE").filter(_.nonEmpty).map { path =>
          val source = scala.io.Source.fromFile(path)
          try source.getLines().map(_.trim).filter(_.nonEmpty).toSet
          finally source.close()
        }
      def forcedSerialReg(r: String): Boolean =
        selfRecurrentBankNames.contains(r) || (serialOraclePrefixes.nonEmpty && {
          val last = r.split('.').last
          serialOraclePrefixes.exists(p => last.startsWith(p) || r.contains(p))
        })
      def hasForcedSerial(scc: Iterable[Int]): Boolean =
        (serialOraclePrefixes.nonEmpty || selfRecurrentBankNames.nonEmpty) &&
          scc.exists(id => nodes(id).role match {
            case RRegSource(r) => selfRefRegs.contains(r) && forcedSerialReg(r)
            case _ => false
          })
      // V2_ORACLE_SERIAL may also name compiler-owned register banks that are
      // not self-recurrent (issue-slot uop banks, fetch-buffer RAM banks).
      // Their recurrence runs through the whole issue/fetch arbiter, and the
      // bank is the only cut point whose value the model line can supply
      // (packed member fields, the same contract as a self-recurrent bank).
      // ORACLE_FREEZE prefixes still win.
      val partialForcedSerial = sys.env.get("V2_ORACLE_SERIAL_PARTIAL")
        .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
      def serialPrefixMatched(r: String): Boolean = serialOraclePrefixes.nonEmpty && {
        val last = r.split('.').last
        serialOraclePrefixes.exists(p => last.startsWith(p) || r.contains(p))
      }
      def prefixFrozen(r: String): Boolean =
        freezePrefixes.exists(p => r.startsWith(p) || r.split('.').last.startsWith(p))
      def dissolveEligible(r: String): Boolean =
        (!frozen(r) || (frozenBankNames(r) && !prefixFrozen(r) && serialPrefixMatched(r))) &&
          dissolveAnchor.forall(_.contains(r)) &&
          (firrtl.bitWidth(regInfos(r).tpe) <= 64 ||
            (wideOracleEnabled && !regInfos(r).tpe.isInstanceOf[firrtl.ir.SIntType]))
      def ineligibleReason(r: String): String =
        if (prefixFrozen(r)) "frozen-prefix"
        else if (frozenBankNames(r)) "compiler-bank"
        else if (!dissolveAnchor.forall(_.contains(r))) "not-anchored"
        else if (firrtl.bitWidth(regInfos(r).tpe) > 64) s"width=${firrtl.bitWidth(regInfos(r).tpe)}"
        else "ok"
      for (scc <- sccs if scc.size > 1 || hasCondOracleCand(scc) || hasForcedSerial(scc)) {
        val selfSrcs = scc.toSeq.flatMap(id => nodes(id).role match {
          case RRegSource(r) if selfRefRegs.contains(r) => Some(r)
          case _ => None
        }).sorted
        val allEligible = selfSrcs.forall(dissolveEligible)
        val nComb = scc.count(id => nodes(id).role == RComb)
        val condTrigger = hasCondOracleCand(scc)
        val forcedTrigger = hasForcedSerial(scc)
        val heuristicTrigger = 2L * nComb * (W - 1) > 8L * W * selfSrcs.size
        val eligibleForced = selfSrcs.filter(r => dissolveEligible(r) && serialPrefixMatched(r))
        if (selfSrcs.nonEmpty && allEligible &&
            (condTrigger || forcedTrigger || heuristicTrigger)) {
          // benefit/cost first, then SCC size; names provide a stable tie-break.
          dissolveGroups += DissolveGroup(
            nComb.toLong * 1000000L / selfSrcs.size, scc, selfSrcs, nComb,
            condTrigger, forcedTrigger, heuristicTrigger)
        } else if (partialForcedSerial && forcedTrigger && eligibleForced.nonEmpty) {
          // V2_ORACLE_SERIAL_PARTIAL: oracle the prefix-matched eligible
          // self-sources even though other self-sources of the SCC stay
          // (compiler banks outside the prefix list, >64-bit registers).
          // Useful when one residual SCC at this stage still glues together
          // regions that later passes (extern read ports) separate anyway.
          dissolveGroups += DissolveGroup(
            nComb.toLong * 1000000L / eligibleForced.size, scc, eligibleForced, nComb,
            condTrigger, forcedTrigger, heuristicTrigger)
          val rest = selfSrcs.filterNot(eligibleForced.contains)
          println(s"[v2] serial SCC (${scc.size} templates, $nComb comb) partially forced: " +
            s"${eligibleForced.size}/${selfSrcs.size} prefix-matched self-source(s) oracled " +
            s"(${eligibleForced.take(3).map(_.split('.').last).mkString(", ")}${if (eligibleForced.size > 3) ", ..." else ""}); " +
            s"kept: ${rest.take(3).map(r => s"${r.split('.').last}(${ineligibleReason(r)})").mkString(", ")}" +
            (if (rest.size > 3) ", ..." else ""))
        } else if (scc.size >= 50) {
          // Diagnostic: the large serial regions that stay per-lane, and why.
          val blocked = selfSrcs.filterNot(dissolveEligible)
          val why =
            if (selfSrcs.isEmpty) "no self-referencing register source"
            else if (blocked.nonEmpty)
              s"${blocked.size}/${selfSrcs.size} self-source(s) ineligible: " +
                blocked.take(4).map(r => s"${r.split('.').last}(${ineligibleReason(r)})").mkString(", ") +
                (if (blocked.size > 4) ", ..." else "")
            else "no trigger (benefit model below cost; use V2_ORACLE_SERIAL)"
          println(s"[v2] serial SCC kept (${scc.size} templates, $nComb comb): $why")
        }
      }
      val dissolved = mutable.LinkedHashSet[String]()
      val dissolveSelectionGroups = if (oracleLimit < 0) dissolveGroups
        else dissolveGroups.sortBy(g =>
          (-g.scoreRatio, -g.scc.size, g.regs.mkString("\u0000")))
      for (g <- dissolveSelectionGroups
          if oracleBudgetLeft(chosen.size + dissolved.size) > 0) {
        val selected = g.regs.take(oracleBudgetLeft(chosen.size + dissolved.size))
        dissolved ++= selected
        println(s"[v2] dissolve serial SCC (${g.scc.size} templates) " +
          s"via ${selected.size}/${g.regs.size} reg oracle(s): ${selected.map(_.split('.').last).take(4).mkString(", ")}" +
          (if (selected.size > 4) ", ..." else ""))
        val allRegSources = g.scc.toSeq.flatMap(id => nodes(id).role match {
          case RRegSource(r) => Some(r)
          case _ => None
        }).distinct
        for ((r, rank) <- selected.zipWithIndex) {
          val directCond = condOracleCands.contains(r)
          val matched = serialOraclePrefixes.filter { p =>
            val last = r.split('.').last
            last.startsWith(p) || r.contains(p)
          }
          val directForced = matched.nonEmpty
          val (stage, reason) =
            if (directCond) ("phase3-condhold", "condhold-experiment")
            else if (directForced) ("phase3-forced-serial", "matched-serial-prefix")
            else if (g.condTrigger) ("phase3-condhold-group", "co-selected-with-condhold")
            else if (g.forcedTrigger) ("phase3-forced-group", "co-selected-with-serial-prefix")
            else ("phase3-heuristic", "serial-cone-benefit-model")
          val ri = regInfos(r)
          val (muxWen, muxGroupSize) = muxHoldAudit(r)
          recordAudit(OracleAudit(
            flatName = r,
            kind = "reg",
            stage = stage,
            reason = reason,
            basePlan = basePlanByReg(r),
            widthBits = firrtl.bitWidth(ri.tpe).toInt,
            sccKey = g.scc.min,
            sccTemplates = g.scc.size,
            sccCombTemplates = g.nComb,
            sccRegSources = allRegSources.size,
            sccSelfSources = g.regs.size,
            groupOracleCandidates = g.regs.size,
            selectedRank = rank,
            benefitEstimate = 2L * g.nComb * (W - 1),
            costEstimate = 8L * W * g.regs.size,
            cyclicRegDrop = -1,
            cyclicTemplateDrop = -1,
            matchedPrefix = matched.mkString(","),
            condHoldCandidate = directCond,
            forcedSerial = directForced,
            phase3CondTrigger = g.condTrigger,
            phase3ForcedTrigger = g.forcedTrigger,
            phase3HeuristicTrigger = g.heuristicTrigger,
            muxHoldWen = muxWen,
            muxHoldGroupSize = muxGroupSize))
        }
      }
      if (dissolved.nonEmpty) {
        val canonicalDissolvedOrder = dissolveGroups.flatMap(_.regs).distinct
        for (r <- canonicalDissolvedOrder if dissolved.contains(r)) {
          val ri = regInfos(r)
          nodes(ri.sourceId) = nodes(ri.sourceId).copy(role = ROracleInject(r))
          val vid = if (wantVerify) Some(addNode(EmptyStmt, RVerify(r), None)) else None
          regInfos(r) = ri.copy(plan = RPOracle, verifyId = vid)
        }
        chosen ++= dissolved
        edges = buildEdges(regInfos)
        sccs = tarjan(nodes.size, edges)
      }

      // A self-recurrent bank whose recurrence folded successfully has no
      // SCC left for the dissolve scan to visit (the fold absorbs the self
      // edge), so the scan above only catches the fold-failed ones. Every
      // remaining self-recurrent bank still evaluates as a per-lane serial
      // recurrence; one injected stream replaces it outright, and — equally
      // important — gives the bank a stable trace key the model line can
      // supply from its packed member fields.
      val strandedSelfBanks = selfRecurrentBankNames.toSeq.sorted
        .filterNot(chosen.contains)
        .filter(regInfos.contains)
        // A folded bank is still subject to explicit candidate exclusions.
        // Otherwise this fallback silently undoes --oracle-freeze.
        .filterNot(prefixFrozen)
      if (strandedSelfBanks.nonEmpty) {
        println(s"[v2] oracling ${strandedSelfBanks.size} folded self-recurrent bank(s)")
        for (r <- strandedSelfBanks) {
          val ri = regInfos(r)
          nodes(ri.sourceId) = nodes(ri.sourceId).copy(role = ROracleInject(r))
          val vid = if (wantVerify) Some(addNode(EmptyStmt, RVerify(r), None)) else None
          regInfos(r) = ri.copy(plan = RPOracle, verifyId = vid)
          val (muxWen, muxGroupSize) = muxHoldAudit(r)
          recordAudit(OracleAudit(
            flatName = r,
            kind = "reg",
            stage = "phase3-forced-bank",
            reason = "self-recurrent-bank",
            basePlan = basePlanByReg(r),
            widthBits = firrtl.bitWidth(ri.tpe).toInt,
            sccKey = -1,
            sccTemplates = 0,
            sccCombTemplates = 0,
            sccRegSources = 1,
            sccSelfSources = 1,
            groupOracleCandidates = 1,
            selectedRank = 0,
            benefitEstimate = 0L,
            costEstimate = 1L,
            cyclicRegDrop = -1,
            cyclicTemplateDrop = -1,
            matchedPrefix = "self-recurrent-bank",
            condHoldCandidate = false,
            forcedSerial = true,
            muxHoldWen = muxWen,
            muxHoldGroupSize = muxGroupSize))
        }
        chosen ++= strandedSelfBanks
        edges = buildEdges(regInfos)
        sccs = tarjan(nodes.size, edges)
      }
    }

    // V2_ORACLE_CONDHOLD is an oracle-selection experiment, not permission to
    // change the recurrence semantics when the finite stream budget runs out.
    // Candidates enter selection as RPShift so their real self-loop is visible
    // to the FVS/dissolve heuristics. Restore every unselected candidate to the
    // exact local mux-hold lowering after selection, then rebuild the graph so
    // scheduling sees its confined source self-loop and its new wen/wdata
    // producers. Keep this finite-budget-only: the unrestricted production
    // configuration retains its historical node numbering and manifest ABI.
    if (oracleLimit >= 0) {
      val fallbackCondHold = regInfos.keysIterator
        .filter(r => condOracleCands.contains(r) && !chosen.contains(r)).toSeq
      for (r <- fallbackCondHold) {
        val ri = regInfos(r)
        val (wen, wdata) = muxHoldExprByReg.getOrElse(r,
          throw new IllegalStateException(s"[v2] missing mux-hold extraction for budget fallback '$r'"))
        condHold(r) = (wen, wdata)
        materializeCondHold(r, wen, wdata)
        regInfos(r) = ri.copy(plan = RPCondHold)
      }
      if (fallbackCondHold.nonEmpty) {
        println(s"[v2] oracle-budget fallback: ${fallbackCondHold.size} mux-hold register(s) restored to local cond-hold")
        edges = buildEdges(regInfos)
        sccs = tarjan(nodes.size, edges)
      }
    }

    // Phase 4a — fully external arrays (V2_EXTERN_ARRAY_FAMILIES).  The
    // consumer does not keep a persistent image at all.  Read data is injected
    // directly, while every read address and every ordered write port's
    // canonical enable/address/data tuple is injected and compared against the
    // RTL-computed value.  Equal initial images plus an equal ordered access
    // trace inductively proves equal memory contents, so recomputing read data
    // from a second consumer-side array would add cost but no checking power.
    val accessProofDataOracles = mutable.LinkedHashSet[String]()
    if (externArrayFamilies.nonEmpty) {
      val one = UIntType(IntWidth(1))
      def zero(tpe: Type): Expression = tpe match {
        case UIntType(width) => UIntLiteral(0, width)
        case SIntType(width) => SIntLiteral(0, width)
        case other => throw new IllegalStateException(
          s"[v2-extern-array] unsupported access payload type $other")
      }
      def requireStreamWidth(name: String, tpe: Type): Unit = {
        val width = firrtl.bitWidth(tpe)
        require(width > 0 && width <= 64,
          s"[v2-extern-array] '$name' is $width bits; access streams require 1..64 bits")
      }
      var accessRank = 0
      def addAudit(name: String, tpe: Type, reason: String, basePlan: String,
          sccKey: Int, candidates: Int, prefix: String): Unit = {
        recordAudit(OracleAudit(
          flatName = name,
          kind = "comb",
          stage = "phase4-extern-array",
          reason = reason,
          basePlan = basePlan,
          widthBits = firrtl.bitWidth(tpe).toInt,
          sccKey = sccKey,
          sccTemplates = 1,
          sccCombTemplates = 0,
          sccRegSources = 0,
          sccSelfSources = 0,
          groupOracleCandidates = candidates,
          selectedRank = accessRank,
          benefitEstimate = 0L,
          costEstimate = 0L,
          cyclicRegDrop = -1,
          cyclicTemplateDrop = -1,
          matchedPrefix = prefix,
          condHoldCandidate = false,
          forcedSerial = false))
        accessRank += 1
      }
      def addInjected(name: String, tpe: Type, verify: Boolean, reason: String,
          basePlan: String, sccKey: Int, candidates: Int, prefix: String): Unit = {
        requireStreamWidth(name, tpe)
        addNode(EmptyStmt, ROracleInject(name), Some(name))
        if (verify && wantVerify) addNode(EmptyStmt, RVerify(name), None)
        combCuts += name
        combCutTypes(name) = tpe
        addAudit(name, tpe, reason, basePlan, sccKey, candidates, prefix)
      }

      var externalArrays = 0
      var readStreams = 0
      var accessStreams = 0
      for ((array, info) <- stateArrayInfos.toSeq.sortBy(_._1) if info.fullyExternal) {
        externalArrays += 1
        val prefix = externArrayFamilies.find(
          externalArrayFamilyMatches(array, _)).getOrElse("")
        require(info.readAccess.size == info.readIds.size,
          s"[v2-extern-array] '$array' read-access metadata mismatch")
        require(info.writeAccess.size == info.writePorts,
          s"[v2-extern-array] '$array' write-access metadata mismatch")

        for (((tid, access), readIndex) <-
             info.readIds.zip(info.readAccess).zipWithIndex) {
          val d = nodes(tid).stmt match {
            case dn @ DefNode(_, _, WSubAccess(_, _, _, _)) => dn
            case other => throw new IllegalStateException(
              s"[v2-extern-array] read template $tid of '$array' is " +
                s"${other.getClass.getSimpleName}, expected DefNode(mem[addr])")
          }
          val WSubAccess(_, address, _, _) = d.value: @unchecked
          require(d.name == access.dataOracle,
            s"[v2-extern-array] '$array' read $readIndex data name changed")

          // Reuse the original read template for the RTL address computation;
          // no statement in the resulting graph references the memory value.
          val rtlAddress = access.addressOracle + "$rtl"
          requireStreamWidth(access.addressOracle, address.tpe)
          nodes(tid) = nodes(tid).copy(
            stmt = DefNode(NoInfo, rtlAddress, address),
            role = RComb,
            produces = Some(rtlAddress))
          addInjected(access.dataOracle, d.value.tpe, verify = false,
            reason = "read-data-access-proof", basePlan = "state-read-data",
            sccKey = tid, candidates = info.readIds.size, prefix = prefix)
          accessProofDataOracles += access.dataOracle
          addInjected(access.addressOracle, address.tpe, verify = true,
            reason = "read-address-access-trace", basePlan = "state-read-address",
            sccKey = tid, candidates = info.readIds.size, prefix = prefix)
          readStreams += 1
          accessStreams += 1
        }

        val writes = nodes(info.commitId).stmt match {
          case Block(stmts) => stmts.collect { case write: essent.ir.MemWrite => write }
          case write: essent.ir.MemWrite => Seq(write)
          case EmptyStmt => Seq.empty
          case other => throw new IllegalStateException(
            s"[v2-extern-array] commit of '$array' is ${other.getClass.getSimpleName}")
        }
        require(writes.size == info.writePorts,
          s"[v2-extern-array] '$array' expected ${info.writePorts} writes, found ${writes.size}")
        for (((write, access), writeIndex) <-
             writes.zip(info.writeAccess).zipWithIndex) {
          require(write.portName == access.portName,
            s"[v2-extern-array] '$array' write-port order changed at $writeIndex")
          require(firrtl.bitWidth(write.wrEn.tpe) == 1 &&
              firrtl.bitWidth(write.wrMask.tpe) == 1,
            s"[v2-extern-array] '$array.${write.portName}' has non-scalar enable/mask")
          val effective = DoPrim(firrtl.PrimOps.And,
            Seq(write.wrEn, write.wrMask), Seq.empty, one)
          val enableRtl = access.enableOracle + "$rtl"
          val addressRtl = access.addressOracle + "$rtl"
          val dataRtl = access.dataOracle + "$rtl"
          addNode(DefNode(NoInfo, enableRtl, effective), RComb, Some(enableRtl))
          val enableRef = WRef(enableRtl, one, NodeKind, SourceFlow)
          addNode(DefNode(NoInfo, addressRtl,
            Mux(enableRef, write.wrAddr, zero(write.wrAddr.tpe), write.wrAddr.tpe)),
            RComb, Some(addressRtl))
          addNode(DefNode(NoInfo, dataRtl,
            Mux(enableRef, write.wrData, zero(write.wrData.tpe), write.wrData.tpe)),
            RComb, Some(dataRtl))
          val key = info.commitId * 16 + writeIndex
          addInjected(access.enableOracle, one, verify = true,
            reason = "write-enable-access-trace", basePlan = "state-write-enable",
            sccKey = key, candidates = info.writePorts, prefix = prefix)
          addInjected(access.addressOracle, write.wrAddr.tpe, verify = true,
            reason = "write-address-access-trace", basePlan = "state-write-address",
            sccKey = key, candidates = info.writePorts, prefix = prefix)
          addInjected(access.dataOracle, write.wrData.tpe, verify = true,
            reason = "write-data-access-trace", basePlan = "state-write-data",
            sccKey = key, candidates = info.writePorts, prefix = prefix)
          accessStreams += 3
        }

        // The persistent image and chronological commit are gone from both
        // correctness and performance builds.  The ordered write-access
        // streams above are their complete Micro-Lockstep replacement.
        nodes(info.commitId) = nodes(info.commitId).copy(stmt = EmptyStmt)
      }
      println(s"[v2] extern arrays: $externalArrays array(s), " +
        s"$readStreams read-data stream(s), $accessStreams verified access stream(s)")
      if (externalArrays > 0) {
        edges = buildEdges(regInfos)
        sccs = tarjan(nodes.size, edges)
      }
    }

    // Phase 4b — extern read ports (V2_EXTERN_READ_FAMILIES): every state-array
    // read whose array flat name contains one of the comma-separated substrings
    // becomes an ordinary comb oracle stream. The read node is renamed to
    // '<name>$rtl' and kept as the verify-side recompute (the emitter fences it
    // under ESSENT_ORACLE_VERIFY, so the perf build drops the read machinery at
    // preprocessing time), an injection node produces '<name>' for every
    // downstream reader, and the manifest gains the stream. This phase runs
    // after every selection/dissolution phase on purpose: with the flag off the
    // oracle contract is byte-identical to before, and with the flag on it only
    // gains streams whose membership depends on the family list alone — never
    // on W or on SCC heuristics — so one family list yields one contract at
    // every width. Reads wider than 64 bits stay local (stream slots are u64).
    if (!externReadFirst) externalizeReadPorts("phase4-extern-read")

    // Dead comb elimination + single-use inlining. Contract names that the
    // data plane / non-comb roles read implicitly (invisible to stmtReads):
    // external IO, every register's $next (commit + verify), wen/wdata of
    // still-cond-hold registers (source reads them at lane-1), comb-cut $rtl
    // values (verify), reads of effect statements. These are never pruned and
    // never inlined.
    {
      // (0) Algebraic simplification + CSE + copy propagation. The Chisel
      // ListLookup decode lowering and reset muxes leave massive constant
      // redundancy in the flat design (mux(c, 0, y), x & 0, duplicate
      // definitions like stall/dec_stall). Fold it here so every later pass
      // and the generated code only see real work. Identity folds that keep
      // an operand are width-guarded: FIRRTL zero-extends operands, so e.g.
      // (a & ones) == a only when all widths agree.
      var foldedOps, cseDefs, copyProps = 0
      locally {
        import firrtl.PrimOps.{And, Or, Xor, Not}
        def w(t: Type): BigInt = firrtl.bitWidth(t)
        def lit(e: Expression): Option[BigInt] = e match {
          case u: UIntLiteral => Some(u.value)
          case _ => None
        }
        def allOnes(x: BigInt, wid: BigInt): Boolean = x == (BigInt(1) << wid.toInt) - 1
        def uint(v: BigInt, wid: BigInt): Expression = UIntLiteral(v, IntWidth(wid))
        def sameW(a: Expression, t: Type): Boolean = w(a.tpe) == w(t)
        // structural equality, bounded so post-inline giants cannot blow up
        def eqSer(a: Expression, b: Expression): Boolean = {
          val sa = a.serialize
          sa.length <= 512 && sa == b.serialize
        }
        val b1 = UIntType(IntWidth(1))
        def simp(e0: Expression): Expression = {
          val e = e0.mapExpr(simp)
          val r = e match {
            case DoPrim(And, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
              case (Some(x), Some(y)) => uint(x & y, w(tpe))
              case (Some(x), _) if x == 0 => uint(0, w(tpe))
              case (_, Some(y)) if y == 0 => uint(0, w(tpe))
              case (Some(x), _) if allOnes(x, w(a.tpe)) && sameW(a, tpe) && sameW(b, tpe) => b
              case (_, Some(y)) if allOnes(y, w(b.tpe)) && sameW(a, tpe) && sameW(b, tpe) => a
              case (None, None) if sameW(a, tpe) && sameW(b, tpe) && eqSer(a, b) => a
              case _ => e
            }
            case DoPrim(Or, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
              case (Some(x), Some(y)) => uint(x | y, w(tpe))
              case (Some(x), _) if x == 0 && sameW(b, tpe) => b
              case (_, Some(y)) if y == 0 && sameW(a, tpe) => a
              case (Some(x), _) if allOnes(x, w(a.tpe)) && sameW(a, tpe) => uint((BigInt(1) << w(tpe).toInt) - 1, w(tpe))
              case (_, Some(y)) if allOnes(y, w(b.tpe)) && sameW(b, tpe) => uint((BigInt(1) << w(tpe).toInt) - 1, w(tpe))
              case (None, None) if sameW(a, tpe) && sameW(b, tpe) && eqSer(a, b) => a
              case _ => e
            }
            case DoPrim(Xor, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
              case (Some(x), Some(y)) => uint(x ^ y, w(tpe))
              case (Some(x), _) if x == 0 && sameW(b, tpe) => b
              case (_, Some(y)) if y == 0 && sameW(a, tpe) => a
              case (None, None) if sameW(a, tpe) && sameW(b, tpe) && eqSer(a, b) => uint(0, w(tpe))
              case _ => e
            }
            case DoPrim(Not, Seq(a), _, tpe) => a match {
              case u: UIntLiteral => uint(~u.value & ((BigInt(1) << w(tpe).toInt) - 1), w(tpe))
              case DoPrim(Not, Seq(inner), _, ti) if sameW(inner, ti) && sameW(inner, tpe) => inner
              case _ => e
            }
            case Mux(c, t, f, tpe) => lit(c) match {
              case Some(x) => if (x != 0) { if (sameW(t, tpe)) t else e }
                              else        { if (sameW(f, tpe)) f else e }
              case None if sameW(t, tpe) && sameW(f, tpe) && eqSer(t, f) => t
              case None if w(tpe) == 1 && w(t.tpe) == 1 && w(f.tpe) == 1 && w(c.tpe) == 1 =>
                (lit(t), lit(f)) match {
                  case (Some(x), _) if x == 1 => DoPrim(Or, Seq(c, f), Seq.empty, b1)
                  case (Some(x), _) if x == 0 =>
                    DoPrim(And, Seq(simp(DoPrim(Not, Seq(c), Seq.empty, b1)), f), Seq.empty, b1)
                  case (_, Some(y)) if y == 1 =>
                    DoPrim(Or, Seq(simp(DoPrim(Not, Seq(c), Seq.empty, b1)), t), Seq.empty, b1)
                  case (_, Some(y)) if y == 0 => DoPrim(And, Seq(c, t), Seq.empty, b1)
                  case _ => e
                }
              case _ => e
            }
            case other => other
          }
          if (!(r eq e)) foldedOps += 1
          r
        }
        def simpStmt(s: Statement): Statement = s match {
          case d: DefNode => d.copy(value = simp(d.value))
          case c: Connect => c.copy(expr = simp(c.expr))
          case other => other.mapExpr(simp)
        }
        for (i <- nodes.indices) {
          val n = nodes(i)
          n.role match {
            case RComb | REffect | RStateRead(_) | RStateCommit(_) =>
              val ns = simpStmt(n.stmt)
              if (!(ns eq n.stmt)) nodes(i) = n.copy(stmt = ns)
            case _ =>
          }
        }
        for ((r, ri) <- regInfos) ri.plan match {
          case RPSerialNext(folded, guarded) =>
            regInfos(r) = ri.copy(plan = RPSerialNext(simp(folded), guarded))
          case _ =>
        }

        // CSE: identical defining expressions collapse onto the first name;
        // the loser becomes a copy, which copy propagation then chases.
        val canonOf = mutable.Map[String, String]()
        for (i <- nodes.indices) {
          val n = nodes(i)
          if (n.role == RComb) n.stmt match {
            case d: DefNode if !d.value.isInstanceOf[WRef] && !d.value.isInstanceOf[UIntLiteral] =>
              val ser = d.value.serialize
              if (ser.length <= 4096) {
                val key = ser + "@" + w(d.value.tpe)
                canonOf.get(key) match {
                  case Some(canon) =>
                    nodes(i) = n.copy(stmt = d.copy(
                      value = WRef(canon, d.value.tpe, NodeKind, SourceFlow)))
                    cseDefs += 1
                  case None => canonOf(key) = d.name
                }
              }
            case _ =>
          }
        }

        // Copy propagation: readers of `a` where `a := b` or `a := literal`
        // read the target directly (defs stay; dead ones are pruned below).
        val aliasTgt = mutable.Map[String, Expression]()
        for (n <- nodes if n.role == RComb) n.stmt match {
          case d: DefNode => d.value match {
            case wr: WRef => aliasTgt(d.name) = wr
            case u: UIntLiteral => aliasTgt(d.name) = u
            case _ =>
          }
          case _ =>
        }
        def resolve(e: Expression, depth: Int): Expression = e match {
          case wr: WRef if depth < 32 => aliasTgt.get(wr.name) match {
            case Some(t) if w(t.tpe) == w(wr.tpe) => resolve(t, depth + 1)
            case _ => wr
          }
          case other => other
        }
        def chase(e: Expression): Expression = e match {
          case wr: WRef =>
            val t = resolve(wr, 0)
            if (!(t eq wr)) copyProps += 1
            t
          case other => other.mapExpr(chase)
        }
        def chaseStmt(s: Statement): Statement = s match {
          case d: DefNode => d.copy(value = d.value match {
            // keep the alias def itself intact; rewrite only inner reads
            case wr: WRef => wr
            case v => chase(v)
          })
          case c: Connect => c.copy(expr = chase(c.expr))
          case other => other.mapExpr(chase)
        }
        if (aliasTgt.nonEmpty) {
          for (i <- nodes.indices) {
            val n = nodes(i)
            n.role match {
              case RComb | REffect | RStateRead(_) | RStateCommit(_) =>
                val ns = chaseStmt(n.stmt)
                if (!(ns eq n.stmt)) nodes(i) = n.copy(stmt = ns)
              case _ =>
            }
          }
          for ((r, ri) <- regInfos) ri.plan match {
            case RPSerialNext(folded, guarded) =>
              regInfos(r) = ri.copy(plan = RPSerialNext(chase(folded), guarded))
            case _ =>
          }
        }
      }
      if (foldedOps + cseDefs + copyProps > 0)
        println(s"[v2] simplify: folded $foldedOps ops, cse $cseDefs defs, copy-propagated $copyProps reads")

      val roots = mutable.Set[String]()
      roots ++= findExternalPorts(circuit).keys
      for ((r, ri) <- regInfos) {
        roots += ri.nextName
        ri.plan match {
          case RPCondHold => roots += r + "$wen"; roots += r + "$wdata"
          case RPAffineScan => roots += r + "$keep"; roots += r + "$add"
          // The folded serial expression reads these names invisibly to
          // stmtReads: they must never be pruned or inlined away.
          case RPSerialNext(folded, guarded) =>
            roots ++= exprReads(folded)
            if (guarded) roots += r + "$gwen"
          case _ =>
        }
      }
      roots ++= combCuts.map(_ + "$rtl")
      for (n <- nodes if n.role == REffect) roots ++= stmtReads(n.stmt)
      // State-array address/write operands are consumed by custom roles and
      // must remain materialized even though those roles are not ordinary
      // RComb nodes in the liveness walk.
      for (si <- stateArrayInfos.values; tid <- si.readIds :+ si.commitId)
        roots ++= stmtReads(nodes(tid).stmt)

      // (a0) equality-chain lookup tables (2026-09-04). A dynamic index into
      // a constant Vec (AES S-box, GF(2^8) multiply tables) lowers to a chain
      // of named nodes _GEN_k = mux(eq(idx, k), c_k, _GEN_{k-1}) with literal
      // leaves, one shared index reference and a literal default at the head.
      // Branchless lowering would turn it into n compares + n masks + n ORs
      // per lane (AES: 48 chains x 256 entries = ~37k instructions per
      // simulated cycle). Replace the chain's tail by a dense constant table
      // indexed by the lane value (the FIRRTL width bounds the index, so a
      // 2^w-entry table is always in range); the private intermediates lose
      // their only reader and are pruned by (a). This runs before (b) on
      // purpose: single-use inlining splits long chains at its size cap.
      var eqLutsMade = 0
      locally {
        val MinEqChain = 12
        val MaxIndexBits = 10
        final case class EqLink(idx: WRef, key: BigInt, value: BigInt,
                                next: Either[BigInt, String], tpe: Type)
        def eqKey(c: Expression): Option[(WRef, BigInt)] = c match {
          case DoPrim(firrtl.PrimOps.Eq, Seq(lit: UIntLiteral, idx: WRef), _, _) => Some((idx, lit.value))
          case DoPrim(firrtl.PrimOps.Eq, Seq(idx: WRef, lit: UIntLiteral), _, _) => Some((idx, lit.value))
          case _ => None
        }
        val links = mutable.Map[String, EqLink]()
        val nodeOf = mutable.Map[String, Int]()
        for (n <- nodes if n.role == RComb) n.stmt match {
          case DefNode(_, nm, Mux(c, t: UIntLiteral, f, tpe)) =>
            for ((idx, k) <- eqKey(c)) {
              val next: Option[Either[BigInt, String]] = f match {
                case fl: UIntLiteral => Some(Left(fl.value))
                case r: WRef => Some(Right(r.name))
                case _ => None
              }
              for (nx <- next) { links(nm) = EqLink(idx, k, t.value, nx, tpe); nodeOf(nm) = n.id }
            }
          case _ =>
        }
        if (links.nonEmpty) {
          val rc = mutable.Map[String, Int]().withDefaultValue(0)
          for (n <- nodes; nm <- stmtReads(n.stmt)) rc(nm) += 1
          val referencedAsPrev = links.values.collect { case EqLink(_, _, _, Right(p), _) if links.contains(p) => p }.toSet
          for (tail <- links.keys.toSeq.sorted if !referencedAsPrev.contains(tail)) {
            val idx = links(tail).idx
            val tpe = links(tail).tpe
            val chain = ArrayBuffer[(String, BigInt, BigInt)]()
            var default: Option[BigInt] = None
            var cur = tail
            var ok = true
            var done = false
            while (ok && !done) {
              val l = links(cur)
              if (l.idx.name != idx.name) ok = false
              else {
                chain += ((cur, l.key, l.value))
                l.next match {
                  case Left(d) => default = Some(d); done = true
                  case Right(p) =>
                    // Only a private intermediate (read solely by this link)
                    // may be folded into the table.
                    if (links.contains(p) && rc(p) == 1) cur = p else ok = false
                }
              }
            }
            val idxBits = firrtl.bitWidth(idx.tpe)
            if (ok && default.isDefined && chain.size >= MinEqChain &&
                idxBits <= MaxIndexBits && firrtl.bitWidth(tpe) <= 64) {
              val size = 1 << idxBits.toInt
              val table = Array.fill[BigInt](size)(default.get)
              // chain(0) is the outermost mux (highest priority): fill from the
              // innermost link outward so earlier conditions win duplicates.
              for ((_, k, v) <- chain.reverse if k >= 0 && k < size) table(k.toInt) = v
              val nm = s"lut$$eq_$eqLutsMade"; eqLutsMade += 1
              addNode(LookupTable(nm, idx, table.toSeq, tpe), RComb, Some(nm))
              val tid = nodeOf(tail)
              nodes(tid) = nodes(tid).copy(stmt = DefNode(NoInfo, tail, WRef(nm, tpe, NodeKind, SourceFlow)))
            }
          }
        }
        if (eqLutsMade > 0)
          println(s"[v2] eq-chain LUT: $eqLutsMade index chains -> constant tables")
      }

      // (a) prune: oracling a cond-hold register orphans its materialized
      // $wen/$wdata templates (their work is duplicated in the $next cone).
      val prodMap = nodes.iterator
        .filter(n => n.role == RComb && n.produces.isDefined)
        .map(n => n.produces.get -> n.id).toMap
      val live = mutable.Set[String]()
      val work = mutable.Queue[String]() ++ roots
      while (work.nonEmpty) {
        val nm = work.dequeue()
        if (live.add(nm))
          prodMap.get(nm).foreach(id => stmtReads(nodes(id).stmt).foreach(work.enqueue(_)))
      }
      val dead = nodes.filter(n => n.role == RComb && n.produces.exists(!live.contains(_)))
      dead.foreach(n => nodes(n.id) = n.copy(stmt = EmptyStmt, produces = None))

      // (b) inline single-use temporaries. Every _s_ array is a store+load
      // round trip through memory (e.g. the ~110-deep csr rdata OR chain);
      // substituting the defining expression into the unique reader keeps the
      // value in registers and lets the backend reassociate chains. All comb
      // reads are same-lane (EData), so substitution is lane-safe; the
      // schedule is rebuilt afterwards, so loop placement stays consistent.
      val readCount = mutable.Map[String, Int]().withDefaultValue(0)
      for (n <- nodes; nm <- stmtReads(n.stmt)) readCount(nm) += 1
      val defExpr: Map[String, Expression] = nodes.iterator.flatMap { n =>
        if (n.role == RComb) n.stmt match {
          case d: DefNode => Some(d.name -> d.value)
          case _ => None
        } else None
      }.toMap
      // A lookup-table index must stay materialized: (b) substitutes only
      // DefNode/Connect expressions, so inlining the index's defining node
      // into a LookupTable statement would leave an unresolvable lane name
      // (BOOM/Rocket boot-ROM `index` after the (a0) rewrite).
      val lutIndexReads: Set[String] = nodes.iterator.flatMap { n =>
        n.stmt match {
          case lt: LookupTable => exprReads(lt.indexExpr)
          case _ => Seq.empty[String]
        }
      }.toSet
      val inlineCandidates: Set[String] = defExpr.keySet.filter { nm =>
        readCount(nm) == 1 && !roots.contains(nm) && !lutIndexReads.contains(nm)
      }
      // Do not let a chain of individually tiny, single-use nodes turn into
      // one enormous C++ expression.  Full-system Rocket/BOOM contains both
      // priority encoders (free lists) and ROM decoders with hundreds of
      // links.  Unbounded substitution made those expressions exceed
      // Clang's default bracket depth and could even overflow its parser
      // stack.  Select candidates in FIRRTL definition order and account for
      // the expression already folded into each selected dependency.  When a
      // budget is reached the current node remains materialized and becomes
      // a fresh boundary for later nodes in the chain.
      final case class InlineShape(nodes: Int, depth: Int)
      // Defaults keep full-system Rocket/BOOM expressions bounded; the two
      // environment knobs exist for the AES-style equality-chain experiment
      // (2026-09-04), where the cap splits one lookup chain into many
      // statements.
      val MaxInlineNodes = sys.env.get("V2_INLINE_MAX_NODES").map(_.toInt).getOrElse(96)
      val MaxInlineDepth = sys.env.get("V2_INLINE_MAX_DEPTH").map(_.toInt).getOrElse(20)
      val selectedShape = mutable.Map[String, InlineShape]()
      def boundedAdd(a: Int, b: Int, limit: Int): Int =
        if (a > limit - b) limit + 1 else a + b
      def expressionShape(e: Expression): InlineShape = e match {
        case w: WRef if selectedShape.contains(w.name) => selectedShape(w.name)
        case _ =>
          var nodesIn = 1
          var depthIn = 0
          e.foreachExpr { child =>
            val s = expressionShape(child)
            nodesIn = boundedAdd(nodesIn, s.nodes, MaxInlineNodes)
            depthIn = math.max(depthIn, s.depth)
          }
          InlineShape(nodesIn, math.min(MaxInlineDepth + 1, depthIn + 1))
      }
      for (n <- nodes if n.role == RComb) n.stmt match {
        case d: DefNode if inlineCandidates.contains(d.name) =>
          val shape = expressionShape(d.value)
          if (shape.nodes <= MaxInlineNodes && shape.depth <= MaxInlineDepth)
            selectedShape(d.name) = shape
        case _ =>
      }
      val inlineable: Set[String] = selectedShape.keySet.toSet
      val inlineCapRetained = inlineCandidates.size - inlineable.size
      if (inlineable.nonEmpty) {
        val memo = mutable.Map[String, Expression]()
        def substituteExpr(e: Expression): Expression = e match {
          case w: WRef if inlineable.contains(w.name) =>
            memo.getOrElseUpdate(w.name, substituteExpr(defExpr(w.name)))
          case other => other.mapExpr(substituteExpr)
        }
        def substituteStmt(s: Statement): Statement = s match {
          case d: DefNode => d.copy(value = substituteExpr(d.value))
          case c: Connect => c.copy(expr = substituteExpr(c.expr))
          case p: Print => p.copy(args = p.args.map(substituteExpr), en = substituteExpr(p.en))
          case st: Stop => st.copy(en = substituteExpr(st.en))
          case mw: MemWrite => mw.copy(wrEn = substituteExpr(mw.wrEn),
            wrMask = substituteExpr(mw.wrMask), wrAddr = substituteExpr(mw.wrAddr),
            wrData = substituteExpr(mw.wrData))
          case other => other
        }
        for (i <- nodes.indices) {
          val n = nodes(i)
          if (n.produces.exists(inlineable.contains))
            nodes(i) = n.copy(stmt = EmptyStmt, produces = None)
          else n.role match {
            case RComb | REffect | RStateRead(_) | RStateCommit(_) =>
              val ns = substituteStmt(n.stmt)
              if (!(ns eq n.stmt)) nodes(i) = n.copy(stmt = ns)
            case _ =>
          }
        }
      }

      // (c) decode-cone lookup tables. ListLookup decode lowers to one
      // priority mux chain PER control output, all walking the same pattern
      // match conditions; after inlining these are the dominant vec-comb cost
      // (~15 outputs x ~40-deep chains on sodor, every term re-loaded from
      // its own 1-bit lane array). For each group of chains sharing one
      // condition sequence emit ONE priority-index template (position of the
      // first true condition) and turn every output into a dense constant
      // table lookup — 16 cache-resident loads per output per window instead
      // of a 40-deep blend chain.
      var lutsMade = 0
      var bitmapLutsMade = 0
      locally {
        val MinChain = 12
        def peelChain(e: Expression): Option[(List[String], List[BigInt], BigInt)] = e match {
          case Mux(c: WRef, t: UIntLiteral, f, _) if firrtl.bitWidth(c.tpe) == 1 =>
            f match {
              case fl: UIntLiteral => Some((List(c.name), List(t.value), fl.value))
              case _ => peelChain(f).map { case (cs, vs, d) => (c.name :: cs, t.value :: vs, d) }
            }
          case _ => None
        }
        // Per-output chains share a common PREFIX of the decode pattern list
        // (trailing entries whose value equals the default were folded away
        // per output, so lengths differ). Prefix sharing is safe WITHOUT any
        // mutual-exclusivity assumption: if the shared index lands past a
        // short chain's end, all of that chain's conditions were false, so
        // the original evaluates its default — the padded table slots.
        val chainLists = ArrayBuffer[List[String]]()
        def scan(e: Expression): Unit = peelChain(e) match {
          case Some((cs, _, _)) if cs.size >= MinChain => chainLists += cs
          case _ => e.foreachExpr(scan)
        }
        for (n <- nodes if n.role == RComb) n.stmt.foreachExpr(scan)
        val masters = ArrayBuffer[List[String]]()
        val masterOf = mutable.Map[List[String], List[String]]()
        for (cs <- chainLists.sortBy(-_.size))
          masterOf.getOrElseUpdate(cs, masters.find(_.startsWith(cs)).getOrElse { masters += cs; cs })
        val useCount = chainLists.groupBy(masterOf).map { case (m, l) => m -> l.size }
        if (chainLists.nonEmpty) {
          val b1 = UIntType(IntWidth(1))
          val idxTpe = UIntType(IntWidth(8))
          val idxOf = mutable.Map[List[String], String]()
          def idxFor(cs: List[String]): String = idxOf.getOrElseUpdate(cs, {
            val nm = s"lut$$idx_${idxOf.size}"
            val expr = cs.zipWithIndex.foldRight(UIntLiteral(cs.size, IntWidth(8)): Expression) {
              case ((c, i), acc) =>
                Mux(WRef(c, b1, NodeKind, SourceFlow), UIntLiteral(i, IntWidth(8)), acc, idxTpe)
            }
            addNode(DefNode(NoInfo, nm, expr), RComb, Some(nm))
            nm
          })
          def tryLut(cs: List[String], vs: List[BigInt], d: BigInt, tpe: Type): Option[Expression] =
            masterOf.get(cs).filter(m => useCount(m) >= 2 && m.size <= 255).map { m =>
              val nm = s"lut$$v_$lutsMade"; lutsMade += 1
              val table = vs ++ List.fill(m.size - cs.size + 1)(d)
              addNode(LookupTable(nm, WRef(idxFor(m), idxTpe, NodeKind, SourceFlow),
                table, tpe), RComb, Some(nm))
              WRef(nm, tpe, NodeKind, SourceFlow)
            }
          def rewriteExpr(e: Expression): Expression = peelChain(e) match {
            case Some((cs, vs, d)) if cs.size >= MinChain =>
              tryLut(cs, vs, d, e.tpe).getOrElse(e)
            case _ => e.mapExpr(rewriteExpr)
          }
          val limit = nodes.size  // freshly added idx/lut nodes are final
          for (i <- 0 until limit) {
            val n = nodes(i)
            if (n.role == RComb) n.stmt match {
              case d: DefNode =>
                val nv = rewriteExpr(d.value)
                if (!(nv eq d.value)) nodes(i) = n.copy(stmt = d.copy(value = nv))
              case c: Connect =>
                val nv = rewriteExpr(c.expr)
                if (!(nv eq c.expr)) nodes(i) = n.copy(stmt = c.copy(expr = nv))
              case _ =>
            }
          }
          if (lutsMade > 0)
            println(s"[v2] decode LUT: $lutsMade chains -> constant tables, ${idxOf.size} shared index template(s)")
        }
      }

      // (d) branchless lowering + tree balancing.
      {
        // Associative tree balancing: inlining turns e.g. the CSR read-port
        // mux into one linear chain of ~80 ORs — an 80-deep dependency chain
        // per lane (measured hotspot). The terms are independent, so rebuild
        // same-op, same-width Or/And/Xor chains as log-depth trees. Add/Cat
        // widen in FIRRTL and are not freely reassociable — left alone.
        // 1-bit muxes emit as C++ `?:` whose nested chains icpx if-converts
        // poorly: measured fallout into per-lane scalar byte OR chains with
        // real branches (the decode cone). Lower them to branchless bitwise
        // select; rebalancing below then flattens the resulting Or/And trees.
        def mux1ToBitwise(e: Expression): Expression = {
          val e2 = e.mapExpr(mux1ToBitwise)
          e2 match {
            case Mux(c, t, f, tpe) if firrtl.bitWidth(tpe) == 1 &&
                firrtl.bitWidth(t.tpe) == 1 && firrtl.bitWidth(f.tpe) == 1 &&
                firrtl.bitWidth(c.tpe) == 1 =>
              val b1 = UIntType(IntWidth(1))
              // Arms may be SInt<1> (ImmGen sign bits); bitwise blending is
              // class-agnostic but the emitted C++ POD ops are not — wrap
              // SInt arms in asUInt so And/Or see one operand class.
              def asU(x: Expression): Expression = x.tpe match {
                case _: SIntType =>
                  DoPrim(firrtl.PrimOps.AsUInt, Seq(x), Seq.empty, b1)
                case _ => x
              }
              val blend = DoPrim(firrtl.PrimOps.Or, Seq(
                DoPrim(firrtl.PrimOps.And, Seq(asU(c), asU(t)), Seq.empty, b1),
                DoPrim(firrtl.PrimOps.And, Seq(
                  DoPrim(firrtl.PrimOps.Not, Seq(asU(c)), Seq.empty, b1), asU(f)), Seq.empty, b1)
              ), Seq.empty, b1)
              // The blend is UInt-typed. An SInt<1> mux (e.g. an ImmGen sign
              // bit) must keep its FIRRTL type: a UInt-declared node makes
              // every downstream SInt pad (= sign-extension) compile to the
              // UInt pad (= zero-extension), corrupting sign-extended
              // immediates. Re-tag with asSInt so the node type is preserved.
              tpe match {
                case _: SIntType =>
                  DoPrim(firrtl.PrimOps.AsSInt, Seq(blend), Seq.empty, SIntType(IntWidth(1)))
                case _ => blend
              }
            case other => other
          }
        }
        // OR-of-equalities -> bitmap LUT. A flattened 1-bit Or chain whose
        // leaves are `eq(x, const_i)` over one shared scrutinee is a set-
        // membership test. Left as arithmetic it costs one compare + one OR
        // per term per lane — Rocket's CSR-address decode (100 eq terms on a
        // UInt<12> node) compiled to a ~730-op serial k-mask chain worth 21%
        // of kernel time (statement static instrs 1051 -> 40 and kernel
        // 667 -> 546 ns/cycle when replaced by this bitmap; the loop then
        // vectorizes as gather + shift + and). Purely structural: no signal
        // names are consulted. Guards: >= MinEqTerms terms so small decoders
        // are left to the balanced tree, scrutinee width <= MaxBitmapIdxWidth
        // so the table stays cache-resident (2^14 bits = 2 KB), scrutinee is
        // a WRef so the index is never re-evaluated.
        val MinEqTerms = 16
        val MaxBitmapIdxWidth = 14
        def lutifyOrOfEq(ls: Seq[Expression]): Seq[Expression] = {
          def asEqLeaf(x: Expression): Option[(WRef, BigInt)] = x match {
            case DoPrim(firrtl.PrimOps.Eq, Seq(s: WRef, l: UIntLiteral), _, _) => Some((s, l.value))
            case DoPrim(firrtl.PrimOps.Eq, Seq(l: UIntLiteral, s: WRef), _, _) => Some((s, l.value))
            case _ => None
          }
          def scrutOk(s: WRef): Boolean = s.tpe match {
            case UIntType(IntWidth(sw)) => sw >= 2 && sw <= MaxBitmapIdxWidth
            case _ => false
          }
          val byScrut = ls.flatMap(asEqLeaf).filter { case (s, _) => scrutOk(s) }
            .groupBy(_._1.name)
          val lutable: Map[String, Seq[(WRef, BigInt)]] =
            byScrut.filter { case (_, g) => g.size >= MinEqTerms }
          if (lutable.isEmpty) ls
          else {
            val replaced = mutable.Set[String]()
            ls.flatMap { leaf =>
              asEqLeaf(leaf).filter { case (s, _) => lutable.contains(s.name) } match {
                case Some((s, _)) if replaced.contains(s.name) => None  // folded into the LUT leaf
                case Some((s, _)) =>
                  replaced += s.name
                  val sw = firrtl.bitWidth(s.tpe).toInt
                  val nWords = ((BigInt(1) << sw).toInt + 63) / 64
                  val words = Array.fill(nWords)(BigInt(0))
                  for ((_, v) <- lutable(s.name) if v >= 0 && v < (BigInt(1) << sw))
                    words((v >> 6).toInt) |= BigInt(1) << (v & 63).toInt
                  val nm = s"lut$$bm_$bitmapLutsMade"; bitmapLutsMade += 1
                  val b1 = UIntType(IntWidth(1))
                  addNode(LookupTable(nm, s, words.toSeq, b1, bitmap = true), RComb, Some(nm))
                  Some(WRef(nm, b1, NodeKind, SourceFlow))
                case None => Some(leaf)
              }
            }
          }
        }
        // Chain heads are handled top-down: when the node reached from a
        // non-same-op parent is an Or/And/Xor chain head, the WHOLE chain is
        // flattened here before any recursion, so lutifyOrOfEq sees the
        // maximal leaf set and a qualifying eq-chain becomes ONE bitmap.
        // (A children-first formulation collapsed every accumulated 16-leaf
        // window separately — Rocket's 100-term CSR chain fragmented into 6
        // partial bitmaps plus residual compares.) Recursion then continues
        // only into the surviving leaves, which are non-same-op subtrees.
        def rebalanceExpr(e: Expression): Expression = e match {
          case DoPrim(op, _, _, tpe)
              if op == firrtl.PrimOps.Or || op == firrtl.PrimOps.And || op == firrtl.PrimOps.Xor =>
            val w = firrtl.bitWidth(tpe)
            def chainLeaves(x: Expression): Seq[Expression] = x match {
              case DoPrim(o2, args, _, t2) if o2 == op && firrtl.bitWidth(t2) == w =>
                args.flatMap(chainLeaves)
              case other => Seq(other)
            }
            val ls0 = chainLeaves(e)
            if (ls0.exists(l => firrtl.bitWidth(l.tpe) != w)) e.mapExpr(rebalanceExpr)
            else {
              val canLut = op == firrtl.PrimOps.Or && w == 1 && ls0.size >= MinEqTerms
              val lsL = if (canLut) lutifyOrOfEq(ls0) else ls0
              val ls = lsL.map(rebalanceExpr)
              if (ls.size == 1) ls.head
              else {
                def build(xs: Seq[Expression]): Expression =
                  if (xs.size == 1) xs.head
                  else {
                    val (a, b) = xs.splitAt(xs.size / 2)
                    DoPrim(op, Seq(build(a), build(b)), Seq.empty, tpe)
                  }
                build(ls)
              }
            }
          case other => other.mapExpr(rebalanceExpr)
        }
        def rebalanceStmt(s: Statement): Statement = s match {
          case d: DefNode => d.copy(value = rebalanceExpr(mux1ToBitwise(d.value)))
          case c: Connect => c.copy(expr = rebalanceExpr(mux1ToBitwise(c.expr)))
          case other => other
        }
        for (i <- nodes.indices) {
          val n = nodes(i)
          n.role match {
            case RComb | REffect | RStateRead(_) | RStateCommit(_) =>
              val ns = rebalanceStmt(n.stmt)
              if (!(ns eq n.stmt)) nodes(i) = n.copy(stmt = ns)
            case _ =>
          }
        }
      }
      if (dead.nonEmpty || inlineable.nonEmpty || lutsMade > 0 || bitmapLutsMade > 0 || eqLutsMade > 0) {
        println(s"[v2] pruned ${dead.size} dead comb templates, inlined ${inlineable.size}/${inlineCandidates.size} single-use temps" +
          (if (inlineCapRetained > 0) s", retained $inlineCapRetained expression boundary temps" else ""))
        if (bitmapLutsMade > 0)
          println(s"[v2] eq-chain bitmap LUT: $bitmapLutsMade OR-of-eq chains -> membership bitmaps")
        edges = buildEdges(regInfos)
        sccs = tarjan(nodes.size, edges)
      }
    }

    val selfLoopIds = edges.filter(e => e.from == e.to).map(_.from).toSet
    val serialSccs = sccs.filter(s => s.size > 1 || s.exists(selfLoopIds.contains))
    val sccSerialTemplates = serialSccs.flatten.toSet
    // Experimental correctness fallback for oracle-budget ablations. The
    // normal v2 mode collapses every non-SCC template to one full-width unit;
    // that loses the exact lane offset when an acyclic chain still contains an
    // EShift edge. Expanding both endpoints preserves the real per-lane edge.
    // Opt-in only: default full-oracle code generation is unchanged.
    val conservativeShiftSerial = sys.env.get("V2_CONSERVATIVE_SHIFT_SERIAL")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    val forceAllSerial = sys.env.get("V2_FORCE_ALL_SERIAL")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    val shiftSerialTemplates = if (conservativeShiftSerial)
      edges.iterator.filter(_.kind == EShift).flatMap(e => Iterator(e.from, e.to)).toSet
    else Set.empty[Int]
    // A state commit mutates the one persistent pre-window image and must run
    // once, after every read port.  Expanding it into per-lane schedule units
    // would allow an early lane to clobber the base seen by a later read.
    val stateCommitTemplates = stateArrayInfos.valuesIterator.map(_.commitId).toSet
    val serialTemplates = (if (forceAllSerial) nodes.indices.toSet
      else sccSerialTemplates ++ shiftSerialTemplates) -- stateCommitTemplates
    val sccOf: Map[Int, Int] = serialSccs.zipWithIndex.flatMap {
      case (scc, i) => scc.map(_ -> i)
    }.toMap
    if (serialTemplates.nonEmpty)
      println(s"[v2] ${serialSccs.size} serial region(s) remain, ${serialTemplates.size} templates " +
        s"(frozen or below oracle threshold) — scheduled per-lane")
    if (conservativeShiftSerial)
      println(s"[v2] experimental conservative shift serialization: " +
        s"+${(shiftSerialTemplates -- sccSerialTemplates).size} templates")
    if (forceAllSerial)
      println(s"[v2] experimental all-template serialization enabled")

    // ---- oracle manifest (registers + comb cuts, one namespace) ----
    val wideOracleRegs = chosen.toSeq.sorted.filter(r => firrtl.bitWidth(regInfos(r).tpe) > 64)
    if (wideOracleRegs.nonEmpty)
      println(s"[v2] wide register oracles: ${wideOracleRegs.size} register(s) split into " +
        s"${wideOracleRegs.map(r => (firrtl.bitWidth(regInfos(r).tpe).toInt + 63) / 64).sum} word stream(s)")
    val oracles = chosen.toSeq.sorted.flatMap { r =>
      val w = firrtl.bitWidth(regInfos(r).tpe).toInt
      val key = r.replace('.', '_')
      if (w <= 64) Seq(OracleSpec(r, key, s"trace_$key", w, isRegister = true, verified = wantVerify))
      else if (!wideOracleEnabled || regInfos(r).tpe.isInstanceOf[firrtl.ir.SIntType])
        throw new IllegalStateException(s"[v2] oracle register '$r' wider than 64 bits unsupported " +
          "(V2_WIDE_ORACLE=1 supports UInt registers)")
      else {
        val words = (w + 63) / 64
        (0 until words).map { i =>
          val wb = if (i == words - 1) w - 64 * i else 64
          OracleSpec(r, s"${key}__w$i", s"trace_${key}__w$i", wb, isRegister = true,
            verified = wantVerify, word = i, words = words)
        }
      }
    } ++ combCuts.toSeq.sorted.map { n =>
      val key = n.replace('.', '_')
      OracleSpec(n, key, s"trace_$key", firrtl.bitWidth(combCutTypes(n)).toInt,
        isRegister = false, verified = wantVerify)
    }

    val producesIdx: Map[String, Int] =
      nodes.iterator.flatMap(n => n.produces.map(_ -> n.id)).toMap

    // LowerTypes flattens one bundle write into one mux-hold recurrence per
    // field. Preserve that lost structure for code generation: fields whose
    // exact extracted write-enable expression is identical can share the
    // window's last-writer index. IDs follow register discovery order, not a
    // hash-map iteration order, so generated names remain deterministic.
    val condHoldRegsByWen = mutable.LinkedHashMap[String, ArrayBuffer[String]]()
    for ((r, ri) <- regInfos if ri.plan == RPCondHold; wen <- muxHoldWenByReg.get(r))
      condHoldRegsByWen.getOrElseUpdate(wen, ArrayBuffer[String]()) += r
    val condHoldGroupOf = mutable.LinkedHashMap[String, Int]()
    var nextCondHoldGroup = 0
    for ((_, regs) <- condHoldRegsByWen if regs.size >= 2) {
      regs.foreach(condHoldGroupOf(_) = nextCondHoldGroup)
      nextCondHoldGroup += 1
    }
    if (condHoldGroupOf.nonEmpty)
      println(s"[v2] shared-wen cond-hold: ${condHoldGroupOf.size} register fields in " +
        s"$nextCondHoldGroup group(s)")

    // Direction changes only the lane indexing of shift/verify (offset sign);
    // the digraph and its SCCs are identical, but the per-lane instance edges
    // of serial regions differ, so each direction gets its own Kahn pass.
    val schedFwd = scheduleUnits(nodes.toIndexedSeq, edges, serialTemplates, sccOf, W, dir = +1, fuseCap)
    val schedRev = scheduleUnits(nodes.toIndexedSeq, edges, serialTemplates, sccOf, W, dir = -1, fuseCap)

    println(s"[v2] templates=${nodes.size} regs=${regDefs.size} oracles=${chosen.size} " +
      s"serialTemplates=${serialTemplates.size} schedUnits=${schedFwd.size}")
    println(s"[v2] oracle budget=${if (oracleLimit < 0) "unlimited" else oracleLimit.toString} " +
      s"selected=${oracles.size} (reg=${chosen.size}, comb=${combCuts.size})")

    val missingAudit = oracles.map(_.flatName).filterNot(oracleAudit.contains)
    require(missingAudit.isEmpty,
      s"[v2-audit] selected oracle(s) missing provenance: ${missingAudit.take(8).mkString(", ")}")
    val orderedAudit = oracles.map(o => oracleAudit(o.flatName))

    val deadStateReport = DeadStatePruneReport(
      sourceEffectsKept = keepSourceEffects,
      enabled = !keepSourceEffects && !disableDeadStatePrune,
      sourceRegisterCount = deadState.sourceRegisters,
      removedRegisters = deadState.removed)
    val partitionTemplates: Seq[Set[Int]] =
      if (partitionCount == 0) Nil
      else {
        val (cones, crossRegs, _) = partitionCones(edges, regInfos)
        val leftover = crossRegs.flatMap(_.toSeq).distinct
        if (leftover.nonEmpty) {
          for (p <- 0 until partitionCount; r <- crossRegs(p).take(3)) {
            val via = crossVia.get((p, r)).map(id => describeNode(nodes(id))).getOrElse("?")
            println(s"[v2-partition] partition $p reads non-oracle register $r via $via")
            var id = crossVia.getOrElse((p, r), -1); var hops = 0
            while (id >= 0 && hops < 14) {
              println(s"[v2-partition]   pulled by: ${describeNode(nodes(id))}")
              id = coneParent.getOrElse((p, id), -1); hops += 1
            }
          }
        }
        require(leftover.isEmpty,
          s"[v2-partition] non-oracle cross-partition reads remain: ${leftover.take(6).mkString(", ")}")
        val total = cones.map(_.size).sum
        println(s"[v2-partition] final: $partitionCount partition(s), templates " +
          cones.map(_.size).mkString("/") + f", replication ${total.toDouble / nodes.size}%.2fx")
        // Balance aid: comb templates per module (6 path segments) in each cone.
        def moduleOf(n: TemplateNode): String = {
          val name = n.produces.getOrElse(stmtReads(n.stmt).headOption.getOrElse(""))
          name.split('.').dropRight(1).take(6).mkString(".")
        }
        for (p <- 0 until partitionCount) {
          val byModule = cones(p).toSeq.filter(id => nodes(id).role == RComb)
            .groupBy(id => moduleOf(nodes(id))).map { case (m, ids) => (m, ids.size) }
            .toSeq.sortBy(-_._2).take(8)
          println(s"[v2-partition] partition $p comb by module: " +
            byModule.map { case (m, c) => s"${m.split('.').takeRight(2).mkString(".")}=$c" }.mkString(", "))
        }
        cones.map(_.toSet)
      }
    Result(nodes.toIndexedSeq, regInfos.toMap, stateArrayInfos, allRegisterBanks,
      combCutTypes.toMap, oracles, schedFwd, schedRev, producesIdx, sccOf,
      serialTemplates.size, condHoldGroupOf.toMap, orderedAudit, clockLowered.report,
      deadStateReport, hostBoundaryInputs, accessProofDataOracles.toSet,
      partitionTemplates)
  }

  private def describeNode(n: TemplateNode): String = n.role match {
    case RComb => s"comb:${n.produces.getOrElse("?")}"
    case RRegSource(r) => s"src:$r"
    case RRegCommit(r) => s"commit:$r"
    case ROracleInject(r) => s"oracle:$r"
    case RVerify(r) => s"verify:$r"
    case RStateRead(a) => s"state-read:$a:${n.produces.getOrElse("?") }"
    case RStateCommit(a) => s"state-commit:$a"
    case REffect => "effect"
  }

  // ------------------------------------------------------------------
  // FVS minimization on the register projection of one SCC.
  // Every cycle passes through at least one register source (the offset-0
  // subgraph is acyclic), so it suffices to make the projection acyclic.
  // ------------------------------------------------------------------
  private def minimizeFvs(cands: Seq[String], scc: Set[Int],
      nodes: CIndexedSeq[TemplateNode], edges: CIndexedSeq[TemplateEdge],
      infos: collection.Map[String, RegInfo]): Seq[String] = {
    val started = System.nanoTime()
    if (cands.size >= 512)
      println(s"[v2-fvs] large projection: templates=${scc.size} registers=${cands.size}")
    val sourceIdToReg = cands.map(r => infos(r).sourceId -> r).toMap
    val adj = edges.filter(e => scc.contains(e.from) && scc.contains(e.to))
      .groupBy(_.from).map { case (k, es) => k -> es.map(_.to).distinct }
      .withDefaultValue(Seq.empty)
    // reg projection: r1 -> r2 iff path from S_r1 to S_r2 not passing another source
    val proj = mutable.Map[String, mutable.Set[String]]()
    for (r <- cands) {
      val reach = mutable.Set[String]()
      val visited = mutable.Set[Int]()
      val work = mutable.Queue[Int]()
      adj(infos(r).sourceId).foreach(work.enqueue(_))
      while (work.nonEmpty) {
        val cur = work.dequeue()
        if (!visited.contains(cur)) {
          visited += cur
          sourceIdToReg.get(cur) match {
            case Some(r2) => if (r2 != r) reach += r2
            // a self-path not via other sources = cond-hold cone, legal serial
            case None => adj(cur).foreach(n => if (!visited.contains(n)) work.enqueue(n))
          }
        }
      }
      proj(r) = reach
    }
    // V2_DUMP_PROJECTION: write the register-projection graph this selector
    // actually solves, so the FVS quality (lower bounds, cycle structure)
    // can be audited offline instead of trusted.
    sys.env.get("V2_DUMP_PROJECTION").foreach { path =>
      val f = new java.io.PrintWriter(path)
      f.println("{")
      f.println(s"""  "candidates": ${cands.size},""")
      f.println("""  "edges": [""")
      val lines = for (r <- cands; r2 <- proj(r).toSeq.sorted)
        yield s"""    ["$r","$r2"]"""
      f.println(lines.mkString(",\n"))
      f.println("  ]")
      f.println("}")
      f.close()
      println(s"[v2-fvs] projection dumped: ${cands.size} nodes, ${proj.valuesIterator.map(_.size).sum} edges -> $path")
    }
    // greedy FVS: self-loops mandatory, then max in*out until acyclic
    val picked = ArrayBuffer[String]()
    var active = cands.toSet
    picked ++= cands.filter(r => proj(r).contains(r))
    active --= picked
    def activeCyclic(): Set[String] = {
      val g = active.map(r => r -> (proj(r).toSet & active)).toMap
      tarjanStr(active, g).filter(s => s.size > 1 ||
        (s.size == 1 && g(s.head).contains(s.head))).flatten.toSet
    }
    if (cands.size < 512) {
      var cyc = activeCyclic()
      while (cyc.nonEmpty) {
        // Accumulate indegrees by walking actual projection edges instead of
        // the former nested |cyc| membership scans.
        val inDeg = mutable.Map[String, Int]().withDefaultValue(0)
        val outDeg = mutable.Map[String, Int]().withDefaultValue(0)
        for (from <- cyc; to <- proj(from) if cyc.contains(to)) {
          outDeg(from) += 1
          inDeg(to) += 1
        }
        val best = cyc.maxBy(r =>
          (outDeg(r).toLong * (inDeg(r) + 1L), outDeg(r), inDeg(r), r))
        picked += best
        active -= best
        cyc = activeCyclic()
      }
    } else {
      // Re-running Tarjan after every selected vertex is still O(F*(R+E)).
      // On complete Small BOOM, 128 picks took 68 seconds with 6.6k cyclic
      // registers remaining. Use the standard source/sink-peeling directed
      // FVS heuristic inside each initial cyclic SCC: a lazy degree heap and
      // incremental adjacency updates make the whole selection O((R+E)logR).
      // Peeling never removes a cycle vertex unless a previously selected
      // vertex has already broken that cycle; the final assertion below
      // independently proves the residual projection acyclic.
      val graph = active.map(r => r -> (proj(r).toSet & active)).toMap
      val cyclicComponents = tarjanStr(active, graph)
        .filter(s => s.size > 1 || (s.size == 1 && graph(s.head).contains(s.head)))
        .sortBy(_.min)
      val fastPicks = cyclicComponents.flatMap(comp => scalableFvsComponent(comp, graph))
      picked ++= fastPicks
      active --= fastPicks
      val residual = active.map(r => r -> (proj(r).toSet & active)).toMap
      val residualCycles = tarjanStr(active, residual).filter(s => s.size > 1 ||
        (s.size == 1 && residual(s.head).contains(s.head)))
      require(residualCycles.isEmpty,
        s"[v2-fvs] scalable selector left ${residualCycles.size} cyclic component(s)")
    }
    if (cands.size >= 512) {
      val elapsedMs = (System.nanoTime() - started) / 1000000L
      println(s"[v2-fvs] complete picked=${picked.size}/${cands.size} elapsedMs=$elapsedMs")
    }
    // V2_FVS_MINIMIZE: reverse-deletion pass. A pick that can rejoin the
    // residual graph without closing a cycle was never necessary; returning
    // it turns one injected stream back into ordinary acyclic (vectorizable)
    // computation. Offline measurement on Small W16: 1,517 -> 1,282 picks.
    val minimized: Seq[String] =
      if (!sys.env.get("V2_FVS_MINIMIZE").contains("1") || picked.isEmpty) picked.toSeq
      else {
        val t0 = System.nanoTime()
        val pickSet = mutable.Set[String]() ++ picked
        val inG = mutable.Set[String]() ++ cands.filterNot(pickSet)
        def createsCycle(v: String): Boolean = {
          val succ = proj(v).iterator.filter(inG).toArray
          if (succ.isEmpty) return false
          val pred = inG.iterator.filter(u => proj(u).contains(v)).toSet
          if (pred.isEmpty) return false
          val seen = mutable.Set[String]() ++ succ
          val work = mutable.Queue[String]() ++ succ
          while (work.nonEmpty) {
            val u = work.dequeue()
            if (pred.contains(u)) return true
            for (w <- proj(u) if inG.contains(w) && !seen.contains(w)) {
              seen += w; work.enqueue(w)
            }
          }
          false
        }
        var returned = 0
        for (v <- picked.sortBy(r => proj(r).size)) {
          if (!createsCycle(v)) { pickSet -= v; inG += v; returned += 1 }
        }
        val ms = (System.nanoTime() - t0) / 1000000L
        println(s"[v2-fvs] reverse-deletion minimization: returned=$returned " +
          s"picks=${picked.size}->${pickSet.size} elapsedMs=$ms")
        picked.filter(pickSet).toSeq
      }
    minimized
  }

  /** Linearithmic greedy FVS for one known cyclic SCC. Nodes with zero
    * in-degree or out-degree are peeled for free; otherwise the same
    * out*(in+1) score as the legacy selector chooses one oracle vertex. */
  private[v2] def scalableFvsComponent(component: Set[String],
      graph: Map[String, Set[String]]): Seq[String] = {
    val names = component.toSeq.sorted
    val index = names.zipWithIndex.toMap
    val n = names.size
    val out = Array.fill(n)(mutable.ArrayBuffer[Int]())
    val in = Array.fill(n)(mutable.ArrayBuffer[Int]())
    for (from <- names; to <- graph(from) if component.contains(to)) {
      val f = index(from); val t = index(to)
      out(f) += t
      in(t) += f
    }
    val active = Array.fill(n)(true)
    val inDeg = in.map(_.size)
    val outDeg = out.map(_.size)
    val version = Array.fill(n)(0)
    val zero = mutable.Queue[Int]()
    case class Entry(score: Long, out: Int, in: Int, name: String, id: Int, version: Int)
    implicit val entryOrdering: Ordering[Entry] = Ordering.by(e =>
      (e.score, e.out, e.in, e.name))
    val heap = mutable.PriorityQueue.empty[Entry]

    def enqueue(id: Int): Unit = if (active(id)) {
      version(id) += 1
      if (inDeg(id) == 0 || outDeg(id) == 0) zero.enqueue(id)
      else heap.enqueue(Entry(outDeg(id).toLong * (inDeg(id) + 1L),
        outDeg(id), inDeg(id), names(id), id, version(id)))
    }
    def remove(id: Int): Unit = if (active(id)) {
      active(id) = false
      out(id).foreach { to => if (active(to)) { inDeg(to) -= 1; enqueue(to) } }
      in(id).foreach { from => if (active(from)) { outDeg(from) -= 1; enqueue(from) } }
    }
    (0 until n).foreach(enqueue)
    val picked = ArrayBuffer[String]()
    var remaining = n
    while (remaining > 0) {
      var peeled = true
      while (peeled) {
        peeled = false
        while (zero.nonEmpty) {
          val id = zero.dequeue()
          if (active(id) && (inDeg(id) == 0 || outDeg(id) == 0)) {
            remove(id); remaining -= 1; peeled = true
          }
        }
      }
      if (remaining > 0) {
        var chosen = -1
        while (chosen < 0 && heap.nonEmpty) {
          val e = heap.dequeue()
          if (active(e.id) && e.version == version(e.id) &&
              e.in == inDeg(e.id) && e.out == outDeg(e.id)) chosen = e.id
        }
        require(chosen >= 0,
          s"[v2-fvs] no scored vertex remains in cyclic component of ${component.size}")
        picked += names(chosen)
        remove(chosen)
        remaining -= 1
      }
    }
    picked.toSeq
  }

  /** Stable benefit order for prefixes of an already chosen FVS. It never
    * changes which registers the unlimited compiler selects. */
  private def orderFvsForBudget(picks: Seq[String], scc: Set[Int],
      nodes: CIndexedSeq[TemplateNode], edges: CIndexedSeq[TemplateEdge],
      infos: collection.Map[String, RegInfo]): Seq[String] = {
    val ids = picks.map(r => r -> infos(r).sourceId).toMap
    val inDeg = mutable.Map[String, Int]().withDefaultValue(0)
    val outDeg = mutable.Map[String, Int]().withDefaultValue(0)
    val ownerById = ids.map(_.swap)
    for (e <- edges if scc.contains(e.from) && scc.contains(e.to)) {
      ownerById.get(e.from).foreach(r => outDeg(r) += 1)
      ownerById.get(e.to).foreach(r => inDeg(r) += 1)
    }
    picks.distinct.sortBy(r => (-(inDeg(r) + 1L) * (outDeg(r) + 1L), r))
  }

  // ------------------------------------------------------------------
  // Grouping + quotient schedule.
  // Non-SCC templates: one full-W vector unit. SCC templates: W lane units.
  // Quotient is provably acyclic; Kahn with (scc, lane) priority keeps
  // serial chains contiguous.
  // ------------------------------------------------------------------
  private def scheduleUnits(nodes: CIndexedSeq[TemplateNode], edges: CIndexedSeq[TemplateEdge],
      serial: Set[Int], sccOf: Map[Int, Int], W: Int, dir: Int, fuseCap: Int): Seq[SchedUnit] = {
    val unitIndex = mutable.LinkedHashMap[(Int, Int), Int]()  // (tid, lane|-1) -> unit id
    val units = ArrayBuffer[SchedUnit]()
    def unitOf(tid: Int, lane: Int): Int = {
      val key = if (serial.contains(tid)) (tid, lane) else (tid, -1)
      unitIndex.getOrElseUpdate(key, {
        units += (if (key._2 < 0) UVec(tid) else ULane(tid, lane))
        units.size - 1
      })
    }
    for (n <- nodes) {
      // Dead-pruned and inlined comb templates are EmptyStmt husks: they
      // produce nothing, read nothing, and emit nothing — but scheduling
      // them consumed fuse-cap slots (BOOM: 9484 husks of 22450 templates,
      // scattering real statements into 1704 single-statement loops and 326
      // fully empty ones). Sources/injects/verifies keep EmptyStmt bodies
      // legitimately; only comb/effect husks are dropped.
      val husk = (n.role == RComb || n.role == REffect) && n.stmt == EmptyStmt
      if (!husk) {
        if (serial.contains(n.id)) (0 until W).foreach(k => unitOf(n.id, k))
        else unitOf(n.id, -1)
      }
    }
    val nUnits = units.size
    val outAdj = Array.fill(nUnits)(mutable.Set[Int]())
    val inDeg = Array.fill(nUnits)(0)
    def addUEdge(a: Int, b: Int): Unit =
      if (a != b && outAdj(a).add(b)) inDeg(b) += 1

    // Edge (u,v,off): v@k reads u@{k - off*dir}. dir=+1 forward, -1 reverse.
    for (e <- edges) {
      val d = e.kind.offset * dir
      (serial.contains(e.from), serial.contains(e.to)) match {
        case (false, false) => addUEdge(unitOf(e.from, -1), unitOf(e.to, -1))
        case (false, true)  => for (k <- 0 until W if k - d >= 0 && k - d < W)
          addUEdge(unitOf(e.from, -1), unitOf(e.to, k))
        case (true, false)  => for (j <- 0 until W if j + d >= 0 && j + d < W)
          addUEdge(unitOf(e.from, j), unitOf(e.to, -1))
        case (true, true)   => for (k <- 0 until W if k - d >= 0 && k - d < W)
          addUEdge(unitOf(e.from, k - d), unitOf(e.to, k))
      }
    }

    // Kahn with priority: serial chains contiguous (scc asc, lane in dep
    // order); vector units layered by role so combinational statements form
    // long fusable runs, template order within a layer approximates source
    // locality. (A greedy locality-aware list scheduler was tried here and
    // measured strictly worse, 184 vs 162 ns/cycle on sodor W=16: it fused
    // commits 27->3 loops and grew comb runs 8.5->15.2 templates, but the
    // cross-loop read share stayed at 97% — multi-use values spread over
    // many loops no matter the order — while the changed emission order
    // lost the source-order cache locality of the static priority.)
    // V2_SOURCE_RANK_LOW experiment: rank reg-sources BELOW comb. With the
    // default (source=3 > comb=2) any source that becomes ready is dequeued
    // immediately and alone — on BOOM that emits 543 singleton reg-source
    // regions which, together with serial islands, cut the fusable comb runs
    // into ~1300 fragments. Ranking sources low lets them pool in the ready
    // set while comb drains, so consecutive dequeues batch into one CSource
    // loop. Off by default pending A/B (same class of risk as the greedy
    // scheduler note above).
    val sourceRankLow = sys.env.get("V2_SOURCE_RANK_LOW")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    def roleRank(t: Int): Int = nodes(t).role match {
      case ROracleInject(_) => 4
      case RRegSource(_)    => if (sourceRankLow) 2 else 3
      case RComb | REffect | RStateRead(_) => if (sourceRankLow) 3 else 2
      case RVerify(_)       => 1
      case RRegCommit(_) | RStateCommit(_) => 0
    }
    // (Scheduling serial lanes EARLY — priority 2 — was tried to widen the
    // store->load distance at scalar/vector boundaries; measured 178 vs 161
    // ns/cycle: worse. Serial chains stay lowest priority.)
    // V2_SERIAL_BURST experiment: baseline Kahn pops a serial lane only when
    // no vector unit is ready, and the comb unlocked by that lane preempts the
    // NEXT serial region — yielding serial/tiny-comb interleaving (858
    // serial|serial small-run interrupters on BOOM, 33% of samples in <=2
    // template loops). Burst mode: once a serial lane pops, keep draining
    // ready serial lanes until none remain, so independent zipper regions
    // emit contiguously and their unlocked combs coalesce into longer runs.
    val serialBurst = sys.env.get("V2_SERIAL_BURST")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    val vecReady = mutable.PriorityQueue[Int]()(Ordering.by { uid: Int =>
      units(uid) match {
        case UVec(t) => (roleRank(t), -t)
        case _       => (Int.MinValue, 0)
      }
    })
    val laneReady = mutable.PriorityQueue[Int]()(Ordering.by { uid: Int =>
      units(uid) match {
        case ULane(t, k) => (-sccOf.getOrElse(t, 0), -k * dir, -t)
        case _           => (Int.MinValue, 0, 0)
      }
    })
    def enqueueReady(u: Int): Unit = units(u) match {
      case UVec(_)     => vecReady.enqueue(u)
      case ULane(_, _) => laneReady.enqueue(u)
    }
    for (u <- 0 until nUnits if inDeg(u) == 0) enqueueReady(u)
    val order = ArrayBuffer[SchedUnit]()
    var burst = false
    while (vecReady.nonEmpty || laneReady.nonEmpty) {
      val takeLane =
        if (laneReady.isEmpty) { burst = false; false }
        else if (vecReady.isEmpty) { burst = true; true }
        else if (serialBurst && burst) true
        else false
      val u = if (takeLane) laneReady.dequeue() else vecReady.dequeue()
      order += units(u)
      for (v <- outAdj(u)) { inDeg(v) -= 1; if (inDeg(v) == 0) enqueueReady(v) }
    }
    if (order.size != nUnits) {
      val stuck = (0 until nUnits).filter(inDeg(_) > 0).take(10)
        .map(u => units(u) match {
          case UVec(t) => describeNode(nodes(t))
          case ULane(t, k) => s"${describeNode(nodes(t))}@lane$k"
        })
      throw new IllegalStateException(
        s"[v2] INVARIANT VIOLATION: quotient graph is cyclic (${nUnits - order.size} unscheduled). " +
        s"This is a compiler bug (theorem: quotient of SCC-grouped template graph is acyclic). Stuck: ${stuck.mkString("; ")}")
    }
    // Verify and commit units have no data successors (verify only asserts;
    // commit only feeds the NEXT window through the boundary lane), yet Kahn
    // interleaves them wherever serial chains stall the ready set, cutting
    // the fusable comb runs into ~130 fragments. Moving them to the tail is
    // always legal — every in-edge source precedes them — and verify keeps
    // its WAR position before commit. Comb/source runs get longer and the
    // ~30 scattered commit loops fuse into a few cap-bounded ones.
    def tailRank(u: SchedUnit): Int = nodes(u.tid).role match {
      case RVerify(_)   => 1
      case RRegCommit(_) => 2
      case _ => 0
    }
    val (body, tail) = order.partition(u => tailRank(u) == 0)
    (body ++ tail.sortBy(u => (tailRank(u), u.tid))).toSeq
  }

  // ------------------------------------------------------------------
  // Tarjan SCC (iterative), integer nodes.
  // ------------------------------------------------------------------
  private def tarjan(n: Int, edges: CIndexedSeq[TemplateEdge]): Seq[Set[Int]] = {
    val adj = Array.fill(n)(ArrayBuffer[Int]())
    edges.foreach(e => adj(e.from) += e.to)
    val index = Array.fill(n)(-1)
    val low = Array.fill(n)(0)
    val onStack = Array.fill(n)(false)
    val stack = mutable.Stack[Int]()
    var counter = 0
    val out = ArrayBuffer[Set[Int]]()
    for (root <- 0 until n if index(root) < 0) {
      val work = mutable.Stack[(Int, Int)]((root, 0))
      while (work.nonEmpty) {
        val (v, pi) = work.pop()
        if (pi == 0) { index(v) = counter; low(v) = counter; counter += 1; stack.push(v); onStack(v) = true }
        var i = pi
        var recursed = false
        while (i < adj(v).size && !recursed) {
          val wn = adj(v)(i)
          if (index(wn) < 0) { work.push((v, i + 1)); work.push((wn, 0)); recursed = true }
          else { if (onStack(wn)) low(v) = math.min(low(v), index(wn)); i += 1 }
        }
        if (!recursed) {
          if (low(v) == index(v)) {
            val scc = mutable.Set[Int]()
            var wn = -1
            do { wn = stack.pop(); onStack(wn) = false; scc += wn } while (wn != v)
            out += scc.toSet
          }
          work.headOption.foreach { case (p, _) => low(p) = math.min(low(p), low(v)) }
        }
      }
    }
    out.toSeq
  }

  private def tarjanStr(ns: Set[String], g: Map[String, Set[String]]): Seq[Set[String]] = {
    val idx = ns.toSeq.sorted.zipWithIndex.toMap
    val rev = idx.map(_.swap)
    val edges = for ((a, ds) <- g.toSeq; d <- ds if idx.contains(d))
      yield TemplateEdge(idx(a), idx(d), EData)
    tarjan(ns.size, edges.toIndexedSeq).map(_.map(rev))
  }
}
