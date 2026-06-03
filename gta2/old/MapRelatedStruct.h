#ifndef  __MAP_RELATED_STRUCT__H__
#define  __MAP_RELATED_STRUCT__H__

#include <windows.h>
#include <cstdio>

struct S16_01 {
    BYTE gap0[800];
    int field_320;
};

struct Map {
    void* FileLoad[65536];  // 0x40000 bytes tile grid
    FILE* File;             // offset 0x40000
    int field_40004;        // tile count
    int field_40008;        // tile index buffer
    int field_4000C;        // tile data buffer
};

struct SpriteS1;
struct S202;
struct AudioSourceParams;
struct GameEntity;
struct Player;
struct Gang;
struct CarSystemManager;

class MapRelatedStruct {
public:
    // Raw data
    Map* Map;
    S16_01 S16_01;
    FILE* Buffer_ZONE;      // allocated, freed in dtor
    int* pCount;            // pointer to count value (was `int count` in original header)
    FILE* field_330;        // ZONE data buffer (allocated, freed in dtor)
    FILE* field_334;        // ZONE string table (allocated, freed in dtor)
    FILE* Buffer_MOBJ;      // MOBJ chunk buffer
    FILE* Buffer_LGHT;      // LGHT chunk buffer
    FILE* Buffer_ANIM;      // ANIM chunk buffer
    int field_344;          // count of MOBJ entries
    int field_348;          // count of ANIM entries
    int field_34C;          // tile data count
    int field_350;          // tile data capacity
    int field_354;          // tile data count (copy)
    int field_358;          // tile index count
    int field_35C;          // tile index capacity
    int field_360;          // dynamic tile index counter
    unsigned short field_364; // ZONE entry iterator index
    short field_366;
    char Len;               // length field for string matching
    char field_369;
    char field_36A;         // string match byte 0
    char field_36B;         // string match byte 1
    char field_36C;         // match flag
    char field_36D;
    char field_36E;         // processing flag (bool)
    char field_36F;         // another flag (bool)

    // Construction / destruction
    MapRelatedStruct();
    ~MapRelatedStruct();

    // Chunk loaders (single-type)
    int sub_464640(MapRelatedStruct* this, FileMgr* dwBytes);   // load ZONE chunk
    int sub_464670(MapRelatedStruct* this, FileMgr* dwBytes);   // load ZONE idx
    int sub_464590(MapRelatedStruct* this, SIZE_T dwBytes);     // load ??? 
    int sub_4645F0(MapRelatedStruct* this, SIZE_T dwBytes);     // load ???
    int sub_4644E0(MapRelatedStruct* this, unsigned int a2);    // load MOBJ chunk
    int sub_464550(MapRelatedStruct* this, int a2);             // load MOBJ/ANIM chunk
    unsigned __int8 sub_464880(MapRelatedStruct* this);         // debug print junctions
    unsigned __int8 sub_464890(MapRelatedStruct* this, _BYTE* a2, FileMgr* dwBytes); // dispatch chunk load

    // Map file I/O
    int sub_4646A0(MapRelatedStruct* this, int a2);             // allocate & load .MAP file
    _WORD* sub_464990(MapRelatedStruct* this, LPCSTR lpFileName); // load map by name

    // Tile queries
    _WORD* FindMaxZForTile(MapRelatedStruct* this, int a2, int a3, _DWORD* a4);
    int* FindMaxZForLocation(MapRelatedStruct* this, int* arg0, int* a2, S202* pS202);
    int sub_4653C0(MapRelatedStruct* this, int a2, int a3, int a4);    // tile lookup (most-used)
    int sub_463570(MapRelatedStruct* this, int a2, int a3, _DWORD* a4);
    int sub_4635F0(MapRelatedStruct* this, int a2, int a3, int* a4);
    int sub_466A00(MapRelatedStruct* this, int a2, int a3, int* a4);
    bool sub_466CF0(MapRelatedStruct* this, int a2, int a3, int a4);   // tile adjacency check

