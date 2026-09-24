package essent

import firrtl.Parser
import firrtl.ir._

object DebugUnknownTypes {
  def main(args: Array[String]): Unit = {
    if (args.length != 1) {
      System.err.println("Usage: runMain essent.DebugUnknownTypes <file.fir>")
      sys.exit(2)
    }

    val source = scala.io.Source.fromFile(args(0))
    val circuit = try {
      Parser.parse(source.getLines(), Parser.IgnoreInfo)
    } finally {
      source.close()
    }

    def hasUnknownType(tpe: Type): Boolean = tpe match {
      case UnknownType => true
      case BundleType(fields) => fields.exists(f => hasUnknownType(f.tpe))
      case VectorType(t, _) => hasUnknownType(t)
      case _ => false
    }

    def exprType(e: Expression): Type = e match {
      case r: Reference => r.tpe
      case s: SubField => s.tpe
      case s: SubIndex => s.tpe
      case s: SubAccess => s.tpe
      case p: DoPrim => p.tpe
      case m: Mux => m.tpe
      case v: ValidIf => v.tpe
      case l: Literal => l.tpe
    }

    def walkExpr(expr: Expression, path: String): Unit = {
      if (hasUnknownType(exprType(expr))) {
        println(s"[expr] $path :: ${expr.serialize} :: ${exprType(expr)}")
      }
      expr match {
        case _: Reference | _: Literal => ()
        case s: SubField => walkExpr(s.expr, s"$path.subfield(${s.name})")
        case s: SubIndex => walkExpr(s.expr, s"$path.subindex(${s.value})")
        case s: SubAccess =>
          walkExpr(s.expr, s"$path.subaccess.expr")
          walkExpr(s.index, s"$path.subaccess.index")
        case p: DoPrim => p.args.zipWithIndex.foreach { case (arg, idx) => walkExpr(arg, s"$path.primArg($idx)") }
        case m: Mux =>
          walkExpr(m.cond, s"$path.mux.cond")
          walkExpr(m.tval, s"$path.mux.t")
          walkExpr(m.fval, s"$path.mux.f")
        case v: ValidIf =>
          walkExpr(v.cond, s"$path.validif.cond")
          walkExpr(v.value, s"$path.validif.value")
      }
    }

    def walkStmt(stmt: Statement, path: String): Unit = {
      stmt match {
        case b: Block =>
          b.stmts.zipWithIndex.foreach { case (s, idx) => walkStmt(s, s"$path.block($idx)") }
        case c: Conditionally =>
          walkExpr(c.pred, s"$path.when.pred")
          walkStmt(c.conseq, s"$path.when.conseq")
          walkStmt(c.alt, s"$path.when.alt")
        case d: DefWire =>
          if (hasUnknownType(d.tpe)) println(s"[wire] $path :: ${d.name} :: ${d.tpe}")
        case d: DefNode =>
          walkExpr(d.value, s"$path.node(${d.name})")
        case c: Connect =>
          walkExpr(c.loc, s"$path.connect.loc")
          walkExpr(c.expr, s"$path.connect.expr")
        case p: PartialConnect =>
          walkExpr(p.loc, s"$path.pconnect.loc")
          walkExpr(p.expr, s"$path.pconnect.expr")
        case i: IsInvalid =>
          walkExpr(i.expr, s"$path.invalid")
        case m: DefMemory =>
          if (hasUnknownType(m.dataType)) println(s"[mem] $path :: ${m.name} :: ${m.dataType}")
        case r: DefRegister =>
          if (hasUnknownType(r.tpe)) println(s"[reg] $path :: ${r.name} :: ${r.tpe}")
          walkExpr(r.clock, s"$path.reg(${r.name}).clock")
          walkExpr(r.reset, s"$path.reg(${r.name}).reset")
          walkExpr(r.init, s"$path.reg(${r.name}).init")
        case p: Print =>
          p.args.zipWithIndex.foreach { case (arg, idx) => walkExpr(arg, s"$path.print($idx)") }
        case s: Stop =>
          walkExpr(s.en, s"$path.stop.en")
        case _: DefInstance | EmptyStmt => ()
        case other =>
          println(s"[stmt] unhandled ${other.getClass} at $path")
      }
    }

    circuit.modules.foreach {
      case m: Module =>
        m.ports.foreach { p =>
          if (hasUnknownType(p.tpe)) {
            println(s"[port] ${m.name}.${p.name} :: ${p.tpe}")
          }
        }
        walkStmt(m.body, s"module(${m.name})")
      case e: ExtModule =>
        e.ports.foreach { p =>
          if (hasUnknownType(p.tpe)) {
            println(s"[extport] ${e.name}.${p.name} :: ${p.tpe}")
          }
        }
    }
  }
}
