#include <Windows.h>
#include <stdio.h>
#include "cWindow.h"
#include "DebugLogFile.h"

#include "Registry.h" 

extern Registry gRegistry;


#pragma comment(lib, "version.lib")


bool	*gDoTest=(bool*)0x005EAD80;
bool	*gSkipMission=(bool*)0x005EADAE;
bool	*gShowCycle=(bool*)0x005EADA7;
bool	*gDoBrianTest = (bool*)0x005EAD7D;
bool	*gDoIainTest = (bool*)0x005EAD8D;
bool	*gSkipTiles = (bool*)0x005EAD90;
bool	*gDoShowCounters = (bool*)0x005EAD95;
bool	*gDoShowCamera = (bool*)0x005EAD82;
bool	*gDoShowInput = (bool*)0x005EAD58;
bool	*gDoShowTiming = (bool*)0x005EAD79;
bool	*gDoShowCollisionBox = (bool*)0x005EADB1;
bool	*gDoShowPhysics = (bool*)0x005EAD85;
bool	*gDoShowImaginary = (bool*)0x005EAD6F;
bool	*gSkipUser = (bool*)0x005EAD64;
bool	*gSkipTrafficLights = (bool*)0x005EAD53;
bool	*gSkipRecycling = (bool*)0x005EAD5B;
bool	*gLogCollisions = (bool*)0x005EADB0;
bool	*gDoShowTrafficLightsInfo = (bool*)0x005EAD96;
bool	*gDoShowIds = (bool*)0x005EADA1;
bool	*gLimitRecycling = (bool*)0x005EADAC;
bool	*gNoAnnoyingChars = (bool*)0x005EAD75;
bool	*gSkipSlopes = (bool*)0x005EAD78;
bool	*gSkipLeft = (bool*)0x005EAD67;
bool	*gSkipRight = (bool*)0x005EAD59;
bool	*gSkipTop = (bool*)0x005EAD8C;
bool	*gSkipBottom = (bool*)0x005EAD5F;
bool	*gSkipLid = (bool*)0x005EAD9C;
bool	*gLogRoutefinder = (bool*)0x005EAD99;
bool	*gDoMike = (bool*)0x005EAD81;
bool	*gSkipParticles = (bool*)0x005EAD56;
bool	*gShowHiddenFaces = (bool*)0x005EAD5A;
bool	*gGetAllWeapons = (bool*)0x005EAD74;
bool	*gDoExitAfterReplay = (bool*)0x005EADAD;
bool	*gDontGetCarBack = (bool*)0x005EAD94;
bool	*gDoShowInstruments = (bool*)0x005EAD55;
bool	*gSkipAmbulance = (bool*)0x005EAD6B;
bool	*gSkilPolice = (bool*)0x005EAD5E;
bool	*gSkipFrontend = (bool*)0x005EAD7C;
bool	*gDoInvulnerable = (bool*)0x005EAD71;
bool	*gShowAllArrows = (bool*)0x005EADB2;
bool	*gDoShowHorn = (bool*)0x005EAD7F;
bool	*gKeepWeaponsAfterDeath = (bool*)0x005EAD9E;
bool	*gSkipSkidMarks = (bool*)0x005EADAF;
bool	*gDoShowJuncIds = (bool*)0x005EAD89;
bool	*gDoCornerWindow = (bool*)0x005EAD68;
bool	*gDoInfiniteLives = (bool*)0x005EAD61;
bool	*gDoLoadSaveGame = (bool*)0x005EAD7E;
bool	*gSkipAudio = (bool*)0x005EAD72;
bool	*gDoDebugKeys = (bool*)0x005EAD87;
bool	*gLogRandom = (bool*)0x005EAD63;
bool	*gLogRandomExtra = (bool*)0x005EAD7A;
bool	*gLogInput = (bool*)0x005EAD91;
bool	*gLogDirectInput = (bool*)0x005EAD77;
bool	*gIgnoreReplayHeader = (bool*)0x005EAD86;
bool	*gSkipTrains = (bool*)0x005EAD57;
bool	*gSkipBuses = (bool*)0x005EAD54;
bool	*gSkipQuitConfirm = (bool*)0x005EADAB;
bool	*gDoSyncCheck = (bool*)0x005EADA8;
bool	*gSkipFireEngines = (bool*)0x005EAD8B;
bool	*gShowBriefNumber = (bool*)0x005EADA5;
bool    *gSkipWindowCheck = (bool*)0x005EAD6C;
bool	*gSkipReplaySyncCheck = (bool*)0x005EADA4;
bool	*gDoShowObjectIds = (bool*)0x005EAD52;
bool	*gGoKillPhonesOnAnswer = (bool*)0x005EADB3;
bool	*gDoMissLogging = (bool*)0x005EAD66;
bool	*gDoTextIdTest = (bool*)0x005EAD9A;
bool	*gDoPolice1 = (bool*)0x005EAD60;
bool	*gDoPolice2 = (bool*)0x005EAD9D;
bool	*gDoPolice3 = (bool*)0x005EADA9;
bool	*gSkipDraw = (bool*)0x005EAD88;
bool	*gDoFreeShopping = (bool*)0x005EAD84;
bool	*gSkipDummies = (bool*)0x005EAD69;
bool	*gDoBlood = (bool*)0x005EAD51;
bool	*gDo3DSound = (bool*)0x005EAD50;
bool	*gTestFileGxt = (bool*)0x005EAD73;
bool	*gShowPlayerNames = (bool*)0x005EAD76;
bool    *gByte1 = (bool*)0x005EADA3;
bool    *gByte2 = (bool*)0x005EAD92;
bool* gPlayReplay = (bool*)0x005EADAA;
/*bool* gSmallCar = (bool*);
bool	*gNopCheat = (bool*);
bool	*gGiveMoney20 = (bool*);
bool	*gFireGun = (bool*);
bool	*gJailKey = (bool*);
bool	*gDoubleDamage = (bool*);
bool	*gSUPZZZ0 = (bool*);
bool	*gInvisibility = (bool*);
bool	*gJailFreeCard = (bool*);
bool	*gHealth99 = (bool*);
bool	*gElectroGun = (bool*);
bool	*gIAMDAVEJ = (bool*);
bool	*gMADEMAN = (bool*);
bool	*gAllTower = (bool*);
bool	*gPontMultiplaerX10 = (bool*);
bool	*gBonusAll = (bool*);
bool	*gGiveBasikWeapon = (bool*);
bool	*gElvis = (bool*);
bool	*gBunt = (bool*);
bool	*gNEKKID = (bool*);
void*   *gBinkBufferClose = (bool*);
bool    *gNetworkGame = (bool*);
byte    *gControl = (bool*);
int gData_6735A5;*/

