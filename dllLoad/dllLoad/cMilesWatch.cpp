// cMilesWatch.cpp - runtime probe of the retail Miles (mss32.dll v5.0r) API
// as used by gta2.exe. See cMilesWatch.h.
//
// GTA2.exe imports mss32.dll directly, so every audio playback step of the
// retail game goes through one of the 52 AIL_* exports. Each detour logs the
// caller (module!+rva, resolved via ProbeLogCaller) plus the arguments, then
// forwards to the original Miles code. This maps DMAudio/AudioManager functions
// to the exact Miles calls used for music streams, vocals and radio.
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "detours.h"
#include "cMilesWatch.h"
#include "cAudioWatch.h"
#include "cHookTrace.h"

// ---- Miles v5.0r handle types (all opaque pointers) ----
typedef void* MHDIGDRIVER;
typedef void* HSAMPLE;
typedef void* H3DSAMPLE;
typedef void* HSTREAM;
typedef void* HPROVIDER;
typedef void* H3DPOBJECT;

// AILSOUNDINFO, layout taken from mss.h 6.1a (mss32/include/mss_6_1a.h) -
// verified identical in the 6.5c SDK header.
typedef struct _AILSOUNDINFO {
    int format;
    const void* data_ptr;
    unsigned int data_len;
    unsigned int rate;
    int bits;
    int channels;
    unsigned int samples;
    unsigned int block_size;
    const void* initial_ptr;
} AILSOUNDINFO;

// ---- log budget per function (per-frame calls would flood the log) ----
enum {
    FN_startup, FN_shutdown, FN_waveOutOpen, FN_waveOutClose, FN_set_preference,
    FN_set_master_vol, FN_dig_release, FN_dig_reacquire, FN_delay,
    FN_mem_alloc, FN_mem_free,
    FN_open_stream, FN_close_stream, FN_start_stream, FN_set_stream_loop_count,
    FN_set_stream_volume, FN_stream_volume, FN_stream_status,
    FN_set_stream_rate, FN_stream_rate, FN_stream_ms_pos, FN_set_stream_ms_pos,
    FN_alloc_sample, FN_init_sample, FN_set_sample_type, FN_set_sample_address,
    FN_sample_status, FN_start_sample, FN_end_sample, FN_release_sample,
    FN_set_sample_vol, FN_set_sample_pan, FN_set_sample_rate, FN_set_sample_loop,
    FN_set_sample_loop_block,
    FN_open_3D_provider, FN_close_3D_provider, FN_enum_3D_providers,
    FN_3D_provider_attr, FN_set_3D_provider_pref,
    FN_alloc_3D_sample, FN_release_3D_sample, FN_start_3D_sample, FN_end_3D_sample,
    FN_3D_sample_status, FN_set_3D_sample_info, FN_set_3D_position,
    FN_set_3D_sample_vol, FN_set_3D_sample_loop, FN_set_3D_sample_loop_block,
    FN_set_3D_sample_rate, FN_set_3D_sample_dist, FN_3D_sample_rate,
    FN_COUNT
};

// Per-function call budget: high-frequency (per-frame) hooks are capped so the
// log stays readable; lifecycle hooks are logged generously.
#define BUDGET_LOW   24
#define BUDGET_HIGH  400

static int s_calls[FN_COUNT];
static int s_installed;
static int s_haveMss;

// Our logging does file I/O; keep Miles from being re-entered through it.
static __declspec(thread) int s_inHook;

static int ShouldLog(int idx, int limit)
{
    if (s_calls[idx] >= limit) return 0;
    s_calls[idx]++;
    return 1;
}

// Log "<tag>Caller" + "<tag>" for one Miles call (caller first, as elsewhere).
static void MilesLog(int idx, const char* name, int limit, const char* info)
{
    if (s_inHook) return;
    s_inHook = 1;
    if (ShouldLog(idx, limit)) {
        ProbeLogCaller(name, TRACE_CALLER_ADDR);
        ProbeLog(name, info);
    }
    s_inHook = 0;
}

// ---- trampolines, filled by GetProcAddress + rewritten by DetourAttach ----
static LPVOID _AIL_startup;
static LPVOID _AIL_shutdown;
static LPVOID _AIL_waveOutOpen;
static LPVOID _AIL_waveOutClose;
static LPVOID _AIL_set_preference;
static LPVOID _AIL_set_digital_master_volume;
static LPVOID _AIL_digital_handle_release;
static LPVOID _AIL_digital_handle_reacquire;
static LPVOID _AIL_delay;
static LPVOID _AIL_mem_alloc_lock;
static LPVOID _AIL_mem_free_lock;
static LPVOID _AIL_open_stream;
static LPVOID _AIL_close_stream;
static LPVOID _AIL_start_stream;
static LPVOID _AIL_set_stream_loop_count;
static LPVOID _AIL_set_stream_volume;
static LPVOID _AIL_stream_volume;
static LPVOID _AIL_stream_status;
static LPVOID _AIL_set_stream_playback_rate;
static LPVOID _AIL_stream_playback_rate;
static LPVOID _AIL_stream_ms_position;
static LPVOID _AIL_set_stream_ms_position;
static LPVOID _AIL_allocate_sample_handle;
static LPVOID _AIL_init_sample;
static LPVOID _AIL_set_sample_type;
static LPVOID _AIL_set_sample_address;
static LPVOID _AIL_sample_status;
static LPVOID _AIL_start_sample;
static LPVOID _AIL_end_sample;
static LPVOID _AIL_release_sample_handle;
static LPVOID _AIL_set_sample_volume;
static LPVOID _AIL_set_sample_pan;
static LPVOID _AIL_set_sample_playback_rate;
static LPVOID _AIL_set_sample_loop_count;
static LPVOID _AIL_set_sample_loop_block;
static LPVOID _AIL_open_3D_provider;
static LPVOID _AIL_close_3D_provider;
static LPVOID _AIL_enumerate_3D_providers;
static LPVOID _AIL_3D_provider_attribute;
static LPVOID _AIL_set_3D_provider_preference;
static LPVOID _AIL_allocate_3D_sample_handle;
static LPVOID _AIL_release_3D_sample_handle;
static LPVOID _AIL_start_3D_sample;
static LPVOID _AIL_end_3D_sample;
static LPVOID _AIL_3D_sample_status;
static LPVOID _AIL_set_3D_sample_info;
static LPVOID _AIL_set_3D_position;
static LPVOID _AIL_set_3D_sample_volume;
static LPVOID _AIL_set_3D_sample_loop_count;
static LPVOID _AIL_set_3D_sample_loop_block;
static LPVOID _AIL_set_3D_sample_playback_rate;
static LPVOID _AIL_set_3D_sample_float_distances;
static LPVOID _AIL_3D_sample_playback_rate;

