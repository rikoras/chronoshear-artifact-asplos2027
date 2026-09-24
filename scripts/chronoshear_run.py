#!/usr/bin/env python3
"""Run the selected online experiments on the configured physical cores."""
from pathlib import Path
import argparse,csv,json,os,re,shlex,subprocess,sys,time
from chronoshear_machine import PHYSICAL_CPUS,binding,host_lock
ROOT=Path(__file__).resolve().parents[1]
MISMATCH_FIELDS=['oracle_mismatch_signals','oracle_checked_signals','oracle_mismatch_raw_events']

def mismatch_statistics(text):
    def last(pattern,source=text):
        matches=re.findall(pattern,source);return matches[-1] if matches else ''
    summaries='\n'.join(re.findall(r'(?m)^(?:LIVE_SIDECAR_(?:COMPLETED|OK)|MODEL_VALIDATION|ROCKET_NATIVE_LIVE)\b[^\n]*',text))
    distinct=last(r'(?<!\w)oracle_mismatch_signals=(\d+)',summaries)
    checked=last(r'(?<!\w)oracle_checked_signals=(\d+)',summaries)
    raw=last(r'(?m)^ORACLE_MISMATCH_DETAIL[ \t]+raw_events=(\d+)[ \t]*$')
    if not raw:
        ordinary='\n'.join(line for line in text.splitlines() if not line.startswith('LIVE_PARTITION '))
        raw=last(r'(?<!\w)oracle_mismatches=(\d+)',ordinary)
    if not distinct and raw=='0':distinct='0'
    return dict(zip(MISMATCH_FIELDS,[distinct,checked,raw]))

def normalize_sample(row):
    row=dict(row)
    if not row.get('oracle_mismatch_raw_events'):
        row['oracle_mismatch_raw_events']=row.get('oracle_mismatches','')
    if not row.get('oracle_mismatch_signals') and str(row['oracle_mismatch_raw_events'])=='0':
        row['oracle_mismatch_signals']='0'
    for field in MISMATCH_FIELDS:row.setdefault(field,'')
    return row

def write_samples(path,rows,fields=()):
    rows=[normalize_sample(row) for row in rows]
    names=list(dict.fromkeys([*fields,*(key for row in rows for key in row),*MISMATCH_FIELDS]))
    if 'oracle_mismatches' in names:
        for row in rows:row['oracle_mismatches']=row['oracle_mismatch_raw_events']
    with path.open('w',newline='') as f:
        writer=csv.DictWriter(f,fieldnames=names);writer.writeheader();writer.writerows(rows)

