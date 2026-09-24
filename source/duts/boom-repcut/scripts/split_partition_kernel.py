#!/usr/bin/env python3
"""Move emitted partition method bodies into independently compiled C++ files.

Assignments, lane loops, assertions and oracle checks are copied verbatim. This
is a compilation boundary only: no RTL work is removed, reordered or replaced.
The input must use instance-local scratch, as the partitioned runtime requires.
"""
import argparse
import bisect
import hashlib
import json
from pathlib import Path
import re


def digest(text):
    return hashlib.sha256(text.encode()).hexdigest()


def cooperative_body(body, partition, forward, poll_bytes=0):
    # Yield only after an existing complete outlined chunk. Its locals have
    # finished; the wrapper's captured flags/indices stay on the same stack.
    masked = re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                    lambda m: ''.join('\n' if c=='\n' else ' ' for c in m[0]), body, flags=re.S)
    stack, ends, positions, levels = [], {}, [], []
    for mark in re.finditer(r'[{}]', masked):
        if mark[0]=='{': stack.append(mark.start())
        elif stack: ends[stack.pop()]=mark.start()
        positions.append(mark.start()); levels.append(len(stack))
    insertions=[]
    pattern=re.compile(r'// \[v2 eval chunk (\d+)\]\s*\[&\]\(\)\s+ESSENT_NOINLINE\s*\{')
    for match in pattern.finditer(body):
        close=ends.get(match.end()-1)
        tail=re.match(r'\s*\(\s*\)\s*;',body[close+1:]) if close is not None else None
        if tail is None: raise ValueError('unrecognized outlined chunk boundary')
        if poll_bytes:
            # Existing schedule comments begin complete emitted units. Split
            # only at the lambda's outer depth after a complete statement;
            # never inside a lane loop, expression, scan or if/else pair.
            depth = levels[bisect.bisect_right(positions, match.end()-1)-1]
            previous = match.end()
            for boundary in re.finditer(r'(?m)^[ \t]*// \[(?:v2|vec)\b[^\n]*', body[match.end():close]):
                point = match.end()+boundary.start()
                if point-previous < poll_bytes or levels[bisect.bisect_right(positions,point)-1] != depth:
                    continue
                before = masked[previous:point].rstrip()
                after = masked[point:close].lstrip()
                if not before or before[-1] not in ';}' or re.match(r'(?:else|while)\b',after):
                    continue
                insertions.append((point, '\n    if (partition_task_poll) partition_task_poll(partition_task_context, '+
                                  f'{partition}, {str(forward).lower()}, {match[1]});\n'))
                previous = point
        at=close+1+tail.end()
        insertions.append((at, '\n    if (partition_task_poll) partition_task_poll(partition_task_context, '+
                          f'{partition}, {str(forward).lower()}, {match[1]});'))
    if not insertions: raise ValueError('cooperative partition has no outlined chunks')
    pieces=[];previous=0
    for at,value in insertions:pieces.extend((body[previous:at],value));previous=at
    pieces.append(body[previous:])
    return ''.join(pieces),len(insertions)


