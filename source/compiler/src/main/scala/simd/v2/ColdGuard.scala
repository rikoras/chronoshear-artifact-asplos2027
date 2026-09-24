package essent.simd.v2

import firrtl._
import firrtl.ir._
import firrtl.PrimOps.{And, Or, Xor, Not, Bits, Pad, Cat, Eq, Shr, Shl}

import collection.mutable

/** Quiet-window specialization ("cold guard").
  *
  * A scalar simulator skips a design's cold expression cones (CSR write
  * paths, CSR read-port selection) through predicted branches, paying nothing
  * per cycle. Vectorization turns those branches into mask/blend dataflow
  * that evaluates both sides of every mux every window. This pass finds the
  * rare-true signals that gate such cones, specializes every comb template
  * under "all of them are 0/false" (constant folding + constant propagation
  * + dead-template elimination), and the emitter dispatches once per window:
  * quiet windows run the specialized image, any window where a guard fires
  * runs the original code. Semantics are bit-identical by construction —
  * the specialized code is the partial evaluation of the full code at values
  * the dispatch just tested.
  *
  * Guard forms:
  *   - named 1-bit comb signal assumed 0 (the shared CSR write-enable,
  *     picked as the name read by the most $gwen expressions);
  *   - predicate `eq(signal, const)` assumed false (selects of muxes that
  *     gate large cones but were inlined by the single-use inliner, e.g. the
  *     CSR arm of the writeback mux). Candidates are collected from the comb
  *     cut points' $rtl cones and scored by how many additional templates
  *     die; only a clear winner is kept.
  */
object ColdGuard {

  /** One guard signal. Exactly one of `name`/`pred` is set. `readyTids` are
    * the template ids whose emission completes the guard's inputs — the
    * window dispatch flag can be computed only after all of them. */
  case class GuardSig(
    desc: String,
    name: Option[String],
    pred: Option[Expression],
    readyTids: Set[Int]
  )

  case class TierBenefit(
    specializedTemplates: Int,
    deadTemplates: Int,
    identityCommits: Int,
    oracleHoldVerifies: Int,
    zeroGwenChains: Int
  )

  /** One cumulative quiet image. `base` assumes only the shared write-enable
    * and reset are zero. `extra`, when present, additionally assumes the
    * selected read-side predicate is false. Keeping both images lets emission
    * use the write-side result as soon as its producer is ready instead of
    * waiting for a late pipeline-register source needed only by the read mux. */
  case class Tier(
    label: String,
    guards: Seq[GuardSig],
    quietStmt: Map[Int, Statement],    // tid -> specialized stmt (only where it differs)
    deadTids: Set[Int],                // comb tids with no live reader in this quiet world
    quietHoldRegs: Set[String],        // quiet $next == the register: commit skipped when quiet
    quietOracleHoldRegs: Set[String],  // same proof for RPOracle: verify adjacent injected states
    quietZeroGwenRegs: Set[String]     // gwen proven 0: serial guard collapses to broadcast
  ) {
    def readyTids: Set[Int] = guards.iterator.flatMap(_.readyTids).toSet
    def touches(tid: Int): Boolean = quietStmt.contains(tid) || deadTids.contains(tid)
    def benefit: TierBenefit = TierBenefit(
      quietStmt.size, deadTids.size, quietHoldRegs.size,
      quietOracleHoldRegs.size, quietZeroGwenRegs.size)
  }

  case class Spec(base: Tier, extra: Option[Tier]) {
    def tiers: Seq[Tier] = base +: extra.toSeq
  }

  // Local structural read-set (mirror of V2Pipeline's; kept private there).
  private def exprReads(e: Expression): Seq[String] = e match {
    case w: WRef => Seq(w.name)
    case w: WSubField => Seq(essent.Emitter.emitExpr(w)(null, essent.Emitter.DefaultContext))
    case m: Mux => exprReads(m.cond) ++ exprReads(m.tval) ++ exprReads(m.fval)
    case p: DoPrim => p.args.flatMap(exprReads)
    case v: ValidIf => exprReads(v.cond) ++ exprReads(v.value)
    case c: WSubAccess => exprReads(c.expr) ++ exprReads(c.index)
    case _ => Seq.empty
  }

