#!/usr/bin/env python3
"""Generate and build independent architectural checks for the bundled processors."""
from pathlib import Path
import argparse
import concurrent.futures
import copy
import json
import os
import re
import subprocess
import sys
from chronoshear_machine import binding

ROOT = Path(__file__).resolve().parents[1]
BOOMS = ('boom-small', 'boom-medium', 'boom-large')
PROCESSORS = ('rocket', *BOOMS)


def generate(dut):
    if dut not in PROCESSORS:
        raise ValueError('Architectural checks are available for Rocket and BOOM')
    from chronoshear_verilator import run, generate as generate_baseline
    if dut == 'rocket':
        if not (ROOT/'generated/rocket/verilator1/VTestHarness___024root.h').is_file():
            generate_baseline(dut)
        print('ARCHITECTURE GENERATED', dut, flush=True)
        return
    original = ROOT / 'generated' / dut / 'verilog'
    if not (original / 'TestHarness.v').is_file():
        generate_baseline(dut)
    output = ROOT / 'generated' / dut / 'architecture'
    output.mkdir(parents=True, exist_ok=True)
    inputs = ROOT / 'inputs' / dut
    prepare = [sys.executable, ROOT / 'source/checks/boom/prepare_boom_architecture.py',
               '--configuration', dut.removeprefix('boom-'),
               '--verilog', original / 'TestHarness.v',
               '--simdtm', inputs / 'blackboxes/SimDTM.v', '--output', output]
    logs = ROOT / '.build/logs' / dut
    run(prepare, logs / 'architecture-fields.log', cwd=ROOT)
    runtime = ROOT / 'tools/verilator'
    flags = ['--cc', '--top-module', 'TestHarness', '--threads', '1', '--no-timing',
             '-O3', '-Wno-fatal', '-Wno-STMTDLY', '--output-split', '20000',
             '--x-assign', 'unique', '-DPRINTF_COND=0', '-DSTOP_COND=0',
             '-I'+str(original), '-I'+str(inputs/'blackboxes'), '-Mdir', str(output)]
    extras = [inputs/'blackboxes'/name for name in
              ('AsyncResetReg.v', 'EICG_wrapper.v', 'plusarg_reader.v', 'SimJTAG.v')
              if (inputs/'blackboxes'/name).is_file()]
    run([*binding(), runtime/'bin/verilator', *flags, output/'TestHarness.v',
         output/'SimDTM.v', *extras], logs/'architecture-verilator.log', cwd=ROOT,
        env={**os.environ, 'VERILATOR_ROOT':str(runtime)})
    run([*prepare, '--root-header', output/'VTestHarness___024root.h'],
        logs/'architecture-fields.log', cwd=ROOT)
    print('ARCHITECTURE GENERATED', dut, flush=True)


def generate_all(duts=None):
    duts = list(PROCESSORS if duts is None else duts)
    if not duts:
        return
    with concurrent.futures.ThreadPoolExecutor(max_workers=min(3, len(duts))) as pool:
        for future in [pool.submit(generate, dut) for dut in duts]:
            future.result()


def recipes(plan=None):
    if plan is None:
        plan = json.loads((ROOT/'BUILD.json').read_text())
    result = {}
    inc = lambda path: '-I${ROOT}/'+str(path)
    baseline = plan['binaries'].get('rocket-verilator-1t')
    online = plan['binaries'].get('chronoshear-rocket-w32')
    if baseline and online and (ROOT/'generated/rocket/verilator1/VTestHarness___024root.h').is_file():
        objects = [copy.deepcopy(unit) for unit in baseline['objects']
                   if not unit['source'].endswith('/run_backdoor_scalar.cpp')]
        objects += [copy.deepcopy(unit) for unit in online['objects']
                    if unit.get('reference') or unit['source'].endswith('/run_backdoor_scalar.cpp')]
        flags = [*baseline['objects'][0]['flags'], inc('source/reference_models/rocket_model'),
                 inc('source/reference_models/rocket_model/tools'), inc('source/duts/rocket-fullchip/runtime')]
        objects.append({'source':'${ROOT}/source/checks/rocket/rocket_architecture.cpp',
                        'flags':flags, 'reference':False, 'memory_gib':1})
        result['chronoshear-architecture-rocket'] = {
            'output':'bin/chronoshear-architecture-rocket', 'dut':'rocket', 'variant':'architecture',
            'kind':'architecture', 'objects':objects, 'libraries':[], 'link_flags':['-pthread','-latomic']}
    for dut in BOOMS:
        folder = Path('generated')/dut/'architecture'
        classes_path = ROOT/folder/'VTestHarness_classes.mk'
        if not classes_path.is_file():
            continue
        online = plan['binaries']['chronoshear-'+dut+'-w32']
        reference = [copy.deepcopy(unit) for unit in online['objects'] if unit.get('reference')]
        if not reference:
            raise ValueError('No current model object recipe for '+dut)
        flags = ['-std=c++17', '-O2', '-march=icelake-server', '-DNDEBUG', '-pthread',
                 '-fbracket-depth=1024', inc(folder), inc('tools/verilator/include'),
                 inc('tools/verilator/include/vltstd'), '-DVM_COVERAGE=0', '-DVM_SC=0',
                 '-DVM_TRACE=0', '-DVM_TRACE_FST=0', '-DVM_TRACE_VCD=0', '-DVM_TRACE_SAIF=0']
        sources = [path.relative_to(ROOT) for path in sorted((ROOT/folder).glob('*.cpp'))
                   if not path.name.endswith('__ALL.cpp')]
        classes = classes_path.read_text()
        for group in ('VM_GLOBAL_FAST', 'VM_GLOBAL_SLOW'):
            match = re.search(r'^'+group+r'\s*\+=\s*(.*?)(?=\n\n|\Z)', classes, re.M|re.S)
            if match:
                sources += [Path('tools/verilator/include')/(name+'.cpp')
                            for name in match[1].replace('\\',' ').split()]
        objects = [{'source':'${ROOT}/'+str(source), 'flags':list(flags),
                    'reference':False, 'memory_gib':1} for source in sources]
        harness_dir = Path('source/harnesses')/dut/'csrc'
        for source in ('SimJTAG.cc', 'remote_bitbang.cc'):
            objects.append({'source':'${ROOT}/'+str(harness_dir/source),
                            'flags':[*flags, inc(harness_dir)],
                            'reference':False, 'memory_gib':0.5})
        # Model object flags stay byte-for-byte identical to the online W32
        # recipe. The harness observes both endpoints but supplies neither's state.
        harness_flags = [*reference[0]['flags'], *flags,
                         inc('source/reference_models/common'),
                         inc('source/reference_models/boom_model/common'),
                         inc('source/duts/boom-repcut/runtime')]
        objects.append({'source':'${ROOT}/source/checks/boom/run_boom_architecture.cpp',
                        'flags':harness_flags, 'reference':False, 'memory_gib':2})
        objects.extend(reference)
        name = 'chronoshear-architecture-'+dut
        result[name] = {'output':'bin/'+name, 'dut':dut, 'variant':'architecture',
                        'kind':'architecture', 'objects':objects,
                        'libraries':copy.deepcopy(online['libraries']),
                        'link_flags':list(dict.fromkeys([*online['link_flags'], '-pthread']))}
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dut', choices=PROCESSORS)
    arguments = parser.parse_args()
    generate_all([arguments.dut] if arguments.dut else None)
    path = ROOT/'BUILD.json'
    plan = json.loads(path.read_text())
    plan['binaries'].update(recipes(plan))
    path.write_text(json.dumps(plan, indent=2)+'\n')
