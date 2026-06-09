#ifndef __MAP_RELATED_STRUCT_H__
#define __MAP_RELATED_STRUCT_H__

#include <windows.h>
#include <cstdio>
#include <cstdlib>

typedef signed int _DWORD;
typedef unsigned short _WORD;
typedef unsigned char _BYTE;
typedef __int64 _QWORD;

#ifndef LOBYTE
#define LOBYTE(w) ((unsigned char)((w) & 0xFF))
#endif
#ifndef HIWORD
#define HIWORD(dw) ((unsigned short)(((unsigned int)(dw) >> 16) & 0xFFFF))
#endif
#ifndef BYTE1
#define BYTE1(dw) ((unsigned char)(((unsigned int)(dw) >> 8) & 0xFF))
#endif
#ifndef BYTE2
#define BYTE2(dw) ((unsigned char)(((unsigned int)(dw) >> 16) & 0xFF))
#endif
#ifndef BYTE3
#define BYTE3(dw) ((unsigned char)(((unsigned int)(dw) >> 24) & 0xFF))
#endif

#include "../Map/Map.h"

struct S16_01;
struct S202;
#include "../AudioSourceParams/AudioSourceParams.h"
struct GameEntity;
class Player;
struct SpriteS1 {
    SpriteS1* FirstElement;
};
class Gang;
#include "../Car/CarSystemManager.h"
class FileMgr;

#pragma pack(push, 1)

struct S16_01 {
    char gap0[800];
    int field_320;
};

struct S16_02 {
    __int16 field;    // 0x00
    __int16 field_2;  // 0x02
    __int16 field_4;  // 0x04
    __int16 field_6;  // 0x06
    __int16 field_8;  // 0x08
    char field_A;     // 0x0A
    char field_B;     // 0x0B

    static void sub_44C840(S16_02* p);
};

struct S202 {
    int field_0;                    // 0x00
    S202* self;                     // 0x04
    CarSystemManager* carMgr;       // 0x08
    int field_C;                    // 0x0C
    void* field_10;                 // 0x10
    class Player* pPlayer;          // 0x14
    int field_18;                   // 0x18
    unsigned char field_1C;         // 0x1C
    char field_1D;                  // 0x1D
    char field_1E;                  // 0x1E
    char field_1F;                  // 0x1F

    static void sub_41F980(S202* p, int value);
    static void* sub_401B20(S202*, SpriteS1*, PublicTransport*);
};

class MapRelatedStruct {
public:
    // 0x000: S16_01 (804 bytes), Map* overlaps at offset 0
    S16_01 s16_01;

    // Map* accessors (shares offset 0 with S16_01.gap0[0..3])
    Map*& getMap() { return *(Map**)&s16_01.gap0[0]; }

    // 0x324
    void* Buffer_ZONE;
    // 0x328
    int* count;
    // 0x32C
    unsigned char* field_330;
    // 0x330
    _WORD* field_334;
    // 0x334
    void* Buffer_MOBJ;
    // 0x338
    void* Buffer_ANIM;
    // 0x33C
    void* Buffer_LGHT;
    // 0x340
    int field_344;
    // 0x344
    int field_348;
    // 0x348
    int field_34C;
    // 0x34C
    int field_350;
    // 0x350
    int field_354;
    // 0x354
    int field_358;
    // 0x358
    int field_35C;
    // 0x35C
    int field_360;
    // 0x360
    _WORD field_364;
    // 0x362
    _WORD field_366;
    // 0x364
    char Len;
    // 0x365
    char field_369;
    // 0x366
    unsigned char field_36A;
    // 0x367
    unsigned char field_36B;
    // 0x368
    unsigned char field_36C;
    // 0x369
    unsigned char field_36D;
    // 0x36A
    unsigned char field_36E;
    // 0x36B
    unsigned char field_36F;

    // Construction / destruction
    MapRelatedStruct();
    ~MapRelatedStruct();