  private def stmtReads(s: Statement): Seq[String] = s match {
    case b: Block => b.stmts.flatMap(stmtReads)
    case d: DefNode => exprReads(d.value)
    case c: Connect => exprReads(c.expr)
    case p: Print => p.args.flatMap(exprReads) ++ exprReads(p.en)
    case st: Stop => exprReads(st.en)
    case mw: essent.ir.MemWrite => exprReads(mw.wrEn) ++ exprReads(mw.wrMask) ++
      exprReads(mw.wrAddr) ++ exprReads(mw.wrData)
    case lt: essent.ir.LookupTable => exprReads(lt.indexExpr)
    case _ => Seq.empty
  }

  private def wOf(t: Type): BigInt = firrtl.bitWidth(t)

  private def legalize(e: Expression, tpe: Type): Expression = {
    val w = wOf(tpe)
    val ew = wOf(e.tpe)
    if (ew > w) DoPrim(Bits, Seq(e), Seq(w - 1, BigInt(0)), tpe)
    else if (ew < w) DoPrim(Pad, Seq(e), Seq(w), tpe)
    else e
  }

  private var predHits = 0  // debug: how many predicate folds fired in a runCore

  /** Substitute literals for `env` names, force predicates in `falsePreds`
    * (matched by serialization) to 0, then constant-fold. Width discipline
    * mirrors V2Pipeline's simplifier. */
  private def substFold(e0: Expression, env: Map[String, BigInt],
      falsePreds: Set[String]): (Expression, Boolean) = {
    var changed = false
    def lit(x: Expression): Option[BigInt] = x match {
      case u: UIntLiteral => Some(u.value)
      case _ => None
    }
    def uint(v: BigInt, wid: BigInt): Expression = UIntLiteral(v, IntWidth(wid))
    def mask(wid: BigInt): BigInt = (BigInt(1) << wid.toInt) - 1
    def allOnes(x: BigInt, wid: BigInt): Boolean = x == mask(wid)
    def sameW(a: Expression, t: Type): Boolean = wOf(a.tpe) == wOf(t)
    def go(x0: Expression): Expression = {
      val x = x0 match {
        case wr: WRef if env.contains(wr.name) =>
          changed = true
          uint(env(wr.name), wOf(wr.tpe))
        case other => other.mapExpr(go)
      }
      val r = x match {
        case p @ DoPrim(Eq, _, _, _)
          if falsePreds.nonEmpty && falsePreds.contains(p.serialize) =>
          predHits += 1
          uint(0, 1)
        case DoPrim(And, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
          case (Some(p), Some(q)) => uint(p & q, wOf(tpe))
          case (Some(p), _) if p == 0 => uint(0, wOf(tpe))
          case (_, Some(q)) if q == 0 => uint(0, wOf(tpe))
          case (Some(p), _) if allOnes(p, wOf(a.tpe)) && sameW(a, tpe) && sameW(b, tpe) => b
          case (_, Some(q)) if allOnes(q, wOf(b.tpe)) && sameW(a, tpe) && sameW(b, tpe) => a
          case _ => x
        }
        case DoPrim(Or, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
          case (Some(p), Some(q)) => uint(p | q, wOf(tpe))
          case (Some(p), _) if p == 0 && sameW(b, tpe) => b
          case (_, Some(q)) if q == 0 && sameW(a, tpe) => a
          case (Some(p), _) if allOnes(p, wOf(a.tpe)) && sameW(a, tpe) => uint(mask(wOf(tpe)), wOf(tpe))
          case (_, Some(q)) if allOnes(q, wOf(b.tpe)) && sameW(b, tpe) => uint(mask(wOf(tpe)), wOf(tpe))
          case _ => x
        }
        case DoPrim(Xor, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
          case (Some(p), Some(q)) => uint(p ^ q, wOf(tpe))
          case (Some(p), _) if p == 0 && sameW(b, tpe) => b
          case (_, Some(q)) if q == 0 && sameW(a, tpe) => a
          case _ => x
        }
        case DoPrim(Not, Seq(a), _, tpe) => lit(a) match {
          case Some(p) => uint(~p & mask(wOf(tpe)), wOf(tpe))
          case None => x
        }
        case DoPrim(Bits, Seq(a), Seq(hi, lo), tpe) => lit(a) match {
          case Some(p) => uint((p >> lo.toInt) & mask(hi - lo + 1), wOf(tpe))
          case None => x
        }
        case DoPrim(Pad, Seq(a), Seq(_), tpe) => lit(a) match {
          case Some(p) => uint(p, wOf(tpe))
          case None => x
        }
        case DoPrim(Cat, Seq(a, b), _, tpe) => (lit(a), lit(b)) match {
          case (Some(p), Some(q)) => uint((p << wOf(b.tpe).toInt) | q, wOf(tpe))
          case _ => x
        }
        case DoPrim(Eq, Seq(a, b), _, _) => (lit(a), lit(b)) match {
          case (Some(p), Some(q)) => uint(if (p == q) 1 else 0, 1)
          case _ => x
        }
        case Mux(c, t, f, tpe) => lit(c) match {
          case Some(p) =>
            val arm = if (p != 0) t else f
            if (sameW(arm, tpe)) arm else legalize(arm, tpe)
          case None => x
        }
        case other => other
      }
      if (!(r eq x)) changed = true
      r
    }
    val out = go(e0)
    (out, changed)
  }

