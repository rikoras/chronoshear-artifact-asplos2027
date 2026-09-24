package essent.simd.v2

import firrtl.ir._
import scala.collection.mutable

/** Replace the two complete cache-side modules, retaining their exact ports.
  * The PTW, HellaCacheArbiter and TileLink fabric stay in the cold circuit.
  * Unlike the FPU specialization, no inactive/unobserved port is removed.
  */
object RocketMemorySpecialization {
  val QualifiedFirrtlSha256 = RocketFpuSpecialization.QualifiedFirrtlSha256
  val Policy = "defaultconfig-native-frontend-dcache"
  val TilePath = "ldut.tile_prci_domain.tile_reset_domain.tile"
  val Definitions = Seq(
    ("Frontend", "frontend", "CHISARocketFrontendModel"),
    ("DCache", "dcache", "CHISARocketDCacheModel"))

  case class PortLeaf(path: String, flow: String, `type`: String, width: BigInt, clock: Boolean)
  case class Boundary(module: String, instance: String, hotDefname: String,
      groundSeamPorts: Int, ports: Seq[PortLeaf])
  case class Contract(schemaVersion: Int, sourceFirrtlSha256: String,
      policy: String, replacementEnabled: Boolean, modules: Seq[Boundary])
  case class Specialized(circuit: Circuit, boundaries: Seq[Boundary])

  /** `gated_clock` is an alias of the common tile clock in DefaultConfig.
    * The clock_enabled outputs still have ordinary data/arbiter uses; they
    * must not be interpreted as enables for the model's entire commit.
    */
  private[v2] def requireCommonTileClock(circuit: Circuit): Unit = {
    val byName = circuit.modules.map(m => m.name -> m).toMap
    val tile = byName.get("RocketTile") match {
      case Some(m: Module) => m
      case _ => throw new IllegalArgumentException("memory clock proof requires RocketTile")
    }
    require(tile.ports.exists(p => p.name == "clock" && p.direction == Input && p.tpe == ClockType),
      "memory clock proof requires the common RocketTile clock input")
    for ((_, instance, _) <- Definitions) {
      val drivers = mutable.ArrayBuffer[(String, Boolean)]()
      def walk(s: Statement, conditional: Boolean): Unit = s match {
        case c: Connect if c.loc.serialize == s"$instance.gated_clock" =>
          drivers += c.expr.serialize -> conditional
        case c: Conditionally => walk(c.conseq, true); walk(c.alt, true)
        case other => other.foreachStmt(child => walk(child, conditional))
      }
      walk(tile.body, false)
      require(drivers.toSeq == Seq("clock" -> false),
        s"$instance.gated_clock is not the unconditional common tile clock: ${drivers.mkString(", ")}")
    }
    val visited = mutable.Set[String]()
    def visit(name: String): Unit = if (visited.add(name)) {
      byName(name) match {
        case em: ExtModule =>
          require(em.defname != "EICG_wrapper", s"native memory subtree contains a clock gate: $name")
        case m: Module =>
          def expr(e: Expression): Unit = {
            require(!(e.isInstanceOf[DoPrim] && e.asInstanceOf[DoPrim].op == firrtl.PrimOps.AsClock),
              s"native memory subtree contains a derived clock: $name")
            e.foreachExpr(expr)
          }
          def stmt(s: Statement): Unit = {
            s.foreachExpr(expr)
            s match { case i: DefInstance => visit(i.module); case _ => }
            s.foreachStmt(stmt)
          }
          stmt(m.body)
      }
    }
    Definitions.foreach(d => visit(d._1))
  }

  private[v2] def leaves(ports: Seq[Port]): Seq[PortLeaf] = {
    val result = mutable.ArrayBuffer[PortLeaf]()
    def visit(path: String, direction: Direction, tpe: Type): Unit = tpe match {
      case BundleType(fields) => fields.foreach { field =>
        val childDirection = if (field.flip == Default) direction
          else if (direction == Input) Output else Input
        visit(s"$path.${field.name}", childDirection, field.tpe)
      }
      case VectorType(element, size) =>
        (0 until size).foreach(i => visit(s"$path[$i]", direction, element))
      case ground =>
        val width = ground match {
          case ClockType | ResetType | AsyncResetType => BigInt(1)
          case UIntType(IntWidth(w)) => w
          case SIntType(IntWidth(w)) => w
          case other => throw new IllegalArgumentException(s"non-ground memory seam: ${other.serialize}")
        }
        result += PortLeaf(path, if (direction == Input) "cold-to-hot" else "hot-to-cold",
          ground.serialize, width, ground == ClockType)
    }
    ports.foreach(p => visit(p.name, p.direction, p.tpe))
    require(result.map(_.path).distinct.size == result.size, "duplicate memory seam leaf")
    result.toSeq
  }

  def specialize(circuit: Circuit): Specialized = {
    requireCommonTileClock(circuit)
    val byName = circuit.modules.map(m => m.name -> m).toMap
    val instances = mutable.ArrayBuffer[(String, String)]()
    val reachable = mutable.Set[String]()
    def visit(name: String, path: String, ancestors: Set[String]): Unit = {
      require(!ancestors(name), s"recursive hierarchy in memory cut: $name")
      reachable += name
      byName(name) match {
        case m: Module =>
          def walk(s: Statement): Unit = s match {
            case i: DefInstance =>
              val child = if (path.isEmpty) i.name else s"$path.${i.name}"
              instances += child -> i.module
              visit(i.module, child, ancestors + name)
            case other => other.foreachStmt(walk)
          }
          walk(m.body)
        case _: ExtModule =>
      }
    }
    visit(circuit.main, "", Set.empty)
    val boundaries = Definitions.map { case (name, instance, defname) =>
      val owners = instances.filter(_._2 == name).map(_._1).toSeq
      require(owners == Seq(s"$TilePath.$instance"),
        s"memory replacement requires unique $TilePath.$instance, found ${owners.mkString(", ")}")
      val module = byName(name) match {
        case m: Module => m
        case _ => throw new IllegalArgumentException(s"memory replacement requires concrete $name")
      }
      val ports = leaves(module.ports)
      require(ports.count(_.clock) == 1 && ports.find(_.clock).get.path == "gated_clock",
        s"$name common-edge clock interface drift")
      Boundary(name, owners.head, defname, ports.size, ports)
    }
    val replacements = boundaries.map { b =>
      val m = byName(b.module)
      b.module -> ExtModule(m.info, m.name, m.ports, b.hotDefname, Seq.empty)
    }.toMap
    val replaced = byName ++ replacements
    reachable.clear()
    def retain(name: String): Unit = if (reachable.add(name)) {
      replaced(name) match {
        case m: Module =>
          def walk(s: Statement): Unit = s match {
            case i: DefInstance => retain(i.module)
            case other => other.foreachStmt(walk)
          }
          walk(m.body)
        case _: ExtModule =>
      }
    }
    retain(circuit.main)
    require(reachable("PTW"), "memory replacement must retain the real PTW")
    Specialized(circuit.copy(modules = circuit.modules.filter(m => reachable(m.name))
      .map(m => replaced(m.name))), boundaries)
  }
}
