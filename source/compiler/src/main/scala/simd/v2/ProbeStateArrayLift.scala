package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.options.Dependency

import java.io.File
import scala.io.Source

/** Fast, non-emitting probe for aggregate state-array candidates in a real
  * FIRRTL circuit.  This runs the production StateArrayLift and its required
  * type/connect preparation, but stops before the expensive whole-design v2
  * graph and C++ emission.  It is intended for fail-fast storage-boundary
  * investigation, not as correctness evidence for an accepted lift.
  */
object ProbeStateArrayLift {
  def main(args: Array[String]): Unit = {
    if (args.length < 3) {
      System.err.println(
        "Usage: ProbeStateArrayLift <design.fir> <register[,register...]|*> " +
          "<field,group|-|--auto> [<field,group> ...]")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    val groupArgs = args.drop(2)
    val autoPack = groupArgs.length == 1 && groupArgs.head == "--auto"
    val groups = if (groupArgs.length == 1 &&
        (groupArgs.head == "-" || groupArgs.head == "--auto")) Seq.empty else
      groupArgs.toSeq.map { group =>
        group.split(',').map(_.trim).filter(_.nonEmpty).toSet
      }.filter(_.nonEmpty)

    val source = Source.fromFile(input)
    val circuit = try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    val requested = args(1).split(',').map(_.trim).filter(_.nonEmpty).toSet
    require(requested.nonEmpty, "at least one register name or '*' is required")
    val registers = if (requested("*")) {
      val found = scala.collection.mutable.LinkedHashSet[String]()
      def collect(statement: firrtl.ir.Statement): Unit = statement match {
        case register: firrtl.ir.DefRegister => register.tpe match {
          case firrtl.ir.VectorType(_, depth) if depth >= 2 => found += register.name
          case _ =>
        }
        case firrtl.ir.Block(statements) => statements.foreach(collect)
        case other => other.foreachStmt(collect)
      }
      circuit.modules.foreach {
        case module: firrtl.ir.Module => collect(module.body)
        case _ =>
      }
      found.toSet
    } else requested
    val compiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency(StateArrayLift), Dependency(firrtl.passes.ExpandWhens)))
    val result = compiler.execute(CircuitState(circuit, Seq(
      EssentOptionsAnnotation(OptFlags(simdV2 = true)),
      StateArrayLiftConfigAnnotation(registers, Set.empty, groups, autoPack))))
    val candidates = result.annotations.collect {
      case candidate: StateArrayCandidateAnnotation => candidate
    }
    val lifted = result.annotations.collect {
      case storage: StateArrayStorageAnnotation => storage
    }
    println(s"[v2-state-array-probe] candidates=${candidates.size} lifted=${lifted.size}")
    candidates.sortBy(candidate => (candidate.module, candidate.register)).foreach { candidate =>
      val counts = candidate.writeSites.toSeq.sortBy(_._1).map {
        case (field, count) =>
          s"$field:${candidate.fieldWidths.getOrElse(field, -1)}:$count"
      }.mkString(",")
      println(s"[v2-state-array-probe] candidate=${candidate.module}.${candidate.register} " +
        s"depth=${candidate.depth} fields=${candidate.fields.size} " +
        s"fieldWidthWrites=$counts")
    }
    lifted.sortBy(storage => (storage.module, storage.register, storage.memory)).foreach { storage =>
      println(s"[v2-state-array-probe] storage=${storage.module}.${storage.memory} " +
        s"source=${storage.register} depth=${storage.depth} width=${storage.packedWidth} " +
        s"fields=${storage.fields.mkString(",")} readPorts=${storage.readPorts}")
    }
  }
}
