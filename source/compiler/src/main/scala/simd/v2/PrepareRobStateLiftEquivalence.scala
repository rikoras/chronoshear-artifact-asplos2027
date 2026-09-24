package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency

import java.io.{File, FileWriter, PrintWriter}
import scala.io.Source

/** Extract the exact Small BOOM ROB and prepare an original/lifted Verilog
  * pair for sequential differential checking. The legacy 15-field pure
  * `rob_uop` payload group and four unreset ground-vector backings are moved.
  * An opt-in candidate also packs the active-reset `rob_val` bit vector into
  * one UInt<32> bank while retaining all of its indexed reads and writes. All
  * update enables, data, addresses, priorities, commit, rollback, flush,
  * exception, valid-bit reset, and retirement decisions remain in RTL.
  */
object PrepareRobStateLiftEquivalence {
  private val SourceModule = "Rob"
  private val OriginalName = "RobOriginal"
  private val LiftedName = "RobLifted"
  private val RobPayloadFields = Set(
    "uopc", "is_rvc", "ftq_idx", "edge_inst", "pc_lob", "pdst", "stale_pdst",
    "is_fencei", "uses_ldq", "uses_stq", "is_sys_pc2epc", "flush_on_commit",
    "ldst", "ldst_val", "dst_rtype")
  private val Registers = Set(
    "rob_uop", "rob_bsy", "rob_unsafe", "rob_exception", "rob_predicated")
  private val FieldGroups = Seq(RobPayloadFields, Set("data"))
  private val ExpectedStorage = Map(
    "rob_uop" -> (45, 6, 1, RobPayloadFields),
    "rob_bsy" -> (1, 7, 7, Set("data")),
    "rob_unsafe" -> (1, 34, 8, Set("data")),
    "rob_exception" -> (1, 34, 3, Set("data")),
    "rob_predicated" -> (1, 1, 5, Set("data")))

