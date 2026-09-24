#!/usr/bin/env python3
"""Add runtime mismatch reporting policy without changing an oracle comparison."""
import argparse
import hashlib
import json
import pathlib
import re
import shutil

def add_exact_count_path(text):
    """Keep every predicate and the original logging/fatal rescan verbatim.

    Once a report-only run has exhausted its log budget, the copied predicates
    accumulate a local count in a warm function. No RTL value or check is omitted.
    """
    if '_v2_verify_exact_count' in text:
        raise ValueError('exact-count preparation requires an original header')
    tokens=re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',re.S)
    plain=tokens.sub(lambda m: ''.join('\n' if c=='\n' else ' ' for c in m[0]),text)
    match=re.search(r'ESSENT_COLD_NOINLINE\s+void\s+_v2_verify_rescan\(int _v2_group, bool _forward, int _lo, int _hi\)\s*\{',plain)
    if not match:raise ValueError('unrecognized checked-rescan signature')
    begin=match.end()-1;depth=1;end=begin+1
    while depth and end<len(plain):
        depth += (plain[end]=='{')-(plain[end]=='}');end+=1
    if depth:raise ValueError('unterminated checked rescan')
    body=text[begin+1:end-1]
    action='record_oracle_mismatch();'
    log_guard=r'oracle_mismatch_should_log\(\)'
    fatal='oracle_mismatches_fatal'
    legacy_action=('verify_mismatches++; if (oracle_mismatch_fatal) '
                   '{ assert_triggered = true; assert_exit_code = 42; }')
    if legacy_action in body:
        if action in body:raise ValueError('mixed mismatch reporting protocols')
        action=legacy_action
        log_guard=r'verify_mismatches < oracle_mismatch_log_limit'
        fatal='oracle_mismatch_fatal'
    count=body.count(action)
    if not count:raise ValueError('rescan has no recognized comparisons')
    hot,logs=re.subn(r'(?m)^[ \t]*if \('+log_guard+r'\) fprintf\(stderr, "ORACLE MISMATCH[^\n]*;\n','',body)
    if logs!=count:raise ValueError('rescan comparison/log coverage differs')
    hot=hot.replace(action,'++_chisa_exact_mismatches;')
    if any(word in hot for word in ('fprintf','assert_triggered','record_oracle_mismatch','oracle_mismatch_should_log','verify_mismatches','oracle_mismatch_fatal')):
        raise ValueError('unexpected side effect in exact-count predicates')
    if re.search(r'\breturn\b',tokens.sub('',hot)):
        raise ValueError('unexpected early return in exact-count predicates')
    predicates=lambda s:[line.strip() for line in s.splitlines() if line.lstrip().startswith('if (') and 'ORACLE_NUM_CYCLES' in line]
    if predicates(hot)!=predicates(body):raise ValueError('exact-count predicates changed')
    dispatch=(f'\n    if (!{fatal} && verify_mismatches >= oracle_mismatch_log_limit &&'
              '\n        _lo >= 0 && _hi >= _lo && verify_mismatches <= UINT64_MAX -'
              f' static_cast<uint64_t>(_hi - _lo) * {count}u) {{'
              '\n      _v2_verify_exact_count(_v2_group, _forward, _lo, _hi);\n      return;\n    }\n')
    helper=('\n  ESSENT_NOINLINE void _v2_verify_exact_count(int _v2_group, bool _forward, int _lo, int _hi) {'
            '\n    uint64_t _chisa_exact_mismatches = 0;\n'+hot+
            '\n    verify_mismatches += _chisa_exact_mismatches;\n  }\n')
    return text[:begin+1]+dispatch+body+text[end-1:end]+helper+text[end:],count

def prepare(header,output,fast_count=False,direct_count=False):
    source=header.read_bytes()
    text=source.decode()
    if header.resolve()==(output/"TestHarness.h").resolve():
        raise ValueError("oracle policy must be prepared in a separate directory")
    supported="set_oracle_mismatch_policy(" in text
    guards=lambda s:[line.strip() for line in s.splitlines()
                     if line.lstrip().startswith("if (") and "ORACLE_NUM_CYCLES" in line]
    original_guards=guards(text)
    actions=logs=0
    if not supported:
        declaration="  uint64_t verify_mismatches = 0;"
        if text.count(declaration)!=1:raise ValueError("missing unique mismatch counter")
        members = (
            "\n  bool oracle_mismatch_fatal = true;"
            "\n  uint64_t oracle_mismatch_log_limit = UINT64_MAX;"
            "\n  void set_oracle_mismatch_policy(bool fatal,uint64_t limit) {"
            "\n    oracle_mismatch_fatal=fatal;oracle_mismatch_log_limit=limit;"
            "\n  }")
        text=text.replace(declaration,declaration+members)
        action="verify_mismatches++; assert_triggered = true; assert_exit_code = 42;"
        actions=text.count(action)
        if not actions:raise ValueError("no recognized oracle mismatch actions")
        text=text.replace(action,
            "verify_mismatches++; if (oracle_mismatch_fatal) { assert_triggered = true; assert_exit_code = 42; }")
        text,logs=re.subn(r'(?m)^(\s*)(fprintf\(stderr, "ORACLE MISMATCH[^\n]+)$',
            r'\1if (verify_mismatches < oracle_mismatch_log_limit) \2',text)
        if logs!=actions:raise ValueError(f"mismatch action/log coverage differs: {actions}/{logs}")
    if guards(text)!=original_guards:
        raise ValueError("oracle comparison guards changed")
    count_predicates=0
    if (fast_count or direct_count) and not re.search(r'uint64_t\s+_v2_verify_count\(', text) \
            and '_v2_verify_exact_count(' not in text:
        text,count_predicates=add_exact_count_path(text)
    direct_report=None
    if direct_count:
        from direct_oracle_count import rewrite_direct_count
        text,direct_report=rewrite_direct_count(text)
    output.mkdir(parents=True,exist_ok=True)
    (output/"TestHarness.h").write_text(text)
    clock=header.parent/"clock_domain_manifest.json"
    if clock.exists():shutil.copyfile(clock,output/clock.name)
    report={
        "sourceHeader":str(header),"sourceSha256":hashlib.sha256(source).hexdigest(),
        "outputSha256":hashlib.sha256(text.encode()).hexdigest(),
        "alreadySupported":supported,"failureActionsAdapted":actions,
        "comparisonGuards":len(original_guards),"comparisonsPreserved":True,
        "mismatchCountingPreserved":True,"defaultFatal":True,
        "rtlAssertionPolicyChanged":False,
        "exactCountPath":fast_count or count_predicates > 0,"exactCountPredicates":count_predicates,
        "directCount":direct_report,
    }
    (output/"oracle-policy.json").write_text(json.dumps(report,indent=2)+"\n")
    print(f"ORACLE_POLICY guards={len(original_guards)} adapted={actions} checks=preserved counters=preserved")

def main():
    p=argparse.ArgumentParser()
    p.add_argument("--header",type=pathlib.Path,required=True)
    p.add_argument("--output",type=pathlib.Path,required=True)
    p.add_argument("--fast-count",action="store_true")
    p.add_argument("--direct-count",action="store_true",
                   help="Use one exact pass for recently mismatching groups after logging is exhausted; preserve every check")
    args=p.parse_args();prepare(args.header,args.output,args.fast_count,args.direct_count)
if __name__=="__main__":main()
