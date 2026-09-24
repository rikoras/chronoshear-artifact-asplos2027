package essent.simd.v2

import firrtl.ir._

/** =====================================================================
  * CHISA v2 pipeline core types.
  *
  * Mathematical model: the whole SIMD compilation problem is phrased on a
  * single object, the TEMPLATE GRAPH. A template is one scalar statement of
  * the flattened, fully-optimized design (lane is a dimension added only at
  * emission). Edges are typed and carry a lane offset:
  *
  *   - EData  (offset 0): combinational operand dependency within a lane
  *   - EShift (offset +1): register carry, lane k consumes lane k-1's value
  *   - EWar   (offset 0): readers-before-commit (write-after-read order)
  *
  * Properties this pipeline relies on (see docs):
  *   (1) If the RTL has no combinational loop, the per-lane expansion of the
  *       template graph is acyclic for every W (offset-0 subgraph is the
  *       single-cycle DAG; every other edge strictly increases the lane).
  *   (2) A template can be vectorized full-width iff it does NOT belong to a
  *       nontrivial SCC of the template graph (all edge kinds as plain
  *       edges). SCC membership == the true serial cone. There is no cycle
  *       breaker anywhere: SCC members are emitted per-lane, period.
  *
  * v2 keeps ONE register lowering (shift form) for every non-oracle
  * register, including self-referencing ones — their serial nature then
  * shows up as an SCC, honestly. Mux-hold prefix-scan/serial reductions are
  * performance refinements to be reintroduced later ON TOP of this
  * correctness baseline.
  * ===================================================================== */

/** Scheduling role of a template statement. A first-class datatype — role is
  * NEVER encoded in Info strings and never re-discovered by name matching. */
sealed trait Role
/** Plain combinational statement (DefNode / Connect). */
case object RComb extends Role
/** Register source phase: writes reg[k] = value visible DURING cycle k,
  * i.e. reg[k] <- reg$next[k-1] (lane k-1 of the next-value template). */
case class RRegSource(reg: String) extends Role
/** Register commit phase: writes reg[k] = reg$next[k] (end-of-cycle value).
  * Ordered after every reader of the register via EWar edges. Only the
  * window-boundary lane's value survives into the next (reversed) window,
  * but committing all lanes is harmless and simple. */
case class RRegCommit(reg: String) extends Role
/** Oracle injection: produces reg's cycle-k value from the pre-recorded
  * trace. No in-edges (that is the point). */
case class ROracleInject(reg: String) extends Role
/** Runtime cross-check: RTL-computed next value vs the injected oracle of
  * the following lane. */
case class RVerify(reg: String) extends Role
/** Read one compiler-lifted state array.  The statement is a DefNode whose
  * value is mem[addr]; emission forwards writes from chronologically earlier
  * lanes so lane k observes exactly the state at the start of cycle k. */
case class RStateRead(array: String) extends Role
/** End-of-window commit for one compiler-lifted state array.  The statement
  * is the array's single MemWrite and is applied in chronological lane order
  * only after every read port has consumed the pre-window image. */
case class RStateCommit(array: String) extends Role
/** Side-effecting statement (MemWrite / Print / Stop): kept per-lane in lane
  * order via explicit chain edges (conservative but rare). */
case object REffect extends Role

sealed trait EdgeKind { def offset: Int }
/** v@k reads u@k. */
case object EData  extends EdgeKind { val offset = 0 }
/** v@k reads u@{k-1} (register carry). */
case object EShift extends EdgeKind { val offset = 1 }
/** v@k must run after u@k, no data flows (WAR on the physical array). */
case object EWar   extends EdgeKind { val offset = 0 }

/** One template node. `stmt` references only scalar flat names (the single
  * post-optimization namespace); the emitter adds lane subscripts. Cross-lane
  * reads inside a source statement are expressed with `WRef(name + "@prev")`
  * — a structural marker resolved by the v2 renamer, not a parsed pattern. */
case class TemplateNode(
  id: Int,
  stmt: Statement,
  role: Role,
  produces: Option[String]
)

case class TemplateEdge(from: Int, to: Int, kind: EdgeKind)

/** Per-register lowering decided by PlanOracles on the same graph the
  * scheduler uses — a single model, so plan/schedule divergence cannot
  * exist. */
sealed trait RegPlan
/** source = shift of $next, commit = $next. Works for every register,
  * self-referencing or not (the graph decides the schedule consequences). */
case object RPShift extends RegPlan
/** Self-referencing register with extracted (wen, wdata), both self-free:
  * source is the per-lane serial chain r[k] = wen[k-1] ? wdata[k-1] : r[k-1].
  * Only the source template serializes; wen/wdata and all readers stay
  * vectorized. */
case object RPCondHold extends RegPlan
/** Self-referencing register whose update is affine in itself:
  *   next ≡ keep ? (r + add) : add   (mod 2^w)
  * with keep (1 bit) and add (w bits) both self-free — accumulators
  * (systolic MatMul `res := res + a*b`), enabled counters, synchronously
  * cleared sums. Both operands are materialized as the vector templates
  * `r$keep` / `r$add`; the source is a parallel prefix scan over the
  * (keep, add) step-function monoid, so nothing in the cone runs per lane
  * (2026-09-04, replaces the per-lane serial-next chain for this shape). */
case object RPAffineScan extends RegPlan
/** Self-referencing register whose update cannot be split into self-free
  * wen/wdata (counters, read-modify-write CSRs). The self-tainted part of the
  * $next cone is folded into one expression evaluated serially per lane:
  * r[k] = folded(operands@[k-1], r[k-1]). Untainted operands stay vectorized
  * templates; costs |folded|*(W-1) scalar ALU ops and zero oracle streams.
  *
  * guarded: extraction proved next ≡ wen ? wdata : r with a SELF-FREE wen
  * (only wdata reads r — the RMW case). wen is materialized as the vector
  * template `r$gwen`; emission then OR-reduces the window's wen lanes and,
  * when all-zero (CSR-quiet window, the common case), replaces the serial
  * chain with a broadcast of the boundary lane — the degenerate hold-monoid
  * prefix scan. Non-zero windows fall back to the full serial chain. */
case class RPSerialNext(folded: Expression, guarded: Boolean = false) extends RegPlan
/** FVS-selected oracle target: source is replaced by trace injection and a
  * Verify node checks $next against the next lane's injected value. */
case object RPOracle extends RegPlan

/** Everything downstream needs to know about one oracle, produced at the
  * single point of decision, serialized verbatim to oracle_manifest.json. */
case class OracleSpec(
  flatName: String,     // flat signal path, e.g. "tile.core.d.exe_reg_pc"
  traceKey: String,     // exact key in the trace 'micro' section (no guessing)
  arraySymbol: String,  // C++ mmap array symbol in oracle_data.h
  widthBits: Int,
  isRegister: Boolean,  // register oracle => pre-eval capture in gen_trace
  verified: Boolean,
  word: Int = 0,        // wide (>64-bit) register: index of this 64-bit word stream
  words: Int = 1        // number of word streams of the register (1 = not wide)
)
