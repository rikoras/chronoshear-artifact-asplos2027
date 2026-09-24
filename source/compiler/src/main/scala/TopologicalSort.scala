package essent

import Graph._
import essent.ir.{RegUpdate, CondRegUpdate, CondMux}
import essent.simd.{VecStmtInfo}
import firrtl.ir.{Statement, DefNode, Connect}

import collection.mutable.{ArrayBuffer, BitSet, HashMap}
import collection.mutable.LinkedHashSet

object TopologicalSort {
  def apply(g: Graph) = {
    val finalOrdering = ArrayBuffer[NodeID]()
    val inStack = BitSet()
    val finished = BitSet()
    def visit(v: NodeID): Unit = {
      if (inStack(v)) {
        findCyclesByTopoSort(g) match {
          case None => throw new Exception("Was a cycle but couldn't reproduce")
          case Some(cycle) => {
            cycle foreach println
            throw new Exception("There is a cycle! (above)")
          }
        }
      } else if (!finished(v)) {
        inStack.add(v)
        g.inNeigh(v) foreach { u => visit(u) }
        finished.add(v)
        inStack.remove(v)
        finalOrdering += v
      }
    }
    g.nodeRange() foreach { 
      startingID =>
      visit(startingID) 
    }
    finalOrdering
  }


  def findCyclesByTopoSort(bg: Graph): Option[Seq[NodeID]] = {
    var cycleFound: Option[Seq[NodeID]] = None
    val inStack = BitSet()
    val finished = BitSet()
    val callerIDs = ArrayBuffer.fill(bg.numNodes())(-1)

    def backtrackToFindCycle(v: NodeID, cycleSoFar: Seq[NodeID]): Seq[NodeID] = {
      if (callerIDs(v) == -1) cycleSoFar
      else if (bg.outNeigh(v).forall(!cycleSoFar.contains(_)))
        backtrackToFindCycle(callerIDs(v), cycleSoFar ++ Seq(v))
      else {
        val loopbackIndices = bg.outNeigh(v) map cycleSoFar.indexOf
        val trimmedCycle = cycleSoFar.drop(loopbackIndices.max)
        trimmedCycle ++ Seq(v)
      }
    }

    def visit(v: NodeID, callerID: NodeID): Unit = {
      if (inStack(v)) {
        val cycle = backtrackToFindCycle(callerID, Seq(v))
        cycleFound = Some(cycle)
      } else if (!finished(v)) {
        if (v != callerID)
          callerIDs(v) = callerID
        inStack.add(v)
        bg.inNeigh(v) foreach { u => visit(u, v) }
        finished.add(v)
        inStack.remove(v)
      }
    }
    bg.nodeRange() foreach { startingID => visit(startingID, startingID) }
    cycleFound
  }
}



object TopologicalSortKahn {

  private case class ReadyNodeInfo(
    id: NodeID,
    position: Int,
    familyKey: String,
    laneIndex: Option[Int]
  )

