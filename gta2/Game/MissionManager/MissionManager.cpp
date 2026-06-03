#include "MissionManager.h"
#include <cstring>
#include <cstdio>

MissionManager gMissionManager;

bool skip_mission;
char do_miss_logging;
MissionScriptObjects* gMissionScriptObjects;
void* gTrafficManager;
char gStr[256];
_DWORD dword_664D18[16];
_DWORD dword_56EC54;
char byte_5931F4;
char byte_5931FC[32];
int unk_664590[0x1D2];
char byte_6645A9[0x19];
char byte_6645C2[0x19];
int unk_6645A8;
int unk_6645C1;
int unk_6645DA;
int unk_6645DB;
int unk_6645DC;
int unk_6645DD;
int unk_6644B0;
int unk_6644B4;
int unk_6646BA;
int unk_6646BC;
int unk_6646C0;
_WORD unk_6646C4[600];
int unk_664CA0[25];
int unk_664CD4;
_DWORD dword_6645E4;
char byte_664B74[32];
_DWORD dword_673E2C;
S107* gS107;
int dword_6644CC[0x964];
_DWORD unk_664DC4[16];
_DWORD unk_664E08;
_DWORD unk_664EBC[4];
CarSystemManager* gCarSystemManager;
MapGm gMapGm;
Game* gGame;
Object* gObject;
MapRelatedStruct* gMapRelatedStruct;
void* gMissionObjective;

//=============================================================================
// Constructor
//=============================================================================
MissionManager::MissionManager()
{
    this->EVENT_LOG_SIZE[1] = 0;
    if ( !skip_mission )
    {
        memset(this->Script, 0, sizeof(this->Script));
        if ( !gMissionScriptObjects )
        {
            gMissionScriptObjects = (MissionScriptObjects*)malloc(0x8ECu);
        }
    }
    this->EVENT_LOG_SIZE[0] = (int)createBuffer(5120u);
    memset(this->pathToScriptFile, 0, sizeof(this->pathToScriptFile));
    memset(this->Script, 0, sizeof(this->Script));
    memset(this->OBJECTIVE_DATA_SIZE, 0, sizeof(this->OBJECTIVE_DATA_SIZE));
    memset((void*)this->EVENT_LOG_SIZE[0], 0, 5120u);
    this->field_0 = 0;
    memset(this->arr_96, 0, sizeof(this->arr_96));
    this->field_184 = 0;
    memset(this->RuntimeCache, 0, sizeof(this->RuntimeCache));
    this->field_278 = 0;
    memset(this->arr_30, 0, sizeof(this->arr_30));
    memset(unk_664590, 0, 0x748u);

    gTrafficManager = malloc(604u);
    if ( !gTrafficManager )
        debug_log(0x20u, "miss2.cpp", 13630);

    memset(&this->EVENT_LOG_SIZE[2], 0, 620000u);
    memset(this->arr_23808, 0, sizeof(this->arr_23808));
    memset(this->arr_15, 0, sizeof(this->arr_15));
    this->Byte_a = 0;
    memset(this->BaseScriptMaxPointers, 0, sizeof(this->BaseScriptMaxPointers));
    this->field_C1DAE = 0;
    memset(this->MissionScriptSize, 0, sizeof(this->MissionScriptSize));
    this->MissionPtrMaybe = 0;
    this->shouldBeEqTo1 = 1;
    this->Bool_A = 0;
    this->Health = 0;
    this->field_314 = 0;
    this->field_318 = 0;
    this->field_31C = 0;
    this->field_320 = 0;
    this->field_324 = 0;
    this->field_328 = 0;
    this->field_32C = 0;
    this->field_330 = 0;
    this->field_334 = 0;
    this->field_338 = 0;
    this->field_33C = 0;
    this->field_340 = 0;
    this->field_348 = 0;
    this->field_34C = 0;
    this->int_A = 0;
    this->Gang = Yakuza;
    this->field_C1E70 = 87;
    this->field_356 = 0;
    this->field_358 = 0;
    this->field_35A = 0;
    this->field_355 = 0;
    this->field_C1E2E = 0;
    this->field_C1E2D = 0;
    this->field_468 = 0;
    if ( do_miss_logging )
        sub_461690(dword_664D18, "test\\MISS_LOG.TXT", 1);
    *(_DWORD *)this->Name = 0;
    unk_6644B0 = 0;
    unk_6644B4 = 0;
    this->field_460 = 0;
    this->field_464 = 0;
    memset(this->arr2_15, 0, sizeof(this->arr2_15));
    this->field_C1E6E = 0;
    this->field_C1E2F = 0;
    this->field_C1E31 = 0;
    memset(this->arr_12, 0, sizeof(this->arr_12));
    this->field_C1EA4 = 0;
}

//=============================================================================
// Destructor
//=============================================================================
MissionManager::~MissionManager()
{
    MissionManager::MissionManagerDes();
}

