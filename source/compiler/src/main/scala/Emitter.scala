package essent

import essent.Extract._
import essent.ir._
import essent.simd.LaneTag

import firrtl._
import firrtl.annotations._
import firrtl.ir._
import firrtl.Mappers._
import firrtl.PrimOps._
import firrtl.Utils._

import scala.util.Random

case class EmitContext(
  forward: Option[Boolean] = None,
  vectorWidth: Int = 4,
  mergedDirection: Boolean = false,
  // Render Mux as the branchless by-value essent_mux helper instead of `?:`.
  // C++ `c ? a[L] : b[L]` has glvalue operands, so the backend lowers it to
  // an address select + conditional load — a pattern the loop vectorizer
  // rejects, collapsing whole lane loops to scalar cmp/cmov chains (measured:
  // only 11% vector instructions on sodor v2). essent_mux takes both sides
  // by value and blends with a mask, which maps to vpblendm/vpternlog.
  // Only v2 emission defines the helper, so this defaults to off.
  branchlessMux: Boolean = false,
  // v2: for UInt<=64 comb assignments, render the RHS as primitive integer
  // dataflow and assign to `.val`. This avoids UInt<1>::operator bool() and
  // byte-predicate round trips while leaving wide/SInt/risky ops on the
  // existing UInt/SInt path. v2 enables this by default after sodor W=16
  // measurements showed no-verify KernelEval improving from ~128 ns/cycle to
  // ~95 ns/cycle when paired with primitiveUIntMuxBlend.
  primitiveUIntExpr: Boolean = false,
  // When primitive UInt lowering is enabled, lower FIRRTL Mux as a masked
  // integer select instead of C++ `?:`. This gives the vectorizer straight-line
  // dataflow for nested control trees and avoids scalar branch forests from
  // nested control Muxes.
  primitiveUIntMuxBlend: Boolean = false,
  // Bounded, pure scalar state expressions only; not vector comb loops.
  scalarMuxSelect: Boolean = false
)

object Emitter {
  val DefaultContext: EmitContext = EmitContext()

  sealed trait OracleValueMode
  case object OracleInlineMode extends OracleValueMode
  case object OracleTraceMode extends OracleValueMode
  case object OracleWarmupMode extends OracleValueMode

  private def broadcastTargets(memName: String)(implicit rn: Renamer, ctx: EmitContext): Seq[String] = {
    ctx.forward match {
      case Some(_) =>
        rn.flatVecMeta.get(memName) match {
          case Some(info) if info.laneIndex < ctx.vectorWidth =>
            val myLaneIdx = info.laneIndex
            (0 until ctx.vectorWidth).filter(_ != myLaneIdx).map { j =>
              essent.passes.SplitRegUpdates.siblingLaneName(memName, myLaneIdx, j)
            }
          case _ => Seq.empty
        }
      case None => Seq.empty
    }
  }

  case class HyperedgeDep(name: String, deps: Seq[String], stmt: Statement)

  // Type Declaration & Initialization
  //----------------------------------------------------------------------------
  def genCppType(tpe: Type) = tpe match {
    case UIntType(IntWidth(w)) => s"UInt<$w>"
    case SIntType(IntWidth(w)) => s"SInt<$w>"
    case AsyncResetType => "UInt<1>"
    case _ => throw new Exception(s"No CPP type implemented for $tpe")
  }

  /** Compute sizeof for UInt<N>/SInt<N> pod templates (matches uint_pod_v2.h). */
  private def cppSizeof(tpe: Type): Int = {
    val bits = tpe match {
      case UIntType(IntWidth(w)) => w.toInt
      case SIntType(IntWidth(w)) => w.toInt
      case AsyncResetType => 1
      case _ => 64
    }
    if (bits <= 8) 1 else if (bits <= 16) 2 else if (bits <= 32) 4
    else if (bits <= 64) 8 else 16
  }

  def chooseAlignment(tpe: Type, vectorWidth: Int): String = {
    val totalBytes = cppSizeof(tpe) * vectorWidth
    if (totalBytes <= 8) ""
    else if (totalBytes <= 16) "alignas(16) "
    else if (totalBytes <= 32) "alignas(32) "
    else "alignas(64) "
  }

  def initializeVals(topLevel: Boolean, vectorWidth: Int = 1,
                     simdPortArrays: Map[String, String] = Map.empty)(
      m: Module, registers: Seq[DefRegister], memories: Seq[DefMemory]) = {
    def initVal(name: String, tpe:Type) = s"$name.rand_init();"
    val emittedArrays = collection.mutable.Set[String]()
    val regInits = registers flatMap { r: DefRegister =>
      if (vectorWidth > 1) {
        LaneTag.extract(r.info) match {
          case Some((scalarSrc, laneIdx)) if laneIdx < vectorWidth =>
            val suffix = essent.passes.SplitRegUpdates.laneNameSuffix(r.name, laneIdx)
            val key = scalarSrc + suffix
            if (!emittedArrays.contains(key)) {
              emittedArrays += key
              Seq(s"for (int _i=0; _i<$vectorWidth; _i++) $key[_i].rand_init();")
            } else Seq()
          case _ => Seq(initVal(r.name, r.tpe))
        }
      } else Seq(initVal(r.name, r.tpe))
    }
    val memInits = memories flatMap { m: DefMemory => {
      if ((m.depth > 1000) && (bitWidth(m.dataType)) <= 64) {
        Seq(s"${m.name}[0].rand_init();",
            s"for (size_t a=0; a < ${m.depth}; a++) ${m.name}[a] = ${m.name}[0].as_single_word() + a;")
      } else
        Seq(s"for (size_t a=0; a < ${m.depth}; a++) ${m.name}[a].rand_init();")
    }}
    val emittedPortArrays = collection.mutable.Set[String]()
    val portInits = m.ports flatMap { p => p.tpe match {
      case ClockType => Seq()
      case _ => if (!topLevel) Seq()
                else simdPortArrays.get(p.name) match {
                  case Some(arrayName) =>
                    if (!emittedPortArrays.contains(arrayName)) {
                      emittedPortArrays += arrayName
                      Seq(s"for (int _i=0; _i<$vectorWidth; _i++) $arrayName[_i].rand_init();")
                    } else Seq()
                  case None => Seq(initVal(p.name, p.tpe))
                }
    }}
    regInits ++ memInits ++ portInits
  }


  // Prefixing & Replacement
  //----------------------------------------------------------------------------
  def addPrefixToNameStmt(prefix: String)(s: Statement): Statement = {
    val replaced = s match {
      case n: DefNode => n.copy(name = prefix + n.name)
      case r: DefRegister => r.copy(name = prefix + r.name)
      case m: DefMemory => m.copy(name = prefix + m.name)
      case w: DefWire => w.copy(name = prefix + w.name)
      case mw: MemWrite => mw.copy(memName = prefix + mw.memName)
      case _ => s
    }
    replaced map addPrefixToNameStmt(prefix) map addPrefixToNameExpr(prefix)
  }

  def addPrefixToNameExpr(prefix: String)(e: Expression): Expression = {
    val replaced = e match {
      case w: WRef => w.copy(name = prefix + w.name)
      case _ => e
    }
    replaced map addPrefixToNameExpr(prefix)
  }

