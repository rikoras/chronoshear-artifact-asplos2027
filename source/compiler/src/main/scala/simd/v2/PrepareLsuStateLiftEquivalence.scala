package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl._
import firrtl.ir._
import firrtl.options.Dependency

import java.io.{File, FileWriter, PrintWriter}
import scala.collection.mutable
import scala.io.Source

/** Extract the exact Small BOOM LSU hierarchy and prepare uniquely-prefixed
  * original/lifted Verilog pairs.  Only three nested payload leaves move:
  * LDQ address, STQ address, and STQ data.  All address generation, validity,
  * forwarding, ordering, replay, exception, and commit logic remains RTL.
  */
object PrepareLsuStateLiftEquivalence {
  private val SourceModule = "LSU"
  private val OriginalName = "LSUOriginal"
  private val LiftedName = "LSULifted"
  private val Registers = Set("ldq", "stq")
  private val FieldGroups = Seq(Set("bits.addr.bits"), Set("bits.data.bits"))
  private val ExpectedStorage = Map(
    "ldq" -> Set(("bits.addr.bits", 40, 11, 1)),
    "stq" -> Set(("bits.addr.bits", 40, 11, 1), ("bits.data.bits", 64, 4, 1)))

  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      System.err.println(
        "Usage: PrepareLsuStateLiftEquivalence <SmallBoomConfig.fir> <output-dir>")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    val output = new File(args(1)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    output.mkdirs()

    val source = Source.fromFile(input)
    val parsed = try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    val moduleByName = parsed.modules.map(module => module.name -> module).toMap
    val sourceModule = moduleByName.get(SourceModule) match {
      case Some(module: Module) => module
      case other => throw new IllegalStateException(
        s"$SourceModule is not a concrete module in $input: $other")
    }

    val concretePortFields: Map[String, Type] = Map(
      "target_offset" -> SIntType(IntWidth(21)),
      "tsc_reg" -> UIntType(IntWidth(64)))
    def concreteType(tpe: Type): Type = tpe match {
      case BundleType(fields) => BundleType(fields.map { field =>
        concretePortFields.get(field.name) match {
          case Some(concrete) => field.copy(tpe = concrete)
          case None => field.copy(tpe = concreteType(field.tpe))
        }
      })
      case VectorType(element, size) => VectorType(concreteType(element), size)
      case other => other
    }
    def concreteExpr(expression: Expression): Expression = expression match {
      case field: WSubField if concretePortFields.contains(field.name) =>
        field.copy(expr = concreteExpr(field.expr), tpe = concretePortFields(field.name))
      case other => other.mapExpr(concreteExpr)
    }
    def concreteStmt(statement: Statement): Statement =
      statement.mapStmt(concreteStmt).mapExpr(concreteExpr)
    val concreteTop = sourceModule.copy(
      ports = sourceModule.ports.map(port => port.copy(tpe = concreteType(port.tpe))),
      body = concreteStmt(sourceModule.body))

    def childModules(module: DefModule): Seq[String] = module match {
      case concrete: Module =>
        val names = mutable.ArrayBuffer[String]()
        def walk(statement: Statement): Unit = statement match {
          case instance: WDefInstance => names += instance.module
          case other => other.foreachStmt(walk)
        }
        walk(concrete.body)
        names.toSeq
      case _: ExtModule => Seq.empty
    }
    val reachable = mutable.LinkedHashSet[String](SourceModule)
    val pending = mutable.Queue[String](SourceModule)
    while (pending.nonEmpty) {
      val name = pending.dequeue()
      childModules(if (name == SourceModule) concreteTop else moduleByName(name)).foreach { child =>
        require(moduleByName.contains(child), s"missing child module $child from $name")
        if (reachable.add(child)) pending.enqueue(child)
      }
    }
    val baseModules = parsed.modules.collect {
      case module if reachable.contains(module.name) =>
        if (module.name == SourceModule) concreteTop else module
    }
    val base = Circuit(parsed.info, baseModules, SourceModule)

    val liftCompiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency(StateArrayLift), Dependency(firrtl.passes.ExpandWhens)))
    val liftedState = liftCompiler.execute(CircuitState(base, Seq(
      EssentOptionsAnnotation(OptFlags(simdV2 = true)),
      StateArrayLiftConfigAnnotation(Registers, Set.empty, FieldGroups))))
    auditStorage(liftedState)

    val originalPrefixed = prefixHierarchy(base, OriginalName)
    val liftedPrefixed = prefixHierarchy(liftedState.circuit, LiftedName)
    writeText(new File(output, s"$OriginalName.fir"), originalPrefixed.serialize)
    writeText(new File(output, s"$LiftedName.fir"), liftedPrefixed.serialize)
    emitVerilog(originalPrefixed, new File(output, s"$OriginalName.v"))
    emitVerilog(liftedPrefixed, new File(output, s"$LiftedName.v"))
    println(s"Prepared artifact LSU equivalence pair under $output; " +
      s"reachableModules=${reachable.size}")
  }

  private def auditStorage(state: CircuitState): Unit = {
    val storage = state.annotations.collect {
      case annotation: StateArrayStorageAnnotation => annotation
    }
    require(storage.size == 3,
      s"expected 3 compiler-owned LSU payload memories, got ${storage.size}")
    val top = state.circuit.modules.collectFirst {
      case module: Module if module.name == SourceModule => module
    }.getOrElse(throw new IllegalStateException(s"missing $SourceModule after state lifting"))
    val writerCounts = mutable.Map[String, Int]()
    def collectMemories(statement: Statement): Unit = statement match {
      case memory: DefMemory => writerCounts(memory.name) = memory.writers.size
      case other => other.foreachStmt(collectMemories)
    }
    collectMemories(top.body)
    val actual = storage.groupBy(_.register).map { case (register, entries) =>
      register -> entries.map { entry =>
        require(entry.fields.size == 1,
          s"LSU payload memory unexpectedly packs fields: $entry")
        (entry.fields.head, entry.packedWidth, entry.readPorts,
          writerCounts.getOrElse(entry.memory, -1))
      }.toSet
    }
    require(actual == ExpectedStorage,
      s"Small LSU payload geometry changed: expected=$ExpectedStorage actual=$actual")
    require(storage.forall(_.depth == 8),
      s"Small LSU payload depth changed: ${storage.map(a => a.register -> a.depth)}")
  }

  /** Give every concrete module a side-specific name so Yosys/Verilator can
    * load both untouched RTL bodies without module-definition collisions.
    */
  private def prefixHierarchy(circuit: Circuit, topName: String): Circuit = {
    val mapping = circuit.modules.map { module =>
      module.name -> (if (module.name == circuit.main) topName
        else s"${topName}__${module.name}")
    }.toMap
    def renameStmt(statement: Statement): Statement = statement match {
      case instance: WDefInstance =>
        instance.copy(module = mapping.getOrElse(instance.module, instance.module))
      case other => other.mapStmt(renameStmt)
    }
    val modules = circuit.modules.map {
      case module: Module => module.copy(
        name = mapping(module.name), body = renameStmt(module.body))
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
