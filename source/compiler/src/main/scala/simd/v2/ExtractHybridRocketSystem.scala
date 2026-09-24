package essent.simd.v2

import firrtl.Parser
import firrtl.ir._
import org.json4s.DefaultFormats
import org.json4s.native.Serialization.writePretty

import java.io.{File, FileWriter, PrintWriter}
import java.nio.file.Files
import java.security.MessageDigest
import scala.collection.mutable
import scala.io.Source

/** Build the cold half of the Rocket full-chip reference model.
  *
  * The locked DefaultConfig TestHarness remains the top.  Only the one
  * reachable `Rocket` module is replaced by an ExtModule with byte-for-byte
  * identical FIRRTL ports.  Frontend, FPU, caches, TLB/PTW, TileLink, debug,
  * interrupts, CLINT/PLIC, boot ROM and AXI memory therefore remain in the
  * generated cold sidecar.  A host adapter drives the ExtModule from the
  * independently implemented rocket_model::ProducerCore.
  *
  * This is intentionally different from extracting a standalone core: all
  * parent connections and every non-core state element stay under the real
  * TestHarness hierarchy.  Unreachable definitions below the removed Rocket
  * body are pruned so they cannot accidentally be mistaken for live model
  * state.
  *
  * Usage:
  *   runMain essent.simd.v2.ExtractHybridRocketSystem \
  *     <DefaultConfig.fir> <output.fir> <contract.json> [--fpu-contract <fpu.json>] [--replace-fpu]
  *
  * --fpu-contract alone audits the retained FPU. --replace-fpu additionally
  * proves the locked CP interface inactive/unobserved and emits a specialized
  * FPU ExtModule; it requires an explicit FPU contract output.
  */
object ExtractHybridRocketSystem {
  private val HotModule = "Rocket"
  private val HotDefname = "CHISARocketModel"
  // The full consumer and the scalar cold producer are linked into one live
  // executable, but in different translation units.  Giving the producer a
  // distinct top name makes its generated header/type unambiguous and keeps
  // the artifact contract honest: this circuit is the cold half, not another
  // complete TestHarness implementation.
  private val ColdTop = "RocketCold"

  private[v2] case class SeamPort(
      path: String,
      direction: Direction,
      tpe: Type,
      clock: Boolean)

  private[v2] case class FpuBoundary(
      instance: String,
      ports: Seq[SeamPort],
      undrivenOutputs: Seq[String],
      parentConnections: Seq[String])