  def replaceNamesStmt(renames: Map[String, String])(s: Statement): Statement = {
    val nodeReplaced = s match {
      case n: DefNode if (renames.contains(n.name)) => n.copy(name = renames(n.name))
      case cm: CondMux if (renames.contains(cm.name)) => cm.copy(name = renames(cm.name))
      case mw: MemWrite if (renames.contains(mw.memName)) => mw.copy(memName = renames(mw.memName))
      case _ => s
    }
    nodeReplaced map replaceNamesStmt(renames) map replaceNamesExpr(renames)
  }

  def replaceNamesExpr(renames: Map[String, String])(e: Expression): Expression = {
    def findRootKind(e: Expression): Kind = e match {
      case w: WRef => w.kind
      case w: WSubField => findRootKind(w.expr)
    }
    e match {
      case w: WRef => {
        if (renames.contains(w.name)) w.copy(name = renames(w.name))
        else w
      }
      case w: WSubField => {
        val fullName = emitExpr(w)
        // flattens out nested WSubFields
        if (renames.contains(fullName)) WRef(renames(fullName), w.tpe, findRootKind(w), w.flow)
        else w
      }
      case _ => e map replaceNamesExpr(renames)
    }
  }


  // Emission
  //----------------------------------------------------------------------------
  def emitPort(topLevel: Boolean, emitSIMD: Boolean = false, index: Int = 0)(p: Port): Seq[String] = p.tpe match {
    case ClockType => if (!topLevel) Seq()
                      else Seq(genCppType(UIntType(IntWidth(1))) + " " + p.name + ";")
      // FUTURE: suppress generation of clock field if not making harness (or used)?
    case _ => if (!topLevel) Seq()
              else {
                if(emitSIMD) {
                  Seq(genCppType(p.tpe) + " " + p.name + ";")
                }
                else {
                  Seq(genCppType(p.tpe) + " " + p.name + ";")
                }
              }
  }

  def chunkLitString(litStr: String, chunkWidth:Int = 16): Seq[String] = {
    if (litStr.length % chunkWidth == 0) litStr.grouped(chunkWidth).toSeq
    else Seq(litStr.take(litStr.length % chunkWidth)) ++ chunkLitString(litStr.drop(litStr.length % chunkWidth), chunkWidth)
  }

  // NOTE: assuming no large UIntLiteral is negative
  def splatLargeLiteralIntoRawArray(value: BigInt, width: BigInt): String = {
    val rawHexStr = value.toString(16)
    val isNeg = value < 0
    val asHexStr = if (isNeg) rawHexStr.tail else rawHexStr
    val arrStr = chunkLitString(asHexStr) map { "0x" + _} mkString(",")
    val leadingNegStr = if (isNeg) "(uint64_t) -" else ""
    val numWords = (width + 63) / 64
    s"std::array<uint64_t,$numWords>({$leadingNegStr$arrStr})"
  }

  // laneVar: if set, emit SIMD refs as base[laneVar] instead of base[laneIdx]
  private var _laneVar: Option[String] = None
  def withLaneVar[T](lv: String)(f: => T): T = {
    val old = _laneVar; _laneVar = Some(lv); val r = f; _laneVar = old; r
  }

  private def normalizedScalarType(tpe: Type): Type = tpe match {
    case ClockType | AsyncResetType | ResetType => UIntType(IntWidth(1))
    case other => other
  }

  private def typeWidthInt(tpe: Type): Int = bitWidth(normalizedScalarType(tpe)).toInt

  private def isUIntLike(tpe: Type): Boolean = normalizedScalarType(tpe) match {
    case _: UIntType => true
    case _ => false
  }

  private def isSIntLike(tpe: Type): Boolean = normalizedScalarType(tpe) match {
    case _: SIntType => true
    case _ => false
  }

  private def coerceRenderedExpr(rendered: String, srcTpe: Type, targetTpe: Type): String = {
    val normSrc = normalizedScalarType(srcTpe)
    val normTgt = normalizedScalarType(targetTpe)
    val srcWidth = typeWidthInt(normSrc)
    val tgtWidth = typeWidthInt(normTgt)

    val casted = (isUIntLike(normSrc), isUIntLike(normTgt), isSIntLike(normSrc), isSIntLike(normTgt)) match {
      case (true, true, _, _) => rendered
      case (_, _, true, true) => rendered
      case (_, true, _, false) => s"$rendered.asUInt()"
      case (false, _, _, true) => s"$rendered.asSInt()"
      case _ => rendered
    }

    if (srcWidth == tgtWidth) casted
    else if (srcWidth < tgtWidth) s"$casted.pad<$tgtWidth>()"
    else normTgt match {
      case _: UIntType => s"$casted.bits<${tgtWidth - 1},0>()"
      case _: SIntType => s"$casted.bits<${tgtWidth - 1},0>().asSInt()"
      case _ => casted
    }
  }

  private def emitExprAsType(expr: Expression, targetTpe: Type)(implicit rn: Renamer = null, ctx: EmitContext = DefaultContext): String =
    coerceRenderedExpr(emitExprWrap(expr), expr.tpe, targetTpe)

  private def emitLowWord(rendered: String): String = s"essent_to_u64($rendered)"

  private def isPrimitiveUIntType(tpe: Type): Boolean = normalizedScalarType(tpe) match {
    case UIntType(IntWidth(w)) => w <= 64
    case _ => false
  }

  /** V2_NATIVE_WIDTH_EXPR=1: compute primitive-UInt expressions in the
    * narrowest unsigned domain that holds every intermediate, instead of
    * promoting everything to uint64_t. Every node is masked to its own FIRRTL
    * width, so mod-2^k arithmetic is identical in any domain at least that
    * wide; the rendering records the maximum node width and
    * emitPrimitiveUIntAssign substitutes the placeholder cast type and
    * literal suffix afterwards. Right shifts note their argument width so a
    * wide operand is never truncated before the shift. */
  private lazy val nativeWidthExpr: Boolean =
    sys.env.get("V2_NATIVE_WIDTH_EXPR").exists(v => v == "1" || v.equalsIgnoreCase("true"))
  private var puMaxWidthSeen: Int = 0
  private def puNote(width: Int): Unit =
    if (width > puMaxWidthSeen) puMaxWidthSeen = width
  private def puCastT: String = if (nativeWidthExpr) "__PUW_T" else "uint64_t"
  private def puLitSfx: String = if (nativeWidthExpr) "__PUW_SFX" else "ULL"

  private def maskLiteral(width: Int): String = {
    if (width >= 64) s"0xffffffffffffffff$puLitSfx"
    else s"0x${((BigInt(1) << width) - 1).toString(16)}$puLitSfx"
  }

  private def primitiveUIntMask(width: Int, raw: String): String = {
    puNote(width)
    if (width >= 64) s"static_cast<$puCastT>($raw)"
    else s"(static_cast<$puCastT>($raw) & ${maskLiteral(width)})"
  }

  private def primitiveUIntCast(width: Int, raw: String): String =
    s"static_cast<typename UInt<$width>::scalar_t>(${primitiveUIntMask(width, raw)})"

  private def primitiveUIntBlend(width: Int, condWidth: Int, cond: String, tval: String, fval: String): String = {
    val m = s"(($puCastT)0 - ($puCastT)((${primitiveUIntMask(condWidth, cond)}) != 0))"
    primitiveUIntMask(width, s"((($tval) & $m) | (($fval) & ~$m))")
  }

  private def isPrimitiveSIntType(tpe: Type): Boolean = normalizedScalarType(tpe) match {
    case SIntType(IntWidth(w)) => w <= 64
    case _ => false
  }