  private def specializeStmt(s: Statement, env: Map[String, BigInt],
      falsePreds: Set[String]): (Statement, Boolean) = s match {
    case d: DefNode =>
      val (v, ch) = substFold(d.value, env, falsePreds)
      (if (ch) d.copy(value = v) else d, ch)
    case c: Connect =>
      val (v, ch) = substFold(c.expr, env, falsePreds)
      (if (ch) c.copy(expr = v) else c, ch)
    case lt: essent.ir.LookupTable =>
      val (v, ch) = substFold(lt.indexExpr, env, falsePreds)
      (if (ch) lt.copy(indexExpr = v) else lt, ch)
    case other =>
      var ch = false
      val ns = other.mapExpr { e =>
        val (v, c) = substFold(e, env, falsePreds)
        ch ||= c
        v
      }
      (if (ch) ns else other, ch)
  }

  /** Everything the quiet world derives from one guard assumption set. */
  private case class Core(
    env: Map[String, BigInt],
    quietOf: Int => Statement,
    changedTids: Set[Int],
    deadTids: Set[Int],
    quietHoldRegs: Set[String],
    quietOracleHoldRegs: Set[String],
    quietZeroGwenRegs: Set[String]
  )

  private def runCore(res: V2Pipeline.Result, zeroNames: Set[String],
      falsePreds: Set[String],
      fixedStateProofs: Option[(Set[String], Set[String], Set[String])] = None): Core = {
    // ---- specialization with constant propagation to fixpoint ----
    var env: Map[String, BigInt] = zeroNames.iterator.map(_ -> BigInt(0)).toMap
    val spec = mutable.Map[Int, Statement]()
    var rounds = 0
    var envGrew = true
    while (envGrew && rounds < 8) {
      envGrew = false
      rounds += 1
      // RComb only: effect statements (Print/Stop) are emitted via the CEffect
      // category, which always executes the ORIGINAL statement with no
      // quiet/loud dispatch. Specializing them here would let the quiet-world
      // liveness walk (below) root on the specialized reads and mark an
      // effect's enable producers dead in quiet windows — the un-specialized
      // effect would then read stale lane arrays (spurious/missed printf).
      // Keeping effects out of `spec` makes quietOf(effect) the original
      // statement, so its producers stay live exactly as emitted.
      for (n <- res.nodes if n.role == RComb) {
        val base = spec.getOrElse(n.id, n.stmt)
        val (ns, ch) = specializeStmt(base, env, falsePreds)
        if (ch) spec(n.id) = ns
        val constant = spec.getOrElse(n.id, n.stmt) match {
          case d: DefNode => d.value match {
            case u: UIntLiteral => Some(u.value)
            case _ => None
          }
          // Flattened module boundaries are Connects.  Treat a specialized
          // literal Connect exactly like a literal DefNode so a cold activity
          // condition can propagate through nested module IO instead of
          // stopping at the first boundary.
          case c: Connect => c.expr match {
            case u: UIntLiteral => Some(u.value)
            case _ => None
          }
          case _ => None
        }
        for (name <- n.produces; value <- constant if !env.contains(name)) {
          env += name -> value
          envGrew = true
        }
      }
    }
    def quietOf(tid: Int): Statement = spec.getOrElse(tid, res.nodes(tid).stmt)

    // ---- identity-hold registers ----
    // A self-holding register whose quiet $next resolves to the register
    // itself makes the commit an identity copy — skippable when quiet. Walk
    // down pad / low-bits truncation / all-ones masking / zero shifts,
    // tracking how many low bits are guaranteed preserved; reaching WRef(r)
    // with at least the register's width preserved proves value identity.
    def lowMaskBits(v: BigInt): Option[Int] =
      if (v.signum > 0 && (v & (v + 1)) == 0) Some(v.bitLength) else None
    def resolvesToReg(e: Expression, r: String, rWidth: Int, kept: Int, depth: Int): Boolean = {
      if (depth > 12 || kept < rWidth) return false
      e match {
        case DoPrim(Pad, Seq(a), _, _) => resolvesToReg(a, r, rWidth, kept, depth + 1)
        case DoPrim(Bits, Seq(a), Seq(hi, lo), _) if lo == BigInt(0) =>
          resolvesToReg(a, r, rWidth, math.min(kept, hi.toInt + 1), depth + 1)
        case DoPrim(And, Seq(a, u: UIntLiteral), _, _) =>
          lowMaskBits(u.value).exists(k => resolvesToReg(a, r, rWidth, math.min(kept, k), depth + 1))
        case DoPrim(And, Seq(u: UIntLiteral, a), _, _) =>
          lowMaskBits(u.value).exists(k => resolvesToReg(a, r, rWidth, math.min(kept, k), depth + 1))
        case DoPrim(Shr, Seq(a), Seq(n), _) if n == BigInt(0) =>
          resolvesToReg(a, r, rWidth, kept, depth + 1)
        case DoPrim(Shl, Seq(a), Seq(n), _) if n == BigInt(0) =>
          resolvesToReg(a, r, rWidth, kept, depth + 1)
        case wr: WRef if wr.name == r => true
        case wr: WRef =>
          res.producesIdx.get(wr.name).flatMap { tid =>
            quietOf(tid) match {
              case d: DefNode if res.nodes(tid).role == RComb => Some(d.value)
              case _ => None
            }
          }.exists(resolvesToReg(_, r, rWidth, kept, depth + 1))
        case _ => false
      }
    }
    def quietNextIsIdentity(ri: V2Pipeline.RegInfo): Boolean =
      res.producesIdx.get(ri.nextName).exists { tid =>
        quietOf(tid) match {
          case d: DefNode =>
            resolvesToReg(d.value, ri.name, wOf(ri.tpe).toInt, Int.MaxValue, 0)
          case _ => false
        }
      }

    val derivedQuietHoldRegs: Set[String] = res.regs.values.collect {
      case ri if (ri.plan match {
        case RPCondHold | RPAffineScan | RPSerialNext(_, _) => true
        case _ => false
      }) && ri.verifyId.isEmpty && quietNextIsIdentity(ri) => ri.name
    }.toSet

    // An oracled register still has its original RTL $next cone solely for
    // Micro-Lockstep verification.  If the exact same quiet specialization
    // proves $next == r, materializing that cone and its lane array adds no
    // checking power: compare injected r[k] with injected r[k+/-1] instead.
    // A change in the oracle stream is then rejected on the same transition;
    // a loud window retains the original RTL-next comparison unchanged.
    val derivedQuietOracleHoldRegs: Set[String] = res.regs.values.collect {
      case ri if ri.plan == RPOracle && quietNextIsIdentity(ri) => ri.name
    }.toSet

    // Guarded serial registers whose gwen is proven 0 when quiet: the serial
    // block collapses to a broadcast under the window flag and its gwen
    // arrays stop being runtime roots.
    val derivedQuietZeroGwenRegs: Set[String] = res.regs.values.collect {
      case ri if (ri.plan match { case RPSerialNext(_, g) => g; case _ => false }) &&
        env.get(ri.name + "$gwen").contains(BigInt(0)) => ri.name
    }.toSet

    // Extra predicates are selected for a read-side cone. Do not let them
    // become new proofs that state updates can be removed: otherwise a read
    // mux guard could accidentally suppress trap/interrupt/debug/counter state.
    // Its liveness calculation therefore inherits the base tier's state proofs.
    val (quietHoldRegs, quietOracleHoldRegs, quietZeroGwenRegs) =
      fixedStateProofs.getOrElse((derivedQuietHoldRegs,
        derivedQuietOracleHoldRegs, derivedQuietZeroGwenRegs))

    // ---- liveness in the quiet world ----
    val rootNames = mutable.Set[String]()
    for ((r, ri) <- res.regs) {
      if (!quietHoldRegs.contains(r) && !quietOracleHoldRegs.contains(r))
        rootNames += ri.nextName
      ri.plan match {
        case RPCondHold =>
          rootNames += r + "$wen"
          rootNames += r + "$wdata"
        case RPAffineScan =>
          // The prefix scan reads both step operands unconditionally every
          // window; they must never land in a cold group (Sodor PC, 2026-09-04).
          rootNames += r + "$keep"
          rootNames += r + "$add"
        case RPSerialNext(folded, g) =>
          val (qf, _) = substFold(folded, env, falsePreds)
          rootNames ++= exprReads(qf).filter(_ != r)
          if (g && !quietZeroGwenRegs.contains(r)) rootNames += r + "$gwen"
        case _ =>
      }
    }
    for (c <- res.combCuts.keys) {
      rootNames += c + "$rtl"
      rootNames += c
    }
    // Host adapters consume ExtModule inputs after eval, outside the FIRRTL
    // template graph.  Keep their producers live in every quiet image.
    rootNames ++= res.hostBoundaryInputs
    // Lifted state kernels are emitted in their original form in both the
    // loud and quiet worlds.  A chronological read needs not only its address
    // cone, but also every write operand used for within-window forwarding;
    // the end-of-window commit needs the same write operands.  Root those
    // comb cones here while still allowing their expressions to specialize
    // under the guard.  We deliberately make no quiet identity proof about
    // the physical array itself.
    for (n <- res.nodes) n.role match {
      case RStateRead(array) =>
        rootNames ++= stmtReads(n.stmt).filter(_ != array)
        rootNames ++= stmtReads(res.nodes(res.stateArrays(array).commitId).stmt)
      case RStateCommit(_) =>
        rootNames ++= stmtReads(n.stmt)
      case _ =>
    }
    rootNames ++= zeroNames - "reset"   // window reduces read the guard arrays

    // Top-level ports (dot-free names) are externally visible — the harness
    // reads them — and always execute. Dotted Connect targets are flattened
    // module-boundary signals: internal dataflow, live only if read (the
    // CSR read port `csr.io_rw_rdata` is exactly such a Connect).
    def isTopPortConnect(n: TemplateNode): Boolean =
      n.stmt.isInstanceOf[Connect] && n.produces.exists(!_.contains('.'))
    val liveTids = mutable.Set[Int]()
    val queue = mutable.Queue[String]()
    val queued = mutable.Set[String]()
    def push(n: String): Unit = if (queued.add(n)) queue.enqueue(n)
    rootNames.foreach(push)
    for (n <- res.nodes) n.role match {
      case RComb if isTopPortConnect(n) =>
        liveTids += n.id
        stmtReads(quietOf(n.id)).foreach(push)
      case REffect =>
        stmtReads(quietOf(n.id)).foreach(push)
      case _ =>
    }
    while (queue.nonEmpty) {
      val name = queue.dequeue()
      res.producesIdx.get(name).foreach { tid =>
        if (res.nodes(tid).role == RComb && liveTids.add(tid))
          stmtReads(quietOf(tid)).foreach(push)
      }
    }
    val deadTids = res.nodes.iterator.collect {
      case n if n.role == RComb && !isTopPortConnect(n) &&
        n.stmt != EmptyStmt && !liveTids.contains(n.id) => n.id
    }.toSet

    Core(env, quietOf, spec.keySet.toSet, deadTids, quietHoldRegs,
      quietOracleHoldRegs, quietZeroGwenRegs)
  }

