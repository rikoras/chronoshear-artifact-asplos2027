package essent.passes

import essent.Emitter._
import essent.EssentOptionsAnnotation
import essent.simd.{LaneTag, SIMDPlanAnnotation, VecStmtInfo,
  MH_PrefixScan, MH_Serial, MH_Fallback, MuxHoldStrategy}
import essent.ir._
import firrtl._
import firrtl.ir._
import firrtl.Mappers._
import firrtl.options.Dependency
import firrtl.passes._
import firrtl.Utils._
import firrtl.annotations.{Annotation, NoTargetAnnotation}

import scala.collection.mutable

case class RegUpdateDirectionAnnotation(isForward: Boolean) extends NoTargetAnnotation

private object RegUpdateInfo {
  val Default = NoInfo
  def interLane(regName: String, fromName: String): Info =
    FileInfo(s"SplitRegUpdates:inter_lane $regName <- $fromName")
  def finalCommit(regName: String): Info =
    FileInfo(s"SplitRegUpdates:final_commit $regName <- ${regName}$$next")
  def simple(info: String): Info =
    FileInfo(s"$info")
  /** Tag a statement as belonging to a mux-hold CondUpdate group.
   *  Format: "MH:<scalarBaseName>:<role>" where role ∈ {wen, wdata, serial, ps_we, ps_d, commit}
   *  BuildScheduleAtoms reads this tag to group statements into CondUpdateAtoms. */
  def muxHoldTag(scalarBase: String, role: String): Info =
    FileInfo(s"MH:$scalarBase:$role")
}

/** Register-class hints once emitted by the retired v1 RegisterDependencyGraph.
  * No producer remains; getRegClass always sees the empty default now.
  * Keys were "module.regName". */
case class RegClassAnnotation(
    counterRegs: Set[String],
    muxHoldRegs: Set[String]
) extends firrtl.annotations.NoTargetAnnotation

object SplitRegUpdates extends Pass {
  def desc = "Appends $next to the name of any reg being assigned to"

  override def prerequisites = Seq(Dependency(essent.passes.RegFromMem1), Dependency(essent.passes.ReplaceAsyncRegs) , Dependency(essent.passes.ReplaceRsvdKeywords))
  override def optionalPrerequisites = firrtl.stage.Forms.LowFormOptimized
  override def invalidates(a: Transform) = false

  def renameRegStmt(s: Statement): Statement = {
    val replaced = s match {
      case c: Connect if (firrtl.Utils.kind(c.loc) == firrtl.RegKind) => {
        DefNode(c.info, emitExpr(c.loc) + "$next", c.expr)
      }
      case _ => s
    }
    replaced map renameRegStmt
  }

  // --------------- LaneTag-based lane lookup (no annotation needed) ---------------

  /** Build a per-module lookup by extracting LaneTags from module body statements. */
  def buildModuleLookup(body: Statement, moduleName: String): Map[String, VecStmtInfo] =
    LaneTag.buildModuleLookup(body, moduleName)

  /** Get scalarSource from annotation, falling back to name itself for non-SIMD signals. */
  def scalarSourceOf(name: String, lookup: Map[String, VecStmtInfo]): String =
    lookup.get(name).map(_.scalarSource).getOrElse(name)

  /** Get laneIndex from annotation. */
  def laneIndexOf(name: String, lookup: Map[String, VecStmtInfo]): Option[Int] =
    lookup.get(name).map(_.laneIndex)

  /** Compute the suffix after _lane_N in a name, using known laneIndex from annotation. */
  def laneNameSuffix(name: String, laneIndex: Int): String = {
    val laneTag = s"_lane_$laneIndex"
    val pos = name.indexOf(laneTag)
    if (pos >= 0) name.drop(pos + laneTag.length) else ""
  }

  /** Construct a sibling lane name from the same scalar family. */
  def siblingLaneName(name: String, myLaneIndex: Int, targetLane: Int): String = {
    val myTag = s"_lane_$myLaneIndex"
    val targetTag = s"_lane_$targetLane"
    val pos = name.indexOf(myTag)
    if (pos >= 0) name.take(pos) + targetTag + name.drop(pos + myTag.length)
    else name
  }

  /**
   * Compute the module-qualified scalar field key for RDG annotation lookups.
   * RegisterDependencyGraph classifies at post-LowerTypes granularity, so a
   * bundle register `ex_reg_btb_resp` flattened into `ex_reg_btb_resp_cfiType`
   * has its entry as `PatchedRocket.ex_reg_btb_resp_cfiType`.
   * LaneTag's scalarSource is the pre-LowerTypes name `ex_reg_btb_resp`,
   * so we append the field suffix to reconstruct the post-LowerTypes key.
   */
  private def scalarFieldKey(name: String, moduleName: String, lookup: Map[String, VecStmtInfo]): String = {
    val scalarName = laneIndexOf(name, lookup)
      .flatMap(li => LaneTag.stripLaneSegment(name, li))
      .getOrElse(scalarSourceOf(name, lookup))
    moduleName + "." + scalarName
  }

  /** RDG emits oracle-target keys in pre-LowerTypes dotted form
    * ("CSRFile.reg_mstatus.prv"), while post-LowerTypes lane names flatten
    * bundle fields with underscores ("reg_mstatus_prv"). Normalize a key to
    * "<Module>.<flattened_reg>" so both sides compare equal; without this,
    * every bundle-field FVS register silently missed LBN classification. */
  def normalizeOracleKey(k: String): String = {
    val i = k.indexOf('.')
    if (i < 0) k else k.take(i + 1) + k.drop(i + 1).replace('.', '_')
  }

  def isLBNLaneRef(s: String, annos: Seq[Annotation], moduleName: String, lookup: Map[String, VecStmtInfo]): Boolean = {
    val fieldKey = scalarFieldKey(s, moduleName, lookup)
    val baseKey = moduleName + "." + scalarSourceOf(s, lookup)
    annos.exists {
      case plan: SIMDPlanAnnotation =>
        val keys = plan.moduleOracleTargets.keysIterator.map(normalizeOracleKey).toSet
        keys.contains(fieldKey) || keys.contains(baseKey)
      case _ => false
    }
  }

  def isCombOracleLaneRef(s: String, annos: Seq[Annotation], moduleName: String, lookup: Map[String, VecStmtInfo]): Boolean = {
    val fieldKey = scalarFieldKey(s, moduleName, lookup)
    val baseKey = moduleName + "." + scalarSourceOf(s, lookup)
    annos.exists {
      case plan: SIMDPlanAnnotation =>
        plan.combOracleTargets.contains(fieldKey) ||
        plan.combOracleTargets.contains(baseKey)
      case _ => false
    }
  }

  def getTraceMapping(annos: Seq[Annotation]): Map[String, String] = {
    annos.collectFirst { case plan: SIMDPlanAnnotation => plan.moduleOracleTargets }
      .getOrElse(Map.empty)
      .map { case (k, v) => normalizeOracleKey(k) -> v }
  }