MissionManager* MissionManager::MissionManager_Des(char a2)
{
    MissionManager::MissionManagerDes();
    if ( (a2 & 1) != 0 )
        free(this);
    return this;
}

void MissionManager::MissionManagerDes()
{
    if ( gMissionScriptObjects )
    {
        free(gMissionScriptObjects);
        gMissionScriptObjects = 0;
    }
    int* v2 = (int*)this->EVENT_LOG_SIZE[1];
    if ( v2 )
    {
        memset(v2 + 1, 0, 3996u);
        free_0((void*)this->EVENT_LOG_SIZE[1]);
        this->EVENT_LOG_SIZE[1] = 0;
    }
    if ( this->EVENT_LOG_SIZE[0] )
    {
        free_0((void*)this->EVENT_LOG_SIZE[0]);
        this->EVENT_LOG_SIZE[0] = 0;
    }
    memset(unk_664590, 0, 0x748u);
    if ( gTrafficManager )
    {
        free(gTrafficManager);
        gTrafficManager = 0;
    }
    this->field_328 = 0;
    this->field_32C = 0;
    this->field_330 = 0;
    this->field_334 = 0;
    this->field_340 = 0;
    this->field_338 = 0;
    this->field_33C = 0;
    this->field_348 = 0;
    this->field_34C = 0;
    this->int_A = 0;
    unk_6644B4 = 0;
    unk_6644B0 = 0;
}

char MissionManager::MissionManager_1()
{
    MissionManager* MissionPtrMaybe = this->MissionPtrMaybe;
    return MissionPtrMaybe && *(_DWORD*)&MissionPtrMaybe->field_0;
}

//=============================================================================
// sub_474F00
//=============================================================================
_WORD* MissionManager::sub_474F00(__int16 a2)
{
    void* v2 = (void*)this->EVENT_LOG_SIZE[1];
    int v3 = 0;
    _WORD* result = (_WORD*)*((_DWORD*)v2 + 1);
    if ( !result )
        return 0;
    while ( *result != a2 )
    {
        result = (_WORD*)*((_DWORD*)v2 + (unsigned __int16)++v3 + 1);
        if ( !result )
            return 0;
    }
    return result;
}

//=============================================================================
// sub_474F30
//=============================================================================
int MissionManager::sub_474F30(const char* a2)
{
    int v3 = 0;
    int v4 = *((_DWORD*)this->EVENT_LOG_SIZE[1] + 1);
    if ( !v4 )
        return 0;
    while ( _strnicmp(a2, (const char*)(v4 + 9), *(unsigned __int8*)(v4 + 8)) )
    {
        v4 = *((_DWORD*)this->EVENT_LOG_SIZE[1] + (unsigned __int16)++v3 + 1);
        if ( !v4 )
            return 0;
    }
    return v4;
}

//=============================================================================
// sub_475A20
//=============================================================================
bool MissionManager::sub_475A20()
{
    return this->Bool_A;
}

//=============================================================================
// sub_475A30
//=============================================================================
char MissionManager::sub_475A30()
{
    return this->field_C1E2D;
}

//=============================================================================
// sub_475A40
//=============================================================================
void MissionManager::sub_475A40(char a2)
{
    this->field_C1E2D = a2;
}

//=============================================================================
// sub_475CA0
//=============================================================================
int MissionManager::sub_475CA0()
{
    int result;
    strcpy((char*)unk_664590, (const char*)MapGm_GetMapName(&gMapGm));
    strcpy(byte_6645A9, (const char*)MapGm_GetStyleFile(&gMapGm));
    strcpy(byte_6645C2, (const char*)MapGm_GetScriptName(&gMapGm));
    unk_6645A8 = 10;
    unk_6645C1 = 10;
    unk_6645DA = 10;
    unk_6645DB = MapGm_GetPlayerArena(&gMapGm);
    unk_6645DC = MapGm_GetBonusStage(&gMapGm);
    LOBYTE(result) = MapGm_GetGang(&gMapGm);
    unk_6645DD = result;
    return result;
}

