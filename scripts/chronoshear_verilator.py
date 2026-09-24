#!/usr/bin/env python3
"""Lower the packaged FIRRTL designs and generate Verilator C++ baselines."""
from pathlib import Path
import argparse,concurrent.futures,json,os,re,subprocess,sys
from chronoshear_machine import binding
ROOT=Path(__file__).resolve().parents[1]

def run(command,log,**kwargs):
    log.parent.mkdir(parents=True,exist_ok=True)
    with log.open('w') as f:subprocess.run(list(map(str,command)),stdout=f,stderr=subprocess.STDOUT,check=True,**kwargs)

def generate(dut):
    plan=json.loads((ROOT/'BUILD.json').read_text());top=plan['designs'][dut]['top'];inp=ROOT/'inputs'/dut
    lower=ROOT/'generated'/dut/'verilog';lower.mkdir(parents=True,exist_ok=True)
    cp=str(ROOT/'tools/chronoshear.jar')+os.pathsep+str(ROOT/'deps/compiler-libraries.jar')
    java=[*binding(),'java','-XX:ActiveProcessorCount=1','-Xmx8G','-Xss16M','-cp',cp]
    if dut in ['boom-medium','boom-large']:
        annotations=[]
        for item in json.loads((inp/'design.anno.json').read_text()):
            if not item['class'].startswith('firrtl.'):continue
            item=dict(item)
            if item['class']=='firrtl.transforms.BlackBoxResourceAnno':
                name=Path(item.pop('resourceId')).name
                file=next(p for p in [inp/'blackboxes'/name,ROOT/'source/harnesses'/dut/'csrc'/name] if p.is_file())
                item.update({'class':'firrtl.transforms.BlackBoxPathAnno','path':str(file)})
            annotations.append(item)
        (lower/'annotations.json').write_text(json.dumps(annotations)+'\n')
        args=['firrtl.stage.FirrtlMain','-i',inp/'design.fir','-faf',lower/'annotations.json','-td',lower,'-o',top+'.v','-X','verilog']
    else:args=['essent.EmitVerilogFromFirrtl',inp/'design.fir',lower]
    run([*java,*args],ROOT/'.build/logs'/dut/'verilog.log',cwd=ROOT)
    verilog=lower/(top+'.v');extra=[]
    if dut=='rocket':
        instrumented=lower/'instrumented';instrumented.mkdir(exist_ok=True)
        run([sys.executable,ROOT/'source/harnesses/rocket/instrument.py',verilog,instrumented/'TestHarness.v','--simdtm-input',inp/'blackboxes/SimDTM.v','--simdtm-output',instrumented/'SimDTM.v'],ROOT/'.build/logs/rocket/instrument.log')
        verilog=instrumented/'TestHarness.v';extra=[instrumented/'SimDTM.v',inp/'blackboxes/EICG_wrapper.v',inp/'blackboxes/plusarg_reader.v']
    elif dut.startswith('boom-'):
        extra=[inp/'blackboxes'/n for n in ['AsyncResetReg.v','EICG_wrapper.v','plusarg_reader.v','SimDTM.v','SimJTAG.v'] if (inp/'blackboxes'/n).exists()]
    vr=ROOT/'tools/verilator';env={**os.environ,'VERILATOR_ROOT':str(vr)}
    for threads in [1,4]:
        output=ROOT/'generated'/dut/('verilator'+str(threads));output.mkdir(parents=True,exist_ok=True)
        flags=['--cc','--top-module',top,'--threads',str(threads),'--no-timing','-O3','-Wno-fatal','-Wno-STMTDLY']
        if dut.startswith('boom-'):flags+=['--output-split','20000','--x-assign','unique','-DPRINTF_COND=0','-DSTOP_COND=0']
        if dut=='rocket':flags+=['--flatten','--assert','--output-split','20000','--output-split-cfuncs','20000','--x-assign','fast','--x-initial','0','--max-num-width','1048576','-DPRINTF_COND=0','-DSTOP_COND=0']
        flags+=['-I'+str(lower),'-I'+str(inp/'blackboxes'),'-Mdir',str(output)]
        run([*binding(),vr/'bin/verilator',*flags,verilog,*extra],ROOT/'.build/logs'/dut/('verilator'+str(threads)+'.log'),env=env,cwd=ROOT)
    print('VERILATOR GENERATED',dut,flush=True)

