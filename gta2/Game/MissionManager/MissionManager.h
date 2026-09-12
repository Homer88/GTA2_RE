
#ifndef __MISSION_MANAGER_H_
#define __MISSION_MANAGER_H_

#include <windows.h>
#include <cstring>
#include "../../Engine/FileMgr/FileMgr.h"

#ifndef _WORD
#define _WORD WORD
#define _DWORD DWORD
#define _BYTE BYTE
#endif



#include "../../Engine/AudioSourceParams/AudioSourceParams.h"


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

    // Audio params (S9)
    AudioSourceParams S9;

    MissionManager();
    ~MissionManager();
    char MissionManager_1();
    void MissionManagerDes();
    MissionManager* MissionManager_Des(char a2);

    _WORD* FindMission(__int16 a2);
    int FindByName(const char* a2);  // (gm) старый: FindMissionByScriptName -> FindByName
    bool IsGameLoaded();
    char GetMissionStatus();
    void sub_475A40(char a2);
    int CopyMapDetails();
    _WORD* SetupMissionText(unsigned __int16 a2);  // (gm) старый: BuildMissionScriptIndex -> SetupMissionText
    char* ExtractFileNameWithoutExtension();
    __int16 LoadLanguageFile(FileMgr* a2);  // (gm) старый: LoadMissionData -> LoadLanguageFile
    unsigned __int16* LoadScriptFiles();  // (gm) старый: LoadMissionScriptData -> LoadScriptFiles
    MissionManager* StartMission(unsigned __int16 a2);
    int* sub_476240(int a2, int a3);
    int* AddRuntimeTimer(int a2, int a3, __int16 a4);
    int* FindData(int a2, int a3);  // (gm) старый: FindMissionTarget -> FindData
    int* sub_476370(int a2, int a3, __int16 a4);
    _DWORD* RemoveData(int a2, int a3);  // (gm) старый: RemoveMissionTarget -> RemoveData
    char* FindDataById(int a2);  // (gm) старый: FindMissionTargetByIndex -> FindDataById
    char AddOrCheckMissionTarget(int a2, char a3, char a4);
    char sub_4764D0(int a2, char a3);
    char UpdateMissionItem(int a2, int a3, char a4);
    bool FindMissionItem(int a2, char a3, char a4);
    _DWORD sub_4799D0();
    __int16 SetMissionGradeLetter(void* a1, void* a2);
    char sub_47EDB0(int a2);
    void BuildActiveMissionList();
    _DWORD* RestoreMissionValues();  // (gm) старый: StartAllMissions -> RestoreMissionValues
    int SaveFile(char* pSaveFileName);
    int LoadMissionMap(char* SaveFileName);
    int ContinueQueuedMissionLine(__int16 a3, char a2);
    _WORD* sub_47F230(__int16 a2, unsigned __int16 a3);
    unsigned __int8 loadScript(char* ScriptName);
    char sub_47F340(int a2, int a3);
    char ActivateMissionTarget(int a2, int a3);
    int* UnregisterTarget(int a2);
    int ClearMissionLineFlags();
    Player* StartNextMission();
    void ProcessMissionQueue();

    // --- анализированные функции миссийной подсистемы (2026-09-07) ---
    unsigned char GetOpcodeParamType(unsigned int opcode);
    void ListAddFront(void* node);  // (gm) старый: AddMissionArgNode -> ListAddFront
    void SetCarFlag_0x8d();
    void PopViewport();
    unsigned char CheckMissionZone(unsigned int op, int x, int y);
    unsigned char GiveWeaponOpcode(void* self);

// ==== импорт имён из gm ====
    // 3 функций
    // 0x00475E60: MissionManager::IsMissionTarget
    void IsMissionTarget();
    // 0x0047D615: MissionManager::DrawMissionGraphic
    void DrawMissionGraphic();
    // 0x0047ECB0: MissionManager::ProcessAnimationEvent
    void ProcessAnimationEvent();
    // 0x00479B70
    // (gm) ������: Script_CheckPedInVehicle -> MissionManager::CheckPedInVehicle
    void CheckPedInVehicle();
    // 0x00479CC0
    // (gm) ������: Script_AddMissionMoney -> MissionManager::GivePlayerMoney
    void GivePlayerMoney();
    // 0x00479E10
    // (gm) ������: Script_SpawnPed -> MissionManager::SpawnRewardObject
    void SpawnRewardObject();
    // 0x0047A1E0
    // (gm) ������: Script_AssignPedToCar -> MissionManager::PlacePedInCar
    void PlacePedInCar();
    // 0x0047A330
    // (gm) ������: Script_SetPedPosition -> MissionManager::SetPedDestination
    void SetPedDestination();
    // 0x0047A620
    // (gm) ������: MapRelatedStruct::RunMissionObjectScript -> MissionManager::GetMarkerSprite
    void GetMarkerSprite();
    // 0x0047ACC0
    // (gm) ������: MapRelatedStruct::RunGangWarCheckScript -> MissionManager::CheckGangWar
    void CheckGangWar();
    // 0x0047B430
    // (gm) ������: Script_GetPlayerMoney -> MissionManager::SavePlayerMoney
    void SavePlayerMoney();
    // 0x0047BE00
    // (gm) ������: Script_CheckCarMatch -> MissionManager::CheckCarAvailability
    void CheckCarAvailability();
    // 0x0047C8A0
    // (gm) ������: MissionManager::CheckMissionObjectType -> MissionManager::CheckMissionState
    void CheckMissionState();
    // 0x0047D040
    // (gm) ������: MissionManager::CheckMissionObjectState -> MissionManager::CheckMissionCondition
    void CheckMissionCondition();
    // 0x0047D260
    // (gm) ������: MissionManager::ExecuteArithmeticOpcode -> MissionManager::ExecuteArithmetic
    void ExecuteArithmetic();
};

#pragma pack(pop)

#endif