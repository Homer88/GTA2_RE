import re, sys, io

SRC = r'C:\work\GTA2_RE\dump\IDA\gta2.exe.h'
lines = io.open(SRC, 'r', encoding='utf-8', errors='replace').read().split('\n')

hdr = re.compile(r'^(struct|enum)\s+((?:__fixed\s+|__udec\s+|__dec\s+)?)([A-Za-z_][A-Za-z0-9_]*)\s*(?::\s*(__int16|__int32|unsigned\s+__int8|unsigned\s+__int16))?\s*$')

defs = {}
i = 0
n = len(lines)
while i < n:
    m = hdr.match(lines[i].strip())
    if not m:
        i += 1
        continue
    kind, base, name, eb = m.group(1), (m.group(2) or '').strip(), m.group(3), m.group(4)
    k = i + 1
    while k < n and k < i + 4 and lines[k].strip() == '':
        k += 1
    if k >= n or lines[k].strip() != '{':
        i += 1
        continue
    depth = 0
    j = k
    body = []
    while j < n:
        s = lines[j]
        depth += s.count('{') - s.count('}')
        if j > k:
            body.append(s)
        if depth == 0:
            break
        j += 1
    if name not in defs:
        defs[name] = (kind, (eb or '').strip(), body)
    i = j + 1

cache = {}

def split_arr(t):
    m = re.match(r'^(.*?)\[(\d+)\]$', t.strip())
    if m:
        return m.group(1).strip(), int(m.group(2))
    return t.strip(), 1

def align_up(x, a):
    if a <= 1:
        return x
    return (x + a - 1) // a * a

PRIM = {
    'char': 1, 'byte': 1, 'bool': 1, '_BYTE': 1, 'unsigned __int8': 1, '__int8': 1,
    '__int16': 2, 'unsigned __int16': 2, 'ushort': 2, 'short': 2, 'wchar_t': 2,
    'int': 4, 'unsigned': 4, 'unsigned int': 4, '__int32': 4, 'float': 4,
    '__int64': 8, 'double': 8,
}

def size_of(t):
    base, cnt = split_arr(t.strip().rstrip(';').strip())
    return elem_size(base) * cnt

def elem_size(t):
    t = t.strip()
    if t in cache:
        return cache[t]
    if t in PRIM:
        cache[t] = PRIM[t]
        return PRIM[t]
    if t.endswith('*'):
        cache[t] = 4
        return 4
    if t in defs:
        kind, b, body = defs[t]
        if kind == 'enum':
            if b and '__int16' in b:
                sz = 2
            elif b and '__int8' in b:
                sz = 1
            else:
                sz = 4
            cache[t] = sz
            return sz
        sz = layout(body)[0]
        cache[t] = sz
        return sz
    cache[t] = 4
    return 4

def elem_align(t):
    t = t.strip()
    base, _ = split_arr(t)
    return min(elem_size(base), 4) if elem_size(base) else 1

def layout(body):
    off = 0
    maxa = 1
    fields = []
    for raw in body:
        line = raw.strip()
        if not line or line.startswith('/*') or line.startswith('//'):
            continue
        forced = None
        m = re.match(r'^__declspec\(align\((\d+)\)\)\s*(.+)$', line)
        if m:
            forced = int(m.group(1))
            line = m.group(2).strip()
        if not line.endswith(';'):
            continue
        s = line[:-1].strip()
        cnt = 1
        m2 = re.search(r'\[(\d+)\]$', s)
        if m2:
            cnt = int(m2.group(1))
            s = s[:m2.start()].strip()
        m3 = re.search(r'(\w+)$', s)
        if not m3:
            continue
        name = m3.group(1)
        base = s[:m3.start()].strip()
        if '*' in base:
            base = base.replace(' ', '')
        if not base:
            continue
        esz = elem_size(base) * cnt
        ea = forced if forced else elem_align(base)
        off = align_up(off, ea)
        maxa = max(maxa, ea)
        fields.append((off, name, base, cnt, esz))
        off += esz
    return align_up(off, maxa), fields

def show(name):
    sz, fields = layout(defs[name][2])
    print('=== %s  size = 0x%X (%d bytes) ===' % (name, sz, sz))
    print('%-7s %-6s %-26s %s' % ('OFF', 'HEX', 'TYPE', 'FIELD'))
    for off, fname, base, cnt, esz in fields:
        t = '%s[%d]' % (base, cnt) if cnt > 1 else base
        print('%-7d 0x%-5X %-26s %s' % (off, off, t, fname))
    print()

TARGETS = sys.argv[1:] or ['Player', 'PlayerStats', 'Weapon', 'S103', 'S104', 'Gangs', 'Gang',
                           'Tango', 'S131', 'CameraOrPhysics', 'cameraPosTarget']
for name in TARGETS:
    if name in defs:
        show(name)
    else:
        print('=== %s NOT FOUND ===' % name)
