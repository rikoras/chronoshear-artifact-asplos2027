"""Replace the report-only precheck/rescan pair with one exact comparison pass.

Only pure XOR/OR reduction prefixes are bypassed. Original strict/logging paths,
comparison predicates, and following boundary-carry assignments remain intact.
Unsupported source shapes fail closed instead of dropping any generated work.
Recent mismatch hints keep clean groups on the cheaper Boolean precheck. Both
paths still compare every field; hints never substitute a previous result.
"""
import hashlib
import re


TOKENS = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
GATE = re.compile(r'if \(done_reset && checks_enabled && update_registers\)\s*\{')
CALL = re.compile(r'if \(UNLIKELY\([^\n]*\b_v2_vacc\w*[^\n]*\)\)\s*'
                  r'_v2_verify_rescan\((\d+), (true|false), (\d+), (\d+)\);')
BRACES = re.compile(r'[{}]')


def mask(text):
    return TOKENS.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)


def block_end(plain, begin):
    depth = 1
    for m in BRACES.finditer(plain, begin):
        depth += 1 if m[0] == '{' else -1
        if depth == 0:
            return m.start()
    raise ValueError('unterminated oracle verification block')


def check_reduction(prefix):
    """The removed prefix may write only its local accumulator/loop variables."""
    if not re.search(r'uint(?:8|16|32|64)_t _v2_vacc\w* = 0;', prefix):
        raise ValueError('verification prefix has no recognized reduction')
    for line in prefix.splitlines():
        line = line.strip()
        if not line or line in ('{', '}', 'ESSENT_LANE_LOOP', 'ESSENT_TAIL_LOOP'):
            continue
        if re.fullmatch(r'uint(?:8|16|32|64)_t _v2_vacc\w* = 0;', line):
            continue
        if re.fullmatch(r'for \(int L = \d+; L < \d+; L\+\+\) \{', line):
            continue
        if re.fullmatch(r'_v2_vacc\w* (?:\|=|=) .+;', line):
            rhs = line.split('=', 1)[1]
            if re.search(r'\+\+|--|(?<![=!<>])=(?!=)', rhs):
                raise ValueError('side effect inside verification reduction')
            calls = re.findall(r'\b([A-Za-z_]\w*)\s*\(', rhs)
            if set(calls) - {'essent_raw', 'essent_to_u64', 'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t'}:
                raise ValueError('unrecognized function in verification reduction')
            continue
        raise ValueError('non-reduction work in verification prefix: ' + line[:160])