def split(header, output, top='TestHarness', helper_bytes=4*1024*1024, cooperative_poll=False, poll_bytes=0):
    text = header.read_text()
    tokens = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
    plain = tokens.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)
    top_match = re.search(r'\b(?:struct|class)\s+'+re.escape(top)+r'\s*\{', plain)
    if not top_match:
        raise ValueError('no named generated top class: '+top)
    stack, ends, depth = [], {}, {}
    for match in re.finditer(r'[{}]', plain):
        if match[0] == '{':
            depth[match.start()] = len(stack)
            stack.append(match.start())
        elif stack:
            ends[stack.pop()] = match.start()
    top_begin = top_match.end()-1
    top_end = ends[top_begin]
    count = re.search(r'ESSENT_PARTITIONS\s*=\s*(\d+)', plain)
    partitions = int(count[1]) if count else 0
    scratch, scratch_edits = [], []
    for line in re.finditer(r'(?m)^.*\bstatic\b.*\b_s_\S+\s*\[.*$', plain[:top_begin]):
        if re.search(r'\bconst\b', line[0]): continue
        declaration = re.fullmatch(r'\s*(alignas\(\d+\)\s+)static\s+((?:UInt|SInt)<\d+>\s+_s_[\w$]+\[\d+\];)\s*',line[0])
        if partitions or not declaration:
            raise ValueError('mutable file-scope scratch cannot be split across translation units')
        # The older whole-kernel emitter has one global scratch arena. Keep
        # exactly one arena across TUs; independent copies would break the
        # forward/reverse carry. Partitioned consumers must stay instance-local.
        scratch.append(declaration[1]+declaration[2])
        scratch_edits.append((line.start(),line.end(),declaration[1]+'extern '+declaration[2]))
    functions = re.compile(r'(?m)^\s*(?:(?:ESSENT_\w+|inline|static)\s+)*'
                           r'(?:void|bool)\s+(?P<name>[A-Za-z_]\w*)\([^;\n]*\)\s*\{')
    edits, groups, methods, chunks = list(scratch_edits), {}, [], {}
    helper_group, helper_size = 0, 0
    for match in functions.finditer(plain, top_begin+1, top_end):
        begin, name = match.end()-1, match['name']
        if depth.get(begin) != depth[top_begin]+1:
            continue
        partition = re.fullmatch(r'eval_(forward|reverse)_p(\d+)', name)
        whole = not partitions and name in ('eval_forward', 'eval_reverse')
        end = ends[begin]+1
        if cooperative_poll and name=='eval_partition':
            edits.append((begin+1,begin+1,
                '\n    if (partition_eval_active) throw std::logic_error("reentrant partition evaluation");'
                '\n    partition_eval_active=true;'
                '\n    struct TaskGuard { bool& active; ~TaskGuard() { active=false; } } task_guard{partition_eval_active};\n'))
        if not partition and not whole and not (name.startswith('_v2_') and end-begin >= 4096):
            continue
        signature = text[match.start():begin].strip()
        if '=' in signature:  # default arguments require a separate declaration parser
            raise ValueError('unsupported default argument in split method: '+name)
        body = text[begin:end]
        if re.search(r'(?m)^\s*#\s*(?:define|undef)\b', body):
            raise ValueError('method changes preprocessor state: '+name)
        declaration = re.sub(r'\binline\s+', '', signature)
        definition = re.sub(r'\b(?:inline|static)\s+', '', signature)
        definition = re.sub(r'\b'+re.escape(name)+r'\s*\(', top+'::'+name+'(', definition, count=1)
        edits.append((match.start(), end, '\n  '+declaration+';'))
        if partition or whole:
            if cooperative_poll:
                if whole: raise ValueError('cooperative callbacks require actual partitions')
                body,chunks[name]=cooperative_body(body,int(partition[2]),partition[1]=='forward',poll_bytes)
            group = f'kernel_p{partition[2]}_{partition[1]}.cpp' if partition else f'kernel_{name[5:]}.cpp'
        else:
            if helper_size and helper_size+len(body) > helper_bytes:
                helper_group += 1
                helper_size = 0
            group = f'kernel_helpers_{helper_group}.cpp'
            helper_size += len(body)
        groups.setdefault(group, []).append((name, definition+' '+body+'\n'))
        methods.append(name)
    expected = ({f'eval_{direction}_p{p}' for p in range(partitions)
                for direction in ('forward', 'reverse')} if partitions else {'eval_forward','eval_reverse'})
    if not expected or not expected.issubset(methods):
        raise ValueError('not all emitted partition directions were found')
    if cooperative_poll:
        edits.append((top_end,top_end,
            '\n  static constexpr bool ESSENT_PARTITION_TASK_POLL = true;'
            '\n  using PartitionTaskPoll = void (*)(void*, unsigned, bool, unsigned);'
            '\n  PartitionTaskPoll partition_task_poll = nullptr;'
            '\n  void* partition_task_context = nullptr;'
            '\n  bool partition_eval_active = false;\n'))
    fragments, previous = [], 0
    for begin, end, replacement in sorted(edits):
        if begin<previous: raise ValueError('overlapping split edits')
        fragments.extend((text[previous:begin],replacement))
        previous = end
    fragments.append(text[previous:])
    slim = ''.join(fragments)
    if cooperative_poll: slim='#include <stdexcept>\n'+slim
    # Value-initializing the very large aggregate inside main makes LLVM
    # optimize its constructor together with every runtime closure. Keep
    # that one-time allocation out of the hot harness translation unit.
    slim += '\n#define ESSENT_PARTITION_FACTORY 1\n'+top+'* chisa_new_partition_kernel();\n'
    output.mkdir(parents=True, exist_ok=True)
    (output/header.name).write_text(slim)
    units = []
    for name, bodies in groups.items():
        contents = '#include "'+header.name+'"\n\n'+'\n'.join(body for _, body in bodies)
        (output/name).write_text(contents)
        units.append({'file':name, 'sha256':digest(contents), 'methods':[name for name, _ in bodies]})
    factory = '#include "'+header.name+'"\n'+top+'* chisa_new_partition_kernel() { return new '+top+'(); }\n'
    (output/'kernel_factory.cpp').write_text(factory)
    units.append({'file':'kernel_factory.cpp', 'sha256':digest(factory), 'methods':[]})
    if scratch:
        contents = '#include "'+header.name+'"\n'+'\n'.join(scratch)+'\n'
        (output/'kernel_scratch.cpp').write_text(contents)
        units.append({'file':'kernel_scratch.cpp','sha256':digest(contents),'methods':[]})
    manifest = {'schema':1, 'kind':'cooperative-partition-method-split' if cooperative_poll else 'verbatim-partition-method-split', 'top':top,
                'input_sha256':digest(text), 'header_sha256':digest(slim),
                'input_bytes':len(text.encode()), 'header_bytes':len(slim.encode()),
                'methods':methods, 'translation_units':units, 'cooperative_poll':cooperative_poll,
                'poll_chunks':chunks, 'poll_bytes':poll_bytes,
                'global_scratch_variables':len(scratch), 'partitions':partitions}
    (output/'kernel-units.json').write_text(json.dumps(manifest,indent=2)+'\n')
    return manifest


if __name__ == '__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--header',type=Path,required=True)
    parser.add_argument('--out',type=Path,required=True)
    parser.add_argument('--top',default='TestHarness')
    parser.add_argument('--cooperative-poll',action='store_true')
    parser.add_argument('--poll-bytes',type=int,default=0)
    args=parser.parse_args()
    result=split(args.header,args.out,args.top,cooperative_poll=args.cooperative_poll,poll_bytes=args.poll_bytes)
    print('SPLIT_KERNEL methods='+str(len(result['methods']))+' units='+str(len(result['translation_units']))+
          ' header_bytes='+str(result['header_bytes']))
