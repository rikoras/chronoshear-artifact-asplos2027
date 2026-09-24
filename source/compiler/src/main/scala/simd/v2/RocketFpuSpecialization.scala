package essent.simd.v2

import essent.{EssentCompiler, EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency
import org.json4s.DefaultFormats
import org.json4s.native.Serialization.writePretty

import java.io.{File, PrintWriter}
import scala.collection.mutable
import scala.io.Source

/** CP observability proof using the same LowForm/DCE stack as the producers.
  * No workload inputs or DUT taps participate in this proof.
  */
object RocketFpuSpecialization {
  val QualifiedFirrtlSha256 = "5b8dc10f26513d19f50d8f185aabb2b648d2f7f535e9414d181a0e4e1d56f6b8"
  val Defname = "CHISARocketFPUCoreModel"
  val Policy = "defaultconfig-cp-inactive"
  private val CpOutputs = Seq("io_cp_req_ready", "io_cp_resp_valid", "io_cp_resp_bits_data", "io_cp_resp_bits_exc")
  private val CpInputs = "io_cp_req_"

  case class StageProof(profile: String, cpValidDriver: String,
      parentOutputReaders: Map[String, Int], survivingFpuCpPorts: Seq[String])
  case class Proof(schemaVersion: Int, cpInactive: Boolean, cpOutputsUnobserved: Boolean,
      stages: Seq[StageProof])
  case class Specialized(circuit: Circuit, proof: Proof)

  private[v2] def corePorts(ports: Seq[Port]): Seq[Port] = ports.map {
    case p @ Port(_, "io", _, BundleType(fields)) =>
      require(fields.count(f => f.name == "cp_req" || f.name == "cp_resp") == 2,
        "FPU specialization requires both original CP bundles")
      p.copy(tpe = BundleType(fields.filterNot(f => f.name == "cp_req" || f.name == "cp_resp")))
    case other => other
  }

  /** Remove the proven-unobserved CP interface, not its values. The remaining
    * FPU core interface is a real ExtModule implemented by the native model.
    */
  def specialize(circuit: Circuit): Specialized = {
    val proof = prove(circuit)
    val fpu = concrete(circuit, "FPU")
    val external = ExtModule(fpu.info, fpu.name, corePorts(fpu.ports), Defname, Seq.empty)
    val byName = circuit.modules.map(m => m.name -> (if (m.name == "FPU") external else m)).toMap
    val reachable = mutable.Set[String]()
    def visit(name: String): Unit = if (reachable.add(name)) {
      byName(name) match {
        case m: Module =>
          def walk(s: Statement): Unit = s match {
            case i: DefInstance => visit(i.module)
            case other => other.foreachStmt(walk)
          }
          walk(m.body)
        case _: ExtModule =>
      }
    }
    visit(circuit.main)
    Specialized(circuit.copy(modules = circuit.modules.filter(m => reachable(m.name)).map(m => byName(m.name))), proof)
  }

  private def requireTargetScope(circuit: Circuit): Unit = {
    val byName = circuit.modules.map(m => m.name -> m).toMap
    val owners = mutable.ArrayBuffer[(String, String)]()
    def visit(name: String, ancestors: Set[String]): Unit = {
      require(!ancestors(name), s"recursive hierarchy in FPU proof: $name")
      byName(name) match {
        case m: Module =>
          def walk(s: Statement): Unit = s match {
            case i: DefInstance =>
              if (i.module == "FPU") owners += name -> i.name
              visit(i.module, ancestors + name)
            case other => other.foreachStmt(walk)
          }
          walk(m.body)
        case _: ExtModule =>
      }
    }
    visit(circuit.main, Set.empty)
    require(owners.toSeq == Seq("RocketTile" -> "fpuOpt"),
      s"CP proof requires the unique reachable RocketTile.fpuOpt, found ${owners.mkString(", ")}")
  }

  private def concrete(circuit: Circuit, name: String): Module = circuit.modules.find(_.name == name) match {
    case Some(m: Module) => m
    case _ => throw new IllegalArgumentException(s"FPU proof requires concrete module $name")
  }

  private def reads(module: Module, targets: Set[String]): Map[String, Int] = {
    val counts = mutable.Map(targets.toSeq.map(_ -> 0): _*)
    def expression(e: Expression): Unit = {
      if (targets(e.serialize)) counts(e.serialize) += 1
      else e.foreachExpr(expression)
    }
    def statement(s: Statement): Unit = s match {
      case c: Connect => expression(c.expr)
      case c: PartialConnect => expression(c.expr)
      case other => other.foreachExpr(expression); other.foreachStmt(statement)
    }
    statement(module.body)
    counts.toMap
  }

  private def drivers(module: Module, target: String): Seq[Expression] = {
    val found = mutable.ArrayBuffer[Expression]()
    def visit(s: Statement): Unit = s match {
      case c: Connect if c.loc.serialize == target => found += c.expr
      case other => other.foreachStmt(visit)
    }
    visit(module.body)
    found.toSeq
  }

  private[v2] def beforeDce(circuit: Circuit): Circuit = {
    val dependencies = firrtl.stage.Forms.LowForm ++ Seq(Dependency(firrtl.passes.RemoveValidIf))
    new firrtl.stage.transforms.Compiler(dependencies).execute(CircuitState(circuit, Seq.empty)).circuit
  }

  private[v2] def lowered(circuit: Circuit, scalar: Boolean): Circuit = {
    val opt = OptFlags(simdV2 = !scalar, vectorWidth = 1, clockDomainLowering = true,
      scalarFastEdgeCommit = scalar, scalarDropSourceEffects = scalar, noDefaultMain = true)
    new firrtl.stage.transforms.Compiler(new EssentCompiler(opt).readyForEssent)
      .execute(CircuitState(circuit, Seq(EssentOptionsAnnotation(opt)))).circuit
  }

  private def snapshot(circuit: Circuit, profile: String, output: Option[File]): StageProof = {
    val parent = concrete(circuit, "RocketTile")
    val fpu = concrete(circuit, "FPU")
    val cpDriver = drivers(parent, "fpuOpt.io_cp_req_valid")
    val readerCounts = reads(parent, CpOutputs.map("fpuOpt." + _).toSet)
    val cpPorts = fpu.ports.filter(p => p.name.startsWith(CpInputs) || p.name.startsWith("io_cp_resp_")).map(_.name)
    output.foreach { directory =>
      directory.mkdirs()
      Seq(parent, fpu).foreach { module =>
        val writer = new PrintWriter(new File(directory, s"$profile-${module.name}.fir"))
        try writer.print(module.serialize) finally writer.close()
      }
    }
    StageProof(profile, cpDriver.map(_.serialize).mkString("; "), readerCounts, cpPorts)
  }

  def prove(circuit: Circuit, output: Option[File] = None): Proof = {
    requireTargetScope(circuit)
    val before = beforeDce(circuit)
    val raw = snapshot(before, "before-dce", output)
    val valid = drivers(concrete(before, "RocketTile"), "fpuOpt.io_cp_req_valid")
    require(valid.size == 1 && valid.head == UIntLiteral(0, IntWidth(1)),
      s"CP valid is not structurally zero after RemoveValidIf: ${raw.cpValidDriver}")
    require(raw.parentOutputReaders.values.forall(_ == 0), s"CP outputs have parent readers: ${raw.parentOutputReaders}")
    require(reads(concrete(before, "FPU"), Set("io_cp_resp_ready")).values.forall(_ == 0),
      "FPU reads CP response ready")
    val stages = Seq(raw) ++ Seq(false, true).map { scalar =>
      val stage = snapshot(lowered(circuit, scalar), if (scalar) "scalar-optimized" else "v2", output)
      require(stage.parentOutputReaders.values.forall(_ == 0), s"CP outputs survive in ${stage.profile}")
      require(stage.survivingFpuCpPorts.isEmpty,
        s"CP ports remain after ${stage.profile} lowering/DCE: ${stage.survivingFpuCpPorts.mkString(", ")}")
      stage
    }
    Proof(1, cpInactive = true, cpOutputsUnobserved = true, stages)
  }

  def main(args: Array[String]): Unit = {
    require(args.length == 2, "usage: RocketFpuSpecialization <RocketCold.fir> <output-dir>")
    val source = Source.fromFile(args(0))
    val circuit = try Parser.parse(source.getLines(), Parser.IgnoreInfo) finally source.close()
    val output = new File(args(1))
    val proof = prove(circuit, Some(output))
    implicit val formats = DefaultFormats
    val writer = new PrintWriter(new File(output, "cp-proof.json"))
    try writer.println(writePretty(proof)) finally writer.close()
    println("ROCKET_FPU_CP_PROOF cp_valid=0 cp_output_readers=0")
  }
}