    // ZONE iteration (string-keyed)
    char* sub_462E40(MapRelatedStruct* this, unsigned __int16 a2); // get ZONE entry by index
    char sub_462E80(MapRelatedStruct* this);                      // check if ZONE entries exist
    char sub_462F50(MapRelatedStruct* this, int a2, int a3);      // zone query
    char sub_4632E0(MapRelatedStruct* this, int a1, int a2, char a3);
    int sub_4633A0(MapRelatedStruct* this, int a1, char a2);
    int sub_463A00(MapRelatedStruct* this, _DWORD* a2);
    int sub_463A40(MapRelatedStruct* this, unsigned int a2);
    unsigned int sub_463A90(MapRelatedStruct* this, unsigned int a2);
    unsigned int sub_463AE0(MapRelatedStruct* this, unsigned int a2, int a3);
    unsigned int sub_463C30(MapRelatedStruct* this, unsigned int a2, int a3, char a4);
    char sub_463F60(MapRelatedStruct* this, int a2, int a3, int a4, int a5, __int16 a6);
    int sub_464060(MapRelatedStruct* this, int a2, int a3, int a4, _DWORD* a5);
    S16_01* sub_464110(MapRelatedStruct* this, int a2, int a3, int a4, char a5);
    char sub_464160(MapRelatedStruct* this, int a2, int a3);
    int sub_464210(MapRelatedStruct* this, int a2, int a3, int a4, int a5);
    unsigned int sub_464250(Map** this, unsigned int a2, unsigned int a3, unsigned int a4);
    int sub_4642A0(MapRelatedStruct* this, void** a1, int* a2, void** a3, void* a4, void** a5, int* a6);
    int sub_464C70(MapRelatedStruct* this, const char* a2);
    int sub_464D00(MapRelatedStruct* this, char* String2, unsigned __int8 a3);
    char* sub_464DA0(MapRelatedStruct* this, char a2);
    char* sub_464E70(MapRelatedStruct* this, char a2);
    char* sub_464FE0(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3, char a4);
    char* sub_465090(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3);
    char* sub_465130(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3);
    char* sub_4651C0(MapRelatedStruct* this);                      // iterate ZONE
    int sub_465250(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3);
    _WORD* sub_465280(MapRelatedStruct* this, int a2, int a3, int a4, int a5);
    Gang* sub_465350(MapRelatedStruct* this, int a2, int a3);      // get gang by tile
    char* sub_465390(MapRelatedStruct* this);                      // iterate 14-type ZONE entries
    S16_02** sub_465410(MapRelatedStruct* this, int a2, int a3, int a4);
    int sub_465490(MapRelatedStruct* this, int a2, int a3, int a4);
    int sub_465510(MapRelatedStruct* this, GameEntity* a2);
    int sub_4655B0(MapRelatedStruct* this, int a2, GameEntity* a3);
    int sub_465650(MapRelatedStruct* this, int a2, int a3, Player* a4);
    char sub_4656D0(MapRelatedStruct* this, int a2, int a3, int a4, int a5, _DWORD* a6, char a7);
    int sub_462C60(MapRelatedStruct* this);
    int sub_462CB0(MapRelatedStruct* this, unsigned __int16 a2);
    _WORD* sub_462CE0(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462D00(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462D20(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462D40(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462D60(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462D80(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462DA0(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462DC0(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462DE0(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462E00(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);
    int sub_462E20(MapRelatedStruct* this, unsigned __int16 a2, __int16 a3);

    // Map effects
    char sub_465FE0(MapRelatedStruct* this, AudioSourceParams* arg0);
    char sub_466170(MapRelatedStruct* this, int arg0);
    char sub_466380(MapRelatedStruct* this, int a2, int a3, int a4, int a5, int a6);
    char sub_466430(MapRelatedStruct* this, int arg0, int a3, int a2, int a5, int a6);
    char sub_466620(MapRelatedStruct* this, void* a2);
    char sub_466730(MapRelatedStruct* this, AudioSourceParams a2);
    int sub_466910(MapRelatedStruct* this, int a2, int a3, _DWORD* a4);
    char sub_466AF0(MapRelatedStruct* this, int a2, int a3, GameEntity* a4);
    char sub_466B70(MapRelatedStruct* this, int* a2, S202* pS202);
    __int16 sub_466D30(MapRelatedStruct* this, AudioSourceParams a2);
    _DWORD* sub_466E20(MapRelatedStruct* this, _DWORD* arg0, int* arg4, SpriteS1* a3, int a2);
    _DWORD* sub_466F70(MapRelatedStruct* this, _DWORD* arg0, S202* a2);
    int sub_467110(MapRelatedStruct* this, int* arg0, SpriteS1* a3, int* a4, Player* pPlayer);
    int sub_467F80(MapRelatedStruct* this, int** arg0, SpriteS1** a3, int* a4, Player* a5);

    // Audio-related queries
    char sub_463850(MapRelatedStruct* this, AudioSourceParams a2);
    char sub_469110(MapRelatedStruct* this, int a2, int a3, char a4);
    unsigned int sub_4692B0(MapRelatedStruct* this);                      // rebuild audio ties
    char sub_469400(MapRelatedStruct* this, _BYTE* a1, _BYTE* a2, _BYTE* a3, char a4);
    _DWORD* sub_469570(MapRelatedStruct* this, _DWORD* arg0, int* arg4, SpriteS1* a3, int a2);
    _DWORD* sub_4696C0(MapRelatedStruct* this, _DWORD* arg0, int* arg4, SpriteS1* a3, int a2);
    int* sub_4696C0(MapRelatedStruct* this, int* arg0, AudioSourceParams* arg4);
    SpriteS1** sub_469850(MapRelatedStruct* this, SpriteS1* arg0, AudioSourceParams* arg4);
    _DWORD* sub_4699A0(MapRelatedStruct* this, _DWORD* arg0, int* arg4, SpriteS1* a3, int a2, SpriteS1* a4);
    char sub_469B00(MapRelatedStruct* this, int* a2, SpriteS1* a3, Player* a4);
    bool sub_469C20(MapRelatedStruct* this, int* arg0, SpriteS1* a3, Player* a4);
    char sub_469DC0(MapRelatedStruct* this, int* a2, SpriteS1* pSpriteS1);
    char sub_469F90(MapRelatedStruct* this, SpriteS1* a2, SpriteS1* arg4, Player* a4);

    // Car AI
    int sub_46A4D0(MapRelatedStruct* this);  // spawn objects from MOBJ
    char sub_46A570(MapRelatedStruct* this, CarSystemManager* arg0, CarSystemManager* a3, CarSystemManager* a4,
                   CarSystemManager* a5, CarSystemManager* a6, CarSystemManager* a2, int a8);
    char sub_46B440(MapRelatedStruct* this, int a2, int a3, int a4, _DWORD* a5, int a6);

    // Tile boundary / adjacency checks
    char sub_420420(MapRelatedStruct* this, int a2, int a3, int a4);    // generic 3-arg query
    int sub_42A850(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4); // tile data pointer
    bool sub_42A8C0(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4); // boundary check
    bool sub_433430(MapRelatedStruct* this, int a2, int a3, int a4);
    bool sub_433470(MapRelatedStruct* this, unsigned __int8 a2, char a3, unsigned __int8 a4);
    bool sub_4334A0(MapRelatedStruct* this, char a2, unsigned __int8 a3, unsigned __int8 a4);
    bool sub_4334D0(MapRelatedStruct* this, unsigned __int8 a2, char a3, unsigned __int8 a4);
    bool sub_433500(MapRelatedStruct* this, char a2, unsigned __int8 a3, unsigned __int8 a4);
    bool sub_433530(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4);

    // Misc
    bool sub_48A350(MapRelatedStruct* this, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4);
    void sub_492130(MapRelatedStruct* this);
    bool sub_492140(MapRelatedStruct* this, int a2, int a3, int a4);
    char sub_49EBE0(MapRelatedStruct* this, int a2, int a3, int a4, _BYTE* a5, _BYTE* a6);
    bool sub_4B9F40(MapRelatedStruct* this, int a2, int a3, int a4);
};

#endif // !__MAP_RELATED_STRUCT__H__
