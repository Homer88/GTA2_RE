#ifndef __MISSION_MANAGER_H_
#define __MISSION_MANAGER_H_

#include <windows.h>
#include <cstring>
#include "../../Engine/FileMgr/FileMgr.h"

#ifndef _WORD
#define _WORD WORD
#define _DWORD DWORD
#define _BYTE BYTE
#define __int16 INT16
#define __int64 INT64
#define LOBYTE(x) (*(_BYTE*)&(x))
#define LOWORD(x) (*(_WORD*)&(x))
#define HIWORD(x) ((_WORD)(((_DWORD)(x) >> 16) & 0xFFFF))
#define BYTE1(x) (*((_BYTE*)&(x) + 1))
#define BYTE2(x) (*((_BYTE*)&(x) + 2))
#endif

class Player;
class MapGm;
class MapRelatedStruct;
class MissionScriptObjects;
class MissionScriptObjectData;
class Game;
class Object;
struct S107;
struct S202;
struct SpriteS1;
struct PublicTransport;
struct AudioSourceParams;
struct EventHandler;
struct CarSystemManager;

enum GangType {
    Yakuza = 0
};

#pragma pack(push, 1)
class MissionManager {
public:
    bool Status;

    short field_0;                    // 0x000
    short pad_02;                     // 0x002
    int arr_96[96];                   // 0x004
    short field_184;                  // 0x184
    short pad_186;                    // 0x186
    int RuntimeCache[60];             // 0x188
    short field_278;                  // 0x278
    short pad_27A;                    // 0x27A
    int arr_30[30];                   // 0x27C
    short gap_2F4_to_314[16];         // 0x2F4 (gap for field_2F4, Name[32], field_460, etc.)
    int field_314;
    int field_318;
    int field_31C;
    int field_320;
    int field_324;
    int field_328;
    int field_32C;
    int field_330;
    int field_334;
    int field_338;
    int field_33C;
    int field_340;
    int field_348;
    int field_34C;
    int int_A;
    int Gang;
    int field_C1E70;
    short field_356;
    short field_358;
    short field_35A;
    char field_355;
    char field_C1E2E;
    char field_C1E2D;
    int field_468;
    char Name[32];
    int field_460;
    int field_464;
    char arr2_15[30];
    char field_C1E6E;
    int field_C1E2F;
    int field_C1E31;
    int arr_12[12];
    int field_C1EA4;

    short OBJECTIVE_DATA_SIZE[6000];  // 0x46C (12000 bytes)
    char Script[65536];               // 0x334C
    int EVENT_LOG_SIZE[155000];       // 0x1334C
    int arr_23808[23808];
    short arr_15[15];
    char Byte_a;
    short BaseScriptMaxPointers[15];
    char field_C1DAE;
    int MissionScriptSize[15];
    void* MissionPtrMaybe;
    int shouldBeEqTo1;
    int Bool_A;
    int Health;
    char pathToScriptFile[260];

    // Audio params (S9 placeholder)
    char S9[4];

    MissionManager();
    ~MissionManager();
    char MissionManager_1();
    void MissionManagerDes();
    MissionManager* MissionManager_Des(char a2);

    _WORD* sub_474F00(__int16 a2);
    int sub_474F30(const char* a2);
    bool sub_475A20();
    char sub_475A30();
    void sub_475A40(char a2);
    int sub_475CA0();
    _WORD* sub_475D30(unsigned __int16 a2);
    char* ExtractFileNameWithoutExtension();
    __int16 sub_475E90(FileMgr* a2);
    unsigned __int16* sub_476070();
    MissionManager* StartMission(unsigned __int16 a2);
    int* sub_476240(int a2, int a3);
    int* sub_476280(int a2, int a3, __int16 a4);
    int* sub_476320(int a2, int a3);
    int* sub_476370(int a2, int a3, __int16 a4);
    _DWORD* sub_4763B0(int a2, int a3);
    char* sub_4763E0(int a2);
    char sub_476400(int a2, char a3, char a4);
    char sub_4764D0(int a2, char a3);
    char sub_476530(int a2, int a3, char a4);
    bool sub_4765A0(int a2, char a3, char a4);
    _DWORD sub_4799D0();
    __int16 sub_47ED20(void* a1, void* a2);
    char sub_47EDB0(int a2);
    void sub_47EE70();
    _DWORD* sub_47EF10();
    int SaveFile(char* pSaveFileName);
    int sub_47F0B0(char* SaveFileName);
    int sub_47F200(__int16 a3, char a2);
    _WORD* sub_47F230(__int16 a2, unsigned __int16 a3);
    unsigned __int8 loadScript(char* ScriptName);
    char sub_47F340(int a2, int a3);
    char sub_47F3B0(int a2, int a3);
    int* sub_47F420(int a2);
    int sub_481200();
    Player* sub_481890();
    void sub_481900();
};
#pragma pack(pop)