// ---- startup / shutdown / digital driver ----
int __stdcall HookAIL_startup(void)
{
    int rc = ((int(__stdcall*)(void))_AIL_startup)();
    char info[64];
    _snprintf(info, sizeof(info), "rc=%d", rc);
    MilesLog(FN_startup, "AIL_startup", BUDGET_HIGH, info);
    return rc;
}

void __stdcall HookAIL_shutdown(void)
{
    MilesLog(FN_shutdown, "AIL_shutdown", BUDGET_HIGH, "");
    ((void(__stdcall*)(void))_AIL_shutdown)();
}

// AIL_waveOutOpen(HDIGDRIVER FAR *drvr, LPHWAVEOUT FAR *lphWaveOut, S32 wDeviceID, LPWAVEFORMAT lpFormat)
// LPWAVEFORMAT == WAVEFORMATEX*
int __stdcall HookAIL_waveOutOpen(MHDIGDRIVER* drvr, void** lphWaveOut, int wDeviceID, WAVEFORMATEX* fmt)
{
    int rc = ((int(__stdcall*)(MHDIGDRIVER*, void**, int, WAVEFORMATEX*))_AIL_waveOutOpen)
        (drvr, lphWaveOut, wDeviceID, fmt);
    char info[256];
    _snprintf(info, sizeof(info),
              "rc=%d deviceID=%d dig=%p wout=%p fmt={tag=0x%04X ch=%u rate=%lu avgBytes=%lu blockAlign=%u bits=%u cbSize=%u}",
              rc, wDeviceID, drvr ? *drvr : NULL, lphWaveOut ? *lphWaveOut : NULL,
              fmt ? fmt->wFormatTag : 0, fmt ? fmt->nChannels : 0,
              fmt ? fmt->nSamplesPerSec : 0, fmt ? fmt->nAvgBytesPerSec : 0,
              fmt ? fmt->nBlockAlign : 0, fmt ? fmt->wBitsPerSample : 0,
              fmt ? fmt->cbSize : 0);
    MilesLog(FN_waveOutOpen, "AIL_waveOutOpen", BUDGET_LOW, info);
    return rc;
}

void __stdcall HookAIL_waveOutClose(MHDIGDRIVER drvr)
{
    char info[48];
    _snprintf(info, sizeof(info), "dig=%p", drvr);
    MilesLog(FN_waveOutClose, "AIL_waveOutClose", BUDGET_LOW, info);
    ((void(__stdcall*)(MHDIGDRIVER))_AIL_waveOutClose)(drvr);
}

int __stdcall HookAIL_set_preference(unsigned int number, int value)
{
    int rc = ((int(__stdcall*)(unsigned int, int))_AIL_set_preference)(number, value);
    char info[80];
    _snprintf(info, sizeof(info), "pref=%u value=%d rc=%d", number, value, rc);
    MilesLog(FN_set_preference, "AIL_set_preference", BUDGET_HIGH, info);
    return rc;
}

void __stdcall HookAIL_set_digital_master_volume(MHDIGDRIVER dig, int volume)
{
    char info[64];
    _snprintf(info, sizeof(info), "dig=%p volume=%d", dig, volume);
    MilesLog(FN_set_master_vol, "AIL_set_digital_master_volume", BUDGET_HIGH, info);
    ((void(__stdcall*)(MHDIGDRIVER, int))_AIL_set_digital_master_volume)(dig, volume);
}

// AIL_digital_handle_release(HDIGDRIVER drvr) -> S32
int __stdcall HookAIL_digital_handle_release(MHDIGDRIVER dig)
{
    char info[64];
    _snprintf(info, sizeof(info), "dig=%p", dig);
    MilesLog(FN_dig_release, "AIL_digital_handle_release", BUDGET_LOW, info);
    return ((int(__stdcall*)(MHDIGDRIVER))_AIL_digital_handle_release)(dig);
}

// AIL_digital_handle_reacquire(HDIGDRIVER drvr) -> S32
int __stdcall HookAIL_digital_handle_reacquire(MHDIGDRIVER dig)
{
    char info[64];
    _snprintf(info, sizeof(info), "dig=%p", dig);
    MilesLog(FN_dig_reacquire, "AIL_digital_handle_reacquire", BUDGET_LOW, info);
    return ((int(__stdcall*)(MHDIGDRIVER))_AIL_digital_handle_reacquire)(dig);
}