    // Tile boundary / adjacency checks
    char sub_420420(int a2, int a3, int a4);
    int sub_42A850(unsigned char a2, unsigned char a3, unsigned char a4);
    bool sub_42A8C0(unsigned char a2, unsigned char a3, unsigned char a4);
    bool sub_433430(int a2, int a3, int a4);
    bool sub_433470(unsigned char a2, char a3, unsigned char a4);
    bool sub_4334A0(char a2, unsigned char a3, unsigned char a4);
    bool sub_4334D0(unsigned char a2, char a3, unsigned char a4);
    bool sub_433500(char a2, unsigned char a3, unsigned char a4);
    bool sub_433530(unsigned char a2, unsigned char a3, unsigned char a4);

    // Chunk loaders: ZONE, MOBJ, ANIM, LGHT
    int sub_462C60();
    int sub_462CB0(unsigned short a2);
    _WORD* sub_462CE0(unsigned short a2, __int16 a3);
    int sub_462D00(unsigned short a2, __int16 a3);
    int sub_462D20(unsigned short a2, __int16 a3);
    int sub_462D40(unsigned short a2, __int16 a3);
    int sub_462D60(unsigned short a2, __int16 a3);
    int sub_462D80(unsigned short a2, __int16 a3);
    int sub_462DA0(unsigned short a2, __int16 a3);
    int sub_462DC0(unsigned short a2, __int16 a3);
    int sub_462DE0(unsigned short a2, __int16 a3);
    int sub_462E00(unsigned short a2, __int16 a3);
    int sub_462E20(unsigned short a2, __int16 a3);
    char* sub_462E40(unsigned short a2);
    char sub_462E80();
    char sub_462F50(int a2, int a3);

    // Map loading / zone query
    char sub_4632E0(int a1, int a2, char a3);
    int sub_4633A0(int a1, char a2);
    int sub_463570(int a2, int a3, _DWORD* a4);
    int sub_4635F0(int a2, int a3, int* a4);
    char sub_463850(AudioSourceParams a2);
    int sub_463A00(_DWORD* a2);
    int sub_463A40(unsigned int a2);
    unsigned int sub_463A90(unsigned int a2);
    unsigned int sub_463AE0(unsigned int a2, int a3);
    unsigned int sub_463C30(unsigned int a2, int a3, char a4);
    char sub_463F60(int a2, int a3, int a4, int a5, __int16 a6);

    // Map tile queries
    int sub_464060(int a2, int a3, int a4, _DWORD* a5);
    S16_01* sub_464110(int a2, int a3, int a4, char a5);
    char sub_464160(int a2, int a3);
    int sub_464210(int a2, int a3, int a4, int a5);
    unsigned int sub_464250(unsigned int a2, unsigned int a3, unsigned int a4);
    int sub_4642A0(_DWORD* a2, _DWORD* a3, _DWORD* a4, _DWORD* a5, _DWORD* a6, int* a7);

    // File chunk loaders
    int sub_4644E0(unsigned int a2);
    int sub_464550(int a2);
    int sub_464590(SIZE_T dwBytes);
    int sub_4645F0(SIZE_T dwBytes);
    int sub_464640(FileMgr* dwBytes);
    int sub_464670(FileMgr* dwBytes);
    int sub_4646A0(int a2);

    // Map file I/O
    unsigned char sub_464880();
    unsigned char sub_464890(_BYTE* a2, FileMgr* dwBytes);
    _WORD* sub_464990(LPCSTR lpFileName);
    _WORD* sub_464980();

    // Zone search
    int sub_464C70(const char* a2);
    int sub_464D00(char* String2, unsigned char a3);
    char* sub_464DA0(char a2);
    char* sub_464E70(char a2);
    char* sub_464EE0(unsigned char arg0, unsigned char a2, char a4);
    char* sub_464FE0(unsigned char a2, unsigned char a3, char a4);
    char* sub_465090(unsigned char a2, unsigned char a3);
    char* sub_465130(unsigned char a2, unsigned char a3);
    char* sub_4651C0();
    int sub_465250(unsigned char a2, unsigned char a3);
    _WORD* sub_465280(int a2, __int16 a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, __int16 a11, __int16 a12, __int16 a13);

