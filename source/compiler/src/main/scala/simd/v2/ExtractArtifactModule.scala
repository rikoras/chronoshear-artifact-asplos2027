package essent.simd.v2

import firrtl._
import firrtl.ir._

import java.io.{File, FileWriter, PrintWriter}
import scala.collection.mutable
import scala.io.Source

/** Lift one module out of the locked artifact FIRRTL as a standalone circuit.
  *
  * The three `Prepare*StateLift*` passes each hardcode the module they extract,
  * because each also builds a *lifted* variant to diff against the original.
  * The uncore needs something different and more repetitive: the same
  * rocket-chip library components -- `Queue`, `Arbiter`, `TLFragmenter`,
  * `TLToAXI4`, `TLBroadcast` -- pulled out unchanged so a C++ reference model
  * can be differentially checked against the artifact's own RTL.  Per-signal
  * scoping found 620 uncore streams collapsing onto 35 declaration sites, so
  * extraction is worth doing once, generically.
  *
  * Two things are resolved that isolation would otherwise break, and one is
  * refused outright:
  *
  *  - only the extracted top's otherwise-unconstrained abstract `Reset` is
  *    fixed to the synchronous reset used by `TestHarness`; nested abstract
  *    resets remain available to FIRRTL inference, because a synchronizer's
  *    child port can legitimately resolve to `AsyncReset`;
  *  - submodules are pulled in transitively, so a component with internal
  *    instances still elaborates;
  *  - a port whose width was inferred from the parent is an error, not a
  *    guess.  Isolating such a module silently changes its behaviour, which
  *    is exactly the failure the BPD differential had to be corrected for.
  *
  * Usage:
  *   runMain essent.simd.v2.ExtractArtifactModule <fir> <Module> <out-dir>
  */
object ExtractArtifactModule {