void __stdcall HookAIL_delay(int ms)
{
    char info[48];
    _snprintf(info, sizeof(info), "ms=%d", ms);
    MilesLog(FN_delay, "AIL_delay", BUDGET_LOW, info);
    ((void(__stdcall*)(int))_AIL_delay)(ms);
}

void* __stdcall HookAIL_mem_alloc_lock(unsigned long size)
{
    void* p = ((void*(__stdcall*)(unsigned long))_AIL_mem_alloc_lock)(size);
    char info[64];
    _snprintf(info, sizeof(info), "size=%lu ptr=%p", size, p);
    MilesLog(FN_mem_alloc, "AIL_mem_alloc_lock", BUDGET_LOW, info);
    return p;
}

void __stdcall HookAIL_mem_free_lock(void* ptr)
{
    MilesLog(FN_mem_free, "AIL_mem_free_lock", BUDGET_LOW, "free");
    ((void(__stdcall*)(void*))_AIL_mem_free_lock)(ptr);
}

// ---- music streams: this is how GTAudio\*.wav get played ----
HSTREAM __stdcall HookAIL_open_stream(MHDIGDRIVER dig, const char* filename, int stream_mem)
{
    HSTREAM s = ((HSTREAM(__stdcall*)(MHDIGDRIVER, const char*, int))_AIL_open_stream)
        (dig, filename, stream_mem);
    char info[320];
    _snprintf(info, sizeof(info), "dig=%p file=%s stream_mem=%d -> stream=%p",
              dig, filename ? filename : "(null)", stream_mem, s);
    MilesLog(FN_open_stream, "AIL_open_stream", BUDGET_HIGH, info);
    return s;
}

void __stdcall HookAIL_close_stream(HSTREAM s)
{
    char info[48];
    _snprintf(info, sizeof(info), "stream=%p", s);
    MilesLog(FN_close_stream, "AIL_close_stream", BUDGET_LOW, info);
    ((void(__stdcall*)(HSTREAM))_AIL_close_stream)(s);
}

void __stdcall HookAIL_start_stream(HSTREAM s)
{
    char info[48];
    _snprintf(info, sizeof(info), "stream=%p", s);
    MilesLog(FN_start_stream, "AIL_start_stream", BUDGET_LOW, info);
    ((void(__stdcall*)(HSTREAM))_AIL_start_stream)(s);
}

void __stdcall HookAIL_set_stream_loop_count(HSTREAM s, int count)
{
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p loopCount=%d", s, count);
    MilesLog(FN_set_stream_loop_count, "AIL_set_stream_loop_count", BUDGET_LOW, info);
    ((void(__stdcall*)(HSTREAM, int))_AIL_set_stream_loop_count)(s, count);
}

void __stdcall HookAIL_set_stream_volume(HSTREAM s, int volume)
{
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p volume=%d", s, volume);
    MilesLog(FN_set_stream_volume, "AIL_set_stream_volume", BUDGET_LOW, info);
    ((void(__stdcall*)(HSTREAM, int))_AIL_set_stream_volume)(s, volume);
}

int __stdcall HookAIL_stream_volume(HSTREAM s)
{
    int v = ((int(__stdcall*)(HSTREAM))_AIL_stream_volume)(s);
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p -> volume=%d", s, v);
    MilesLog(FN_stream_volume, "AIL_stream_volume", BUDGET_LOW, info);
    return v;
}

int __stdcall HookAIL_stream_status(HSTREAM s)
{
    int st = ((int(__stdcall*)(HSTREAM))_AIL_stream_status)(s);
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p -> status=%d", s, st);
    MilesLog(FN_stream_status, "AIL_stream_status", BUDGET_LOW, info);
    return st;
}

void __stdcall HookAIL_set_stream_playback_rate(HSTREAM s, int rate)
{
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p rate=%d", s, rate);
    MilesLog(FN_set_stream_rate, "AIL_set_stream_playback_rate", BUDGET_LOW, info);
    ((void(__stdcall*)(HSTREAM, int))_AIL_set_stream_playback_rate)(s, rate);
}

int __stdcall HookAIL_stream_playback_rate(HSTREAM s)
{
    int r = ((int(__stdcall*)(HSTREAM))_AIL_stream_playback_rate)(s);
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p -> rate=%d", s, r);
    MilesLog(FN_stream_rate, "AIL_stream_playback_rate", BUDGET_LOW, info);
    return r;
}

void __stdcall HookAIL_stream_ms_position(HSTREAM s, long* total_ms, long* current_ms)
{
    ((void(__stdcall*)(HSTREAM, long*, long*))_AIL_stream_ms_position)(s, total_ms, current_ms);
    char info[96];
    _snprintf(info, sizeof(info), "stream=%p total_ms=%ld cur_ms=%ld", s,
              total_ms ? *total_ms : -1, current_ms ? *current_ms : -1);
    MilesLog(FN_stream_ms_pos, "AIL_stream_ms_position", BUDGET_LOW, info);
}

void __stdcall HookAIL_set_stream_ms_position(HSTREAM s, int pos)
{
    char info[64];
    _snprintf(info, sizeof(info), "stream=%p pos=%d", s, pos);
    MilesLog(FN_set_stream_ms_pos, "AIL_set_stream_ms_position", BUDGET_LOW, info);
    ((void(__stdcall*)(HSTREAM, int))_AIL_set_stream_ms_position)(s, pos);
}

