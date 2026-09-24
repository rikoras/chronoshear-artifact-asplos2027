package essent.simd.v2

import essent.EssentOptionsAnnotation
import firrtl._
import firrtl.annotations.NoTargetAnnotation
import firrtl.ir._
import firrtl.options.Dependency
import firrtl.passes.MemPortUtils

import scala.collection.mutable

/** Descriptive discovery result, retained for diagnostics even when the
  * candidate fails a lifting check.  `writeSites` counts pre-RemoveAccesses
  * source-level write locations, not the one-hot locations produced later.
  */
case class StateArrayCandidateAnnotation(
    module: String,
    register: String,
    depth: Int,
    fields: Seq[String],
    fieldWidths: Map[String, Int],
    writeSites: Map[String, Int]) extends NoTargetAnnotation

/** Identifies a compiler-owned packed state memory after the aggregate
  * register has been rewritten.  Ordinary source RTL memories use the same
  * chronological backend contract without this annotation; this metadata
  * additionally maps a packed backing to the untouched aggregate-register
  * fields for differential checking.
  */
case class StateArrayStorageAnnotation(
    module: String,
    register: String,
    memory: String,
    depth: Int,
    packedWidth: Int,
    fields: Seq[String],
    fieldWidths: Seq[Int],
    readPorts: Int) extends NoTargetAnnotation

/** Programmatic equivalent of the two bring-up environment variables.  Tests
  * and future frontends can select a lift without mutating process-global
  * environment state. */
case class StateArrayLiftConfigAnnotation(
    registers: Set[String],
    fields: Set[String],
    fieldGroups: Seq[Set[String]] = Seq.empty,
    autoPack: Boolean = false,
    autoPackRegisters: Set[String] = Set.empty) extends NoTargetAnnotation

/** Lift selected leaves of Reg(Vec(entries, Bundle)) into one packed,
  * combinational-read/synchronous-write state memory while dynamic accesses
  * still exist.  Later FIRRTL passes preserve the explicit address ports
  * instead of expanding every entry into an unrelated mux-hold recurrence.
  *
  * Selection is deliberately explicit during bring-up:
  *
  *   V2_STATE_ARRAY_LIFT=rob_uop
  *   V2_STATE_ARRAY_FIELDS=uopc,is_rvc,ftq_idx,...
  *
  * The field list is atomic.  If any requested leaf has another write shape,
  * a non-UInt type, a different guard/address, or an aggregate use that cannot
  * be rewritten exactly, no field is lifted.  Whole-vector synchronous reset
  * is supported when every leaf is lifted: reset becomes one final-priority
  * memory write per entry, preserving register reset priority exactly.
  */
object StateArrayLift extends Transform {
  override def inputForm: CircuitForm = MidForm
  override def outputForm: CircuitForm = MidForm

  // ExpandConnects gives one leaf Connect per Bundle field, but dynamic Vec
  // accesses are still present.  RemoveAccesses is the irreversible point
  // that turns one indexed port into entries x fields muxes.
  override def prerequisites = Seq(Dependency(firrtl.passes.ExpandConnects))
  override def optionalPrerequisites = Seq.empty
  override def optionalPrerequisiteOf = Seq(
    Dependency(firrtl.passes.RemoveAccesses),
    Dependency(firrtl.passes.ExpandWhens),
    Dependency(firrtl.passes.LowerTypes))
  override def invalidates(a: Transform): Boolean = false

  private val BoolType = UIntType(IntWidth(1))
  private val One = UIntLiteral(1, IntWidth(1))
  private val GroundField = "data"

  private case class LeafDesc(path: String, tpe: Type)
  private case class RegisterShape(
      elem: BundleType,
      dimensions: Vector[Int],
      ground: Boolean) {
    val depth: Int = dimensions.product
    val nested: Boolean = dimensions.size > 1
  }
  private case class IndexPart(index: Expression, size: Int, dynamic: Boolean)
  private case class IndexedLeaf(
      root: String,
      field: String,
      index: Expression,
      dynamic: Boolean)
  private case class WriteSite(
      field: String,
      index: Expression,
      dynamic: Boolean,
      value: Expression,
      guard: Expression,
      info: Info)
  private case class Lifted(module: Module, annotation: StateArrayStorageAnnotation)