  def main(args: Array[String]): Unit = {
    throw new UnsupportedOperationException("Rocket RTL-sidecar generation is retired; use the native model or complete RTL trace simulation")
    if (args.length < 3) {
      System.err.println(
        "Usage: ExtractHybridRocketSystem <DefaultConfig.fir> " +
          "<output.fir> <contract.json> [--fpu-contract <fpu.json>] [--replace-fpu]")
      System.exit(2)
    }

    var replaceFpu = false
    var fpuContractArg: Option[String] = None
    var replaceMemory = false
    var memoryContractArg: Option[String] = None
    var index = 3
    while (index < args.length) {
      args(index) match {
        case "--fpu-contract" if fpuContractArg.isEmpty && index + 1 < args.length =>
          fpuContractArg = Some(args(index + 1)); index += 2
        case "--replace-fpu" if !replaceFpu => replaceFpu = true; index += 1
        case "--memory-contract" if memoryContractArg.isEmpty && index + 1 < args.length =>
          memoryContractArg = Some(args(index + 1)); index += 2
        case "--replace-memory" if !replaceMemory => replaceMemory = true; index += 1
        case other => throw new IllegalArgumentException(s"unknown, duplicate, or incomplete extraction option: $other")
      }
    }
    require(!replaceFpu || fpuContractArg.nonEmpty, "--replace-fpu requires --fpu-contract PATH")
    require(replaceMemory == memoryContractArg.nonEmpty,
      "--replace-memory and --memory-contract PATH must be provided together")

    val input = new File(args(0)).getCanonicalFile
    val output = new File(args(1)).getCanonicalFile
    val contract = new File(args(2)).getCanonicalFile
    val fpuContract = fpuContractArg.map(path => new File(path).getCanonicalFile)
    val memoryContract = memoryContractArg.map(path => new File(path).getCanonicalFile)
    memoryContract.foreach(file => require(!Set(input, output, contract)(file) && !fpuContract.contains(file),
      "memory contract must have its own output path"))
    fpuContract.foreach(file => require(!Set(input, output, contract)(file),
      "FPU audit contract must have its own output path"))
    require(input.isFile, s"missing input FIRRTL: $input")
    if (replaceFpu || replaceMemory) {
      require(sha256(input) == RocketFpuSpecialization.QualifiedFirrtlSha256,
        "native module replacement requires the qualified DefaultConfig FIRRTL")
      for (file <- Seq(input, output)) {
        require(!new File(file.getPath.stripSuffix(".fir") + ".anno.json").exists(),
          "native module replacement requires annotation-free FIRRTL staging")
      }
    }
    Option(output.getParentFile).foreach(_.mkdirs())
    Option(contract.getParentFile).foreach(_.mkdirs())

    val source = Source.fromFile(input)
    val parsed =
      try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    // Resolve and validate the optional audit before writing any artifacts.
    val fpuAudit = fpuContract.map(_ => fpuBoundary(parsed))

    val byName = parsed.modules.map(m => m.name -> m).toMap
    val originalHot = byName.getOrElse(
      HotModule, throw new IllegalArgumentException(
        s"$HotModule is absent from ${input.getName}"))
    require(originalHot.isInstanceOf[Module],
      s"$HotModule is already an ExtModule in ${input.getName}")

    val hot = ExtModule(
      originalHot.info,
      originalHot.name,
      originalHot.ports,
      HotDefname,
      Seq.empty)
    val replaced = byName.updated(HotModule, hot)
    val reachable = transitiveClosure(parsed.main, replaced)
    require(reachable.contains(HotModule),
      s"$HotModule is not reachable from ${parsed.main}")
    require(reachable.contains("FPU"),
      "the hybrid cut unexpectedly removed the Rocket FPU")
    for (required <- Seq(
        "Frontend", "ICache", "DCache", "TLB", "PTW", "TLPLIC",
        "TLDebugModule", "TLBroadcast", "AXI4RAM", "SimAXIMem")) {
      require(reachable.contains(required),
        s"the hybrid cut unexpectedly removed required module $required")
    }

    val instancePaths = findInstancePaths(parsed.main, replaced)
    val hotInstances = instancePaths.filter(_._2 == HotModule)
    require(hotInstances.size == 1,
      s"expected one reachable Rocket instance, found ${hotInstances.size}: " +
        hotInstances.map(_._1).mkString(", "))

    val modules = parsed.modules.flatMap { module =>
      if (!reachable(module.name)) None
      else if (module.name == HotModule) Some(hot)
      else if (module.name == parsed.main) module match {
        case concrete: Module => Some(concrete.copy(name = ColdTop))
        case _: ExtModule => throw new IllegalArgumentException(
          s"top ${parsed.main} unexpectedly is an ExtModule")
      }
      else Some(module)
    }
    require(!parsed.modules.exists(_.name == ColdTop),
      s"cold top name $ColdTop already exists in ${input.getName}")
    val baseline = Circuit(parsed.info, modules, ColdTop)
    val specialization = if (replaceFpu) Some(RocketFpuSpecialization.specialize(baseline)) else None
    val fpuHybrid = specialization.map(_.circuit).getOrElse(baseline)
    val memorySpecialization = if (replaceMemory) Some(RocketMemorySpecialization.specialize(fpuHybrid)) else None
    val hybrid = memorySpecialization.map(_.circuit).getOrElse(fpuHybrid)
    writeText(output, hybrid.serialize)

    val seam = flattenPorts(hot.ports)
    writeContract(
      contract,
      input,
      output,
      parsed,
      hybrid,
      hotInstances.head._1,
      seam,
      if (replaceFpu) RocketFpuSpecialization.Policy else "retained-cold-rtl")
    fpuAudit.foreach(boundary => writeFpuContract(fpuContract.get, input, boundary, specialization))
    memorySpecialization.foreach { memory =>
      implicit val formats = DefaultFormats
      val file = memoryContract.get
      Option(file.getParentFile).foreach(_.mkdirs())
      writeText(file, writePretty(RocketMemorySpecialization.Contract(1, sha256(input),
        RocketMemorySpecialization.Policy, replacementEnabled = true, memory.boundaries)) + "\n")
    }

    val fromHost = seam.count(p => !p.clock && p.direction == Output)
    val toHost = seam.count(p => !p.clock && p.direction == Input)
    println(
      s"Rocket hybrid system: top=${hybrid.main} hot=${hotInstances.head._1} " +
        s"coldModules=${hybrid.modules.size - (if (replaceFpu) 2 else 1)} seamToHost=$toHost " +
        s"seamFromHost=$fromHost output=$output")
  }