//=============================================================================
// sub_475D30
//=============================================================================
_WORD* MissionManager::sub_475D30(unsigned __int16 a2)
{
    unsigned int v3 = 0;
    char* i;
    for ( i = (char*)this->EVENT_LOG_SIZE[0]; v3 < a2; i += *(unsigned __int8*)(i + 8) + 9 )
        v3 += *(unsigned __int8*)(i + 8) + 9;
    void* Buffer = createBuffer(0xFA0u);
    this->EVENT_LOG_SIZE[1] = (int)Buffer;
    memset(Buffer, 0, 0xFA0u);
    _WORD* result = (_WORD*)(int)a2;
    unsigned __int8* v8 = (unsigned __int8*)this->EVENT_LOG_SIZE[0];
    int v9 = 0;
    unsigned int v10 = 0;
    if ( a2 )
    {
        do
        {
            *((_WORD*)v8 + 1) = (_WORD)MapRelatedStruct_sub_464D00(gMapRelatedStruct, (char*)v8 + 9, strlen((const char*)v8 + 9));
            *((_DWORD*)this->EVENT_LOG_SIZE[1] + v9 + 1) = (int)v8;
            int v11 = v8[8] + 9;
            v10 += v11;
            v8 += v11;
            ++v9;
        }
        while ( v10 < a2 );
        result = (_WORD*)this->EVENT_LOG_SIZE[1];
        *result = v9;
    }
    else
    {
        *(_WORD*)this->EVENT_LOG_SIZE[1] = 0;
    }
    return result;
}

//=============================================================================
// ExtractFileNameWithoutExtension
//=============================================================================
char* MissionManager::ExtractFileNameWithoutExtension()
{
    char* result = strrchr(this->pathToScriptFile, '\\');
    if ( result )
    {
        char* Name = this->Name;
        ++result;
        *(_DWORD*)this->Name = 0;
        this->field_460 = 0;
        this->field_464 = 0;
        size_t v4 = strlen(result);
        if ( v4 )
        {
            while ( result[v4] != '.' )
            {
                if ( !--v4 )
                    return result;
            }
            return strncpy(Name, result, v4);
        }
    }
    return result;
}

//=============================================================================
// sub_475E90
//=============================================================================
__int16 MissionManager::sub_475E90(FileMgr* a2)
{
    int size = 0;
    if ( gMissionManager.shouldBeEqTo1 )
    {
        int v6 = MissionManager::sub_474F30((const char*)a2);
        int v7 = *(unsigned __int16*)(v6 + 2);
        short v8 = *((_WORD*)gMissionManager.BaseScriptMaxPointers + v7);
        size = v8;
        short v11_placeholder = *((_WORD*)gMissionManager.arr_15 + v7);
        memcpy(
            (char*)gMissionManager.OBJECTIVE_DATA_SIZE + 2 * (unsigned __int16)v8,
            &gMissionManager.arr_23808[768 * v7],
            0xC00u);
        memcpy(
            (char*)gMissionManager.Script
            + *((unsigned __int16*)gMissionManager.OBJECTIVE_DATA_SIZE + (unsigned __int16)size),
            &gMissionManager.EVENT_LOG_SIZE[5000 * *(__int16*)(v6 + 2) + 2],
            gMissionManager.MissionScriptSize[*(__int16*)(v6 + 2)]);
    }
    else
    {
        strcpy(gStr, "data\\");
        strcat(gStr, (const char*)a2);
        FileMgr::SetFilePath(gStr);
        FileMgr::FileOpen(0, gStr);
        a2 = (FileMgr*)2;
        FileMgr::Read((FILE*)&size, (SIZE_T*)&a2);
        a2 = (FileMgr*)2;
        FileMgr::Read((FILE*)&a2, (SIZE_T*)&a2);
        a2 = (FileMgr*)4;
        int v10;
        FileMgr::Read((FILE*)&v10, (SIZE_T*)&a2);
        a2 = (FileMgr*)3072;
        FileMgr::Read((FILE*)((char*)this->OBJECTIVE_DATA_SIZE + 2 * (unsigned __int16)size), (SIZE_T*)&a2);
        partOfLoadScrip(
            (char*)this->Script + *((unsigned __int16*)this->OBJECTIVE_DATA_SIZE + (unsigned __int16)size),
            (int*)&v10);
        FileMgr::CloseFile(0);
    }
    return size;
}

//=============================================================================
// sub_476070
//=============================================================================
unsigned __int16* MissionManager::sub_476070()
{
    unsigned __int16 v2 = 0;
    int v12 = 0;
    int v13 = 0;
    unsigned __int16* result = (unsigned __int16*)this->EVENT_LOG_SIZE[1];
    if ( *result )
    {
        do
        {
            int v4 = *(_DWORD*)&result[2 * v2 + 2];
            if ( *(_BYTE*)(v4 + 4) == 21 )
            {
                size_t v5 = strlen((const char*)(v4 + 9));
                *(_BYTE*)(v5 + v4 + 6) = 83;
                *(_BYTE*)(v5 + v4 + 7) = 67;
                *(_BYTE*)(v5 + v4 + 8) = 82;
                if ( this->shouldBeEqTo1 == 1 )
                {
                    sprintf(gStr, "data\\%s\\", this->Name);
                    strncat(gStr, (const char*)(v4 + 9), *(unsigned __int8*)(v4 + 8));
                    FileMgr::FileOpen(0, gStr);
                    int fileSize1;
                    SIZE_T v14 = 2;
                    FileMgr::Read((FILE*)&fileSize1, &v14);
                    *((_WORD*)this->BaseScriptMaxPointers + (unsigned __int16)v12) = (_WORD)fileSize1;
                    int fileSize2;
                    v14 = 2;
                    FileMgr::Read((FILE*)&fileSize2, &v14);
                    *((_WORD*)this->arr_15 + (unsigned __int16)v12) = (_WORD)fileSize2;
                    int fileSize3;
                    v14 = 4;
                    FileMgr::Read((FILE*)&fileSize3, &v14);
                    int* v8 = &this->MissionScriptSize[(unsigned __int16)v12];
                    *v8 = fileSize3;
                    v14 = 3072;
                    FileMgr::Read((FILE*)&this->arr_23808[768 * (unsigned __int16)v12], &v14);
                    partOfLoadScrip(&this->EVENT_LOG_SIZE[5000 * (unsigned __int16)v12 + 2], v8);
                    FileMgr::CloseFile(0);
                    *(_WORD*)(v4 + 2) = v12;
                    v12 = (unsigned __int16)v12 + 1;
                }
            }
            result = (unsigned __int16*)this->EVENT_LOG_SIZE[1];
            v2 = ++*(_DWORD*)&v2;
        }
        while ( v2 < *result );
    }
    return result;
}

