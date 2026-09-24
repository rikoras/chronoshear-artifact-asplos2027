#!/usr/bin/env python3
"""Compile FIRRTL and generate matching online reference-model bindings."""
from pathlib import Path
import argparse,concurrent.futures,csv,json,os,re,shutil,subprocess,sys
from chronoshear_machine import binding
from chronoshear_oracle_signals import prepare as prepare_signal_counts
ROOT=Path(__file__).resolve().parents[1]
sys.path[:0]=[str(ROOT/'source/duts/boom-repcut/scripts'),str(ROOT/'source/scripts/paper_experiments')]

def run(command,**kwargs):subprocess.run(list(map(str,command)),check=True,**kwargs)

def fabric(contract,dest):
    import generate_system_bus_oracle_bindings as sbus
    import generate_periphery_bus_oracle_bindings as pbus
    entries=json.loads((contract/'oracle_manifest.json').read_text())['oracles'];selected={}
    for name,module in [('system_bus',sbus),('periphery_bus',pbus)]:
        own=[e for e in entries if e['flat'].startswith(module.PREFIX)];selected[name]=own
        (dest/(name+'_native_capture.inc')).write_text(module.native_capture_text(own,module._load_banks(contract/'register_bank_manifest.json')))
    lanes={e['traceKey']:e for e in json.loads((dest/'contract-layout.json').read_text())['oracles']}
    lines=['#pragma once','#include "record_bits.h"','namespace chisa::boom_model::wide::fields {']
    for name,own in selected.items():
        lines.append(f'inline constexpr RecordField {name}_columns[{len(own)}] = {{')
        for entry in own:
            lane=lanes[entry['traceKey']];lines.append('  {1, {{'+','.join(map(str,[lane['recordOffset'],lane['elemBytes'],lane['width'],0,0]))+'}}},')
        lines.append('};')
    lines.append('}');(dest/'cold_record_fields.h').write_text('\n'.join(lines)+'\n')
    own=selected['system_bus'];idx=lambda key:next(i for i,e in enumerate(own) if e['traceKey']==key)
    (dest/'cold_contract.h').write_text('#pragma once\n#include <cstddef>\nnamespace chisa::boom_system::cold_contract {\n'+f'inline constexpr std::size_t sbus_count={len(own)}, pbus_count={len(selected["periphery_bus"])};\n'+f'inline constexpr std::size_t sbus_readys={idx("ldut_subsystem_sbus_system_bus_xbar_readys_mask")}, sbus_state1={idx("ldut_subsystem_sbus_system_bus_xbar_state__1")};\n}}\n')