def signal_summary(row):
    signals=row.get('oracle_mismatch_signals','');checked=row.get('oracle_checked_signals','')
    if signals!='':return ' differing_signals='+str(signals)+('/'+str(checked) if checked!='' else '')
    return ' differing_signals=unknown' if row.get('oracle_mismatch_raw_events','')!='' else ''

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--experiment',default='main',choices=['main','width','threads'])
    ap.add_argument('--dut');ap.add_argument('--select',default='.')
    ap.add_argument('--output',type=Path);ap.add_argument('--repetitions',type=int,default=1)
    a=ap.parse_args();cpus=list(PHYSICAL_CPUS)
    out=(a.output or ROOT/'results'/a.experiment).resolve();out.mkdir(parents=True,exist_ok=True)
    cases=json.loads((ROOT/'EXPERIMENTS.json').read_text())['cases']
    main_ids={c['id'] for c in cases if c['experiment']=='main' and c['simulator']=='chronoshear'}
    cases=[c for c in cases if c['experiment']==a.experiment and (not a.dut or c['dut']==a.dut) and re.search(a.select,c['id'])]
    if not cases:raise SystemExit('No matching experiments')
    values={'ROOT':str(ROOT),'OUTPUT':str(out),'PYTHON':sys.executable,**{'CPU'+str(i):str(cpu) for i,cpu in enumerate(cpus)}}
    def expand(s):return re.sub(r'\$\{(\w+)\}',lambda m:values[m[1]],s)
    failed=False
    with host_lock():
        reference_duts=sorted({c['dut'] for c in cases if c['experiment']=='main' and c['simulator']=='chronoshear' and c['dut'] in ['rocket','boom-small','boom-medium','boom-large']})
        if reference_duts:
            from chronoshear_reference_check import run_checks
            run_checks(reference_duts,out/'reference')
        selected={(c['experiment'],c['id']) for c in cases}
        main_duts={c['dut'] for c in cases if c['experiment']=='main'}
        samples=out/'samples.csv'
        if samples.exists():
            with samples.open() as f:
                reader=csv.DictReader(f);fields=reader.fieldnames;prior=list(reader)
            prior=[r for r in prior if (r['experiment'],r['id']) not in selected and not
                   (r['experiment']=='main' and r['simulator']=='chronoshear' and
                    r['dut'] in main_duts and r['id'] not in main_ids)]
            write_samples(samples,prior,fields)
        for c in cases:
            mask=cpus[:c['cores']]
            if len(mask)!=c['cores']:raise SystemExit('Not enough physical cores in chronoshear_machine.py')
            cmd=[*binding(c['cores']),*[expand(s) for s in c['command']]]
            env={**os.environ,**{k:expand(v) for k,v in c.get('env',{}).items()}}
            for rep in range(a.repetitions):
                stem=c['id']+'-'+str(rep+1);log=out/(stem+'.log')
                print('RUN '+stem,flush=True);started=time.time()
                with log.open('w') as f:
                    f.write('COMMAND '+shlex.join(cmd)+'\n')
                    for key in c.get('env',{}):f.write(key+'='+env[key]+'\n')
                    f.flush()
                    try:
                        result=subprocess.run(cmd,cwd=ROOT,env=env,stdout=f,stderr=subprocess.STDOUT,timeout=1200)
                        code=result.returncode
                    except subprocess.TimeoutExpired:code=124
                text=log.read_text(errors='replace');matches=re.findall(c['ns_pattern'],text)
                missing=[p for p in c['accept'] if not re.search(p,text)]
                ns=float(matches[-1]) if matches else None
                ok=code==0 and not missing and ns is not None and ns>0
                row={k:c.get(k,'') for k in ['id','dut','experiment','simulator','width','cores','rtl_cores','timing_scope']}
                row.update(status='pass' if ok else 'fail',returncode=code,missing='; '.join(missing),
                           cpus=','.join(map(str,mask)),elapsed_seconds=time.time()-started,sample=rep+1,
                           ns_per_cycle=ns,throughput_khz=1e6/ns if ok else None,log=log.name)
                row.update(mismatch_statistics(text))
                for label,pattern in [('reference_active_ns',r'producer_ns_per_cycle=([0-9.]+)'),
                                      ('rtl_active_ns',r'consumer_ns_per_cycle=([0-9.]+)'),
                                      ('reference_wait_ns',r'(?:consumer_wait|wait_source)_ns_per_cycle=([0-9.]+)')]:
                    m=re.findall(pattern,text);row[label]=m[-1] if m else ''
                samples=out/'samples.csv';prior=[];fields=[]
                if samples.exists():
                    with samples.open() as f:
                        reader=csv.DictReader(f);fields=reader.fieldnames;prior=list(reader)
                prior=[r for r in prior if (r['experiment'],r['id'],r['sample'])!=(row['experiment'],row['id'],str(row['sample']))]
                write_samples(samples,[*prior,row],fields)
                print(('PASS '+stem+' %.3f kHz'%row['throughput_khz']+signal_summary(row)) if ok else ('FAIL '+stem+'; see '+str(log)),flush=True)
                failed|=not ok
    return int(failed)

if __name__=='__main__':raise SystemExit(main())
