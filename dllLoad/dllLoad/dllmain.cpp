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
#include "cClassProbe.h"
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
#include "cPed.h"
#include "cWeapon.h"
#include "cGame.h"
#include "cSaveLog.h"
#include "cHudTrace.h"
#include "cCharacterTrace.h"
#include "cS169Trace.h"
#include "cPlayerTrace.h"
#include "cCarTrace.h"


#pragma comment(lib, "detours.lib")

int FunMapGM();
///void  FunS20();
void printError(LONG Error, PVOID address);

unsigned int Error;

// Trampoline to the original Menu::LoadTextMenu (0x00453E20).
// DetourAttach rewrites this variable to the Detours trampoline; cMenu.cpp
// calls through it so the retail code still builds every menu page / reads .gxt text.
LPVOID _LoadTextMenu = (LPVOID)0x00453E20;

// Trampoline to the retail menu text resolver (0x00452200). DetourAttach
// rewrites this variable to the trampoline; HookMenuResolveText calls through
// it first and then overrides the string only for our own selector pages.
// (AddrToFunc.h labels this address "Menu::ApplyMoneyCheatIfApplicable" - the
// label is wrong: the function resolves menu entry text, page1/page5 special
// cases included.)
LPVOID _MenuResolveText = (LPVOID)0x00452200;


LPVOID _InitDefautValue = (LPVOID)0x00461AF0;        // InitDefautValue
LPVOID _InitGraphicsAndInput = (LPVOID)0x004031C0;     // InitGraphicsAndInput
LPVOID _SetWeapon = (LPVOID)0x00433810;               // Weapon::SetWeapon
LPVOID _SetPed = (LPVOID)0x004CCA10;                  // Weapon::SetPed
LPVOID _CopyNameGang = (LPVOID)0x0045DB40;             // Gang::SetName
LPVOID _PedSetSearchType = (LPVOID)0x00403920;         // Ped::SetSearchType
LPVOID _PedSetS169 = (LPVOID)0x00403930;               // Ped::SetS169
LPVOID _PedSetCarId = (LPVOID)0x00403940;              // Ped::SetCarId
LPVOID _PedSetHealth = (LPVOID)0x004039A0;             // Ped::SetHealth
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
LPVOID _UpdateWrapper = (LPVOID)0x004CAC30;

// --- save-file writers (see cSaveLog.h): trampolines used by cSaveLog.cpp ---
LPVOID _WriteFileSvg = (LPVOID)0x0047EF40;  // MissionManager::SaveFile
LPVOID _WriteFileDat = (LPVOID)0x004A89E0;  // PlayerData::WriteFileNamePlayer
LPVOID _WriteFileHsc = (LPVOID)0x004A8D80;  // PlayerData::sub_4A8D80 (hiscores)
LPVOID _UpdateBestScores = (LPVOID)0x004A90A0; // PlayerData::UpdateBestScores
LPVOID _MapGmSetScores = (LPVOID)0x0045EC20;   // MapGm::sub_45EC20 (выбор мира: очки уровня)
LPVOID _SaveLevelRecord = (LPVOID)0x004A8F90;  // PlayerData::sub_4A8F90 (запись рекорда слота)

// --- text-draw observer (cMenu.cpp): trampoline to retail DrawGTATextRaw.
// Only reads: pushes every call into a 512-entry ring dumped by CrashFilter.
LPVOID _DrawGTATextRaw = (LPVOID)0x004CC100; // DrawGTATextRaw

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