  private def selectedNames: Set[String] =
    sys.env.get("V2_STATE_ARRAY_LIFT").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).toSet

  private def requestedFields: Set[String] =
    sys.env.get("V2_STATE_ARRAY_FIELDS").toSeq
      .flatMap(_.split(',')).map(_.trim).filter(_.nonEmpty).toSet

  /** Multiple independently packed memories may be carved from one aggregate
    * register.  Groups are separated by ';', fields inside a group by ',':
    *
    *   V2_STATE_ARRAY_FIELD_GROUPS=tag,conf,p_cnt;age;s_cnt
    *
    * This handles structures whose fields have different write-port shapes
    * without introducing packed-word masks or read/modify/write host magic.
    */
  private def requestedFieldGroups: Seq[Set[String]] =
    sys.env.get("V2_STATE_ARRAY_FIELD_GROUPS").toSeq
      .flatMap(_.split(';')).map { group =>
        group.split(',').map(_.trim).filter(_.nonEmpty).toSet
      }.filter(_.nonEmpty)

  private def automaticPackingNames: Set[String] =
    sys.env.get("V2_STATE_ARRAY_AUTO_PACK").toSeq.flatMap { raw =>
      raw.split(',').map(_.trim).filter(_.nonEmpty).map { value =>
        if (value == "1" || value.equalsIgnoreCase("true") ||
            value.equalsIgnoreCase("on")) "*" else value
      }
    }.toSet

  private def leafFields(tpe: Type, prefix: Vector[String] = Vector.empty): Vector[LeafDesc] = tpe match {
    case BundleType(fields) =>
      fields.toVector.flatMap(f => leafFields(f.tpe, prefix :+ f.name))
    case _: UIntType | _: SIntType | ClockType | AsyncResetType | ResetType | AnalogType(_) =>
      Vector(LeafDesc(prefix.mkString("."), tpe))
    case VectorType(elem, size) =>
      (0 until size).toVector.flatMap(i => leafFields(elem, prefix :+ i.toString))
    case _ => Vector.empty
  }

  private def registerShape(tpe: Type): Option[RegisterShape] = {
    def peel(current: Type, dimensions: Vector[Int]): Option[RegisterShape] = current match {
      case VectorType(elem, size) if size >= 2 => peel(elem, dimensions :+ size)
      case bundle: BundleType if dimensions.nonEmpty =>
        Some(RegisterShape(bundle, dimensions, ground = false))
      case ground @ (_: UIntType | _: SIntType) if dimensions.nonEmpty =>
        Some(RegisterShape(
          BundleType(Seq(Field(GroundField, Default, ground))),
          dimensions,
          ground = true))
      case _ => None
    }
    peel(tpe, Vector.empty)
  }

  private def indexWidth(size: Int): Int =
    math.max(1, BigInt(size - 1).bitLength)

  private def fitIndex(index: Expression, width: Int): Expression = {
    val current = firrtl.bitWidth(index.tpe).toInt
    if (current == width) index
    else if (current < width)
      DoPrim(firrtl.PrimOps.Pad, Seq(index), Seq(BigInt(width)), UIntType(IntWidth(width)))
    else
      DoPrim(firrtl.PrimOps.Bits, Seq(index), Seq(BigInt(width - 1), BigInt(0)),
        UIntType(IntWidth(width)))
  }

  /** Flatten root[i][j] into one address while dynamic accesses still carry
    * their original Vec dimensions.  Nested state arrays currently require
    * power-of-two dimensions, which makes concatenation the exact row-major
    * address mapping used by FIRRTL's later RemoveAccesses pass. */
  private def flattenIndices(parts: List[IndexPart]): Option[Expression] = parts match {
    case Nil => None
    case part :: Nil => Some(part.index)
    case many if many.forall(part => (part.size & (part.size - 1)) == 0) =>
      Some(many.map(part => fitIndex(part.index, indexWidth(part.size))).reduceLeft {
        (outer, inner) =>
          val width = firrtl.bitWidth(outer.tpe) + firrtl.bitWidth(inner.tpe)
          DoPrim(firrtl.PrimOps.Cat, Seq(outer, inner), Nil, UIntType(IntWidth(width)))
      })
    case _ => None
  }

  /** Recover root[index]...[index].field from dynamic or constant accesses.
    * The suffix and Vec dimensions are accumulated structurally; a nested
    * Vec becomes one row-major memory address rather than N unrelated leaves.
    */
  private def indexedLeaf(e: Expression): Option[IndexedLeaf] = {
    val resultType = e.tpe
    def loop(x: Expression, suffix: List[String], indices: List[IndexPart]): Option[IndexedLeaf] = x match {
      case WSubField(base, name, _, _) => loop(base, name :: suffix, indices)
      case WSubAccess(base, index, _, _) => base.tpe match {
        case VectorType(_, size) =>
          loop(base, suffix, IndexPart(index, size, dynamic = true) :: indices)
        case _ => None
      }
      case WSubIndex(base, index, _, _) => base.tpe match {
        case VectorType(_, size) =>
          val literal = UIntLiteral(index, IntWidth(indexWidth(size)))
          loop(base, suffix, IndexPart(literal, size, dynamic = false) :: indices)
        case _ => None
      }
      case WRef(root, _, _, _) if indices.nonEmpty =>
        val field = if (suffix.nonEmpty) Some(suffix.mkString(".")) else resultType match {
          case _: UIntType | _: SIntType => Some(GroundField)
          case _ => None
        }
        for {
          name <- field
          index <- flattenIndices(indices)
        } yield IndexedLeaf(root, name, index, indices.exists(_.dynamic))
      case _ => None
    }
    loop(e, Nil, Nil)
  }

  private def isOne(e: Expression): Boolean = e match {
    case UIntLiteral(v, _) => v == 1
    case _ => false
  }

  private def and(a: Expression, b: Expression): Expression =
    if (isOne(a)) b else if (isOne(b)) a
    else DoPrim(firrtl.PrimOps.And, Seq(a, b), Nil, BoolType)

  private def not(a: Expression): Expression =
    DoPrim(firrtl.PrimOps.Not, Seq(a), Nil, BoolType)

  private def collectWrites(
      s: Statement,
      guard: Expression,
      roots: Set[String],
      out: mutable.Map[String, mutable.ArrayBuffer[WriteSite]]): Unit = s match {
    case Block(stmts) => stmts.foreach(collectWrites(_, guard, roots, out))
    case Conditionally(_, pred, conseq, alt) =>
      collectWrites(conseq, and(guard, pred), roots, out)
      collectWrites(alt, and(guard, not(pred)), roots, out)
    case Connect(info, loc, value) => indexedLeaf(loc).foreach { leaf =>
      if (roots.contains(leaf.root))
        out.getOrElseUpdate(leaf.root, mutable.ArrayBuffer()) +=
          WriteSite(leaf.field, leaf.index, leaf.dynamic, value, guard, info)
    }
    case PartialConnect(info, loc, value) => indexedLeaf(loc).foreach { leaf =>
      if (roots.contains(leaf.root))
        out.getOrElseUpdate(leaf.root, mutable.ArrayBuffer()) +=
          WriteSite(leaf.field, leaf.index, leaf.dynamic, value, guard, info)
    }
    case other => other.foreachStmt(collectWrites(_, guard, roots, out))
  }

  private def containsRef(e: Expression, name: String): Boolean = {
    var found = false
    def walk(x: Expression): Unit = if (!found) x match {
      case WRef(n, _, _, _) if n == name => found = true
      case other => other.foreachExpr(walk)
    }
    walk(e)
    found
  }

  private def literalZero(e: Expression): Boolean = e match {
    case UIntLiteral(v, _) => v == 0
    case _ => false
  }

  private def addrKey(e: Expression): String = s"${e.tpe.serialize}:${e.serialize}"

  /** Conservatively recover packed payload groups without requiring a
    * hand-maintained field list.  Two leaves may share a group only when the
    * source FIRRTL gives them the same ordered write-port addresses and
    * guards.  Data is deliberately not part of the signature: each field has
    * its own wdata, which liftRegister packs after proving that none of it
    * reads the aggregate being replaced.
    *
    * This is an eligibility discovery step, not a relaxed rewrite.  Every
    * resulting group still passes all of liftRegister's fail-closed checks.
    * Keeping the grouping here source-structural prevents semantically equal
    * but differently written enables from being combined accidentally.
    */
  private def automaticFieldGroups(
      reg: DefRegister,
      sites: Seq[WriteSite]): Seq[Set[String]] = {
    val shape = registerShape(reg.tpe).getOrElse(return Seq.empty)
    val leaves = leafFields(shape.elem).filter(_.path.nonEmpty)
    val activeReset = !literalZero(reg.reset)
    val byField = sites.groupBy(_.field)
    val eligible = leaves.filter { leaf =>
      val width = firrtl.bitWidth(leaf.tpe).toInt
      val writes = byField.getOrElse(leaf.path, Nil)
      leaf.tpe.isInstanceOf[UIntType] && width >= 1 && width <= 64 &&
        writes.nonEmpty && !writes.exists(write => containsRef(write.value, reg.name))
    }

    // A partially lifted active-reset aggregate has no residual reset value
    // with the same type.  The existing exact rule therefore permits auto
    // packing only when one <=64-bit group removes the entire register.
    if (activeReset) {
      val signatures = eligible.map { leaf =>
        byField(leaf.path).map(write =>
          s"${write.dynamic}:${addrKey(write.index)}:${write.guard.serialize}")
      }.distinct
      val width = eligible.map(leaf => firrtl.bitWidth(leaf.tpe).toInt).sum
      if (eligible.size == leaves.size && signatures.size == 1 && width <= 64)
        return Seq(eligible.map(_.path).toSet)
      return Seq.empty
    }

    val samePorts = mutable.LinkedHashMap[Seq[String], mutable.ArrayBuffer[LeafDesc]]()
    eligible.foreach { leaf =>
      val signature = byField(leaf.path).map(write =>
        s"${write.dynamic}:${addrKey(write.index)}:${write.guard.serialize}")
      samePorts.getOrElseUpdate(signature, mutable.ArrayBuffer()) += leaf
    }
    val groups = mutable.ArrayBuffer[Set[String]]()
    samePorts.foreach { case (signature, compatible) =>
      // A lone multi-write control leaf (for example a branch mask updated
      // once per resident entry) creates many chronological ports without
      // reducing any payload recurrence family.  Leave it in RTL unless it
      // shares the exact ports with another field; explicit field groups can
      // still request such a lift when measurements justify it.
      if (compatible.size == 1 && signature.size > 1) {
        // Intentionally skipped.
      } else {
        var current = mutable.ArrayBuffer[String]()
        var currentWidth = 0
        compatible.foreach { leaf =>
          val width = firrtl.bitWidth(leaf.tpe).toInt
          if (current.nonEmpty && currentWidth + width > 64) {
            groups += current.toSet
            current = mutable.ArrayBuffer[String]()
            currentWidth = 0
          }
          current += leaf.path
          currentWidth += width
        }
        if (current.nonEmpty) groups += current.toSet
      }
    }
    groups.toSeq
  }

  /** Collect selected-field source reads after ExpandConnects.  Lvalue leaves
    * are excluded explicitly; their address expressions are still traversed.
    * Whole-entry and whole-array reads are reported as unsupported because
    * removing selected fields from the original Bundle would change them.
    */
  private def collectReadAddresses(
      body: Statement,
      root: String,
      selected: Set[String]): Either[String, mutable.LinkedHashMap[String, Expression]] = {
    val reads = mutable.LinkedHashMap[String, Expression]()
    var unsupported: Option[String] = None

    def expr(e: Expression): Unit = if (unsupported.isEmpty) indexedLeaf(e) match {
      case Some(leaf) if leaf.root == root =>
        if (selected.contains(leaf.field)) reads.getOrElseUpdate(addrKey(leaf.index), leaf.index)
        // The address may itself contain a state read; the aggregate root is
        // intentionally not traversed.
        expr(leaf.index)
      case _ => e match {
        case WSubAccess(WRef(n, _, _, _), index, _, _) if n == root =>
          unsupported = Some(s"whole-entry dynamic read '${e.serialize}'")
          expr(index)
        case WSubIndex(WRef(n, _, _, _), _, _, _) if n == root =>
          unsupported = Some(s"whole-entry constant read '${e.serialize}'")
        case WRef(n, _, _, _) if n == root =>
          unsupported = Some(s"whole-array read '${e.serialize}'")
        case other => other.foreachExpr(expr)
      }
    }

    def locIndices(e: Expression): Unit = indexedLeaf(e) match {
      case Some(leaf) if leaf.root == root => expr(leaf.index)
      case _ => e.foreachExpr(locIndices)
    }

    def stmt(s: Statement): Unit = if (unsupported.isEmpty) s match {
      case Block(stmts) => stmts.foreach(stmt)
      case Conditionally(_, pred, conseq, alt) => expr(pred); stmt(conseq); stmt(alt)
      case Connect(_, loc, value) => locIndices(loc); expr(value)
      case PartialConnect(_, loc, value) => locIndices(loc); expr(value)
      case r: DefRegister if r.name == root =>
        expr(r.clock); expr(r.reset) // r.init is the allowed aggregate self reference
      case d: DefNode => expr(d.value)
      case r: DefRegister => expr(r.clock); expr(r.reset); expr(r.init)
      case p: Print => expr(p.clk); expr(p.en); p.args.foreach(expr)
      case st: Stop => expr(st.clk); expr(st.en)
      case v: Verification => expr(v.clk); expr(v.pred); expr(v.en)
      case other =>
        other.foreachExpr(expr)
        other.foreachStmt(stmt)
    }
    stmt(body)
    unsupported.toLeft(reads)
  }

  private def portField(mem: DefMemory, port: String, field: String, flow: Flow): Expression = {
    val memTpe = MemPortUtils.memType(mem)
    val memRef = WRef(mem.name, memTpe, MemKind, SourceFlow)
    val portTpe = firrtl.Utils.field_type(memTpe, port)
    val portRef = WSubField(memRef, port, portTpe, SourceFlow)
    val fieldTpe = firrtl.Utils.field_type(portTpe, field)
    WSubField(portRef, field, fieldTpe, flow)
  }

  private def pack(values: Seq[Expression]): Expression = {
    require(values.nonEmpty)
    def asUInt(value: Expression): Expression = value.tpe match {
      case _: UIntType => value
      case SIntType(width) =>
        DoPrim(firrtl.PrimOps.AsUInt, Seq(value), Nil, UIntType(width))
      case other => throw new IllegalArgumentException(
        s"cannot pack state field of type ${other.serialize}")
    }
    val unsigned = values.map(asUInt)
    unsigned.tail.foldLeft(unsigned.head) { (a, b) =>
      val width = firrtl.bitWidth(a.tpe) + firrtl.bitWidth(b.tpe)
      DoPrim(firrtl.PrimOps.Cat, Seq(a, b), Nil, UIntType(IntWidth(width)))
    }
  }

  /** Remove selected Bundle leaves without renaming or reindexing any
    * residual path.  Nested Bundles are safe because field names remain
    * stable.  A nested Vec cannot be compacted after removing one element
    * without changing every following index, so it remains fail-closed until
    * a sparse-vector representation is defined.
    */
  private def pruneSelectedLeaves(
      elem: BundleType,
      requested: Set[String]): Either[String, BundleType] = {
    def under(path: Vector[String]): Boolean = {
      val prefix = path.mkString(".")
      requested.exists(name => name == prefix || name.startsWith(prefix + "."))
    }

    def loop(tpe: Type, path: Vector[String]): Either[String, Option[Type]] = tpe match {
      case BundleType(fields) =>
        val kept = mutable.ArrayBuffer[Field]()
        fields.foreach { field =>
          loop(field.tpe, path :+ field.name) match {
            case Left(reason) => return Left(reason)
            case Right(Some(child)) => kept += field.copy(tpe = child)
            case Right(None) =>
          }
        }
        if (kept.isEmpty) Right(None) else Right(Some(BundleType(kept.toSeq)))
      case _: VectorType if under(path) =>
        Left(s"nested Vec leaf lifting is not enabled yet (${path.mkString(".")})")
      case _: VectorType => Right(Some(tpe))
      case _ =>
        if (requested.contains(path.mkString("."))) Right(None)
        else Right(Some(tpe))
    }

    loop(elem, Vector.empty).map {
      case Some(bundle: BundleType) => bundle
      case None => BundleType(Seq.empty)
      case Some(other) => throw new IllegalStateException(
        s"Bundle pruning produced ${other.serialize}")
    }
  }

  private def liftRegister(
      m: Module,
      reg: DefRegister,
      sites: Seq[WriteSite],
      requested: Set[String]): Either[String, Lifted] = {
    val shape = registerShape(reg.tpe).getOrElse(return Left(
      s"expected Reg(Vec(..., Bundle|UInt|SInt)), got ${reg.tpe.serialize}"))
    val elem = shape.elem
    val depth = shape.depth
    val ground = shape.ground
    val activeReset = !literalZero(reg.reset)
    if (requested.isEmpty) return Left("V2_STATE_ARRAY_FIELDS is empty (discovery only)")

    val leaves = leafFields(elem).filter(_.path.nonEmpty)
    val byPath = leaves.map(f => f.path -> f).toMap
    val missing = requested -- byPath.keySet
    if (missing.nonEmpty) return Left(s"unknown field(s): ${missing.toSeq.sorted.mkString(",")}")
    val unsupported = requested.toSeq.filterNot { field => byPath(field).tpe match {
      case _: UIntType | _: SIntType => true
      case _ => false
    }}
    if (unsupported.nonEmpty)
      return Left(s"non-integer field(s): ${unsupported.sorted.mkString(",")}")

    val orderedFields = leaves.filter(f => requested.contains(f.path))
    val packedWidth = orderedFields.map(f => firrtl.bitWidth(f.tpe).toInt).sum
    if (packedWidth <= 0 || packedWidth > 64)
      return Left(s"packed width $packedWidth is outside supported range 1..64")

    val byField = sites.groupBy(_.field)
    val writeCounts = orderedFields.map(f => f.path -> byField.getOrElse(f.path, Nil).size)
    if (writeCounts.exists(_._2 == 0))
      return Left(s"requested fields have no write (${writeCounts.filter(_._2 == 0).map(_._1).mkString(",")})")
    if (writeCounts.map(_._2).distinct.size != 1)
      return Left(s"requested fields do not have the same write-port count " +
        s"(${writeCounts.map { case (f, n) => s"$f=$n" }.mkString(",")})")
    val writePortCount = writeCounts.head._2
    // ExpandConnects preserves each field's last-connect order. Pair the Nth
    // write of every selected field into one packed memory port, and require
    // those writes to agree on address and guard. Multiple ports are exact:
    // the chronological backend commits them in FIRRTL port order, with the
    // later port winning when two writes target the same entry.
    val writesByPort = (0 until writePortCount).map { port =>
      orderedFields.map(f => byField(f.path)(port))
    }
    val writes = writesByPort.flatten
    if (writes.exists(w => containsRef(w.value, reg.name)))
      return Left("requested field write data reads the aggregate register")
    writesByPort.zipWithIndex.foreach { case (portWrites, port) =>
      val guards = portWrites.map(_.guard.serialize).distinct
      val addrs = portWrites.map(w => addrKey(w.index)).distinct
      if (guards.size != 1)
        return Left(s"requested fields do not share write-enable on port $port")
      if (addrs.size != 1)
        return Left(s"requested fields do not share write address on port $port")
    }

    val readAddrs = collectReadAddresses(m.body, reg.name, requested) match {
      case Left(reason) => return Left(reason)
      case Right(value) => value
    }
    if (readAddrs.isEmpty) return Left("requested fields have no source reads")

    val reducedElem = pruneSelectedLeaves(elem, requested) match {
      case Left(reason) => return Left(reason)
      case Right(value) => value
    }
    val reducedRegTpe = VectorType(reducedElem, depth)
    // A ground vector has no residual aggregate shell once its synthetic
    // `data` field is selected. Bundle vectors may retain unselected fields.
    val removeWholeRegister = ground || reducedElem.fields.isEmpty
    if (shape.nested && !removeWholeRegister)
      return Left("nested Vec lifting currently requires every leaf")
    if (shape.nested && activeReset)
      return Left("nested Vec lifting does not support active aggregate reset")
    if (activeReset) {
      reg.reset.tpe match {
        case UIntType(IntWidth(width)) if width == 1 =>
        case other => return Left(
          s"only synchronous UInt<1> aggregate reset is supported, got ${other.serialize}")
      }
      if (!removeWholeRegister)
        return Left("active aggregate reset requires lifting every field")
      if (containsRef(reg.init, reg.name))
        return Left("active aggregate reset value reads the aggregate register")
      if (reg.init.tpe != reg.tpe)
        return Left(s"active aggregate reset type ${reg.init.tpe.serialize} " +
          s"does not match ${reg.tpe.serialize}")
    }
    val namespace = Namespace(m)
    val memName = namespace.newName(s"__v2_state_${reg.name}")
    val readerNames = (0 until readAddrs.size).map(i => s"r$i")
    val normalWriterNames = (0 until writePortCount).map(i => s"w$i")
    // Register reset has priority over every ordinary connect regardless of
    // source order.  Appending the per-entry reset ports makes them the final
    // chronological memory ports, so they win every same-address conflict.
    val resetWriterNames = if (activeReset)
      (0 until depth).map(i => s"reset$i") else Seq.empty
    val writerNames = normalWriterNames ++ resetWriterNames
    val mem = DefMemory(reg.info, memName, UIntType(IntWidth(packedWidth)), depth,
      writeLatency = 1, readLatency = 0, readers = readerNames,
      writers = writerNames, readwriters = Seq.empty, ReadUnderWrite.Old)

    val portForAddr = readAddrs.keys.zip(readerNames).toMap
    val dataForAddr = portForAddr.map { case (key, port) =>
      key -> portField(mem, port, "data", SourceFlow)
    }
    val fieldSlice = {
      var high = packedWidth - 1
      orderedFields.map { f =>
        val width = firrtl.bitWidth(f.tpe).toInt
        val lo = high - width + 1
        val result = f.path -> (high, lo, f.tpe)
        high = lo - 1
        result
      }.toMap
    }

    def rewriteExpr(e: Expression): Expression = indexedLeaf(e) match {
      case Some(leaf) if leaf.root == reg.name && requested.contains(leaf.field) =>
        val (hi, lo, tpe) = fieldSlice(leaf.field)
        val width = hi - lo + 1
        val bits = DoPrim(firrtl.PrimOps.Bits, Seq(dataForAddr(addrKey(leaf.index))),
          Seq(BigInt(hi), BigInt(lo)), UIntType(IntWidth(width)))
        tpe match {
          case _: UIntType => bits
          case _: SIntType => DoPrim(firrtl.PrimOps.AsSInt, Seq(bits), Nil, tpe)
          case other => throw new IllegalStateException(
            s"unsupported lifted field type ${other.serialize}")
        }
      case _ => e match {
        case WRef(n, _, kind, flow) if n == reg.name =>
          require(!removeWholeRegister,
            s"unexpected whole-register reference after lifting every field of '$n'")
          WRef(n, reducedRegTpe, kind, flow)
        case WSubAccess(WRef(n, _, kind, rootFlow), index, _, flow) if n == reg.name =>
          require(!removeWholeRegister,
            s"unexpected whole-entry access after lifting every field of '$n'")
          WSubAccess(WRef(n, reducedRegTpe, kind, rootFlow), rewriteExpr(index), reducedElem, flow)
        case WSubIndex(WRef(n, _, kind, rootFlow), index, _, flow) if n == reg.name =>
          require(!removeWholeRegister,
            s"unexpected constant whole-entry access after lifting every field of '$n'")
          WSubIndex(WRef(n, reducedRegTpe, kind, rootFlow), index, reducedElem, flow)
        case WSubField(base, name, tpe, flow) =>
          val rewrittenBase = rewriteExpr(base)
          val rewrittenType = rewrittenBase.tpe match {
            case BundleType(fields) => fields.find(_.name == name).map(_.tpe).getOrElse(tpe)
            case _ => tpe
          }
          WSubField(rewrittenBase, name, rewrittenType, flow)
        case WSubAccess(base, index, tpe, flow) =>
          val rewrittenBase = rewriteExpr(base)
          val rewrittenType = rewrittenBase.tpe match {
            case VectorType(element, _) => element
            case _ => tpe
          }
          WSubAccess(rewrittenBase, rewriteExpr(index), rewrittenType, flow)
        case WSubIndex(base, index, tpe, flow) =>
          val rewrittenBase = rewriteExpr(base)
          val rewrittenType = rewrittenBase.tpe match {
            case VectorType(element, _) => element
            case _ => tpe
          }
          WSubIndex(rewrittenBase, index, rewrittenType, flow)
        case other => other.mapExpr(rewriteExpr)
      }
    }

    def rewriteStmt(s: Statement): Statement = s match {
      case Connect(_, loc, _) if indexedLeaf(loc).exists(l =>
          l.root == reg.name && requested.contains(l.field)) => EmptyStmt
      case PartialConnect(_, loc, _) if indexedLeaf(loc).exists(l =>
          l.root == reg.name && requested.contains(l.field)) => EmptyStmt
      case r: DefRegister if r.name == reg.name =>
        if (removeWholeRegister) EmptyStmt
        else r.copy(tpe = reducedRegTpe, clock = rewriteExpr(r.clock),
          reset = rewriteExpr(r.reset), init = rewriteExpr(r.init))
      case other => other.mapStmt(rewriteStmt).mapExpr(rewriteExpr)
    }

    val readerConnects = readAddrs.values.zip(readerNames).flatMap { case (addr, port) => Seq(
      Connect(NoInfo, portField(mem, port, "addr", SinkFlow), rewriteExpr(addr)),
      Connect(NoInfo, portField(mem, port, "en", SinkFlow), One),
      Connect(NoInfo, portField(mem, port, "clk", SinkFlow), rewriteExpr(reg.clock)))
    }.toSeq
    val writerConnects = writesByPort.zip(normalWriterNames).flatMap { case (portWrites, port) =>
      val writeData = pack(portWrites.map(w => rewriteExpr(w.value)))
      Seq(
        Connect(NoInfo, portField(mem, port, "addr", SinkFlow), rewriteExpr(portWrites.head.index)),
        Connect(NoInfo, portField(mem, port, "en", SinkFlow), rewriteExpr(portWrites.head.guard)),
        Connect(NoInfo, portField(mem, port, "clk", SinkFlow), rewriteExpr(reg.clock)),
        Connect(NoInfo, portField(mem, port, "data", SinkFlow), writeData),
        Connect(NoInfo, portField(mem, port, "mask", SinkFlow), One))
    }

    val resetAddrWidth = math.max(1, BigInt(depth - 1).bitLength)
    val sourceElem = reg.tpe.asInstanceOf[VectorType].tpe
    def resetLeaf(entry: Int, field: LeafDesc): Expression = {
      val indexed = WSubIndex(reg.init, entry, sourceElem, SourceFlow)
      if (ground) indexed
      else field.path.split('.').foldLeft(indexed: Expression) { case (base, name) =>
        val tpe = firrtl.Utils.field_type(base.tpe, name)
        WSubField(base, name, tpe, SourceFlow)
      }
    }
    val resetWriterConnects = resetWriterNames.zipWithIndex.flatMap { case (port, entry) =>
      val resetData = pack(orderedFields.map(f => rewriteExpr(resetLeaf(entry, f))))
      Seq(
        Connect(NoInfo, portField(mem, port, "addr", SinkFlow),
          UIntLiteral(entry, IntWidth(resetAddrWidth))),
        Connect(NoInfo, portField(mem, port, "en", SinkFlow), rewriteExpr(reg.reset)),
        Connect(NoInfo, portField(mem, port, "clk", SinkFlow), rewriteExpr(reg.clock)),
        Connect(NoInfo, portField(mem, port, "data", SinkFlow), resetData),
        Connect(NoInfo, portField(mem, port, "mask", SinkFlow), One))
    }

    val body = Block(Seq(mem, rewriteStmt(m.body)) ++ readerConnects ++
      writerConnects ++ resetWriterConnects)
    val ann = StateArrayStorageAnnotation(m.name, reg.name, memName, depth,
      packedWidth, orderedFields.map(_.path),
      orderedFields.map(f => firrtl.bitWidth(f.tpe).toInt), readerNames.size)
    Right(Lifted(m.copy(body = body), ann))
  }

  override def execute(state: CircuitState): CircuitState = {
    val isV2 = state.annotations.collectFirst {
      case EssentOptionsAnnotation(opt) => opt.simdV2
    }.getOrElse(false)
    val config = state.annotations.collectFirst {
      case a: StateArrayLiftConfigAnnotation => a
    }
    val selected = config.map(_.registers).getOrElse(selectedNames)
    if (!isV2 || selected.isEmpty) return state

    val requestedGroups = config.map { c =>
      if (c.fieldGroups.nonEmpty) c.fieldGroups else Seq(c.fields)
    }.getOrElse {
      val groups = requestedFieldGroups
      if (groups.nonEmpty) groups else Seq(requestedFields)
    }.filter(_.nonEmpty)
    val autoPackNames = config.map { annotation =>
      annotation.autoPackRegisters ++ (if (annotation.autoPack) Set("*") else Set.empty)
    }.getOrElse(automaticPackingNames)
    def autoPack(name: String): Boolean =
      autoPackNames("*") || autoPackNames(name)
    val discovered = mutable.ArrayBuffer[StateArrayCandidateAnnotation]()
    val lifted = mutable.ArrayBuffer[StateArrayStorageAnnotation]()

    val modules = state.circuit.modules.map {
      case original: Module =>
        val regs = mutable.LinkedHashMap[String, DefRegister]()
        def findRegs(s: Statement): Unit = s match {
          case r: DefRegister if selected.contains(r.name) => regs(r.name) = r
          case Block(stmts) => stmts.foreach(findRegs)
          case other => other.foreachStmt(findRegs)
        }
        findRegs(original.body)

        val writes = mutable.Map[String, mutable.ArrayBuffer[WriteSite]]()
        collectWrites(original.body, One, selected, writes)
        for ((name, reg) <- regs) registerShape(reg.tpe) match {
          case Some(shape) =>
            val fields = leafFields(shape.elem).filter(_.path.nonEmpty)
            val counts = fields.iterator.map { f =>
              f.path -> writes.getOrElse(name, mutable.ArrayBuffer()).count(_.field == f.path)
            }.toMap
            discovered += StateArrayCandidateAnnotation(
              original.name, name, shape.depth, fields.map(_.path),
              fields.iterator.map(field =>
                field.path -> firrtl.bitWidth(field.tpe).toInt).toMap,
              counts)
            val single = counts.count(_._2 == 1)
            val multi = counts.count(_._2 > 1)
            val unwritten = counts.count(_._2 == 0)
            println(s"[v2-state-array] discovered ${original.name}.$name: " +
              s"depth=${shape.depth} dimensions=${shape.dimensions.mkString("x")} " +
              s"fields=${fields.size} single-write=$single " +
              s"multi-write=$multi unwritten=$unwritten")
          case None =>
            println(s"[v2-state-array] rejected ${original.name}.$name: " +
              s"expected Vec storage, got ${reg.tpe.serialize}")
        }

        regs.foldLeft(original) { case (beforeRegister, (name, sourceReg)) =>
          val sourceSites = writes.get(name).map(_.toSeq).getOrElse(Seq.empty)
          val groups = if (autoPack(name)) {
            val automatic = automaticFieldGroups(sourceReg, sourceSites)
            val selectedFields = automatic.iterator.flatMap(_.iterator).toSet
            val discoveredFields = registerShape(sourceReg.tpe)
              .map(shape => leafFields(shape.elem).filter(_.path.nonEmpty).map(_.path).toSet)
              .getOrElse(Set.empty[String])
            println(s"[v2-state-array] auto-pack ${original.name}.$name: " +
              s"groups=${automatic.size} selected=${selectedFields.size} " +
              s"skipped=${discoveredFields.size - selectedFields.size}")
            automatic
          } else requestedGroups
          groups.foldLeft(beforeRegister) { case (current, requested) =>
            var currentReg: Option[DefRegister] = None
            def walk(s: Statement): Unit = s match {
              case r: DefRegister if r.name == name => currentReg = Some(r)
              case Block(stmts) => stmts.foreach(walk)
              case other => other.foreachStmt(walk)
            }
            walk(current.body)
            currentReg match {
              case None =>
                println(s"[v2-state-array] not lifted ${current.name}.$name " +
                  s"fields=${requested.toSeq.sorted.mkString(",")}: aggregate register already removed")
                current
              case Some(reg) =>
                val currentWrites = mutable.Map[String, mutable.ArrayBuffer[WriteSite]]()
                collectWrites(current.body, One, Set(name), currentWrites)
                val sites = currentWrites.get(name).map(_.toSeq).getOrElse(Seq.empty[WriteSite])
                liftRegister(current, reg, sites, requested) match {
                  case Right(result) =>
                    lifted += result.annotation
                    println(s"[v2-state-array] lifted ${result.annotation.module}.${result.annotation.register}: " +
                      s"memory=${result.annotation.memory} depth=${result.annotation.depth} " +
                      s"width=${result.annotation.packedWidth} fields=${result.annotation.fields.size} " +
                      s"read-ports=${result.annotation.readPorts}")
                    result.module
                  case Left(reason) =>
                    println(s"[v2-state-array] not lifted ${current.name}.$name " +
                      s"fields=${requested.toSeq.sorted.mkString(",")}: $reason")
                    current
                }
            }
          }
        }
      case other => other
    }

    val foundNames = discovered.map(_.register).toSet
    val missing = selected -- foundNames
    if (missing.nonEmpty)
      println(s"[v2-state-array] requested register(s) not found: ${missing.toSeq.sorted.mkString(",")}")
    if (requestedGroups.isEmpty && autoPackNames.isEmpty)
      println("[v2-state-array] discovery-only: set V2_STATE_ARRAY_FIELDS or " +
        "V2_STATE_ARRAY_FIELD_GROUPS to enable lifting")
    state.copy(circuit = state.circuit.copy(modules = modules),
      annotations = state.annotations ++ discovered ++ lifted)
  }
}
