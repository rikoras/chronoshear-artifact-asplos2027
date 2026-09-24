package essent.simd.v2

import essent.{EssentOptionsAnnotation, Extract, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency

import java.io.{File, FileWriter, PrintWriter}
import scala.collection.mutable
import scala.io.Source

/** Build artifact-exact original/lifted RTL for TLToAXI4's 128-entry indexed
  * in-flight counter family.  Width inference is performed on the complete
  * locked TestHarness before the module is isolated.
  */
object PrepareIndexedCounterStateLiftEquivalence {
  private val ModuleName = "TLToAXI4_1"
  private val Family = "count"
  private val Depth = 128
  private val Width = 1
  private val Reads = 130
  private val Writes = 130 // two ordinary ports plus 128 reset-priority ports

  def main(args: Array[String]): Unit = {
    if (args.length < 2 || args.length > 3 ||
        (args.length == 3 && !Set("memory", "bank")(args(2)))) {
      System.err.println(
        "Usage: PrepareIndexedCounterStateLiftEquivalence " +
          "<SmallBoomConfig.fir> <output-dir> [memory|bank]")
      System.exit(2)
    }
    val banked = args.lift(2).contains("bank")
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
    require(byName.contains(ModuleName), s"$ModuleName is not present in $input")
    val closure = transitiveClosure(ModuleName, byName)
    val modules = concrete.modules.collect {
      case module if closure(module.name) => resolveReset(module)
    }
    val base = Circuit(concrete.info, modules, ModuleName)
    requireBoundPorts(base.modules.find(_.name == ModuleName).get)

    val compiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency(IndexedCounterStateLift),
      Dependency(firrtl.passes.ExpandWhens)))
    val selection: firrtl.annotations.Annotation = if (banked)
      IndexedCounterBankLiftConfigAnnotation(
        Set(s"$ModuleName.$Family"), minimumDepth = Depth)
    else IndexedCounterStateLiftConfigAnnotation(
      Set(s"$ModuleName.$Family"), minimumDepth = Depth)
    val liftedState = compiler.execute(CircuitState(base, Seq(
      EssentOptionsAnnotation(OptFlags(simdV2 = true)), selection)))
    audit(liftedState, banked)

    val originalName = ModuleName + "Original"
    val liftedName = ModuleName + "Lifted"
    val original = prefixHierarchy(base, originalName)
    val lifted = prefixHierarchy(liftedState.circuit, liftedName)
    writeText(new File(output, s"$originalName.fir"), original.serialize)
    writeText(new File(output, s"$liftedName.fir"), lifted.serialize)
    emitVerilog(original, new File(output, s"$originalName.v"))
    emitVerilog(lifted, new File(output, s"$liftedName.v"))
    println(s"[indexed-counter-lift] prepared $ModuleName.$Family " +
      s"mode=${if (banked) "bank" else "memory"}: " +
      s"closure=${closure.size} depth=$Depth width=$Width" +
      (if (banked) " banks=2" else s" reads=$Reads writes=$Writes"))
  }

  private def audit(state: CircuitState, banked: Boolean): Unit = {
    if (banked) {
      val annotations = state.annotations.collect {
        case annotation: IndexedCounterBankStorageAnnotation => annotation
      }
      require(annotations.size == 1,
        s"expected one indexed counter bank mapping, got ${annotations.size}: $annotations")
      val annotation = annotations.head
      require(annotation.module == ModuleName && annotation.family == Family &&
          annotation.banks.size == 2 && annotation.membersByIndex.size == Depth,
        s"locked indexed-counter bank geometry changed: $annotation")
      val top = state.circuit.modules.collectFirst {
        case module: Module if module.name == ModuleName => module
      }.get
      val registers = Extract.findInstancesOf[DefRegister](top.body)
      val banks = registers.filter(register => annotation.banks.contains(register.name))
      require(banks.size == 2 && banks.forall(register => firrtl.bitWidth(register.tpe) == 64),
        s"expected two 64-bit indexed banks, got ${banks.map(r => r.name -> r.tpe)}")
      require(!registers.exists(register => register.name.startsWith("count_")),
        "source count registers remain after bank packing")
      return
    }
    val storage = state.annotations.collect {
      case annotation: StateArrayStorageAnnotation
          if annotation.memory.startsWith("__v2_indexed_") => annotation
    }
    require(storage.size == 1,
      s"expected one indexed counter memory, got ${storage.size}: $storage")
    val annotation = storage.head
    require(annotation.module == ModuleName &&
        annotation.register == Family &&
        annotation.depth == Depth &&
        annotation.packedWidth == Width &&
        annotation.readPorts == Reads &&
        annotation.fields == Seq("data") &&
        annotation.fieldWidths == Seq(Width),
      s"locked indexed-counter geometry changed: $annotation")
    val top = state.circuit.modules.collectFirst {
      case module: Module if module.name == ModuleName => module
    }.get
    val memories = mutable.ArrayBuffer[DefMemory]()
    def walk(statement: Statement): Unit = statement match {
      case memory: DefMemory if memory.name == annotation.memory => memories += memory
      case other => other.foreachStmt(walk)
    }
    walk(top.body)
    require(memories.size == 1 && memories.head.writers.size == Writes,
      s"expected $Writes chronological writer ports, got ${memories.map(_.writers.size)}")
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