  /** Storage of a narrow SInt<w> is the value sign-extended to the full
    * scalar_t width (SInt::sign_extend), so the signed storage type reads
    * back the exact value. */
  private def sintStorageSigned(w: Int): String =
    if (w <= 8) "int8_t" else if (w <= 16) "int16_t" else if (w <= 32) "int32_t" else "int64_t"

  /** Sign-extend the low w bits of a uint64 pattern into an int64 value. */
  private def sextExpr(w: Int, raw: String): String =
    if (w >= 64) s"static_cast<int64_t>(static_cast<uint64_t>($raw))"
    else s"(static_cast<int64_t>(static_cast<uint64_t>($raw) << ${64 - w}) >> ${64 - w})"

  /** Multi-word UInt reference (width > 64): the .val word array, so a narrow
    * slice can be taken with one or two word reads instead of the POD helper. */
  private def wideRefWords(arg: Expression)(implicit rn: Renamer, ctx: EmitContext): Option[String] =
    normalizedScalarType(arg.tpe) match {
      case UIntType(IntWidth(w)) if w > 64 => arg match {
        case r: WRef => Some(s"${emitExpr(r)}.val")
        case r: WSubField => Some(s"${emitExpr(r)}.val")
        case r: WSubAccess => Some(s"${emitExpr(r)}.val")
        case _ => None
      }
      case _ => None
    }

  /** bits(hi, lo) of a multi-word reference as a raw uint64 (unmasked above outW). */
  private def wideRefBits(words: String, hi: Int, lo: Int): String = {
    val outW = hi - lo + 1
    val k = lo / 64
    val sh = lo % 64
    if (sh + outW <= 64) s"($words[$k] >> $sh)"
    else s"(($words[$k] >> $sh) | ($words[${k + 1}] << ${64 - sh}))"
  }

  private lazy val nativeWideExpr: Boolean =
    !sys.env.get("V2_NATIVE_WIDE_EXPR").exists(v => v == "0" || v.equalsIgnoreCase("false"))

  /** Project only the requested bits of a wide wiring expression. Building
    * each intermediate UInt in a long Cat tree repeatedly copies the growing
    * word array. Slicing the tree emits each destination word directly.
    * Arithmetic with carries and dynamic shifts retain the POD fallback. */
  private def primitiveUIntSlice(e: Expression, hi: Int, lo: Int)
      (implicit rn: Renamer, ctx: EmitContext): Option[String] = {
    if (lo < 0 || hi < lo || hi - lo >= 64) return None
    puNote(64)
    val inW = normalizedScalarType(e.tpe) match {
      case UIntType(IntWidth(w)) if w.isValidInt && w >= 0 => w.toInt
      case _ => return None
    }
    val high = math.min(hi, inW - 1)
    if (lo >= inW) return Some(s"static_cast<$puCastT>(0)")
    val width = high - lo + 1
    def canon(code: String): String = primitiveUIntMask(width, code)
    def slice(arg: Expression, h: Int = high, l: Int = lo): Option[String] =
      primitiveUIntSlice(arg, h, l)
    if (inW <= 64)
      return primitiveUIntRaw(e).map(a => canon(s"(static_cast<$puCastT>($a) >> $lo)"))
    wideRefWords(e) match {
      case Some(words) => return Some(canon(wideRefBits(words, high, lo)))
      case None =>
    }
    e match {
      case literal: UIntLiteral =>
        Some(canon(s"0x${((literal.value >> lo) & ((BigInt(1) << width) - 1)).toString(16)}$puLitSfx"))
      case m: Mux =>
        for { c <- primitiveUIntRaw(m.cond); t <- slice(m.tval); f <- slice(m.fval) }
          yield primitiveUIntBlend(width, typeWidthInt(m.cond.tpe), c, t, f)
      case p: DoPrim => p.op match {
        case Cat =>
          val lowWidth = typeWidthInt(p.args(1).tpe)
          if (high < lowWidth) slice(p.args(1))
          else if (lo >= lowWidth) slice(p.args(0), high - lowWidth, lo - lowWidth)
          else for {
            low <- slice(p.args(1), lowWidth - 1, lo)
            upper <- slice(p.args(0), high - lowWidth, 0)
          } yield canon(s"((static_cast<$puCastT>($upper) << ${lowWidth - lo}) | ($low))")
        case Bits => slice(p.args.head, high + p.consts(1).toInt, lo + p.consts(1).toInt)
        case Head =>
          val offset = typeWidthInt(p.args.head.tpe) - p.consts.head.toInt
          slice(p.args.head, high + offset, lo + offset)
        case Tail | Pad | AsUInt => slice(p.args.head)
        case Shr => slice(p.args.head, high + p.consts.head.toInt, lo + p.consts.head.toInt)
        case Shl =>
          val shift = p.consts.head.toInt
          if (high < shift) Some(s"static_cast<$puCastT>(0)")
          else if (lo >= shift) slice(p.args.head, high - shift, lo - shift)
          else slice(p.args.head, high - shift, 0)
            .map(a => canon(s"(static_cast<$puCastT>($a) << ${shift - lo})"))
        case And | Or | Xor =>
          val op = if (p.op == And) "&" else if (p.op == Or) "|" else "^"
          for { a <- slice(p.args(0)); b <- slice(p.args(1)) } yield canon(s"(($a) $op ($b))")
        case Not => slice(p.args.head).map(a => canon(s"(~static_cast<$puCastT>($a))"))
        case _ => None
      }
      case _ => None
    }
  }

  private def primitiveWideUIntAssign(target: String, targetTpe: Type, rhs: Expression)
      (implicit rn: Renamer, ctx: EmitContext): Option[String] = {
    val width = normalizedScalarType(targetTpe) match {
      case UIntType(IntWidth(w)) if nativeWideExpr && w > 64 && w <= 4096 => w.toInt
      case _ => return None
    }
    val words = (0 until (width + 63) / 64).map { i =>
      primitiveUIntSlice(rhs, math.min(width - 1, i * 64 + 63), i * 64)
        .map(_.replace("__PUW_T", "uint64_t").replace("__PUW_SFX", "ULL"))
    }
    if (words.exists(_.isEmpty)) None
    else {
      // Read all source words before storing: serial lowering can alias RHS
      // storage with its destination, including cross-word shifts/slices.
      val values = words.zipWithIndex.map { case (word, i) => s"const uint64_t _v2_word_$i = ${word.get};" }
      val stores = words.indices.map(i => s"$target.val[$i] = _v2_word_$i;")
      Some((Seq("{") ++ values ++ stores ++ Seq("}")).mkString(" "))
    }
  }