    // Gang / entity tile queries
    Gang* sub_465350(int a2, int a3);
    char* sub_465390();
    int sub_4653C0(int a2, int a3, int a4);
    S16_02** sub_465410(int a2, int a3, int a4);
    int sub_465490(int a2, int a3, int a4);
    int sub_465510(GameEntity* a2);
    int sub_4655B0(int a2, GameEntity* a3);
    int sub_465650(int a2, int a3, Player* a4);
    char sub_4656D0(int a2, int a3, int a4, int a5, _DWORD* a6, char a7);

    // Map effects / audio
    char sub_465FE0(AudioSourceParams* arg0);
    char sub_466170(int arg0);
    char sub_466380(int a2, int a3, int a4, int a5, int a6);
    char sub_466430(int arg0, int a3, int a2, int a5, int a6);
    char sub_466620(void* a2);
    char sub_466730(AudioSourceParams a2);
    int sub_466910(int a2, int a3, _DWORD* a4);
    _WORD* FindMaxZForTile(int a2, int a3, _DWORD* a4);
    _WORD* sub_466A00(int a2, int a3, int* a4);
    char sub_466AF0(int a2, int a3, GameEntity* a4);
    char sub_466B70(int* a2, S202* pS202);
    bool sub_466CF0(int a2, int a3, int a4);
    __int16 sub_466D30(AudioSourceParams a2);
    _DWORD* sub_466E20(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2);
    _DWORD* sub_466F70(_DWORD* arg0, S202* a2);
    __int16 sub_467020(int*, SpriteS1*, void*, void*, void*);
    int sub_467110(int* arg0, SpriteS1* a3, int* a4, Player* pPlayer);
    int sub_467F80(int** arg0, SpriteS1** a3, int* a4, Player* a5);

    // Audio
    char sub_469110(int a2, int a3, char a4);
    unsigned int sub_4692B0();
    char sub_469400(_BYTE* a1, _BYTE* a2, _BYTE* a3, char a4);
    _DWORD* sub_469570(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2);
    _DWORD* sub_4696C0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2);
    int* sub_4696C0(int* arg0, AudioSourceParams* arg4);
    SpriteS1** sub_469850(SpriteS1* arg0, AudioSourceParams* arg4);
    _DWORD* sub_4699A0(_DWORD* arg0, int* arg4, SpriteS1* a3, int a2, SpriteS1* a4);
    char sub_469B00(int* a2, SpriteS1* a3, Player* a4);
    bool sub_469C20(int* arg0, SpriteS1* a3, Player* a4);
    char sub_469DC0(int* a2, SpriteS1* pSpriteS1);
    char sub_469F90(SpriteS1* a2, SpriteS1* arg4, Player* a4);

    // Car AI / MOBJ spawning
    int sub_46A4D0();
    char sub_46A570(CarSystemManager* arg0, CarSystemManager* a3, CarSystemManager* a4, CarSystemManager* a5, CarSystemManager* a6, CarSystemManager* a2, int a8);
    char sub_46B440(CarSystemManager* a6, CarSystemManager* a2, int a8, _DWORD* a5, __int16 arg10);

    // Misc
    bool sub_48A350(unsigned char a2, unsigned char a3, unsigned char a4);
    void sub_492130();
    bool sub_492140(int a2, int a3, int a4);
    char sub_49EBE0(int a2, int a3, int a4, _BYTE* a5, _BYTE* a6);
    bool sub_4B9F40(int a2, int a3, int a4);

    // Max Z / location
    int* FindMaxZForLocation(int* arg0, int* a2, S202* pS202);

    // Helper for destructor
    void sub_464B30();
    void sub_464330();
};

#pragma pack(pop)

extern MapRelatedStruct* gMapRelatedStruct;

#endif // __MAP_RELATED_STRUCT_H__