// ---- 2D samples (vocals, SFX): the game hands Miles memory, no file I/O ----
HSAMPLE __stdcall HookAIL_allocate_sample_handle(MHDIGDRIVER dig)
{
    HSAMPLE s = ((HSAMPLE(__stdcall*)(MHDIGDRIVER))_AIL_allocate_sample_handle)(dig);
    char info[48];
    _snprintf(info, sizeof(info), "dig=%p -> sample=%p", dig, s);
    MilesLog(FN_alloc_sample, "AIL_allocate_sample_handle", BUDGET_LOW, info);
    return s;
}

void __stdcall HookAIL_init_sample(HSAMPLE s)
{
    char info[48];
    _snprintf(info, sizeof(info), "sample=%p", s);
    MilesLog(FN_init_sample, "AIL_init_sample", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE))_AIL_init_sample)(s);
}

// v5.0r AIL_set_sample_type has 3 args; the 3rd meaning is unverified.
void __stdcall HookAIL_set_sample_type(HSAMPLE s, unsigned int type, unsigned int extra)
{
    char info[96];
    _snprintf(info, sizeof(info), "sample=%p type=%u extra=0x%X", s, type, extra);
    MilesLog(FN_set_sample_type, "AIL_set_sample_type", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, unsigned int, unsigned int))_AIL_set_sample_type)(s, type, extra);
}

void __stdcall HookAIL_set_sample_address(HSAMPLE s, void* address, unsigned int size)
{
    char info[96];
    _snprintf(info, sizeof(info), "sample=%p address=%p size=%u", s, address, size);
    MilesLog(FN_set_sample_address, "AIL_set_sample_address", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, void*, unsigned int))_AIL_set_sample_address)(s, address, size);
}

int __stdcall HookAIL_sample_status(HSAMPLE s)
{
    int st = ((int(__stdcall*)(HSAMPLE))_AIL_sample_status)(s);
    char info[64];
    _snprintf(info, sizeof(info), "sample=%p -> status=%d", s, st);
    MilesLog(FN_sample_status, "AIL_sample_status", BUDGET_LOW, info);
    return st;
}

void __stdcall HookAIL_start_sample(HSAMPLE s)
{
    char info[48];
    _snprintf(info, sizeof(info), "sample=%p", s);
    MilesLog(FN_start_sample, "AIL_start_sample", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE))_AIL_start_sample)(s);
}

void __stdcall HookAIL_end_sample(HSAMPLE s)
{
    char info[48];
    _snprintf(info, sizeof(info), "sample=%p", s);
    MilesLog(FN_end_sample, "AIL_end_sample", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE))_AIL_end_sample)(s);
}

void __stdcall HookAIL_release_sample_handle(HSAMPLE s)
{
    MilesLog(FN_release_sample, "AIL_release_sample_handle", BUDGET_LOW, "release");
    ((void(__stdcall*)(HSAMPLE))_AIL_release_sample_handle)(s);
}

void __stdcall HookAIL_set_sample_volume(HSAMPLE s, int volume)
{
    char info[64];
    _snprintf(info, sizeof(info), "sample=%p volume=%d", s, volume);
    MilesLog(FN_set_sample_vol, "AIL_set_sample_volume", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, int))_AIL_set_sample_volume)(s, volume);
}

void __stdcall HookAIL_set_sample_pan(HSAMPLE s, int pan)
{
    char info[64];
    _snprintf(info, sizeof(info), "sample=%p pan=%d", s, pan);
    MilesLog(FN_set_sample_pan, "AIL_set_sample_pan", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, int))_AIL_set_sample_pan)(s, pan);
}

void __stdcall HookAIL_set_sample_playback_rate(HSAMPLE s, int rate)
{
    char info[64];
    _snprintf(info, sizeof(info), "sample=%p rate=%d", s, rate);
    MilesLog(FN_set_sample_rate, "AIL_set_sample_playback_rate", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, int))_AIL_set_sample_playback_rate)(s, rate);
}

void __stdcall HookAIL_set_sample_loop_count(HSAMPLE s, int count)
{
    char info[64];
    _snprintf(info, sizeof(info), "sample=%p loopCount=%d", s, count);
    MilesLog(FN_set_sample_loop, "AIL_set_sample_loop_count", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, int))_AIL_set_sample_loop_count)(s, count);
}

void __stdcall HookAIL_set_sample_loop_block(HSAMPLE s, int loop_start, int loop_end)
{
    char info[80];
    _snprintf(info, sizeof(info), "sample=%p loop=[%d..%d]", s, loop_start, loop_end);
    MilesLog(FN_set_sample_loop_block, "AIL_set_sample_loop_block", BUDGET_LOW, info);
    ((void(__stdcall*)(HSAMPLE, int, int))_AIL_set_sample_loop_block)(s, loop_start, loop_end);
}

// ---- 3D provider (mssds3dh.m3d) and 3D samples ----
// AIL_open_3D_provider(HPROVIDER lib) -> M3DRESULT. The handle comes from
// AIL_enumerate_3D_providers, it is NOT a provider name.
int __stdcall HookAIL_open_3D_provider(HPROVIDER lib)
{
    int rc = ((int(__stdcall*)(HPROVIDER))_AIL_open_3D_provider)(lib);
    char info[128];
    _snprintf(info, sizeof(info), "provider=%p -> rc=%d", lib, rc);
    MilesLog(FN_open_3D_provider, "AIL_open_3D_provider", BUDGET_LOW, info);
    return rc;
}

void __stdcall HookAIL_close_3D_provider(HPROVIDER lib)
{
    MilesLog(FN_close_3D_provider, "AIL_close_3D_provider", BUDGET_LOW, "close");
    ((void(__stdcall*)(HPROVIDER))_AIL_close_3D_provider)(lib);
}

