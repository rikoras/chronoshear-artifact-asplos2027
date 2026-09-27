"""Keep boundary comparisons hot after report-only logging is exhausted."""
from pathlib import Path
import re

NAME='_v2_verify_boundary_rescan'
REPORT='_v2_verify_boundary_report'
SIGNATURE=re.compile(r'ESSENT_COLD_NOINLINE void (TestHarness::)?'+NAME+r'\(int _v2_group, bool _forward\) \{')
DECL='ESSENT_COLD_NOINLINE void '+NAME+'(int _v2_group, bool _forward);'

def rewrite(text):
    match=SIGNATURE.search(text)
    if not match:return text,0
    start=match.end();end=start;depth=1
    while depth:
        if end>=len(text):raise ValueError('Unterminated boundary helper')
        depth+=(text[end]=='{')-(text[end]=='}');end+=1
    body=text[start:end-1];lines=[line.strip() for line in body.splitlines() if line.strip()]
    switch=lines.index('switch (_v2_group) {');prefix=lines[:switch]
    cases=[];i=switch+1;total=0
    while i<len(lines) and lines[i].startswith('case '):
        case=re.fullmatch(r'case (\d+): \{',lines[i])
        if not case:raise ValueError('Unexpected boundary case')
        i+=1;groups={}
        while lines[i]!='break;':
            declaration=''
            if lines[i].startswith('{ const '):declaration=lines[i][2:];i+=1
            guard=lines[i];i+=1
            if not guard.startswith('if (') or not guard.endswith(') {'):
                raise ValueError('Unexpected boundary comparison')
            condition=guard[4:-3]
            if not lines[i].startswith('if (oracle_mismatch_should_log()) fprintf(stderr, "ORACLE MISMATCH '):
                raise ValueError('Unexpected boundary report')
            i+=1
            mask=re.fullmatch(r'_chronoshear_mark_oracle_mask\((\d+), UINT64_C\(1\) << (\d+)\);',lines[i]);i+=1
            if not mask or lines[i]!='record_oracle_mismatch();':raise ValueError('Unexpected boundary accounting')
            i+=1
            if lines[i]!=('} }' if declaration else '}'):raise ValueError('Unexpected boundary block end')
            i+=1;total+=1
            groups.setdefault(int(mask[1]),[]).append((declaration,condition,int(mask[2])))
        i+=1
        if lines[i]!='}':raise ValueError('Unexpected boundary case end')
        i+=1;cases.append((int(case[1]),groups))
    if lines[i:]!=['default: break;','}']:raise ValueError('Unexpected boundary tail')
    if total!=body.count('record_oracle_mismatch();'):raise ValueError('Incomplete boundary predicate coverage')
    scope=match[1] or ''
    hot=[f'ESSENT_NOINLINE void {scope}{NAME}(int _v2_group, bool _forward) {{',
         '    if (oracle_mismatches_fatal || verify_mismatches < oracle_mismatch_log_limit ||',
         f'        verify_mismatches > UINT64_MAX - UINT64_C({total})) {{',
         f'      {REPORT}(_v2_group, _forward); return;', '    }',
         *['    '+s for s in prefix], '    uint64_t _count = 0;', '    switch (_v2_group) {']
    for case,groups in cases:
        hot.append(f'      case {case}: {{')
        for group,checks in groups.items():
            hot+=['        { uint64_t _mask = 0;']
            for declaration,condition,bit in checks:
                hot+=['          {'+(' '+declaration if declaration else ''),
                      f'            const uint64_t _different = static_cast<uint64_t>({condition});',
                      '            _count += _different;',f'            _mask |= _different << {bit};','          }']
            hot+=[f'          _chronoshear_mark_oracle_mask({group}, _mask);','        }']
        hot+=['        break;', '      }']
    hot+=['      default: break;', '    }', '    verify_mismatches += _count;', '  }']
    original=text[match.start():end].replace(NAME+'(',REPORT+'(',1)
    return text[:match.start()]+'\n'.join(hot)+'\n  '+original+text[end:],total

def prepare(header,kernels=()):
    paths=[Path(header),*map(Path,kernels)]
    original={p:p.read_text() for p in paths}
    if any(REPORT+'(' in s for s in original.values()):return 0
    updated={};counts=[]
    for path,text in original.items():
        updated[path],count=rewrite(text)
        if count:counts.append(count)
    if not counts:return 0
    if len(counts)!=1:raise ValueError('Expected one unpartitioned boundary helper')
    for path,text in updated.items():
        if DECL in text:
            text=text.replace(DECL,DECL.replace('ESSENT_COLD_NOINLINE','ESSENT_NOINLINE')+'\n  '+DECL.replace(NAME,REPORT))
        if text!=original[path]:path.write_text(text)
    return counts[0]
