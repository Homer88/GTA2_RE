#include "StyleTileLoader.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

static StyleTileAssets gStyleTiles;

static void* AllocAligned64K(size_t size, unsigned char** outBase) {
    if (!outBase) return 0;
    *outBase = 0;
    if (size == 0) return 0;
    // NewMemory behavior: malloc(size + 0x10000), return 64K-aligned pointer.
    unsigned char* p = (unsigned char*)malloc(size + 0x10000);
    if (!p) return 0;
    *outBase = p;
    uintptr_t aligned = ((uintptr_t)p + 0xFFFFu) & ~(uintptr_t)0xFFFFu;
    return (void*)aligned;
}

static bool ReadExact(FILE* f, void* dst, size_t n) {
    return fread(dst, 1, n, f) == n;
}

static void StyleTiles_InitDefaults() {
    for (int i = 0; i < 1024; ++i) gStyleTiles.spec[i] = 1;
    for (int i = 0; i < 992; ++i) gStyleTiles.s1501[i] = (unsigned short)i;
    for (int i = 992; i < 1024; ++i) gStyleTiles.s1501[i] = 0;
}

static void FreeChunk(unsigned char*& p, unsigned int& n) { if (p) { free(p); p = 0; } n = 0; }

void StyleTiles_Unload() {
    if (gStyleTiles.tileBase) { free(gStyleTiles.tileBase); gStyleTiles.tileBase = 0; }
    if (gStyleTiles.ppalBase) { free(gStyleTiles.ppalBase); gStyleTiles.ppalBase = 0; }
    if (gStyleTiles.palx) { free(gStyleTiles.palx); gStyleTiles.palx = 0; }
    FreeChunk(gStyleTiles.sprx, gStyleTiles.sprxBytes);
    FreeChunk(gStyleTiles.sprb, gStyleTiles.sprbBytes);
    FreeChunk(gStyleTiles.fonb, gStyleTiles.fonbBytes);
    FreeChunk(gStyleTiles.cari, gStyleTiles.cariBytes);
    FreeChunk(gStyleTiles.obji, gStyleTiles.objiBytes);
    gStyleTiles.tile = 0;
    gStyleTiles.ppal = 0;
    gStyleTiles.tileBytes = 0;
    gStyleTiles.ppalBytes = 0;
    gStyleTiles.palxCount = 0;
    gStyleTiles.tileCount = 0;
    gStyleTiles.physPalCount = 0;
    gStyleTiles.loaded = false;
    StyleTiles_InitDefaults();
}

const StyleTileAssets* StyleTiles_Get() { return &gStyleTiles; }
bool StyleTiles_Ready() { return gStyleTiles.loaded && gStyleTiles.tile && gStyleTiles.ppal && gStyleTiles.palx; }
unsigned int StyleTiles_TileCount() { return gStyleTiles.tileCount; }
unsigned int StyleTiles_PhysPalCount() { return gStyleTiles.physPalCount; }

unsigned short StyleTiles_GetPhysPalForTile(unsigned int tileIdx) {
    if (!gStyleTiles.palx || gStyleTiles.palxCount == 0) return 0;
    if (tileIdx < gStyleTiles.palxCount) return gStyleTiles.palx[tileIdx];
    return gStyleTiles.palx[tileIdx % gStyleTiles.palxCount];
}

unsigned short StyleTiles_GetRemappedTile(unsigned int tileIdx) {
    unsigned int idx = tileIdx & 1023u;
    return gStyleTiles.s1501[idx];
}

unsigned short StyleTiles_GetSpec(unsigned int tileIdx) {
    unsigned int idx = tileIdx & 1023u;
    return gStyleTiles.spec[idx];
}

const unsigned short* StyleTiles_GetSpecTable() { return gStyleTiles.spec; }

