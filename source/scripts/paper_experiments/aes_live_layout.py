#!/usr/bin/env python3
"""Generate exact live writer offsets from the emitted AES oracle contract."""
import argparse
import hashlib
import json
from pathlib import Path


def generate(manifest, width, output, cycles):
    document = json.loads(manifest.read_text())
    entries = {e['traceKey']: e for e in document['oracles']}
    names = [f'state_{i}' for i in range(16)] + ['rounds', 'STM']
    if len(document['oracles']) != 18 or len(entries) != 18 or set(entries) != set(names):
        raise ValueError('AES live model requires the exact 18-register Cipher contract')
    occupied = set()
    for name in names:
        e = entries[name]
        if (e['kind'] != 'reg' or e['elemBytes'] != 1 or not e.get('verified') or
                e['width'] != (2 if name == 'STM' else 4 if name == 'rounds' else 8)):
            raise ValueError(f'Incompatible AES stream {name}')
        region = set(range(e['blockOffset'], e['blockOffset'] + 2 * width))
        if min(region) < 0 or max(region) >= document['blockBytes'] or occupied & region:
            raise ValueError('Overlapping or out-of-range oracle layout')
        occupied |= region
    if document['layout'] not in ('window-major-v4m', 'window-major-v4'):
        raise ValueError('Unsupported window layout')
    output.mkdir(parents=True, exist_ok=True)
    (output / 'oracle_data.h').write_text(
        '#pragma once\n#include <cstdint>\n'
        f'constexpr int ORACLE_NUM_CYCLES = {cycles + 1};\n'
        'inline const char* oracle_kernel_base = nullptr;\n')
    offsets = ','.join(str(entries[n]['blockOffset']) for n in names)
    (output / 'aes_live_layout.h').write_text(
        '#pragma once\n#include <cstddef>\n'
        f'inline constexpr std::size_t aes_offsets[18] = {{{offsets}}};\n'
        f'inline constexpr std::size_t aes_block_bytes = {document["blockBytes"]};\n'
        f'inline constexpr int aes_width = {width};\n'
        f'inline constexpr bool aes_mirrored = {str(document["layout"].endswith("m")).lower()};\n')
    (output / 'layout-source.json').write_text(json.dumps({
        'manifest_sha256': hashlib.sha256(manifest.read_bytes()).hexdigest(),
        'width': width, 'logical_cycles': cycles, 'oracle_count': len(entries),
        'source': 'independent online CipherModel; no trace input'}, indent=2) + '\n')


if __name__ == '__main__':
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--manifest', type=Path, required=True)
    p.add_argument('--width', type=int, choices=[4, 8, 16, 32], required=True)
    p.add_argument('--cycles', type=int, default=100000)
    p.add_argument('--output', type=Path, required=True)
    a = p.parse_args()
    if a.cycles <= 0:
        p.error('cycles must be positive')
    generate(a.manifest, a.width, a.output, a.cycles)