  private[v2] def fpuBoundary(circuit: Circuit): FpuBoundary = {
    val byName = circuit.modules.map(m => m.name -> m).toMap
    val module = byName.get("FPU") match {
      case Some(m: Module) => m
      case _ => throw new IllegalArgumentException("FPU audit requires the original concrete FPU module")
    }
    val instances = findInstancePaths(circuit.main, byName)
    val fpus = instances.filter(_._2 == "FPU")
    require(fpus.size == 1, s"FPU audit requires one reachable instance, found ${fpus.size}")
    val path = fpus.head._1
    val ports = flattenPorts(module.ports)
    require(ports.map(_.path).distinct.size == ports.size, "duplicate FPU boundary leaf")
    ports.foreach(p => bitWidth(p.tpe))
    val driven = mutable.Set[String]()
    def mark(location: Expression): Unit = {
      val prefix = location.serialize
      ports.filter(p => p.direction == Output &&
        (p.path == prefix || p.path.startsWith(prefix + ".") || p.path.startsWith(prefix + "[")))
        .foreach(p => driven += p.path)
    }
    def drivers(statement: Statement): Unit = statement match {
      case c: Connect => mark(c.loc)
      case c: PartialConnect => mark(c.loc)
      case other => other.foreachStmt(drivers)
    }
    drivers(module.body)

    val split = path.lastIndexOf('.')
    val parentModule = if (split < 0) circuit.main else instances.toMap.apply(path.substring(0, split))
    val localName = path.substring(split + 1)
    val connections = mutable.ArrayBuffer[String]()
    def collect(statement: Statement): Unit = statement match {
      case b: Block => b.stmts.foreach(collect)
      case c: Conditionally => collect(c.conseq); collect(c.alt)
      case other if other.serialize.contains(localName + ".") => connections += other.serialize
      case _ =>
    }
    byName(parentModule) match {
      case m: Module => collect(m.body)
      case _ => throw new IllegalArgumentException("FPU parent is not a concrete module")
    }
    FpuBoundary(path, ports, ports.filter(p => p.direction == Output && !driven(p.path)).map(_.path), connections.toSeq)
  }

  private def transitiveClosure(
      root: String,
      byName: Map[String, DefModule]): Set[String] = {
    val seen = mutable.LinkedHashSet(root)
    val pending = mutable.Queue(root)
    while (pending.nonEmpty) {
      val name = pending.dequeue()
      val module = byName.getOrElse(name,
        throw new IllegalArgumentException(
          s"reachable module $name is absent from the circuit"))
      module match {
        case m: Module =>
          def walk(statement: Statement): Unit = statement match {
            case instance: DefInstance =>
              if (seen.add(instance.module)) pending.enqueue(instance.module)
            case other => other.foreachStmt(walk)
          }
          walk(m.body)
        case _: ExtModule =>
      }
    }
    seen.toSet
  }

  private def findInstancePaths(
      root: String,
      byName: Map[String, DefModule]): Seq[(String, String)] = {
    val result = mutable.ArrayBuffer[(String, String)]()

    def visit(moduleName: String, prefix: String): Unit = {
      byName(moduleName) match {
        case module: Module =>
          def walk(statement: Statement): Unit = statement match {
            case instance: DefInstance =>
              val path = if (prefix.isEmpty) instance.name
                         else s"$prefix.${instance.name}"
              result += path -> instance.module
              visit(instance.module, path)
            case other => other.foreachStmt(walk)
          }
          walk(module.body)
        case _: ExtModule =>
      }
    }

    visit(root, "")
    result.toSeq
  }

  private def flip(direction: Direction): Direction = direction match {
    case Input => Output
    case Output => Input
  }

  private def flattenPorts(ports: Seq[Port]): Seq[SeamPort] = {
    val result = mutable.ArrayBuffer[SeamPort]()

    def visit(path: String, direction: Direction, tpe: Type): Unit = tpe match {
      case BundleType(fields) => fields.foreach { field =>
        val childDirection = field.flip match {
          case Flip => flip(direction)
          case Default => direction
        }
        visit(s"$path.${field.name}", childDirection, field.tpe)
      }
      case VectorType(element, size) =>
        (0 until size).foreach(index =>
          visit(s"$path[$index]", direction, element))
      case ground =>
        result += SeamPort(path, direction, ground, ground == ClockType)
    }

    ports.foreach(port => visit(port.name, port.direction, port.tpe))
    result.toSeq
  }

  private def sha256(file: File): String = {
    val digest = MessageDigest.getInstance("SHA-256")
    val bytes = Files.readAllBytes(file.toPath)
    digest.digest(bytes).map(b => f"${b & 0xff}%02x").mkString
  }

  private def json(text: String): String = "\"" + text.flatMap {
    case '\\' => "\\\\"
    case '"' => "\\\""
    case '\n' => "\\n"
    case '\r' => "\\r"
    case '\t' => "\\t"
    case c if c < ' ' => f"\\u${c.toInt}%04x"
    case c => c.toString
  } + "\""

  private def bitWidth(tpe: Type): BigInt = tpe match {
    case ClockType | ResetType | AsyncResetType => 1
    case UIntType(IntWidth(width)) => width
    case SIntType(IntWidth(width)) => width
    case other => throw new IllegalArgumentException(
      s"unbound or non-ground Rocket seam type: ${other.serialize}")
  }