  /** Predicate candidates: mux selects of shape eq(<ref>, <const>) inside the
    * comb cut points' $rtl cones (the inliner usually dissolved their names).
    * These gate value cones a real scalar run would branch around. */
  private def discoverPredCandidates(res: V2Pipeline.Result): Seq[Expression] = {
    val out = mutable.LinkedHashMap[String, Expression]()
    val visited = mutable.Set[String]()
    def walkExpr(e: Expression, depth: Int): Unit = {
      if (depth > 200 || out.size >= 24) return
      e match {
        case m: Mux =>
          m.cond match {
            case p @ DoPrim(Eq, Seq(_: WRef, _: UIntLiteral), _, _) if wOf(p.tpe) == 1 =>
              out.getOrElseUpdate(p.serialize, p)
            case p @ DoPrim(Eq, Seq(_: UIntLiteral, _: WRef), _, _) if wOf(p.tpe) == 1 =>
              out.getOrElseUpdate(p.serialize, p)
            case _ =>
          }
          walkExpr(m.cond, depth + 1); walkExpr(m.tval, depth + 1); walkExpr(m.fval, depth + 1)
        case p: DoPrim => p.args.foreach(walkExpr(_, depth + 1))
        case v: ValidIf => walkExpr(v.cond, depth + 1); walkExpr(v.value, depth + 1)
        case wr: WRef if visited.add(wr.name) =>
          res.producesIdx.get(wr.name).foreach { tid =>
            if (res.nodes(tid).role == RComb) res.nodes(tid).stmt match {
              case d: DefNode => walkExpr(d.value, depth + 1)
              case _ =>
            }
          }
        case _ =>
      }
    }
    for (c <- res.combCuts.keys; tid <- res.producesIdx.get(c + "$rtl")) {
      res.nodes(tid).stmt match {
        case d: DefNode => walkExpr(d.value, 0)
        case _ =>
      }
    }
    out.values.toSeq
  }