  /** Signed counterpart of primitiveUIntRaw: every SInt<w<=64> value is
    * rendered as an int64_t holding the exact value (sign-extended). Results
    * are exact by FIRRTL width reasoning (a result that fits w<=64 bits never
    * overflows int64 except through the wrapping ops, which re-extend). Uses
    * the 64-bit domain (puNote(64)) so the placeholder cast type is uint64_t. */
  private def primitiveSIntRaw(e: Expression)(implicit rn: Renamer, ctx: EmitContext): Option[String] = {
    if (!isPrimitiveSIntType(e.tpe)) return None
    val width = typeWidthInt(e.tpe)
    puNote(64)
    def sraw(arg: Expression): Option[String] = primitiveSIntRaw(arg)
    def uraw(arg: Expression): Option[String] = primitiveUIntRaw(arg)
    def sraw2(args: Seq[Expression]): Option[(String, String)] =
      if (args.size == 2) for { a <- sraw(args(0)); b <- sraw(args(1)) } yield (a, b) else None
    def storageRead(code: String): String =
      s"static_cast<int64_t>(static_cast<${sintStorageSigned(width)}>($code.ui.val))"
    e match {
      case w: WRef => Some(storageRead(emitExpr(w)))
      case w: WSubField => Some(storageRead(emitExpr(w)))
      case w: WSubAccess => Some(storageRead(emitExpr(w)))
      case l: SIntLiteral =>
        val pattern = l.value & ((BigInt(1) << 64) - 1)
        Some(s"static_cast<int64_t>(static_cast<uint64_t>(0x${pattern.toString(16)}ULL))")
      case m: Mux =>
        for { c <- uraw(m.cond); t <- sraw(m.tval); f <- sraw(m.fval) } yield {
          val cw = typeWidthInt(m.cond.tpe)
          val mm = s"(static_cast<uint64_t>(0) - static_cast<uint64_t>((${primitiveUIntMask(cw, c)}) != 0))"
          s"static_cast<int64_t>((static_cast<uint64_t>($t) & $mm) | (static_cast<uint64_t>($f) & ~$mm))"
        }
      case p: DoPrim => p.op match {
        case AsSInt =>
          if (isPrimitiveSIntType(p.args.head.tpe)) sraw(p.args.head)
          else uraw(p.args.head).map(a => sextExpr(typeWidthInt(p.args.head.tpe), a))
        case Cvt =>
          if (isPrimitiveSIntType(p.args.head.tpe)) sraw(p.args.head)
          else uraw(p.args.head).map(a => s"static_cast<int64_t>(static_cast<uint64_t>($a))")
        case Pad =>
          if (isPrimitiveSIntType(p.args.head.tpe)) sraw(p.args.head) else None
        case Neg =>
          if (isPrimitiveSIntType(p.args.head.tpe)) sraw(p.args.head).map(a => s"(-($a))")
          else uraw(p.args.head).map(a => s"(-static_cast<int64_t>(static_cast<uint64_t>($a)))")
        case Add => sraw2(p.args).map { case (a, b) => s"(($a) + ($b))" }
        case Sub => sraw2(p.args).map { case (a, b) => s"(($a) - ($b))" }
        case Mul => sraw2(p.args).map { case (a, b) => s"(($a) * ($b))" }
        case Addw => sraw2(p.args).map { case (a, b) =>
          sextExpr(width, s"(static_cast<uint64_t>($a) + static_cast<uint64_t>($b))") }
        case Subw => sraw2(p.args).map { case (a, b) =>
          sextExpr(width, s"(static_cast<uint64_t>($a) - static_cast<uint64_t>($b))") }
        case Shl =>
          val sh = p.consts.head.toInt
          if (sh >= 64) None
          else sraw(p.args.head).map(a => sextExpr(width, s"(static_cast<uint64_t>($a) << $sh)"))
        case Shr =>
          val sh = math.min(p.consts.head.toInt, 63)
          sraw(p.args.head).map(a => s"(($a) >> $sh)")
        case Dshl =>
          for { a <- sraw(p.args(0)); b <- uraw(p.args(1)) } yield
            sextExpr(width, s"(static_cast<uint64_t>($a) << ($b))")
        case Dshlw =>
          for { a <- sraw(p.args(0)); b <- uraw(p.args(1)) } yield
            sextExpr(width, s"(((($b)) >= $width) ? static_cast<uint64_t>(0) : (static_cast<uint64_t>($a) << ($b)))")
        case Dshr =>
          for { a <- sraw(p.args(0)); b <- uraw(p.args(1)) } yield
            s"(($a) >> (((($b)) < 63) ? static_cast<int>($b) : 63))"
        case _ => None
      }
      case _ => None
    }
  }

