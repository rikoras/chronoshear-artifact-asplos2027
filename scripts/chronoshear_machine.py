"""Machine placement. Edit these constants when moving the artifact."""
from contextlib import contextmanager
import fcntl,os,sys
sys.dont_write_bytecode = True
SOCKET = 0
NUMA_NODE = 0
PHYSICAL_CPUS = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30]

@contextmanager
def host_lock():
    path = f'/tmp/chronoshear-socket{SOCKET}.lock'
    try:
        fd = os.open(path, os.O_RDONLY)
    except FileNotFoundError:
        try:
            fd = os.open(path, os.O_RDONLY | os.O_CREAT | os.O_EXCL, 0o444)
            os.fchmod(fd, 0o444)
        except FileExistsError:
            fd = os.open(path, os.O_RDONLY)
    with os.fdopen(fd, 'r') as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            print('Waiting for another experiment or build to finish.', flush=True)
            fcntl.flock(lock, fcntl.LOCK_EX)
        yield

def binding(count=None):
    cpus = PHYSICAL_CPUS if count is None else PHYSICAL_CPUS[:count]
    if count is not None and len(cpus) != count:
        raise RuntimeError('Not enough CPUs in chronoshear_machine.py')
    return ['numactl', '--physcpubind=' + ','.join(map(str, cpus)), '--membind=' + str(NUMA_NODE)]
