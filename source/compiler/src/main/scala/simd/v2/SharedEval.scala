package essent.simd.v2

import java.io.Writer
import scala.collection.mutable.ArrayBuffer

/** Share complete emitted blocks without changing either directional schedule.
  * Blocks have no escaping local declarations: the fixed-direction emitter
  * already permits an outlined function boundary between any two blocks. */
private[v2] object SharedEval {
  final case class Block(key: String, weight: Int, text: String) {
    lazy val code: String = text.linesIterator
      .filterNot(line => line.trim.isEmpty || line.trim.startsWith("//")).mkString("\n")
  }

  final class Capture extends Writer {
    private val text = new java.lang.StringBuilder
    private val body = ArrayBuffer[Block]()
    private var current: Option[(String, Int)] = None
    private var prelude = ""
    private var ended = false

    override def write(chars: Array[Char], offset: Int, length: Int): Unit = {
      text.append(chars, offset, length)
      ()
    }
    override def flush(): Unit = ()
    override def close(): Unit = ()

    private def drain(): String = {
      val result = text.toString
      text.setLength(0)
      result
    }
    def beforeBlock(key: String, weight: Int): Unit = {
      require(!ended)
      current match {
        case Some((previous, cost)) => body += Block(previous, cost, drain())
        case None => prelude = drain()
      }
      current = Some(key -> weight)
    }
    def finishBody(): Unit = {
      require(!ended)
      current match {
        case Some((key, weight)) => body += Block(key, weight, drain())
        case None => prelude = drain()
      }
      current = None
      ended = true
    }
    def prefix: String = { require(ended); prelude }
    def suffix: String = { require(ended); text.toString }
    def blocks: Vector[Block] = { require(ended); body.toVector }
  }

  final case class Part(forward: Vector[Block], reverse: Vector[Block], shared: Boolean) {
    def weight: Int = math.max(forward.map(_.weight).sum, reverse.map(_.weight).sum)
  }

  /** Unique block identities yield an ordered set of common anchors via LIS.
    * Unmatched regions retain their original order inside directional arms;
    * no topological equivalence or lane-index substitution is assumed. */
  def align(forward: Vector[Block], reverse: Vector[Block], limit: Int): Vector[Part] = {
    require(limit > 0)
    def unique(blocks: Vector[Block]): Map[String, Int] =
      blocks.zipWithIndex.groupBy(_._1.key).iterator.collect {
        case (key, Seq((_, index))) => key -> index
      }.toMap
    val fi = unique(forward)
    val ri = unique(reverse)
    val candidates = forward.indices.flatMap(i =>
      ri.get(forward(i).key).filter(_ => fi.contains(forward(i).key)).map(j => i -> j)).toVector
    val tails = ArrayBuffer[Int]()
    val previous = Array.fill(candidates.size)(-1)
    for (i <- candidates.indices) {
      val target = candidates(i)._2
      var lo = 0
      var hi = tails.size
      while (lo < hi) {
        val mid = (lo + hi) / 2
        if (candidates(tails(mid))._2 < target) lo = mid + 1 else hi = mid
      }
      if (lo > 0) previous(i) = tails(lo - 1)
      if (lo == tails.size) tails += i else tails(lo) = i
    }
    val anchors = ArrayBuffer[(Int, Int)]()
    var at = tails.lastOption.getOrElse(-1)
    while (at >= 0) { anchors += candidates(at); at = previous(at) }

    val parts = ArrayBuffer[Part]()
    val pendingF = ArrayBuffer[Block]()
    val pendingR = ArrayBuffer[Block]()
    def bounded(blocks: Seq[Block]): Vector[Vector[Block]] = {
      val groups = ArrayBuffer[Vector[Block]]()
      val group = ArrayBuffer[Block]()
      var weight = 0
      for (block <- blocks) {
        if (group.nonEmpty && weight + block.weight > limit) {
          groups += group.toVector; group.clear(); weight = 0
        }
        group += block; weight += block.weight
      }
      if (group.nonEmpty) groups += group.toVector
      groups.toVector
    }
    def flush(): Unit = {
      for ((f, r) <- bounded(pendingF.toSeq).zipAll(bounded(pendingR.toSeq), Vector.empty, Vector.empty))
        parts += Part(f, r, shared = false)
      pendingF.clear(); pendingR.clear()
    }
    var f = 0
    var r = 0
    for ((nextF, nextR) <- anchors.reverseIterator) {
      pendingF ++= forward.slice(f, nextF)
      pendingR ++= reverse.slice(r, nextR)
      if (forward(nextF).code == reverse(nextR).code) {
        flush()
        parts += Part(Vector(forward(nextF)), Vector(reverse(nextR)), shared = true)
      } else {
        pendingF += forward(nextF); pendingR += reverse(nextR)
      }
      f = nextF + 1; r = nextR + 1
    }
    pendingF ++= forward.drop(f); pendingR ++= reverse.drop(r)
    flush()
    parts.toVector
  }
}
