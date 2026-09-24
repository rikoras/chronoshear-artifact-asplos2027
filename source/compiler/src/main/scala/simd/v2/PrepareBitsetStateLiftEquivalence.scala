package essent.simd.v2

import essent.{EssentOptionsAnnotation, Extract, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency

import java.io.{File, FileWriter, PrintWriter}
import scala.collection.mutable
import scala.io.Source

/** Emit artifact-exact original/packed RTL pairs for every Small BOOM
  * TLFIFOFixer shape that owns a `flight` bitset. */
object PrepareBitsetStateLiftEquivalence {
  private case class Candidate(module: String, depth: Int,
      bankWidths: Seq[Int], firstMember: String)
  private val Candidates = Seq(
    Candidate("TLFIFOFixer", 16, Seq(16), "flight__0"),
    Candidate("TLFIFOFixer_2", 16, Seq(16), "flight_0"),
    Candidate("TLFIFOFixer_3", 21, Seq(21), "flight_0"),
    Candidate("TLFIFOFixer_4", 128, Seq(64, 64), "flight_0"))

  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      System.err.println(
        "Usage: PrepareBitsetStateLiftEquivalence <SmallBoomConfig.fir> <output-dir>")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    val output = new File(args(1)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    output.mkdirs()

    val source = Source.fromFile(input)
    val parsed = try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    val widthCompiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency[firrtl.passes.InferWidths]))
    val concrete = widthCompiler.execute(CircuitState(parsed, Seq.empty)).circuit
    val byName = concrete.modules.map(module => module.name -> module).toMap

    Candidates.foreach { candidate =>
      require(byName.contains(candidate.module),
        s"${candidate.module} is not present in $input")
      val closure = transitiveClosure(candidate.module, byName)
      val modules = concrete.modules.collect {
        case module if closure(module.name) => resolveReset(module)
      }
      val base = Circuit(concrete.info, modules, candidate.module)
      requireBoundPorts(base.modules.find(_.name == candidate.module).get)

      val compiler = new firrtl.stage.transforms.Compiler(Seq(
        Dependency(BitsetStateLift), Dependency(firrtl.passes.ExpandWhens)))
      val liftedState = compiler.execute(CircuitState(base, Seq(
        EssentOptionsAnnotation(OptFlags(simdV2 = true)),
        BitsetStateLiftConfigAnnotation(
          Set(s"${candidate.module}.flight"), minimumDepth = candidate.depth))))
      audit(candidate, liftedState)

      val originalName = candidate.module + "Original"
      val liftedName = candidate.module + "Lifted"
      val original = prefixHierarchy(base, originalName)
      val lifted = prefixHierarchy(liftedState.circuit, liftedName)
      val candidateOutput = new File(output, candidate.module)
      candidateOutput.mkdirs()
      writeText(new File(candidateOutput, s"$originalName.fir"), original.serialize)
      writeText(new File(candidateOutput, s"$liftedName.fir"), lifted.serialize)
      emitVerilog(original, new File(candidateOutput, s"$originalName.v"))
      emitVerilog(lifted, new File(candidateOutput, s"$liftedName.v"))
      println(s"[bitset-state-lift] prepared ${candidate.module}.flight: " +
        s"closure=${closure.size} depth=${candidate.depth} " +
        s"banks=${candidate.bankWidths.mkString(",")}")
    }
  }

  private def audit(candidate: Candidate, state: CircuitState): Unit = {
    val annotations = state.annotations.collect {
      case annotation: IndexedCounterBankStorageAnnotation
          if annotation.family == "flight" => annotation
    }
    require(annotations.size == 1,
      s"${candidate.module}: expected one bitset bank mapping, got $annotations")
    val annotation = annotations.head
    require(annotation.module == candidate.module &&
        annotation.membersByIndex.size == candidate.depth &&
        annotation.membersByIndex.head == candidate.firstMember &&
        annotation.banks.size == candidate.bankWidths.size,
      s"${candidate.module}: locked bitset geometry changed: $annotation")
    val top = state.circuit.modules.collectFirst {
      case module: Module if module.name == candidate.module => module
    }.get
    val registers = Extract.findInstancesOf[DefRegister](top.body)
    val banks = annotation.banks.map(name =>
      registers.find(_.name == name).getOrElse(throw new IllegalStateException(
        s"${candidate.module}: missing packed bank $name")))
    require(banks.map(register => firrtl.bitWidth(register.tpe).toInt) ==
        candidate.bankWidths,
      s"${candidate.module}: packed bank widths changed: ${banks.map(_.tpe)}")
    require(!registers.exists(_.name == "flight"),
      s"${candidate.module}: aggregate flight register remains after packing")
  }

  private def transitiveClosure(root: String,
      modules: Map[String, DefModule]): Set[String] = {
    val seen = mutable.LinkedHashSet(root)
    val pending = mutable.Queue(root)
    while (pending.nonEmpty) {
      val current = pending.dequeue()
      def walk(statement: Statement): Unit = statement match {
        case instance: DefInstance =>
          if (seen.add(instance.module)) pending.enqueue(instance.module)
        case other => other.foreachStmt(walk)
      }
      modules(current).foreachStmt(walk)
    }
    seen.toSet
  }

  private def resolveReset(module: DefModule): DefModule = {
    val bool = UIntType(IntWidth(1))
    def tpe(value: Type): Type = value match {
      case ResetType => bool
      case other => other.mapType(tpe)
    }
    def expression(value: Expression): Expression = value match {
      case ref: WRef if ref.tpe == ResetType => ref.copy(tpe = bool)
      case ref: Reference if ref.tpe == ResetType => ref.copy(tpe = bool)
      case other => other.mapExpr(expression)
    }
    def statement(value: Statement): Statement =
      value.mapStmt(statement).mapExpr(expression).mapType(tpe)
    val ports = module.ports.map(port => port.copy(tpe = tpe(port.tpe)))
    module match {
      case concrete: Module => concrete.copy(ports = ports, body = statement(concrete.body))
      case other => other.mapPort(port => port.copy(tpe = tpe(port.tpe)))
    }
  }

  private def requireBoundPorts(module: DefModule): Unit = {
    val unknown = mutable.ArrayBuffer[String]()
    def walk(path: String, value: Type): Unit = value match {
      case UIntType(UnknownWidth) | SIntType(UnknownWidth) => unknown += path
      case BundleType(fields) => fields.foreach(field => walk(s"$path.${field.name}", field.tpe))
      case VectorType(element, size) if size > 0 => walk(s"$path[0]", element)
      case _ =>
    }
    module.ports.foreach(port => walk(port.name, port.tpe))
    require(unknown.isEmpty,
      s"${module.name} has parent-inferred port width(s): ${unknown.mkString(",")}")
  }

  private def prefixHierarchy(circuit: Circuit, topName: String): Circuit = {
    val mapping = circuit.modules.map { module =>
      module.name -> (if (module.name == circuit.main) topName
        else s"${topName}__${module.name}")
    }.toMap
    def rename(statement: Statement): Statement = statement match {
      case instance: WDefInstance =>
        instance.copy(module = mapping.getOrElse(instance.module, instance.module))
      case other => other.mapStmt(rename)
    }
    val modules = circuit.modules.map {
      case module: Module => module.copy(
        name = mapping(module.name), body = rename(module.body))
      case module: ExtModule => module.copy(name = mapping(module.name))
    }
    circuit.copy(modules = modules, main = topName)
  }

  private def emitVerilog(circuit: Circuit, file: File): Unit = {
    val result = new VerilogCompiler().compileAndEmit(CircuitState(circuit, Seq.empty))
    val bodies = result.annotations.collect {
      case annotation: EmittedVerilogCircuitAnnotation => annotation.value.value
      case annotation: EmittedVerilogModuleAnnotation => annotation.value.value
    }
    require(bodies.nonEmpty, s"VerilogCompiler emitted no Verilog for ${circuit.main}")
    writeText(file, bodies.mkString("\n"))
  }

  private def writeText(file: File, body: String): Unit = {
    val writer = new PrintWriter(new FileWriter(file))
    try writer.print(body)
    finally writer.close()
  }
}
