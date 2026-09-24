package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency

import java.io.{File, FileWriter, PrintWriter}
import scala.collection.mutable
import scala.io.Source

/** Prepare exact original/lifted RTL pairs for the four additional Small BOOM
  * payload arrays under evaluation.  Width inference deliberately runs on the
  * complete locked TestHarness before extraction: FetchTargetQueue has two
  * parent-inferred port leaves, and specializing them after isolation would
  * no longer test the artifact instance used by CHISA.
  *
  * Only the named payload/tag backing moves.  Valid bits, hit logic, refill,
  * replacement, exception handling, FTQ enqueue/dequeue control, and every
  * protocol state machine remain in the original RTL modules.
  */
object PreparePeripheralStateLiftEquivalence {
  private case class Candidate(
    module: String,
    register: String,
    fieldGroups: Seq[Set[String]],
    depth: Int,
    width: Int,
    reads: Int,
    writes: Int,
    fields: Set[String])

  private val FtqFields = Set(
    "cfi_idx.valid", "cfi_idx.bits", "cfi_taken", "cfi_mispredicted",
    "cfi_type", "br_mask", "cfi_is_call", "cfi_is_ret", "cfi_npc_plus4",
    "ras_top", "ras_idx", "start_bank")
  private val Candidates = Seq(
    Candidate("FetchTargetQueue", "ram", Seq(FtqFields),
      depth = 16, width = 61, reads = 4, writes = 2, fields = FtqFields),
    Candidate("TLB", "superpage_entries", Seq(Set("level", "tag")),
      depth = 4, width = 29, reads = 4, writes = 4, fields = Set("level", "tag")),
    Candidate("NBDTLB", "superpage_entries", Seq(Set("level", "tag")),
      depth = 4, width = 29, reads = 4, writes = 4, fields = Set("level", "tag")),
    Candidate("PTW", "tags", Seq(Set("data")),
      depth = 8, width = 32, reads = 8, writes = 1, fields = Set("data")))

  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      System.err.println(
        "Usage: PreparePeripheralStateLiftEquivalence <SmallBoomConfig.fir> <output-dir>")
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
    val moduleByName = concrete.modules.map(module => module.name -> module).toMap

    Candidates.foreach { candidate =>
      require(moduleByName.contains(candidate.module),
        s"${candidate.module} is not present in $input")
      val closure = transitiveClosure(candidate.module, moduleByName)
      val missing = closure.filterNot(moduleByName.contains)
      require(missing.isEmpty,
        s"${candidate.module} instantiates absent modules: ${missing.mkString(",")}")
      val modules = concrete.modules.collect {
        case module if closure.contains(module.name) => resolveReset(module)
      }
      val base = Circuit(concrete.info, modules, candidate.module)
      requireBoundPorts(base.modules.find(_.name == candidate.module).get)

      val liftCompiler = new firrtl.stage.transforms.Compiler(Seq(
        Dependency(StateArrayLift), Dependency(firrtl.passes.ExpandWhens)))
      val liftedState = liftCompiler.execute(CircuitState(base, Seq(
        EssentOptionsAnnotation(OptFlags(simdV2 = true)),
        StateArrayLiftConfigAnnotation(
          Set(candidate.register), Set.empty, candidate.fieldGroups))))
      auditStorage(candidate, liftedState)

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
      println(s"[peripheral-lift] prepared ${candidate.module}: " +
        s"closure=${closure.size} depth=${candidate.depth} width=${candidate.width} " +
        s"reads=${candidate.reads} writes=${candidate.writes}")
    }
  }

  private def auditStorage(candidate: Candidate, state: CircuitState): Unit = {
    val storage = state.annotations.collect {
      case annotation: StateArrayStorageAnnotation => annotation
    }
    require(storage.size == 1,
      s"${candidate.module}: expected one compiler-owned memory, got ${storage.size}: $storage")
    val annotation = storage.head
    require(annotation.module == candidate.module &&
        annotation.register == candidate.register &&
        annotation.depth == candidate.depth &&
        annotation.packedWidth == candidate.width &&
        annotation.readPorts == candidate.reads &&
        annotation.fields.toSet == candidate.fields,
      s"${candidate.module}: Small artifact storage geometry changed: $annotation")
    val top = state.circuit.modules.collectFirst {
      case module: Module if module.name == candidate.module => module
    }.getOrElse(throw new IllegalStateException(
      s"missing ${candidate.module} after state lifting"))
    val writerCounts = mutable.Map[String, Int]()
    def walk(statement: Statement): Unit = statement match {
      case memory: DefMemory => writerCounts(memory.name) = memory.writers.size
      case other => other.foreachStmt(walk)
    }
    walk(top.body)
    require(writerCounts.get(annotation.memory).contains(candidate.writes),
      s"${candidate.module}: expected ${candidate.writes} writer(s) for " +
        s"${annotation.memory}, got ${writerCounts.get(annotation.memory)}")
  }

  private def transitiveClosure(
      root: String, modules: Map[String, DefModule]): Set[String] = {
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

  /** The artifact resolves abstract reset ports to synchronous UInt<1>. */
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
      s"${module.name} still has unknown port widths after global inference: ${unknown.mkString(",")}")
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
    try writer.print(body) finally writer.close()
  }
}
