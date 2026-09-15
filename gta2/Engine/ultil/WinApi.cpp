#include "WinApi.h"
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include "../Registry/Registry.h"
#include "../Movie/Movie.h"
#include "../Debug/DebugLogFile.h"


WinApi *gWinApi;
extern Movie* gMovie;

#define MaxTextElement 80
extern int gTimer, gTime;
extern bool  gPlayReplay, gByte1, gByte2;
extern	HINSTANCE ghInstance;
extern Registry* gRegistry;
extern HWND gHWND;

extern	DWORD	gMajor;
extern	DWORD	gMinor;

extern bool gDoTest, gSkipMission, gShowCycle, gDoBrianTest, gDoIainTest, gSkipTiles, gDoShowCounters, gDoShowCamera, gDoShowInput, gDoShowTiming,
gDoShowCollisionBox, gDoShowPhysics, gDoShowImaginary, gSkipUser, gSkipTrafficLights, gSkipRecycling, gLogCollisions, gDoShowTrafficLightsInfo,
gDoShowIds, gLimitRecycling, gNoAnnoyingChars, gSkipSlopes, gSkipLeft, gSkipRight, gSkipTop, gSkipBottom, gSkipLid, gLogRoutefinder, gDoMike,
gSkipParticles, gShowHiddenFaces, gGetAllWeapons, gDoExitAfterReplay, gDontGetCarBack, gDoShowInstruments, gSkipAmbulance, gSkilPolice,
gSkipFrontend, gDoInvulnerable, gShowAllArrows, gDoShowHorn, gKeepWeaponsAfterDeath, gSkipSkidMarks, gDoShowJuncIds, gDoCornerWindow,
gDoInfiniteLives, gDoLoadSaveGame, gSkipAudio, gDoDebugKeys, gLogRandom, gLogRandomExtra, gLogInput, gLogDirectInput, gIgnoreReplayHeader,
gSkipTrains, gSkipBuses, gSkipQuitConfirm, gDoSyncCheck, gSkipFireEngines, gShowBriefNumber, gSkipWindowCheck, gSkipReplaySyncCheck,
gDoShowObjectIds, gGoKillPhonesOnAnswer, gDoMissLogging, gDoTextIdTest, gDoPolice1, gDoPolice2, gDoPolice3, gSkipDraw, gDoFreeShopping, gSkipDummies,
gDoBlood, gDo3dSound, gTestFileGxt, gShowPlayerNames;
extern bool gNopCheat, gSmallCar, gGiveMoney99k, gElectroGun, gMademan, gHealth99, gPointMultiPlayerX10, gAllTower, gSUPZZZ0, gBonusAll, gGiveBasikWeapon,
gElvis, gBunt, gNEKKID, gJailFreeCard, gInvisibility, gDoubleDamage, gJailKey, gFireGun, gNetworkGame;
extern bool gGiveMoney20k, gAllTower;
bool gExploding_on;
char gTextArrayChar[MaxTextElement];
bool gMaxFrameRate, gMinFrameRate;
extern char gData[255], gVideo[255];
int gTrippleBufferCheck;
const char gD3ddll[11] = "d3ddll.dll";
const char gDmavideo[13] = "dmavideo.dll";
extern int gRenderDevice, gVideoDevice;
extern int gGamma;
extern int gWindowWidth, gWindowHeight;

extern int gFullWidth, gFullHeight;

extern int gStartMode;
extern int gTrippleBuffer;



WinApi::WinApi(){
}

char * WinApi::Convertor_wchar_t_ToChar(wchar_t *Text){
	wchar_t * _Text=Text;
	for (int index=0; _Text; ++index){
		if (index>=79){
			break;
		};
		gTextArrayChar[index]= *_Text<128u ? *(BYTE*)_Text: '#';
		++_Text;
	};
	return gTextArrayChar;
	
}
wchar_t* WinApi::CopyWideString(wchar_t* dest, wchar_t* source) {
    if (dest && source) {
        wchar_t* p = dest;
        while (*source) {
            *p++ = *source++;
        }
        *p = 0;
    }
    return dest;
}