unsigned char StyleTiles_SamplePixel(unsigned int tileId, int x, int y, bool flipX, bool flipY, unsigned char rot) {
    // GTA2 style format: 992 tiles in 63 pages of 64K, each page 256x256 pixels.
    // 16 tiles per page arranged 4 cols x 4 rows, each tile 64x64.
    if (!gStyleTiles.tile || gStyleTiles.tileCount == 0) return 0;
    if (tileId >= gStyleTiles.tileCount) return 0;
    if (x < 0) x = 0; if (x > 63) x = 63;
    if (y < 0) y = 0; if (y > 63) y = 63;
    int tx = x, ty = y;
    // rot: 0=0,1=90CW,2=180,3=270CW - match gbh_DrawTilePart flags&0x60 behavior.
    for (unsigned char r = 0; r < (rot & 3u); ++r) {
        int nx = 63 - ty;
        int ny = tx;
        tx = nx; ty = ny;
    }
    if (flipX) tx = 63 - tx;
    if (flipY) ty = 63 - ty;
    if (tx < 0) tx = 0; if (tx > 63) tx = 63;
    if (ty < 0) ty = 0; if (ty > 63) ty = 63;
    unsigned int page = tileId / 16u;
    unsigned int inPage = tileId % 16u;
    unsigned int tileRow = inPage / 4u;
    unsigned int tileCol = inPage % 4u;
    size_t off = (size_t)page * 65536u + (size_t)(tileRow * 64u + (unsigned int)ty) * 256u + (size_t)(tileCol * 64u + (unsigned int)tx);
    if (off >= gStyleTiles.tileBytes) return 0;
    return gStyleTiles.tile[off];
}

const unsigned char* StyleTiles_GetPhysPalette(unsigned int physIdx) {
    // GTA2 style format: 64 palette pages of 64K each. Each page contains 64 palettes
    // of 256 doublewords (1024 bytes). Palettes stored in doubleword-wide columns down each page.
    // Entry = pageBase + (colorIndex*64 + palInPage) * 4. Output BGRA per color.
    static unsigned char decoded[1024];
    if (!gStyleTiles.ppal || gStyleTiles.physPalCount == 0) return 0;
    if (physIdx >= gStyleTiles.physPalCount) physIdx = physIdx % gStyleTiles.physPalCount;
    unsigned int page = physIdx / 64u;
    unsigned int inPage = physIdx % 64u;
    size_t pageBase = (size_t)page * 65536u;
    for (unsigned int ci = 0; ci < 256u; ++ci) {
        size_t off = pageBase + ((size_t)ci * 64u + inPage) * 4u;
        if (off + 4u <= gStyleTiles.ppalBytes) {
            decoded[ci*4+0] = gStyleTiles.ppal[off+0];
            decoded[ci*4+1] = gStyleTiles.ppal[off+1];
            decoded[ci*4+2] = gStyleTiles.ppal[off+2];
            decoded[ci*4+3] = gStyleTiles.ppal[off+3];
        } else {
            decoded[ci*4+0]=decoded[ci*4+1]=decoded[ci*4+2]=decoded[ci*4+3]=0;
        }
    }
    return decoded;
}

const unsigned char* StyleTiles_GetTilePixels(unsigned int tileIdx) {
    if (!gStyleTiles.tile || gStyleTiles.tileCount == 0) return 0;
    if (tileIdx >= gStyleTiles.tileCount) return 0;
    return gStyleTiles.tile + (size_t)tileIdx * 4096u;
}