  def getCombOracleTraceMapping(annos: Seq[Annotation]): Map[String, String] = {
    annos.collectFirst { case plan: SIMDPlanAnnotation => plan.combOracleTargets }
      .getOrElse(Map.empty)
  }

  def getMuxHoldStrategy(s: String, annos: Seq[Annotation], moduleName: String, lookup: Map[String, VecStmtInfo]): MuxHoldStrategy = {
    val fieldKey = scalarFieldKey(s, moduleName, lookup)
    val baseKey = moduleName + "." + scalarSourceOf(s, lookup)
    annos.collectFirst { case plan: SIMDPlanAnnotation =>
      plan.muxHoldStrategies.get(fieldKey)
        .orElse(plan.muxHoldStrategies.get(baseKey))
    }.flatten.getOrElse(MH_Fallback)
  }

  def getRegClass(annos: Seq[Annotation]): RegClassAnnotation = {
    annos.collectFirst { case rc: RegClassAnnotation => rc }
      .getOrElse(RegClassAnnotation(Set.empty, Set.empty))
  }

  def isCounterReg(name: String, regClass: RegClassAnnotation, moduleName: String, lookup: Map[String, VecStmtInfo]): Boolean = {
    val fieldKey = scalarFieldKey(name, moduleName, lookup)
    val baseKey = moduleName + "." + scalarSourceOf(name, lookup)
    regClass.counterRegs.contains(fieldKey) || regClass.counterRegs.contains(baseKey)
  }

  def isMuxHoldReg(name: String, regClass: RegClassAnnotation, moduleName: String, lookup: Map[String, VecStmtInfo]): Boolean = {
    val fieldKey = scalarFieldKey(name, moduleName, lookup)
    val baseKey = moduleName + "." + scalarSourceOf(name, lookup)
    regClass.muxHoldRegs.contains(fieldKey) || regClass.muxHoldRegs.contains(baseKey)
  }

  // --------------- Mux-hold extraction helpers ---------------

  /** Build map from name → its defining value expression.
    *
    * Captures DefNodes AND single-assignment WIRE definitions (`Connect(wire, expr)`
    * with a WireKind LHS). At this stage (post-ExpandWhens) every wire has exactly
    * one connect, so `name -> expr` is well defined. Capturing wires — not just
    * DefNodes — is what lets the mux-hold walkers (extractMuxHoldPattern,
    * containsRegRef, isExactSelfRef, inlineAndSubstitute) follow a self-reference or
    * hold branch that routes THROUGH a named wire (e.g. `if_pc_next`). Without it,
    * such references dead-end: the register is mis-tagged / fails extraction and
    * silently degrades to a fully-serialized Standard shift that drags its whole
    * reader cone into the SCC (the "mysterious extra scalar atoms" bug).
    *
    * NOTE (intentional, slightly ad-hoc — see docs/SIMD_CORRECTNESS_AND_PERF_RECOVERY.md):
    * this hand-patches wire resolution into the one map every codegen walker shares,
    * rather than introducing a single unified `resolveRef` used everywhere (the
    * proper fix). Relies on the single-assignment-wire invariant. */
  def buildDefNodeMap(s: Statement): Map[String, Expression] = {
    val m = mutable.Map[String, Expression]()
    val wireConnCount = mutable.Map[String, Int]().withDefaultValue(0)
    def walk(st: Statement): Unit = st match {
      case b: Block   => b.stmts.foreach(walk)
      case d: DefNode => m(d.name) = d.value
      case c: Connect => c.loc match {
        case wr: WRef if wr.kind == firrtl.WireKind =>
          wireConnCount(wr.name) += 1
          m(wr.name) = c.expr
        case _ =>
      }
      case _          =>
    }
    walk(s)
    // Defensive: only resolve wires with EXACTLY one connect. If a wire is driven
    // more than once (should not happen post-ExpandWhens, but we do not assume it),
    // `name -> expr` is ill-defined; drop it so walkers treat it as unresolved
    // (same as before this change) rather than following a wrong driver.
    wireConnCount.foreach { case (n, cnt) => if (cnt > 1) m.remove(n) }
    m.toMap
  }

  /** Check whether expr (transitively through DefNodes) references regName */
  private def containsRegRef(
    expr: Expression, regName: String,
    nodeMap: Map[String, Expression], depth: Int = 0
  ): Boolean = {
    if (depth > 15) return false
    expr match {
      case wr: WRef =>
        if (wr.name == regName) true
        else nodeMap.get(wr.name).exists(containsRegRef(_, regName, nodeMap, depth+1))
      case m: Mux        => containsRegRef(m.cond, regName, nodeMap, depth+1) ||
                            containsRegRef(m.tval, regName, nodeMap, depth+1) ||
                            containsRegRef(m.fval, regName, nodeMap, depth+1)
      case d: DoPrim     => d.args.exists(containsRegRef(_, regName, nodeMap, depth+1))
      case v: ValidIf    => containsRegRef(v.cond, regName, nodeMap, depth+1) ||
                            containsRegRef(v.value, regName, nodeMap, depth+1)
      case _ => false
    }
  }

  /** True iff expr is exactly the register's value, possibly wrapped in
    * width-identity operations. Chisel/firrtl width inference routinely wraps
    * the hold branch of a conditional update as `bits(pad(reg, n), k, 0)`;
    * failing to see through those wrappers mis-classifies a plain hold
    * register as self-referencing wdata and serializes its whole reader cone
    * per lane. `truncFloor` tracks the narrowest low-bits truncation applied
    * by enclosing `bits(_, hi, 0)` wrappers: the chain is value-preserving
    * iff no truncation cuts below the register's own width. */
  private def isExactSelfRef(
    expr: Expression, regName: String,
    nodeMap: Map[String, Expression], depth: Int = 0,
    truncFloor: BigInt = BigInt(Int.MaxValue)
  ): Boolean = {
    if (depth > 10) return false
    expr match {
      case wr: WRef if wr.name == regName =>
        truncFloor >= firrtl.bitWidth(wr.tpe)
      case wr: WRef =>
        nodeMap.get(wr.name).exists(isExactSelfRef(_, regName, nodeMap, depth + 1, truncFloor))
      case DoPrim(PrimOps.Pad, Seq(a), _, _) =>
        isExactSelfRef(a, regName, nodeMap, depth + 1, truncFloor)
      case DoPrim(PrimOps.Bits, Seq(a), Seq(hi, lo), _) if lo == BigInt(0) =>
        isExactSelfRef(a, regName, nodeMap, depth + 1, truncFloor.min(hi + 1))
      case DoPrim(PrimOps.AsUInt, Seq(a), _, _) =>
        isExactSelfRef(a, regName, nodeMap, depth + 1, truncFloor)
      case DoPrim(PrimOps.AsSInt, Seq(a), _, _) =>
        isExactSelfRef(a, regName, nodeMap, depth + 1, truncFloor)
      case _ => false
    }
  }