  def main(args: Array[String]): Unit = {
    val includeRobValBitset = args.length == 3 &&
      args(2) == "--include-rob-val-bitset"
    if (args.length != 2 && !includeRobValBitset) {
      System.err.println(
        "Usage: PrepareRobStateLiftEquivalence <SmallBoomConfig.fir> <output-dir> " +
          "[--include-rob-val-bitset]")
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
      case module: Module if module.name == SourceModule => module
    }.getOrElse(throw new IllegalStateException(
      s"$SourceModule is not present in $input"))
    var childInstances = Vector.empty[String]
    def collectInstances(statement: Statement): Unit = statement match {
      case instance: WDefInstance => childInstances :+= instance.name
      case other => other.foreachStmt(collectInstances)
    }
    collectInstances(sourceModule.body)
    require(childInstances.isEmpty,
      s"$SourceModule unexpectedly contains child instances: ${childInstances.mkString(",")}")

    def isolated(name: String): Circuit = {
      val targetOffsetType = SIntType(IntWidth(21))
      def concreteType(tpe: Type): Type = tpe match {
        case BundleType(fields) => BundleType(fields.map { field =>
          if (field.name == "target_offset") field.copy(tpe = targetOffsetType)
          else field.copy(tpe = concreteType(field.tpe))
        })
        case VectorType(element, size) => VectorType(concreteType(element), size)
        case other => other
      }
      def concreteExpr(expression: Expression): Expression = expression match {
        case field: WSubField if field.name == "target_offset" =>
          field.copy(expr = concreteExpr(field.expr), tpe = targetOffsetType)
        case other => other.mapExpr(concreteExpr)
      }
      def concreteStmt(statement: Statement): Statement =
        statement.mapStmt(concreteStmt).mapExpr(concreteExpr)
      // The parent resolves MicroOp.target_offset from its packed immediate
      // format.  The locked artifact low FIR proves this is SInt<21>.
      val ports = sourceModule.ports.map(port => port.copy(tpe = concreteType(port.tpe)))
      val module = sourceModule.copy(
        name = name, ports = ports, body = concreteStmt(sourceModule.body))
      Circuit(parsed.info, Seq(module), name)
    }

    val original = isolated(OriginalName)
    val transforms = (if (includeRobValBitset) Seq(Dependency(BitsetStateLift))
      else Seq.empty) ++ Seq(
        Dependency(StateArrayLift), Dependency(firrtl.passes.ExpandWhens))
    val liftCompiler = new firrtl.stage.transforms.Compiler(transforms)
    val annotations: Seq[firrtl.annotations.Annotation] = Seq(
      EssentOptionsAnnotation(OptFlags(simdV2 = true)),
      StateArrayLiftConfigAnnotation(Registers, Set.empty, FieldGroups)) ++
      (if (includeRobValBitset)
        Seq(BitsetStateLiftConfigAnnotation(Set("rob_val"), minimumDepth = 32))
      else Seq.empty)
    val liftedState = liftCompiler.execute(CircuitState(
      isolated(LiftedName), annotations))
    val storage = liftedState.annotations.collect {
      case annotation: StateArrayStorageAnnotation => annotation
    }
    require(storage.size == ExpectedStorage.size,
      s"expected ${ExpectedStorage.size} compiler-owned ROB memories, got ${storage.size}")
    val liftedModule = liftedState.circuit.modules.collectFirst {
      case module: Module if module.name == LiftedName => module
    }.getOrElse(throw new IllegalStateException(s"missing $LiftedName after state lifting"))
    val memoryWriters = collection.mutable.Map[String, Int]()
    def collectMemories(statement: Statement): Unit = statement match {
      case memory: DefMemory => memoryWriters(memory.name) = memory.writers.size
      case other => other.foreachStmt(collectMemories)
    }
    collectMemories(liftedModule.body)
    val byRegister = storage.map(annotation => annotation.register -> annotation).toMap
    require(byRegister.keySet == ExpectedStorage.keySet,
      s"unexpected ROB lifted registers: ${byRegister.keySet.toSeq.sorted.mkString(",")}")
    for ((register, (width, reads, writes, fields)) <- ExpectedStorage) {
      val annotation = byRegister(register)
      require(annotation.depth == 32 && annotation.packedWidth == width &&
          annotation.readPorts == reads && annotation.fields.toSet == fields &&
          memoryWriters.get(annotation.memory).contains(writes),
        s"Small ROB storage geometry changed for $register: annotation=$annotation " +
        s"writers=${memoryWriters.get(annotation.memory)}")
    }
    val bitsets = liftedState.annotations.collect {
      case annotation: IndexedCounterBankStorageAnnotation
          if annotation.family == "rob_val" => annotation
    }
    if (includeRobValBitset) {
      require(bitsets.size == 1,
        s"expected one packed rob_val mapping, got $bitsets")
      val mapping = bitsets.head
      require(mapping.module == LiftedName && mapping.banks.size == 1 &&
          mapping.membersByIndex == (0 until 32).map(index => s"rob_val_$index"),
        s"Small ROB rob_val geometry changed: $mapping")
      val registers = collection.mutable.ArrayBuffer[DefRegister]()
      def collectRegisters(statement: Statement): Unit = statement match {
        case register: DefRegister => registers += register
        case other => other.foreachStmt(collectRegisters)
      }
      collectRegisters(liftedModule.body)
      val bank = registers.find(_.name == mapping.banks.head).getOrElse(
        throw new IllegalStateException(s"missing packed rob_val bank ${mapping.banks.head}"))
      require(firrtl.bitWidth(bank.tpe) == 32,
        s"packed rob_val bank width changed: ${bank.tpe}")
      require(!registers.exists(_.name == "rob_val"),
        "aggregate rob_val register remains after bitset packing")
    } else require(bitsets.isEmpty,
      s"rob_val was packed without the opt-in candidate: $bitsets")

    writeText(new File(output, s"$OriginalName.fir"), original.serialize)
    writeText(new File(output, s"$LiftedName.fir"), liftedState.circuit.serialize)
    emitVerilog(original, output)
    emitVerilog(liftedState.circuit, output)
    val mode = if (includeRobValBitset) "payload+rob_val-bitset" else "payload"
    println(s"Prepared artifact ROB equivalence pair under $output mode=$mode")
  }

  private def emitVerilog(circuit: Circuit, output: File): Unit = {
    val result = new VerilogCompiler().compileAndEmit(CircuitState(circuit, Seq.empty))
    val emitted = result.annotations.collect {
      case annotation: EmittedVerilogCircuitAnnotation =>
        (annotation.value.name, annotation.value.outputSuffix, annotation.value.value)
      case annotation: EmittedVerilogModuleAnnotation =>
        (annotation.value.name, annotation.value.outputSuffix, annotation.value.value)
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
