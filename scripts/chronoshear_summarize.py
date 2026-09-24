#!/usr/bin/env python3
"""Summarize raw samples in kHz and relative to single-threaded Verilator."""
from pathlib import Path
import argparse,csv,statistics

def signal_statistics(samples):
    counts=[];checked=[]
    for row in samples:
        value=row.get('oracle_mismatch_signals','')
        raw=row.get('oracle_mismatch_raw_events') or row.get('oracle_mismatches','')
        if value=='' and str(raw)=='0':value='0'
        counts.append(int(value) if value!='' else None)
        value=row.get('oracle_checked_signals','')
        checked.append(int(value) if value!='' else None)
    def interval(values):
        low,high=min(values),max(values)
        return str(low) if low==high else f'{low}-{high}'
    known=all(value is not None for value in counts)
    relevant=any(any(row.get(field,'')!='' for field in
                    ['oracle_mismatch_signals','oracle_checked_signals','oracle_mismatch_raw_events','oracle_mismatches'])
                 for row in samples)
    return {'oracle_mismatch_signals_min':min(counts) if known else '',
            'oracle_mismatch_signals_max':max(counts) if known else '',
            'oracle_mismatch_signals_per_run':interval(counts) if known else 'unknown' if relevant else '',
            'oracle_checked_signals':interval(checked) if all(value is not None for value in checked) else ''}

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
                    {'samples':len(samples),'status':'pass' if ok else 'fail','ns_per_cycle':ns,'throughput_khz':1e6/ns if ns else None}|
                    signal_statistics(samples))
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
        signals=best['oracle_mismatch_signals_per_run'];checked=best['oracle_checked_signals']
        detail=(' differing_signals_per_run='+signals+('/'+checked if checked else '')) if signals else ''
        print(f"SELECT {dut}: ChronoShear W={best['width']}, {best['throughput_khz']:.3f} kHz"+detail)
    rows=[row for row in rows if row['id'] not in excluded]
    baselines={r['dut']:r['ns_per_cycle'] for r in rows if r['simulator']=='verilator-1t' and r['status']=='pass'}
    for r in rows:
        r['speedup_verilator_1t']=baselines[r['dut']]/r['ns_per_cycle'] if r['dut'] in baselines and r['ns_per_cycle'] else None
    if rows:
        with (a.directory/'summary.csv').open('w') as f:
            writer=csv.DictWriter(f,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
    print(str(a.directory/'summary.csv'))

if __name__=='__main__':main()