char *aTestReplay0Rep = (char*)0x00595FF0; // 11 масcив


void __stdcall GetVersionLaunch( int * pMajorVersion,  int  * pMinorVersion) {

    // Проверка входных указателей
    if (pMajorVersion == NULL || pMinorVersion == NULL) {
        return;
    }

    // Инициализация выходных значений
    *pMajorVersion = 0;
    *pMinorVersion = 0;

    // Получение размера информации о версии
    DWORD dummyHandle = 0;
    DWORD versionInfoSize = GetFileVersionInfoSizeA("GTA2.EXE", &dummyHandle);

    if (versionInfoSize == 0) {
        return;
    }

    // Выделение памяти (C++98 style)
    BYTE* pVersionInfo = (BYTE*)malloc(versionInfoSize);
    if (pVersionInfo == NULL) {
        return;
    }

    // Получение информации о версии
    if (!GetFileVersionInfoA("GTA2.EXE", 0, versionInfoSize, pVersionInfo)) {
        free(pVersionInfo);
        return;
    }

    // Получение указателя на структуру версии
    VS_FIXEDFILEINFO* pFileInfo = NULL;
    UINT fileInfoLen = 0;

    if (!VerQueryValueA(pVersionInfo, "\\", (LPVOID*)&pFileInfo, &fileInfoLen) ||
        pFileInfo == NULL ||
        fileInfoLen < sizeof(VS_FIXEDFILEINFO))
    {
        free(pVersionInfo);
        return;
    }

    // Извлечение версий с помощью макросов Windows
    *pMajorVersion = HIWORD(pFileInfo->dwFileVersionMS);
    *pMinorVersion = LOWORD(pFileInfo->dwFileVersionMS);
    // Освобождение памяти
  

    free(pVersionInfo);
}

