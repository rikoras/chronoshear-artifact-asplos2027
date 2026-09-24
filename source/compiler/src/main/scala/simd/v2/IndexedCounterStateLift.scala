package essent.simd.v2

import essent.EssentOptionsAnnotation
import firrtl._
import firrtl.annotations.NoTargetAnnotation
import firrtl.ir._
import firrtl.options.Dependency
import firrtl.passes.MemPortUtils

import scala.collection.mutable

/** Explicit configuration for recovering scalar, elaboration-unrolled counter
  * families.  A selector can be either a leaf family (`count`) or a
  * module-qualified family (`TLToAXI4_1.count`).
  *
  * `minimumDepth` is deliberately part of the configuration: tiny scalar
  * families are normally cheaper than an addressable state table and should
  * not be changed merely because they happen to have numbered names.
  */
case class IndexedCounterStateLiftConfigAnnotation(
    families: Set[String],
    minimumDepth: Int = 16) extends NoTargetAnnotation

/** Programmatic selector for the packed-register variant.  This keeps the
  * same strict indexed-counter recognition as the memory lift, but represents
  * a one-bit family as <=64-bit banks.  It is an experimental physical-state
  * lowering and is independently opt-in from the chronological-memory form.
  */
case class IndexedCounterBankLiftConfigAnnotation(
    families: Set[String],
    minimumDepth: Int = 16) extends NoTargetAnnotation

/** Source-to-physical mapping for one packed indexed-counter family. */
case class IndexedCounterBankStorageAnnotation(
    module: String,
    family: String,
    banks: Seq[String],
    membersByIndex: Seq[String]) extends NoTargetAnnotation

/** Recover a Chisel-loop-expanded family of independent counters as one
  * indexed storage object before RemoveAccesses destroys the common address.
  *
  * The motivating artifact is TLToAXI4's `count_1 .. count_128`.  Chisel
  * emits one scalar register and one copy of the update/assert/stall logic per
  * AXI ID.  The update is nevertheless an indexed two-port operation:
  * exactly one request ID may increment and exactly one response ID may
  * decrement in a cycle.  Leaving the scalars unrelated gives V2 128
  * self-loop SCCs/oracles and turns an indexed lookup into a 128-way mux.
  *
  * This transform moves storage only.  Every consumer of every original
  * scalar (including overflow/underflow assertions and stall logic) remains
  * in FIRRTL and reads the corresponding table entry.  The two ordinary
  * memory writes implement the exact old-value expression, including the
  * same-ID increment+decrement collision.  Synchronous reset is represented
  * by final-priority per-entry ports, matching StateArrayLift's chronological
  * memory contract.
  *
  * Recognition is intentionally fail-closed.  A family is changed only if:
  *
  *   - every member is a same-width UInt register with identical clock/reset;
  *   - every member has exactly one unconditional update of the form
  *       count := count + inc - dec (with the original width truncations);
  *   - `inc` and `dec` each factor into a shared enable and a distinct bit of
  *     one shared UIntToOH-style `bits(dshl(1, address), depth-1, 0)` value;
  *   - selector bits cover the table exactly once; and
  *   - reset, when present, initializes every entry to zero.
  *
  * A source change that violates any item simply leaves the RTL untouched.
  */
object IndexedCounterStateLift extends Transform {
  override def inputForm: CircuitForm = MidForm
  override def outputForm: CircuitForm = MidForm

  override def prerequisites = Seq(Dependency(firrtl.passes.ExpandConnects))
  override def optionalPrerequisites = Seq.empty
  override def optionalPrerequisiteOf = Seq(
    Dependency(StateArrayLift),
    Dependency(firrtl.passes.RemoveAccesses),
    Dependency(firrtl.passes.ExpandWhens),
    Dependency(firrtl.passes.LowerTypes))
  override def invalidates(a: Transform): Boolean = false

  private val BoolType = UIntType(IntWidth(1))
  private val One = UIntLiteral(1, IntWidth(1))

