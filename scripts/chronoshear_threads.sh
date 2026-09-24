#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
OUT="${1:-$DIR/../results/threads}"
python3 "$DIR/chronoshear_run.py" --experiment main --select "^boom-large-verilator-1t$" --output "$OUT"
python3 "$DIR/chronoshear_run.py" --experiment threads --output "$OUT"
python3 "$DIR/chronoshear_summarize.py" "$OUT"
python3 "$DIR/chronoshear_plot.py" "$OUT"