  /** Find top-level Mux(cond, tval, fval_with_self) where cond and tval are
    * free of self-references. Resolves through DefNode indirections while
    * retaining all arithmetic and width-changing operations.
    *
    * Also handles the case where BOTH branches contain self-references,
    * provided one branch is exactly the self-register (a "hold" pattern):
    *   mux(cond, SELF, fval_with_self) → hold when cond, recurse into fval
    *   mux(cond, tval_with_self, SELF) → hold when !cond, recurse into tval
    *
    * serialOk: the caller will route this register through the serial mux-hold
    * chain (genSerialMuxHold), which substitutes remaining self-references in
    * wdata with the previous lane's serial value. Under that contract any
    * subtree is extractable — the identity fallback (wen=1, wdata=whole expr)
    * is always valid, and composing it through the branches above preserves
    * equivalence. Without serialOk, wdata must be self-free, so only exact
    * self-holds are accepted as fallbacks.
    */
  def extractMuxHoldPattern(
    expr: Expression,
    regName: String,
    nodeMap: Map[String, Expression],
    depth: Int = 0,
    serialOk: Boolean = false
  ): Option[(Expression, Expression)] = {
    val one = UIntLiteral(BigInt(1), IntWidth(1))
    if (depth > 10) return None
    expr match {
      case m: Mux =>
        val condFree = !containsRegRef(m.cond, regName, nodeMap)
        val tvalHasSelf = containsRegRef(m.tval, regName, nodeMap)
        val fvalHasSelf = containsRegRef(m.fval, regName, nodeMap)
        if (condFree && fvalHasSelf && !tvalHasSelf) {
          // Pure hold (fval IS the register, possibly pad/bits-wrapped) must be
          // recognized BEFORE recursing: with serialOk the recursion's identity
          // fallback would "succeed" with (wen=1, wdata=self) and needlessly
          // keep the self-reference inside wdata, serializing its reader cone.
          if (isExactSelfRef(m.fval, regName, nodeMap)) Some((m.cond, m.tval))
          else extractMuxHoldPattern(m.fval, regName, nodeMap, depth + 1, serialOk) match {
            case Some((innerWen, innerWdata)) =>
              val wen = DoPrim(PrimOps.Or, Seq(m.cond, innerWen), Seq.empty, UIntType(IntWidth(1)))
              val wdata = Mux(m.cond, m.tval, innerWdata, m.tpe)
              Some((wen, wdata))
            case None =>
              if (serialOk) Some((one, m))
              else None
          }
        } else if (condFree && tvalHasSelf && !fvalHasSelf) {
          if (isExactSelfRef(m.tval, regName, nodeMap)) {
            val notCond = DoPrim(PrimOps.Not, Seq(m.cond), Seq.empty, m.cond.tpe)
            Some((notCond, m.fval))
          } else extractMuxHoldPattern(m.tval, regName, nodeMap, depth + 1, serialOk) match {
            case Some((innerWen, innerWdata)) =>
              val notCond = DoPrim(PrimOps.Not, Seq(m.cond), Seq.empty, m.cond.tpe)
              val wen = DoPrim(PrimOps.Or, Seq(notCond, innerWen), Seq.empty, UIntType(IntWidth(1)))
              val wdata = Mux(notCond, m.fval, innerWdata, m.tpe)
              Some((wen, wdata))
            case None =>
              if (serialOk) Some((one, m))
              else None
          }
        } else if (condFree && tvalHasSelf && fvalHasSelf) {
          val tvalIsSelf = isExactSelfRef(m.tval, regName, nodeMap)
          val fvalIsSelf = isExactSelfRef(m.fval, regName, nodeMap)
          if (tvalIsSelf && !fvalIsSelf) {
            // mux(cond, SELF, fval_with_self): hold when cond, update from fval when !cond
            extractMuxHoldPattern(m.fval, regName, nodeMap, depth + 1, serialOk) match {
              case Some((innerWen, innerWdata)) =>
                val notCond = DoPrim(PrimOps.Not, Seq(m.cond), Seq.empty, m.cond.tpe)
                val wen = DoPrim(PrimOps.And, Seq(notCond, innerWen), Seq.empty, UIntType(IntWidth(1)))
                val wdata = innerWdata
                Some((wen, wdata))
              case None =>
                if (serialOk) {
                  val notCond = DoPrim(PrimOps.Not, Seq(m.cond), Seq.empty, m.cond.tpe)
                  Some((notCond, m.fval))
                } else None
            }
          } else if (fvalIsSelf && !tvalIsSelf) {
            // mux(cond, tval_with_self, SELF): hold when !cond, update from tval when cond
            extractMuxHoldPattern(m.tval, regName, nodeMap, depth + 1, serialOk) match {
              case Some((innerWen, innerWdata)) =>
                val wen = DoPrim(PrimOps.And, Seq(m.cond, innerWen), Seq.empty, UIntType(IntWidth(1)))
                val wdata = innerWdata
                Some((wen, wdata))
              case None =>
                if (serialOk) Some((m.cond, m.tval)) else None
            }
          } else if (serialOk) Some((one, m))
          else None
        } else if (serialOk) Some((one, m))
        else None
      case wr: WRef =>
        nodeMap.get(wr.name).flatMap(extractMuxHoldPattern(_, regName, nodeMap, depth + 1, serialOk))
          .orElse(if (serialOk) Some((one, wr)) else None)
      case other =>
        // Do not recurse through unary operations: dropping not/shift/slice
        // changes wdata, and wrapping only an extracted wdata is also wrong
        // for not(mux(c, x, self)), whose apparent hold branch changes self.
        // Keep the complete expression in serial mode, or decline extraction.
        // Proven identity views of a hold branch are handled by isExactSelfRef.
        if (serialOk) Some((one, other)) else None
    }
  }

  // --------------- SIMD rename ---------------