extern MissionManager gMissionManager;

extern bool skip_mission;
extern char do_miss_logging;
extern MissionScriptObjects* gMissionScriptObjects;
extern void* gTrafficManager;
extern char gStr[256];
extern _DWORD dword_664D18[16];
extern _DWORD dword_56EC54;
extern char byte_5931F4;
extern char byte_5931FC[32];
extern int unk_664590[];
extern char byte_6645A9[];
extern char byte_6645C2[];
extern int unk_6645A8;
extern int unk_6645C1;
extern int unk_6645DA;
extern int unk_6645DB;
extern int unk_6645DC;
extern int unk_6645DD;
extern int unk_6644B0;
extern int unk_6644B4;
extern int unk_6646BA;
extern int unk_6646BC;
extern int unk_6646C0;
extern _WORD unk_6646C4[];
extern int unk_664CA0[];
extern int unk_664CD4;
extern _DWORD dword_6645E4;
extern char byte_664B74[];
extern _DWORD dword_673E2C;
extern S107* gS107;
extern int dword_6644CC[];
extern _DWORD unk_664DC4[];
extern _DWORD unk_664E08;
extern _DWORD unk_664EBC[];
extern CarSystemManager* gCarSystemManager;
extern MapGm gMapGm;
extern Game* gGame;
extern Object* gObject;
extern MapRelatedStruct* gMapRelatedStruct;
extern void* gMissionObjective;

extern void* createBuffer(unsigned int size);
extern void debug_log(unsigned int, const char*, int, ...);
extern void sub_461690(_DWORD*, const char*, int);
extern void sub_461590(_DWORD*, _DWORD*);
extern int WriteSub_402CF0(const char*, int*, int*);
extern int ARWBinarySub_402DA0(const char*, int, int*);
extern void free_0(void*);
extern void free_1(void*);
extern char sub_44AB80(int a3);
extern char sub_4759A0(int* arr);
extern char sub_4759C0(int* arr);
extern char sub_475980(int* arr);
extern void sub_476930(void* a2, int a3);
extern void sub_476950(void* a2, unsigned __int8 a3);
extern void sub_478240(int arr_96_1);
extern void partOfLoadScrip(void* buffer, int* sizePtr);
extern int AudioSourceParams_sub_41E370(void*, int, int);
extern int AudioSourceParams_sub_463710(void*, int);
extern int S202_sub_401B20(S202*, SpriteS1*, PublicTransport*);
extern int S202_sub_40CE30(S202*, unsigned __int8);
extern int MissionObjective_sub_4C4F30(void*, int*, int*, int, int, int, int, int, int);
extern int SpriteS1_sub_4BB020(void*, void*);
extern int sub_4BA6C0(void*, void*);
extern int sub_401B90(int*, _BYTE*, _DWORD*);
extern int Player_sub_401B40(void*, S202*, int);
extern int MapGm_GetMapName(MapGm*);
extern int MapGm_GetStyleFile(MapGm*);
extern int MapGm_GetScriptName(MapGm*);
extern int MapGm_GetPlayerArena(MapGm*);
extern int MapGm_GetBonusStage(MapGm*);
extern int MapGm_GetGang(MapGm*);
extern int MapGm_GetPlayerSlotSave(MapGm*);
extern int MapGm_GetSpecialTokens(MapGm*);
extern void MapRelatedStruct_sub_4642A0(MapRelatedStruct*, void**, int*, void**, void*, void**, int*);
extern void MapRelatedStruct_sub_464250(void*, int, unsigned int, unsigned int);
extern int MapRelatedStruct_sub_464D00(MapRelatedStruct*, char*, unsigned int);
extern void Player_sub_4A6B20(void*, int);
extern void Object_sub_483D90(Object*, void*);
extern void Object_sub_485640(Object*, void*);
extern int sub_476B10(MapGm*, int);
extern int MissionScriptObjects_RemoveFirstElement(MissionScriptObjects*);
extern void MissionScriptObjectData_sub_475B70(void*, char, __int16);
extern int MissionScriptObjectData_sub_476E50(void*, void*);
extern void MissionScriptObjects_sub_47F4D0(MissionScriptObjects*);
extern void MissionScriptObjects_sub_481380(MissionScriptObjects*);
extern Game* Game_GetPlayer1(Game*);
extern void S63_sub_483C60(void*, int);
extern void MapRelatedStruct_sub_464C70(MapRelatedStruct*, char*);
extern int MapGm_sub_45E700(MapGm*);

#endif
