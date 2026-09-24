package essent

import essent.Extract._
import essent.simd.VecStmtInfo

import firrtl.ir._

import collection.mutable.HashMap

trait SigDecType
case object ExtIO extends SigDecType
case object RegSet extends SigDecType
case object Local extends SigDecType
case object MuxOut extends SigDecType
case object PartOut extends SigDecType
case object PartCache extends SigDecType
case object Probe extends SigDecType

case class SigMeta(decType: SigDecType, sigType: firrtl.ir.Type)

class Renamer {
  val nameToEmitName = HashMap[String,String]()
  val nameToMeta = HashMap[String,SigMeta]()
  val nameToSimdInfo = HashMap[String, (String, Int)]()

  var vectorWidth: Int = 1

  // The SOLE source of truth for SIMD lane info — built from LaneTags at emission time
  var flatVecMeta: HashMap[String, VecStmtInfo] = HashMap.empty
  var flatScalarPath: HashMap[String, String] = HashMap.empty

  private val KnownSuffixes = essent.simd.SIMDConstants.KnownSuffixes

  private def stripKnownSuffix(name: String): (String, String) = {
    KnownSuffixes.find(s => name.endsWith(s)) match {
      case Some(suf) => (name.dropRight(suf.length), suf)
      case None => (name, "")
    }
  }

  def populateFromSG(sg: StatementGraph, extIOMap: Map[String,Type]): Unit = {
    val stateNames = sg.stateElemNames().toSet
    sg.nodeRange() foreach { id =>
      val name = sg.idToName(id)
      val decType = if (stateNames.contains(name))        RegSet
                    else if (extIOMap.contains(name))     ExtIO
                    else                                  Local
      val sigType = if (extIOMap.contains(name)) extIOMap(name)
                    else try findResultType(sg.idToStmt(id))
                         catch { case e: Exception =>
                           throw new Exception(s"findResultType failed for stmt #$id '$name': ${sg.idToStmt(id).serialize}", e)
                         }
      nameToEmitName(name) = name
      nameToMeta(name) = SigMeta(decType, sigType)
    }
    val unusedExtSigs = extIOMap.keys.toSet -- sg.nameToID.keys
    unusedExtSigs foreach { name =>
      nameToEmitName(name) = name
      nameToMeta(name) = SigMeta(ExtIO, extIOMap(name))
    }
    fixEmitNames()
    if (vectorWidth > 1) fixSimdNames()
  }

  def fixEmitNames(): Unit = {
    def shouldBeLocal(meta: SigMeta) = meta.decType match {
      case Local | MuxOut | PartOut => true
      case _ => false
    }
    val namesToLocalize = nameToMeta collect {
      case (name, meta) if shouldBeLocal(meta) => name
    }
    namesToLocalize foreach { name =>
      nameToEmitName(name) = removeDots(nameToEmitName(name))
    }
  }

  def fixSimdNames(): Unit = {
    nameToEmitName.keys.toSeq.foreach { canonicalName =>
      val (baseName, suffix) = stripKnownSuffix(canonicalName)
      flatVecMeta.get(baseName) match {
        case Some(info) if info.laneIndex < vectorWidth =>
          // flatScalarPath gives us the full flattened scalar path directly — no string manipulation
          val scalarPath = flatScalarPath.getOrElse(baseName, baseName)
          val isLocal = nameToMeta.get(canonicalName).exists(m =>
            m.decType == Local || m.decType == MuxOut || m.decType == PartOut)
          val emitPath = if (isLocal) removeDots(scalarPath) else scalarPath
          val emitSuffix = if (isLocal) removeDots(suffix) else suffix
          val arrayBase = if (isLocal) s"_s_$emitPath$emitSuffix" else s"$emitPath$emitSuffix"
          if (!isLocal) structMemberBases += arrayBase
          nameToSimdInfo(canonicalName) = (arrayBase, info.laneIndex)
        case _ =>
      }
    }
  }

  def mutateDecTypeIfLocal(name: String, newDecType: SigDecType): Unit = {
    val currentMeta = nameToMeta(name)
    if (currentMeta.decType == Local)
      nameToMeta(name) = currentMeta.copy(decType = newDecType)
  }

  def addPartCache(name: String, sigType: firrtl.ir.Type): Unit = {
    nameToEmitName(name) = removeDots(name)
    nameToMeta(name) = SigMeta(PartCache, sigType)
  }