void  WinApi::GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion){
	
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


void WinApi::InitTimer() {
    gTimer = timeGetTime();
    gTime = 0;
}

void WinApi::GetDebugParam() {
    gPlayReplay = gRegistry->GetPlayReplay("play_replay");
    gByte1 = true;
    gByte2 = true;

    BYTE pDebugMode = gRegistry->GetReplayNum("replaynum") + 48;

    //????
    //aTextReplay0Rep[11] = pDebugMode;
    if (!gPlayReplay) {
        if ((pDebugMode - 47) >= 10) {
            pDebugMode = 0;
        }

        gRegistry->SetDebugByteValue("replaynum", pDebugMode);
    }
     bool 
    gDoTest                         = gRegistry->GetParamDebug("do_test");
    gSkipMission                    = gRegistry->GetParamDebug("skip_mission");
    gShowCycle                      = gRegistry->GetParamDebug("show_cycle");
    gDoBrianTest                    = gRegistry->GetParamDebug("do_brian_test");
    gDoIainTest                     = gRegistry->GetParamDebug("do_iain_test");
    gSkipTiles                      = gRegistry->GetParamDebug("skip_tiles");
    gDoShowCounters                 = gRegistry->GetParamDebug("do_show_counters");
    gDoShowCamera                   = gRegistry->GetParamDebug("do_show_camera");
    gDoShowInput                    = gRegistry->GetParamDebug("do_show_input");
    gDoShowTiming                   = gRegistry->GetParamDebug("do_show_timing");
    gDoShowCollisionBox             = gRegistry->GetParamDebug("do_show_collision_box");
    gDoShowPhysics                  = gRegistry->GetParamDebug("do_show_physics");
    gDoShowImaginary                = gRegistry->GetParamDebug("do_show_imaginary");
    gSkipUser                       = gRegistry->GetParamDebug("skip_user");
    gSkipTrafficLights              = gRegistry->GetParamDebug("skip_traffic_lights");
    gSkipRecycling                  = gRegistry->GetParamDebug("skip_recycling");
    gLogCollisions                  = gRegistry->GetParamDebug("log_collisions");
    gDoShowTrafficLightsInfo        = gRegistry->GetParamDebug("do_show_traffic_lights_info");
    gDoShowIds                      = gRegistry->GetParamDebug("do_show_ids");
    gLimitRecycling                 = gRegistry->GetParamDebug("limit_recycling");
    gNoAnnoyingChars                = gRegistry->GetParamDebug("no_annoying_chars");
    gSkipSlopes                     = gRegistry->GetParamDebug("skip_slopes");
    gSkipLeft                       = gRegistry->GetParamDebug("skip_left");
    gSkipRight                      = gRegistry->GetParamDebug("skip_right");
    gSkipTop                        = gRegistry->GetParamDebug("skip_top");
    gSkipBottom                     = gRegistry->GetParamDebug("skip_bottom");
    gSkipLid                        = gRegistry->GetParamDebug("skip_lid");
    gLogRoutefinder                 = gRegistry->GetParamDebug("log_routefinder");
    gDoMike                         = gRegistry->GetParamDebug("do_mike");
    gSkipParticles                  = gRegistry->GetParamDebug("skip_particles");
    gShowHiddenFaces                = gRegistry->GetParamDebug("show_hidden_faces");
    gGetAllWeapons                  = gRegistry->GetParamDebug("get_all_weapons");
    gDoExitAfterReplay              = gRegistry->GetParamDebug("do_exit_after_replay");
    gDontGetCarBack                 = gRegistry->GetParamDebug("dont_get_car_back");
    gDoShowInstruments              = gRegistry->GetParamDebug("do_show_instruments");
    gSkipAmbulance                  = gRegistry->GetParamDebug("skip_ambulance");
    gSkilPolice                     = gRegistry->GetParamDebug("skip_police");
    gSkipFrontend                   = gRegistry->GetParamDebug("skip_frontend");
    gDoInvulnerable                 = gRegistry->GetParamDebug("do_invulnerable");
    gShowAllArrows                  = gRegistry->GetParamDebug("show_all_arrows");
    gDoShowHorn                     = gRegistry->GetParamDebug("do_show_horn");
    gKeepWeaponsAfterDeath          = gRegistry->GetParamDebug("keep_weapons_after_death");
    gSkipSkidMarks                  = gRegistry->GetParamDebug("skip_skidmarks");
    gDoShowJuncIds                  = gRegistry->GetParamDebug("do_show_junc_ids");
    gDoCornerWindow                 = gRegistry->GetParamDebug("do_corner_window");
    gDoInfiniteLives                = gRegistry->GetParamDebug("do_infinite_lives");
    gDoLoadSaveGame                 = gRegistry->GetParamDebug("do_load_savegame");
    gSkipAudio                      = gRegistry->GetParamDebug("skip_audio");
    gDoDebugKeys                    = gRegistry->GetParamDebug("do_debug_keys");
    gLogRandom                      = gRegistry->GetParamDebug("log_random");
    gLogRandomExtra                 = gRegistry->GetParamDebug("log_random_extra");
    gLogInput                       = gRegistry->GetParamDebug("log_input");
    gLogDirectInput                 = gRegistry->GetParamDebug("log_directinput");
    gIgnoreReplayHeader             = gRegistry->GetParamDebug("ignore_replay_header");
    gSkipTrains                     = gRegistry->GetParamDebug("skip_trains");
    gSkipBuses                      = gRegistry->GetParamDebug("skip_buses");
    gSkipQuitConfirm                = gRegistry->GetParamDebug("skip_quit_confirm");
    gDoSyncCheck                    = gRegistry->GetParamDebug("do_sync_check");
    gSkipFireEngines                = gRegistry->GetParamDebug("skip_fire_engines");
    gShowBriefNumber                = gRegistry->GetParamDebug("show_brief_number");
    //
    gSkipWindowCheck                = gRegistry->GetParamDebug("skip_window_check");
    gSkipReplaySyncCheck            = gRegistry->GetParamDebug("skip_replay_sync_check");
    gDoShowObjectIds                = gRegistry->GetParamDebug("do_show_object_ids");
    gGoKillPhonesOnAnswer           = gRegistry->GetParamDebug("do_kill_phones_on_answer");
    gDoMissLogging                  = gRegistry->GetParamDebug("do_miss_logging");
    gDoTextIdTest                   = gRegistry->GetParamDebug("do_text_id_test");
    gDoPolice1                      = gRegistry->GetParamDebug("do_police_1");
    gDoPolice2                      = gRegistry->GetParamDebug("do_police_2");
    gDoPolice3                      = gRegistry->GetParamDebug("do_police_3");
    gSkipDraw                       = gRegistry->GetParamDebug("skip_draw");
    gDoFreeShopping                 = gRegistry->GetParamDebug("do_free_shopping");
    gSkipDummies                    = gRegistry->GetParamDebug("skip_dummies");
    gDoBlood                        = gRegistry->GetParamDebug("do_blood");
    gDo3dSound                      = gRegistry->GetParamDebug("do_3d_sound");
    gTestFileGxt                    = this->AllGtxFile();
    gShowPlayerNames                = gRegistry->SetShowPlayerName("show_player_names", 1u);
}

bool WinApi::AllGtxFile() {

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
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}

void WinApi::FindGraphicDevice() {
   gRenderDevice = gRegistry->ConfigureSetScreen("renderdevice", 1u);
    gVideoDevice = gRegistry->ConfigureSetScreen("videodevice", 1u);

    strcpy(gData, gD3ddll);
    strcpy(gVideo, gDmavideo);

    gRegistry->SetVideoName("rendername", (LPBYTE)gData, 255);
    gRegistry->SetVideoName("videoname", (LPBYTE)gVideo, 255);
    if (!strcmp(gData, "softdll.dll")) {
        gTrippleBufferCheck = 0;
    }
    else
        gTrippleBufferCheck = (strcmp(gData, "3dfx.dll") == 0) + 1;
}
int gLighting;
int  gTimeDayAndNight;

void WinApi::ConfigureVideoDevice() {
    if (gNetworkGame) {
        gMaxFrameRate = true;
        gMinFrameRate = true;
    }
    else {
        gMaxFrameRate = gRegistry->ConfigureSetScreen("max_frame_rate", 1) != 0;
        gMinFrameRate = gRegistry->ConfigureSetScreen("min_frame_rate", 0) != 0;
    }
    if (gRegistry->ConfigureSetScreen("lighting", 1)) {
        gLighting = 1;
        gTimeDayAndNight = DAY;
    }
    else {
        gLighting = 0;
        gTimeDayAndNight = NIGHT;
    }
    //if (gSpriteS3) FixMe
    ///S39
    gRegistry->ConfigureSetScreen("exploding_on", 1);
    gExploding_on = gRegistry->ConfigureSetScreen("exploding_on", 1) != 1;

}

void WinApi::DefautInitParam() {
    //Данная функция для сетевой игры 
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
    gNopCheat      = false;
    gDoPolice1     = false;
    gDoPolice2 = false;
    gDoPolice3 = false;
    gSkipDraw = false;
    gDoFreeShopping        = false;
    gSmallCar              = false;
    gGiveMoney20k           = false;
    gGiveMoney99k           = false;
    gElectroGun            = false;
    gMademan                = false;
    gHealth99              = false;
    gPointMultiPlayerX10     = false;
    gAllTower               = false;
    gSUPZZZ0                = false;
    gBonusAll               = false;
    gGiveBasikWeapon        = false;
    gElvis                  = false;
    gBunt                   = false;
    gNEKKID                 = false;
    gJailFreeCard           = false;
    gInvisibility           = false;
    gDoubleDamage           = false;
    gJailKey                = false;
    gFireGun                = false;
    gDoShowCounters = false;
}



bool WinApi::ConfigureVideoWindow() {
    int pStartModeDefaut = gStartMode;
    int pTrippleBufferDefaut = gTrippleBuffer;
    int pFullWidth = gFullWidth;
    int pWindowWidth = gWindowWidth;
    int pFullHeight = gFullHeight;

    int pWindowHeight = gWindowHeight;

    gWindowWidth = gRegistry->ConfigureSetScreen("window_width", 128);
    gWindowHeight = gRegistry->ConfigureSetScreen("window_height", 224);
    gFullWidth = gRegistry->ConfigureSetScreen("full_width", 224);
    gFullHeight = gRegistry->ConfigureSetScreen("full_height", 224);
    gStartMode = gRegistry->ConfigureSetScreen("start_mode", 1);
    if (gTrippleBufferCheck) {
        gTrippleBuffer = gRegistry->ConfigureSetScreen("tripple_buffer", 0);

    }
    else {
        gTrippleBuffer = 1;
    }

    if (gStartMode != pStartModeDefaut || gTrippleBuffer != pTrippleBufferDefaut) {
        return true;
    }
    if (gStartMode != pStartModeDefaut || gTrippleBuffer != pTrippleBufferDefaut) {
        return true;
    }
    if (gStartMode == FullScreen) {
        if (gFullWidth != pFullWidth) {
            return true;
        }
        if (pFullHeight == gFullHeight) {
            return false;
        }

    }
    else {
        return false;
    }
    return true;

}
void WinApi::SetShowCursor() {
    int result;
    do {
        result = ShowCursor(0);
    } while (result >= 0);
}

int WinApi::SetVideoPlayer() {
    this->ConfigureVideoDevice();
    this->ConfigureVideoWindow();
    //Dint();
    //gMovie.CloseScreen();
    int v1;
    int v0 = 0;//gMovie.field4;
    if (gTrippleBuffer) {
        v1 = v0 | 16;
    }
    else {
        v1 = v0 & 0xffffffff;
    }
    //gMovie.field4 = v1;
    if (gStartMode) {
        this->VideoCheck();
    }
    else {
        if (!this->VideoCheck1()) {
            if (gWindowWidth == 640 ||
                (gWindowWidth == 640, gWindowHeight == 480, !this->VideoCheck1())) {
                this->VideoCheck();
                gStartMode = FullScreen;
                gRegistry->SetConfigureWindowSize("start_mode", 1);
            }
            else {
                gRegistry->SetConfigureWindowSize("window_width", gWindowWidth);
                gRegistry->SetConfigureWindowSize("window_height", gWindowHeight);
            }

        }
    }
    this->SetGamma();
    return 0;
}

void WinApi::SetGamma() {
    if (this->SetVideoGamma(gRegistry->ConfigureSetScreen("gamma", 0xAu))) {
        gGamma = 30;
    }

}
bool WinApi::SetVideoGamma(int Gamma) {
    return true;
}



void WinApi::VideoCheck() {
    int v0 = 0;
    bool  v1 = gMovie->CheckMode(gFullWidth, gFullHeight, 16);
    if (!v1) {
        if (gFullHeight == 640 ||
            (gFullWidth == 640, v0 = 1, gFullHeight = 480, (v1 = gMovie->CheckMode(640, 480, 16)) == 0)) {
            DebugLog(0xBBBu, "video.cpp", 1358);
        }
    }
    if (gMovie->Status) {
        int v3 = gMovie->field4;
        v3 |= 1;
        gMovie->field4 = v3;

    }
    if (gMovie->SetMode(gHWND, &v1)) {
        DebugLog(0x40Du, "video.cpp", 1365);
    }
    this->SetShowCursor();
    SetWindowLongA(gHWND, -16, 268435456);
    SetWindowPos(gHWND, 0, 0, 0, 0, 0, 1595);
    UpdateWindow(gHWND);
    ShowWindow(gHWND, true);
    DirectInput2();
    if (v0) {
        gRegistry->SetConfigureWindowSize("full_width", gFullWidth);
        gRegistry->SetConfigureWindowSize("full_height", gFullHeight);
    }
}

int gData_byte = 1;
int gX, gY;
char WinApi::VideoCheck1() {
    char result;
    Movie* v1;
    int v2;
    struct tagRECT v3;
    struct tagRECT Rect;

    result = gData_byte;
    if (result)
    {
        //DirectX();
        SetWindowLongA(gHWND, -16, 282001408);
        SetWindowPos(gHWND, 0, 0, 0, 0, 0, 0x63Bu);
        UpdateWindow(gHWND);
        ShowWindow(gHWND, 5);
        GetWindowRect(gHWND, &Rect);
        GetClientRect(gHWND, &v3);
        if (!SetWindowPos(
            gHWND,
            0,
            gX,
            gY,
            Rect.right + v3.left + gWindowWidth - v3.right - Rect.left,
            Rect.bottom + v3.top + gWindowHeight - v3.bottom - Rect.top,
            0x316u))
            return 0;
        UpdateWindow(gHWND);
        ShowWindow(gHWND, 5);
        // v1 = gMovie;
         //if (gMovie)
         /*{
             v2 = gMovie->field_4;
             BYTE1(v2) |= 1u;
             gMovie->field_4 = v2;
             v1 = gMovie;
         }
         if (Vid_SetMode(v1, gHWND, -2) == 1)
         {
             return 0;
         }
         else
         {
             SetCursor_ShowTrue();
             return 1;
         }
     }
     return result;*/
    }
}


void  WinApi::DirectInput2() {}



WinApi::~WinApi(){};