  /** Pre-compute lane index and family key for every node BEFORE the sort.
   *  Uses flatVecMeta (from LaneTag + ReconcileLaneMeta) as the primary lane source,
   *  with dependency propagation for derived nodes not in the annotation. */
  private def precomputeLaneInfo(
    g: Graph, width: Int, flatVecMeta: HashMap[String, VecStmtInfo] = HashMap.empty
  ): (Array[Option[Int]], Array[String]) = {
    val n = g.numNodes()
    val lane = Array.fill[Option[Int]](n)(None)
    val family = Array.fill[String](n)("")
    val laneSource = Array.fill[Int](n)(0) // 0=none, 1=annotation, 3=inferred

    g match {
      case sg: StatementGraph =>
        val KnownSuffixes = essent.simd.SIMDConstants.KnownSuffixes
        def stripKnownSuffix(name: String): String =
          KnownSuffixes.find(s => name.endsWith(s)).map(sfx => name.dropRight(sfx.length)).getOrElse(name)

        // Phase 1: annotation-based lane assignment
        g.nodeRange().foreach { id =>
          val name = sg.idToName(id)
          val baseName = stripKnownSuffix(name)
          flatVecMeta.get(baseName).foreach { info =>
            if (info.laneIndex < width) {
              lane(id) = Some(info.laneIndex)
              laneSource(id) = 1
            }
          }
        }

        // Phase 2: propagate lane from dependencies
        var changed = true
        while (changed) {
          changed = false
          g.nodeRange().foreach { id =>
            if (lane(id).isEmpty) {
              val depLanes = sg.inNeigh(id)
                .flatMap(dep => lane(dep))
                .filter(_ < width)
                .distinct
              if (depLanes.size == 1) {
                lane(id) = Some(depLanes.head)
                laneSource(id) = 3
                changed = true
              }
            }
          }
        }

        // Phase 3: compute family keys
        val familyDone = Array.fill(n)(false)

        // 3a: annotation-sourced nodes — use scalarSource as family key
        g.nodeRange().foreach { id =>
          if (laneSource(id) == 1) {
            val name = sg.idToName(id)
            val baseName = stripKnownSuffix(name)
            val kind = sg.idToStmt(id).getClass.getSimpleName
            val scalarSrc = flatVecMeta.get(baseName).map(_.scalarSource).getOrElse(baseName)
            family(id) = s"$kind:$scalarSrc"
            familyDone(id) = true
          }
        }

        // 3b: scalar nodes (no lane)
        g.nodeRange().foreach { id =>
          if (!familyDone(id) && lane(id).isEmpty) {
            val kind = sg.idToStmt(id).getClass.getSimpleName
            family(id) = s"$kind:${sg.idToName(id)}"
            familyDone(id) = true
          }
        }

        // 3c: dep-inferred nodes — use dep family keys (recursive)
        changed = true
        while (changed) {
          changed = false
          g.nodeRange().foreach { id =>
            if (!familyDone(id)) {
              val allDepsReady = sg.inNeigh(id).forall(familyDone(_))
              if (allDepsReady) {
                val kind = sg.idToStmt(id).getClass.getSimpleName
                val depFamSig = sg.inNeigh(id).toSeq
                  .map(dep => family(dep))
                  .sorted
                  .mkString(",")
                family(id) = s"$kind:dep($depFamSig)"
                familyDone(id) = true
                changed = true
              }
            }
          }
        }

      case _ =>
        g.nodeRange().foreach { id =>
          family(id) = s"Node:$id"
        }
    }

    (lane, family)
  }

  private def preferWithinFamily(
    nodes: Seq[ReadyNodeInfo], preferredNextLane: Option[Int], width: Int
  ): ReadyNodeInfo = {
    preferredNextLane.flatMap { nextLane =>
      nodes.find(_.laneIndex.contains(nextLane))
    }.getOrElse {
      nodes.minBy { info =>
        val laneScore = info.laneIndex match {
          case Some(0) => (0, 0)
          case Some(idx) if idx < width => (1, idx)
          case Some(idx) => (2, idx)
          case None => (3, Int.MaxValue)
        }
        (laneScore._1, laneScore._2, info.position)
      }
    }
  }

  // Nodes whose family benefits from lane grouping (combinational logic).
  // These are deferred until their full family is ready.
  private def isGroupable(stmt: Statement): Boolean = stmt match {
    case _: DefNode  => true
    case _: Connect  => true
    case _: CondMux  => true
    case _ => false
  }

