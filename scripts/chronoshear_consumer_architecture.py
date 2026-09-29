#!/usr/bin/env python3
"""Build observation-enabled copies of the BOOM W32 consumers."""
from pathlib import Path
import argparse,copy,json,re,shutil,sys

ROOT=Path(__file__).resolve().parents[1]
BOOMS=('boom-small','boom-medium','boom-large')
sys.path.insert(0,str(ROOT/'source/checks/boom'))

def generate(dut):
    from instrument_consumer_architecture import instrument
    if dut not in BOOMS:raise ValueError('Unsupported consumer architecture check: '+dut)
    source=ROOT/'generated'/dut/'w32';output=ROOT/'generated'/dut/'validation-w32'
    files=[source/'TestHarness.h',*sorted(source.glob('kernel_*.cpp'))]
    if not files[0].is_file():raise RuntimeError('Generate '+dut+' W32 before its architecture check')
    work=ROOT/'.build/consumer-architecture'/dut;work.mkdir(parents=True,exist_ok=True)
    marker='// CHRONOSHEAR_OBSERVATION_FILE '
    texts=[path.read_text() for path in files]
    if any(marker in s for s in texts):raise RuntimeError('Source already has observation file markers')
    combined=''.join(marker+str(i)+'\n'+s for i,s in enumerate(texts))
    raw=work/'source.h';raw.write_text(combined)
    instrument(raw,work/'instrumented',32,dut.removeprefix('boom-'))
    checked=(work/'instrumented/TestHarness.h').read_text()
    parts=re.split(r'(?m)^'+re.escape(marker)+r'(\d+)\n',checked)
    if parts[0] or len(parts)!=1+2*len(files):raise RuntimeError('Observation file boundaries changed')
    if output.exists():shutil.rmtree(output)
    output.mkdir(parents=True)
    for path in source.iterdir():
        if path.is_file() and path.name!='TestHarness.h' and path.suffix in ('.h','.hpp','.inc'):
            shutil.copy2(path,output/path.name)
    for index,path in enumerate(files):
        if int(parts[1+2*index])!=index:raise RuntimeError('Observation file order changed')
        (output/path.name).write_text(parts[2+2*index])
    for name in ['consumer_architecture_fields.h','consumer_architecture_owners.h']:
        (output/name).write_text((work/'instrumented'/name).read_text())
    print('CONSUMER ARCHITECTURE GENERATED',dut,flush=True)

def recipes(plan):
    result={}
    for dut in BOOMS:
        folder='generated/'+dut+'/validation-w32'
        if not (ROOT/folder/'consumer_architecture_fields.h').is_file():continue
        source=plan['binaries']['chronoshear-'+dut+'-w32']
        spec=copy.deepcopy(source);old='${ROOT}/generated/'+dut+'/w32/'
        new='${ROOT}/'+folder+'/'
        observer_flags=None
        for unit in spec['objects']:
            if unit.get('reference'):continue
            unit['flags']=['-I${ROOT}/'+folder,*[f for f in unit['flags'] if not f.startswith('-DCHISA_DISABLE_ARCHITECTURE_CAPTURE')],'-DCHISA_CONSUMER_ARCHITECTURE=1']
            if unit['source'].endswith('/run_live_sidecar.cpp'):
                observer_flags=list(unit['flags'])
                unit['flags'].append('-Dmain=chronoshear_validation_main')
            elif unit['source'].startswith(old):unit['source']=unit['source'].replace(old,new,1)
        if observer_flags is None:raise RuntimeError('No matching BOOM runtime recipe')
        for source_file in ['source/duts/boom-repcut/runtime/consumer_architecture.cpp','source/checks/boom/consumer_validation_main.cpp']:
            spec['objects'].append({'source':'${ROOT}/'+source_file,'flags':list(observer_flags),'reference':False,'memory_gib':1})
        name='chronoshear-validate-'+dut+'-w32'
        spec.update(output='bin/'+name,variant='validation-w32',kind='architecture')
        result[name]=spec
    return result

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--dut',choices=BOOMS);a=p.parse_args()
    for dut in ([a.dut] if a.dut else BOOMS):generate(dut)
    plan=json.loads((ROOT/'BUILD.json').read_text());plan['binaries'].update(recipes(plan))
    (ROOT/'BUILD.json').write_text(json.dumps(plan,indent=2)+'\n')

if __name__=='__main__':main()