  private def primitiveUIntRaw(e: Expression)(implicit rn: Renamer, ctx: EmitContext): Option[String] = {
    if (!isPrimitiveUIntType(e.tpe)) return None
    val width = typeWidthInt(e.tpe)
    def canon(code: String): String = primitiveUIntMask(width, code)
    def raw(arg: Expression): Option[String] = primitiveUIntRaw(arg)
    def raw2(args: Seq[Expression]): Option[(String, String)] =
      if (args.size == 2) for { a <- raw(args(0)); b <- raw(args(1)) } yield (a, b) else None
    // Bit pattern of an operand: UInt as is; narrow SInt masked to its width.
    def rawBits(arg: Expression): Option[String] =
      if (isPrimitiveSIntType(arg.tpe))
        primitiveSIntRaw(arg).map(a => primitiveUIntMask(typeWidthInt(arg.tpe), s"static_cast<uint64_t>($a)"))
      else raw(arg)
    def rawBits2(args: Seq[Expression]): Option[(String, String)] =
      if (args.size == 2) for { a <- rawBits(args(0)); b <- rawBits(args(1)) } yield (a, b) else None
    def signedArgs(args: Seq[Expression]): Boolean = args.nonEmpty && args.forall(a => isPrimitiveSIntType(a.tpe))
    def sraw2(args: Seq[Expression]): Option[(String, String)] =
      if (args.size == 2) for { a <- primitiveSIntRaw(args(0)); b <- primitiveSIntRaw(args(1)) } yield (a, b) else None
    def cmp(args: Seq[Expression], op: String): Option[String] =
      if (signedArgs(args)) sraw2(args).map { case (a, b) => canon(s"(($a) $op ($b))") }
      else raw2(args).map { case (a, b) => canon(s"(($a) $op ($b))") }
    // Narrow slice of a multi-word reference: one or two word reads.
    def wideSlice(arg: Expression, hi: Int, lo: Int): Option[String] =
      if (nativeWideExpr) primitiveUIntSlice(arg, hi, lo).map(canon)
      else wideRefWords(arg).map { words =>
        puNote(64)
        canon(s"static_cast<$puCastT>(${wideRefBits(words, hi, lo)})")
      }

    e match {
      case w: WRef =>
        Some(s"${emitExpr(w)}.val")
      case w: WSubField =>
        Some(s"${emitExpr(w)}.val")
      case w: WSubAccess =>
        Some(s"${emitExpr(w)}.val")
      case u: UIntLiteral =>
        Some(primitiveUIntMask(width, s"0x${u.value.toString(16)}$puLitSfx"))
      case m: Mux =>
        for {
          c <- raw(m.cond)
          t <- raw(m.tval)
          f <- raw(m.fval)
        } yield {
          val condWidth = typeWidthInt(m.cond.tpe)
          if (ctx.scalarMuxSelect) {
            val word = if (width <= 32) "uint32_t" else "uint64_t"
            canon(s"essent_select_word<$word>((${primitiveUIntMask(condWidth, c)}) != 0, " +
              s"static_cast<$word>($t), static_cast<$word>($f))")
          } else if (ctx.primitiveUIntMuxBlend) primitiveUIntBlend(width, condWidth, c, t, f)
          else canon(s"((${primitiveUIntMask(condWidth, c)}) != 0 ? ($t) : ($f))")
        }
      case p: DoPrim => p.op match {
        case Add | Addw =>
          raw2(p.args).map { case (a, b) => canon(s"(static_cast<$puCastT>($a) + static_cast<$puCastT>($b))") }
        case Sub | Subw =>
          raw2(p.args).map { case (a, b) => canon(s"(static_cast<$puCastT>($a) - static_cast<$puCastT>($b))") }
        case Mul =>
          // POD .val retains its storage width. Cast operands before the
          // operation: casting a 32-bit product/sum afterwards cannot recover
          // lost high bits (Rocket SFMA needs UInt<24> * UInt<24> -> UInt<48>).
          raw2(p.args).map { case (a, b) => canon(s"(static_cast<$puCastT>($a) * static_cast<$puCastT>($b))") }
        case Lt => cmp(p.args, "<")
        case Leq => cmp(p.args, "<=")
        case Gt => cmp(p.args, ">")
        case Geq => cmp(p.args, ">=")
        case Eq => cmp(p.args, "==")
        case Neq => cmp(p.args, "!=")
        case And =>
          rawBits2(p.args).map { case (a, b) => canon(s"(($a) & ($b))") }
        case Or =>
          rawBits2(p.args).map { case (a, b) => canon(s"(($a) | ($b))") }
        case Xor =>
          rawBits2(p.args).map { case (a, b) => canon(s"(($a) ^ ($b))") }
        case Not =>
          rawBits(p.args.head).map(a => canon(s"(~static_cast<$puCastT>($a))"))
        case Pad =>
          raw(p.args.head).map(canon)
        case AsUInt =>
          rawBits(p.args.head).map(canon)
        case Dshl =>
          // result width w_a + 2^w_b - 1 <= 64 here, so the amount stays
          // below the evaluation domain width and the shift is defined.
          raw2(p.args).map { case (a, b) => canon(s"(static_cast<$puCastT>($a) << ($b))") }
        case Dshlw =>
          val aw = typeWidthInt(p.args.head.tpe)
          raw2(p.args).map { case (a, b) =>
            canon(s"(((($b)) >= $aw) ? static_cast<$puCastT>(0) : (static_cast<$puCastT>($a) << ($b)))") }
        case Dshr =>
          val aw = typeWidthInt(p.args.head.tpe)
          rawBits2(p.args).map { case (a, b) =>
            puNote(aw)
            canon(s"(((($b)) >= $aw) ? static_cast<$puCastT>(0) : (static_cast<$puCastT>($a) >> ($b)))") }
        case Shl =>
          val sh = p.consts.head.toInt
          if (sh >= 64) None else raw(p.args.head).map(a => canon(s"(static_cast<$puCastT>($a) << $sh)"))
        case Shr =>
          val sh = p.consts.head.toInt
          val inW = typeWidthInt(p.args.head.tpe)
          if (inW > 64) { if (width > 64) None else wideSlice(p.args.head, inW - 1, sh) }
          else if (sh >= 64) None else rawBits(p.args.head).map { a =>
            puNote(typeWidthInt(p.args.head.tpe))
            canon(s"(static_cast<$puCastT>($a) >> $sh)")
          }
        case Cat =>
          val loWidth = typeWidthInt(p.args(1).tpe)
          if (width > 64 || loWidth >= 64) None
          else rawBits2(p.args).map { case (hi, lo) =>
            canon(s"((static_cast<$puCastT>($hi) << $loWidth) | ${primitiveUIntMask(loWidth, lo)})")
          }
        case Bits =>
          val hi = p.consts(0).toInt
          val lo = p.consts(1).toInt
          val outW = hi - lo + 1
          val inW = typeWidthInt(p.args.head.tpe)
          if (outW > 64) None
          else if (inW > 64) wideSlice(p.args.head, hi, lo)
          else if (lo >= 64) None
          else rawBits(p.args.head).map { a =>
            puNote(typeWidthInt(p.args.head.tpe))
            canon(s"((static_cast<$puCastT>($a) >> $lo) & ${maskLiteral(outW)})")
          }
        case Head =>
          val n = p.consts.head.toInt
          val inW = typeWidthInt(p.args.head.tpe)
          val sh = inW - n
          if (inW > 64) { if (n > 64 || sh < 0) None else wideSlice(p.args.head, inW - 1, sh) }
          else if (sh < 0 || sh >= 64) None
          else rawBits(p.args.head).map { a =>
            puNote(typeWidthInt(p.args.head.tpe))
            canon(s"((static_cast<$puCastT>($a) >> $sh) & ${maskLiteral(n)})")
          }
        case Tail =>
          val n = p.consts.head.toInt
          val inW = typeWidthInt(p.args.head.tpe)
          val outW = inW - n
          if (outW <= 0 || outW > 64) None
          else if (inW > 64) wideSlice(p.args.head, outW - 1, 0)
          else rawBits(p.args.head).map(a => canon(s"(static_cast<$puCastT>($a) & ${maskLiteral(outW)})"))
        case Andr =>
          rawBits(p.args.head).map(a => canon(s"(${primitiveUIntMask(typeWidthInt(p.args.head.tpe), a)} == ${maskLiteral(typeWidthInt(p.args.head.tpe))})"))
        case Orr =>
          rawBits(p.args.head).map(a => canon(s"(${primitiveUIntMask(typeWidthInt(p.args.head.tpe), a)} != 0)"))
        case Xorr =>
          rawBits(p.args.head).map { a =>
            puNote(64) // __builtin_parityll consumes a full uint64_t
            canon(s"(__builtin_parityll(${primitiveUIntMask(typeWidthInt(p.args.head.tpe), a)}))")
          }
        case _ =>
          None
      }
      case _ =>
        None
    }
  }

  def emitPrimitiveUIntAssign(target: String, targetTpe: Type, rhs: Expression)
      (implicit rn: Renamer, ctx: EmitContext = DefaultContext): Option[String] = {
    if (ctx == null || !ctx.primitiveUIntExpr) None
    else if (!isPrimitiveUIntType(targetTpe) && !isPrimitiveSIntType(targetTpe))
      primitiveWideUIntAssign(target, targetTpe, rhs)
    else {
      puMaxWidthSeen = 0
      val width = typeWidthInt(targetTpe)
      val rendered: Option[String] =
        if (isPrimitiveUIntType(targetTpe))
          primitiveUIntRaw(rhs).map(r => s"$target.val = ${primitiveUIntCast(width, r)};")
        else
          // Narrow SInt storage is the value sign-extended to scalar_t width;
          // truncating the exact int64 value reproduces exactly that pattern.
          primitiveSIntRaw(rhs).map(r => s"$target.ui.val = static_cast<typename UInt<$width>::scalar_t>($r);")
      rendered.map { code =>
        if (!nativeWidthExpr) code
        else {
          val mw = math.max(puMaxWidthSeen, width)
          val (t, sfx) =
            if (mw <= 8) ("uint8_t", "u")
            else if (mw <= 16) ("uint16_t", "u")
            else if (mw <= 32) ("uint32_t", "u")
            else ("uint64_t", "ULL")
          code.replace("__PUW_T", t).replace("__PUW_SFX", sfx)
        }
      }
    }
  }

  /** Bitwise ops (and/or/xor) act on raw bits, but the POD C++ types define
    * no mixed UInt/SInt operators. When operand classes disagree, render
    * every SInt operand through .asUInt() — bit-identical, and keeps the
    * generated code compilable regardless of which pass built the node. */
  private def emitBitwiseOperandAsUInt(arg: Expression)
      (implicit rn: Renamer, ctx: EmitContext): String =
    normalizedScalarType(arg.tpe) match {
      case t if isSIntLike(t) => s"${emitExprWrap(arg)}.asUInt()"
      case _ => emitExprWrap(arg)
    }

