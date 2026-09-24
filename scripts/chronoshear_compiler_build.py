#!/usr/bin/env python3
"""Rebuild the ChronoShear compiler using the bundled Scala dependencies."""
from pathlib import Path
import os,shutil,subprocess,time
from chronoshear_machine import binding,host_lock
ROOT=Path(__file__).resolve().parents[1]

def build():
    work=ROOT/'.build/compiler';classes=work/'classes'
    if classes.exists():shutil.rmtree(classes)
    classes.mkdir(parents=True,exist_ok=True)
    sources=sorted(p for p in (ROOT/'source/compiler/src/main').rglob('*.scala') if 'disabled' not in p.name)
    args=work/'sources.txt';args.write_text(''.join('"'+str(p)+'"\n' for p in sources))
    compiler_cp=os.pathsep.join(map(str,sorted((ROOT/'deps/scala').glob('*.jar'))))
    command=[*binding(),'java','-XX:ActiveProcessorCount=4','-Xmx6G','-Xss16M','-cp',compiler_cp,
             'scala.tools.nsc.Main','-classpath',str(ROOT/'deps/compiler-libraries.jar'),'-d',str(classes),'@'+str(args)]
    start=time.monotonic()
    subprocess.run(command,check=True)
    resources=ROOT/'source/compiler/src/main/resources'
    if resources.exists():shutil.copytree(resources,classes,dirs_exist_ok=True)
    subprocess.run(['jar','cf',str(ROOT/'tools/chronoshear.jar'),'-C',str(classes),'.'],check=True)
    print('Compiler build: %.2f seconds'%(time.monotonic()-start))

if __name__=='__main__':
    with host_lock():build()
