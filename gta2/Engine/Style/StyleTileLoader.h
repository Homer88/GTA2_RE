#pragma once
#include <cstdint>
#include <cstddef>

struct StyleTileAssets {
    unsigned char* tileBase;   // raw malloc
    unsigned char* tile;       // 64K-aligned
    unsigned char* ppalBase;
    unsigned char* ppal;       // 64K-aligned, 1024 bytes per physical palette
    unsigned short* palx;      // virtual->physical palette map
    unsigned short spec[1024]; // SPEC/arr1024 categories (default 1)
    unsigned short s1501[1024];// tile remap table (identity init)
    unsigned int tileBytes;
    unsigned int ppalBytes;
    unsigned int palxCount;    // number of u16 entries
    unsigned int tileCount;    // tileBytes / 4096
    unsigned int physPalCount; // ppalBytes / 1024
    // Extra raw chunks captured for debug/IDA-view adapter (read-only, optional).
    unsigned char* sprx = nullptr; unsigned int sprxBytes = 0;
    unsigned char* sprb = nullptr; unsigned int sprbBytes = 0; // expected 12 bytes
    unsigned char* fonb = nullptr; unsigned int fonbBytes = 0;
    unsigned char* cari = nullptr; unsigned int cariBytes = 0;
    unsigned char* obji = nullptr; unsigned int objiBytes = 0;
    bool loaded;
};

bool StyleTiles_Load(const char* styPath);
void StyleTiles_Unload();
const StyleTileAssets* StyleTiles_Get();
bool StyleTiles_Ready();
unsigned int StyleTiles_TileCount();
unsigned int StyleTiles_PhysPalCount();
const unsigned char* StyleTiles_GetTilePixels(unsigned int tileIdx); // 64x64 indexed
const unsigned char* StyleTiles_GetPhysPalette(unsigned int physIdx); // 256*4 bytes
unsigned short StyleTiles_GetPhysPalForTile(unsigned int tileIdx);
unsigned short StyleTiles_GetRemappedTile(unsigned int tileIdx);
unsigned short StyleTiles_GetSpec(unsigned int tileIdx);
const unsigned short* StyleTiles_GetSpecTable();
unsigned char StyleTiles_SamplePixel(unsigned int tileId, int x, int y, bool flipX, bool flipY, unsigned char rot);
unsigned char StyleTiles_SamplePixel(unsigned int tileId, int x, int y, bool flipX, bool flipY, unsigned char rot);