//=============================================================================
// StartMission
//=============================================================================
MissionManager* MissionManager::StartMission(unsigned __int16 a2)
{
    if ( *((_WORD*)this->OBJECTIVE_DATA_SIZE + a2) )
        return (MissionManager*)((char*)this->Script + *((unsigned __int16*)this->OBJECTIVE_DATA_SIZE + a2));
    else
        return 0;
}

//=============================================================================
// sub_476240
//=============================================================================
int* MissionManager::sub_476240(int a2, int a3)
{
    int* result = this->arr_96;
    int v4 = 0;
    while ( *result != a2 || result[1] != a3 )
    {
        result += 3;
        if ( (unsigned __int16)++v4 >= 0x20u )
            return 0;
    }
    return result;
}

//=============================================================================
// sub_476280
//=============================================================================
int* MissionManager::sub_476280(int a2, int a3, __int16 a4)
{
    int* result = this->arr_96;
    int v5 = 0;
    do
    {
        if ( !*((_WORD*)result + 4) )
            break;
        result += 3;
        ++v5;
    }
    while ( (unsigned __int16)v5 < 0x20u );
    *result = a2;
    result[1] = a3;
    *((_WORD*)result + 4) = a4;
    ++this->field_0;
    return result;
}

//=============================================================================
// sub_476320
//=============================================================================
int* MissionManager::sub_476320(int a2, int a3)
{
    int* result = this->RuntimeCache;
    int v4 = 0;
    while ( *result != a2 || result[1] != a3 )
    {
        result += 3;
        if ( (unsigned __int16)++v4 >= 20u )
            return 0;
    }
    return result;
}

//=============================================================================
// sub_476370
//=============================================================================
int* MissionManager::sub_476370(int a2, int a3, __int16 a4)
{
    int* result = this->RuntimeCache;
    int v5 = 0;
    do
    {
        if ( !*((_WORD*)result + 4) )
            break;
        result += 3;
        ++v5;
    }
    while ( (unsigned __int16)v5 < 0x14u );
    *result = a2;
    result[1] = a3;
    *((_WORD*)result + 4) = a4;
    ++this->field_184;
    return result;
}

//=============================================================================
// sub_4763B0
//=============================================================================
_DWORD* MissionManager::sub_4763B0(int a2, int a3)
{
    _DWORD* result = (_DWORD*)MissionManager::sub_476320(a2, a3);
    if ( result )
    {
        *result = 0;
        result[1] = 0;
        *((_WORD*)result + 4) = 0;
        --this->field_184;
    }
    return result;
}

//=============================================================================
// sub_4763E0
//=============================================================================
char* MissionManager::sub_4763E0(int a2)
{
    char* result = (char*)this->RuntimeCache;
    int v3 = 0;
    while ( *((_DWORD*)result + 1) != a2 )
    {
        result += 12;
        if ( (unsigned __int16)++v3 >= 0x14u )
            return 0;
    }
    return result;
}

//=============================================================================
// sub_476400
//=============================================================================
char MissionManager::sub_476400(int a2, char a3, char a4)
{
    int* v5 = 0;
    int* arr_30 = this->arr_30;
    unsigned __int8 i;
    for ( i = 0; i < 0xFu; ++i )
    {
        if ( !*arr_30 && !*((_BYTE*)arr_30 + 4) && !v5 )
            v5 = arr_30;
        if ( *arr_30 == a2 )
        {
            char v8 = *((_BYTE*)arr_30 + 4);
            if ( (v8 == a3 || v8 == 23) && (a4 ? sub_4759C0(arr_30) : sub_4759A0(arr_30)) )
                return 1;
        }
        arr_30 += 2;
    }
    if ( v5 )
    {
        *((_BYTE*)v5 + 4) = a3;
        *v5 = a2;
        *((_BYTE*)v5 + 6) = 2 * (a4 != 0) + 2;
        ++this->field_278;
    }
    return 0;
}

