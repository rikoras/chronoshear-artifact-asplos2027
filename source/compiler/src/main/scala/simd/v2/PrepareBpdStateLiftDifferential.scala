package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency

import java.io.{File, FileWriter, PrintWriter}
import scala.io.Source

/** Extract the exact LoopBranchPredictorColumn from a RepCut FIRRTL file and
  * emit independently named original/lifted Verilog modules for differential
  * simulation.  This is an evidence generator, not a replacement DUT source.
  */
object PrepareBpdStateLiftDifferential {
  private val SourceModule = "LoopBranchPredictorColumn"
  private val OriginalName = "BpdOriginal"
  private val LiftedName = "BpdLifted"
  private val FieldGroups = Seq(
    Set("tag", "conf", "p_cnt"), Set("age"), Set("s_cnt"))

  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      System.err.println(
        "Usage: PrepareBpdStateLiftDifferential <SmallBoomConfig.fir> <output-dir>")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    val output = new File(args(1)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    output.mkdirs()

    val source = Source.fromFile(input)
    val parsed = try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    val sourceModule = parsed.modules.collectFirst {
      case m: Module if m.name == SourceModule => m
    }.getOrElse(throw new IllegalStateException(
      s"$SourceModule is not present in $input"))

    def isolated(name: String): Circuit = {
      val u1 = UIntType(IntWidth(1))
      val u37 = UIntType(IntWidth(37))
      def concretePortType(tpe: Type): Type = tpe match {
        case BundleType(fields) => BundleType(fields.map { field =>
          if (Set("f2_req_idx", "update_idx").contains(field.name))
            field.copy(tpe = u37)
          else field.copy(tpe = concretePortType(field.tpe))
        })
        case other => other
      }
      def concreteResetExpr(e: Expression): Expression = e match {
        case w: WRef if w.name == "reset" && w.tpe == ResetType => w.copy(tpe = u1)
        case other => other.mapExpr(concreteResetExpr)
      }
      def concreteResetStmt(s: Statement): Statement =
        s.mapStmt(concreteResetStmt).mapExpr(concreteResetExpr)
      // The parent TestHarness resolves this abstract Chisel Reset to a
      // one-bit synchronous reset.  An extracted module has no parent, so
      // make the same resolution explicitly and identically on both sides.
      val ports = sourceModule.ports.map {
        case p if p.name == "reset" && p.tpe == ResetType => p.copy(tpe = u1)
        case p => p.copy(tpe = concretePortType(p.tpe))
      }
      val module = sourceModule.copy(
        name = name, ports = ports, body = concreteResetStmt(sourceModule.body))
      Circuit(parsed.info, Seq(module), name)
    }

    val original = isolated(OriginalName)
    val liftInput = isolated(LiftedName)
    val opt = OptFlags(simdV2 = true)
    // StateArrayLift intentionally runs before ExpandWhens so it can recover
    // source write guards.  Include the immediately following production
    // pass here as well; its job includes lifting branch-local temporaries
    // referenced by the new root-level memory-port connects.
    val liftCompiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency(StateArrayLift), Dependency(firrtl.passes.ExpandWhens)))
    val liftedState = liftCompiler.execute(CircuitState(liftInput, Seq(
      EssentOptionsAnnotation(opt),
      StateArrayLiftConfigAnnotation(Set("entries"), Set.empty, FieldGroups))))
    val lifted = liftedState.circuit
    val storage = liftedState.annotations.collect {
      case a: StateArrayStorageAnnotation => a
    }
    require(storage.size == 3,
      s"expected exactly three compiler-owned BPD memories, got ${storage.size}")
    require(storage.map(_.fields.toSet).toSet == FieldGroups.toSet,
      s"lifted BPD field groups changed: ${storage.map(_.fields.mkString(",")).mkString(";")}")

    writeText(new File(output, s"$OriginalName.fir"), original.serialize)
    writeText(new File(output, s"$LiftedName.fir"), lifted.serialize)
    emitVerilog(original, output)
    emitVerilog(lifted, output)
    println(s"Prepared artifact BPD differential under $output")
  }

  private def emitVerilog(circuit: Circuit, output: File): Unit = {
    val result = new VerilogCompiler().compileAndEmit(CircuitState(circuit, Seq.empty))
    val emitted = result.annotations.collect {
      case a: EmittedVerilogCircuitAnnotation =>
        (a.value.name, a.value.outputSuffix, a.value.value)
      case a: EmittedVerilogModuleAnnotation =>
        (a.value.name, a.value.outputSuffix, a.value.value)
    }
    require(emitted.nonEmpty, s"VerilogCompiler emitted no Verilog for ${circuit.main}")
    emitted.foreach { case (name, suffix, body) =>
      writeText(new File(output, name + suffix), body)
    }
  }

  private def writeText(file: File, body: String): Unit = {
    val writer = new PrintWriter(new FileWriter(file))
    try writer.print(body) finally writer.close()
  }
}