bool StyleTiles_Load(const char* styPath) {
    StyleTiles_Unload();
    if (!styPath || !*styPath) return false;
    FILE* f = fopen(styPath, "rb");
    if (!f) return false;

    unsigned char hdr[6];
    if (!ReadExact(f, hdr, 6)) { fclose(f); return false; }
    if (memcmp(hdr, "GBST", 4) != 0) { fclose(f); return false; }
    unsigned short ver = (unsigned short)(hdr[4] | (hdr[5] << 8));
    if (ver != 700) { fclose(f); return false; }

    std::vector<unsigned char> tileTmp, ppalTmp, palxTmp, specTmp, sprxTmp, sprbTmp, fonbTmp, cariTmp, objiTmp;
    for (;;) {
        unsigned char ch[8];
        if (fread(ch, 1, 8, f) != 8) break;
        char tag[5] = {0,0,0,0,0}; memcpy(tag, ch, 4);
        unsigned int sz = (unsigned int)ch[4] | ((unsigned int)ch[5]<<8) | ((unsigned int)ch[6]<<16) | ((unsigned int)ch[7]<<24);
        long payload = ftell(f);
        if (sz > 0x20000000u) { fclose(f); return false; }

        auto readVec = [&](std::vector<unsigned char>& v)->bool { v.resize(sz); return ReadExact(f, v.empty()?0:&v[0], sz); };
        if (memcmp(tag, "TILE", 4) == 0) { if (!readVec(tileTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "PPAL", 4) == 0) { if (!readVec(ppalTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "PALX", 4) == 0) { if (!readVec(palxTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "SPEC", 4) == 0) { if (!readVec(specTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "SPRX", 4) == 0) { if (!readVec(sprxTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "SPRB", 4) == 0) { if (!readVec(sprbTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "FONB", 4) == 0) { if (!readVec(fonbTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "CARI", 4) == 0) { if (!readVec(cariTmp)) { fclose(f); return false; } }
        else if (memcmp(tag, "OBJI", 4) == 0) { if (!readVec(objiTmp)) { fclose(f); return false; } }
        else { if (fseek(f, (long)sz, SEEK_CUR) != 0) { fclose(f); return false; } }
        (void)payload;
    }
    fclose(f);

    if (tileTmp.empty() || ppalTmp.empty() || palxTmp.empty()) {
        return false;
    }
    if ((tileTmp.size() % 4096u) != 0) return false;
    if ((ppalTmp.size() % 1024u) != 0) return false;
    if ((palxTmp.size() % 2u) != 0) return false;

    gStyleTiles.tile = (unsigned char*)AllocAligned64K(tileTmp.size(), &gStyleTiles.tileBase);
    gStyleTiles.ppal = (unsigned char*)AllocAligned64K(ppalTmp.size(), &gStyleTiles.ppalBase);
    gStyleTiles.palx = (unsigned short*)malloc(palxTmp.size());
    if (!gStyleTiles.tile || !gStyleTiles.ppal || !gStyleTiles.palx) { StyleTiles_Unload(); return false; }

    auto copyChunk = [&](unsigned char*& dst, unsigned int& dstBytes, const std::vector<unsigned char>& src) {
        dst = 0; dstBytes = 0;
        if (src.empty()) return;
        dst = (unsigned char*)malloc(src.size());
        if (!dst) return;
        memcpy(dst, &src[0], src.size());
        dstBytes = (unsigned int)src.size();
    };

    memcpy(gStyleTiles.tile, &tileTmp[0], tileTmp.size());
    memcpy(gStyleTiles.ppal, &ppalTmp[0], ppalTmp.size());
    memcpy(gStyleTiles.palx, &palxTmp[0], palxTmp.size());
    copyChunk(gStyleTiles.sprx, gStyleTiles.sprxBytes, sprxTmp);
    copyChunk(gStyleTiles.sprb, gStyleTiles.sprbBytes, sprbTmp);
    copyChunk(gStyleTiles.fonb, gStyleTiles.fonbBytes, fonbTmp);
    copyChunk(gStyleTiles.cari, gStyleTiles.cariBytes, cariTmp);
    copyChunk(gStyleTiles.obji, gStyleTiles.objiBytes, objiTmp);

    gStyleTiles.tileBytes = (unsigned int)tileTmp.size();
    gStyleTiles.ppalBytes = (unsigned int)ppalTmp.size();
    gStyleTiles.palxCount = (unsigned int)(palxTmp.size() / 2u);
    gStyleTiles.tileCount = gStyleTiles.tileBytes / 4096u;
    gStyleTiles.physPalCount = gStyleTiles.ppalBytes / 1024u;

    StyleTiles_InitDefaults();
    if (!specTmp.empty()) {
        // SPEC layout: repeated groups; each group is list of u16 tile indices terminated by 0, for categories 2..10.
        const unsigned char* d = &specTmp[0];
        size_t n = specTmp.size();
        size_t off = 0;
        for (int cat = 2; cat <= 10; ++cat) {
            while (off + 2 <= n) {
                unsigned short v = (unsigned short)(d[off] | (d[off+1]<<8));
                off += 2;
                if (v == 0) break;
                if (v < 1024) gStyleTiles.spec[v] = (unsigned short)cat;
                if (off + 2 > n) break;
            }
        }
    }

    gStyleTiles.loaded = true;
    return true;
}