  private def guardReadyTids(res: V2Pipeline.Result, reads: Seq[String]): Set[Int] =
    reads.distinct.flatMap { n =>
      res.regs.get(n).map(_.sourceId)
        .orElse(res.producesIdx.get(n).filter(t => res.nodes(t).role == RComb))
    }.toSet

  def build(res: V2Pipeline.Result): Option[Spec] =
    build(res, sys.env.getOrElse("V2_COLD_GUARD", "auto"),
      sys.env.getOrElse("V2_COLD_GUARD_EXTRA", "auto"))

  /** Explicit configuration entry used by focused compiler tests. */
  private[v2] def build(res: V2Pipeline.Result, configuredMode: String,
      configuredExtraMode: String): Option[Spec] = {
    val mode = configuredMode.trim
    if (mode == "0" || mode.equalsIgnoreCase("off")) return None
    val extraMode = configuredExtraMode.trim
    val wantExtra = !(extraMode == "0" || extraMode.equalsIgnoreCase("off"))

    // ---- base guard: the comb name read by the most $gwen expressions ----
    val guardedRegs = res.regs.values.collect {
      case ri if (ri.plan match { case RPSerialNext(_, g) => g; case _ => false }) => ri.name
    }.toSeq
    val gwenReadFreq = mutable.Map[String, Int]().withDefaultValue(0)
    for (r <- guardedRegs; tid <- res.producesIdx.get(r + "$gwen")) {
      res.nodes(tid).stmt match {
        case d: DefNode =>
          exprReads(d.value).distinct.foreach { n =>
            if (n != "reset") gwenReadFreq(n) += 1
          }
        case _ =>
      }
    }
    def oneBitCombProducer(name: String): Option[Int] =
      res.producesIdx.get(name).filter { tid =>
        res.nodes(tid).role == RComb && (res.nodes(tid).stmt match {
          case d: DefNode => wOf(d.value.tpe) == 1
          case c: Connect => wOf(c.expr.tpe) == 1
          case _ => false
        })
      }
    def isResetSignalName(name: String): Boolean = {
      val lower = name.toLowerCase
      lower == "reset" || lower.endsWith(".reset") || lower.endsWith("$reset")
    }
    def legalGuardName(name: String): Boolean =
      !isResetSignalName(name) && oneBitCombProducer(name).isDefined

    // Targeted full-chip diagnostic.  A comma-separated list of name
    // fragments asks the existing exact quiet-world analysis to score matching
    // one-bit comb signals.  This is intentionally opt-in: broad candidate
    // searches are useful while locating a module activity predicate, but do
    // not belong on every production compile.
    sys.env.get("V2_COLD_GUARD_SCAN").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty) match {
      case patterns if patterns.nonEmpty =>
        val directReads = mutable.Map[String, Int]().withDefaultValue(0)
        for (n <- res.nodes; read <- stmtReads(n.stmt).distinct)
          directReads(read) += 1
        val limit = sys.env.get("V2_COLD_GUARD_SCAN_LIMIT")
          .flatMap(_.trim.toIntOption).filter(_ > 0).getOrElse(64)
        val matches = res.producesIdx.keysIterator
          .filter(legalGuardName)
          .filter(name => patterns.exists(name.contains))
          .toSeq.sortBy(name => (-directReads(name), name))
        println(s"[v2-debug] cold guard scan: ${matches.size} match(es), scoring ${math.min(limit, matches.size)}")
        val scored = matches.take(limit).map { name =>
          val core = runCore(res, Set(name, "reset"), Set.empty)
          val specialized = core.changedTids.count(tid => !core.deadTids(tid))
          (name, directReads(name), specialized, core.deadTids.size,
            core.quietHoldRegs.size, core.quietOracleHoldRegs.size,
            core.quietZeroGwenRegs.size)
        }.sortBy { case (name, reads, specialized, dead, holds, oracleHolds, gwens) =>
          (-dead, -holds, -oracleHolds, -specialized, -gwens, -reads, name)
        }
        for ((name, reads, specialized, dead, holds, oracleHolds, gwens) <- scored)
          println(s"[v2-debug] cold scan dead=$dead hold=$holds specialized=$specialized " +
            s"oracleHold=$oracleHolds gwen=$gwens directReads=$reads $name")
      case _ =>
    }
    val autoPick = gwenReadFreq.toSeq
      .filter { case (name, _) => legalGuardName(name) }
      .sortBy { case (name, count) => (-count, name) }
      .headOption
    val guardNames: Seq[String] = mode match {
      case "auto" | "" | "1" | "on" =>
        autoPick match {
          case Some((n, c)) if c >= 3 => Seq(n)
          case _ =>
            println("[v2] cold guard: no shared write-enable found (need >=3 guarded registers) — disabled")
            return None
        }
      case explicit if explicit.equalsIgnoreCase("reset-only") => Seq.empty
      case explicit => explicit.split(',').toSeq.map(_.trim).filter(_.nonEmpty).distinct
    }
    val invalidGuards = guardNames.filter(name => oneBitCombProducer(name).isEmpty)
    if (invalidGuards.nonEmpty) {
      println(s"[v2] cold guard: '${invalidGuards.head}' is not a 1-bit comb producer — disabled")
      return None
    }
    val guardTids = guardNames.map(name => oneBitCombProducer(name).get)