void __stdcall GetDebugParam() {
    *gPlayReplay = gRegistry.GetPlayReplay("play_replay");
    *gByte1 = true;
    *gByte2 = true;

    BYTE pDebugMode = gRegistry.GetReplaynum("replaynum") + 48;

    aTestReplay0Rep[11] = pDebugMode;
    if (!gPlayReplay) {
        if ((pDebugMode - 47) >= 10) {
            pDebugMode = 0;
        }

        gRegistry.SetDebugByteValue("replaynum", pDebugMode);
    }
    *gDoTest = gRegistry.GetParamDebug("do_test");
    writeFileLog((char*)"Param.txt", (char*)"do_test", (char*)"address", *gDoTest);
    *gSkipMission = gRegistry.GetParamDebug("skip_mission");
    *gShowCycle = gRegistry.GetParamDebug("show_cycle");
    *gDoBrianTest = gRegistry.GetParamDebug("do_brian_test");
    *gDoIainTest = gRegistry.GetParamDebug("do_iain_test");
    *gSkipTiles = gRegistry.GetParamDebug("skip_tiles");
    *gDoShowCounters = gRegistry.GetParamDebug("do_show_counters");
    *gDoShowCamera = gRegistry.GetParamDebug("do_show_camera");
    *gDoShowInput = gRegistry.GetParamDebug("do_show_input");
    *gDoShowTiming = gRegistry.GetParamDebug("do_show_timing");
    *gDoShowCollisionBox = gRegistry.GetParamDebug("do_show_collision_box");
    *gDoShowPhysics = gRegistry.GetParamDebug("do_show_physics");
    *gDoShowImaginary = gRegistry.GetParamDebug("do_show_imaginary");
    *gSkipUser = gRegistry.GetParamDebug("skip_user");
    *gSkipTrafficLights = gRegistry.GetParamDebug("skip_traffic_lights");
    *gSkipRecycling = gRegistry.GetParamDebug("skip_recycling");
    *gLogCollisions = gRegistry.GetParamDebug("log_collisions");
    *gDoShowTrafficLightsInfo = gRegistry.GetParamDebug("do_show_traffic_lights_info");
    *gDoShowIds = gRegistry.GetParamDebug("do_show_ids");
    *gLimitRecycling = gRegistry.GetParamDebug("limit_recycling");
    *gNoAnnoyingChars = gRegistry.GetParamDebug("no_annoying_chars");
    *gSkipSlopes = gRegistry.GetParamDebug("skip_slopes");
    *gSkipLeft = gRegistry.GetParamDebug("skip_left");
    *gSkipRight = gRegistry.GetParamDebug("skip_right");
    *gSkipTop = gRegistry.GetParamDebug("skip_top");
    *gSkipBottom = gRegistry.GetParamDebug("skip_bottom");
    *gSkipLid = gRegistry.GetParamDebug("skip_lid");
    *gLogRoutefinder = gRegistry.GetParamDebug("log_routefinder");
    *gDoMike = gRegistry.GetParamDebug("do_mike");
    *gSkipParticles = gRegistry.GetParamDebug("skip_particles");
    *gShowHiddenFaces = gRegistry.GetParamDebug("show_hidden_faces");
    *gGetAllWeapons = gRegistry.GetParamDebug("get_all_weapons");
    *gDoExitAfterReplay = gRegistry.GetParamDebug("do_exit_after_replay");
    *gDontGetCarBack = gRegistry.GetParamDebug("dont_get_car_back");
    *gDoShowInstruments = gRegistry.GetParamDebug("do_show_instruments");
    *gSkipAmbulance = gRegistry.GetParamDebug("skip_ambulance");
    *gSkilPolice = gRegistry.GetParamDebug("skip_police");
    *gSkipFrontend = gRegistry.GetParamDebug("skip_frontend");
    *gDoInvulnerable = gRegistry.GetParamDebug("do_invulnerable");
    *gShowAllArrows = gRegistry.GetParamDebug("show_all_arrows");
    *gDoShowHorn = gRegistry.GetParamDebug("do_show_horn");
    *gKeepWeaponsAfterDeath = gRegistry.GetParamDebug("keep_weapons_after_death");
    *gSkipSkidMarks = gRegistry.GetParamDebug("skip_skidmarks");
    *gDoShowJuncIds = gRegistry.GetParamDebug("do_show_junc_ids");
    *gDoCornerWindow = gRegistry.GetParamDebug("do_corner_window");
    *gDoInfiniteLives = gRegistry.GetParamDebug("do_infinite_lives");
    *gDoLoadSaveGame = gRegistry.GetParamDebug("do_load_savegame");
    *gSkipAudio = gRegistry.GetParamDebug("skip_audio");
    *gDoDebugKeys = gRegistry.GetParamDebug("do_debug_keys");
    *gLogRandom = gRegistry.GetParamDebug("log_random");
    *gLogRandomExtra = gRegistry.GetParamDebug("log_random_extra");
    *gLogInput = gRegistry.GetParamDebug("log_input");
    *gLogDirectInput = gRegistry.GetParamDebug("log_directinput");
    *gIgnoreReplayHeader = gRegistry.GetParamDebug("ignore_replay_header");
    *gSkipTrains = gRegistry.GetParamDebug("skip_trains");
    *gSkipBuses = gRegistry.GetParamDebug("skip_buses");
    *gSkipQuitConfirm = gRegistry.GetParamDebug("skip_quit_confirm");
    *gDoSyncCheck = gRegistry.GetParamDebug("do_sync_check");
    *gSkipFireEngines = gRegistry.GetParamDebug("skip_fire_engines");
    *gShowBriefNumber = gRegistry.GetParamDebug("show_brief_number");
    *gSkipWindowCheck = gRegistry.GetParamDebug("skip_window_check");
    *gSkipReplaySyncCheck = gRegistry.GetParamDebug("skip_replay_sync_check");
    *gDoShowObjectIds = gRegistry.GetParamDebug("do_show_object_ids");
    *gGoKillPhonesOnAnswer = gRegistry.GetParamDebug("do_kill_phones_on_answer");
    *gDoMissLogging = gRegistry.GetParamDebug("do_miss_logging");
    *gDoTextIdTest = gRegistry.GetParamDebug("do_text_id_test");
    *gDoPolice1 = gRegistry.GetParamDebug("do_police_1");
    *gDoPolice2 = gRegistry.GetParamDebug("do_police_2");
    *gDoPolice3 = gRegistry.GetParamDebug("do_police_3");
    *gSkipDraw = gRegistry.GetParamDebug("skip_draw");
    *gDoFreeShopping = gRegistry.GetParamDebug("do_free_shopping");
    *gSkipDummies = gRegistry.GetParamDebug("skip_dummies");
    *gDoBlood = gRegistry.GetParamDebug("do_blood");
    *gDo3DSound = gRegistry.GetParamDebug("do_3d_sound");
    *gTestFileGxt = AllGtxFile();
    *gShowPlayerNames = gRegistry.SetShowPlayerName("show_player_names", 1u);

}