  def renameRegStmtSIMD(
    s: Statement, annos: Seq[Annotation], vectorWidth: Int,
    isForward: Boolean, moduleName: String,
    regClass: RegClassAnnotation, nodeMap: Map[String, Expression],
    lookup: Map[String, VecStmtInfo]
  ): Statement = {
    val traceMap = getTraceMapping(annos)
    val replaced = s match {
      case c: Connect if (firrtl.Utils.kind(c.loc) == firrtl.RegKind) => {
        val currentName = emitExpr(c.loc)
        val isLBN = isLBNLaneRef(currentName, annos, moduleName, lookup)
        val isPureCounter = isCounterReg(currentName, regClass, moduleName, lookup)
        val isMH = isMuxHoldReg(currentName, regClass, moduleName, lookup) && !isLBN
        if (isPureCounter) {
          EmptyStmt
        } else if (isLBN) {
          val baseName = scalarSourceOf(currentName, lookup)
          val myLaneIdx = laneIndexOf(currentName, lookup)
          val subFieldSuffix = myLaneIdx.map(idx => laneNameSuffix(currentName, idx)).getOrElse("")
          // Field-granular lookup first: Vectorize runs BEFORE LowerTypes, so a
          // bundle-field register lane is named `reg_mstatus_lane_0_mpie` and the
          // RDG trace map is keyed at field granularity ("CSRFile.reg_mstatus_mpie").
          // scalarFieldKey reconstructs exactly that key (same as the isLBN check).
          // The legacy base+suffix concatenation stays as fallback for whole
          // registers whose trace name predates field-granular keys.
          val fieldKey = normalizeOracleKey(scalarFieldKey(currentName, moduleName, lookup))
          val fullTraceField = traceMap.getOrElse(fieldKey, {
            val traceField = traceMap.getOrElse(moduleName + "." + baseName,
              traceMap.getOrElse(baseName, ""))
            if (traceField.nonEmpty) traceField + subFieldSuffix else ""
          })
          if (fullTraceField.isEmpty)
            System.err.println(s"[SplitRegUpdates] WARN: LBN '$currentName' (module $moduleName, key $fieldKey) " +
              "has NO trace mapping; its oracle would be zero-filled")
          val oracleInfo = if (fullTraceField.nonEmpty)
            c.info ++ FileInfo(s"oracle:$fullTraceField")
          else c.info
          val zeroLit: Literal = c.expr.tpe match {
            case UIntType(w) => UIntLiteral(BigInt(0), w)
            case SIntType(w) => SIntLiteral(BigInt(0), w)
            case other => throw new AssertionError(
              s"LBN oracle requires UInt or SInt, got $other on $currentName")
          }
          Block(Seq(
            DefNode(c.info, currentName + "$next", c.expr),
            DefNode(oracleInfo, currentName + "$oracle", zeroLit)
          ))
        } else if (isMH) {
          val serialOk = getMuxHoldStrategy(currentName, annos, moduleName, lookup) == MH_Serial
          // SAFETY NET (see docs/SIMD_CORRECTNESS_AND_PERF_RECOVERY.md): if the
          // strategy-based extraction fails, retry with serialOk=true. Failures here
          // are regs whose enable/hold references the reg itself (e.g. a stall
          // condition reading the pipeline reg it holds) or a nested self-ref that
          // the parallel (PrefixScan) form cannot express. The identity fallback
          // (wen=1, wdata=whole expr) ALWAYS succeeds and is ALWAYS correct; it
          // routes the reg to the serial mux-hold chain (genForReg detects the
          // self-referential $wdata and picks serial) instead of degrading to a
          // fully-serialized Standard shift that drags the whole reader cone into
          // the SCC. Slightly ad-hoc: a catch-all retry rather than teaching the
          // parallel extractor every shape.
          val extracted = extractMuxHoldPattern(c.expr, currentName, nodeMap, 0, serialOk)
            .orElse(extractMuxHoldPattern(c.expr, currentName, nodeMap, 0, serialOk = true))
          extracted match {
            case Some((cond, tval)) =>
              val wenName  = currentName + "$wen"
              val wdataName = currentName + "$wdata"
              val regTpe = c.loc.tpe
              val regW = bitWidth(regTpe)
              val tvalW = bitWidth(tval.tpe)
              val wdataExpr = if (tvalW > regW) {
                DoPrim(PrimOps.Bits, Seq(tval), Seq(regW - 1, 0), regTpe)
              } else if (tvalW < regW) {
                DoPrim(PrimOps.Pad, Seq(tval), Seq(regW), regTpe)
              } else {
                tval
              }
              val mhBase = scalarFieldKey(currentName, moduleName, lookup)
              Block(Seq(
                DefNode(c.info ++ RegUpdateInfo.muxHoldTag(mhBase, "wen"), wenName, cond),
                DefNode(c.info ++ RegUpdateInfo.muxHoldTag(mhBase, "wdata"), wdataName, wdataExpr)
              ))
            case None =>
              // Fail-loud backstop: mux-hold reg inextractable even under the serial
              // identity fallback (should be essentially unreachable). Degrades to a
              // Standard shift that serializes its reader cone; surface it (once, at
              // lane 0) instead of failing silently.
              if (laneIndexOf(currentName, lookup).contains(0))
                System.err.println(
                  s"[SplitRegUpdates] WARN: mux-hold reg '$currentName' (module $moduleName) " +
                  s"had no extractable (wen,wdata) even as serial -> Standard shift; its reader cone will serialize.")
              DefNode(c.info, currentName + "$next", c.expr)
          }
        } else {
          DefNode(c.info, currentName + "$next", c.expr)
        }
      }
      case _ => s
    }

    replaced.map { (stmt: Statement) =>
      renameRegStmtSIMD(stmt, annos, vectorWidth, isForward, moduleName, regClass, nodeMap, lookup)
    }
  }

  def replaceLBNRef(s: Statement, annos: Seq[Annotation], moduleName: String, lookup: Map[String, VecStmtInfo]): Statement = {

    def shouldReplace(name: String, kind: firrtl.Kind): Boolean =
      kind == firrtl.RegKind && isLBNLaneRef(name, annos, moduleName, lookup)

    def onExpr(expr: Expression): Expression = expr match {
      case wr: WRef => {
        if (shouldReplace(wr.name, wr.kind)) {
          WRef(wr.name + "$oracle", wr.tpe, NodeKind, wr.flow)
        } else {
          wr
        }
      }
      case r: Reference => {
        if (shouldReplace(r.name, r.kind)) {
          Reference(r.name + "$oracle", r.tpe, NodeKind, r.flow)
        } else {
          r
        }
      }
      case sf: SubField =>
        SubField(onExpr(sf.expr), sf.name, sf.tpe, sf.flow)

      case si: SubIndex =>
        SubIndex(onExpr(si.expr), si.value, si.tpe, si.flow)

      case sa: SubAccess =>
        SubAccess(onExpr(sa.expr), onExpr(sa.index), sa.tpe, sa.flow)

      case d: DoPrim =>
        DoPrim(d.op, d.args.map(onExpr), d.consts, d.tpe)

      case m: Mux =>
        Mux(onExpr(m.cond), onExpr(m.tval), onExpr(m.fval), m.tpe)

      case v: ValidIf =>
        ValidIf(onExpr(v.cond), onExpr(v.value), v.tpe)

      case other => other
    }

    s match {
      case b: Block =>
        Block(b.stmts.map(sub => replaceLBNRef(sub, annos, moduleName, lookup)))
      case c: Connect =>
        Connect(c.info, c.loc, onExpr(c.expr))
      case d: DefNode =>
        DefNode(d.info, d.name, onExpr(d.value))
      case _ => s
    }
  }

