package essent

import firrtl.ir._
import essent.Emitter._
import essent.Extract._
import essent.ir._
import essent.simd.VecStmtInfo
import firrtl.Utils.{False, True}

import collection.mutable.{ArrayBuffer, BitSet, HashMap}
import scala.reflect.ClassTag

// Extends Graph to include more attributes per node
//  - Associates a name (String) and Statement with each node
//  - Name must be unique, since can find nodes by name too
//  - Nodes can have an EmptyStatement if no need to emit

class StatementGraph extends Graph {
  // Access companion object's type aliases without prefix
                                                                       
  import Graph.{NodeID, AdjacencyList}


  // Internal data structures
  //----------------------------------------------------------------------------
  // Vertex name (string of destination variable) -> numeric ID
  val nameToID = HashMap[String,NodeID]()
  // Numeric vertex ID -> name (string destination variable)
  val idToName = ArrayBuffer[String]()
  // Numeric vertex ID -> firrtl statement (Block used for aggregates)
  val idToStmt = ArrayBuffer[Statement]()
  // Numeric vertex ID -> Boolean indicating whether node should be emitted
  val validNodes = BitSet()


  //rikora
  val nameToDeps = HashMap[String, Seq[String]]()
  def makeSeqDeps(): Unit = {
    idToStmt.zipWithIndex foreach { case(stmt, id) => {
      val sourceRegs = stmt match {
        case dr: DefRegister => Some(dr.name)
        // case mw: MemWrite => Some(mw.memName)
        case _ => None
      }
      sourceRegs foreach { 
        sr : String =>
        val successors = getAllSuccessors(nameToID(sr))
        successors foreach { succ =>
          if(idToStmt(succ).isInstanceOf[RegUpdate]) {
            val targetName = idToName(succ)
            nameToDeps(targetName) = nameToDeps.getOrElse(targetName, Seq()) :+ sr
          }
        }
      }
    }}
    println(s"Sequential Dep Map: ${nameToDeps.size} entries")
  }

  // Graph building
  //----------------------------------------------------------------------------
  def getID(vertexName: String) = {
    if (nameToID contains vertexName) nameToID(vertexName)
    else {
      val newID = nameToID.size                
      nameToID(vertexName) = newID
      idToName += vertexName
      idToStmt += EmptyStmt                         
      growNeighsIfNeeded(newID)
                                                                        
      newID
    }
  }

  def addEdge(sourceName: String, destName: String): Unit = {
    super.addEdge(getID(sourceName), getID(destName))
  }

  def addEdgeIfNew(sourceName: String, destName: String): Unit = {
    super.addEdgeIfNew(getID(sourceName), getID(destName))
  }

  def addStatementNode(resultName: String, depNames: Seq[String],
                       stmt: Statement = EmptyStmt): Unit = {
                        
    val potentiallyNewDestID = getID(resultName)

                                                          
    depNames foreach {depName : String => addEdge(depName, resultName)}

    if (potentiallyNewDestID >= idToStmt.size) {
      val numElemsToGrow = potentiallyNewDestID - idToStmt.size + 1
      idToStmt.appendAll(ArrayBuffer.fill(numElemsToGrow)(EmptyStmt))
    }
    idToStmt(potentiallyNewDestID) = stmt
    // Don't want to emit state element declarations
    if (!stmt.isInstanceOf[DefRegister] && !stmt.isInstanceOf[DefMemory])
      validNodes += potentiallyNewDestID
  }

  def buildFromBodies(bodies: Seq[Statement]): Unit = {
    val bodyHE = bodies flatMap {
      case b: Block => b.stmts flatMap findDependencesStmt                                                         
      case s => findDependencesStmt(s)
    }
    println(s"Building graph from ${bodyHE.size} hyperedges...")
    bodyHE foreach { he => addStatementNode(he.name, he.deps, he.stmt) }
  }


  // Traversal / Queries / Extraction
  //----------------------------------------------------------------------------
  def collectValidStmts(ids: Seq[NodeID]): Seq[Statement] = ids filter validNodes map idToStmt

  def stmtsOrdered(kahn: Boolean = false, width: Int = 2): Seq[Statement] = kahn match {
      case true =>
        collectValidStmts(TopologicalSortKahn(this, width).toSeq)
      case false =>
        collectValidStmts(TopologicalSort(this).toSeq)
  }

  def containsStmtOfType[T <: Statement]()(implicit tag: ClassTag[T]): Boolean = {
    (idToStmt collectFirst { case s: T => s }).isDefined
  }

  def findIDsOfStmtOfType[T <: Statement]()(implicit tag: ClassTag[T]): Seq[NodeID] = {
    (idToStmt.zipWithIndex collect { case (s: T , id: Int) => id }).toSeq
  }

  def allRegDefs(): Seq[DefRegister] = (idToStmt collect {
    case dr: DefRegister => dr
  }).toSeq

  def stateElemNames(): Seq[String] = (idToStmt collect {
    case dr: DefRegister => dr.name
    case dm: DefMemory => dm.name
  }).toSeq

  def stateElemIDs() = findIDsOfStmtOfType[DefRegister]() ++ findIDsOfStmtOfType[DefMemory]()

