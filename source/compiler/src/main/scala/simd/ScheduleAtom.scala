package essent.simd

import firrtl.ir._

sealed trait ScheduleAtom {
  def id: String
  def moduleName: String
  def deps: Set[String]
  def produces: Set[String]
}

case class ParallelAtom(
  id:           String,
  moduleName:   String,
  scalarSource: String,
  lanes:        IndexedSeq[Statement],
  deps:         Set[String],
  produces:     Set[String]
) extends ScheduleAtom

case class ShiftAtom(
  id:        String,
  moduleName: String,
  regName:   String,
  forward:   Boolean,
  shifts:    IndexedSeq[Statement],
  deps:      Set[String],
  produces:  Set[String]
) extends ScheduleAtom

case class CondUpdateAtom(
  id:        String,
  moduleName: String,
  regName:   String,
  wenAtom:   ParallelAtom,
  wdataAtom: ParallelAtom,
  updates:   IndexedSeq[Statement],
  deps:      Set[String],
  produces:  Set[String]
) extends ScheduleAtom

case class OracleAtom(
  id:                  String,
  moduleName:          String,
  regName:             String,
  oraclePlaceholders:  IndexedSeq[Statement],
  verifyStmt:          Option[Statement],
  deps:                Set[String],
  produces:            Set[String]
) extends ScheduleAtom

case class CommitAtom(
  id:       String,
  moduleName: String,
  regName:  String,
  commits:  IndexedSeq[Statement],
  deps:     Set[String],
  produces: Set[String]
) extends ScheduleAtom

case class ScalarAtom(
  id:        String,
  moduleName: String,
  stmts:     IndexedSeq[Statement],
  deps:      Set[String],
  produces:  Set[String]
) extends ScheduleAtom
