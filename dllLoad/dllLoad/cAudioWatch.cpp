// cAudioWatch.cpp - runtime probe of the retail audio path (see cAudioWatch.h).
// Attach pattern mirrors cMenu.cpp: DetourAttach rewrites the LPVOID globals to
// the Detours trampoline; each hook logs the caller (TraceCall) and forwards to
// the original retail code. All events are written to "audio.txt".
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "detours.h"
#include "cAudioWatch.h"
#include "DebugLogFile.h"
#include "cHookTrace.h"

// ---- trampolines (file-scope, rewritten by DetourAttach) ----
LPVOID _DMAudio_AddAudioObject = (LPVOID)0x00410530;   // DMAudio::sub_410530
LPVOID _DMAudio_LoadSTY        = (LPVOID)0x00410550;   // DMAudio::LoadSTY
LPVOID _DMAudio_Sub410560      = (LPVOID)0x00410560;   // DMAudio::sub_410560
LPVOID _DMAudio_PlayVocal      = (LPVOID)0x004105B0;   // DMAudio::PlayVocal
LPVOID _DMAudio_PlayMusic      = (LPVOID)0x00410590;   // DMAudio::sub_410590
LPVOID _DMAudio_Init3DSound    = (LPVOID)0x00410670;   // DMAudio::Init3DSound
LPVOID _SoundCard_LoadSounds   = (LPVOID)0x004B6B40;   // SoundCard::LoadSounds
LPVOID _AudioManager_StopMusic = (LPVOID)0x004B2350;   // AudioManager::sub_4B2350

// ---- log helpers ----
// Forward-declared retail class tags: only used to type the __thiscall `this`
// pointer (ECX) of the detoured functions; bodies are NOT needed here.
struct DMAudio;
struct AudioManager;
struct SoundCard;

static void AudioLog(const char* what, const char* info)
{
    writeFileLog((char*)"audio.txt", (char*)what, (char*)"audio", (char*)info);
}

// ---- DMAudio wrappers (retail is __thiscall; detoured via __fastcall) ----

// int __thiscall DMAudio::sub_410530(DMAudio* this, int* AudioObject)  - sets base sample rate
int __fastcall HookDMAudio_AddAudioObject(DMAudio* self, void* _edx, int* pAudioObject)
{
    (void)_edx;
    TraceCall("DMAudio::AddAudioObject @0x00410530", TRACE_CALLER_ADDR);
    int sampleRate = ((int(__thiscall*)(DMAudio*, int*))_DMAudio_AddAudioObject)(self, pAudioObject);
    char info[160];
    _snprintf(info, sizeof(info), "sampleRate=%d, *AudioObject=%d",
              sampleRate, pAudioObject ? *pAudioObject : -1);
    AudioLog("AddAudioObject", info);
    return sampleRate;
}

// char __thiscall DMAudio::LoadSTY(DMAudio* this, const char* FileName) - loads a .sty bank
char __fastcall HookDMAudio_LoadSTY(DMAudio* self, void* _edx, const char* FileName)
{
    (void)_edx;
    TraceCall("DMAudio::LoadSTY @0x00410550", TRACE_CALLER_ADDR);
    char info[256];
    _snprintf(info, sizeof(info), "style=%s", FileName ? FileName : "(null)");
    AudioLog("LoadSTY", info);
    return ((char(__thiscall*)(DMAudio*, const char*))_DMAudio_LoadSTY)(self, FileName);
}

// char __thiscall DMAudio::sub_410560(DMAudio* this) - music/Vocal poll entry
char __fastcall HookDMAudio_Sub410560(DMAudio* self, void* _edx)
{
    (void)_edx;
    TraceCall("DMAudio::sub_410560 @0x00410560", TRACE_CALLER_ADDR);
    AudioLog("sub_410560", "poll");
    return ((char(__thiscall*)(DMAudio*))_DMAudio_Sub410560)(self);
}

// void __thiscall DMAudio::PlayVocal(DMAudio* this, int vocal)
void __fastcall HookDMAudio_PlayVocal(DMAudio* self, void* _edx, int vocal)
{
    (void)_edx;
    TraceCall("DMAudio::PlayVocal @0x004105B0", TRACE_CALLER_ADDR);
    char info[64];
    _snprintf(info, sizeof(info), "vocal=%d", vocal);
    AudioLog("PlayVocal", info);
    ((void(__thiscall*)(DMAudio*, int))_DMAudio_PlayVocal)(self, vocal);
}

