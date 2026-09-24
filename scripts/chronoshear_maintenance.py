#!/usr/bin/env python3
"""Interactively clean or rebuild the selected artifact components."""
from pathlib import Path
import argparse,hashlib,json,re,shutil,subprocess,sys
from chronoshear_machine import binding,host_lock
ROOT=Path(__file__).resolve().parents[1]
DUTS=['aes','matmul','sodor','rocket','boom-small','boom-medium','boom-large']
STAGES={1:'ChronoShear FIRRTL -> C++ and model bindings',2:'ChronoShear model/harness/RTL objects and binaries',
        3:'Verilator FIRRTL -> Verilog -> C++',4:'Verilator C++ objects and binaries',5:'ChronoShear Scala compiler -> JAR',
        6:'Reference-model architectural checks'}

def choose(prompt,items):
    for key,value in items.items():print(f'  {key}. {value}')
    answer=input(prompt+' (numbers separated by commas, or all): ').strip().lower()
    if answer=='all':return list(items)
    result=[int(x.strip()) for x in answer.split(',')]
    if not result or any(x not in items for x in result):raise ValueError('Invalid menu selection')
    return list(dict.fromkeys(result))

def remove(path):
    if path.is_dir():shutil.rmtree(path)
    else:path.unlink(missing_ok=True)

def clean_backend(plan,duts,kind):
    for name,spec in plan['binaries'].items():
        if spec.get('dut') not in duts or spec.get('kind')!=kind:continue
        print('Remove',spec['output']);remove(ROOT/spec['output'])
        receipt=ROOT/'.build/receipts'/(name+'.json')
        keys=set(json.loads(receipt.read_text()).get('objects',[])) if receipt.exists() else set()
        for unit in spec['objects']:
            payload={'source':unit['source'].replace('${ROOT}',str(ROOT)),'flags':[f.replace('${ROOT}',str(ROOT)) for f in unit['flags']]}
            keys.add(hashlib.sha256(json.dumps(payload,sort_keys=True).encode()).hexdigest()[:24])
        for key in keys:
            for path in (ROOT/'.build/objects').glob(key+'.*'):remove(path)
        remove(receipt);remove(ROOT/'.build'/(name+'-link.log'))

def execute(selection):
    from chronoshear_recipes import refresh
    import chronoshear_emit as emit
    import chronoshear_verilator as verilator
    import chronoshear_architecture as architecture
    import chronoshear_build as backend
    duts=selection['duts'];stages=selection['stages'];action=selection['action']
    processors=[dut for dut in duts if dut in architecture.PROCESSORS]
    build_checks=bool(set(stages)&{2,4,6})
    with host_lock():
        plan=refresh()
        if 5 in stages:
            if action in ['clean','clean-rebuild']:remove(ROOT/'tools/chronoshear.jar');remove(ROOT/'.build/compiler')
            if action!='clean':
                import chronoshear_compiler_build
                chronoshear_compiler_build.build()
        for dut in duts:
            if build_checks and dut in processors and action!='clean':
                remove(ROOT/'bin'/('chronoshear-architecture-'+dut))
            if 1 in stages:
                clean_backend(plan,[dut],'chronoshear')
                clean_backend(plan,[dut],'architecture')
                for p in (ROOT/'generated'/dut).glob('*'):
                    if p.name.startswith(('w','mt6-w')):print('Remove',p.relative_to(ROOT));remove(p)
                remove(ROOT/'.build/emission'/dut)
            if 2 in stages and action in ['clean','clean-rebuild']:
                clean_backend(plan,[dut],'chronoshear')
                clean_backend(plan,[dut],'architecture')
            if 3 in stages:
                clean_backend(plan,[dut],'verilator')
                clean_backend(plan,[dut],'architecture')
                for name in ['verilog','verilator1','verilator4']:remove(ROOT/'generated'/dut/name)
                if dut in architecture.BOOMS:remove(ROOT/'generated'/dut/'architecture')
            if 4 in stages and action in ['clean','clean-rebuild']:
                clean_backend(plan,[dut],'verilator')
                clean_backend(plan,[dut],'architecture')
            if 6 in stages and action in ['clean','clean-rebuild']:
                clean_backend(plan,[dut],'architecture')
                if dut in architecture.BOOMS:remove(ROOT/'generated'/dut/'architecture')
        if action=='clean':return
        if 1 in stages or 2 in stages:
            required=[dut for dut in duts if 1 in stages or any(not (ROOT/'generated'/dut/('w'+str(w))/(plan['designs'][dut]['top']+'.h')).exists() for w in [4,8,16,32])]
            if required:emit.generate_all(required,[4,8,16,32])
            if 'boom-large' in duts and (1 in stages or not (ROOT/'generated/boom-large/mt6-w16/TestHarness.h').exists()):
                if not (ROOT/'.build/emission/boom-large/w16/oracle_manifest.json').exists():emit.emit('boom-large',16)
                subprocess.run([sys.executable,str(ROOT/'scripts/chronoshear_emit.py'),'--dut','boom-large','--width','16','--partitioned'],check=True)
        if 3 in stages or 4 in stages:
            required=[dut for dut in duts if 3 in stages or not all((ROOT/'generated'/dut/('verilator'+str(n))/(('V'+plan['designs'][dut]['top'])+'_classes.mk')).exists() for n in [1,4])]
            if required:verilator.generate_all(required)
        if build_checks and processors:
            required=[dut for dut in processors if not (ROOT/'generated'/dut/'w32'/(plan['designs'][dut]['top']+'.h')).is_file()]
            if required:emit.generate_all(required,[32])
            required=[dut for dut in processors if 6 in stages or not
                      (ROOT/'generated'/dut/('verilator1' if dut=='rocket' else 'architecture')/'VTestHarness___024root.h').is_file()]
            if required:architecture.generate_all(required)
        plan=refresh();selected=[]
        for name,spec in plan['binaries'].items():
            if spec.get('dut') in duts and ((2 in stages and spec.get('kind')=='chronoshear') or
                (4 in stages and spec.get('kind')=='verilator') or (build_checks and spec.get('kind')=='architecture')):selected.append(name)
        if selected:
            cpus,memory=backend.topology()
            args=argparse.Namespace(select='^('+ '|'.join(re.escape(n) for n in selected)+')$',jobs=16,memory_gib=46,cxx='clang++-19',rebuild=False)
            backend.build(args,cpus,memory)
        print('Finished. Experiment inputs and results are unchanged.')

def main():
    if len(sys.argv)==3 and sys.argv[1]=='--execute':execute(json.loads(sys.argv[2]));return
    print('ChronoShear clean / rebuild')
    print('  1. Clean only\n  2. Rebuild\n  3. Clean and rebuild')
    action=int(input('Action [1/2/3]: ').strip())
    if action not in [1,2,3]:raise ValueError('Select one action')
    duts=[DUTS[i-1] for i in choose('DUTs',{i+1:d for i,d in enumerate(DUTS)})]
    stages=choose('Components',STAGES)
    selection={'action':{1:'clean',2:'rebuild',3:'clean-rebuild'}[action],'duts':duts,'stages':stages}
    print('Action:',selection['action'],'DUTs:',', '.join(duts))
    print('Selected:', '; '.join(STAGES[i] for i in stages))
    subprocess.run([*binding(),sys.executable,__file__,'--execute',json.dumps(selection)],check=True)

if __name__=='__main__':main()
