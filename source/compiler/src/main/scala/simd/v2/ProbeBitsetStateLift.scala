package essent.simd.v2

import essent.{EssentOptionsAnnotation, OptFlags}
import firrtl.{CircuitState, Parser}
import firrtl.options.Dependency

import java.io.File
import scala.io.Source

/** Fast structural probe for packed one-bit aggregate state. */
object ProbeBitsetStateLift {
  def main(args: Array[String]): Unit = {
    if (args.length != 2) {
      System.err.println(
        "Usage: ProbeBitsetStateLift <design.fir> <register[,register...]>")
      System.exit(2)
    }
    val input = new File(args(0)).getCanonicalFile
    require(input.isFile, s"missing input FIRRTL: $input")
    val registers = args(1).split(',').map(_.trim).filter(_.nonEmpty).toSet
    require(registers.nonEmpty, "at least one bitset register is required")

    val source = Source.fromFile(input)
    val circuit = try Parser.parse(source.getLines(), Parser.IgnoreInfo)
      finally source.close()
    val compiler = new firrtl.stage.transforms.Compiler(Seq(
      Dependency(BitsetStateLift), Dependency(firrtl.passes.ExpandWhens)))
    val result = compiler.execute(CircuitState(circuit, Seq(
      EssentOptionsAnnotation(OptFlags(simdV2 = true)),
      BitsetStateLiftConfigAnnotation(registers))))
    val mappings = result.annotations.collect {
      case annotation: IndexedCounterBankStorageAnnotation
          if registers.exists(value => value.split('.').last == annotation.family) => annotation
    }
    println(s"[v2-bitset-bank-probe] lifted=${mappings.size}")
    mappings.sortBy(mapping => (mapping.module, mapping.family)).foreach { mapping =>
      println(s"[v2-bitset-bank-probe] storage=${mapping.module}.${mapping.family} " +
        s"depth=${mapping.membersByIndex.size} banks=${mapping.banks.size} " +
        s"first=${mapping.membersByIndex.head} last=${mapping.membersByIndex.last}")
    }
  }
}
