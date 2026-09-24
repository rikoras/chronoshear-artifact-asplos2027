"""Content-addressed, per-translation-unit build receipts.

A dependency scan precedes a compile, so a receipt never claims that an object
was built from headers merely hashed after compilation. Existing objects without
this evidence are rebuilt once. Nothing here changes compilation flags.
"""
import hashlib
import json
import os
from pathlib import Path
import shlex
import subprocess
import threading


def sha256(path):
    with Path(path).open('rb') as stream:
        digest = hashlib.sha256()
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
        return digest.hexdigest()


def dependencies(depfile, cwd):
    text = Path(depfile).read_text().replace('\\\n', '')
    if ':' not in text:
        raise ValueError('missing dependency target: ' + str(depfile))
    names = shlex.split(text.split(':', 1)[1])
    return sorted({str((Path(cwd) / name).absolute()) for name in names})


def hashes(paths):
    return {str(path): sha256(path) for path in sorted(set(paths))}


def write_json(path, value):
    path = Path(path)
    temporary = path.with_name(path.name + '.tmp')
    temporary.write_text(json.dumps(value, indent=2, sort_keys=True) + '\n')
    os.replace(temporary, path)


def verify_inputs(receipt):
    for path, expected in receipt['inputs'].items():
        if not Path(path).is_file() or sha256(path) != expected:
            raise RuntimeError('build input changed: ' + path)


def snapshot_inputs(inputs, directory, root, extra_paths=()):
    directory, root = Path(directory), Path(root).resolve()
    extra_paths = {str(Path(p).resolve()) for p in extra_paths}
    directory.mkdir(parents=True, exist_ok=True)
    saved = {}
    for name, digest in inputs.items():
        path = Path(name)
        if str(path.resolve()) not in extra_paths and not path.resolve().is_relative_to(root):
            continue
        destination = directory / digest
        if not destination.exists() or sha256(destination) != digest:
            payload = path.read_bytes()
            if hashlib.sha256(payload).hexdigest() != digest:
                raise RuntimeError('input changed before snapshot: ' + name)
            temporary = directory / f'{digest}.tmp-{os.getpid()}-{threading.get_ident()}'
            temporary.write_bytes(payload)
            os.replace(temporary, destination)
        saved[name] = digest
    return saved


def compile_object(compiler, flags, toolchain, source, obj, cwd, snapshot_directory=None, snapshot_root=None, extra_inputs=()):
    source, obj, cwd = Path(source), Path(obj), Path(cwd)
    dep = obj.with_suffix('.d')
    receipt_path = obj.with_suffix('.receipt.json')
    identity = {'compiler': toolchain, 'flags': list(flags), 'source': str(source),
                'cwd': str(cwd)}
    extra_inputs = {str(Path(p).resolve()) for p in extra_inputs}
    if extra_inputs: identity['extra_inputs'] = sorted(extra_inputs)
    try:
        receipt = json.loads(receipt_path.read_text())
        if (receipt['schema'] == 1 and receipt['identity'] == identity and
                receipt['object_sha256'] == sha256(obj) and
                (set(dependencies(dep, cwd)) | extra_inputs) == set(receipt['inputs'])):
            verify_inputs(receipt)
            if snapshot_directory is not None:
                receipt['input_blobs'] = snapshot_inputs(receipt['inputs'], snapshot_directory, snapshot_root or cwd, extra_inputs)
                receipt['snapshot_directory'] = str(snapshot_directory)
                write_json(receipt_path, receipt)
            return receipt, False
    except (OSError, ValueError, KeyError, RuntimeError):
        pass

    obj.parent.mkdir(parents=True, exist_ok=True)
    scan = obj.with_suffix('.scan.d')
    candidate = obj.with_suffix('.candidate.o')
    candidate_dep = obj.with_suffix('.candidate.d')
    log = obj.with_suffix('.log')
    # -M (not -MM) retains -isystem inputs such as FESVR and SoftFloat.
    with log.open('w') as output:
        command = [compiler, *flags, '-M', '-MT', str(obj), '-MF', str(scan), str(source)]
        result = subprocess.run(command, cwd=cwd, stdout=output, stderr=subprocess.STDOUT)
        if result.returncode:
            raise RuntimeError('dependency scan failed: ' + str(log))
        before = hashes(set(dependencies(scan, cwd)) | extra_inputs)
        blobs = snapshot_inputs(before, snapshot_directory, snapshot_root or cwd, extra_inputs) if snapshot_directory is not None else {}
        command = [compiler, *flags, '-MD', '-MT', str(obj), '-MF', str(candidate_dep),
                   '-c', str(source), '-o', str(candidate)]
        result = subprocess.run(command, cwd=cwd, stdout=output, stderr=subprocess.STDOUT)
        if result.returncode:
            raise RuntimeError('compile failed: ' + str(log))
    after = hashes(set(dependencies(candidate_dep, cwd)) | extra_inputs)
    if before != after:
        raise RuntimeError('inputs changed during compilation; candidate not accepted: ' + str(source))
    receipt = {'schema': 1, 'identity': identity, 'command': command,
               'inputs': before, 'object_sha256': sha256(candidate)}
    if snapshot_directory is not None:
        receipt['input_blobs'] = blobs
        receipt['snapshot_directory'] = str(snapshot_directory)
    os.replace(candidate, obj)
    os.replace(candidate_dep, dep)
    write_json(receipt_path, receipt)
    return receipt, True
