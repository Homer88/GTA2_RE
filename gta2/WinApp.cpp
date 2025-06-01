#include <stdlib.h>
#include <cstdio> // Для FILE, fopen, fclose
#include <windows.h>
#include <winver.h>
#include "WinMain.h"
#include "Global.h"

#pragma comment(lib, "version.lib")

//Плобальные переменные 
bool	gDoTest;
bool	gSkipMission;
bool	gShowCycle;
bool	gDoBrianTest;
bool	gDoIainTest;
bool	gSkipTiles;
bool	gDoShowCounters;
bool	gDoShowCamera;
bool	gDoShowInput;
bool	gDoShowTiming;
bool	gDoShowCollisionBox;
bool	gDoShowPhysics;
bool	gDoShowImaginary;
bool	gSkipUser;
bool	gSkipTrafficLights;
bool	gSkipRecycling;
bool	gLogCollisions;
bool	gDoShowTrafficLightsInfo;
bool	gDoShowIds;
bool	gLimitRecycling;
bool	gNoAnnoyingChars;
bool	gSkipSlopes;
bool	gSkipLeft;
bool	gSkipRight;
bool	gSkipTop;
bool	gSkipBottom;
bool	gSkipLid;
bool	gLogRoutefinder;
bool	gDoMike;
bool	gSkipParticles;
bool	gShowHiddenFaces;
bool	gGetAllWeapons;
bool	gDoExitAfterReplay;
bool	gDontGetCarBack;
bool	gDoShowInstruments;
bool	gSkipAmbulance;
bool	gSkilPolice;
bool	gSkipFrontend;
bool	gDoInvulnerable;
bool	gShowAllArrows;
bool	gDoShowHorn;
bool	gKeepWeaponsAfterDeath;
bool	gSkipSkidMarks;
bool	gDoShowJuncIds;
bool	gDoCornerWindow;
bool	gDoInfiniteLives;
bool	gDoLoadSaveGame;
bool	gSkipAudio;
bool	gDoDebugKeys;
bool	gLogRandom;
bool	gLogRandomExtra;
bool	gLogInput;
bool	gLogDirectInput;
bool	gIgnoreReplayHeader;
bool	gSkipTrains;
bool	gSkipBuses;
bool	gSkipQuitConfirm;
bool	gDoSyncCheck;
bool	gSkipFireEngines;
bool	gShowBriefNumber;
bool    gSkipWindowCheck;
bool	gSkipReplaySyncCheck;
bool	gDoShowObjectIds;
bool	gGoKillPhonesOnAnswer;
bool	gDoMissLogging;
bool	gDoTextIdTest;
bool	gDoPolice1;
bool	gDoPolice2;
bool	gDoPolice3;
bool	gSkipDraw;
bool	gDoFreeShopping;
bool	gSkipDummies;
bool	gDoBlood;
bool	gDo3dSound;
bool	gTestFileGxt;
bool	gShowPlayerNames;
bool    gByte1;
bool    gByte2;
bool    gPlayReplay;
bool    gSmallCar;
bool	gNopCheat;
bool	gGiveMoney20;
bool	gFireGun;
bool	gJailKey;
bool	gDoubleDamage;
bool	gSUPZZZ0;
bool	gInvisibility;
bool	gJailFreeCard;
bool	gHealth99;
bool	gElectroGun;
bool	gIAMDAVEJ;
bool	gMADEMAN;
bool	gAllTower;
bool	gPontMultiplaerX10;
bool	gBonusAll;
bool	gGiveBasikWeapon;
bool	gElvis;
bool	gBunt;
bool	gNEKKID;

// Обработчик сообщений
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Рисуем текст
            TextOut(hdc, 50, 50, "Hello, C++98!", 12);
            
            EndPaint(hwnd, &ps);
            return 0;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}




