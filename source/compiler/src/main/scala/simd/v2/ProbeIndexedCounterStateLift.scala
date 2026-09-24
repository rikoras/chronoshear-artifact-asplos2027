package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.ir.{DefMemory, Module, Statement}
import firrtl.options.Dependency

import java.io.File
import scala.io.Source

/** Fast production-pattern probe for indexed scalar counter recovery.  It
  * parses and type-checks the real circuit, runs the exact transform, and
  * stops before graph construction/C++ emission.  Correctness acceptance is
  * provided separately by the original-vs-lifted differential gate.
  */
object ProbeIndexedCounterStateLift {
  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      System.err.println(
        "Usage: ProbeIndexedCounterStateLift <design.fir> <family[,family...]>")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    val families = args(1).split(',').map(_.trim).filter(_.nonEmpty).toSet
    require(families.nonEmpty, "at least one family is required")

    val source = Source.fromFile(input)
    val circuit = try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    val compiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency(IndexedCounterStateLift),
      Dependency(firrtl.passes.ExpandWhens)))
    val result = compiler.execute(CircuitState(circuit, Seq(
      EssentOptionsAnnotation(OptFlags(simdV2 = true)),
      IndexedCounterStateLiftConfigAnnotation(families))))
    val lifted = result.annotations.collect {
      case storage: StateArrayStorageAnnotation
          if storage.memory.startsWith("__v2_indexed_") => storage
    }
    println(s"[v2-indexed-state-probe] lifted=${lifted.size}")
    lifted.sortBy(storage => (storage.module, storage.register)).foreach { storage =>
      val writers = result.circuit.modules.collectFirst {
        case module: Module if module.name == storage.module =>
          var found = Option.empty[DefMemory]
          def walk(statement: Statement): Unit = statement match {
            case memory: DefMemory if memory.name == storage.memory => found = Some(memory)
            case other => other.foreachStmt(walk)
          }
          walk(module.body)
          found.map(_.writers.size).getOrElse(0)
      }.getOrElse(0)
      println(s"[v2-indexed-state-probe] storage=${storage.module}.${storage.memory} " +
        s"source=${storage.register} depth=${storage.depth} width=${storage.packedWidth} " +
        s"reads=${storage.readPorts} writes=$writers")
    }
  }
}
