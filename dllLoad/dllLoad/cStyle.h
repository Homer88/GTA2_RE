#ifndef __Style__H__
#define __Style__H__

#include <stddef.h>

// ---------------------------------------------------------------------------
// Style == front-end/level style (.STY) descriptor.  IDA: gta2.exe.h:7470-7506.
// gStyle is a POINTER CELL at 0x00670684 (gta2.exe.asm:1072033-1072034,
// written by `mov dword ptr gStyle, eax` gta2.exe.asm:9185 / 10124); the
// object itself is heap: operator_new(0x106C) in Menu::Menu (gta2.exe.c:72299)
// and in Game::Game (gta2.exe.c:77142).
//
// Size proof: ctor arr1024[1024] starts at 0x6C -> 0x6C + 0x1000 = 0x106C
// (kGlobals "S15 Style" 0x00670684 / 0x106c, done.md:19).
//
// Filled by Style::LoadFstyle 0x004C0820 (gta2.exe.c:159224) which parses the
// 8-byte chunk headers of a "GBST"+0x02BC file through Style::parse_chunk
// 0x004C05B0 (gta2.exe.c:159148) - 16 tags, see the per-field comments.
//
// NOTE: IDA named member +0x1C `Car` (type Car*) - it is really the FONB
// (font/char metrics) chunk buffer, renamed here to avoid clashing with
// struct Car.  All other IDA names are kept as comments.
// ---------------------------------------------------------------------------

// PALB chunk, exactly 16 bytes (checked `if (v8 != 16) debug_log` in
// Style::read_palb_chunk_REAL gta2.exe.c:158710).  IDA declares it as 21
// bytes - wrong.  8 x u16 offsets into the global palettes.
struct S15_0002
{
    unsigned short Offset[8];
};
static_assert(sizeof(S15_0002) == 0x10, "PALB chunk 16 bytes");

// SPRB chunk, exactly 12 bytes (`if (v6 != 12)` gta2.exe.c:158680).
// 6 x u16 bases of the sprite palettes.
struct S15_001
{
    unsigned short Base[6];
};
static_assert(sizeof(S15_001) == 0x0C, "SPRB chunk 12 bytes");

// Tile remap table: 1024 x u16 = 2048 bytes (gta2.exe.c:158474-158481,
// sub_4BF7F0 builds it from the TILE chunk).  IDA parses it as
// char + gap[2046] + char - a misparse.
struct S1501
{
    unsigned short Id[1024];
};
static_assert(sizeof(S1501) == 2048, "tile remap table 2048 bytes");

// CARI chunk: car model descriptions, 0x404 allocated
// (operator_new(0x404) in Style::sub_4C0410, gta2.exe.c:159060-159128).
struct S284
{
    int             Car[256];
    unsigned char   CountModelCar;
};
static_assert(sizeof(S284) == 0x404, "S284 alloc 0x404");

struct Style
{
    short           totalPal;       // 0x00 IDA field      sum of PALB u16 (sub_4BF790)
    short           charCount;      // 0x02 IDA field_2    sum of FONB shorts
    unsigned short  spriteCount;    // 0x04 IDA field_4    (SPRX size >> 3) + 1
    unsigned short  objectCount;    // 0x06 IDA field_6    OBJI size >> 1
    unsigned short  colourBanks;    // 0x08 IDA PalitrePal PPAL size >> 10
    char            field_A;        // 0x0A not zeroed by ctor (pad)
    char            field_B;        // 0x0B pad
    int             S382;           // 0x0C IDA field_C    cumulative PALB copy (16 bytes)
    S15_0002*       PALB;           // 0x10 IDA S15_0002*  raw PALB chunk
    S15_001*        SPRB1;          // 0x14 IDA field_14   cumulative SPRB copy
    int             SPRB;           // 0x18 IDA field_18   raw SPRB chunk
    void*           FONB;           // 0x1C IDA Car*       font/char chunk buffer
    int             SPRX;           // 0x20 IDA field_20   sprite data, 8 bytes/sprite
    int             OBJI;           // 0x24 IDA field_24   object records, 2 bytes each
    void*           PALX;           // 0x28 IDA FILE*      physical palette, 0x8000 bytes
    int             PPAL;           // 0x2C IDA field_2C   aligned palette pointer
    int             PPAL_Base;      // 0x30 IDA field_30   raw malloc ptr (sub_4059F0)
    int             SPRG;           // 0x34 IDA field_34   aligned global sprite offsets
    int             SPRG_Base;      // 0x38 IDA field_38   raw malloc ptr
    int             TILE;           // 0x3C IDA Tiles      aligned tile data
    S1501*          S1501;          // 0x40                tile remap table (2048)
    int             TILE_Base;      // 0x44 IDA field_44   raw malloc ptr
    int             DELS;           // 0x48 IDA field_48   sprite offsets
    int             DELX;           // 0x4C IDA field_4C   sprite indices (freed after build)
    int             SpriteBuffer;   // 0x50 IDA field_50   built sprite buffer
    int             SpriteLookup;   // 0x54 IDA field_54   sprite lookup table
    int             CARI;           // 0x58 IDA field_58   car model records
    S284*           pCar_5C;        // 0x5C IDA S284*
    int             delx3;          // 0x60                total built sprite buffer size
    char*           RECY;           // 0x64 IDA recy      recyclable CarModel list
    short           n_recy;         // 0x68 IDA n_recy
    bool            ColourDepth;    // 0x6A set to 1 by ResolveColorSettings (gta2.exe.c:169501)
    char            pad2;           // 0x6B
    int             arr1024[1024];  // 0x6C tile special attributes (SPEC chunk, values 1..10)
};

static_assert(sizeof(Style) == 0x106C, "Style size 0x106C");
static_assert(offsetof(Style, PALB) == 0x10, "Style PALB 0x10");
static_assert(offsetof(Style, S1501) == 0x40, "Style S1501 0x40");
static_assert(offsetof(Style, pCar_5C) == 0x5C, "Style pCar_5C 0x5C");
static_assert(offsetof(Style, ColourDepth) == 0x6A, "Style ColourDepth 0x6A");
static_assert(offsetof(Style, arr1024) == 0x6C, "Style arr1024 0x6C");

// Legacy detour stub (the DetourAttach for it in dllmain.cpp is commented out).
// Kept static so this header may be included from several translation units.
static unsigned __int8 __stdcall GetNumberOfCars(void* pthis)
{
    (void)pthis;
    return 0;
}

#endif // !__Style__H__
