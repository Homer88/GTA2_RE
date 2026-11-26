#include "cPed.h"
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
LPVOID _SpawnMapObjects = (LPVOID)0x0046A4D0; // MapRelatedStruct::SpawnMapObjects
LPVOID _ObjectSpawnObject = (LPVOID)0x004852E0; // Object::SpawnObject(type,x,y,z,rot)
LPVOID _LoadMOBJ = (LPVOID)0x00464590;
LPVOID _LoadLGHT = (LPVOID)0x004645F0;
LPVOID _LoadANIM = (LPVOID)0x00464670;
LPVOID _RenderBlockLid = (LPVOID)0x0046DFE0;


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

int __fastcall HookLoadMOBJ(void* thisp, void* _EDX, unsigned int dwBytes)
{
    TraceCall("MapRelatedStruct::LoadMOBJ @0x00464590", TRACE_CALLER_ADDR);
    char b[128];
    _snprintf(b, sizeof(b), "LoadMOBJ size=%u this=0x%08X", dwBytes, (unsigned long)(ULONG_PTR)thisp);
    writeFileLog((char*)"mapobj.txt", b, (char*)"LoadMOBJ", (char*)"");
    int r = ((int (__fastcall*)(void*, void*, unsigned int))_LoadMOBJ)(thisp, _EDX, dwBytes);
    _snprintf(b, sizeof(b), "LoadMOBJ ret=%d", r);
    writeFileLog((char*)"mapobj.txt", b, (char*)"LoadMOBJ", (char*)"");
    return r;
}

int __fastcall HookLoadLGHT(void* thisp, void* _EDX, unsigned int dwBytes)
{
    TraceCall("MapRelatedStruct::LoadLGHT @0x004645F0", TRACE_CALLER_ADDR);
    char b[128];
    _snprintf(b, sizeof(b), "LoadLGHT size=%u this=0x%08X", dwBytes, (unsigned long)(ULONG_PTR)thisp);
    writeFileLog((char*)"mapobj.txt", b, (char*)"LoadLGHT", (char*)"");
    int r = ((int (__fastcall*)(void*, void*, unsigned int))_LoadLGHT)(thisp, _EDX, dwBytes);
    _snprintf(b, sizeof(b), "LoadLGHT ret=%d", r);
    writeFileLog((char*)"mapobj.txt", b, (char*)"LoadLGHT", (char*)"");
    return r;
}

int __fastcall HookLoadANIM(void* thisp, void* _EDX, void* dwBytes)
{
    TraceCall("MapRelatedStruct::LoadANIM @0x00464670", TRACE_CALLER_ADDR);
    char b[128];
    _snprintf(b, sizeof(b), "LoadANIM arg=0x%08X this=0x%08X", (unsigned long)(ULONG_PTR)dwBytes, (unsigned long)(ULONG_PTR)thisp);
    writeFileLog((char*)"mapobj.txt", b, (char*)"LoadANIM", (char*)"");
    int r = ((int (__fastcall*)(void*, void*, void*))_LoadANIM)(thisp, _EDX, dwBytes);
    _snprintf(b, sizeof(b), "LoadANIM ret=%d", r);
    writeFileLog((char*)"mapobj.txt", b, (char*)"LoadANIM", (char*)"");
    return r;
}

