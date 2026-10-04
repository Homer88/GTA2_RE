// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <iostream>
//#include <cstdlib>
#include <Windows.h>
#include <tlhelp32.h>
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
#include "cAudioWatch.h"
#include "cMilesWatch.h"
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

// ---- strlen emulator ---------------------------------------------------
// The game hands ucrtbase's bounded strlen a bogus pointer: 0x7263694D, which is
// the ASCII text "Micr" lifted out of the driver-name field
// 'Microsoft DirectSound3D hardware support' instead of a pointer to it.
// Walking that address faults inside the loop.
//
// That ucrtbase routine is:
//   80 38 00        cmp byte ptr [eax], 0
//   74 05           je   short +5
//   40              inc  eax
//   3B C1           cmp  eax, ecx
//   75 F6           jne  short -10
//   8B C8           mov  ecx, eax      <-- +10
//   2B CE           sub  ecx, esi
//   3B CA           cmp  ecx, edx
//
// ECX already holds the intended end and ESI the intended start, so setting
// EAX = ECX and stepping past the loop yields ecx = (end - start), exactly the
// length the caller compares against. No guessing.

static const BYTE kStrlenPat[] = {
    0x80, 0x38, 0x00, 0x74, 0x05, 0x40, 0x3B, 0xC1, 0x75, 0xF6, 0x8B, 0xC8
};

static int g_lenPatched = 0;
static int g_lenBudget  = 256;

static int PatchStrlen(EXCEPTION_RECORD* r, CONTEXT* c)
{
    BYTE code[sizeof(kStrlenPat)];

    if (r->ExceptionCode != EXCEPTION_ACCESS_VIOLATION) return 0;
    if (r->NumberParameters < 2) return 0;
    if (r->ExceptionInformation[0] != 0) return 0;      // READ only
    if (g_lenPatched >= g_lenBudget) return 0;

    __try {
        memcpy(code, (const void*)c->Eip, sizeof(code));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return 0;
    }
    if (memcmp(code, kStrlenPat, sizeof(kStrlenPat)) != 0) return 0;

    // the loop has to be able to terminate, or this is some other routine
    if (c->Eax < 0x00010000u) return 0;
    if (c->Ecx <= c->Eax) return 0;
    if (c->Esi > c->Eax) return 0;

    unsigned long len = c->Ecx - c->Eax;

    // Startup calls a Win32 string routine on a stale heap pointer. The value
    // is a real address (it differs every run), not text. Handing it an empty
    // string is the honest answer and lets the game continue into video init.
    static char kEmpty[2] = { 0, 0 };
    c->Eax = (DWORD)kEmpty;
    c->Ecx = (DWORD)kEmpty;
    c->Esi = (DWORD)kEmpty;
    ++g_lenPatched;
    {
        extern void VideoTrace(const char* fmt, ...);
        VideoTrace("[strlen-patched] #%d bogus=%08lX claimed_len=%lu -> empty",
                   g_lenPatched, (unsigned long)c->Ecx, len);
    }
    return 1;
}