// char __thiscall DMAudio::sub_410590(DMAudio* this, unsigned __int8 trackIndex, int loop) -> PlayMusic
char __fastcall HookDMAudio_PlayMusic(DMAudio* self, void* _edx, unsigned __int8 trackIndex, int loop)
{
    (void)_edx;
    TraceCall("DMAudio::PlayMusic(sub_410590) @0x00410590", TRACE_CALLER_ADDR);
    char info[96];
    _snprintf(info, sizeof(info), "trackIndex=%u loop=%d", (unsigned)trackIndex, loop);
    AudioLog("PlayMusic", info);
    return ((char(__thiscall*)(DMAudio*, unsigned __int8, int))_DMAudio_PlayMusic)
        (self, trackIndex, loop);
}

// byte __thiscall DMAudio::Init3DSound(DMAudio* this, byte pSound3DConfigure) - runs right after LoadSTY in Inistal_Defaut
byte __fastcall HookDMAudio_Init3DSound(DMAudio* self, void* _edx, byte pSound3DConfigure)
{
    (void)_edx;
    TraceCall("DMAudio::Init3DSound @0x00410670", TRACE_CALLER_ADDR);
    char info[64];
    _snprintf(info, sizeof(info), "pSound3DConfigure=%u", (unsigned)pSound3DConfigure);
    AudioLog("Init3DSound", info);
    return ((byte(__thiscall*)(DMAudio*, byte))_DMAudio_Init3DSound)(self, pSound3DConfigure);
}

// char __thiscall SoundCard::LoadSounds(SoundCard* this, const char* buffer) - low-level bank loader
char __fastcall HookSoundCard_LoadSounds(SoundCard* self, void* _edx, const char* buffer)
{
    (void)_edx;
    TraceCall("SoundCard::LoadSounds @0x004B6B40", TRACE_CALLER_ADDR);
    char info[160];
    _snprintf(info, sizeof(info), "bank=%s", buffer ? buffer : "(null)");
    AudioLog("LoadSounds", info);
    return ((char(__thiscall*)(SoundCard*, const char*))_SoundCard_LoadSounds)(self, buffer);
}

// char __thiscall AudioManager::sub_4B2350(AudioManager* this, unsigned __int8 idx, int loop) -> StopMusic
char __fastcall HookAudioManager_StopMusic(AudioManager* self, void* _edx, unsigned __int8 idx, int loop)
{
    (void)_edx;
    TraceCall("AudioManager::StopMusic(sub_4B2350) @0x004B2350", TRACE_CALLER_ADDR);
    char info[96];
    _snprintf(info, sizeof(info), "trackIndex=%u loop=%d", (unsigned)idx, loop);
    AudioLog("StopMusic", info);
    return ((char(__thiscall*)(AudioManager*, unsigned __int8, int))_AudioManager_StopMusic)
        (self, idx, loop);
}

// ---- file-open probe: catches any open of "GTAudio\*" / "*.wav" ----
typedef HANDLE(WINAPI* CreateFileAFunc)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
typedef HANDLE(WINAPI* CreateFileWFunc)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

static CreateFileAFunc RealCreateFileA = CreateFileA;
static CreateFileWFunc RealCreateFileW = CreateFileW;

// Re-entry guard: our own logging writes files via fopen->CreateFileA, which must
// NOT re-enter the hook. __declspec(thread) keeps it safe on every thread.
static __declspec(thread) int s_inOpenHook;

static int ContainsInsensitive(const char* s, const char* sub)
{
    size_t subLen = strlen(sub);
    if (subLen == 0) return 1;
    for (; *s; s++) {
        size_t i = 0;
        while (i < subLen && s[i] && tolower((unsigned char)s[i]) == tolower((unsigned char)sub[i])) i++;
        if (i == subLen) return 1;
    }
    return 0;
}

static int EndsWithInsensitive(const char* s, const char* suf)
{
    size_t sl = strlen(s), fl = strlen(suf);
    if (fl > sl) return 0;
    s += sl - fl;
    for (size_t i = 0; i < fl; i++) {
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)suf[i])) return 0;
    }
    return 1;
}

static int WideEndsWithInsensitive(const wchar_t* s, const char* suf)
{
    size_t sl = wcslen(s), fl = strlen(suf);
    if (fl > sl) return 0;
    s += sl - fl;
    for (size_t i = 0; i < fl; i++) {
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)suf[i])) return 0;
    }
    return 1;
}

static void LogWavOpen(const char* path)
{
    char line[400];
    _snprintf(line, sizeof(line), "%s", path ? path : "(null)");
    AudioLog("OpenWav", line);
}

