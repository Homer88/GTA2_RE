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
// Map::GetTileDataPtr (0x0042A830)
// Index tile grid: returns pointer to (char*)this + 1024 * a2 + 4 * a3
//=============================================================================
char* Map::GetTileDataPtr(int a2, int a3)
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
    return *(int*)GetTileDataPtr(y, x);
}

//=============================================================================
// Map::SetGridTile
// Sets tile index in grid at position (x, y)
//=============================================================================
void Map::SetGridTile(int x, int y, int tileIndex)
{
    *(int*)GetTileDataPtr(y, x) = tileIndex;
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
// Map::FindTileForMaxZ (0x00466910)
// Walks tiles upward from a grid position, returns TileData whose
// boundary type (flags&3) == 2, writing the matched z to outZ.
//=============================================================================
int Map::FindTileForMaxZ(int x, int y, int* outZ)
{
    // this is Map* (fields +0x40008 tile index buffer, +0x4000C tile data)
    int* piVar1 = (int*)GetTileDataPtr(y, x);
    unsigned int uMin = *(unsigned char*)(field_40008 + 1 + *piVar1 * 4);
    unsigned char* pb = (unsigned char*)(field_40008 + *piVar1 * 4);
    int iVar4 = (*pb - uMin) + -1;
    if ( iVar4 < 0 )
        return 0;
    pb = pb + iVar4 * 4 + 4;
    do
    {
        int tile = field_4000C + *(int*)pb * 0xc;
        if ( (*(unsigned char*)(tile + 0xb) & 3) != 0 )
        {
            if ( (*(unsigned char*)(tile + 0xb) & 3) != 2 )
                return 0;
            if ( outZ ) *outZ = uMin + iVar4;
            return tile;
        }
        iVar4 = iVar4 - 1;
        pb = pb - 4;
    } while ( iVar4 >= 0 );
    return 0;
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