  private def writeContract(
      file: File,
      input: File,
      output: File,
      original: Circuit,
      hybrid: Circuit,
      hotPath: String,
      ports: Seq[SeamPort],
      fpuPolicy: String): Unit = {
    val writer = new PrintWriter(new FileWriter(file))
    try {
      writer.println("{")
      writer.println("  \"schemaVersion\": 1,")
      writer.println(s"  \"sourceFirrtl\": ${json(input.getName)},")
      writer.println(s"  \"sourceFirrtlSha256\": ${json(sha256(input))},")
      writer.println(s"  \"hybridFirrtl\": ${json(output.getName)},")
      writer.println(s"  \"hybridFirrtlSha256\": ${json(sha256(output))},")
      writer.println(s"  \"top\": ${json(hybrid.main)},")
      writer.println(s"  \"hotInstance\": ${json(hotPath)},")
      writer.println(s"  \"hotModule\": ${json(HotModule)},")
      writer.println(s"  \"hotDefname\": ${json(HotDefname)},")
      writer.println(s"  \"fpuPolicy\": ${json(fpuPolicy)},")
      writer.println(s"  \"originalDefinitions\": ${original.modules.size},")
      writer.println(s"  \"reachableDefinitions\": ${hybrid.modules.size},")
      writer.println(s"  \"groundSeamPorts\": ${ports.size},")
      writer.println("  \"ports\": [")
      writePorts(writer, ports)
      writer.println("  ]")
      writer.println("}")
    } finally writer.close()
  }

  private def writePorts(writer: PrintWriter, ports: Seq[SeamPort]): Unit = {
    ports.zipWithIndex.foreach { case (port, index) =>
        val comma = if (index + 1 == ports.size) "" else ","
        val direction = port.direction match {
          // FIRRTL input: parent/cold system drives the hot model.
          case Input => "cold-to-hot"
          // FIRRTL output: hot model drives the parent/cold system.
          case Output => "hot-to-cold"
        }
        writer.println("    {" +
          s"\"path\":${json(port.path)}," +
          s"\"flow\":${json(direction)}," +
          s"\"type\":${json(port.tpe.serialize)}," +
          s"\"width\":${bitWidth(port.tpe)}," +
          s"\"clock\":${port.clock}" +
          s"}$comma")
    }
  }

  private def writeFpuContract(file: File, input: File, boundary: FpuBoundary,
      specialization: Option[RocketFpuSpecialization.Specialized]): Unit = {
    val ports = specialization.map(s => flattenPorts(s.circuit.modules.find(_.name == "FPU").get.ports))
      .getOrElse(boundary.ports)
    val retainedPaths = ports.map(_.path).toSet
    val omitted = boundary.ports.filterNot(p => retainedPaths(p.path))
    Option(file.getParentFile).foreach(_.mkdirs())
    val writer = new PrintWriter(new FileWriter(file))
    try {
      writer.println("{")
      writer.println(s"  \"schemaVersion\": ${if (specialization.isDefined) 2 else 1},")
      writer.println(s"  \"sourceFirrtlSha256\": ${json(sha256(input))},")
      writer.println("  \"module\": \"FPU\",")
      writer.println(s"  \"instance\": ${json(boundary.instance)},")
      writer.println(s"  \"replacementEnabled\": ${specialization.isDefined},")
      writer.println(s"  \"policy\": ${json(if (specialization.isDefined) RocketFpuSpecialization.Policy else "retained-cold-rtl-audit")},")
      writer.println(s"  \"groundSeamPorts\": ${ports.size},")
      writer.println(s"  \"undrivenOutputs\": ${boundary.undrivenOutputs.filter(retainedPaths).map(json).mkString("[", ",", "]")},")
      writer.println(s"  \"parentConnections\": ${boundary.parentConnections.map(json).mkString("[", ",", "]")},")
      specialization.foreach { s =>
        implicit val formats = DefaultFormats
        writer.println(s"  \"hotDefname\": ${json(RocketFpuSpecialization.Defname)},")
        writer.println(s"  \"originalGroundSeamPorts\": ${boundary.ports.size},")
        writer.println(s"  \"originalUndrivenOutputs\": ${boundary.undrivenOutputs.map(json).mkString("[", ",", "]")},")
        writer.println(s"  \"cpProof\": ${writePretty(s.proof)},")
        writer.println("  \"omittedPorts\": [")
        writePorts(writer, omitted)
        writer.println("  ],")
      }
      writer.println("  \"ports\": [")
      writePorts(writer, ports)
      writer.println("  ]")
      writer.println("}")
    } finally writer.close()
  }

  private def writeText(file: File, body: String): Unit = {
    val writer = new PrintWriter(new FileWriter(file))
    try writer.print(body)
    finally writer.close()
  }
}