static LONG CALLBACK CrashPatchVeh(EXCEPTION_POINTERS* ep)
{
    if (PatchStrlen(ep->ExceptionRecord, ep->ContextRecord))
        return EXCEPTION_CONTINUE_EXECUTION;
    return EXCEPTION_CONTINUE_SEARCH;
}

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

        // Which module owns the faulting EIP, and which thread crashed?
        // A non-main thread means the fault is not in whatever we just called.
        {
            DWORD pid = GetCurrentProcessId();
            DWORD tid = GetCurrentThreadId();
            // GetThreadInformation/GetCurrentThreadId is Vista+; this hook targets XP-era
            // code, so detect the main thread by enumerating threads instead.
            DWORD mainTid = 0;
            {
                HANDLE tsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
                if (tsnap != INVALID_HANDLE_VALUE) {
                    THREADENTRY32 te;
                    te.dwSize = sizeof(te);
                    if (Thread32First(tsnap, &te)) {
                        do {
                            if (te.th32OwnerProcessID == pid) { mainTid = te.dwSize ? te.th32ThreadID : 0; break; }
                        } while (Thread32Next(tsnap, &te));
                    }
                    CloseHandle(tsnap);
                }
            }
            fprintf(f, "THREAD: 0x%08lX  (first=0x%08lX) %s\r\n",
                    (unsigned long)tid, (unsigned long)mainTid,
                    (tid == mainTid) ? "<= MAIN THREAD" : "<= NOT main thread");
            (void)pid;

            HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
            if (snap != INVALID_HANDLE_VALUE) {
                MODULEENTRY32 me;
                me.dwSize = sizeof(me);
                if (Module32First(snap, &me)) {
                    do {
                        unsigned long base = (unsigned long)me.modBaseAddr;
                        if ((unsigned long)ctx->Eip >= base &&
                            (unsigned long)ctx->Eip < base + me.modBaseSize)
                            fprintf(f, "FAULT MODULE: %s base=0x%08lX offset=0x%08lX\r\n",
                                    me.szModule, base,
                                    (unsigned long)ctx->Eip - base);
                    } while (Module32Next(snap, &me));
                }
                fprintf(f, "LOADED MODULES:\r\n");
                if (Module32First(snap, &me)) {
                    do {
                        char path[MAX_PATH];
                        if (GetModuleFileNameA(me.hModule, path, MAX_PATH))
                            fprintf(f, "    %-30s 0x%08lX - 0x%08lX  %s\r\n",
                                    me.szModule, (unsigned long)me.modBaseAddr,
                                    (unsigned long)((unsigned long)me.modBaseAddr + me.modBaseSize),
                                    path);
                        else
                            fprintf(f, "    %-30s 0x%08lX - 0x%08lX  <no path>\r\n",
                                    me.szModule, (unsigned long)me.modBaseAddr,
                                    (unsigned long)((unsigned long)me.modBaseAddr + me.modBaseSize));
                    } while (Module32Next(snap, &me));
                }
                CloseHandle(snap);
            }
        }

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

        // What is the bogus "pointer" actually? 0x7263694D is ASCII "Micr".
        // Find which module (if any) claims that range, and try to read the
        // bytes around it so we can see what filled it in.
        {
            // Dump the game-exe code right around the return address we saw
            // on the stack, so we can see the actual call site instead of
            // guessing from the (collapsed) dump.
            {
                unsigned char* code = (unsigned char*)(*(DWORD*)((BYTE*)ctx + offsetof(CONTEXT, Esp) + 0x70));
                fprintf(f, "CODE AT 0x00420042: ");
                __try {
                    for (int k = -16; k < 32; ++k) fprintf(f, "%02X ", code[k]);
                    fprintf(f, "\r\n");
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                    fprintf(f, "CODE AT 0x00420042: <unreadable>\r\n");
                }
            }
            HANDLE msnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
            if (msnap != INVALID_HANDLE_VALUE) {
                MODULEENTRY32 me;
                me.dwSize = sizeof(me);
                if (Module32First(msnap, &me)) {
                    do {
                        unsigned long base = (unsigned long)me.modBaseAddr;
                        if ((unsigned long)ctx->Esi >= base &&
                            (unsigned long)ctx->Esi < base + me.modBaseSize)
                            fprintf(f, "ESI POINTS INTO MODULE: %s base=0x%08lX off=0x%08lX\r\n",
                                    me.szModule, base, (unsigned long)ctx->Esi - base);
                    } while (Module32Next(msnap, &me));
                }
                CloseHandle(msnap);
            }
            __try {
                unsigned char* p = (unsigned char*)ctx->Esi;
                fprintf(f, "MEM AT ESI: ");
                for (int k = -8; k < 40; ++k) {
                    unsigned char c = p[k];
                    if (c >= 32 && c < 127) fprintf(f, "%c", c);
                    else fprintf(f, ".");
                }
                fprintf(f, "\r\n");
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                fprintf(f, "MEM AT ESI: <unreadable>\r\n");
            }
            // ECX - ESI is the length the caller expected; print it.
            fprintf(f, "ECX-ESI = %lu\r\n", (unsigned long)(ctx->Ecx - ctx->Esi));
        }

        // Walk further up the stack and name the module for every plausible
        // return address. This is what tells us who actually called the
        // function that faulted.
        {
            HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
            MODULEENTRY32 me;
            me.dwSize = sizeof(me);
            fprintf(f, "STACK WALK (return addresses only):\r\n");
            __try {
                for (int d = 0; d < 256; ++d) {
                    DWORD v = ((DWORD*)ctx->Esp)[d];
                    if (v < 0x00400000 || v > 0x7FFFFFFF) continue;
                    if (snap != INVALID_HANDLE_VALUE && Module32First(snap, &me)) {
                        do {
                            unsigned long base = (unsigned long)me.modBaseAddr;
                            if ((unsigned long)v >= base &&
                                (unsigned long)v < base + me.modBaseSize) {
                                fprintf(f, "  [esp+0x%03X] = 0x%08X  %s+0x%05lX%s\r\n",
                                        d * 4, v, me.szModule,
                                        (unsigned long)v - base,
                                        (base == 0x00400000) ? "   <== GAME EXE" : "");
                                break;
                            }
                        } while (Module32Next(snap, &me));
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                fprintf(f, "  <stack walk stopped>\r\n");
            }
            if (snap != INVALID_HANDLE_VALUE) CloseHandle(snap);
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
    
    // --- early video trace: must run before Detour/console setup ---
    {
        extern void VideoTrace(const char* fmt, ...);
        char mb[MAX_PATH];
        SYSTEMTIME st;
        GetLocalTime(&st);
        sprintf(mb, "C:\\games\\GTA2 _old\\log\\video_trace.log");
        FILE* vf = fopen(mb, "ab");
        if (vf) {
            fprintf(vf, "=== DllMain reason=%lu  dll=%p  hWnd=%p ===\r\n",
                (unsigned long)dwReason, (void*)hModule, (void*)GetForegroundWindow());
            fclose(vf);
        }
    }

    AllocConsole();
    switch (dwReason){
     

case DLL_PROCESS_ATTACH:
       /// MessageBox(0, L"Load Dll!", 0, 0);
        SetUnhandledExceptionFilter(&CrashFilter);
        AddVectoredExceptionHandler(1, &CrashPatchVeh);
        {
            extern void VideoTraceInstall();
            extern void VideoTraceStartVidHook();
            VideoTraceInstall();
            VideoTraceStartVidHook();
        }
        TraceInit();
         TraceEvent("DllMain: DLL_PROCESS_ATTACH");
         StartInspector();
         SaveDebugStartHotkeys();

        DetourRestoreAfterWith();

        // Isolation switch: set GTA2_NOHOOK=1 to load this DLL for tracing only,
        // with every detour left detached. Any crash that still happens then
        // belongs to the game, not to our hooks. This is the cheapest way to
        // tell "our hook returns garbage" apart from "the port is broken".
        if (getenv("GTA2_NOHOOK")) {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOHOOK set - all detours skipped");
            InstallAudioWatchHooks();
            InstallMilesWatchHooks();
            break;
        }

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
        // audio-path probe: DMAudio/LoadSTY/PlayMusic/StopMusic + open of *.wav
        InstallAudioWatchHooks();
        // Miles probe: all 52 AIL_* exports gta2.exe imports from mss32.dll v5.0r
        InstallMilesWatchHooks();
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
