#!/usr/bin/env python3
"""Build selected ChronoShear executables in a shared CPU and memory pool."""
from pathlib import Path
import argparse,concurrent.futures,hashlib,json,os,re,shutil,subprocess,sys,time
from chronoshear_machine import SOCKET,NUMA_NODE,PHYSICAL_CPUS,binding,host_lock
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'source/duts/boom-repcut/scripts'))
from build_receipts import compile_object,sha256,write_json
sys.path.insert(0,str(ROOT/'source/scripts'))
from audit_reference_inputs import enforce_reference_inputs

def expand(value):return value.replace('${ROOT}',str(ROOT))

def topology():
    memory=int(re.search(r'MemTotal:\s+(\d+)',Path(f'/sys/devices/system/node/node{NUMA_NODE}/meminfo').read_text())[1])/1024**2
    return list(PHYSICAL_CPUS),memory

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--select',default='chronoshear-');ap.add_argument('--jobs',type=int,default=16)
    ap.add_argument('--memory-gib',type=float,default=46);ap.add_argument('--cxx',default='clang++-19')
    ap.add_argument('--rebuild',action='store_true')
    args=ap.parse_args();cpus,memory=topology()
    if 'CHRONOSHEAR_NUMA_BOUND' not in os.environ:
        env={**os.environ,'CHRONOSHEAR_NUMA_BOUND':'1'}
        os.execvpe('numactl',[*binding(),sys.executable,*sys.argv],env)
    with host_lock():
        build(args,cpus,memory)

def build(args,cpus,memory):
    specs=json.loads((ROOT/'BUILD.json').read_text())['binaries']
    selected={k:v for k,v in specs.items() if re.search(args.select,k)}
    if not selected:raise RuntimeError('no matching executables')
    cxx=shutil.which(args.cxx) or shutil.which('clang++')
    if not cxx:raise RuntimeError('Clang 19 is required')
    version=subprocess.check_output([cxx,'--version'],text=True)
    toolchain={'command':cxx,'executable':str(Path(cxx).resolve()),'executable_sha256':sha256(Path(cxx).resolve()),'version':version}
    lld=shutil.which('ld.lld-19') or shutil.which('ld.lld') or str(ROOT/'tools/llvm/usr/lib/llvm-19/bin/ld.lld')
    if not Path(lld).exists():raise RuntimeError('LLD 19 is required')
    work=ROOT/'.build';(work/'objects').mkdir(parents=True,exist_ok=True);(work/'receipts').mkdir(exist_ok=True)
    tasks={};links={};started=time.time();completed=[];reference_inputs={}
    for name,spec in selected.items():
        keys=[]
        for unit in spec['objects']:
            payload={'source':expand(unit['source']),'flags':[expand(f) for f in unit['flags']]}
            if any('profile-instr' in f or 'profile-use' in f for f in payload['flags']):raise RuntimeError('PGO is disabled')
            key=hashlib.sha256(json.dumps(payload,sort_keys=True).encode()).hexdigest()[:24]
            task=tasks.setdefault(key,{**unit,**payload,'key':key,'object':str(work/'objects'/(key+'.o'))})
            task['reference']=task.get('reference',False) or unit.get('reference',False);keys.append(key)
        links[name]={'keys':keys,'spec':spec}
    def compile_one(task):
        begin=time.monotonic()
        if args.rebuild:Path(task['object']).unlink(missing_ok=True)
        receipt,built=compile_object(cxx,task['flags'],toolchain,task['source'],task['object'],ROOT)
        row={'key':task['key'],'source':task['source'],'seconds':time.monotonic()-begin,'compiled':built,'sha256':receipt['object_sha256']}
        print('CXX',Path(task['source']).name,round(row['seconds'],2),flush=True)
        return row,receipt['inputs'] if task.get('reference') else {}
    jobs=min(args.jobs,len(cpus));budget=min(args.memory_gib,memory-10)
    pending=sorted(tasks.values(),key=lambda t:-float(t.get('memory_gib',2)))
    active={};used=0;errors=[]
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
        while pending or active:
            while len(active)<jobs:
                index=next((i for i,t in enumerate(pending) if used+float(t.get('memory_gib',2))<=budget),None)
                if index is None:break
                task=pending.pop(index);weight=float(task.get('memory_gib',2));used+=weight
                active[pool.submit(compile_one,task)]=weight
            if not active:raise RuntimeError('compilation memory budget is too small')
            done,_=concurrent.futures.wait(active,return_when=concurrent.futures.FIRST_COMPLETED)
            for future in done:
                used-=active.pop(future)
                try:
                    row,inputs=future.result();completed.append(row)
                    for path,digest in inputs.items():
                        path=str(Path(path).resolve())
                        if path in reference_inputs and reference_inputs[path]!=digest:raise RuntimeError('reference input changed between objects: '+path)
                        reference_inputs[path]=digest
                except Exception as error:
                    errors.append(str(error));print('CXX FAILED',error,flush=True)
    if errors:raise RuntimeError('\n'.join(errors))
    audit=enforce_reference_inputs(sorted(reference_inputs))
    if audit['files']!=reference_inputs:raise RuntimeError('reference inputs changed before linking')
    def link_one(item):
        name,entry=item;spec=entry['spec'];dest=ROOT/spec['output'];dest.parent.mkdir(parents=True,exist_ok=True)
        flags=[expand(f) for f in spec['link_flags']]
        flags=[('-fuse-ld='+lld) if f=='-fuse-ld=lld' else f for f in flags]
        if any(f.startswith('-flto') for f in flags):flags+=['-Wl,--threads=2,--thinlto-jobs=2']
        command=[cxx,*[tasks[k]['object'] for k in entry['keys']],*flags,*[expand(x) for x in spec['libraries']],'-o',str(dest)]
        begin=time.monotonic()
        with (work/(name+'-link.log')).open('w') as log:subprocess.run(command,cwd=ROOT,stdout=log,stderr=subprocess.STDOUT,check=True)
        subprocess.run(['strip','--strip-debug',str(dest)],check=True)
        receipt={'binary':str(dest.relative_to(ROOT)),'binary_sha256':sha256(dest),'compiler':toolchain,'command':command,
                 'link_seconds':time.monotonic()-begin,'objects':entry['keys'],'march':'icelake-server','pgo':False}
        write_json(work/'receipts'/(name+'.json'),receipt);print('LINK',name,flush=True);return receipt
    with concurrent.futures.ThreadPoolExecutor(max_workers=min(4,max(1,jobs//2))) as pool:
        binaries=list(pool.map(link_one,links.items()))
    result={'status':'pass','started':started,'finished':time.time(),'socket':SOCKET,'nodes':[NUMA_NODE],'cpus':cpus,
            'jobs':jobs,'memory_budget_gib':budget,'compile':completed,'binaries':binaries}
    write_json(work/'build-results.json',result)

if __name__=='__main__':main()