//=============================================================================
// sub_4764D0
//=============================================================================
char MissionManager::sub_4764D0(int a2, char a3)
{
    int v4 = 15;
    int* arr_30 = this->arr_30;
    char result;
    do
    {
        result = a2;
        if ( *arr_30 != a2 )
            goto LABEL_8;
        if ( !a3 )
        {
            result = sub_4759A0(arr_30);
            if ( !result )
                goto LABEL_8;
LABEL_7:
            *arr_30 = 0;
            *((_BYTE*)arr_30 + 4) = 0;
            *((_BYTE*)arr_30 + 5) = 0;
            *((_BYTE*)arr_30 + 6) = 0;
            --this->field_278;
            goto LABEL_8;
        }
        result = sub_4759C0(arr_30);
        if ( result )
            goto LABEL_7;
LABEL_8:
        arr_30 += 2;
        --v4;
    }
    while ( v4 );
    return result;
}

//=============================================================================
// sub_476530
//=============================================================================
char MissionManager::sub_476530(int a2, int a3, char a4)
{
    int* arr_30 = this->arr_30;
    char result = sub_44AB80(a3);
    char v6 = result;
    unsigned __int8 v7 = 0;
    while ( 1 )
    {
        if ( *arr_30 == a2 )
        {
            result = *((_BYTE*)arr_30 + 4);
            if ( result == 23 || result == v6 )
                break;
        }
        arr_30 += 2;
        if ( (unsigned __int8)++v7 >= 0xFu )
            return result;
    }
    if ( !a4 )
    {
        result = sub_4759A0(arr_30);
        if ( !result )
            return result;
        goto LABEL_11;
    }
    result = sub_4759C0(arr_30);
    if ( result )
    {
LABEL_11:
        char v8 = *((_BYTE*)arr_30 + 6);
        *((_BYTE*)arr_30 + 5) = v6;
        result = v8 | 1;
        *((_BYTE*)arr_30 + 6) = result;
    }
    return result;
}

//=============================================================================
// sub_4765A0
//=============================================================================
bool MissionManager::sub_4765A0(int a2, char a3, char a4)
{
    unsigned __int8 v4 = 0;
    int* i;
    for ( i = this->arr_30; ; i += 2 )
    {
        if ( *i == a2 )
        {
            char v6 = *((_BYTE*)i + 4);
            if ( (v6 == a3 || v6 == 23) && (a4 ? sub_4759C0(i) : sub_4759A0(i)) )
                break;
        }
        if ( ++v4 >= 15u )
            return 0;
    }
    return sub_475980(i);
}

//=============================================================================
// sub_4799D0
//=============================================================================
_DWORD MissionManager::sub_4799D0()
{
    MissionScriptObjectData* v1;
    int* v2 = dword_6644CC;
    MissionScriptObjectData* v13 = v1;
    int* v3 = &dword_6644CC[6];
    _DWORD* started = MissionManager::StartMission(gMissionManager, dword_6644CC[1]);
    char a2[4];
    char v15, v16, v17;
    void* v5 = (void*)sub_401B90(v3, (_BYTE*)a2, unk_664DC4);
    Player_sub_401B40((void*)&v2[3], (S202*)&v15, (int)v5);
    void* v6 = (void*)sub_401B90(&v2[5], (_BYTE*)&v16, unk_664DC4);
    SpriteS1* v7 = (SpriteS1*)Player_sub_401B40((void*)&v2[2], (S202*)&v17, (int)v6);
    AudioSourceParams_sub_463710(&gMissionManager.S9, (int)v7->FirstElement);
    int* v8 = (int*)S202_sub_401B20((S202*)&v2[4], (SpriteS1*)&v17, (PublicTransport*)&unk_664E08);
    int* v9 = (int*)Player_sub_401B40((void*)&v2[4], (S202*)&v16, (int)&unk_664E08);
    AudioSourceParams_sub_41E370(&gMissionManager.S9, *v9, *v8);
    int v10 = started[2];
    if ( v10 && *(_DWORD*)(v10 + 136) != 6 )
    {
        if ( SpriteS1_sub_4BB020(*(SpriteS1**)(v10 + 80), &gMissionManager.S9)
            || sub_4BA6C0(&gMissionManager.S9, *(SpriteS1**)(started[2] + 80)) )
        {
            int* v12 = dword_6644CC;
            v13->field_8 = 1;
            MissionScriptObjectData_sub_476E50(v13, v12);
            return 0;
        }
        v2 = dword_6644CC;
    }
    v13->field_8 = 0;
    MissionScriptObjectData_sub_476E50(v13, v2);
    return 0;
}

