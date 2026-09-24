package essent

import firrtl._
import firrtl.annotations.{Annotation, JsonProtocol}
import firrtl.transforms.DontTouchAnnotation

import java.io.{File, FileWriter, PrintWriter}
import scala.io.Source

/**
  * Run FIRRTL's [[VerilogCompiler]] on a .fir file and write emitted Verilog files.
  *
  * Does not load `.anno.json` by default: Sodor's Top.anno.json contains
  * FirrtlFileAnnotation pointing at another .fir, which is for ChiselStage, not this path.
  *
  * Usage:
  *   runMain essent.EmitVerilogFromFirrtl <path/to/Top.fir> [output_dir]
  *     [--dont-touch-annotations path/to/architecture.anno.json]
  *
  * Default `output_dir` is the directory containing the `.fir` file.
  */
object EmitVerilogFromFirrtl {
  def main(args: Array[String]): Unit = {
    if (args.isEmpty || !(args.length == 1 || args.length == 2 ||
        (args.length == 4 && args(2) == "--dont-touch-annotations"))) {
      System.err.println("Usage: EmitVerilogFromFirrtl <in.fir> [output_dir] [--dont-touch-annotations file]")
      System.exit(1)
    }
    val firPath = new File(args(0)).getCanonicalFile
    if (!firPath.isFile) {
      System.err.println(s"Not a file: $firPath")
      System.exit(1)
    }
    val outDir =
      if (args.length >= 2) new File(args(1)).getCanonicalFile
      else firPath.getParentFile
    outDir.mkdirs()

    val firSrc = Source.fromFile(firPath)
    val circuit =
      try Parser.parse(firSrc.getLines(), Parser.IgnoreInfo)
      finally firSrc.close()

    // Architecture observers preserve only explicitly named signals. Never
    // auto-load the Chisel annotation file, which may select a different
    // input circuit or change unrelated lowering behavior.
    val annotations = if (args.length == 4) readDontTouchAnnotations(new File(args(3)))
                      else Seq.empty
    val state = CircuitState(circuit, annotations)
    val verilogCompiler = new VerilogCompiler()
    println("Running VerilogCompiler (large circuits may take minutes)...")
    val result = verilogCompiler.compileAndEmit(state)

    var n = 0
    result.annotations.foreach {
      case anno: EmittedVerilogCircuitAnnotation =>
        writeFile(outDir, anno.value.name, anno.value.outputSuffix, anno.value.value)
        n += 1
      case anno: EmittedVerilogModuleAnnotation =>
        writeFile(outDir, anno.value.name, anno.value.outputSuffix, anno.value.value)
        n += 1
      case _ =>
    }

    if (n == 0) {
      System.err.println("No EmittedVerilog* annotations (see FIRRTL log above).")
      System.exit(2)
    }
    println(s"EmitVerilogFromFirrtl: wrote $n file(s) under $outDir")
  }

  private[essent] def readDontTouchAnnotations(file: File): Seq[Annotation] = {
    val source = Source.fromFile(file)
    val parsed = try JsonProtocol.deserialize(source.mkString)
                 finally source.close()
    require(parsed.nonEmpty && parsed.forall(_.isInstanceOf[DontTouchAnnotation]),
      "architecture observer accepts a nonempty DontTouchAnnotation list only")
    parsed
  }

  private def writeFile(dir: File, base: String, suffix: String, body: String): Unit = {
    val f = new File(dir, base + suffix)
    val w = new PrintWriter(new FileWriter(f))
    try w.print(body)
    finally w.close()
    println(s"  ${f.getName} (${body.length} chars)")
  }
}
