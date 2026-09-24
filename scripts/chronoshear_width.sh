#!/usr/bin/env bash
set -euo pipefail
DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
OUT="${1:-$DIR/../results/width}"
python3 "$DIR/chronoshear_run.py" --experiment main --select "verilator-1t$" --output "$OUT"
python3 "$DIR/chronoshear_run.py" --experiment width --output "$OUT"
python3 "$DIR/chronoshear_summarize.py" "$OUT"
python3 "$DIR/chronoshear_plot.py" "$OUT"
