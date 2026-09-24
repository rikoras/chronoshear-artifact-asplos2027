package essent.simd.v2

import essent.EssentOptionsAnnotation
import firrtl._
import firrtl.annotations.NoTargetAnnotation
import firrtl.ir._
import firrtl.options.Dependency

import scala.collection.mutable

/** Explicit opt-in for packing Reg(Vec(UInt<1>)) state into <=64-bit banks.
  * A selector may be a leaf (`flight`) or module-qualified
  * (`TLFIFOFixer_2.flight`).
  */
case class BitsetStateLiftConfigAnnotation(
    registers: Set[String],
    minimumDepth: Int = 8) extends NoTargetAnnotation

/** Recover an aggregate one-bit state vector as a small number of physical
  * UInt banks while indexed writes and constant-entry reads are still
  * visible.
  *
  * This targets structures such as TLFIFOFixer's `flight`: Chisel describes
  * one indexed bitset, but RemoveAccesses otherwise expands it into one
  * mux-hold register per source ID.  The transform changes storage only.  It
  * keeps every write address, write enable, write value, reduction, stall and
  * assertion in RTL, and applies multiple writes in original FIRRTL order.
  *
  * Recognition is deliberately fail-closed.  The selected register must be
  * Reg(Vec(UInt<1>)), have a synchronous all-zero aggregate reset, and have
  * only direct constant/indexed bit writes whose address/control/data do not
  * read the bitset itself.  Constant reads are always supported.  Dynamic
  * reads are accepted only for a single <=64-bit, power-of-two bank whose
  * selector width exactly covers the bank; this is lowered to one dynamic
  * shift and bit extraction without out-of-range ambiguity.  Unsupported
  * whole-vector or wider/multi-bank dynamic reads leave the original RTL
  * unchanged.
  */
object BitsetStateLift extends Transform {
  override def inputForm: CircuitForm = MidForm
  override def outputForm: CircuitForm = MidForm

  override def prerequisites = Seq(Dependency(firrtl.passes.ExpandConnects))
  override def optionalPrerequisites = Seq.empty
  override def optionalPrerequisiteOf = Seq(
    Dependency(IndexedCounterStateLift),
    Dependency(StateArrayLift),
    Dependency(firrtl.passes.RemoveAccesses),
    Dependency(firrtl.passes.ExpandWhens),
    Dependency(firrtl.passes.LowerTypes))
  override def invalidates(a: Transform): Boolean = false

  private val BoolType = UIntType(IntWidth(1))
  private val One = UIntLiteral(1, IntWidth(1))

  private case class Request(module: Option[String], register: String)
  private case class Location(index: Expression, dynamic: Boolean)
  private case class Write(index: Expression, dynamic: Boolean,
      value: Expression, guard: Expression, info: Info)
  private case class Lifted(module: Module,
      annotation: IndexedCounterBankStorageAnnotation)

