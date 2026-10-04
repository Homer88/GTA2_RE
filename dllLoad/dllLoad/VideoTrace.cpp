#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "detours.h"

static CRITICAL_SECTION g_vtLock;
static int g_vtInit = 0;

#define VT_PATH "C:\\games\\GTA2 _old\\log\\video_trace.log"

void VideoTrace(const char* fmt, ...)
{
    if (!g_vtInit) {
        InitializeCriticalSection(&g_vtLock);
        g_vtInit = 1;
    }

    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    EnterCriticalSection(&g_vtLock);
    FILE* f = fopen(VT_PATH, "ab");
    if (f) {
        SYSTEMTIME st;
        GetLocalTime(&st);
        fprintf(f, "[%02d:%02d:%02d.%03d] %s\r\n",
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, buf);
        fclose(f);
    }
    LeaveCriticalSection(&g_vtLock);
}

typedef LONG (WINAPI* tRegQueryValueExA)(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
typedef int  (WINAPI* tSetWindowLongA)(HWND, int, LONG);
typedef BOOL (WINAPI* tSetWindowPos)(HWND, HWND, int, int, int, int, UINT);
typedef BOOL (WINAPI* tShowWindow)(HWND, int);

static tRegQueryValueExA g_realRegQuery = 0;
static tSetWindowLongA   g_realSetWindowLong = 0;
static tSetWindowPos     g_realSetWindowPos = 0;
static tShowWindow       g_realShowWindow = 0;

static void LogRect(HWND h, const char* tag)
{
    RECT r;
    RECT wr;
    if (!h || !GetWindowRect(h, &r)) {
        VideoTrace("%s hWnd=%p <no window>", tag, h);
        return;
    }
    GetWindowRect(h, &wr);
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    LONG style = GetWindowLongA(h, GWL_STYLE);
    LONG ex = GetWindowLongA(h, GWL_EXSTYLE);
    VideoTrace("%s hWnd=%p pid=%lu vis=%d rect=(%ld,%ld,%ld,%ld) %ldx%ld style=0x%08lX ex=0x%08lX",
        tag, h, (unsigned long)pid, IsWindowVisible(h) ? 1 : 0,
        r.left, r.top, r.right, r.bottom,
        r.right - r.left, r.bottom - r.top,
        (unsigned long)style, (unsigned long)ex);
}

LONG WINAPI VT_RegQueryValueExA(HKEY hKey, LPCSTR name, LPDWORD res, LPDWORD type,
    LPBYTE data, LPDWORD cb)
{
    if (!g_realRegQuery)
        g_realRegQuery = (tRegQueryValueExA)GetProcAddress(GetModuleHandleA("advapi32.dll"), "RegQueryValueExA");

    LONG r = g_realRegQuery(hKey, name, res, type, data, cb);

    DWORD sz = cb ? *cb : 0;
    if (data && sz && sz <= 16) {
        unsigned long v = 0;
        memcpy(&v, data, sz);
        VideoTrace("RegQuery %-18s sz=%lu -> val=%lu (0x%lX)",
            name ? name : "?", (unsigned long)sz, v, v);
    }
    else {
        VideoTrace("RegQuery %-18s sz=%lu", name ? name : "?", (unsigned long)sz);
    }
    return r;
}

int WINAPI VT_SetWindowLongA(HWND h, int i, LONG v)
{
    if (!g_realSetWindowLong)
        g_realSetWindowLong = (tSetWindowLongA)GetProcAddress(GetModuleHandleA("user32.dll"), "SetWindowLongA");

    int prev = g_realSetWindowLong(h, i, v);
    VideoTrace("SetWindowLong hWnd=%p idx=%d val=0x%08lX prev=0x%08lX",
        h, i, (unsigned long)v, (unsigned long)prev);
    return prev;
}

BOOL WINAPI VT_ShowWindow(HWND h, int cmd)
{
    if (!g_realShowWindow)
        g_realShowWindow = (tShowWindow)GetProcAddress(GetModuleHandleA("user32.dll"), "ShowWindow");

    BOOL prev = g_realShowWindow(h, cmd);
    VideoTrace("ShowWindow hWnd=%p cmd=%d -> %d", h, cmd, prev ? 1 : 0);
    LogRect(h, "  win");
    return prev;
}

BOOL WINAPI VT_SetWindowPos(HWND h, HWND after, int x, int y, int cx, int cy, UINT flags)
{
    if (!g_realSetWindowPos)
        g_realSetWindowPos = (tSetWindowPos)GetProcAddress(GetModuleHandleA("user32.dll"), "SetWindowPos");

    BOOL r = g_realSetWindowPos(h, after, x, y, cx, cy, flags);
    VideoTrace("SetWindowPos hWnd=%p (%d,%d) %dx%d flags=0x%X -> %d",
        h, x, y, cx, cy, flags, r ? 1 : 0);
    LogRect(h, "  win");
    return r;
}

void VideoTraceInstall()
{
    HMODULE adv = GetModuleHandleA("advapi32.dll");
    HMODULE usr = GetModuleHandleA("user32.dll");
    if (!adv) adv = LoadLibraryA("advapi32.dll");
    if (!usr) usr = LoadLibraryA("user32.dll");

    if (adv) {
        g_realRegQuery = (tRegQueryValueExA)GetProcAddress(adv, "RegQueryValueExA");
        DetourAttach((PVOID*)&g_realRegQuery, (PVOID)VT_RegQueryValueExA);
    }
    if (usr) {
        g_realSetWindowLong = (tSetWindowLongA)GetProcAddress(usr, "SetWindowLongA");
        DetourAttach((PVOID*)&g_realSetWindowLong, (PVOID)VT_SetWindowLongA);

        g_realShowWindow = (tShowWindow)GetProcAddress(usr, "ShowWindow");
        DetourAttach((PVOID*)&g_realShowWindow, (PVOID)VT_ShowWindow);

        g_realSetWindowPos = (tSetWindowPos)GetProcAddress(usr, "SetWindowPos");
        DetourAttach((PVOID*)&g_realSetWindowPos, (PVOID)VT_SetWindowPos);
    }

    VideoTrace("VideoTraceInstall: detours prepared (adv=%p usr=%p)", adv, usr);
}

// ---- Vid_SetMode interception: windowed stub (-2) ----
typedef int (__stdcall *tVid_SetMode)(void* pVideo, HWND hWnd, int modeId);
static tVid_SetMode g_realVidSetMode = 0;

int __stdcall VT_Vid_SetMode(void* pVideo, HWND hWnd, int modeId)
{
    if (modeId == -2) {
        // dump GLOBAL.txt 10771-10774: window keeps WS_VISIBLE only
        SetWindowLongA(hWnd, -16, 0x10000000);
        SetWindowPos(hWnd, NULL, 0, 0, 0, 0, 0x63b);
        UpdateWindow(hWnd);
        ShowWindow(hWnd, 1);
        LogRect(hWnd, "  WINDOW");
        VideoTrace("Vid_SetMode WINDOWED STUB -2 hWnd=%p -> return 1 (orig skipped)", hWnd);
        return 1;
    }

    if (!g_realVidSetMode) {
        VideoTrace("Vid_SetMode modeId=%d but orig is NULL!", modeId);
        return 1;
    }

    VideoTrace("Vid_SetMode PASSTHRU modeId=%d hWnd=%p pVideo=%p", modeId, hWnd, pVideo);
    int r = g_realVidSetMode(pVideo, hWnd, modeId);
    VideoTrace("Vid_SetMode PASSTHRU modeId=%d -> ret %d", modeId, r);
    return r;
}

// ---- LoadLibraryA trace: see what strings the game really loads ----
typedef HMODULE (WINAPI* tLoadLibraryA)(LPCSTR);
static tLoadLibraryA g_realLoadLibraryA = 0;

HMODULE WINAPI VT_LoadLibraryA(LPCSTR name)
{
    if (!g_realLoadLibraryA)
        g_realLoadLibraryA = (tLoadLibraryA)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    if (!name) {
        VideoTrace("LoadLibraryA(NULL)!");
        return g_realLoadLibraryA ? g_realLoadLibraryA(name) : NULL;
    }

    char buf[300];
    __try {
        strncpy(buf, name, sizeof(buf) - 1);
        buf[sizeof(buf) - 1] = 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        VideoTrace("LoadLibraryA(<bad ptr %p>)", (void*)name);
        return g_realLoadLibraryA ? g_realLoadLibraryA(name) : NULL;
    }

    HMODULE h = g_realLoadLibraryA ? g_realLoadLibraryA(name) : NULL;
    VideoTrace("LoadLibraryA(\"%s\") -> %p", buf, (void*)h);
    return h;
}

// ---- hooks on fixed dump addresses (port keeps original layout) ----
// dump GLOBAL.txt: addr 004031c0 InitDirectX  -> BOOL, no args (DirectInput)
// dump GLOBAL.txt: addr 004cc6d0 ConfigureVideoSystem -> void, no args
typedef int  (__cdecl *tInitDirectX)(void);
typedef void (__cdecl *tConfigureVideoSystem)(void);

static tInitDirectX          g_realInitDirectX = 0;
static tConfigureVideoSystem g_realConfigVideo = 0;

int __cdecl VT_InitDirectX(void)
{
    VideoTrace(">> InitDirectX  @004031C0  ENTER");
    int r = 0;
    if (g_realInitDirectX)
        r = g_realInitDirectX();
    VideoTrace("<< InitDirectX  @004031C0  ret=%d", r);
    return r;
}

void __cdecl VT_ConfigureVideoSystem(void)
{
    VideoTrace(">> ConfigureVideoSystem @004CC6D0 ENTER (fullscreen=%d)",
        (int)GetForegroundWindow() ? 1 : 0);
    if (g_realConfigVideo)
        g_realConfigVideo();
    VideoTrace("<< ConfigureVideoSystem @004CC6D0 EXIT");
}

static DWORD WINAPI VidHookThread(LPVOID)
{
    PVOID initDirectX = (PVOID)0x004031C0;
    PVOID configVideo = (PVOID)0x004CC6D0;

    g_realInitDirectX = (tInitDirectX)initDirectX;
    g_realConfigVideo = (tConfigureVideoSystem)configVideo;
    g_realLoadLibraryA = (tLoadLibraryA)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    Sleep(200);
    DetourUpdateThread(GetCurrentThread());
    if (NO_ERROR == DetourTransactionBegin()) {
        DetourAttach((PVOID*)&g_realInitDirectX, (PVOID)VT_InitDirectX);
        DetourAttach((PVOID*)&g_realConfigVideo, (PVOID)VT_ConfigureVideoSystem);
        DetourAttach((PVOID*)&g_realLoadLibraryA, (PVOID)VT_LoadLibraryA);
        LONG err = DetourTransactionCommit();
        VideoTrace("VidHook: addr-hooks commit err=%ld initReal=%p cfgReal=%p llaReal=%p",
            err, (void*)g_realInitDirectX, (void*)g_realConfigVideo, (void*)g_realLoadLibraryA);
    }
    else {
        VideoTrace("VidHook: addr DetourTransactionBegin failed");
    }
    return 0;
}

void VideoTraceStartVidHook()
{
    // dump first bytes at the retail dump addresses to verify they exist in the port exe
    {
        // .rdata:0056E4B8 - the ddraw driver-name string
        __try {
            char* s = (char*)0x0056E4B8;
            VideoTrace("PROBE rdata 0x0056E4B8 = \"%s\" (len=%d)", s, (int)strlen(s));
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            VideoTrace("PROBE rdata 0x0056E4B8 <unreadable>");
        }

        // driver name globals used by FindGraphiDevace
        const DWORD gs[] = { 0x006732E0, 0x006732E4, 0x006732D8, 0x006732DC };
        for (int i = 0; i < 4; ++i) {
            __try {
                VideoTrace("PROBE global @%08lX = \"%s\"", (unsigned long)gs[i], (char*)gs[i]);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                VideoTrace("PROBE global @%08lX <unreadable>", (unsigned long)gs[i]);
            }
        }
    }

    CreateThread(NULL, 0, VidHookThread, NULL, 0, NULL);
}
