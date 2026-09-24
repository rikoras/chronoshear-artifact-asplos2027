#!/usr/bin/env python3
"""Count distinct mismatching RTL signals while retaining every event comparison."""
from pathlib import Path
import argparse
import re


LOG = re.compile(r'ORACLE MISMATCH (?:reg|comb)=([^ ]+)')
COUNT = re.compile(r'(?m)^(?P<indent>[ \t]*)_count \+= (?P<expr>\(uint64_t\)\(!\((?P<equality>[^\n]+)\)\));$')
CASE = re.compile(r'(?m)^[ \t]*case \d+: \{\n(?:(?!^[ \t]*case |^[ \t]*default:)[\s\S])*?^[ \t]*return _count;\n[ \t]*\}', re.M)
MARKER = '// CHRONOSHEAR_DISTINCT_ORACLE_SIGNALS'


def normalize(expression):
    return re.sub(r'\s+', '', expression.replace('_v2_other', '_other'))


def add_signal_counts(sources):
    """Transform one monolithic header or a header and all its split kernel units."""
    if any(MARKER in text for text in sources.values()):
        raise ValueError('Distinct-signal accounting is already present')
    equality_names, names, cold_sites = {}, set(), 0
    for text in sources.values():
        lines = text.splitlines()
        for index, line in enumerate(lines):
            match = LOG.search(line)
            if match is None:
                continue
            name = match[1]
            names.add(name)
            cold_sites += 1
            if index == 0 or index + 1 >= len(lines) or lines[index + 1].strip() != 'record_oracle_mismatch();':
                raise ValueError('Unrecognized oracle report/action pair: ' + name)
            guard = lines[index - 1].strip()
            predicate = re.search(r'!\((.*)\)', guard)
            if predicate is None and '[window-boundary]' in line and ' != ' in guard and guard.startswith('if ('):
                continue
            if predicate is None or not guard.startswith('if ('):
                raise ValueError('Unrecognized oracle comparison guard: ' + name)
            # Strip only closing parentheses beyond the equality's own balance.
            equality = predicate[1]
            while equality.count(')') > equality.count('('):
                if not equality.endswith(')'):
                    raise ValueError('Unbalanced oracle comparison: ' + name)
                equality = equality[:-1]
            key = normalize(equality)
            if key in equality_names and equality_names[key] != name:
                raise ValueError('One comparison maps to different oracle signals')
            equality_names[key] = name
    if not names:
        raise ValueError('No oracle comparisons found')
    names = sorted(names)
    signal_ids = {name: index for index, name in enumerate(names)}
    groups, first_slot, count_sites = [], {}, 0
    result = {}
    for path, text in sources.items():
        def group(match):
            nonlocal count_sites
            body = match[0]
            predicates = list(COUNT.finditer(body))
            if not predicates:
                return body
            if len(predicates) > 64 or body.count('uint64_t _count = 0;') != 1:
                raise ValueError('Unsupported exact-count group')
            ids = []
            slot = len(groups)
            for bit, predicate in enumerate(predicates):
                name = equality_names.get(normalize(predicate['equality']))
                if name is None:
                    raise ValueError('Exact predicate has no original report identity: ' + predicate['equality'][:180])
                ids.append(signal_ids[name])
                first_slot.setdefault(name, (slot, bit))
            groups.append(ids)
            count_sites += len(ids)
            cursor = iter(range(len(ids)))
            def record(predicate):
                bit = next(cursor)
                indent, expression = predicate['indent'], predicate['expr']
                return (f'{indent}const uint64_t _chronoshear_mismatch_{bit} = {expression};\n'
                        f'{indent}_count += _chronoshear_mismatch_{bit};\n'
                        f'{indent}_chronoshear_signals |= _chronoshear_mismatch_{bit} << {bit};')
            body = COUNT.sub(record, body)
            body = body.replace('uint64_t _count = 0;', 'uint64_t _count = 0;\n        uint64_t _chronoshear_signals = 0;')
            body = body.replace('return _count;', f'_chronoshear_mark_oracle_mask({slot}, _chronoshear_signals);\n        return _count;')
            return body
        signature = re.search(r'uint64_t _v2_verify_count\([^;\n]*\) const \{', text)
        if signature:
            depth, end = 1, signature.end()
            for brace in re.finditer(r'[{}]', text[end:]):
                depth += 1 if brace[0] == '{' else -1
                if depth == 0:
                    end += brace.end()
                    break
            if depth:
                raise ValueError('Unterminated exact-count helper')
            body = CASE.sub(group, text[signature.start():end])
            rewritten = text[:signature.start()] + body + text[end:]
        else:
            rewritten = text
        if COUNT.search(rewritten):
            raise ValueError('Exact-count predicate was outside a recognized group')
        result[path] = rewritten
    # A cold-only signal still gets a slot, including checks emitted without the
    # optional count-only helper. Repeated boundary/direction checks share it.
    for name in names:
        if name not in first_slot:
            if not groups or len(groups[-1]) == 64:
                groups.append([])
            first_slot[name] = (len(groups) - 1, len(groups[-1]))
            groups[-1].append(signal_ids[name])
    marked_sites = 0
    for path, text in result.items():
        lines = text.splitlines(keepends=True)
        for index, line in enumerate(lines):
            match = LOG.search(line)
            if match is not None:
                slot, bit = first_slot[match[1]]
                indent = re.match(r'\s*', lines[index + 1])[0]
                lines[index + 1] = (f'{indent}_chronoshear_mark_oracle_mask({slot}, UINT64_C(1) << {bit});\n'
                                    + lines[index + 1])
                marked_sites += 1
        result[path] = ''.join(lines)
    if marked_sites != cold_sites:
        raise ValueError('Incomplete oracle-report coverage')
    words = (len(names) + 63) // 64
    offsets, flat = [0], []
    for ids in groups:
        flat.extend(ids)
        offsets.append(len(flat))
    members = f'''
  {MARKER}
  mutable uint64_t _chronoshear_oracle_seen[{len(groups)}]{{}};
  static constexpr unsigned oracle_checked_signal_count() {{ return {len(names)}; }}
  static constexpr unsigned oracle_mismatch_signal_words() {{ return {words}; }}
  void _chronoshear_mark_oracle_mask(unsigned group, uint64_t mask) const {{
    if (mask && (__atomic_load_n(&_chronoshear_oracle_seen[group], __ATOMIC_RELAXED) & mask) != mask)
      __atomic_fetch_or(&_chronoshear_oracle_seen[group], mask, __ATOMIC_RELAXED);
  }}
  void oracle_mismatch_signal_union(uint64_t* signals) const {{
    static constexpr unsigned offsets[] = {{{','.join(map(str, offsets))}}};
    static constexpr unsigned short identities[] = {{{','.join(map(str, flat))}}};
    for (unsigned group = 0; group < {len(groups)}; ++group) {{
      uint64_t mask = __atomic_load_n(&_chronoshear_oracle_seen[group], __ATOMIC_RELAXED);
      while (mask) {{
        const unsigned bit = __builtin_ctzll(mask);
        const unsigned id = identities[offsets[group] + bit];
        signals[id / 64] |= UINT64_C(1) << (id % 64);
        mask &= mask - 1;
      }}
    }}
  }}
  uint64_t oracle_mismatch_signal_count() const {{
    uint64_t signals[{words}]{{}}, count = 0;
    oracle_mismatch_signal_union(signals);
    for (uint64_t bits : signals) count += __builtin_popcountll(bits);
    return count;
  }}
'''
    declaration = '  uint64_t verify_mismatches = 0;'
    headers = [path for path, text in result.items() if declaration in text]
    if len(headers) != 1 or result[headers[0]].count(declaration) != 1:
        raise ValueError('Missing unique generated top counter')
    result[headers[0]] = result[headers[0]].replace(declaration, declaration + members)
    return result, {'signals': len(names), 'groups': len(groups), 'exact_predicates': count_sites,
                    'cold_predicates': cold_sites, 'state_bytes': 8 * len(groups)}


def prepare(header, kernels=()):
    paths = [Path(header), *map(Path, kernels)]
    updated, report = add_signal_counts({p: p.read_text() for p in paths})
    for path, text in updated.items():
        path.write_text(text)
    return report


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('header', type=Path)
    parser.add_argument('--split', action='store_true')
    args = parser.parse_args()
    kernels = sorted(args.header.parent.glob('kernel_*.cpp')) if args.split else ()
    print(prepare(args.header, kernels))
