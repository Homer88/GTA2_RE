// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <iostream>
//#include <cstdlib>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//#include <assert.h>

#include "detours.h"
//#include "pch.h"
//  файлы конфигурации 
#include "InitMapGM.h"
//#include "InitS20Fun.h"
#include "DebugLogFile.h"
#include "cHookTrace.h"
#include "cInspector.h"

#include "cDirectX.h"
//#include "cGang.h"
//#include "cGangs.h"
#include "cMapGm.h"
#include "cMenu.h"
//#include "cPed.h"

//#include "cS8.h"
//#include "cS19.h"
//#include "cS20.h"
//#include "cText.h"
#include "cStyle.h"
//#include "cWeapon.h"
#include "cWindow.h"
#include "cGang.h"
#include "cWeapon.h"
#include "cGame.h"
#include "cSaveLog.h"


#pragma comment(lib, "detours.lib")

int FunMapGM();
///void  FunS20();
void printError(LONG Error, PVOID address);

unsigned int Error;

// Trampoline to the original Menu::LoadTextMenu (0x00453E20).
// DetourAttach rewrites this variable to the Detours trampoline; cMenu.cpp
// calls through it so the retail code still builds every menu page / reads .gxt text.
LPVOID _LoadTextMenu = (LPVOID)0x00453E20;


LPVOID _InitDefautValue = (LPVOID)0x00461AF0;        // InitDefautValue
LPVOID _InitGraphicsAndInput = (LPVOID)0x004031C0;     // InitGraphicsAndInput
LPVOID _SetWeapon = (LPVOID)0x00433810;               // Weapon::SetWeapon
LPVOID _SetPed = (LPVOID)0x004CCA10;                  // Weapon::SetPed
LPVOID _CopyNameGang = (LPVOID)0x0045DB40;             // Gang::SetName
LPVOID _LoadGame = (LPVOID)0x00455C20;                // Menu::LoadGame
LPVOID _SaveGame = (LPVOID)0x00455C90;                // Menu::SaveGame
LPVOID _MultiplayerMenu = (LPVOID)0x004565E0;         // Menu::MultiplayerMenu
LPVOID _SetGameState = (LPVOID)0x0045A480;             // Game::sub_45A480 (State/isDead setter)
LPVOID _GameCtor = (LPVOID)0x0045C4D0;                 // Game::Game (constructor)
LPVOID _ProcessInput = (LPVOID)0x00452050;             // Menu::ProcessInput (reads keyboard)
LPVOID _InitFrontedLessGame = (LPVOID)0x00461DE0;      // InitFrontedLessGame (boot/level init)
LPVOID _Resurs = (LPVOID)0x0045B469;                   // Game::Resurs (loads Level resources)
LPVOID _sub_45B5F0 = (LPVOID)0x0045B5F0;               // Game::sub_45B5F0 (inits world)
LPVOID _Sub465390 = (LPVOID)0x00465390;                // MapRelatedStruct::sub_465390 (gangs/zone)
LPVOID _Sub481890 = (LPVOID)0x00481890;                // MissionManager::sub_481890 (missions)
LPVOID _StartGames = (LPVOID)0x004A6DA0;               // Player::StartGames (starts player)
LPVOID _UpdateWrapper = (LPVOID)0x004CAC30;            // Hud::UpdateWrapper

// --- save-file writers (see cSaveLog.h): trampolines used by cSaveLog.cpp ---
LPVOID _WriteFileSvg = (LPVOID)0x0047EF40;  // MissionManager::SaveFile
LPVOID _WriteFileDat = (LPVOID)0x004A89E0;  // PlayerData::WriteFileNamePlayer
LPVOID _WriteFileHsc = (LPVOID)0x004A8D80;  // PlayerData::sub_4A8D80 (hiscores)