//=============================================================================
// sub_47ED20
//=============================================================================
__int16 MissionManager::sub_47ED20(void* a1, void* a2)
{
    unsigned __int8 v3 = 0;
    unsigned __int8* v4 = (unsigned __int8*)gMissionManager.field_340;
    while ( a1 != (void*)*v4 )
    {
        ++v4;
        if ( ++v3 >= 0x13u )
            goto LABEL_8;
    }
    sub_476950(a2, (unsigned __int8)byte_5931FC[v3]);
    if ( (unsigned __int8)byte_5931FC[v3] >= 0x5Bu )
        LOWORD(v4) = sub_476930(a2, 1);
    else
        LOWORD(v4) = sub_476930(a2, 3);
LABEL_8:
    if ( v3 == 19 )
    {
        sub_476930(a2, 3);
        LOWORD(v4) = sub_476950(a2, 65);
    }
    return (__int16)v4;
}

//=============================================================================
// sub_47EDB0
//=============================================================================
char MissionManager::sub_47EDB0(int a2)
{
    MissionManager* started = MissionManager::StartMission(this, a2);
    a2 = 3;
    int v17 = 1;
    int v18;
    S202_sub_40CE30((S202*)&v18, BYTE2(started->arr_96[2]));
    int* v5;
    int v20;
    S202_sub_40CE30((S202*)&v20, BYTE1(started->arr_96[2]));
    char v19;
    SpriteS1* v7 = (SpriteS1*)S202_sub_401B20(0, (SpriteS1*)&v19, (PublicTransport*)&unk_664E08);
    int v22;
    S202_sub_40CE30((S202*)&v22, (unsigned __int8)started->arr_96[2]);
    char v21;
    SpriteS1* v9 = (SpriteS1*)S202_sub_401B20(0, (SpriteS1*)&v21, (PublicTransport*)&unk_664E08);
    int v16 = unk_664E08;
    int v15 = unk_664E08;
    int v14 = *v5;
    int FirstElement = (int)v7->FirstElement;
    int v12 = (int)v9->FirstElement;
    MissionManager* v10 = MissionManager::StartMission(this, HIWORD(started->arr_96[1]));
    return (char)MissionObjective_sub_4C4F30(gMissionObjective, &v17, &a2, v10->arr_96[1], v12, FirstElement, v14, v15, v16);
}

//=============================================================================
// sub_47EE70
//=============================================================================
void MissionManager::sub_47EE70()
{
    unsigned __int16 v1 = 0;
    unsigned __int16 v2 = 0;
    short* OBJECTIVE_DATA_SIZE = this->OBJECTIVE_DATA_SIZE;
    do
    {
        if ( *(_WORD*)OBJECTIVE_DATA_SIZE )
        {
            _WORD* started = (_WORD*)MissionManager::StartMission(this, v2);
            __int16 v5 = started[1];
            if ( v5 == 275 || v5 == 276 )
            {
                int v6 = 4 * v1++;
                *(_WORD*)((char*)&unk_6646C4 + v6) = *started;
                *(_WORD*)((char*)&unk_6646C6 + v6) = started[4];
            }
        }
        ++v2;
        OBJECTIVE_DATA_SIZE = (short*)((char*)OBJECTIVE_DATA_SIZE + 2);
    }
    while ( v2 < 0x1770u );
    unk_6646BA = v1;
    if ( v1 < 0x12Cu )
        memset((void*)(4 * v1 + (int)unk_6646C4), 0, 4 * (300 - v1));
}

//=============================================================================
// sub_47EF10
//=============================================================================
_DWORD* MissionManager::sub_47EF10()
{
    _WORD* v1 = unk_6646C4;
    int v2 = 300;
    _DWORD* result;
    do
    {
        LOWORD(result) = *v1;
        if ( *v1 )
        {
            int v4 = (__int16)v1[1];
            _DWORD* started = (_DWORD*)MissionManager::StartMission(this, (unsigned __int16)result);
            started[2] = v4;
        }
        v1 += 2;
        --v2;
    }
    while ( v2 );
    return result;
}