  def doNotDecLocal() = {
    val notLocalSigs = nameToMeta collect {
      case (name, SigMeta(decType, sigType)) if decType != Local => name
    }
    notLocalSigs.toSet
  }

  def removeDots(s: String) = s.replace('.','$')

  def decLocal(name: String) = {
    if (nameToSimdInfo.contains(name)) false
    else if (preDeclaredLocals.contains(name)) false
    else nameToMeta(name).decType == Local
  }

  private var simdBaseOverrides: Map[String, String] = Map.empty
  private var scalarLaneBindings: Map[String, String] = Map.empty
  private var endpointLanes: Set[String] = Set.empty

  /** A temporary whose users are in this lane loop needs one local value,
    * even when the logical graph has several uses of it. */
  def withScalarLaneBindings[T](bindings: Map[String, String])(body: => T): T = {
    val saved = scalarLaneBindings
    scalarLaneBindings = saved ++ bindings
    try body finally scalarLaneBindings = saved
  }

  /** Commit-only next-state values retain the two possible sweep endpoints. */
  def setEndpointLanes(names: Set[String]): Unit = endpointLanes = names
  def simdStorageLanes(name: String): Int = if (endpointLanes(name)) 2 else vectorWidth
  private def storageLane(name: String, lane: String): String =
    if (!endpointLanes(name)) lane
    else if (lane == "0") "0"
    else if (lane == (vectorWidth - 1).toString) "1"
    else s"(($lane) == 0 ? 0 : 1)"

  private def resolvedSimdInfo(name: String): Option[(String, Int)] =
    nameToSimdInfo.get(name).map { case (base, lane) =>
      (simdBaseOverrides.getOrElse(name, base), lane)
    }

  /** Override only the emitted array base while preserving canonical signal
    * metadata and lane indices. Used by v2 scratch-slot allocation after its
    * dry emission has proved that logical temporary lifetimes do not overlap. */
  def setSimdBaseOverrides(overrides: Map[String, String]): Unit =
    simdBaseOverrides = overrides

  def clearSimdBaseOverrides(): Unit = simdBaseOverrides = Map.empty

  def isSimd(name: String): Boolean = nameToSimdInfo.contains(name)
  def simdBase(name: String): Option[String] = resolvedSimdInfo(name).map(_._1)
  def simdLane(name: String): Option[Int] = nameToSimdInfo.get(name).map(_._2)

  def emit(canonicalName: String): String = scalarLaneBindings.getOrElse(canonicalName,
    resolvedSimdInfo(canonicalName) match {
      case Some((base, idx)) => s"$base[${storageLane(canonicalName, idx.toString)}]"
      case None => nameToEmitName(canonicalName)
    })

  def emitForLane(canonicalName: String, laneVar: String): String = scalarLaneBindings.getOrElse(canonicalName,
    resolvedSimdInfo(canonicalName) match {
      case Some((base, _)) => s"$base[${storageLane(canonicalName, laneVar)}]"
      case None => nameToEmitName(canonicalName)
    })

  private val declaredSimdArrays = collection.mutable.Set[String]()
  private val preDeclaredLocals = collection.mutable.Set[String]()
  private val structMemberBases = collection.mutable.Set[String]()

  def addStructMemberBase(base: String): Unit = structMemberBases += base

  def simdArrayDecl(name: String, typeStr: String): Option[String] = {
    resolvedSimdInfo(name).flatMap { case (base, _) =>
      if (!declaredSimdArrays.contains(base)) {
        declaredSimdArrays += base
        if (structMemberBases.contains(base)) None
        // alignas(64): lane arrays are accessed as whole zmm vectors; without
        // it every 64B access may straddle a cache line (v1 emitted this too).
        else Some(s"alignas(64) $typeStr $base[${simdStorageLanes(name)}];")
      } else None
    }
  }

  def preDeclareLocal(name: String): Unit = preDeclaredLocals += name
  def isPreDeclared(name: String): Boolean = preDeclaredLocals.contains(name)
  def isSimdLane(name: String): Boolean = nameToSimdInfo.contains(name)

  def resetDeclaredArrays(): Unit = {
    declaredSimdArrays.clear()
    preDeclaredLocals.clear()
  }

  def vcdOldValue(sig_name: String) = sig_name + "_old"
}
