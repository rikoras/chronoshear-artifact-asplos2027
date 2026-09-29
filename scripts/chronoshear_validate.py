#!/usr/bin/env python3
"""Check BOOM ChronoShear retirement and final architectural state."""
from pathlib import Path
import argparse,csv,json,os,re,subprocess
from chronoshear_machine import PHYSICAL_CPUS,binding,host_lock

ROOT=Path(__file__).resolve().parents[1]
BOOMS=('boom-small','boom-medium','boom-large')

def fields(text,prefix):
    lines=[line for line in text.splitlines() if line.startswith(prefix+' ')]
    return dict(re.findall(r'(\w+)=([^\s]+)',lines[-1])) if lines else {}

def run_checks(duts,output):
    output=Path(output).resolve();output.mkdir(parents=True,exist_ok=True)
    plan=json.loads((ROOT/'EXPERIMENTS.json').read_text())
    rows=[];failed=[]
    for dut in duts:
        case=next(c for c in plan['cases'] if c['experiment']=='main' and c['id']=='chronoshear-'+dut+'-w32')
        binary=ROOT/'bin'/('chronoshear-validate-'+dut+'-w32')
        if not binary.is_file():
            raise RuntimeError('Missing '+binary.name+'; rebuild architectural checks with chronoshear_maintenance.sh')
        values={'ROOT':str(ROOT),**{'CPU'+str(i):str(cpu) for i,cpu in enumerate(PHYSICAL_CPUS)}}
        expand=lambda s:re.sub(r'\$\{(\w+)\}',lambda m:values[m[1]],s)
        arguments=[expand(s) for s in case['command'][1:] if s!='--eval-timing' and not s.startswith(('--timing-from=','--timing-until='))]
        cmd=[*binding(case['cores']),str(binary),*arguments]
        env={**os.environ,**{k:expand(v) for k,v in case.get('env',{}).items()}}
        log=output/(dut+'.log');print('SIMULATOR ARCHITECTURE '+dut+': checking retirement and final state',flush=True)
        with log.open('w') as f:
            try:result=subprocess.run(cmd,cwd=ROOT,env=env,stdout=f,stderr=subprocess.STDOUT,timeout=1800);code=result.returncode
            except subprocess.TimeoutExpired:code=124
        text=log.read_text(errors='replace');state=fields(text,'CONSUMER_ARCHITECTURE')
        validation=fields(text,'MODEL_VALIDATION');ordered=fields(text,'ARCHITECTURE_ORDERED')
        ok=code==0 and state.get('status')=='pass' and validation.get('architecture_status')=='pass'
        ok=ok and validation.get('program_done')=='1' and validation.get('program_exit')=='0' and validation.get('boundary_mismatches')=='0'
        ok=ok and int(state.get('rtl_retired','0'))>0 and state.get('rtl_retired')==state.get('model_retired')
        ok=ok and int(state.get('rtl_stores','0'))>0 and state.get('rtl_stores')==state.get('model_stores') and int(state.get('memory_bytes','0'))>0
        ok=ok and ordered.get('compared')==state.get('rtl_retired') and all(ordered.get(k)=='0' for k in ['mismatches','model_pending','rtl_pending'])
        if any(line.startswith('LIVE_SIDECAR_TIMING ') for line in text.splitlines()):raise RuntimeError('Validation unexpectedly emitted performance timing')
        row={'dut':dut,'width':32,'status':'pass' if ok else 'fail','retirements':state.get('rtl_retired',''),
             'stores':state.get('rtl_stores',''),'memory_bytes':state.get('memory_bytes',''),
             'register_scope':state.get('register_scope',''),'memory_scope':state.get('memory_scope',''),
             'oracle_mismatch_signals':validation.get('oracle_mismatch_signals',''),'log':log.name}
        rows.append(row);print('SIMULATOR ARCHITECTURE '+dut+': '+('PASS' if ok else 'FAIL'),flush=True)
        if not ok:failed.append(dut)
    with (output/'summary.csv').open('w') as f:
        writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
    if failed:raise RuntimeError('Simulator architecture check failed: '+', '.join(failed)+'; see '+str(output))
    return rows

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--dut',choices=BOOMS);p.add_argument('--output',type=Path,default=ROOT/'results/validate')
    a=p.parse_args()
    with host_lock():run_checks([a.dut] if a.dut else BOOMS,a.output)

if __name__=='__main__':main()
