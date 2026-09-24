package essent.simd

import essent.ir._
import firrtl.ir._

import scala.collection.mutable

/**
 * Attaches lane identity to FIRRTL statement `info` fields.
 *
 * Vectorize stamps every cloned statement with a LaneTag via `info ++ LaneTag(src, idx)`.
 * Standard FIRRTL passes (LowerTypes, SplitExpressions, ConstantPropagation, etc.)
 * preserve statement `info`, so the tag propagates through the pipeline.
 *
 * Downstream passes extract lane metadata directly from LaneTags via `buildModuleLookup`,
 * eliminating the need for a centralized VecMetadataAnnotation reconciliation pass.
 */
object LaneTag {
  private val Prefix = "LANE:"
  private val TagPattern = """LANE:([^:]*):(\d+)""".r

  def apply(scalarSource: String, laneIndex: Int): Info =
    FileInfo(s"$Prefix$scalarSource:$laneIndex")

  def extract(info: Info): Option[(String, Int)] = info match {
    case fi: FileInfo =>
      fi.escaped match {
        case TagPattern(src, idx) => Some((src, idx.toInt))
        case _ => None
      }
    case MultiInfo(infos) =>
      infos.iterator.map(extract).collectFirst { case Some(v) => v }
    case NoInfo => None
  }

  def attach(existingInfo: Info, scalarSource: String, laneIndex: Int): Info =
    existingInfo ++ apply(scalarSource, laneIndex)

  /** Strip the `_lane_N` segment from a flattened lane name, yielding the scalar name.
    *
    * `io_lane_0_imem_req_valid` → `io_imem_req_valid`; `reg_lane_3` → `reg`.
    *
    * This is the ONLY sanctioned lane→scalar name transform. It depends solely on
    * the `_lane_N` convention Vectorize itself inserts (guarded by its name-clash
    * check), NOT on the LaneTag scalarSource payload — whose shape varies by
    * statement kind (short name for DefNode/DefRegister, full path for Connect) —
    * and NOT on how LowerTypes rewrites names. Do not reintroduce
    * `scalarSource + suffix` style path reconstruction anywhere.
    */
  def stripLaneSegment(name: String, laneIndex: Int): Option[String] = {
    val tag = s"_lane_$laneIndex"
    val pos = name.indexOf(tag)
    if (pos < 0) None
    else {
      val end = pos + tag.length
      // Reject prefix hits like `_lane_1` matching inside `_lane_12`.
      if (end < name.length && name.charAt(end).isDigit) None
      else Some(name.take(pos) + name.drop(end))
    }
  }

  /**
   * Walk a module body and build a name → VecStmtInfo lookup from LaneTags.
   * This is the single point-of-use replacement for the old EnrichVecMeta pass:
   * each consumer calls this on the module body it is currently processing.
   */
  def buildModuleLookup(body: Statement, moduleName: String): Map[String, VecStmtInfo] = {
    val result = mutable.Map[String, VecStmtInfo]()
    flattenStmts(body).foreach { stmt =>
      resultName(stmt).foreach { name =>
        extract(stmtInfo(stmt)).foreach { case (src, lane) =>
          result(name) = VecStmtInfo(src, lane, None, moduleName)
        }
      }
    }
    result.toMap
  }

  private def stmtInfo(stmt: Statement): Info = stmt match {
    case d: DefNode      => d.info
    case c: Connect      => c.info
    case r: DefRegister  => r.info
    case m: DefMemory    => m.info
    case w: DefWire      => w.info
    case iv: IsInvalid   => iv.info
    case _               => NoInfo
  }

  private def resultName(stmt: Statement): Option[String] = {
    import essent.Emitter.emitExpr
    stmt match {
      case d: DefNode        => Some(d.name)
      case c: Connect        => Some(emitExpr(c.loc))
      case r: DefRegister    => Some(r.name)
      case m: DefMemory      => Some(m.name)
      case w: DefWire        => Some(w.name)
      case ru: RegUpdate     => Some(emitExpr(ru.regRef))
      case cru: CondRegUpdate => Some(emitExpr(cru.regRef))
      case _                 => None
    }
  }

  private def flattenStmts(s: Statement): Seq[Statement] = s match {
    case b: Block => b.stmts.flatMap(flattenStmts)
    case EmptyStmt => Seq.empty
    case other => Seq(other)
  }
}
