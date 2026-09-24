#!/usr/bin/env python3
"""Estimate a baseline's interval cost from two bounded runs of the same program."""
import argparse, json, re, subprocess, sys, time
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--binary',required=True);p.add_argument('--elf',required=True)
p.add_argument('--begin',type=int,required=True);p.add_argument('--end',type=int,required=True)
a=p.parse_args();times=[]
for cycles in (a.begin,a.end):
 command=[a.binary,'--seed=1','--cycle-count',f'--max-cycles={cycles}',a.elf]
 start=time.monotonic();run=subprocess.run(command,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,text=True);elapsed=time.monotonic()-start
 print('BASELINE_INTERVAL_RUN '+json.dumps({'command':command,'returncode':run.returncode,'seconds':elapsed}),flush=True)
 print(run.stdout,flush=True)
 if not re.search(r'after\s+'+str(cycles)+r'\s+cycles',run.stdout):raise SystemExit('Baseline did not reach the requested cycle boundary')
 expected_stop=re.search(r'via trace_count \(timeout, seed \d+\) after '+str(cycles)+r' cycles',run.stdout)
 if (run.returncode!=0 and not expected_stop) or re.search(r'(segmentation fault|assertion.*failed)',run.stdout,re.I):raise SystemExit('Unexpected baseline failure')
 times.append(elapsed)
ns=(times[1]-times[0])*1e9/(a.end-a.begin)
if ns<=0:raise SystemExit('Nonpositive interval estimate')
print(f'BASELINE_INTERVAL_PASS timed_cycles={a.end-a.begin} ns_per_cycle={ns:.3f}')