  def mergeIsAcyclic(nameA: String, nameB: String): Boolean = {
    val idA = nameToID(nameA)
    val idB = nameToID(nameB)
    super.mergeIsAcyclic(idA, idB)
  }

  def extractSourceIDs(e: Expression): Seq[NodeID] = findDependencesExpr(e) map nameToID


  // Mutation
  //----------------------------------------------------------------------------
  def addOrderingDepsForStateUpdates(): Unit = {
    def addOrderingEdges(writerID: NodeID, readerTargetID: NodeID): Unit = {
                                                
      outNeigh(readerTargetID) foreach {
        readerID => if (readerID != writerID) addEdgeIfNew(readerID, writerID)
      }
    }
    idToStmt.zipWithIndex foreach { case(stmt, id) => {
      val readerTargetName = stmt match {
        case ru: RegUpdate => Some(emitExpr(ru.regRef))
        case cru: CondRegUpdate => Some(emitExpr(cru.regRef))
        case mw: MemWrite => Some(mw.memName)
        case _ => None
      }
      readerTargetName foreach { 
        name =>
        // println(s"Adding ordering edges for state update stmt: $name")
        if (nameToID.contains(name)) addOrderingEdges(id, nameToID(name))
      }
    }}
  }


  val orderingEdges = collection.mutable.HashSet[(NodeID, NodeID, String)]()

  def addOrderingDepsForStateUpdatesReverse(): Unit = {
    def isDefNode(id: NodeID): Boolean = {
      val stmt = idToStmt(id)
      !stmt.isInstanceOf[DefRegister] && !stmt.isInstanceOf[DefMemory] && stmt != EmptyStmt
    }

    def isLBNRegister(regName: String): Boolean =
      nameToID.contains(regName + "$oracle")

    def addReverseOrderingEdges(writerID: NodeID, readerTargetID: NodeID, reason: String): Unit = {
      outNeigh(readerTargetID).toSeq foreach { readerID =>
        if (readerID != writerID && isDefNode(readerID)) {
          addEdgeIfNew(writerID, readerID)
          orderingEdges += ((writerID, readerID, reason))
        }
      }
    }

    def addStandardOrderingEdges(writerID: NodeID, readerTargetID: NodeID, reason: String): Unit = {
      outNeigh(readerTargetID) foreach {
        readerID => if (readerID != writerID) {
          addEdgeIfNew(readerID, writerID)
          orderingEdges += ((readerID, writerID, reason))
        }
      }
    }

    idToStmt.zipWithIndex foreach { case(stmt, id) => {
      stmt match {
        case ru: RegUpdate if !(ru.info.isInstanceOf[FileInfo] && ru.info.asInstanceOf[FileInfo].escaped == "final_commit") =>
          val name = emitExpr(ru.regRef)
          if (isLBNRegister(name)) {
          } else if (nameToID.contains(name)) {
            addReverseOrderingEdges(id, nameToID(name), s"reverse:inter_lane_shift($name)")
          }

        case cru: CondRegUpdate if !(cru.info.isInstanceOf[FileInfo] && cru.info.asInstanceOf[FileInfo].escaped == "final_commit") =>
          val name = emitExpr(cru.regRef)
          if (nameToID.contains(name)) {
            addReverseOrderingEdges(id, nameToID(name), s"reverse:cond_reg_update($name)")
          }

        case mw: MemWrite =>
          val name = mw.memName
          if (nameToID.contains(name)) addStandardOrderingEdges(id, nameToID(name), s"standard:mem_write($name)")

        case _ =>
      }

      stmt match {
        case ru: RegUpdate if ru.info.isInstanceOf[FileInfo] &&
            ru.info.asInstanceOf[FileInfo].escaped == "final_commit" =>
          val regName = emitExpr(ru.regRef)
          if (isLBNRegister(regName)) {
          } else {
            val ruName = regName + "$final"
            if (nameToID.contains(ruName)) {
              val ruID = nameToID(ruName)
              outNeigh(ruID).toSeq foreach { readerID =>
                if (readerID != id) {
                  addEdgeIfNew(readerID, id)
                  orderingEdges += ((readerID, id, s"final_commit_wait($regName)"))
                }
              }
            }
          }
        case cru: CondRegUpdate if cru.info.isInstanceOf[FileInfo] &&
            cru.info.asInstanceOf[FileInfo].escaped == "final_commit" =>
          val regName = emitExpr(cru.regRef)
          val ruName = regName + "$final"
          if (nameToID.contains(ruName)) {
            val ruID = nameToID(ruName)
            outNeigh(ruID).toSeq foreach { readerID =>
              if (readerID != id) {
                addEdgeIfNew(readerID, id)
                orderingEdges += ((readerID, id, s"final_commit_wait($regName)"))
              }
            }
          }
        case _ =>
      }
    }}
  }


