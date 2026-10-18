"""Dump PE section table of a binary (no pefile dependency)."""
import struct
import sys

path = sys.argv[1] if len(sys.argv) > 1 else r'C:\games\gta2\gta2.exe'
data = open(path, 'rb').read()

e_lfanew = struct.unpack_from('<I', data, 0x3C)[0]
sig = data[e_lfanew:e_lfanew + 4]
coff = e_lfanew + 4
nsec, = struct.unpack_from('<H', data, coff + 2)
opthdr_size, = struct.unpack_from('<H', data, coff + 16)
opt = coff + 20
magic, = struct.unpack_from('<H', data, opt)
if magic == 0x10B:
    imagebase, = struct.unpack_from('<I', data, opt + 28)
    sec_off = opt + opthdr_size
    print('%s  PE32  imagebase=0x%08X  sections=%d' % (path, imagebase, nsec))
else:
    imagebase, = struct.unpack_from('<Q', data, opt + 24)
    sec_off = opt + opthdr_size
    print('%s  PE32+ imagebase=0x%016X  sections=%d' % (path, imagebase, nsec))

print('%-10s %8s %8s %8s %8s  %s' %
      ('name', 'vsize', 'vaddr', 'rawsz', 'rawptr', 'va-range'))
for k in range(nsec):
    o = sec_off + k * 40
    name = data[o:o + 8].rstrip(b'\0').decode('ascii', 'replace')
    vsize, vaddr, rawsz, rawptr = struct.unpack_from('<IIII', data, o + 8)
    print('%-10s 0x%06X 0x%06X 0x%06X 0x%06X  0x%08X..0x%08X'
          % (name, vsize, vaddr, rawsz, rawptr,
             imagebase + vaddr, imagebase + vaddr + vsize))

print()
for probe in (0x41F730, 0x420950, 0x49EFE0, 0x4BF000):
    rva = probe - imagebase
    for k in range(nsec):
        o = sec_off + k * 40
        vsize, vaddr, rawsz, rawptr = struct.unpack_from('<IIII', data, o + 8)
        if vaddr <= rva < vaddr + max(vsize, rawsz):
            file_off = rawptr + (rva - vaddr)
            print('VA 0x%08X -> file 0x%06X  (delta from VA-imagebase = 0x%X)'
                  % (probe, file_off, file_off - rva))
            break