def recipes(plan):
    result={}
    inc=lambda p:'-I${ROOT}/'+str(p)
    for dut,config in plan['designs'].items():
        for n in [1,4]:
            folder=Path('generated')/dut/('verilator'+str(n));top='V'+config['top']
            if not (ROOT/folder/(top+'_classes.mk')).exists():continue
            flags=['-std=c++17','-O3' if dut=='matmul' else '-O2','-march=icelake-server','-DNDEBUG','-pthread','-fbracket-depth=1024',
                   inc(folder),inc('tools/verilator/include'),inc('tools/verilator/include/vltstd'),'-DVM_COVERAGE=0','-DVM_SC=0','-DVM_TRACE=0','-DVM_TRACE_FST=0','-DVM_TRACE_VCD=0','-DVM_TRACE_SAIF=0',f'-DCHRONOSHEAR_BASELINE_THREADS={n}']
            sources=[p.relative_to(ROOT) for p in sorted((ROOT/folder).glob('*.cpp')) if not p.name.endswith('__ALL.cpp')]
            classes=(ROOT/folder/(top+'_classes.mk')).read_text()
            for group in ['VM_GLOBAL_FAST','VM_GLOBAL_SLOW']:
                m=re.search(r'^'+group+r'\s*\+=\s*(.*?)(?=\n\n|\Z)',classes,re.M|re.S)
                if m:sources += [Path('tools/verilator/include')/(x+'.cpp') for x in m[1].replace('\\',' ').split()]
            libs=[];harness=Path('source/harnesses')/dut
            if dut=='matmul':flags+=['-DMODE=2','-mprefer-vector-width=512',inc('inputs/matmul')];sources.append(Path('source/duts/matmul-feedforward/bench.cpp'))
            elif dut in ['aes','sodor']:sources.append(harness/f'verilator{n}.cpp')
            elif dut=='rocket':flags+=['-DROCKET_FIRRTL_VERILOG_LAYOUT=1'];sources.append(Path('source/duts/rocket-fullchip/runtime/run_backdoor_scalar.cpp'))
            else:
                flags+=['-DVERILATOR','-DTEST_HARNESS=VTestHarness','-D__STDC_FORMAT_MACROS',f'-DCHISA_BASELINE_THREADS={n}',
                        '-include','${ROOT}/'+str(harness/'csrc/verilator.h'),'-include','${ROOT}/inputs/'+dut+'/plusargs.h','-include','${ROOT}/'+str(folder/'VTestHarness.h'),
                        inc(harness),inc(harness/'csrc'),inc('deps/fesvr'),inc('deps/fesvr/build')]
                sources += [harness/'verilator.cpp',*[harness/'csrc'/f for f in ['SimDTM.cc','SimJTAG.cc','remote_bitbang.cc']]]
                libs=['${ROOT}/deps/fesvr/build/libfesvr.a']
            name=dut+'-verilator-'+str(n)+'t'
            result[name]={'output':'bin/'+name,'dut':dut,'variant':'verilator'+str(n),'kind':'verilator',
                          'objects':[{'source':'${ROOT}/'+str(p),'flags':flags,'reference':False,'memory_gib':1} for p in sources],
                          'libraries':libs,'link_flags':['-pthread']}
    return result

def generate_all(duts):
    with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:
        for future in [pool.submit(generate,dut) for dut in duts]:future.result()

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--dut',required=True);a=p.parse_args();generate(a.dut)