  private case class FamilyRequest(module: Option[String], leaf: String)
  private case class Update(reg: DefRegister, connect: Connect,
      inc: Expression, dec: Expression)
  private case class Selector(index: Int, vector: Expression,
      address: Expression, common: Expression)
  private case class Member(update: Update, inc: Selector, dec: Selector)
  private case class Lifted(module: Module,
      memoryAnnotation: Option[StateArrayStorageAnnotation] = None,
      bankAnnotation: Option[IndexedCounterBankStorageAnnotation] = None)

  private def configuredFamilies: Set[String] =
    sys.env.get("V2_INDEXED_STATE_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).toSet

  private def configuredBankFamilies: Set[String] =
    sys.env.get("V2_INDEXED_COUNTER_BANK_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).toSet

  private def parseRequest(value: String): FamilyRequest = {
    val dot = value.lastIndexOf('.')
    if (dot < 0) FamilyRequest(None, value)
    else FamilyRequest(Some(value.take(dot)), value.drop(dot + 1))
  }

  private def applies(request: FamilyRequest, module: String): Boolean =
    request.module.forall(_ == module)

  private def familyOrdinal(name: String, family: String): Option[Int] = {
    if (name == family) Some(0)
    else if (name.startsWith(family + "_")) {
      val suffix = name.drop(family.length + 1)
      if (suffix.nonEmpty && suffix.forall(_.isDigit)) Some(suffix.toInt)
      else None
    } else None
  }

  private def isOne(value: Expression): Boolean = value match {
    case UIntLiteral(v, _) => v == 1
    case _ => false
  }

  private def isZero(value: Expression): Boolean = value match {
    case UIntLiteral(v, _) => v == 0
    case _ => false
  }

  private def and(left: Expression, right: Expression): Expression =
    if (isOne(left)) right
    else if (isOne(right)) left
    else DoPrim(firrtl.PrimOps.And, Seq(left, right), Seq.empty, BoolType)

  private def eq(left: Expression, right: Expression): Expression =
    DoPrim(firrtl.PrimOps.Eq, Seq(left, right), Seq.empty, BoolType)

  private def neq(left: Expression, right: Expression): Expression =
    DoPrim(firrtl.PrimOps.Neq, Seq(left, right), Seq.empty, BoolType)

  private def containsAnyRef(value: Expression, names: Set[String]): Boolean = {
    var found = false
    def walk(expression: Expression): Unit = if (!found) expression match {
      case WRef(name, _, _, _) if names(name) => found = true
      case other => other.foreachExpr(walk)
    }
    walk(value)
    found
  }

  private def portField(mem: DefMemory, port: String, field: String,
      flow: Flow): Expression = {
    val memType = MemPortUtils.memType(mem)
    val memRef = WRef(mem.name, memType, MemKind, SourceFlow)
    val portType = firrtl.Utils.field_type(memType, port)
    val portRef = WSubField(memRef, port, portType, SourceFlow)
    val fieldType = firrtl.Utils.field_type(portType, field)
    WSubField(portRef, field, fieldType, flow)
  }

  private def wrapAdd(left: Expression, right: Expression,
      width: Int): Expression = {
    val wide = UIntType(IntWidth(width + 1))
    val result = UIntType(IntWidth(width))
    val sum = DoPrim(firrtl.PrimOps.Add, Seq(left, right), Seq.empty, wide)
    DoPrim(firrtl.PrimOps.Tail, Seq(sum), Seq(BigInt(1)), result)
  }

  private def wrapSub(left: Expression, right: Expression,
      width: Int): Expression = {
    val wide = UIntType(IntWidth(width + 1))
    val result = UIntType(IntWidth(width))
    val difference = DoPrim(firrtl.PrimOps.Sub, Seq(left, right), Seq.empty, wide)
    DoPrim(firrtl.PrimOps.Tail, Seq(difference), Seq(BigInt(1)), result)
  }

  private def liftFamily(module: Module, request: FamilyRequest,
      minimumDepth: Int, banked: Boolean): Either[String, Lifted] = {
    val registers = mutable.LinkedHashMap[String, DefRegister]()
    val nodes = mutable.LinkedHashMap[String, Expression]()
    val connects = mutable.LinkedHashMap[String, mutable.ArrayBuffer[(Connect, Boolean)]]()

    def discover(statement: Statement, conditional: Boolean): Unit = statement match {
      case register: DefRegister
          if familyOrdinal(register.name, request.leaf).isDefined =>
        registers(register.name) = register
      case node: DefNode => nodes(node.name) = node.value
      case connect @ Connect(_, WRef(name, _, _, _), _)
          if familyOrdinal(name, request.leaf).isDefined =>
        connects.getOrElseUpdate(name, mutable.ArrayBuffer()) += ((connect, conditional))
      case Block(statements) => statements.foreach(discover(_, conditional))
      case Conditionally(_, _, conseq, alt) =>
        discover(conseq, conditional = true)
        discover(alt, conditional = true)
      case other => other.foreachStmt(discover(_, conditional))
    }
    discover(module.body, conditional = false)

    if (registers.size < minimumDepth)
      return Left(s"only ${registers.size} member(s), minimum is $minimumDepth")

    val orderedRegisters = registers.values.toSeq.sortBy(register =>
      familyOrdinal(register.name, request.leaf).get)
    val registerNames = orderedRegisters.iterator.map(_.name).toSet
    val widths = orderedRegisters.map(_.tpe).collect {
      case tpe: UIntType => firrtl.bitWidth(tpe).toInt
    }
    if (widths.size != orderedRegisters.size || widths.distinct.size != 1)
      return Left("members are not same-width UInt registers")
    val width = widths.head
    if (width < 1 || width > 64)
      return Left(s"member width $width is outside supported range 1..64")

    val clocks = orderedRegisters.map(_.clock.serialize).distinct
    val resets = orderedRegisters.map(_.reset.serialize).distinct
    if (clocks.size != 1 || resets.size != 1)
      return Left("members do not share one clock/reset")
    val activeReset = !isZero(orderedRegisters.head.reset)
    if (activeReset && orderedRegisters.exists(register => !isZero(register.init)))
      return Left("active reset is supported only for all-zero initialization")
    if (activeReset) orderedRegisters.head.reset.tpe match {
      case UIntType(IntWidth(value)) if value == 1 =>
      case other => return Left(s"active reset is not synchronous UInt<1>: ${other.serialize}")
    }

    def dereference(value: Expression): Expression = value match {
      case WRef(name, _, NodeKind, _) if nodes.contains(name) =>
        dereference(nodes(name))
      case other => other
    }

    def oneTail(value: Expression): Option[Expression] = dereference(value) match {
      case DoPrim(firrtl.PrimOps.Tail, Seq(inner), Seq(amount), _) if amount == 1 =>
        Some(inner)
      case _ => None
    }

    def matchUpdate(register: DefRegister, connect: Connect): Option[Update] = {
      for {
        subValue <- oneTail(connect.expr)
        sub = dereference(subValue)
        pair <- sub match {
          case DoPrim(firrtl.PrimOps.Sub, Seq(addValue, dec), _, _) => Some((addValue, dec))
          case _ => None
        }
        addValue <- oneTail(pair._1)
        add = dereference(addValue)
        operands <- add match {
          case DoPrim(firrtl.PrimOps.Add, Seq(old @ WRef(name, _, _, _), inc), _, _)
              if name == register.name => Some((old, inc))
          case DoPrim(firrtl.PrimOps.Add, Seq(inc, old @ WRef(name, _, _, _)), _, _)
              if name == register.name => Some((old, inc))
          case _ => None
        }
        if firrtl.bitWidth(operands._2.tpe) == 1
        if firrtl.bitWidth(pair._2.tpe) == 1
      } yield Update(register, connect, operands._2, pair._2)
    }

    val updates = orderedRegisters.map { register =>
      connects.get(register.name) match {
        case Some(values) if values.size == 1 && !values.head._2 =>
          matchUpdate(register, values.head._1) match {
            case Some(update) => update
            case None => return Left(s"${register.name} update is not count + inc - dec")
          }
        case Some(values) =>
          return Left(s"${register.name} has ${values.size} or conditional update(s)")
        case None => return Left(s"${register.name} has no update")
      }
    }

    def flattenAnd(value: Expression): Seq[Expression] = dereference(value) match {
      case DoPrim(firrtl.PrimOps.And, Seq(left, right), _, _) =>
        flattenAnd(left) ++ flattenAnd(right)
      case other => Seq(other)
    }

    def oneHotAddress(value: Expression, depth: Int): Option[Expression] = {
      def strip(expression: Expression): Expression = dereference(expression) match {
        case DoPrim(firrtl.PrimOps.Bits, Seq(inner), Seq(high, low), _)
            if high == depth - 1 && low == 0 => dereference(inner)
        case other => other
      }
      strip(value) match {
        case DoPrim(firrtl.PrimOps.Dshl, Seq(literal, address), _, _)
            if isOne(literal) => Some(address)
        case _ => None
      }
    }

    def matchSelector(value: Expression, depth: Int): Either[String, Selector] = {
      val factors = flattenAnd(value)
      val candidates = factors.zipWithIndex.flatMap { case (factor, position) =>
        dereference(factor) match {
          case DoPrim(firrtl.PrimOps.Bits, Seq(vector), Seq(high, low), _)
              if high == low && high >= 0 && high < depth &&
                firrtl.bitWidth(vector.tpe) == depth =>
            oneHotAddress(vector, depth).map(address =>
              (position, high.toInt, vector, address))
          case _ => None
        }
      }
      if (candidates.size != 1)
        Left(s"expected one UIntToOH selector factor, found ${candidates.size}")
      else {
        val (position, index, vector, address) = candidates.head
        val commonFactors = factors.zipWithIndex.collect {
          case (factor, current) if current != position => factor
        }
        val common = commonFactors.foldLeft(One: Expression)(and)
        Right(Selector(index, vector, address, common))
      }
    }

    val depth = updates.size
    val members = updates.map { update =>
      (matchSelector(update.inc, depth), matchSelector(update.dec, depth)) match {
        case (Right(inc), Right(dec)) => Member(update, inc, dec)
        case (Left(reason), _) => return Left(s"${update.reg.name} increment: $reason")
        case (_, Left(reason)) => return Left(s"${update.reg.name} decrement: $reason")
      }
    }
    if (members.map(_.inc.index).sorted != (0 until depth) ||
        members.map(_.dec.index).sorted != (0 until depth))
      return Left("increment/decrement selectors do not cover every entry exactly once")
    if (members.exists(member => member.inc.index != member.dec.index))
      return Left("increment and decrement selectors disagree on an entry index")

    def oneSerialized(values: Seq[Expression], label: String): Either[String, Expression] = {
      val groups = values.groupBy(_.serialize)
      if (groups.size == 1) Right(values.head)
      else Left(s"$label is not shared by every member (${groups.size} forms)")
    }
    val incVector = oneSerialized(members.map(_.inc.vector), "increment one-hot vector") match {
      case Right(value) => value
      case Left(reason) => return Left(reason)
    }
    val decVector = oneSerialized(members.map(_.dec.vector), "decrement one-hot vector") match {
      case Right(value) => value
      case Left(reason) => return Left(reason)
    }
    val incAddress = oneSerialized(members.map(_.inc.address), "increment address") match {
      case Right(value) => value
      case Left(reason) => return Left(reason)
    }
    val decAddress = oneSerialized(members.map(_.dec.address), "decrement address") match {
      case Right(value) => value
      case Left(reason) => return Left(reason)
    }
    val incCommon = oneSerialized(members.map(_.inc.common), "increment enable") match {
      case Right(value) => value
      case Left(reason) => return Left(reason)
    }
    val decCommon = oneSerialized(members.map(_.dec.common), "decrement enable") match {
      case Right(value) => value
      case Left(reason) => return Left(reason)
    }
    val controls = Seq(incVector, decVector, incAddress, decAddress, incCommon, decCommon)
    if (controls.exists(containsAnyRef(_, registerNames)))
      return Left("selector/address/control logic reads the counter family")

    // One-bit modulo arithmetic is exactly XOR: for every Boolean old/inc/dec
    // combination, (old + inc - dec) mod 2 == old xor inc xor dec.  Pack at
    // most 64 entries per physical register, keep the original count_i names
    // as slice DefNodes, and leave every consumer/assert/protocol decision in
    // the RTL.  The packed next expression is compact because the already
    // proven one-hot vectors provide the whole-bank toggle masks directly.
    if (banked) {
      if (width != 1)
        return Left(s"packed counter banks currently require width 1, got $width")
      if (!activeReset)
        return Left("packed counter banks currently require synchronous zero reset")

      val namespace = Namespace(module)
      val membersByIndex = members.sortBy(_.inc.index).map(_.update.reg)
      val banks = membersByIndex.grouped(64).zipWithIndex.map {
        case (chunk, bankIndex) =>
          val bankWidth = chunk.size
          val bankType = UIntType(IntWidth(bankWidth))
          val bankName = namespace.newName(s"__v2_indexed_${request.leaf}_bank_$bankIndex")
          val bankSource = WRef(bankName, bankType, RegKind, SourceFlow)
          val bankSink = WRef(bankName, bankType, RegKind, SinkFlow)
          val definition = DefRegister(chunk.head.info, bankName, bankType,
            chunk.head.clock, chunk.head.reset, UIntLiteral(0, IntWidth(bankWidth)))
          (bankName, bankType, bankSource, bankSink, definition, chunk)
      }.toSeq

      val replacementKinds = membersByIndex.iterator.map(register =>
        register.name -> WRef(register.name, register.tpe, NodeKind, SourceFlow)).toMap
      def rewriteExpression(value: Expression): Expression = value match {
        case WRef(name, _, _, flow) if replacementKinds.contains(name) =>
          replacementKinds(name).copy(flow = flow)
        case other => other.mapExpr(rewriteExpression)
      }
      def rewriteStatement(statement: Statement): Statement = statement match {
        case register: DefRegister if registerNames(register.name) => EmptyStmt
        case Connect(_, WRef(name, _, _, _), _) if registerNames(name) => EmptyStmt
        case other => other.mapStmt(rewriteStatement).mapExpr(rewriteExpression)
      }

      val sliceNodes = banks.flatMap { case (_, bankType, bankSource, _, _, chunk) =>
        chunk.zipWithIndex.map { case (register, bit) =>
          val slice = DoPrim(firrtl.PrimOps.Bits, Seq(bankSource),
            Seq(BigInt(bit), BigInt(bit)), register.tpe)
          DefNode(register.info, register.name, slice)
        }
      }
      val rewrittenIncVector = rewriteExpression(incVector)
      val rewrittenDecVector = rewriteExpression(decVector)
      val rewrittenIncCommon = rewriteExpression(incCommon)
      val rewrittenDecCommon = rewriteExpression(decCommon)
      val bankUpdates = banks.zipWithIndex.map {
        case ((_, bankType, bankSource, bankSink, _, chunk), bankIndex) =>
          val low = bankIndex * 64
          val high = low + chunk.size - 1
          val zero = UIntLiteral(0, IntWidth(chunk.size))
          def slice(vector: Expression): Expression =
            DoPrim(firrtl.PrimOps.Bits, Seq(vector),
              Seq(BigInt(high), BigInt(low)), bankType)
          val incMask = Mux(rewrittenIncCommon, slice(rewrittenIncVector), zero, bankType)
          val decMask = Mux(rewrittenDecCommon, slice(rewrittenDecVector), zero, bankType)
          val toggled = DoPrim(firrtl.PrimOps.Xor, Seq(bankSource, incMask),
            Seq.empty, bankType)
          val next = DoPrim(firrtl.PrimOps.Xor, Seq(toggled, decMask),
            Seq.empty, bankType)
          Connect(NoInfo, bankSink, next)
      }
      val body = Block(banks.map(_._5) ++ sliceNodes ++
        Seq(rewriteStatement(module.body)) ++ bankUpdates)
      val annotation = IndexedCounterBankStorageAnnotation(module.name,
        request.leaf, banks.map(_._1), membersByIndex.map(_.name))
      return Right(Lifted(module.copy(body = body), bankAnnotation = Some(annotation)))
    }

    val namespace = Namespace(module)
    val memoryName = namespace.newName(s"__v2_indexed_${request.leaf}")
    val constantReaders = (0 until depth).map(index => s"r$index")
    val incReader = "r_inc"
    val decReader = "r_dec"
    val normalWriters = Seq("inc", "dec")
    val resetWriters = if (activeReset)
      (0 until depth).map(index => s"reset$index") else Seq.empty
    val memory = DefMemory(orderedRegisters.head.info, memoryName,
      UIntType(IntWidth(width)), depth,
      writeLatency = 1, readLatency = 0,
      readers = constantReaders ++ Seq(incReader, decReader),
      writers = normalWriters ++ resetWriters,
      readwriters = Seq.empty, ReadUnderWrite.Old)

    val constantData = members.iterator.map(member =>
      member.update.reg.name -> portField(memory,
        constantReaders(member.inc.index), "data", SourceFlow)).toMap

    def rewriteExpression(value: Expression): Expression = value match {
      case WRef(name, _, _, _) if constantData.contains(name) => constantData(name)
      case other => other.mapExpr(rewriteExpression)
    }
    def rewriteStatement(statement: Statement): Statement = statement match {
      case register: DefRegister if registerNames(register.name) => EmptyStmt
      case Connect(_, WRef(name, _, _, _), _) if registerNames(name) => EmptyStmt
      case other => other.mapStmt(rewriteStatement).mapExpr(rewriteExpression)
    }

    val addressWidth = math.max(1, BigInt(depth - 1).bitLength)
    val zeroVector = UIntLiteral(0, IntWidth(depth))
    val incEnable = and(rewriteExpression(incCommon),
      neq(rewriteExpression(incVector), zeroVector))
    val decEnable = and(rewriteExpression(decCommon),
      neq(rewriteExpression(decVector), zeroVector))
    val rewrittenIncAddress = rewriteExpression(incAddress)
    val rewrittenDecAddress = rewriteExpression(decAddress)
    val oldInc = portField(memory, incReader, "data", SourceFlow)
    val oldDec = portField(memory, decReader, "data", SourceFlow)
    val collision = and(incEnable, and(decEnable,
      eq(rewrittenIncAddress, rewrittenDecAddress)))
    val incData = wrapAdd(oldInc, One, width)
    // The decrement port is chronologically last.  On a same-address
    // increment+decrement it must write old+1-1, not old-1.
    val decData = wrapSub(wrapAdd(oldDec, collision, width), One, width)
    val clock = rewriteExpression(orderedRegisters.head.clock)

    val readerConnects = constantReaders.zipWithIndex.flatMap {
      case (port, index) => Seq(
        Connect(NoInfo, portField(memory, port, "addr", SinkFlow),
          UIntLiteral(index, IntWidth(addressWidth))),
        Connect(NoInfo, portField(memory, port, "en", SinkFlow), One),
        Connect(NoInfo, portField(memory, port, "clk", SinkFlow), clock))
    } ++ Seq(
      Connect(NoInfo, portField(memory, incReader, "addr", SinkFlow), rewrittenIncAddress),
      Connect(NoInfo, portField(memory, incReader, "en", SinkFlow), One),
      Connect(NoInfo, portField(memory, incReader, "clk", SinkFlow), clock),
      Connect(NoInfo, portField(memory, decReader, "addr", SinkFlow), rewrittenDecAddress),
      Connect(NoInfo, portField(memory, decReader, "en", SinkFlow), One),
      Connect(NoInfo, portField(memory, decReader, "clk", SinkFlow), clock))

    def writerConnects(port: String, address: Expression, enable: Expression,
        data: Expression): Seq[Statement] = Seq(
      Connect(NoInfo, portField(memory, port, "addr", SinkFlow), address),
      Connect(NoInfo, portField(memory, port, "en", SinkFlow), enable),
      Connect(NoInfo, portField(memory, port, "clk", SinkFlow), clock),
      Connect(NoInfo, portField(memory, port, "data", SinkFlow), data),
      Connect(NoInfo, portField(memory, port, "mask", SinkFlow), One))

    val normalWriterConnects =
      writerConnects("inc", rewrittenIncAddress, incEnable, incData) ++
      writerConnects("dec", rewrittenDecAddress, decEnable, decData)
    val reset = rewriteExpression(orderedRegisters.head.reset)
    val resetWriterConnects = resetWriters.zipWithIndex.flatMap {
      case (port, index) => writerConnects(port,
        UIntLiteral(index, IntWidth(addressWidth)), reset,
        UIntLiteral(0, IntWidth(width)))
    }

    val body = Block(Seq(memory, rewriteStatement(module.body)) ++
      readerConnects ++ normalWriterConnects ++ resetWriterConnects)
    val annotation = StateArrayStorageAnnotation(module.name, request.leaf,
      memoryName, depth, width, Seq("data"), Seq(width),
      constantReaders.size + 2)
    Right(Lifted(module.copy(body = body), memoryAnnotation = Some(annotation)))
  }

  override def execute(state: CircuitState): CircuitState = {
    val enabled = state.annotations.collectFirst {
      case EssentOptionsAnnotation(options) => options.simdV2
    }.getOrElse(false)
    val config = state.annotations.collectFirst {
      case annotation: IndexedCounterStateLiftConfigAnnotation => annotation
    }
    val bankConfig = state.annotations.collectFirst {
      case annotation: IndexedCounterBankLiftConfigAnnotation => annotation
    }
    val selectedMemory = config.map(_.families).getOrElse(configuredFamilies)
    val selectedBanks = bankConfig.map(_.families).getOrElse(configuredBankFamilies)
    val memoryMinimumDepth = config.map(_.minimumDepth).getOrElse(16)
    val bankMinimumDepth = bankConfig.map(_.minimumDepth).getOrElse(16)
    if (!enabled || (selectedMemory.isEmpty && selectedBanks.isEmpty)) return state
    require(memoryMinimumDepth >= 2 && bankMinimumDepth >= 2,
      s"indexed counter minimum depth must be at least 2, got " +
        s"memory=$memoryMinimumDepth bank=$bankMinimumDepth")
    require((selectedMemory intersect selectedBanks).isEmpty,
      s"indexed counter families cannot select both memory and bank storage: " +
        s"${(selectedMemory intersect selectedBanks).toSeq.sorted.mkString(",")}")

    val requests = selectedMemory.toSeq.sorted.map(value =>
      (parseRequest(value), false, memoryMinimumDepth)) ++
      selectedBanks.toSeq.sorted.map(value =>
        (parseRequest(value), true, bankMinimumDepth))
    val annotations = mutable.ArrayBuffer[firrtl.annotations.Annotation]()
    val modules = state.circuit.modules.map {
      case original: Module =>
        requests.filter { case (request, _, _) => applies(request, original.name) }
          .foldLeft(original) {
          case (current, (request, banked, minimumDepth)) =>
            liftFamily(current, request, minimumDepth, banked) match {
              case Right(lifted) =>
                lifted.memoryAnnotation.foreach { annotation =>
                  annotations += annotation
                  println(s"[v2-indexed-state] lifted ${original.name}.${request.leaf}: " +
                    s"depth=${annotation.depth} width=${annotation.packedWidth} " +
                    s"reads=${annotation.readPorts} writes=2+reset")
                }
                lifted.bankAnnotation.foreach { annotation =>
                  annotations += annotation
                  println(s"[v2-indexed-bank] lifted ${original.name}.${request.leaf}: " +
                    s"depth=${annotation.membersByIndex.size} width=1 " +
                    s"banks=${annotation.banks.size}")
                }
                lifted.module
              case Left(reason) =>
                // A leaf-only request legitimately visits many modules.  Log
                // only modules that actually contain at least two matching
                // registers, avoiding thousands of discovery-only lines.
                var matches = 0
                def count(statement: Statement): Unit = statement match {
                  case register: DefRegister
                      if familyOrdinal(register.name, request.leaf).isDefined => matches += 1
                  case other => other.foreachStmt(count)
                }
                count(current.body)
                if (matches >= 2)
                  println(s"[v2-indexed-state] skipped ${original.name}.${request.leaf}: $reason")
                current
            }
        }
      case other => other
    }
    state.copy(circuit = state.circuit.copy(modules = modules),
      annotations = state.annotations ++ annotations)
  }
}