// ---- low-rate draw-tape thread --------------------------------------------
// Appends the newest DrawGTATextRaw ring entries to C:\games\gta2\draw_ring.log
// every ~2 s so that a "hang" (no crash) still shows what the frontend was
// drawing just before it froze. Never touches the hot path.
static DWORD WINAPI DrawRingThreadProc(LPVOID)
{
    extern void DumpDrawRingFile(void);
    extern void DumpHudRingFile(void);
    extern void DumpCharacterRingFile(void);
    extern void DumpS169RingFile(void);
    extern void DumpPlayerRingFile(void);
    extern void DumpCarRingFile(void);
    for (;;) {
        Sleep(2000);
        DumpDrawRingFile();
        DumpHudRingFile();
        DumpCharacterRingFile();
        DumpS169RingFile();
        DumpPlayerRingFile();
        DumpCarRingFile();
    }
    return 0;
}

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

        // ---- name-typing / text-draw forensics added for the menu crash ----
        {
            __try {
                fprintf(f, "GLOW dword_67358C = 0x%08lX (lighting flag 0/0x8000)\r\n",
                        (unsigned long)(*(DWORD*)0x0067358C));
                fprintf(f, "GLOW 673400/673420/673440/673460 = 0x%08lX/0x%08lX/0x%08lX/0x%08lX\r\n",
                        (unsigned long)(*(DWORD*)0x00673400),
                        (unsigned long)(*(DWORD*)0x00673420),
                        (unsigned long)(*(DWORD*)0x00673440),
                        (unsigned long)(*(DWORD*)0x00673460));
                fprintf(f, "GLOW 673400..: ");
                for (int k = 0; k < 16; ++k) {
                    fprintf(f, "%02X ", *(unsigned char*)(0x0067357C + k));
                }
                fprintf(f, "\r\n");
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                fprintf(f, "GLOW: <unreadable>\r\n");
            }
            __try {
                Menu* m = GetGameMenu();
                if (m) {
                    fprintf(f, "MENU: Page=%u State=%d Frontend=%d FontStyle=%u "
                               "Length=%d Key=%d CurIdx=%d\r\n",
                            (unsigned)m->Page, m->State, m->FrontendState,
                            (unsigned)m->FontStyle, (int)m->Length, (int)m->Key,
                            (int)m->CurrentMenuItemsIndex);
                    fprintf(f, "MENU name: \"%.9ls\"\r\n", m->pPlayerName);
                }
                else {
                    fprintf(f, "MENU: NULL (menu not created yet)\r\n");
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                fprintf(f, "MENU: <unreadable>\r\n");
            }
            extern void DumpDrawRing(FILE* f);
            DumpDrawRing(f);
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
         // DrawGTATextRaw tape thread (see DrawRingThreadProc above). Reads
         // only our own ring; killed with the process (no cancel needed).
         {
             HANDLE h = CreateThread(NULL, 0, DrawRingThreadProc, NULL, 0, NULL);
             if (h) CloseHandle(h);
         }

DetourRestoreAfterWith();

        // CSV создаётся сразу: если fopen не сработает, ClassProbe.log
        // расскажет об этом на старте, а не молча потеряет данные.
        ProbeThisInit();

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
        Error = DetourAttach(&_MenuResolveText, (PVOID)HookMenuResolveText);
        printError(Error, _MenuResolveText);

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

        // --- Ped setters: single-store retail stubs, fully re-implemented ---
        // 1 = attach our replacements, 0 = leave retail code untouched.
        // Flip to 0 for a control run when bisecting a crash.
#define HOOK_PED_SETTERS 1
#if HOOK_PED_SETTERS
        Error = DetourAttach(&_PedSetSearchType, (PVOID)HookSetSearchType);
        printError(Error, _PedSetSearchType);
        Error = DetourAttach(&_PedSetS169, (PVOID)HookSetS169);
        printError(Error, _PedSetS169);
        Error = DetourAttach(&_PedSetCarId, (PVOID)HookSetCarId);
        printError(Error, _PedSetCarId);
        Error = DetourAttach(&_PedSetHealth, (PVOID)HookSetHealth);
        printError(Error, _PedSetHealth);
#endif

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
        Error = DetourAttach(&_UpdateBestScores, (PVOID)HookUpdateBestScores);
        printError(Error, _UpdateBestScores);
        // Выбор мира -> инструментальные хуки (cSaveLog.cpp): retail делает
        // работу, мы пишем в Save.log что именно загрузилось/записалось.
        Error = DetourAttach(&_MapGmSetScores, (PVOID)HookMapGmSetScores);
        printError(Error, _MapGmSetScores);
        Error = DetourAttach(&_SaveLevelRecord, (PVOID)HookSaveLevelRecord);
        printError(Error, _SaveLevelRecord);
        // DrawGTATextRaw observer (cMenu.cpp trace ring). Flip GTA2_NOTEXTTRACE=1
        // to prove whether this observers hook can freeze menu rendering at all.
        if (!getenv("GTA2_NOTEXTTRACE")) {
            Error = DetourAttach(&_DrawGTATextRaw, (PVOID)HookDrawGTATextRaw);
            printError(Error, _DrawGTATextRaw);
        }
        else {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOTEXTTRACE set - DrawGTATextRaw detour skipped");
        }
        // HUD observer hooks (cHudTrace.cpp): every Hud::* entry point from
        // AddrToFunc.h. Logs (this,args) into a ring taped to hud_trace.log.
        // Flip GTA2_NOHUDTRACE=1 to skip the whole set.
        if (!getenv("GTA2_NOHUDTRACE")) {
            Error = DetourAttach(&_Hud_4219F0,                 (PVOID)HookHud_4219F0);                 printError(Error, _Hud_4219F0);
            Error = DetourAttach(&_Hud_45D3A0,                 (PVOID)HookHud_45D3A0);                 printError(Error, _Hud_45D3A0);
            Error = DetourAttach(&_Hud_Hud_des,                (PVOID)HookHud_Hud_des);                printError(Error, _Hud_Hud_des);
            Error = DetourAttach(&_Hud_4C6940,                 (PVOID)HookHud_4C6940);                 printError(Error, _Hud_4C6940);
            Error = DetourAttach(&_Hud_4C6960,                 (PVOID)HookHud_4C6960);                 printError(Error, _Hud_4C6960);
            Error = DetourAttach(&_Hud_4C69A0,                 (PVOID)HookHud_4C69A0);                 printError(Error, _Hud_4C69A0);
            Error = DetourAttach(&_Hud_Hud1,                   (PVOID)HookHud_Hud1);                   printError(Error, _Hud_Hud1);
            Error = DetourAttach(&_Hud_Init_s_Wrapper,         (PVOID)HookHud_Init_s_Wrapper);         printError(Error, _Hud_Init_s_Wrapper);
            Error = DetourAttach(&_Hud_4C6DA0,                 (PVOID)HookHud_4C6DA0);                 printError(Error, _Hud_4C6DA0);
            Error = DetourAttach(&_Hud_SetSpeedText,           (PVOID)HookHud_SetSpeedText);           printError(Error, _Hud_SetSpeedText);
            Error = DetourAttach(&_Hud_4C6DE0,                 (PVOID)HookHud_4C6DE0);                 printError(Error, _Hud_4C6DE0);
            Error = DetourAttach(&_Hud_HandleKeyboard_Wrapper, (PVOID)HookHud_HandleKeyboard_Wrapper); printError(Error, _Hud_HandleKeyboard_Wrapper);
            Error = DetourAttach(&_Hud_DrawSprite,             (PVOID)HookHud_DrawSprite);             printError(Error, _Hud_DrawSprite);
            Error = DetourAttach(&_Hud_DrawSprite_Wrapper,     (PVOID)HookHud_DrawSprite_Wrapper);     printError(Error, _Hud_DrawSprite_Wrapper);
            Error = DetourAttach(&_Hud_DrawUI,                 (PVOID)HookHud_DrawUI);                 printError(Error, _Hud_DrawUI);
            Error = DetourAttach(&_Hud_DrawUIWrapper,          (PVOID)HookHud_DrawUIWrapper);          printError(Error, _Hud_DrawUIWrapper);
            Error = DetourAttach(&_Hud_Update2_Wrapper,        (PVOID)HookHud_Update2_Wrapper);        printError(Error, _Hud_Update2_Wrapper);
            Error = DetourAttach(&_Hud_4CAB50,                 (PVOID)HookHud_4CAB50);                 printError(Error, _Hud_4CAB50);
            Error = DetourAttach(&_Hud_SetSpeedText_Wrapper,   (PVOID)HookHud_SetSpeedText_Wrapper);   printError(Error, _Hud_SetSpeedText_Wrapper);
            Error = DetourAttach(&_Hud_UpdateWrapper,          (PVOID)HookHud_UpdateWrapper);          printError(Error, _Hud_UpdateWrapper);
        }
        else {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOHUDTRACE set - Hud::* observer detours skipped");
        }
        // Character observer hooks (cCharacterTrace.cpp): every Character::* entry
        // point from AddrToFunc.h. Logs (this,args) into a ring taped to
        // character_trace.log. Flip GTA2_NOCHARTRACE=1 to skip the whole set.
        if (!getenv("GTA2_NOCHARTRACE")) {
            Error = DetourAttach(&_Character_420C30, (PVOID)HookCharacter_420C30); printError(Error, _Character_420C30);
            Error = DetourAttach(&_Character_43AE10, (PVOID)HookCharacter_43AE10); printError(Error, _Character_43AE10);
            Error = DetourAttach(&_Character_43DB40, (PVOID)HookCharacter_43DB40); printError(Error, _Character_43DB40);
            Error = DetourAttach(&_Character_43DBD0, (PVOID)HookCharacter_43DBD0); printError(Error, _Character_43DBD0);
            Error = DetourAttach(&_Character_43DC60, (PVOID)HookCharacter_43DC60); printError(Error, _Character_43DC60);
            Error = DetourAttach(&_Character_43DD80, (PVOID)HookCharacter_43DD80); printError(Error, _Character_43DD80);
            Error = DetourAttach(&_Character_43DE10, (PVOID)HookCharacter_43DE10); printError(Error, _Character_43DE10);
            Error = DetourAttach(&_Character_43DEB0, (PVOID)HookCharacter_43DEB0); printError(Error, _Character_43DEB0);
            Error = DetourAttach(&_Character_43DF60, (PVOID)HookCharacter_43DF60); printError(Error, _Character_43DF60);
            Error = DetourAttach(&_Character_43DFB0, (PVOID)HookCharacter_43DFB0); printError(Error, _Character_43DFB0);
            Error = DetourAttach(&_Character_43E080, (PVOID)HookCharacter_43E080); printError(Error, _Character_43E080);
            Error = DetourAttach(&_Character_440CC0, (PVOID)HookCharacter_440CC0); printError(Error, _Character_440CC0);
            Error = DetourAttach(&_Character_4416B0, (PVOID)HookCharacter_4416B0); printError(Error, _Character_4416B0);
            Error = DetourAttach(&_Character_441960, (PVOID)HookCharacter_441960); printError(Error, _Character_441960);
            Error = DetourAttach(&_Character_445A20, (PVOID)HookCharacter_445A20); printError(Error, _Character_445A20);
            Error = DetourAttach(&_Character_45AA30, (PVOID)HookCharacter_45AA30); printError(Error, _Character_45AA30);
        }
        else {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOCHARTRACE set - Character::* observer detours skipped");
        }
        // S169 observer hooks (cS169Trace.cpp): every S169::* entry point from
        // AddrToFunc.h (the reconstruction's AIController). Logs into a ring
        // taped to s169_trace.log. Flip GTA2_NOS169TRACE=1 to skip the whole set.
        if (!getenv("GTA2_NOS169TRACE")) {
            Error = DetourAttach(&_S169_4035B0, (PVOID)HookS169_4035B0); printError(Error, _S169_4035B0);
            Error = DetourAttach(&_S169_403650, (PVOID)HookS169_403650); printError(Error, _S169_403650);
            Error = DetourAttach(&_S169_4037A0, (PVOID)HookS169_4037A0); printError(Error, _S169_4037A0);
            Error = DetourAttach(&_S169_4038E0, (PVOID)HookS169_4038E0); printError(Error, _S169_4038E0);
            Error = DetourAttach(&_S169_4038F0, (PVOID)HookS169_4038F0); printError(Error, _S169_4038F0);
            Error = DetourAttach(&_S169_403BE0, (PVOID)HookS169_403BE0); printError(Error, _S169_403BE0);
            Error = DetourAttach(&_S169_403C40, (PVOID)HookS169_403C40); printError(Error, _S169_403C40);
            Error = DetourAttach(&_S169_403D10, (PVOID)HookS169_403D10); printError(Error, _S169_403D10);
            Error = DetourAttach(&_S169_403D20, (PVOID)HookS169_403D20); printError(Error, _S169_403D20);
            Error = DetourAttach(&_S169_403DA0, (PVOID)HookS169_403DA0); printError(Error, _S169_403DA0);
            Error = DetourAttach(&_S169_403E90, (PVOID)HookS169_403E90); printError(Error, _S169_403E90);
            Error = DetourAttach(&_S169_403FB0, (PVOID)HookS169_403FB0); printError(Error, _S169_403FB0);
            Error = DetourAttach(&_S169_404120, (PVOID)HookS169_404120); printError(Error, _S169_404120);
            Error = DetourAttach(&_S169_404400, (PVOID)HookS169_404400); printError(Error, _S169_404400);
            Error = DetourAttach(&_S169_404420, (PVOID)HookS169_404420); printError(Error, _S169_404420);
            Error = DetourAttach(&_S169_404450, (PVOID)HookS169_404450); printError(Error, _S169_404450);
            Error = DetourAttach(&_S169_404480, (PVOID)HookS169_404480); printError(Error, _S169_404480);
            Error = DetourAttach(&_S169_404490, (PVOID)HookS169_404490); printError(Error, _S169_404490);
            Error = DetourAttach(&_S169_4045D0, (PVOID)HookS169_4045D0); printError(Error, _S169_4045D0);
            Error = DetourAttach(&_S169_4046F0, (PVOID)HookS169_4046F0); printError(Error, _S169_4046F0);
            Error = DetourAttach(&_S169_404840, (PVOID)HookS169_404840); printError(Error, _S169_404840);
            Error = DetourAttach(&_S169_4048A0, (PVOID)HookS169_4048A0); printError(Error, _S169_4048A0);
            Error = DetourAttach(&_S169_404900, (PVOID)HookS169_404900); printError(Error, _S169_404900);
            Error = DetourAttach(&_S169_4049F0, (PVOID)HookS169_4049F0); printError(Error, _S169_4049F0);
            Error = DetourAttach(&_S169_404AD0, (PVOID)HookS169_404AD0); printError(Error, _S169_404AD0);
            Error = DetourAttach(&_S169_404C90, (PVOID)HookS169_404C90); printError(Error, _S169_404C90);
            Error = DetourAttach(&_S169_404CE0, (PVOID)HookS169_404CE0); printError(Error, _S169_404CE0);
            Error = DetourAttach(&_S169_404D40, (PVOID)HookS169_404D40); printError(Error, _S169_404D40);
            Error = DetourAttach(&_S169_404EF0, (PVOID)HookS169_404EF0); printError(Error, _S169_404EF0);
            Error = DetourAttach(&_S169_405240, (PVOID)HookS169_405240); printError(Error, _S169_405240);
            Error = DetourAttach(&_S169_405760, (PVOID)HookS169_405760); printError(Error, _S169_405760);
            Error = DetourAttach(&_S169_433360, (PVOID)HookS169_433360); printError(Error, _S169_433360);
            Error = DetourAttach(&_S169_433370, (PVOID)HookS169_433370); printError(Error, _S169_433370);
            Error = DetourAttach(&_S169_439970, (PVOID)HookS169_439970); printError(Error, _S169_439970);
        }
        else {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOS169TRACE set - S169::* observer detours skipped");
        }
        // Player observer hooks (cPlayerTrace.cpp): every Player::* entry point from
        // AddrToFunc.h. Logs (this,args,ret) into a ring taped to player_trace.log.
        // Flip GTA2_NOPLAYERTRACE=1 to skip the whole set.
        if (!getenv("GTA2_NOPLAYERTRACE")) {
            Error = DetourAttach(&_Player_401B40, (PVOID)HookPlayer_401B40); printError(Error, _Player_401B40);
            Error = DetourAttach(&_Player_40CE50, (PVOID)HookPlayer_40CE50); printError(Error, _Player_40CE50);
            Error = DetourAttach(&_Player_40CE70, (PVOID)HookPlayer_40CE70); printError(Error, _Player_40CE70);
            Error = DetourAttach(&_Player_40E530, (PVOID)HookPlayer_40E530); printError(Error, _Player_40E530);
            Error = DetourAttach(&_Player_40E570, (PVOID)HookPlayer_40E570); printError(Error, _Player_40E570);
            Error = DetourAttach(&_Player_40EC20, (PVOID)HookPlayer_40EC20); printError(Error, _Player_40EC20);
            Error = DetourAttach(&_Player_40F840, (PVOID)HookPlayer_40F840); printError(Error, _Player_40F840);
            Error = DetourAttach(&_Player_411810, (PVOID)HookPlayer_411810); printError(Error, _Player_411810);
            Error = DetourAttach(&_Player_411820, (PVOID)HookPlayer_411820); printError(Error, _Player_411820);
            Error = DetourAttach(&_Player_411830, (PVOID)HookPlayer_411830); printError(Error, _Player_411830);
            Error = DetourAttach(&_Player_411840, (PVOID)HookPlayer_411840); printError(Error, _Player_411840);
            Error = DetourAttach(&_Player_411850, (PVOID)HookPlayer_411850); printError(Error, _Player_411850);
            Error = DetourAttach(&_Player_411860, (PVOID)HookPlayer_411860); printError(Error, _Player_411860);
            Error = DetourAttach(&_Player_41D020, (PVOID)HookPlayer_41D020); printError(Error, _Player_41D020);
            Error = DetourAttach(&_Player_41DC40, (PVOID)HookPlayer_41DC40); printError(Error, _Player_41DC40);
            Error = DetourAttach(&_Player_41DC70, (PVOID)HookPlayer_41DC70); printError(Error, _Player_41DC70);
            Error = DetourAttach(&_Player_41E260, (PVOID)HookPlayer_41E260); printError(Error, _Player_41E260);
            Error = DetourAttach(&_Player_41E390, (PVOID)HookPlayer_41E390); printError(Error, _Player_41E390);
            Error = DetourAttach(&_Player_421100, (PVOID)HookPlayer_421100); printError(Error, _Player_421100);
            Error = DetourAttach(&_Player_421150, (PVOID)HookPlayer_421150); printError(Error, _Player_421150);
            Error = DetourAttach(&_Player_4211A0, (PVOID)HookPlayer_4211A0); printError(Error, _Player_4211A0);
            Error = DetourAttach(&_Player_4211C0, (PVOID)HookPlayer_4211C0); printError(Error, _Player_4211C0);
            Error = DetourAttach(&_Player_421260, (PVOID)HookPlayer_421260); printError(Error, _Player_421260);
            Error = DetourAttach(&_Player_421270, (PVOID)HookPlayer_421270); printError(Error, _Player_421270);
            Error = DetourAttach(&_Player_4212A0, (PVOID)HookPlayer_4212A0); printError(Error, _Player_4212A0);
            Error = DetourAttach(&_Player_4212B0, (PVOID)HookPlayer_4212B0); printError(Error, _Player_4212B0);
            Error = DetourAttach(&_Player_421980, (PVOID)HookPlayer_421980); printError(Error, _Player_421980);
            Error = DetourAttach(&_Player_421990, (PVOID)HookPlayer_421990); printError(Error, _Player_421990);
            Error = DetourAttach(&_Player_4219A0, (PVOID)HookPlayer_4219A0); printError(Error, _Player_4219A0);
            Error = DetourAttach(&_Player_4219D0, (PVOID)HookPlayer_4219D0); printError(Error, _Player_4219D0);
            Error = DetourAttach(&_Player_424470, (PVOID)HookPlayer_424470); printError(Error, _Player_424470);
            Error = DetourAttach(&_Player_4348F0, (PVOID)HookPlayer_4348F0); printError(Error, _Player_4348F0);
            Error = DetourAttach(&_Player_434900, (PVOID)HookPlayer_434900); printError(Error, _Player_434900);
            Error = DetourAttach(&_Player_434920, (PVOID)HookPlayer_434920); printError(Error, _Player_434920);
            Error = DetourAttach(&_Player_434940, (PVOID)HookPlayer_434940); printError(Error, _Player_434940);
            Error = DetourAttach(&_Player_434950, (PVOID)HookPlayer_434950); printError(Error, _Player_434950);
            Error = DetourAttach(&_Player_453A90, (PVOID)HookPlayer_453A90); printError(Error, _Player_453A90);
            Error = DetourAttach(&_Player_453AB0, (PVOID)HookPlayer_453AB0); printError(Error, _Player_453AB0);
            Error = DetourAttach(&_Player_45A970, (PVOID)HookPlayer_45A970); printError(Error, _Player_45A970);
            Error = DetourAttach(&_Player_45B0C0, (PVOID)HookPlayer_45B0C0); printError(Error, _Player_45B0C0);
            Error = DetourAttach(&_Player_45B0D0, (PVOID)HookPlayer_45B0D0); printError(Error, _Player_45B0D0);
            Error = DetourAttach(&_Player_461DB0, (PVOID)HookPlayer_461DB0); printError(Error, _Player_461DB0);
            Error = DetourAttach(&_Player_4766A0, (PVOID)HookPlayer_4766A0); printError(Error, _Player_4766A0);
            Error = DetourAttach(&_Player_4766B0, (PVOID)HookPlayer_4766B0); printError(Error, _Player_4766B0);
            Error = DetourAttach(&_Player_4766C0, (PVOID)HookPlayer_4766C0); printError(Error, _Player_4766C0);
            Error = DetourAttach(&_Player_4766D0, (PVOID)HookPlayer_4766D0); printError(Error, _Player_4766D0);
            Error = DetourAttach(&_Player_476700, (PVOID)HookPlayer_476700); printError(Error, _Player_476700);
            Error = DetourAttach(&_Player_476730, (PVOID)HookPlayer_476730); printError(Error, _Player_476730);
            Error = DetourAttach(&_Player_482CC0, (PVOID)HookPlayer_482CC0); printError(Error, _Player_482CC0);
            Error = DetourAttach(&_Player_49DD10, (PVOID)HookPlayer_49DD10); printError(Error, _Player_49DD10);
            Error = DetourAttach(&_Player_49DD20, (PVOID)HookPlayer_49DD20); printError(Error, _Player_49DD20);
            Error = DetourAttach(&_Player_49DD30, (PVOID)HookPlayer_49DD30); printError(Error, _Player_49DD30);
            Error = DetourAttach(&_Player_49DD80, (PVOID)HookPlayer_49DD80); printError(Error, _Player_49DD80);
            Error = DetourAttach(&_Player_49DDF0, (PVOID)HookPlayer_49DDF0); printError(Error, _Player_49DDF0);
            Error = DetourAttach(&_Player_49DE40, (PVOID)HookPlayer_49DE40); printError(Error, _Player_49DE40);
            Error = DetourAttach(&_Player_49DEF0, (PVOID)HookPlayer_49DEF0); printError(Error, _Player_49DEF0);
            Error = DetourAttach(&_Player_49DF90, (PVOID)HookPlayer_49DF90); printError(Error, _Player_49DF90);
            Error = DetourAttach(&_Player_49E040, (PVOID)HookPlayer_49E040); printError(Error, _Player_49E040);
            Error = DetourAttach(&_Player_49E270, (PVOID)HookPlayer_49E270); printError(Error, _Player_49E270);
            Error = DetourAttach(&_Player_49E650, (PVOID)HookPlayer_49E650); printError(Error, _Player_49E650);
            Error = DetourAttach(&_Player_49E820, (PVOID)HookPlayer_49E820); printError(Error, _Player_49E820);
            Error = DetourAttach(&_Player_49E950, (PVOID)HookPlayer_49E950); printError(Error, _Player_49E950);
            Error = DetourAttach(&_Player_49E980, (PVOID)HookPlayer_49E980); printError(Error, _Player_49E980);
            Error = DetourAttach(&_Player_49EA60, (PVOID)HookPlayer_49EA60); printError(Error, _Player_49EA60);
            Error = DetourAttach(&_Player_49EA70, (PVOID)HookPlayer_49EA70); printError(Error, _Player_49EA70);
            Error = DetourAttach(&_Player_49EC80, (PVOID)HookPlayer_49EC80); printError(Error, _Player_49EC80);
            Error = DetourAttach(&_Player_49ECA0, (PVOID)HookPlayer_49ECA0); printError(Error, _Player_49ECA0);
            Error = DetourAttach(&_Player_49ECC0, (PVOID)HookPlayer_49ECC0); printError(Error, _Player_49ECC0);
            Error = DetourAttach(&_Player_49ED00, (PVOID)HookPlayer_49ED00); printError(Error, _Player_49ED00);
            Error = DetourAttach(&_Player_49ED60, (PVOID)HookPlayer_49ED60); printError(Error, _Player_49ED60);
            Error = DetourAttach(&_Player_49EDC0, (PVOID)HookPlayer_49EDC0); printError(Error, _Player_49EDC0);
            Error = DetourAttach(&_Player_49EE10, (PVOID)HookPlayer_49EE10); printError(Error, _Player_49EE10);
            Error = DetourAttach(&_Player_49EE80, (PVOID)HookPlayer_49EE80); printError(Error, _Player_49EE80);
            Error = DetourAttach(&_Player_49EEB0, (PVOID)HookPlayer_49EEB0); printError(Error, _Player_49EEB0);
            Error = DetourAttach(&_Player_49EF50, (PVOID)HookPlayer_49EF50); printError(Error, _Player_49EF50);
            Error = DetourAttach(&_Player_49EF80, (PVOID)HookPlayer_49EF80); printError(Error, _Player_49EF80);
            Error = DetourAttach(&_Player_49F010, (PVOID)HookPlayer_49F010); printError(Error, _Player_49F010);
            Error = DetourAttach(&_Player_49F170, (PVOID)HookPlayer_49F170); printError(Error, _Player_49F170);
            Error = DetourAttach(&_Player_49F1B0, (PVOID)HookPlayer_49F1B0); printError(Error, _Player_49F1B0);
            Error = DetourAttach(&_Player_49F280, (PVOID)HookPlayer_49F280); printError(Error, _Player_49F280);
            Error = DetourAttach(&_Player_49F2D0, (PVOID)HookPlayer_49F2D0); printError(Error, _Player_49F2D0);
            Error = DetourAttach(&_Player_49F350, (PVOID)HookPlayer_49F350); printError(Error, _Player_49F350);
            Error = DetourAttach(&_Player_49F460, (PVOID)HookPlayer_49F460); printError(Error, _Player_49F460);
            Error = DetourAttach(&_Player_49F4E0, (PVOID)HookPlayer_49F4E0); printError(Error, _Player_49F4E0);
            Error = DetourAttach(&_Player_49F4F0, (PVOID)HookPlayer_49F4F0); printError(Error, _Player_49F4F0);
            Error = DetourAttach(&_Player_49F500, (PVOID)HookPlayer_49F500); printError(Error, _Player_49F500);
            Error = DetourAttach(&_Player_49F570, (PVOID)HookPlayer_49F570); printError(Error, _Player_49F570);
            Error = DetourAttach(&_Player_49F660, (PVOID)HookPlayer_49F660); printError(Error, _Player_49F660);
            Error = DetourAttach(&_Player_49F6C0, (PVOID)HookPlayer_49F6C0); printError(Error, _Player_49F6C0);
            Error = DetourAttach(&_Player_49F720, (PVOID)HookPlayer_49F720); printError(Error, _Player_49F720);
            Error = DetourAttach(&_Player_49F930, (PVOID)HookPlayer_49F930); printError(Error, _Player_49F930);
            Error = DetourAttach(&_Player_49FAC0, (PVOID)HookPlayer_49FAC0); printError(Error, _Player_49FAC0);
            Error = DetourAttach(&_Player_49FB00, (PVOID)HookPlayer_49FB00); printError(Error, _Player_49FB00);
            Error = DetourAttach(&_Player_49FBE0, (PVOID)HookPlayer_49FBE0); printError(Error, _Player_49FBE0);
            Error = DetourAttach(&_Player_49FDC0, (PVOID)HookPlayer_49FDC0); printError(Error, _Player_49FDC0);
            Error = DetourAttach(&_Player_49FF80, (PVOID)HookPlayer_49FF80); printError(Error, _Player_49FF80);
            Error = DetourAttach(&_Player_4A0020, (PVOID)HookPlayer_4A0020); printError(Error, _Player_4A0020);
            Error = DetourAttach(&_Player_4A0080, (PVOID)HookPlayer_4A0080); printError(Error, _Player_4A0080);
            Error = DetourAttach(&_Player_4A0120, (PVOID)HookPlayer_4A0120); printError(Error, _Player_4A0120);
            Error = DetourAttach(&_Player_4A0290, (PVOID)HookPlayer_4A0290); printError(Error, _Player_4A0290);
            Error = DetourAttach(&_Player_4A0560, (PVOID)HookPlayer_4A0560); printError(Error, _Player_4A0560);
            Error = DetourAttach(&_Player_4A0850, (PVOID)HookPlayer_4A0850); printError(Error, _Player_4A0850);
            Error = DetourAttach(&_Player_4A0900, (PVOID)HookPlayer_4A0900); printError(Error, _Player_4A0900);
            Error = DetourAttach(&_Player_4A0930, (PVOID)HookPlayer_4A0930); printError(Error, _Player_4A0930);
            Error = DetourAttach(&_Player_4A0960, (PVOID)HookPlayer_4A0960); printError(Error, _Player_4A0960);
            Error = DetourAttach(&_Player_4A09B0, (PVOID)HookPlayer_4A09B0); printError(Error, _Player_4A09B0);
            Error = DetourAttach(&_Player_4A0C60, (PVOID)HookPlayer_4A0C60); printError(Error, _Player_4A0C60);
            Error = DetourAttach(&_Player_4A0CC0, (PVOID)HookPlayer_4A0CC0); printError(Error, _Player_4A0CC0);
            Error = DetourAttach(&_Player_4A0D10, (PVOID)HookPlayer_4A0D10); printError(Error, _Player_4A0D10);
            Error = DetourAttach(&_Player_4A0D40, (PVOID)HookPlayer_4A0D40); printError(Error, _Player_4A0D40);
            Error = DetourAttach(&_Player_4A0F30, (PVOID)HookPlayer_4A0F30); printError(Error, _Player_4A0F30);
            Error = DetourAttach(&_Player_4A1130, (PVOID)HookPlayer_4A1130); printError(Error, _Player_4A1130);
            Error = DetourAttach(&_Player_4A1360, (PVOID)HookPlayer_4A1360); printError(Error, _Player_4A1360);
            Error = DetourAttach(&_Player_4A16B0, (PVOID)HookPlayer_4A16B0); printError(Error, _Player_4A16B0);
            Error = DetourAttach(&_Player_4A1B20, (PVOID)HookPlayer_4A1B20); printError(Error, _Player_4A1B20);
            Error = DetourAttach(&_Player_4A1BA0, (PVOID)HookPlayer_4A1BA0); printError(Error, _Player_4A1BA0);
            Error = DetourAttach(&_Player_4A1BE0, (PVOID)HookPlayer_4A1BE0); printError(Error, _Player_4A1BE0);
            Error = DetourAttach(&_Player_4A1DA0, (PVOID)HookPlayer_4A1DA0); printError(Error, _Player_4A1DA0);
            Error = DetourAttach(&_Player_4A20E0, (PVOID)HookPlayer_4A20E0); printError(Error, _Player_4A20E0);
            Error = DetourAttach(&_Player_4A2240, (PVOID)HookPlayer_4A2240); printError(Error, _Player_4A2240);
            Error = DetourAttach(&_Player_4A2640, (PVOID)HookPlayer_4A2640); printError(Error, _Player_4A2640);
            Error = DetourAttach(&_Player_4A26C0, (PVOID)HookPlayer_4A26C0); printError(Error, _Player_4A26C0);
            Error = DetourAttach(&_Player_4A2980, (PVOID)HookPlayer_4A2980); printError(Error, _Player_4A2980);
            Error = DetourAttach(&_Player_4A2C70, (PVOID)HookPlayer_4A2C70); printError(Error, _Player_4A2C70);
            Error = DetourAttach(&_Player_4A2D70, (PVOID)HookPlayer_4A2D70); printError(Error, _Player_4A2D70);
            Error = DetourAttach(&_Player_4A2DB0, (PVOID)HookPlayer_4A2DB0); printError(Error, _Player_4A2DB0);
            Error = DetourAttach(&_Player_4A2E00, (PVOID)HookPlayer_4A2E00); printError(Error, _Player_4A2E00);
            Error = DetourAttach(&_Player_4A2F20, (PVOID)HookPlayer_4A2F20); printError(Error, _Player_4A2F20);
            Error = DetourAttach(&_Player_4A3140, (PVOID)HookPlayer_4A3140); printError(Error, _Player_4A3140);
            Error = DetourAttach(&_Player_4A31B0, (PVOID)HookPlayer_4A31B0); printError(Error, _Player_4A31B0);
            Error = DetourAttach(&_Player_4A32D0, (PVOID)HookPlayer_4A32D0); printError(Error, _Player_4A32D0);
            Error = DetourAttach(&_Player_4A34A0, (PVOID)HookPlayer_4A34A0); printError(Error, _Player_4A34A0);
            Error = DetourAttach(&_Player_4A3A40, (PVOID)HookPlayer_4A3A40); printError(Error, _Player_4A3A40);
            Error = DetourAttach(&_Player_4A3DF0, (PVOID)HookPlayer_4A3DF0); printError(Error, _Player_4A3DF0);
            Error = DetourAttach(&_Player_4A3FB0, (PVOID)HookPlayer_4A3FB0); printError(Error, _Player_4A3FB0);
            Error = DetourAttach(&_Player_4A4170, (PVOID)HookPlayer_4A4170); printError(Error, _Player_4A4170);
            Error = DetourAttach(&_Player_4A4490, (PVOID)HookPlayer_4A4490); printError(Error, _Player_4A4490);
            Error = DetourAttach(&_Player_4A4570, (PVOID)HookPlayer_4A4570); printError(Error, _Player_4A4570);
            Error = DetourAttach(&_Player_4A4780, (PVOID)HookPlayer_4A4780); printError(Error, _Player_4A4780);
            Error = DetourAttach(&_Player_4A47F0, (PVOID)HookPlayer_4A47F0); printError(Error, _Player_4A47F0);
            Error = DetourAttach(&_Player_4A4890, (PVOID)HookPlayer_4A4890); printError(Error, _Player_4A4890);
            Error = DetourAttach(&_Player_4A48C0, (PVOID)HookPlayer_4A48C0); printError(Error, _Player_4A48C0);
            Error = DetourAttach(&_Player_4A48E0, (PVOID)HookPlayer_4A48E0); printError(Error, _Player_4A48E0);
            Error = DetourAttach(&_Player_4A4930, (PVOID)HookPlayer_4A4930); printError(Error, _Player_4A4930);
            Error = DetourAttach(&_Player_4A4940, (PVOID)HookPlayer_4A4940); printError(Error, _Player_4A4940);
            Error = DetourAttach(&_Player_4A49B0, (PVOID)HookPlayer_4A49B0); printError(Error, _Player_4A49B0);
            Error = DetourAttach(&_Player_4A49C0, (PVOID)HookPlayer_4A49C0); printError(Error, _Player_4A49C0);
            Error = DetourAttach(&_Player_4A4AE0, (PVOID)HookPlayer_4A4AE0); printError(Error, _Player_4A4AE0);
            Error = DetourAttach(&_Player_4A4C40, (PVOID)HookPlayer_4A4C40); printError(Error, _Player_4A4C40);
            Error = DetourAttach(&_Player_4A4C90, (PVOID)HookPlayer_4A4C90); printError(Error, _Player_4A4C90);
            Error = DetourAttach(&_Player_4A4CB0, (PVOID)HookPlayer_4A4CB0); printError(Error, _Player_4A4CB0);
            Error = DetourAttach(&_Player_4A4CF0, (PVOID)HookPlayer_4A4CF0); printError(Error, _Player_4A4CF0);
            Error = DetourAttach(&_Player_4A4D50, (PVOID)HookPlayer_4A4D50); printError(Error, _Player_4A4D50);
            Error = DetourAttach(&_Player_4A4E10, (PVOID)HookPlayer_4A4E10); printError(Error, _Player_4A4E10);
            Error = DetourAttach(&_Player_4A4E70, (PVOID)HookPlayer_4A4E70); printError(Error, _Player_4A4E70);
            Error = DetourAttach(&_Player_4A4EA0, (PVOID)HookPlayer_4A4EA0); printError(Error, _Player_4A4EA0);
            Error = DetourAttach(&_Player_4A5100, (PVOID)HookPlayer_4A5100); printError(Error, _Player_4A5100);
            Error = DetourAttach(&_Player_4A5130, (PVOID)HookPlayer_4A5130); printError(Error, _Player_4A5130);
            Error = DetourAttach(&_Player_4A5150, (PVOID)HookPlayer_4A5150); printError(Error, _Player_4A5150);
            Error = DetourAttach(&_Player_4A5180, (PVOID)HookPlayer_4A5180); printError(Error, _Player_4A5180);
            Error = DetourAttach(&_Player_4A51C0, (PVOID)HookPlayer_4A51C0); printError(Error, _Player_4A51C0);
            Error = DetourAttach(&_Player_4A5220, (PVOID)HookPlayer_4A5220); printError(Error, _Player_4A5220);
            Error = DetourAttach(&_Player_4A5300, (PVOID)HookPlayer_4A5300); printError(Error, _Player_4A5300);
            Error = DetourAttach(&_Player_4A53D0, (PVOID)HookPlayer_4A53D0); printError(Error, _Player_4A53D0);
            Error = DetourAttach(&_Player_4A5400, (PVOID)HookPlayer_4A5400); printError(Error, _Player_4A5400);
            Error = DetourAttach(&_Player_4A5460, (PVOID)HookPlayer_4A5460); printError(Error, _Player_4A5460);
            Error = DetourAttach(&_Player_4A5570, (PVOID)HookPlayer_4A5570); printError(Error, _Player_4A5570);
            Error = DetourAttach(&_Player_4A5600, (PVOID)HookPlayer_4A5600); printError(Error, _Player_4A5600);
            Error = DetourAttach(&_Player_4A5640, (PVOID)HookPlayer_4A5640); printError(Error, _Player_4A5640);
            Error = DetourAttach(&_Player_4A5690, (PVOID)HookPlayer_4A5690); printError(Error, _Player_4A5690);
            Error = DetourAttach(&_Player_4A5710, (PVOID)HookPlayer_4A5710); printError(Error, _Player_4A5710);
            Error = DetourAttach(&_Player_4A5780, (PVOID)HookPlayer_4A5780); printError(Error, _Player_4A5780);
            Error = DetourAttach(&_Player_4A59A0, (PVOID)HookPlayer_4A59A0); printError(Error, _Player_4A59A0);
            Error = DetourAttach(&_Player_4A5A50, (PVOID)HookPlayer_4A5A50); printError(Error, _Player_4A5A50);
            Error = DetourAttach(&_Player_4A5AD0, (PVOID)HookPlayer_4A5AD0); printError(Error, _Player_4A5AD0);
            Error = DetourAttach(&_Player_4A5B40, (PVOID)HookPlayer_4A5B40); printError(Error, _Player_4A5B40);
            Error = DetourAttach(&_Player_4A5E90, (PVOID)HookPlayer_4A5E90); printError(Error, _Player_4A5E90);
            Error = DetourAttach(&_Player_4A6050, (PVOID)HookPlayer_4A6050); printError(Error, _Player_4A6050);
            Error = DetourAttach(&_Player_4A6100, (PVOID)HookPlayer_4A6100); printError(Error, _Player_4A6100);
            Error = DetourAttach(&_Player_4A61F0, (PVOID)HookPlayer_4A61F0); printError(Error, _Player_4A61F0);
            Error = DetourAttach(&_Player_4A62B0, (PVOID)HookPlayer_4A62B0); printError(Error, _Player_4A62B0);
            Error = DetourAttach(&_Player_4A6310, (PVOID)HookPlayer_4A6310); printError(Error, _Player_4A6310);
            Error = DetourAttach(&_Player_4A6350, (PVOID)HookPlayer_4A6350); printError(Error, _Player_4A6350);
            Error = DetourAttach(&_Player_4A6400, (PVOID)HookPlayer_4A6400); printError(Error, _Player_4A6400);
            Error = DetourAttach(&_Player_4A6530, (PVOID)HookPlayer_4A6530); printError(Error, _Player_4A6530);
            Error = DetourAttach(&_Player_4A65E0, (PVOID)HookPlayer_4A65E0); printError(Error, _Player_4A65E0);
            Error = DetourAttach(&_Player_4A6610, (PVOID)HookPlayer_4A6610); printError(Error, _Player_4A6610);
            Error = DetourAttach(&_Player_4A6900, (PVOID)HookPlayer_4A6900); printError(Error, _Player_4A6900);
            Error = DetourAttach(&_Player_4A69A0, (PVOID)HookPlayer_4A69A0); printError(Error, _Player_4A69A0);
            Error = DetourAttach(&_Player_4A6A80, (PVOID)HookPlayer_4A6A80); printError(Error, _Player_4A6A80);
            Error = DetourAttach(&_Player_4A6B20, (PVOID)HookPlayer_4A6B20); printError(Error, _Player_4A6B20);
            Error = DetourAttach(&_Player_4A6C80, (PVOID)HookPlayer_4A6C80); printError(Error, _Player_4A6C80);
            Error = DetourAttach(&_Player_4A6EF0, (PVOID)HookPlayer_4A6EF0); printError(Error, _Player_4A6EF0);
            Error = DetourAttach(&_Player_4A6FD0, (PVOID)HookPlayer_4A6FD0); printError(Error, _Player_4A6FD0);
            Error = DetourAttach(&_Player_4A7010, (PVOID)HookPlayer_4A7010); printError(Error, _Player_4A7010);
            Error = DetourAttach(&_Player_4A7680, (PVOID)HookPlayer_4A7680); printError(Error, _Player_4A7680);
            Error = DetourAttach(&_Player_4A76D0, (PVOID)HookPlayer_4A76D0); printError(Error, _Player_4A76D0);
            Error = DetourAttach(&_Player_4A7910, (PVOID)HookPlayer_4A7910); printError(Error, _Player_4A7910);
            Error = DetourAttach(&_Player_4A7B70, (PVOID)HookPlayer_4A7B70); printError(Error, _Player_4A7B70);
            Error = DetourAttach(&_Player_4A7BA0, (PVOID)HookPlayer_4A7BA0); printError(Error, _Player_4A7BA0);
            Error = DetourAttach(&_Player_4A7E80, (PVOID)HookPlayer_4A7E80); printError(Error, _Player_4A7E80);
            Error = DetourAttach(&_Player_4A81E0, (PVOID)HookPlayer_4A81E0); printError(Error, _Player_4A81E0);
            Error = DetourAttach(&_Player_4A8340, (PVOID)HookPlayer_4A8340); printError(Error, _Player_4A8340);
            Error = DetourAttach(&_Player_4A83C0, (PVOID)HookPlayer_4A83C0); printError(Error, _Player_4A83C0);
            Error = DetourAttach(&_Player_4BA0A0, (PVOID)HookPlayer_4BA0A0); printError(Error, _Player_4BA0A0);
            Error = DetourAttach(&_Player_4C7340, (PVOID)HookPlayer_4C7340); printError(Error, _Player_4C7340);
            Error = DetourAttach(&_Player_4CCAB0, (PVOID)HookPlayer_4CCAB0); printError(Error, _Player_4CCAB0);
            Error = DetourAttach(&_Player_4CCAD0, (PVOID)HookPlayer_4CCAD0); printError(Error, _Player_4CCAD0);
            Error = DetourAttach(&_Player_4CCAE0, (PVOID)HookPlayer_4CCAE0); printError(Error, _Player_4CCAE0);
        }
        else {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOPLAYERTRACE set - Player::* observer detours skipped");
        }
        // Car observer hooks (cCarTrace.cpp): every Car::* entry point from AddrToFunc.h
        // Logs (this,args,ret) into a ring taped to car_trace.log.
        // Flip GTA2_NOCARTRACE=1 to skip the whole set.
                                if (!getenv("GTA2_NOCARTRACE")) {
            Error = DetourAttach(&_Car_403800, (PVOID)HookCar_403800); printError(Error, _Car_403800);
            Error = DetourAttach(&_Car_403820, (PVOID)HookCar_403820); printError(Error, _Car_403820);
            Error = DetourAttach(&_Car_403BA0, (PVOID)HookCar_403BA0); printError(Error, _Car_403BA0);
            Error = DetourAttach(&_Car_403BC0, (PVOID)HookCar_403BC0); printError(Error, _Car_403BC0);
            Error = DetourAttach(&_Car_40F890, (PVOID)HookCar_40F890); printError(Error, _Car_40F890);
            Error = DetourAttach(&_Car_4112A0, (PVOID)HookCar_4112A0); printError(Error, _Car_4112A0);
            Error = DetourAttach(&_Car_4118B0, (PVOID)HookCar_4118B0); printError(Error, _Car_4118B0);
            Error = DetourAttach(&_Car_4118C0, (PVOID)HookCar_4118C0); printError(Error, _Car_4118C0);
            Error = DetourAttach(&_Car_4118D0, (PVOID)HookCar_4118D0); printError(Error, _Car_4118D0);
            Error = DetourAttach(&_Car_4118F0, (PVOID)HookCar_4118F0); printError(Error, _Car_4118F0);
            Error = DetourAttach(&_Car_411900, (PVOID)HookCar_411900); printError(Error, _Car_411900);
            Error = DetourAttach(&_Car_411910, (PVOID)HookCar_411910); printError(Error, _Car_411910);
            Error = DetourAttach(&_Car_411920, (PVOID)HookCar_411920); printError(Error, _Car_411920);
            Error = DetourAttach(&_Car_411930, (PVOID)HookCar_411930); printError(Error, _Car_411930);
            Error = DetourAttach(&_Car_411940, (PVOID)HookCar_411940); printError(Error, _Car_411940);
            Error = DetourAttach(&_Car_411950, (PVOID)HookCar_411950); printError(Error, _Car_411950);
            Error = DetourAttach(&_Car_411970, (PVOID)HookCar_411970); printError(Error, _Car_411970);
            Error = DetourAttach(&_Car_411990, (PVOID)HookCar_411990); printError(Error, _Car_411990);
            Error = DetourAttach(&_Car_414F20, (PVOID)HookCar_414F20); printError(Error, _Car_414F20);
            Error = DetourAttach(&_Car_414F60, (PVOID)HookCar_414F60); printError(Error, _Car_414F60);
            Error = DetourAttach(&_Car_414F70, (PVOID)HookCar_414F70); printError(Error, _Car_414F70);
            Error = DetourAttach(&_Car_414F80, (PVOID)HookCar_414F80); printError(Error, _Car_414F80);
            Error = DetourAttach(&_Car_416B80, (PVOID)HookCar_416B80); printError(Error, _Car_416B80);
            Error = DetourAttach(&_Car_416BB0, (PVOID)HookCar_416BB0); printError(Error, _Car_416BB0);
            Error = DetourAttach(&_Car_41E430, (PVOID)HookCar_41E430); printError(Error, _Car_41E430);
            Error = DetourAttach(&_Car_41E440, (PVOID)HookCar_41E440); printError(Error, _Car_41E440);
            Error = DetourAttach(&_Car_41E450, (PVOID)HookCar_41E450); printError(Error, _Car_41E450);
            Error = DetourAttach(&_Car_41E460, (PVOID)HookCar_41E460); printError(Error, _Car_41E460);
            Error = DetourAttach(&_Car_41F6E0, (PVOID)HookCar_41F6E0); printError(Error, _Car_41F6E0);
            Error = DetourAttach(&_Car_41F700, (PVOID)HookCar_41F700); printError(Error, _Car_41F700);
            Error = DetourAttach(&_Car_41F730, (PVOID)HookCar_41F730); printError(Error, _Car_41F730);
            Error = DetourAttach(&_Car_41F750, (PVOID)HookCar_41F750); printError(Error, _Car_41F750);
            Error = DetourAttach(&_Car_41F860, (PVOID)HookCar_41F860); printError(Error, _Car_41F860);
            Error = DetourAttach(&_Car_41F880, (PVOID)HookCar_41F880); printError(Error, _Car_41F880);
            Error = DetourAttach(&_Car_41F8A0, (PVOID)HookCar_41F8A0); printError(Error, _Car_41F8A0);
            Error = DetourAttach(&_Car_41F8F0, (PVOID)HookCar_41F8F0); printError(Error, _Car_41F8F0);
            Error = DetourAttach(&_Car_41F940, (PVOID)HookCar_41F940); printError(Error, _Car_41F940);
            Error = DetourAttach(&_Car_41F960, (PVOID)HookCar_41F960); printError(Error, _Car_41F960);
            Error = DetourAttach(&_Car_41FA60, (PVOID)HookCar_41FA60); printError(Error, _Car_41FA60);
            Error = DetourAttach(&_Car_41FAB0, (PVOID)HookCar_41FAB0); printError(Error, _Car_41FAB0);
            Error = DetourAttach(&_Car_41FAC0, (PVOID)HookCar_41FAC0); printError(Error, _Car_41FAC0);
            Error = DetourAttach(&_Car_41FBB0, (PVOID)HookCar_41FBB0); printError(Error, _Car_41FBB0);
            Error = DetourAttach(&_Car_41FBD0, (PVOID)HookCar_41FBD0); printError(Error, _Car_41FBD0);
            Error = DetourAttach(&_Car_41FD50, (PVOID)HookCar_41FD50); printError(Error, _Car_41FD50);
            Error = DetourAttach(&_Car_41FDA0, (PVOID)HookCar_41FDA0); printError(Error, _Car_41FDA0);
            Error = DetourAttach(&_Car_41FDF0, (PVOID)HookCar_41FDF0); printError(Error, _Car_41FDF0);
            Error = DetourAttach(&_Car_41FF00, (PVOID)HookCar_41FF00); printError(Error, _Car_41FF00);
            Error = DetourAttach(&_Car_420330, (PVOID)HookCar_420330); printError(Error, _Car_420330);
            Error = DetourAttach(&_Car_420450, (PVOID)HookCar_420450); printError(Error, _Car_420450);
            Error = DetourAttach(&_Car_4207F0, (PVOID)HookCar_4207F0); printError(Error, _Car_4207F0);
            Error = DetourAttach(&_Car_420840, (PVOID)HookCar_420840); printError(Error, _Car_420840);
            Error = DetourAttach(&_Car_4208F0, (PVOID)HookCar_4208F0); printError(Error, _Car_4208F0);
            Error = DetourAttach(&_Car_420950, (PVOID)HookCar_420950); printError(Error, _Car_420950);
            Error = DetourAttach(&_Car_4209F0, (PVOID)HookCar_4209F0); printError(Error, _Car_4209F0);
            Error = DetourAttach(&_Car_4213D0, (PVOID)HookCar_4213D0); printError(Error, _Car_4213D0);
            Error = DetourAttach(&_Car_421430, (PVOID)HookCar_421430); printError(Error, _Car_421430);
            Error = DetourAttach(&_Car_421460, (PVOID)HookCar_421460); printError(Error, _Car_421460);
            Error = DetourAttach(&_Car_421470, (PVOID)HookCar_421470); printError(Error, _Car_421470);
            Error = DetourAttach(&_Car_421490, (PVOID)HookCar_421490); printError(Error, _Car_421490);
            Error = DetourAttach(&_Car_4214B0, (PVOID)HookCar_4214B0); printError(Error, _Car_4214B0);
            Error = DetourAttach(&_Car_4214D0, (PVOID)HookCar_4214D0); printError(Error, _Car_4214D0);
            Error = DetourAttach(&_Car_4214E0, (PVOID)HookCar_4214E0); printError(Error, _Car_4214E0);
            Error = DetourAttach(&_Car_4214F0, (PVOID)HookCar_4214F0); printError(Error, _Car_4214F0);
            Error = DetourAttach(&_Car_421510, (PVOID)HookCar_421510); printError(Error, _Car_421510);
            Error = DetourAttach(&_Car_421540, (PVOID)HookCar_421540); printError(Error, _Car_421540);
            Error = DetourAttach(&_Car_421550, (PVOID)HookCar_421550); printError(Error, _Car_421550);
            Error = DetourAttach(&_Car_421560, (PVOID)HookCar_421560); printError(Error, _Car_421560);
            Error = DetourAttach(&_Car_421570, (PVOID)HookCar_421570); printError(Error, _Car_421570);
            Error = DetourAttach(&_Car_421590, (PVOID)HookCar_421590); printError(Error, _Car_421590);
            Error = DetourAttach(&_Car_4215B0, (PVOID)HookCar_4215B0); printError(Error, _Car_4215B0);
            Error = DetourAttach(&_Car_4215C0, (PVOID)HookCar_4215C0); printError(Error, _Car_4215C0);
            Error = DetourAttach(&_Car_4215F0, (PVOID)HookCar_4215F0); printError(Error, _Car_4215F0);
            Error = DetourAttach(&_Car_421610, (PVOID)HookCar_421610); printError(Error, _Car_421610);
            Error = DetourAttach(&_Car_421620, (PVOID)HookCar_421620); printError(Error, _Car_421620);
            Error = DetourAttach(&_Car_421640, (PVOID)HookCar_421640); printError(Error, _Car_421640);
            Error = DetourAttach(&_Car_421660, (PVOID)HookCar_421660); printError(Error, _Car_421660);
            Error = DetourAttach(&_Car_421680, (PVOID)HookCar_421680); printError(Error, _Car_421680);
            Error = DetourAttach(&_Car_4216A0, (PVOID)HookCar_4216A0); printError(Error, _Car_4216A0);
            Error = DetourAttach(&_Car_4216C0, (PVOID)HookCar_4216C0); printError(Error, _Car_4216C0);
            Error = DetourAttach(&_Car_4216E0, (PVOID)HookCar_4216E0); printError(Error, _Car_4216E0);
            Error = DetourAttach(&_Car_421700, (PVOID)HookCar_421700); printError(Error, _Car_421700);
            Error = DetourAttach(&_Car_421720, (PVOID)HookCar_421720); printError(Error, _Car_421720);
            Error = DetourAttach(&_Car_421740, (PVOID)HookCar_421740); printError(Error, _Car_421740);
            Error = DetourAttach(&_Car_421760, (PVOID)HookCar_421760); printError(Error, _Car_421760);
            Error = DetourAttach(&_Car_421780, (PVOID)HookCar_421780); printError(Error, _Car_421780);
            Error = DetourAttach(&_Car_421790, (PVOID)HookCar_421790); printError(Error, _Car_421790);
            Error = DetourAttach(&_Car_4217A0, (PVOID)HookCar_4217A0); printError(Error, _Car_4217A0);
            Error = DetourAttach(&_Car_4217B0, (PVOID)HookCar_4217B0); printError(Error, _Car_4217B0);
            Error = DetourAttach(&_Car_4217C0, (PVOID)HookCar_4217C0); printError(Error, _Car_4217C0);
            Error = DetourAttach(&_Car_4217D0, (PVOID)HookCar_4217D0); printError(Error, _Car_4217D0);
            Error = DetourAttach(&_Car_4217E0, (PVOID)HookCar_4217E0); printError(Error, _Car_4217E0);
            Error = DetourAttach(&_Car_4217F0, (PVOID)HookCar_4217F0); printError(Error, _Car_4217F0);
            Error = DetourAttach(&_Car_421810, (PVOID)HookCar_421810); printError(Error, _Car_421810);
            Error = DetourAttach(&_Car_421830, (PVOID)HookCar_421830); printError(Error, _Car_421830);
            Error = DetourAttach(&_Car_421870, (PVOID)HookCar_421870); printError(Error, _Car_421870);
            Error = DetourAttach(&_Car_421890, (PVOID)HookCar_421890); printError(Error, _Car_421890);
            Error = DetourAttach(&_Car_4218A0, (PVOID)HookCar_4218A0); printError(Error, _Car_4218A0);
            Error = DetourAttach(&_Car_4218B0, (PVOID)HookCar_4218B0); printError(Error, _Car_4218B0);
            Error = DetourAttach(&_Car_4218C0, (PVOID)HookCar_4218C0); printError(Error, _Car_4218C0);
            Error = DetourAttach(&_Car_4218D0, (PVOID)HookCar_4218D0); printError(Error, _Car_4218D0);
            Error = DetourAttach(&_Car_4218E0, (PVOID)HookCar_4218E0); printError(Error, _Car_4218E0);
            Error = DetourAttach(&_Car_4218F0, (PVOID)HookCar_4218F0); printError(Error, _Car_4218F0);
            Error = DetourAttach(&_Car_421900, (PVOID)HookCar_421900); printError(Error, _Car_421900);
            Error = DetourAttach(&_Car_421910, (PVOID)HookCar_421910); printError(Error, _Car_421910);
            Error = DetourAttach(&_Car_421950, (PVOID)HookCar_421950); printError(Error, _Car_421950);
            Error = DetourAttach(&_Car_421C40, (PVOID)HookCar_421C40); printError(Error, _Car_421C40);
            Error = DetourAttach(&_Car_421CF0, (PVOID)HookCar_421CF0); printError(Error, _Car_421CF0);
            Error = DetourAttach(&_Car_421D80, (PVOID)HookCar_421D80); printError(Error, _Car_421D80);
            Error = DetourAttach(&_Car_421D90, (PVOID)HookCar_421D90); printError(Error, _Car_421D90);
            Error = DetourAttach(&_Car_421DF0, (PVOID)HookCar_421DF0); printError(Error, _Car_421DF0);
            Error = DetourAttach(&_Car_421E70, (PVOID)HookCar_421E70); printError(Error, _Car_421E70);
            Error = DetourAttach(&_Car_421EC0, (PVOID)HookCar_421EC0); printError(Error, _Car_421EC0);
            Error = DetourAttach(&_Car_421F40, (PVOID)HookCar_421F40); printError(Error, _Car_421F40);
            Error = DetourAttach(&_Car_421F80, (PVOID)HookCar_421F80); printError(Error, _Car_421F80);
            Error = DetourAttach(&_Car_421FD0, (PVOID)HookCar_421FD0); printError(Error, _Car_421FD0);
            Error = DetourAttach(&_Car_4220A0, (PVOID)HookCar_4220A0); printError(Error, _Car_4220A0);
            Error = DetourAttach(&_Car_4221D0, (PVOID)HookCar_4221D0); printError(Error, _Car_4221D0);
            Error = DetourAttach(&_Car_422260, (PVOID)HookCar_422260); printError(Error, _Car_422260);
            Error = DetourAttach(&_Car_4222A0, (PVOID)HookCar_4222A0); printError(Error, _Car_4222A0);
            Error = DetourAttach(&_Car_4222D0, (PVOID)HookCar_4222D0); printError(Error, _Car_4222D0);
            Error = DetourAttach(&_Car_4222F0, (PVOID)HookCar_4222F0); printError(Error, _Car_4222F0);
            Error = DetourAttach(&_Car_422360, (PVOID)HookCar_422360); printError(Error, _Car_422360);
            Error = DetourAttach(&_Car_422500, (PVOID)HookCar_422500); printError(Error, _Car_422500);
            Error = DetourAttach(&_Car_422670, (PVOID)HookCar_422670); printError(Error, _Car_422670);
            Error = DetourAttach(&_Car_4226C0, (PVOID)HookCar_4226C0); printError(Error, _Car_4226C0);
            Error = DetourAttach(&_Car_422980, (PVOID)HookCar_422980); printError(Error, _Car_422980);
            Error = DetourAttach(&_Car_422A40, (PVOID)HookCar_422A40); printError(Error, _Car_422A40);
            Error = DetourAttach(&_Car_422AA0, (PVOID)HookCar_422AA0); printError(Error, _Car_422AA0);
            Error = DetourAttach(&_Car_422B70, (PVOID)HookCar_422B70); printError(Error, _Car_422B70);
            Error = DetourAttach(&_Car_422BD0, (PVOID)HookCar_422BD0); printError(Error, _Car_422BD0);
            Error = DetourAttach(&_Car_422CB0, (PVOID)HookCar_422CB0); printError(Error, _Car_422CB0);
            Error = DetourAttach(&_Car_422D20, (PVOID)HookCar_422D20); printError(Error, _Car_422D20);
            Error = DetourAttach(&_Car_422D80, (PVOID)HookCar_422D80); printError(Error, _Car_422D80);
            Error = DetourAttach(&_Car_422DE0, (PVOID)HookCar_422DE0); printError(Error, _Car_422DE0);
            Error = DetourAttach(&_Car_422E00, (PVOID)HookCar_422E00); printError(Error, _Car_422E00);
            Error = DetourAttach(&_Car_422F00, (PVOID)HookCar_422F00); printError(Error, _Car_422F00);
            Error = DetourAttach(&_Car_4230D0, (PVOID)HookCar_4230D0); printError(Error, _Car_4230D0);
            Error = DetourAttach(&_Car_423180, (PVOID)HookCar_423180); printError(Error, _Car_423180);
            Error = DetourAttach(&_Car_423290, (PVOID)HookCar_423290); printError(Error, _Car_423290);
            Error = DetourAttach(&_Car_423310, (PVOID)HookCar_423310); printError(Error, _Car_423310);
            Error = DetourAttach(&_Car_423480, (PVOID)HookCar_423480); printError(Error, _Car_423480);
            Error = DetourAttach(&_Car_4234A0, (PVOID)HookCar_4234A0); printError(Error, _Car_4234A0);
            Error = DetourAttach(&_Car_423510, (PVOID)HookCar_423510); printError(Error, _Car_423510);
            Error = DetourAttach(&_Car_423590, (PVOID)HookCar_423590); printError(Error, _Car_423590);
            Error = DetourAttach(&_Car_4235D0, (PVOID)HookCar_4235D0); printError(Error, _Car_4235D0);
            Error = DetourAttach(&_Car_423630, (PVOID)HookCar_423630); printError(Error, _Car_423630);
            Error = DetourAttach(&_Car_423720, (PVOID)HookCar_423720); printError(Error, _Car_423720);
            Error = DetourAttach(&_Car_4237B0, (PVOID)HookCar_4237B0); printError(Error, _Car_4237B0);
            Error = DetourAttach(&_Car_4237F0, (PVOID)HookCar_4237F0); printError(Error, _Car_4237F0);
            Error = DetourAttach(&_Car_423830, (PVOID)HookCar_423830); printError(Error, _Car_423830);
            Error = DetourAttach(&_Car_423850, (PVOID)HookCar_423850); printError(Error, _Car_423850);
            Error = DetourAttach(&_Car_423940, (PVOID)HookCar_423940); printError(Error, _Car_423940);
            Error = DetourAttach(&_Car_423A50, (PVOID)HookCar_423A50); printError(Error, _Car_423A50);
            Error = DetourAttach(&_Car_423A70, (PVOID)HookCar_423A70); printError(Error, _Car_423A70);
            Error = DetourAttach(&_Car_423AA0, (PVOID)HookCar_423AA0); printError(Error, _Car_423AA0);
            Error = DetourAttach(&_Car_423B30, (PVOID)HookCar_423B30); printError(Error, _Car_423B30);
            Error = DetourAttach(&_Car_423B50, (PVOID)HookCar_423B50); printError(Error, _Car_423B50);
            Error = DetourAttach(&_Car_423B80, (PVOID)HookCar_423B80); printError(Error, _Car_423B80);
            Error = DetourAttach(&_Car_423C30, (PVOID)HookCar_423C30); printError(Error, _Car_423C30);
            Error = DetourAttach(&_Car_424010, (PVOID)HookCar_424010); printError(Error, _Car_424010);
            Error = DetourAttach(&_Car_424030, (PVOID)HookCar_424030); printError(Error, _Car_424030);
            Error = DetourAttach(&_Car_424090, (PVOID)HookCar_424090); printError(Error, _Car_424090);
            Error = DetourAttach(&_Car_4241C0, (PVOID)HookCar_4241C0); printError(Error, _Car_4241C0);
            Error = DetourAttach(&_Car_424220, (PVOID)HookCar_424220); printError(Error, _Car_424220);
            Error = DetourAttach(&_Car_424280, (PVOID)HookCar_424280); printError(Error, _Car_424280);
            Error = DetourAttach(&_Car_4243C0, (PVOID)HookCar_4243C0); printError(Error, _Car_4243C0);
            Error = DetourAttach(&_Car_424400, (PVOID)HookCar_424400); printError(Error, _Car_424400);
            Error = DetourAttach(&_Car_4244A0, (PVOID)HookCar_4244A0); printError(Error, _Car_4244A0);
            Error = DetourAttach(&_Car_424630, (PVOID)HookCar_424630); printError(Error, _Car_424630);
            Error = DetourAttach(&_Car_424660, (PVOID)HookCar_424660); printError(Error, _Car_424660);
            Error = DetourAttach(&_Car_424680, (PVOID)HookCar_424680); printError(Error, _Car_424680);
            Error = DetourAttach(&_Car_4246A0, (PVOID)HookCar_4246A0); printError(Error, _Car_4246A0);
            Error = DetourAttach(&_Car_424700, (PVOID)HookCar_424700); printError(Error, _Car_424700);
            Error = DetourAttach(&_Car_424880, (PVOID)HookCar_424880); printError(Error, _Car_424880);
            Error = DetourAttach(&_Car_424960, (PVOID)HookCar_424960); printError(Error, _Car_424960);
            Error = DetourAttach(&_Car_424E30, (PVOID)HookCar_424E30); printError(Error, _Car_424E30);
            Error = DetourAttach(&_Car_424F80, (PVOID)HookCar_424F80); printError(Error, _Car_424F80);
            Error = DetourAttach(&_Car_425590, (PVOID)HookCar_425590); printError(Error, _Car_425590);
            Error = DetourAttach(&_Car_425650, (PVOID)HookCar_425650); printError(Error, _Car_425650);
            Error = DetourAttach(&_Car_425760, (PVOID)HookCar_425760); printError(Error, _Car_425760);
            Error = DetourAttach(&_Car_425770, (PVOID)HookCar_425770); printError(Error, _Car_425770);
            Error = DetourAttach(&_Car_425780, (PVOID)HookCar_425780); printError(Error, _Car_425780);
            Error = DetourAttach(&_Car_425790, (PVOID)HookCar_425790); printError(Error, _Car_425790);
            Error = DetourAttach(&_Car_4257B0, (PVOID)HookCar_4257B0); printError(Error, _Car_4257B0);
            Error = DetourAttach(&_Car_425A40, (PVOID)HookCar_425A40); printError(Error, _Car_425A40);
            Error = DetourAttach(&_Car_425B60, (PVOID)HookCar_425B60); printError(Error, _Car_425B60);
            Error = DetourAttach(&_Car_425CA0, (PVOID)HookCar_425CA0); printError(Error, _Car_425CA0);
            Error = DetourAttach(&_Car_425D60, (PVOID)HookCar_425D60); printError(Error, _Car_425D60);
            Error = DetourAttach(&_Car_425D90, (PVOID)HookCar_425D90); printError(Error, _Car_425D90);
            Error = DetourAttach(&_Car_425DD0, (PVOID)HookCar_425DD0); printError(Error, _Car_425DD0);
            Error = DetourAttach(&_Car_425DF0, (PVOID)HookCar_425DF0); printError(Error, _Car_425DF0);
            Error = DetourAttach(&_Car_425E30, (PVOID)HookCar_425E30); printError(Error, _Car_425E30);
            Error = DetourAttach(&_Car_425E60, (PVOID)HookCar_425E60); printError(Error, _Car_425E60);
            Error = DetourAttach(&_Car_425ED0, (PVOID)HookCar_425ED0); printError(Error, _Car_425ED0);
            Error = DetourAttach(&_Car_425F20, (PVOID)HookCar_425F20); printError(Error, _Car_425F20);
            Error = DetourAttach(&_Car_425FD0, (PVOID)HookCar_425FD0); printError(Error, _Car_425FD0);
            Error = DetourAttach(&_Car_426030, (PVOID)HookCar_426030); printError(Error, _Car_426030);
            Error = DetourAttach(&_Car_4260C0, (PVOID)HookCar_4260C0); printError(Error, _Car_4260C0);
            Error = DetourAttach(&_Car_426120, (PVOID)HookCar_426120); printError(Error, _Car_426120);
            Error = DetourAttach(&_Car_426140, (PVOID)HookCar_426140); printError(Error, _Car_426140);
            Error = DetourAttach(&_Car_426220, (PVOID)HookCar_426220); printError(Error, _Car_426220);
            Error = DetourAttach(&_Car_4262B0, (PVOID)HookCar_4262B0); printError(Error, _Car_4262B0);
            Error = DetourAttach(&_Car_4262E0, (PVOID)HookCar_4262E0); printError(Error, _Car_4262E0);
            Error = DetourAttach(&_Car_426580, (PVOID)HookCar_426580); printError(Error, _Car_426580);
            Error = DetourAttach(&_Car_4266F0, (PVOID)HookCar_4266F0); printError(Error, _Car_4266F0);
            Error = DetourAttach(&_Car_426730, (PVOID)HookCar_426730); printError(Error, _Car_426730);
            Error = DetourAttach(&_Car_4267B0, (PVOID)HookCar_4267B0); printError(Error, _Car_4267B0);
            Error = DetourAttach(&_Car_426E00, (PVOID)HookCar_426E00); printError(Error, _Car_426E00);
            Error = DetourAttach(&_Car_426EE0, (PVOID)HookCar_426EE0); printError(Error, _Car_426EE0);
            Error = DetourAttach(&_Car_426F00, (PVOID)HookCar_426F00); printError(Error, _Car_426F00);
            Error = DetourAttach(&_Car_426F40, (PVOID)HookCar_426F40); printError(Error, _Car_426F40);
            Error = DetourAttach(&_Car_426F60, (PVOID)HookCar_426F60); printError(Error, _Car_426F60);
            Error = DetourAttach(&_Car_426FA0, (PVOID)HookCar_426FA0); printError(Error, _Car_426FA0);
            Error = DetourAttach(&_Car_427180, (PVOID)HookCar_427180); printError(Error, _Car_427180);
            Error = DetourAttach(&_Car_427290, (PVOID)HookCar_427290); printError(Error, _Car_427290);
            Error = DetourAttach(&_Car_427450, (PVOID)HookCar_427450); printError(Error, _Car_427450);
            Error = DetourAttach(&_Car_4274C0, (PVOID)HookCar_4274C0); printError(Error, _Car_4274C0);
            Error = DetourAttach(&_Car_4279E0, (PVOID)HookCar_4279E0); printError(Error, _Car_4279E0);
            Error = DetourAttach(&_Car_427A20, (PVOID)HookCar_427A20); printError(Error, _Car_427A20);
            Error = DetourAttach(&_Car_427B20, (PVOID)HookCar_427B20); printError(Error, _Car_427B20);
            Error = DetourAttach(&_Car_427B40, (PVOID)HookCar_427B40); printError(Error, _Car_427B40);
            Error = DetourAttach(&_Car_427BD0, (PVOID)HookCar_427BD0); printError(Error, _Car_427BD0);
            Error = DetourAttach(&_Car_427CA0, (PVOID)HookCar_427CA0); printError(Error, _Car_427CA0);
            Error = DetourAttach(&_Car_427D10, (PVOID)HookCar_427D10); printError(Error, _Car_427D10);
            Error = DetourAttach(&_Car_4292F0, (PVOID)HookCar_4292F0); printError(Error, _Car_4292F0);
            Error = DetourAttach(&_Car_429370, (PVOID)HookCar_429370); printError(Error, _Car_429370);
            Error = DetourAttach(&_Car_4293D0, (PVOID)HookCar_4293D0); printError(Error, _Car_4293D0);
            Error = DetourAttach(&_Car_429660, (PVOID)HookCar_429660); printError(Error, _Car_429660);
            Error = DetourAttach(&_Car_429800, (PVOID)HookCar_429800); printError(Error, _Car_429800);
            Error = DetourAttach(&_Car_429810, (PVOID)HookCar_429810); printError(Error, _Car_429810);
            Error = DetourAttach(&_Car_4298B0, (PVOID)HookCar_4298B0); printError(Error, _Car_4298B0);
            Error = DetourAttach(&_Car_429E50, (PVOID)HookCar_429E50); printError(Error, _Car_429E50);
            Error = DetourAttach(&_Car_429FC0, (PVOID)HookCar_429FC0); printError(Error, _Car_429FC0);
            Error = DetourAttach(&_Car_429FF0, (PVOID)HookCar_429FF0); printError(Error, _Car_429FF0);
            Error = DetourAttach(&_Car_42A360, (PVOID)HookCar_42A360); printError(Error, _Car_42A360);
            Error = DetourAttach(&_Car_42A510, (PVOID)HookCar_42A510); printError(Error, _Car_42A510);
            Error = DetourAttach(&_Car_42A5B0, (PVOID)HookCar_42A5B0); printError(Error, _Car_42A5B0);
            Error = DetourAttach(&_Car_42AC60, (PVOID)HookCar_42AC60); printError(Error, _Car_42AC60);
            Error = DetourAttach(&_Car_42C030, (PVOID)HookCar_42C030); printError(Error, _Car_42C030);
            Error = DetourAttach(&_Car_42C8B0, (PVOID)HookCar_42C8B0); printError(Error, _Car_42C8B0);
            Error = DetourAttach(&_Car_42D390, (PVOID)HookCar_42D390); printError(Error, _Car_42D390);
            Error = DetourAttach(&_Car_42D820, (PVOID)HookCar_42D820); printError(Error, _Car_42D820);
            Error = DetourAttach(&_Car_42FB80, (PVOID)HookCar_42FB80); printError(Error, _Car_42FB80);
            Error = DetourAttach(&_Car_430090, (PVOID)HookCar_430090); printError(Error, _Car_430090);
            Error = DetourAttach(&_Car_430320, (PVOID)HookCar_430320); printError(Error, _Car_430320);
            Error = DetourAttach(&_Car_430CC0, (PVOID)HookCar_430CC0); printError(Error, _Car_430CC0);
            Error = DetourAttach(&_Car_431770, (PVOID)HookCar_431770); printError(Error, _Car_431770);
            Error = DetourAttach(&_Car_431C10, (PVOID)HookCar_431C10); printError(Error, _Car_431C10);
            Error = DetourAttach(&_Car_432370, (PVOID)HookCar_432370); printError(Error, _Car_432370);
            Error = DetourAttach(&_Car_4327A0, (PVOID)HookCar_4327A0); printError(Error, _Car_4327A0);
            Error = DetourAttach(&_Car_447EA0, (PVOID)HookCar_447EA0); printError(Error, _Car_447EA0);
            Error = DetourAttach(&_Car_447EB0, (PVOID)HookCar_447EB0); printError(Error, _Car_447EB0);
            Error = DetourAttach(&_Car_447EC0, (PVOID)HookCar_447EC0); printError(Error, _Car_447EC0);
            Error = DetourAttach(&_Car_447ED0, (PVOID)HookCar_447ED0); printError(Error, _Car_447ED0);
            Error = DetourAttach(&_Car_447F00, (PVOID)HookCar_447F00); printError(Error, _Car_447F00);
            Error = DetourAttach(&_Car_44A3E0, (PVOID)HookCar_44A3E0); printError(Error, _Car_44A3E0);
            Error = DetourAttach(&_Car_450CC0, (PVOID)HookCar_450CC0); printError(Error, _Car_450CC0);
            Error = DetourAttach(&_Car_475AA0, (PVOID)HookCar_475AA0); printError(Error, _Car_475AA0);
            Error = DetourAttach(&_Car_475C10, (PVOID)HookCar_475C10); printError(Error, _Car_475C10);
            Error = DetourAttach(&_Car_475C30, (PVOID)HookCar_475C30); printError(Error, _Car_475C30);
            Error = DetourAttach(&_Car_475C40, (PVOID)HookCar_475C40); printError(Error, _Car_475C40);
            Error = DetourAttach(&_Car_475C80, (PVOID)HookCar_475C80); printError(Error, _Car_475C80);
            Error = DetourAttach(&_Car_4761F0, (PVOID)HookCar_4761F0); printError(Error, _Car_4761F0);
            Error = DetourAttach(&_Car_476230, (PVOID)HookCar_476230); printError(Error, _Car_476230);
            Error = DetourAttach(&_Car_476270, (PVOID)HookCar_476270); printError(Error, _Car_476270);
            Error = DetourAttach(&_Car_4762D0, (PVOID)HookCar_4762D0); printError(Error, _Car_4762D0);
            Error = DetourAttach(&_Car_4762E0, (PVOID)HookCar_4762E0); printError(Error, _Car_4762E0);
            Error = DetourAttach(&_Car_4762F0, (PVOID)HookCar_4762F0); printError(Error, _Car_4762F0);
            Error = DetourAttach(&_Car_476300, (PVOID)HookCar_476300); printError(Error, _Car_476300);
            Error = DetourAttach(&_Car_476310, (PVOID)HookCar_476310); printError(Error, _Car_476310);
            Error = DetourAttach(&_Car_476350, (PVOID)HookCar_476350); printError(Error, _Car_476350);
            Error = DetourAttach(&_Car_482D90, (PVOID)HookCar_482D90); printError(Error, _Car_482D90);
            Error = DetourAttach(&_Car_4895E0, (PVOID)HookCar_4895E0); printError(Error, _Car_4895E0);
            Error = DetourAttach(&_Car_48A930, (PVOID)HookCar_48A930); printError(Error, _Car_48A930);
            Error = DetourAttach(&_Car_49EFC0, (PVOID)HookCar_49EFC0); printError(Error, _Car_49EFC0);
            Error = DetourAttach(&_Car_49EFD0, (PVOID)HookCar_49EFD0); printError(Error, _Car_49EFD0);
            Error = DetourAttach(&_Car_49EFE0, (PVOID)HookCar_49EFE0); printError(Error, _Car_49EFE0);
            Error = DetourAttach(&_Car_4A9AD0, (PVOID)HookCar_4A9AD0); printError(Error, _Car_4A9AD0);
            Error = DetourAttach(&_Car_4AFB30, (PVOID)HookCar_4AFB30); printError(Error, _Car_4AFB30);
            Error = DetourAttach(&_Car_4B9A30, (PVOID)HookCar_4B9A30); printError(Error, _Car_4B9A30);
            Error = DetourAttach(&_Car_4BE7A0, (PVOID)HookCar_4BE7A0); printError(Error, _Car_4BE7A0);
            Error = DetourAttach(&_Car_4BE980, (PVOID)HookCar_4BE980); printError(Error, _Car_4BE980);
            Error = DetourAttach(&_Car_4BE9C0, (PVOID)HookCar_4BE9C0); printError(Error, _Car_4BE9C0);
            Error = DetourAttach(&_Car_4BE9F0, (PVOID)HookCar_4BE9F0); printError(Error, _Car_4BE9F0);
            Error = DetourAttach(&_Car_4BEA20, (PVOID)HookCar_4BEA20); printError(Error, _Car_4BEA20);
            Error = DetourAttach(&_Car_4BEAC0, (PVOID)HookCar_4BEAC0); printError(Error, _Car_4BEAC0);
            Error = DetourAttach(&_Car_4BEB30, (PVOID)HookCar_4BEB30); printError(Error, _Car_4BEB30);
            Error = DetourAttach(&_Car_4BEB70, (PVOID)HookCar_4BEB70); printError(Error, _Car_4BEB70);
            Error = DetourAttach(&_Car_4BEBC0, (PVOID)HookCar_4BEBC0); printError(Error, _Car_4BEBC0);
            Error = DetourAttach(&_Car_4BED90, (PVOID)HookCar_4BED90); printError(Error, _Car_4BED90);
            Error = DetourAttach(&_Car_4BEE10, (PVOID)HookCar_4BEE10); printError(Error, _Car_4BEE10);
            Error = DetourAttach(&_Car_4BEF70, (PVOID)HookCar_4BEF70); printError(Error, _Car_4BEF70);
            Error = DetourAttach(&_Car_4BF000, (PVOID)HookCar_4BF000); printError(Error, _Car_4BF000);
            Error = DetourAttach(&_Car_4BF070, (PVOID)HookCar_4BF070); printError(Error, _Car_4BF070);
            Error = DetourAttach(&_Car_4BF100, (PVOID)HookCar_4BF100); printError(Error, _Car_4BF100);
            Error = DetourAttach(&_Car_4BF180, (PVOID)HookCar_4BF180); printError(Error, _Car_4BF180);
        } else {
            extern void VideoTrace(const char* fmt, ...);
            VideoTrace("[dllLoad] GTA2_NOCARTRACE set - Car::* observer detours skipped");
        }
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
      ProbeThisClose();
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