// Получаем версию EXE
void GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion){
	
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




//Получение Debug переменных
void GetDebugParam() {
   gPlayReplay = gRegistry.GetPlayReplay("play_replay");
    gByte1 = true;
    gByte2 = true;
    
    BYTE pDebugMode = gRegistry.GetReplaynum("replaynum")+48;

    //????
    //aTextReplay0Rep[11] = pDebugMode;
    if (!gPlayReplay) {
        if ((pDebugMode-47)>=10){
            pDebugMode = 0;
			}
		
        gRegistry.SetDebugByteValue("replaynum", pDebugMode);
    }

    gDoTest =       gRegistry.GetParamDebug("do_test");
    gSkipMission =  gRegistry.GetParamDebug("skip_mission");
    gShowCycle =    gRegistry.GetParamDebug("show_cycle");
    gDoBrianTest =  gRegistry.GetParamDebug("do_brian_test");
    gDoIainTest =   gRegistry.GetParamDebug("do_iain_test");
    gSkipTiles =    gRegistry.GetParamDebug("skip_tiles");
    gDoShowCounters = gRegistry.GetParamDebug("do_show_counters");
    gDoShowCamera = gRegistry.GetParamDebug("do_show_camera");
    gDoShowInput = gRegistry.GetParamDebug("do_show_input");
    gDoShowTiming = gRegistry.GetParamDebug("do_show_timing");
    gDoShowCollisionBox = gRegistry.GetParamDebug("do_show_collision_box");
    gDoShowPhysics = gRegistry.GetParamDebug("do_show_physics");
    gDoShowImaginary = gRegistry.GetParamDebug("do_show_imaginary");
    gSkipUser = gRegistry.GetParamDebug("skip_user");
    gSkipTrafficLights = gRegistry.GetParamDebug("skip_traffic_lights");
    gSkipRecycling = gRegistry.GetParamDebug("skip_recycling");
    gLogCollisions = gRegistry.GetParamDebug("log_collisions");
    gDoShowTrafficLightsInfo = gRegistry.GetParamDebug("do_show_traffic_lights_info");
    gDoShowIds = gRegistry.GetParamDebug("do_show_ids");
    gLimitRecycling = gRegistry.GetParamDebug("limit_recycling");
    gNoAnnoyingChars = gRegistry.GetParamDebug("no_annoying_chars");
    gSkipSlopes = gRegistry.GetParamDebug("skip_slopes");
    gSkipLeft = gRegistry.GetParamDebug("skip_left");
    gSkipRight = gRegistry.GetParamDebug("skip_right");
    gSkipTop = gRegistry.GetParamDebug("skip_top");
    gSkipBottom = gRegistry.GetParamDebug("skip_bottom");
    gSkipLid = gRegistry.GetParamDebug("skip_lid");
    gLogRoutefinder = gRegistry.GetParamDebug("log_routefinder");
    gDoMike = gRegistry.GetParamDebug("do_mike");
    gSkipParticles = gRegistry.GetParamDebug("skip_particles");
    gShowHiddenFaces = gRegistry.GetParamDebug("show_hidden_faces");
    gGetAllWeapons = gRegistry.GetParamDebug("get_all_weapons");
    gDoExitAfterReplay = gRegistry.GetParamDebug("do_exit_after_replay");
    gDontGetCarBack = gRegistry.GetParamDebug("dont_get_car_back");
    gDoShowInstruments = gRegistry.GetParamDebug("do_show_instruments");
    gSkipAmbulance = gRegistry.GetParamDebug("skip_ambulance");
    gSkilPolice = gRegistry.GetParamDebug("skip_police");
    gSkipFrontend = gRegistry.GetParamDebug("skip_frontend");
    gDoInvulnerable = gRegistry.GetParamDebug("do_invulnerable");
    gShowAllArrows = gRegistry.GetParamDebug("show_all_arrows");
    gDoShowHorn = gRegistry.GetParamDebug("do_show_horn");
    gKeepWeaponsAfterDeath = gRegistry.GetParamDebug("keep_weapons_after_death");
    gSkipSkidMarks = gRegistry.GetParamDebug("skip_skidmarks");
    gDoShowJuncIds = gRegistry.GetParamDebug("do_show_junc_ids");
    gDoCornerWindow = gRegistry.GetParamDebug("do_corner_window");
    gDoInfiniteLives = gRegistry.GetParamDebug("do_infinite_lives");
    gDoLoadSaveGame = gRegistry.GetParamDebug("do_load_savegame");
    gSkipAudio = gRegistry.GetParamDebug("skip_audio");
    gDoDebugKeys = gRegistry.GetParamDebug("do_debug_keys");
    gLogRandom = gRegistry.GetParamDebug("log_random");
    gLogRandomExtra = gRegistry.GetParamDebug("log_random_extra");
    gLogInput = gRegistry.GetParamDebug("log_input");
    gLogDirectInput = gRegistry.GetParamDebug("log_directinput");
    gIgnoreReplayHeader = gRegistry.GetParamDebug("ignore_replay_header");
    gSkipTrains = gRegistry.GetParamDebug("skip_trains");
    gSkipBuses = gRegistry.GetParamDebug("skip_buses");
    gSkipQuitConfirm = gRegistry.GetParamDebug("skip_quit_confirm");
    gDoSyncCheck = gRegistry.GetParamDebug("do_sync_check");
    gSkipFireEngines = gRegistry.GetParamDebug("skip_fire_engines");
    gShowBriefNumber = gRegistry.GetParamDebug("show_brief_number");
    //
    gSkipWindowCheck = gRegistry.GetParamDebug("skip_window_check");
    gSkipReplaySyncCheck = gRegistry.GetParamDebug("skip_replay_sync_check");
    gDoShowObjectIds = gRegistry.GetParamDebug("do_show_object_ids");
    gGoKillPhonesOnAnswer = gRegistry.GetParamDebug("do_kill_phones_on_answer");
    gDoMissLogging = gRegistry.GetParamDebug("do_miss_logging");
    gDoTextIdTest = gRegistry.GetParamDebug("do_text_id_test");
    gDoPolice1 = gRegistry.GetParamDebug("do_police_1");
    gDoPolice2 = gRegistry.GetParamDebug("do_police_2");
    gDoPolice3 = gRegistry.GetParamDebug("do_police_3");
    gSkipDraw = gRegistry.GetParamDebug("skip_draw");
    gDoFreeShopping = gRegistry.GetParamDebug("do_free_shopping");
    gSkipDummies = gRegistry.GetParamDebug("skip_dummies");
    gDoBlood = gRegistry.GetParamDebug("do_blood");
    gDo3dSound = gRegistry.GetParamDebug("do_3d_sound");
    gTestFileGxt = AllGtxFile();
    gShowPlayerNames = gRegistry.SetShowPlayerName("show_player_names", 1u);

}


bool AllGtxFile() {

    // Список файлов для проверки
    const char* gxtFiles[] = {
        "data\\e.gxt",  // English
        "data\\f.gxt",  // French
        "data\\g.gxt",  // German
        "data\\i.gxt",  // Italian
        "data\\j.gxt",  // Japanese
        "data\\s.gxt"   // Spanish
    };
    enum File
    {
        English,
        French,
        German,
        Italian,
        Japanese,
        Spanish,

    };
    const int fileCount = sizeof(gxtFiles) / sizeof(gxtFiles[0]);
    for (int i = 0; i < fileCount; ++i) {
        FILE* file = fopen(gxtFiles[i], "rb");
        if (file) {
            fclose(file);
        }
		else{
            return false;
			}
    }
    return true;
}


bool DefautInitParam(){

    gShowAllArrows = false;
    gGoKillPhonesOnAnswer = false;
    gSkipDummies = false;
    gSkipTiles = false;
    gDoTest = false;
    gSkipMission = false;
    gDoBrianTest = false;
    gDoIainTest = false;
    gSkipUser = false;
    gSkipTrafficLights = false;
    gSkipRecycling = false;
    gLogCollisions = false;
    gDoShowTrafficLightsInfo = false;
    gLimitRecycling = false;
    gNoAnnoyingChars = false;
    gSkipSlopes = false;
    gSkipLeft = false;
    gSkipRight = false;
    gSkipTop = false;
    gSkipBottom = false;
    gSkipLid = false;
    gLogRoutefinder = false;
    gDoMike = false;
    gSkipParticles = false;
    gShowHiddenFaces = false;
    gGetAllWeapons = false;
    gDoExitAfterReplay = false;
    gDontGetCarBack = false;
    gSkipAmbulance = false;
    gSkipFrontend = false;
    gDoInvulnerable = false;
    gKeepWeaponsAfterDeath = false;
    gSkipSkidMarks = false;
    gDoInfiniteLives = false;
    gDoLoadSaveGame = false;
    gSkipAudio = false;
    gDoDebugKeys = false;
    gLogInput = false;
    gLogDirectInput = false;
    gIgnoreReplayHeader = false;
    gSkipTrains = false;
    gSkipBuses = false;
    gSkipQuitConfirm = false;
    gSkipFireEngines = false;
    gSkipWindowCheck = false;
    gDoMissLogging = false;
    gNopCheat = false;
    gDoPolice1 = false;
    gDoPolice2 = false;
    gDoPolice3 = false;
    gSkipDraw = false;
    gDoFreeShopping = false;
    gSmallCar = false;
    gGiveMoney20 = false;
    gIAMDAVEJ = false;
    gElectroGun = false;
    gMADEMAN = false;
    gHealth99 = false;
    gPontMultiplaerX10 = false;
    gAllTower = false;
    gSUPZZZ0 = false;
    gBonusAll = false;
    gGiveBasikWeapon = false;
    gElvis = false;
    gBunt = false;
    gNEKKID = false;
    gJailFreeCard = false;
    gInvisibility = false;
    gDoubleDamage = false;
    gJailKey = false;
    gFireGun = false;
    gDoShowCounters = false;
	return false;

	}


void  CopyWideString(wchar_t* dest, const wchar_t* src){
	
	wchar_t* current = dest;  // Сохраняем начало буфера
	
	// Копируем строку посимвольно, включая нулевой символ
	do {
		*current = *src;       // Копируем текущий символ
		current++;             // Переходим к следующей позиции в буфере
		src++;                 // Переходим к следующему символу источника
	} while (*(current - 1));  // Проверяем последний скопированный символ
}




int gRenderdevice;
int gVideodevice;
char gData[256] = { 0 };
char gVideo[255] = { 0 };

const char gD3ddll[11] = "d3ddll.dll";
const char gDmavideo[13] = "dmavideo.dll";
int gTrippleBufferCheck;
//BYTE gbD3ddll = "d3ddll.dll";

void FindGraphiDevace() {
    //BYTE Data[20];
    gRenderdevice = gRegistry.ConfigSetScreen("renderdevice", 1u);
	gVideodevice=gRegistry.ConfigSetScreen("videodevice", 1u);
    
    strcpy(gData, gD3ddll);
    strcpy(gVideo, gDmavideo);

    gRegistry.SetVideoName("rendername", (LPBYTE)gData, 255);
    gRegistry.SetVideoName("videoname", (LPBYTE)gVideo, 255);
    if (!strcmp(gData, "softdll.dll")){ 
        gTrippleBufferCheck=0;
    }
    else 
        gTrippleBufferCheck=(strcmp(gData, "3dfx.dll")==0)+1;
   

}