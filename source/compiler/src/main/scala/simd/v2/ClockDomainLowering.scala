package essent.simd.v2

import essent.{Emitter, Extract}
import essent.ir.{MemWrite, RegUpdate}
import firrtl._
import firrtl.ir._
import firrtl.PrimOps

import scala.collection.mutable

/** Converts clock-gated synchronous domains into explicit state enables for
  * the cycle-level SIMD model.
  *
  * CHISA evaluates one logical rising edge per lane.  A synchronous EICG
  * whose enable is sampled while the source clock is low therefore advances
  * its child state on logical edge t+1 iff `en || test_en` computed from the
  * post-edge-t state is true.  That is exactly a mux-hold register update and
  * an AND on each synchronous memory write enable.  The clock waveform itself
  * is not data and is removed only after this conversion.
  *
  * This pass is intentionally fail-closed.  Treating an unknown derived or
  * independent clock as the primary clock would silently validate a
  * different DUT, which is worse than rejecting the design.
  */
object ClockDomainLowering {
  private val U1 = UIntType(IntWidth(1))
  private val One = UIntLiteral(1, IntWidth(1))
  private val Zero = UIntLiteral(0, IntWidth(1))

  case class Report(
      sourceClocks: Seq[String],
      clockGates: Seq[String],
      gatedRegisters: Int,
      gatedMemoryWrites: Int,
      gatedEffects: Int,
      enableNodes: Seq[String],
      gatedRegisterNames: Seq[String] = Seq.empty,
      gatedMemoryWriteNames: Seq[String] = Seq.empty,
      enableExpressions: Seq[(String, String)] = Seq.empty)

  case class Lowered(stmts: Seq[Statement], report: Report)

  private case class Domain(root: String, enable: Expression)

  private def rendered(e: Expression): String =
    Emitter.emitExpr(e)(null, Emitter.DefaultContext)

  private def isRef(e: Expression): Boolean = e match {
    case _: WRef | _: WSubField | _: WSubIndex | _: WSubAccess => true
    case _ => false
  }

  private def isOne(e: Expression): Boolean = e match {
    case UIntLiteral(v, _) => v != 0
    case _ => false
  }

  private def isZero(e: Expression): Boolean = e match {
    case UIntLiteral(v, _) => v == 0
    case _ => false
  }

  private def and(a: Expression, b: Expression): Expression =
    if (isZero(a) || isZero(b)) Zero
    else if (isOne(a)) b
    else if (isOne(b)) a
    else if (a.serialize == b.serialize) a
    else DoPrim(PrimOps.And, Seq(a, b), Seq.empty, U1)

  private def or(a: Expression, b: Expression): Expression =
    if (isOne(a) || isOne(b)) One
    else if (isZero(a)) b
    else if (isZero(b)) a
    else if (a.serialize == b.serialize) a
    else DoPrim(PrimOps.Or, Seq(a, b), Seq.empty, U1)

  private def sourceRef(e: Expression): Expression = e match {
    case w: WRef => w.copy(flow = SourceFlow)
    case w: WSubField => w.copy(expr = sourceRef(w.expr), flow = SourceFlow)
    case w: WSubIndex => w.copy(expr = sourceRef(w.expr), flow = SourceFlow)
    case w: WSubAccess => w.copy(expr = sourceRef(w.expr), flow = SourceFlow)
    case other => other
  }