  // FUTURE: what if reg is dead? should update be generated for connect?
  def generateRegUpdates(s: Statement): Seq[Statement] = s match {
    case b: Block => b.stmts flatMap generateRegUpdates
    case r: DefRegister => {
      Seq(RegUpdate(NoInfo, WRef(r.name, r.tpe, RegKind), WRef(r.name + "$next", r.tpe, RegKind)))
    }
    case _ => Seq()
  }


  /** Check whether this register had a successful $wen/$wdata extraction.
    * If so, no $next was generated; we use CondRegUpdate instead. */
  def hasMuxHoldExtraction(name: String, regClass: RegClassAnnotation,
      moduleName: String, nodeMap: Map[String, Expression],
      lookup: Map[String, VecStmtInfo]): Boolean = {
    if (!isMuxHoldReg(name, regClass, moduleName, lookup)) return false
    nodeMap.contains(name + "$wen")
  }

  def generateRegUpdatesSIMD(s: Statement, vectorWidth: Int, isForward: Boolean,
                             annos: Seq[Annotation] = Seq(), moduleName: String = "",
                             regClass: RegClassAnnotation = RegClassAnnotation(Set.empty, Set.empty),
                             nodeMap: Map[String, Expression] = Map.empty,
                             lookup: Map[String, VecStmtInfo] = Map.empty): Seq[Statement] = {

    def genPrefixScan(regName: String, myLaneIdx: Int, tpe: Type, w: Int, forward: Boolean): Seq[Statement] = {
      def laneName(j: Int) = siblingLaneName(regName, myLaneIdx, j)
      val scalarBase = scalarFieldKey(regName, moduleName, lookup)
      val psWeInfo = RegUpdateInfo.muxHoldTag(scalarBase, "ps_we")
      val psDInfo = RegUpdateInfo.muxHoldTag(scalarBase, "ps_d")
      val commitInfo = RegUpdateInfo.muxHoldTag(scalarBase, "commit")
      def wenRef(j: Int) = WRef(laneName(j) + "$wen", UIntType(IntWidth(1)), NodeKind)
      def wdataRef(j: Int) = WRef(laneName(j) + "$wdata", tpe, NodeKind)
      def regRef(j: Int) = WRef(laneName(j), tpe, RegKind)
      val base = laneName(0) // use lane_0's full name to avoid cross-module collisions

      val indices = if (forward) (0 until w).toSeq else (0 until w).reverse
      val initIdx = indices.head

      val stmts = mutable.ArrayBuffer[Statement]()

      // scanExprs(k) = scan over lanes indices(0..k) applied to the carry-in
      // (regRef(initIdx)) = the register's END-of-cycle value at lane indices(k).
      val scanExprs: IndexedSeq[Expression] = if (w == 4) {
        val Seq(i0, i1, i2, i3) = indices
        val we10n = s"${base}$$ps_we_${i1}${i0}"
        val d10n  = s"${base}$$ps_d_${i1}${i0}"
        val we21n = s"${base}$$ps_we_${i2}${i1}"
        val d21n  = s"${base}$$ps_d_${i2}${i1}"
        val we32n = s"${base}$$ps_we_${i3}${i2}"
        val d32n  = s"${base}$$ps_d_${i3}${i2}"
        val we20n = s"${base}$$ps_we_${i2}${i0}"
        val we30n = s"${base}$$ps_we_${i3}${i0}"

        stmts += DefNode(psWeInfo, we10n, DoPrim(PrimOps.Or, Seq(wenRef(i1), wenRef(i0)), Seq.empty, UIntType(IntWidth(1))))
        stmts += DefNode(psDInfo, d10n, Mux(wenRef(i1), wdataRef(i1), wdataRef(i0), tpe))
        stmts += DefNode(psWeInfo, we21n, DoPrim(PrimOps.Or, Seq(wenRef(i2), wenRef(i1)), Seq.empty, UIntType(IntWidth(1))))
        stmts += DefNode(psDInfo, d21n, Mux(wenRef(i2), wdataRef(i2), wdataRef(i1), tpe))
        stmts += DefNode(psWeInfo, we32n, DoPrim(PrimOps.Or, Seq(wenRef(i3), wenRef(i2)), Seq.empty, UIntType(IntWidth(1))))
        stmts += DefNode(psDInfo, d32n, Mux(wenRef(i3), wdataRef(i3), wdataRef(i2), tpe))
        stmts += DefNode(psWeInfo, we20n, DoPrim(PrimOps.Or, Seq(WRef(we21n, UIntType(IntWidth(1)), NodeKind), wenRef(i0)), Seq.empty, UIntType(IntWidth(1))))
        stmts += DefNode(psWeInfo, we30n, DoPrim(PrimOps.Or, Seq(WRef(we32n, UIntType(IntWidth(1)), NodeKind), WRef(we10n, UIntType(IntWidth(1)), NodeKind)), Seq.empty, UIntType(IntWidth(1))))

        IndexedSeq(
          Mux(wenRef(i0), wdataRef(i0), regRef(initIdx), tpe),
          Mux(WRef(we10n, UIntType(IntWidth(1)), NodeKind), WRef(d10n, tpe, NodeKind), regRef(initIdx), tpe),
          Mux(WRef(we20n, UIntType(IntWidth(1)), NodeKind),
            Mux(WRef(we21n, UIntType(IntWidth(1)), NodeKind), WRef(d21n, tpe, NodeKind), wdataRef(i0), tpe),
            regRef(initIdx), tpe),
          Mux(WRef(we30n, UIntType(IntWidth(1)), NodeKind),
            Mux(WRef(we32n, UIntType(IntWidth(1)), NodeKind), WRef(d32n, tpe, NodeKind), WRef(d10n, tpe, NodeKind), tpe),
            regRef(initIdx), tpe)
        )
      } else {
        indices.indices.map { k =>
          val lane = indices(k)
          if (k == 0) {
            Mux(wenRef(lane), wdataRef(lane), regRef(initIdx), tpe)
          } else {
            var accWen: Expression = wenRef(lane)
            var accData: Expression = wdataRef(lane)
            for (prev <- (0 until k).reverse) {
              val pLane = indices(prev)
              val prevAccWen = accWen
              accWen = DoPrim(PrimOps.Or, Seq(prevAccWen, wenRef(pLane)), Seq.empty, UIntType(IntWidth(1)))
              accData = Mux(prevAccWen, accData, wdataRef(pLane), tpe)
            }
            Mux(accWen, accData, regRef(initIdx), tpe)
          }
        }.toIndexedSeq
      }

      // Source phase: readers of lane indices(k) must see the START-of-cycle
      // value = scan over lanes indices(0..k-1), i.e. scanExprs(k-1); the init
      // lane keeps the carry-in untouched. Tagged "inter_lane" so
      // BuildScheduleAtoms wraps each in a ShiftAtom producing the BARE lane
      // name (source-before-readers via data deps, commit-after-readers via
      // anti-dep edges) — symmetric with a standard register's
      // shift/final_commit two-phase structure. Without this phase readers
      // observe the END-of-cycle value (one cycle early).
      for (k <- indices.indices if k > 0) {
        stmts += RegUpdate(RegUpdateInfo.simple("inter_lane"),
          regRef(indices(k)), scanExprs(k - 1))
      }
      // Commit phase: end-of-cycle values; the boundary lane carries the
      // window's carry-out into the next (zig-zag reversed) window.
      for (k <- indices.indices) {
        stmts += RegUpdate(commitInfo, regRef(indices(k)), scanExprs(k))
      }
      stmts.toSeq
    }

    def substituteInExpr(expr: Expression, oldName: String, newExpr: Expression): Expression = expr match {
      case wr: WRef if wr.name == oldName => newExpr
      case wr: WRef => wr
      case m: Mux => Mux(substituteInExpr(m.cond, oldName, newExpr),
        substituteInExpr(m.tval, oldName, newExpr),
        substituteInExpr(m.fval, oldName, newExpr), m.tpe)
      case dp: DoPrim => DoPrim(dp.op, dp.args.map(substituteInExpr(_, oldName, newExpr)), dp.consts, dp.tpe)
      case vi: ValidIf => ValidIf(substituteInExpr(vi.cond, oldName, newExpr),
        substituteInExpr(vi.value, oldName, newExpr), vi.tpe)
      case other => other
    }

    def inlineAndSubstitute(expr: Expression, regName: String, replacement: Expression,
                            nMap: Map[String, Expression], depth: Int = 0): Expression = {
      if (depth > 30) return expr
      expr match {
        case wr: WRef if wr.name == regName => replacement
        case wr: WRef =>
          nMap.get(wr.name) match {
            case Some(nodeExpr) if containsRegRef(nodeExpr, regName, nMap, 0) =>
              inlineAndSubstitute(nodeExpr, regName, replacement, nMap, depth + 1)
            case _ => wr
          }
        case m: Mux => Mux(
          inlineAndSubstitute(m.cond, regName, replacement, nMap, depth + 1),
          inlineAndSubstitute(m.tval, regName, replacement, nMap, depth + 1),
          inlineAndSubstitute(m.fval, regName, replacement, nMap, depth + 1), m.tpe)
        case dp: DoPrim => DoPrim(dp.op,
          dp.args.map(inlineAndSubstitute(_, regName, replacement, nMap, depth + 1)),
          dp.consts, dp.tpe)
        case vi: ValidIf => ValidIf(
          inlineAndSubstitute(vi.cond, regName, replacement, nMap, depth + 1),
          inlineAndSubstitute(vi.value, regName, replacement, nMap, depth + 1), vi.tpe)
        case other => other
      }
    }

    def genSerialMuxHold(regName: String, myLaneIdx: Int, tpe: Type, w: Int, forward: Boolean,
                         wdataSelfDep: Boolean): Seq[Statement] = {
      val scalarSrc = scalarSourceOf(regName, lookup)
      val suffix = laneNameSuffix(regName, myLaneIdx)
      val base = if (suffix.nonEmpty) scalarSrc + suffix else scalarSrc
      def laneName(j: Int) = siblingLaneName(regName, myLaneIdx, j)
      val serialBase = base
      val scalarBase = scalarFieldKey(regName, moduleName, lookup)
      val serialInfo = RegUpdateInfo.muxHoldTag(scalarBase, "serial")
      val serialCommitInfo = RegUpdateInfo.muxHoldTag(scalarBase, "commit")
      def wenRef(j: Int) = WRef(laneName(j) + "$wen", UIntType(IntWidth(1)), NodeKind)
      def wdataRef(j: Int) = WRef(laneName(j) + "$wdata", tpe, NodeKind)
      def regRef(j: Int) = WRef(laneName(j), tpe, RegKind)
      def serialRef(j: Int) = WRef(s"${serialBase}$$serial_${j}", tpe, NodeKind)

      val indices = if (forward) (0 until w).toSeq else (0 until w).reverse
      val stmts = mutable.ArrayBuffer[Statement]()

      for ((lane, k) <- indices.zipWithIndex) {
        val holdRef = if (k == 0) regRef(lane) else serialRef(indices(k - 1))
        val wdata = if (!wdataSelfDep || k == 0) {
          wdataRef(lane)
        } else {
          val prevSerial = serialRef(indices(k - 1))
          val origExpr = nodeMap.getOrElse(laneName(lane) + "$wdata", wdataRef(lane))
          val substituted = inlineAndSubstitute(origExpr, laneName(lane), prevSerial, nodeMap)
          substituted
        }
        stmts += DefNode(serialInfo, s"${serialBase}$$serial_${lane}",
          Mux(wenRef(lane), wdata, holdRef, tpe))
      }
      // Source phase: readers of lane k must see the register's START-of-cycle
      // value = carry-in advanced through lanes 0..k-1, which is exactly
      // serial_{k-1} (the init lane keeps the carry-in untouched). Tagged
      // "inter_lane" so BuildScheduleAtoms wraps each in a ShiftAtom producing
      // the BARE lane name: readers data-depend on it (source-before-readers)
      // and the commit below is anti-dep ordered after them — symmetric with a
      // standard register's shift/final_commit two-phase structure. Without
      // this phase readers observe the END-of-cycle value (one cycle early).
      for ((lane, k) <- indices.zipWithIndex if k > 0) {
        stmts += RegUpdate(RegUpdateInfo.simple("inter_lane"),
          regRef(lane), serialRef(indices(k - 1)))
      }
      // Commit phase: end-of-cycle values; the boundary lane carries the
      // window's carry-out into the next (zig-zag reversed) window.
      for ((lane, k) <- indices.zipWithIndex) {
        stmts += RegUpdate(serialCommitInfo, regRef(lane), serialRef(lane))
      }
      stmts.toSeq
    }

    def genForReg(r: DefRegister): Seq[Statement] = {
      val isPureCounter = isCounterReg(r.name, regClass, moduleName, lookup)
      if (isPureCounter) return Seq()

      laneIndexOf(r.name, lookup) match {
        case Some(i) =>
          val isLBN = isLBNLaneRef(r.name, annos, moduleName, lookup)
          val isMHExtracted = !isLBN && hasMuxHoldExtraction(r.name, regClass, moduleName, nodeMap, lookup)
          val mhStrategy = if (isMHExtracted) getMuxHoldStrategy(r.name, annos, moduleName, lookup) else MH_Fallback

          val mhScalarBase = scalarFieldKey(r.name, moduleName, lookup)

          val finalCommit = RegUpdate(RegUpdateInfo.simple("final_commit"),
            WRef(r.name, r.tpe, RegKind), WRef(r.name + "$next", r.tpe, RegKind))

          val mhCommit = CondRegUpdate(
            if (isMHExtracted) RegUpdateInfo.muxHoldTag(mhScalarBase, "commit")
            else RegUpdateInfo.simple("final_commit"),
            WRef(r.name + "$wen", UIntType(IntWidth(1)), NodeKind),
            WRef(r.name, r.tpe, RegKind),
            WRef(r.name + "$wdata", r.tpe, NodeKind))

          // The extracted $wdata is the source of truth: if it references the reg
          // itself, the parallel prefix-scan form is invalid (it assumes a self-free
          // wdata) and we MUST use the serial chain, regardless of the RDG-assigned
          // strategy. This is what makes the renamePhase serial-retry safety net
          // land: salvaged regs carry a PrefixScan annotation but a self-referential
          // identity-fallback $wdata, so they route here to serial.
          val wdataSelf = isMHExtracted &&
            nodeMap.get(r.name + "$wdata").exists(containsRegRef(_, r.name, nodeMap, 0))
          val isPrefixScan = isMHExtracted && mhStrategy == MH_PrefixScan && !wdataSelf
          val isSerial = isMHExtracted && (mhStrategy == MH_Serial || wdataSelf)

          if (isForward) {
            if (isPrefixScan) {
              if (i == 0) genPrefixScan(r.name, i, r.tpe, vectorWidth, forward = true)
              else Seq()
            } else if (isSerial) {
              if (i == 0) genSerialMuxHold(r.name, i, r.tpe, vectorWidth, forward = true, mhStrategy == MH_Serial || wdataSelf)
              else Seq()
            } else if (i == 0) {
              if (isLBN && vectorWidth > 1) {
                val oracleName = siblingLaneName(r.name, i, 1) + "$oracle"
                Seq(finalCommit, LBNVerify(NoInfo, WRef(r.name, r.tpe, RegKind), WRef(oracleName, r.tpe, NodeKind)))
              } else if (isMHExtracted) {
                Seq(mhCommit)
              } else {
                Seq(finalCommit)
              }
            } else if (i < vectorWidth) {
              if (isLBN) {
                Seq(finalCommit)
              } else if (isMHExtracted) {
                val prevName = siblingLaneName(r.name, i, i - 1)
                Seq(
                  RegUpdate(RegUpdateInfo.muxHoldTag(mhScalarBase, "carry"),
                    WRef(r.name, r.tpe, RegKind),
                    WRef(prevName, r.tpe, RegKind)),
                  mhCommit
                )
              } else {
                val prevNextName = siblingLaneName(r.name, i, i - 1) + "$next"
                Seq(
                  RegUpdate(RegUpdateInfo.simple("inter_lane"),
                    WRef(r.name, r.tpe, RegKind),
                    WRef(prevNextName, r.tpe, RegKind)),
                  finalCommit
                )
              }
            } else {
              if (isMHExtracted) Seq(mhCommit)
              else Seq(RegUpdate(NoInfo, WRef(r.name, r.tpe, RegKind), WRef(r.name + "$next", r.tpe, RegKind)))
            }
          } else {
            if (isPrefixScan) {
              if (i == vectorWidth - 1) genPrefixScan(r.name, i, r.tpe, vectorWidth, forward = false)
              else Seq()
            } else if (isSerial) {
              if (i == vectorWidth - 1) genSerialMuxHold(r.name, i, r.tpe, vectorWidth, forward = false, mhStrategy == MH_Serial || wdataSelf)
              else Seq()
            } else if (i == vectorWidth - 1) {
              if (isLBN && vectorWidth > 1) {
                val oracleName = siblingLaneName(r.name, i, vectorWidth - 2) + "$oracle"
                Seq(finalCommit, LBNVerify(NoInfo, WRef(r.name, r.tpe, RegKind), WRef(oracleName, r.tpe, NodeKind)))
              } else if (isMHExtracted) {
                Seq(mhCommit)
              } else {
                Seq(finalCommit)
              }
            } else if (i < vectorWidth - 1) {
              if (isLBN) {
                Seq(finalCommit)
              } else if (isMHExtracted) {
                val nextName = siblingLaneName(r.name, i, i + 1)
                Seq(
                  RegUpdate(RegUpdateInfo.muxHoldTag(mhScalarBase, "carry"),
                    WRef(r.name, r.tpe, RegKind),
                    WRef(nextName, r.tpe, RegKind)),
                  mhCommit
                )
              } else {
                val nextNextName = siblingLaneName(r.name, i, i + 1) + "$next"
                Seq(
                  RegUpdate(RegUpdateInfo.simple("inter_lane"),
                    WRef(r.name, r.tpe, RegKind),
                    WRef(nextNextName, r.tpe, RegKind)),
                  finalCommit
                )
              }
            } else {
              if (isMHExtracted) Seq(mhCommit)
              else Seq(RegUpdate(NoInfo, WRef(r.name, r.tpe, RegKind), WRef(r.name + "$next", r.tpe, RegKind)))
            }
          }

        case None =>
          Seq(RegUpdate(NoInfo, WRef(r.name, r.tpe, RegKind), WRef(r.name + "$next", r.tpe, RegKind)))
      }
    }

    s match {
      case b: Block =>
        b.stmts flatMap (stmt => generateRegUpdatesSIMD(stmt, vectorWidth, isForward, annos, moduleName, regClass, nodeMap, lookup))
      case r: DefRegister => genForReg(r)
      case _ => Seq()
    }
  }