  def main(args: Array[String]): Unit = {
    if (args.length != 3) {
      System.err.println(
        "Usage: ExtractArtifactModule <SmallBoomConfig.fir> <ModuleName> <output-dir>")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    val moduleName = args(1)
    val output = new File(args(2)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    output.mkdirs()

    val source = Source.fromFile(input)
    val parsed =
      try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()

    val byName = parsed.modules.map(m => m.name -> m).toMap
    require(byName.contains(moduleName),
      s"$moduleName is not present in $input")

    val closure = transitiveClosure(moduleName, byName)
    val missing = closure.filterNot(byName.contains)
    require(missing.isEmpty,
      s"$moduleName instantiates modules absent from the circuit: ${missing.mkString(", ")}")

    // Do not eagerly rewrite abstract Reset to UInt.  That was sufficient for
    // plain Queue modules, but it makes an AsyncValidSync closure ill-typed:
    // its child Reset port is resolved to AsyncReset by the parent connection.
    // The standard compiler pipeline contains InferResets and has the whole
    // transitive closure here, so it has exactly the evidence needed to make
    // the per-module choice without guessing.
    // C++ emission embeds child module structs by value, so their type
    // definitions must precede the parent that names them. Alphabetical
    // ordering happened to work for several single-level components but
    // fails immediately for AsyncQueueSource_1 -> AsyncValidSync_*. Keep a
    // deterministic child-before-parent order in the extracted circuit.
    val extracted = dependencyOrder(moduleName, byName).map { name =>
      if (name == moduleName) resolveTopReset(byName(name)) else byName(name)
    }
    val top = extracted.find(_.name == moduleName).get
    checkPortWidthsAreBound(top)

    val circuit = Circuit(parsed.info, extracted, moduleName)
    writeText(new File(output, s"$moduleName.fir"), circuit.serialize)
    emitVerilog(circuit, output)

    val instanceCount = closure.size - 1
    println(s"Extracted $moduleName from ${input.getName} " +
      s"(${instanceCount} submodule definition(s)) into $output")
  }

  /** Module names reachable from `root` through DefInstance, including root. */
  private def transitiveClosure(
      root: String, byName: Map[String, DefModule]): Set[String] = {
    val seen = mutable.Set(root)
    val pending = mutable.Queue(root)
    while (pending.nonEmpty) {
      val current = pending.dequeue()
      byName.get(current).foreach { module =>
        def walk(statement: Statement): Unit = statement match {
          case instance: DefInstance =>
            if (seen.add(instance.module)) pending.enqueue(instance.module)
          case other => other.foreachStmt(walk)
        }
        module.foreachStmt(walk)
      }
    }
    seen.toSet
  }

  /** Deterministic post-order of the instance DAG: every instantiated module
    * appears before the module that embeds it. */
  private[v2] def dependencyOrder(
      root: String, byName: Map[String, DefModule]): Seq[String] = {
    val emitted = mutable.Set[String]()
    val visiting = mutable.Set[String]()
    val result = mutable.ArrayBuffer[String]()

    def children(module: DefModule): Seq[String] = {
      val found = mutable.ArrayBuffer[String]()
      def walk(statement: Statement): Unit = statement match {
        case instance: DefInstance => found += instance.module
        case other => other.foreachStmt(walk)
      }
      module.foreachStmt(walk)
      found.distinct.sorted.toSeq
    }

    def visit(name: String): Unit = {
      require(!visiting(name),
        s"recursive module instantiation while extracting $root: $name")
      if (!emitted(name)) {
        visiting += name
        children(byName(name)).foreach(visit)
        visiting -= name
        emitted += name
        result += name
      }
    }

    visit(root)
    result.toSeq
  }

  /** The circuit main cannot retain an abstract Reset because it has no
    * parent connection from which InferResets could learn a concrete kind.
    * Resolve only this module.  Rewriting the full closure is incorrect: an
    * AsyncValidSync child receives an AsyncReset and must retain that type. */
  private def resolveTopReset(module: DefModule): DefModule = {
    val bool = UIntType(IntWidth(1))
    def expr(e: Expression): Expression = e match {
      case ref: WRef if ref.tpe == ResetType => ref.copy(tpe = bool)
      case ref: Reference if ref.tpe == ResetType => ref.copy(tpe = bool)
      case other => other.mapExpr(expr)
    }
    def tpe(t: Type): Type = t match {
      case ResetType => bool
      case BundleType(fields) => BundleType(fields.map(f => f.copy(tpe = tpe(f.tpe))))
      case VectorType(element, size) => VectorType(tpe(element), size)
      case other => other
    }
    def stmt(s: Statement): Statement = s.mapStmt(stmt).mapExpr(expr).mapType(tpe)
    val ports = module.ports.map(p => p.copy(tpe = tpe(p.tpe)))
    module match {
      case m: Module => m.copy(ports = ports, body = stmt(m.body))
      case other => other.mapPort(p => p.copy(tpe = tpe(p.tpe)))
    }
  }

  /** Refuse a module whose port widths were inferred from its parent.
    * Isolating one silently changes its behaviour; the caller must extract a
    * concrete instance or specialize the width deliberately. */
  private def checkPortWidthsAreBound(module: DefModule): Unit = {
    val unbound = mutable.ArrayBuffer[String]()
    def check(path: String, t: Type): Unit = t match {
      case UIntType(UnknownWidth) | SIntType(UnknownWidth) => unbound += path
      case BundleType(fields) => fields.foreach(f => check(s"$path.${f.name}", f.tpe))
      case VectorType(element, size) =>
        if (size > 0) check(s"$path[0]", element)
      case _ =>
    }
    module.ports.foreach(port => check(port.name, port.tpe))
    require(unbound.isEmpty,
      s"${module.name} has port(s) with parent-inferred width, so isolating it " +
        s"would change behaviour: ${unbound.mkString(", ")}")
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
    try writer.print(body)
    finally writer.close()
  }
}
