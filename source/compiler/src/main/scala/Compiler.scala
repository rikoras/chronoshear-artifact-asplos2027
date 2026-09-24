package essent

import java.io.{File, FileWriter, Writer}

import essent.Emitter._
import essent.Extract._
import essent.ir._
import essent.Util._
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency
import firrtl.stage.TransformManager.TransformDependency
import firrtl.stage.transforms

import firrtl.annotations._
import collection.mutable.{HashSet, ArrayBuffer}
import logger._
import essent.passes.{SplitRegUpdates, RegUpdateDirectionAnnotation}
import essent.simd._

@SerialVersionUID(2L)
case class CheckpointAnno(
  categories: Map[String, RegCategory],
  condUpdateKeys: Set[String],
  oracleTargets: Set[String],
  fvsOrder: Seq[String],
  moduleOracleTargets: Map[String, String],
  muxHoldStrategies: Map[String, MuxHoldStrategy],
  combOracleTargets: Map[String, String],
  combOracleFlatNames: Map[String, String]
) extends Serializable



class EssentEmitter(initialOpt: OptFlags, private val _headerWriter: Writer, state: CircuitState,
                    reverseState: Option[CircuitState] = None) extends LazyLogging {
  private var w: Writer = _headerWriter
  val circuit: Circuit = state.circuit
  val annos: Seq[Annotation] = state.annotations
  val reverseAnnos: Seq[Annotation] = reverseState.map(_.annotations.toSeq).getOrElse(annos)
  val flagVarName = "PARTflags"
  implicit val rn: Renamer = new Renamer
  rn.vectorWidth = initialOpt.vectorWidth
  implicit var emitCtx: EmitContext = EmitContext(vectorWidth = initialOpt.vectorWidth)
  val actTrac = new ActivityTracker(w, initialOpt)
  val vcd: Option[Vcd] = if (initialOpt.withVCD) Some(new Vcd(circuit,initialOpt,w,rn)) else None

  private def activeAnnos: Seq[Annotation] =
    if (emitCtx.forward.contains(false)) reverseAnnos else annos

  private val probeSignals: Map[String, String] = {
    val path = initialOpt.probeSignalsFile
    if (path.nonEmpty && new File(path).exists()) {
      val src = scala.io.Source.fromFile(path)
      val json = try src.mkString finally src.close()
      import org.json4s._
      import org.json4s.native.JsonMethods._
      val entries = try {
        parse(json) match {
          case JArray(items) => items.flatMap {
            case JObject(fields) =>
              val m = fields.toMap
              for {
                JString(sig) <- m.get("signal")
                JString(trace) <- m.get("trace")
              } yield sig -> trace
            case _ => None
          }.toMap
          case _ => Map.empty[String, String]
        }
      } catch { case e: Exception =>
        System.err.println(s"[Compiler] WARN: Failed to parse probe signals JSON at $path: ${e.getMessage}")
        Map.empty[String, String]
      }
      if (entries.nonEmpty)
        println(s"[Compiler] Loaded ${entries.size} probe signals from $path")
      entries
    } else Map.empty
  }

  private val hasOracleMapping: Boolean =
    (annos ++ reverseAnnos).exists {
      case plan: SIMDPlanAnnotation => plan.moduleOracleTargets.nonEmpty
      case _ => false
    }
  // Declaring Modules
  //----------------------------------------------------------------------------
  def declareModule(m: Module, topName: String): Unit = {
    val registers = findInstancesOf[DefRegister](m.body)
    val memories = findInstancesOf[DefMemory](m.body)


    def stickyReorder[T](items: Seq[T], getName: T => String, vectorWidth: Int): Seq[T] = {
      if (vectorWidth <= 1) return items

                                   
      val nameToItem = items.map(i => getName(i) -> i).toMap

                    
      val emittedNames = HashSet[String]()
      val result = ArrayBuffer[T]()

                                         
                                                      
      // Build lane family groups from annotation
      val familyGroups = collection.mutable.Map[String, collection.mutable.Map[Int, String]]()
      for (item0 <- items) {
        val n0 = getName(item0)
        rn.flatVecMeta.get(n0).foreach { info =>
          if (info.laneIndex < vectorWidth) {
            val suffix = essent.passes.SplitRegUpdates.laneNameSuffix(n0, info.laneIndex)
            val familyKey = info.scalarSource + suffix
            familyGroups.getOrElseUpdate(familyKey, collection.mutable.Map.empty)(info.laneIndex) = n0
          }
        }
      }

      items.foreach { item =>
        val name = getName(item)

        if (!emittedNames.contains(name)) {
          result += item
          emittedNames += name

          rn.flatVecMeta.get(name).foreach { info =>
            if (info.laneIndex == 0) {
              val suffix = essent.passes.SplitRegUpdates.laneNameSuffix(name, 0)
              val familyKey = info.scalarSource + suffix
              familyGroups.get(familyKey).foreach { lanes =>
                for (lane <- 1 until vectorWidth) {
                  lanes.get(lane).foreach { sibName =>
                    if (!emittedNames.contains(sibName)) {
                      nameToItem.get(sibName).foreach { sibItem =>
                        result += sibItem
                        emittedNames += sibName
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

                        
                                                  
      items.foreach { item =>
        val name = getName(item)
        if (!emittedNames.contains(name)) {
          result += item
          emittedNames += name
        }
      }

      result.toSeq
    }

    val modulesAndPrefixes = findModuleInstances(m.body)
    val moduleDecs = modulesAndPrefixes map { case (module, fullName) => {
      val instanceName = fullName.split("\\.").last
      s"$module $instanceName;"
    }}
    val modName = m.name
    w.writeLines(0, "")
    w.writeLines(0, s"typedef struct $modName {")
    val vectorWidth = initialOpt.vectorWidth


    if(registers.nonEmpty){
      if (vectorWidth > 1) {
        val simdGroups = collection.mutable.LinkedHashMap[String, (String, Type, Int)]()
        val scalarRegs = ArrayBuffer[DefRegister]()

        for (r <- registers) {
          simd.LaneTag.extract(r.info) match {
            case Some((scalarSrc, laneIdx)) if laneIdx < vectorWidth =>
              val suffix = essent.passes.SplitRegUpdates.laneNameSuffix(r.name, laneIdx)
              val key = scalarSrc + suffix
              simdGroups.getOrElseUpdate(key, (genCppType(r.tpe), r.tpe, 0))
              simdGroups(key) = (genCppType(r.tpe), r.tpe, simdGroups(key)._3 + 1)
            case _ =>
              scalarRegs += r
          }
        }

        val sortedKeys = simdGroups.keys.toSeq.sortBy { key =>
          val (_, tpe, _) = simdGroups(key)
          (bitWidth(tpe).toInt, key)
        }

        val decs = ArrayBuffer[String]()
        for (key <- sortedKeys) {
          val (typeStr, tpe, count) = simdGroups(key)
          if (count == vectorWidth)
            decs += s"${chooseAlignment(tpe, vectorWidth)}$typeStr $key[$vectorWidth];"
        }
        for (key <- sortedKeys) {
          val (typeStr, _, count) = simdGroups(key)
          if (count != vectorWidth) {
            for (r <- registers) {
              simd.LaneTag.extract(r.info) match {
                case Some((scalarSrc, laneIdx)) =>
                  val sfx = essent.passes.SplitRegUpdates.laneNameSuffix(r.name, laneIdx)
                  if (scalarSrc + sfx == key) decs += s"${genCppType(r.tpe)} ${r.name};"
                case _ =>
              }
            }
          }
        }
        for (r <- scalarRegs) {
          decs += s"${genCppType(r.tpe)} ${r.name};"
        }
        w.writeLines(1, decs.toSeq)
      } else {
        val registerDecs = registers map { d: DefRegister =>
          s"${genCppType(d.tpe)} ${d.name};"
        }
        w.writeLines(1, registerDecs)
      }
    }
    if(memories.nonEmpty){
      val memDecs = memories map {m: DefMemory => {
        s"${genCppType(m.dataType)} ${m.name}[${m.depth}];"
      }}
      w.writeLines(1, memDecs)
    }

    var simdPortArrays: Map[String, String] = Map.empty

    w.writeLines(1, m.ports flatMap emitPort(modName == topName))


    w.writeLines(1, moduleDecs)
    w.writeLines(0, "")
    w.writeLines(1, s"$modName() {")
    val initWidth = vectorWidth
    w.writeLines(2, initializeVals(modName == topName, initWidth, simdPortArrays)(m, registers, memories))
    w.writeLines(1, "}")
    if (modName == topName) {
      w.writeLines(0, "")
      // w.writeLines(1, s"void connect_harness(CommWrapper<struct $modName> *comm);")
    } else {
      w.writeLines(0, s"} $modName;")
    }
  }

  def declareExtModule(m: ExtModule): Unit = {
    val modName = m.name
    w.writeLines(0, "")
    w.writeLines(0, s"typedef struct $modName {")
    w.writeLines(1, m.ports flatMap emitPort(true))
    w.writeLines(0, s"} $modName;")
  }


  // Write General-purpose Eval
  //----------------------------------------------------------------------------

  def writeBodyInner(indentLevel: Int, sg: StatementGraph, opt: OptFlags,
                     keepAvail: Set[String] = Set()): Unit = {
    writeBodyLegacy(indentLevel, sg, opt, keepAvail)
  }

  private def writeBodyLegacy(indentLevel: Int, sg: StatementGraph, opt: OptFlags,
                              keepAvail: Set[String]): Unit = {
    val ordered = sg.stmtsOrdered()
    ordered foreach { stmt => stmt match {
      case cm: CondMux =>
        if (rn.nameToMeta(cm.name).decType == MuxOut)
          w.writeLines(indentLevel, s"${genCppType(cm.mux.tpe)} ${rn.emit(cm.name)};")
        val muxCondRaw = emitExpr(cm.mux.cond)
        val muxCond = if (muxCondRaw == "reset") s"UNLIKELY($muxCondRaw)" else muxCondRaw
        w.writeLines(indentLevel, s"if (UNLIKELY($muxCond)) {")
        writeBodyInner(indentLevel + 1, StatementGraph(cm.tWay, false), opt)
        w.writeLines(indentLevel, "} else {")
        writeBodyInner(indentLevel + 1, StatementGraph(cm.fWay, false), opt)
        w.writeLines(indentLevel, "}")
      case _ =>
        w.writeLines(indentLevel, emitStmt(stmt))
        if (opt.withVCD)  vcd.get.compSmallEval(stmt, indentLevel)
        if (opt.trackSigs) actTrac.emitSigTracker(stmt, indentLevel)
    }}
  }

  def checkRegResetSafety(sg: StatementGraph): Unit = {
    val updatesWithResets = sg.allRegDefs() filter { r => emitExpr(r.reset) != "UInt<1>(0x0)" }
    assert(updatesWithResets.isEmpty)
  }


  // Write Zoning Optimized Eval
  //----------------------------------------------------------------------------
  def genEvalFuncName(partID: Int): String = "EVAL_" + partID
  def genCommitFuncName(partID: Int): String = "COMMIT_" + partID
  def genFastNextName(partID: Int, updateIndex: Int): String =
    s"_essent_fast_next_${partID}_$updateIndex"
  def genFastDirtyName(partID: Int): String =
    s"_essent_fast_dirty_$partID"

  /** Stateful effects that must observe a false-to-true update transition.
    * Keep this traversal broader than Block: CondMux and future structured
    * statements may carry nested effects that cannot use the pure-register
    * fast path without also preserving their control structure. */
  private def registerEdgeEffects(stmt: Statement): Seq[Statement] = stmt match {
    case _: RegUpdate | _: CondRegUpdate | _: MemWrite | _: Print |
         _: LBNVerify => Seq(stmt)
    case _ =>
      val effects = ArrayBuffer[Statement]()
      stmt.foreachStmt(child => effects ++= registerEdgeEffects(child))
      effects.toSeq
  }

  private def partRegisterEdgeEffects(cp: CondPart): Seq[Statement] =
    cp.memberStmts.flatMap(registerEdgeEffects)

  /** Return the unconditional register updates whose cached `$next` values
    * can be committed without re-running the partition body.  The count check
    * rejects a RegUpdate nested under CondMux (partitionByType intentionally
    * descends only through unconditional Blocks). */
  private def fastEdgeRegUpdates(cp: CondPart, opt: OptFlags): Seq[RegUpdate] = {
    if (!opt.scalarFastEdgeCommit) return Seq.empty
    val effects = partRegisterEdgeEffects(cp)
    val (unconditional, _) = partitionByType[RegUpdate](cp.memberStmts)
    if (effects.nonEmpty && effects.forall(_.isInstanceOf[RegUpdate]) &&
        effects.size == unconditional.size) unconditional
    else Seq.empty
  }

  private def genDepPartTriggers(consumerIDs: Seq[Int],
      condition: String): Seq[String] =
    consumerIDs.sorted.map { consumerID =>
      s"$flagVarName[$consumerID] |= $condition;"
    }

  private def genAllTriggers(signalNames: Seq[String], outputConsumers: Map[String, Seq[Int]],
      suffix: String): Seq[String] = {
    selectFromMap(signalNames, outputConsumers).toSeq flatMap { case (name, consumerIDs) => {
      genDepPartTriggers(consumerIDs,
        s"${rn.emit(name)} != ${rn.emit(name + suffix)}")
    }}
  }

  def writeZoningPredecs(
                          sg: StatementGraph,
                          condPartWorker: MakeCondPart,
                          topName: String,
                          extIOtypes: Map[String, Type],
                          opt: OptFlags): Unit = {
    // predeclare part outputs
    val outputPairs = condPartWorker.getPartOutputsToDeclare()
    val outputConsumers = condPartWorker.getPartInputMap()
    w.writeLines(1, outputPairs map {case (name, tpe) => s"${genCppType(tpe)} ${rn.emit(name)};"})
    val extIOCacheDecs = condPartWorker.getExternalPartInputTypes(extIOtypes) map {
      case (name, tpe) => s"${genCppType(tpe)} ${rn.emit(name + condPartWorker.cacheSuffix)};"
    }
    w.writeLines(1, extIOCacheDecs)
    w.writeLines(1, s"std::array<bool,${condPartWorker.getNumParts()}> $flagVarName;")
    if (opt.scalarPartProfile) {
      w.writeLines(1,
        s"std::array<uint64_t,${condPartWorker.getNumParts()}> _essent_part_eval_counts{};")
      w.writeLines(1,
        s"std::array<uint64_t,${condPartWorker.getNumParts()}> _essent_part_commit_counts{};")
      w.writeLines(1,
        s"std::array<uint64_t,${condPartWorker.getNumParts()}> _essent_part_dirty_commit_counts{};")
    }
    if (opt.scalarFastEdgeCommit) {
      sg.stmtsOrdered().foreach {
        case cp: CondPart =>
          val fastUpdates = fastEdgeRegUpdates(cp, opt)
          fastUpdates.zipWithIndex.foreach {
            case (update, index) =>
              w.writeLines(1,
                s"${genCppType(update.regRef.tpe)} ${genFastNextName(cp.id, index)};")
          }
          if (fastUpdates.nonEmpty)
            // Conservative until the first non-committing preview.  The
            // normal producer protocol always refreshes this bit before its
            // first prepared edge, while `true` also preserves the historical
            // writeback behavior for an unusual caller.
            w.writeLines(1, s"bool ${genFastDirtyName(cp.id)} = true;")
        case _ =>
      }
    }
    // FUTURE: worry about namespace collisions with user variables
    w.writeLines(1, s"bool sim_cached = false;")
    w.writeLines(1, s"bool regs_set = false;")
    w.writeLines(1, s"bool prev_update_registers = true;")
    w.writeLines(1, s"bool update_registers;")
    w.writeLines(1, s"bool done_reset;")
    w.writeLines(1, s"bool verbose;")
    w.writeLines(0, "")
    sg.stmtsOrdered() foreach { stmt => stmt match {
      case cp: CondPart => {
        w.writeLines(1, s"void ${genEvalFuncName(cp.id)}() {")
        if (opt.scalarPartProfile)
          w.writeLines(2, s"++_essent_part_eval_counts[${cp.id}];")
        if (!cp.alwaysActive)
          w.writeLines(2, s"$flagVarName[${cp.id}] = false;")
        if (opt.trackParts)
          w.writeLines(2, s"${actTrac.actVarName}[${cp.id}]++;")

        val cacheOldOutputs = cp.outputsToDeclare.toSeq map {
          case (name, tpe) => { s"[[maybe_unused]] ${genCppType(tpe)} ${rn.emit(name + condPartWorker.cacheSuffix)} = ${rn.emit(name)};"
        }}
        w.writeLines(2, cacheOldOutputs)
        val (regUpdates, noRegUpdates) = partitionByType[RegUpdate](cp.memberStmts)
        val keepAvail = (cp.outputsToDeclare map { _._1 }).toSet
        val bodySG = StatementGraph(noRegUpdates, false)
        if (opt.conditionalMuxes)
          MakeCondMux(bodySG, rn, keepAvail)
        writeBodyInner(2, bodySG, opt, keepAvail)
        val fastUpdates = fastEdgeRegUpdates(cp, opt)
        fastUpdates.zipWithIndex.foreach { case (update, index) =>
          w.writeLines(2,
            s"${genFastNextName(cp.id, index)} = ${emitExpr(update.expr)};")
        }
        if (fastUpdates.nonEmpty) {
          // A prepared false-to-true edge only needs a physical assignment
          // when at least one cached next value differs from the current
          // register image.  Most full-chip uncore registers are idle, so
          // guard at partition granularity rather than repeating identical
          // UInt assignments for every clock edge.
          val changed = fastUpdates.zipWithIndex.map { case (update, index) =>
            val resultName = findResultName(update).get
            s"${rn.emit(resultName)} != ${genFastNextName(cp.id, index)}"
          }.mkString(" || ")
          w.writeLines(2, s"${genFastDirtyName(cp.id)} = $changed;")
        }
        w.writeLines(2, genAllTriggers(cp.outputsToDeclare.keys.toSeq,
          outputConsumers, condPartWorker.cacheSuffix))
        val regUpdateNamesInPart = regUpdates flatMap findResultName
        w.writeLines(2, genAllTriggers(regUpdateNamesInPart, outputConsumers,
          "$next"))
        // triggers for MemWrites
        val memWritesInPart = cp.memberStmts collect { case mw: MemWrite => mw }
        val memWriteTriggers = memWritesInPart flatMap { mw => {
          val condition = s"${emitExprWrap(mw.wrEn)} && ${emitExprWrap(mw.wrMask)}"
          genDepPartTriggers(outputConsumers.getOrElse(mw.memName, Seq()),
            condition)
        }}
        w.writeLines(2, memWriteTriggers)
        w.writeLines(2, regUpdates.flatMap(stmt => emitStmt(stmt)))

        w.writeLines(1, "}")

        if (fastUpdates.nonEmpty) {
          // The preceding eval(false) has already computed every retained
          // next value.  Preserve the original graph position and dirty-flag
          // propagation, but omit the partition's combinational recompute.
          // Clear the incoming flag exactly as EVAL_n would: a prepared edge
          // may enter here with the flag set because `reg != cached_next`,
          // then legitimately set it again for post-edge consumers below.
          w.writeLines(1, s"void ${genCommitFuncName(cp.id)}() {")
          if (!cp.alwaysActive)
            w.writeLines(2, s"$flagVarName[${cp.id}] = false;")
          w.writeLines(2, s"if (UNLIKELY(${genFastDirtyName(cp.id)})) {")
          if (opt.scalarPartProfile)
            w.writeLines(3, s"++_essent_part_dirty_commit_counts[${cp.id}];")
          fastUpdates.zipWithIndex.foreach { case (update, index) =>
            val resultName = findResultName(update).get
            val cache = genFastNextName(cp.id, index)
            w.writeLines(3, genDepPartTriggers(
              outputConsumers.getOrElse(resultName, Seq()),
              s"${rn.emit(resultName)} != $cache"))
            w.writeLines(3, s"${rn.emit(resultName)} = $cache;")
          }
          // The commit has made the complete partition image equal to its
          // cached next image.  Without clearing this bit, a partition whose
          // register does not feed its own next-state cone can keep issuing
          // the same physical stores on every later edge until some unrelated
          // input wakes EVAL_n again.  Small BOOM's cold sidecars drop exactly
          // this kind of already-committed idle work.
          w.writeLines(3, s"${genFastDirtyName(cp.id)} = false;")
          w.writeLines(2, "}")
          w.writeLines(1, "}")
        }
      }
      case _ => throw new Exception(s"Statement at top-level is not a CondPart (${stmt.serialize})")
    }}
    w.writeLines(0, "")
  }

  def writeZoningBody(sg: StatementGraph, condPartWorker: MakeCondPart,
      opt: OptFlags, hasTopResetPort: Boolean): Unit = {
    // `done_reset` also gates generated assertions. A top without the legacy
    // port named exactly `reset` must not lose partition caching merely
    // because its wrapper keeps assertions disabled; its concrete reset
    // inputs already participate in ordinary external-input dirty tracking.
    if (hasTopResetPort) {
      w.writeLines(2, "if (reset || !done_reset) {")
      w.writeLines(3, "sim_cached = false;")
      w.writeLines(3, "regs_set = false;")
      w.writeLines(2, "}")
    }
    w.writeLines(2, "if (!sim_cached) {")
    w.writeLines(3, s"$flagVarName.fill(true);")
    w.writeLines(2, "}")
    w.writeLines(2, "sim_cached = regs_set;")
    // A false -> true update transition is a clock edge.  Only partitions
    // containing clock-gated effects have to run merely because an edge
    // occurred; ordinary combinational partitions are activated by their
    // input dependencies.  Filling every partition here defeats zoning for
    // clients that perform a post-edge combinational settle (`eval(true)`
    // followed by `eval(false)`) and made small cold RTL sidecars execute the
    // whole extracted module on every active clock.
    val fastEdgeParts = sg.stmtsOrdered().collect {
      case cp: CondPart if fastEdgeRegUpdates(cp, opt).nonEmpty => cp.id
    }.toSet
    val outputConsumers = condPartWorker.getPartInputMap()
    val externalPartInputNames = condPartWorker.getExternalPartInputNames()
    val registerEdgeParts = sg.stmtsOrdered().collect {
      case cp: CondPart
          if !cp.alwaysActive && !fastEdgeParts.contains(cp.id) &&
             partRegisterEdgeEffects(cp).nonEmpty =>
        cp.id
    }.sorted
    if (fastEdgeParts.nonEmpty) {
      // A false -> true call pair is the producer's preview/commit protocol.
      // When no external RTL input changed between the two calls, every
      // cached pure-register next value is exact even if its partition flag
      // is set: that flag commonly means `current != next` and exists to wake
      // post-edge consumers, not that the preview is stale.  Small BOOM cold
      // sidecars exploit the same prepared-edge rule.  If a caller changes
      // any input after preview, fail back to the ordinary EVAL path.
      val externalInputsUnchanged = externalPartInputNames.toSeq.sorted
        .map(name =>
          s"(${rn.emit(name)} == ${rn.emit(name + condPartWorker.cacheSuffix)})")
        .mkString(" && ") match {
          case "" => "true"
          case expression => expression
        }
      w.writeLines(2,
        "const bool scalar_external_inputs_unchanged = prepared_edge || " +
        "!update_registers || prev_update_registers || " +
        s"($externalInputsUnchanged);")
      w.writeLines(2,
        "const bool scalar_fast_edge_commit = update_registers && " +
        "!prev_update_registers && scalar_external_inputs_unchanged;")
    }
    if (registerEdgeParts.nonEmpty) {
      w.writeLines(2, "if (update_registers && !prev_update_registers) {")
      registerEdgeParts.foreach { id =>
        w.writeLines(3, s"$flagVarName[$id] = true;")
      }
      w.writeLines(2, "}")
    }
    w.writeLines(2, "prev_update_registers = update_registers;")
    w.writeLines(2, "this->update_registers = update_registers;")
    w.writeLines(2, "this->done_reset = done_reset;")
    w.writeLines(2, "this->verbose = verbose;")
    // do activity detection on other inputs (external IOs and resets)
    w.writeLines(2, genAllTriggers(externalPartInputNames, outputConsumers,
      condPartWorker.cacheSuffix))
    // cache old versions
    val extIOCaches = externalPartInputNames map {
      sigName => s"${rn.emit(sigName + condPartWorker.cacheSuffix)} = ${rn.emit(sigName)};"
    }
    w.writeLines(2, extIOCaches.toSeq)
    sg.stmtsOrdered() foreach { stmt => stmt match {
      case cp: CondPart => {
        if (!cp.alwaysActive && fastEdgeParts.contains(cp.id)) {
          w.writeLines(2, "if (UNLIKELY(scalar_fast_edge_commit)) {")
          if (opt.scalarPartProfile)
            w.writeLines(3, s"++_essent_part_commit_counts[${cp.id}];")
          // COMMIT_n clears the incoming partition flag before its dirty
          // guard.  Do that one required store in place when the cached
          // register image is already clean, avoiding an otherwise empty
          // out-of-line call for large cold sidecars.
          w.writeLines(3,
            s"if (UNLIKELY(${genFastDirtyName(cp.id)})) ${genCommitFuncName(cp.id)}();")
          w.writeLines(3, s"else $flagVarName[${cp.id}] = false;")
          w.writeLines(2,
            s"} else if (UNLIKELY($flagVarName[${cp.id}])) ${genEvalFuncName(cp.id)}();")
        } else if (!cp.alwaysActive)
          w.writeLines(2, s"if (UNLIKELY($flagVarName[${cp.id}])) ${genEvalFuncName(cp.id)}();")
        else if (cp.memberStmts.nonEmpty && cp.memberStmts.forall {
          case _: Print => true
          case _ => false
        }) {
          // Print is emitted with these three common gates on every line.
          // Zoning used to call a large print-only partition unconditionally,
          // making a quiet full-chip producer test thousands of impossible
          // assertion messages on every fixed-point probe.  Hoisting the
          // common condition is exact and leaves mixed side-effect partitions
          // untouched.
          w.writeLines(2,
            s"if (UNLIKELY(done_reset && update_registers && verbose)) ${genEvalFuncName(cp.id)}();")
        } else
          w.writeLines(2, s"${genEvalFuncName(cp.id)}();")
      }
      case _ => w.writeLines(2, emitStmt(stmt))
    }}
    // w.writeLines(2,  "#ifdef ALL_ON")
    // w.writeLines(2, s"$flagVarName.fill(true);" )
    // w.writeLines(2,  "#endif")
    w.writeLines(2, "regs_set = true;")
  }


  // General Structure (and Compiler Boilerplate)
  //----------------------------------------------------------------------------
  def execute(circuit: Circuit): Unit = {
    val opt = initialOpt
    val topName = circuit.main
    val headerGuardName = topName.toUpperCase + "_H_"
    w.writeLines(0, s"#ifndef $headerGuardName")
    w.writeLines(0, s"#define $headerGuardName")
    w.writeLines(0, "")
    w.writeLines(0, "#include <array>")
    w.writeLines(0, "#include <cassert>")
    w.writeLines(0, "#include <cstdint>")
    w.writeLines(0, "#include <cinttypes>")
    w.writeLines(0, "#include <cstdlib>")
    w.writeLines(0, "#include \"sint.h\"")
    if (hasOracleMapping) {
      w.writeLines(0, "#include \"oracle_data.h\"")
    }
    w.writeLines(0, "#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)")
    w.writeLines(0, "#define ESSENT_ORACLE_LOAD(name, idx) (((const uint64_t*)__builtin_assume_aligned((name), 64))[(idx)])")
    w.writeLines(0, "#define ESSENT_NOINLINE __attribute__((noinline))")
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
    if (opt.trackParts || opt.trackSigs || opt.withVCD) {
      w.writeLines(0, "#include <fstream>")
    }

    if(opt.withVCD) {
      w.writeLines(0, "uint64_t vcd_cycle_count = 0;")
      w.writeLines(1,s"""FILE *outfile;""")
                                                                            
      w.writeLines(1,s"""char VCD_BUF[2000];""")
    }
    // Full-chip scalar sidecars must retain the same gated-clock semantics as
    // V2.  ClockDomainLowering analyzes the intact hierarchy, then returns
    // the ordinary clockless flattened statements expected by the legacy
    // zoning emitter.  Keep this opt-in so historical scalar artifacts do not
    // change silently.
    val scalarBodies = if (opt.clockDomainLowering) {
      require(!opt.simdV2,
        "--clock-domain-lowering is only for the legacy scalar emitter")
      simd.v2.ClockDomainLowering.lower(circuit).stmts
    } else {
      Extract.flattenWholeDesign(circuit, opt.removeFlatConnects, false)
    }
    val sg = StatementGraph(scalarBodies, false)
    val reverseSG: Option[StatementGraph] = reverseState.map { rs =>
      StatementGraph(rs.circuit, opt.removeFlatConnects, false)
    }

    // addInterLaneMemoryDeps moved below after flatVecMeta is built

    // Dump graph to DOT file for visualization
    try {
      val dotPath = new File(opt.outputDir(), s"$topName.graph.dot").getPath
      sg.dumpDot(dotPath)
      println(s"Wrote StatementGraph DOT to: $dotPath")
    } catch {
      case ex: Throwable => println(s"Failed to write DOT: ${ex.getMessage}")
    }


    logger.info(sg.makeStatsString())
    val containsAsserts = sg.containsStmtOfType[Stop]()
    val extIOMap = findExternalPorts(circuit)
    val condPartWorker = MakeCondPart(sg, rn, extIOMap)

    rn.populateFromSG(sg, extIOMap)
    reverseSG.foreach(rsg => rn.populateFromSG(rsg, extIOMap))

    if (probeSignals.nonEmpty) {
      var promoted = 0
      val probeDecs = ArrayBuffer[String]()
      for (sig <- probeSignals.keys.toSeq.sorted) {
        if (rn.nameToMeta.contains(sig)) {
          val typeStr = genCppType(rn.nameToMeta(sig).sigType)
          val emitName = sig.replace('.', '$')
          rn.mutateDecTypeIfLocal(sig, Probe)
          rn.nameToEmitName(sig) = emitName
          probeDecs += s"$typeStr $emitName;"
          promoted += 1
        }
      }
      if (promoted > 0) {
        println(s"[Compiler] Promoted $promoted probe signals to struct members")
        w.writeLines(1, "// ---- comb oracle probe fields ----")
        w.writeLines(1, probeDecs.toSeq)
      }
    }

    OptMuxToLUT(sg)
    reverseSG.foreach(rsg => OptMuxToLUT(rsg))

    if (opt.useCondParts) {
      condPartWorker.doOpt(opt.partCutoff)
    } else {
      if (opt.regUpdates)
        OptElideRegUpdates(sg)
      if (opt.conditionalMuxes)
        MakeCondMux(sg, rn, Set())
    }
    

    checkRegResetSafety(sg)

    if (opt.trackParts || opt.trackSigs || opt.trackExts)
      actTrac.declareTop(sg, topName, condPartWorker)

    circuit.modules foreach {
      case m: Module => declareModule(m, topName)
      case m: ExtModule => declareExtModule(m)
    }
    val topModule = findModule(topName, circuit) match {case m: Module => m}
    if (initialOpt.writeHarness) {
      w.writeLines(0, "")
      w.writeLines(1, s"void connect_harness(CommWrapper<struct $topName> *comm) {")
      w.writeLines(2, HarnessGenerator.harnessConnections(topModule))
      w.writeLines(1, "}")
      w.writeLines(0, "")
    }
    if (opt.withVCD)  { vcd.get.declareOldvaluesAll(circuit) }
    if(opt.withVCD) { vcd.get.genWaveHeader() }
    // A source-effect-free scalar producer still exposes inert assertion
    // fields so the shared Rocket full-chip wrapper keeps one stable ABI.
    // Only containsAsserts controls evaluation/exit behavior below.
    if (containsAsserts || opt.scalarDropSourceEffects) {
      w.writeLines(1, "bool assert_triggered = false;")
      w.writeLines(1, "int assert_exit_code;")
      w.writeLines(0, "")
    }
    if (opt.useCondParts)
      writeZoningPredecs(sg, condPartWorker, circuit.main, extIOMap, opt)
    if (hasOracleMapping) {
      w.writeLines(1, "int oracle_cycle = 0;")
      w.writeLines(0, "")
    }
    val preparedEdgeArgument =
      if (opt.scalarFastEdgeCommit) ", bool prepared_edge = false" else ""
    w.writeLines(1,
      s"void eval(bool update_registers, bool verbose, bool done_reset$preparedEdgeArgument) {")
    if(opt.withVCD) { vcd.get.initializeOldValues(circuit) }
    if (opt.trackParts || opt.trackSigs)
      w.writeLines(2, "act_cycle_count++;")
    if (opt.useCondParts)
      writeZoningBody(sg, condPartWorker, opt,
        topModule.ports.exists(_.name == "reset"))
    else {
      writeBodyInner(2, sg, opt)
    }
    if(opt.withVCD) { vcd.get.compareOldValues(circuit) }
    if (containsAsserts) {
      w.writeLines(2, "if (done_reset && update_registers && assert_triggered) exit(assert_exit_code);")
      w.writeLines(2, "if (!done_reset) assert_triggered = false;")
    }
    w.writeLines(0, "")
    if(opt.withVCD) { vcd.get.assignOldValues(circuit) }
    if (hasOracleMapping) {
      w.writeLines(2, s"if (update_registers && done_reset) oracle_cycle += 1;")
    }
    w.writeLines(2, "")
    w.writeLines(1, "}")
    // if (opt.trackParts || opt.trackSigs) {
    //   w.writeLines(1, s"~$topName() {")
    //   w.writeLines(2, "writeActToJson();")
    //   w.writeLines(1, "}")
    // }
    w.writeLines(0, "")
    w.writeLines(0, "")
    w.writeLines(0, s"} $topName;") //closing top module dec
    w.writeLines(0, "")
    if (!opt.noDefaultMain) {
      val iters = opt.defaultMainIters
      w.writeLines(0, "#ifndef ESSENT_NO_DEFAULT_MAIN")
      w.writeLines(0, "int main() {")
      w.writeLines(1, s"$topName t;")
      w.writeLines(1, s"for(int i=0; i<$iters; i++) {")
      w.writeLines(2, "t.eval(true, false, true);")
      w.writeLines(1, "}")
      w.writeLines(1, "return 0;")
      w.writeLines(0, "}")
      w.writeLines(0, "#endif")
    }

    w.writeLines(0, s"#endif  // $headerGuardName")
  }
}

case class EssentOptionsAnnotation(opt: OptFlags) extends NoTargetAnnotation

class EssentCompiler(opt: OptFlags) extends LazyLogging {

  // VerilogMemDelays: compiling memory latencies to combinational-read memories with delay pipelines.
  // This pass eliminates mems with read latency = 1 (introduced by CHIRRTL smem)
  // and thus satisfy essent.pass.FactorMemReads (memHasRightParams)

  // ConvertAsserts: Convert Verification IR (with op == Formal.Assert) into conventional print statement

  val readyForEssent_1: Seq[TransformDependency] = Seq(
    Dependency(firrtl.passes.memlib.VerilogMemDelays),
    Dependency(essent.passes.RemoveFormalNCover),
    Dependency(firrtl.transforms.formal.ConvertAsserts),
    Dependency(firrtl.passes.ExpandWhens)
    ) ++ (if (opt.scalarDropSourceEffects) Seq(
      Dependency(essent.passes.RemoveSourceEffects)) else Seq.empty) ++
    (if (opt.simdV2) Seq(
      Dependency(essent.simd.v2.BitsetStateLift),
      Dependency(essent.simd.v2.IndexedCounterStateLift),
      Dependency(essent.simd.v2.StateArrayLift)) else Seq.empty)


  val readyForEssent_3: Seq[TransformDependency] =
    (firrtl.stage.Forms.LowFormOptimized.asInstanceOf[Seq[TransformDependency]]) ++
    Seq(
      Dependency(essent.passes.LegacyInvalidNodesForConds),
      Dependency(essent.passes.ReplaceAsyncRegs)) ++
    // V2 and opt-in scalar full-chip emission must see the intact hierarchy:
    // ClockDomainLowering resolves EICG-derived domains into explicit
    // register/memory/effect enables before deleting Clock-only statements.
    // Historical scalar flows still take NoClockConnects here.
    (if (opt.simdV2 || opt.clockDomainLowering) Seq.empty
     else Seq(Dependency(essent.passes.NoClockConnects))) ++
    Seq(
      Dependency(essent.passes.RegFromMem1),
      Dependency(essent.passes.FactorMemReads),
      Dependency(essent.passes.FactorMemWrites),
      Dependency(essent.passes.SplitRegUpdates),
      Dependency(essent.passes.FixMulResultWidth),
      Dependency(essent.passes.DistinctTypeInstNames),
      Dependency(essent.passes.RemoveAsAsyncReset),
      Dependency(essent.passes.ReplaceRsvdKeywords)
    )

  val readyForEssent = readyForEssent_1 ++ readyForEssent_3

  def compileAndEmit(stateOld: CircuitState): Unit = {
    val circuit = stateOld.circuit
    val topName = circuit.main

    //we need to inject meta data here....
    val optAnno = EssentOptionsAnnotation(opt)

    // println( "Generating C++ for top module: " + topName)

    if (opt.writeHarness) {
      val harnessFilename = new File(opt.outputDir(), s"$topName-harness.cc")
      val harnessWriter = new FileWriter(harnessFilename)
      if (opt.withVCD) { HarnessGenerator.topFile(topName, harnessWriter," |  dut.genWaveHeader();") }
      else { HarnessGenerator.topFile(topName, harnessWriter, "")}
      harnessWriter.close()
    }


    val firrtlCompiler = new transforms.Compiler(readyForEssent)
    val cState = CircuitState(circuit, Seq(optAnno) ++ stateOld.annotations)
    println("Running FIRRTL transforms...")
    println("===============================")

    if (opt.simdV2) {
      // v2 pipeline: full NON-SIMD transform stack (names finalized by all
      // optimizations), then template-graph analysis + emission. No Vectorize,
      // no SplitRegUpdates SIMD phases, no atoms, no cycle breaker.
      val scalarState = firrtlCompiler.execute(cState)
      simd.v2.EmitV2.run(scalarState.circuit, opt, scalarState.annotations)
      return
    }

    val dumpPasses = opt.dumpLoFirrtl

    def runTransformWithLogging(state: CircuitState, t: firrtl.Transform): CircuitState = {
      logger.info(s">> Running ${t.name}")
      val t0 = System.nanoTime()
      val result = t.transform(state)
      val elapsed = (System.nanoTime() - t0) / 1e6
      val nMods = result.circuit.modules.size
      val nStmts = result.circuit.modules.collect { case m: Module =>
        flattenStmts(m.body).size
      }.sum
      println(f"  [pass] ${t.name}%-50s ${elapsed}%6.1f ms | $nMods%3d modules, $nStmts%6d stmts")
      logger.trace(s"\n===== After ${t.name} =====\n${result.circuit.serialize}")

      if (dumpPasses) {
        val safeName = t.name.replaceAll("[^a-zA-Z0-9_.-]", "_")
        val dumpFile = new File(opt.outputDir(), s"$topName.pass.$safeName.fir")
        val w = new FileWriter(dumpFile)
        w.write(result.circuit.serialize)
        w.close()
      }

      result
    }

    val (resultState, reverseResultOpt): (CircuitState, Option[CircuitState]) =
      (firrtlCompiler.execute(cState), None)

    if (opt.dumpLoFirrtl) {
      val debugFilename = new File(opt.outputDir(), s"$topName.lo.fir")
      val debugWriter = new FileWriter(debugFilename)
      debugWriter.write(resultState.circuit.serialize)
      debugWriter.close()
    }

    val outputDir = if (opt.outputDir().nonEmpty) opt.outputDir() else System.getProperty("user.dir")
    val dutFile = new File(outputDir, s"$topName.h")

    val dutWriter = new FileWriter(dutFile)
    val emitter = new EssentEmitter(opt, dutWriter, resultState, reverseResultOpt)
    emitter.execute(resultState.circuit)
    dutWriter.close()
  }
}