  private def commonOperandType(args: Seq[Expression]): Option[Type] = {
    val normTypes = args.map(a => normalizedScalarType(a.tpe))
    if (normTypes.nonEmpty && normTypes.forall(isUIntLike)) {
      Some(UIntType(IntWidth(args.map(a => typeWidthInt(a.tpe)).max)))
    } else if (normTypes.nonEmpty && normTypes.forall(isSIntLike)) {
      Some(SIntType(IntWidth(args.map(a => typeWidthInt(a.tpe)).max)))
    } else {
      None
    }
  }

  /** Extract the raw FIRRTL name of an expression without renaming or SIMD context. */
  def emitExprRaw(e: Expression): String = emitExpr(e)(null, DefaultContext)

  def emitExpr(e: Expression)(implicit rn: Renamer = null, ctx: EmitContext = DefaultContext): String = e match {
    case w: WRef =>
      if (rn == null) w.name
      else _laneVar match {
        case Some(lv) => rn.emitForLane(w.name, lv)
        case None => rn.emit(w.name)
      }
    case u: UIntLiteral => {
      val maxIn64Bits = (BigInt(1) << 64) - 1
      val width = bitWidth(u.tpe)
      val asHexStr = u.value.toString(16)
      if ((width <= 64) || (u.value <= maxIn64Bits)) s"UInt<$width>(0x$asHexStr)"
      else s"UInt<$width>(${splatLargeLiteralIntoRawArray(u.value, width)})"
    }
    case u: SIntLiteral => {
      val width = bitWidth(u.tpe)
      if (width <= 64) s"SInt<$width>(${u.value.toString(10)})"
      else s"SInt<$width>(${splatLargeLiteralIntoRawArray(u.value, width)})"
    }
    case m: Mux => {
      val condName = emitExprWrap(m.cond)
      val tvalName = emitExprAsType(m.tval, m.tpe)
      val fvalName = emitExprAsType(m.fval, m.tpe)
      if (ctx != null && ctx.branchlessMux)
        s"essent_mux($condName, $tvalName, $fvalName)"
      else
        s"$condName ? $tvalName : $fvalName"
    }
    case w: WSubField => {
      val result = s"${emitExprRaw(w.expr)}.${w.name}"
      if (rn == null) result
      else _laneVar match {
        case Some(lv) => rn.emitForLane(result, lv)
        case None => rn.emit(result)
      }
    }
    case w: WSubAccess => s"${emitExpr(w.expr)}[${emitLowWord(emitExprWrap(w.index))}]"
    case p: DoPrim => p.op match {
      case Add =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" + ")
          case None => p.args.map(emitExprWrap).mkString(" + ")
        }
      case Addw => s"${emitExprWrap(p.args(0))}.addw(${emitExprWrap(p.args(1))})"
      case Sub =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" - ")
          case None => p.args.map(emitExprWrap).mkString(" - ")
        }
      case Subw => s"${emitExprWrap(p.args(0))}.subw(${emitExprWrap(p.args(1))})"
      case Mul => p.args map emitExprWrap mkString(" * ")
      case Div => p.args map emitExprWrap mkString(" / ")
      case Rem => p.args map emitExprWrap mkString(" % ")
      case Lt  =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" < ")
          case None => p.args.map(emitExprWrap).mkString(" < ")
        }
      case Leq =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" <= ")
          case None => p.args.map(emitExprWrap).mkString(" <= ")
        }
      case Gt  =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" > ")
          case None => p.args.map(emitExprWrap).mkString(" > ")
        }
      case Geq =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" >= ")
          case None => p.args.map(emitExprWrap).mkString(" >= ")
        }
      case Eq =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" == ")
          case None => p.args.map(emitExprWrap).mkString(" == ")
        }
      case Neq =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" != ")
          case None => p.args.map(emitExprWrap).mkString(" != ")
        }
      case Pad => s"${emitExprWrap(p.args.head)}.pad<${bitWidth(p.tpe)}>()"
      case AsUInt => s"${emitExprWrap(p.args.head)}.asUInt()"
      case AsSInt => s"${emitExprWrap(p.args.head)}.asSInt()"
      case AsClock => throw new Exception("AsClock unimplemented!")
      case AsAsyncReset => emitExpr(p.args.head)                    
      case Shl => s"${emitExprWrap(p.args.head)}.shl<${p.consts.head.toInt}>()"
      // case Shlw => s"${emitExprWrap(p.args.head)}.shlw<${p.consts.head.toInt}>()"
      case Shr => s"${emitExprWrap(p.args.head)}.shr<${p.consts.head.toInt}>()"
      case Dshl => p.args map emitExprWrap mkString(" << ")
      case Dshlw => s"${emitExprWrap(p.args(0))}.dshlw(${emitExpr(p.args(1))})"
      case Dshr => p.args map emitExprWrap mkString(" >> ")
      case Cvt => s"${emitExprWrap(p.args.head)}.cvt()"
      case Neg => s"-${emitExprWrap(p.args.head)}"
      case Not => s"~${emitExprWrap(p.args.head)}"
      case And =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" & ")
          case None => p.args.map(emitBitwiseOperandAsUInt).mkString(" & ")
        }
      case Or =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" | ")
          case None => p.args.map(emitBitwiseOperandAsUInt).mkString(" | ")
        }
      case Xor =>
        commonOperandType(p.args) match {
          case Some(tpe) => p.args.map(arg => emitExprAsType(arg, tpe)).mkString(" ^ ")
          case None => p.args.map(emitBitwiseOperandAsUInt).mkString(" ^ ")
        }
      case Andr => s"${emitExprWrap(p.args.head)}.andr()"
      case Orr => s"${emitExprWrap(p.args.head)}.orr()"
      case Xorr => s"${emitExprWrap(p.args.head)}.xorr()"
      case Cat => s"${emitExprWrap(p.args(0))}.cat(${emitExpr(p.args(1))})"
      case Bits => s"${emitExprWrap(p.args.head)}.bits<${p.consts(0).toInt},${p.consts(1).toInt}>()"
      case Head => s"${emitExprWrap(p.args.head)}.head<${p.consts.head.toInt}>()"
      case Tail => s"${emitExprWrap(p.args.head)}.tail<${p.consts.head.toInt}>()"
    }
    case _ => throw new Exception(s"Don't yet support $e")
  }

  def emitExprWrap(e: Expression)(implicit rn: Renamer, ctx: EmitContext = DefaultContext): String = e match {
    case DoPrim(_,_,_,_) | Mux(_,_,_,_) => s"(${emitExpr(e)})"
    case _ => emitExpr(e)
  }

  def extractOracleTraceField(info: Info): Option[String] = info match {
    case fi: FileInfo if fi.escaped.startsWith("oracle:") =>
      Some(fi.escaped.stripPrefix("oracle:"))
    case MultiInfo(infos) =>
      infos.iterator.map(extractOracleTraceField).collectFirst { case Some(v) => v }
    case _ => None
  }

  def sanitizeTraceField(field: String): String =
    "trace_" + field.replace('.', '_').replace(':', '_')
      .replace("(", "").replace(")", "").replace("-", "m")

  /** Derive an instance-specific oracle array name from the flattened node path.
    * For auto-generated oracle names (prefixed "micro_"), the module-level trace
    * name can alias when multiple instances of the same module type share a
    * register name (e.g. int_issue_unit.slots_0.state vs slots_1.state).
    * This method replaces the module-level name with one derived from the full
    * flattened instance path, guaranteeing uniqueness.
    */
  private def resolveOracleArrayName(annotationField: String, oracleNodeName: String)(implicit rn: Renamer): String = {
    if (!annotationField.startsWith("micro_"))
      return sanitizeTraceField(annotationField)

    val withoutOracle = oracleNodeName.stripSuffix("$oracle")
    val (basePath, subFieldSuffix) = rn.flatVecMeta.get(withoutOracle) match {
      case Some(info) =>
        val suffix = essent.passes.SplitRegUpdates.laneNameSuffix(withoutOracle, info.laneIndex)
        val laneTag = s"_lane_${info.laneIndex}"
        val pos = withoutOracle.indexOf(laneTag)
        val base = if (pos >= 0) withoutOracle.take(pos) else withoutOracle
        (base, suffix)
      case None =>
        val localName = withoutOracle.split('.').last
        (None: Option[(String, Int)]) match {
          case Some((scalarBase, _)) =>
            val prefix = withoutOracle.dropRight(localName.length)
            (prefix + scalarBase, "")
          case None => (withoutOracle, "")
        }
    }
    val parts = basePath.split('.')
    val subPath = if (parts.length > 1) parts.drop(1).mkString("_") else parts.mkString("_")
    sanitizeTraceField(s"micro_${subPath}${subFieldSuffix}")
  }

  private def extractLaneIndex(nodeName: String)(implicit rn: Renamer): Int = {
    val baseName = nodeName.stripSuffix("$oracle")
    rn.flatVecMeta.get(baseName).map(_.laneIndex).getOrElse {
      val localName = baseName.split('.').last
      (None: Option[(String, Int)]).map(_._2).getOrElse(0)
    }
  }

  private def oracleIndexExpr(laneExpr: String)(implicit ctx: EmitContext): String = {
    if (ctx.mergedDirection) {
      s"(oracle_cycle + _oracle_base + _oracle_step * ($laneExpr))"
    } else ctx.forward match {
      case Some(true) => s"(oracle_cycle + $laneExpr)"
      case Some(false) =>
        val revBase = 2 * ctx.vectorWidth - 1
        s"(oracle_cycle + $revBase - $laneExpr)"
      case None => s"(oracle_cycle + $laneExpr)"
    }
  }

  private def emitOracleValue(typeStr: String, arrayName: String, regExpr: String,
                              laneExpr: String, mode: OracleValueMode)(implicit ctx: EmitContext): String = {
    mode match {
      case OracleTraceMode =>
        s"$typeStr((uint64_t)ESSENT_ORACLE_LOAD($arrayName, ${oracleIndexExpr(laneExpr)}))"
      case OracleWarmupMode =>
        s"$typeStr((uint64_t)${emitLowWord(regExpr)})"
      case OracleInlineMode =>
        s"$typeStr(done_reset ? ESSENT_ORACLE_LOAD($arrayName, ${oracleIndexExpr(laneExpr)}) : (uint64_t)${emitLowWord(regExpr)})"
    }
  }

  def emitStmt(s: Statement, oracleMode: OracleValueMode = OracleInlineMode)(implicit rn: Renamer, ctx: EmitContext = DefaultContext): Seq[String] = s match {
    case b: Block => b.stmts flatMap (emitStmt(_, oracleMode))
    case d: DefNode => {
      val lhs_orig = d.name
      val lhs = rn.emit(lhs_orig)
      val oracleField = extractOracleTraceField(d.info)
      val rhs = oracleField match {
        case Some(field) =>
          val arrayName = resolveOracleArrayName(field, lhs_orig)
          val laneIdx = extractLaneIndex(lhs_orig)
          val regRef = lhs_orig.stripSuffix("$oracle")
          emitOracleValue(genCppType(d.value.tpe), arrayName, rn.emit(regRef), laneIdx.toString, oracleMode)
        case None =>
          emitExpr(d.value)
      }
      val arrayDecl = rn.simdArrayDecl(lhs_orig, genCppType(d.value.tpe)).toSeq
      if (rn.decLocal(lhs_orig))
        arrayDecl :+ s"[[maybe_unused]] ${genCppType(d.value.tpe)} $lhs = $rhs;"
      else arrayDecl :+ s"$lhs = $rhs;"
    }
    case c: Connect => {
      val lhs_orig = emitExprRaw(c.loc)
      val lhs = rn.emit(lhs_orig)
      val rhs = emitExpr(c.expr)
      val arrayDecl = rn.simdArrayDecl(lhs_orig, genCppType(c.loc.tpe)).toSeq
      if (rn.decLocal(lhs_orig))
        arrayDecl :+ s"[[maybe_unused]] ${genCppType(c.loc.tpe)} $lhs = $rhs;"
      else arrayDecl :+ s"$lhs = $rhs;"
    }
    case p: Print => {
      val formatters = "(%h)|(%x)|(%d)|(%ld)".r.findAllIn(p.string.serialize).toList
      val argWidths = p.args map {e: Expression => bitWidth(e.tpe)}
      if (!(argWidths forall { _ <= 64 })) throw new Exception(s"Can't print wide signals")
      val replacements = formatters zip argWidths map { case(format, width) =>
        if (format == "%h" || format == "%x") {
          val printWidth = math.ceil(width.toDouble/4).toInt
          (format, s"""%0${printWidth}" PRIx64 """")
        } else {
          val printWidth = math.ceil(math.log10((1L<<width.toInt).toDouble)).toInt
          (format, s"""%${printWidth}" PRIu64 """")
        }
      }
      val formatString = replacements.foldLeft(p.string.serialize){
        case (str, (searchFor, replaceWith)) => str.replaceFirst(searchFor, replaceWith)
      }
      val printfArgs = Seq(s""""$formatString"""") ++
                        (p.args map {arg => emitLowWord(emitExprWrap(arg))})
      Seq(s"if (UNLIKELY(done_reset && update_registers && verbose && ${emitExprWrap(p.en)})) printf(${printfArgs mkString(", ")});")
    }
    case st: Stop => {
      Seq(s"if (UNLIKELY(${emitExpr(st.en)})) {assert_triggered = true; assert_exit_code = ${st.ret};}")
    }
    case mw: MemWrite => {
      val guard = if (ctx.forward.isDefined) s"${emitExprWrap(mw.wrEn)} && ${emitExprWrap(mw.wrMask)}"
                  else s"update_registers && ${emitExprWrap(mw.wrEn)} && ${emitExprWrap(mw.wrMask)}"
      val addr = emitLowWord(emitExprWrap(mw.wrAddr))
      val data = emitExpr(mw.wrData)
      val primary = s"${mw.memName}[$addr] = $data;"
      val targets = broadcastTargets(mw.memName)
      if (targets.nonEmpty) {
        val copies = targets.map(t => s"$t[$addr] = $data;").mkString(" ")
        Seq(s"if (UNLIKELY($guard)) { $primary $copies }")
      } else {
        Seq(s"if (UNLIKELY($guard)) $primary")
      }
    }
    case ru: RegUpdate =>
      if (ctx.forward.isDefined) Seq(s"${emitExpr(ru.regRef)} = ${emitExpr(ru.expr)};")
      else Seq(s"if (update_registers) ${emitExpr(ru.regRef)} = ${emitExpr(ru.expr)};")
    case cru: CondRegUpdate =>
      if (ctx.forward.isDefined) Seq(s"if (${emitExpr(cru.cond)}) ${emitExpr(cru.regRef)} = ${emitExpr(cru.expr)};")
      else Seq(s"if (update_registers && ${emitExpr(cru.cond)}) ${emitExpr(cru.regRef)} = ${emitExpr(cru.expr)};")
    case lv: LBNVerify =>
      val dirTag = if (ctx.mergedDirection) {
        "%s"
      } else ctx.forward match {
        case Some(true) => "FWD"
        case Some(false) => "REV"
        case None => "---"
      }
      val leadArg = if (ctx.mergedDirection) """(_forward ? "FWD" : "REV"), """ else ""
      Seq(s"if (verbose && update_registers && done_reset && !(${emitExpr(lv.regRef)} == ${emitExpr(lv.oracleRef)})) fprintf(stderr, \"VERIFY FAIL [$dirTag]: ${emitExprRaw(lv.regRef)} got=0x%lx expect=0x%lx cyc=%d\\n\", $leadArg(uint64_t)${emitLowWord(emitExpr(lv.regRef))}, (uint64_t)${emitLowWord(emitExpr(lv.oracleRef))}, oracle_cycle);")
    case lt: LookupTable =>
      val typeStr = genCppType(lt.resultType)
      val lutVar = s"_lut_${lt.name.replace('.', '$')}"
      val entriesStr = lt.entries.map(e => s"0x${e.toString(16)}ULL").mkString(", ")
      val indexStr = emitExpr(lt.indexExpr)
      val lhs = rn.emit(lt.name)
      val arrayDecl = rn.simdArrayDecl(lt.name, typeStr).toSeq
      val decl = if (rn.decLocal(lt.name)) s"[[maybe_unused]] $typeStr $lhs" else lhs
      arrayDecl ++ Seq(
        s"static const uint64_t $lutVar[] = {$entriesStr};",
        s"$decl = $typeStr($lutVar[${emitLowWord(indexStr)}]);"
      )
    case r: DefRegister => Seq()
    case w: DefWire => Seq()
    case m: DefMemory => Seq()
    case i: WDefInstance => Seq()
    case _ => throw new Exception(s"Don't yet support $s")
  }

  def emitStmtForLane(s: Statement, laneVar: String, oracleMode: OracleValueMode = OracleInlineMode)(implicit rn: Renamer, ctx: EmitContext = DefaultContext): Seq[String] = withLaneVar(laneVar) {
    s match {
      case d: DefNode =>
        val lhs_orig = d.name
        val lhs = rn.emitForLane(lhs_orig, laneVar)
        val oracleField = extractOracleTraceField(d.info)
        val rhs = oracleField match {
          case Some(field) =>
            val arrayName = resolveOracleArrayName(field, lhs_orig)
            val regRef = lhs_orig.stripSuffix("$oracle")
            emitOracleValue(genCppType(d.value.tpe), arrayName, rn.emitForLane(regRef, laneVar), laneVar, oracleMode)
          case None =>
            emitExpr(d.value)
        }
        Seq(s"$lhs = $rhs;")
      case c: Connect =>
        val lhs_orig = emitExprRaw(c.loc)
        val lhs = rn.emitForLane(lhs_orig, laneVar)
        val rhs = emitExpr(c.expr)
        Seq(s"$lhs = $rhs;")
      case ru: RegUpdate =>
        Seq(s"${rn.emitForLane(emitExprRaw(ru.regRef), laneVar)} = ${emitExpr(ru.expr)};")
      case cru: CondRegUpdate =>
        Seq(s"if (${emitExpr(cru.cond)}) ${rn.emitForLane(emitExprRaw(cru.regRef), laneVar)} = ${emitExpr(cru.expr)};")
      case mw: MemWrite =>
        val guard = s"${emitExpr(mw.wrEn)} && ${emitExpr(mw.wrMask)}"
        val addr = emitLowWord(emitExpr(mw.wrAddr))
        val data = emitExpr(mw.wrData)
        Seq(s"if (UNLIKELY($guard)) ${rn.emitForLane(mw.memName, laneVar)}[$addr] = $data;")
      case lv: LBNVerify =>
        val dirTag = if (ctx.mergedDirection) "%s" else ctx.forward match {
          case Some(true) => "FWD"; case Some(false) => "REV"; case None => "---"
        }
        val leadArg = if (ctx.mergedDirection) """(_forward ? "FWD" : "REV"), """ else ""
        Seq(s"if (verbose && update_registers && done_reset && !(${emitExpr(lv.regRef)} == ${emitExpr(lv.oracleRef)})) fprintf(stderr, \"VERIFY FAIL [$dirTag]: got=0x%lx expect=0x%lx cyc=%d\\n\", $leadArg(uint64_t)${emitLowWord(emitExpr(lv.regRef))}, (uint64_t)${emitLowWord(emitExpr(lv.oracleRef))}, oracle_cycle);")
      case lt: LookupTable =>
        val typeStr = genCppType(lt.resultType)
        val lutVar = s"_lut_${lt.name.replace('.', '$')}"
        val entriesStr = lt.entries.map(e => s"0x${e.toString(16)}ULL").mkString(", ")
        val indexStr = emitExpr(lt.indexExpr)
        val lhs = rn.emitForLane(lt.name, laneVar)
        Seq(
          s"static const uint64_t $lutVar[] = {$entriesStr};",
          s"$lhs = $typeStr($lutVar[${emitLowWord(indexStr)}]);"
        )
      case _ => emitStmt(s, oracleMode)
    }
  }

  def emitAtom(atom: essent.simd.ScheduleAtom, withComments: Boolean = true)(implicit rn: Renamer, ctx: EmitContext = DefaultContext): Seq[String] = {
    import essent.simd._
    val header = if (withComments) {
      val typeName = atom match {
        case _: ParallelAtom   => "PARALLEL"
        case _: ShiftAtom      => "SHIFT"
        case _: CondUpdateAtom => "COND_UPDATE"
        case _: OracleAtom     => "ORACLE"
        case _: CommitAtom     => "COMMIT"
        case _: ScalarAtom     => "SCALAR"
      }
      val nLanes = atom match {
        case pa: ParallelAtom   => pa.lanes.size
        case sa: ShiftAtom      => sa.shifts.size
        case ca: CondUpdateAtom => ca.updates.size
        case oa: OracleAtom     => oa.oraclePlaceholders.size
        case ca: CommitAtom     => ca.commits.size
        case sa: ScalarAtom     => sa.stmts.size
      }
      Seq(s"// ---- ATOM [$typeName] ${atom.id} ($nLanes lanes, ${atom.deps.size} deps) ----")
    } else Seq.empty

    val body = atom match {
      case pa: ParallelAtom =>
        pa.lanes.flatMap(stmt => emitStmt(stmt))
      case sa: ShiftAtom =>
        sa.shifts.flatMap(stmt => emitStmt(stmt))
      case ca: CondUpdateAtom =>
        val wenLines = ca.wenAtom.lanes.flatMap(stmt => emitStmt(stmt))
        val wdataLines = ca.wdataAtom.lanes.flatMap(stmt => emitStmt(stmt))
        val updateLines = ca.updates.flatMap(stmt => emitStmt(stmt))
        wenLines ++ wdataLines ++ updateLines
      case oa: OracleAtom =>
        val placeholders = oa.oraclePlaceholders.flatMap(stmt => emitStmt(stmt))
        val verify = oa.verifyStmt.toSeq.flatMap(stmt => emitStmt(stmt))
        placeholders ++ verify
      case ca: CommitAtom =>
        ca.commits.flatMap(stmt => emitStmt(stmt))
      case sa: ScalarAtom =>
        sa.stmts.flatMap(stmt => emitStmt(stmt))
    }
    header ++ body
  }
}
