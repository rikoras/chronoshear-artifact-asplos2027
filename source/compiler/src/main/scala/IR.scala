package essent.ir

import firrtl._
import firrtl.ir._

// ESSENT's additions to the IR for optimization

case class RegUpdate(info: Info, regRef: Expression, expr: Expression) extends Statement {
  def serialize: String =  s"${regRef.serialize} <= ${expr.serialize}" + info.serialize
  def mapStmt(f: Statement => Statement): Statement = this
  def mapExpr(f: Expression => Expression): Statement = this.copy(regRef = f(regRef), expr = f(expr))
  def mapType(f: Type => Type): Statement = this
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  def foreachExpr(f: Expression => Unit): Unit = { f(regRef); f(expr) }
  def foreachInfo(f: Info => Unit): Unit = f(info)
  def foreachStmt(f: Statement => Unit): Unit = ()
  def foreachString(f: String => Unit): Unit = ()
  def foreachType(f: Type => Unit): Unit = ()
}

/** Conditional register update: `if (cond) reg = expr`.
  * Unlike RegUpdate, the dependency set does NOT include regRef —
  * only cond and expr are dependencies. This breaks self-loops
  * for mux-hold registers. */
case class CondRegUpdate(info: Info, cond: Expression, regRef: Expression, expr: Expression) extends Statement {
  def serialize: String = s"if (${cond.serialize}) ${regRef.serialize} <= ${expr.serialize}" + info.serialize
  def mapStmt(f: Statement => Statement): Statement = this
  def mapExpr(f: Expression => Expression): Statement = this.copy(cond = f(cond), regRef = f(regRef), expr = f(expr))
  def mapType(f: Type => Type): Statement = this
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  // regRef is intentionally included: foreachExpr traverses ALL sub-expressions.
  // Dependency analysis (findDependencesStmt) manually excludes regRef as a read dep.
  def foreachExpr(f: Expression => Unit): Unit = { f(cond); f(regRef); f(expr) }
  def foreachInfo(f: Info => Unit): Unit = f(info)
  def foreachStmt(f: Statement => Unit): Unit = ()
  def foreachString(f: String => Unit): Unit = ()
  def foreachType(f: Type => Unit): Unit = ()
}

case class MemWrite(memName: String,
                    portName: String,
                    wrEn: Expression,
                    wrMask: Expression,
                    wrAddr: Expression,
                    wrData: Expression) extends Statement {
  def serialize: String = s"if (${wrEn.serialize} && ${wrMask.serialize}) $memName[${wrAddr.serialize}] = ${wrData.serialize}"
  def mapStmt(f: Statement => Statement): Statement = this
  def mapExpr(f: Expression => Expression): Statement = {
    MemWrite(memName, portName, f(wrEn), f(wrMask), f(wrAddr), f(wrData))
  }
  def mapType(f: Type => Type): Statement = this
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  def nodeName(): String = s"$memName.$portName"
  def foreachExpr(f: Expression => Unit): Unit = { f(wrEn); f(wrMask); f(wrAddr); f(wrData) }
  def foreachInfo(f: Info => Unit): Unit = ()
  def foreachStmt(f: Statement => Unit): Unit = ()
  def foreachString(f: String => Unit): Unit = { f(memName); f(portName) }
  def foreachType(f: Type => Unit): Unit = ()
}

case class LBNVerify(info: Info, regRef: Expression, oracleRef: Expression) extends Statement {
  def serialize: String = s"assert(${regRef.serialize} == ${oracleRef.serialize})" + info.serialize
  def mapStmt(f: Statement => Statement): Statement = this
  def mapExpr(f: Expression => Expression): Statement = this.copy(regRef = f(regRef), oracleRef = f(oracleRef))
  def mapType(f: Type => Type): Statement = this
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  def foreachExpr(f: firrtl.ir.Expression => Unit): Unit = { f(regRef); f(oracleRef) }
  def foreachInfo(f: firrtl.ir.Info => Unit): Unit = f(info)
  def foreachStmt(f: firrtl.ir.Statement => Unit): Unit = ()
  def foreachString(f: String => Unit): Unit = ()
  def foreachType(f: firrtl.ir.Type => Unit): Unit = ()
}

case class LookupTable(
    name: String,
    indexExpr: Expression,
    entries: Seq[BigInt],
    resultType: Type,
    // Perf: bitmap=true encodes a 1-bit set-membership test (result is bit
    // `indexExpr` of the packed `entries` words) instead of a dense value
    // table. Used to collapse wide OR-of-equality chains — e.g. Rocket's
    // 100-term CSR-address decode, which otherwise compiles to a serial
    // ~730-op k-mask reduction chain — into one load + shift + mask per lane.
    bitmap: Boolean = false) extends Statement {
  def serialize: String =
    s"$name = ${if (bitmap) "bitmap-lut" else "lut"}[${indexExpr.serialize}] (${entries.size} entries)"
  def mapStmt(f: Statement => Statement): Statement = this
  def mapExpr(f: Expression => Expression): Statement = this.copy(indexExpr = f(indexExpr))
  def mapType(f: Type => Type): Statement = this.copy(resultType = f(resultType))
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  def foreachExpr(f: Expression => Unit): Unit = f(indexExpr)
  def foreachInfo(f: Info => Unit): Unit = ()
  def foreachStmt(f: Statement => Unit): Unit = ()
  def foreachString(f: String => Unit): Unit = ()
  def foreachType(f: Type => Unit): Unit = f(resultType)
}

case class CondMux(name: String, mux: Mux, tWay: Seq[Statement], fWay: Seq[Statement]) extends Statement {
  def serialize: String =  "conditional mux"
  def mapStmt(f: Statement => Statement): Statement = this.copy(tWay = tWay map f, fWay = fWay map f)
  def mapExpr(f: Expression => Expression): Statement = this
  def mapType(f: Type => Type): Statement = this
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  def foreachExpr(f: Expression => Unit): Unit = { f(mux.cond); f(mux.tval); f(mux.fval) }
  def foreachInfo(f: Info => Unit): Unit = ()
  def foreachStmt(f: Statement => Unit): Unit = { tWay.foreach(f); fWay.foreach(f) }
  def foreachString(f: String => Unit): Unit = f(name)
  def foreachType(f: Type => Unit): Unit = ()
}

case class CondPart(
    id: Int,
    alwaysActive: Boolean,
    inputs: Seq[String],
    memberStmts: Seq[Statement],
    outputsToDeclare: Map[String,firrtl.ir.Type]) extends Statement {
  def serialize: String = s"CondPart #$id"
  def mapStmt(f: Statement => Statement): Statement = this.copy(memberStmts = memberStmts map f)
  def mapExpr(f: Expression => Expression): Statement = this
  def mapType(f: Type => Type): Statement = this
  def mapString(f: String => String): Statement = this
  def mapInfo(f: Info => Info): Statement = this
  def foreachExpr(f: Expression => Unit): Unit = ()
  def foreachInfo(f: Info => Unit): Unit = ()
  def foreachStmt(f: Statement => Unit): Unit = memberStmts.foreach(f)
  def foreachString(f: String => Unit): Unit = ()
  def foreachType(f: Type => Unit): Unit = outputsToDeclare.values.foreach(f)
}