  /** Analyze the intact hierarchy, then rewrite the same flattened scalar IR
    * shape historically consumed by V2. */
  def lower(circuit: Circuit): Lowered = {
    val unsquished = Extract.flattenWholeDesign(circuit, squishOutConnects = false)
    val top = Extract.findModule(circuit.main, circuit).asInstanceOf[Module]
    val topClocks = top.ports.collect { case Port(_, n, _, ClockType) => n }.toSet
    if (topClocks.isEmpty) {
      // Combinational unit tests and already-factored synthetic memory tests
      // intentionally have no clock waveform at all.  Preserve that useful
      // clockless IR mode, but never accept actual registers/effects without
      // a source clock from which their edge semantics can be derived.
      val clockedState = unsquished.collect {
        case r: DefRegister => r.name
        case p: Print => "printf:" + p.string.serialize
        case _: Stop => "stop"
      }
      require(clockedState.isEmpty,
        s"[v2-clock] top '${circuit.main}' has no source Clock port but contains " +
          s"clocked state/effects: ${clockedState.take(5).mkString(", ")}")
      val clockless = Extract.flattenWholeDesign(
        essent.passes.NoClockConnects.run(circuit), squishOutConnects = true)
      return Lowered(clockless, Report(Seq.empty, Seq.empty, 0, 0, 0, Seq.empty))
    }

    val allDefinedNames = unsquished.flatMap {
      case d: DefNode => Seq(d.name)
      case r: DefRegister => Seq(r.name)
      case m: DefMemory => Seq(m.name)
      case w: DefWire => Seq(w.name)
      case _ => Seq.empty
    }.toSet
    val storageNames = unsquished.collect {
      case r: DefRegister => r.name
      case m: DefMemory => m.name
    }.toSet
    val topDataPorts = top.ports.collect {
      case Port(_, n, Input, t) if t != ClockType => n
    }.toSet

    val extOutputNames = mutable.Set[String]()
    val gatePrefixes = mutable.ArrayBuffer[String]()
    for ((moduleName, prefix) <- Extract.findAllModuleInstances(circuit)) {
      Extract.findModule(moduleName, circuit) match {
        case em: ExtModule =>
          em.ports.collect { case Port(_, n, Output, t) if t != ClockType =>
            extOutputNames += (prefix + n)
          }
          if (em.defname == "EICG_wrapper") gatePrefixes += prefix
        case _ =>
      }
    }

    val clockDefs = mutable.LinkedHashMap[String, Expression]()
    val valueDefs = mutable.LinkedHashMap[String, Expression]()
    unsquished.foreach {
      case d: DefNode if d.value.tpe == ClockType => clockDefs(d.name) = d.value
      case d: DefNode => valueDefs(d.name) = d.value
      case c: Connect if c.loc.tpe == ClockType || c.expr.tpe == ClockType =>
        clockDefs(rendered(c.loc)) = c.expr
      case c: Connect => valueDefs(rendered(c.loc)) = c.expr
      case _ =>
    }

    val gateByOutput = gatePrefixes.iterator.map { prefix =>
      val required = Seq("in", "en", "test_en").map(prefix + _)
      val missing = required.filterNot(n => clockDefs.contains(n) || valueDefs.contains(n))
      require(missing.isEmpty,
        s"[v2-clock] EICG '$prefix' is missing connection(s): ${missing.mkString(", ")}")
      (prefix + "out") -> prefix
    }.toMap

    def normalizeData(e: Expression, stack: Set[String] = Set.empty,
        depth: Int = 0): Expression = {
      require(depth <= 128,
        s"[v2-clock] gate-enable expression exceeds 128 aliases near '${e.serialize}'")
      if (isRef(e)) {
        val name = rendered(e)
        if (storageNames(name) || topDataPorts(name) || extOutputNames(name)) sourceRef(e)
        else valueDefs.get(name) match {
          case Some(next) =>
            require(!stack(name), s"[v2-clock] cyclic data alias while resolving '$name'")
            normalizeData(next, stack + name, depth + 1)
          case None =>
            // A surviving definition is safe to reference.  This includes
            // compiler-created nodes whose connect was already factored.
            if (allDefinedNames(name)) sourceRef(e)
            else throw new IllegalStateException(
              s"[v2-clock] unresolved gate-enable source '$name'")
        }
      } else e.mapExpr(ch => normalizeData(ch, stack, depth + 1))
    }

    val domainMemo = mutable.Map[String, Domain]()
    val resolvingClocks = mutable.Set[String]()

    def resolveClock(e: Expression): Domain = {
      if (!isRef(e)) e match {
        case DoPrim(PrimOps.AsClock, Seq(arg), _, _) =>
          throw new IllegalStateException(
            s"[v2-clock] arbitrary asClock-derived clock is unsupported: ${arg.serialize}")
        case _ => throw new IllegalStateException(
          s"[v2-clock] unsupported derived-clock expression: ${e.serialize}")
      }
      else {
        val name = rendered(e)
        domainMemo.getOrElseUpdate(name, {
          require(!resolvingClocks(name),
            s"[v2-clock] cyclic Clock connection while resolving '$name'")
          resolvingClocks += name
          val result = gateByOutput.get(name) match {
            case Some(prefix) =>
              val parent = resolveClock(clockDefs(prefix + "in"))
              val gateEnable = or(normalizeData(valueDefs(prefix + "en")),
                normalizeData(valueDefs(prefix + "test_en")))
              Domain(parent.root, and(parent.enable, gateEnable))
            case None => clockDefs.get(name) match {
              case Some(next) => resolveClock(next)
              case None if topClocks(name) => Domain(name, One)
              case None => throw new IllegalStateException(
                s"[v2-clock] Clock '$name' does not resolve to a top clock or recognized EICG")
            }
          }
          resolvingClocks -= name
          result
        })
      }
    }

    val regDomains = unsquished.collect { case r: DefRegister =>
      r.name -> resolveClock(r.clock)
    }.toMap

    val memoryWriteDomains = mutable.Map[(String, String), Domain]()
    unsquished.collect { case m: DefMemory => m }.foreach { m =>
      m.writers.foreach { port =>
        val clockPort = s"${m.name}.$port.clk"
        val clock = clockDefs.getOrElse(clockPort,
          throw new IllegalStateException(
            s"[v2-clock] memory write port '$clockPort' has no Clock connection"))
        memoryWriteDomains((m.name, port)) = resolveClock(clock)
      }
    }
    val effectDomains = unsquished.collect {
      case p: Print => resolveClock(p.clk)
      case s: Stop => resolveClock(s.clk)
    }
    val usedRoots = (regDomains.valuesIterator.map(_.root) ++
      memoryWriteDomains.valuesIterator.map(_.root) ++
      effectDomains.iterator.map(_.root)).toSet
    require(usedRoots.size <= 1,
      s"[v2-clock] independent source clocks are unsupported: ${usedRoots.toSeq.sorted.mkString(", ")}")

    // Use one graph node per distinct gate expression.  Thousands of state
    // elements in one domain then share a single computed enable instead of
    // embedding the same expression in every mux-hold update.
    val rawClockless = Extract.flattenWholeDesign(
      essent.passes.NoClockConnects.run(circuit), squishOutConnects = true)
    val occupied = rawClockless.flatMap {
      case d: DefNode => Seq(d.name)
      case r: DefRegister => Seq(r.name)
      case m: DefMemory => Seq(m.name)
      case _ => Seq.empty
    }.toSet
    val enableByKey = mutable.LinkedHashMap[String, (String, Expression)]()
    def enabledRef(domain: Domain): Option[WRef] = {
      if (isOne(domain.enable)) None
      else {
        val key = domain.enable.serialize
        val (name, _) = enableByKey.getOrElseUpdate(key, {
          var i = enableByKey.size
          var candidate = s"__chisa_clock_enable_$i"
          while (occupied(candidate)) { i += 1; candidate = s"__chisa_clock_enable_$i" }
          candidate -> domain.enable
        })
        Some(WRef(name, U1, NodeKind, SourceFlow))
      }
    }

    // SplitRegUpdates gives every register a stable `r$next` DefNode and a
    // final `r <= r$next` RegUpdate.  V2 deliberately builds its recurrence
    // graph from that named next-state node (and its emitter commits the same
    // name), rather than re-reading RegUpdate.expr.  Put the clock hold into
    // the DefNode itself.  Wrapping only RegUpdate.expr looks correct in this
    // flattened IR but is silently outside V2's next-state contract: the
    // manifest would claim a gated register while generated C++ advanced it
    // on every source-clock edge.
    val nextDefNames = rawClockless.collect { case d: DefNode => d.name }.toSet
    val gatedNextDefs = mutable.LinkedHashMap[
      String, (String, WRef, Expression)]() // next name -> (reg name, enable, reg ref)

    var gatedRegs = 0
    var gatedWrites = 0
    var gatedEffects = 0
    val gatedRegNames = mutable.ArrayBuffer[String]()
    val gatedWriteNames = mutable.ArrayBuffer[String]()
    rawClockless.foreach {
      case ru: RegUpdate =>
        val name = rendered(ru.regRef)
        regDomains.get(name).flatMap(enabledRef) match {
          case Some(en) =>
            val expectedNext = name + "$next"
            val actualNext = ru.expr match {
              case ref: WRef => ref.name
              case other => throw new IllegalStateException(
                s"[v2-clock] gated register '$name' has non-canonical update " +
                  s"'${other.serialize}', expected a '$expectedNext' reference")
            }
            require(actualNext == expectedNext,
              s"[v2-clock] gated register '$name' commits '$actualNext', " +
                s"expected '$expectedNext'")
            require(nextDefNames(expectedNext),
              s"[v2-clock] gated register '$name' has no '$expectedNext' DefNode")
            require(!gatedNextDefs.contains(expectedNext),
              s"[v2-clock] duplicate update for gated register '$name'")
            gatedNextDefs(expectedNext) =
              (name, en, sourceRef(ru.regRef))
            gatedRegs += 1
            gatedRegNames += name
          case None =>
        }
      case _ =>
    }
    val expectedGatedRegs = regDomains.iterator.collect {
      case (name, domain) if !isOne(domain.enable) => name
    }.toSet
    require(gatedRegNames.toSet == expectedGatedRegs,
      s"[v2-clock] failed to materialize gated register update(s): " +
        s"${(expectedGatedRegs -- gatedRegNames).toSeq.sorted.take(8).mkString(", ")}")

    var rewrittenGatedDefs = 0
    val rewritten = rawClockless.map {
      case d: DefNode if gatedNextDefs.contains(d.name) =>
        val (_, en, regRef) = gatedNextDefs(d.name)
        rewrittenGatedDefs += 1
        d.copy(value = Mux(en, d.value, regRef, d.value.tpe))
      case mw: MemWrite =>
        memoryWriteDomains.get((mw.memName, mw.portName)).flatMap(enabledRef) match {
          case Some(en) =>
            gatedWrites += 1
            gatedWriteNames += s"${mw.memName}.${mw.portName}"
            mw.copy(wrEn = and(en, mw.wrEn))
          case None => mw
        }
      case p: Print =>
        enabledRef(resolveClock(p.clk)) match {
          case Some(en) => gatedEffects += 1; p.copy(en = and(en, p.en))
          case None => p
        }
      case s: Stop =>
        enabledRef(resolveClock(s.clk)) match {
          case Some(en) => gatedEffects += 1; s.copy(en = and(en, s.en))
          case None => s
        }
      case other => other
    }
    require(rewrittenGatedDefs == gatedNextDefs.size,
      s"[v2-clock] rewrote $rewrittenGatedDefs of ${gatedNextDefs.size} gated next-state definitions")
    val enableNodes = enableByKey.valuesIterator.map { case (name, expr) =>
      DefNode(NoInfo, name, expr)
    }.toSeq
    if (gatePrefixes.nonEmpty || enableNodes.nonEmpty)
      println(s"[v2-clock] roots=${usedRoots.toSeq.sorted.mkString(",")} " +
        s"gates=${gatePrefixes.size} enables=${enableNodes.size} " +
        s"gated-regs=$gatedRegs gated-mem-writes=$gatedWrites gated-effects=$gatedEffects")

    Lowered(enableNodes ++ rewritten, Report(
      sourceClocks = usedRoots.toSeq.sorted,
      clockGates = gatePrefixes.toSeq.sorted,
      gatedRegisters = gatedRegs,
      gatedMemoryWrites = gatedWrites,
      gatedEffects = gatedEffects,
      enableNodes = enableNodes.map(_.name),
      gatedRegisterNames = gatedRegNames.toSeq.sorted,
      gatedMemoryWriteNames = gatedWriteNames.toSeq.sorted,
      enableExpressions = enableNodes.map(d => d.name -> d.value.serialize)))
  }
}