//=============================================================================
// SaveFile
//=============================================================================
int MissionManager::SaveFile(char* pSaveFileName)
{
    char* FileName = pSaveFileName;
    if ( !pSaveFileName || !*pSaveFileName )
    {
        char PlayerSlotSave = MapGm_GetPlayerSlotSave(&gMapGm);
        sprintf(gStr, "player\\plyslot%d.svg", PlayerSlotSave);
        FileName = gStr;
    }
    MissionManager::sub_47EE70();
    Player_sub_4A6B20((void*)((char*)gGame + 0), (int)&dword_6645E4); // TODO: Game::Player offset
    Object_sub_483D90(gObject, byte_664B74);
    // TODO: qmemcpy(unk_664CA0, &gObject->S63[0].S63_1, 50u);
    memcpy(unk_664CA0, (char*)gObject + 0, 50u);  // placeholder offset
    unk_664CD4 = MapGm_GetSpecialTokens(&gMapGm);
    int v9, v10, v6, v11, v7;
    void* pSaveFileName_ptr;
    MapRelatedStruct_sub_4642A0(gMapRelatedStruct, &pSaveFileName_ptr, &v9, &v10, &v6, &v11, &v7);
    MissionManager::sub_475CA0();
    int a3 = 1864;
    WriteSub_402CF0(FileName, unk_664590, &a3);
    a3 = 4;
    ARWBinarySub_402DA0(FileName, (int)&pSaveFileName_ptr, (int)&a3);
    if ( pSaveFileName_ptr )
        ARWBinarySub_402DA0(FileName, v9, (int)&pSaveFileName_ptr);
    a3 = 4;
    ARWBinarySub_402DA0(FileName, (int)&v6, (int)&a3);
    if ( v6 )
        ARWBinarySub_402DA0(FileName, v10, (int)&v6);
    a3 = 4;
    ARWBinarySub_402DA0(FileName, (int)&v7, (int)&a3);
    int result = v7;
    if ( v7 )
        return ARWBinarySub_402DA0(FileName, v11, (int)&v7);
    return result;
}

//=============================================================================
// sub_47F0B0
//=============================================================================
int MissionManager::sub_47F0B0(char* SaveFileName)
{
    int v10 = 0, v11 = 0;
    int v8 = 0, v7 = 0;
    int size = 0;
    FileMgr* v12 = 0;
    MapRelatedStruct_sub_4642A0(gMapRelatedStruct, &v10, &size, &v11, &v8, &v12, &v7);
    FileMgr::FileOpen(0, SaveFileName);
    SaveFileName = (char*)1864;
    FileMgr::Read((FILE*)unk_664590, (SIZE_T*)&SaveFileName);
    SaveFileName = (char*)4;
    FileMgr::Read((FILE*)&size, (SIZE_T*)&SaveFileName);
    if ( size )
        FileMgr::Read((FILE*)v10, (SIZE_T*)&size);
    SaveFileName = (char*)4;
    FileMgr::Read((FILE*)&v8, (SIZE_T*)&SaveFileName);
    if ( v8 )
        FileMgr::Read((FILE*)v11, (SIZE_T*)&v8);
    SaveFileName = (char*)4;
    FileMgr::Read((FILE*)&v7, (SIZE_T*)&SaveFileName);
    if ( v7 )
        FileMgr::Read((FILE*)v12, (SIZE_T*)&v7);
    MapRelatedStruct_sub_464250((char*)gMapRelatedStruct + 0, size, (unsigned int)v8, (unsigned int)v7); // TODO: MapRelatedStruct::Map offset
    FileMgr::CloseFile(0);
    MissionManager::sub_47EF10();
    Object_sub_485640(gObject, byte_664B74);
    memcpy(&gObject, unk_664CA0, 48u);
    int result = sub_476B10(&gMapGm, unk_664CD4);
    this->Bool_A = 1;
    return result;
}

//=============================================================================
// sub_47F200
//=============================================================================
int MissionManager::sub_47F200(__int16 a3, char a2)
{
    int v3 = (int)MissionScriptObjects_RemoveFirstElement(gMissionScriptObjects);
    MissionScriptObjectData_sub_475B70((void*)v3, a2, a3);
    return v3;
}

//=============================================================================
// sub_47F230
//=============================================================================
_WORD* MissionManager::sub_47F230(__int16 a2, unsigned __int16 a3)
{
    if ( skip_mission )
        return 0;
    unsigned __int16 v3 = 0;
    if ( 6000 - a3 <= 0 )
        return 0;
    _WORD* result;
    while ( 1 )
    {
        result = (_WORD*)MissionManager::StartMission(this, v3 + a3);
        if ( result )
        {
            if ( result[1] == a2 )
                break;
        }
        v3 = (unsigned __int16)(v3 + 1);
        if ( v3 >= 6000 - a3 )
            return 0;
    }
    return result;
}