// AIL_enumerate_3D_providers(HPROENUM FAR *next, HPROVIDER FAR *dest, C8 FAR * FAR *name)
int __stdcall HookAIL_enumerate_3D_providers(void** next, HPROVIDER** dest, char*** name)
{
    int rc = ((int(__stdcall*)(void**, HPROVIDER**, char***))_AIL_enumerate_3D_providers)
        (next, dest, name);
    char info[256];
    _snprintf(info, sizeof(info), "next=%p rc=%d provider=%p name=%s",
              next ? *next : NULL, rc,
              (dest && *dest) ? (void*)*dest : NULL,
              (name && *name && **name) ? **name : "(null)");
    MilesLog(FN_enum_3D_providers, "AIL_enumerate_3D_providers", BUDGET_LOW, info);
    return rc;
}

// AIL_3D_provider_attribute(HPROVIDER lib, C8 const FAR *name, void FAR *val)
void __stdcall HookAIL_3D_provider_attribute(HPROVIDER lib, const char* attr, void* value)
{
    char info[160];
    _snprintf(info, sizeof(info), "name=%s value=%p",
              attr ? attr : "(null)", value);
    MilesLog(FN_3D_provider_attr, "AIL_3D_provider_attribute", BUDGET_LOW, info);
    ((void(__stdcall*)(HPROVIDER, const char*, void*))_AIL_3D_provider_attribute)
        (lib, attr, value);
}

// AIL_set_3D_provider_preference(HPROVIDER lib, C8 const FAR *name, void const FAR *val)
void __stdcall HookAIL_set_3D_provider_preference(HPROVIDER lib, const char* pref, const void* value)
{
    char info[160];
    _snprintf(info, sizeof(info), "name=%s value=%p",
              pref ? pref : "(null)", value);
    MilesLog(FN_set_3D_provider_pref, "AIL_set_3D_provider_preference", BUDGET_LOW, info);
    ((void(__stdcall*)(HPROVIDER, const char*, const void*))_AIL_set_3D_provider_preference)
        (lib, pref, value);
}

H3DSAMPLE __stdcall HookAIL_allocate_3D_sample_handle(HPROVIDER lib)
{
    H3DSAMPLE s = ((H3DSAMPLE(__stdcall*)(HPROVIDER))_AIL_allocate_3D_sample_handle)(lib);
    char info[64];
    _snprintf(info, sizeof(info), "provider=%p -> sample3D=%p", lib, s);
    MilesLog(FN_alloc_3D_sample, "AIL_allocate_3D_sample_handle", BUDGET_LOW, info);
    return s;
}

void __stdcall HookAIL_release_3D_sample_handle(H3DSAMPLE s)
{
    MilesLog(FN_release_3D_sample, "AIL_release_3D_sample_handle", BUDGET_LOW, "release");
    ((void(__stdcall*)(H3DSAMPLE))_AIL_release_3D_sample_handle)(s);
}

void __stdcall HookAIL_start_3D_sample(H3DSAMPLE s)
{
    char info[48];
    _snprintf(info, sizeof(info), "sample3D=%p", s);
    MilesLog(FN_start_3D_sample, "AIL_start_3D_sample", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE))_AIL_start_3D_sample)(s);
}

void __stdcall HookAIL_end_3D_sample(H3DSAMPLE s)
{
    char info[48];
    _snprintf(info, sizeof(info), "sample3D=%p", s);
    MilesLog(FN_end_3D_sample, "AIL_end_3D_sample", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE))_AIL_end_3D_sample)(s);
}

int __stdcall HookAIL_3D_sample_status(H3DSAMPLE s)
{
    int st = ((int(__stdcall*)(H3DSAMPLE))_AIL_3D_sample_status)(s);
    char info[64];
    _snprintf(info, sizeof(info), "sample3D=%p -> status=%d", s, st);
    MilesLog(FN_3D_sample_status, "AIL_3D_sample_status", BUDGET_LOW, info);
    return st;
}

// AIL_set_3D_sample_info(H3DSAMPLE S, AILSOUNDINFO const FAR*info) -> S32
int __stdcall HookAIL_set_3D_sample_info(H3DSAMPLE s, const AILSOUNDINFO* info)
{
    char buf[224];
    _snprintf(buf, sizeof(buf),
              "sample3D=%p info={format=%d data=%p len=%lu rate=%lu bits=%d ch=%d samples=%lu block=%lu}",
              s,
              info ? info->format : 0,
              info ? (const void*)info->data_ptr : NULL,
              info ? info->data_len : 0,
              info ? info->rate : 0,
              info ? info->bits : 0,
              info ? info->channels : 0,
              info ? info->samples : 0,
              info ? info->block_size : 0);
    MilesLog(FN_set_3D_sample_info, "AIL_set_3D_sample_info", BUDGET_LOW, buf);
    return ((int(__stdcall*)(H3DSAMPLE, const AILSOUNDINFO*))_AIL_set_3D_sample_info)(s, info);
}

void __stdcall HookAIL_set_3D_position(H3DPOBJECT obj, float x, float y, float z)
{
    char info[128];
    _snprintf(info, sizeof(info), "obj=%p pos=(%.3f, %.3f, %.3f)", obj, x, y, z);
    MilesLog(FN_set_3D_position, "AIL_set_3D_position", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DPOBJECT, float, float, float))_AIL_set_3D_position)(obj, x, y, z);
}