def emit(dut,width,partitioned=False):
    config=json.loads((ROOT/'BUILD.json').read_text())['designs'][dut]
    variant=('mt6-' if partitioned else '')+'w'+str(width);inp=ROOT/'inputs'/dut
    output=ROOT/'generated'/dut/variant;work=ROOT/'.build/emission'/dut/variant
    work.mkdir(parents=True,exist_ok=True);output.mkdir(parents=True,exist_ok=True)
    fir=work/'design.fir';shutil.copy2(inp/'design.fir',fir)
    if (inp/'design.anno.json').exists():shutil.copy2(inp/'design.anno.json',work/'design.anno.json')
    env={k:v for k,v in os.environ.items() if not k.startswith('V2_') and k not in ['JAVA_TOOL_OPTIONS','ORACLE_FREEZE','FUSE_CAP','SCRATCH_MODE']}
    env.update({k:v.replace('${INPUT}',str(inp)) for k,v in config['environment'].items()})
    if partitioned:env['V2_PARTITION_FILE']=str(inp/'partitions.txt')
    cp=str(ROOT/'tools/chronoshear.jar')+os.pathsep+str(ROOT/'deps/compiler-libraries.jar')
    args=['java','-XX:ActiveProcessorCount=1','-Xmx8G','-Xss16M','-cp',cp,'essent.Driver','--simd-v2','--width',str(width),'--simd-v2-fuse-cap','32',
          '--simd-v2-member-scratch' if partitioned else '--simd-v2-static-scratch',*config['arguments'],str(fir)]
    with (work/'emit.log').open('w') as log:run([*binding(),*args],env=env,cwd=work,stdout=log,stderr=subprocess.STDOUT)
    manifest=json.loads((work/'oracle_manifest.json').read_text());top=config['top'];header=work/(top+'.h')
    expected=inp/('oracle_contract_mt6.csv' if partitioned else 'oracle_contract.csv')
    if expected.exists():
        with expected.open() as f:rows=list(csv.DictReader(f))
        identity=lambda rows:{(e['traceKey'],int(e['width']),e['kind']) for e in rows}
        if identity(rows)!=identity(manifest['oracles']):raise RuntimeError('Oracle contract changed: '+dut+' '+variant)
    ref=output/'reference_model';ref.mkdir(exist_ok=True)
    if dut in ['boom-medium','boom-large']:
        from generate_record_layout import generate
        from generate_system_oracle_writer import render_header
        baseline=None
        if partitioned:
            baseline=ROOT/'.build/emission/boom-large/w16/oracle_manifest.json'
            if not baseline.exists():raise RuntimeError('Generate boom-large W16 before its partitioned variant')
        generate(work/'oracle_manifest.json',ref,dut.removeprefix('boom-'),config['geometry'],baseline)
        run([sys.executable,ROOT/'source/duts/boom-repcut/scripts/generate_record_fields.py','--output',ref,'--banks',work/'register_bank_manifest.json'])
        (ref/'native_system_oracle_writer.inc').write_text(render_header(manifest,manifest['oracles'],width))
        run([sys.executable,ROOT/'source/duts/boom-repcut/scripts/generate_system_probes.py','--manifest',work/'oracle_manifest.json','--output',ref/'system_probe_registry.inc'])
        fabric(work,ref)
    elif dut=='boom-small':
        from generate_small_oracle_additions import generate
        from generate_system_oracle_writer import render_header
        data=[json.loads((inp/'base_oracles.json').read_text()),manifest,json.loads((work/'state_array_manifest.json').read_text()),json.loads((work/'register_bank_manifest.json').read_text())]
        base=data[0]
        for entry in base['oracles']:entry['blockOffset']=entry['blockOffset']*width//4
        base['blockBytes']=base['blockBytes']*width//4
        additions,profile,_=generate(*data,width)
        (ref/'small_additional_oracles.h').write_text(additions);(ref/'dram_access_profile.inc').write_text(profile)
        (ref/'small_system_oracle_writer.inc').write_text(render_header(base,base['oracles'],width))
    if dut.startswith('boom-') or dut=='rocket':
        from prepare_oracle_report_only import prepare
        policy=work/'checked';prepare(header,policy,fast_count=True,direct_count=dut in ['boom-medium','boom-large'] and not partitioned)
        prepare_signal_counts(policy/header.name)
        if dut in ['boom-medium','boom-large']:
            from split_partition_kernel import split
            # Remove former kernel units if a compiler update changes their count.
            for p in output.glob('kernel_*.cpp'):p.unlink()
            split(policy/header.name,output,cooperative_poll=partitioned,poll_bytes=32768 if partitioned else 0)
        else:shutil.copy2(policy/header.name,output/header.name)
    else:
        shutil.copy2(header,output/header.name)
        if dut!='matmul':prepare_signal_counts(output/header.name)
    for p in work.glob('*.inc'):shutil.copy2(p,output/p.name)
    if dut=='aes':
        from aes_live_layout import generate
        generate(work/'oracle_manifest.json',width,output,100000)
    elif dut=='matmul':
        if manifest['oracles']:raise RuntimeError('MatMul should not require oracles')
        (output/'oracle_data.h').write_text('#pragma once\nconstexpr int ORACLE_NUM_CYCLES=0, ORACLE_ARRAY_LEN=0, ORACLE_NUM_ARRAYS=0;\ninline bool oracle_load(const char*) { return true; }\ninline void oracle_unload() {}\n')
    elif dut=='sodor':
        run([sys.executable,ROOT/'source/duts/sodor-fullchip/flow/gen_sidecar_writer.py','--manifest',work/'oracle_manifest.json','--top-h',output/'SodorFullChip.h','--output',output/'sidecar_writer_gen.inc','--shim-dir',output,'--width',width,'--allow-mapping-subset'])
    elif dut=='rocket':
        (output/'oracle_data.h').write_text('#pragma once\n#include <cstdint>\nconstexpr int ORACLE_NUM_CYCLES=1<<30, ORACLE_ARRAY_LEN=1<<30, ORACLE_STREAM_COUNT=1092;\n'+f'constexpr int64_t ORACLE_DATA_BLOCK_BYTES={manifest["blockBytes"]}LL;\nconstexpr int ORACLE_DATA_MIRRORED=1;\n#define ROCKET_CONSUMER_EXTERNAL_DRAM 1\ninline const char* oracle_kernel_base=nullptr;\n')
    else:(output/'oracle_data.h').write_text('#pragma once\n')
    for p in output.rglob('*.json'):p.unlink()
    print('EMITTED',dut,variant,flush=True)

def generate_all(duts,widths):
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        futures=[pool.submit(run,[sys.executable,__file__,'--worker','--dut',d,'--width',w]) for d in duts for w in widths]
        for f in futures:f.result()

if __name__=='__main__':
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--dut',required=True);p.add_argument('--width',type=int,default=32);p.add_argument('--partitioned',action='store_true');p.add_argument('--worker',action='store_true');a=p.parse_args()
    emit(a.dut,a.width,a.partitioned)
