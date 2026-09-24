package essent.simd.v2

import essent.{Renamer, SigMeta, Local, RegSet, ExtIO, OptFlags}
import essent.Emitter._
import essent.Extract._
import essent.Util.IndentWriter
import essent.simd.v2.V2Pipeline._

import firrtl._
import firrtl.ir._

import java.io.{File, FileWriter, Writer}
import collection.mutable
import collection.mutable.ArrayBuffer

/** C++ emission for the v2 pipeline. One flat namespace; registers are
  * member arrays `T reg[W]` in nested module structs (member path == flat
  * name), top-level ports are member arrays. Produced locals are normally
  * eval-local arrays declared at first definition. Scratch can also be hoisted
  * to file-scope static storage, or to the top object for A/B experiments.
  * Expression rendering is delegated to essent.Emitter via Renamer.emitForLane
  * — v2 supplies the lane subscript, never parses names. */
object EmitV2 {

  // Keep the 256 MiB TestHarness AXI backing off the C++ object stack. Small
  // queues/cache arrays remain inline for locality; the access syntax is the
  // same for std::unique_ptr<T[]> and T[N].
  private val HeapMemoryElements = 1 << 20

  /** Compiler-created banks do not exist in the source module hierarchy, so
    * they live as explicit members of the generated top object.  Keep this
    * spelling centralized: the renamer, declaration emitter, and differential
    * manifest must agree exactly. */
  private def registerBankStorageName(name: String): String =
    "_v2_bank_" + name.replace('.', '$')

  /** Lane arrays used to be alignas(64) unconditionally, which pads every
    * UInt<1>[16] (16 real bytes) to a full cache line — with ~260 boolean
    * scratch arrays that wasted ~16KB of the 32KB L1D (measured 4.9% L1D
    * miss rate vs 0.01% scalar). Align to the array's natural size instead,
    * capped at 64: consecutive narrow arrays then pack into shared lines and
    * unaligned AVX loads are free on the target hosts. */
  private def laneAlign(tpe: Type, w: Int): Int = {
    val bits = firrtl.bitWidth(tpe).toInt
    val elemBytes = if (bits <= 8) 1 else if (bits <= 16) 2 else if (bits <= 32) 4
      else 8 * ((bits + 63) / 64)
    val total = elemBytes * w
    if (total >= 64) 64 else if (total >= 32) 32 else 16
  }

  private def envBool(name: String, default: Boolean): Boolean =
    sys.env.get(name).map(_.trim.toLowerCase) match {
      case Some("1" | "true" | "yes" | "on") => true
      case Some("0" | "false" | "no" | "off") => false
      case Some(_) => default
      case None => default
    }

  private var scratchReaders: Map[String, Set[Int]] = Map.empty
  private var loopLocalExcluded: Set[String] = Set.empty
  private var endpointNextNames: Set[String] = Set.empty
  private var endpointNextTids: Set[Int] = Set.empty
  private val smallSelectEligible = mutable.Map[Expression, Boolean]()
  private val smallSelectRegisters = mutable.Set[String]()

  /** Eager evaluation is limited to cheap unsigned expressions. In particular,
    * dynamic memory accesses, division, wide arithmetic and variable shifts
    * must retain their existing conditional evaluation. */
  private def cheapScalarChoice(expr: Expression): Boolean =
    smallSelectEligible.getOrElseUpdate(expr, {
      import firrtl.PrimOps._
      val allowed = Set(And, Or, Xor, Not, Bits, Head, Tail, Pad, Cat, Shl, Shr,
        Add, Addw, Sub, Subw, Eq, Neq, Lt, Leq, Gt, Geq, Andr, Orr)
      var cost = 0
      var muxes = 0
      var safe = true
      def named(e: Expression): Boolean = e match {
        case _: WRef => true
        case f: WSubField => named(f.expr)
        case _ => false
      }
      def visit(e: Expression): Unit = if (safe) {
        safe = e.tpe.isInstanceOf[UIntType] && bitWidth(e.tpe) <= 64
        if (safe) e match {
          case _: WRef | _: UIntLiteral =>
          case f: WSubField if named(f) =>
          case m: Mux => cost += 1; muxes += 1; m.foreachExpr(visit)
          case op: DoPrim if allowed.exists(_ == op.op) => cost += 1; op.foreachExpr(visit)
          case _ => safe = false
        }
        if (cost > 12) safe = false
      }
      visit(expr)
      safe && muxes > 0
    })

  /** Return an address tree, not an eagerly evaluated write-data expression.
    * All leaves have the exact stored type; unsupported conversions and
    * computed values keep their established path. The caller supplies a
    * valid lane even when no earlier write exists. */
  private def forwardingDataPointer(expr: Expression, tpe: Type, lane: String)
      (implicit rn: Renamer, ctx: essent.EmitContext): Option[String] = {
    if (expr.tpe != tpe) return None
    def named(e: Expression): Boolean = e match {
      case _: WRef => true
      case f: WSubField => named(f.expr)
      case _ => false
    }
    def scalarCondition(e: Expression): Boolean = e match {
      case _: WRef | _: UIntLiteral => e.tpe.isInstanceOf[UIntType] && bitWidth(e.tpe) <= 64
      case f: WSubField if named(f) => e.tpe.isInstanceOf[UIntType] && bitWidth(e.tpe) <= 64
      case _ => false
    }
    expr match {
      case e if named(e) => Some(withLaneVar(lane) { s"&(${emitExpr(expr)})" })
      case m: Mux if scalarCondition(m.cond) =>
        for (yes <- forwardingDataPointer(m.tval, tpe, lane);
             no <- forwardingDataPointer(m.fval, tpe, lane)) yield {
          val condition = withLaneVar(lane) { emitExpr(m.cond) }
          s"essent_select_ptr(essent_to_u64($condition) != 0, $yes, $no)"
        }
      case _ => None
    }
  }

  /** Keep private next-state intermediates only at the sweep endpoints when
    * their sole readers are boundary-only commits. RPShift sources, oracle
    * verification, state accesses and externally visible values stay full
    * width. Both endpoints are retained so shared comb helpers remain
    * independent of the forward/reverse direction. */
  private def prepareScratchShapes(res: Result, W: Int, cold: Option[ColdGuard.Spec])
      (implicit rn: Renamer): Unit = {
    endpointNextNames = Set.empty
    endpointNextTids = Set.empty
    val readers = mutable.Map[String, mutable.Set[Int]]()
    for (node <- res.nodes; name <- scratchNodeAccesses(res, node.id)._2)
      readers.getOrElseUpdate(name, mutable.Set.empty) += node.id
    val tiers = cold.toSeq.flatMap(_.tiers)
    val coldTids = res.nodes.iterator.filter(n => tiers.exists(_.touches(n.id))).map(_.id).toSet
    val guardReads = tiers.iterator.flatMap(_.guards.iterator).flatMap(g =>
      g.name.toSeq ++ g.pred.toSeq.flatMap(scratchExprReads)).toSet
    val escaped = res.hostBoundaryInputs ++ res.oracles.map(_.flatName) ++ guardReads
    escaped.foreach(n => readers.getOrElseUpdate(n, mutable.Set.empty) += -1)
    scratchReaders = readers.iterator.map { case (name, ids) => name -> ids.toSet }.toMap
    loopLocalExcluded = escaped ++ coldTids.iterator.flatMap(t => res.nodes(t).produces)
    if (W > 1 && envBool("V2_BOUNDARY_NEXT", default = true)) {
      val fwdVec = res.scheduleFwd.collect { case UVec(t) => t }.toSet
      val revVec = res.scheduleRev.collect { case UVec(t) => t }.toSet
      val possible = res.nodes.iterator.filter { node =>
        node.role == RComb && node.produces.nonEmpty && fwdVec(node.id) && revVec(node.id) &&
          !coldTids(node.id) && (node.stmt.isInstanceOf[DefNode] || node.stmt.isInstanceOf[Connect] ||
            node.stmt.isInstanceOf[essent.ir.LookupTable]) && node.produces.forall { name =>
              rn.nameToMeta.get(name).exists(_.decType == Local) &&
                scratchReaders.get(name).exists(_.nonEmpty)
            }
      }.map(_.id).toSet
      val pending = mutable.Map[Int, Int]()
      val upstream = mutable.Map[Int, mutable.Set[Int]]()
      val ready = mutable.Queue[Int]()
      for (tid <- possible.toSeq.sorted) {
        val waits = mutable.Set[Int]()
        var eligible = true
        for (name <- res.nodes(tid).produces; reader <- scratchReaders(name)) {
          if (reader < 0) eligible = false
          else res.nodes(reader).role match {
            case RRegCommit(r) if res.regs(r).plan != RPOracle && res.regs(r).nextName == name =>
            case RComb if possible(reader) => waits += reader
            case _ => eligible = false
          }
        }
        if (eligible) {
          pending(tid) = waits.size
          if (waits.isEmpty) ready.enqueue(tid)
          waits.foreach(reader => upstream.getOrElseUpdate(reader, mutable.Set.empty) += tid)
        }
      }
      val endpoints = mutable.Set[Int]()
      while (ready.nonEmpty) {
        val tid = ready.dequeue()
        if (endpoints.add(tid)) {
          upstream.getOrElse(tid, mutable.Set.empty).foreach { producer =>
            pending(producer) -= 1
            if (pending(producer) == 0) ready.enqueue(producer)
          }
        }
      }
      endpointNextTids = endpoints.toSet
      endpointNextNames = endpointNextTids.iterator.flatMap(t => res.nodes(t).produces).toSet
    }
    rn.setEndpointLanes(endpointNextNames)
    if (endpointNextNames.nonEmpty)
      println(s"[v2] boundary-only next-state cones: ${endpointNextNames.size} arrays x $W -> 2 lanes")
  }

  /** A multiply-used expression can stay in a register when every use lies
    * in the same fused loop; duplicating its expression is unnecessary. */
  private def loopScalarBindings(res: Result, tids: Seq[Int])
      (implicit rn: Renamer): Map[String, String] = {
    if (!envBool("V2_LOOP_LOCALS", default = true) || u1PackEnabled) return Map.empty
    val group = tids.toSet
    tids.iterator.flatMap { tid =>
      val node = res.nodes(tid)
      if (node.role != RComb || !(node.stmt.isInstanceOf[DefNode] ||
          node.stmt.isInstanceOf[Connect] || node.stmt.isInstanceOf[essent.ir.LookupTable])) Iterator.empty
      else node.produces.toSeq.sorted.iterator.zipWithIndex.collect {
        case (name, index) if !loopLocalExcluded(name) && !condHoldWdataAliases.contains(name) &&
            rn.nameToMeta.get(name).exists(_.decType == Local) &&
            scratchReaders.get(name).exists(uses => uses.nonEmpty && !uses(tid) && uses.subsetOf(group)) =>
          name -> s"_v2_local_${tid}_$index"
      }
    }.toMap
  }

  /** Choose between a depth-indexed last-writer table and replaying only the
    * writes that can exist inside one SIMD window.
    *
    * The old fixed `depth <= 4096` rule cleared a 128/512/2048-entry `int`
    * table even at W=4 with one write port, where there are only six possible
    * preceding-lane/write-port comparisons.  Conversely, at W=32 the bounded
    * replay can already contain hundreds of comparisons and a direct table is
    * normally preferable.  This cost proxy therefore scales with both W and
    * the exact write-port count instead of classifying the hardware memory by
    * depth alone.
    *
    * V2_STATE_LAST_WRITER_DENSE_FACTOR is an A/B escape hatch.  Zero forces
    * bounded replay; larger values retain the direct table for progressively
    * deeper arrays.  Four is deliberately conservative about the extra
    * branches and address expressions in replay while eliminating the clear
    * cliff observed on complete-Small BOOM.  A Clang 19 full-chip scan of
    * factors 1/2/4/8 selected two: one overuses bounded replay for the many
    * depth-eight queues, while four and eight retain unnecessary depth-sized
    * clears.
    */
  private def preferDenseLastWriter(depth: Int, W: Int, writePorts: Int): Boolean = {
    val factor = sys.env.get("V2_STATE_LAST_WRITER_DENSE_FACTOR")
      .flatMap(_.trim.toIntOption).filter(_ >= 0).getOrElse(2)
    if (W <= 1 || writePorts <= 0 || factor == 0) false
    else {
      val precedingComparisons = W.toLong * (W - 1L) / 2L * writePorts.toLong
      depth.toLong <= precedingComparisons * factor.toLong
    }
  }

  /** Host-code shape for bounded sparse state forwarding.
    *
    * FIRRTL expressions are pure, so evaluating a write-data expression when
    * its write is disabled does not change RTL semantics.  For narrow POD
    * UInt/SInt values, `essent_mux` lowers the chronological overwrite to a
    * mask blend instead of one difficult host branch per possible preceding
    * write.  Wide values deliberately retain the branch: their mux helper
    * must copy multiple words and is itself branch based, so eagerly copying
    * them would add work without removing control flow.
    *
    * Complete-Small BOOM qualification (Clang 19, W=4) replaced 474 sparse
    * read sites, reduced dynamic branches by about 6.3% and branch misses by
    * about 27%, and improved paired throughput by 1.097x across nine
    * interleaved samples.  A transformed W=1 build then matched independent
    * Verilator for 50,000 cycles / 96,201,920 comparisons.  Keep an env
    * opt-out for bisecting; persistent state commits retain conditional
    * stores and wide values retain their established branching form.
    */
  private def narrowPodStateValues(tpes: Seq[Type]): Boolean =
    tpes.nonEmpty && tpes.forall {
      case UIntType(IntWidth(width)) => width <= 64
      case SIntType(IntWidth(width)) => width <= 64
      case _ => false
    }

  private def branchlessSparseStateRead(tpes: Seq[Type]): Boolean =
    narrowPodStateValues(tpes) &&
      envBool("V2_STATE_SPARSE_BRANCHLESS", default = true)

  /** Dense-table counterpart to sparse branch-free forwarding.
    * A disabled write is redirected to one extra local sentinel slot, so it
    * cannot alter the hardware-addressed portion of the last-writer table.
    * The table is local scratch rather than architectural state; the extra
    * slot therefore changes neither the state ABI nor the persistent array.
    *
    * Complete-Small BOOM (Clang 19, W=4) replaced 520 dense read sites across
    * both directions.  Nine interleaved samples improved by a paired median
    * 1.101x; dynamic branch misses fell about 29% even though retired
    * instructions rose about 1.1%.  Keep an opt-out for bisecting. */
  private def branchlessDenseLastWriter(tpes: Seq[Type]): Boolean =
    narrowPodStateValues(tpes) &&
      envBool("V2_STATE_DENSE_BRANCHLESS", default = true)

  /** FIRRTL permits a memory address type whose value space is larger than
    * a non-power-of-two memory depth.  Such accesses have unspecified RTL
    * data, but indexing the generated C++ array with them is undefined
    * behaviour.  Select a deterministic zero for those reads; this remains a
    * legal value of the RTL don't-care while keeping the host execution
    * memory-safe. */
  private def stateAddressCanEscape(depth: Int): Boolean =
    depth > 0 && (depth & (depth - 1)) != 0

  private def stateReadExpr(
      array: String, tpe: Type, address: String, depth: Int): String =
    if (!stateAddressCanEscape(depth)) s"$array[$address]"
    else s"(($address) < (uint64_t)$depth ? $array[$address] : " +
      s"${genCppType(tpe)}(0))"

  private def lastWriterReadExpr(
      table: String, address: String, depth: Int): String =
    if (!stateAddressCanEscape(depth)) s"$table[$address]"
    else s"(($address) < (uint64_t)$depth ? $table[$address] : -1)"

  /** Adjacent full-width state commits have already been proven mutually
    * independent by the scheduler: they target distinct persistent arrays
    * and all of their write data has been computed before this schedule run.
    * Sharing one chronological lane loop therefore only interleaves stores to
    * distinct objects; it does not change any array's lane order, write-port
    * priority, enable, mask, or address.  Complete-Small BOOM currently has
    * 504 such schedule runs but 700 separately emitted lane loops across the
    * two directions, so retaining one loop per run removes pure host control
    * duplication.  Keep an opt-out until the full-chip qualification is
    * archived alongside the earlier state-access transformations. */
  private def fuseStateCommitRuns: Boolean =
    envBool("V2_STATE_COMMIT_RUN_FUSION", default = true)

  /** Maximum comb statements fused into one lane loop (0 = unlimited).
    * See the CComb case in emitRunGroup for the measured rationale. */
  private def combLoopCap: Int =
    sys.env.get("V2_COMB_LOOP_CAP").map(_.trim).filter(_.nonEmpty)
      .map(_.toInt).getOrElse(6)

  /** Window-level any-write guard for state reads (V2_STATE_READ_ANY_GUARD,
    * default on): when no write enable of the array fires anywhere in the
    * SIMD window, every lane's read equals the persistent pre-window image,
    * so the last-writer table / forwarding scan / local image copy can be
    * skipped outright. Mirrors the established state-commit any-guard.
    * Arrays with a bulk zero reset keep the full path unconditionally. */
  private def stateReadAnyGuard: Boolean =
    envBool("V2_STATE_READ_ANY_GUARD", default = true)

  /** SEMANTICS-BREAKING probe (never default, never gate it as correct):
    * arrays whose flat name contains one of these comma-separated substrings
    * get their reads stubbed to zero and their read machinery skipped. The
    * zero-data bench delta against the champion is the cost CEILING of the
    * read-port externalization direction (injected reads + write-stream
    * verification would delete the same machinery); it decides whether the
    * full manifest/capture/consumer plumbing is worth building. */
  private def externProbeFamilies: Seq[String] =
    sys.env.get("V2_EXTERN_PROBE_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty)
  private def externProbe(array: String): Boolean =
    externProbeFamilies.exists(array.contains)

  /** Extern read ports (V2_EXTERN_READ_FAMILIES): a state read renamed to
    * '<name>$rtl' by the pipeline exists only as the Micro-Lockstep recompute
    * for its injected stream. Fence its machinery behind ESSENT_ORACLE_VERIFY
    * so the perf build deletes the whole read path at preprocessing time. */
  private def externReadFence(name: String, body: Seq[String]): Seq[String] =
    if (!name.endsWith("$rtl")) body
    else (s"#if ESSENT_ORACLE_VERIFY // [extern-read] verify-only recompute: $name" +: body) :+ "#endif"

  /** True when every read of the array is an externalized stream. The perf
    * build then has no reader of the persistent image (all read paths are
    * fenced), so its commits are verify-only as well: the verify build still
    * maintains the image for the '$rtl' recomputes and the state audits. */
  private def externAllReads(res: Result, array: String): Boolean = {
    val info = res.stateArrays(array)
    info.fullyExternal || (info.readIds.nonEmpty &&
      info.readIds.forall(t => res.nodes(t).produces.exists(_.endsWith("$rtl"))))
  }

  /** Cross-direction shared comb outlining (V2_SHARED_COMB_OUTLINE, default
    * on). The forward and reverse bodies emit byte-identical comb lane loops
    * — comb statements are lane-local and always iterate L ascending — so
    * each emitted comb group becomes one member function called from both
    * bodies instead of being duplicated. Measured on the champion build:
    * 3,085 identical comb blocks per direction (14.5MB of duplicated
    * source); the real-data profile shows ~6MB/window instruction streaming
    * as the current wall, and this halves the comb share of it. */
  private var capturingSharedEval = false
  private def sharedCombOutline: Boolean =
    !capturingSharedEval && envBool("V2_SHARED_COMB_OUTLINE", default = true)
  /** Only groups whose rendered body reaches this many characters are shared;
    * smaller groups stay inline. Outlining every group measured -13..-17%:
    * thousands of noinline boundaries broke cross-group register reuse and
    * redundant-load elimination, costing far more than the fetch savings
    * (text -18%) — instruction streaming was already prefetch-hidden. */
  private def sharedCombMinChars: Int =
    sys.env.get("V2_SHARED_COMB_MIN_CHARS").map(_.trim).filter(_.nonEmpty)
      .map(_.toInt).getOrElse(20000)
  private def sharedCombBodySize(body: String): Int =
    body.length - body.linesIterator.filter(_.trim.startsWith("// [v2 lane-local]"))
      .map(_.length + 1).sum
  private val sharedCombFns = mutable.LinkedHashMap[String, (Int, String)]()

  // ---- u1 bit-sliced comb segments (V2_U1_PACK, experimental) --------------
  // W lanes of a 1-bit signal are packed into one W-bit mask; a consecutive
  // run of pure-u1 statements (and/or/xor/not/mux/eq/neq over u1) then costs
  // one scalar bitwise op per statement for all lanes. Pack/unpack happen only
  // at segment boundaries; every produced signal is unpacked back to its lane
  // array so downstream consumers (later comb, commits, verify) are unchanged.
  // Bits above lane W-1 of a mask may hold garbage; unpack and all mask ops
  // are insensitive to them.
  private def u1PackEnabled: Boolean = envBool("V2_U1_PACK", default = false)
  private def u1PackMinChain: Int =
    sys.env.get("V2_U1_PACK_MIN").map(_.trim).filter(_.nonEmpty)
      .map(_.toInt).getOrElse(4)

  private def u1Type(tpe: firrtl.ir.Type): Boolean = tpe match {
    case firrtl.ir.UIntType(firrtl.ir.IntWidth(w)) => w == 1
    case _ => false
  }

  private def exprWidth(e: firrtl.ir.Expression): Option[BigInt] = e.tpe match {
    case firrtl.ir.UIntType(firrtl.ir.IntWidth(w)) => Some(w)
    case _ => None
  }

  private def refLike(e: firrtl.ir.Expression): Boolean = e match {
    case _: firrtl.ir.UIntLiteral | _: firrtl.ir.Mux | _: firrtl.ir.DoPrim => false
    case _ => true
  }

  /** A lane-wise equality of two narrow reference operands (or reference vs
    * literal): the vector compare's k-mask output IS the packed form, so this
    * is a free entry point into a bit-sliced segment. */
  private def u1CmpLeaf(e: firrtl.ir.Expression): Boolean = e match {
    case p: firrtl.ir.DoPrim =>
      import firrtl.PrimOps._
      (p.op == Eq || p.op == Neq) && u1Type(p.tpe) && p.args.size == 2 && {
        val widths = p.args.map(exprWidth)
        widths.forall(w => w.exists(x => x >= 1 && x <= 64)) &&
          widths.exists(_.exists(_ > 1)) && // both-u1 compares stay mask ops
          exprWidth(p.args(0)) == exprWidth(p.args(1)) && (p.args match {
            case Seq(a, b) =>
              (refLike(a) && refLike(b)) ||
                (refLike(a) && b.isInstanceOf[firrtl.ir.UIntLiteral]) ||
                (a.isInstanceOf[firrtl.ir.UIntLiteral] && refLike(b))
            case _ => false
          })
      }
    case _ => false
  }

  private def u1PureExpr(e: firrtl.ir.Expression): Boolean =
    if (u1CmpLeaf(e)) true
    else e match {
      case u: firrtl.ir.UIntLiteral => u1Type(u.tpe)
      case m: firrtl.ir.Mux =>
        u1Type(m.tpe) && u1PureExpr(m.cond) && u1PureExpr(m.tval) && u1PureExpr(m.fval)
      case p: firrtl.ir.DoPrim =>
        import firrtl.PrimOps._
        u1Type(p.tpe) && (p.op match {
          case And | Or | Xor => p.args.forall(u1PureExpr)
          case Eq | Neq => p.args.forall(u1PureExpr)
          case Not | AsUInt | Pad => p.args.size == 1 && u1PureExpr(p.args.head)
          case _ => false
        })
      // reference-like leaf: accepted when 1-bit; the emission phase further
      // requires it to render as a lane array (rejects dynamic accesses etc.)
      case other => u1Type(other.tpe)
    }

  /** (serializeKey, flat lvalue name, expression) for a packable statement. */
  private def u1PackTarget(stmt: firrtl.ir.Statement)
      : Option[(String, String, firrtl.ir.Expression)] = stmt match {
    case d: firrtl.ir.DefNode
        if !condHoldWdataAliases.contains(d.name) && !endpointNextNames(d.name) &&
          u1Type(d.value.tpe) && u1PureExpr(d.value) =>
      Some((d.name, d.name, d.value))
    case c: firrtl.ir.Connect if !endpointNextNames(emitExprRaw(c.loc)) &&
        u1Type(c.loc.tpe) && u1PureExpr(c.expr) =>
      Some((c.loc.serialize, emitExprRaw(c.loc), c.expr))
    case _ => None
  }

  private def u1Leaves(e: firrtl.ir.Expression,
      refs: mutable.LinkedHashMap[String, firrtl.ir.Expression],
      cmps: mutable.LinkedHashMap[String, firrtl.ir.DoPrim]): Unit =
    if (u1CmpLeaf(e)) {
      val p = e.asInstanceOf[firrtl.ir.DoPrim]
      val k = p.serialize
      if (!cmps.contains(k)) cmps(k) = p
    } else e match {
      case _: firrtl.ir.UIntLiteral => ()
      case m: firrtl.ir.Mux =>
        u1Leaves(m.cond, refs, cmps); u1Leaves(m.tval, refs, cmps)
        u1Leaves(m.fval, refs, cmps)
      case p: firrtl.ir.DoPrim => p.args.foreach(u1Leaves(_, refs, cmps))
      case r =>
        val k = r.serialize
        if (!refs.contains(k)) refs(k) = r
    }

  private def u1MaskExpr(e: firrtl.ir.Expression, local: String => Option[String],
      mt: String): Option[String] = if (u1CmpLeaf(e)) local(e.serialize) else e match {
    case u: firrtl.ir.UIntLiteral =>
      Some(if (u.value == 0) s"($mt)0" else s"($mt)~($mt)0")
    case m: firrtl.ir.Mux =>
      for {
        c <- u1MaskExpr(m.cond, local, mt)
        t <- u1MaskExpr(m.tval, local, mt)
        f <- u1MaskExpr(m.fval, local, mt)
      } yield s"(($c & $t) | (~$c & $f))"
    case p: firrtl.ir.DoPrim =>
      import firrtl.PrimOps._
      def bin(sep: String, wrap: String => String = identity): Option[String] =
        for {
          a <- u1MaskExpr(p.args(0), local, mt)
          b <- u1MaskExpr(p.args(1), local, mt)
        } yield wrap(s"($a $sep $b)")
      p.op match {
        case And => bin("&")
        case Or => bin("|")
        case Xor => bin("^")
        case Neq => bin("^")
        case Eq => bin("^", inner => s"(~$inner)")
        case Not => u1MaskExpr(p.args.head, local, mt).map(a => s"(~$a)")
        case AsUInt | Pad => u1MaskExpr(p.args.head, local, mt)
        case _ => None
      }
    case r => local(r.serialize)
  }

  /** Render one packed segment, or None when any operand/target does not
    * render as a plain lane array (the caller then falls back to the normal
    * lane-loop emission for these statements). */
  private def u1PackedSegmentStr(res: Result, W: Int, tids: Seq[Int])
      (implicit rn: Renamer, ctx: essent.EmitContext): Option[Seq[String]] = {
    val mt = if (W <= 8) "uint8_t" else if (W <= 16) "uint16_t"
      else if (W <= 32) "uint32_t" else "uint64_t"
    val targets = tids.map(t => u1PackTarget(res.nodes(t).stmt))
    if (targets.exists(_.isEmpty)) return None
    val flat = targets.map(_.get)
    if (flat.map(_._1).distinct.size != flat.size) return None // repeated target
    def render0(expr: firrtl.ir.Expression): Option[String] = {
      val s = withLaneVar("0") { emitExpr(expr) }
      if (s.endsWith("[0]")) Some(s) else None
    }
    def lvalue0(name: String): Option[String] = {
      val s = rn.emitForLane(name, "0")
      if (s.endsWith("[0]")) Some(s) else None
    }
    val produced = mutable.LinkedHashMap[String, String]()
    val inputs = mutable.LinkedHashMap[String, (String, firrtl.ir.Expression)]()
    val cmpIns = mutable.LinkedHashMap[String, (String, firrtl.ir.DoPrim)]()
    for ((key, _, e) <- flat) {
      val refs = mutable.LinkedHashMap[String, firrtl.ir.Expression]()
      val cmps = mutable.LinkedHashMap[String, firrtl.ir.DoPrim]()
      u1Leaves(e, refs, cmps)
      for ((k, repr) <- refs)
        if (!produced.contains(k) && !inputs.contains(k))
          inputs(k) = (s"_v2_pki_${inputs.size}", repr)
      for ((k, p) <- cmps)
        if (!cmpIns.contains(k)) cmpIns(k) = (s"_v2_pkc_${cmpIns.size}", p)
      produced(key) = s"_v2_pk_${produced.size}"
    }
    def scalarTy(width: BigInt): String =
      if (width <= 8) "uint8_t" else if (width <= 16) "uint16_t"
      else if (width <= 32) "uint32_t" else "uint64_t"
    def cmpBase(e: firrtl.ir.Expression, sty: String): Option[String] =
      render0(e).map(base => s"reinterpret_cast<const $sty*>(&$base)")
    val packLines = inputs.toSeq.map { case (_, (loc, repr)) =>
      render0(repr) match {
        case Some(base) => s"  const $mt $loc = ($mt)essent_pack_u1<$W>(&$base);"
        case None => return None
      }
    } ++ cmpIns.toSeq.map { case (_, (loc, p)) =>
      import firrtl.PrimOps._
      val width = exprWidth(p.args.head).getOrElse(return None)
      val sty = scalarTy(width)
      val call = p.args match {
        case Seq(a, lit: firrtl.ir.UIntLiteral) =>
          cmpBase(a, sty).map(b =>
            s"essent_pack_cmp_eq_k<$W, $sty>($b, 0x${lit.value.toString(16)}ULL)")
        case Seq(lit: firrtl.ir.UIntLiteral, b) =>
          cmpBase(b, sty).map(bb =>
            s"essent_pack_cmp_eq_k<$W, $sty>($bb, 0x${lit.value.toString(16)}ULL)")
        case Seq(a, b) =>
          for { ba <- cmpBase(a, sty); bb <- cmpBase(b, sty) }
            yield s"essent_pack_cmp_eq<$W, $sty>($ba, $bb)"
        case _ => None
      }
      call match {
        case Some(c) =>
          val body = if (p.op == Neq) s"($mt)~($mt)$c" else s"($mt)$c"
          s"  const $mt $loc = $body;"
        case None => return None
      }
    }
    val lookup = (k: String) => produced.get(k)
      .orElse(inputs.get(k).map(_._1)).orElse(cmpIns.get(k).map(_._1))
    val stmtLines = flat.map { case (key, _, e) =>
      u1MaskExpr(e, lookup, mt) match {
        case Some(rhs) => s"  const $mt ${produced(key)} = ($mt)$rhs;"
        case None => return None
      }
    }
    val unpackLines = flat.map { case (key, name, _) =>
      lvalue0(name) match {
        case Some(base) => s"  essent_unpack_u1<$W>(&$base, ${produced(key)});"
        case None => return None
      }
    }
    Some(Seq(s"// [vec comb-packed] ${tids.size} templates x $W lanes (u1 bit-sliced)",
      "{") ++ packLines ++ stmtLines ++ unpackLines ++ Seq("}"))
  }

  /** Skip one persistent-state commit lane loop when none of its write
    * conditions is true anywhere in the SIMD window.  The reduction only
    * reads already-computed write enables/masks; the original chronological
    * lane/port loop remains unchanged on the active path.  Complete-Small
    * BOOM W=4 emits 228 such loops across both directions, covering 529
    * arrays but only 374 distinct write conditions per direction after
    * same-access fields are collapsed.  A 60k x 9 interleaved Clang 19 A/B
    * improved the monitor-free generated consumer by 1.0231x geometrically
    * without injection and 1.0336x with injection (8/9 wins in both). */
  private def guardEmptyStateCommitWindows: Boolean =
    envBool("V2_STATE_COMMIT_ANY_GUARD", default = true)

  /** Eager, branch-free match predicate.  Bitwise `&` is intentional: unlike
    * C++ `&&`, it has no short-circuit control-flow contract for Clang to
    * preserve before inlining the small UInt accessors. */
  private def sparseMatchExpr(enable: String, mask: String, address: String,
      readAddress: String): String =
    s"UInt<1>((uint64_t)((uint64_t)(essent_to_u64($enable) != 0) & " +
      s"(uint64_t)(essent_to_u64($mask) != 0) & " +
      s"(uint64_t)(essent_to_u64($address) == $readAddress)))"

  /** Storage tier of a packed oracle stream. SInt streams are forced to the
    * u64 tier: the trace generator serializes SInt values sign-extended to 64
    * bits, which both overflows a narrow tier's range check and is exactly
    * what SInt<w>(uint64) reconstruction expects. */
  private def specElemBytes(res: Result, o: OracleSpec): Int = {
    val isSigned = (if (o.isRegister) res.regs.get(o.flatName).map(_.tpe)
                    else res.combCuts.get(o.flatName))
      .exists(_.isInstanceOf[firrtl.ir.SIntType])
    if (isSigned) 8
    else if (o.widthBits <= 8) 1 else if (o.widthBits <= 16) 2
    else if (o.widthBits <= 32) 4 else 8
  }

  // Oracle data format v4 (window-major): the packed file stores one
  // contiguous block per 2W-cycle super-window holding every stream's 2W
  // values, instead of one contiguous region per stream over all cycles.
  // Injection for a window then reads ONE sequential block (hardware
  // prefetch + page locality) instead of touching ~one scattered cache line
  // per stream, and every call site addresses `oracle_win_base + <constant>`
  // instead of loading a per-stream global pointer. Layout is decided here
  // (descending elemBytes keeps every slot naturally aligned), baked into
  // the emitted call sites, and published via oracle_manifest.json
  // (blockOffset per stream, blockBytes global) for the packer to follow.
  private var v4Off: Map[String, Long] = Map.empty
  private var v4Elem: Map[String, Int] = Map.empty
  private var v4BlockBytes: Long = 0L

  private def computeV4Layout(res: Result, W: Int): Unit = {
    // Within each elemBytes tier (tier order preserves natural alignment with
    // zero padding), place streams in kernel first-access order — the position
    // of the oracle's defining template in scheduleFwd — so a window's
    // injection sweep walks its block quasi-monotonically instead of jumping
    // by arraySymbol's alphabetical accident. V2_V4_LAYOUT_ALPHA=1 restores
    // the old alphabetical order for A/B bisection.
    val alphaLayout = sys.env.get("V2_V4_LAYOUT_ALPHA").exists(v => v == "1" || v == "true")
    val schedPos: Map[Int, Int] = {
      val m = mutable.HashMap[Int, Int]()
      for ((u, i) <- res.scheduleFwd.zipWithIndex) if (!m.contains(u.tid)) m(u.tid) = i
      m.toMap
    }
    def firstUse(o: OracleSpec): Int =
      if (alphaLayout) 0
      else res.producesIdx.get(o.flatName).flatMap(schedPos.get).getOrElse(Int.MaxValue)
    // V2_V4_LAYOUT_HOT_FILE=path: "flatName count" lines (change entries per
    // stream over a profiling run, see SYSMODEL_DECODE_LANE_HIST). Streams
    // are placed hottest first, so the decoder's element writes for a window
    // land in a compact region (BOOM dhrystone: 90% of the entries hit 340
    // of 2,086 streams) instead of touching one cold line per stream. Every
    // slot is 2W*elemBytes bytes, a multiple of 8, so mixing element sizes
    // keeps natural alignment; unlisted streams keep the tiered order.
    val hotCount: Map[String, Long] = sys.env.get("V2_V4_LAYOUT_HOT_FILE").map { path =>
      val src = scala.io.Source.fromFile(path)
      try src.getLines().flatMap { line =>
        line.trim.split("\\s+") match {
          case Array(name, count) if count.forall(_.isDigit) => Some(name -> count.toLong)
          case _ => None
        }
      }.toMap finally src.close()
    }.getOrElse(Map.empty)
    if (hotCount.nonEmpty) {
      val hit = res.oracles.count(o => hotCount.getOrElse(o.flatName, 0L) > 0L)
      println(s"[v2] v4 layout: activity order from ${sys.env("V2_V4_LAYOUT_HOT_FILE")} " +
        s"($hit of ${res.oracles.size} streams active)")
    }
    val order = res.oracles.sortBy(o =>
      (-hotCount.getOrElse(o.flatName, 0L), -specElemBytes(res, o), firstUse(o), o.arraySymbol))
    var off = 0L
    val offs = mutable.LinkedHashMap[String, Long]()
    val elems = mutable.LinkedHashMap[String, Int]()
    for (o <- order) {
      val eb = specElemBytes(res, o)
      offs(o.arraySymbol) = off
      elems(o.arraySymbol) = eb
      off += 2L * W * eb
    }
    v4Off = offs.toMap
    v4Elem = elems.toMap
    v4BlockBytes = (off + 63L) & ~63L
  }

  /** Typed stream-slot expression for the current super-window: constant
    * offset off the single window base pointer. The trailing comment is
    * load-bearing — packers validate emitted (offset, stream) pairs against
    * the manifest through it. */
  private def v4StreamExpr(sym: String): String =
    s"((const uint${v4Elem(sym) * 8}_t*)(oracle_win_base + ${v4Off(sym)}L) /* $sym */)"

  def run(circuit: Circuit, opt: OptFlags,
      annotations: Seq[firrtl.annotations.Annotation] = Seq.empty): Unit = {
    val W = opt.vectorWidth
    require(W >= 1, s"[v2] --width must be >= 1, got $W")  // W=1: scalar control experiment
    boundaryVerify = new BoundaryVerifyRegistry
    require(!(opt.simdV2MemberScratch && opt.simdV2StaticScratch),
      "[v2] choose at most one of --simd-v2-member-scratch and --simd-v2-static-scratch")
    require(opt.simdV2OracleLimit >= -1,
      s"[v2] --simd-v2-oracle-limit must be >= -1, got ${opt.simdV2OracleLimit}")
    val topName = circuit.main

    val stateArrayAnnotations = annotations.collect {
      case a: StateArrayStorageAnnotation => a
    }
    val indexedCounterBankAnnotations = annotations.collect {
      case a: IndexedCounterBankStorageAnnotation => a
    }
    val res = V2Pipeline.build(circuit, W,
      wantVerify = !opt.simdV2NoVerify,
      freezePrefixes = opt.oracleFreeze,
      oracleAll = opt.simdV2OracleAll,
      oracleLimit = opt.simdV2OracleLimit,
      fuseCap = opt.simdV2FuseCap,
      stateArrayAnnotations = stateArrayAnnotations,
      indexedCounterBankAnnotations = indexedCounterBankAnnotations,
      // RepCut's Verilator performance build compiles the source-level
      // printf/stop monitors out with PRINTF_COND=0/STOP_COND=0.  Offer the
      // same release configuration without weakening CHISA's own per-oracle
      // Micro-Lockstep checks.  Keep it opt-in until the full-chip A/B below
      // has established both the contract change and runtime benefit.
      keepSourceEffects = !envBool("V2_DISABLE_SOURCE_EFFECTS", default = false))

    // ColdGuard roots every operand consumed by chronological state reads and
    // commits.  The state kernels themselves remain on the exact full image;
    // only their ordinary comb input cones may be quiet-specialized.
    val coldSpec = ColdGuard.build(res)

    computeV4Layout(res, W)

    val outputDir = if (opt.outputDir().nonEmpty) opt.outputDir() else System.getProperty("user.dir")
    writeManifest(res, new File(outputDir, "oracle_manifest.json"))
    writeOracleAudit(res, W, new File(outputDir, "oracle_audit.json"))
    writeSerialRegionAudit(res, W, new File(outputDir, "serial_region_audit.json"))
    writeStateArrayManifest(res, W, new File(outputDir, "state_array_manifest.json"))
    writeDeadStateManifest(res, new File(outputDir, "dead_state_manifest.json"))
    writeClockDomainManifest(res.clockDomains,
      new File(outputDir, "clock_domain_manifest.json"))
    writeExtModuleManifest(circuit, W, new File(outputDir, "extmodule_manifest.json"))
    writeExtModuleFields(circuit, new File(outputDir, "extmodule_fields.inc"))
    writeRegOracleInc(res, new File(outputDir, "reg_oracle_fields.inc"))
    writeRegisterBankManifest(res, new File(outputDir, "register_bank_manifest.json"))
    writeCombProbeFiles(res, new File(outputDir, "probe_signals_v2.json"),
      new File(outputDir, "probe_fields_v2.inc"))

    val w: Writer = new FileWriter(new File(outputDir, s"$topName.h"))
    try emitHeader(circuit, res, W, topName, opt.simdV2FuseCap,
      opt.simdV2MemberScratch, opt.simdV2StaticScratch, opt.simdV2MergeEval, coldSpec, w)
    finally w.close()
    println(s"[v2] wrote $outputDir/$topName.h")
  }

  // ------------------------------------------------------------------
  // Renamer setup: single namespace, arrays everywhere except scalar reset.
  // ------------------------------------------------------------------
  private def buildRenamer(circuit: Circuit, res: Result, W: Int,
      hoistScratch: Boolean): Renamer = {
    val rn = new Renamer
    rn.vectorWidth = W
    val extIO = findExternalPorts(circuit)

    def isScalarPort(name: String, tpe: Type): Boolean =
      tpe == ClockType || name == "reset"

    for ((name, tpe) <- extIO if tpe != ClockType) {
      rn.nameToEmitName(name) = name
      rn.nameToMeta(name) = SigMeta(ExtIO, tpe)
      if (!isScalarPort(name, tpe)) {
        rn.nameToSimdInfo(name) = (name, 0)
        rn.addStructMemberBase(name)
      }
    }
    val registerBankNames = res.registerBanks.iterator.map(_.name).toSet
    for ((rName, ri) <- res.regs) {
      val emitName = if (registerBankNames(rName)) registerBankStorageName(rName) else rName
      rn.nameToEmitName(rName) = emitName
      rn.nameToMeta(rName) = SigMeta(RegSet, ri.tpe)
      rn.nameToSimdInfo(rName) = (emitName, 0)
      rn.addStructMemberBase(emitName)
    }
    for (n <- res.nodes; name <- n.produces if !rn.nameToMeta.contains(name)) {
      val tpe = n.stmt match {
        case d: DefNode => d.value.tpe
        case c: Connect => c.loc.tpe
        case lt: essent.ir.LookupTable => lt.resultType
        case _ =>
          res.regs.get(name).map(_.tpe)
            .orElse(res.combCuts.get(name))   // comb cut injection template
            .getOrElse(throw new IllegalStateException(s"[v2] no type for produced name '$name'"))
      }
      val emitName = rn.removeDots(name)
      val simdBase = s"_s_$emitName"
      rn.nameToEmitName(name) = emitName
      rn.nameToMeta(name) = SigMeta(Local, tpe)
      rn.nameToSimdInfo(name) = (simdBase, 0)
      if (hoistScratch) rn.addStructMemberBase(simdBase)
    }
    rn
  }

  // ------------------------------------------------------------------
  // Struct declarations (nested modules; member path == flat name).
  // ------------------------------------------------------------------
  /** A C++ module struct is shared by every instance of that FIRRTL module.
    * Remove a memory member only when every instance of that exact module
    * memory is fully externalized; a mixed instance set fails closed instead
    * of silently deleting storage from an ordinary instance. */
  private def fullyExternalMemoryMembers(
      circuit: Circuit, res: Result): Map[String, Set[String]] = {
    val requested = res.stateArrays.valuesIterator
      .filter(_.fullyExternal).map(_.name).toSet
    if (requested.isEmpty) return Map.empty

    val prefixesByModule = findAllModuleInstances(circuit)
      .groupBy(_._1).view.mapValues(_.map(_._2)).toMap
    val omitted = mutable.LinkedHashMap[String, mutable.LinkedHashSet[String]]()
    val covered = mutable.LinkedHashSet[String]()
    for (module <- circuit.modules.collect { case m: Module => m };
         memory <- findInstancesOf[DefMemory](module.body)) {
      val paths = prefixesByModule.getOrElse(module.name, Seq.empty)
        .map(_ + memory.name)
      val selected = paths.filter(requested)
      if (selected.nonEmpty) {
        require(selected.size == paths.size,
          s"[v2-extern-array] cannot remove shared C++ member " +
            s"'${module.name}.${memory.name}': only ${selected.size}/${paths.size} " +
            "FIRRTL instances are fully external")
        omitted.getOrElseUpdate(module.name, mutable.LinkedHashSet()) += memory.name
        covered ++= selected
      }
    }
    val unresolved = requested -- covered
    require(unresolved.isEmpty,
      s"[v2-extern-array] fully external array(s) do not map to FIRRTL memory members: " +
        unresolved.take(8).mkString(", "))
    omitted.iterator.map { case (module, names) => module -> names.toSet }.toMap
  }

  private def emitStructs(circuit: Circuit, res: Result, W: Int,
      omittedMemories: Map[String, Set[String]], w: Writer): Unit = {
    val topName = circuit.main
    for (m <- circuit.modules) m match {
      case mod: Module if mod.name != topName =>
        emitModuleStruct(mod, W, w, isTop = false, circuit,
          omittedMemoryNames = omittedMemories.getOrElse(mod.name, Set.empty))
      case _: Module =>
      case em: ExtModule => emitExtModuleStruct(em, W, w)
    }
  }

  /** ExtModules are explicit host boundaries. Their non-clock ports carry one
    * value per virtual cycle, just like top-level ports; an adapter (dtm_t,
    * plusarg setup, etc.) fills output lanes and consumes input lanes. Keeping
    * them as structs is the same representation used by the scalar backend,
    * but v2 makes the time dimension explicit instead of silently dropping
    * the blackbox. */
  private def emitExtModuleStruct(m: ExtModule, W: Int, w: Writer): Unit = {
    val ports = m.ports.filter(_.tpe != ClockType)
    w.writeLines(0, "")
    w.writeLines(0, s"typedef struct ${m.name} {")
    for (p <- ports)
      w.writeLines(1, s"alignas(${laneAlign(p.tpe, W)}) ${genCppType(p.tpe)} ${p.name}[$W];")
    w.writeLines(0, "")
    w.writeLines(1, "void rand_init() {")
    for (p <- ports)
      w.writeLines(2, s"for (int _i = 0; _i < $W; _i++) ${p.name}[_i].rand_init();")
    w.writeLines(1, "}")
    w.writeLines(0, s"} ${m.name};")
  }

  private def emitModuleStruct(m: Module, W: Int, w: Writer, isTop: Boolean,
      circuit: Circuit, registerBanks: Seq[RegisterBankInfo] = Seq.empty,
      omittedMemoryNames: Set[String] = Set.empty): Unit = {
    val registers = findInstancesOf[DefRegister](m.body)
    val memories = findInstancesOf[DefMemory](m.body)
      .filterNot(memory => omittedMemoryNames(memory.name))
    val children = findModuleInstances(m.body)
    w.writeLines(0, "")
    w.writeLines(0, s"typedef struct ${m.name} {")
    for (r <- registers)
      w.writeLines(1, s"alignas(${laneAlign(r.tpe, W)}) ${genCppType(r.tpe)} ${r.name}[$W];")
    for (mem <- memories) {
      require(mem.depth.isValidInt, s"[v2-state-array] memory '${mem.name}' depth is too large")
      val depth = mem.depth.toInt
      if (depth >= HeapMemoryElements)
        w.writeLines(1, s"std::unique_ptr<${genCppType(mem.dataType)}[]> ${mem.name} = " +
          s"std::make_unique<${genCppType(mem.dataType)}[]>($depth);")
      else
        w.writeLines(1, s"alignas(${laneAlign(mem.dataType, depth)}) ${genCppType(mem.dataType)} ${mem.name}[$depth];")
    }
    for ((childMod, fullName) <- children)
      w.writeLines(1, s"$childMod ${fullName.split('.').last};")
    if (isTop) {
      for (bank <- registerBanks) {
        val tpe = UIntType(IntWidth(bank.width))
        w.writeLines(1, s"alignas(${laneAlign(tpe, W)}) ${genCppType(tpe)} " +
          s"${registerBankStorageName(bank.name)}[$W];")
      }
      for (p <- m.ports if p.tpe != ClockType) {
        if (p.name == "reset") w.writeLines(1, s"${genCppType(p.tpe)} ${p.name};")
        else w.writeLines(1, s"alignas(${laneAlign(p.tpe, W)}) ${genCppType(p.tpe)} ${p.name}[$W];")
      }
    }
    w.writeLines(0, "")
    w.writeLines(1, s"void rand_init() {")
    for (r <- registers)
      w.writeLines(2, s"for (int _i = 0; _i < $W; _i++) ${r.name}[_i].rand_init();")
    for (mem <- memories)
      w.writeLines(2, s"for (int _i = 0; _i < ${mem.depth}; _i++) ${mem.name}[_i].rand_init();")
    for ((_, fullName) <- children)
      w.writeLines(2, s"${fullName.split('.').last}.rand_init();")
    if (isTop) {
      for (bank <- registerBanks)
        w.writeLines(2, s"for (int _i = 0; _i < $W; _i++) " +
          s"${registerBankStorageName(bank.name)}[_i].rand_init();")
      for (p <- m.ports if p.tpe != ClockType) {
        if (p.name == "reset") w.writeLines(2, s"${p.name}.rand_init();")
        else w.writeLines(2, s"for (int _i = 0; _i < $W; _i++) ${p.name}[_i].rand_init();")
      }
    }
    w.writeLines(1, "}")
    if (!isTop) w.writeLines(0, s"} ${m.name};")
  }

  // ------------------------------------------------------------------
  // Header
  // ------------------------------------------------------------------
  private def emitHeader(circuit: Circuit, res: Result, W: Int, topName: String,
      fuseCap: Int, memberScratch: Boolean, staticScratch: Boolean,
      mergeEval: Boolean, coldSpec: Option[ColdGuard.Spec], w: Writer): Unit = {
    implicit val rn: Renamer = buildRenamer(circuit, res, W, memberScratch || staticScratch)
    zcScratchOverrides = Map.empty
    sharedCombFns.clear()
    smallSelectEligible.clear()
    smallSelectRegisters.clear()
    condHoldWdataAliases = res.registerBanks.iterator.flatMap { bank =>
      bank.forwardSource.filter(_ => res.regs.get(bank.name).exists(_.plan == RPCondHold))
        .map(source => (bank.name + "$wdata") -> source)
    }.toMap
    condHoldWdataAliases.foreach { case (alias, source) =>
      require(rn.nameToMeta(alias).sigType == rn.nameToMeta(source).sigType,
        s"[v2-reg-bank] direct wdata alias '$alias' has a different type from '$source'")
    }
    if (condHoldWdataAliases.nonEmpty)
      println(s"[v2-reg-bank] zero-copy cond-hold wdata: ${condHoldWdataAliases.size} bank(s)")
    // branchlessMux measured: 161 -> 196 ns/cycle on sodor W=16. The hot mux
    // conditions (stall/kill/reset) are heavily biased, so predicted branches
    // that evaluate one side beat blends that always evaluate both. Helper
    // stays emitted for experiments; default off.
    //
    // Primitive UInt lowering is different: it only applies to UInt<=64 comb
    // assignments and keeps nested Muxes as integer mask/blend dataflow. That
    // removes the UInt<1>::operator bool() / byte-array control-flow boundary
    // that made icpx scalarize the hot lane loops. On sodor W=16 this reduced
    // no-verify KernelEval from ~128 ns/cycle to ~95 ns/cycle and full-verify
    // KernelEval from ~153 ns/cycle to ~121 ns/cycle. Keep env opt-outs for
    // bisecting regressions:
    //   V2_PRIMITIVE_UINT_EXPR=0
    //   V2_PRIMITIVE_UINT_MUX_BLEND=0
    val primitiveUIntExpr = envBool("V2_PRIMITIVE_UINT_EXPR", default = true)
    val primitiveUIntMuxBlend =
      primitiveUIntExpr && envBool("V2_PRIMITIVE_UINT_MUX_BLEND", default = true)
    implicit val ctx: essent.EmitContext =
      essent.EmitContext(forward = Some(true), vectorWidth = W,
        branchlessMux = envBool("V2_BRANCHLESS_MUX", default = false),
        primitiveUIntExpr = primitiveUIntExpr,
        primitiveUIntMuxBlend = primitiveUIntMuxBlend)

    val hoistedScratch = memberScratch || staticScratch
    prepareScratchShapes(res, W, coldSpec)
    // A BOOM-sized eval contains several thousand independent lane loops.
    // Keeping them in one C++ function makes LLVM's LoopRotate/SCEV passes
    // repeatedly update one enormous dominator tree (minutes of compile time
    // and multi-GB RSS).  With hoisted scratch, schedule blocks have no
    // function-local values that must flow between them, so they can be
    // wrapped in ordered noinline lambdas without changing dataflow.  The
    // wrapper retains flags/index arrays and invokes every chunk in the exact
    // original schedule order. Chunk weight charges every vector loop a
    // substantial fixed cost plus its fused template count, and scalar lane
    // statements individually; this bounds both loop count and CFG size. Set
    // V2_EVAL_CHUNK_WEIGHT=0 to bisect/disable. By default only schedules of
    // at least V2_EVAL_OUTLINE_MIN_UNITS=30000 are outlined; explicitly
    // setting the chunk weight forces the choice for smaller kernels too.
    val explicitEvalChunkWeight = sys.env.contains("V2_EVAL_CHUNK_WEIGHT") ||
      sys.env.contains("V2_EVAL_CHUNK_BLOCKS")
    // Complete-Small BOOM A/B (Clang 19, W=4): 1536 first removed the giant
    // eval-function cliff; a longer interleaved scan then selected 3072 over
    // 1536 by 1.0232x (7/9 wins).  6144 lost 0.9858x to 3072 in the follow-up
    // ultra-long scan, while 768 was already a clear loss.  Weight 3072 emits
    // 54 helpers per direction and compiles in about 67 seconds instead of
    // roughly 300 seconds unoutlined.  The current full-chip schedule has
    // 37,502 units, so use a 30,000-unit automatic threshold; the 14,174-unit
    // core-only schedule remains unoutlined without an explicit override.
    val requestedEvalChunkWeight = sys.env.get("V2_EVAL_CHUNK_WEIGHT")
      .orElse(sys.env.get("V2_EVAL_CHUNK_BLOCKS")) // compatibility with early experiments
      .flatMap(_.trim.toIntOption).getOrElse(3072)
    val evalOutlineMinUnits = sys.env.get("V2_EVAL_OUTLINE_MIN_UNITS")
      .flatMap(_.trim.toIntOption).getOrElse(30000)
    val largeEval = math.max(res.scheduleFwd.size, res.scheduleRev.size) >= evalOutlineMinUnits
    val evalChunkWeight =
      if (hoistedScratch && requestedEvalChunkWeight > 0 &&
          (explicitEvalChunkWeight || largeEval)) requestedEvalChunkWeight else 0
    if (requestedEvalChunkWeight > 0 && !hoistedScratch)
      println("[v2] eval outlining disabled for eval-local scratch")
    else if (requestedEvalChunkWeight > 0 && !explicitEvalChunkWeight && !largeEval)
      println(s"[v2] eval outlining skipped: schedule below $evalOutlineMinUnits units")
    // Merged-direction emission only knows how to atomically roll singleton
    // register chains.  State-array forwarding/commit is direction-sensitive,
    // so use the two proven fixed-direction bodies for now.
    val hasZipper = res.sccOf.groupBy(_._2).values.exists(_.size > 1) ||
      res.stateArrays.nonEmpty
    // The ordered access streams of a fully-external array have exactly one
    // consumer: their RVerify node.  They do not feed the simulated design,
    // so staging each stream through a writable lane array before comparing
    // it to `$rtl` only adds a copy.  Alias these streams directly to their
    // current v4m block slot.  Fail closed if graph construction ever gives
    // one a functional consumer; unlike the experimental register zero-copy
    // path, this does not turn repeated functional reads into cold mmap reads.
    val requestedDirectVerify = res.stateArrays.valuesIterator
      .filter(_.fullyExternal).flatMap { info =>
        info.readAccess.iterator.map(_.addressOracle) ++
          info.writeAccess.iterator.flatMap(a => Iterator(
            a.enableOracle, a.addressOracle, a.dataOracle))
      }.toSet
    directVerifyOracles =
      if (!directVerifyOracle) Set.empty
      else requestedDirectVerify.filter { name =>
        val specs = res.oracles.filter(_.flatName == name)
        val verifyNodes = res.nodes.filter(_.role == RVerify(name))
        // A --simd-v2-no-verify build intentionally has no RVerify consumer;
        // leave its established injection shape unchanged in this pass.
        if (verifyNodes.isEmpty) false
        else {
        val producers = res.nodes.filter(_.produces.contains(name))
        val ordinaryReaders = res.nodes.filter(n =>
          V2Pipeline.stmtReads(n.stmt).contains(name))
        require(specs.size == 1,
          s"[v2-direct-verify] '$name' has ${specs.size} oracle specs, expected one")
        val spec = specs.head
        require(!spec.isRegister && spec.verified && spec.words == 1,
          s"[v2-direct-verify] '$name' is not one verified scalar comb oracle")
        require(producers.size == 1 && producers.head.role == ROracleInject(name),
          s"[v2-direct-verify] '$name' is not produced solely by ROracleInject")
        require(verifyNodes.size == 1,
          s"[v2-direct-verify] '$name' has ${verifyNodes.size} RVerify consumers, expected one")
        require(ordinaryReaders.isEmpty,
          s"[v2-direct-verify] '$name' gained ordinary consumer(s): " +
            ordinaryReaders.take(4).map(_.id).mkString(","))
        val tpe = res.combCuts.getOrElse(name,
          throw new IllegalStateException(
            s"[v2-direct-verify] '$name' is missing its comb-cut type"))
        val width = firrtl.bitWidth(tpe).toInt
        require(!tpe.isInstanceOf[firrtl.ir.SIntType] && width <= 64 &&
            specElemBytes(res, spec) ==
              (if (width <= 8) 1 else if (width <= 16) 2
               else if (width <= 32) 4 else 8),
          s"[v2-direct-verify] '$name' does not have an alias-safe POD layout")
        true
        }
      }
    if (directVerifyOracles.nonEmpty)
      println(s"[v2] direct-verify oracle injection: ${directVerifyOracles.size} " +
        "fully-external access stream(s) aliased")

    val directVerifyInfo = directVerifyOracles.iterator.map { name =>
      val spec = res.oracles.find(_.flatName == name).get
      name -> ((v4Off(spec.arraySymbol), v4Elem(spec.arraySymbol),
        genCppType(res.combCuts(name))))
    }.toMap
    val registerZcInfo =
      if (!zeroCopy || (mergeEval && !hasZipper)) Map.empty[String, (Long, Int, String)]
      else {
        // Cold outline helpers (_v2_cold_comb_full) carry no direction
        // parameter; a register they read must keep its injected lane array.
        val coldRead: Set[String] = coldSpec match {
          case None => Set.empty
          case Some(spec) =>
            val tiers = spec.base +: spec.extra.toSeq
            res.nodes.indices.iterator
              .filter(t => tiers.exists(_.touches(t)))
              .flatMap(t => V2Pipeline.stmtReads(res.nodes(t).stmt))
              .toSet
        }
        res.oracles.iterator.filter { o =>
          o.isRegister && res.regs.get(o.flatName).exists { ri =>
            ri.plan == RPOracle && !ri.tpe.isInstanceOf[firrtl.ir.SIntType]
          } && o.words == 1 && o.widthBits <= 64 && !coldRead.contains(o.flatName) &&
            specElemBytes(res, o) == (if (o.widthBits <= 8) 1 else if (o.widthBits <= 16) 2
              else if (o.widthBits <= 32) 4 else 8)
        }.map { o =>
          o.flatName -> ((v4Off(o.arraySymbol), v4Elem(o.arraySymbol),
            genCppType(res.regs(o.flatName).tpe)))
        }.toMap
      }
    require((directVerifyInfo.keySet intersect registerZcInfo.keySet).isEmpty,
      "[v2-direct-verify] comb and register alias sets overlap")
    zcInfo = registerZcInfo ++ directVerifyInfo
    zcSymbols = zcInfo.keysIterator.map { name =>
      val specs = res.oracles.filter(_.flatName == name)
      require(specs.size == 1,
        s"[v2] aliased oracle '$name' has ${specs.size} stream symbols")
      name -> specs.head.arraySymbol
    }.toMap
    if (zeroCopy)
      println(s"[v2] zero-copy oracle injection: ${registerZcInfo.size}/${res.oracles.count(_.isRegister)} register streams aliased")
    // Oracle registers whose committed storage IS still consumed: operands of
    // serial/cond-hold chains (whole-chain hoisting reads previous-window
    // committed lanes at window start) and anything cold tiers touch (quiet
    // images rely on held storage). These keep their commit.
    oracleCommitKeep = {
      val serialReads = res.regs.valuesIterator.flatMap(ri => ri.plan match {
        case RPSerialNext(folded, _) => V2Pipeline.exprReads(folded)
        case _ => Seq.empty[String]
      }).toSet
      // Every template inside a residual serial region is scheduled per-lane
      // or chain-coalesced; both forms may read operand storage under the
      // previous-window (committed) model — keep every oracle register any
      // of them reads. (Measured on Rocket W=16: the folded-expr set alone
      // missed the consumer and the first window misverified.)
      val serialRegionReads = res.sccOf.keysIterator
        .flatMap(t => V2Pipeline.stmtReads(res.nodes(t).stmt)).toSet
      val coldReads: Set[String] = coldSpec match {
        case None => Set.empty
        case Some(spec) =>
          res.nodes.indices.iterator
            .filter(t => spec.tiers.exists(_.touches(t)))
            .flatMap(t => V2Pipeline.stmtReads(res.nodes(t).stmt))
            .toSet
      }
      val keep = (serialReads ++ serialRegionReads ++ coldReads)
        .filter(n => res.regs.get(n).exists(_.plan == RPOracle))
      if (keep.nonEmpty)
        println(s"[v2] oracle commits kept for ${keep.size} serial/cold-consumed register(s)")
      keep
    }
    // Aliased registers own no storage: suppress lane-array declarations for
    // every alias spelling (fwd/rev/rescan) via the no-declare base set.
    for (m <- Seq(zcDirOverrides(W, +1), zcDirOverrides(W, -1), zcRescanOverrides(W)); b <- m.values)
      rn.addStructMemberBase(b)
    val reuseRequested = envBool("V2_REUSE_SCRATCH", default = false)
    val reuseReportRequested = envBool("V2_REPORT_SCRATCH_REUSE", default = false)
    if ((reuseRequested || reuseReportRequested) && !hoistedScratch)
      println("[v2] scratch reuse planning requested but eval-local scratch is unchanged; use static/member scratch")
    val reuseReport = if (hoistedScratch && (reuseRequested || reuseReportRequested))
      Some(buildScratchReusePlan(res, W, fuseCap, mergeEval, hasZipper, coldSpec))
    else None
    val scratchReuse = if (reuseRequested) reuseReport else None
    reuseReport.foreach { p =>
      val status = if (scratchReuse.isDefined) "enabled" else "report-only"
      val blocks = p.traceBlocks.map { case (name, count) => s"$name=$count" }.mkString(",")
      println(s"[v2] scratch reuse $status: old=${p.oldArrays} arrays/${p.oldBytes} B " +
        s"new=${p.slots.size} typed slots/${p.newBytes} B unseen=${p.unseenArrays} " +
        s"liveIn=${p.liveInArrays} blocks=[$blocks]")
    }
    scratchReuse.foreach { p =>
      // File-scope references keep the original signal spellings available
      // to post-emission observers. LLVM resolves these immutable bindings
      // directly to the shared storage. Member scratch retains base renaming
      // to avoid reference members and their copy/indirection semantics.
      if (!staticScratch) {
        zcScratchOverrides = p.overrides
        rn.setSimdBaseOverrides(p.overrides)
      }
      p.slots.foreach(s => rn.addStructMemberBase(s.base))
    }

    val guard = topName.toUpperCase + "_H_"
    w.writeLines(0, s"#ifndef $guard")
    w.writeLines(0, s"#define $guard")
    w.writeLines(0, "")
    w.writeLines(0, "#include <array>")
    w.writeLines(0, "#include <cassert>")
    w.writeLines(0, "#include <cstdint>")
    w.writeLines(0, "#include <cinttypes>")
    w.writeLines(0, "#include <cstdio>")
    w.writeLines(0, "#include <cstdlib>")
    w.writeLines(0, "#include <cstring>")
    // The scan helpers below use x86 intrinsics only inside AVX-512 feature
    // guards.  Keep the header itself target-neutral so an ARM build host can
    // compile the scalar fallback (and can cross-compile the same source for
    // x86 once a sysroot is supplied).
    w.writeLines(0, "#if defined(__x86_64__) || defined(_M_X64)")
    w.writeLines(0, "#include <immintrin.h>")
    w.writeLines(0, "#endif")
    w.writeLines(0, "#include <memory>")
    w.writeLines(0, "#include \"sint_pod_v2.h\"")
    if (Seq("V2_BRANCHLESS_HOLD", "V2_BRANCHLESS_FORWARD", "V2_SMALL_STATE_SELECT")
        .exists(name => envBool(name, default = false)))
      w.writeLines(0, "#include \"branch_select.h\"")
    if (res.oracles.nonEmpty) w.writeLines(0, "#include \"oracle_data.h\"")
    w.writeLines(0, "#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)")
    // Lane loops have no loop-carried dependences by construction (serial
    // chains are emitted separately, without this pragma). Note: icpx still
    // rejects some loops over "assumed OUTPUT dependence" between member
    // array stores reached through `this`; pair with -fno-alias (safe: every
    // emitted array is a distinct object). `omp simd` (forced vectorization)
    // measured strictly worse — it overrides the cost model.
    w.writeLines(0, "#if defined(__clang__) || defined(__INTEL_LLVM_COMPILER)")
    w.writeLines(0, "#define ESSENT_LANE_LOOP _Pragma(\"clang loop vectorize(assume_safety)\")")
    // Lane loops over W-1 lanes (the cross-lane register verify: next[k] vs
    // injected r[k+1]): with a trip count one short of the lane count the
    // default cost model picks half the width plus a scalar remainder that
    // covers most of the lanes. Predicated (tail-folded) vectorization at
    // the full lane width runs them as one masked vector iteration; the
    // scalar remainder never runs. Applied to every kernel lane loop it
    // measured slower (the unroll(disable) it needs hurts the W-lane loops),
    // so it is limited to the short loops.
    // Width capped at 32 lanes: wider requests exceed what the backend
    // vectorizes as one masked iteration; a W-1 loop then folds in two.
    w.writeLines(0, s"#define ESSENT_TAIL_LOOP _Pragma(\"clang loop vectorize(assume_safety) " +
      s"vectorize_width(${math.min(W, 32)}) vectorize_predicate(enable) unroll(disable)\")")
    w.writeLines(0, "#elif defined(__GNUC__)")
    w.writeLines(0, "#define ESSENT_LANE_LOOP _Pragma(\"GCC ivdep\")")
    w.writeLines(0, "#define ESSENT_TAIL_LOOP _Pragma(\"GCC ivdep\")")
    w.writeLines(0, "#else")
    w.writeLines(0, "#define ESSENT_LANE_LOOP")
    w.writeLines(0, "#define ESSENT_TAIL_LOOP")
    w.writeLines(0, "#endif")
    // Perf: oracle streams are stored width-honest (u8/u16/u32/u64 chosen from
    // the signal width, elemBytes in oracle_manifest.json) instead of a flat
    // 8 B per cycle per stream — Rocket's 112 injected streams drop from 896
    // to ~300 stream bytes per simulated cycle, so injection touches ~3x
    // fewer cache lines and the mmap'd file shrinks accordingly. The loader
    // is type-generic so a packer that still emits uint64_t* pointers (boom /
    // fpu-guider not yet migrated) keeps working as the degenerate u64 tier.
    // v4: stream slots inside a window block are naturally aligned to their
    // elem tier only (blocks themselves start 64B-aligned), so no 64B
    // alignment promise here — unaligned vector loads are free on the hosts.
    w.writeLines(0, "template <typename E>")
    w.writeLines(0, "static inline uint64_t essent_oracle_load(const E* p, int64_t i) {")
    w.writeLines(1, "return (uint64_t)p[i];")
    w.writeLines(0, "}")
    w.writeLines(0, "#define ESSENT_ORACLE_LOAD(name, idx) essent_oracle_load((name), (idx))")
    w.writeLines(0, "#if defined(__GNUC__) || defined(__clang__)")
    w.writeLines(0, "#define ESSENT_COLD_NOINLINE __attribute__((cold, noinline))")
    w.writeLines(0, "#define ESSENT_NOINLINE __attribute__((noinline))")
    w.writeLines(0, "#else")
    w.writeLines(0, "#define ESSENT_COLD_NOINLINE")
    w.writeLines(0, "#define ESSENT_NOINLINE")
    w.writeLines(0, "#endif")
    w.writeLines(0, "#ifndef ESSENT_ORACLE_VERIFY")
    w.writeLines(0, "#define ESSENT_ORACLE_VERIFY 1")
    w.writeLines(0, "#endif")
    w.writeLines(0, "template <int W>")
    w.writeLines(0, "static inline uint64_t essent_to_u64(const UInt<W>& v) {")
    w.writeLines(1, "if constexpr (W <= 64) return v.as_single_word();")
    w.writeLines(1, "else return v.template bits<63,0>().as_single_word();")
    w.writeLines(0, "}")
    w.writeLines(0, "template <int W>")
    w.writeLines(0, "static inline uint64_t essent_to_u64(const SInt<W>& v) {")
    w.writeLines(1, "if constexpr (W <= 64) return (uint64_t)v.as_single_word();")
    w.writeLines(1, "else return v.template bits<63,0>().as_single_word();")
    w.writeLines(0, "}")
    // Raw scalar storage of a narrow POD lane, for verify accumulation in the
    // value's native width tier (widening every u8 operand to u64 first cost
    // a vpmovzx per operand; XOR equality only needs the raw bits). Narrow
    // (!kWide) instantiations only — accumAssign guards on width <= 64.
    w.writeLines(0, "template <int W>")
    w.writeLines(0, "static inline typename UInt<W>::scalar_t essent_raw(const UInt<W>& v) { return v.val; }")
    w.writeLines(0, "template <int W>")
    w.writeLines(0, "static inline typename UInt<W>::scalar_t essent_raw(const SInt<W>& v) { return v.ui.val; }")
    // Compare a contiguous lane slice as bytes. Masked loads cover exactly
    // the requested bytes, including unaligned W-1 register slices. The
    // caller ORs all fields before the original single cold-rescan branch.
    w.writeLines(0, "#ifndef ESSENT_VERIFY_PACKED")
    w.writeLines(0, "#define ESSENT_VERIFY_PACKED 1")
    w.writeLines(0, "#endif")
    w.writeLines(0, "#if ESSENT_VERIFY_PACKED && defined(__AVX512F__) && defined(__AVX512BW__)")
    w.writeLines(0, "template <int Lanes, int ElemBytes, typename A, typename B>")
    w.writeLines(0, "static inline __m512i essent_verify_block(const A* a, const B* b) {")
    w.writeLines(1, "static_assert(sizeof(A) == ElemBytes && sizeof(B) == ElemBytes, \"oracle POD storage has padding\");")
    w.writeLines(1, "constexpr int bytes = Lanes * ElemBytes;")
    w.writeLines(1, "const char* pa = reinterpret_cast<const char*>(a);")
    w.writeLines(1, "const char* pb = reinterpret_cast<const char*>(b);")
    w.writeLines(1, "__m512i diff = _mm512_setzero_si512();")
    w.writeLines(1, "for (int offset = 0; offset < (bytes / 64) * 64; offset += 64) {")
    w.writeLines(2, "diff = _mm512_or_si512(diff, _mm512_xor_si512(_mm512_loadu_si512(pa + offset), _mm512_loadu_si512(pb + offset)));")
    w.writeLines(1, "}")
    w.writeLines(1, "if constexpr (bytes % 64 != 0) {")
    w.writeLines(2, "constexpr __mmask64 mask = (__mmask64)((uint64_t(1) << (bytes % 64)) - 1);")
    w.writeLines(2, "diff = _mm512_or_si512(diff, _mm512_xor_si512(_mm512_maskz_loadu_epi8(mask, pa + (bytes / 64) * 64), _mm512_maskz_loadu_epi8(mask, pb + (bytes / 64) * 64)));")
    w.writeLines(1, "}")
    w.writeLines(1, "return diff;")
    w.writeLines(0, "}")
    w.writeLines(0, "#endif")
    // Branchless by-value mux. `c ? a[L] : b[L]` has glvalue operands, so
    // the backend lowers it to address-select + conditional load, which the
    // loop vectorizer rejects (whole lane loops fell back to scalar
    // cmp/cmov chains). Taking both sides by value and blending with a mask
    // keeps the loop a pure dataflow of loads/logic/stores -> vpblendm.
    w.writeLines(0, "template <int C, int W>")
    w.writeLines(0, "static inline UInt<W> essent_mux(UInt<C> c, UInt<W> t, UInt<W> f) {")
    w.writeLines(1, "if constexpr (!UInt<W>::kWide) {")
    w.writeLines(2, "using S = typename UInt<W>::scalar_t;")
    w.writeLines(2, "const S m = (S)0 - (S)(c.val != 0);")
    w.writeLines(2, "UInt<W> r;")
    w.writeLines(2, "r.val = (S)((t.val & m) | (f.val & (S)~m));")
    w.writeLines(2, "return r;")
    w.writeLines(1, "} else {")
    w.writeLines(2, "return bool(c) ? t : f;")
    w.writeLines(1, "}")
    w.writeLines(0, "}")
    w.writeLines(0, "template <int C, int W>")
    w.writeLines(0, "static inline SInt<W> essent_mux(UInt<C> c, SInt<W> t, SInt<W> f) {")
    w.writeLines(1, "return SInt<W>(essent_mux(c, t.ui, f.ui));")
    w.writeLines(0, "}")
    // Oracle-inject / register-commit primitives with __restrict PARAMETERS.
    // Perf: emitted as plain fused lane loops, every [vec oracle-inject] and
    // [vec commit] loop was rejected by icpx's vectorizer ("assumed
    // FLOW/OUTPUT/ANTI dependence"): lane elements are unsigned-char-based
    // PODs whose stores through `this` may legally alias the stream pointers
    // and this->oracle_cycle, and icpx 2025.3 ignores both the assume_safety
    // pragma and block-scope __restrict locals when disproving those
    // dependences (verified on a reduced testcase; stock clang honors the
    // pragma). __restrict FUNCTION parameters are the one form all three
    // backends honor (the noalias scopes survive inlining), so each template
    // is routed through these helpers instead: every inject loop vectorizes,
    // and commit — an elementwise identity copy of two same-typed POD arrays —
    // becomes a plain memcpy that lowers to vector moves (measured on Rocket
    // W=8: eval_forward static instructions -10.5%, kernel 667->642 ns/cycle
    // with the other v2 fixes excluded). Type deduction on T doubles as a
    // compile-time check that commit source/destination widths match.
    // v4 window-major: `src` already points at this stream's slot inside the
    // current super-window block, so fwd reads elements [0, W) and rev reads
    // the second half back-to-front — no cycle-cursor argument at all.
    // v4m pre-mirrored rev half: the packer stores the second half of each
    // stream's 2W-slot reversed (lane L's rev value at element W+L), so both
    // passes inject with a straight same-order copy — no runtime vpshufb.
    // Same-size tiers copy raw bytes without the T(uint64) re-mask: stream
    // values come from the reference RTL sim and are canonical by
    // construction, the packer range-checks the tier, and Micro-Lockstep
    // verify catches any malformed injection on the very next window.
    // V2_NO_PREMIRROR=1 restores chronological rev order (layout tag v4)
    // for A/B bisection; the mask-free copy stays in both modes.
    val revIdx = if (premirror) "W + L" else "2 * W - 1 - L"
    w.writeLines(0, "template <int W, typename T, typename E>")
    w.writeLines(0, "static inline void essent_inject_fwd(T* __restrict dst, const E* __restrict src) {")
    w.writeLines(1, "if constexpr (sizeof(T) == sizeof(E)) memcpy(dst, src, W * sizeof(T));")
    w.writeLines(1, "else {")
    w.writeLines(2, "ESSENT_LANE_LOOP")
    w.writeLines(2, "for (int L = 0; L < W; L++) dst[L] = T(ESSENT_ORACLE_LOAD(src, L));")
    w.writeLines(1, "}")
    w.writeLines(0, "}")
    w.writeLines(0, "template <int W, typename T, typename E>")
    w.writeLines(0, "static inline void essent_inject_rev(T* __restrict dst, const E* __restrict src) {")
    if (premirror) {
      w.writeLines(1, "if constexpr (sizeof(T) == sizeof(E)) memcpy(dst, src + W, W * sizeof(T));")
      w.writeLines(1, "else {")
      w.writeLines(2, "ESSENT_LANE_LOOP")
      w.writeLines(2, s"for (int L = 0; L < W; L++) dst[L] = T(ESSENT_ORACLE_LOAD(src, $revIdx));")
      w.writeLines(1, "}")
    } else {
      w.writeLines(1, "ESSENT_LANE_LOOP")
      w.writeLines(1, s"for (int L = 0; L < W; L++) dst[L] = T(ESSENT_ORACLE_LOAD(src, $revIdx));")
    }
    w.writeLines(0, "}")
    w.writeLines(0, "template <int W, typename T>")
    w.writeLines(0, "static inline void essent_commit_lanes(T* __restrict dst, const T* __restrict src) {")
    w.writeLines(1, "memcpy(dst, src, W * sizeof(T));")
    w.writeLines(0, "}")
    // Wide (>64-bit) register oracles: one stream per 64-bit word, stored
    // into the wide POD's word array (UInt<N>::val is std::array<uint64_t,k>).
    w.writeLines(0, "template <int W, int I, typename T, typename E>")
    w.writeLines(0, "static inline void essent_inject_word_fwd(T* __restrict dst, const E* __restrict src) {")
    w.writeLines(1, "ESSENT_LANE_LOOP")
    w.writeLines(1, "for (int L = 0; L < W; L++) dst[L].val[I] = (uint64_t)ESSENT_ORACLE_LOAD(src, L);")
    w.writeLines(0, "}")
    w.writeLines(0, "template <int W, int I, typename T, typename E>")
    w.writeLines(0, "static inline void essent_inject_word_rev(T* __restrict dst, const E* __restrict src) {")
    w.writeLines(1, "ESSENT_LANE_LOOP")
    w.writeLines(1, s"for (int L = 0; L < W; L++) dst[L].val[I] = (uint64_t)ESSENT_ORACLE_LOAD(src, $revIdx);")
    w.writeLines(0, "}")
    // Bytes per super-window block of the v4 window-major oracle file. The
    // harness cross-checks this against the packer's oracle_data.h constant
    // with a static_assert, so a stale repack cannot silently misindex.
    w.writeLines(0, s"static constexpr int64_t ORACLE_BLOCK_BYTES = ${v4BlockBytes}LL;")
    w.writeLines(0, s"static constexpr int ORACLE_KERNEL_MIRRORED = ${if (premirror) 1 else 0};")
    emitCondHoldHelpers(w)
    emitAffineScanHelpers(w)
    if (staticScratch) emitStaticScratchArrays(res, W, scratchReuse, w)
    emitLookupTables(res, w)

    val omittedMemoryMembers = fullyExternalMemoryMembers(circuit, res)
    emitStructs(circuit, res, W, omittedMemoryMembers, w)

    // open top struct
    val topMod = findModule(topName, circuit).asInstanceOf[Module]
    emitModuleStruct(topMod, W, w, isTop = true, circuit,
      registerBanks = res.registerBanks,
      omittedMemoryNames = omittedMemoryMembers.getOrElse(topName, Set.empty))
    if (memberScratch) emitTopScratchMembers(res, W, scratchReuse, w)
    w.writeLines(0, "")
    w.writeLines(1, "bool assert_triggered = false;")
    w.writeLines(1, "int assert_exit_code = 0;")
    w.writeLines(1, "uint64_t verify_mismatches = 0;")
    // Reporting policy is independent of verification and datapath execution.
    // A relaxed runner still executes every compare and counts every mismatch;
    // only oracle failures stop setting the design's assertion/exit state.
    w.writeLines(1, "bool oracle_mismatches_fatal = true;")
    w.writeLines(1, "uint64_t oracle_mismatch_log_limit = 16;")
    w.writeLines(1, "void set_oracle_mismatch_policy(bool fatal, uint64_t log_limit = 16) {")
    w.writeLines(2, "oracle_mismatches_fatal = fatal; oracle_mismatch_log_limit = log_limit;")
    w.writeLines(1, "}")
    w.writeLines(1, "bool oracle_mismatch_should_log() const {")
    w.writeLines(2, "return oracle_mismatches_fatal || verify_mismatches < oracle_mismatch_log_limit;")
    w.writeLines(1, "}")
    w.writeLines(1, "void record_oracle_mismatch() {")
    w.writeLines(2, "++verify_mismatches;")
    w.writeLines(2, "if (oracle_mismatches_fatal) { assert_triggered = true; assert_exit_code = 42; }")
    w.writeLines(1, "}")
    // A partial terminal SIMD half-window contains synthetic lanes beyond the
    // scalar trace.  The harness can suppress assertions and oracle checks for
    // that half while keeping done_reset=true, so oracle injection and the
    // real datapath cycles remain unchanged.
    w.writeLines(1, "bool checks_enabled = true;")
    // Keep the cycle cursor present even for a zero-internal-oracle control.
    // Rocket's trace-driven harness still uses it to align external inputs.
    w.writeLines(1, "int oracle_cycle = 0;")
    // v4: base of the current super-window's block in the mmap'd oracle file.
    // The harness points it at the kernel section on init; eval advances it
    // by ORACLE_BLOCK_BYTES in lockstep with oracle_cycle.
    w.writeLines(1, "const char* oracle_win_base = nullptr;")
    // Window-boundary verification state (see BoundaryVerifyRegistry): the
    // previous sweep's last-lane RTL next-state per verified register oracle,
    // and whether that sweep ran with checks enabled. A harness that re-seeks
    // the oracle stream must clear oracle_boundary_valid.
    w.writeLines(1, "bool oracle_boundary_valid = false;")
    val carryRegs = res.nodes.iterator.flatMap(n => n.role match {
      case RVerify(r) if res.regs.contains(r) => Some(r)
      case _ => None
    }).toSeq.distinct
    if (carryRegs.nonEmpty)
      w.writeLines(1, s"// [boundary-verify] ${carryRegs.size} carried next-state values")
    for (r <- carryRegs)
      w.writeLines(1, s"${genCppType(res.regs(r).tpe)} ${boundaryCarryName(r)};")
    w.writeLines(0, "")

    // A member helper can see register state plus member/file-scope scratch,
    // but not arrays declared inside eval. Keep local-scratch emission on the
    // exact inline fallback rather than passing hundreds of pointers through
    // the cold interface.
    val verifyOutline = new VerifyOutlineRegistry(hoistedScratch)
    val coldCombOutline = new ColdCombOutlineRegistry(hoistedScratch)
    val coldCommitOutline = new ColdCommitOutlineRegistry(hoistedScratch)
    if (!verifyOutline.enabled && res.oracles.exists(_.verified))
      println("[v2] verify cold outlining disabled for eval-local scratch")
    if (!coldCombOutline.enabled && coldSpec.isDefined)
      println("[v2] cold full-arm outlining disabled for eval-local scratch")

    // Merged emission (one shared body, direction branches only around the
    // small direction-dependent parts) is only proven safe when every serial
    // region is a single template (a singleton chain can be emitted
    // atomically; multi-template zippers interleave per lane and cannot).
    // Off by default until merged direction branches are validated per DUT.
    // The shared body targets kernels whose duplicated directions overflow the
    // instruction cache; cold specialization is preserved in both modes.
    sharedCombFns.clear()
    // Partitioned emits default to partition bodies only (the whole-design
    // bodies double the header and its compile time); V2_PARTITION_ONLY=0
    // keeps eval_forward/eval_reverse for a mono replay of the same emit.
    val partitionOnly = res.partitions.nonEmpty && envBool("V2_PARTITION_ONLY", default = true)
    if (partitionOnly) {
      println("[v2-partition] whole-design eval bodies replaced by stubs (V2_PARTITION_ONLY)")
      for (fname <- Seq("eval_forward", "eval_reverse")) {
        w.writeLines(1, s"void $fname(bool update_registers, bool verbose, bool done_reset) {")
        w.writeLines(2, "abort();  // partition-only header: use eval_partition()")
        w.writeLines(1, "}")
      }
      w.writeLines(1, "void eval(bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, "eval_forward(update_registers, verbose, done_reset);")
      w.writeLines(1, "}")
    } else if (!mergeEval && (envBool("V2_SHARED_EVAL", default = false) ||
        sys.env.get("V2_SHARED_EVAL").exists(v => v == "regions" || v == "merged")) && hoistedScratch) {
      // The legacy merged scheduler has its own scratch-lifetime trace; keep
      // it paired with its emitter when explicitly requested by the CLI.
      emitSharedEval(res, W, fuseCap, coldSpec, coldCombOutline, coldCommitOutline,
        verifyOutline, if (requestedEvalChunkWeight > 0) requestedEvalChunkWeight else 3072, w)
    } else if (!mergeEval || hasZipper) {
      if (mergeEval && hasZipper)
        println("[v2] multi-template serial regions present — falling back to two eval bodies")
      emitEvalFunctionZc(res, W, "eval_forward", res.scheduleFwd, dir = +1, fuseCap,
        coldSpec, coldCombOutline, coldCommitOutline, verifyOutline, evalChunkWeight, w)
      emitEvalFunctionZc(res, W, "eval_reverse", res.scheduleRev, dir = -1, fuseCap,
        coldSpec, coldCombOutline, coldCommitOutline, verifyOutline, evalChunkWeight, w)
      w.writeLines(1, "void eval(bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, "eval_forward(update_registers, verbose, done_reset);")
      w.writeLines(2, "eval_reverse(update_registers, verbose, done_reset);")
      w.writeLines(1, "}")
    } else {
      if (evalChunkWeight > 0)
        println("[v2] eval outlining currently applies to fixed-direction bodies; merged eval unchanged")
      emitMergedEval(res, W, fuseCap, coldSpec, coldCombOutline, coldCommitOutline,
        verifyOutline, w)
      w.writeLines(1, "void eval_forward(bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, "eval_dir(true, update_registers, verbose, done_reset);")
      w.writeLines(1, "}")
      w.writeLines(1, "void eval_reverse(bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, "eval_dir(false, update_registers, verbose, done_reset);")
      w.writeLines(1, "}")
      w.writeLines(1, "void eval(bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, "eval_dir(true, update_registers, verbose, done_reset);")
      w.writeLines(2, "eval_dir(false, update_registers, verbose, done_reset);")
      w.writeLines(1, "}")
    }
    // Two-level parallelism: one eval pair per partition, each restricted to
    // the partition's template cone (schedule order preserved). Threads run
    // separate harness instances, so this needs member scratch storage.
    if (res.partitions.nonEmpty) {
      if (mergeEval && !hasZipper)
        println("[v2-partition] merged eval requested; partition bodies use the two-body form")
      w.writeLines(1, s"// [v2 partitions] ${res.partitions.size} partition(s): " +
        res.partitions.map(_.size).mkString("/") + " templates")
      for ((part, p) <- res.partitions.zipWithIndex) {
        // A state array read by this partition but committed elsewhere must
        // be an externalized read port (its value then comes from the trace).
        val foreignArrays = res.stateArrays.keysIterator.filter { a =>
          val si = res.stateArrays(a)
          !part.contains(si.commitId) && si.readIds.exists(part.contains)
        }.toSeq.sorted
        val unexternalized = foreignArrays.filterNot(a => externAllReads(res, a))
        require(unexternalized.isEmpty, s"[v2-partition] partition $p reads state array(s) it does not " +
          s"own without externalized read ports: ${unexternalized.take(6).mkString(", ")}")
        if (foreignArrays.nonEmpty)
          println(s"[v2-partition] partition $p: ${foreignArrays.size} foreign state array(s), all externalized")
        emitEvalFunctionZc(res, W, s"eval_forward_p$p",
          res.scheduleFwd.filter(u => part.contains(u.tid)), dir = +1, fuseCap,
          coldSpec, coldCombOutline, coldCommitOutline, verifyOutline, evalChunkWeight, w)
        emitEvalFunctionZc(res, W, s"eval_reverse_p$p",
          res.scheduleRev.filter(u => part.contains(u.tid)), dir = -1, fuseCap,
          coldSpec, coldCombOutline, coldCommitOutline, verifyOutline, evalChunkWeight, w)
      }
      w.writeLines(1, s"static constexpr int ESSENT_PARTITIONS = ${res.partitions.size};")
      w.writeLines(1, "void eval_partition(int p, bool forward, bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, "switch (p) {")
      for (p <- res.partitions.indices)
        w.writeLines(3, s"case $p: if (forward) eval_forward_p$p(update_registers, verbose, done_reset); " +
          s"else eval_reverse_p$p(update_registers, verbose, done_reset); break;")
      w.writeLines(3, "default: break;")
      w.writeLines(2, "}")
      w.writeLines(1, "}")
    } else {
      w.writeLines(1, "static constexpr int ESSENT_PARTITIONS = 0;")
    }
    emitColdCombOutlineHelper(res, W, coldCombOutline, w)
    emitColdCommitOutlineHelper(res, W, coldCommitOutline, w)
    emitVerifyOutlineHelper(res, W, verifyOutline, w)
    emitBoundaryVerifyHelper(res, W, w)
    if (sharedCombFns.nonEmpty) {
      w.writeLines(1, s"// [v2 shared-comb] ${sharedCombFns.size} groups called from both directions")
      for ((_, (id, body)) <- sharedCombFns) {
        w.writeLines(1, s"ESSENT_NOINLINE void _v2_cshare_$id() {")
        w.write(body)
        w.writeLines(1, "}")
      }
    }
    if (smallSelectRegisters.nonEmpty)
      println(s"[v2] bounded scalar selects: ${smallSelectRegisters.size} register(s)")
    w.writeLines(0, s"} $topName;")
    w.writeLines(0, "")
    w.writeLines(0, s"#endif  // $guard")
  }

  /** Affine prefix scan (RPAffineScan). Lane step function f_i(x) =
    * keep_i ? x + add_i : add_i (mod 2^BW); composition
    * (f ∘ g) = (keep_f & keep_g, keep_f ? add_g + add_f : add_f) is
    * associative, so a Hillis-Steele scan over the (keep, add) pairs yields
    * r[i] = P[i-1](r[0]) for every lane in log2(W) steps. The window lives in
    * one vector register: a YMM when W * sizeof(lane) == 32 bytes (native
    * lanes), else a ZMM (narrower lanes widened on load, narrowed on store).
    * Wider windows compose two half-scans through one scalar link, like the
    * cond-hold scan. W < 16 without a native YMM fit, and non-powers of two,
    * use the sequential chain (measured: at W = 8 the vector setup costs
    * more than the 7-link chain it replaces). */
  private def emitAffineScanHelpers(w: Writer): Unit = {
    def iota(n: Int) = (0 until n).mkString(", ")
    val code = s"""
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__) && defined(__AVX512VBMI__)
#define ESSENT_AFFINE_SCAN_VECTOR 1
// ---- 512-bit lane ops (EB bytes per lane, N = 64 / EB lanes) ----
template <int EB> struct essent_zmm_ops;
template <> struct essent_zmm_ops<1> {
  using V = __m512i; using K = __mmask64; static constexpr int N = 64;
  static inline V iota() { alignas(64) static const uint8_t t[64] = {${iota(64)}}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi8(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi8(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi8(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi8(static_cast<char>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_subs_epu8(iota(), set1(static_cast<uint64_t>(s))); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epu8(_mm512_adds_epu8(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm512_loadu_si512(reinterpret_cast<const void*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm512_storeu_si512(reinterpret_cast<void*>(p), v); }
};
template <> struct essent_zmm_ops<2> {
  using V = __m512i; using K = __mmask32; static constexpr int N = 32;
  static inline V iota() { alignas(64) static const uint16_t t[32] = {${iota(32)}}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi16(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi16(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi16(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi16(static_cast<short>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_max_epi16(_mm512_sub_epi16(iota(), set1(static_cast<uint64_t>(s))), _mm512_setzero_si512()); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epi16(_mm512_add_epi16(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) {
    if constexpr (sizeof(S) == 2) return _mm512_loadu_si512(reinterpret_cast<const void*>(p));
    else return _mm512_cvtepu8_epi16(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
  }
  template <typename S> static inline void store(S* p, V v) {
    if constexpr (sizeof(S) == 2) _mm512_storeu_si512(reinterpret_cast<void*>(p), v);
    else _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), _mm512_cvtepi16_epi8(v));
  }
};
template <> struct essent_zmm_ops<4> {
  using V = __m512i; using K = __mmask16; static constexpr int N = 16;
  static inline V iota() { alignas(64) static const uint32_t t[16] = {${iota(16)}}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi32(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi32(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi32(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi32(static_cast<int>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_max_epi32(_mm512_sub_epi32(iota(), set1(static_cast<uint64_t>(s))), _mm512_setzero_si512()); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epi32(_mm512_add_epi32(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) {
    if constexpr (sizeof(S) == 4) return _mm512_loadu_si512(reinterpret_cast<const void*>(p));
    else if constexpr (sizeof(S) == 2) return _mm512_cvtepu16_epi32(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
    else return _mm512_cvtepu8_epi32(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p)));
  }
  template <typename S> static inline void store(S* p, V v) {
    if constexpr (sizeof(S) == 4) _mm512_storeu_si512(reinterpret_cast<void*>(p), v);
    else if constexpr (sizeof(S) == 2) _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), _mm512_cvtepi32_epi16(v));
    else _mm_storeu_si128(reinterpret_cast<__m128i*>(p), _mm512_cvtepi32_epi8(v));
  }
};
template <> struct essent_zmm_ops<8> {
  using V = __m512i; using K = __mmask8; static constexpr int N = 8;
  static inline V iota() { alignas(64) static const uint64_t t[8] = {${iota(8)}}; return _mm512_load_si512(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm512_permutexvar_epi64(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm512_mask_add_epi64(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm512_mask_mov_epi64(src, m, a); }
  static inline V set1(uint64_t v) { return _mm512_set1_epi64(static_cast<long long>(v)); }
  static inline V and_(V a, V b) { return _mm512_and_si512(a, b); }
  static inline V idx_fwd(int s) { return _mm512_max_epi64(_mm512_sub_epi64(iota(), set1(static_cast<uint64_t>(s))), _mm512_setzero_si512()); }
  static inline V idx_rev(int s, int last) { return _mm512_min_epi64(_mm512_add_epi64(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) {
    if constexpr (sizeof(S) == 8) return _mm512_loadu_si512(reinterpret_cast<const void*>(p));
    else if constexpr (sizeof(S) == 4) return _mm512_cvtepu32_epi64(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)));
    else if constexpr (sizeof(S) == 2) return _mm512_cvtepu16_epi64(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p)));
    else return _mm512_cvtepu8_epi64(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(p)));
  }
  template <typename S> static inline void store(S* p, V v) {
    if constexpr (sizeof(S) == 8) _mm512_storeu_si512(reinterpret_cast<void*>(p), v);
    else if constexpr (sizeof(S) == 4) _mm256_storeu_si256(reinterpret_cast<__m256i*>(p), _mm512_cvtepi64_epi32(v));
    else if constexpr (sizeof(S) == 2) _mm_storeu_si128(reinterpret_cast<__m128i*>(p), _mm512_cvtepi64_epi16(v));
    else _mm_storel_epi64(reinterpret_cast<__m128i*>(p), _mm512_cvtepi64_epi8(v));
  }
};
// ---- 256-bit native-lane ops (EB bytes per lane, N = 32 / EB lanes) ----
template <int EB> struct essent_ymm_ops;
template <> struct essent_ymm_ops<1> {
  using V = __m256i; using K = __mmask32; static constexpr int N = 32;
  static inline V iota() { alignas(32) static const uint8_t t[32] = {${iota(32)}}; return _mm256_load_si256(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm256_permutexvar_epi8(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm256_mask_add_epi8(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm256_mask_mov_epi8(src, m, a); }
  static inline V set1(uint64_t v) { return _mm256_set1_epi8(static_cast<char>(v)); }
  static inline V and_(V a, V b) { return _mm256_and_si256(a, b); }
  static inline V idx_fwd(int s) { return _mm256_subs_epu8(iota(), set1(static_cast<uint64_t>(s))); }
  static inline V idx_rev(int s, int last) { return _mm256_min_epu8(_mm256_adds_epu8(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm256_loadu_si256(reinterpret_cast<const V*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm256_storeu_si256(reinterpret_cast<V*>(p), v); }
};
template <> struct essent_ymm_ops<2> {
  using V = __m256i; using K = __mmask16; static constexpr int N = 16;
  static inline V iota() { alignas(32) static const uint16_t t[16] = {${iota(16)}}; return _mm256_load_si256(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm256_permutexvar_epi16(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm256_mask_add_epi16(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm256_mask_mov_epi16(src, m, a); }
  static inline V set1(uint64_t v) { return _mm256_set1_epi16(static_cast<short>(v)); }
  static inline V and_(V a, V b) { return _mm256_and_si256(a, b); }
  static inline V idx_fwd(int s) { return _mm256_max_epi16(_mm256_sub_epi16(iota(), set1(static_cast<uint64_t>(s))), _mm256_setzero_si256()); }
  static inline V idx_rev(int s, int last) { return _mm256_min_epi16(_mm256_add_epi16(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm256_loadu_si256(reinterpret_cast<const V*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm256_storeu_si256(reinterpret_cast<V*>(p), v); }
};
template <> struct essent_ymm_ops<4> {
  using V = __m256i; using K = __mmask8; static constexpr int N = 8;
  static inline V iota() { alignas(32) static const uint32_t t[8] = {${iota(8)}}; return _mm256_load_si256(reinterpret_cast<const V*>(t)); }
  static inline V perm(V idx, V v) { return _mm256_permutexvar_epi32(idx, v); }
  static inline V mask_add(V src, K m, V a, V b) { return _mm256_mask_add_epi32(src, m, a, b); }
  static inline V mask_mov(V src, K m, V a) { return _mm256_mask_mov_epi32(src, m, a); }
  static inline V set1(uint64_t v) { return _mm256_set1_epi32(static_cast<int>(v)); }
  static inline V and_(V a, V b) { return _mm256_and_si256(a, b); }
  static inline V idx_fwd(int s) { return _mm256_max_epi32(_mm256_sub_epi32(iota(), set1(static_cast<uint64_t>(s))), _mm256_setzero_si256()); }
  static inline V idx_rev(int s, int last) { return _mm256_min_epi32(_mm256_add_epi32(iota(), set1(static_cast<uint64_t>(s))), set1(static_cast<uint64_t>(last))); }
  template <typename S> static inline V load(const S* p) { return _mm256_loadu_si256(reinterpret_cast<const V*>(p)); }
  template <typename S> static inline void store(S* p, V v) { _mm256_storeu_si256(reinterpret_cast<V*>(p), v); }
};
template <int W>
static inline uint64_t essent_keep_mask(const UInt<1>* keep) {
  static_assert(sizeof(UInt<1>) == 1);
  const void* p = reinterpret_cast<const void*>(keep);
  if constexpr (W == 64) { const __m512i v = _mm512_loadu_si512(p); return static_cast<uint64_t>(_mm512_test_epi8_mask(v, v)); }
  else if constexpr (W == 32) { const __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p)); return static_cast<uint64_t>(_mm256_test_epi8_mask(v, v)); }
  else if constexpr (W == 16) { const __m128i v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(p)); return static_cast<uint64_t>(_mm_test_epi8_mask(v, v)); }
  else { const __m128i v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(p)); return static_cast<uint64_t>(_mm_test_epi8_mask(v, v)) & 0xffull; }
}
// Quiet-window test: no lane adds anything (all add lanes zero).
static inline bool essent_vec_all_zero(__m512i v) { return _mm512_test_epi64_mask(v, v) == 0; }
static inline bool essent_vec_all_zero(__m256i v) { return _mm256_testz_si256(v, v) != 0; }
// Forward scan body: time order = increasing lane index, seed = r[0].
template <class O, int W, int BW, typename S>
static inline void essent_affine_scan_body_fwd(S* r, const UInt<1>* keep, const S* add) {
  using K = typename O::K;
  using V = typename O::V;
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
  constexpr uint64_t ALL = (W == 64) ? ~0ull : ((1ull << W) - 1ull);
  constexpr bool needMask = BW < 8 * (O::N == W ? static_cast<int>(sizeof(S)) : 64 / W);
  const V vm = O::set1(M);
  uint64_t k = essent_keep_mask<W>(keep);
  V a = O::template load<S>(add);
  const V vs = O::set1(static_cast<uint64_t>(r[0]));
  if (__builtin_expect(k == ALL, 1)) {
    // Plain prefix sum (no clear inside the window). Quiet window: hold.
    if (essent_vec_all_zero(a)) { O::template store<S>(r, vs); return; }
    for (int s = 1; s < W; s <<= 1) {
      const uint64_t low = (1ull << s) - 1ull;
      a = O::mask_add(a, static_cast<K>(ALL & ~low), a, O::perm(O::idx_fwd(s), a));
      if constexpr (needMask) a = O::and_(a, vm);
    }
    V out = O::mask_add(vs, static_cast<K>(ALL & ~1ull), vs, O::perm(O::idx_fwd(1), a));
    if constexpr (needMask) out = O::and_(out, vm);
    O::template store<S>(r, out);
    return;
  }
  for (int s = 1; s < W; s <<= 1) {
    const uint64_t low = (1ull << s) - 1ull;
    const V sh = O::perm(O::idx_fwd(s), a);
    a = O::mask_add(a, static_cast<K>(k & ~low), a, sh);
    if constexpr (needMask) a = O::and_(a, vm);
    k = k & ((k << s) | low) & ALL;
  }
  V out = O::perm(O::idx_fwd(1), a);
  out = O::mask_add(out, static_cast<K>((k << 1) & ALL), out, vs);
  if constexpr (needMask) out = O::and_(out, vm);
  out = O::mask_mov(out, static_cast<K>(1), vs);
  O::template store<S>(r, out);
}
// Reverse scan body: time order = decreasing lane index, seed = r[W-1].
template <class O, int W, int BW, typename S>
static inline void essent_affine_scan_body_rev(S* r, const UInt<1>* keep, const S* add) {
  using K = typename O::K;
  using V = typename O::V;
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
  constexpr uint64_t ALL = (W == 64) ? ~0ull : ((1ull << W) - 1ull);
  constexpr bool needMask = BW < 8 * (O::N == W ? static_cast<int>(sizeof(S)) : 64 / W);
  const V vm = O::set1(M);
  uint64_t k = essent_keep_mask<W>(keep);
  V a = O::template load<S>(add);
  const V vs = O::set1(static_cast<uint64_t>(r[W - 1]));
  if (__builtin_expect(k == ALL, 1)) {
    if (essent_vec_all_zero(a)) { O::template store<S>(r, vs); return; }
    for (int s = 1; s < W; s <<= 1) {
      const uint64_t high = ALL & ~((1ull << (W - s)) - 1ull);
      a = O::mask_add(a, static_cast<K>(ALL & ~high), a, O::perm(O::idx_rev(s, W - 1), a));
      if constexpr (needMask) a = O::and_(a, vm);
    }
    V out = O::mask_add(vs, static_cast<K>(ALL >> 1), vs, O::perm(O::idx_rev(1, W - 1), a));
    if constexpr (needMask) out = O::and_(out, vm);
    O::template store<S>(r, out);
    return;
  }
  for (int s = 1; s < W; s <<= 1) {
    const uint64_t high = ALL & ~((1ull << (W - s)) - 1ull);
    const V sh = O::perm(O::idx_rev(s, W - 1), a);
    a = O::mask_add(a, static_cast<K>(k & ~high), a, sh);
    if constexpr (needMask) a = O::and_(a, vm);
    k = k & ((k >> s) | high);
  }
  V out = O::perm(O::idx_rev(1, W - 1), a);
  out = O::mask_add(out, static_cast<K>(k >> 1), out, vs);
  if constexpr (needMask) out = O::and_(out, vm);
  out = O::mask_mov(out, static_cast<K>(1ull << (W - 1)), vs);
  O::template store<S>(r, out);
}
#endif

template <int W, int BW>
static inline void essent_affine_scan_fwd(UInt<BW>* __restrict r, const UInt<1>* __restrict keep, const UInt<BW>* __restrict add) {
  using S = typename UInt<BW>::scalar_t;
  static_assert(sizeof(UInt<BW>) == sizeof(S), "affine scan needs scalar register storage");
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
#if defined(ESSENT_AFFINE_SCAN_VECTOR)
  if constexpr (W * sizeof(S) == 32 && (W == 8 || W == 16 || W == 32)) {
    essent_affine_scan_body_fwd<essent_ymm_ops<32 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr ((W == 16 || W == 32 || W == 64) && sizeof(S) <= 64 / W) {
    essent_affine_scan_body_fwd<essent_zmm_ops<64 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr (W >= 16 && (W & (W - 1)) == 0) {
    constexpr int H = W / 2;
    essent_affine_scan_fwd<H, BW>(r, keep, add);
    r[H].val = static_cast<S>((keep[H - 1].val ? static_cast<S>(r[H - 1].val + add[H - 1].val) : add[H - 1].val) & M);
    essent_affine_scan_fwd<H, BW>(r + H, keep + H, add + H);
    return;
  }
#endif
  for (int L = 1; L < W; L++) r[L].val = static_cast<S>((keep[L - 1].val ? static_cast<S>(r[L - 1].val + add[L - 1].val) : add[L - 1].val) & M);
}

template <int W, int BW>
static inline void essent_affine_scan_rev(UInt<BW>* __restrict r, const UInt<1>* __restrict keep, const UInt<BW>* __restrict add) {
  using S = typename UInt<BW>::scalar_t;
  static_assert(sizeof(UInt<BW>) == sizeof(S), "affine scan needs scalar register storage");
  constexpr uint64_t M = static_cast<uint64_t>(UInt<BW>::kMask);
#if defined(ESSENT_AFFINE_SCAN_VECTOR)
  if constexpr (W * sizeof(S) == 32 && (W == 8 || W == 16 || W == 32)) {
    essent_affine_scan_body_rev<essent_ymm_ops<32 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr ((W == 16 || W == 32 || W == 64) && sizeof(S) <= 64 / W) {
    essent_affine_scan_body_rev<essent_zmm_ops<64 / W>, W, BW, S>(reinterpret_cast<S*>(r), keep, reinterpret_cast<const S*>(add));
    return;
  } else if constexpr (W >= 16 && (W & (W - 1)) == 0) {
    constexpr int H = W / 2;
    essent_affine_scan_rev<H, BW>(r + H, keep + H, add + H);
    r[H - 1].val = static_cast<S>((keep[H].val ? static_cast<S>(r[H].val + add[H].val) : add[H].val) & M);
    essent_affine_scan_rev<H, BW>(r, keep, add);
    return;
  }
#endif
  for (int L = W - 2; L >= 0; L--) r[L].val = static_cast<S>((keep[L + 1].val ? static_cast<S>(r[L + 1].val + add[L + 1].val) : add[L + 1].val) & M);
}
"""
    w.writeLines(0, code.split("\n").toSeq)
  }

  private def emitCondHoldHelpers(w: Writer): Unit = {
    w.writeLines(0, Seq(
      "",
      // Lane bitmask helpers for the vector-scan read-port forwarding
      // (stateReadLaneStr): W bytes of 0/1 -> one bit per lane.
      "template <int W>",
      "static inline uint64_t essent_lane_all() { return W >= 64 ? ~0ull : ((1ull << W) - 1ull); }",
      "template <int W>",
      "static inline uint64_t essent_lane_mask(const uint8_t* t) {",
      "#if defined(__AVX2__)",
      "  if constexpr (W == 32) {",
      "    const __m256i v = _mm256_load_si256(reinterpret_cast<const __m256i*>(t));",
      "    return static_cast<uint32_t>(_mm256_movemask_epi8(_mm256_cmpgt_epi8(v, _mm256_setzero_si256())));",
      "  } else if constexpr (W == 16) {",
      "    const __m128i v = _mm_load_si128(reinterpret_cast<const __m128i*>(t));",
      "    return static_cast<uint32_t>(_mm_movemask_epi8(_mm_cmpgt_epi8(v, _mm_setzero_si128())));",
      "  } else if constexpr (W == 64) {",
      "    return essent_lane_mask<32>(t) | (essent_lane_mask<32>(t + 32) << 32);",
      "  } else",
      "#endif",
      "  {",
      "    uint64_t m = 0;",
      "    for (int i = 0; i < W; i++) m |= static_cast<uint64_t>(t[i] != 0) << i;",
      "    return m;",
      "  }",
      "}",
      "",
      // Bundle-level cond-hold lowering. All flattened fields in one group
      // have the exact same write-enable, so compute the serial last-writer
      // index once, then apply it independently to every field's wdata. The
      // apply loop has no loop-carried data dependency and can vectorize even
      // when W/BW has no hand-written prefix-scan intrinsic path below.
      "template <int W>",
      "static inline void essent_condhold_index_fwd(int16_t* __restrict idx, const UInt<1>* __restrict wen) {",
      "  static_assert(W < 32768, \"cond-hold index type is too narrow\");",
      "#if defined(__AVX512F__) && defined(__AVX512CD__) && defined(__AVX512BW__) && defined(__AVX512VL__) && !defined(CHISA_NO_FAST_HOLD_INDEX)",
      "  if constexpr ((W == 16 || W == 32) && sizeof(UInt<1>) == 1) {",
      "    uint32_t mask;",
      "    if constexpr (W == 16)",
      "      mask = static_cast<uint32_t>(_mm_cmpneq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wen)), _mm_setzero_si128()));",
      "    else",
      "      mask = static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen)), _mm256_setzero_si256()));",
      "    const __m512i bits = _mm512_set1_epi32(static_cast<int>(mask));",
      "    const __m512i one = _mm512_set1_epi32(1);",
      "    const __m512i lanes = _mm512_setr_epi32(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);",
      "    for (int B = 0; B < W; B += 16) {",
      "      const __m512i lane = _mm512_add_epi32(lanes, _mm512_set1_epi32(B));",
      "      const __m512i prefix = _mm512_sub_epi32(_mm512_sllv_epi32(one, lane), one);",
      "      const __m512i last = _mm512_sub_epi32(_mm512_set1_epi32(31), _mm512_lzcnt_epi32(_mm512_and_si512(bits, prefix)));",
      "      _mm256_storeu_si256(reinterpret_cast<__m256i*>(idx + B), _mm512_cvtepi32_epi16(last));",
      "    }",
      "    return;",
      "  }",
      "#endif",
      "  int last = -1;",
      "  idx[0] = -1;",
      "  for (int L = 1; L < W; L++) {",
      "    if (essent_to_u64(wen[L - 1])) last = L - 1;",
      "    idx[L] = static_cast<int16_t>(last);",
      "  }",
      "}",
      "template <int W>",
      "static inline void essent_condhold_index_rev(int16_t* __restrict idx, const UInt<1>* __restrict wen) {",
      "  static_assert(W < 32768, \"cond-hold index type is too narrow\");",
      "#if defined(__AVX512F__) && defined(__AVX512CD__) && defined(__AVX512BW__) && defined(__AVX512VL__) && !defined(CHISA_NO_FAST_HOLD_INDEX)",
      "  if constexpr ((W == 16 || W == 32) && sizeof(UInt<1>) == 1) {",
      "    uint32_t mask;",
      "    if constexpr (W == 16)",
      "      mask = static_cast<uint32_t>(_mm_cmpneq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wen)), _mm_setzero_si128()));",
      "    else",
      "      mask = static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen)), _mm256_setzero_si256()));",
      "    const __m512i bits = _mm512_set1_epi32(static_cast<int>(mask));",
      "    const __m512i zero = _mm512_setzero_si512();",
      "    const __m512i lanes = _mm512_setr_epi32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);",
      "    for (int B = 0; B < W; B += 16) {",
      "      const __m512i above = _mm512_add_epi32(lanes, _mm512_set1_epi32(B));",
      "      const __m512i suffix = _mm512_sllv_epi32(_mm512_set1_epi32(-1), above);",
      "      const __m512i candidates = _mm512_and_si512(bits, suffix);",
      "      const __m512i firstBit = _mm512_and_si512(candidates, _mm512_sub_epi32(zero, candidates));",
      "      const __m512i first = _mm512_sub_epi32(_mm512_set1_epi32(31), _mm512_lzcnt_epi32(firstBit));",
      "      _mm256_storeu_si256(reinterpret_cast<__m256i*>(idx + B), _mm512_cvtepi32_epi16(first));",
      "    }",
      "    return;",
      "  }",
      "#endif",
      "  int last = -1;",
      "  idx[W - 1] = -1;",
      "  for (int L = W - 2; L >= 0; L--) {",
      "    if (essent_to_u64(wen[L + 1])) last = L + 1;",
      "    idx[L] = static_cast<int16_t>(last);",
      "  }",
      "}",
      "template <int W, typename T>",
      "static ESSENT_NOINLINE void essent_condhold_apply_fwd(T* __restrict r, const int16_t* __restrict idx, const T* __restrict wdata) {",
      "  const T seed = r[0];",
      "  if (idx[W - 1] < 0) { for (int L = 1; L < W; ++L) r[L] = seed; return; }",
      (if (envBool("V2_BRANCHLESS_HOLD", default = false))
        "  if (essent_hold_permute<W>(r, idx, wdata, seed)) return;" else ""),
      "  ESSENT_LANE_LOOP",
      "  for (int L = 1; L < W; L++) {",
      "    const int I = idx[L];",
      (if (envBool("V2_BRANCHLESS_HOLD", default = false))
        "    r[L] = essent_index_or_seed(I, wdata, seed);" else "    r[L] = I < 0 ? seed : wdata[I];"),
      "  }",
      "}",
      "template <int W, typename T>",
      "static ESSENT_NOINLINE void essent_condhold_apply_rev(T* __restrict r, const int16_t* __restrict idx, const T* __restrict wdata) {",
      "  const T seed = r[W - 1];",
      "  if (idx[0] < 0) { for (int L = 0; L < W - 1; ++L) r[L] = seed; return; }",
      (if (envBool("V2_BRANCHLESS_HOLD", default = false))
        "  if (essent_hold_permute<W>(r, idx, wdata, seed)) return;" else ""),
      "  ESSENT_LANE_LOOP",
      "  for (int L = W - 2; L >= 0; L--) {",
      "    const int I = idx[L];",
      (if (envBool("V2_BRANCHLESS_HOLD", default = false))
        "    r[L] = essent_index_or_seed(I, wdata, seed);" else "    r[L] = I < 0 ? seed : wdata[I];"),
      "  }",
      "}",
      "template <int W, int BW>",
      "static inline void essent_condhold_scan_fwd(UInt<BW>* __restrict r, const UInt<1>* __restrict wen, const UInt<BW>* __restrict wdata) {",
      "#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)",
      // Perf: without a matching (W, BW) branch the scan falls through to the scalar
      // loop below — a W-deep serially dependent cmov chain threaded through memory
      // (store-to-load forwarding between iterations). On Rocket W=8 that fallback was
      // taken at all 156 callsites and cost ~23% of kernel time (667→516 ns/cycle when
      // these W==8 branches were added). Each branch replaces the 7-deep cmov chain
      // with a 3-step (log2 W) masked-select scan: 2 vector loads + 3 masked
      // permute/shift selects + 1 vector store, all lanes in one register.
      // The analogous W=4 prefix path was tested on the complete TestHarness.
      // Four lanes are too short to repay mask construction and vector shuffles:
      // it retired more host instructions and was ~0.6% slower in paired A/B.
      "  if constexpr (W == 8 && BW <= 8) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;",
      "    __m128i val = _mm_slli_si128(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(wdata)), 1);",
      "    val = _mm_insert_epi8(val, static_cast<int>(r[0].val), 0);",
      "    __mmask16 take = static_cast<__mmask16>((~valid) & ((valid << 1) & 0xffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 1)); valid |= (valid << 1) & 0xffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 2) & 0xffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 2)); valid |= (valid << 2) & 0xffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 4) & 0xffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 4));",
      "    _mm_storel_epi64(reinterpret_cast<__m128i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 8 && BW > 8 && BW <= 16) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;",
      "    __m128i val = _mm_slli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 2);",
      "    val = _mm_insert_epi16(val, static_cast<int>(r[0].val), 0);",
      "    __mmask8 take = static_cast<__mmask8>((~valid) & ((valid << 1) & 0xffu));",
      "    val = _mm_mask_mov_epi16(val, take, _mm_slli_si128(val, 2)); valid |= (valid << 1) & 0xffu;",
      "    take = static_cast<__mmask8>((~valid) & ((valid << 2) & 0xffu));",
      "    val = _mm_mask_mov_epi16(val, take, _mm_slli_si128(val, 4)); valid |= (valid << 2) & 0xffu;",
      "    take = static_cast<__mmask8>((~valid) & ((valid << 4) & 0xffu));",
      "    val = _mm_mask_mov_epi16(val, take, _mm_slli_si128(val, 8));",
      "    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 8 && BW > 16 && BW <= 32) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;",
      "    const __m256i wd = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wdata));",
      "    __m256i val = _mm256_permutevar8x32_epi32(wd, _mm256_setr_epi32(0,0,1,2,3,4,5,6));",
      "    val = _mm256_mask_mov_epi32(val, static_cast<__mmask8>(0x01), _mm256_set1_epi32(static_cast<int>(r[0].val)));",
      "    __mmask8 take = static_cast<__mmask8>((~valid) & ((valid << 1) & 0xffu));",
      "    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(0,0,1,2,3,4,5,6))); valid |= (valid << 1) & 0xffu;",
      "    take = static_cast<__mmask8>((~valid) & ((valid << 2) & 0xffu));",
      "    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(0,0,0,1,2,3,4,5))); valid |= (valid << 2) & 0xffu;",
      "    take = static_cast<__mmask8>((~valid) & ((valid << 4) & 0xffu));",
      "    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(0,0,0,0,0,1,2,3)));",
      "    _mm256_storeu_si256(reinterpret_cast<__m256i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 8 && BW > 32 && BW <= 64) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = ((static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) << 1) & 0xfeu) | 1u;",
      "    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));",
      "    __m512i val = _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,1,2,3,4,5,6), wd);",
      "    val = _mm512_mask_mov_epi64(val, static_cast<__mmask8>(0x01), _mm512_set1_epi64(static_cast<long long>(r[0].val)));",
      "    __mmask8 take = static_cast<__mmask8>((~valid) & ((valid << 1) & 0xffu));",
      "    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,1,2,3,4,5,6), val)); valid |= (valid << 1) & 0xffu;",
      "    take = static_cast<__mmask8>((~valid) & ((valid << 2) & 0xffu));",
      "    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,0,1,2,3,4,5), val)); valid |= (valid << 2) & 0xffu;",
      "    take = static_cast<__mmask8>((~valid) & ((valid << 4) & 0xffu));",
      "    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(0,0,0,0,0,1,2,3), val));",
      "    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 16 && BW <= 8) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = ((_mm_cmpneq_epi8_mask(wb, zero) << 1) & 0xfffeu) | 1u;",
      "    __m128i val = _mm_slli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 1);",
      "    val = _mm_insert_epi8(val, static_cast<int>(r[0].val), 0);",
      "    __mmask16 take = static_cast<__mmask16>((~valid) & ((valid << 1) & 0xffffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 1)); valid |= (valid << 1) & 0xffffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 2) & 0xffffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 2)); valid |= (valid << 2) & 0xffffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 4) & 0xffffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 4)); valid |= (valid << 4) & 0xffffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 8) & 0xffffu));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_slli_si128(val, 8));",
      "    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 16 && BW > 16 && BW <= 32) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = ((_mm_cmpneq_epi8_mask(wb, zero) << 1) & 0xfffeu) | 1u;",
      "    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));",
      "    __m512i val = _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14), wd);",
      "    val = _mm512_mask_mov_epi32(val, static_cast<__mmask16>(0x0001), _mm512_set1_epi32(static_cast<int>(r[0].val)));",
      "    __mmask16 take = static_cast<__mmask16>((~valid) & ((valid << 1) & 0xffffu));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14), val)); valid |= (valid << 1) & 0xffffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 2) & 0xffffu));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13), val)); valid |= (valid << 2) & 0xffffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 4) & 0xffffu));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11), val)); valid |= (valid << 4) & 0xffffu;",
      "    take = static_cast<__mmask16>((~valid) & ((valid << 8) & 0xffffu));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7), val));",
      "    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 32 && BW > 8 && BW <= 16) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m256i zero = _mm256_setzero_si256();",
      "    const __m256i wb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen));",
      "    uint32_t valid = (static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(wb, zero)) << 1) | 1u;",
      "    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));",
      "    const __m512i lane = _mm512_set_epi16(31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);",
      "    __m512i val = _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(1)), wd);",
      "    val = _mm512_mask_mov_epi16(val, static_cast<__mmask32>(0x00000001u), _mm512_set1_epi16(static_cast<short>(r[0].val)));",
      "    __mmask32 take = static_cast<__mmask32>((~valid) & (valid << 1));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(1)), val)); valid |= valid << 1;",
      "    take = static_cast<__mmask32>((~valid) & (valid << 2));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(2)), val)); valid |= valid << 2;",
      "    take = static_cast<__mmask32>((~valid) & (valid << 4));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(4)), val)); valid |= valid << 4;",
      "    take = static_cast<__mmask32>((~valid) & (valid << 8));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(8)), val)); valid |= valid << 8;",
      "    take = static_cast<__mmask32>((~valid) & (valid << 16));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_subs_epu16(lane, _mm512_set1_epi16(16)), val));",
      "    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);",
      "    return;",
      // Perf: every (W, BW) pair with no hand-written path above used to fall
      // through to the W-deep serially dependent cmov/branch chain. At W=16
      // the complete-TestHarness build takes that fallback for BW in (8,16]
      // and (32,64] — including the hot BPD meta (38-bit) and predicted-pc
      // (40-bit) bank columns. Composing two proven half-width scans plus one
      // scalar chain link keeps the log-depth masked-select structure without
      // any new intrinsics; BW > 64 degenerates to the same scalar work as
      // the fallback and stays correct. Semantics unit-tested exhaustively
      // (fwd/rev, W in {8,16,32} x BW classes, random windows). Compile with
      // -DCHISA_NO_SCAN_COMPOSE to bisect without re-emitting.
      "  }",
      "#if !defined(CHISA_NO_SCAN_COMPOSE)",
      "  else if constexpr (W == 16 || W == 32) {",
      "    constexpr int H = W / 2;",
      "    essent_condhold_scan_fwd<H, BW>(r, wen, wdata);",
      "    r[H] = essent_to_u64(wen[H - 1]) ? wdata[H - 1] : r[H - 1];",
      "    essent_condhold_scan_fwd<H, BW>(r + H, wen + H, wdata + H);",
      "    return;",
      "  }",
      "#endif",
      "#endif",
      "  for (int L = 1; L < W; L++) r[L] = essent_to_u64(wen[L - 1]) ? wdata[L - 1] : r[L - 1];",
      "}",
      "",
      "template <int W, int BW>",
      "static inline void essent_condhold_scan_rev(UInt<BW>* __restrict r, const UInt<1>* __restrict wen, const UInt<BW>* __restrict wdata) {",
      "#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)",
      // Perf: mirrored W == 8 fast paths for the reverse (zig-zag) direction; see the
      // comment on essent_condhold_scan_fwd above for the measured impact.
      "  if constexpr (W == 8 && BW <= 8) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;",
      "    __m128i val = _mm_srli_si128(_mm_loadl_epi64(reinterpret_cast<const __m128i*>(wdata)), 1);",
      "    val = _mm_insert_epi8(val, static_cast<int>(r[7].val), 7);",
      "    __mmask16 take = static_cast<__mmask16>((~valid) & (valid >> 1));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 1)); valid |= valid >> 1;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 2));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 2)); valid |= valid >> 2;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 4));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 4));",
      "    _mm_storel_epi64(reinterpret_cast<__m128i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 8 && BW > 8 && BW <= 16) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;",
      "    __m128i val = _mm_srli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 2);",
      "    val = _mm_insert_epi16(val, static_cast<int>(r[7].val), 7);",
      "    __mmask8 take = static_cast<__mmask8>((~valid) & (valid >> 1));",
      "    val = _mm_mask_mov_epi16(val, take, _mm_srli_si128(val, 2)); valid |= valid >> 1;",
      "    take = static_cast<__mmask8>((~valid) & (valid >> 2));",
      "    val = _mm_mask_mov_epi16(val, take, _mm_srli_si128(val, 4)); valid |= valid >> 2;",
      "    take = static_cast<__mmask8>((~valid) & (valid >> 4));",
      "    val = _mm_mask_mov_epi16(val, take, _mm_srli_si128(val, 8));",
      "    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 8 && BW > 16 && BW <= 32) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;",
      "    const __m256i wd = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wdata));",
      "    __m256i val = _mm256_permutevar8x32_epi32(wd, _mm256_setr_epi32(1,2,3,4,5,6,7,7));",
      "    val = _mm256_mask_mov_epi32(val, static_cast<__mmask8>(0x80), _mm256_set1_epi32(static_cast<int>(r[7].val)));",
      "    __mmask8 take = static_cast<__mmask8>((~valid) & (valid >> 1));",
      "    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(1,2,3,4,5,6,7,7))); valid |= valid >> 1;",
      "    take = static_cast<__mmask8>((~valid) & (valid >> 2));",
      "    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(2,3,4,5,6,7,7,7))); valid |= valid >> 2;",
      "    take = static_cast<__mmask8>((~valid) & (valid >> 4));",
      "    val = _mm256_mask_mov_epi32(val, take, _mm256_permutevar8x32_epi32(val, _mm256_setr_epi32(4,5,6,7,7,7,7,7)));",
      "    _mm256_storeu_si256(reinterpret_cast<__m256i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 8 && BW > 32 && BW <= 64) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = (static_cast<uint32_t>(_mm_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80u;",
      "    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));",
      "    __m512i val = _mm512_permutexvar_epi64(_mm512_setr_epi64(1,2,3,4,5,6,7,7), wd);",
      "    val = _mm512_mask_mov_epi64(val, static_cast<__mmask8>(0x80), _mm512_set1_epi64(static_cast<long long>(r[7].val)));",
      "    __mmask8 take = static_cast<__mmask8>((~valid) & (valid >> 1));",
      "    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(1,2,3,4,5,6,7,7), val)); valid |= valid >> 1;",
      "    take = static_cast<__mmask8>((~valid) & (valid >> 2));",
      "    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(2,3,4,5,6,7,7,7), val)); valid |= valid >> 2;",
      "    take = static_cast<__mmask8>((~valid) & (valid >> 4));",
      "    val = _mm512_mask_mov_epi64(val, take, _mm512_permutexvar_epi64(_mm512_setr_epi64(4,5,6,7,7,7,7,7), val));",
      "    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 16 && BW <= 8) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = (_mm_cmpneq_epi8_mask(wb, zero) >> 1) | 0x8000u;",
      "    __m128i val = _mm_srli_si128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(wdata)), 1);",
      "    val = _mm_insert_epi8(val, static_cast<int>(r[15].val), 15);",
      "    __mmask16 take = static_cast<__mmask16>((~valid) & (valid >> 1));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 1)); valid |= valid >> 1;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 2));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 2)); valid |= valid >> 2;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 4));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 4)); valid |= valid >> 4;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 8));",
      "    val = _mm_mask_mov_epi8(val, take, _mm_srli_si128(val, 8));",
      "    _mm_storeu_si128(reinterpret_cast<__m128i*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 16 && BW > 16 && BW <= 32) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m128i zero = _mm_setzero_si128();",
      "    const __m128i wb = _mm_loadu_si128(reinterpret_cast<const __m128i*>(wen));",
      "    uint32_t valid = (_mm_cmpneq_epi8_mask(wb, zero) >> 1) | 0x8000u;",
      "    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));",
      "    __m512i val = _mm512_permutexvar_epi32(_mm512_setr_epi32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15), wd);",
      "    val = _mm512_mask_mov_epi32(val, static_cast<__mmask16>(0x8000), _mm512_set1_epi32(static_cast<int>(r[15].val)));",
      "    __mmask16 take = static_cast<__mmask16>((~valid) & (valid >> 1));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15), val)); valid |= valid >> 1;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 2));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,15), val)); valid |= valid >> 2;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 4));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(4,5,6,7,8,9,10,11,12,13,14,15,15,15,15,15), val)); valid |= valid >> 4;",
      "    take = static_cast<__mmask16>((~valid) & (valid >> 8));",
      "    val = _mm512_mask_mov_epi32(val, take, _mm512_permutexvar_epi32(_mm512_setr_epi32(8,9,10,11,12,13,14,15,15,15,15,15,15,15,15,15), val));",
      "    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);",
      "    return;",
      "  } else if constexpr (W == 32 && BW > 8 && BW <= 16) {",
      "    static_assert(sizeof(UInt<BW>) == sizeof(typename UInt<BW>::scalar_t));",
      "    const __m256i zero = _mm256_setzero_si256();",
      "    const __m256i wb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(wen));",
      "    uint32_t valid = (static_cast<uint32_t>(_mm256_cmpneq_epi8_mask(wb, zero)) >> 1) | 0x80000000u;",
      "    const __m512i wd = _mm512_loadu_si512(reinterpret_cast<const void*>(wdata));",
      "    const __m512i lane = _mm512_set_epi16(31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0);",
      "    const __m512i top = _mm512_set1_epi16(31);",
      "    __m512i val = _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(1)), top), wd);",
      "    val = _mm512_mask_mov_epi16(val, static_cast<__mmask32>(0x80000000u), _mm512_set1_epi16(static_cast<short>(r[31].val)));",
      "    __mmask32 take = static_cast<__mmask32>((~valid) & (valid >> 1));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(1)), top), val)); valid |= valid >> 1;",
      "    take = static_cast<__mmask32>((~valid) & (valid >> 2));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(2)), top), val)); valid |= valid >> 2;",
      "    take = static_cast<__mmask32>((~valid) & (valid >> 4));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(4)), top), val)); valid |= valid >> 4;",
      "    take = static_cast<__mmask32>((~valid) & (valid >> 8));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(8)), top), val)); valid |= valid >> 8;",
      "    take = static_cast<__mmask32>((~valid) & (valid >> 16));",
      "    val = _mm512_mask_mov_epi16(val, take, _mm512_permutexvar_epi16(_mm512_min_epu16(_mm512_add_epi16(lane, _mm512_set1_epi16(16)), top), val));",
      "    _mm512_storeu_si512(reinterpret_cast<void*>(r), val);",
      "    return;",
      // Perf: reverse-direction mirror of the half-width composition above.
      "  }",
      "#if !defined(CHISA_NO_SCAN_COMPOSE)",
      "  else if constexpr (W == 16 || W == 32) {",
      "    constexpr int H = W / 2;",
      "    essent_condhold_scan_rev<H, BW>(r + H, wen + H, wdata + H);",
      "    r[H - 1] = essent_to_u64(wen[H]) ? wdata[H] : r[H];",
      "    essent_condhold_scan_rev<H, BW>(r, wen, wdata);",
      "    return;",
      "  }",
      "#endif",
      "#endif",
      "  for (int L = W - 2; L >= 0; L--) r[L] = essent_to_u64(wen[L + 1]) ? wdata[L + 1] : r[L + 1];",
      "}",
      "",
      "template <int W, int BW>",
      "static inline void essent_condhold_scan_fwd(SInt<BW>* __restrict r, const UInt<1>* __restrict wen, const SInt<BW>* __restrict wdata) {",
      "  for (int L = 1; L < W; L++) r[L] = essent_to_u64(wen[L - 1]) ? wdata[L - 1] : r[L - 1];",
      "}",
      "template <int W, int BW>",
      "static inline void essent_condhold_scan_rev(SInt<BW>* __restrict r, const UInt<1>* __restrict wen, const SInt<BW>* __restrict wdata) {",
      "  for (int L = W - 2; L >= 0; L--) r[L] = essent_to_u64(wen[L + 1]) ? wdata[L + 1] : r[L + 1];",
      "}",
      "",
      // Perf: bit-sliced single-bit comb (V2_U1_PACK). W lanes of a 1-bit
      // signal live in one W-bit mask; a chain of u1 and/or/xor/mux/compare
      // statements then costs one scalar bitwise op per statement for ALL
      // lanes, instead of a per-lane loop. Pack/unpack sit only at chain
      // boundaries. clang lowers these loops to movmsk-style sequences.
      "template <int W>",
      "static inline uint64_t essent_pack_u1(const UInt<1>* __restrict v) {",
      "#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)",
      "  if constexpr (W == 16) {",
      "    return _mm_test_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(v)), _mm_set1_epi8(1));",
      "  } else if constexpr (W == 32) {",
      "    return _mm256_test_epi8_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(v)), _mm256_set1_epi8(1));",
      "  }",
      "#endif",
      "  uint64_t m = 0;",
      "  ESSENT_LANE_LOOP",
      "  for (int L = 0; L < W; L++) m |= (uint64_t)(v[L].val & 1u) << L;",
      "  return m;",
      "}",
      "template <int W>",
      "static inline void essent_unpack_u1(UInt<1>* __restrict v, uint64_t m) {",
      "#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)",
      "  if constexpr (W == 16) {",
      "    _mm_storeu_si128(reinterpret_cast<__m128i*>(v), _mm_maskz_set1_epi8(static_cast<__mmask16>(m), 1));",
      "    return;",
      "  } else if constexpr (W == 32) {",
      "    _mm256_storeu_si256(reinterpret_cast<__m256i*>(v), _mm256_maskz_set1_epi8(static_cast<__mmask32>(m), 1));",
      "    return;",
      "  }",
      "#endif",
      "  ESSENT_LANE_LOOP",
      "  for (int L = 0; L < W; L++) v[L].val = (uint8_t)((m >> L) & 1u);",
      "}",
      // Compare-to-mask entry points: a lane-wise equality of narrow operands
      // produces the packed form directly (vpcmpeq* writes a k-mask), so wide
      // compares feeding u1 logic cost one instruction for all lanes instead
      // of a per-lane loop. E = the storage scalar type of both operands.
      "template <int W, typename S>",
      "static inline uint64_t essent_pack_cmp_eq(const S* __restrict a, const S* __restrict b) {",
      "#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)",
      "  if constexpr (W == 16 && sizeof(S) == 1) {",
      "    return _mm_cmpeq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(a)), _mm_loadu_si128(reinterpret_cast<const __m128i*>(b)));",
      "  } else if constexpr (W == 16 && sizeof(S) == 2) {",
      "    return _mm256_cmpeq_epi16_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(a)), _mm256_loadu_si256(reinterpret_cast<const __m256i*>(b)));",
      "  } else if constexpr (W == 16 && sizeof(S) == 4) {",
      "    return _mm512_cmpeq_epi32_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), _mm512_loadu_si512(reinterpret_cast<const void*>(b)));",
      "  } else if constexpr (W == 16 && sizeof(S) == 8) {",
      "    const __mmask8 lo = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), _mm512_loadu_si512(reinterpret_cast<const void*>(b)));",
      "    const __mmask8 hi = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a + 8)), _mm512_loadu_si512(reinterpret_cast<const void*>(b + 8)));",
      "    return (uint64_t)lo | ((uint64_t)hi << 8);",
      "  }",
      "#endif",
      "  uint64_t m = 0;",
      "  for (int L = 0; L < W; L++) m |= (uint64_t)(a[L] == b[L]) << L;",
      "  return m;",
      "}",
      "template <int W, typename S>",
      "static inline uint64_t essent_pack_cmp_eq_k(const S* __restrict a, uint64_t k) {",
      "#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)",
      "  if constexpr (W == 16 && sizeof(S) == 1) {",
      "    return _mm_cmpeq_epi8_mask(_mm_loadu_si128(reinterpret_cast<const __m128i*>(a)), _mm_set1_epi8((char)k));",
      "  } else if constexpr (W == 16 && sizeof(S) == 2) {",
      "    return _mm256_cmpeq_epi16_mask(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(a)), _mm256_set1_epi16((short)k));",
      "  } else if constexpr (W == 16 && sizeof(S) == 4) {",
      "    return _mm512_cmpeq_epi32_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), _mm512_set1_epi32((int)k));",
      "  } else if constexpr (W == 16 && sizeof(S) == 8) {",
      "    const __m512i kk = _mm512_set1_epi64((long long)k);",
      "    const __mmask8 lo = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a)), kk);",
      "    const __mmask8 hi = _mm512_cmpeq_epi64_mask(_mm512_loadu_si512(reinterpret_cast<const void*>(a + 8)), kk);",
      "    return (uint64_t)lo | ((uint64_t)hi << 8);",
      "  }",
      "#endif",
      "  uint64_t m = 0;",
      "  for (int L = 0; L < W; L++) m |= (uint64_t)(a[L] == (S)k) << L;",
      "  return m;",
      "}"
    ))
  }

  private case class ScratchValue(base: String, tpe: Type, names: Vector[String], order: Int, lanes: Int)
  private case class ScratchSlot(base: String, tpe: Type, lanes: Int)
  private case class ScratchReusePlan(overrides: Map[String, String], slots: Vector[ScratchSlot],
      oldArrays: Int, oldBytes: Long, newBytes: Long, unseenArrays: Int, liveInArrays: Int,
      traceBlocks: Seq[(String, Int)])
  private case class ScratchBlock(defs: Set[String], reads: Set[String]) {
    def touches: Set[String] = defs ++ reads
  }
  private object ScratchDiscardWriter extends Writer {
    override def write(c: Int): Unit = ()
    override def write(cbuf: Array[Char], off: Int, len: Int): Unit = ()
    override def write(str: String): Unit = ()
    override def write(str: String, off: Int, len: Int): Unit = ()
    override def flush(): Unit = ()
    override def close(): Unit = ()
  }

  private def scratchValues(res: Result)(implicit rn: Renamer): Vector[ScratchValue] = {
    val byBase = mutable.LinkedHashMap[String, (Type, ArrayBuffer[String])]()
    for (n <- res.nodes; name <- n.produces
         if !condHoldWdataAliases.contains(name) && !zcInfo.contains(name)) {
      rn.nameToMeta.get(name) match {
        case Some(SigMeta(Local, tpe)) =>
          rn.simdBase(name).foreach { base =>
            byBase.get(base) match {
              case Some((oldType, names)) =>
                require(oldType == tpe, s"[v2] scratch base '$base' has mixed FIRRTL types")
                if (!names.contains(name)) names += name
              case None => byBase(base) = (tpe, ArrayBuffer(name))
            }
          }
        case _ =>
      }
    }
    byBase.iterator.zipWithIndex.map { case ((base, (tpe, names)), order) =>
      ScratchValue(base, tpe, names.toVector, order, rn.simdStorageLanes(names.head))
    }.toVector
  }

  private def scratchArrayBytes(tpe: Type, W: Int): Long = {
    val bits = firrtl.bitWidth(tpe).toInt
    val elemBytes = if (bits <= 8) 1L else if (bits <= 16) 2L else if (bits <= 32) 4L
      else 8L * ((bits + 63) / 64)
    val raw = elemBytes * W
    val align = laneAlign(tpe, W).toLong
    ((raw + align - 1) / align) * align
  }

  private def scratchExprReads(e: Expression): Seq[String] = e match {
    case w: WRef => Seq(w.name)
    case w: WSubField =>
      Seq(essent.Emitter.emitExpr(w)(null, essent.Emitter.DefaultContext))
    case m: Mux => scratchExprReads(m.cond) ++ scratchExprReads(m.tval) ++ scratchExprReads(m.fval)
    case p: DoPrim => p.args.flatMap(scratchExprReads)
    case v: ValidIf => scratchExprReads(v.cond) ++ scratchExprReads(v.value)
    case a: WSubAccess => scratchExprReads(a.expr) ++ scratchExprReads(a.index)
    case _ => Seq.empty
  }

  private def scratchStmtReads(s: Statement): Seq[String] = s match {
    case b: Block => b.stmts.flatMap(scratchStmtReads)
    case d: DefNode => scratchExprReads(d.value)
    case c: Connect => scratchExprReads(c.expr)
    case p: Print => p.args.flatMap(scratchExprReads) ++ scratchExprReads(p.en)
    case st: Stop => scratchExprReads(st.en)
    case mw: essent.ir.MemWrite => scratchExprReads(mw.wrEn) ++ scratchExprReads(mw.wrMask) ++
      scratchExprReads(mw.wrAddr) ++ scratchExprReads(mw.wrData)
    case lt: essent.ir.LookupTable => scratchExprReads(lt.indexExpr)
    case _ => Seq.empty
  }

  /** Logical scratch names touched by one scheduled template. Original comb
    * reads cover both the full and quiet images: specialization only replaces
    * reads with constants or removes dead statements. Role-specific reads are
    * explicit because their statements are synthetic EmptyStmt nodes. */
  private def scratchNodeAccesses(res: Result, tid: Int): (Seq[String], Seq[String]) = {
    val n = res.nodes(tid)
    if (n.produces.exists(condHoldWdataAliases.contains)) return (Seq.empty, Seq.empty)
    val defs = n.role match {
      case RComb | REffect if n.stmt == EmptyStmt => Seq.empty
      case _ => n.produces.toSeq
    }
    val reads = n.role match {
      case RComb | REffect => scratchStmtReads(n.stmt)
      case RRegSource(r) =>
        val ri = res.regs(r)
        ri.plan match {
          case RPShift => Seq(ri.nextName)
          case RPCondHold => Seq(r + "$wen",
            condHoldWdataAliases.getOrElse(r + "$wdata", r + "$wdata"))
          case RPAffineScan => Seq(r + "$keep", r + "$add")
          case RPSerialNext(folded, guarded) =>
            scratchExprReads(folded) ++ (if (guarded) Seq(r + "$gwen") else Seq.empty)
          case RPOracle => Seq.empty
        }
      case RRegCommit(r) => Seq(res.regs(r).nextName)
      case RStateRead(a) =>
        scratchStmtReads(n.stmt) ++
          scratchStmtReads(res.nodes(res.stateArrays(a).commitId).stmt)
      case RStateCommit(_) => scratchStmtReads(n.stmt)
      case ROracleInject(_) => Seq.empty
      case RVerify(r) if res.regs.contains(r) => Seq(res.regs(r).nextName, r)
      case RVerify(r) => Seq(r + "$rtl", r)
    }
    (defs, reads)
  }

  /** A dry emission trace. Every entry is one actual emitted loop, serial
    * chain, lane statement, or guard reduction. Treating every logical value
    * in a block as mutually live deliberately forgoes in-loop slot reuse. */
  private final class ScratchBlockTrace(val label: String, res: Result,
      canonicalToBase: Map[String, String]) {
    private val recorded = ArrayBuffer[ScratchBlock]()

    private def bases(names: Iterable[String]): Set[String] =
      names.iterator.flatMap(canonicalToBase.get).toSet

    def recordTids(tids: Seq[Int]): Unit = {
      val accesses = tids.map(t => scratchNodeAccesses(res, t))
      recorded += ScratchBlock(
        bases(accesses.iterator.flatMap(_._1).toSeq),
        bases(accesses.iterator.flatMap(_._2).toSeq))
    }

    def recordGuard(tier: ColdGuard.Tier): Unit = recorded += ScratchBlock(Set.empty,
      bases(tier.guards.iterator.flatMap { g =>
        g.name.toSeq ++ g.pred.toSeq.flatMap(scratchExprReads)
      }.toSeq))

    def blocks: Vector[ScratchBlock] = recorded.toVector
  }

  private def scratchTypeKey(value: ScratchValue): (String, String, Int) =
    (value.tpe.serialize, genCppType(value.tpe), value.lanes)

  /** Color the union of per-kernel interval graphs. Split forward/reverse
    * traces remain separate timelines, but a shared color must be legal in
    * both because outlined helpers use one global Renamer mapping. */
  private def colorScratch(values: Vector[ScratchValue], traces: Seq[ScratchBlockTrace],
      W: Int): ScratchReusePlan = {
    val traceBlocks = traces.map(t => t.label -> t.blocks)
    val intervals = traceBlocks.map { case (_, blocks) =>
      val ranges = mutable.Map[String, (Int, Int)]()
      for ((block, i) <- blocks.zipWithIndex; base <- block.touches) {
        val (first, _) = ranges.getOrElse(base, (i, i))
        ranges(base) = first -> i
      }
      ranges.toMap
    }
    val seen = intervals.iterator.flatMap(_.keysIterator).toSet
    val unseen = values.filterNot(v => seen.contains(v.base))
    val liveIn = mutable.Set[String]()
    for ((_, blocks) <- traceBlocks) {
      val touched = mutable.Set[String]()
      for (block <- blocks; base <- block.touches if touched.add(base))
        if (!block.defs.contains(base)) liveIn += base
    }
    val conservative = unseen.iterator.map(_.base).toSet ++ liveIn
    val orderedTypes = values.map(v => scratchTypeKey(v)).distinct
    val typeIds = orderedTypes.zipWithIndex.toMap
    val allocationValues = values.map { value =>
      val lifetimes = intervals.map(_.get(value.base).map { case (first, last) =>
        ScratchSlotAllocator.Interval(first, last)
      }).toVector
      ScratchSlotAllocator.Value(typeIds(scratchTypeKey(value)), value.order,
        lifetimes, conservative.contains(value.base))
    }
    val assignment = ScratchSlotAllocator.allocate(allocationValues)
    val colors = values.indices.iterator.map(i => values(i).base -> assignment(i)).toMap

    val slots = ArrayBuffer[ScratchSlot]()
    val slotBase = mutable.Map[String, String]()
    for ((key, typeId) <- orderedTypes.zipWithIndex) {
      val group = values.filter(v => scratchTypeKey(v) == key)
      val count = group.map(v => colors(v.base)).maxOption.getOrElse(-1) + 1
      for (color <- 0 until count) {
        val base = s"_v2_sc_t${typeId}_$color"
        slots += ScratchSlot(base, group.head.tpe, group.head.lanes)
      }
      group.foreach(v => slotBase(v.base) = s"_v2_sc_t${typeId}_${colors(v.base)}")
    }

    val overrides = values.iterator.flatMap { v =>
      v.names.iterator.map(_ -> slotBase(v.base))
    }.toMap
    val oldBytes = values.map(v => scratchArrayBytes(v.tpe, v.lanes)).sum
    val newBytes = slots.map(s => scratchArrayBytes(s.tpe, s.lanes)).sum
    ScratchReusePlan(overrides, slots.toVector, values.size, oldBytes, newBytes, unseen.size,
      liveIn.size, traceBlocks.map { case (name, blocks) => name -> blocks.size })
  }

  private def buildScratchReusePlan(res: Result, W: Int, fuseCap: Int,
      mergeEval: Boolean, hasZipper: Boolean, cold: Option[ColdGuard.Spec])
      (implicit rn: Renamer, ctx: essent.EmitContext): ScratchReusePlan = {
    val values = scratchValues(res)
    val canonicalToBase = values.iterator.flatMap(v => v.names.map(_ -> v.base)).toMap
    val sink = ScratchDiscardWriter
    val verifyOutline = new VerifyOutlineRegistry(enabled = true)
    val coldCombOutline = new ColdCombOutlineRegistry(enabled = true)
    val coldCommitOutline = new ColdCommitOutlineRegistry(enabled = true)
    val traces = ArrayBuffer[ScratchBlockTrace]()

    if (!mergeEval || hasZipper) {
      val fwd = new ScratchBlockTrace("forward", res, canonicalToBase)
      emitEvalFunctionZc(res, W, "_v2_scratch_plan_forward", res.scheduleFwd, +1, fuseCap,
        cold, coldCombOutline, coldCommitOutline, verifyOutline, 0, sink, Some(fwd))
      traces += fwd
      val rev = new ScratchBlockTrace("reverse", res, canonicalToBase)
      emitEvalFunctionZc(res, W, "_v2_scratch_plan_reverse", res.scheduleRev, -1, fuseCap,
        cold, coldCombOutline, coldCommitOutline, verifyOutline, 0, sink, Some(rev))
      traces += rev
    } else {
      val merged = new ScratchBlockTrace("merged", res, canonicalToBase)
      emitMergedEval(res, W, fuseCap, cold, coldCombOutline, coldCommitOutline,
        verifyOutline, sink, Some(merged))
      traces += merged
    }
    colorScratch(values, traces.toSeq, W)
  }

  private def emitTopScratchMembers(res: Result, W: Int, reuse: Option[ScratchReusePlan], w: Writer)
      (implicit rn: Renamer): Unit = {
    val scratch = reuse.map(_.slots.map(s => (s.base, s.tpe, s.lanes)))
      .getOrElse(scratchValues(res).map(s => (s.base, s.tpe, s.lanes)))
    if (scratch.nonEmpty) {
      w.writeLines(0, "")
      val countDesc = if (reuse.isDefined) s"${scratch.size} typed slots" else s"${scratch.size} arrays"
      w.writeLines(1, s"// v2 produced-local scratch, hoisted out of eval stack ($countDesc).")
      for ((base, tpe, lanes) <- scratch)
        w.writeLines(1, s"alignas(${laneAlign(tpe, lanes)}) ${genCppType(tpe)} $base[$lanes];")
    }
  }

  private def lutTableName(lt: essent.ir.LookupTable): String =
    s"_lut_${lt.name.replace('.', '$')}"

  /** Every LookupTable of the design as ONE file-scope constant array, in the
    * narrowest unsigned type that holds its entries (bitmaps stay packed
    * uint64 words). Emitted before the struct so every lane, direction, cold
    * group and cshare body indexes the same object: AES's 48 S-box / GF(2^8)
    * tables then occupy 12 KB (L1-resident) instead of 565 block-scope copies. */
  private def emitLookupTables(res: Result, w: Writer): Unit = {
    val seen = mutable.LinkedHashSet[String]()
    val lines = mutable.ArrayBuffer[String]()
    for (n <- res.nodes) n.stmt match {
      case lt: essent.ir.LookupTable if seen.add(lt.name) =>
        val name = lutTableName(lt)
        if (lt.bitmap) {
          lines += s"alignas(64) static const uint64_t $name[] = {${lt.entries.map(e => s"0x${e.toString(16)}ULL").mkString(", ")}};"
        } else {
          val max = if (lt.entries.isEmpty) BigInt(0) else lt.entries.max
          val (tpe, suffix) =
            if (max <= 0xff) ("uint8_t", "U") else if (max <= 0xffff) ("uint16_t", "U")
            else if (max <= 0xffffffffL) ("uint32_t", "U") else ("uint64_t", "ULL")
          lines += s"alignas(64) static const $tpe $name[] = {${lt.entries.map(e => s"0x${e.toString(16)}$suffix").mkString(", ")}};"
        }
      case _ =>
    }
    if (lines.nonEmpty) {
      w.writeLines(0, "")
      w.writeLines(0, s"// v2 lookup tables (${lines.size}), file-scope constants shared by every lane and direction.")
      lines.foreach(l => w.writeLines(0, l))
    }
  }

  private def emitStaticScratchArrays(res: Result, W: Int, reuse: Option[ScratchReusePlan], w: Writer)
      (implicit rn: Renamer): Unit = {
    val scratch = reuse.map(_.slots.map(s => (s.base, s.tpe, s.lanes)))
      .getOrElse(scratchValues(res).map(s => (s.base, s.tpe, s.lanes)))
    if (scratch.nonEmpty) {
      w.writeLines(0, "")
      val countDesc = if (reuse.isDefined) s"${scratch.size} typed slots" else s"${scratch.size} arrays"
      w.writeLines(0, s"// v2 produced-local scratch, file-scope static ($countDesc).")
      w.writeLines(0, "// Not per-Top-instance; eval overwrites scratch before use.")
      for ((base, tpe, lanes) <- scratch)
        w.writeLines(0, s"alignas(${laneAlign(tpe, lanes)}) static ${genCppType(tpe)} $base[$lanes];")
      reuse.foreach { plan =>
        for (value <- scratchValues(res)) {
          val slot = plan.overrides(value.names.head)
          w.writeLines(0, s"static ${genCppType(value.tpe)} (&${value.base})[${value.lanes}] = $slot;")
        }
      }
    }
  }

  // ------------------------------------------------------------------
  // Eval body
  // ------------------------------------------------------------------
  /** Fusion category of a full-width vector unit: units of the same category
    * that are adjacent in the schedule share one lane loop (they are mutually
    * independent by construction — comb units at the same lane, sources of
    * distinct registers, commits of distinct registers, etc.). */
  private sealed trait FuseCat
  private case object CComb extends FuseCat
  private case object CBoundaryComb extends FuseCat
  // Perf: printf/assert side effects get their own category instead of fusing
  // into CComb. A call or a shared scalar store (assert_triggered) inside a
  // lane loop makes the whole loop unvectorizable — one fused REffect
  // statement used to poison an entire 18-template [vec comb] loop. Splitting
  // only cuts a fused run at the effect's exact schedule slot, so statement
  // execution order is unchanged. Printf INTERLEAVING can shift at lane
  // granularity: effects that used to share one fused loop with interleaving
  // comb statements now print batched per effect group rather than
  // round-robin within a single loop (per-cycle content is identical).
  // Contract with ColdGuard: effect statements are ALWAYS emitted in their
  // original form with no quiet/loud dispatch, so ColdGuard must not
  // quiet-specialize them and must root quiet-window liveness on their
  // original read sets (see the RComb-only guard in ColdGuard.runCore).
  private case object CEffect extends FuseCat
  private case object CSource extends FuseCat
  private case object CCommit extends FuseCat
  private case object CStateRead extends FuseCat
  private case object CStateCommit extends FuseCat
  private case object COracle extends FuseCat      // register inject (boundary-lane semantics)
  private case object CVerify extends FuseCat      // register verify (W-1 in-window lanes + boundary carry)
  private case object CCombOracle extends FuseCat  // comb inject (all lanes, same-cycle index)
  private case object CCombVerify extends FuseCat  // comb verify (all lanes, same-cycle index)

  private sealed trait VerifyOutlineKind
  private case object VRegVerify extends VerifyOutlineKind
  private case object VRegQuietHoldVerify extends VerifyOutlineKind
  private case object VCombVerify extends VerifyOutlineKind
  private case class VerifyOutlineGroup(kind: VerifyOutlineKind, fields: Vector[String])

  /** Stable group ids shared by forward/reverse emission. The emitted helper
    * uses one switch case per distinct fused verify group; singleton UVec and
    * ULane fallback units register one-field groups through the same path. */
  private final class VerifyOutlineRegistry(val enabled: Boolean) {
    private val ids = mutable.LinkedHashMap[VerifyOutlineGroup, Int]()

    def register(kind: VerifyOutlineKind, fields: Seq[String]): Int = {
      require(enabled, "verify outline group registered while outlining is disabled")
      val group = VerifyOutlineGroup(kind, fields.toVector)
      ids.getOrElseUpdate(group, ids.size)
    }

    def groups: Seq[(VerifyOutlineGroup, Int)] = ids.toSeq
  }

  /** Window-boundary verification of register oracles.
    *
    * The in-window verify groups compare next[k] with the injected value of
    * lane k+1 (forward) or k-1 (reverse), so the last simulated cycle of a
    * sweep (lane W-1 forward, lane 0 reverse) has no partner inside the
    * window: its RTL next-state is the state of the first cycle of the
    * FOLLOWING sweep, which that sweep injects from the stream before any
    * reader runs. Without a boundary check the RTL's update of every oracled
    * register in that cycle was never compared: a wrong result was silently
    * overwritten by the next injection (one unchecked cycle per W).
    *
    * Mechanism: every verify site stores the boundary lane's next-state into
    * a scalar member (`_v2_bcarry_<reg>`, the "carry"); the following sweep
    * compares the carry with the stream element it is about to inject into
    * its boundary lane -- element 0 of the new block after a reverse sweep,
    * the mirrored element of the same block after a forward sweep. The
    * carry is valid only when the previous sweep ran with checks enabled
    * (`oracle_boundary_valid`, maintained at the end of every sweep), so the
    * first window after reset and windows after a suppressed half are
    * skipped exactly like the in-window checks. Groups are keyed by the
    * register set of an eval body so partition bodies rescan only their own
    * carries. */
  private final class BoundaryVerifyRegistry {
    private val ids = mutable.LinkedHashMap[Vector[String], Int]()
    def register(fields: Seq[String]): Int = ids.getOrElseUpdate(fields.toVector, ids.size)
    def groups: Seq[(Vector[String], Int)] = ids.toSeq
  }
  private var boundaryVerify = new BoundaryVerifyRegistry

  private def boundaryCarryName(r: String): String =
    "_v2_bcarry_" + r.map(c => if (c.isLetterOrDigit) c else '_')

  /** Lane holding the sweep's last simulated cycle, whose next-state is carried. */
  private def boundaryCarryLane(W: Int, dir: Int): String = if (dir > 0) (W - 1).toString else "0"

  /** In-block stream element that a sweep in direction `dir` injects into its
    * boundary lane: forward lane 0 reads element 0; reverse lane W-1 reads
    * the first chronological element of the second half (mirrored or not). */
  private def boundaryStreamIdx(W: Int, dir: Int): String =
    if (dir > 0) "0" else (if (premirror) 2 * W - 1 else W).toString

  /** Registers whose verify template is in this schedule (partition bodies
    * see a subset). Schedule order keeps group ids stable across directions. */
  private def boundaryVerifyRegs(res: Result, schedule: Seq[SchedUnit]): Seq[String] =
    schedule.iterator.map(_.tid).toSeq.distinct.flatMap(t => res.nodes(t).role match {
      case RVerify(r) if res.regs.contains(r) => Some(r)
      case _ => None
    })

  /** `carry = <from>[boundary lane]`: `from` is the RTL next-state array on
    * the loud path and the register itself under a proven quiet identity. */
  private def boundaryCarryStoreStr(r: RegInfo, from: String, W: Int, dir: Int)
      (implicit rn: Renamer): String =
    s"${boundaryCarryName(r.name)} = ${rn.emitForLane(from, boundaryCarryLane(W, dir))};"

  private def wideAccTarget: String = if (verifyWideAcc) "_v2_vacc" else "_v2_vacc8"

  /** Hot-path boundary check at the start of a sweep: accumulate carry vs.
    * stream-element differences per storage tier (same accumulators as the
    * in-window groups), rescan cold on any difference. */
  private def emitBoundaryVerifyBlock(res: Result, W: Int, regs: Seq[String], dir: Int,
      w: Writer, indent: Int = 2): Unit = {
    if (regs.isEmpty) return
    val groupId = boundaryVerify.register(regs)
    val byName = res.oracles.groupBy(_.flatName)
    val widths = regs.map(r => firrtl.bitWidth(res.regs(r).tpe).toInt)
    val idx = boundaryStreamIdx(W, dir)
    w.writeLines(indent, s"// [boundary-verify] ${regs.size} register oracles: previous sweep's " +
      s"last-lane next-state vs this sweep's boundary injection (group $groupId)")
    w.writeLines(indent, "#if ESSENT_ORACLE_VERIFY")
    w.writeLines(indent, "if (done_reset && checks_enabled && update_registers && oracle_boundary_valid) {")
    vaccDecls(widths).foreach(w.writeLines(indent + 1, _))
    for (r <- regs; ri = res.regs(r); spec <- byName.getOrElse(r, Seq.empty)) {
      val stream = v4StreamExpr(spec.arraySymbol)
      if (spec.words > 1)
        w.writeLines(indent + 1, s"$wideAccTarget |= (uint8_t)(${boundaryCarryName(r)}.val[${spec.word}] " +
          s"!= (uint64_t)ESSENT_ORACLE_LOAD($stream, $idx));")
      else
        w.writeLines(indent + 1, accumAssign(boundaryCarryName(r),
          s"${genCppType(ri.tpe)}(ESSENT_ORACLE_LOAD($stream, $idx))", firrtl.bitWidth(ri.tpe).toInt))
    }
    w.writeLines(indent + 1, s"if (UNLIKELY(${vaccTestExpr(widths)})) _v2_verify_boundary_rescan($groupId, ${dir > 0});")
    w.writeLines(indent, "}")
    w.writeLines(indent, "#endif")
  }

  /** Cold exact rescan and report for the boundary check, one switch case per
    * distinct register set. Range guards follow verifyLinesAtStr: record 0 is
    * the pre-loop phantom and records past ORACLE_NUM_CYCLES are padding. */
  private def emitBoundaryVerifyHelper(res: Result, W: Int, w: Writer): Unit = {
    if (boundaryVerify.groups.isEmpty) return
    val byName = res.oracles.groupBy(_.flatName)
    w.writeLines(1, "#if ESSENT_ORACLE_VERIFY")
    w.writeLines(1, "ESSENT_COLD_NOINLINE void _v2_verify_boundary_rescan(int _v2_group, bool _forward) {")
    w.writeLines(2, s"const int _v2_lane = _forward ? 0 : ${W - 1};  // lane of the previous sweep that produced the value")
    w.writeLines(2, s"const int _v2_idx = _forward ? 0 : ${if (premirror) 2 * W - 1 else W};")
    w.writeLines(2, s"const int _v2_cycle_idx = oracle_cycle + (_forward ? 0 : $W);")
    w.writeLines(2, "if (_v2_cycle_idx - 1 < 1 || _v2_cycle_idx >= ORACLE_NUM_CYCLES) return;")
    w.writeLines(2, "switch (_v2_group) {")
    for ((regs, id) <- boundaryVerify.groups) {
      w.writeLines(3, s"case $id: {")
      for (r <- regs; ri = res.regs(r); spec <- byName.getOrElse(r, Seq.empty)) {
        val carry = boundaryCarryName(r)
        val stream = v4StreamExpr(spec.arraySymbol)
        if (spec.words > 1) {
          w.writeLines(4, s"if ($carry.val[${spec.word}] != (uint64_t)ESSENT_ORACLE_LOAD($stream, _v2_idx)) {")
          w.writeLines(5, s"if (oracle_mismatch_should_log()) fprintf(stderr, \"ORACLE MISMATCH reg=${ri.name} word=${spec.word} lane=%d cyc=%d rtl=0x%\" PRIx64 \" oracle=0x%\" PRIx64 \" [window-boundary]\\n\", _v2_lane, _v2_cycle_idx, (uint64_t)$carry.val[${spec.word}], (uint64_t)ESSENT_ORACLE_LOAD($stream, _v2_idx));")
          w.writeLines(5, "record_oracle_mismatch();")
          w.writeLines(4, "}")
        } else {
          val tpe = genCppType(ri.tpe)
          w.writeLines(4, s"{ const $tpe _v2_oracle = $tpe(ESSENT_ORACLE_LOAD($stream, _v2_idx));")
          w.writeLines(4, s"if (!($carry == _v2_oracle)) {")
          w.writeLines(5, s"if (oracle_mismatch_should_log()) fprintf(stderr, \"ORACLE MISMATCH reg=${ri.name} lane=%d cyc=%d rtl=0x%\" PRIx64 \" oracle=0x%\" PRIx64 \" [window-boundary]\\n\", _v2_lane, _v2_cycle_idx, essent_to_u64($carry), essent_to_u64(_v2_oracle));")
          w.writeLines(5, "record_oracle_mismatch();")
          w.writeLines(4, "} }")
        }
      }
      w.writeLines(4, "break;")
      w.writeLines(3, "}")
    }
    w.writeLines(3, "default: break;")
    w.writeLines(2, "}")
    w.writeLines(1, "}")
    w.writeLines(1, "#endif")
    w.writeLines(0, "")
  }

  private case class ColdCombOutlineGroup(tids: Vector[Int])

  /** Stable full-image ids shared by forward/reverse cold comb dispatches.
    * The helper can only see hoisted scratch; eval-local scratch keeps the
    * original inline body. */
  private final class ColdCombOutlineRegistry(val enabled: Boolean) {
    private val ids = mutable.LinkedHashMap[ColdCombOutlineGroup, Int]()

    def register(tids: Seq[Int]): Int = {
      require(enabled, "cold comb outline group registered while outlining is disabled")
      val group = ColdCombOutlineGroup(tids.toVector)
      ids.getOrElseUpdate(group, ids.size)
    }

    def groups: Seq[(ColdCombOutlineGroup, Int)] = ids.toSeq
  }

  private case class ColdCommitOutlineGroup(tids: Vector[Int])

  private final class ColdCommitOutlineRegistry(val enabled: Boolean) {
    private val ids = mutable.LinkedHashMap[ColdCommitOutlineGroup, Int]()

    def register(tids: Seq[Int]): Int = {
      require(enabled, "cold commit outline group registered while outlining is disabled")
      val group = ColdCommitOutlineGroup(tids.toVector)
      ids.getOrElseUpdate(group, ids.size)
    }

    def groups: Seq[(ColdCommitOutlineGroup, Int)] = ids.toSeq
  }

  private def catName(c: FuseCat): String = c match {
    case CComb => "comb"
    case CBoundaryComb => "boundary-next"
    case CEffect => "effect"
    case CSource => "reg-source"
    case CCommit => "commit"
    case CStateRead => "state-read"
    case CStateCommit => "state-commit"
    case COracle => "oracle-inject"
    case CVerify => "oracle-verify"
    case CCombOracle => "comb-inject"
    case CCombVerify => "comb-verify"
  }

  /** Per-eval emission state for cumulative cold-guard images. Both the split
    * and merged kernels use this planner so readiness cuts and stage selection
    * cannot drift apart. */
  private final case class GuardEmitState(tier: ColdGuard.Tier, flag: String,
      parentFlag: Option[String], pending: mutable.Set[Int], var on: Boolean)

  private final class ColdEmitPlan(cold: Option[ColdGuard.Spec], W: Int, w: Writer,
      scratchTrace: Option[ScratchBlockTrace] = None)
      (implicit rn: Renamer, ctx: essent.EmitContext) {
    private val states: Seq[GuardEmitState] = cold.toSeq.flatMap { spec =>
      val base = GuardEmitState(spec.base, "_v2_quiet_base", None,
        mutable.Set[Int]() ++ spec.base.readyTids, on = false)
      val extra = spec.extra.map(t => GuardEmitState(t, "_v2_quiet_extra",
        Some(base.flag), mutable.Set[Int]() ++ t.readyTids, on = false))
      base +: extra.toSeq
    }

    def start(): Unit = {
      for (s <- states) w.writeLines(2, s"bool ${s.flag} = false;")
      progress(Seq.empty)
    }

    def progress(done: Iterable[Int]): Unit = {
      states.foreach(_.pending --= done)
      var parentOn = true
      for (s <- states) {
        if (!s.on && parentOn && s.pending.isEmpty) {
          scratchTrace.foreach(_.recordGuard(s.tier))
          emitColdGuardReduce(W, s.tier, s.flag, s.parentFlag, w)
          s.on = true
        }
        parentOn = s.on
      }
    }

    def base: Option[GuardEmitState] = states.headOption.filter(_.on)

    def comb(tids: Seq[Int]): Option[GuardEmitState] = {
      val ready = states.filter(_.on)
      // Once the base image has removed a producer, a later window with
      // base=true but extra=false cannot safely return to the original image.
      ready.headOption.filter(s => tids.exists(s.tier.touches))
        .orElse(ready.reverseIterator.find(s => tids.exists(s.tier.touches)))
    }

    def endsAt(tid: Int): Boolean =
      states.exists(s => !s.on && s.pending.contains(tid))

    /** Split adjacent independent comb templates only when their quiet image
      * differs. Order is preserved, including the conservative effect chain. */
    def stageRuns(isComb: Boolean, tids: Seq[Int]): Seq[Seq[Int]] = {
      if (!isComb) return Seq(tids)
      val ready = states.filter(_.on)
      def stateOf(t: Int): Option[GuardEmitState] =
        ready.headOption.filter(_.tier.touches(t))
          .orElse(ready.reverseIterator.find(_.tier.touches(t)))
      def key(t: Int): String = stateOf(t).map(_.flag).getOrElse("plain")

      // The fine-grained form below minimizes duplicated source text, but a
      // sparse quiet cone can turn one hardware-unit guard into hundreds of
      // tiny host branches.  For the full-chip experiment, allow one raw
      // fused comb group to become the dispatch unit: unchanged templates in
      // the group are emitted in both images, while the hot image still drops
      // dead templates and specializes boundary consumers.  A raw group that
      // touches two cumulative guard tiers retains the exact split form.
      val coalesceRaw = envBool("V2_COLD_GUARD_COALESCE_RAW", default = false)
      val touchedFlags = tids.iterator.flatMap(t => stateOf(t).map(_.flag)).toSet
      if (coalesceRaw && touchedFlags.size <= 1) return Seq(tids)

      val out = ArrayBuffer[ArrayBuffer[Int]]()
      var last = ""
      for (t <- tids) {
        val k = key(t)
        if (out.isEmpty || k != last) out += ArrayBuffer[Int]()
        out.last += t
        last = k
      }
      out.map(_.toSeq).toSeq
    }
  }

  /** Use the existing directional emitter as the source of both schedules.
    * Only complete blocks with identical emitted code are shared. Directional
    * regions retain their own lane order, including multi-template SCCs and
    * state-array accesses. Chunk boundaries retain the existing fusion scope. */
  private def emitSharedEval(res: Result, W: Int, fuseCap: Int,
      cold: Option[ColdGuard.Spec], coldCombOutline: ColdCombOutlineRegistry,
      coldCommitOutline: ColdCommitOutlineRegistry,
      verifyOutline: VerifyOutlineRegistry, chunkWeight: Int, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    val forward = new SharedEval.Capture
    val reverse = new SharedEval.Capture
    // Sharing the surrounding eval removes the need for individual comb
    // helpers. Keep their bodies in the chunk so LLVM can reuse registers
    // and eliminate loads across adjacent groups.
    val savedCapture = capturingSharedEval
    capturingSharedEval = true
    try {
      emitEvalFunctionZc(res, W, "eval_forward", res.scheduleFwd, +1, fuseCap,
        cold, coldCombOutline, coldCommitOutline, verifyOutline, 0, forward,
        capture = Some(forward))
      emitEvalFunctionZc(res, W, "eval_reverse", res.scheduleRev, -1, fuseCap,
        cold, coldCombOutline, coldCommitOutline, verifyOutline, 0, reverse,
        capture = Some(reverse))
    } finally capturingSharedEval = savedCapture
    require(SharedEval.Block("prefix", 0, forward.prefix).code ==
      SharedEval.Block("prefix", 0, reverse.prefix).code,
      "shared eval requires identical directional local declarations")
    val parts = SharedEval.align(forward.blocks, reverse.blocks, chunkWeight)
    if (!sys.env.get("V2_SHARED_EVAL").contains("merged")) {
      emitSharedCombRegions(W, cold, forward, reverse, parts, chunkWeight, w)
      return
    }
    w.writeLines(1, "ESSENT_NOINLINE void eval_shared(bool _forward, bool update_registers, bool verbose, bool done_reset) {")
    w.write(forward.prefix)
    var weight = 0
    var chunks = 0
    var open = false
    for (part <- parts) {
      if (open && weight + part.weight > chunkWeight) {
        w.writeLines(2, "}();"); open = false
      }
      if (!open) {
        w.writeLines(2, s"// [v2 shared eval chunk $chunks]")
        w.writeLines(2, "[&]() ESSENT_NOINLINE {")
        zcRescanDecls(W).foreach(w.writeLines(3, _))
        open = true; weight = 0; chunks += 1
      }
      if (part.shared) part.forward.foreach(b => w.write(b.text))
      else {
        w.writeLines(2, "if (_forward) {")
        part.forward.foreach(b => w.write(b.text))
        w.writeLines(2, "} else {")
        part.reverse.foreach(b => w.write(b.text))
        w.writeLines(2, "}")
      }
      weight += part.weight
    }
    if (open) w.writeLines(2, "}();")
    w.writeLines(2, "if (_forward) {")
    w.write(forward.suffix)
    w.writeLines(2, "} else {")
    w.write(reverse.suffix)
    w.writeLines(2, "}")
    w.writeLines(1, "}")
    for ((name, direction) <- Seq("eval_forward" -> "true", "eval_reverse" -> "false")) {
      w.writeLines(1, s"void $name(bool update_registers, bool verbose, bool done_reset) {")
      w.writeLines(2, s"eval_shared($direction, update_registers, verbose, done_reset);")
      w.writeLines(1, "}")
    }
    w.writeLines(1, "void eval(bool update_registers, bool verbose, bool done_reset) {")
    w.writeLines(2, "eval_shared(true, update_registers, verbose, done_reset);")
    w.writeLines(2, "eval_shared(false, update_registers, verbose, done_reset);")
    w.writeLines(1, "}")
    val shared = parts.filter(_.shared).flatMap(_.forward)
    println(s"[v2] shared eval: ${shared.size} shared blocks, " +
      s"${shared.map(_.text.length.toLong).sum} source bytes shared, $chunks chunks")
  }

  /** Keep directional control in separate callers and share only contiguous
    * comb regions. This avoids a direction branch at every common-code join,
    * while retaining fusion across small comb groups within each region. */
  private def emitSharedCombRegions(W: Int, cold: Option[ColdGuard.Spec],
      forward: SharedEval.Capture, reverse: SharedEval.Capture,
      parts: Vector[SharedEval.Part], chunkWeight: Int, w: Writer): Unit = {
    val minWeight = sys.env.get("V2_SHARED_REGION_MIN_WEIGHT").flatMap(_.toIntOption).getOrElse(128)
    val regions = ArrayBuffer[Vector[SharedEval.Block]]()
    val pending = ArrayBuffer[SharedEval.Block]()
    var pendingWeight = 0
    def flush(): Unit = {
      if (pending.nonEmpty && (pendingWeight >= minWeight ||
          pending.iterator.map(b => sharedCombBodySize(b.text)).sum >= sharedCombMinChars))
        regions += pending.toVector
      pending.clear(); pendingWeight = 0
    }
    for (part <- parts) {
      val comb = part.shared && part.forward.forall(b =>
        b.key.startsWith("vec:comb:") || b.key.startsWith("vec:boundary-next:"))
      if (comb) {
        if (pending.nonEmpty && pendingWeight + part.weight > chunkWeight) flush()
        pending ++= part.forward; pendingWeight += part.weight
      } else flush()
    }
    flush()
    val starts = regions.zipWithIndex.map { case (blocks, id) => blocks.head.key -> (blocks, id) }.toMap
    val flags = cold.toSeq.flatMap(s => Seq("_v2_quiet_base") ++
      s.extra.toSeq.map(_ => "_v2_quiet_extra"))
    val flagArgs = flags.map(", " + _).mkString
    val flagParams = flags.map(", bool& " + _).mkString
    w.writeLines(1, s"// [v2 shared-comb-regions] ${regions.size} helpers")

    for ((name, dir, capture) <- Seq(("eval_forward", +1, forward), ("eval_reverse", -1, reverse))) {
      w.writeLines(1, s"void $name(bool update_registers, bool verbose, bool done_reset) {")
      w.write(capture.prefix)
      var at = 0
      var weight = 0
      var open = false
      def before(cost: Int): Unit = {
        if (open && weight + cost > chunkWeight) { w.writeLines(2, "}();"); open = false }
        if (!open) {
          w.writeLines(2, "[&]() ESSENT_NOINLINE {")
          zcLocalDecls(W, dir).foreach(w.writeLines(3, _))
          weight = 0; open = true
        }
        weight += cost
      }
      val blocks = capture.blocks
      while (at < blocks.size) {
        starts.get(blocks(at).key) match {
          case Some((region, id)) =>
            require(blocks.slice(at, at + region.size).map(_.key) == region.map(_.key),
              "shared comb region must be contiguous in both schedules")
            before(region.map(_.weight).sum)
            w.writeLines(2, s"_v2_comb_region_$id(${dir > 0}, update_registers, verbose, done_reset$flagArgs);")
            at += region.size
          case None =>
            before(blocks(at).weight)
            w.write(blocks(at).text)
            at += 1
        }
      }
      if (open) w.writeLines(2, "}();")
      w.write(capture.suffix)
      w.writeLines(1, "}")
    }
    w.writeLines(1, "void eval(bool update_registers, bool verbose, bool done_reset) {")
    w.writeLines(2, "eval_forward(update_registers, verbose, done_reset);")
    w.writeLines(2, "eval_reverse(update_registers, verbose, done_reset);")
    w.writeLines(1, "}")
    for ((blocks, id) <- regions.zipWithIndex) {
      w.writeLines(1, s"ESSENT_NOINLINE void _v2_comb_region_$id(bool _forward, bool update_registers, bool verbose, bool done_reset$flagParams) {")
      w.writeLines(2, "(void)_forward; (void)update_registers; (void)verbose; (void)done_reset;")
      zcRescanDecls(W).foreach(w.writeLines(2, _))
      blocks.foreach(b => w.write(b.text))
      w.writeLines(1, "}")
    }
    println(s"[v2] shared comb regions: ${regions.size} helpers, " +
      s"${regions.map(_.size).sum} blocks, ${regions.flatten.map(_.text.length.toLong).sum} source bytes shared")
  }

  private def emitEvalFunctionZc(res: Result, W: Int, fname: String,
      schedule: Seq[SchedUnit], dir: Int, fuseCap: Int,
      cold: Option[ColdGuard.Spec], coldCombOutline: ColdCombOutlineRegistry,
      coldCommitOutline: ColdCommitOutlineRegistry,
      verifyOutline: VerifyOutlineRegistry, evalChunkWeight: Int, w: Writer,
      scratchTrace: Option[ScratchBlockTrace] = None,
      capture: Option[SharedEval.Capture] = None)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    // Zero-copy aliases are direction-specific (fwd half vs mirrored rev
    // half); scope them to this eval body on top of any scratch overrides.
    rn.setSimdBaseOverrides(zcScratchOverrides ++ zcDirOverrides(W, dir))
    try emitEvalFunction(res, W, fname, schedule, dir, fuseCap,
      cold, coldCombOutline, coldCommitOutline, verifyOutline, evalChunkWeight, w, scratchTrace, capture)
    finally rn.setSimdBaseOverrides(zcScratchOverrides)
  }

  private def emitEvalFunction(res: Result, W: Int, fname: String,
      schedule: Seq[SchedUnit], dir: Int, fuseCap: Int,
      cold: Option[ColdGuard.Spec], coldCombOutline: ColdCombOutlineRegistry,
      coldCommitOutline: ColdCommitOutlineRegistry,
      verifyOutline: VerifyOutlineRegistry, evalChunkWeight: Int, w: Writer,
      scratchTrace: Option[ScratchBlockTrace] = None,
      capture: Option[SharedEval.Capture] = None)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    rn.resetDeclaredArrays()
    val sccSizes: Map[Int, Int] =
      res.sccOf.groupBy(_._2).map { case (k, v) => k -> v.size }
    // Experimental correctness fallback for oracle-budget ablations. When a
    // residual SCC contains both a serial register source and its per-lane
    // producers, rolling that source into one whole-width chain can read
    // producer lanes that have not run yet. Keep every source at its exact
    // schedule position when requested. Default emission is unchanged.
    val forcePerLaneSerial = envBool("V2_FORCE_PER_LANE_SERIAL", default = false)
    // Correctness, not a heuristic: whole-chain coalescing (cond-hold scan /
    // guarded chain) is only sound when every operand of every lane is a
    // full-width vector template — true for singleton serial SCCs. Inside a
    // multi-template SCC the reg's wen/wdata are themselves serialized
    // per-lane, and hoisting the whole chain to the first lane's slot reads
    // producer lanes that have not run yet (BOOM div.neg_out: the scan read
    // wen[1..2] one window stale -> the cycle-534785 x9 writeback bug).
    // A whole-chain emission is additionally unsound when the chain's own
    // expression reads ANOTHER serial-family register's read view: the hoist
    // to the first-lane slot then consumes lanes that register's scan/chain
    // has not produced yet (BOOM div: resHi's guarded chain read isHi[L-1]
    // 116 lines before isHi's cond-hold scan — the cycle-534785 x9 bug).
    def serialFamilyReg(r: String): Boolean = res.regs.get(r).exists { ri2 =>
      ri2.plan match {
        case RPCondHold | RPAffineScan | RPSerialNext(_, _) => true
        case _ => res.sccOf.contains(ri2.sourceId)
      }
    }
    def regReadsOf(e: firrtl.ir.Expression): Seq[String] = e match {
      case w: firrtl.WRef => if (res.regs.contains(w.name)) Seq(w.name) else Seq.empty
      case other =>
        val buf = Seq.newBuilder[String]
        other.foreachExpr(sub => buf ++= regReadsOf(sub))
        buf.result()
    }
    val chainOperandHazard: Map[Int, Boolean] = res.nodes.iterator.collect {
      case n if n.role.isInstanceOf[RRegSource] =>
        val r = n.role.asInstanceOf[RRegSource].reg
        val hazard = res.regs(r).plan match {
          case RPSerialNext(folded, _) =>
            regReadsOf(folded).exists(r2 => r2 != r && serialFamilyReg(r2))
          case _ => false
        }
        n.id -> hazard
    }.toMap
    def needsPerLaneSerial(tid: Int): Boolean =
      res.sccOf.get(tid).exists(scc => sccSizes.getOrElse(scc, 0) > 1) ||
      chainOperandHazard.getOrElse(tid, false) || forcePerLaneSerial
    // A group is profitable here only if at least two of its fields are safe
    // for whole-chain emission. Members inside a multi-template SCC retain
    // their exact per-lane schedule and deliberately do not consume a shared
    // index that may have been computed before their lane-local wen is ready.
    val sharedCondHoldGroups: Set[Int] =
      if (W <= 1) Set.empty
      else res.condHoldGroupOf.iterator
        .filter { case (r, _) => !needsPerLaneSerial(res.regs(r).sourceId) }
        .toSeq.groupBy(_._2).collect { case (group, members) if members.size >= 2 => group }.toSet
    val builtCondHoldGroups = mutable.Set[Int]()
    if (capture.isEmpty)
      w.writeLines(1, s"void $fname(bool update_registers, bool verbose, bool done_reset) {")
    // In the Verilator-equivalent performance build all source Print/Stop
    // effects are absent, so `verbose` has no remaining consumer.  Keep the
    // public eval ABI identical and make strict generated-binding builds
    // warning-clean in both configurations.
    w.writeLines(2, "(void)verbose;")
    // Zero-copy stream aliases as hoisted __restrict locals: one win_base
    // load per function, and the restrict qualifier keeps the vectorizer
    // from assuming stores clobber the (read-only) stream memory — emitting
    // the cast expression at every read site measured 2x slower (every
    // char-derived pointer aliased every store).
    // When eval outlining is active, redeclare these inside every chunk. This
    // preserves their block-scope __restrict information in the function that
    // LLVM actually vectorizes instead of accessing captured pointer slots.
    if (evalChunkWeight <= 0 && capture.isEmpty) zcLocalDecls(W, dir).foreach(w.writeLines(2, _))
    sharedCondHoldGroups.toSeq.sorted.foreach { group =>
      w.writeLines(2, s"int16_t ${condHoldIndexName(group)}[$W];")
    }
    w.writeLines(2, s"// [v2 schedule] ${schedule.size} units, ${sccSizes.size} serial regions " +
      s"(${res.serialTemplateCount} templates x $W lanes), ${res.oracles.size} oracle streams")

    def catOf(u: SchedUnit): Option[FuseCat] = u match {
      case UVec(t) => res.nodes(t).role match {
        case RComb            => Some(if (endpointNextTids(t)) CBoundaryComb else CComb)
        case REffect          => Some(CEffect)  // perf: keep calls/assert stores out of vector loops
        case RRegSource(_)    => Some(CSource)
        case RRegCommit(_)    => Some(CCommit)
        case RStateRead(_)    => Some(CStateRead)
        case RStateCommit(_)  => Some(CStateCommit)
        case ROracleInject(r) => Some(if (res.regs.contains(r)) COracle else CCombOracle)
        case RVerify(r)       => Some(if (res.regs.contains(r)) CVerify else CCombVerify)
      }
      case _ => None
    }

    val buf = ArrayBuffer[Int]()
    var bufCat: Option[FuseCat] = None
    val coldPlan = new ColdEmitPlan(cold, W, w, scratchTrace)
    coldPlan.start()

    /** Open/close only at semantic block boundaries. The noinline lambda is
      * a separate LLVM function but captures wrapper locals (cold flags and
      * shared cond-hold indices) by reference. Hoisted produced-value scratch
      * remains directly addressable, and invocation order is unchanged. */
    final class EvalChunks(limit: Int) {
      private var open = false
      private var weight = 0
      private var emittedChunks = 0

      private def begin(): Unit = {
        w.writeLines(2, s"// [v2 eval chunk $emittedChunks]")
        w.writeLines(2, "[&]() ESSENT_NOINLINE {")
        zcLocalDecls(W, dir).foreach(w.writeLines(3, _))
        open = true
        weight = 0
        emittedChunks += 1
      }

      private def end(): Unit = if (open) {
        w.writeLines(2, "}();")
        open = false
      }

      def beforeBlock(blockWeight: Int, key: String): Unit = {
        capture.foreach(_.beforeBlock(key, blockWeight))
        if (limit > 0) {
          require(blockWeight > 0)
          if (open && weight > 0 && weight + blockWeight > limit) end()
          if (!open) begin()
          weight += blockWeight
        }
      }

      def finish(): Unit = end()
      def count: Int = emittedChunks
    }
    val evalChunks = new EvalChunks(evalChunkWeight)

    def flushRun(): Unit = {
      if (buf.isEmpty) return
      val groups = if (fuseCap > 0) buf.toSeq.grouped(fuseCap).toSeq else Seq(buf.toSeq)
      val cat = bufCat.get
      for (raw <- groups; g <- coldPlan.stageRuns(cat == CComb, raw)) {
        // LoopRotate updates a function-wide dominator tree for every loop;
        // even 32--48 loops in one BOOM chunk remained pathological with both
        // loop and SLP vectorization disabled. Charge a large fixed weight per
        // loop (plus fused-body size), keeping the default near 6--8 loops per
        // helper while allowing many loop-free serial lane statements.
        evalChunks.beforeBlock(24 + g.size, s"vec:${catName(cat)}:${g.mkString(",")}")
        scratchTrace.foreach(_.recordTids(g))
        val stateStage = coldPlan.base
        val combStage = if (cat == CComb) coldPlan.comb(g) else None
        def holdReg(t: Int): Option[String] = res.nodes(t).role match {
          case RRegCommit(r) if stateStage.exists { stage =>
            stage.tier.quietHoldRegs.contains(r) ||
              stage.tier.quietOracleHoldRegs.contains(r)
          } => Some(r)
          case _ => None
        }
        val dualComb = combStage.isDefined
        val dualCommit = cat == CCommit && stateStage.isDefined && g.exists(t => holdReg(t).isDefined)
        val dualVerify = cat == CVerify && stateStage.exists { stage =>
          g.exists(t => res.nodes(t).role match {
            case RVerify(r) => stage.tier.quietOracleHoldRegs.contains(r)
            case _ => false
          })
        }
        if (dualComb) {
          val stage = combStage.get
          emitColdDualCombGroup(res, W, g, stage.tier, stage.flag, coldCombOutline, w)
        } else if (dualCommit) {
          emitColdDualCommitGroup(res, W, g, g.filter(t => holdReg(t).isEmpty),
            stateStage.get.flag, coldCommitOutline, boundaryLaneStr(W, dir), w)
        } else if (dualVerify) {
          emitColdDualVerifyGroup(res, W, g, dir, stateStage.get.tier,
            stateStage.get.flag, verifyOutline, w)
        }
        else emitRunGroup(res, W, cat, g, dir, verifyOutline, w)
        coldPlan.progress(g)
      }
      buf.clear()
      bufCat = None
    }

    // Serial source chain, wrapped in the quiet dispatch when this register's
    // gwen is proven zero in quiet windows (broadcast arm skips the gwen
    // reduce and its arrays entirely).
    def emitSerialChain(ri: RegInfo): Unit = {
      evalChunks.beforeBlock(24, s"chain:${ri.sourceId}")
      scratchTrace.foreach(_.recordTids(Seq(ri.sourceId)))
      val stage = coldPlan.base
      val quietBcast = stage.exists(_.tier.quietZeroGwenRegs.contains(ri.name))
      if (quietBcast) {
        val quietFlag = stage.get.flag
        w.writeLines(2, s"if (UNLIKELY(!$quietFlag)) {")
        serialChainLoopStr(ri, W, dir).foreach(l => w.writeLines(3, l))
        w.writeLines(2, "} else {")
        broadcastOnlyStr(ri, W, dir).foreach(l => w.writeLines(3, l))
        w.writeLines(2, "}")
      } else {
        res.condHoldGroupOf.get(ri.name).filter(sharedCondHoldGroups).fold {
          serialChainLoopStr(ri, W, dir).foreach(l => w.writeLines(2, l))
        } { group =>
          val buildIndex = builtCondHoldGroups.add(group)
          sharedCondHoldStr(ri, W, dir, group, buildIndex)
            .foreach(l => w.writeLines(2, l))
        }
      }
      coldPlan.progress(Seq(ri.sourceId))
    }

    // Serial-region annotations: which SCC a per-lane statement belongs to,
    // which registers make it serial, and how big its comb cone is. Grep for
    // "[serial" to audit everything that did not vectorize.
    var curSerial = (-1, -1)  // (scc, lane) of the last serial unit emitted
    val seenScc = mutable.Set[Int]()  // region header printed once per function
    val chainDone = mutable.Set[Int]()

    // Window-boundary check of the previous sweep's carried next-states
    // against this sweep's boundary injection, before any verify group of
    // this sweep overwrites the carries. Own block, direction-keyed, so the
    // shared-eval pairing keeps it in the directional arms.
    val boundaryRegs = boundaryVerifyRegs(res, schedule)
    if (boundaryRegs.nonEmpty) {
      evalChunks.beforeBlock(24 + boundaryRegs.size / 8,
        s"boundary-verify:${if (dir > 0) "fwd" else "rev"}")
      emitBoundaryVerifyBlock(res, W, boundaryRegs, dir, w)
    }

    val sched = schedule.toIndexedSeq
    val lastLaneUnitAt = sched.zipWithIndex.collect {
      case (ULane(tid, _), index) => tid -> index
    }.toMap
    var i = 0
    while (i < sched.size) {
      val u = sched(i)
      catOf(u) match {
        case some @ Some(cat) =>
          if (bufCat.isDefined && bufCat != some) flushRun()
          bufCat = some
          buf += u.tid
          // End the fused group at a guard input producer so the newly ready
          // quiet image can protect the very next scheduled group.
          if (coldPlan.endsAt(u.tid)) flushRun()
          curSerial = (-1, -1)
          i += 1
        case None =>
          flushRun()
          // A full run of one source template across all lanes (singleton
          // serial SCC) rolls into a serial chain loop: same W-1 statements,
          // ~30x smaller code footprint than the unrolled form.
          val chainLen = u match {
            case ULane(t, _) if res.nodes(t).role.isInstanceOf[RRegSource] =>
              var j = i
              while (j < sched.size && (sched(j) match {
                case ULane(t2, _) => t2 == u.tid
                case _ => false
              })) j += 1
              j - i
            case _ => 0
          }
          if (chainLen == W && !needsPerLaneSerial(u.tid)) {
            if (W > 1) {
              val r = res.nodes(u.tid).role.asInstanceOf[RRegSource].reg
              val scc = res.sccOf.getOrElse(u.tid, -1)
              if (seenScc.add(scc))
                w.writeLines(2, s"// [serial scc=$scc] ${sccDesc(res, scc)}")
              w.writeLines(2, s"// [serial scc=$scc chain-loop]")
              emitSerialChain(res.regs(r))
            } else coldPlan.progress(Seq(u.tid))
            curSerial = (-1, -1)
            i += chainLen
          } else if (chainDone.contains(u.tid)) {
            curSerial = (-1, -1)
            i += 1
          } else {
            // Whole-chain emission for singleton serial registers (cond-hold
            // scan, guarded serial-next): every operand of every lane comes
            // from full-width vector templates (plus the self edge), so the
            // readiness of the first non-boundary lane implies all producers
            // are emitted and the remaining lanes can be rolled into one
            // atomic chain construct.
            def wholeChainPlan(tid: Int, plan: RegPlan): Boolean =
              !needsPerLaneSerial(tid) && (plan match {
                case RPCondHold => true
                case RPAffineScan => true
                case RPSerialNext(_, guarded) => guarded
                case _ => false
              })
            val emittedWholeCondHold = u match {
              case ULane(t, k) =>
                res.nodes(t).role match {
                  case RRegSource(r) if wholeChainPlan(t, res.regs(r).plan) =>
                    val boundary = if (dir > 0) k == 0 else k == W - 1
                    if (boundary) false
                    else {
                      val scc = res.sccOf.getOrElse(t, -1)
                      if (seenScc.add(scc))
                        w.writeLines(2, s"// [serial scc=$scc] ${sccDesc(res, scc)}")
                      w.writeLines(2, s"// [serial scc=$scc chain-loop]")
                      emitSerialChain(res.regs(r))
                      chainDone += t
                      curSerial = (-1, -1)
                      true
                    }
                  case _ => false
                }
              case _ => false
            }
            if (!emittedWholeCondHold) {
              val willEmit = u match {
                case ULane(t, k) => res.nodes(t).role match {
                  case RRegSource(_) => if (dir > 0) k != 0 else k != W - 1
                  // The boundary-lane verify unit stores the carry (emitUnit).
                  case RVerify(_)    => true
                  case _ => true
                }
                case _ => true
              }
              u match {
                case ULane(t, k) =>
                  // Boundary-lane sources emit nothing; do not annotate
                  // silent units.
                  if (willEmit) scratchTrace.foreach(_.recordTids(Seq(t)))
                  val scc = res.sccOf.getOrElse(t, -1)
                  if (willEmit && (scc, k) != curSerial) {
                    if (seenScc.add(scc))
                      w.writeLines(2, s"// [serial scc=$scc] ${sccDesc(res, scc)}")
                    w.writeLines(2, s"// [serial scc=$scc lane=$k]")
                    curSerial = (scc, k)
                  }
                case _ =>
              }
              if (willEmit) {
                val ULane(t, k) = u: @unchecked
                evalChunks.beforeBlock(1, s"lane:$t:${if (dir > 0) k else W - 1 - k}")
              }
              emitUnit(res, W, u, dir, verifyOutline, w)
              if (lastLaneUnitAt.get(u.tid).contains(i))
                coldPlan.progress(Seq(u.tid))
            }
            i += 1
          }
      }
    }
    flushRun()
    evalChunks.finish()
    capture.foreach(_.finishBody())
    if (evalChunkWeight > 0)
      println(s"[v2] eval outlining: $fname -> ${evalChunks.count} noinline chunk(s), " +
        s"target weight $evalChunkWeight each")

    // Boundary carries stored by this sweep are usable by the next one only
    // when this sweep ran its checks (see BoundaryVerifyRegistry).
    w.writeLines(2, "if (update_registers) oracle_boundary_valid = done_reset && checks_enabled;")
    if (dir > 0) {
      w.writeLines(2, "if (done_reset && checks_enabled && update_registers && assert_triggered) exit(assert_exit_code);")
      w.writeLines(2, "if (!done_reset || !checks_enabled) assert_triggered = false;")
    } else {
      w.writeLines(2, "if (done_reset && checks_enabled && update_registers && assert_triggered) exit(assert_exit_code);")
      w.writeLines(2, "if (!done_reset || !checks_enabled) assert_triggered = false;")
      w.writeLines(2, s"if (update_registers && done_reset) { oracle_cycle += ${2 * W}; oracle_win_base += ORACLE_BLOCK_BYTES; }")
    }
    if (capture.isEmpty) w.writeLines(1, "}")
    w.writeLines(0, "")
  }

  private def stateWrites(res: Result, array: String): Seq[essent.ir.MemWrite] = {
    def collect(s: Statement): Seq[essent.ir.MemWrite] = s match {
      case mw: essent.ir.MemWrite => Seq(mw)
      case b: Block => b.stmts.flatMap(collect)
      case EmptyStmt => Seq.empty
      case other => throw new IllegalStateException(
        s"[v2-state-array] commit for '$array' contains ${other.getClass.getSimpleName}, expected MemWrite")
    }
    val writes = collect(res.nodes(res.stateArrays(array).commitId).stmt)
    require(writes.size == res.stateArrays(array).writePorts,
      s"[v2-state-array] '$array' write metadata says ${res.stateArrays(array).writePorts}, found ${writes.size}")
    writes
  }

  /** A synchronous aggregate-register reset reaches FIRRTL memory form as one
    * final-priority writer per entry.  Executing those ports literally makes
    * a 128-entry indexed state lift test 128 identical `if (reset)` branches
    * per virtual cycle even after reset has been deasserted.
    *
    * Recognize only the exact compiler-owned, all-zero, full-depth suffix
    * produced by StateArrayLift/IndexedCounterStateLift.  The suffix and
    * address checks prove priority and coverage; any non-zero/masked/sparse
    * form keeps the ordinary chronological-port path.
    */
  private case class BulkZeroReset(enable: Expression, ports: Set[String])
  private case class StateWritePlan(
      all: Seq[essent.ir.MemWrite],
      ordinary: Seq[essent.ir.MemWrite],
      bulkZeroReset: Option[BulkZeroReset])

  private def stateWritePlan(res: Result, array: String): StateWritePlan = {
    val writes = stateWrites(res, array)
    val si = res.stateArrays(array)
    def resetOrdinal(name: String): Option[Int] = {
      if (!name.startsWith("reset")) None
      else {
        val suffix = name.drop("reset".length)
        if (suffix.nonEmpty && suffix.forall(_.isDigit)) Some(suffix.toInt)
        else None
      }
    }
    def literal(value: Expression): Option[BigInt] = value match {
      case UIntLiteral(number, _) => Some(number)
      case _ => None
    }

    val resetWrites = writes.flatMap(write => resetOrdinal(write.portName).map(_ -> write))
    val resetPorts = resetWrites.map(_._2.portName).toSet
    val suffixIsReset = resetWrites.size == si.depth &&
      writes.takeRight(si.depth).forall(write => resetPorts(write.portName)) &&
      writes.dropRight(si.depth).forall(write => !resetPorts(write.portName))
    val exactCoverage = resetWrites.sortBy(_._1).zipWithIndex.forall {
      case ((ordinal, write), index) =>
        ordinal == index && literal(write.wrAddr).contains(BigInt(index))
    }
    val zeroAndUnmasked = resetWrites.forall { case (_, write) =>
      literal(write.wrData).contains(BigInt(0)) &&
        literal(write.wrMask).contains(BigInt(1))
    }
    val enables = resetWrites.map(_._2.wrEn).groupBy(_.serialize)
    val bulk = if (si.compilerLifted && suffixIsReset && exactCoverage &&
        zeroAndUnmasked && enables.size == 1)
      Some(BulkZeroReset(resetWrites.head._2.wrEn, resetPorts))
    else None
    StateWritePlan(writes, bulk.map(value =>
      writes.filterNot(write => value.ports(write.portName))).getOrElse(writes), bulk)
  }

  private def stateReadParts(res: Result, tid: Int): (DefNode, Expression) =
    res.nodes(tid).stmt match {
      case d @ DefNode(_, _, WSubAccess(_, addr, _, _)) => (d, addr)
      case other => throw new IllegalStateException(
        s"[v2-state-array] read template $tid is ${other.getClass.getSimpleName}, expected DefNode(mem[addr])")
    }

  /** Exact proof key for fields stored in distinct FIRRTL memories but driven
    * by one logical queue/table access.  LowerTypes commonly turns a Queue
    * payload bundle into `ram_data`, `ram_opcode`, `ram_source`, ... .  Their
    * values have different types, but their address, enable, mask, port
    * priority, and parent instance are byte-for-byte identical.
    *
    * The key intentionally contains only access semantics, never write data.
    * Equal keys therefore permit sharing the chronological last-writer scan;
    * each field still reads and writes its own physical array.  Requiring one
    * parent path prevents unrelated memories that happen to use the same
    * top-level counter from being coalesced accidentally. */
  private case class SameAccessWrite(enable: String, mask: String, address: String)
  private case class SameAccessReadKey(
      parent: String, depth: Int, readAddress: String,
      writes: Vector[SameAccessWrite])
  private case class SameAccessCommitKey(
      parent: String, depth: Int, writes: Vector[SameAccessWrite])

  private def stateArrayParent(array: String): String = {
    val dot = array.lastIndexOf('.')
    if (dot < 0) "" else array.take(dot)
  }

  private def sameAccessWrites(plan: StateWritePlan): Vector[SameAccessWrite] =
    plan.ordinary.map(write => SameAccessWrite(
      write.wrEn.serialize, write.wrMask.serialize, write.wrAddr.serialize)).toVector

  /** Restrict the first implementation to the high-confidence Queue shape:
    * one read port per field, at least one ordinary writer, dense small state,
    * and no synthesized bulk-reset suffix.  Multi-read arrays keep the
    * existing same-array image optimization; reset tables keep their proven
    * reset-specialized path. */
  private def sameAccessReadKey(res: Result, tid: Int): Option[SameAccessReadKey] = {
    val RStateRead(array) = res.nodes(tid).role: @unchecked
    val info = res.stateArrays(array)
    val plan = stateWritePlan(res, array)
    if (info.depth > 4096 || info.readIds != Seq(tid) ||
        plan.bulkZeroReset.nonEmpty || plan.ordinary.isEmpty) None
    else {
      val (_, readAddress) = stateReadParts(res, tid)
      Some(SameAccessReadKey(stateArrayParent(array), info.depth,
        readAddress.serialize, sameAccessWrites(plan)))
    }
  }

  private def sameAccessCommitKey(
      res: Result, array: String): Option[SameAccessCommitKey] = {
    val info = res.stateArrays(array)
    val plan = stateWritePlan(res, array)
    if (info.depth > 4096 || info.readIds.size != 1 ||
        plan.bulkZeroReset.nonEmpty || plan.ordinary.isEmpty) None
    else Some(SameAccessCommitKey(stateArrayParent(array), info.depth,
      sameAccessWrites(plan)))
  }

  /** Full-width state read.  The physical array holds the pre-window image.
    * Arrays whose depth is small relative to W and their write-port count use
    * a depth-sized last-writer table advanced in chronological lane/port
    * order, reducing a port from O(W^2*P) address comparisons to
    * O(depth+W*P).  Deeper arrays use a bounded scan over only the preceding
    * writes in this SIMD window, avoiding work proportional to storage that
    * the current window cannot possibly touch.
    * Looking up before installing lane L's write preserves register old-value
    * semantics on a same-cycle read/write; repeated addresses naturally leave
    * the latest chronological writer, including deterministic write-port
    * order within one virtual cycle.
    */
  private def stateReadLoopStr(res: Result, tid: Int, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    val RStateRead(array) = res.nodes(tid).role: @unchecked
    val si = res.stateArrays(array)
    val plan = stateWritePlan(res, array)
    // The shared-image form can represent a bulk reset directly.  Reuse it
    // even for a singleton port instead of expanding the reset suffix into a
    // depth-sized last-writer switch.
    if (plan.bulkZeroReset.nonEmpty && si.depth <= 4096)
      return denseStateReadGroupStr(res, Seq(tid), W, dir)
    val writes = plan.all
    val (d, readAddr) = stateReadParts(res, tid)
    val out = rn.emitForLane(d.name, "L")
    val addrL = withLaneVar("L") { emitExpr(readAddr) }
    val laneLoop = if (dir > 0) s"for (int L = 0; L < $W; L++)"
      else s"for (int L = ${W - 1}; L >= 0; L--)"
    if (externProbe(array)) return Seq(
      s"// [extern-probe] read of '$array' stubbed (semantics-breaking ceiling probe)",
      s"$laneLoop { $out = ${genCppType(si.tpe)}(0); }")
    val dense = preferDenseLastWriter(si.depth, W, writes.size)
    val fullPath: Seq[String] = if (dense) {
      val pCount = math.max(1, writes.size)
      val branchlessDense = branchlessDenseLastWriter(Seq(si.tpe))
      val persistentRead = stateReadExpr(
        si.name, si.tpe, "_v2_sa_addr", si.depth)
      val lastWriterRead = lastWriterReadExpr(
        "_v2_sa_last", "_v2_sa_addr", si.depth)
      val loadForward = if (writes.isEmpty) Seq.empty else {
        val selectedPointer = if (envBool("V2_BRANCHLESS_FORWARD", default = false) && pCount == 1)
          forwardingDataPointer(writes.head.wrData, si.tpe, "_v2_sa_prev_lane") else None
        val cases = writes.zipWithIndex.flatMap { case (mw, p) =>
          val data = withLaneVar("_v2_sa_prev_lane") { emitExpr(mw.wrData) }
          Seq(s"        case $p: _v2_sa_value = $data; break;")
        }
        if (selectedPointer.isDefined) Seq(
          "    // [branchless-forward] select a valid source before loading data",
          s"    const int _v2_sa_prev_code = $lastWriterRead;",
          "    const bool _v2_sa_prev_valid = _v2_sa_prev_code >= 0;",
          "    [[maybe_unused]] const int _v2_sa_prev_lane = _v2_sa_prev_code & -static_cast<int>(_v2_sa_prev_valid);",
          s"    _v2_sa_value = *essent_select_ptr(_v2_sa_prev_valid, ${selectedPointer.get}, &_v2_sa_value);")
        else if (branchlessDense && pCount == 1) {
          val data = withLaneVar("_v2_sa_prev_lane") { emitExpr(writes.head.wrData) }
          Seq(
            s"    const int _v2_sa_prev_code = $lastWriterRead;",
            "    const uint64_t _v2_sa_prev_valid = " +
              "(uint64_t)(_v2_sa_prev_code >= 0);",
            "    [[maybe_unused]] const int _v2_sa_prev_lane = " +
              "_v2_sa_prev_code & -static_cast<int>(_v2_sa_prev_valid);",
            "    _v2_sa_value = essent_mux(UInt<1>(_v2_sa_prev_valid), " +
              s"$data, _v2_sa_value);")
        } else Seq(
            s"    const int _v2_sa_prev_code = $lastWriterRead;",
            "    if (_v2_sa_prev_code >= 0) {",
            // Some write-data expressions are lane-invariant after FIRRTL
            // optimization.  Keep one uniform forwarding switch while avoiding
            // -Wunused-variable failures in generated full-system headers.
            s"      [[maybe_unused]] const int _v2_sa_prev_lane = _v2_sa_prev_code / $pCount;",
            s"      switch (_v2_sa_prev_code % $pCount) {") ++ cases ++ Seq(
            "        default: __builtin_unreachable();",
            "      }",
            "    }")
      }
      val install = writes.zipWithIndex.flatMap { case (mw, p) =>
        val wen = withLaneVar("L") { emitExpr(mw.wrEn) }
        val mask = withLaneVar("L") { emitExpr(mw.wrMask) }
        val addr = withLaneVar("L") { emitExpr(mw.wrAddr) }
        if (branchlessDense) {
          val inRange = if (stateAddressCanEscape(si.depth))
            s" & (uint64_t)(_v2_sa_write_addr_$p < (uint64_t)${si.depth})"
          else ""
          Seq(
          s"    const uint64_t _v2_sa_write_addr_$p = essent_to_u64($addr);",
          s"    const uint64_t _v2_sa_write_take_$p = " +
            s"(uint64_t)(essent_to_u64($wen) != 0) & " +
            s"(uint64_t)(essent_to_u64($mask) != 0)$inRange;",
          s"    const uint64_t _v2_sa_write_mask_$p = " +
            s"(uint64_t)0 - _v2_sa_write_take_$p;",
          s"    const uint64_t _v2_sa_write_slot_$p = " +
            s"(_v2_sa_write_addr_$p & _v2_sa_write_mask_$p) | " +
            s"((uint64_t)${si.depth} & ~_v2_sa_write_mask_$p);",
          s"    _v2_sa_last[_v2_sa_write_slot_$p] = L * $pCount + $p;")
        } else {
          val inRange = if (stateAddressCanEscape(si.depth))
            s" && essent_to_u64($addr) < (uint64_t)${si.depth}"
          else ""
          Seq(
          s"    if (essent_to_u64($wen) && essent_to_u64($mask)$inRange) " +
            s"_v2_sa_last[essent_to_u64($addr)] = L * $pCount + $p;")
        }
      }
      val lastWriterSlots = si.depth + (if (branchlessDense) 1 else 0)
      Seq(
        "{",
        s"  // [state-read-dense] forwarding=${if (branchlessDense) "branchless" else "branching"}",
        s"  int _v2_sa_last[$lastWriterSlots];",
        s"  for (int _v2_sa_i = 0; _v2_sa_i < $lastWriterSlots; _v2_sa_i++) " +
          "_v2_sa_last[_v2_sa_i] = -1;",
        s"  $laneLoop {",
        s"    const uint64_t _v2_sa_addr = essent_to_u64($addrL);",
        s"    ${genCppType(si.tpe)} _v2_sa_value = $persistentRead;") ++
        loadForward ++ Seq(s"    $out = _v2_sa_value;") ++ install ++ Seq("  }", "}")
    } else {
      val jLoop = if (dir > 0) "for (int J = 0; J < L; J++)"
        else s"for (int J = ${W - 1}; J > L; J--)"
      val branchless = plan.bulkZeroReset.isEmpty &&
        branchlessSparseStateRead(Seq(si.tpe))
      val persistentRead = stateReadExpr(
        si.name, si.tpe, "_v2_sa_addr", si.depth)
      val forward = writes.zipWithIndex.flatMap { case (mw, port) =>
        val wen = withLaneVar("J") { emitExpr(mw.wrEn) }
        val mask = withLaneVar("J") { emitExpr(mw.wrMask) }
        val addr = withLaneVar("J") { emitExpr(mw.wrAddr) }
        val data = withLaneVar("J") { emitExpr(mw.wrData) }
        if (branchless) Seq(
          s"      const UInt<1> _v2_sa_take_$port = " +
            sparseMatchExpr(wen, mask, addr, "_v2_sa_addr") + ";",
          s"      _v2_sa_value = essent_mux(_v2_sa_take_$port, $data, " +
            "_v2_sa_value);")
        else Seq(
          s"      if (essent_to_u64($wen) && essent_to_u64($mask) && " +
            s"essent_to_u64($addr) == _v2_sa_addr) _v2_sa_value = $data;")
      }
      Seq(
        "{",
        s"  // [state-read-sparse] forwarding=${if (branchless) "branchless" else "branching"}",
        s"  $laneLoop {",
        s"    const uint64_t _v2_sa_addr = essent_to_u64($addrL);",
        s"    ${genCppType(si.tpe)} _v2_sa_value = $persistentRead;",
        s"    $jLoop {") ++ forward ++ Seq(
        "    }",
        s"    $out = _v2_sa_value;",
        "  }",
        "}")
    }
    val guarded = if (!stateReadAnyGuard || writes.isEmpty || plan.bulkZeroReset.nonEmpty) fullPath
    else {
      val guardTerms = writes.map { mw =>
        val wen = withLaneVar("G") { emitExpr(mw.wrEn) }
        val mask = withLaneVar("G") { emitExpr(mw.wrMask) }
        s"    _v2_sa_anyw |= (uint64_t)(essent_to_u64($wen) != 0) & " +
          s"(uint64_t)(essent_to_u64($mask) != 0);"
      }
      val fastRead = if (!stateAddressCanEscape(si.depth)) Seq(
        s"    $laneLoop { $out = ${si.name}[essent_to_u64($addrL)]; }")
      else Seq(
        s"    $laneLoop {",
        s"      const uint64_t _v2_sa_fast_addr = essent_to_u64($addrL);",
        s"      $out = ${stateReadExpr(si.name, si.tpe, "_v2_sa_fast_addr", si.depth)};",
        "    }")
      Seq(
        "{",
        "  // [state-read-any-guard]",
        "  uint64_t _v2_sa_anyw = 0;",
        s"  for (int G = 0; G < $W; G++) {") ++ guardTerms ++ Seq(
        "  }",
        "  if (_v2_sa_anyw == 0) {") ++ fastRead ++ Seq(
        "  } else {") ++ fullPath.map("  " + _) ++ Seq(
        "  }",
        "}")
    }
    externReadFence(d.name, guarded)
  }

  /** Dense full-width reads that are adjacent in the schedule and target the
    * same array share one local chronological image.  Every port observes the
    * same pre-cycle-L image, so install lane L's writes only after all of that
    * lane's reads.  The old per-port form rebuilt a depth-sized last-writer
    * table, reloaded the persistent image, and selected forwarded data for
    * every port.  BOOM's 11R LDQ/STQ address arrays consequently paid that
    * machinery 22 times per direction.  One image copy followed by direct
    * reads is both the scalar semantics and O(depth + W*(R+P)).
    *
    * The caller supplies only one contiguous same-array run.  Keeping runs
    * intact preserves schedule order if a later state-read address has an
    * ordinary data dependency on an earlier read.
    */
  private def denseStateReadGroupStr(res: Result, tids: Seq[Int], W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    require(tids.nonEmpty, "[v2-state-array] empty dense state-read group")
    val arrays = tids.map { tid =>
      val RStateRead(array) = res.nodes(tid).role: @unchecked
      array
    }.distinct
    require(arrays.size == 1,
      s"[v2-state-array] grouped reads span arrays ${arrays.mkString(",")}")
    val array = arrays.head
    val si = res.stateArrays(array)
    require(si.depth <= 4096,
      s"[v2-state-array] dense group requested for sparse array '$array' depth ${si.depth}")
    val plan = stateWritePlan(res, array)
    val writes = plan.ordinary
    val laneLoop = if (dir > 0) s"for (int L = 0; L < $W; L++)"
      else s"for (int L = ${W - 1}; L >= 0; L--)"

    if (externProbe(array)) return tids.flatMap { tid =>
      val (d, _) = stateReadParts(res, tid)
      val out = rn.emitForLane(d.name, "L")
      Seq(s"// [extern-probe] read of '$array' stubbed",
        s"$laneLoop { $out = ${genCppType(si.tpe)}(0); }")
    }
    val reads = tids.zipWithIndex.flatMap { case (tid, readIndex) =>
      val (d, readAddr) = stateReadParts(res, tid)
      val out = rn.emitForLane(d.name, "L")
      val addr = withLaneVar("L") { emitExpr(readAddr) }
      if (!stateAddressCanEscape(si.depth))
        Seq(s"    $out = _v2_sa_image[essent_to_u64($addr)];")
      else {
        val addressName = s"_v2_sa_group_addr_$readIndex"
        Seq(
          s"    const uint64_t $addressName = essent_to_u64($addr);",
          s"    $out = ${stateReadExpr("_v2_sa_image", si.tpe, addressName, si.depth)};")
      }
    }
    val ordinaryInstall = writes.map { mw =>
      val wen = withLaneVar("L") { emitExpr(mw.wrEn) }
      val mask = withLaneVar("L") { emitExpr(mw.wrMask) }
      val addr = withLaneVar("L") { emitExpr(mw.wrAddr) }
      val data = withLaneVar("L") { emitExpr(mw.wrData) }
      val inRange = if (stateAddressCanEscape(si.depth))
        s" && essent_to_u64($addr) < (uint64_t)${si.depth}"
      else ""
      s"    if (essent_to_u64($wen) && essent_to_u64($mask)$inRange) " +
        s"_v2_sa_image[essent_to_u64($addr)] = $data;"
    }
    val install = plan.bulkZeroReset match {
      case Some(reset) =>
        val enable = withLaneVar("L") { emitExpr(reset.enable) }
        Seq(s"    if (essent_to_u64($enable)) {",
          "      memset(_v2_sa_image, 0, sizeof(_v2_sa_image));",
          "    } else {") ++ ordinaryInstall.map("  " + _) ++ Seq("    }")
      case None => ordinaryInstall
    }
    val fullPath = Seq(
      "{",
      s"  ${genCppType(si.tpe)} _v2_sa_image[${si.depth}];",
      s"  memcpy(_v2_sa_image, &${si.name}[0], sizeof(_v2_sa_image));",
      s"  $laneLoop {") ++ reads ++ install ++ Seq("  }", "}")
    val guarded = if (!stateReadAnyGuard || writes.isEmpty || plan.bulkZeroReset.nonEmpty) fullPath
    else {
      val guardTerms = writes.map { mw =>
        val wen = withLaneVar("G") { emitExpr(mw.wrEn) }
        val mask = withLaneVar("G") { emitExpr(mw.wrMask) }
        s"    _v2_sa_anyw |= (uint64_t)(essent_to_u64($wen) != 0) & " +
          s"(uint64_t)(essent_to_u64($mask) != 0);"
      }
      val fastReads = tids.zipWithIndex.flatMap { case (tid, readIndex) =>
        val (d, readAddr) = stateReadParts(res, tid)
        val out = rn.emitForLane(d.name, "L")
        val addr = withLaneVar("L") { emitExpr(readAddr) }
        if (!stateAddressCanEscape(si.depth))
          Seq(s"      $out = ${si.name}[essent_to_u64($addr)];")
        else {
          val addressName = s"_v2_sa_fast_group_addr_$readIndex"
          Seq(
            s"      const uint64_t $addressName = essent_to_u64($addr);",
            s"      $out = ${stateReadExpr(si.name, si.tpe, addressName, si.depth)};")
        }
      }
      Seq(
        "{",
        "  // [state-read-any-guard]",
        "  uint64_t _v2_sa_anyw = 0;",
        s"  for (int G = 0; G < $W; G++) {") ++ guardTerms ++ Seq(
        "  }",
        "  if (_v2_sa_anyw == 0) {",
        s"    $laneLoop {") ++ fastReads ++ Seq(
        "    }",
        "  } else {") ++ fullPath.map("  " + _) ++ Seq(
        "  }",
        "}")
    }
    externReadFence(stateReadParts(res, tids.head)._1.name, guarded)
  }

  /** Distinct fields with one proven access key share the complete forwarding
    * decision.  One last-writer code identifies the preceding lane/port for
    * every field; the switch then loads each field's own write data.  This is
    * the array-of-struct access pattern recovered at code-generation time,
    * without physically packing fields or changing the RTL storage ABI. */
  private def sameAccessStateReadGroupStr(
      res: Result, tids: Seq[Int], W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    require(tids.size >= 2,
      "[v2-state-array] same-access read fusion requires at least two fields")
    val keys = tids.flatMap(tid => sameAccessReadKey(res, tid)).distinct
    require(keys.size == 1,
      s"[v2-state-array] same-access read group has ${keys.size} access keys")
    val key = keys.head
    val entries = tids.zipWithIndex.map { case (tid, field) =>
      val RStateRead(array) = res.nodes(tid).role: @unchecked
      val info = res.stateArrays(array)
      val plan = stateWritePlan(res, array)
      val (definition, _) = stateReadParts(res, tid)
      (field, definition, info, plan.ordinary)
    }
    require(entries.map(_._3.name).distinct.size == entries.size,
      "[v2-state-array] same-access read group repeats a physical array")
    if (entries.forall { case (_, _, info, _) => externProbe(info.name) })
      return Seq(s"// [extern-probe] same-access group stubbed (semantics-breaking ceiling probe)",
        s"for (int L = 0; L < $W; L++) {") ++
        entries.map { case (_, definition, info, _) =>
          s"  ${rn.emitForLane(definition.name, "L")} = ${genCppType(info.tpe)}(0);"
        } ++ Seq("}")
    val portCount = key.writes.size
    require(portCount > 0 && entries.forall(_._4.size == portCount),
      "[v2-state-array] same-access read group has inconsistent writer counts")
    val (_, leaderAddress) = stateReadParts(res, tids.head)
    val address = withLaneVar("L") { emitExpr(leaderAddress) }
    val laneLoop = if (dir > 0) s"for (int L = 0; L < $W; L++)"
      else s"for (int L = ${W - 1}; L >= 0; L--)"
    val priorLoop = if (dir > 0) "for (int J = 0; J < L; J++)"
      else s"for (int J = ${W - 1}; J > L; J--)"

    val valueDeclarations = entries.map { case (field, _, info, _) =>
      s"    ${genCppType(info.tpe)} _v2_sa_field_value_$field = " +
        s"${stateReadExpr(info.name, info.tpe, "_v2_sa_field_addr", info.depth)};"
    }
    val forwardingCases = (0 until portCount).flatMap { port =>
      val assignments = entries.map { case (field, _, _, writes) =>
        val data = withLaneVar("_v2_sa_field_prev_lane") {
          emitExpr(writes(port).wrData)
        }
        s"        _v2_sa_field_value_$field = $data;"
      }
      Seq(s"      case $port:") ++ assignments ++ Seq("        break;")
    }
    val outputs = entries.map { case (field, definition, _, _) =>
      s"    ${rn.emitForLane(definition.name, "L")} = _v2_sa_field_value_$field;"
    }
    val leaderWrites = entries.head._4
    val branchlessDense = branchlessDenseLastWriter(entries.map(_._3.tpe))
    val installs = leaderWrites.zipWithIndex.flatMap { case (write, port) =>
      val enable = withLaneVar("L") { emitExpr(write.wrEn) }
      val mask = withLaneVar("L") { emitExpr(write.wrMask) }
      val writeAddress = withLaneVar("L") { emitExpr(write.wrAddr) }
      if (branchlessDense) {
        val inRange = if (stateAddressCanEscape(key.depth))
          s" & (uint64_t)(_v2_sa_field_write_addr_$port < (uint64_t)${key.depth})"
        else ""
        Seq(
        s"    const uint64_t _v2_sa_field_write_addr_$port = " +
          s"essent_to_u64($writeAddress);",
        s"    const uint64_t _v2_sa_field_write_take_$port = " +
          s"(uint64_t)(essent_to_u64($enable) != 0) & " +
          s"(uint64_t)(essent_to_u64($mask) != 0)$inRange;",
        s"    const uint64_t _v2_sa_field_write_mask_$port = " +
          s"(uint64_t)0 - _v2_sa_field_write_take_$port;",
        s"    const uint64_t _v2_sa_field_write_slot_$port = " +
          s"(_v2_sa_field_write_addr_$port & _v2_sa_field_write_mask_$port) | " +
          s"((uint64_t)${key.depth} & ~_v2_sa_field_write_mask_$port);",
        s"    _v2_sa_field_last[_v2_sa_field_write_slot_$port] = " +
          s"L * $portCount + $port;")
      } else {
        val inRange = if (stateAddressCanEscape(key.depth))
          s" && essent_to_u64($writeAddress) < (uint64_t)${key.depth}"
        else ""
        Seq(
        s"    if (essent_to_u64($enable) && essent_to_u64($mask)$inRange) " +
          s"_v2_sa_field_last[essent_to_u64($writeAddress)] = " +
          s"L * $portCount + $port;")
      }
    }
    val priorScans = leaderWrites.zipWithIndex.map { case (write, port) =>
      val enable = withLaneVar("J") { emitExpr(write.wrEn) }
      val mask = withLaneVar("J") { emitExpr(write.wrMask) }
      val writeAddress = withLaneVar("J") { emitExpr(write.wrAddr) }
      s"      if (essent_to_u64($enable) && essent_to_u64($mask) && " +
        s"essent_to_u64($writeAddress) == _v2_sa_field_addr) " +
        s"_v2_sa_field_prev_code = J * $portCount + $port;"
    }
    val branchlessSparse = branchlessSparseStateRead(entries.map(_._3.tpe))
    val branchlessPriorScans = leaderWrites.zipWithIndex.flatMap {
        case (write, port) =>
      val enable = withLaneVar("J") { emitExpr(write.wrEn) }
      val mask = withLaneVar("J") { emitExpr(write.wrMask) }
      val writeAddress = withLaneVar("J") { emitExpr(write.wrAddr) }
      val take = s"_v2_sa_field_take_$port"
      val assignments = entries.map { case (field, _, _, writes) =>
        val data = withLaneVar("J") { emitExpr(writes(port).wrData) }
        s"      _v2_sa_field_value_$field = essent_mux($take, $data, " +
          s"_v2_sa_field_value_$field);"
      }
      Seq(s"      const UInt<1> $take = " +
        sparseMatchExpr(enable, mask, writeAddress, "_v2_sa_field_addr") + ";") ++
        assignments
    }
    val selectForwarded = Seq(
      "    if (_v2_sa_field_prev_code >= 0) {",
      s"      [[maybe_unused]] const int _v2_sa_field_prev_lane = " +
        s"_v2_sa_field_prev_code / $portCount;",
      s"      switch (_v2_sa_field_prev_code % $portCount) {") ++
      forwardingCases ++ Seq(
      "        default: __builtin_unreachable();",
      "      }",
      "    }")
    val selectForwardedBranchless = {
      require(portCount > 0,
        "[v2-state-array] branchless dense field selection requires a writer")
      val assignments = entries.map { case (field, _, _, writes) =>
        val data = withLaneVar("_v2_sa_field_prev_lane") {
          emitExpr(writes.head.wrData)
        }
        s"    _v2_sa_field_value_$field = essent_mux(" +
          s"UInt<1>(_v2_sa_field_prev_valid), $data, " +
          s"_v2_sa_field_value_$field);"
      }
      Seq(
        "    const uint64_t _v2_sa_field_prev_valid = " +
          "(uint64_t)(_v2_sa_field_prev_code >= 0);",
        "    [[maybe_unused]] const int _v2_sa_field_prev_lane = " +
          "_v2_sa_field_prev_code & " +
          "-static_cast<int>(_v2_sa_field_prev_valid);") ++ assignments
    }

    val fullPath = if (preferDenseLastWriter(key.depth, W, portCount)) {
      val branchlessSelect = branchlessDense && portCount == 1
      val lastWriterSlots = key.depth + (if (branchlessDense) 1 else 0)
      Seq(
        "{",
        s"  // [state-field-read-fused] ${entries.size} arrays share one access scan, " +
          s"mode=${if (branchlessDense) "dense-branchless" else "dense"}",
        s"  int _v2_sa_field_last[$lastWriterSlots];",
        s"  for (int _v2_sa_field_i = 0; _v2_sa_field_i < $lastWriterSlots; " +
          "_v2_sa_field_i++) _v2_sa_field_last[_v2_sa_field_i] = -1;",
        s"  $laneLoop {",
        s"    const uint64_t _v2_sa_field_addr = essent_to_u64($address);",
        s"    const int _v2_sa_field_prev_code = ${lastWriterReadExpr("_v2_sa_field_last", "_v2_sa_field_addr", key.depth)};") ++
        valueDeclarations ++
        (if (branchlessSelect) selectForwardedBranchless else selectForwarded) ++
        outputs ++ installs ++ Seq("  }", "}")
    } else if (branchlessSparse) {
      Seq(
        "{",
        s"  // [state-field-read-fused] ${entries.size} arrays share one access scan, mode=sparse-branchless",
        s"  $laneLoop {",
        s"    const uint64_t _v2_sa_field_addr = essent_to_u64($address);") ++
        valueDeclarations ++ Seq(s"    $priorLoop {") ++
        branchlessPriorScans ++ Seq("    }") ++ outputs ++ Seq("  }", "}")
    } else {
      Seq(
        "{",
        s"  // [state-field-read-fused] ${entries.size} arrays share one access scan, mode=sparse-branching",
        s"  $laneLoop {",
        s"    const uint64_t _v2_sa_field_addr = essent_to_u64($address);",
        "    int _v2_sa_field_prev_code = -1;",
        s"    $priorLoop {") ++ priorScans ++ Seq("    }") ++
        valueDeclarations ++ selectForwarded ++ outputs ++ Seq("  }", "}")
    }
    // Same window-level any-write guard as the single-array read paths: all
    // fields of a same-access group share one write condition set, so one
    // reduction covers every field. Bulk-reset arrays keep the full path.
    val plansOk = tids.forall { tid =>
      val RStateRead(array) = res.nodes(tid).role: @unchecked
      stateWritePlan(res, array).bulkZeroReset.isEmpty
    }
    val guarded = if (!stateReadAnyGuard || leaderWrites.isEmpty || !plansOk) fullPath
    else {
      val guardTerms = leaderWrites.map { mw =>
        val wen = withLaneVar("G") { emitExpr(mw.wrEn) }
        val mask = withLaneVar("G") { emitExpr(mw.wrMask) }
        s"    _v2_sa_anyw |= (uint64_t)(essent_to_u64($wen) != 0) & " +
          s"(uint64_t)(essent_to_u64($mask) != 0);"
      }
      val fastReads = entries.map { case (field, definition, info, _) =>
        s"      ${rn.emitForLane(definition.name, "L")} = " +
          s"${info.name}[_v2_sa_field_addr];"
      }
      Seq(
        "{",
        "  // [state-read-any-guard]",
        "  uint64_t _v2_sa_anyw = 0;",
        s"  for (int G = 0; G < $W; G++) {") ++ guardTerms ++ Seq(
        "  }",
        "  if (_v2_sa_anyw == 0) {",
        s"    $laneLoop {",
        s"      const uint64_t _v2_sa_field_addr = essent_to_u64($address);") ++
        fastReads ++ Seq(
        "    }",
        "  } else {") ++ fullPath.map("  " + _) ++ Seq(
        "  }",
        "}")
    }
    // Fence only when the whole group is the verify-side recompute of extern
    // read streams; a mixed group (should not happen with per-array family
    // matching) stays unfenced and merely wastes the extern members' work.
    if (entries.forall { case (_, definition, _, _) => definition.name.endsWith("$rtl") })
      externReadFence(entries.head._2.name, guarded)
    else guarded
  }

  /** Split a fused state-read unit into contiguous access runs.  Dense
    * multi-port reads of one array share an image; adjacent one-read fields
    * with a proven identical access key share one last-writer scan.  Sparse
    * memories and unmatched singleton runs retain their established shape.
    */
  private def stateReadRunStr(res: Result, tids: Seq[Int], W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    type RunKey = Either[SameAccessReadKey, String]
    val runs = ArrayBuffer[(RunKey, ArrayBuffer[Int])]()
    for (tid <- tids) {
      val RStateRead(array) = res.nodes(tid).role: @unchecked
      val key: RunKey = sameAccessReadKey(res, tid).map(Left(_))
        .getOrElse(Right(array))
      if (runs.lastOption.exists(_._1 == key)) runs.last._2 += tid
      else runs += key -> ArrayBuffer(tid)
    }
    runs.flatMap { case (key, run) =>
      val RStateRead(array) = res.nodes(run.head).role: @unchecked
      key match {
        case Left(_) if run.size >= 2 =>
          sameAccessStateReadGroupStr(res, run.toSeq, W, dir)
        case Right(_) if run.size >= 2 && res.stateArrays(array).depth <= 4096 =>
          denseStateReadGroupStr(res, run.toSeq, W, dir)
        case _ => run.flatMap(tid => stateReadLoopStr(res, tid, W, dir))
      }
    }.toSeq
  }

  /** Exact single-lane form used when a state read participates in a serial
    * SCC.  Earlier writer lanes are already scheduled by the EShift edges.
    *
    * Perf (Small BOOM W=32, 2026-09-03): the per-lane scan over every earlier
    * lane (`for J < lane`) is O(W^2) scalar compares per read port and was the
    * largest branch-misprediction source of the consumer (loop exits with a
    * lane-dependent trip count). With V2_STATE_LANE_VECTOR_SCAN=1 (default)
    * the match predicate of every write port is evaluated for all W lanes in
    * one vector lane loop, reduced to a lane bitmask, masked to the earlier
    * lanes and the chronologically last writer is picked with a bit scan.
    * Lanes at or after the current one are masked out, so their not-yet
    * computed operands are never used. Header-patched prototype: -2% wall,
    * -27% branch mispredictions, zero mismatches over 1.4M cycles. */
  private lazy val stateLaneVectorScan: Boolean =
    envBool("V2_STATE_LANE_VECTOR_SCAN", default = true)

  private def stateReadLaneStr(res: Result, tid: Int, lane: Int, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    val RStateRead(array) = res.nodes(tid).role: @unchecked
    val si = res.stateArrays(array)
    val plan = stateWritePlan(res, array)
    val writes = plan.ordinary
    val (d, readAddr) = stateReadParts(res, tid)
    val k = lane.toString
    val out = rn.emitForLane(d.name, k)
    if (externProbe(array))
      return Seq(s"$out = ${genCppType(si.tpe)}(0); // [extern-probe] stubbed")
    val addr = withLaneVar(k) { emitExpr(readAddr) }
    val tpe = genCppType(si.tpe)
    if (stateLaneVectorScan && W >= 2 && W <= 64) {
      val boundary = if (dir > 0) lane == 0 else lane == W - 1
      val ports = writes.zipWithIndex.map { case (mw, port) =>
        val wen = withLaneVar("J") { emitExpr(mw.wrEn) }
        val mask = withLaneVar("J") { emitExpr(mw.wrMask) }
        val waddr = withLaneVar("J") { emitExpr(mw.wrAddr) }
        val data = withLaneVar("J") { emitExpr(mw.wrData) }
        (port, "static_cast<uint8_t>(essent_to_u64(" +
          sparseMatchExpr(wen, mask, waddr, "_v2_sa_addr") + "))", data)
      }
      val resetTake = plan.bulkZeroReset.map { reset =>
        val en = withLaneVar("J") { emitExpr(reset.enable) }
        s"static_cast<uint8_t>(essent_to_u64($en) != 0)"
      }
      val takes = ports.map(_._2) ++ resetTake.toSeq
      val nTake = takes.size
      val scan: Seq[String] =
        if (boundary || nTake == 0) Seq.empty
        else {
          val range = if (dir > 0) s"((1ull << $lane) - 1ull)"
            else s"(~((2ull << $lane) - 1ull) & essent_lane_all<$W>())"
          val pick = if (dir > 0) "63 - __builtin_clzll(_v2_ball)" else "__builtin_ctzll(_v2_ball)"
          // Chronologically last lane; inside one lane a bulk reset beats the
          // write ports and a later port beats an earlier one (same order as
          // the scalar scan's last-assignment-wins).
          val portSel = ports.reverse.map { case (port, _, data) =>
            (s"((_v2_b$port >> J) & 1ull)", s"_v2_sa_value = $data;") }
          val resetSel = resetTake.map(_ =>
            (s"((_v2_b${nTake - 1} >> J) & 1ull)", s"_v2_sa_value = $tpe(0);")).toSeq
          val conds = resetSel ++ portSel
          val sel = conds.zipWithIndex.map { case ((c, a), i) =>
            if (conds.size == 1) s"      $a"
            else if (i == 0) s"      if ($c) $a"
            else if (i == conds.size - 1) s"      else $a"
            else s"      else if ($c) $a"
          }
          val pointers = writes.map(mw => forwardingDataPointer(mw.wrData, si.tpe, "J"))
          val direct = envBool("V2_BRANCHLESS_FORWARD", default = false) && pointers.forall(_.isDefined)
          val selection = if (direct) {
            val safePick = if (dir > 0) "63 - __builtin_clzll(_v2_safe_bits)" else "__builtin_ctzll(_v2_safe_bits)"
            Seq(
              "    // [branchless-forward] no-match bitmap uses a safe index and the original value",
              "    const uint64_t _v2_safe_bits = _v2_ball | static_cast<uint64_t>(_v2_ball == 0);",
              s"    const int J = $safePick;",
              s"    const $tpe* _v2_selected = &_v2_sa_value;") ++
              pointers.zipWithIndex.map { case (ptr, port) =>
                s"    _v2_selected = essent_select_ptr(((_v2_b$port >> J) & 1ull) != 0, ${ptr.get}, _v2_selected);"
              } ++ resetTake.toSeq.flatMap { _ => Seq(
                s"    const $tpe _v2_reset_value(0);",
                s"    _v2_selected = essent_select_ptr(((_v2_b${nTake - 1} >> J) & 1ull) != 0, &_v2_reset_value, _v2_selected);")
              } ++ Seq("    _v2_sa_value = *_v2_selected;")
          } else Seq("    if (_v2_ball) {", s"      const int J = $pick;") ++ sel ++ Seq("    }")
          Seq("  {",
            s"    alignas(64) uint8_t _v2_tk[$nTake][$W];",
            "    ESSENT_LANE_LOOP",
            s"    for (int J = 0; J < $W; J++) {") ++
            takes.zipWithIndex.map { case (t, i) => s"      _v2_tk[$i][J] = $t;" } ++
            Seq("    }") ++
            (0 until nTake).map(i => s"    const uint64_t _v2_b$i = essent_lane_mask<$W>(_v2_tk[$i]) & $range;") ++
            Seq("    const uint64_t _v2_ball = " + (0 until nTake).map(i => s"_v2_b$i").mkString(" | ") + ";") ++
            selection ++ Seq("  }")
        }
      externReadFence(d.name, Seq(
        "{",
        "  // [state-read-sparse-lane] forwarding=vector-scan",
        s"  const uint64_t _v2_sa_addr = essent_to_u64($addr);",
        s"  $tpe _v2_sa_value = ${si.name}[_v2_sa_addr];") ++ scan ++ Seq(
        s"  $out = _v2_sa_value;",
        "}"))
    } else {
    val jLoop = if (dir > 0) s"for (int J = 0; J < $lane; J++)"
      else s"for (int J = ${W - 1}; J > $lane; J--)"
    val branchless = plan.bulkZeroReset.isEmpty &&
      branchlessSparseStateRead(Seq(si.tpe))
    val ordinaryForward = writes.zipWithIndex.flatMap { case (mw, port) =>
      val wen = withLaneVar("J") { emitExpr(mw.wrEn) }
      val mask = withLaneVar("J") { emitExpr(mw.wrMask) }
      val addr = withLaneVar("J") { emitExpr(mw.wrAddr) }
      val data = withLaneVar("J") { emitExpr(mw.wrData) }
      if (branchless) Seq(
        s"    const UInt<1> _v2_sa_lane_take_$port = " +
          sparseMatchExpr(wen, mask, addr, "_v2_sa_addr") + ";",
        s"    _v2_sa_value = essent_mux(_v2_sa_lane_take_$port, $data, " +
          "_v2_sa_value);")
      else Seq(
        s"    if (essent_to_u64($wen) && essent_to_u64($mask) && " +
          s"essent_to_u64($addr) == _v2_sa_addr) _v2_sa_value = $data;")
    }
    val forward = plan.bulkZeroReset match {
      case Some(reset) =>
        val enable = withLaneVar("J") { emitExpr(reset.enable) }
        Seq(s"    if (essent_to_u64($enable)) {",
          s"      _v2_sa_value = ${genCppType(si.tpe)}(0);",
          "    } else {") ++ ordinaryForward.map("  " + _) ++ Seq("    }")
      case None => ordinaryForward
    }
    externReadFence(d.name, Seq(
      "{",
      s"  // [state-read-sparse-lane] forwarding=${if (branchless) "branchless" else "branching"}",
      s"  const uint64_t _v2_sa_addr = essent_to_u64($addr);",
      s"  ${genCppType(si.tpe)} _v2_sa_value = ${si.name}[_v2_sa_addr];",
      s"  $jLoop {") ++ forward ++ Seq(
      "  }",
      s"  $out = _v2_sa_value;",
      "}"))
    }
  }

  /** Apply all virtual-cycle writes to the persistent image in chronological
    * order.  Multiple writes to one entry therefore leave the last write,
    * exactly as scalar cycle-by-cycle execution would.
    */
  private def stateCommitBodyStr(res: Result, array: String, lane: String)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    val plan = stateWritePlan(res, array)
    val writes = plan.ordinary
    val si = res.stateArrays(array)
    val ordinaryPortWrites = writes.map { mw =>
      val wen = withLaneVar(lane) { emitExpr(mw.wrEn) }
      val mask = withLaneVar(lane) { emitExpr(mw.wrMask) }
      val addr = withLaneVar(lane) { emitExpr(mw.wrAddr) }
      val data = withLaneVar(lane) { emitExpr(mw.wrData) }
      s"    if (essent_to_u64($wen) && essent_to_u64($mask)) " +
        s"$array[essent_to_u64($addr)] = $data;"
    }
    plan.bulkZeroReset match {
      case Some(reset) =>
        val enable = withLaneVar(lane) { emitExpr(reset.enable) }
        Seq(s"    if (essent_to_u64($enable)) {",
          s"      memset(&$array[0], 0, sizeof(${genCppType(si.tpe)}) * ${si.depth});",
          "    } else {") ++ ordinaryPortWrites.map("  " + _) ++ Seq("    }")
      case None => ordinaryPortWrites
    }
  }

  /** Branch-free OR reduction of all actions covered by one emitted commit
    * loop.  Same-access payload fields naturally collapse here because their
    * enable/mask expressions are identical. */
  private def stateCommitAnyConditions(
      res: Result, arrays: Seq[String], lane: String)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    arrays.flatMap { array =>
      val plan = stateWritePlan(res, array)
      val ordinary = plan.ordinary.map { write =>
        val enable = withLaneVar(lane) { emitExpr(write.wrEn) }
        val mask = withLaneVar(lane) { emitExpr(write.wrMask) }
        s"((uint64_t)(essent_to_u64($enable) != 0) & " +
          s"(uint64_t)(essent_to_u64($mask) != 0))"
      }
      val reset = plan.bulkZeroReset.toSeq.map { value =>
        val enable = withLaneVar(lane) { emitExpr(value.enable) }
        s"(uint64_t)(essent_to_u64($enable) != 0)"
      }
      ordinary ++ reset
    }.distinct
  }

  /** Surround one established chronological commit loop with an optional
    * whole-window activity test.  `body` keeps its original lane/port order;
    * only the all-disabled case bypasses it. */
  private def stateCommitLoopShape(
      res: Result, arrays: Seq[String], W: Int, dir: Int,
      comments: Seq[String], body: Seq[String])
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    val loop = if (dir > 0) s"for (int L = 0; L < $W; L++)"
      else s"for (int L = ${W - 1}; L >= 0; L--)"
    val loopLines = Seq(s"  $loop {") ++ body ++ Seq("  }")
    val commentLines = comments.map(comment => s"  // $comment")
    if (!guardEmptyStateCommitWindows) {
      Seq("if (update_registers) {") ++ commentLines ++ loopLines ++ Seq("}")
    } else {
      val conditions = stateCommitAnyConditions(res, arrays, "G")
      require(conditions.nonEmpty,
        "[v2-state-array] state commit activity guard has no write condition")
      Seq("if (update_registers) {") ++ commentLines ++ Seq(
        s"  // [state-commit-any-guard] ${arrays.size} array(s), ${conditions.size} condition(s)",
        "  uint64_t _v2_sa_any = 0;",
        s"  for (int G = 0; G < $W; G++) {") ++
        conditions.map(condition => s"    _v2_sa_any |= $condition;") ++ Seq(
        "  }",
        "  if (_v2_sa_any != 0) {") ++
        loopLines.map("  " + _) ++ Seq(
        "  }",
        "}")
    }
  }

  private def stateCommitLoopStr(res: Result, array: String, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    stateCommitLoopShape(res, Seq(array), W, dir, Seq.empty,
      stateCommitBodyStr(res, array, "L"))
  }

  /** Commit the same-access fields under one lane loop and one condition per
    * write port.  Port ordering within every physical array is unchanged;
    * only independent field stores are placed beside one another. */
  private def sameAccessStateCommitBodyStr(
      res: Result, arrays: Seq[String], lane: String)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    require(arrays.size >= 2 && arrays.distinct.size == arrays.size,
      "[v2-state-array] same-access commit fusion requires distinct arrays")
    val keys = arrays.flatMap(array => sameAccessCommitKey(res, array)).distinct
    require(keys.size == 1,
      s"[v2-state-array] same-access commit group has ${keys.size} access keys")
    val plans = arrays.map(array => stateWritePlan(res, array).ordinary)
    val portCount = keys.head.writes.size
    require(portCount > 0 && plans.forall(_.size == portCount),
      "[v2-state-array] same-access commit group has inconsistent writer counts")
    (0 until portCount).flatMap { port =>
      val leader = plans.head(port)
      val enable = withLaneVar(lane) { emitExpr(leader.wrEn) }
      val mask = withLaneVar(lane) { emitExpr(leader.wrMask) }
      val address = withLaneVar(lane) { emitExpr(leader.wrAddr) }
      val writes = arrays.zip(plans).map { case (array, plan) =>
        val data = withLaneVar(lane) { emitExpr(plan(port).wrData) }
        s"      $array[_v2_sa_field_waddr_$port] = $data;"
      }
      Seq(
        s"    if (essent_to_u64($enable) && essent_to_u64($mask)) {",
        s"      const uint64_t _v2_sa_field_waddr_$port = essent_to_u64($address);") ++
        writes ++ Seq("    }")
    }
  }

  private def sameAccessStateCommitGroupStr(
      res: Result, arrays: Seq[String], W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    stateCommitLoopShape(res, arrays, W, dir,
      Seq(s"[state-field-commit-fused] ${arrays.size} arrays share one access loop"),
      sameAccessStateCommitBodyStr(res, arrays, "L"))
  }

  private def stateCommitRunStr(res: Result, tids: Seq[Int], W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    // A fully external array has no consumer-side storage and its commit node
    // is intentionally empty.  Its ordered writes are checked through the
    // generated enable/address/data access streams instead.
    val activeT = tids.filterNot(tid => res.nodes(tid).role match {
      case RStateCommit(a) => res.stateArrays(a).fullyExternal
      case _ => false
    })
    if (activeT.isEmpty) return Seq.empty
    // Commits of fully-externalized arrays are verify-only (no perf-build
    // reader survives the read fences). Split them out of the run and fence
    // them; commits of distinct arrays are independent, so regrouping is
    // order-safe. Mixed runs simply lose some fusion, nothing else.
    val (externT, normalT) = activeT.partition(tid => res.nodes(tid).role match {
      case RStateCommit(a) => externAllReads(res, a)
      case _ => false
    })
    if (externT.nonEmpty) {
      val normal = if (normalT.isEmpty) Seq.empty
        else stateCommitRunBodyStr(res, normalT, W, dir)
      return normal ++
        ("#if ESSENT_ORACLE_VERIFY // [extern-read] commits of fully-externalized arrays" +:
          stateCommitRunBodyStr(res, externT, W, dir)) :+ "#endif"
    }
    stateCommitRunBodyStr(res, activeT, W, dir)
  }

  private def stateCommitRunBodyStr(res: Result, tids: Seq[Int], W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    type RunKey = Either[SameAccessCommitKey, String]
    val runs = ArrayBuffer[(RunKey, ArrayBuffer[String])]()
    for (tid <- tids) res.nodes(tid).role match {
      case RStateCommit(array) =>
        val key: RunKey = sameAccessCommitKey(res, array).map(Left(_))
          .getOrElse(Right(array))
        if (runs.lastOption.exists(_._1 == key)) runs.last._2 += array
        else runs += key -> ArrayBuffer(array)
      case other => throw new IllegalStateException(
        s"[v2-state-array] state commit run contains $other")
    }
    def establishedShape: Seq[String] = runs.flatMap { case (key, arrays) => key match {
      case Left(_) if arrays.size >= 2 =>
        sameAccessStateCommitGroupStr(res, arrays.toSeq, W, dir)
      case _ => arrays.flatMap(array => stateCommitLoopStr(res, array, W, dir))
    }}.toSeq

    // A singleton access group already has one lane loop.  Otherwise every
    // run member is a full-width commit to a distinct array, so retain each
    // array's chronological writes but share the surrounding host loop.
    if (!fuseStateCommitRuns || runs.size <= 1) establishedShape
    else {
      // Preserve one lexical scope per former loop.  Same-access groups reuse
      // local names such as `_v2_sa_field_waddr_0`; braces keep those names
      // independent after their lane loops are merged.
      val bodies = runs.flatMap { case (key, arrays) =>
        val body = key match {
          case Left(_) if arrays.size >= 2 =>
            Seq(s"    // [state-field-commit-fused] ${arrays.size} arrays share one access condition") ++
              sameAccessStateCommitBodyStr(res, arrays.toSeq, "L")
          case _ => arrays.flatMap(array => stateCommitBodyStr(res, array, "L"))
        }
        Seq("    {") ++ body.map("  " + _) ++ Seq("    }")
      }
      stateCommitLoopShape(res, runs.flatMap(_._2).toSeq, W, dir,
        Seq(s"[state-commit-run-fused] ${runs.size} access groups share one lane loop"),
        bodies.toSeq)
    }
  }

  /** One fused vector run: declarations then a shared lane loop. Emits for a
    * fixed direction (callers branch on direction outside when merging). */
  private def emitRunGroup(res: Result, W: Int, cat: FuseCat, tids: Seq[Int],
      dir: Int, verifyOutline: VerifyOutlineRegistry, w: Writer, declare: Boolean = true)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
      // W=1 (scalar control experiment): shift sources are structurally
      // empty loops whose bodies still reference lane W-2 / lane 1 names —
      // skip them instead of emitting dead references. Cross-lane verifies
      // are empty too, but CVerify still stores the boundary carries, which
      // are the only register checks a W=1 build has.
      if (W == 1 && cat == CSource) return
      if (cat == CEffect)
        w.writeLines(2, s"// [effect] ${tids.size} templates x $W lanes (scalar loop; see CEffect)")
      else
        w.writeLines(2, s"// [vec ${catName(cat)}] ${tids.size} templates x $W lanes")
      if (declare) {
        for (t <- tids; name <- res.nodes(t).produces) {
          val tpe = rn.nameToMeta(name).sigType
          rn.simdArrayDecl(name, genCppType(tpe)).foreach(d => w.writeLines(2, d))
        }
      }
      cat match {
        case CComb | CBoundaryComb =>
          // Perf: cap how many comb statements share one lane loop. On the
          // complete-Small W=16 build, splitting flat comb loops at six
          // statements (text-transform prototype, 2026-08-21) measured +3.8%
          // and raised the eval body's static vector share from 34.5% to
          // 40.5%: smaller loops keep live vector state inside the register
          // file and let clang vectorize runs it refused as one block.
          // Statement order is unchanged; run members are mutually
          // independent by FuseCat construction. V2_COMB_LOOP_CAP=0 restores
          // the single fused loop.
          val cap = combLoopCap
          var cw: Writer = w // redirected to a capture buffer when outlining
          def emitLaneStatements(g: Seq[Int], indent: Int): Unit = {
            val bindings = loopScalarBindings(res, g)
            rn.withScalarLaneBindings(bindings) {
              for ((name, local) <- bindings.toSeq.sortBy(_._2)) {
                cw.writeLines(indent, s"// [v2 lane-local] $name $local")
                cw.writeLines(indent, s"${genCppType(rn.nameToMeta(name).sigType)} $local;")
              }
              for (t <- g)
                withLaneVar("L") { cw.writeLines(indent, emitCombStmt(res.nodes(t).stmt)) }
            }
          }
          def emitNormal(ts: Seq[Int], vectorize: Boolean = true): Unit = if (ts.nonEmpty) {
            val groups = if (vectorize && cap > 0) ts.grouped(cap).toSeq else Seq(ts)
            for (group <- groups) {
              var at = 0
              while (at < group.size) {
                val endpoints = endpointNextTids(group(at))
                var until = at + 1
                while (until < group.size && endpointNextTids(group(until)) == endpoints) until += 1
                val g = group.slice(at, until)
                if (endpoints) {
                  cw.writeLines(2, s"// [boundary next] ${g.size} templates, two retained lanes")
                  for (lane <- Seq(0, W - 1)) {
                    cw.writeLines(2, s"{ const int L = $lane;")
                    emitLaneStatements(g, 3)
                    cw.writeLines(2, "}")
                  }
                } else {
                  if (vectorize) cw.writeLines(2, "ESSENT_LANE_LOOP")
                  cw.writeLines(2, s"for (int L = 0; L < $W; L++) {")
                  emitLaneStatements(g, 3)
                  cw.writeLines(2, "}")
                }
                at = until
              }
            }
          }
          // Perf: one statement that lowers through the wide POD helper path
          // (multi-word cat/bits/arithmetic emitted as method calls) makes
          // clang refuse to vectorize the whole fused loop ("call instruction
          // cannot be vectorized"), sacrificing every clean statement fused
          // with it — the caprg profile showed a single .cat() statement
          // keeping four u1 statements and an u11 concat scalar. Segregate
          // such statements into their own loops so the clean remainder
          // vectorizes. Statement order is unchanged. V2_COMB_POISON_SPLIT=0
          // restores the mixed loops.
          def poisonStmt(t: Int): Boolean = res.nodes(t).stmt match {
            case d: firrtl.ir.DefNode if condHoldWdataAliases.contains(d.name) => false
            // A native multi-word assignment can be vectorized, but forcing
            // W lanes at once keeps W * word-count values live. Let clang
            // choose its width independently of the narrow fused statements.
            case d: firrtl.ir.DefNode if bitWidth(d.value.tpe) > 64 => true
            case d: firrtl.ir.DefNode =>
              withLaneVar("L") {
                emitPrimitiveUIntAssign(rn.emitForLane(d.name, "L"), d.value.tpe, d.value)
              }.isEmpty
            case c: firrtl.ir.Connect if bitWidth(c.loc.tpe) > 64 => true
            case c: firrtl.ir.Connect =>
              withLaneVar("L") {
                emitPrimitiveUIntAssign(rn.emitForLane(emitExprRaw(c.loc), "L"),
                  c.loc.tpe, c.expr)
              }.isEmpty
            case _ => false
          }
          def emitSegregated(ts: Seq[Int]): Unit = if (ts.nonEmpty) {
            var i = 0
            while (i < ts.size) {
              val p = poisonStmt(ts(i))
              var j = i + 1
              while (j < ts.size && poisonStmt(ts(j)) == p) j += 1
              val seg = ts.slice(i, j)
              if (p) {
                cw.writeLines(2, s"// [vec comb-wide] ${seg.size} templates (compiler-selected vector width)")
                emitNormal(seg, vectorize = false)
              } else emitNormal(seg)
              i = j
            }
          }
          val poisonSplit = envBool("V2_COMB_POISON_SPLIT", default = true)
          def emitBody(): Unit = if (!u1PackEnabled) {
            if (poisonSplit) emitSegregated(tids) else emitNormal(tids)
          } else {
            // Consecutive pure-u1 statements of at least u1PackMinChain become
            // one bit-sliced segment; everything else keeps the lane loops.
            // Statement order is preserved exactly across segment boundaries.
            val pending = mutable.ArrayBuffer[Int]()
            val packRun = mutable.ArrayBuffer[Int]()
            def flushPack(): Unit = {
              if (packRun.size >= u1PackMinChain) {
                u1PackedSegmentStr(res, W, packRun.toSeq) match {
                  case Some(lines) =>
                    emitNormal(pending.toSeq); pending.clear()
                    cw.writeLines(2, lines)
                  case None => pending ++= packRun
                }
              } else pending ++= packRun
              packRun.clear()
            }
            for (t <- tids) {
              if (u1PackTarget(res.nodes(t).stmt).isDefined) packRun += t
              else { flushPack(); pending += t }
            }
            flushPack()
            emitNormal(pending.toSeq)
          }
          if (!sharedCombOutline) emitBody()
          else {
            // The rendered group is identical for both directions, so render
            // once into a member function and call it from each body. Keyed
            // by the exact statement sequence; a reverse-schedule group that
            // (unexpectedly) differs simply becomes its own function.
            val key = s"$W:" + tids.mkString(",")
            sharedCombFns.get(key) match {
              case Some((existing, _)) =>
                w.writeLines(2, s"_v2_cshare_$existing();")
              case None =>
                val sw = new java.io.StringWriter()
                cw = sw
                emitBody()
                cw = w
                val body = sw.toString
                if (sharedCombBodySize(body) >= sharedCombMinChars) {
                  val fresh = sharedCombFns.size
                  sharedCombFns(key) = (fresh, body)
                  w.writeLines(2, s"_v2_cshare_$fresh();")
                } else w.write(body) // small group: keep inline in both bodies
            }
          }
        case CEffect =>
          // Perf: deliberately NO ESSENT_LANE_LOOP pragma and no vectorization
          // ambition — these are UNLIKELY-guarded printf/assert statements. As
          // part of a CComb loop they blocked vectorization of every other
          // statement fused with them. FIRRTL assertions lower to an adjacent
          // Print/Stop pair with the same enable. Test that structural fact and
          // evaluate the enable once: the diagnostic print remains before the
          // stop, while the common not-taken path loses one branch and one copy
          // of the monitor predicate. The run-level guard makes disabled
          // checks truly free. An unpaired Print/Stop keeps the generic path.
          val effectStmts = tids.map(t => res.nodes(t).stmt)
          w.writeLines(2, "if (verbose || checks_enabled) {")
          w.writeLines(3, s"for (int L = 0; L < $W; L++) {")
          var effectIndex = 0
          while (effectIndex < effectStmts.size) {
            val current = effectStmts(effectIndex)
            val next = effectStmts.lift(effectIndex + 1)
            (current, next) match {
              case (print: Print, Some(stop: Stop))
                  if print.en.serialize == stop.en.serialize =>
                withLaneVar("L") {
                  w.writeLines(4, s"if (UNLIKELY(${emitExprWrap(print.en)})) {")
                  w.writeLines(5, "if (verbose) {")
                  w.writeLines(6, emitCombStmt(print))
                  w.writeLines(5, "}")
                  w.writeLines(5, "if (checks_enabled) {")
                  w.writeLines(6,
                    s"assert_triggered = true; assert_exit_code = ${stop.ret};")
                  w.writeLines(5, "}")
                  w.writeLines(4, "}")
                }
                effectIndex += 2
              case (print: Print, _) =>
                w.writeLines(4, "if (verbose) {")
                withLaneVar("L") { w.writeLines(5, emitCombStmt(print)) }
                w.writeLines(4, "}")
                effectIndex += 1
              case (stop: Stop, _) =>
                w.writeLines(4, "if (checks_enabled) {")
                withLaneVar("L") { w.writeLines(5, emitCombStmt(stop)) }
                w.writeLines(4, "}")
                effectIndex += 1
              case (other, _) =>
                throw new IllegalStateException(
                  s"CEffect run contains ${other.getClass.getSimpleName}, expected Print/Stop")
            }
          }
          w.writeLines(3, "}")
          w.writeLines(2, "}")
        case CSource =>
          // Sources of distinct registers are independent; each reads only its
          // own $next array. The ±1-lane read would land on the producer's
          // fresh vector stores and never store-to-load forward — stage each
          // $next array through an aligned local first (full-width aligned
          // copy forwards; the shifted stores then read the local).
          val shiftRegs = tids.flatMap(t => res.nodes(t).role match {
            case RRegSource(r) if res.regs(r).plan == RPShift => Some(res.regs(r))
            case _ => None
          })
          val rest = tids.filter(t => res.nodes(t).role match {
            case RRegSource(r) => res.regs(r).plan != RPShift
            case _ => true
          })
          w.writeLines(2, "{")
          for ((ri, idx) <- shiftRegs.zipWithIndex) {
            val t = genCppType(ri.tpe)
            w.writeLines(3, s"alignas(64) $t _v2s_$idx[$W];")
            w.writeLines(3, s"memcpy(_v2s_$idx, &${rn.emitForLane(ri.nextName, "0")}, sizeof(_v2s_$idx));")
          }
          if (!sourceLoop) {
            // Shifted memcpy from the staged snapshot: identical semantics to
            // the lane-loop distribute (lanes [1,W) fwd / [0,W-1) rev; the
            // boundary lane is written by the window-boundary code), but one
            // unconditional wide copy per register instead of a loop the
            // vectorizer only partially covered (34% scalar residue measured
            // in the BOOM W=16 reg-source region).
            for ((ri, idx) <- shiftRegs.zipWithIndex) {
              val (dst, srcOff) = if (dir > 0) ("1", "0") else ("0", "1")
              w.writeLines(3, s"memcpy(&${rn.emitForLane(ri.name, dst)}, &_v2s_$idx[$srcOff], " +
                s"sizeof(_v2s_$idx) - sizeof(_v2s_$idx[0]));")
            }
          }
          val loopRegs = if (sourceLoop) shiftRegs else Seq.empty[RegInfo]
          if (loopRegs.nonEmpty || rest.nonEmpty) {
            w.writeLines(3, "ESSENT_LANE_LOOP")
            if (dir > 0) w.writeLines(3, s"for (int L = ${W - 1}; L >= 1; L--) {")
            else w.writeLines(3, s"for (int L = 0; L < ${W - 1}; L++) {")
            val prevIdx = if (dir > 0) "L - 1" else "L + 1"
            for ((ri, idx) <- loopRegs.zipWithIndex)
              w.writeLines(4, s"${rn.emitForLane(ri.name, "L")} = _v2s_$idx[$prevIdx];")
            withLaneVar("L") {
              for (t <- rest) res.nodes(t).role match {
                case RRegSource(r) => w.writeLines(4, sourceLineStr(res.regs(r), "L", dir))
                case _ =>
              }
            }
            w.writeLines(3, "}")
          }
          w.writeLines(2, "}")
        case CCommit =>
          // Perf: one memcpy-backed helper call per register instead of a
          // fused lane loop — the loop form never vectorized (icpx assumed
          // aliasing between the POD lane stores; such scalar copy loops were
          // ~10% of kernel samples on Rocket W=8).
          // Oracle registers get no commit at all: the next window's lanes
          // come entirely from injection, the cold rescan reads the injected
          // (not committed) lanes, and --dump-final dumps only harness-side
          // architectural state. V2_KEEP_ORACLE_COMMIT=1 restores them.
          val commitRegs = tids.flatMap(t => res.nodes(t).role match {
            case RRegCommit(r) if commitWanted(r, res.regs(r)) => Some(r)
            case _ => None
          })
          if (commitRegs.nonEmpty) {
            w.writeLines(2, "if (update_registers) {")
            for (r <- commitRegs) w.writeLines(3, commitCallStr(r, res.regs(r), W, boundaryLaneStr(W, dir)))
            w.writeLines(2, "}")
          }
        case CStateRead =>
          // Keep state forwarding separate from unrelated SIMD comb loops,
          // but share one chronological walk across adjacent read ports of
          // the same dense array.
          stateReadRunStr(res, tids, W, dir).foreach(line => w.writeLines(2, line))
        case CStateCommit =>
          stateCommitRunStr(res, tids, W, dir).foreach(line => w.writeLines(2, line))
        case COracle =>
          // done_reset is loop-invariant: hoist it, or the backend emits a
          // byte-compare + cmov per lane per stream (measured: ~850 cmpb).
          // Perf: one essent_inject_* helper call per stream — the fused lane
          // loop form never vectorized (icpx assumed dependences between the
          // lane stores and the stream pointer / this->oracle_cycle).
          // Zero-copied registers need no injection at all: every read of
          // them aliases the block slot directly (see zcDirOverrides).
          val injectRegs = tids.flatMap(t => res.nodes(t).role match {
            case ROracleInject(r) if !zcInfo.contains(r) => Some(r)
            case _ => None
          })
          if (injectRegs.nonEmpty) {
            w.writeLines(2, "if (done_reset) {")
            for (r <- injectRegs; spec <- res.oracles.filter(_.flatName == r))
              w.writeLines(3, injectCallStr(res.regs(r).name, spec, dir, W))
            w.writeLines(2, "}")
          }
        case CVerify =>
          // Hot path: branchless OR-accumulate (vectorizes); cold path: one
          // predicted-never call per group into the exact per-lane report.
          // Accumulation runs per storage tier (see accumAssign); compares
          // are emitted tier-sorted so each tier vectorizes as one clean
          // homogeneous reduction.
          w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
          val (lo, hi) = if (dir > 0) (0, W - 1) else (1, W)
          val vRegs = tids.flatMap(t => res.nodes(t).role match {
            case RVerify(r) => Some(res.regs(r))
            case _ => None
          })
          val vWidths = vRegs.map(r => firrtl.bitWidth(r.tpe).toInt)
          w.writeLines(2, "if (done_reset && checks_enabled && update_registers) {")
          if (W > 1) {
            vaccDecls(vWidths).foreach(w.writeLines(3, _))
            withLaneVar("L") {
              emitVerifyReduction(vRegs.map(r =>
                verifyReductionTerm(firrtl.bitWidth(r.tpe).toInt, r.nextName, r.name, lo, dir, W)),
                W, lo, hi, tail = true, w = w)
            }
            if (verifyOutline.enabled) {
              val fields = tids.flatMap(t => res.nodes(t).role match {
                case RVerify(r) => Some(r)
                case _ => None
              })
              val groupId = verifyOutline.register(VRegVerify, fields)
              w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(vWidths)})) " +
                s"_v2_verify_rescan($groupId, ${dir > 0}, $lo, $hi);")
            } else {
              w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(vWidths)})) for (int L = $lo; L < $hi; L++) {")
              withLaneVar("L") {
                for (t <- tids) res.nodes(t).role match {
                  case RVerify(r) =>
                    verifyLinesStr(res.regs(r), "L", dir, W).foreach(l => w.writeLines(4, l))
                  case _ =>
                }
              }
              w.writeLines(3, "}")
            }
          }
          // The last lane's next-state has no in-window partner: carry it to
          // the following sweep's boundary check (BoundaryVerifyRegistry).
          w.writeLines(3, s"// [boundary-carry] ${vRegs.size} last-lane next-state values")
          for (r <- vRegs) w.writeLines(3, boundaryCarryStoreStr(r, r.nextName, W, dir))
          w.writeLines(2, "}")
          w.writeLines(2, "#endif")
        case CCombOracle =>
          // Reset phase needs typed zeros (cannot reference $rtl); hoist the
          // loop-invariant done_reset into two loop bodies.
          // Perf: injection side uses the __restrict-parameter helpers for the
          // same vectorization reason as COracle above. Direct-verify access
          // streams alias their read-only block slots and need neither arm.
          val injectCuts = tids.flatMap(t => res.nodes(t).role match {
            case ROracleInject(r) if !zcInfo.contains(r) => Some(r)
            case _ => None
          })
          if (injectCuts.nonEmpty) {
            w.writeLines(2, "if (done_reset) {")
            for (r <- injectCuts; spec <- res.oracles.filter(_.flatName == r))
              w.writeLines(3, injectCallStr(r, spec, dir, W))
            w.writeLines(2, s"} else for (int L = 0; L < $W; L++) {")
            withLaneVar("L") {
              for (r <- injectCuts)
                w.writeLines(3, s"${rn.emitForLane(r, "L")} = ${genCppType(res.combCuts(r))}(0);")
            }
            w.writeLines(2, "}")
          }
        case CCombVerify =>
          w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
          val cvFields = tids.flatMap(t => res.nodes(t).role match {
            case RVerify(r) => Some(r)
            case _ => None
          })
          val cvWidths = cvFields.map(r => firrtl.bitWidth(res.combCuts(r)).toInt)
          w.writeLines(2, "if (done_reset && checks_enabled && update_registers) {")
          vaccDecls(cvWidths).foreach(w.writeLines(3, _))
          withLaneVar("L") {
            emitVerifyReduction(cvFields.map(r =>
              verifyReductionTerm(firrtl.bitWidth(res.combCuts(r)).toInt, r + "$rtl", r, 0, 0, W)),
              W, 0, W, tail = false, w = w)
          }
          if (verifyOutline.enabled) {
            val groupId = verifyOutline.register(VCombVerify, cvFields)
            w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(cvWidths)})) " +
              s"_v2_verify_rescan($groupId, ${dir > 0}, 0, $W);")
          } else {
            w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(cvWidths)})) for (int L = 0; L < $W; L++) {")
            withLaneVar("L") {
              for (t <- tids) res.nodes(t).role match {
                case RVerify(r) =>
                  combVerifyLinesStr(r, "L", dir, W).foreach(l => w.writeLines(4, l))
                case _ =>
              }
            }
            w.writeLines(3, "}")
          }
          w.writeLines(2, "}")
          w.writeLines(2, "#endif")
      }
    }

  /** Verification image for an oracled register whose RTL next-state was
    * proven to be an identity under the active quiet guard.  Comparing the
    * adjacent injected states is exactly the original next[k] == r[k+/-1]
    * check with the proven substitution next[k] := r[k]; no RTL expression
    * or next-state lane array needs to run on the quiet path. */
  private def emitQuietHoldVerifyGroup(res: Result, W: Int, tids: Seq[Int],
      dir: Int, verifyOutline: VerifyOutlineRegistry, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    if (tids.isEmpty) return
    val regs = tids.flatMap(t => res.nodes(t).role match {
      case RVerify(r) => Some(res.regs(r))
      case _ => None
    })
    val widths = regs.map(r => firrtl.bitWidth(r.tpe).toInt)
    val (lo, hi) = if (dir > 0) (0, W - 1) else (1, W)
    w.writeLines(2, s"// [vec oracle-verify-quiet-hold] ${regs.size} templates x $W lanes")
    w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
    w.writeLines(2, "if (done_reset && checks_enabled && update_registers) {")
    if (W > 1) {
      vaccDecls(widths).foreach(w.writeLines(3, _))
      withLaneVar("L") {
        emitVerifyReduction(regs.map(r =>
          verifyReductionTerm(firrtl.bitWidth(r.tpe).toInt, r.name, r.name, lo, dir, W)),
          W, lo, hi, tail = true, w = w)
      }
      if (verifyOutline.enabled) {
        val fields = tids.flatMap(t => res.nodes(t).role match {
          case RVerify(r) => Some(r)
          case _ => None
        })
        val groupId = verifyOutline.register(VRegQuietHoldVerify, fields)
        w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(widths)})) " +
          s"_v2_verify_rescan($groupId, ${dir > 0}, $lo, $hi);")
      } else {
        w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(widths)})) for (int L = $lo; L < $hi; L++) {")
        withLaneVar("L") {
          for (r <- regs)
            quietHoldVerifyLinesStr(r, "L", dir, W).foreach(l => w.writeLines(4, l))
        }
        w.writeLines(3, "}")
      }
    }
    // Quiet identity (next == r): the boundary lane's next-state is its own
    // injected value; carry it for the following sweep's boundary check.
    w.writeLines(3, s"// [boundary-carry] ${regs.size} last-lane values (quiet identity)")
    for (r <- regs) w.writeLines(3, boundaryCarryStoreStr(r, r.name, W, dir))
    w.writeLines(2, "}")
    w.writeLines(2, "#endif")
  }

  /** Loud windows retain the complete RTL-next verifier. Quiet windows use
    * adjacent-oracle checks only for the registers covered by the identity
    * proof; unrelated fields in the same fused verify run stay unchanged. */
  private def emitColdDualVerifyGroup(res: Result, W: Int, tids: Seq[Int],
      dir: Int, tier: ColdGuard.Tier, quietFlag: String,
      verifyOutline: VerifyOutlineRegistry, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    if (W == 1) { emitRunGroup(res, W, CVerify, tids, dir, verifyOutline, w); return }
    val (holdTids, ordinaryTids) = tids.partition(t => res.nodes(t).role match {
      case RVerify(r) => tier.quietOracleHoldRegs.contains(r)
      case _ => false
    })
    require(holdTids.nonEmpty,
      "cold dual verifier requires at least one quiet oracle-hold register")
    w.writeLines(2, s"// [vec oracle-verify] ${tids.size} templates x $W lanes " +
      s"[cold-guarded: quiet rewrites ${holdTids.size} RTL-next checks]")
    w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
    w.writeLines(2, s"if (UNLIKELY(!$quietFlag)) {")
    emitRunGroup(res, W, CVerify, tids, dir, verifyOutline, w)
    w.writeLines(2, "} else {")
    if (ordinaryTids.nonEmpty)
      emitRunGroup(res, W, CVerify, ordinaryTids, dir, verifyOutline, w)
    emitQuietHoldVerifyGroup(res, W, holdTids, dir, verifyOutline, w)
    w.writeLines(2, "}")
    w.writeLines(2, "#endif")
  }

  /** Compute one cumulative quiet-stage flag. Base starts with reset and its
    * named guard reductions. An extra stage starts loud unless its parent is
    * already quiet, then ORs only its newly-added predicate guards. */
  private def emitColdGuardReduce(W: Int, tier: ColdGuard.Tier, quietFlag: String,
      parentFlag: Option[String], w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    w.writeLines(2, s"// [v2 cold-guard ${tier.label}] ${tier.guards.map(_.desc).mkString(" | ")}")
    w.writeLines(2, "{")
    parentFlag match {
      case Some(parent) => w.writeLines(3, s"uint64_t _cg = $parent ? 0 : 1;")
      case None => w.writeLines(3, "uint64_t _cg = essent_to_u64(reset);")
    }
    for (g <- tier.guards) {
      g.name.foreach(n => w.writeLines(3, wordOrReduceLines(n, 0, W, W, "_cg")))
      g.pred.foreach { p =>
        val body = withLaneVar("L") { emitExpr(p) }
        w.writeLines(3, s"for (int L = 0; L < $W; L++) _cg |= essent_to_u64($body);")
      }
    }
    w.writeLines(3, s"$quietFlag = (_cg == 0);")
    w.writeLines(2, "}")
  }

  /** Broadcast-only serial source: every lane holds the boundary lane's
    * value. Used as the quiet arm of serial blocks whose gwen is proven zero
    * in quiet windows. The loop covers ALL lanes (the boundary lane rewrites
    * its own value): a partial-range store compiles to unaligned + masked
    * vector stores that no later wide load can forward from. */
  private def broadcastOnlyStr(ri: RegInfo, W: Int, dir: Int)
      (implicit rn: Renamer): Seq[String] = {
    val rL = rn.emitForLane(ri.name, "L")
    val boundary = rn.emitForLane(ri.name, if (dir > 0) "0" else (W - 1).toString)
    Seq("{", s"  const ${genCppType(ri.tpe)} _gv = $boundary;", "  ESSENT_LANE_LOOP",
      s"  for (int L = 0; L < $W; L++) $rL = _gv;", "}")
  }

  /** OR-reduce lanes [lo, hi) of a UInt<1> lane array into `acc`: whole
    * 8-byte chunks when the array length allows, else a byte loop. Reducing
    * the full array where only a sub-range is needed is a safe
    * overapproximation for guard uses (the guarded fallback path is always
    * semantically valid). */
  private def wordOrReduceLines(name: String, lo: Int, hi: Int, W: Int, acc: String)
      (implicit rn: Renamer): String = {
    val elem0 = rn.emitForLane(name, "0")
    if (W % 8 == 0)
      s"{ const uint64_t* _gq = (const uint64_t*)&$elem0; " +
        s"for (int Q = 0; Q < ${W / 8}; Q++) $acc |= _gq[Q]; }"
    else {
      val l = rn.emitForLane(name, "L")
      s"for (int L = $lo; L < $hi; L++) $acc |= essent_to_u64($l);"
    }
  }

  /** A fused comb group containing quiet-specializable templates: full form
    * behind the active stage flag, constant-propagated form (dead templates dropped)
    * otherwise. Declarations are hoisted so both arms and every later group
    * see the arrays. */
  private def emitColdDualCombGroup(res: Result, W: Int, tids: Seq[Int],
      tier: ColdGuard.Tier, quietFlag: String,
      coldCombOutline: ColdCombOutlineRegistry, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    val quietTids = tids.filterNot(tier.deadTids.contains)
    val nSpec = quietTids.count(tier.quietStmt.contains)
    w.writeLines(2, s"// [vec comb] ${tids.size} templates x $W lanes " +
      s"[cold-guarded ${tier.label}: quiet drops ${tids.size - quietTids.size}, specializes $nSpec]")
    for (t <- tids; name <- res.nodes(t).produces) {
      val tpe = rn.nameToMeta(name).sigType
      rn.simdArrayDecl(name, genCppType(tpe)).foreach(d => w.writeLines(2, d))
    }
    w.writeLines(2, s"if (UNLIKELY(!$quietFlag)) {")
    if (coldCombOutline.enabled) {
      val groupId = coldCombOutline.register(tids)
      w.writeLines(3, s"_v2_cold_comb_full($groupId);")
    } else {
      w.writeLines(3, "ESSENT_LANE_LOOP")
      w.writeLines(3, s"for (int L = 0; L < $W; L++) {")
      for (t <- tids)
        withLaneVar("L") { w.writeLines(4, emitCombStmt(res.nodes(t).stmt)) }
      w.writeLines(3, "}")
    }
    if (quietTids.nonEmpty) {
      w.writeLines(2, "} else {")
      w.writeLines(3, s"// [vec comb-quiet] ${quietTids.size} templates x $W lanes")
      w.writeLines(3, "ESSENT_LANE_LOOP")
      w.writeLines(3, s"for (int L = 0; L < $W; L++) {")
      for (t <- quietTids) {
        val s = tier.quietStmt.getOrElse(t, res.nodes(t).stmt)
        withLaneVar("L") { w.writeLines(4, emitCombStmt(s)) }
      }
      w.writeLines(3, "}")
    }
    w.writeLines(2, "}")
  }

  /** One cold member dispatcher for every distinct full comb group. Both split
    * directions call the same case, removing the original image from the hot
    * eval bodies while keeping the quiet image inline. */
  private def emitColdCombOutlineHelper(res: Result, W: Int,
      outline: ColdCombOutlineRegistry, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    if (!outline.enabled || outline.groups.isEmpty) return

    w.writeLines(1, "ESSENT_COLD_NOINLINE void _v2_cold_comb_full(int _v2_group) {")
    w.writeLines(2, "switch (_v2_group) {")
    for ((group, id) <- outline.groups) {
      w.writeLines(3, s"case $id: {")
      w.writeLines(4, "ESSENT_LANE_LOOP")
      w.writeLines(4, s"for (int L = 0; L < $W; L++) {")
      for (t <- group.tids)
        withLaneVar("L") { w.writeLines(5, emitCombStmt(res.nodes(t).stmt)) }
      w.writeLines(4, "}")
      w.writeLines(4, "break;")
      w.writeLines(3, "}")
    }
    w.writeLines(3, "default: break;")
    w.writeLines(2, "}")
    w.writeLines(1, "}")
    w.writeLines(0, "")
  }

  /** Commit group containing identity-hold registers: their quiet $next is
    * the register itself, so the copy is skipped when quiet. */
  private def emitColdDualCommitGroup(res: Result, W: Int, allTids: Seq[Int],
      quietTids: Seq[Int], quietFlag: String,
      coldCommitOutline: ColdCommitOutlineRegistry, boundaryLane: String, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    def wanted(t: Int): Boolean = res.nodes(t).role match {
      case RRegCommit(r) => commitWanted(r, res.regs(r))
      case _ => false
    }
    val activeAllTids = allTids.filter(wanted)
    val activeQuietTids = quietTids.filter(wanted)
    if (activeAllTids.isEmpty) return
    def loop(tids: Seq[Int], indent: Int): Unit = {
      // Boundary-lane commits; see commitCallStr.
      for (t <- tids) res.nodes(t).role match {
        case RRegCommit(r) =>
          w.writeLines(indent, commitCallStr(r, res.regs(r), W, boundaryLane))
        case _ =>
      }
    }
    w.writeLines(2, s"// [vec commit] ${activeAllTids.size} templates x $W lanes " +
      s"[cold-guarded: quiet skips ${activeAllTids.size - activeQuietTids.size} identity commits]")
    w.writeLines(2, "if (update_registers) {")
    w.writeLines(2, s"if (UNLIKELY(!$quietFlag)) {")
    if (coldCommitOutline.enabled) {
      val groupId = coldCommitOutline.register(activeAllTids)
      w.writeLines(3, s"_v2_cold_commit_full($groupId, $boundaryLane);")
    } else loop(activeAllTids, 3)
    if (activeQuietTids.nonEmpty) {
      w.writeLines(2, "} else {")
      loop(activeQuietTids, 3)
    }
    w.writeLines(2, "}")
    w.writeLines(2, "}")
  }

  /** Shared full commit loops. Callers retain the update_registers guard and
    * quiet copy subset; only the rare full copy is moved out of both evals. */
  private def emitColdCommitOutlineHelper(res: Result, W: Int,
      outline: ColdCommitOutlineRegistry, w: Writer)
      (implicit rn: Renamer): Unit = {
    if (!outline.enabled || outline.groups.isEmpty) return

    // Shared between both sweep directions: the caller passes the boundary
    // lane the following sweep reads (W-1 after forward, 0 after reverse).
    w.writeLines(1, "ESSENT_COLD_NOINLINE void _v2_cold_commit_full(int _v2_group, int _v2_bk) {")
    w.writeLines(2, "(void)_v2_bk;")
    w.writeLines(2, "switch (_v2_group) {")
    for ((group, id) <- outline.groups) {
      w.writeLines(3, s"case $id: {")
      // Boundary-lane commits; see commitCallStr.
      for (t <- group.tids) res.nodes(t).role match {
        case RRegCommit(r) =>
          w.writeLines(4, commitCallStr(r, res.regs(r), W, "_v2_bk"))
        case _ =>
      }
      w.writeLines(4, "break;")
      w.writeLines(3, "}")
    }
    w.writeLines(3, "default: break;")
    w.writeLines(2, "}")
    w.writeLines(1, "}")
    w.writeLines(0, "")
  }

  private def sccDesc(res: Result, scc: Int): String = {
    val ms = res.sccOf.collect { case (t, s) if s == scc => t }.toSeq
    val regs = ms.flatMap(t => res.nodes(t).role match {
      case RRegSource(r) => Some(r.split('.').last)
      case _ => None
    }).sorted
    val nComb = ms.count(t => res.nodes(t).role == RComb)
    s"${ms.size} templates ($nComb comb), regs=[${regs.take(4).mkString(",")}${if (regs.size > 4) s",+${regs.size - 4}" else ""}]"
  }

  private def serialChainLoopStr(ri: RegInfo, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] =
    ri.plan match {
      case RPCondHold => condHoldScanStr(ri, W, dir)
      case RPAffineScan => affineScanStr(ri, W, dir)
      case RPSerialNext(_, true) if W > 1 => guardedSerialChainStr(ri, W, dir)
      case _ =>
        val loop =
          if (dir > 0) s"for (int L = 1; L < $W; L++) ${sourceLineStr(ri, "L", dir)}"
          else s"for (int L = ${W - 2}; L >= 0; L--) ${sourceLineStr(ri, "L", dir)}"
        Seq(loop)
    }

  /** Guarded serial chain (RMW registers with a proven self-free wen):
    * next ≡ wen ? wdata(r) : r, so a window whose wen lanes are all zero
    * reduces the chain to a broadcast of the boundary lane — the degenerate
    * hold-monoid prefix scan. CSR write instructions are rare, so the fast
    * path covers almost every window; non-zero windows run the original
    * serial chain unchanged (bit-identical semantics either way).
    *   forward: chain lanes 1..W-1 read wen[0..W-2]
    *   reverse: chain lanes W-2..0 read wen[1..W-1] */
  private def guardedSerialChainStr(ri: RegInfo, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    val gwenL = rn.emitForLane(ri.name + "$gwen", "L")
    val rL = rn.emitForLane(ri.name, "L")
    val boundary = rn.emitForLane(ri.name, if (dir > 0) "0" else (W - 1).toString)
    val (glo, ghi) = if (dir > 0) (0, W - 1) else (1, W)
    // Full-range broadcast (boundary lane self-stores): aligned full-width
    // vector stores, forwardable to later wide loads of the array.
    val bcast = s"for (int L = 0; L < $W; L++) $rL = _gv;"
    val chain =
      if (dir > 0) s"for (int L = 1; L < $W; L++) ${sourceLineStr(ri, "L", dir)}"
      else s"for (int L = ${W - 2}; L >= 0; L--) ${sourceLineStr(ri, "L", dir)}"
    Seq(
      "{",
      s"  uint64_t _gany = 0;",
      s"  ${wordOrReduceLines(ri.name + "$gwen", glo, ghi, W, "_gany")}",
      s"  if (_gany == 0) {",
      s"    const ${genCppType(ri.tpe)} _gv = $boundary;",
      s"    ESSENT_LANE_LOOP",
      s"    $bcast",
      s"  } else {",
      s"    $chain",
      s"  }",
      "}")
  }

  /** Parallel prefix form of:
    *   forward: r[k] = wen[k-1] ? wdata[k-1] : r[k-1]
    *   reverse: r[k] = wen[k+1] ? wdata[k+1] : r[k+1]
    *
    * Pair scan is last-write-wins over (valid, value), seeded with the boundary
    * lane as a valid carry. This removes the lane-by-lane scalar store chain,
    * so following vector consumers see one vector-friendly write to r[].
    */
  private def condHoldScanStr(ri: RegInfo, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    if (W <= 1) return Seq()
    val r = rn.simdBase(ri.name).getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}"))
    val wen = rn.simdBase(ri.name + "$wen").getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}$$wen"))
    val wdataName = condHoldWdataAliases.getOrElse(ri.name + "$wdata", ri.name + "$wdata")
    val wdata = rn.simdBase(wdataName).getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for $wdataName"))
    val fn = if (dir > 0) "essent_condhold_scan_fwd" else "essent_condhold_scan_rev"
    Seq(s"$fn<$W>($r, $wen, $wdata);")
  }

  /** Affine prefix scan call: r[k] = keep[k-1] ? r[k-1] + add[k-1] : add[k-1]
    * (forward; mirrored for the reverse half), seeded with the boundary lane. */
  private def affineScanStr(ri: RegInfo, W: Int, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    if (W <= 1) return Seq()
    val r = rn.simdBase(ri.name).getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}"))
    val keep = rn.simdBase(ri.name + "$keep").getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}$$keep"))
    val add = rn.simdBase(ri.name + "$add").getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}$$add"))
    val fn = if (dir > 0) "essent_affine_scan_fwd" else "essent_affine_scan_rev"
    Seq(s"$fn<$W>($r, $keep, $add);")
  }

  private def condHoldIndexName(group: Int): String = s"_v2_cond_idx_$group"

  /** One member of a shared-write-enable cond-hold bundle. The first member
    * reached in this eval computes the group's last-writer index from its own
    * (structurally identical) wen array; later fields reuse that index. */
  private def sharedCondHoldStr(ri: RegInfo, W: Int, dir: Int,
      group: Int, buildIndex: Boolean)
      (implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] = {
    if (W <= 1) return Seq.empty
    val r = rn.simdBase(ri.name).getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}"))
    val wen = rn.simdBase(ri.name + "$wen").getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for ${ri.name}$$wen"))
    val wdataName = condHoldWdataAliases.getOrElse(ri.name + "$wdata", ri.name + "$wdata")
    val wdata = rn.simdBase(wdataName).getOrElse(
      throw new IllegalStateException(s"[v2] missing SIMD base for $wdataName"))
    val idx = condHoldIndexName(group)
    val suffix = if (dir > 0) "fwd" else "rev"
    val build = if (buildIndex)
      Seq(s"essent_condhold_index_$suffix<$W>($idx, $wen);") else Seq.empty
    build :+ s"essent_condhold_apply_$suffix<$W>($r, $idx, $wdata);"
  }

  /** Merged body: one function shared by both zig-zag directions. Vector comb
    * and commit runs are direction-independent and emitted once; sources,
    * injects and verifies differ only in index arithmetic and get small
    * `if (_forward)` branches; serial chain loops branch on direction too.
    * Only valid when every serial region is a singleton chain (checked by the
    * caller): the region-level quotient order of the forward schedule is then
    * a valid order for the reverse direction as well. */
  private def emitMergedEval(res: Result, W: Int, fuseCap: Int,
      cold: Option[ColdGuard.Spec], coldCombOutline: ColdCombOutlineRegistry,
      coldCommitOutline: ColdCommitOutlineRegistry,
      verifyOutline: VerifyOutlineRegistry, w: Writer,
      scratchTrace: Option[ScratchBlockTrace] = None)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    rn.resetDeclaredArrays()
    // Merged emission is selected only when every residual serial SCC is a
    // singleton, so every grouped cond-hold member is whole-chain safe.
    val sharedCondHoldGroups: Set[Int] =
      if (W <= 1) Set.empty else res.condHoldGroupOf.valuesIterator.toSet
    val builtCondHoldGroups = mutable.Set[Int]()
    w.writeLines(1, "__attribute__((noinline)) void eval_dir(bool _forward, bool update_registers, bool verbose, bool done_reset) {")
    w.writeLines(2, "(void)verbose;")
    sharedCondHoldGroups.toSeq.sorted.foreach { group =>
      w.writeLines(2, s"int16_t ${condHoldIndexName(group)}[$W];")
    }
    w.writeLines(2, s"// [v2 schedule] merged body, ${res.scheduleFwd.size} units, " +
      s"${res.serialTemplateCount} serial chain(s), ${res.oracles.size} oracle streams")

    def catOf(u: SchedUnit): Option[FuseCat] = u match {
      case UVec(t) => res.nodes(t).role match {
        case RComb            => Some(if (endpointNextTids(t)) CBoundaryComb else CComb)
        case REffect          => Some(CEffect)  // perf: keep calls/assert stores out of vector loops
        case RRegSource(_)    => Some(CSource)
        case RRegCommit(_)    => Some(CCommit)
        case RStateRead(_)    => Some(CStateRead)
        case RStateCommit(_)  => Some(CStateCommit)
        case ROracleInject(r) => Some(if (res.regs.contains(r)) COracle else CCombOracle)
        case RVerify(r)       => Some(if (res.regs.contains(r)) CVerify else CCombVerify)
      }
      case _ => None
    }
    // Commits write the boundary lane of the following sweep (W-1 after
    // forward, 0 after reverse), so they are emitted per direction too.
    def dirIndependent(cat: FuseCat): Boolean = cat match {
      case CComb | CBoundaryComb | CEffect => true
      case _ => false
    }

    val buf = ArrayBuffer[Int]()
    var bufCat: Option[FuseCat] = None
    val coldPlan = new ColdEmitPlan(cold, W, w, scratchTrace)
    coldPlan.start()

    def flushRun(): Unit = {
      if (buf.isEmpty) return
      val groups = if (fuseCap > 0) buf.toSeq.grouped(fuseCap).toSeq else Seq(buf.toSeq)
      val cat = bufCat.get
      for (raw <- groups; g <- coldPlan.stageRuns(cat == CComb, raw)) {
        scratchTrace.foreach(_.recordTids(g))
        val stateStage = coldPlan.base
        val combStage = if (cat == CComb) coldPlan.comb(g) else None
        def holdReg(t: Int): Option[String] = res.nodes(t).role match {
          case RRegCommit(r) if stateStage.exists { stage =>
            stage.tier.quietHoldRegs.contains(r) ||
              stage.tier.quietOracleHoldRegs.contains(r)
          } => Some(r)
          case _ => None
        }
        val dualCommit = cat == CCommit && stateStage.isDefined &&
          g.exists(t => holdReg(t).isDefined)
        val dualVerify = cat == CVerify && stateStage.exists { stage =>
          g.exists(t => res.nodes(t).role match {
            case RVerify(r) => stage.tier.quietOracleHoldRegs.contains(r)
            case _ => false
          })
        }
        if (combStage.isDefined) {
          val stage = combStage.get
          emitColdDualCombGroup(res, W, g, stage.tier, stage.flag, coldCombOutline, w)
        } else if (dualCommit) {
          emitColdDualCommitGroup(res, W, g, g.filter(t => holdReg(t).isEmpty),
            stateStage.get.flag, coldCommitOutline, s"(_forward ? ${W - 1} : 0)", w)
        } else if (dualVerify) {
          w.writeLines(2, "if (_forward) {")
          emitColdDualVerifyGroup(res, W, g, +1, stateStage.get.tier,
            stateStage.get.flag, verifyOutline, w)
          w.writeLines(2, "} else {")
          emitColdDualVerifyGroup(res, W, g, -1, stateStage.get.tier,
            stateStage.get.flag, verifyOutline, w)
          w.writeLines(2, "}")
        } else if (dirIndependent(cat))
          emitRunGroup(res, W, cat, g, dir = +1, verifyOutline, w)
        else {
          // declarations hoisted out of the branch so both arms see them
          for (t <- g; name <- res.nodes(t).produces) {
            val tpe = rn.nameToMeta(name).sigType
            rn.simdArrayDecl(name, genCppType(tpe)).foreach(d => w.writeLines(2, d))
          }
          w.writeLines(2, "if (_forward) {")
          emitRunGroup(res, W, cat, g, dir = +1, verifyOutline, w, declare = false)
          w.writeLines(2, "} else {")
          emitRunGroup(res, W, cat, g, dir = -1, verifyOutline, w, declare = false)
          w.writeLines(2, "}")
        }
        coldPlan.progress(g)
      }
      buf.clear()
      bufCat = None
    }

    def emitSerialChain(ri: RegInfo): Unit = {
      scratchTrace.foreach(_.recordTids(Seq(ri.sourceId)))
      val stage = coldPlan.base
      val quietBcast = stage.exists(_.tier.quietZeroGwenRegs.contains(ri.name))
      if (quietBcast) {
        val quietFlag = stage.get.flag
        w.writeLines(2, s"if (UNLIKELY(!$quietFlag)) {")
        w.writeLines(3, "if (_forward) {")
        serialChainLoopStr(ri, W, +1).foreach(l => w.writeLines(4, l))
        w.writeLines(3, "} else {")
        serialChainLoopStr(ri, W, -1).foreach(l => w.writeLines(4, l))
        w.writeLines(3, "}")
        w.writeLines(2, "} else {")
        w.writeLines(3, "if (_forward) {")
        broadcastOnlyStr(ri, W, +1).foreach(l => w.writeLines(4, l))
        w.writeLines(3, "} else {")
        broadcastOnlyStr(ri, W, -1).foreach(l => w.writeLines(4, l))
        w.writeLines(3, "}")
        w.writeLines(2, "}")
      } else {
        res.condHoldGroupOf.get(ri.name).filter(sharedCondHoldGroups).fold {
          w.writeLines(2, "if (_forward) {")
          serialChainLoopStr(ri, W, +1).foreach(l => w.writeLines(3, l))
          w.writeLines(2, "} else {")
          serialChainLoopStr(ri, W, -1).foreach(l => w.writeLines(3, l))
          w.writeLines(2, "}")
        } { group =>
          val buildIndex = builtCondHoldGroups.add(group)
          w.writeLines(2, "if (_forward) {")
          sharedCondHoldStr(ri, W, +1, group, buildIndex)
            .foreach(l => w.writeLines(3, l))
          w.writeLines(2, "} else {")
          sharedCondHoldStr(ri, W, -1, group, buildIndex)
            .foreach(l => w.writeLines(3, l))
          w.writeLines(2, "}")
        }
      }
      coldPlan.progress(Seq(ri.sourceId))
    }

    val boundaryRegs = boundaryVerifyRegs(res, res.scheduleFwd)
    if (boundaryRegs.nonEmpty) {
      w.writeLines(2, "if (_forward) {")
      emitBoundaryVerifyBlock(res, W, boundaryRegs, +1, w)
      w.writeLines(2, "} else {")
      emitBoundaryVerifyBlock(res, W, boundaryRegs, -1, w)
      w.writeLines(2, "}")
    }

    val sched = res.scheduleFwd.toIndexedSeq
    val seenScc = mutable.Set[Int]()
    val chainDone = mutable.Set[Int]()
    var i = 0
    while (i < sched.size) {
      val u = sched(i)
      catOf(u) match {
        case some @ Some(_) =>
          if (bufCat.isDefined && bufCat != some) flushRun()
          bufCat = some
          buf += u.tid
          if (coldPlan.endsAt(u.tid)) flushRun()
          i += 1
        case None =>
          val ULane(t, k) = u: @unchecked
          val role = res.nodes(t).role
          if (!role.isInstanceOf[RRegSource])
            throw new IllegalStateException(
              s"[v2] merged emission expects singleton serial chains, got $role")
          // The whole chain is emitted atomically, anchored at its first
          // non-boundary lane: lane 0 (fwd) has no statement and no in-edges
          // (it can be scheduled before the chain's operand producers), while
          // lane 1's position guarantees all shared operand producers are
          // already emitted — for both directions, since region-level edges
          // are direction-independent. Later lanes of the chain are skipped.
          if (!chainDone.contains(t) && k >= 1) {
            flushRun()
            val ri = res.regs(role.asInstanceOf[RRegSource].reg)
            val scc = res.sccOf.getOrElse(t, -1)
            if (seenScc.add(scc))
              w.writeLines(2, s"// [serial scc=$scc] ${sccDesc(res, scc)}")
            w.writeLines(2, s"// [serial scc=$scc chain-loop]")
            emitSerialChain(ri)
            chainDone += t
          }
          i += 1
      }
    }
    flushRun()

    w.writeLines(2, "if (update_registers) oracle_boundary_valid = done_reset && checks_enabled;")
    w.writeLines(2, "if (done_reset && checks_enabled && update_registers && assert_triggered) exit(assert_exit_code);")
    w.writeLines(2, "if (!done_reset || !checks_enabled) assert_triggered = false;")
    w.writeLines(2, s"if (!_forward && update_registers && done_reset) { oracle_cycle += ${2 * W}; oracle_win_base += ORACLE_BLOCK_BYTES; }")
    w.writeLines(1, "}")
    w.writeLines(0, "")
  }

  /** Comb/effect statement rendered for the current lane var. */
  private def emitCombStmt(stmt: Statement)(implicit rn: Renamer, ctx: essent.EmitContext): Seq[String] =
    stmt match {
      case EmptyStmt => Seq()  // pruned dead comb template
      case d: DefNode if condHoldWdataAliases.contains(d.name) => Seq()
      case lt: essent.ir.LookupTable if lt.bitmap =>
        // Membership bitmap: `x in {c_0..c_n}` as bit x of a packed constant
        // table — one load + shift + mask per lane instead of n compares + n
        // ORs. Perf: Rocket's 100-term CSR-address decode was 21% of kernel
        // time as a serial k-mask reduction; as a bitmap the statement drops
        // from ~1051 to ~40 static instructions and its lane loop vectorizes
        // (gather + vpsrlv + vpand). Index safety comes from the FIRRTL type:
        // a UInt<w> lane value is always < 2^w and the table has 2^w bits.
        // The packed table itself is emitted once at file scope by
        // emitLookupTables (2026-09-04): a block-scope `static const` inside a
        // per-lane serial statement was a distinct object per lane and per
        // direction — AES carried 565 copies of its 48 S-box tables (1.1 MB)
        // and ran its lookups out of L2/L3.
        val lutVar = lutTableName(lt)
        val idxVar = s"_bmi_${lt.name.replace('.', '$')}"
        Seq(
          "{",
          s"const uint64_t $idxVar = essent_to_u64(${emitExpr(lt.indexExpr)});",
          s"${rn.emitForLane(lt.name, laneTok)} = ${genCppType(lt.resultType)}(($lutVar[$idxVar >> 6] >> ($idxVar & 63)) & 1);",
          "}")
      case lt: essent.ir.LookupTable =>
        // Decode LUT: dense constant table indexed by the shared priority
        // index. `static const` inside the lane loop is a single object.
        // Dense table hoisted to file scope in its narrowest integer type
        // (see emitLookupTables); the statement only indexes it.
        val lutVar = lutTableName(lt)
        Seq(
          s"${rn.emitForLane(lt.name, laneTok)} = ${genCppType(lt.resultType)}($lutVar[essent_to_u64(${emitExpr(lt.indexExpr)})]);")
      case d: DefNode =>
        val lhs = rn.emitForLane(d.name, laneTok)
        emitPrimitiveUIntAssign(lhs, d.value.tpe, d.value)
          .map(Seq(_))
          .getOrElse(Seq(s"$lhs = ${emitExpr(d.value)};"))
      case c: Connect =>
        val lhs = emitExprRaw(c.loc)
        val lhsLane = rn.emitForLane(lhs, laneTok)
        emitPrimitiveUIntAssign(lhsLane, c.loc.tpe, c.expr)
          .map(Seq(_))
          .getOrElse(Seq(s"$lhsLane = ${emitExpr(c.expr)};"))
      case other => emitStmt(other)
    }

  // current lane token from Emitter's laneVar (we always set it around calls)
  private var _lane: String = "L"
  private def laneTok: String = _lane
  private def withLaneVar[T](lv: String)(f: => T): T = {
    val old = _lane; _lane = lv
    val r = essent.Emitter.withLaneVar(lv)(f)
    _lane = old
    r
  }

  private def sourceLineStr(r: RegInfo, k: String, dir: Int)
      (implicit rn: Renamer, ctx: essent.EmitContext): String = {
    val prev = if (dir > 0) s"$k - 1" else s"$k + 1"
    r.plan match {
      case RPCondHold =>
        val wdata = condHoldWdataAliases.getOrElse(r.name + "$wdata", r.name + "$wdata")
        val enable = s"essent_to_u64(${rn.emitForLane(r.name + "$wen", prev)})"
        val yes = rn.emitForLane(wdata, prev)
        val no = rn.emitForLane(r.name, prev)
        if (envBool("V2_SMALL_STATE_SELECT", default = false) &&
            r.tpe.isInstanceOf[UIntType] && bitWidth(r.tpe) <= 64) {
          smallSelectRegisters += r.name
          val word = if (bitWidth(r.tpe) <= 32) "uint32_t" else "uint64_t"
          s"${rn.emitForLane(r.name, k)} = ${genCppType(r.tpe)}(" +
            s"essent_select_word<$word>($enable != 0, essent_to_u64($yes), essent_to_u64($no)));"
        } else s"${rn.emitForLane(r.name, k)} = $enable ? $yes : $no;"
      case RPAffineScan =>
        val t = genCppType(r.tpe)
        val keep = rn.emitForLane(r.name + "$keep", prev)
        val add = rn.emitForLane(r.name + "$add", prev)
        s"${rn.emitForLane(r.name, k)} = $t(essent_to_u64($keep) ? " +
        s"(essent_to_u64(${rn.emitForLane(r.name, prev)}) + essent_to_u64($add)) : essent_to_u64($add));"
      case RPSerialNext(folded, _) =>
        // Whole folded expression rendered at the previous lane; the embedded
        // self-reference then reads r[k-1] — the serial chain semantics.
        // Mask/blend rendering (V2_SERIAL_MASK_BLEND=1) measured WORSE as a
        // default (full-verify 118 -> 178 ns/cycle on sodor W=16): serial wen
        // conditions are heavily biased, so predicted ternary branches that
        // evaluate one side beat blends that always evaluate both — the same
        // lesson as the vec-comb essent_mux experiment. Kept as an opt-in for
        // guarded chains whose slow path rarely executes.
        val lhs = rn.emitForLane(r.name, k)
        val blend = envBool("V2_SERIAL_MASK_BLEND", default = false)
        val small = if (envBool("V2_SMALL_STATE_SELECT", default = false) && cheapScalarChoice(folded))
          withLaneVar(prev) {
            emitPrimitiveUIntAssign(lhs, r.tpe, folded)(rn, ctx.copy(scalarMuxSelect = true))
          } else None
        if (small.isDefined) smallSelectRegisters += r.name
        small.orElse(if (blend) withLaneVar(prev) { emitPrimitiveUIntAssign(lhs, r.tpe, folded) } else None)
          .getOrElse {
            val rhs = withLaneVar(prev) { emitExpr(folded) }
            s"$lhs = $rhs;"
          }
      case _ =>
        s"${rn.emitForLane(r.name, k)} = ${rn.emitForLane(r.nextName, prev)};"
    }
  }

  /** Guard: emitted only under `if (done_reset)` (hoisted, loop-invariant);
    * during reset the register keeps its value, so no else branch exists. */
  private def oracleLineStr(r: RegInfo, spec: OracleSpec, k: String, dir: Int, W: Int)
      (implicit rn: Renamer): String = {
    // v4: in-block element index — fwd lane k reads element k, rev lane k
    // reads element 2W-1-k of the current super-window's slot.
    val idx = if (dir > 0) s"($k)" else s"${2 * W - 1} - ($k)"
    val tpe = genCppType(r.tpe)
    if (spec.words > 1)
      s"${rn.emitForLane(r.name, k)}.val[${spec.word}] = (uint64_t)ESSENT_ORACLE_LOAD(${v4StreamExpr(spec.arraySymbol)}, $idx);"
    else
      s"${rn.emitForLane(r.name, k)} = $tpe(ESSENT_ORACLE_LOAD(${v4StreamExpr(spec.arraySymbol)}, $idx));"
  }

  /** Full-window oracle injection as one essent_inject_* call. Perf: the
    * __restrict parameters are what lets the backend vectorize the copy; see
    * the helper definitions in the emitted prelude. Works for register and
    * comb-cut targets alike (`name` is the lane-array flat name). */
  private def injectCallStr(name: String, spec: OracleSpec, dir: Int, W: Int)
      (implicit rn: Renamer): String = {
    if (spec.words > 1) {
      val fn = if (dir > 0) "essent_inject_word_fwd" else "essent_inject_word_rev"
      s"$fn<$W, ${spec.word}>(&${rn.emitForLane(name, "0")}, ${v4StreamExpr(spec.arraySymbol)});"
    } else {
      val fn = if (dir > 0) "essent_inject_fwd" else "essent_inject_rev"
      s"$fn<$W>(&${rn.emitForLane(name, "0")}, ${v4StreamExpr(spec.arraySymbol)});"
    }
  }

  /** Window-boundary register commit. After a forward sweep only lane W-1
    * (the reverse sweep's boundary lane) needs next[]; after a reverse sweep
    * only lane 0. Every other lane is rewritten by the register's shift /
    * serial source before any reader runs in the next sweep, so copying all
    * W lanes only moved cache lines (BOOM W=16: 1,842 full-width copies per
    * sweep -> one element each, 50-100 ns/cycle; deleting every commit
    * measured far more, but only because the dead next cones then folded
    * away under ESSENT_ORACLE_VERIFY=0). Oracle
    * registers that keep their commit (oracleCommitKeep) still copy every
    * lane — hoisted chains read their committed operand lanes at window
    * start — and W=1 has no sources at all, so it keeps the full copy
    * (one essent_commit_lanes memcpy; a lane loop never vectorized).
    * Oracle registers keep the full copy as well: they are re-injected
    * before any reader of the next sweep runs, so the copy is observable
    * only under reset, but gating it on `!done_reset` measured no faster
    * (BOOM W=16 6,530 -> 6,620 ns/cycle; the copy keeps the injected
    * lines warm for the next window's injection). */
  private def commitCallStr(r: String, ri: RegInfo, W: Int, boundaryLane: String)
      (implicit rn: Renamer): String =
    if (W == 1 || ri.plan == RPOracle)
      s"essent_commit_lanes<$W>(&${rn.emitForLane(r, "0")}, &${rn.emitForLane(ri.nextName, "0")});"
    else
      s"${rn.emitForLane(r, boundaryLane)} = ${rn.emitForLane(ri.nextName, boundaryLane)};"

  /** Lane that the following sweep reads as its boundary. */
  private def boundaryLaneStr(W: Int, dir: Int): String = if (dir > 0) (W - 1).toString else "0"

  // Comb cut injection semantics (now emitted through injectCallStr): the
  // value visible DURING cycle k, same-cycle index, only under
  // `if (done_reset)`. During reset (else branch at the emit site) the
  // computed $rtl value does not exist yet (injection schedules before the
  // cone on purpose — that is the cut), so the caller injects a typed zero;
  // architectural reset state is enforced by the registers' own reset muxes,
  // and the first real window is verified.

  /** Mismatch predicate for a comb cut: computed $rtl vs injected, same lane,
    * same cycle. Bool-valued: `!(a == b)` forces the UInt<1> contextual bool
    * conversion (a bare cast from UInt<1> to uint64_t does not compile). */
  private def combVerifyMismatchExpr(name: String, k: String)(implicit rn: Renamer): String =
    s"(!(${rn.emitForLane(name + "$rtl", k)} == ${rn.emitForLane(name, k)}))"

  /** Mismatch predicate for an oracled register: RTL-computed next[k] vs
    * injected r[other]. fwd: other = k+1; rev: other = k-1. Bool-valued. */
  private def verifyMismatchAtExpr(r: RegInfo, k: String, other: String)
      (implicit rn: Renamer): String =
    s"(!(${rn.emitForLane(r.nextName, k)} == ${rn.emitForLane(r.name, other)}))"

  private def verifyMismatchExpr(r: RegInfo, k: String, dir: Int)(implicit rn: Renamer): String = {
    val other = if (dir > 0) s"($k) + 1" else s"($k) - 1"
    verifyMismatchAtExpr(r, k, other)
  }

  /** Hot-path accumulate: OR the mismatch evidence into the group-local
    * `_v2_vacc`. Deliberately no cycle-range guards and no side effects, so
    * the lane loop vectorizes; boundary/padding lanes (trace record 0, zero
    * padding past ORACLE_NUM_CYCLES) may set bits spuriously — the cold
    * rescan re-applies the exact range checks and reports nothing for them.
    * Cost of a spurious pass: one scalar rescan on at most the first window
    * and the windows past the end of the trace.
    *
    * For <=64-bit signals accumulate the raw XOR of the two words instead of
    * a boolean: pure homogeneous integer load/xor/or that the backend turns
    * into a vector OR-reduction; the UInt<1>-to-bool form compiles to scalar
    * setcc chains. Wider signals fall back to the boolean compare. */
  private val verifyWideAcc = sys.env.get("V2_VERIFY_WIDE_ACC").exists(v => v == "1" || v == "true")

  /** v4m: packer pre-mirrors the rev half of every stream slot so both
    * injection passes are straight copies. Advertised through the manifest
    * layout tag — packers that don't know the tag fail loudly instead of
    * packing chronologically under a mirrored kernel. */
  private val premirror = !sys.env.get("V2_NO_PREMIRROR").exists(v => v == "1" || v == "true")

  /** Access-proof oracle values are verification operands only. With the
    * pre-mirrored block layout, their lane order already matches each fixed
    * direction body, so verification can read the block slot directly and
    * avoid materializing an otherwise dead comb-cut array. */
  private val directVerifyOracle = premirror &&
    envBool("V2_DIRECT_VERIFY_ORACLE", default = true)
  private var directVerifyOracles: Set[String] = Set.empty

  /** Oracle registers' commits are dead code (next window is fully injected,
    * rescan reads injected lanes, --dump-final dumps harness state only) —
    * EXCEPT when the register is an operand of a serial/cond-hold chain:
    * whole-chain hoisting reads operand storage at window start expecting the
    * previous window's committed lane values (the cycle-534785 soundness
    * model). Those operands keep their commit; see oracleCommitKeep.
    * Rocket W=16 still misverified its first window with the keep-set
    * heuristics (consumer unidentified — suspected zig-zag boundary handoff
    * through committed storage), so the skip is OPT-IN per configuration:
    * V2_SKIP_ORACLE_COMMIT=1, enabled where the full verification gates
    * prove it (BOOM: green at W=16/32). */
  private val skipOracleCommit = sys.env.get("V2_SKIP_ORACLE_COMMIT").exists(v => v == "1" || v == "true")
  private var oracleCommitKeep: Set[String] = Set.empty

  private def commitWanted(r: String, ri: RegInfo): Boolean =
    !zcInfo.contains(r) &&
      (!skipOracleCommit || ri.plan != RPOracle || oracleCommitKeep.contains(r))

  /** V2_SOURCE_LOOP=1 restores the lane-loop zipper distribute (default:
    * shifted memcpy from the staged snapshot). */
  private val sourceLoop = sys.env.get("V2_SOURCE_LOOP").exists(v => v == "1" || v == "true")

  /** Zero-copy injection: every read of an eligible oracle REGISTER aliases
    * its v4m block slot directly (fwd half; pre-mirrored rev half), through
    * the Renamer's base-override hook — the inject copy, its lane-array
    * traffic, and the commit disappear. Eligible = register oracle, plan
    * RPOracle, unsigned, width <= 64, storage tier == scalar size (raw
    * reinterpret is then layout-exact). Comb cuts keep the copy (their reset
    * else-branch writes a typed zero). Measured VERDICT on BOOM W=16: 2x
    * SLOWER than the inject copy (2590 vs 1328 ns/cycle, all gates green) —
    * the per-window inject copy acts as a software prefetch + L1-resident
    * staging buffer (one cold stream read + N hot lane-array re-reads);
    * aliasing turns every consumer read into a cold streaming-region read.
    * Kept as an opt-in negative-result artifact: V2_ZEROCOPY=1 (requires the
    * harness's zeroed reset block; see gen_harness_*). */
  private val zeroCopy = premirror && sys.env.get("V2_ZEROCOPY").exists(v => v == "1" || v == "true")
  private var zcInfo: Map[String, (Long, Int, String)] = Map.empty // aliased flat -> (blockOff, elemBytes, cppType)
  private var zcSymbols: Map[String, String] = Map.empty
  private var zcScratchOverrides: Map[String, String] = Map.empty
  // Synthetic cond-hold `$wdata` name -> physical source register.  The
  // template and graph edge remain as ordering witnesses, but no temporary
  // lane array or copy is emitted for an exact bank-to-bank forwarding.
  private var condHoldWdataAliases: Map[String, String] = Map.empty

  /** Identifier-safe hoisted-local name for one zero-copied register. */
  private def zcLocal(n: String): String = "_zc_" + n.map(c => if (c.isLetterOrDigit) c else '_')

  private def zcDirOverrides(W: Int, dir: Int): Map[String, String] =
    zcInfo.map { case (n, _) => n -> zcLocal(n) }

  private def zcLocalDecls(W: Int, dir: Int): Seq[String] =
    zcInfo.iterator.map { case (n, (off, eb, cpp)) =>
      val maybeUnused = if (directVerifyOracles.contains(n)) "[[maybe_unused]] " else ""
      val half = if (dir < 0) s" + ${W.toLong * eb}L" else ""
      s"${maybeUnused}const $cpp* __restrict ${zcLocal(n)} = " +
        s"(const $cpp*)((const char*)(oracle_win_base + ${off}L) " +
        s"/* ${zcSymbols(n)} */$half);"
    }.toSeq

  /** Rescan runs with a runtime direction flag; the alias picks the half at
    * runtime. `_forward` is in scope inside _v2_verify_rescan. */
  private def zcRescanOverrides(W: Int): Map[String, String] =
    zcInfo.map { case (n, _) => n -> zcLocal(n) }

  private def zcRescanDecls(W: Int): Seq[String] =
    zcInfo.iterator.map { case (n, (off, eb, cpp)) =>
      val maybeUnused = if (directVerifyOracles.contains(n)) "[[maybe_unused]] " else ""
      s"${maybeUnused}const $cpp* __restrict ${zcLocal(n)} = " +
        s"(const $cpp*)((const char*)(oracle_win_base + ${off}L) " +
        s"/* ${zcSymbols(n)} */ + (_forward ? 0 : ${W * eb}));"
    }.toSeq

  /** Accumulator tier (bits) for one verified signal. Narrow signals share
    * the accumulator of their storage width; >64-bit signals compare to a
    * bool and land in the u8 accumulator. */
  private def verifyTier(widthBits: Int): Int =
    if (widthBits > 64 || widthBits <= 8) 8
    else if (widthBits <= 16) 16 else if (widthBits <= 32) 32 else 64

  /** Group-local accumulator declarations, one per tier present in the
    * group. V2_VERIFY_WIDE_ACC=1 restores the single u64 accumulator (every
    * operand widened through essent_to_u64) for A/B bisection. */
  private def vaccDecls(widths: Seq[Int]): Seq[String] =
    if (verifyWideAcc) Seq("uint64_t _v2_vacc = 0;")
    else widths.map(verifyTier).distinct.sorted.map(t => s"uint${t}_t _v2_vacc$t = 0;")

  private def vaccTestExpr(widths: Seq[Int]): String =
    if (verifyWideAcc) "_v2_vacc != 0"
    else widths.map(verifyTier).distinct.sorted
      .map(t => s"(uint64_t)_v2_vacc$t").mkString("(", " | ", ") != 0")

  private def accumAssign(a: String, b: String, widthBits: Int): String =
    if (verifyWideAcc) {
      if (widthBits <= 64) s"_v2_vacc |= essent_to_u64($a) ^ essent_to_u64($b);"
      else s"_v2_vacc |= (uint64_t)(!($a == $b));"
    } else {
      val t = verifyTier(widthBits)
      if (widthBits <= 64) s"_v2_vacc$t |= (uint${t}_t)(essent_raw($a) ^ essent_raw($b));"
      else s"_v2_vacc$t |= (uint8_t)(!($a == $b));"
    }

  private case class VerifyReductionTerm(width: Int, statement: String,
      blockPointers: Option[(String, String)])

  /** Only complete, unit-stride lane arrays can be loaded as byte blocks.
    * Scalar bindings and compact endpoint storage retain the scalar emitter.
    */
  private def verifyReductionTerm(width: Int, a: String, b: String,
      lo: Int, shift: Int, W: Int)(implicit rn: Renamer): VerifyReductionTerm = {
    val other = if (shift > 0) "(L) + 1" else if (shift < 0) "(L) - 1" else "L"
    val stmt = accumAssign(rn.emitForLane(a, "L"), rn.emitForLane(b, other), width)
    def contiguous(name: String): Boolean = rn.simdBase(name).exists { base =>
      rn.simdStorageLanes(name) == W && rn.emitForLane(name, "L") == s"$base[L]"
    }
    val pointers = if (width <= 64 && contiguous(a) && contiguous(b))
      Some((s"&${rn.emitForLane(a, lo.toString)}",
        s"&${rn.emitForLane(b, (lo + shift).toString)}")) else None
    VerifyReductionTerm(width, stmt, pointers)
  }

  /** Native byte blocks avoid per-field horizontal reductions and widening.
    * XOR differences are ORed, never XORed together, so simultaneous faults
    * cannot cancel. Reporting remains at the original scheduling point.
    */
  private def emitVerifyReduction(terms: Seq[VerifyReductionTerm], W: Int,
      lo: Int, hi: Int, tail: Boolean, w: Writer): Unit = {
    val (blocks, remaining) = terms.partition(_.blockPointers.nonEmpty)
    val packed = envBool("V2_VERIFY_PACKED", default = false) &&
      !verifyWideAcc && W >= 8 && hi > lo && blocks.size >= 2
    def portable(ts: Seq[VerifyReductionTerm]): Unit =
      if (ts.nonEmpty) emitVerifyTierReduction(ts.map(t => t.width -> t.statement),
        W, lo, hi, tail, w)
    if (!packed) portable(terms)
    else {
      w.writeLines(3, "#if ESSENT_VERIFY_PACKED && defined(__AVX512F__) && defined(__AVX512BW__)")
      w.writeLines(3, s"// [verify-packed] ${blocks.size} fields x ${hi - lo} lanes")
      val count = math.min(4, blocks.size)
      val accs = (0 until count).map(i => s"_v2_vpack$i")
      accs.foreach(a => w.writeLines(3, s"__m512i $a = _mm512_setzero_si512();"))
      for ((term, i) <- blocks.zipWithIndex) {
        val (a, b) = term.blockPointers.get
        val acc = accs(i % count)
        w.writeLines(3, s"$acc = _mm512_or_si512($acc, " +
          s"essent_verify_block<${hi - lo}, ${verifyTier(term.width) / 8}>($a, $b));")
      }
      portable(remaining)
      val merged = accs.reduceLeft((a, b) => s"_mm512_or_si512($a, $b)")
      val target = s"_v2_vacc${verifyTier(terms.head.width)}"
      w.writeLines(3, s"const __m512i _v2_vpacked = $merged;")
      w.writeLines(3, s"$target |= _mm512_test_epi64_mask(_v2_vpacked, _v2_vpacked) != 0;")
      w.writeLines(3, "#else")
      portable(terms)
      w.writeLines(3, "#endif")
    }
  }

  private def emitVerifyTierReduction(terms: Seq[(Int, String)], W: Int,
      lo: Int, hi: Int, tail: Boolean, w: Writer): Unit = {
    val split = envBool("V2_VERIFY_SPLIT_TIERS", default = true) &&
      !verifyWideAcc && terms.forall(_._1 <= 64)
    val pragma = if (tail && W > 1) "ESSENT_TAIL_LOOP" else "ESSENT_LANE_LOOP"
    if (!split) {
      w.writeLines(3, pragma)
      w.writeLines(3, s"for (int L = $lo; L < $hi; L++) {")
      terms.sortBy(t => verifyTier(t._1)).foreach(t => w.writeLines(4, t._2))
      w.writeLines(3, "}")
    } else {
      for ((tier, fields) <- terms.groupBy(t => verifyTier(t._1)).toSeq.sortBy(_._1)) {
        val count = math.min(4, fields.size)
        val target = s"_v2_vacc$tier"
        val accs = (0 until count).map(i => s"${target}_p$i")
        w.writeLines(3, s"// [verify-reduction] u$tier: ${fields.size} fields, $count accumulators")
        accs.foreach(a => w.writeLines(3, s"uint${tier}_t $a = 0;"))
        w.writeLines(3, pragma)
        w.writeLines(3, s"for (int L = $lo; L < $hi; L++) {")
        for (((_, statement), i) <- fields.zipWithIndex)
          w.writeLines(4, statement.replace(target + " |=", accs(i % count) + " |="))
        w.writeLines(3, "}")
        w.writeLines(3, s"$target = (uint${tier}_t)(${accs.mkString(" | ")});")
      }
    }
  }

  private def combVerifyAccStr(name: String, tpe: Type, k: String)(implicit rn: Renamer): String =
    accumAssign(rn.emitForLane(name + "$rtl", k), rn.emitForLane(name, k),
      firrtl.bitWidth(tpe).toInt)

  private def verifyAccStr(r: RegInfo, k: String, dir: Int)(implicit rn: Renamer): String = {
    val other = if (dir > 0) s"($k) + 1" else s"($k) - 1"
    accumAssign(rn.emitForLane(r.nextName, k), rn.emitForLane(r.name, other),
      firrtl.bitWidth(r.tpe).toInt)
  }

  private def quietHoldVerifyAccStr(r: RegInfo, k: String, dir: Int)
      (implicit rn: Renamer): String = {
    val other = if (dir > 0) s"($k) + 1" else s"($k) - 1"
    accumAssign(rn.emitForLane(r.name, k), rn.emitForLane(r.name, other),
      firrtl.bitWidth(r.tpe).toInt)
  }

  /** Cold rescan body for a comb cut. Emitted under the group guard
    * `done_reset && update_registers`, entered only when `_v2_vacc` is set. */
  private def combVerifyLinesAtStr(name: String, k: String, selfIdx: String)
      (implicit rn: Renamer): Seq[String] = {
    def rf(n: String, idx: String): String = rn.emitForLane(n, idx)
    Seq(
      s"if (($selfIdx) >= 1 && ($selfIdx) < ORACLE_NUM_CYCLES && ${combVerifyMismatchExpr(name, k)}) {",
      s"  if (oracle_mismatch_should_log()) fprintf(stderr, \"ORACLE MISMATCH comb=$name lane=%d cyc=%d rtl=0x%\" PRIx64 \" oracle=0x%\" PRIx64 \"\\n\", (int)($k), (int)($selfIdx), essent_to_u64(${rf(name + "$rtl", k)}), essent_to_u64(${rf(name, k)}));",
      s"  record_oracle_mismatch();",
      s"}"
    )
  }

  private def combVerifyLinesStr(name: String, k: String, dir: Int, W: Int)
      (implicit rn: Renamer): Seq[String] = {
    val selfIdx = if (dir > 0) s"oracle_cycle + ($k)" else s"oracle_cycle + ${2 * W - 1} - ($k)"
    combVerifyLinesAtStr(name, k, selfIdx)
  }

  /** Cold rescan body for an oracled register. Same guard convention as
    * [[combVerifyLinesStr]]. */
  private def verifyLinesAtStr(r: RegInfo, k: String, other: String,
      selfIdx: String, cycleIdx: String)(implicit rn: Renamer): Seq[String] = {
    def rf(name: String, idx: String): String = rn.emitForLane(name, idx)
    Seq(
      s"if (($selfIdx) >= 1 && ($cycleIdx) < ORACLE_NUM_CYCLES && ${verifyMismatchAtExpr(r, k, other)}) {",
      s"  if (oracle_mismatch_should_log()) fprintf(stderr, \"ORACLE MISMATCH reg=${r.name} lane=%d cyc=%d rtl=0x%\" PRIx64 \" oracle=0x%\" PRIx64 \"\\n\", (int)($k), (int)($cycleIdx), essent_to_u64(${rf(r.nextName, k)}), essent_to_u64(${rf(r.name, other)}));",
      s"  record_oracle_mismatch();",
      s"}"
    )
  }

  private def verifyLinesStr(r: RegInfo, k: String, dir: Int, W: Int)
      (implicit rn: Renamer): Seq[String] = {
    // Trace record 0 is the pre-loop phantom (reset state) and records past
    // ORACLE_NUM_CYCLES are zero padding: check only real cycles, same
    // convention as the harness output cross-check.
    val other    = if (dir > 0) s"($k) + 1" else s"($k) - 1"
    val selfIdx  = if (dir > 0) s"oracle_cycle + ($k)" else s"oracle_cycle + ${2 * W - 1} - ($k)"
    val cycleIdx = if (dir > 0) s"oracle_cycle + ($k) + 1" else s"oracle_cycle + ${2 * W} - ($k)"
    verifyLinesAtStr(r, k, other, selfIdx, cycleIdx)
  }

  /** Exact diagnostic rescan for the quiet identity image.  The first value
    * is the RTL next-state after substituting the proven next := current;
    * retaining the ordinary `rtl=`/`oracle=` labels keeps log parsers and
    * mismatch accounting identical to the full verifier. */
  private def quietHoldVerifyLinesAtStr(r: RegInfo, k: String, other: String,
      selfIdx: String, cycleIdx: String)(implicit rn: Renamer): Seq[String] = {
    def rf(name: String, idx: String): String = rn.emitForLane(name, idx)
    val mismatch = s"(!(${rf(r.name, k)} == ${rf(r.name, other)}))"
    Seq(
      s"if (($selfIdx) >= 1 && ($cycleIdx) < ORACLE_NUM_CYCLES && $mismatch) {",
      s"  if (oracle_mismatch_should_log()) fprintf(stderr, \"ORACLE MISMATCH reg=${r.name} lane=%d cyc=%d rtl=0x%\" PRIx64 \" oracle=0x%\" PRIx64 \" [quiet-hold]\\n\", (int)($k), (int)($cycleIdx), essent_to_u64(${rf(r.name, k)}), essent_to_u64(${rf(r.name, other)}));",
      s"  record_oracle_mismatch();",
      s"}"
    )
  }

  private def quietHoldVerifyLinesStr(r: RegInfo, k: String, dir: Int, W: Int)
      (implicit rn: Renamer): Seq[String] = {
    val other = if (dir > 0) s"($k) + 1" else s"($k) - 1"
    val selfIdx = if (dir > 0) s"oracle_cycle + ($k)" else
      s"oracle_cycle + ${2 * W - 1} - ($k)"
    val cycleIdx = if (dir > 0) s"oracle_cycle + ($k) + 1" else
      s"oracle_cycle + ${2 * W} - ($k)"
    quietHoldVerifyLinesAtStr(r, k, other, selfIdx, cycleIdx)
  }

  /** Emit one shared cold dispatcher after the eval bodies. Class-scope name
    * lookup lets earlier inline member definitions call this later member.
    * Runtime direction arithmetic keeps each diagnostic group to one body. */
  private def emitVerifyOutlineHelper(res: Result, W: Int,
      outline: VerifyOutlineRegistry, w: Writer)(implicit rn: Renamer): Unit = {
    if (!outline.enabled || outline.groups.isEmpty) return

    // Zero-copied registers have no lane arrays; the rescan reads the same
    // block slot through a runtime-direction alias (`_forward` is a param).
    rn.setSimdBaseOverrides(zcScratchOverrides ++ zcRescanOverrides(W))
    try emitVerifyOutlineHelperBody(res, W, outline, w)
    finally rn.setSimdBaseOverrides(zcScratchOverrides)
  }

  private def emitVerifyOutlineHelperBody(res: Result, W: Int,
      outline: VerifyOutlineRegistry, w: Writer)(implicit rn: Renamer): Unit = {
    w.writeLines(1, "#if ESSENT_ORACLE_VERIFY")
    // Keep the exact diagnostic path cold. A report-only runner with its
    // log quota exhausted still checks every value, but does not need the
    // per-mismatch branch/store/reporting machinery. The separate read-only
    // reduction can vectorize even when mismatches occur in every window.
    // The opt-out supports identical-header A/B tests of the counting path.
    w.writeLines(1, "#ifndef ESSENT_VERIFY_COUNT_ONLY")
    w.writeLines(1, "#define ESSENT_VERIFY_COUNT_ONLY 1")
    w.writeLines(1, "#endif")
    w.writeLines(1, "#if ESSENT_VERIFY_COUNT_ONLY")
    w.writeLines(1, "ESSENT_NOINLINE uint64_t _v2_verify_count(" +
      "int _v2_group, bool _forward, int _lo, int _hi) const {")
    zcRescanDecls(W).foreach(w.writeLines(2, _))
    w.writeLines(2, "switch (_v2_group) {")
    for ((group, id) <- outline.groups) {
      val nextCycle = if (group.kind == VCombVerify) 0 else 1
      w.writeLines(3, s"case $id: {")
      // The scalar diagnostic checks self >= 1 and self + nextCycle < N.
      // Intersect those chronological bounds with this call's lane slice
      // once, so no phantom/padding lane contributes and the loop is pure.
      // int64_t keeps the bound calculation defined near int cursor limits.
      w.writeLines(4, "const int64_t _cycle = oracle_cycle;")
      w.writeLines(4, s"const int64_t _min = _forward ? 1 - _cycle : " +
        s"_cycle + ${2 * W + nextCycle} - (int64_t)ORACLE_NUM_CYCLES;")
      w.writeLines(4, s"const int64_t _max = _forward ? (int64_t)ORACLE_NUM_CYCLES - _cycle - $nextCycle : " +
        s"_cycle + ${2 * W - 1};")
      w.writeLines(4, "const int64_t _begin = _min > _lo ? _min : _lo;")
      w.writeLines(4, "const int64_t _end = _max < _hi ? _max : _hi;")
      w.writeLines(4, "uint64_t _count = 0;")
      w.writeLines(4, "ESSENT_LANE_LOOP")
      w.writeLines(4, "for (int64_t L = _begin; L < _end; ++L) {")
      if (group.kind != VCombVerify)
        w.writeLines(5, "const int64_t _other = L + (_forward ? 1 : -1);")
      for (name <- group.fields) {
        val mismatch = group.kind match {
          case VRegVerify => verifyMismatchAtExpr(res.regs(name), "L", "_other")
          case VRegQuietHoldVerify =>
            s"(!(${rn.emitForLane(name, "L")} == ${rn.emitForLane(name, "_other")}))"
          case VCombVerify => combVerifyMismatchExpr(name, "L")
        }
        w.writeLines(5, s"_count += (uint64_t)$mismatch;")
      }
      w.writeLines(4, "}")
      w.writeLines(4, "return _count;")
      w.writeLines(3, "}")
    }
    w.writeLines(3, "default: return 0;")
    w.writeLines(2, "}")
    w.writeLines(1, "}")
    w.writeLines(1, "#endif")
    w.writeLines(1, "ESSENT_COLD_NOINLINE void _v2_verify_rescan(" +
      "int _v2_group, bool _forward, int _lo, int _hi) {")
    w.writeLines(2, "#if ESSENT_VERIFY_COUNT_ONLY")
    w.writeLines(2, "if (!oracle_mismatches_fatal && verify_mismatches >= oracle_mismatch_log_limit) {")
    w.writeLines(3, "const uint64_t _count = _v2_verify_count(_v2_group, _forward, _lo, _hi);")
    // On wraparound the original scalar policy could start logging again;
    // preserve that behavior, as well as unrelated RTL assertion state.
    w.writeLines(3, "if (_count <= UINT64_MAX - verify_mismatches) { verify_mismatches += _count; return; }")
    w.writeLines(2, "}")
    w.writeLines(2, "#endif")
    zcRescanDecls(W).foreach(w.writeLines(2, _))
    w.writeLines(2, "switch (_v2_group) {")
    for ((group, id) <- outline.groups) {
      w.writeLines(3, s"case $id: {")
      w.writeLines(4, "for (int L = _lo; L < _hi; L++) {")
      group.kind match {
        case VRegVerify =>
          w.writeLines(5, "const int _v2_other = _forward ? L + 1 : L - 1;")
          w.writeLines(5, s"const int _v2_self_idx = oracle_cycle + " +
            s"(_forward ? L : ${2 * W - 1} - L);")
          w.writeLines(5, s"const int _v2_cycle_idx = oracle_cycle + " +
            s"(_forward ? L + 1 : ${2 * W} - L);")
          for (name <- group.fields)
            verifyLinesAtStr(res.regs(name), "L", "_v2_other",
              "_v2_self_idx", "_v2_cycle_idx").foreach(l => w.writeLines(5, l))
        case VRegQuietHoldVerify =>
          w.writeLines(5, "const int _v2_other = _forward ? L + 1 : L - 1;")
          w.writeLines(5, s"const int _v2_self_idx = oracle_cycle + " +
            s"(_forward ? L : ${2 * W - 1} - L);")
          w.writeLines(5, s"const int _v2_cycle_idx = oracle_cycle + " +
            s"(_forward ? L + 1 : ${2 * W} - L);")
          for (name <- group.fields)
            quietHoldVerifyLinesAtStr(res.regs(name), "L", "_v2_other",
              "_v2_self_idx", "_v2_cycle_idx").foreach(l => w.writeLines(5, l))
        case VCombVerify =>
          w.writeLines(5, s"const int _v2_self_idx = oracle_cycle + " +
            s"(_forward ? L : ${2 * W - 1} - L);")
          for (name <- group.fields)
            combVerifyLinesAtStr(name, "L", "_v2_self_idx").foreach(l => w.writeLines(5, l))
      }
      w.writeLines(4, "}")
      w.writeLines(4, "break;")
      w.writeLines(3, "}")
    }
    w.writeLines(3, "default: break;")
    w.writeLines(2, "}")
    w.writeLines(1, "}")
    w.writeLines(1, "#endif")
    w.writeLines(0, "")
  }

  private def emitUnit(res: Result, W: Int, u: SchedUnit, dir: Int,
      verifyOutline: VerifyOutlineRegistry, w: Writer)
      (implicit rn: Renamer, ctx: essent.EmitContext): Unit = {
    def rf(name: String, idx: String): String = rn.emitForLane(name, idx)
    def sourceLine(r: RegInfo, k: String): String = sourceLineStr(r, k, dir)
    def oracleLine(r: RegInfo, spec: OracleSpec, k: String): String = oracleLineStr(r, spec, k, dir, W)
    def verifyLines(r: RegInfo, k: String, indent: Int): Seq[String] = verifyLinesStr(r, k, dir, W)

    u match {
      case UVec(t) => res.nodes(t).role match {
        case RRegSource(r) =>
          val ri = res.regs(r)
          val plainShift = ri.plan match {
            case RPCondHold | RPAffineScan | RPSerialNext(_, _) => false
            case _ => true
          }
          if (plainShift && !sourceLoop) {
            // Same staged-snapshot + shifted-memcpy lowering as the fused
            // CSource case (see there for the store-to-load-forwarding
            // rationale); boundary lane written by the window-boundary code.
            val t = genCppType(ri.tpe)
            val (dst, srcOff) = if (dir > 0) ("1", "0") else ("0", "1")
            w.writeLines(2, "{")
            w.writeLines(3, s"alignas(64) $t _v2s_u[$W];")
            w.writeLines(3, s"memcpy(_v2s_u, &${rn.emitForLane(ri.nextName, "0")}, sizeof(_v2s_u));")
            w.writeLines(3, s"memcpy(&${rn.emitForLane(ri.name, dst)}, &_v2s_u[$srcOff], " +
              "sizeof(_v2s_u) - sizeof(_v2s_u[0]));")
            w.writeLines(2, "}")
          } else if (dir > 0) {
            w.writeLines(2, s"for (int L = ${W - 1}; L >= 1; L--) ${sourceLine(ri, "L")}")
          } else {
            w.writeLines(2, s"for (int L = 0; L < ${W - 1}; L++) ${sourceLine(ri, "L")}")
          }
        case RRegCommit(r) =>
          // Perf: memcpy helper instead of a lane loop; see commitCallStr.
          // Oracle registers skip commit unless still consumed (commitWanted).
          if (commitWanted(r, res.regs(r)))
            w.writeLines(2, s"if (update_registers) ${commitCallStr(r, res.regs(r), W, boundaryLaneStr(W, dir))}")
        case RStateRead(_) =>
          res.nodes(t).produces.foreach { name =>
            rn.simdArrayDecl(name, genCppType(rn.nameToMeta(name).sigType))
              .foreach(d => w.writeLines(2, d))
          }
          stateReadLoopStr(res, t, W, dir).foreach(line => w.writeLines(2, line))
        case RStateCommit(array) =>
          val commitLines = if (res.stateArrays(array).fullyExternal) Seq.empty
            else if (externAllReads(res, array))
              ("#if ESSENT_ORACLE_VERIFY // [extern-read] commit of fully-externalized array" +:
                stateCommitLoopStr(res, array, W, dir)) :+ "#endif"
            else stateCommitLoopStr(res, array, W, dir)
          commitLines.foreach(line => w.writeLines(2, line))
        case ROracleInject(r) =>
          // Perf: __restrict-parameter inject helper; see injectCallStr.
          // Zero-copied registers: reads alias the block, nothing to inject.
          val specs = res.oracles.filter(_.flatName == r)
          if (res.regs.contains(r)) {
            if (!zcInfo.contains(r))
              for (spec <- specs)
                w.writeLines(2, s"if (done_reset) ${injectCallStr(res.regs(r).name, spec, dir, W)}")
          } else if (!zcInfo.contains(r)) {
            val spec = specs.head
            w.writeLines(2, s"if (done_reset) ${injectCallStr(r, spec, dir, W)}")
            w.writeLines(2, s"else for (int L = 0; L < $W; L++) ${rn.emitForLane(r, "L")} = ${genCppType(res.combCuts(r))}(0);")
          }
        case RVerify(r) =>
          w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
          val uvWidth = Seq(
            if (res.regs.contains(r)) firrtl.bitWidth(res.regs(r).tpe).toInt
            else firrtl.bitWidth(res.combCuts(r)).toInt)
          w.writeLines(2, "if (done_reset && checks_enabled && update_registers) {")
          vaccDecls(uvWidth).foreach(w.writeLines(3, _))
          if (res.regs.contains(r)) {
            val (lo, hi) = if (dir > 0) (0, W - 1) else (1, W)
            withLaneVar("L") {
              emitVerifyReduction(Seq(verifyReductionTerm(uvWidth.head,
                res.regs(r).nextName, res.regs(r).name, lo, dir, W)),
                W, lo, hi, tail = true, w = w)
            }
            if (verifyOutline.enabled) {
              val groupId = verifyOutline.register(VRegVerify, Seq(r))
              w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(uvWidth)})) " +
                s"_v2_verify_rescan($groupId, ${dir > 0}, $lo, $hi);")
            } else {
              w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(uvWidth)})) for (int L = $lo; L < $hi; L++) {")
              verifyLines(res.regs(r), "L", 3).foreach(l => w.writeLines(4, l))
              w.writeLines(3, "}")
            }
          } else {
            withLaneVar("L") {
              emitVerifyReduction(Seq(verifyReductionTerm(uvWidth.head,
                r + "$rtl", r, 0, 0, W)),
                W, 0, W, tail = false, w = w)
            }
            if (verifyOutline.enabled) {
              val groupId = verifyOutline.register(VCombVerify, Seq(r))
              w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(uvWidth)})) " +
                s"_v2_verify_rescan($groupId, ${dir > 0}, 0, $W);")
            } else {
              w.writeLines(3, s"if (UNLIKELY(${vaccTestExpr(uvWidth)})) for (int L = 0; L < $W; L++) {")
              combVerifyLinesStr(r, "L", dir, W).foreach(l => w.writeLines(4, l))
              w.writeLines(3, "}")
            }
          }
          w.writeLines(2, "}")
          w.writeLines(2, "#endif")
        case RComb | REffect =>
          // non-fusable path not expected, but handle uniformly
          res.nodes(t).produces.foreach { name =>
            rn.simdArrayDecl(name, genCppType(rn.nameToMeta(name).sigType))
              .foreach(d => w.writeLines(2, d))
          }
          w.writeLines(2, s"for (int L = 0; L < $W; L++) {")
          withLaneVar("L") { w.writeLines(3, emitCombStmt(res.nodes(t).stmt)) }
          w.writeLines(2, "}")
      }

      case ULane(t, k) =>
        val node = res.nodes(t)
        node.produces.foreach { name =>
          rn.simdArrayDecl(name, genCppType(rn.nameToMeta(name).sigType))
            .foreach(d => w.writeLines(2, d))
        }
        node.role match {
          case RComb | REffect =>
            withLaneVar(k.toString) { w.writeLines(2, emitCombStmt(node.stmt)) }
          case RRegSource(r) =>
            val boundary = if (dir > 0) k == 0 else k == W - 1
            if (!boundary) w.writeLines(2, sourceLine(res.regs(r), k.toString))
          case RRegCommit(r) =>
            val ri = res.regs(r)
            if (commitWanted(r, ri))
              w.writeLines(2, s"if (update_registers) ${rf(r, k.toString)} = ${rf(ri.nextName, k.toString)};")
          case RStateRead(_) =>
            stateReadLaneStr(res, t, k, W, dir).foreach(line => w.writeLines(2, line))
          case RStateCommit(array) =>
            // RStateCommit is deliberately kept full-width by scheduling;
            // retain a fail-fast guard if an experimental serializer violates
            // that invariant.
            throw new IllegalStateException(
              s"[v2-state-array] commit '$array' was scheduled as ULane($k)")
          case ROracleInject(r) =>
            val specs = res.oracles.filter(_.flatName == r)
            if (res.regs.contains(r)) {
              if (!zcInfo.contains(r))
                for (spec <- specs)
                  w.writeLines(2, s"if (done_reset) ${oracleLine(res.regs(r), spec, k.toString)}")
            } else if (!zcInfo.contains(r)) {
              val spec = specs.head
              val idx = if (dir > 0) s"$k" else s"${2 * W - 1} - $k"
              val target = rn.emitForLane(r, k.toString)
              val tpe = genCppType(res.combCuts(r))
              w.writeLines(2, s"if (done_reset) $target = $tpe(ESSENT_ORACLE_LOAD(${v4StreamExpr(spec.arraySymbol)}, $idx));")
              w.writeLines(2, s"else $target = $tpe(0);")
            }
          case RVerify(r) =>
            val isReg = res.regs.contains(r)
            val inRange = !isReg || (if (dir > 0) k < W - 1 else k > 0)
            if (inRange) {
              // Single-lane form of the accumulate-then-rescan pattern: one
              // predicted-never mismatch test, range checks in the cold body.
              w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
              val mismatch = if (isReg)
                verifyMismatchExpr(res.regs(r), k.toString, dir)
              else combVerifyMismatchExpr(r, k.toString)
              w.writeLines(2, "if (done_reset && checks_enabled && update_registers && " +
                s"UNLIKELY((uint64_t)$mismatch)) {")
              if (verifyOutline.enabled) {
                val kind = if (isReg) VRegVerify else VCombVerify
                val groupId = verifyOutline.register(kind, Seq(r))
                w.writeLines(3, s"_v2_verify_rescan($groupId, ${dir > 0}, $k, ${k + 1});")
              } else if (isReg) {
                verifyLines(res.regs(r), k.toString, 2).foreach(l => w.writeLines(3, l))
              } else {
                combVerifyLinesStr(r, k.toString, dir, W).foreach(l => w.writeLines(3, l))
              }
              w.writeLines(2, "}")
              w.writeLines(2, "#endif")
            } else if (isReg) {
              // Boundary lane: no in-window partner; carry the RTL next-state
              // to the following sweep's boundary check.
              w.writeLines(2, "#if ESSENT_ORACLE_VERIFY")
              w.writeLines(2, "if (done_reset && checks_enabled && update_registers) " +
                boundaryCarryStoreStr(res.regs(r), res.regs(r).nextName, W, dir))
              w.writeLines(2, "#endif")
            }
        }
    }
  }

  // ------------------------------------------------------------------
  // Data-plane artifacts
  // ------------------------------------------------------------------
  /** Host-boundary ABI for every reachable ExtModule.  The source artifact
    * contains many parameter-specialized declarations that FIRRTL may dedup;
    * this manifest intentionally describes the post-transform definitions and
    * every concrete hierarchical instance consumed by the emitted kernel.
    * Clock ports remain in the manifest even though they are not represented
    * as lane arrays in the generated C++ struct.
    */
  private def writeExtModuleManifest(circuit: Circuit, W: Int, f: File): Unit = {
    def json(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\u${c.toInt}%04x"
      case c => c.toString
    } + "\""
    def direction(p: Port): String = p.direction match {
      case Input => "input"
      case Output => "output"
    }
    def adapter(m: ExtModule): String = m.defname match {
      case "plusarg_reader" => "plusarg-constant"
      case "SimDTM" => "fesvr-dtm"
      case "EICG_wrapper" => "compiler-lowered-clock-gate"
      case "CHISARocketModel" => "rocket-guider-core"
      case "CHISARocketFPUCoreModel" => "rocket-guider-fpu-core"
      case "CHISARocketFrontendModel" => "rocket-guider-frontend"
      case "CHISARocketDCacheModel" => "rocket-guider-dcache"
      case _ => "unimplemented"
    }
    def width(tpe: Type): Int = tpe match {
      case ClockType | ResetType | AsyncResetType => 1
      case _ => firrtl.bitWidth(tpe).toInt
    }
    def parameter(p: Param): String = p match {
      case IntParam(name, value) =>
        s"{\"name\":${json(name)},\"kind\":\"integer\",\"value\":$value}"
      case DoubleParam(name, value) if java.lang.Double.isFinite(value) =>
        s"{\"name\":${json(name)},\"kind\":\"double\",\"value\":$value}"
      case DoubleParam(name, value) =>
        s"{\"name\":${json(name)},\"kind\":\"double\",\"value\":${json(value.toString)}}"
      case StringParam(name, value) =>
        s"{\"name\":${json(name)},\"kind\":\"string\",\"value\":${json(value.string)}}"
      case RawStringParam(name, value) =>
        s"{\"name\":${json(name)},\"kind\":\"raw-string\",\"value\":${json(value)}}"
    }

    val definitions = circuit.modules.collect { case m: ExtModule => m }.sortBy(_.name)
    val extByName = definitions.map(m => m.name -> m).toMap
    val instances = findAllModuleInstances(circuit).flatMap { case (module, rawPath) =>
      extByName.get(module).map(m => (rawPath.stripSuffix("."), m))
    }.sortBy(_._1)
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println("  \"version\": 1,")
    pw.println(s"  \"width\": $W,")
    pw.println(s"  \"windowCycles\": ${2 * W},")
    pw.println(s"  \"definitionCount\": ${definitions.size},")
    pw.println(s"  \"instanceCount\": ${instances.size},")
    pw.println("  \"definitions\": [")
    definitions.zipWithIndex.foreach { case (m, mi) =>
      val comma = if (mi < definitions.size - 1) "," else ""
      pw.println("    {")
      pw.println(s"      \"module\": ${json(m.name)},")
      pw.println(s"      \"defname\": ${json(m.defname)},")
      pw.println(s"      \"adapter\": ${json(adapter(m))},")
      pw.println("      \"parameters\": [")
      m.params.zipWithIndex.foreach { case (p, pi) =>
        val pcomma = if (pi < m.params.size - 1) "," else ""
        pw.println(s"        ${parameter(p)}$pcomma")
      }
      pw.println("      ],")
      pw.println("      \"ports\": [")
      m.ports.zipWithIndex.foreach { case (p, pi) =>
        val isClock = p.tpe == ClockType
        val pcomma = if (pi < m.ports.size - 1) "," else ""
        val rtlFlow = if (p.direction == Input) "to-host" else "from-host"
        val transport = if (isClock) "clock-contract" else "per-cycle-lanes"
        pw.println("        {" +
          s"\"name\":${json(p.name)}," +
          s"\"direction\":${json(direction(p))}," +
          s"\"rtlFlow\":${json(rtlFlow)}," +
          s"\"type\":${json(p.tpe.serialize)}," +
          s"\"width\":${width(p.tpe)}," +
          s"\"clock\":$isClock," +
          s"\"transport\":${json(transport)}" +
          s"}$pcomma")
      }
      pw.println("      ]")
      pw.println(s"    }$comma")
    }
    pw.println("  ],")
    pw.println("  \"instances\": [")
    instances.zipWithIndex.foreach { case ((path, m), i) =>
      val comma = if (i < instances.size - 1) "," else ""
      pw.println("    {" +
        s"\"path\":${json(path)}," +
        s"\"module\":${json(m.name)}," +
        s"\"defname\":${json(m.defname)}," +
        s"\"adapter\":${json(adapter(m))}" +
        s"}$comma")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    val byAdapter = instances.groupBy { case (_, m) => adapter(m) }
      .toSeq.sortBy(_._1).map { case (a, xs) => s"$a=${xs.size}" }.mkString(", ")
    println(s"[v2-extmodule] wrote ${f.getPath} (${definitions.size} definition(s), " +
      s"${instances.size} instance(s): $byAdapter)")
  }

  /** X-macro inventory for host adapters.  It deliberately contains concrete
    * C++ member paths, so the adapter build fails at compile time if FIRRTL
    * hierarchy or emitted struct naming drifts.  The file has no include
    * guard because consumers include it repeatedly with different macros. */
  private def writeExtModuleFields(circuit: Circuit, f: File): Unit = {
    def cppString(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\x${c.toInt}%02x"
      case c => c.toString
    } + "\""
    val extByName = circuit.modules.collect { case m: ExtModule => m.name -> m }.toMap
    val instances = findAllModuleInstances(circuit).flatMap { case (module, rawPath) =>
      extByName.get(module).map(m => rawPath.stripSuffix(".") -> m)
    }.sortBy(_._1)
    val pw = new java.io.PrintWriter(f)
    pw.println("// Generated by CHISA. Define every CHISA_EXT_* macro before inclusion.")
    instances.foreach { case (path, m) => m.defname match {
      case "plusarg_reader" =>
        val format = m.params.collectFirst {
          case StringParam("FORMAT", value) => value.string
          case RawStringParam("FORMAT", value) => value
        }.getOrElse(throw new IllegalStateException(
          s"[v2-extmodule] plusarg_reader '$path' has no FORMAT parameter"))
        val default = m.params.collectFirst { case IntParam("DEFAULT", value) => value }
          .getOrElse(throw new IllegalStateException(
            s"[v2-extmodule] plusarg_reader '$path' has no DEFAULT parameter"))
        val width = m.params.collectFirst { case IntParam("WIDTH", value) => value }
          .getOrElse(throw new IllegalStateException(
            s"[v2-extmodule] plusarg_reader '$path' has no WIDTH parameter"))
        val outputs = m.ports.collect { case Port(_, name, Output, tpe) if tpe != ClockType => name }
        require(outputs.size == 1,
          s"[v2-extmodule] plusarg_reader '$path' must have exactly one data output")
        pw.println(s"CHISA_EXT_PLUSARG_READER($path, ${outputs.head}, " +
          s"${cppString(format)}, $default, $width)")
      case "SimDTM" => pw.println(s"CHISA_EXT_SIMDTM($path)")
      case "EICG_wrapper" => pw.println(s"CHISA_EXT_EICG_LOWERED($path)")
      case "CHISARocketModel" => pw.println(s"CHISA_EXT_ROCKET_MODEL($path)")
      case "CHISARocketFPUCoreModel" => pw.println(s"CHISA_EXT_ROCKET_FPU_MODEL($path)")
      case "CHISARocketFrontendModel" => pw.println(s"CHISA_EXT_ROCKET_FRONTEND_MODEL($path)")
      case "CHISARocketDCacheModel" => pw.println(s"CHISA_EXT_ROCKET_DCACHE_MODEL($path)")
      case other => pw.println(s"CHISA_EXT_UNIMPLEMENTED($path, ${cppString(other)})")
    }}
    pw.close()
    println(s"[v2-extmodule] wrote ${f.getPath} (${instances.size} concrete field path(s))")
  }

  private def writeClockDomainManifest(report: ClockDomainLowering.Report, f: File): Unit = {
    def json(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\u${c.toInt}%04x"
      case c => c.toString
    } + "\""
    def strings(xs: Seq[String]): String = xs.map(json).mkString("[", ",", "]")
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println("  \"version\": 1,")
    pw.println(s"  \"sourceClocks\": ${strings(report.sourceClocks)},")
    pw.println(s"  \"clockGates\": ${strings(report.clockGates)},")
    pw.println(s"  \"gatedRegisterCount\": ${report.gatedRegisters},")
    pw.println(s"  \"gatedMemoryWriteCount\": ${report.gatedMemoryWrites},")
    pw.println(s"  \"gatedEffectCount\": ${report.gatedEffects},")
    pw.println(s"  \"gatedRegisters\": ${strings(report.gatedRegisterNames)},")
    pw.println(s"  \"gatedMemoryWrites\": ${strings(report.gatedMemoryWriteNames)},")
    pw.println("  \"enableNodes\": [")
    report.enableExpressions.zipWithIndex.foreach { case ((name, expression), i) =>
      val comma = if (i + 1 < report.enableExpressions.size) "," else ""
      pw.println(s"    {\"name\":${json(name)},\"expression\":${json(expression)}}$comma")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    println(s"[v2-clock] wrote ${f.getPath} (${report.gatedRegisters} gated register(s), " +
      s"${report.gatedMemoryWrites} gated memory write(s))")
  }

  /** Exact provenance for performance-only dead-register deletion.  This is
    * deliberately separate from state_array_manifest.json: the latter is a
    * runtime storage ABI, while this file is a compiler-proof/audit input and
    * must never be consumed as oracle data by a sidecar. */
  private def writeDeadStateManifest(res: Result, f: File): Unit = {
    def json(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\u${c.toInt}%04x"
      case c => c.toString
    } + "\""
    val report = res.deadStatePrune
    val removed = report.removedRegisters.sorted
    require(removed.distinct.size == removed.size,
      "[v2-dead-state] removed-register inventory contains duplicates")
    val monitor = removed.filter(_.contains(".monitor."))
    val retained = report.sourceRegisterCount - removed.size
    require(retained >= 0,
      s"[v2-dead-state] removed ${removed.size} of ${report.sourceRegisterCount} registers")
    require(report.enabled || removed.isEmpty,
      "[v2-dead-state] disabled prune unexpectedly removed registers")
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println("  \"version\": 1,")
    pw.println(s"  \"sourceEffectsKept\": ${report.sourceEffectsKept},")
    pw.println(s"  \"enabled\": ${report.enabled},")
    pw.println(s"  \"sourceRegisterCount\": ${report.sourceRegisterCount},")
    pw.println(s"  \"removedCount\": ${removed.size},")
    pw.println(s"  \"retainedCount\": $retained,")
    pw.println(s"  \"monitorRemovedCount\": ${monitor.size},")
    pw.println("  \"removedRegisters\": [")
    removed.zipWithIndex.foreach { case (name, i) =>
      val comma = if (i + 1 < removed.size) "," else ""
      pw.println(s"    ${json(name)}$comma")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    println(s"[v2-dead-state] wrote ${f.getPath} " +
      s"(enabled=${report.enabled} removed=${removed.size} monitor=${monitor.size})")
  }

  private def writeManifest(res: Result, f: File): Unit = {
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    // Keep the v2 window-major file ABI.  Access-proof streams only extend
    // each entry's provenance; they do not change offsets or serialization.
    pw.println("""  "version": 2,""")
    pw.println(s"""  "layout": "${if (premirror) "window-major-v4m" else "window-major-v4"}",""")
    pw.println(s"""  "blockBytes": $v4BlockBytes,""")
    pw.println("""  "oracles": [""")
    res.oracles.zipWithIndex.foreach { case (o, i) =>
      val comma = if (i < res.oracles.size - 1) "," else ""
      // elemBytes: storage tier of the packed stream (u8/u16/u32/u64 from the
      // signal width, SInt forced to u64 — see specElemBytes). blockOffset:
      // this stream's slot inside every window-major block; the emitted call
      // sites bake the same constants, the packer follows this manifest.
      val elemBytes = specElemBytes(res, o)
      val verification = if (!o.verified) "none"
        else if (res.accessProofDataOracles(o.flatName)) "access-trace-induction"
        else "direct-micro-lockstep"
      pw.println(s"""    {"flat": "${o.flatName}", "traceKey": "${o.traceKey}", "array": "${o.arraySymbol}", "width": ${o.widthBits}, "word": ${o.word}, "words": ${o.words}, "elemBytes": $elemBytes, "blockOffset": ${v4Off(o.arraySymbol)}, "kind": "${if (o.isRegister) "reg" else "comb"}", "verified": ${o.verified}, "verification": "$verification"}$comma""")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    println(s"[v2] wrote ${f.getPath} (${res.oracles.size} oracles, v4 blockBytes=$v4BlockBytes)")
  }

  /** Machine-readable ownership of every residual serial SCC.  Oracle
    * selection reports what was cut, but full-system performance work also
    * needs to know what remains per-lane.  Keep template ids and exact flat
    * names here instead of guessing ownership from generated C++ chunks.
    */
  private def writeSerialRegionAudit(res: Result, W: Int, f: File): Unit = {
    def json(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\u${c.toInt}%04x"
      case c => c.toString
    } + "\""
    def roleName(role: Role): String = role match {
      case RComb => "comb"
      case _: RRegSource => "register-source"
      case _: RRegCommit => "register-commit"
      case _: ROracleInject => "oracle-inject"
      case _: RVerify => "oracle-verify"
      case _: RStateRead => "state-read"
      case _: RStateCommit => "state-commit"
      case REffect => "effect"
    }
    def flatName(node: TemplateNode): String = node.produces.getOrElse(node.role match {
      case RRegSource(reg) => reg
      case RRegCommit(reg) => reg
      case ROracleInject(reg) => reg
      case RVerify(reg) => reg
      case RStateRead(array) => array
      case RStateCommit(array) => array
      case _ => V2Pipeline.stmtReads(node.stmt).headOption.getOrElse("")
    })
    def planName(node: TemplateNode): String = node.role match {
      case RRegSource(reg) => res.regs.get(reg).map(_.plan).map {
        case RPShift => "shift"
        case RPCondHold => "cond-hold-prefix-scan"
        case RPAffineScan => "affine-prefix-scan"
        case RPSerialNext(_, true) => "serial-next-guarded"
        case RPSerialNext(_, false) => "serial-next"
        case RPOracle => "oracle"
      }.getOrElse("missing-register")
      case _ => "not-register-source"
    }

    val regions = res.sccOf.toSeq.groupBy(_._2).toSeq.sortBy(_._1).map {
      case (id, entries) => id -> entries.map(_._1).sorted
    }
    val regionSize = regions.iterator.map { case (id, tids) => id -> tids.size }.toMap
    def serialFamilyReg(reg: String): Boolean = res.regs.get(reg).exists { info =>
      info.plan match {
        case RPCondHold | RPAffineScan | RPSerialNext(_, _) => true
        case _ => res.sccOf.contains(info.sourceId)
      }
    }
    def regReads(expression: Expression): Seq[String] = expression match {
      case ref: WRef if res.regs.contains(ref.name) => Seq(ref.name)
      case other =>
        val reads = Seq.newBuilder[String]
        other.foreachExpr(sub => reads ++= regReads(sub))
        reads.result()
    }
    def hasCrossSerialHazard(reg: String): Boolean = res.regs(reg).plan match {
      case RPSerialNext(folded, _) =>
        regReads(folded).exists(other => other != reg && serialFamilyReg(other))
      case _ => false
    }
    val forcePerLane = envBool("V2_FORCE_PER_LANE_SERIAL", default = false)
    def emissionName(id: Int, node: TemplateNode): String = {
      val multiTemplate = regionSize(res.sccOf(id)) > 1
      node.role match {
        case RRegSource(reg) if forcePerLane => "per-lane-forced"
        case RRegSource(_) if multiTemplate => "per-lane-scc"
        case RRegSource(reg) if hasCrossSerialHazard(reg) => "per-lane-cross-serial-hazard"
        case RRegSource(reg) => res.regs(reg).plan match {
          case RPCondHold => "prefix-scan"
          case RPAffineScan => "affine-prefix-scan"
          case RPSerialNext(_, true) => "guarded-broadcast-or-serial-loop"
          case _ => "serial-loop"
        }
        case _ => "per-lane-scc"
      }
    }
    require(regions.map(_._2.size).sum == res.sccOf.size,
      "[v2-serial] region membership does not cover the serial SCC map")
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println("  \"version\": 2,")
    pw.println(s"  \"width\": $W,")
    pw.println(s"  \"windowCycles\": ${2 * W},")
    pw.println(s"  \"regionCount\": ${regions.size},")
    pw.println(s"  \"templateCount\": ${res.sccOf.size},")
    pw.println("  \"regions\": [")
    regions.zipWithIndex.foreach { case ((id, tids), ri) =>
      val comma = if (ri + 1 < regions.size) "," else ""
      pw.println(s"    {\"id\":$id,\"templateCount\":${tids.size},\"members\":[")
      tids.zipWithIndex.foreach { case (tid, mi) =>
        val node = res.nodes(tid)
        val memberComma = if (mi + 1 < tids.size) "," else ""
        pw.println(s"      {\"templateId\":$tid,\"role\":${json(roleName(node.role))}," +
          s"\"plan\":${json(planName(node))},\"emission\":${json(emissionName(tid, node))}," +
          s"\"flat\":${json(flatName(node))}}$memberComma")
      }
      pw.println(s"    ]}$comma")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    val top = regions.sortBy { case (id, tids) => (-tids.size, id) }.take(5).map {
      case (_, tids) =>
        val representative = tids.iterator.map(tid => flatName(res.nodes(tid)))
          .find(_.nonEmpty).getOrElse("?")
        s"${tids.size}:${representative.split('.').last}"
    }
    println(s"[v2-serial] wrote ${f.getPath} (${regions.size} region(s), " +
      s"${res.sccOf.size} template(s), top=${top.mkString(",")})")
  }

  /** Machine-readable ABI for differential checks of persistent state.
    * These values are not oracle streams. Version 1 is retained when every
    * entry is a compiler-lifted aggregate register (legacy consumers); version
    * 2 additionally describes ordinary RTL memories and their port counts.
    * The full-system flow uses this to audit cache/RF/queue/AXI backing rather
    * than silently treating memories as host magic.
    */
  private def writeStateArrayManifest(res: Result, W: Int, f: File): Unit = {
    def json(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\u${c.toInt}%04x"
      case c => c.toString
    } + "\""
    val arrays = res.stateArrays.values.toSeq.sortBy(_.name)
    val version = if (arrays.exists(_.fullyExternal)) 3
      else if (arrays.forall(_.compilerLifted)) 1 else 2
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println(s"  \"version\": $version,")
    pw.println(s"  \"width\": $W,")
    pw.println(s"  \"windowCycles\": ${2 * W},")
    pw.println("  \"arrays\": [")
    arrays.zipWithIndex.foreach { case (array, ai) =>
      val packedWidth = firrtl.bitWidth(array.tpe).toInt
      require(array.fields.map(_._2).sum == packedWidth,
        s"[v2-state-array] '${array.name}' field widths do not sum to $packedWidth")
      val comma = if (ai < arrays.size - 1) "," else ""
      pw.println("    {")
      pw.println(s"      \"kind\": ${json(if (array.compilerLifted) "compiler-lifted" else "rtl-memory")},")
      pw.println(s"      \"source\": ${json(array.sourceRegister)},")
      pw.println(s"      \"storage\": ${json(array.name)},")
      pw.println(s"      \"depth\": ${array.depth},")
      pw.println(s"      \"packedWidth\": $packedWidth,")
      pw.println(s"      \"readPorts\": ${array.readIds.size},")
      pw.println(s"      \"writePorts\": ${array.writePorts},")
      pw.println(s"      \"fullyExternal\": ${array.fullyExternal},")
      pw.println(s"      \"storageMaterialized\": ${!array.fullyExternal},")
      pw.println(s"      \"verification\": ${json(if (array.fullyExternal)
        "read-data-oracle+ordered-access-trace" else "chronological-local-image")},")
      pw.println("      \"readAccess\": [")
      array.readAccess.zipWithIndex.foreach { case (access, ri) =>
        val accessComma = if (ri < array.readAccess.size - 1) "," else ""
        pw.println(s"        {\"dataOracle\": ${json(access.dataOracle)}, " +
          s"\"addressOracle\": ${json(access.addressOracle)}}$accessComma")
      }
      pw.println("      ],")
      pw.println("      \"writeAccess\": [")
      array.writeAccess.zipWithIndex.foreach { case (access, wi) =>
        val accessComma = if (wi < array.writeAccess.size - 1) "," else ""
        pw.println(s"        {\"port\": ${json(access.portName)}, " +
          s"\"enableOracle\": ${json(access.enableOracle)}, " +
          s"\"addressOracle\": ${json(access.addressOracle)}, " +
          s"\"dataOracle\": ${json(access.dataOracle)}}$accessComma")
      }
      pw.println("      ],")
      pw.println("      \"fields\": [")
      var high = packedWidth - 1
      array.fields.zipWithIndex.foreach { case ((name, width), fi) =>
        val low = high - width + 1
        val fieldComma = if (fi < array.fields.size - 1) "," else ""
        pw.println(s"        {\"name\": ${json(name)}, \"width\": $width, " +
          s"\"high\": $high, \"low\": $low}$fieldComma")
        high = low - 1
      }
      require(high == -1, s"[v2-state-array] '${array.name}' slice construction failed")
      pw.println("      ]")
      pw.println(s"    }$comma")
    }
    pw.println("  ],")
    // Shared-wen cond-hold groups are compiler-recognized bundle payloads
    // that remain ordinary RTL registers rather than oracle streams.  Record
    // their flattened names so the BOOM flow can compare the untouched scalar
    // register with the final (lane 0 after the reverse half-window) SIMD
    // state at every complete window boundary.  This is deliberately an
    // out-of-band validation ABI, not part of the hot oracle contract.
    val bankNames = res.registerBanks.iterator.map(_.name).toSet
    val checkedRegisters = res.condHoldGroupOf.toSeq
      .filterNot { case (name, _) => bankNames(name) }
      .sortBy(_._1).map {
      case (name, group) => (name, group, firrtl.bitWidth(res.regs(name).tpe).toInt)
    }
    checkedRegisters.foreach { case (name, _, width) =>
      require(width >= 1 && (version >= 2 || width <= 64),
        s"[v2-state-array] checked register '$name' width $width is unsupported by manifest v$version")
    }
    pw.println("  \"registers\": [")
    checkedRegisters.zipWithIndex.foreach { case ((name, group, width), i) =>
      val comma = if (i < checkedRegisters.size - 1) "," else ""
      pw.println(s"    {\"source\": ${json(name)}, \"storage\": ${json(name)}, " +
        s"\"width\": $width, \"group\": $group}$comma")
    }
    pw.println("  ],")
    // Low-form register banks retain one physical UInt lane-array while their
    // original flattened leaf names become combinational slices.  Record the
    // source-to-slice mapping so the untouched scalar BOOM and the SIMD bank's
    // final boundary lane can still be compared for every logical field.
    val banks = res.registerBanks.sortBy(_.name)
    pw.println("  \"packedRegisters\": [")
    banks.zipWithIndex.foreach { case (bank, bi) =>
      require(bank.width >= 1 && bank.width <= 64,
        s"[v2-reg-bank] '${bank.name}' width ${bank.width} is outside 1..64")
      require(bank.fields.map(_.width).sum == bank.width,
        s"[v2-reg-bank] '${bank.name}' field widths do not sum to ${bank.width}")
      val comma = if (bi < banks.size - 1) "," else ""
      pw.println("    {")
      pw.println(s"      \"storage\": ${json(registerBankStorageName(bank.name))},")
      pw.println(s"      \"packedWidth\": ${bank.width},")
      pw.println("      \"fields\": [")
      bank.fields.zipWithIndex.foreach { case (field, fi) =>
        val fieldComma = if (fi < bank.fields.size - 1) "," else ""
        pw.println(s"        {\"source\": ${json(field.source)}, " +
          s"\"width\": ${field.width}, \"high\": ${field.high}, " +
          s"\"low\": ${field.low}}$fieldComma")
      }
      pw.println("      ]")
      pw.println(s"    }$comma")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    println(s"[v2-state-array] wrote ${f.getPath} v$version (${arrays.size} array(s), " +
      s"${checkedRegisters.size} shared-wen register(s), ${banks.size} register bank(s))")
  }

  /** Selection provenance joined with the final packed-stream layout. This
    * artifact is intentionally separate from oracle_manifest.json: packers
    * consume the manifest as a strict ABI, while this report is for compiler
    * and performance diagnosis only. */
  private def writeOracleAudit(res: Result, W: Int, f: File): Unit = {
    def json(s: String): String = "\"" + s.flatMap {
      case '\\' => "\\\\"
      case '"' => "\\\""
      case '\n' => "\\n"
      case '\r' => "\\r"
      case '\t' => "\\t"
      case c if c < ' ' => f"\\u${c.toInt}%04x"
      case c => c.toString
    } + "\""
    val specs = res.oracles.map(o => o.flatName -> o).toMap
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println("  \"version\": 2,")
    pw.println(s"  \"width\": $W,")
    pw.println(s"  \"windowCycles\": ${2 * W},")
    pw.println(s"  \"oracleCount\": ${res.oracleAudit.size},")
    pw.println(s"  \"registerCount\": ${res.regs.size},")
    pw.println(s"  \"registerOracleCount\": ${res.oracles.count(_.isRegister)},")
    pw.println(s"  \"combOracleCount\": ${res.oracles.count(o => !o.isRegister)},")
    pw.println(s"  \"serialTemplateCount\": ${res.serialTemplateCount},")
    pw.println(s"  \"scheduleUnitsForward\": ${res.scheduleFwd.size},")
    pw.println(s"  \"scheduleUnitsReverse\": ${res.scheduleRev.size},")
    pw.println("  \"settings\": {")
    pw.println(s"    \"V2_ORACLE_CONDHOLD\": ${json(sys.env.getOrElse("V2_ORACLE_CONDHOLD", ""))},")
    pw.println(s"    \"V2_ORACLE_CONDHOLD_EXCEPT\": ${json(sys.env.getOrElse("V2_ORACLE_CONDHOLD_EXCEPT", ""))},")
    pw.println(s"    \"V2_ORACLE_SERIAL\": ${json(sys.env.getOrElse("V2_ORACLE_SERIAL", ""))}")
    pw.println("  },")
    pw.println(s"  \"blockBytes\": $v4BlockBytes,")
    pw.println(f"  \"bytesPerCycle\": ${v4BlockBytes.toDouble / (2 * W)}%.3f,")
    pw.println("  \"oracles\": [")
    res.oracleAudit.zipWithIndex.foreach { case (a, i) =>
      val spec = specs(a.flatName)
      val elemBytes = specElemBytes(res, spec)
      val comma = if (i < res.oracleAudit.size - 1) "," else ""
      pw.println("    {" +
        s"\"flat\":${json(a.flatName)}," +
        s"\"kind\":${json(a.kind)}," +
        s"\"stage\":${json(a.stage)}," +
        s"\"reason\":${json(a.reason)}," +
        s"\"basePlan\":${json(a.basePlan)}," +
        s"\"width\":${a.widthBits}," +
        s"\"elemBytes\":$elemBytes," +
        s"\"bytesPerCycle\":$elemBytes," +
        s"\"blockOffset\":${v4Off(spec.arraySymbol)}," +
        s"\"sccKey\":${a.sccKey}," +
        s"\"sccTemplates\":${a.sccTemplates}," +
        s"\"sccCombTemplates\":${a.sccCombTemplates}," +
        s"\"sccRegSources\":${a.sccRegSources}," +
        s"\"sccSelfSources\":${a.sccSelfSources}," +
        s"\"groupOracleCandidates\":${a.groupOracleCandidates}," +
        s"\"selectedRank\":${a.selectedRank}," +
        s"\"benefitEstimate\":${a.benefitEstimate}," +
        s"\"costEstimate\":${a.costEstimate}," +
        s"\"cyclicRegDrop\":${a.cyclicRegDrop}," +
        s"\"cyclicTemplateDrop\":${a.cyclicTemplateDrop}," +
        s"\"matchedPrefix\":${json(a.matchedPrefix)}," +
        s"\"condHoldCandidate\":${a.condHoldCandidate}," +
        s"\"forcedSerial\":${a.forcedSerial}," +
        s"\"phase3CondTrigger\":${a.phase3CondTrigger}," +
        s"\"phase3ForcedTrigger\":${a.phase3ForcedTrigger}," +
        s"\"phase3HeuristicTrigger\":${a.phase3HeuristicTrigger}," +
        s"\"muxHoldWen\":${json(a.muxHoldWen)}," +
        s"\"muxHoldGroupSize\":${a.muxHoldGroupSize}" +
        s"}$comma")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    println(s"[v2] wrote ${f.getPath} (${res.oracleAudit.size} selection records)")
  }

  private def writeRegOracleInc(res: Result, f: File): Unit = {
    val pw = new java.io.PrintWriter(f)
    pw.println("// Auto-generated by CHISA v2 — REG_ORACLE(member_access, trace_key)")
    pw.println("// Consumed by the scalar trace generator; capture is PRE-eval.")
    // Compiler-created banks live as flattened top-object lane arrays, not in
    // the source module hierarchy; tap them by their storage spelling.
    val bankNames = res.registerBanks.iterator.map(_.name).toSet
    for (o <- res.oracles if o.isRegister) {
      val access =
        if (bankNames(o.flatName)) registerBankStorageName(o.flatName)
        else o.flatName
      if (o.words > 1) pw.println(s"""  REG_ORACLE_WORD(t.$access, ${o.word}, "${o.traceKey}");""")
      else pw.println(s"""  REG_ORACLE(t.$access, "${o.traceKey}");""")
    }
    pw.close()
    println(s"[v2] wrote ${f.getPath}")
  }

  /** Physical layout of every compiler-created register bank: which source
    * leaves it packs and at which bit range. The model line rebinds member
    * streams to bank streams with exactly this table, and the audit re-locks
    * against it; nothing downstream should re-derive slices from names. */
  private def writeRegisterBankManifest(res: Result, f: File): Unit = {
    val oracleByFlat = res.oracles.iterator.map(o => o.flatName -> o.traceKey).toMap
    val pw = new java.io.PrintWriter(f)
    pw.println("{")
    pw.println(s"""  "bankCount": ${res.registerBanks.size},""")
    pw.println("""  "banks": [""")
    for ((bank, index) <- res.registerBanks.zipWithIndex) {
      val comma = if (index == res.registerBanks.size - 1) "" else ","
      val fields = bank.fields.map { field =>
        s"""{"source":"${field.source}","width":${field.width},""" +
          s""""high":${field.high},"low":${field.low}}"""
      }.mkString(",")
      pw.println(s"""    {"name":"${bank.name}",""" +
        s""""traceKey":${oracleByFlat.get(bank.name).map("\"" + _ + "\"").getOrElse("null")},""" +
        s""""width":${bank.width},"selfRecurrent":${bank.selfRecurrent},""" +
        s""""fields":[$fields]}$comma""")
    }
    pw.println("  ]")
    pw.println("}")
    pw.close()
    println(s"[v2] wrote ${f.getPath} (${res.registerBanks.size} banks)")
  }

  /** Comb cut points: (a) probe list for the scalar emit's --probe-signals
    * promotion; (b) PUSH_AS lines reading the promoted globals POST-eval.
    * Same manifest, same keys — nothing inferred on the consumer side. */
  private def writeCombProbeFiles(res: Result, probeJson: File, probeInc: File): Unit = {
    val combs = res.oracles.filterNot(_.isRegister)
    val pj = new java.io.PrintWriter(probeJson)
    pj.println("[")
    combs.zipWithIndex.foreach { case (o, i) =>
      val comma = if (i < combs.size - 1) "," else ""
      pj.println(s"""  {"signal": "${o.flatName}", "trace": "${o.traceKey}"}$comma""")
    }
    pj.println("]")
    pj.close()
    val pi = new java.io.PrintWriter(probeInc)
    pi.println("// Auto-generated by CHISA v2 — PUSH_AS(promoted_global, trace_key), POST-eval values.")
    if (combs.isEmpty) pi.println("  // (no comb cut points)")
    for (o <- combs)
      pi.println(s"""  PUSH_AS(${o.flatName.replace('.', '$')}, "${o.traceKey}");""")
    pi.close()
    println(s"[v2] wrote ${probeJson.getPath} + ${probeInc.getPath} (${combs.size} comb probes)")
  }
}
