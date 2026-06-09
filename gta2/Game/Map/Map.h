#ifndef __MAP_H__
#define __MAP_H__

#include <windows.h>

#pragma pack(push, 1)
struct TileData {
    DWORD field_0;
    DWORD field_4;
    WORD  field_8;
    BYTE  field_A;
    BYTE  flags;      // lower 2 bits = boundary type, upper = tile category
};
#pragma pack(pop)

class Map {
public:
    Map();

    char* sub_42A830(int a2, int a3);

    int&  GridAt(int x, int y);
    int   GetGridTile(int x, int y);
    void  SetGridTile(int x, int y, int tileIndex);

    BYTE  GetTileMinHeight(int tileIndex);
    BYTE  GetTileMaxHeight(int tileIndex);
    int   GetTileDataRef(int tileIndex, int zLevel);

    TileData* GetTileData(int dataRef);
    int       GetTileCount();
    int       GetTileDataCount();

    // 0x00000: tile grid data (256x256 ints = 262144 bytes)
    char FileLoad[262144];

    // 0x40000: tile count
    int File;

    // 0x40004: tile data entry count
    int field_40004;

    // 0x40008: pointer to tile index buffer
    int field_40008;

    // 0x4000C: pointer to tile data buffer (12-byte entries)
    int field_4000C;
};

#endif // __MAP_H__
