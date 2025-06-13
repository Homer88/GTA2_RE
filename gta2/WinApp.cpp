#include <stdlib.h>
#include <cstdio> // Для FILE, fopen, fclose
#include <windows.h>
#include <winver.h>
#include "WinMain.h"
#include "Global.h"

#pragma comment(lib, "version.lib")


///Switch 
#define  RunPlayVideo   7

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
void*    gBinkBufferClose;
bool    gNetworkGame=false;
byte    gControl;
int gData_6735A5;

// Обработчик сообщений
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    HWND pHWND;
    if (uMsg <= 70) {

        if (uMsg == 70) {
            if (gMenu.Status) {
                pHWND = HWND(lParam + 12);
                uMsg = (lParam + 8);
                BinkClose(uMsg,hwnd);

            }
      }
    }
    else {
        switch (uMsg) {
            case WM_DESTROY:
                if (gNetworkGame) {
                    gNetwork.CloseConnect();
                    ReleaseMutex(gHANDLE);
                    CloseHandle(gHANDLE);
                    gHANDLE = 0;
                    Destructor();
                    DestructorMovie();
                    PostQuitMessage(0);
                    break;
                }
            case 5:
                switch (wParam) 
             
                {
                case 1:
                    gControl = 2;
                    gDMAudio.InitAudioManager();
                    break;
                case 0:
                case 2:
                    gControl = 0;
                    gDMAudio.InitAudioManager3D();
                    break;
                default:
                    break;
                }
                break;
            case 6:
                if (wParam) {
                    if (wParam <= 2){
                        lParam = 1;
                        Deff(1);

                    }
                    else
                    {
                        Deff(0);

                    }
                }
                break;
            case RunPlayVideo:
                gDMAudio.InitAudioManager3D();
                char  CDVol = gRegistry.ConfigureSoundSetting("CDVol", 127);
                gDMAudio.SetCDVol(CDVol);
                char SFXVol = gRegistry.ConfigureSoundSetting("SFXVol", 127);
                gDMAudio.SetSFXVol(SFXVol);
                if (gSkipFrontend1) {
                    gDMAudio.Init3DSound(0);
                }
                else{

                    char Sound3DConfigure = gRegistry.GetSound3DConfigure("do_3d_sound");
                    gDMAudio.Init3DSound(Sound3DConfigure);
                    bool v11=gDMAudio.Get3DSound();
                    gRegistry.SetSound3DConfigure("do_3d_sound", v11);
                }

                if (true) {
                    Deff(1);
                    if (!gSkipFrontend1) {
                        InitInput();
                    }
                    if (gMovie.Status && !IsVideoPlaying) {
                        SetVideoPlayer();
                        //FixME
                        // sub_4CB880();
                        gData_6735A5 = 0;
                }
                    //if (gGame)


                }
                break;
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


int BinkClose(UINT uMSG, HWND hWND) {

    /*if (gBinkBufferClose) {
        BinkBufferCheckWinPos(gBinkBufferClose, MSG, hWND);
    }*/
    return 0;
}

void Destructor() {
    //FixMe
    //Аудио и клавиатура 
}
void DestructorMovie() {
    //FixMe
    //Аудио и клавиатура 
}

void Deff(byte a) {

    if (gSkipFrontend1) {
        if (true) {
            gMenu.SetFrontendKeysEnabled(a);
        }
        else
            gReplay.SetField_75344(a);
    }
}

void InitInput() {
    ///FIXME
    //if (gInput)
    //return InitDirectXInput();

}

int gVideoPlay = 0;
// Проверяет, активно ли видео (воспроизведение или пауза)
bool IsVideoPlaying()
{
    return gVideoPlay == 1 || gVideoPlay == 2;
}


bool gMaxFrameRate;
bool gMinFrameRate;
int  gLighting;
int  gTimeDayAndNight;
bool  gExploding_on;
enum TimeDay {
    day = 32768,
    night = 0,
};

void ConfigureVideoDevice() {

    if (gNetworkGame){
        gMaxFrameRate = true;
        gMinFrameRate = true;
    }
    else {
        gMaxFrameRate = gRegistry.ConfigSetScreen("max_frame_rate", 1) != 0;
        gMinFrameRate = gRegistry.ConfigSetScreen("min_frame_rate", 0) != 0;
    }
    if (gRegistry.ConfigSetScreen("lighting", 1)) {
        gLighting = 1;
        gTimeDayAndNight = day;
    }
    else {
        gLighting = 0;
        gTimeDayAndNight = night;
    }
    //if (gSpriteS3) FixMe
    ///S39
    gRegistry.ConfigSetScreen("exploding_on", 1);
    gExploding_on = gRegistry.ConfigSetScreen("exploding_on", 1) != 1;
}



int gWindowWidth;
int gWindowHeight;

int gFullWidth;
int gFullHeight;

int gStartMode;
int gTrippleBuffer;

enum ModeSize {
    FullScreen=1,
    WindowScreen=0,
};


bool ConfigureVideoWindow() {
    int pStartModeDefaut = gStartMode;
    int pTrippleBufferDefaut = gTrippleBuffer;
    int pFullWidth = gFullWidth;
    int pWindowWidth = gWindowWidth;
    int pFullHeight = gFullHeight;
    
    int pWindowHeight = gWindowHeight;

    gWindowWidth = gRegistry.ConfigSetScreen("window_width", 128);
    gWindowHeight = gRegistry.ConfigSetScreen("window_height", 224);
    gFullWidth = gRegistry.ConfigSetScreen("full_width", 224);
    gFullHeight = gRegistry.ConfigSetScreen("full_height", 224);
    gStartMode = gRegistry.ConfigSetScreen( "start_mode", 1);
    if (gTrippleBufferCheck) {
        gTrippleBuffer = gRegistry.ConfigSetScreen("tripple_buffer", 0);

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

void Dint() {
//FixMe
    //Надо хорошо диассемблировать.

}
void SetShowCursor() {
    int result;
    
    do
        result = ShowCursor(0);
    while (result >= 0);

}

void DirectInput2() {
  /*  if (!gDirectInput1
        || S219
        || ((int(__stdcall*)(DirectInput*, void*, s219**, _DWORD))gDirectInput1->s209->field_C)(
            gDirectInput1,
            &unk_576C14,
            &S219,
            0)
        || (*(int(__stdcall**)(s219*, void*))S219->S209->gap2C)(S219, &unk_5782C4)
        || (*(int(__stdcall**)(s219*, HWND, int)) & S219->S209->gap2C[8])(S219, gHWND, 5))
    {
        return 0;
    }
    (*(void(__stdcall**)(s219*)) & S219->S209->field_1C)(S219);
    return 1;*/
}
void VideoCheck() {
    int v0=0;
    int v1 = gMovie.CheckMode(gFullWidth, gFullWidth, 16);
    if (!v1 ) {
        if (gFullHeight == 640 ||
            (gFullWidth == 640, v0 = 1, gFullHeight = 480, (v1= gMovie.CheckMode(640, 480, 16)) == 0)) {
            DebugLog(0xBBBu, "video.cpp", 1358);
        }
    }
    if (gMovie.Status) {
        int v3 = gMovie.field4;
        v3 |= 1;
        gMovie.field4 = v3;

    }
    if (gMovie.SetMode(gHWND, v1)) {
        DebugLog(0x40Du, "video.cpp", 1365);
    }
    SetShowCursor();
    SetWindowLongA(gHWND, -16, 268435456);
    SetWindowPos(gHWND, 0, 0, 0, 0, 0, 1595);
    UpdateWindow(gHWND);
    ShowWindow(gHWND, true);
    DirectInput2();
    if (v0) {
        gRegistry.SetConfigureWindowSize("full_width", gFullWidth);
        gRegistry.SetConfigureWindowSize("full_height", gFullHeight);
    }
}

int gData_byte = 1;
int gX, gY;
char VideoCheck1() {
    char result; // al
    Movie* v1; // eax
    int v2; // ecx
    struct tagRECT v3; // [esp+0h] [ebp-20h] BYREF
    struct tagRECT Rect; // [esp+10h] [ebp-10h] BYREF

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

bool SetVideoGamma(int Gamma) {
    return true;
}
int gGamma;
void SetGamma() {
    if (SetVideoGamma(gRegistry.ConfigSetScreen("gamma", 0xAu))) {
        gGamma = 30;
    }

}

int SetVideoPlayer() {

        ConfigureVideoDevice();
        ConfigureVideoWindow();
        Dint();
        gMovie.CloseScreen();
        int v1;
        int v0 = gMovie.field4;
        if (gTrippleBuffer) {
            v1 = v0 | 16;
        }
        else {
            v1 = v0 & 0xffffffff;
        }
        gMovie.field4 = v1;
        if (gStartMode) {
            VideoCheck();
        }
        else {
            if (!VideoCheck1()) {
                if (gWindowWidth == 640 ||
                    (gWindowWidth == 640, gWindowHeight == 480, !VideoCheck1())) {
                    VideoCheck();
                    gStartMode = FullScreen;
                    gRegistry.SetConfigureWindowSize("start_mode", 1);
                }
                else {
                    gRegistry.SetConfigureWindowSize("window_width", gWindowWidth);
                    gRegistry.SetConfigureWindowSize("window_height", gWindowHeight);
                }

            }
        }
        SetGamma();
}
