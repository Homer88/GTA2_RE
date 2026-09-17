#include <Windows.h>
#include <stdio.h>

#include "cGame.h"
#include "cHookTrace.h"
#include "cInspector.h"
#include "DebugLogFile.h"

// gGame @0x005EB4FC is a POINTER CELL: the Game instance itself is malloc'ed
// by InitFrontedLessGame (operator_new(0x40) + Game::Game).
Game* gGame = (Game*)0x005EB4FC; // legacy alias: the CELL address (kept for Inspector)

Game* GetGamePtr(void)
{
    return *(Game**)0x005EB4FC;
}

// Trampolines rewritten by DetourAttach in dllmain.cpp to the original retail code:
extern LPVOID _SetGameState;         // Game::sub_45A480 @0x0045A480  (State/isDead setter)
extern LPVOID _GameCtor;             // Game::Game      @0x0045C4D0  (constructor)
extern LPVOID _InitFrontedLessGame;  // InitFrontedLessGame @0x00461DE0
extern LPVOID _Resurs;               // Game::Resurs      @0x0045B469 (loads Level resources)
extern LPVOID _sub_45B5F0;           // Game::sub_45B5F0  @0x0045B5F0 (inits world: gangs, missions, players)
extern LPVOID _Sub465390;            // MapRelatedStruct::sub_465390 @0x00465390 (creates gangs per zone)
extern LPVOID _Sub481890;            // MissionManager::sub_481890    @0x00481890 (loads missions)
extern LPVOID _StartGames;           // Player::StartGames @0x004A6DA0 (starts player in world)
extern LPVOID _UpdateWrapper;        // Hud::UpdateWrapper @0x004CAC30 (HUD create/refresh)

static const char* GameStructTag(Game* g)
{
    return GetGlobalStructName((unsigned long)(ULONG_PTR)g);
}

// One-shot diagnostic: scan a memory window for any 4-byte cell equal to a given
// target pointer (the heap Game instance). Finds the TRUE gGame cell address at runtime
// (0x005EB4FC stayed NULL even after InitFrontedLessGame ran) and detects off-by-N moves.
static ULONG s_createdGamePtr = 0; // heap Game instance set by the ctor hook

static void ScanForPtrCell(ULONG target, ULONG fromAddr, ULONG toAddr, const char* what)
{
    if (!target)
        return;
    char line[96];
    int hits = 0;
    ULONG addr = fromAddr;
    __try {
        while (addr < toAddr) {
            MEMORY_BASIC_INFORMATION mbi;
            if (!VirtualQuery((LPCVOID)addr, &mbi, sizeof(mbi)))
                break;
            ULONG regionEnd = (ULONG)((ULONG_PTR)mbi.BaseAddress + mbi.RegionSize);
            if (regionEnd > toAddr)
                regionEnd = toAddr;
            BOOL readable = (mbi.State == MEM_COMMIT) &&
                !(mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)) &&
                mbi.Protect != 0;
            if (readable) {
                for (; addr < regionEnd; addr += 4) {
                    if (*(ULONG*)addr == target) {
                        _snprintf(line, sizeof(line), "%s: cell @0x%08X == 0x%08X", what, addr, target);
                        writeFileLog((char*)"game.txt", line, (char*)"Scan", (char*)"");
                        if (++hits >= 24)
                            break;
                    }
                }
            }
            addr = regionEnd;
        }
        _snprintf(line, sizeof(line), "%s done, hits=%d (searched 0x%08X-0x%08X)", what, hits, fromAddr, toAddr);
        writeFileLog((char*)"game.txt", line, (char*)"Scan", (char*)"");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        _snprintf(line, sizeof(line), "%s aborted at exception, hits=%d @addr=0x%08X", what, hits, addr);
        writeFileLog((char*)"game.txt", line, (char*)"Scan", (char*)"");
    }
}

// At Game ctor time the gGame assignment has not happened yet: only remember the heap ptr.
static void ScanForGamePtrCell(Game* g)
{
    s_createdGamePtr = (ULONG)(ULONG_PTR)g;
    char line[96];
    _snprintf(line, sizeof(line), "s_createdGamePtr = 0x%08X (scan will run later, after gGame=pGame_2)", s_createdGamePtr);
    writeFileLog((char*)"game.txt", line, (char*)"Scan", (char*)"");
}