    val zeroNames = guardNames.toSet + "reset"
    val base = runCore(res, zeroNames, Set.empty)

    // ---- extra predicate guard: pick the candidate that kills the most
    //      additional templates; keep only a clear winner ----
    var chosenPred: Option[(Expression, Int)] = None
    if (wantExtra) {
      val cands = discoverPredCandidates(res)
      if (sys.env.contains("V2_COLD_GUARD_DEBUG"))
        println(s"[v2-debug] cold guard: ${cands.size} predicate candidate(s)")
      for (p <- cands) {
        predHits = 0
        val cres = runCore(res, zeroNames, Set(p.serialize),
          fixedStateProofs = Some((base.quietHoldRegs,
            base.quietOracleHoldRegs, base.quietZeroGwenRegs)))
        val dead = cres.deadTids.size
        val marginal = dead - base.deadTids.size
        if (sys.env.contains("V2_COLD_GUARD_DEBUG")) {
          println(s"[v2-debug]   marginal=$marginal predHits=$predHits  ${p.serialize.take(90)}")
          val rdata = res.producesIdx.keys.find(_.endsWith("io_rw_rdata"))
          rdata.foreach { rn =>
            val tid = res.producesIdx(rn)
            val deadQ = cres.deadTids.contains(tid)
            val readers = res.nodes.iterator.filter(n =>
              (n.role == RComb || n.role == REffect) && !cres.deadTids.contains(n.id) &&
              stmtReads(cres.quietOf(n.id)).contains(rn)).map(_.id).take(5).toSeq
            println(s"[v2-debug]     $rn dead=$deadQ liveQuietReaders=$readers")
          }
        }
        if (marginal >= 16 && chosenPred.forall(_._2 < marginal))
          chosenPred = Some((p, marginal))
      }
    }