def rewrite_direct_count(text, adaptive=True):
    if '// CHISA_DIRECT_EXACT_COUNT' in text:
        raise ValueError('direct-count preparation requires an unmodified header')
    plain = mask(text)
    modern = bool(re.search(r'uint64_t\s+_v2_verify_count\(', plain))
    exact = bool(re.search(r'void\s+_v2_verify_exact_count\(', plain))
    if not modern and not exact:
        raise ValueError('direct count requires an existing exact-count implementation')
    fatal = ('oracle_mismatches_fatal' if re.search(r'\bbool\s+oracle_mismatches_fatal\b', plain)
             else 'oracle_mismatch_fatal')
    if not re.search(r'\bbool\s+' + fatal + r'\b', plain):
        raise ValueError('unrecognized oracle failure policy')
    # The legacy helper mutates the count. Bound the entire possible increment
    # before calling it; overflow keeps the original precheck/rescan path.
    capacity = plain.count('++_chisa_exact_mismatches;') if not modern else 0
    if not modern and not capacity:
        raise ValueError('legacy exact-count capacity is unavailable')
    edits, sites = [], []
    for gate in GATE.finditer(plain):
        begin = gate.end()
        end = block_end(plain, begin)
        calls = list(CALL.finditer(plain, begin, end))
        if not calls:
            continue
        if len(calls) != 1:
            raise ValueError('multiple oracle rescan calls in one verification block')
        call = calls[0]
        check_reduction(plain[begin:call.start()])
        condition = call[0].split('_v2_verify_rescan', 1)[0].strip()
        terms = re.findall(r'\(uint64_t\)(_v2_vacc(?:8|16|32|64))\b', condition)
        expected = 'if (UNLIKELY((' + ' | '.join('(uint64_t)' + term for term in terms) + ') != 0))'
        if not terms or re.sub(r'\s+', '', condition) != re.sub(r'\s+', '', expected):
            raise ValueError('unrecognized verification reduction decision')
        group, direction, lo, hi = call.groups()
        if int(hi) < int(lo):
            raise ValueError('reversed exact-count lane bounds')
        args = ', '.join((group, direction, lo, hi))
        condition = f'!{fatal} && verify_mismatches >= oracle_mismatch_log_limit'
        hint = '_chisa_direct_count_history()[' + str(2*int(group)+(direction=='true')) + ']'
        if adaptive: condition += ' && ' + hint
        if modern:
            enabled = '#if ESSENT_VERIFY_COUNT_ONLY\n'
            direct = (f'        const uint64_t _chisa_count = _v2_verify_count({args});\n'
                      '        if (_chisa_count <= UINT64_MAX - verify_mismatches)\n'
                      '          verify_mismatches += _chisa_count;\n'
                      f'        else _v2_verify_rescan({args});\n')
            if adaptive: direct += f'        {hint} = _chisa_count != 0;\n'
        else:
            enabled = ''
            condition += f' && verify_mismatches <= UINT64_MAX - UINT64_C({capacity * (int(hi)-int(lo))})'
            direct = f'        _v2_verify_exact_count({args});\n'
            if adaptive:
                direct = '        const uint64_t _chisa_before = verify_mismatches;\n' + direct
                direct += f'        {hint} = verify_mismatches != _chisa_before;\n'
        # The original reduction and conditional rescan are kept verbatim in
        # the fallback. Everything after the call, especially bcarry updates,
        # stays outside the choice and executes exactly where it did before.
        original = text[begin:call.end()]
        fallback = original
        if adaptive:
            fallback = ('\n' + enabled + '        const uint64_t _chisa_before = verify_mismatches;\n' +
                        ('#endif\n' if modern else '') + original + '\n' + enabled +
                        f'        {hint} = !{fatal} && verify_mismatches >= oracle_mismatch_log_limit &&\n'
                        '          verify_mismatches != _chisa_before;\n' + ('#endif\n' if modern else ''))
        replacement = ('\n      // CHISA_DIRECT_EXACT_COUNT\n' + enabled +
                       f'      if ({condition}) {{\n' + direct +
                       '      } else\n' + ('#endif\n' if modern else '') +
                       '      {' + fallback + '\n      }')
        edits.append((begin, call.end(), replacement))
        sites.append({'group': int(group), 'forward': direction == 'true', 'lo': int(lo), 'hi': int(hi),
                      'original_prefix_sha256': hashlib.sha256(original.encode()).hexdigest(),
                      'following_block_sha256': hashlib.sha256(text[call.end():end].encode()).hexdigest()})
    # A partial rewrite could silently leave a new generated source shape on
    # an unreviewed path. Require every recognized reduction call to be owned.
    literal_calls = re.findall(r'_v2_verify_rescan\(\d+, (?:true|false), \d+, \d+\);', plain)
    if not sites or len(sites) != len(list(CALL.finditer(plain))) or len(sites) != len(literal_calls):
        raise ValueError('incomplete direct-count verification-block coverage')
    if adaptive:
        # Hints choose between two equivalent checks; they never cache values
        # or counts. Thread-local sharing between instances is safe because a
        # stale hint only changes which complete comparison pass runs. No DUT
        # member or allocation layout changes, and there is no training file.
        slots = 2*(1+max(s['group'] for s in sites))
        method = re.search(r'(?m)^[ \t]*ESSENT_COLD_NOINLINE\s+void\s+_v2_verify_rescan\(', plain)
        if method is None:raise ValueError('missing rescan declaration for direct-count hint helper')
        helper = ('\n  static unsigned char* _chisa_direct_count_history() {\n'
                  f'    static thread_local unsigned char hints[{slots}]{{}};\n'
                  '    return hints;\n  }\n')
        edits.append((method.start(), method.start(), helper))
        edits.sort()
    parts, previous = [], 0
    for begin, end, replacement in edits:
        if begin < previous:
            raise ValueError('nested direct-count verification blocks')
        parts.extend((text[previous:begin], replacement))
        previous = end
    parts.append(text[previous:])
    return ''.join(parts), {'sites': sites, 'adaptive': adaptive,
                           'hint_bytes_per_thread': slots if adaptive else 0,
                           'count_helper': '_v2_verify_count' if modern else '_v2_verify_exact_count',
                           'strict_and_logging_path_preserved': True, 'boundary_carry_preserved': True}