// Run after the gGame assignment landed (Resurs/StartGames entry): locate the true cell.
static void ScanPostAssignment(int already, const char* where)
{
    char b[256];
    int i;
    ULONG fence[8] = { 0x005EB4E0, 0x005EB4E4, 0x005EB4E8, 0x005EB4EC,
                       0x005EB4F8, 0x005EB4FC, 0x005EB500, 0x005EB504 };
    int n = 0;
    __try {
        n = _snprintf(b, sizeof(b), "== %s-entry: gGameCell@0x005EB4FC=0x%08X (created=0x%08X) fence:",
                      where, *(DWORD*)0x005EB4FC, s_createdGamePtr);
        for (i = 0; i < 8; i++)
            n += _snprintf(b + n, sizeof(b) - n, " %08X", *(DWORD*)fence[i]);
        if (already)
            _snprintf(b + n, sizeof(b) - n, " [%s ALREADY]", where);
        writeFileLog((char*)"game.txt", b, (char*)"Scan", (char*)"");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        _snprintf(b, sizeof(b), "== %s-entry fence read aborted @fence[%d]", where, i);
        writeFileLog((char*)"game.txt", b, (char*)"Scan", (char*)"");
    }
    ScanForPtrCell(s_createdGamePtr, 0x00426000UL, 0x00680000UL, where);
}

// Retail Game::sub_45A480 @0x0045A480 is __thiscall(Game* this, int isDead, int state, char bonus):
// sets this->isDead = isDead, this->State = state (and MapGm bonus) when
// isDead == -1 || isDead > a2. Game::SetState @0x0045A4B0 calls it with bonus = 0.
int __fastcall HookSetState(Game* g, void* _EDX, int isDeadNew, int state, char bonus)
{
    char buf[192];
    (void)_EDX;
    TraceCall("Game::sub_45A480 @0x0045A480", TRACE_CALLER_ADDR);
    _snprintf(buf, sizeof(buf),
        "state %d->%d isDead %d->%d bonus=0x%02X  %s@0x%08X",
        g->State, state, g->isDead, isDeadNew, (unsigned char)bonus,
        GameStructTag(g), (unsigned long)(ULONG_PTR)g);
    writeFileLog((char*)"game.txt", buf, (char*)"SetState", (char*)"");
    return ((int (__thiscall*)(Game*, int, int, char))_SetGameState)(g, isDeadNew, state, bonus);
}

// Retail Game::Game @0x0045C4D0 is __thiscall(Game* this, int index, char data) and
// returns `this` in EAX; the CALLER (InitFrontedLessGame) stores that EAX into gGame
// right after the call. Our hook MUST return the ctor result in EAX, otherwise gGame
// gets garbage (usually 0 -> crash at gGame->PlayerMain). Log then `return r;`.
Game* __fastcall HookGameCtor(Game* g, void* _EDX, int index, char data)
{
    char buf[192];
    (void)_EDX;
    TraceCall("Game::Game @0x0045C4D0", TRACE_CALLER_ADDR);
    Game* r = ((Game* (__thiscall*)(Game*, int, char))_GameCtor)(g, index, data);
    DWORD cell = *(DWORD*)0x005EB4FC;
    _snprintf(buf, sizeof(buf),
        "Game ctor done: @0x%08X %s, index=%d data=%d State=%d isDead=%d MaxIdx=%d PlayerInFocus=%d gGameCell=0x%08X",
        (unsigned long)(ULONG_PTR)g, GameStructTag(g), index, (int)data,
        g->State, g->isDead, (int)g->NumberPlayer, (int)g->PlayerInFocus, cell);
    writeFileLog((char*)"game.txt", buf, (char*)"GameCtor", (char*)"");
    ScanForGamePtrCell(g);
    return r;
}