  def addInterLaneMemoryDeps(isForward: Boolean, vectorWidth: Int,
      flatVecMeta: HashMap[String, VecStmtInfo] = HashMap.empty): Unit = {
    val memWritesByBaseLane = idToStmt.zipWithIndex.collect {
      case (mw: MemWrite, id) =>
        flatVecMeta.get(mw.memName).map { info =>
          (info.scalarSource, info.laneIndex, id, mw)
        }
    }.flatten

    // Build reverse index: (scalarSource, laneIndex) → memName
    val srcToLaneNames = collection.mutable.Map[(String, Int), String]()
    for ((mw: MemWrite, _) <- idToStmt.zipWithIndex) {
      flatVecMeta.get(mw.memName).foreach { info =>
        srcToLaneNames((info.scalarSource, info.laneIndex)) = mw.memName
      }
    }

    for ((scalarSrc, lane, mwID, _) <- memWritesByBaseLane) {
      val adjacentLane = if (isForward) lane + 1 else lane - 1
      if (adjacentLane >= 0 && adjacentLane < vectorWidth) {
        srcToLaneNames.get((scalarSrc, adjacentLane)).foreach { adjacentMemName =>
          if (nameToID.contains(adjacentMemName)) {
            val adjacentMemID = nameToID(adjacentMemName)
            outNeigh(adjacentMemID).toSeq.foreach { readerID =>
              if (readerID != mwID) {
                addEdgeIfNew(mwID, readerID)
              }
            }
          }
        }
      }
    }
  }

  def mergeStmtsMutably(mergeDest: NodeID, mergeSources: Seq[NodeID], mergeStmt: Statement): Unit = {
    val mergedID = mergeDest
    val idsToRemove = mergeSources
    idsToRemove foreach { id => idToStmt(id) = EmptyStmt }
    // NOTE: keeps mappings of name (idToName & nameToID) for debugging dead nodes
    mergeNodesMutably(mergeDest, mergeSources)
    idToStmt(mergeDest) = mergeStmt
    validNodes(mergeDest) = (mergeSources :+ mergeDest) exists { validNodes }
    validNodes --= idsToRemove
  }


  // Stats
  //----------------------------------------------------------------------------
  def numValidNodes() = validNodes.size

  def numNodeRefs() = idToName.size

  def makeStatsString() =
    s"Graph has ${numNodes()} nodes (${numValidNodes()} valid) and ${numEdges()} edges"

  def dump(): String = {
    val sb = new StringBuilder
    sb.append(makeStatsString()).append('\n')
    nodeRange() foreach { id =>
      val name = if (id < idToName.size) idToName(id) else s"$id"
      val validStr = if (validNodes(id)) "valid" else "dead"
      val stmtType = if (id < idToStmt.size) idToStmt(id).getClass.getSimpleName else "EmptyStmt"
      val inNames = inNeigh(id).map(idToName).mkString(", ")
      val outNames = outNeigh(id).map(idToName).mkString(", ")
      sb.append(s"[$id] $name ($validStr, $stmtType)\n")
      if (inNeigh(id).nonEmpty) sb.append(s"  in:  $inNames\n")
      if (outNeigh(id).nonEmpty) sb.append(s"  out: $outNames\n")
    }
    sb.toString
  }

  def printDump(): Unit = {
    println(dump())
  }

  private def escapeLabel(s: String): String =
    s.replace("\\", "\\\\").replace("\"", "\\\"")

  def toDot(includeDead: Boolean = true): String = {
    val sb = new StringBuilder
    sb.append("digraph StatementGraph {\n")
    sb.append("  rankdir=LR;\n")
    // nodes
    nodeRange() foreach { id =>
      val name = if (id < idToName.size) idToName(id) else s"$id"
      val stmtType = if (id < idToStmt.size) idToStmt(id).getClass.getSimpleName else "EmptyStmt"
      val isValid = validNodes(id)
      if (includeDead || isValid) {
        val style = if (isValid) "" else ",style=dashed"
        val label = escapeLabel(s"$name\\n$stmtType")
        sb.append(s"  $id [label=\"$label\",shape=box$style];\n")
      }
    }
    // edges
    nodeRange() foreach { src =>
      val srcIncluded = includeDead || validNodes(src)
      if (srcIncluded) {
        outNeigh(src) foreach { dst =>
          val dstIncluded = includeDead || validNodes(dst)
          if (dstIncluded) sb.append(s"  $src -> $dst;\n")
        }
      }
    }
    sb.append("}\n")
    sb.toString
  }

  def dumpDot(path: String, includeDead: Boolean = true): Unit = {
    val pw = new java.io.PrintWriter(path)
    try pw.write(toDot(includeDead)) finally pw.close()
  }
}



object StatementGraph {
  def apply(bodies: Seq[Statement], isSIMD: Boolean): StatementGraph = {
    println("Building StatementGraph...")
    // print(bodies)
    val sg = new StatementGraph
    sg.buildFromBodies(bodies)

                         
    if(isSIMD) {
      println("SIMD building StatementGraph...")
      sg.addOrderingDepsForStateUpdatesReverse()
    }
    else{
      sg.addOrderingDepsForStateUpdates()
    }
    sg
  }

  def apply(circuit: Circuit, removeFlatConnects: Boolean = true, isSIMD:Boolean): StatementGraph ={
    apply(flattenWholeDesign(circuit, removeFlatConnects, isSIMD), isSIMD)
  }
}
