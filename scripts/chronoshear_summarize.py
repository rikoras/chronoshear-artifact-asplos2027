#!/usr/bin/env python3
"""Summarize raw samples in kHz and relative to single-threaded Verilator."""
from pathlib import Path
import argparse,csv,statistics

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('directory',type=Path);a=p.parse_args()
    groups={}
    with (a.directory/'samples.csv').open() as f:
        for row in csv.DictReader(f):groups.setdefault(row['id'],[]).append(row)
    rows=[]
    for name,samples in sorted(groups.items()):
        c=samples[0];ok=all(s['status']=='pass' for s in samples)
        ns=statistics.median(float(s['ns_per_cycle']) for s in samples) if ok else None
        rows.append({k:c.get(k,'') for k in ['id','dut','experiment','simulator','width','cores','rtl_cores','timing_scope']}|
                    {'samples':len(samples),'status':'pass' if ok else 'fail','ns_per_cycle':ns,'throughput_khz':1e6/ns if ns else None})
    candidates={}
    for row in rows:
        if row['experiment']=='main' and row['simulator']=='chronoshear':
            candidates.setdefault(row['dut'],[]).append(row)
    excluded=set()
    for dut,widths in sorted(candidates.items()):
        passed=[row for row in widths if row['status']=='pass']
        if not passed:
            print(f'FAIL {dut}: no passing ChronoShear width; see samples.csv')
            continue
        best=min(passed,key=lambda row:(row['ns_per_cycle'],int(row['width'])))
        excluded.update(row['id'] for row in widths if row is not best)
        print(f"SELECT {dut}: ChronoShear W={best['width']}, {best['throughput_khz']:.3f} kHz")
    rows=[row for row in rows if row['id'] not in excluded]
    baselines={r['dut']:r['ns_per_cycle'] for r in rows if r['simulator']=='verilator-1t' and r['status']=='pass'}
    for r in rows:
        r['speedup_verilator_1t']=baselines[r['dut']]/r['ns_per_cycle'] if r['dut'] in baselines and r['ns_per_cycle'] else None
    if rows:
        with (a.directory/'summary.csv').open('w') as f:
            writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
    print(str(a.directory/'summary.csv'))

if __name__=='__main__':main()