  private def configuredRegisters: Set[String] =
    sys.env.get("V2_BITSET_BANK_FAMILIES").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).toSet

  private def parseRequest(value: String): Request = {
    val dot = value.lastIndexOf('.')
    if (dot < 0) Request(None, value)
    else Request(Some(value.take(dot)), value.drop(dot + 1))
  }

  private def applies(request: Request, module: String): Boolean =
    request.module.forall(_ == module)

  private def isOne(value: Expression): Boolean = value match {
    case UIntLiteral(number, _) => number == 1
    case _ => false
  }

  private def isZero(value: Expression): Boolean = value match {
    case UIntLiteral(number, _) => number == 0
    case _ => false
  }

  private def and(left: Expression, right: Expression): Expression =
    if (isOne(left)) right
    else if (isOne(right)) left
    else DoPrim(firrtl.PrimOps.And, Seq(left, right), Seq.empty, BoolType)

  private def not(value: Expression): Expression =
    DoPrim(firrtl.PrimOps.Not, Seq(value), Seq.empty, BoolType)

  private def location(value: Expression, root: String): Option[Location] = value match {
    case WSubAccess(WRef(name, _, _, _), index, _: UIntType, _) if name == root =>
      Some(Location(index, dynamic = true))
    case WSubIndex(WRef(name, _, _, _), index, _: UIntType, _) if name == root =>
      Some(Location(UIntLiteral(index,
        IntWidth(math.max(1, BigInt(index).bitLength))), dynamic = false))
    case _ => None
  }

  private def rootedAt(value: Expression, root: String): Boolean = value match {
    case WRef(name, _, _, _) => name == root
    case WSubField(base, _, _, _) => rootedAt(base, root)
    case WSubIndex(base, _, _, _) => rootedAt(base, root)
    case WSubAccess(base, _, _, _) => rootedAt(base, root)
    case _ => false
  }

  private def containsRef(value: Expression, name: String): Boolean = {
    var found = false
    def walk(expression: Expression): Unit = if (!found) expression match {
      case WRef(current, _, _, _) if current == name => found = true
      case other => other.foreachExpr(walk)
    }
    walk(value)
    found
  }

  /** Return why an indexed read cannot be represented by one exact packed
    * bank access.  Requiring an exact power-of-two selector domain avoids
    * assigning a value to FIRRTL's out-of-range vector-read cases.  The
    * <=64-bit restriction also keeps this storage recovery from silently
    * rebuilding a wide multi-bank mux in the combinational graph.
    */
  private def unsupportedDynamicRead(index: Expression, root: String,
      depth: Int): Option[String] = {
    if (depth > 64)
      Some(s"dynamic read requires one <=64-bit bank, got depth $depth")
    else if ((depth & (depth - 1)) != 0)
      Some(s"dynamic read requires power-of-two depth, got $depth")
    else if (containsRef(index, root))
      Some("dynamic read selector reads the bitset")
    else {
      val width = firrtl.bitWidth(index.tpe)
      val expected = BigInt(depth - 1).bitLength
      if (!width.isValidInt || width.toInt != expected)
        Some(s"dynamic read selector width $width does not exactly cover " +
          s"depth $depth (expected $expected)")
      else None
    }
  }

  /** Prove that the aggregate reset wire's final value defines every entry as
    * zero.  IsInvalid is tracked in source order, rather than ignored: an
    * invalidation after a zero connect would correctly fail the proof.
    */
  private def hasAllZeroInit(module: Module, register: DefRegister,
      depth: Int): Boolean = register.init match {
    case WRef(initName, VectorType(UIntType(IntWidth(width)), size), _, _)
        if width == 1 && size == depth =>
      var hasWire = false
      var valid = true
      val zero = Array.fill(depth)(false)

      def indexed(value: Expression): Option[Int] = value match {
        case WSubIndex(WRef(name, _, _, _), index, _, _)
            if name == initName && index >= 0 && index < depth => Some(index)
        case _ => None
      }
      def update(statement: Statement, conditional: Boolean): Unit = statement match {
        case wire: DefWire if wire.name == initName => hasWire = wire.tpe == register.tpe
        case Block(statements) => statements.foreach(update(_, conditional))
        case Conditionally(_, _, conseq, alt) =>
          update(conseq, conditional = true)
          update(alt, conditional = true)
        case Connect(_, loc, value) if rootedAt(loc, initName) =>
          indexed(loc) match {
            case Some(index) if !conditional && isZero(value) => zero(index) = true
            case _ => valid = false
          }
        case PartialConnect(_, loc, _) if rootedAt(loc, initName) => valid = false
        case IsInvalid(_, loc) if rootedAt(loc, initName) =>
          if (conditional) valid = false
          else indexed(loc) match {
            case Some(index) => zero(index) = false
            case None => loc match {
              case WRef(name, _, _, _) if name == initName => java.util.Arrays.fill(zero, false)
              case _ => valid = false
            }
          }
        case other => other.foreachStmt(update(_, conditional))
      }
      update(module.body, conditional = false)
      hasWire && valid && zero.forall(identity)
    case _ => false
  }

  private def liftRegister(module: Module, register: DefRegister,
      minimumDepth: Int): Either[String, Lifted] = {
    val depth = register.tpe match {
      case VectorType(UIntType(IntWidth(width)), size)
          if width == 1 && size >= minimumDepth => size
      case VectorType(UIntType(IntWidth(width)), size) =>
        return Left(s"requires Vec(UInt<1>) depth >= $minimumDepth, got width=$width depth=$size")
      case other => return Left(s"requires Reg(Vec(UInt<1>)), got ${other.serialize}")
    }
    if (isZero(register.reset))
      return Left("requires an active synchronous all-zero reset")
    register.reset.tpe match {
      case UIntType(IntWidth(width)) if width == 1 =>
      case other => return Left(s"reset is not synchronous UInt<1>: ${other.serialize}")
    }
    if (!hasAllZeroInit(module, register, depth))
      return Left("aggregate reset value is not proven all-zero")

    val writes = mutable.ArrayBuffer[Write]()
    var unsupportedWrite: Option[String] = None
    def collect(statement: Statement, guard: Expression): Unit = statement match {
      case Block(statements) => statements.foreach(collect(_, guard))
      case Conditionally(_, predicate, conseq, alt) =>
        collect(conseq, and(guard, predicate))
        collect(alt, and(guard, not(predicate)))
      case Connect(info, loc, value) if rootedAt(loc, register.name) =>
        location(loc, register.name) match {
          case Some(found) => writes += Write(found.index, found.dynamic, value, guard, info)
          case None => unsupportedWrite = Some(s"unsupported write '${loc.serialize}'")
        }
      case PartialConnect(_, loc, _) if rootedAt(loc, register.name) =>
        unsupportedWrite = Some(s"partial write '${loc.serialize}'")
      case IsInvalid(_, loc) if rootedAt(loc, register.name) =>
        unsupportedWrite = Some(s"invalid write '${loc.serialize}'")
      case other => other.foreachStmt(collect(_, guard))
    }
    collect(module.body, One)
    unsupportedWrite.foreach(reason => return Left(reason))
    if (writes.isEmpty) return Left("has no indexed writes")
    writes.foreach { write =>
      if (firrtl.bitWidth(write.value.tpe) != 1)
        return Left(s"write value '${write.value.serialize}' is not one bit")
      if (Seq(write.index, write.value, write.guard).exists(
          containsRef(_, register.name)))
        return Left("write address/control/data reads the bitset")
      if (!write.dynamic) write.index match {
        case UIntLiteral(index, _) if index >= 0 && index < depth =>
        case _ => return Left(s"constant write address is outside 0..${depth - 1}")
      }
    }

    // Dynamic reads are packed only when they map to one exact machine-word
    // bank.  This admits Rob.rob_val[rob_tail] and its other five-bit indexed
    // consumers, while a 128-entry table or a selector with spare encodings
    // remains untouched.
    var unsupportedRead: Option[String] = None
    def readExpression(value: Expression): Unit = if (unsupportedRead.isEmpty) value match {
      case WSubIndex(WRef(name, _, _, _), index, _, _) if name == register.name =>
        if (index < 0 || index >= depth)
          unsupportedRead = Some(s"constant read index $index is outside 0..${depth - 1}")
      case WSubAccess(WRef(name, _, _, _), index, _, _) if name == register.name =>
        unsupportedDynamicRead(index, register.name, depth).foreach { reason =>
          unsupportedRead = Some(s"dynamic read '${value.serialize}': $reason")
        }
      case WRef(name, _, _, _) if name == register.name =>
        unsupportedRead = Some(s"whole-vector read '$name'")
      case other => other.foreachExpr(readExpression)
    }
    def readStatement(statement: Statement): Unit = if (unsupportedRead.isEmpty) statement match {
      case Block(statements) => statements.foreach(readStatement)
      case Conditionally(_, predicate, conseq, alt) =>
        readExpression(predicate); readStatement(conseq); readStatement(alt)
      case Connect(_, loc, value) if location(loc, register.name).isDefined =>
        location(loc, register.name).foreach(found => readExpression(found.index))
        readExpression(value)
      case PartialConnect(_, loc, value) if location(loc, register.name).isDefined =>
        location(loc, register.name).foreach(found => readExpression(found.index))
        readExpression(value)
      case current: DefRegister if current.name == register.name =>
        readExpression(current.clock); readExpression(current.reset)
      case Connect(_, loc, value) => readExpression(loc); readExpression(value)
      case PartialConnect(_, loc, value) => readExpression(loc); readExpression(value)
      case node: DefNode => readExpression(node.value)
      case current: DefRegister =>
        readExpression(current.clock); readExpression(current.reset); readExpression(current.init)
      case print: Print =>
        readExpression(print.clk); readExpression(print.en); print.args.foreach(readExpression)
      case stop: Stop => readExpression(stop.clk); readExpression(stop.en)
      case verification: Verification =>
        readExpression(verification.clk); readExpression(verification.pred)
        readExpression(verification.en)
      case other =>
        other.foreachExpr(readExpression)
        other.foreachStmt(readStatement)
    }
    readStatement(module.body)
    unsupportedRead.foreach(reason => return Left(reason))

    val namespace = Namespace(module)
    // Match LowerTypes' collision rule so the logical entry names are the
    // same names an untouched scalar module would have produced.  For the
    // TLFIFOFixer module that also owns aggregate `flight_1`, this correctly
    // selects flight__0 ... flight__15.
    var logicalPrefix = register.name
    while ((0 until depth).exists(index => namespace.contains(s"${logicalPrefix}_$index")))
      logicalPrefix += "_"
    val members = (0 until depth).map(index => s"${logicalPrefix}_$index")
    members.foreach { member =>
      require(namespace.newName(member) == member,
        s"failed to reserve logical bitset projection '$member'")
    }

    case class Bank(name: String, tpe: UIntType, source: WRef, sink: WRef,
        definition: DefRegister, low: Int, size: Int)
    val banks = (0 until depth).grouped(64).zipWithIndex.map {
      case (indices, bankIndex) =>
        val chunk = indices.toSeq
        val bankType = UIntType(IntWidth(chunk.size))
        val bankName = namespace.newName(
          s"__v2_bitset_${register.name}_bank_$bankIndex")
        val source = WRef(bankName, bankType, RegKind, SourceFlow)
        val sink = WRef(bankName, bankType, RegKind, SinkFlow)
        val definition = DefRegister(register.info, bankName, bankType,
          register.clock, register.reset, UIntLiteral(0, IntWidth(chunk.size)))
        Bank(bankName, bankType, source, sink, definition, chunk.head, chunk.size)
    }.toSeq

    val memberRefs = members.zipWithIndex.map { case (member, index) =>
      val bank = banks(index / 64)
      val bit = index - bank.low
      val value = DoPrim(firrtl.PrimOps.Bits, Seq(bank.source),
        Seq(BigInt(bit), BigInt(bit)), BoolType)
      member -> (DefNode(register.info, member, value),
        WRef(member, BoolType, NodeKind, SourceFlow))
    }.toMap

    def rewriteExpression(value: Expression): Expression = value match {
      case WSubIndex(WRef(name, _, _, _), index, _, flow) if name == register.name =>
        memberRefs(members(index))._2.copy(flow = flow)
      case WSubAccess(WRef(name, _, _, _), index, _, _) if name == register.name =>
        require(banks.size == 1,
          s"dynamic bitset read survived proof with ${banks.size} banks: ${value.serialize}")
        val rewrittenIndex = rewriteExpression(index)
        unsupportedDynamicRead(rewrittenIndex, register.name, depth).foreach { reason =>
          throw new IllegalStateException(
            s"unsupported dynamic bitset read survived proof: ${value.serialize}: $reason")
        }
        val bank = banks.head
        val shifted = DoPrim(firrtl.PrimOps.Dshr,
          Seq(bank.source, rewrittenIndex), Seq.empty, bank.tpe)
        DoPrim(firrtl.PrimOps.Bits, Seq(shifted), Seq(BigInt(0), BigInt(0)), BoolType)
      case WRef(name, _, _, _) if name == register.name =>
        throw new IllegalStateException(s"whole bitset read survived proof: $name")
      case other => other.mapExpr(rewriteExpression)
    }

    def rewriteStatement(statement: Statement): Statement = statement match {
      case current: DefRegister if current.name == register.name => EmptyStmt
      case Connect(_, loc, _) if location(loc, register.name).isDefined => EmptyStmt
      case PartialConnect(_, loc, _) if location(loc, register.name).isDefined => EmptyStmt
      case other => other.mapStmt(rewriteStatement).mapExpr(rewriteExpression)
    }

    def rawMask(write: Write, bank: Bank): Either[String, Expression] = {
      val zero = UIntLiteral(0, IntWidth(bank.size))
      if (!write.dynamic) write.index match {
        case UIntLiteral(index, _) if index >= bank.low && index < bank.low + bank.size =>
          Right(UIntLiteral(BigInt(1) << (index.toInt - bank.low), IntWidth(bank.size)))
        case UIntLiteral(_, _) => Right(zero)
        case _ => Left("non-literal constant write address")
      } else {
        val rewrittenIndex = rewriteExpression(write.index)
        val addressWidth = firrtl.bitWidth(rewrittenIndex.tpe)
        if (!addressWidth.isValidInt || addressWidth <= 0 || addressWidth > 12)
          Left(s"indexed write address width $addressWidth is outside 1..12")
        else {
          val shiftedWidth = BigInt(1) << addressWidth.toInt
          if (shiftedWidth < depth)
            Left(s"indexed write address width $addressWidth cannot cover depth $depth")
          else {
            val shiftedType = UIntType(IntWidth(shiftedWidth))
            val shifted = DoPrim(firrtl.PrimOps.Dshl,
              Seq(One, rewrittenIndex), Seq.empty, shiftedType)
            val fullType = UIntType(IntWidth(depth))
            val full = DoPrim(firrtl.PrimOps.Bits, Seq(shifted),
              Seq(BigInt(depth - 1), BigInt(0)), fullType)
            Right(DoPrim(firrtl.PrimOps.Bits, Seq(full),
              Seq(BigInt(bank.low + bank.size - 1), BigInt(bank.low)), bank.tpe))
          }
        }
      }
    }

    val bankUpdates = banks.map { bank =>
      val zero = UIntLiteral(0, IntWidth(bank.size))
      val next = writes.foldLeft[Either[String, Expression]](Right(bank.source)) {
        case (Left(reason), _) => Left(reason)
        case (Right(previous), write) => rawMask(write, bank).map { raw =>
          val guard = rewriteExpression(write.guard)
          val mask = if (isOne(guard)) raw else Mux(guard, raw, zero, bank.tpe)
          val cleared = DoPrim(firrtl.PrimOps.And, Seq(previous,
            DoPrim(firrtl.PrimOps.Not, Seq(mask), Seq.empty, bank.tpe)),
            Seq.empty, bank.tpe)
          val writeValue = rewriteExpression(write.value)
          val set = Mux(writeValue, mask, zero, bank.tpe)
          DoPrim(firrtl.PrimOps.Or, Seq(cleared, set), Seq.empty, bank.tpe)
        }
      }
      next match {
        case Right(value) => Connect(NoInfo, bank.sink, value)
        case Left(reason) => return Left(reason)
      }
    }

    val projectionNodes = members.map(memberRefs(_)._1)
    val body = Block(banks.map(_.definition) ++ projectionNodes ++
      Seq(rewriteStatement(module.body)) ++ bankUpdates)
    val annotation = IndexedCounterBankStorageAnnotation(module.name,
      register.name, banks.map(_.name), members)
    Right(Lifted(module.copy(body = body), annotation))
  }

  override def execute(state: CircuitState): CircuitState = {
    val enabled = state.annotations.collectFirst {
      case EssentOptionsAnnotation(options) => options.simdV2
    }.getOrElse(false)
    val config = state.annotations.collectFirst {
      case annotation: BitsetStateLiftConfigAnnotation => annotation
    }
    val selected = config.map(_.registers).getOrElse(configuredRegisters)
    val minimumDepth = config.map(_.minimumDepth).getOrElse(8)
    if (!enabled || selected.isEmpty) return state
    require(minimumDepth >= 2,
      s"bitset bank minimum depth must be at least 2, got $minimumDepth")

    val requests = selected.toSeq.sorted.map(parseRequest)
    val annotations = mutable.ArrayBuffer[IndexedCounterBankStorageAnnotation]()
    val modules = state.circuit.modules.map {
      case original: Module =>
        requests.filter(request => applies(request, original.name)).foldLeft(original) {
          case (current, request) =>
            val registers = mutable.ArrayBuffer[DefRegister]()
            def find(statement: Statement): Unit = statement match {
              case register: DefRegister if register.name == request.register =>
                registers += register
              case other => other.foreachStmt(find)
            }
            find(current.body)
            registers.toSeq match {
              case Seq(register) => liftRegister(current, register, minimumDepth) match {
                case Right(lifted) =>
                  annotations += lifted.annotation
                  println(s"[v2-bitset-bank] lifted ${current.name}.${request.register}: " +
                    s"depth=${lifted.annotation.membersByIndex.size} " +
                    s"banks=${lifted.annotation.banks.size}")
                  lifted.module
                case Left(reason) =>
                  println(s"[v2-bitset-bank] skipped ${current.name}.${request.register}: $reason")
                  current
              }
              case Seq() => current
              case _ =>
                println(s"[v2-bitset-bank] skipped ${current.name}.${request.register}: " +
                  s"found ${registers.size} definitions")
                current
            }
        }
      case other => other
    }
    state.copy(circuit = state.circuit.copy(modules = modules),
      annotations = state.annotations ++ annotations)
  }
}
