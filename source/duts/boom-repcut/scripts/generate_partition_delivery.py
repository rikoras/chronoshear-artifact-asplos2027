#!/usr/bin/env python3
"""Audit actual emitted partition oracle reads against the retained contract.

Accepts the split emitter's restricted address form. Helpers that read oracle
storage or an unrecognized pointer use fail closed. The optional C++ header
authorizes partition-local expansion readiness for bounded injection calls.
Source windows remain complete until all readers and expansion writers finish.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def audit(split, layout_path, executable=False):
    manifest = json.loads((split / 'kernel-units.json').read_text())
    layout = json.loads(layout_path.read_text())
    lanes = layout['oracles']
    by_offset = {row['blockOffset']: row for row in lanes}
    if len(by_offset) != len(lanes):
        raise ValueError('ambiguous oracle block offsets')
    reads, sources = {}, {}
    address = re.compile(r'\boracle_win_base\s*\+\s*(\d+)L?\b')
    injection = re.compile(r'\bessent_inject_(?:word_)?(fwd|rev)<(\d+)(?:,\s*\d+)?>\('
                           r'[^;]*?,\s*\(\(const uint(8|16|32|64)_t\*\)\('
                           r'oracle_win_base \+ (\d+)L?\)')
    widths = set()
    header = split / 'TestHarness.h'
    if sha(header) != manifest['header_sha256']:
        raise ValueError('kernel header changed since split')
    for line in header.read_text().splitlines():
        if 'oracle_win_base' in line and not re.fullmatch(r'\s*const char\* oracle_win_base = nullptr;\s*', line):
            raise ValueError('oracle use outside split partition methods: ' + line[:240])
    for unit in manifest['translation_units']:
        path = split / unit['file']
        digest = sha(path)
        if digest != unit['sha256']:
            raise ValueError('kernel unit changed since split: ' + str(path))
        sources[unit['file']] = digest
        match = re.fullmatch(r'kernel_p(\d+)_(forward|reverse)\.cpp', unit['file'])
        offsets = set()
        for line in path.read_text().splitlines():
            if 'oracle_win_base' not in line:
                continue
            if match is None:
                raise ValueError('oracle read in shared helper needs a call-sensitive audit: ' + str(path))
            # Remove just the emitted cursor update. Other uses on the same
            # line must still be recognized as retained oracle addresses.
            line = line.replace('oracle_win_base += ORACLE_BLOCK_BYTES;', '')
            found = address.findall(line)
            if len(found) != len(re.findall(r'\boracle_win_base\b', line)):
                raise ValueError('unsupported oracle pointer expression: ' + line[:240])
            if executable and found:
                call = injection.search(line)
                if len(found) != 1 or call is None or call[4] != found[0]:
                    raise ValueError('partial delivery requires a bounded emitted injection: ' + line[:240])
                if call[1] != {'forward':'fwd','reverse':'rev'}[match[2]]:
                    raise ValueError('injection direction differs from partition method')
                lane = by_offset.get(int(call[4]))
                if lane is None or int(call[3]) != 8 * lane['elemBytes']:
                    raise ValueError('injection element size differs from retained lane')
                widths.add(int(call[2]))
            offsets.update(map(int, found))
        unknown = offsets - by_offset.keys()
        if unknown:
            raise ValueError('oracle address missing from actual contract: ' + str(sorted(unknown)))
        if match:
            reads[int(match[1]), match[2]] = offsets
    count = len(reads) // 2
    if set(reads) != {(p,d) for p in range(count) for d in ('forward','reverse')} or not count:
        raise ValueError('missing or noncontiguous partition methods')
    partitions = []
    masks = {offset: 0 for offset in by_offset}
    for p in range(count):
        forward, reverse = reads[p, 'forward'], reads[p, 'reverse']
        if forward != reverse:
            raise ValueError('forward/reverse oracle read coverage differs: ' + str(p))
        partitions.append({'partition': p, 'streams': len(forward), 'block_offsets': sorted(forward)})
        for offset in forward:
            masks[offset] |= 1 << p
    missing = [offset for offset, mask in masks.items() if not mask]
    if missing:
        raise ValueError('retained fields not covered by partition reads: ' + str(missing[:16]))
    if executable and (len(widths) != 1 or next(iter(widths)) not in (4,8,16,32)):
        raise ValueError('inconsistent or unsupported injection width')
    if executable:
        width = next(iter(widths))
        intervals = sorted((row['blockOffset'], row['blockOffset'] + 2*width*row['elemBytes']) for row in lanes)
        if any(a[1] > b[0] for a,b in zip(intervals,intervals[1:])):
            raise ValueError('overlapping expanded oracle lanes')
    result = {'schema': 1, 'basis': 'literal reads in emitted forward/reverse methods; shared helpers contain no oracle pointer',
              'runtime_readiness': ('partition expansion; complete source window' if executable else
                                    'complete-window; this audit does not authorize partial owner publication'),
              'executable': executable, 'width': next(iter(widths)) if executable else None,
              'layout_sha256': sha(layout_path), 'split_manifest_sha256': sha(split / 'kernel-units.json'),
              'units': sources, 'partitions': partitions,
              'reader_histogram': {str(n): sum(mask.bit_count() == n for mask in masks.values())
                                   for n in range(1, count + 1)},
              'lanes': [{'lane': row['lane'], 'record_offset': row['recordOffset'],
                         'block_offset': row['blockOffset'], 'bytes': row['elemBytes'],
                         'kind': row['kind'], 'readers': masks[row['blockOffset']]}
                        for row in lanes]}
    return result


def write_header(report, path):
    if not report['executable']:
        raise ValueError('C++ delivery requires bounded injection audit')
    lanes = sorted(report['lanes'], key=lambda row: row['lane'])
    if [row['lane'] for row in lanes] != list(range(len(lanes))):
        raise ValueError('noncontiguous modeled lane indices')
    text = ('#pragma once\n#include <array>\n#include <cstdint>\n'
            'namespace chisa::boom_repcut::delivery {\n'
            f'inline constexpr unsigned partitions = {len(report["partitions"])};\n'
            f'inline constexpr unsigned width = {report["width"]};\n')
    for name, field, kind in [('readers','readers','std::uint64_t'),('offsets','block_offset','std::uint32_t')]:
        text += f'inline constexpr std::array<{kind}, {len(lanes)}> {name} = {{\n'
        for start in range(0,len(lanes),16):
            text += '  '+', '.join(str(row[field]) for row in lanes[start:start+16])+',\n'
        text += '};\n'
    text += '}\n'
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--split', type=Path, required=True)
    parser.add_argument('--layout', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--header', action='store_true', help='also emit the bounded partition delivery contract')
    args = parser.parse_args()
    report = audit(args.split, args.layout, executable=args.header)
    args.out.mkdir(parents=True, exist_ok=True)
    (args.out/'partition-delivery.json').write_text(json.dumps(report, indent=2)+'\n')
    if args.header:
        write_header(report,args.out/'partition_delivery.inc')
    print(json.dumps({'partitions': [dict(partition=p['partition'], streams=p['streams']) for p in report['partitions']],
                      'reader_histogram': report['reader_histogram']}))


if __name__ == '__main__':
    main()