void __fastcall HookSpawnMapObjects(void* thisp, void* _EDX)
{
    TraceCall("MapRelatedStruct::SpawnMapObjects @0x0046A4D0", TRACE_CALLER_ADDR);
    char b[256];
    __try {
        unsigned char* p = (unsigned char*)thisp;
        DWORD buf = *(DWORD*)(p + 0x338);
        DWORD unk344 = *(DWORD*)(p + 0x344);
        _snprintf(b, sizeof(b), "SpawnMapObjects enter this=0x%08X mobjBuf=0x%08X f344=%u caller=0x%08X", (unsigned long)(ULONG_PTR)thisp, buf, unk344, (unsigned long)TRACE_CALLER_ADDR);
        if (buf && unk344) {
            unsigned char* rec = (unsigned char*)buf;
            unsigned n = unk344 < 64 ? unk344 : 64;
            for (unsigned i = 0; i < n; ++i) {
                unsigned char* r = rec + i * 6;
                short wx = *(short*)(r + 0);
                short wy = *(short*)(r + 2);
                unsigned rotB = r[4];
                unsigned typeB = r[5];
                char rb[192];
                _snprintf(rb, sizeof(rb), "MOBJ_REC i=%u rawX=%d rawY=%d rotB=%u type=%u bytes=%02X %02X %02X %02X %02X %02X", i, (int)wx, (int)wy, rotB, typeB, r[0],r[1],r[2],r[3],r[4],r[5]);
                writeFileLog((char*)"mapobj.txt", rb, (char*)"MOBJ_REC", (char*)"");
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        _snprintf(b, sizeof(b), "SpawnMapObjects enter this=0x%08X caller=0x%08X", (unsigned long)(ULONG_PTR)thisp, (unsigned long)TRACE_CALLER_ADDR);
    }
    writeFileLog((char*)"mapobj.txt", b, (char*)"SpawnMapObjects", (char*)"");
    ((void (__fastcall*)(void*, void*))_SpawnMapObjects)(thisp, _EDX);
    writeFileLog((char*)"mapobj.txt", (char*)"SpawnMapObjects EXIT OK", (char*)"SpawnMapObjects", (char*)"");
}


static volatile LONG gTileTraceLidN = 0;
static volatile LONG gTileTraceBlockN = 0;

void __fastcall HookRenderBlockLid(void* thisp, void* _EDX)
{
    LONG n = InterlockedIncrement(&gTileTraceLidN) - 1;
    if (n < 400) {
        __try {
            unsigned short lid = *(unsigned short*)0x006633BC;
            unsigned char b5930d0 = *(unsigned char*)0x005930D0;
            unsigned short wA4 = *(unsigned short*)0x006633A4;
            unsigned short wB0 = *(unsigned short*)0x006633B0;
            unsigned short wC0 = *(unsigned short*)0x006633C0;
            unsigned short wC4 = *(unsigned short*)0x006633C4;
            unsigned char* blk  = *(unsigned char**)0x00663298;
            unsigned char slope = blk ? blk[11] : 0;
            unsigned char arrows= blk ? blk[10] : 0;
            char b[384];
            _snprintf(b, sizeof(b), "lid=0x%04X virt=%u rot=%u flat=%u b5930D0=%d A4=0x%04X B0=0x%04X C0=0x%04X C4=0x%04X slope=0x%02X arr=0x%02X blk=0x%08X caller=0x%08X",
                lid, (unsigned)(lid & 1023u), (unsigned)((lid>>13)&7u), (unsigned)((lid>>12)&1u), (int)(signed char)b5930d0,
                wA4,wB0,wC0,wC4,slope,arrows,(unsigned long)(ULONG_PTR)blk,(unsigned long)TRACE_CALLER_ADDR);
            writeFileLog((char*)"tile_trace.txt", b, (char*)"RenderBlockLid", (char*)"");
        } __except (EXCEPTION_EXECUTE_HANDLER) {}
    }
    ((void (__fastcall*)(void*, void*))_RenderBlockLid)(thisp, _EDX);
}

static void logTileCtx(const char* tag, void* thisp) {
    __try {
        unsigned short wA4 = *(unsigned short*)0x006633A4;
        unsigned short wB0 = *(unsigned short*)0x006633B0;
        unsigned short wBC = *(unsigned short*)0x006633BC;
        unsigned short wC0 = *(unsigned short*)0x006633C0;
        unsigned short wC4 = *(unsigned short*)0x006633C4;
        unsigned char* blk  = *(unsigned char**)0x00663298;
        unsigned char slope = blk ? blk[11] : 0;
        unsigned char arrows= blk ? blk[10] : 0;
        char b[384];
        _snprintf(b, sizeof(b), "A4=0x%04X B0=0x%04X BC=0x%04X C0=0x%04X C4=0x%04X slope=0x%02X arr=0x%02X blk=0x%08X this=0x%08X caller=0x%08X",
            wA4,wB0,wBC,wC0,wC4,slope,arrows,(unsigned long)(ULONG_PTR)blk,(unsigned long)(ULONG_PTR)thisp,(unsigned long)TRACE_CALLER_ADDR);
        writeFileLog((char*)"tile_trace.txt", b, (char*)tag, (char*)"");
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

int __fastcall HookObjectSpawnObject(void* thisp, void* _EDX, int type, int x, int y, int z, int rot)
{
    TraceCall("Object::SpawnObject @0x004852E0", TRACE_CALLER_ADDR);
    char b[256];
    _snprintf(b, sizeof(b), "type=%d x=%d y=%d z=%d rot=%d rot16=%u (0x%04X) rot32=0x%08X this=0x%08X caller=0x%08X", type, x, y, z, rot, (unsigned)((unsigned short)rot), (unsigned)((unsigned short)rot), (unsigned)rot, (unsigned long)(ULONG_PTR)thisp, (unsigned long)TRACE_CALLER_ADDR);
    writeFileLog((char*)"mapobj.txt", b, (char*)"ObjectSpawn", (char*)"");
    int r = ((int (__fastcall*)(void*, void*, int, int, int, int, int))_ObjectSpawnObject)(thisp, _EDX, type, x, y, z, rot);
    char b2[128];
    _snprintf(b2, sizeof(b2), "ret=0x%08X type=%d", r, type);
    writeFileLog((char*)"mapobj.txt", b2, (char*)"ObjectSpawnRet", (char*)"");
    return r;
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
    char b[256];
    _snprintf(b, sizeof(b), "  Player::StartGames enter this=0x%08X gGameCell=0x%08X", (unsigned long)(ULONG_PTR)thisp, *(DWORD*)0x005EB4FC);
    writeFileLog((char*)"game.txt", b, (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(void*, void*))_StartGames)(thisp, _EDX);
    __try {
        unsigned char* p = (unsigned char*)thisp;
        int auxX = *(int*)(p + 0x2A0);
        int auxY = *(int*)(p + 0x2A4);
        int auxZ = *(int*)(p + 0x2A8);
        int camX = *(int*)(p + 0x38);
        int camY = *(int*)(p + 0x3C);
        int camZ = *(int*)(p + 0x40);
        unsigned char* ped = *(unsigned char**)(p + 0x2C4);
        int pedX=0,pedY=0,pedZ=0;
        if (ped) { pedX=*(int*)(ped+0x1AC); pedY=*(int*)(ped+0x1B0); pedZ=*(int*)(ped+0x1B4); }
        _snprintf(b,sizeof(b),"Player cam=%d,%d,%d aux=%d,%d,%d ped=0x%08X pedPos=%d,%d,%d tile=%d,%d",
            camX,camY,camZ,auxX,auxY,auxZ,(unsigned long)(ULONG_PTR)ped,pedX,pedY,pedZ, (auxX?auxX:camX)/16384,(auxY?auxY:camY)/16384);
        writeFileLog((char*)"camera.txt", b, (char*)"StartGames", (char*)"");
    } __except(EXCEPTION_EXECUTE_HANDLER) {}
}

void __fastcall HookUpdateWrapper(void* thisp, void* _EDX)
{
    writeFileLog((char*)"game.txt", (char*)"  Hud::UpdateWrapper enter", (char*)"InitGame", (char*)"");
    ((void (__fastcall*)(void*, void*))_UpdateWrapper)(thisp, _EDX);
}