  override def run(c: Circuit): Circuit = ???

  /** Phase 1: Direction-agnostic combinational logic rename ($next/$oracle/$wen/$wdata)
    * and LBN reference replacement. Run ONCE on the shared circuit. */
  /**
   * @return (renamed CircuitState, per-module nodeMap built AFTER renaming)
   *   The nodeMap captures $wen/$wdata DefNodes before DCE can remove them.
   */
  def renamePhase(state: CircuitState): (CircuitState, Map[String, Map[String, Expression]]) = {
    val vecWidth = state.annotations.collectFirst {
      case EssentOptionsAnnotation(opt) => opt
    }.get.vectorWidth
    val annos: Seq[Annotation] = state.annotations
    val regClass = getRegClass(annos)
    val c = state.circuit
    var totalOracleNodes = 0
    val postRenameNodeMaps = mutable.Map[String, Map[String, Expression]]()
    val modulesx = c.modules.map {
      case m: ExtModule => m
      case m: Module =>
        val nodeMap = buildDefNodeMap(m.body)
        val lookup = buildModuleLookup(m.body, m.name)
        val renamed = renameRegStmtSIMD(m.body, annos, vecWidth, true, m.name, regClass, nodeMap, lookup)
        val withLBN = replaceLBNRef(renamed, annos, m.name, lookup)
        postRenameNodeMaps(m.name) = buildDefNodeMap(withLBN)
        val oracleNodes = essent.Extract.flattenStmts(withLBN).collect {
          case d: DefNode if d.name.endsWith("$oracle") => d
        }
        val oracleCount = oracleNodes.size
        if (oracleCount > 0) {
          val noTrace = oracleNodes.filterNot(d => d.info.serialize.contains("oracle:"))
          println(s"[SplitRegUpdates.renamePhase] Module ${m.name}: $oracleCount oracle DefNodes, " +
            s"${noTrace.size} WITHOUT trace annotation (silent zero-fill!)")
          noTrace.map(_.name).take(40).foreach(n => println(s"[SplitRegUpdates.renamePhase]   NO-TRACE: $n"))
        }
        totalOracleNodes += oracleCount
        m.copy(body = withLBN)
    }
    println(s"[SplitRegUpdates.renamePhase] TOTAL oracle DefNodes: $totalOracleNodes")
    val newState = state.copy(circuit = Circuit(c.info, modulesx, c.main))
    (newState, postRenameNodeMaps.toMap)
  }

