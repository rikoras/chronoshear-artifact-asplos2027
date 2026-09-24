"""Create backend recipes for the generated window variants."""
from pathlib import Path
import copy,json,re
ROOT=Path(__file__).resolve().parents[1]

def refresh():
    path=ROOT/'BUILD.json';data=json.loads(path.read_text());templates=data['templates']
    binaries={k:v for k,v in data['binaries'].items() if not k.startswith('chronoshear-') or v.get('kind')=='architecture'}
    for dut,template in templates.items():
        partitioned=dut.endswith('-mt');design=dut.removesuffix('-mt')
        base_width=32 if design in ['aes','matmul','sodor','rocket','boom-small'] else 16
        base_variant=('mt6-' if partitioned else '')+'w'+str(base_width)
        old='generated/'+design+'/'+base_variant
        for width in ([16] if partitioned else data['designs'][design]['widths']):
            variant=('mt6-' if partitioned else '')+'w'+str(width);new='generated/'+design+'/'+variant
            name='chronoshear-'+design+'-'+variant
            spec=json.loads(json.dumps(template).replace(old,new))
            spec.update(output='bin/'+name,dut=design,variant=variant,kind='chronoshear')
            for unit in spec['objects']:
                unit['flags']=[re.sub(r'^(-D(?:CHISA_CONSUMER_WIDTH|WIDTH))=\d+$',lambda m:m[1]+'='+str(width),f) for f in unit['flags']]
                unit['flags']=[f for f in unit['flags'] if not f.startswith('-DCHISA_PARTITION_DELIVERY_HEADER=')]
                if design=='boom-small':unit['flags'].append('-DCHISA_SMALL_WIDTH_VARIANT=1')
                unit['memory_gib']=.5 if unit['reference'] else (6 if design=='boom-small' else 2)
            if design in ['boom-medium','boom-large']:
                kernel=next(o for o in spec['objects'] if Path(o['source']).name in ['kernel_forward.cpp','kernel_p0_forward.cpp'])
                nonkernel=[o for o in spec['objects'] if not Path(o['source']).name.startswith('kernel_')]
                for cpp in sorted((ROOT/new).glob('kernel_*.cpp')):
                    unit=copy.deepcopy(kernel);unit['source']='${ROOT}/'+cpp.relative_to(ROOT).as_posix()
                    if cpp.name=='kernel_factory.cpp':unit['flags']=[f for f in unit['flags'] if not re.fullmatch('-O[0-3s]',f)]+['-O0']
                    unit['memory_gib']=4 if cpp.name in ['kernel_forward.cpp','kernel_reverse.cpp'] else 2
                    nonkernel.append(unit)
                spec['objects']=nonkernel
            binaries[name]=spec
    from chronoshear_verilator import recipes
    binaries.update(recipes(data))
    data['binaries']=binaries
    from chronoshear_architecture import recipes as architecture_recipes
    binaries.update(architecture_recipes(data))
    path.write_text(json.dumps(data,indent=2)+'\n')
    return data

if __name__=='__main__':refresh()