  private def chooseNextReadyNode(
    worklist: LinkedHashSet[NodeID],
    deferred: LinkedHashSet[NodeID],
    lastFamilyKey: Option[String],
    lastLaneIndex: Option[Int],
    preFamily: Array[String],
    preLane: Array[Option[Int]],
    width: Int,
    g: Graph
  ): NodeID = {
    val allReady = (worklist.toSeq ++ deferred.toSeq).zipWithIndex.map { case (id, pos) =>
      ReadyNodeInfo(id, pos, preFamily(id), preLane(id))
    }
    val readyGroups = allReady.groupBy(_.familyKey)

    // Check which deferred families are now complete
    val newlyComplete = deferred.toSeq.filter { id =>
      val fam = preFamily(id)
      val group = readyGroups.getOrElse(fam, Seq.empty)
      group.size >= width && group.exists(_.laneIndex.isDefined)
    }
    newlyComplete.foreach { id =>
      deferred.remove(id)
      worklist.add(id)
    }

    val worklistInfos = worklist.toSeq.zipWithIndex.map { case (id, pos) =>
      ReadyNodeInfo(id, pos, preFamily(id), preLane(id))
    }

    if (worklistInfos.isEmpty) {
      // All ready nodes are deferred. Un-defer the most-complete family.
      val deferredInfos = deferred.toSeq.map { id =>
        ReadyNodeInfo(id, 0, preFamily(id), preLane(id))
      }
      val deferredGroups = deferredInfos.groupBy(_.familyKey).values.toSeq
      val bestGroup = deferredGroups.maxBy(_.size)
      bestGroup.foreach(info => { deferred.remove(info.id); worklist.add(info.id) })
      return preferWithinFamily(bestGroup, Some(0), width).id
    }

    // Priority 1: continue current family
    val preferredFromLast = lastFamilyKey.flatMap { key =>
      val sameFamily = worklistInfos.filter(_.familyKey == key)
      if (sameFamily.nonEmpty) {
        Some(preferWithinFamily(sameFamily, lastLaneIndex.map(_ + 1), width).id)
      } else None
    }

    preferredFromLast.getOrElse {
      val wlGroups = worklistInfos.groupBy(_.familyKey).values.toSeq
      val completeFamilies = wlGroups.filter { group =>
        group.size >= width && group.exists(_.laneIndex.isDefined)
      }
      val scalarNodes = worklistInfos.filter(_.laneIndex.isEmpty)

      if (completeFamilies.nonEmpty) {
        // Priority 2: complete lane families
        val chosenGroup = completeFamilies.maxBy { group =>
          val exactMatch = if (group.size == width) 1 else 0
          val hasLaneZero = group.exists(_.laneIndex.contains(0))
          val earliestPosition = group.map(_.position).min
          (exactMatch, group.size, if (hasLaneZero) 1 else 0, -earliestPosition)
        }
        preferWithinFamily(chosenGroup, Some(0), width).id
      } else if (scalarNodes.nonEmpty) {
        // Priority 3: scalar nodes
        scalarNodes.minBy(_.position).id
      } else {
        // Priority 4: only incomplete lane nodes in worklist.
        // These are non-groupable types (RegUpdate, etc.) — emit immediately.
        val wlGroupsSorted = wlGroups.sortBy(g => (-g.size, g.head.position))
        val chosenGroup = wlGroupsSorted.head
        if (chosenGroup.size > 1)
          preferWithinFamily(chosenGroup, Some(0), width).id
        else
          chosenGroup.head.id
      }
    }
  }

