package essent

import java.io.File
import scala.io.Source
import firrtl.annotations.{Annotation, JsonProtocol, UnrecognizedAnnotation}
import logger._
import firrtl.CircuitState
import org.json4s.{JObject, JString}


object Driver {
  /** Rocket-Chip emits these annotations for collateral generation or
    * downstream synthesis guidance.  Their classes are not on CHISA's
    * classpath and none changes FIRRTL simulation semantics.  Keep annotation
    * loading fail-closed: recognized FIRRTL annotations survive, these exact
    * metadata records are reported and dropped, and every other unknown class
    * remains an error.
    */
  private val IgnorableExternalAnnotationClasses = Set(
    "freechips.rocketchip.util.SRAMAnnotation",
    "freechips.rocketchip.util.ParamsAnnotation",
    "freechips.rocketchip.util.RetimeModuleAnnotation",
    "freechips.rocketchip.util.RegFieldDescMappingAnnotation",
    "freechips.rocketchip.util.AddressMapAnnotation")

  private def annotationClass(annotation: UnrecognizedAnnotation): String =
    annotation.underlying match {
      case JObject(fields) => fields.collectFirst {
        case ("class", JString(name)) => name
      }.getOrElse("<missing-class>")
      case _ => "<malformed-annotation>"
    }

  private[essent] def deserializeAnnotations(json: String): Seq[Annotation] = {
    val parsed = JsonProtocol.deserialize(json, allowUnrecognizedAnnotations = true)
    val external = parsed.collect { case a: UnrecognizedAnnotation =>
      annotationClass(a) -> a
    }
    val rejected = external.map(_._1).filterNot(IgnorableExternalAnnotationClasses).distinct.sorted
    require(rejected.isEmpty,
      s"unrecognized annotation class(es): ${rejected.mkString(", ")}")
    if (external.nonEmpty) {
      val counts = external.groupBy(_._1).toSeq.sortBy(_._1).map {
        case (name, entries) => s"$name=${entries.size}"
      }
      println(s"[Driver] Ignoring non-semantic external annotations: ${counts.mkString(", ")}")
    }
    parsed.filterNot(_.isInstanceOf[UnrecognizedAnnotation])
  }

  def main(args: Array[String]): Unit = {
    (new ArgsParser).getConfig(args.toSeq) match {
      case Some(config) => generate(config)
      case None =>
    }
  }

  def generate(opt: OptFlags): Unit = {
    Logger.setClassLogLevels(Map("essent" -> logger.LogLevel(opt.essentLogLevel)))
    Logger.setClassLogLevels(Map("firrtl" -> logger.LogLevel(opt.firrtlLogLevel)))
    val sourceReader = Source.fromFile(opt.firInputFile)

    val annoPath = opt.firInputFile.toString.stripSuffix(".fir") + ".anno.json"
    val annos: Seq[Annotation] = if (new File(annoPath).exists()) {
      val annoSource = Source.fromFile(annoPath)
      val json = try annoSource.getLines().mkString finally annoSource.close()
      deserializeAnnotations(json)
    } else {
      println(s"[Driver] No annotation file found at $annoPath, proceeding without annotations")
      Seq.empty[Annotation]
    }

    val pure_circuit = firrtl.Parser.parse(sourceReader.getLines(), firrtl.Parser.IgnoreInfo)
    val circuit = CircuitState(circuit = pure_circuit, annotations = annos)

    sourceReader.close()
    val compiler = new EssentCompiler(opt)
    compiler.compileAndEmit(circuit)
  }
}
