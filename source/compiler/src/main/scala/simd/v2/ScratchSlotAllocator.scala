package essent.simd.v2

import java.util.BitSet
import scala.collection.mutable

/** Typed scratch slots shared across disjoint lifetimes in every eval body. */
private[v2] object ScratchSlotAllocator {
  final case class Interval(first: Int, last: Int) {
    require(first <= last)
  }

  final case class Value(typeId: Int, order: Int,
      lifetimes: Vector[Option[Interval]], dedicated: Boolean = false)

  def allocate(values: Vector[Value]): Array[Int] = {
    val count = values.size
    val colors = Array.fill(count)(-1)
    if (count == 0) return colors
    val timelines = values.head.lifetimes.size
    require(values.forall(_.lifetimes.size == timelines))
    val groups = values.indices.groupBy(i => values(i).typeId).toSeq.sortBy(_._1)

    for ((_, members) <- groups) {
      // Unknown or cross-window values get private slots. There is no reason
      // to build their complete conflict graph or repeatedly color its clique.
      val (privateValues, reusable) = members.partition(i => values(i).dedicated)
      privateValues.sortBy(i => values(i).order).zipWithIndex.foreach {
        case (id, color) => colors(id) = color
      }
      val firstReusableColor = privateValues.size
      if (reusable.nonEmpty) {
        val neighbors = new Array[BitSet](count)
        reusable.foreach(i => neighbors(i) = new BitSet(count))
        for (timeline <- 0 until timelines) {
          val present = reusable.filter(i => values(i).lifetimes(timeline).isDefined)
            .sortBy(i => (values(i).lifetimes(timeline).get.first, values(i).order))
          val active = mutable.ArrayBuffer[Int]()
          for (id <- present) {
            val start = values(id).lifetimes(timeline).get.first
            var kept = 0
            var j = 0
            while (j < active.size) {
              val other = active(j)
              if (values(other).lifetimes(timeline).get.last >= start) {
                active(kept) = other
                kept += 1
                neighbors(id).set(other)
                neighbors(other).set(id)
              }
              j += 1
            }
            active.trimEnd(active.size - kept)
            active += id
          }
        }

        val usedColors = new Array[BitSet](count)
        reusable.foreach(i => usedColors(i) = new BitSet())
        val saturation = Array.fill(count)(0)
        val degree = Array.fill(count)(0)
        reusable.foreach(i => degree(i) = neighbors(i).cardinality())

        // An indexed heap keeps one entry per uncolored value. Recomputing
        // every candidate's neighbor colors at every selection made Rocket's
        // 10K-value plan take minutes. Lazy heap entries would instead retain
        // millions of stale entries on dense graphs.
        val heap = reusable.toArray
        val position = Array.fill(count)(-1)
        var heapSize = heap.length
        heap.indices.foreach(i => position(heap(i)) = i)
        def better(a: Int, b: Int): Boolean = {
          if (saturation(a) != saturation(b)) saturation(a) > saturation(b)
          else if (degree(a) != degree(b)) degree(a) > degree(b)
          else values(a).order < values(b).order
        }
        def swap(a: Int, b: Int): Unit = {
          val saved = heap(a)
          heap(a) = heap(b)
          heap(b) = saved
          position(heap(a)) = a
          position(heap(b)) = b
        }
        def up(from: Int): Unit = {
          var at = from
          while (at > 0 && better(heap(at), heap((at - 1) / 2))) {
            val parent = (at - 1) / 2
            swap(at, parent)
            at = parent
          }
        }
        def down(from: Int): Unit = {
          var at = from
          var finished = false
          while (!finished && at * 2 + 1 < heapSize) {
            val left = at * 2 + 1
            val right = left + 1
            val child = if (right < heapSize && better(heap(right), heap(left))) right else left
            if (better(heap(child), heap(at))) {
              swap(at, child)
              at = child
            } else finished = true
          }
        }
        var build = heapSize / 2 - 1
        while (build >= 0) { down(build); build -= 1 }

        while (heapSize != 0) {
          val pick = heap(0)
          heapSize -= 1
          if (heapSize != 0) {
            heap(0) = heap(heapSize)
            position(heap(0)) = 0
            down(0)
          }
          position(pick) = -1
          val color = usedColors(pick).nextClearBit(firstReusableColor)
          colors(pick) = color
          var other = neighbors(pick).nextSetBit(0)
          while (other >= 0) {
            if (colors(other) < 0 && !usedColors(other).get(color)) {
              usedColors(other).set(color)
              saturation(other) += 1
              up(position(other))
            }
            other = neighbors(pick).nextSetBit(other + 1)
          }
        }
        reusable.foreach { id =>
          var other = neighbors(id).nextSetBit(id + 1)
          while (other >= 0) {
            require(colors(id) != colors(other), "overlapping scratch values share a slot")
            other = neighbors(id).nextSetBit(other + 1)
          }
        }
      }
    }
    colors
  }
}