  def apply(g: Graph, width: Int = 2, flatVecMeta: HashMap[String, VecStmtInfo] = HashMap.empty) = {
    val numNodes = g.numNodes()
    val inDegree = new Array[Int](numNodes)
    val finalOrdering = new ArrayBuffer[NodeID](numNodes)

    val (preLane, preFamily) = precomputeLaneInfo(g, width, flatVecMeta)

    // Pre-compute which nodes are groupable (combinational logic that benefits
    // from having all lane siblings emitted together).
    val groupable = Array.fill(numNodes)(false)
    g match {
      case sg: StatementGraph =>
        g.nodeRange().foreach { id =>
          if (preLane(id).isDefined) groupable(id) = isGroupable(sg.idToStmt(id))
        }
      case _ =>
    }

    g.nodeRange().foreach { v =>
      inDegree(v) = g.inNeigh(v).size
    }

    val worklist = LinkedHashSet[NodeID]()
    val deferred = LinkedHashSet[NodeID]()

    g.nodeRange().foreach { v =>
      if (inDegree(v) == 0) worklist.add(v)
    }

    def processNode(u: NodeID): Unit = {
      finalOrdering += u
      g.outNeigh(u).foreach { v =>
        inDegree(v) -= 1
        if (inDegree(v) == 0) {
          if (groupable(v)) deferred.add(v)
          else worklist.add(v)
        }
      }
    }

    var lastFamilyKey: Option[String] = None
    var lastLaneIndex: Option[Int] = None

    // Seed: move groupable initial nodes to deferred
    worklist.toSeq.foreach { v =>
      if (groupable(v)) { worklist.remove(v); deferred.add(v) }
    }

    while (worklist.nonEmpty || deferred.nonEmpty) {
      val u = chooseNextReadyNode(
        worklist, deferred, lastFamilyKey, lastLaneIndex,
        preFamily, preLane, width, g
      )

      worklist.remove(u)
      deferred.remove(u)
      processNode(u)

      lastFamilyKey = Some(preFamily(u))
      lastLaneIndex = preLane(u)
    }

    // Post-sort SIMD compaction: iteratively move lane siblings to be adjacent.
    // Each pass may free new opportunities as successors get compacted.
    if (finalOrdering.size == numNodes) {
      var pass = 0
      var keepGoing = true
      while (keepGoing && pass < 10) {
        keepGoing = compactLaneFamilies(finalOrdering, g, preLane, preFamily, groupable, width)
        pass += 1
      }
    }

    if (finalOrdering.size != numNodes) {
      val stuck = g.nodeRange().filterNot(finalOrdering.contains).toSeq
      println(s"\n========== CYCLE DETECTED ==========")
      println(s"Kahn processed ${finalOrdering.size}/${numNodes} nodes, ${stuck.size} stuck")

      g match {
        case sg: StatementGraph =>
          val stuckSet = stuck.toSet
          val stuckWithIncoming = stuck.filter { id =>
            sg.inNeigh(id).exists(stuckSet.contains)
          }

          println(s"\n--- Stuck nodes with stuck predecessors (cycle participants) ---")
          stuckWithIncoming.take(200).foreach { id =>
            val name = sg.idToName(id)
            val stmtKind = sg.idToStmt(id).getClass.getSimpleName
            val stuckPreds = sg.inNeigh(id).filter(stuckSet.contains)
              .map(pid => s"  ${sg.idToName(pid)} [${sg.idToStmt(pid).getClass.getSimpleName}]")
            println(s"\n[$id] $name ($stmtKind)")
            stuckPreds.foreach(p => println(s"  ← $p"))
          }

          findCyclesByTopoSort(g) match {
            case Some(cycle) =>
              println(s"\n--- DFS cycle trace (${cycle.size} nodes) ---")
              cycle.foreach { id =>
                val name = sg.idToName(id)
                val stmtKind = sg.idToStmt(id).getClass.getSimpleName
                val stmtStr = sg.idToStmt(id).serialize.take(120)
                println(s"  [$id] $name ($stmtKind)")
                println(s"        stmt: $stmtStr")
              }
              println(s"\n--- Cycle edges (annotated) ---")
              def edgeLabel(a: Int, b: Int): String = {
                sg.orderingEdges.collectFirst {
                  case (from, to, reason) if from == a && to == b => s"[ORDERING: $reason]"
                }.getOrElse("[DATA_DEP]")
              }
              cycle.sliding(2).foreach {
                case Seq(a, b) =>
                  val aName = sg.idToName(a)
                  val bName = sg.idToName(b)
                  println(s"  $aName  →  $bName  ${edgeLabel(a, b)}")
                case _ =>
              }
              if (cycle.size >= 2) {
                val last = cycle.last
                val first = cycle.head
                println(s"  ${sg.idToName(last)}  →  ${sg.idToName(first)}  ${edgeLabel(last, first)}  (back-edge)")
              }
            case None =>
              println("DFS could not reproduce cycle trace.")
          }
          println("=" * 40)
          throw new Exception("Cycle detected! (details above)")
        case _ =>
          findCyclesByTopoSort(g) match {
            case Some(cycle) =>
              cycle.foreach(println)
              throw new Exception("Cycle detected! (Trace printed above)")
            case None =>
              throw new Exception(s"Cycle detected by Kahn's algo (processed ${finalOrdering.size}/${numNodes} nodes), but DFS trace failed.")
          }
      }
    }
    finalOrdering
  }

