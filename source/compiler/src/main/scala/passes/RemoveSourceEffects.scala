package essent.passes

import firrtl._
import firrtl.Mappers._
import firrtl.Utils._
import firrtl.ir._
import firrtl.options.Dependency
import firrtl.passes._

/** Remove source-level diagnostic effects before the optimized LowForm
  * pipeline runs.
  *
  * ConvertAsserts has already lowered FIRRTL verification assertions into
  * Print/Stop pairs.  Removing both effects here lets the ordinary FIRRTL
  * dead-code passes delete their otherwise-live protocol-monitor cones.  The
  * pass is not a default: the scalar full-chip producer opts in only when an
  * independent consumer retains Micro-Lockstep and final-state checking.
  */
object RemoveSourceEffects extends Pass {
  def desc = "Removes scalar producer source Print/Stop effects"

  override def prerequisites =
    Seq(Dependency(firrtl.transforms.formal.ConvertAsserts))
  override def optionalPrerequisites = Seq.empty
  override def optionalPrerequisiteOf = Seq(
    Dependency[firrtl.transforms.ConstantPropagation],
    Dependency[firrtl.transforms.DeadCodeElimination])
  override def invalidates(a: Transform) = false

  private def removeEffects(count: Array[Int])(stmt: Statement): Statement = {
    val retained = stmt match {
      case _: Print | _: Stop =>
        count(0) += 1
        EmptyStmt
      case other => other
    }
    retained.mapStmt(removeEffects(count))
  }

  private def onModule(count: Array[Int])(module: DefModule): DefModule =
    module match {
      case concrete: Module =>
        concrete.copy(body = squashEmpty(removeEffects(count)(concrete.body)))
      case external: ExtModule => external
    }

  def run(circuit: Circuit): Circuit = {
    val count = Array(0)
    val result = circuit.copy(modules = circuit.modules.map(onModule(count)))
    println(s"[scalar-source-effects] removed ${count(0)} Print/Stop effect(s)")
    result
  }
}