    // Diagnostic/performance shape closest to scalar Verilator: keep every
    // still-live statement in its original form and guard only work proven
    // unreachable in a quiet window.  This avoids duplicating hundreds of
    // merely-simplified templates in the hot text image.  Identity commits
    // and zero-gwen serial chains remain specialized through their dedicated
    // emitter paths.
    val deadOnly = sys.env.get("V2_COLD_GUARD_DEAD_ONLY")
      .exists(v => v == "1" || v.equalsIgnoreCase("true") || v.equalsIgnoreCase("on"))
    def quietStmtOf(core: Core): Map[Int, Statement] = {
      val liveChanged = core.changedTids.iterator
        .filterNot(core.deadTids.contains)
      if (!deadOnly)
        liveChanged.map(t => t -> core.quietOf(t)).toMap
      else {
        // Quiet liveness is computed from the specialized statements.  When
        // constant propagation crosses a template boundary, a live quiet
        // statement may stop reading a producer and make that producer dead.
        // Emitting the original live statement in that situation is unsound:
        // it would still read the skipped producer's stale scratch value
        // (notably reset_n=~reset in the debug CDC during a reset=0 window).
        // Keep only these boundary specializations; every other live template
        // remains in its original form, preserving the small dead-only image.
        val deadProduced = core.deadTids.iterator
          .flatMap(t => res.nodes(t).produces).toSet
        liveChanged
          .filter(t => stmtReads(res.nodes(t).stmt).exists(deadProduced.contains))
          .map(t => t -> core.quietOf(t))
          .toMap
      }
    }

