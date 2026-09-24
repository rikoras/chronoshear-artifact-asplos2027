package essent

import essent.Extract._
import essent.ir._
import firrtl.ir._
import firrtl.{PrimOps, WRef}

object OptMuxToLUT {
  val MinChainLength = 16

  def apply(sg: StatementGraph)(implicit rn: Renamer): Int = {
    val candidateInfo = collection.mutable.HashMap[Int, CandidateNode]()
    val nameToId = collection.mutable.HashMap[String, Int]()

    for (id <- sg.idToStmt.indices if sg.validNodes.contains(id)) {
      sg.idToStmt(id) match {
        case DefNode(_, name, Mux(
          DoPrim(PrimOps.Eq, Seq(a, b), _, _),
          tval: UIntLiteral, fval, tpe)) =>
          extractKeyAndIndex(a, b) match {
            case Some((key, indexName)) =>
              val fvalName = fvalRefName(fval)
              val defaultLit = fval match {
                case u: UIntLiteral => Some(u.value)
                case _ => None
              }
              candidateInfo(id) = CandidateNode(key, tval.value, indexName, fvalName, defaultLit)
              nameToId(name) = id
            case None =>
          }
        case _ =>
      }
    }

    if (candidateInfo.isEmpty) return 0

    val referencedAsChainPrev = collection.mutable.Set[String]()
    for ((_, cn) <- candidateInfo) {
      cn.fvalRefName.foreach { ref =>
        if (nameToId.contains(ref)) referencedAsChainPrev += ref
      }
    }

    val tailIds = candidateInfo.keys.filter { id =>
      !referencedAsChainPrev.contains(sg.idToName(id))
    }.toSeq

    var totalConverted = 0

    for (tailId <- tailIds) {
      val tailInfo = candidateInfo(tailId)
      val chain = collection.mutable.ArrayBuffer[(Int, BigInt, BigInt)]()
      chain += ((tailId, tailInfo.key, tailInfo.value))

      val indexName = tailInfo.indexName
      var fvalRef = tailInfo.fvalRefName
      var defaultVal: Option[BigInt] = tailInfo.defaultLit
      var valid = true

      while (valid && fvalRef.isDefined) {
        nameToId.get(fvalRef.get) match {
          case Some(prevId) if candidateInfo.contains(prevId) =>
            val prev = candidateInfo(prevId)
            if (prev.indexName == indexName) {
              chain += ((prevId, prev.key, prev.value))
              defaultVal = prev.defaultLit
              fvalRef = prev.fvalRefName
            } else {
              valid = false
            }
          case _ =>
            valid = false
        }
      }

      // Replacing the tail with a LUT may delete only chain nodes whose value
      // is private to that tail.  StatementGraph.mergeStmtsMutably rewires
      // graph edges, but it cannot rewrite an external statement's WRef to an
      // intermediate `_GEN_*` name.  Deleting a shared intermediate therefore
      // emitted an undeclared C++ identifier in the complete BOOM AXI path.
      val chainIds = chain.iterator.map(_._1).toSet
      val sourceIds = chain.tail.map(_._1).toSeq
      val hasExternalIntermediateConsumer = sourceIds.exists { id =>
        sg.outNeigh(id).exists(consumer => !chainIds.contains(consumer))
      }

      if (!valid || chain.length < MinChainLength || defaultVal.isEmpty ||
          hasExternalIntermediateConsumer) {
        // skip
      } else {
        val maxKey = chain.map(_._2).max.toInt
        val tableSize = maxKey + 1
        val entries = Array.fill[BigInt](tableSize)(defaultVal.get)
        chain.foreach { case (_, k, v) => entries(k.toInt) = v }

        val tailStmt = sg.idToStmt(tailId).asInstanceOf[DefNode]
        val tailMux = tailStmt.value.asInstanceOf[Mux]
        val indexExpr = extractIndexExpr(
          tailMux.cond.asInstanceOf[DoPrim].args.head,
          tailMux.cond.asInstanceOf[DoPrim].args(1))

        val lutStmt = LookupTable(
          name = sg.idToName(tailId),
          indexExpr = indexExpr,
          entries = entries.toSeq,
          resultType = tailMux.tpe
        )

        sg.mergeStmtsMutably(tailId, sourceIds, lutStmt)
        totalConverted += 1
      }
    }

    if (totalConverted > 0)
      println(s"[OptMuxToLUT] Converted $totalConverted mux chains into lookup tables")

    totalConverted
  }

  private case class CandidateNode(
    key: BigInt,
    value: BigInt,
    indexName: String,
    fvalRefName: Option[String],
    defaultLit: Option[BigInt]
  )

  private def extractKeyAndIndex(a: Expression, b: Expression): Option[(BigInt, String)] = {
    (a, b) match {
      case (lit: UIntLiteral, ref) => refName(ref).map(n => (lit.value, n))
      case (ref, lit: UIntLiteral) => refName(ref).map(n => (lit.value, n))
      case _ => None
    }
  }

  private def extractIndexExpr(a: Expression, b: Expression): Expression = {
    (a, b) match {
      case (_: UIntLiteral, ref) => ref
      case (ref, _: UIntLiteral) => ref
      case _ => a
    }
  }

  private def refName(e: Expression): Option[String] = e match {
    case r: Reference => Some(r.name)
    case _ => None
  }

  private def fvalRefName(e: Expression): Option[String] = e match {
    case r: Reference => Some(r.name)
    case _ => None
  }
}