// Resolve the address the retail caller continues at to "module!+rva". Unlike
// TraceCall (which maps into gta2.exe symbol names), this covers callers inside
// ANY loaded module (CRT, DLLs, winmm, etc.).
static void FormatCaller(unsigned long callerAddr, char* out, int outSize)
{
    char mod[MAX_PATH] = "?";
    unsigned long rva = callerAddr;
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery((LPCVOID)callerAddr, &mbi, sizeof(mbi)) && mbi.AllocationBase) {
        HMODULE h = (HMODULE)mbi.AllocationBase;
        if (GetModuleFileNameA(h, mod, MAX_PATH) > 0) {
            const char* baseName = strrchr(mod, '\\');
            if (baseName) memmove(mod, baseName + 1, strlen(baseName + 1) + 1);
        }
        rva = callerAddr - (unsigned long)mbi.AllocationBase;
    }
    _snprintf(out, outSize, "%s!+0x%04X (caller=0x%08X)", mod, rva, callerAddr);
}

static void LogWavOpenCaller(unsigned long callerAddr)
{
    char line[540];
    FormatCaller(callerAddr, line, sizeof(line));
    AudioLog("OpenWavCaller", line);
}

// Shared entry points for the other probes (see cAudioWatch.h): same log file,
// caller resolution works for callers in any loaded module.
void ProbeLog(const char* tag, const char* info)
{
    AudioLog(tag, info);
}

void ProbeLogCaller(const char* tag, unsigned long callerAddr)
{
    char line[540];
    FormatCaller(callerAddr, line, sizeof(line));
    AudioLog(tag, line);
}

HANDLE WINAPI HookCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                              LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                              DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
                              HANDLE hTemplateFile)
{
    if (!s_inOpenHook && lpFileName && (ContainsInsensitive(lpFileName, "GTAudio")
                                       || EndsWithInsensitive(lpFileName, ".wav"))) {
        s_inOpenHook = 1;
        LogWavOpen(lpFileName);
        LogWavOpenCaller(TRACE_CALLER_ADDR);
        s_inOpenHook = 0;
    }
    return RealCreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                           dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI HookCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
                              LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                              DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
                              HANDLE hTemplateFile)
{
    if (!s_inOpenHook && lpFileName && WideEndsWithInsensitive(lpFileName, ".wav")) {
        char ascii[260];
        int n = WideCharToMultiByte(CP_ACP, 0, lpFileName, -1, ascii, sizeof(ascii), NULL, NULL);
        if (n > 0) {
            s_inOpenHook = 1;
            LogWavOpen(ascii);
            LogWavOpenCaller(TRACE_CALLER_ADDR);
            s_inOpenHook = 0;
        }
    }
    return RealCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                           dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

void InstallAudioWatchHooks(void)
{
    // DMAudio / AudioManager wrappers
    DetourTransactionBegin();
    if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR) {
        printf("cAudioWatch: DetourUpdateThread failed\n");
        return;
    }
    DetourAttach(&(PVOID&)_DMAudio_AddAudioObject, (PVOID)HookDMAudio_AddAudioObject);
    DetourAttach(&(PVOID&)_DMAudio_LoadSTY,        (PVOID)HookDMAudio_LoadSTY);
    DetourAttach(&(PVOID&)_DMAudio_Sub410560,      (PVOID)HookDMAudio_Sub410560);
    DetourAttach(&(PVOID&)_DMAudio_PlayVocal,      (PVOID)HookDMAudio_PlayVocal);
    DetourAttach(&(PVOID&)_DMAudio_PlayMusic,      (PVOID)HookDMAudio_PlayMusic);
    DetourAttach(&(PVOID&)_DMAudio_Init3DSound,    (PVOID)HookDMAudio_Init3DSound);
    DetourAttach(&(PVOID&)_SoundCard_LoadSounds,   (PVOID)HookSoundCard_LoadSounds);
    DetourAttach(&(PVOID&)_AudioManager_StopMusic, (PVOID)HookAudioManager_StopMusic);
    // file-open probe (kernel32/kerbase exports)
    DetourAttach(&(PVOID&)RealCreateFileA, (PVOID)HookCreateFileA);
    DetourAttach(&(PVOID&)RealCreateFileW, (PVOID)HookCreateFileW);

    LONG err = DetourTransactionCommit();
    printf("cAudioWatch: hooks installed (%ld)\n", err);
    AudioLog("Install", err == NO_ERROR ? "ok" : "commit failed");
}