static LONG WINAPI CrashFilter(EXCEPTION_POINTERS* ep) {
    char path[MAX_PATH + 32];
    char exe[MAX_PATH];
    DWORD n = GetModuleFileNameA(NULL, exe, MAX_PATH);
    if (n > 0 && n < MAX_PATH) {
        char* sl = strrchr(exe, '\\');
        if (sl) { sl[1] = 0; } else { exe[0] = 0; }
        sprintf(path, "%sgta2_crash.log", exe);
    }
    else {
        strcpy(path, "gta2_crash.log");
    }
    FILE* f = fopen(path, "ab");
    if (f) {
        EXCEPTION_RECORD* er = ep->ExceptionRecord;
        CONTEXT* ctx = ep->ContextRecord;
        SYSTEMTIME st;
        unsigned char code[16];
        DWORD* stack = (DWORD*)ctx->Esp;
        int i;
        GetLocalTime(&st);
        fprintf(f, "\r\n--- CRASH %04d-%02d-%02d %02d:%02d:%02d.%03d ---\r\n",
                st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        fprintf(f, "Code: 0x%08X  Addr: 0x%08X  Flags: 0x%08X\r\n",
                er->ExceptionCode, (unsigned int)(ULONG_PTR)er->ExceptionAddress, er->ExceptionFlags);
        fprintf(f, "EIP: 0x%08X  EAX: 0x%08X  EBX: 0x%08X\r\n",
                ctx->Eip, ctx->Eax, ctx->Ebx);
        fprintf(f, "ECX: 0x%08X  EDX: 0x%08X  ESI: 0x%08X\r\n",
                ctx->Ecx, ctx->Edx, ctx->Esi);
        fprintf(f, "EDI: 0x%08X  ESP: 0x%08X  EBP: 0x%08X\r\n",
                ctx->Edi, ctx->Esp, ctx->Ebp);
        __try {
            for (i = 0; i < 16; i++) {
                code[i] = *(unsigned char*)(ctx->Eip + i);
            }
            fprintf(f, "CODE: ");
            for (i = 0; i < 16; i++) {
                fprintf(f, "%02X ", code[i]);
            }
            fprintf(f, "\r\n");
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            fprintf(f, "CODE: <unreadable>\r\n");
        }
        __try {
            fprintf(f, "STACK: ");
            for (i = 0; i < 8; i++) {
                fprintf(f, "0x%08X ", stack[i]);
            }
            fprintf(f, "\r\n");
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            fprintf(f, "STACK: <unreadable>\r\n");
        }
        fclose(f);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  dwReason,
                       LPVOID lpReserved
                     )
{

    // Получить дескриптор окна консоли
    HWND consoleWindow = GetConsoleWindow();

    if (consoleWindow != NULL) {
        // Спрятать окно
        ShowWindow(consoleWindow, SW_HIDE);
    }

    //LPVOID _InfoVersion = (LPVOID)0x004D0920;
   // LPVOID _InitGraphicsAndInput =  (LPVOID)0x004031c0;
    //LPVOID _GetDebugParam = (LPVOID)0x00451930;
    //LPVOID _GetNumberOfCars = (LPVOID)0x00432850;
    // _LoadTextMenu is now a file-scope global (see above)
   // LPVOID  _AllGxtFile = (LPVOID)0x00451800;
   // LPVOID  _InitDefautValue = (LPVOID)0x00461AF0;
    //LPVOID _CleanupDirectInput = (LPVOID)0x0044BA40;
    //LPVOID _CreateInputDevice = (LPVOID)0x0044BA00;
    //LPVOID _sub_459540 = (LPVOID)0x00459540;

    // --- enabled for the load-function trace (set to 0 to detach them) ---
    LPVOID _GetVersionFiles = (LPVOID)0x004D0920;    // GetVersionFiles
    LPVOID _fPlayReplay = (LPVOID)0x00451930;        // fPlayReplay (reads all debug params)
    LPVOID _AllGxtFile = (LPVOID)0x00451800;        // AllGxtFile
    LPVOID _SetPlayerNameFromMenu = (LPVOID)0x00459540; // Menu::SetPlayerNameFromMenu
    (void)_GetVersionFiles; (void)_fPlayReplay; (void)_AllGxtFile; (void)_SetPlayerNameFromMenu;
    //LPVOID _CopyNameGang = (LPVOID)0x0045DB40;
    //LPVOID _CopyNameGang = (LPVOID)0x0045DB40;  // Gang::SetName
    
    ///S19
   // LPVOID _SetPararam_0 = (LPVOID)0x004c4d60;
    
    //cText
    //LPVOID _GetLanguageJapan = (LPVOID)0x00452E60;  // Text::LanguageJapan
    // Weapons
    //LPVOID _SetWeapon = (LPVOID)0x00433810;   // Weapon::SetWeapon
    ///LPVOID _SetPed = (LPVOID)0x004cca10;     // Weapon::SetPed
    
    AllocConsole();
    switch (dwReason){
     

case DLL_PROCESS_ATTACH:
       /// MessageBox(0, L"Load Dll!", 0, 0);
        SetUnhandledExceptionFilter(&CrashFilter);
        TraceInit();
         TraceEvent("DllMain: DLL_PROCESS_ATTACH");
         StartInspector();
         SaveDebugStartHotkeys();

        DetourRestoreAfterWith();
        if (DetourTransactionBegin() != NO_ERROR)
        {
            OutputDebugStringA("error DetourTransactionBegin");
            return FALSE;
        }

        if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
        {
            printf("error DetourUpdateThread");
            return FALSE;
        }

       /* Error = DetourAttach(&_GetVersionFiles, (PVOID)GetVersionFiles);
        printError(Error, _GetVersionFiles);
        DetourAttach(&_InitDefautValue, (PVOID)InitDefautValue);
        //DetourAttach(&_CleanupDirectInput, (PVOID)CleanupDirectInput);
        //DetourAttach(&_CreateInputDevice, (PVOID)CreateInputDevice);
        ///DetourAttach(&_SetPlayerNameFromMenu, (PVOID)SetPlayerNameFromMenu);
        DetourAttach(&_GetNumberOfCars, (PVOID)GetNumberOfCars);
        /*DetourAttach(&_SetPararam_0, (PVOID)SetPararam_0);
        DetourAttach(&_CopyNameGang, (PVOID)CopyNameGang);
        DetourAttach(&_SetPararam_0, (PVOID)SetPararam_0);
        DetourAttach(&_GetLanguageJapan, (PVOID)GetLanguageJapan);
        DetourAttach(&_SetWeapon, (PVOID)SetWeapon);
        DetourAttach(&_SetPed, (PVOID)SetPed);
        */
        //--- active trace hooks (functions are traced to hook_trace.log) ---
        Error = DetourAttach(&_GetVersionFiles, (PVOID)GetVersionFiles);
        printError(Error, _GetVersionFiles);
        Error = DetourAttach(&_fPlayReplay, (PVOID)fPlayReplay);
        printError(Error, _fPlayReplay);
        Error = DetourAttach(&_AllGxtFile, (PVOID)AllGxtFile);
        printError(Error, _AllGxtFile);
        Error = DetourAttach(&_SetPlayerNameFromMenu, (PVOID)SetPlayerNameFromMenu);
        printError(Error, _SetPlayerNameFromMenu);
        //Error =  DetourAttach(&_InitGraphicsAndInput, (PVOID)InitGraphicsAndInput);
        //printError(Error, _InitGraphicsAndInput);

        //Error = DetourAttach(&_fPlayReplay, (PVOID)fPlayReplay);
        //printError(Error, _fPlayReplay);

       /// Error = DetourAttach(&_AllGxtFile, (PVOID)AllGxtFile);
        //printError(Error, _AllGxtFile);
        //*/
        //FunS20();
        //FunMapGM();
        DetourAttach(&_LoadTextMenu, (PVOID)LoadTextMenu);

        // --- Menu load/save series + setter hooks (trace + chain to original) ---
        Error = DetourAttach(&_LoadGame, (PVOID)LoadGame);
        printError(Error, _LoadGame);
        Error = DetourAttach(&_SaveGame, (PVOID)SaveGame);
        printError(Error, _SaveGame);
        Error = DetourAttach(&_MultiplayerMenu, (PVOID)MultiplayerMenu);
        printError(Error, _MultiplayerMenu);
        Error = DetourAttach(&_ProcessInput, (PVOID)HookProcessInput);
        printError(Error, _ProcessInput);
        Error = DetourAttach(&_CopyNameGang, (PVOID)HookSetName);
        printError(Error, _CopyNameGang);

        // ---------------- risky REPLACEMENT hooks: 0 = NOT attached -------------
        // They replace the real video / input init; the re-implemented bodies are
        // incomplete. Flip the define to 1 to attach them, at your own risk. ----
#define HOOK_INITDAFAULTVALUE 0
#define HOOK_INITGRAPHICSANDINPUT 0
#if HOOK_INITDAFAULTVALUE
        Error = DetourAttach(&_InitDefautValue, (PVOID)InitDefautValue);
        printError(Error, _InitDefautValue);
#endif
#if HOOK_INITGRAPHICSANDINPUT
        Error = DetourAttach(&_InitGraphicsAndInput, (PVOID)InitGraphicsAndInput);
        printError(Error, _InitGraphicsAndInput);
#endif
        Error = DetourAttach(&_SetWeapon, (PVOID)SetWeapon);
        printError(Error, _SetWeapon);
        Error = DetourAttach(&_SetPed, (PVOID)SetPed);
        printError(Error, _SetPed);
        // ---- Game ----
        Error = DetourAttach(&_SetGameState, (PVOID)HookSetState);
        printError(Error, _SetGameState);
        Error = DetourAttach(&_GameCtor, (PVOID)HookGameCtor);
        printError(Error, _GameCtor);
        Error = DetourAttach(&_InitFrontedLessGame, (PVOID)HookInitFrontedLessGame);
        printError(Error, _InitFrontedLessGame);
        Error = DetourAttach(&_Resurs, (PVOID)HookResurs);
        printError(Error, _Resurs);
        Error = DetourAttach(&_sub_45B5F0, (PVOID)Hook_sub_45B5F0);
        printError(Error, _sub_45B5F0);
        Error = DetourAttach(&_Sub465390, (PVOID)HookSub465390);
        printError(Error, _Sub465390);
        Error = DetourAttach(&_Sub481890, (PVOID)HookSub481890);
        printError(Error, _Sub481890);
        Error = DetourAttach(&_StartGames, (PVOID)HookStartGames);
        printError(Error, _StartGames);
        Error = DetourAttach(&_UpdateWrapper, (PVOID)HookUpdateWrapper);
        printError(Error, _UpdateWrapper);
        // save-file writers -> Save.log (cSaveLog.cpp)
        Error = DetourAttach(&_WriteFileSvg, (PVOID)HookSaveFile);
        printError(Error, _WriteFileSvg);
        Error = DetourAttach(&_WriteFileDat, (PVOID)HookWriteFileNamePlayer);
        printError(Error, _WriteFileDat);
        Error = DetourAttach(&_WriteFileHsc, (PVOID)HookWriteHiscores);
        printError(Error, _WriteFileHsc);
        if (DetourTransactionCommit() != NO_ERROR)
        {
            printf("error DetourTransactionCommit");
            return FALSE;
        }
     break;
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
       break;
    case DLL_PROCESS_DETACH:
        TraceEvent("DllMain: DLL_PROCESS_DETACH (unload)");
        StopInspector();
        TraceClose();
        break;
    }
    //DetourRestoreAfterWith();
    printf("Dettach and shutdown everything\n");
    return true;
}


void printError(LONG Error, PVOID address) {


    switch (Error)
    {
    case ERROR_INVALID_BLOCK:
        MessageBox(0, L"ERROR_INVALID_BLOCK", 0, 0);
        break;
    case ERROR_INVALID_HANDLE:
        MessageBox(0, L"ERROR_INVALID_HANDLE", 0, 0);
        break;
    case ERROR_INVALID_OPERATION:
        MessageBox(0, L"ERROR_INVALID_OPERATION", 0, 0);
        writeFileLog((char*)"windows.txt", (char*)"addres=", (char*)"Error ", (unsigned int)address);
        break;
    case ERROR_NOT_ENOUGH_MEMORY:
        MessageBox(0, L"ERROR_NOT_ENOUGH_MEMORY", 0, 0);
        break;
    case NO_ERROR:
        //MessageBox(0, L"NO_ERROR", 0, 0);
        break;
    default:
        break;
    }
}



int FunMapGM()
{
    //Error=  DetourAttach(&_LoadFileResurce     ,  (PVOID)LoadFileResurce);
   // printError(Error, _LoadFileResurce);
    //Error = DetourAttach(&_SetSaveFile         ,  (PVOID)SetSaveFile);
    //printError(Error, _SetSaveFile);
    //Error = DetourAttach(&_SetPlayerArena      ,  (PVOID)SetPlayerArena);
    //printError(Error, _SetPlayerArena);
   // Error = DetourAttach(&_SetSaveFile         ,  (PVOID)SetSaveFile);
   // printError(Error, _SetSaveFile);
    //Error = DetourAttach(&_SetPlayerArena      ,  (PVOID)SetPlayerArena);
    //printError(Error, _SetPlayerArena);
    //Error = DetourAttach(&_SetBonusStage       ,  (PVOID)SetBonusStage);
    //printError(Error, _SetBonusStage);
   // Error = DetourAttach(&_Set_FUN_0045E4B0    ,  (PVOID)Set_FUN_0045E4B0);
    //printError(Error, _Set_FUN_0045E4B0);
    //Error = DetourAttach(&_SetPlayerSlotSave   ,  (PVOID)SetPlayerSlotSave);
    //printError(Error, _SetPlayerSlotSave);
    //Error = DetourAttach(&_SetBonus            ,  (PVOID)SetBonus);
    //printError(Error, _SetBonus);
    return 0;
};

/*void FunS20() {
    DetourAttach(&_SetPararm_0x2ee0, (PVOID)SetPararm_0x2ee0);
}*/
