package essent.simd

import firrtl.annotations._
import firrtl.ir._

sealed trait RegCategory
case object RegCat_Counter    extends RegCategory
case object RegCat_CondUpdate extends RegCategory
case object RegCat_Oracle     extends RegCategory
case object RegCat_Standard   extends RegCategory

case class CondUpdateInfo(wenExpr: Expression, wdataExpr: Expression)

sealed trait MuxHoldStrategy
case object MH_PrefixScan extends MuxHoldStrategy
case object MH_Serial     extends MuxHoldStrategy
case object MH_Fallback   extends MuxHoldStrategy

case class SIMDPlanAnnotation(
  categories:    Map[String, RegCategory],
  condUpdates:   Map[String, CondUpdateInfo],
  oracleTargets: Set[String],
  fvsOrder:      Seq[String],
  moduleOracleTargets: Map[String, String] = Map.empty,
  muxHoldStrategies:   Map[String, MuxHoldStrategy] = Map.empty,
  combOracleTargets:   Map[String, String] = Map.empty,
  combOracleFlatNames: Map[String, String] = Map.empty
) extends NoTargetAnnotation

case class VecStmtInfo(
  scalarSource: String,
  laneIndex:    Int,
  category:     Option[RegCategory],
  moduleName:   String
)

object SIMDConstants {
  val KnownSuffixes: Seq[String] = Seq(
    "$final_commit", "$next", "$oracle", "$wen", "$wdata", "$final", "$cache"
  )
}
