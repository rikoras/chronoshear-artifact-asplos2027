#!/usr/bin/env python3
"""Generate a fully unrolled 16x16 matrix multiplier with registered outputs."""
import argparse
import hashlib
import json
from pathlib import Path


def generate(out):
    out.mkdir(parents=True, exist_ok=True)
    n = 16
    lines = ['circuit FeedForwardMatMul :', '  module FeedForwardMatMul :',
             '    input clock : Clock', '    input reset : UInt<1>']
    ports = []
    for side in ('a', 'b'):
        for i in range(n * n):
            name = f'in_{side}_{i}'
            lines.append(f'    input {name} : UInt<8>')
            ports.append(f'INPUT_{side.upper()}({i}, {name})')
    for i in range(n * n):
        lines.append(f'    output out_{i} : UInt<32>')
        ports.append(f'OUTPUT({i}, out_{i})')
    registers = []
    nodes = []
    for row in range(n):
        for col in range(n):
            previous = []
            for k in range(n):
                name = f'product_{row}_{col}_{k}'
                nodes.append(f'    node {name} = pad(mul(in_a_{row*n+k}, in_b_{k*n+col}), 32)')
                previous.append(name)
            for level in range(4):
                current = []
                for i in range(len(previous) // 2):
                    name = f'sum_{level}_{row}_{col}_{i}'
                    nodes.append(f'    node {name} = tail(add({previous[2*i]}, {previous[2*i+1]}), 1)')
                    current.append(name)
                previous = current
            result = f'result_{row}_{col}'
            registers.append((result, previous[0]))
            lines.append(f'    out_{row*n+col} <= {result}')
    # Every register reads only the current inputs, through combinational logic.
    # No holds, accumulators, state machines, memories, or oracle values.
    declarations = [f'    reg {name} : UInt<32>, clock' for name, _ in registers]
    connects = [f'    {name} <= mux(reset, UInt<32>(0), {expr})' for name, expr in registers]
    # FIRRTL permits declarations before the output connects.
    split = next(i for i, line in enumerate(lines) if ' <= ' in line)
    lines[split:split] = declarations
    fir = '\n'.join(lines + nodes + connects) + '\n'
    (out / 'FeedForwardMatMul.fir').write_text(fir)
    (out / 'ports.inc').write_text('\n'.join(ports) + '\n')
    metadata = dict(top='FeedForwardMatMul', dimension=n, input_bits=8,
                    output_bits=32, max_output=n * 255 * 255,
                    latency_edges=1, initiation_interval=1, multipliers=n**3,
                    adders=n*n*(n-1), registers=len(registers), feedback_edges=0,
                    firrtl_statements=len(nodes) + 2*len(registers) + n*n,
                    firrtl_sha256=hashlib.sha256(fir.encode()).hexdigest())
    (out / 'design.json').write_text(json.dumps(metadata, indent=2) + '\n')
    print(json.dumps(metadata))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('output', type=Path)
    generate(parser.parse_args().output)