bool __stdcall  AllGtxFile() {
    bool EnglishFile; // bl
    FILE* English; // eax
    FILE* France; // eax
    FILE* German; // eax
    FILE* Italia; // eax
    FILE* Japanese; // eax
    FILE* Spanish; // eax
    bool SpanishFile; // al
    bool FranceFile; // [esp+7h] [ebp-5h]
    bool GermanFile; // [esp+8h] [ebp-4h]
    bool ItaliaFile; // [esp+9h] [ebp-3h]
    bool JapaneseFile; // [esp+Ah] [ebp-2h]

    EnglishFile = 0;
    FranceFile = 0;
    GermanFile = 0;
    ItaliaFile = 0;
    JapaneseFile = 0;
    English = (FILE*)fopen("data\\e.gxt", "rb");
    if (English)
    {
        fclose(English);
        EnglishFile = 1;
    }
    France = (FILE*)fopen("data\\f.gxt", "rb");
    if (France)
    {
        fclose(France);
        FranceFile = 1;
    }
    German = (FILE*)fopen("data\\g.gxt", "rb");
    if (German)
    {
        fclose(German);
        GermanFile = 1;
    }
    Italia = (FILE*)fopen("data\\i.gxt", "rb");
    if (Italia)
    {
        fclose(Italia);
        ItaliaFile = 1;
    }
    Japanese = (FILE*)fopen("data\\j.gxt", "rb");
    if (Japanese)
    {
        fclose(Japanese);
        JapaneseFile = 1;
    }
    Spanish = (FILE*)fopen("data\\s.gxt", "rb");
    if (Spanish)
    {
        fclose(Spanish);
        SpanishFile = 1;
    }
    else
    {
        SpanishFile = 0;
    }
    return !EnglishFile && !FranceFile && !GermanFile && !ItaliaFile && !JapaneseFile && !SpanishFile;
}
