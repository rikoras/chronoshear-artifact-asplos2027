#!/usr/bin/env bash
set -uo pipefail
DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
OUT="${1:-$DIR/../results/main}"
status=0
for dut in aes matmul sodor rocket boom_small boom_medium boom_large; do
  bash "$DIR/chronoshear_$dut.sh" --output "$OUT" || status=1
done
python3 "$DIR/chronoshear_summarize.py" "$OUT" || status=1
python3 "$DIR/chronoshear_plot.py" "$OUT" || status=1
exit "$status"
