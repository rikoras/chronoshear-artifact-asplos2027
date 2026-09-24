#!/usr/bin/env python3
"""Add read-only architectural observation metadata to original BOOM Verilog."""
import argparse
from pathlib import Path
import re

GEOMETRY = {'small': (1, 52, 48, 16, 8), 'medium': (2, 80, 64, 32, 16),
            'large': (3, 100, 96, 32, 24)}
TILE = 'ldut.tile_prci_domain.tile_reset_domain.boom_tile'


def prepare(configuration, verilog, simdtm, output, root_header=None):
    commit, integer, floating, ftq, stores = GEOMETRY[configuration]
    text = verilog.read_text()
    modules = {m[1]: m[0] for m in re.finditer(r'(?ms)^module (\w+)\b.*?^endmodule\b', text)}
    paths = {'': 'TestHarness'}

    def module_at(path):
        if path in paths:
            return paths[path]
        parent, _, instance = path.rpartition('.')
        body = modules[module_at(parent)]
        match = re.search(r'(?m)^\s+(\w+)\s+' + re.escape(instance) + r'\s*\(', body)
        if not match:
            raise ValueError('No instance: ' + path)
        paths[path] = match[1]
        return match[1]

    rows, marks = [], {}

    def add(label, path, signal, bits=1, array=0, writable=False):
        module = module_at(path)
        member = 'TestHarness' + ''.join('__DOT__' + x for x in path.split('.') if x) + '__DOT__' + signal
        rows.append((label, member, bits, array))
        marks.setdefault(module, {})[signal] = writable

    for bank in range(commit):
        for label, signal, bits in [
            ('valid', 'io_commit_arch_valids', 1), ('commit', 'io_commit_valids', 1),
            ('enq', 'io_enq_valids', 1), ('rd', 'io_commit_uops_{n}_ldst', 6),
            ('rdvalid', 'io_commit_uops_{n}_ldst_val', 1), ('rdtype', 'io_commit_uops_{n}_dst_rtype', 2),
            ('pdst', 'io_commit_uops_{n}_pdst', (integer-1).bit_length()),
            ('ftq', 'io_commit_uops_{n}_ftq_idx', (ftq-1).bit_length()),
            ('pclow', 'io_commit_uops_{n}_pc_lob', 6), ('edge', 'io_commit_uops_{n}_edge_inst', 1),
            ('store', 'io_commit_uops_{n}_uses_stq', 1)]:
            signal = signal.format(n=bank) if '{n}' in signal else signal + '_' + str(bank)
            add(label + str(bank), TILE + '.core.rob', signal, bits)
    for label in ['head', 'tail']:
        add('rob_' + label, TILE + '.core.rob', 'rob_' + label, 5)
    add('debug', TILE + '.core.csr', 'reg_debug')
    add('core_clock', TILE, 'core_clock')
    add('store_head', TILE + '.lsu', 'stq_commit_head', (stores-1).bit_length())
    for i in range(ftq):
        add('ftqpc' + str(i), TILE + '.frontend.ftq', 'pcs_' + str(i), 40)
    for i in range(stores):
        for label, suffix, bits in [('address','addr_bits',40), ('data','data_bits',64),
                                    ('command','uop_mem_cmd',5), ('size','uop_mem_size',2)]:
            add('stq' + label + str(i), TILE + '.lsu', f'stq_{i}_bits_{suffix}', bits)
    for fp, count, ports in [(False, integer, commit+1), (True, floating, 2)]:
        prefix = 'floating' if fp else 'integer'
        path = TILE + ('.core.fp_pipeline.fregfile' if fp else '.core.iregfile')
        add(prefix, path, 'regfile', 65 if fp else 64, count)
        for i in range(ports):
            add(prefix+'writevalid'+str(i), path, f'io_write_ports_{i}_valid')
            add(prefix+'writeaddress'+str(i), path, f'io_write_ports_{i}_bits_addr',
                (max(integer, floating)-1).bit_length())
            add(prefix+'writedata'+str(i), path, f'io_write_ports_{i}_bits_data', 65 if fp else 64)
    for signal, bits in [('debug_req_ready',1), ('debug_resp_valid',1),
                         ('debug_resp_bits_resp',2), ('debug_resp_bits_data',32)]:
        add(signal, '', 'SimDTM_' + signal, bits)

    def instrument(body, selected):
        for signal, writable in selected.items():
            pattern = (r'(?m)^(\s*(?:input|output|inout|wire|reg|bit|int)\s+'
                       r'(?:(?:wire|reg|logic|signed)\s+)*(?:\[[^\]\n]+\]\s*)?' +
                       re.escape(signal) + r')([ \t]*(?:\[[^\]\n]+\])?)([ \t]*[,;=]|[ \t]*$)')
            attribute = 'public_flat_rw' if writable else 'public_flat_rd'
            body, count = re.subn(pattern, r'\1\2 /* verilator ' + attribute + r' */\3', body)
            if count != 1:
                raise ValueError(f'Observation {signal}: expected one declaration, got {count}')
        return body

    for module, selected in marks.items():
        text = text.replace(modules[module], instrument(modules[module], selected), 1)
    dtm_text = simdtm.read_text()
    dtm_signals = [('debug_req_valid_reg',1), ('debug_req_bits_addr_reg',7),
                   ('debug_req_bits_op_reg',2), ('debug_req_bits_data_reg',32),
                   ('debug_resp_ready_reg',1), ('exit_reg',32)]
    dtm_text = instrument(dtm_text, {name: True for name, _ in dtm_signals})
    rows += [(name, 'TestHarness__DOT__SimDTM__DOT__'+name, bits, 0) for name,bits in dtm_signals]

    output.mkdir(parents=True, exist_ok=True)
    (output/'TestHarness.v').write_text(text)
    (output/'SimDTM.v').write_text(dtm_text)
    header = root_header.read_text() if root_header else None
    lines = ['#pragma once', f'inline constexpr unsigned kCommit = {commit}, kInteger = {integer}, '
             f'kFloating = {floating}, kFtq = {ftq}, kStores = {stores};',
             'struct RtlFields {', '  VTestHarness___024root& root;']
    for label, member, bits, count in rows:
        if header:
            declaration = re.search(r'(?m)^\s*([^\n;]+)\b'+re.escape(member)+r'\s*;', header)
            if not declaration:
                raise ValueError('Generated root is missing ' + member)
            if f'/*{bits-1}:0*/' not in declaration[1]:
                raise ValueError('Generated root has unexpected width: ' + member)
            if count and not re.search(r',\s*'+str(count)+r'>', declaration[1]):
                raise ValueError('Generated root has unexpected array geometry: ' + member)
        if count:
            lines.append(f'  auto& {label}(unsigned i) const {{ return root.{member}[i]; }}')
        else:
            lines.append(f'  auto& {label}() const {{ return root.{member}; }}')
    def switch(name, label, count, wide=False):
        result = 'sfp::rec_t' if wide else 'std::uint64_t'
        lines.append(f'  {result} {name}(unsigned i) const {{ switch(i) {{')
        for i in range(count):
            value = f'{label}{i}()'
            if wide:
                value = f'(sfp::rec_t({value}[2]) << 64) | (std::uint64_t({value}[1]) << 32) | {value}[0]'
            lines.append(f'    case {i}: return {value};')
        lines.append('    default: throw std::runtime_error("architectural observation index out of range"); } }')
    for field in ['valid','commit','enq','rd','rdvalid','rdtype','pdst','ftq','pclow','edge','store']:
        switch(field, field, commit)
    switch('pc', 'ftqpc', ftq)
    for field in ['address','data','command','size']:
        switch('stq_'+field, 'stq'+field, stores)
    for fp, ports in [(False, commit+1), (True, 2)]:
        prefix = 'floating' if fp else 'integer'
        for field in ['valid','address','data']:
            switch(prefix+'_write_'+field, prefix+'write'+field, ports, fp and field=='data')
    lines.append('};')
    (output/'boom_architecture_fields.h').write_text('\n'.join(lines)+'\n')
    print(f'ARCHITECTURE_FIELDS configuration={configuration} signals={len(rows)} verified={int(header is not None)}')


if __name__ == '__main__':
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--configuration', choices=GEOMETRY, required=True)
    p.add_argument('--verilog', type=Path, required=True)
    p.add_argument('--simdtm', type=Path, required=True)
    p.add_argument('--output', type=Path, required=True)
    p.add_argument('--root-header', type=Path)
    a = p.parse_args()
    prepare(a.configuration, a.verilog, a.simdtm, a.output, a.root_header)
