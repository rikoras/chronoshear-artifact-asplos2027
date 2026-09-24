#!/usr/bin/env python3
"""Compare software reference models with original RTL, without oracle injection."""
from pathlib import Path
import argparse,csv,json,re,subprocess,time
from chronoshear_machine import binding,host_lock

ROOT=Path(__file__).resolve().parents[1]

def fields(text,prefix):
    lines=[line for line in text.splitlines() if line.startswith(prefix+' ')]
    return dict(re.findall(r'(\w+)=([^\s]+)',lines[-1])) if lines else {}

def run_checks(duts,output):
    output=Path(output).resolve();output.mkdir(parents=True,exist_ok=True)
    checks=json.loads((ROOT/'EXPERIMENTS.json').read_text())['reference_checks']
    requested=set(duts)
    selected=[check for check in checks if check['dut'] in requested]
    if {check['dut'] for check in selected}!=requested or len(selected)!=len(requested):
        raise RuntimeError('Each selected processor requires exactly one reference-model check')
    rows=[];failed=[]
    for check in selected:
        dut=check['dut']
        log=output/(dut+'.log')
        command=[s.replace('${ROOT}',str(ROOT)) for s in check['command']]
        print('REFERENCE ARCHITECTURE '+dut+': checking original RTL',flush=True)
        start=time.monotonic()
        with log.open('w') as f:
            try:
                result=subprocess.run([*binding(1),*command],cwd=ROOT,stdout=f,stderr=subprocess.STDOUT,timeout=900)
                code=result.returncode
            except subprocess.TimeoutExpired:code=124
        text=log.read_text(errors='replace')
        state=fields(text,check['summary'])
        retired=fields(text,'ROCKET_ORDERED_RETIRE') if dut=='rocket' else state
        count=retired.get('compared' if dut=='rocket' else 'compared_retirements','0')
        ok=code==0 and state.get('status')=='pass' and int(count)>0
        ok=ok and all(state.get(k)==str(v) for k,v in check['required'].items())
        if dut=='rocket':
            ok=ok and all(retired.get(k)=='0' for k in ['mismatches','model_pending','rtl_pending'])
        else:
            ok=ok and int(state.get('compared_stores','0'))>0 and int(state.get('memory_bytes','0'))>0
        row={'dut':dut,'status':'pass' if ok else 'fail','retirements':count,
             'stores':state.get('compared_stores',''),'register_scope':check['register_scope'],
             'memory_scope':check['memory_scope'],'comparison_scope':check['scope'],
             'oracle_injection':'none','elapsed_seconds':time.monotonic()-start,'log':log.name}
        rows.append(row)
        print('REFERENCE ARCHITECTURE '+dut+': '+('PASS' if ok else 'FAIL')+
              ', retirements='+count+', scope='+check['scope'],flush=True)
        if not ok:failed.append(dut)
    path=output/'summary.csv';previous=[]
    if path.exists():
        with path.open() as f:previous=list(csv.DictReader(f))
    previous=[r for r in previous if r['dut'] not in {r['dut'] for r in rows}]
    if rows:
        with path.open('w') as f:
            writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows([*previous,*rows])
    if failed:raise RuntimeError('Reference-model architecture check failed: '+', '.join(failed)+'; see '+str(output))
    return rows

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dut',choices=['rocket','boom-small','boom-medium','boom-large'])
    p.add_argument('--output',type=Path,default=ROOT/'results/reference')
    a=p.parse_args()
    with host_lock():run_checks([a.dut] if a.dut else ['rocket','boom-small','boom-medium','boom-large'],a.output)

if __name__=='__main__':main()