// Dump raw code bytes of a window (used to decode the gGame write instruction:
// "mov [imm32], reg" = 89 05 <adr> right after the ctor call at InitFrontedLessGame+0x221).
static void LogCodeBytes(ULONG from, ULONG len, const char* label)
{
    char b[384];
    int off = 0;
    ULONG a = from;
    __try {
        for (a = from; a < from + len; a++) {
            if (off > 360)
                break;
            off += _snprintf(b + off, sizeof(b) - off, "%02X ", *(unsigned char*)a);
        }
        writeFileLog((char*)"game.txt", b, (char*)label, (char*)"");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        _snprintf(b, sizeof(b), "%s: <unreadable @0x%08X>", label, a);
        writeFileLog((char*)"game.txt", b, (char*)label, (char*)"");
    }
}

// Retail InitFrontedLessGame @0x00461DE0 is __stdcall(void): boot/level-init entry that
// allocates the Game instance on the heap and stores the pointer into the gGame global.
void __stdcall HookInitFrontedLessGame(void)
{
    char buf[128];
    LogCodeBytes(0x00461FE0UL, 0x50, "CodeInit1"); // region around the single-player ctor call @0x462001
    ((void (__stdcall*)(void))_InitFrontedLessGame)();
    _snprintf(buf, sizeof(buf),
        "InitFrontedLessGame done: gGameCell@0x005EB4FC=0x%08X",
        *(DWORD*)0x005EB4FC);
    writeFileLog((char*)"game.txt", buf, (char*)"InitGame", (char*)"");
}

// --- Init-chain crash isolation (__thiscall = __fastcall(this, void* _EDX)) ----
void __fastcall HookResurs(Game* g, void* _EDX)
{
    char b[96];
    _snprintf(b, sizeof(b), "  Resurs enter this=0x%08X gGameCell=0x%08X", (unsigned long)(ULONG_PTR)g, *(DWORD*)0x005EB4FC);
    writeFileLog((char*)"game.txt", b, (char*)"InitGame", (char*)"");
    ScanPostAssignment(0, "Resurs");
    ((void (__fastcall*)(Game*, void*))_Resurs)(g, _EDX);
}

void __fastcall Hook_sub_45B5F0(Game* g, void* _EDX)
{
    char b[96];
    _snprintf(b, sizeof(b), "  sub_45B5F0 enter this=0x%08X gGameCell=0x%08X", (unsigned long)(ULONG_PTR)g, *(DWORD*)0x005EB4FC);
    writeFileLog((char*)"game.txt", b, (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(Game*, void*))_sub_45B5F0)(g, _EDX);
    writeFileLog((char*)"game.txt", (char*)"  sub_45B5F0 EXIT OK", (char*)"InitGame", (char*)"");
}

void __fastcall HookSub465390(void* thisp, void* _EDX)
{
    writeFileLog((char*)"game.txt", (char*)"  sub_465390 (gangs/zone) enter", (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(void*, void*))_Sub465390)(thisp, _EDX);
    writeFileLog((char*)"game.txt", (char*)"  sub_465390 EXIT OK", (char*)"InitGame", (char*)"");
}

void __fastcall HookSub481890(void* thisp, void* _EDX)
{
    writeFileLog((char*)"game.txt", (char*)"  sub_481890 (missions) enter", (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(void*, void*))_Sub481890)(thisp, _EDX);
    writeFileLog((char*)"game.txt", (char*)"  sub_481890 EXIT OK", (char*)"InitGame", (char*)"");
}

void __fastcall HookStartGames(void* thisp, void* _EDX)
{
    char b[96];
    _snprintf(b, sizeof(b), "  Player::StartGames enter this=0x%08X gGameCell=0x%08X", (unsigned long)(ULONG_PTR)thisp, *(DWORD*)0x005EB4FC);
    writeFileLog((char*)"game.txt", b, (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(void*, void*))_StartGames)(thisp, _EDX);
}

void __fastcall HookUpdateWrapper(void* thisp, void* _EDX)
{
    writeFileLog((char*)"game.txt", (char*)"  Hud::UpdateWrapper enter", (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(void*, void*))_UpdateWrapper)(thisp, _EDX);
}