    val extraCore = chosenPred.map { case (p, _) =>
      val core = runCore(res, zeroNames, Set(p.serialize),
        fixedStateProofs = Some((base.quietHoldRegs,
          base.quietOracleHoldRegs, base.quietZeroGwenRegs)))
      (p, core)
    }
    // A template that is live in the base world but dead with the read-side
    // predicate belongs to the extra stage. Do not partially specialize it in
    // base: then the late dispatch can use full/extra safely without needing a
    // third base image for the predicate-active case.
    val extraReadTids = extraCore.map { case (_, core) =>
      val newlyDead = core.deadTids -- base.deadTids
      val differentlySpecialized = core.changedTids.filter { tid =>
        core.quietOf(tid).serialize != base.quietOf(tid).serialize
      }
      newlyDead ++ differentlySpecialized
    }.getOrElse(Set.empty)
    val baseGuards = guardNames.zip(guardTids).map { case (name, tid) =>
      GuardSig(name, Some(name), None, Set(tid))
    }
    val baseTier = Tier("base", baseGuards, quietStmtOf(base) -- extraReadTids,
      base.deadTids, base.quietHoldRegs, base.quietOracleHoldRegs,
      base.quietZeroGwenRegs)

    val extraTier = extraCore.map { case (p, core) =>
      val guard = GuardSig(p.serialize.take(60), None, Some(p),
        guardReadyTids(res, exprReads(p)))
      Tier("extra", Seq(guard), quietStmtOf(core), core.deadTids,
        core.quietHoldRegs, core.quietOracleHoldRegs, core.quietZeroGwenRegs)
    }

    val combCount = res.nodes.count(n => n.role == RComb && n.stmt != EmptyStmt)
    val predDesc = chosenPred.map { case (p, m) =>
      s"; extra pred '${p.serialize.take(48)}' (+$m dead)"
    }.getOrElse("")
    val bb = baseTier.benefit
    val extraDesc = extraTier.map { t =>
      val b = t.benefit
      s"; extra total ${b.specializedTemplates} specialized, ${b.deadTemplates} dead"
    }.getOrElse("")
    val guardDesc = if (guardNames.isEmpty) "reset-only" else guardNames.mkString(" | ")
    val shapeDesc = if (deadOnly) "; dead-only emission" else ""
    println(s"[v2] cold guard: '$guardDesc'$predDesc$shapeDesc — base specializes " +
      s"${bb.specializedTemplates} and kills ${bb.deadTemplates} of $combCount comb templates, " +
      s"skips ${bb.identityCommits} identity commits, rewrites " +
      s"${bb.oracleHoldVerifies} oracle hold checks, collapses ${bb.zeroGwenChains} gwen guards" +
      extraDesc)
    Some(Spec(baseTier, extraTier))
  }
}
