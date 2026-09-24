#!/usr/bin/env bash
set -euo pipefail
if (( $# )); then
  printf 'Usage: bash scripts/chronoshear_clean_results.sh\n' >&2
  exit 2
fi
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
rm -rf -- "$ROOT/results"
mkdir -p -- "$ROOT/results"
printf 'Cleaned %s/results/\n' "$ROOT"