// AIL_set_3D_sample_volume(H3DSAMPLE S, S32 volume)
void __stdcall HookAIL_set_3D_sample_volume(H3DSAMPLE s, int volume)
{
    char info[80];
    _snprintf(info, sizeof(info), "sample3D=%p volume=%d", s, volume);
    MilesLog(FN_set_3D_sample_vol, "AIL_set_3D_sample_volume", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE, int))_AIL_set_3D_sample_volume)(s, volume);
}

void __stdcall HookAIL_set_3D_sample_loop_count(H3DSAMPLE s, unsigned int count)
{
    char info[80];
    _snprintf(info, sizeof(info), "sample3D=%p loopCount=%u", s, count);
    MilesLog(FN_set_3D_sample_loop, "AIL_set_3D_sample_loop_count", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE, unsigned int))_AIL_set_3D_sample_loop_count)(s, count);
}

void __stdcall HookAIL_set_3D_sample_loop_block(H3DSAMPLE s, unsigned int start, unsigned int end)
{
    char info[96];
    _snprintf(info, sizeof(info), "sample3D=%p loop=[%u..%u]", s, start, end);
    MilesLog(FN_set_3D_sample_loop_block, "AIL_set_3D_sample_loop_block", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE, unsigned int, unsigned int))_AIL_set_3D_sample_loop_block)
        (s, start, end);
}

void __stdcall HookAIL_set_3D_sample_playback_rate(H3DSAMPLE s, int rate)
{
    char info[80];
    _snprintf(info, sizeof(info), "sample3D=%p rate=%d", s, rate);
    MilesLog(FN_set_3D_sample_rate, "AIL_set_3D_sample_playback_rate", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE, int))_AIL_set_3D_sample_playback_rate)(s, rate);
}

// v5.0r has 5 args here (@20); exact meaning unverified -> log raw words.
void __stdcall HookAIL_set_3D_sample_float_distances(H3DSAMPLE s, float a, float b, float c, float d)
{
    char info[160];
    _snprintf(info, sizeof(info), "sample3D=%p dist=(%.3f, %.3f, %.3f, %.3f)", s, a, b, c, d);
    MilesLog(FN_set_3D_sample_dist, "AIL_set_3D_sample_float_distances", BUDGET_LOW, info);
    ((void(__stdcall*)(H3DSAMPLE, float, float, float, float))_AIL_set_3D_sample_float_distances)
        (s, a, b, c, d);
}

int __stdcall HookAIL_3D_sample_playback_rate(H3DSAMPLE s)
{
    int r = ((int(__stdcall*)(H3DSAMPLE))_AIL_3D_sample_playback_rate)(s);
    char info[64];
    _snprintf(info, sizeof(info), "sample3D=%p -> rate=%d", s, r);
    MilesLog(FN_3D_sample_rate, "AIL_3D_sample_playback_rate", BUDGET_LOW, info);
    return r;
}

// ---- install ----
// mss32.dll may not be loaded when our DLL is injected: watch LoadLibrary and
// install the AIL hooks as soon as it appears.
typedef HMODULE(WINAPI* LoadLibraryAFunc)(LPCSTR);
typedef HMODULE(WINAPI* LoadLibraryWFunc)(LPCWSTR);

static LoadLibraryAFunc RealLoadLibraryA = LoadLibraryA;
static LoadLibraryWFunc RealLoadLibraryW = LoadLibraryW;

static int IsMilesDll(const char* name)
{
    if (!name) return 0;
    return strstr(name, "mss32") != NULL;
}

static HMODULE WINAPI HookLoadLibraryA(LPCSTR name)
{
    HMODULE h = RealLoadLibraryA(name);
    if (!s_haveMss && IsMilesDll(name)) {
        s_haveMss = 1;
        InstallMilesWatchHooks();
    }
    return h;
}

static HMODULE WINAPI HookLoadLibraryW(LPCWSTR name)
{
    HMODULE h = RealLoadLibraryW(name);
    if (!s_haveMss && name) {
        char ascii[260];
        if (WideCharToMultiByte(CP_ACP, 0, name, -1, ascii, sizeof(ascii), NULL, NULL)) {
            if (IsMilesDll(ascii)) {
                s_haveMss = 1;
                InstallMilesWatchHooks();
            }
        }
    }
    return h;
}