  /** Phase 2: Direction-dependent register update generation (RegUpdate/CondRegUpdate/
    * LBNVerify/prefix-scan/serial). Run ONCE per direction (forward/reverse).
    *
    * @param preDCENodeMaps  Optional per-module nodeMap from BEFORE postSplitTransforms.
    *   generateUpdatesPhase checks for $wen/$wdata DefNodes (created by renamePhase)
    *   to decide if a register had successful mux-hold extraction. If postSplitTransforms
    *   (specifically DCE) runs between renamePhase and this phase, those DefNodes may be
    *   removed because nothing references them yet. Pass the pre-DCE nodeMap so the
    *   hasMuxHoldExtraction check finds them.
    */
  def generateUpdatesPhase(state: CircuitState, isForward: Boolean,
      preDCENodeMaps: Map[String, Map[String, Expression]] = Map.empty): CircuitState = {
    val vecWidth = state.annotations.collectFirst {
      case EssentOptionsAnnotation(opt) => opt
    }.get.vectorWidth
    val annos: Seq[Annotation] = state.annotations
    val regClass = getRegClass(annos)
    val c = state.circuit
    val modulesx = c.modules.map {
      case m: ExtModule => m
      case m: Module =>
        val nodeMap = preDCENodeMaps.getOrElse(m.name, buildDefNodeMap(m.body))
        val lookup = buildModuleLookup(m.body, m.name)
        val regUpdates = generateRegUpdatesSIMD(m.body, vecWidth, isForward, annos, m.name, regClass, nodeMap, lookup)
        val newBody = squashEmpty(Block(Seq(m.body) ++ regUpdates))

        // Verify that all WRef targets in generated updates reference defined names.
        // This guards against postSplitTransforms renaming signals that the update
        // generation depends on (e.g. $next, $wen, $wdata).
        val definedNames = collectDefinedNames(newBody, m.ports)
        val updateRefs = regUpdates.flatMap(collectWRefNames)
        val missing = updateRefs.filterNot(n =>
          definedNames.contains(n) || n.endsWith("$oracle"))
        if (missing.nonEmpty) {
          val dir = if (isForward) "forward" else "reverse"
          System.err.println(
            s"[SplitRegUpdates] WARNING ($dir): ${missing.size} unresolved refs in ${m.name}: " +
              missing.take(10).mkString(", ") + (if (missing.size > 10) " ..." else ""))
        }

        {
          val flatUpd = regUpdates.flatMap(essent.Extract.flattenStmts)
          def infoOf(s: Statement): String = s match {
            case ru: RegUpdate => ru.info.serialize
            case cru: CondRegUpdate => cru.info.serialize
            case _ => ""
          }
          val nShift = flatUpd.count(s => infoOf(s).contains("inter_lane"))
          val nCommit = flatUpd.count(s => infoOf(s).contains("final_commit"))
          val nPlain = flatUpd.count(s => s.isInstanceOf[RegUpdate] && infoOf(s).trim.isEmpty)
          if (flatUpd.nonEmpty)
            println(s"[SplitRegUpdates] ${m.name} (${if (isForward) "fwd" else "rev"}): " +
              s"${flatUpd.size} update stmts = $nShift inter_lane + $nCommit final_commit + $nPlain plain(no-lane-meta) + ${flatUpd.size - nShift - nCommit - nPlain} other")
        }

        m.copy(body = newBody)
    }
    state.copy(
      circuit = Circuit(c.info, modulesx, c.main),
      annotations = state.annotations :+ RegUpdateDirectionAnnotation(isForward)
    )
  }

