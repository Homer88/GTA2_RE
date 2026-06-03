#ifndef __MAP_H__
#define __MAP_H__

#include <windows.h>

class Map {
public:
    Map();

    // formula: (char*)this + 1024 * a2 + 4 * a3 -> indexes into tile grid (256x256 ints)
    char* sub_42A830(int a2, int a3);

    // 0x00000: tile grid data (256x256 ints = 262144 bytes)
    char FileLoad[262144];

    // 0x40000: tile count
    int File;

    // 0x40004: tile info count
    int field_40004;

    // 0x40008: pointer to tile index buffer
    int field_40008;

    // 0x4000C: pointer to tile data buffer
    int field_4000C;
};

#endif // __MAP_H__