  /**
    * Post-sort compaction: for each groupable lane family whose siblings are
    * scattered, move them adjacent to the latest sibling if no dependency is
    * violated.  A node at position A can be moved to position B (B > A) only
    * if no node in (A, B] depends on it.
    */
  private def compactLaneFamilies(
    order: ArrayBuffer[NodeID],
    g: Graph,
    preLane: Array[Option[Int]],
    preFamily: Array[String],
    groupable: Array[Boolean],
    width: Int
  ): Boolean = {
    val n = order.size
    val posOf = new Array[Int](g.numNodes())
    order.zipWithIndex.foreach { case (id, pos) => posOf(id) = pos }

    // For each position, compute "earliest successor position" —
    // the node can safely be delayed up to (but not including) this position.
    val earliestSucc = Array.fill(n)(n)
    order.zipWithIndex.foreach { case (id, pos) =>
      g.outNeigh(id).foreach { succ =>
        val sp = posOf(succ)
        if (sp < earliestSucc(pos)) earliestSucc(pos) = sp
      }
    }

    // Group groupable lane nodes by family
    val familyMembers = collection.mutable.Map[String, ArrayBuffer[(NodeID, Int)]]()
    order.zipWithIndex.foreach { case (id, pos) =>
      if (groupable(id) && preLane(id).isDefined) {
        familyMembers.getOrElseUpdate(preFamily(id), ArrayBuffer()) += ((id, pos))
      }
    }

    // For each family with scattered siblings, try to compact
    var movedNodes = 0
    val toRemove = collection.mutable.BitSet()
    val insertBefore = collection.mutable.Map[Int, ArrayBuffer[NodeID]]()

    familyMembers.foreach { case (_, members) =>
      if (members.size >= 2 && members.size <= 2 * width) {
        val sorted = members.sortBy(_._2)
        val latestPos = sorted.last._2
        val earliestPos = sorted.head._2

        // Skip if already compact (all siblings within a tight window)
        if (latestPos - earliestPos >= sorted.size) {
          val canCompact = sorted.init.forall { case (_, pos) =>
            earliestSucc(pos) > latestPos
          }

          if (canCompact) {
            val toInsert = sorted.init.sortBy { case (id, _) =>
              preLane(id).getOrElse(Int.MaxValue)
            }.map(_._1)
            toInsert.foreach { id => toRemove += posOf(id) }
            insertBefore.getOrElseUpdate(latestPos, ArrayBuffer()).prependAll(toInsert)
            movedNodes += toInsert.size
          }
        }
      }
    }

    if (movedNodes > 0) {
      val newOrder = ArrayBuffer[NodeID]()
      newOrder.sizeHint(n)
      order.zipWithIndex.foreach { case (id, pos) =>
        insertBefore.get(pos).foreach(ins => newOrder ++= ins)
        if (!toRemove(pos)) newOrder += id
      }
      order.clear()
      order ++= newOrder
      println(s"[KahnSort] Post-sort compaction: moved $movedNodes nodes to group ${insertBefore.size} families")
      true
    } else false
  }

  def findCyclesByTopoSort(bg: Graph): Option[Seq[NodeID]] = {
    var cycleFound: Option[Seq[NodeID]] = None
    val inStack = collection.mutable.BitSet()
    val finished = collection.mutable.BitSet()
    val callerIDs = ArrayBuffer.fill(bg.numNodes())(-1)

    def backtrackToFindCycle(v: NodeID, cycleSoFar: Seq[NodeID]): Seq[NodeID] = {
      if (callerIDs(v) == -1) cycleSoFar
      else if (bg.outNeigh(v).forall(!cycleSoFar.contains(_)))
        backtrackToFindCycle(callerIDs(v), cycleSoFar ++ Seq(v))
      else {
        val loopbackIndices = bg.outNeigh(v) map cycleSoFar.indexOf
        val trimmedCycle = cycleSoFar.drop(loopbackIndices.max)
        trimmedCycle ++ Seq(v)
      }
    }

    def visit(v: NodeID, callerID: NodeID): Unit = {
      if (cycleFound.isDefined) return

      if (inStack(v)) {
        val cycle = backtrackToFindCycle(callerID, Seq(v))
        cycleFound = Some(cycle)
      } else if (!finished(v)) {
        if (v != callerID)
          callerIDs(v) = callerID
        inStack.add(v)
        bg.inNeigh(v) foreach { u => visit(u, v) }
        finished.add(v)
        inStack.remove(v)
      }
    }
    bg.nodeRange() foreach { startingID => visit(startingID, startingID) }
    cycleFound
  }
}