  private def collectDefinedNames(s: Statement, ports: Seq[Port] = Seq.empty): Set[String] = {
    val names = mutable.HashSet[String]()
    for (p <- ports) names += p.name
    def walk(stmt: Statement): Unit = stmt match {
      case b: Block => b.stmts.foreach(walk)
      case d: DefNode => names += d.name
      case r: DefRegister => names += r.name
      case w: DefWire => names += w.name
      case m: DefMemory => names += m.name
      case _ =>
    }
    walk(s)
    names.toSet
  }

  private def collectWRefNames(s: Statement): Seq[String] = {
    val refs = mutable.ArrayBuffer[String]()
    def walkExpr(e: Expression): Unit = e match {
      case wr: WRef => refs += wr.name
      case m: Mux => walkExpr(m.cond); walkExpr(m.tval); walkExpr(m.fval)
      case dp: DoPrim => dp.args.foreach(walkExpr)
      case _ =>
    }
    def walkStmt(stmt: Statement): Unit = stmt match {
      case b: Block => b.stmts.foreach(walkStmt)
      case ru: RegUpdate => walkExpr(ru.regRef); walkExpr(ru.expr)
      case cru: CondRegUpdate => walkExpr(cru.cond); walkExpr(cru.regRef); walkExpr(cru.expr)
      case lv: LBNVerify => walkExpr(lv.regRef); walkExpr(lv.oracleRef)
      case d: DefNode => walkExpr(d.value)
      case _ =>
    }
    walkStmt(s)
    refs.toSeq
  }

  override def execute(state: CircuitState): CircuitState = {
    val isSIMD = false // v1 SIMD path retired; the transform always runs its scalar form
    val c = state.circuit
    if (!isSIMD) {
      val modulesx = c.modules.map {
        case m: ExtModule => m
        case m: Module =>
          val newBody = squashEmpty(Block(Seq(renameRegStmt(m.body)) ++ generateRegUpdates(m.body)))
          m.copy(body = newBody)
      }
      state.copy(circuit = Circuit(c.info, modulesx, c.main))
    } else {
      val isForward = state.annotations.collectFirst {
        case RegUpdateDirectionAnnotation(dir) => dir
      }.getOrElse(true)
      val (renamed, nodeMaps) = renamePhase(state)
      generateUpdatesPhase(renamed, isForward, nodeMaps)
    }
  }
}