//=============================================================================
// loadScript
//=============================================================================
unsigned __int8 MissionManager::loadScript(char* ScriptName)
{
    unsigned __int8 result = (unsigned __int8)skip_mission;
    if ( !skip_mission )
    {
        char* pScriptName = ScriptName;
        int index = this->pathToScriptFile - ScriptName;
        char v6;
        do
        {
            v6 = *pScriptName;
            pScriptName[index] = *pScriptName;
            ++pScriptName;
        }
        while ( v6 );
        FileMgr::SetFilePath(this->pathToScriptFile);
        FileMgr::FileOpen(0, this->pathToScriptFile);
        ScriptName = (char*)12000;
        FileMgr::Read((FILE*)this->OBJECTIVE_DATA_SIZE, (SIZE_T*)&ScriptName);
        ScriptName = (char*)65536;
        FileMgr::Read((FILE*)this->Script, (SIZE_T*)&ScriptName);
        ScriptName = (char*)2;
        int size;
        FileMgr::Read((FILE*)&size, (SIZE_T*)&ScriptName);
        void* v9 = (void*)this->EVENT_LOG_SIZE[0];
        ScriptName = (char*)5118;
        partOfLoadScrip(v9, (int*)&ScriptName);
        FileMgr::CloseFile(0);
        MissionManager::sub_475D30(size);
        MissionManager::ExtractFileNameWithoutExtension();
        return (unsigned __int8)MissionManager::sub_476070();
    }
    return result;
}

//=============================================================================
// sub_47F340
//=============================================================================
char MissionManager::sub_47F340(int a2, int a3)
{
    int* v4 = MissionManager::sub_476240(a2, a3);
    int* v5 = v4;
    if ( !v4 )
        return 0;
    MissionManager* started = MissionManager::StartMission(this, *((_WORD*)v4 + 4));
    int v8 = MissionManager::sub_47F200(HIWORD(started->arr_96[2]), 0);
    started->arr_96[1] = v8;
    if ( !v8 )
        return 0;
    __int16 v9 = *(_WORD*)(v8 + 282);
    char result = 1;
    LOWORD(started->arr_96[2]) = v9;
    *v5 = 0;
    v5[1] = 0;
    *((_WORD*)v5 + 4) = 0;
    --this->field_0;
    return result;
}

//=============================================================================
// sub_47F3B0
//=============================================================================
char MissionManager::sub_47F3B0(int a2, int a3)
{
    int* v4 = MissionManager::sub_476320(a2, a3);
    if ( !v4 )
        return 0;
    MissionManager* started = MissionManager::StartMission(this, *((_WORD*)v4 + 4));
    if ( started->field_2 == 168 )
    {
        char result = 1;
        BYTE2(started->arr_96[3]) = 1;
        return result;
    }
    if ( started->field_2 != 213 )
        return 0;
    int v7 = MissionManager::sub_47F200(HIWORD(started->arr_96[2]), 0);
    started->arr_96[1] = v7;
    if ( v7 )
        LOWORD(started->arr_96[2]) = *(_WORD*)(v7 + 282);
    return 1;
}

//=============================================================================
// sub_47F420
//=============================================================================
int* MissionManager::sub_47F420(int a2)
{
    int* result = (int*)MissionManager::sub_4763E0(a2);
    if ( result )
        return MissionManager::sub_4763B0(*result, a2);
    return result;
}

//=============================================================================
// sub_481200
//=============================================================================
int MissionManager::sub_481200()
{
    char v2 = 0;
    char* arr2_15 = this->arr2_15;
    int v6 = 32;
    int result;
    do
    {
        if ( ((1 << v2) & unk_6646BC) != 0 )
        {
            MissionManager* started = MissionManager::StartMission(this, *(_WORD*)arr2_15);
            S63_sub_483C60((EventHandler*)started->arr_96[1], 174);
            MissionManager::sub_47F420(gMissionManager, *(_DWORD*)(started->arr_96[1] + 20));
        }
        ++v2;
        arr2_15 += 2;
        result = --v6;
    }
    while ( v6 );
    return result;
}

//=============================================================================
// sub_481890
//=============================================================================
Player* MissionManager::sub_481890()
{
    Player* result;
    LOBYTE(result) = (char)skip_mission;
    if ( !skip_mission )
    {
        MissionScriptObjectData* pMissionScriptObjectData = (MissionScriptObjectData*)MissionScriptObjects_RemoveFirstElement(gMissionScriptObjects);
        _WORD* v4 = MissionManager::sub_47F230(59, 0);
        if ( v4 )
        {
            // MissionScriptObjectDatar::sub_481400(pMissionScriptObjectData);
            MissionScriptObjectData_sub_475B70(pMissionScriptObjectData, 0, *v4);
            return Game_GetPlayer1(gGame);
        }
        else
        {
            return (Player*)debug_log(0x41u, "miss2.cpp", 12774);
        }
    }
    return result;
}

//=============================================================================
// sub_481900
//=============================================================================
void MissionManager::sub_481900()
{
    if ( skip_mission )
    {
        *(int*)((char*)gCarSystemManager + 0x5C) = 0;
    }
    else
    {
        if ( byte_5931F4 )
        {
            if ( do_miss_logging )
            {
                MissionScriptObjects_sub_47F4D0(gMissionScriptObjects);
                sub_461590(dword_664D18, &dword_56EC54);
            }
        }
        MissionScriptObjects_sub_481380(gMissionScriptObjects);
        *(int*)((char*)gCarSystemManager + 0x5C) = 0;
    }
}
