#include "Map.h"

//=============================================================================
// Map::Map (0x004630B0)
//=============================================================================
Map::Map()
{
    field_40008 = 0;
    field_4000C = 0;
    field_40004 = 0;
    File = 0;
}

//=============================================================================
// Map::sub_42A830 (0x0042A830)
// Index tile grid: returns pointer to (char*)this + 1024 * a2 + 4 * a3
//=============================================================================
char* Map::sub_42A830(int a2, int a3)
{
    return (char*)this + 1024 * a2 + 4 * a3;
}

//=============================================================================
// Map::GridAt
// Returns reference to tile grid int at position (x, y)
//=============================================================================
int& Map::GridAt(int x, int y)
{
    return ((int*)FileLoad)[y * 256 + x];
}

//=============================================================================
// Map::GetGridTile
// Returns tile index from grid at position (x, y)
//=============================================================================
int Map::GetGridTile(int x, int y)
{
    return *(int*)sub_42A830(y, x);
}

//=============================================================================
// Map::SetGridTile
// Sets tile index in grid at position (x, y)
//=============================================================================
void Map::SetGridTile(int x, int y, int tileIndex)
{
    *(int*)sub_42A830(y, x) = tileIndex;
}

//=============================================================================
// Map::GetTileMinHeight
// Returns minimum z-level for a tile index entry
//=============================================================================
BYTE Map::GetTileMinHeight(int tileIndex)
{
    return *(BYTE*)(field_40008 + 4 * tileIndex + 1);
}

//=============================================================================
// Map::GetTileMaxHeight
// Returns maximum z-level for a tile index entry
//=============================================================================
BYTE Map::GetTileMaxHeight(int tileIndex)
{
    return *(BYTE*)(field_40008 + 4 * tileIndex);
}

//=============================================================================
// Map::GetTileDataRef
// Returns tile data reference (DWORD) for tileIndex at given z-level
//=============================================================================
int Map::GetTileDataRef(int tileIndex, int zLevel)
{
    int entry = field_40008 + 4 * tileIndex;
    BYTE minHeight = *(BYTE*)(entry + 1);
    return *(int*)(entry + 4 + 4 * (zLevel - minHeight));
}

//=============================================================================
// Map::GetTileData
// Returns pointer to 12-byte tile data entry
//=============================================================================
TileData* Map::GetTileData(int dataRef)
{
    return (TileData*)(field_4000C + 12 * dataRef);
}

//=============================================================================
// Map::GetTileCount
// Returns number of unique tile indices (File field)
//=============================================================================
int Map::GetTileCount()
{
    return File;
}

//=============================================================================
// Map::GetTileDataCount
// Returns number of tile data entries
//=============================================================================
int Map::GetTileDataCount()
{
    return field_40004;
}
