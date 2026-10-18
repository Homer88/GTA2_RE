"""Independently verify the binary `ret N` for the 11 Car hooks the generator
corrected (decompiler value disagreed with the binary).

Method: from each function entry, do a breadth-first walk over actual control
flow (following every unconditional/conditional branch target and fallthrough
until a `ret` is reached). This is a genuinely different algorithm from the
generator's linear byte scan, so agreement is real evidence, not a re-run of
the same code. A correct `ret N` must be uniform across every reachable path
of one function (mismatched cleanup would corrupt the caller's stack), so the
single value found per address is authoritative.
"""
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

EXE = r'C:\games\gta2\gta2.exe'
IMAGEBASE = 0x3F0000

TARGETS = [
    (0x41F730, 'decomp=0  bin=1'),
    (0x41FBB0, 'decomp=1  bin=0'),
    (0x420950, 'decomp=1  bin=4'),
    (0x421680, 'decomp=1  bin=0'),
    (0x422500, 'decomp=1  bin=3'),
    (0x4234A0, 'decomp=2  bin=1'),
    (0x423B80, 'decomp=1  bin=0'),
    (0x426F60, 'decomp=1  bin=0'),
    (0x429FF0, 'decomp=2  bin=4'),
    (0x42C030, 'decomp=1  bin=0'),
    (0x49EFE0, 'decomp=1  bin=0'),
]

md = Cs(CS_ARCH_X86, CS_MODE_32)
with open(EXE, 'rb') as f:
    exe = f.read()


def reachable_rets(start, budget=4000):
    """All distinct `ret N` byte counts reachable from *start*."""
    seen = set()
    queue = [start]
    rets = set()
    while queue and len(seen) < budget:
        a = queue.pop()
        if a in seen:
            continue
        seen.add(a)
        off = a - IMAGEBASE
        insns = list(md.disasm(exe[off:off + 16], a))
        if not insns:
            continue
        i = insns[0]
        if i.mnemonic == 'ret':
            op = i.op_str.strip()
            n = int(op, 16) if op.startswith('0x') else (int(op) if op else 0)
            rets.add(n)
            continue
        if i.mnemonic == 'jmp':
            if i.op_str.startswith('0x'):
                queue.append(int(i.op_str, 16))
            continue
        if i.mnemonic.startswith('j') or i.mnemonic.startswith('loop'):
            if i.op_str.startswith('0x'):
                queue.append(int(i.op_str, 16))
            queue.append(i.address + i.size)
            continue
        if i.mnemonic in ('retf', 'retn'):
            rets.add(-1)
            continue
        queue.append(i.address + i.size)
    return rets


ok = 0
for addr, note in TARGETS:
    bin_slots = int(note.split('bin=')[1])
    rets = sorted(reachable_rets(addr))
    slots = {r // 4 if r >= 0 and r % 4 == 0 else r for r in rets}
    match = slots == {bin_slots}
    if match:
        ok += 1
    print('0x%06X %-16s reachable rets=%-6s slots=%-6s bin=%-2d %s'
          % (addr, note, rets, sorted(slots), bin_slots,
             'OK' if match else 'MISMATCH'))
print('%d/%d verified' % (ok, len(TARGETS)))
