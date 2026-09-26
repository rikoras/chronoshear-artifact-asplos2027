"""Explain signal-level observations separately from architectural validation."""

ARCHITECTURALLY_VALIDATED_DUTS=frozenset(['rocket','boom-small','boom-medium','boom-large'])

ORACLE_NOTE=(
    'The supplied reference models have passed independent architectural checks '
    'for the packaged workloads. Benign signal-level differences may remain: '
    'a nonzero oracle-mismatch count alone does not imply an architectural error. '
    'Oracle comparisons remain enabled; program and external-boundary errors '
    'are still failures.'
)

def verification_note():
    return 'ORACLE_CHECK_NOTE '+ORACLE_NOTE
