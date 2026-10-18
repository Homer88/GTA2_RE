"""Cross-check: which Car::* entry points are already detoured in dllmain.cpp.

Writes nothing; prints an overlap report.
"""
import io
import os
import re

DLL = r'C:\work\GTA2_RE\dllLoad\dllLoad'


def car_entries():
    out = []
    pat = re.compile(r'\{\s*(0x[0-9A-Fa-f]+)UL,\s*"Car::(\w+)"')
    for line in io.open(os.path.join(DLL, 'AddrToFunc.h'),
                        encoding='utf-8', errors='replace'):
        m = pat.search(line)
        if m:
            out.append((int(m.group(1), 16), m.group(2)))
    return out


def detoured_addrs():
    """Addresses named in any DetourAttach call anywhere in dllLoad."""
    addrs = set()
    names = set()
    for fn in os.listdir(DLL):
        if not fn.lower().endswith('.cpp'):
            continue
        src = io.open(os.path.join(DLL, fn), encoding='utf-8',
                      errors='replace').read()
        for m in re.finditer(r'DetourAttach\(&(\w+)', src):
            sym = m.group(1)
            names.add(sym)
            h = re.search(r'([0-9A-Fa-f]{6})$', sym)
            if h:
                addrs.add(int(h.group(1), 16) + 0x400000)
    return addrs, names


def main():
    car = car_entries()
    det, syms = detoured_addrs()
    overlap = [(a, n) for a, n in car if a in det]
    print('Car:: entries in AddrToFunc.h : %d' % len(car))
    print('detour symbols (all *.cpp)    : %d' % len(syms))
    print('resolved addresses            : %d' % len(det))
    print('OVERLAP (must skip): %d' % len(overlap))
    for a, n in overlap:
        print('   0x%06X %s' % (a, n))

    # how many Car addresses fall inside ranges already owned by other tracers
    print()
    print('Car address range: 0x%06X .. 0x%06X' % (car[0][0], car[-1][0]))


if __name__ == '__main__':
    main()