void InstallMilesWatchHooks(void)
{
    if (s_installed) return;

    HMODULE mss = GetModuleHandleA("mss32.dll");
    if (!mss) {
        ProbeLog("MilesInstall", "mss32.dll not loaded yet - hooks skipped");
        printf("cMilesWatch: mss32.dll not loaded\n");
        return;
    }
    s_haveMss = 1;

    // Exact stdcall-decorated export names of retail mss32.dll v5.0r.
#define RESOLVE(var, name) var = (LPVOID)GetProcAddress(mss, name)
    RESOLVE(_AIL_startup,                   "_AIL_startup@0");
    RESOLVE(_AIL_shutdown,                  "_AIL_shutdown@0");
    RESOLVE(_AIL_waveOutOpen,               "_AIL_waveOutOpen@16");
    RESOLVE(_AIL_waveOutClose,              "_AIL_waveOutClose@4");
    RESOLVE(_AIL_set_preference,            "_AIL_set_preference@8");
    RESOLVE(_AIL_set_digital_master_volume, "_AIL_set_digital_master_volume@8");
    RESOLVE(_AIL_digital_handle_release,    "_AIL_digital_handle_release@4");
    RESOLVE(_AIL_digital_handle_reacquire,  "_AIL_digital_handle_reacquire@4");
    RESOLVE(_AIL_delay,                     "_AIL_delay@4");
    RESOLVE(_AIL_mem_alloc_lock,            "_AIL_mem_alloc_lock@4");
    RESOLVE(_AIL_mem_free_lock,             "_AIL_mem_free_lock@4");
    RESOLVE(_AIL_open_stream,               "_AIL_open_stream@12");
    RESOLVE(_AIL_close_stream,              "_AIL_close_stream@4");
    RESOLVE(_AIL_start_stream,              "_AIL_start_stream@4");
    RESOLVE(_AIL_set_stream_loop_count,     "_AIL_set_stream_loop_count@8");
    RESOLVE(_AIL_set_stream_volume,         "_AIL_set_stream_volume@8");
    RESOLVE(_AIL_stream_volume,             "_AIL_stream_volume@4");
    RESOLVE(_AIL_stream_status,             "_AIL_stream_status@4");
    RESOLVE(_AIL_set_stream_playback_rate,  "_AIL_set_stream_playback_rate@8");
    RESOLVE(_AIL_stream_playback_rate,      "_AIL_stream_playback_rate@4");
    RESOLVE(_AIL_stream_ms_position,        "_AIL_stream_ms_position@12");
    RESOLVE(_AIL_set_stream_ms_position,    "_AIL_set_stream_ms_position@8");
    RESOLVE(_AIL_allocate_sample_handle,    "_AIL_allocate_sample_handle@4");
    RESOLVE(_AIL_init_sample,               "_AIL_init_sample@4");
    RESOLVE(_AIL_set_sample_type,           "_AIL_set_sample_type@12");
    RESOLVE(_AIL_set_sample_address,        "_AIL_set_sample_address@12");
    RESOLVE(_AIL_sample_status,             "_AIL_sample_status@4");
    RESOLVE(_AIL_start_sample,              "_AIL_start_sample@4");
    RESOLVE(_AIL_end_sample,                "_AIL_end_sample@4");
    RESOLVE(_AIL_release_sample_handle,     "_AIL_release_sample_handle@4");
    RESOLVE(_AIL_set_sample_volume,         "_AIL_set_sample_volume@8");
    RESOLVE(_AIL_set_sample_pan,            "_AIL_set_sample_pan@8");
    RESOLVE(_AIL_set_sample_playback_rate,  "_AIL_set_sample_playback_rate@8");
    RESOLVE(_AIL_set_sample_loop_count,     "_AIL_set_sample_loop_count@8");
    RESOLVE(_AIL_set_sample_loop_block,     "_AIL_set_sample_loop_block@12");
    RESOLVE(_AIL_open_3D_provider,          "_AIL_open_3D_provider@4");
    RESOLVE(_AIL_close_3D_provider,         "_AIL_close_3D_provider@4");
    RESOLVE(_AIL_enumerate_3D_providers,    "_AIL_enumerate_3D_providers@12");
    RESOLVE(_AIL_3D_provider_attribute,     "_AIL_3D_provider_attribute@12");
    RESOLVE(_AIL_set_3D_provider_preference,"_AIL_set_3D_provider_preference@12");
    RESOLVE(_AIL_allocate_3D_sample_handle, "_AIL_allocate_3D_sample_handle@4");
    RESOLVE(_AIL_release_3D_sample_handle,  "_AIL_release_3D_sample_handle@4");
    RESOLVE(_AIL_start_3D_sample,           "_AIL_start_3D_sample@4");
    RESOLVE(_AIL_end_3D_sample,             "_AIL_end_3D_sample@4");
    RESOLVE(_AIL_3D_sample_status,          "_AIL_3D_sample_status@4");
    RESOLVE(_AIL_set_3D_sample_info,        "_AIL_set_3D_sample_info@8");
    RESOLVE(_AIL_set_3D_position,           "_AIL_set_3D_position@16");
    RESOLVE(_AIL_set_3D_sample_volume,      "_AIL_set_3D_sample_volume@8");
    RESOLVE(_AIL_set_3D_sample_loop_count,  "_AIL_set_3D_sample_loop_count@8");
    RESOLVE(_AIL_set_3D_sample_loop_block,  "_AIL_set_3D_sample_loop_block@12");
    RESOLVE(_AIL_set_3D_sample_playback_rate,"_AIL_set_3D_sample_playback_rate@8");
    RESOLVE(_AIL_set_3D_sample_float_distances, "_AIL_set_3D_sample_float_distances@20");
    RESOLVE(_AIL_3D_sample_playback_rate,   "_AIL_3D_sample_playback_rate@4");
#undef RESOLVE

    DetourTransactionBegin();
    if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR) {
        printf("cMilesWatch: DetourUpdateThread failed\n");
        return;
    }
    if (!s_haveMss) {
        // mss32.dll was not in the process yet: retry when it gets loaded.
        DetourAttach(&(PVOID&)RealLoadLibraryA, (PVOID)HookLoadLibraryA);
        DetourAttach(&(PVOID&)RealLoadLibraryW, (PVOID)HookLoadLibraryW);
    }
    DetourAttach(&(_AIL_startup),                     (PVOID)HookAIL_startup);
    DetourAttach(&(_AIL_shutdown),                    (PVOID)HookAIL_shutdown);
    DetourAttach(&(_AIL_waveOutOpen),                 (PVOID)HookAIL_waveOutOpen);
    DetourAttach(&(_AIL_waveOutClose),                (PVOID)HookAIL_waveOutClose);
    DetourAttach(&(_AIL_set_preference),              (PVOID)HookAIL_set_preference);
    DetourAttach(&(_AIL_set_digital_master_volume),   (PVOID)HookAIL_set_digital_master_volume);
    DetourAttach(&(_AIL_digital_handle_release),      (PVOID)HookAIL_digital_handle_release);
    DetourAttach(&(_AIL_digital_handle_reacquire),    (PVOID)HookAIL_digital_handle_reacquire);
    DetourAttach(&(_AIL_delay),                       (PVOID)HookAIL_delay);
    DetourAttach(&(_AIL_mem_alloc_lock),              (PVOID)HookAIL_mem_alloc_lock);
    DetourAttach(&(_AIL_mem_free_lock),               (PVOID)HookAIL_mem_free_lock);
    DetourAttach(&(_AIL_open_stream),                 (PVOID)HookAIL_open_stream);
    DetourAttach(&(_AIL_close_stream),                (PVOID)HookAIL_close_stream);
    DetourAttach(&(_AIL_start_stream),                (PVOID)HookAIL_start_stream);
    DetourAttach(&(_AIL_set_stream_loop_count),       (PVOID)HookAIL_set_stream_loop_count);
    DetourAttach(&(_AIL_set_stream_volume),           (PVOID)HookAIL_set_stream_volume);
    DetourAttach(&(_AIL_stream_volume),               (PVOID)HookAIL_stream_volume);
    DetourAttach(&(_AIL_stream_status),               (PVOID)HookAIL_stream_status);
    DetourAttach(&(_AIL_set_stream_playback_rate),    (PVOID)HookAIL_set_stream_playback_rate);
    DetourAttach(&(_AIL_stream_playback_rate),        (PVOID)HookAIL_stream_playback_rate);
    DetourAttach(&(_AIL_stream_ms_position),          (PVOID)HookAIL_stream_ms_position);
    DetourAttach(&(_AIL_set_stream_ms_position),      (PVOID)HookAIL_set_stream_ms_position);
    DetourAttach(&(_AIL_allocate_sample_handle),      (PVOID)HookAIL_allocate_sample_handle);
    DetourAttach(&(_AIL_init_sample),                 (PVOID)HookAIL_init_sample);
    DetourAttach(&(_AIL_set_sample_type),             (PVOID)HookAIL_set_sample_type);
    DetourAttach(&(_AIL_set_sample_address),          (PVOID)HookAIL_set_sample_address);
    DetourAttach(&(_AIL_sample_status),               (PVOID)HookAIL_sample_status);
    DetourAttach(&(_AIL_start_sample),                (PVOID)HookAIL_start_sample);
    DetourAttach(&(_AIL_end_sample),                  (PVOID)HookAIL_end_sample);
    DetourAttach(&(_AIL_release_sample_handle),       (PVOID)HookAIL_release_sample_handle);
    DetourAttach(&(_AIL_set_sample_volume),           (PVOID)HookAIL_set_sample_volume);
    DetourAttach(&(_AIL_set_sample_pan),              (PVOID)HookAIL_set_sample_pan);
    DetourAttach(&(_AIL_set_sample_playback_rate),    (PVOID)HookAIL_set_sample_playback_rate);
    DetourAttach(&(_AIL_set_sample_loop_count),       (PVOID)HookAIL_set_sample_loop_count);
    DetourAttach(&(_AIL_set_sample_loop_block),       (PVOID)HookAIL_set_sample_loop_block);
    DetourAttach(&(_AIL_open_3D_provider),            (PVOID)HookAIL_open_3D_provider);
    DetourAttach(&(_AIL_close_3D_provider),           (PVOID)HookAIL_close_3D_provider);
    DetourAttach(&(_AIL_enumerate_3D_providers),      (PVOID)HookAIL_enumerate_3D_providers);
    DetourAttach(&(_AIL_3D_provider_attribute),       (PVOID)HookAIL_3D_provider_attribute);
    DetourAttach(&(_AIL_set_3D_provider_preference),  (PVOID)HookAIL_set_3D_provider_preference);
    DetourAttach(&(_AIL_allocate_3D_sample_handle),   (PVOID)HookAIL_allocate_3D_sample_handle);
    DetourAttach(&(_AIL_release_3D_sample_handle),    (PVOID)HookAIL_release_3D_sample_handle);
    DetourAttach(&(_AIL_start_3D_sample),             (PVOID)HookAIL_start_3D_sample);
    DetourAttach(&(_AIL_end_3D_sample),               (PVOID)HookAIL_end_3D_sample);
    DetourAttach(&(_AIL_3D_sample_status),            (PVOID)HookAIL_3D_sample_status);
    DetourAttach(&(_AIL_set_3D_sample_info),          (PVOID)HookAIL_set_3D_sample_info);
    DetourAttach(&(_AIL_set_3D_position),             (PVOID)HookAIL_set_3D_position);
    DetourAttach(&(_AIL_set_3D_sample_volume),        (PVOID)HookAIL_set_3D_sample_volume);
    DetourAttach(&(_AIL_set_3D_sample_loop_count),    (PVOID)HookAIL_set_3D_sample_loop_count);
    DetourAttach(&(_AIL_set_3D_sample_loop_block),    (PVOID)HookAIL_set_3D_sample_loop_block);
    DetourAttach(&(_AIL_set_3D_sample_playback_rate), (PVOID)HookAIL_set_3D_sample_playback_rate);
    DetourAttach(&(_AIL_set_3D_sample_float_distances),(PVOID)HookAIL_set_3D_sample_float_distances);
    DetourAttach(&(_AIL_3D_sample_playback_rate),     (PVOID)HookAIL_3D_sample_playback_rate);

    LONG err = DetourTransactionCommit();
    s_installed = (err == NO_ERROR);
    printf("cMilesWatch: mss32 hooks installed (%ld)\n", err);
    ProbeLog("MilesInstall", err == NO_ERROR ? "ok" : "commit failed");
}