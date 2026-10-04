#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

// minimal DirectDraw decls - avoid ddraw.h SDK issues
typedef struct _MYDDPIXELFORMAT {
    DWORD dwSize, dwFlags;
    DWORD dwFourCC;
    union { DWORD dwRGBBitCount, dwLuminanceBitCount; };
    DWORD dwRBitMask, dwGBitMask, dwBBitMask, dwABitMask;
} MYDDPIXELFORMAT;

typedef struct _MYDDMODEINFO {
    DWORD dmSize, dmDriverExtra, dmFields;
    short dmOrientation, dmPaperSize, dmPaperLength, dmPaperWidth;
    short dmScale, dmCopies, dmDefaultSource, dmPrintQuality;
    short dmColor, dmDuplex, dmYResolution, dmTTOption;
    short dmCollate, dmFormName[32];
    short dmLogPixels;
    DWORD dmBitsPerPel, dmPelsWidth, dmPelsHeight;
    DWORD dmDisplayFlags, dmDisplayFrequency, dmICMMethod, dmICMIntent;
    DWORD dmMediaType, dmDitherType, dmReserved1, dmReserved2;
    DWORD dmPanningWidth, dmPanningHeight;
} MYDDMODEINFO;

typedef HRESULT (CALLBACK *MYENUMMODECB)(MYDDMODEINFO*, LPVOID);
typedef HRESULT (CALLBACK *MYENUMDEVICECB)(LPCSTR, LPVOID, LPVOID, DWORD);

#define DDERR_SUCCESS_        0
#define DDERR_UNSUPPORTED_    0x80004001L
#define DDERR_INVALIDPARAMS_  0x80070057L
#define DDENUM_DONE_          0xFFFFFFFFL

typedef HRESULT (WINAPI *tDDC)(LPCGUID, LPVOID*, IUnknown*);
typedef HRESULT (WINAPI *tDDCL)(LPCGUID, LPVOID*, LPVOID, IUnknown*);

static HMODULE g_real = 0;
static tDDC g_realDDC = 0;
static FILE* g_log = 0;

static void L(const char* fmt, ...)
{
    if (!g_log) {
        g_log = fopen("C:\\games\\GTA2 _old\\log\\shim.log", "ab");
        if (!g_log) return;
    }
    va_list ap; va_start(ap, fmt);
    vfprintf(g_log, fmt, ap);
    va_end(ap);
    fputc('\n', g_log);
    fflush(g_log);
}

static const DWORD s_modes[4][2] = { {640,480}, {800,600}, {1024,768}, {3840,2160} };

// IDirectDraw7 vtable: 46=EnumDisplayModes 12=EnumDisplayDevices
// 25=SetDisplayMode 30=RestoreDisplayMode
static HRESULT STDMETHODCALLTYPE OvEnumDisplayModes(LPVOID self, DWORD flags,
    LPVOID fmt, MYENUMMODECB cb, LPVOID ctx)
{
    L("EnumDisplayModes flags=%08lX", flags);
    int n = 0;
    for (int i = 0; i < 4; ++i) {
        for (int b = 0; b < 2; ++b) {
            MYDDMODEINFO mi; ZeroMemory(&mi, sizeof(mi));
            mi.dmSize = sizeof(mi);
            mi.dmFields = 0x00080000 | 0x00040000 | 0x00080000; // BITSPERPEL|PELSWIDTH|PELSHEIGHT
            mi.dmFields = 0x00000004 | 0x00080000 | 0x00100000; // ORIENTATION|BITSPERPEL|PELSWIDTH
            mi.dmFields = 0x00000001 | 0x00000002 | 0x00000004;  // PELSHEIGHT|PELSWIDTH|BPP
            mi.dmFields = 0x00100000 | 0x00080000 | 0x00040000; // PELSHEIGHT|PELSWIDTH|BITSPERPEL
            mi.dmPelsWidth = s_modes[i][0];
            mi.dmPelsHeight = s_modes[i][1];
            mi.dmBitsPerPel = b ? 16 : 32;
            L("  offer %lux%lux%u", mi.dmPelsWidth, mi.dmPelsHeight, mi.dmBitsPerPel);
            if (cb && cb(&mi, ctx) == DDENUM_DONE_) return DDERR_SUCCESS_;
            n++;
        }
    }
    L("EnumDisplayModes done, offered %d", n);
    return DDERR_SUCCESS_;
}

static HRESULT STDMETHODCALLTYPE OvEnumDisplayDevices(LPVOID self, LPCSTR dev,
    DWORD idx, LPVOID out, LPVOID ctx)
{
    L("EnumDisplayDevices(\"%s\", %lu)", dev ? dev : "(null)", (unsigned long)idx);
    if (idx > 0) return DDERR_INVALIDPARAMS_;
    if (out) {
        BYTE* p = (BYTE*)out;
        ZeroMemory(p, 220);
        const char* d = "Microsoft Remote Display Adapter";
        const char* n = "RemoteDisplay";
        const char* dr = "remotedisplay.dll";
        for (int i = 0; i < 64; ++i) { p[i] = d[i]; if (!d[i]) break; }
        for (int i = 0; i < 32; ++i) { p[64+i] = n[i]; if (!n[i]) break; }
        for (int i = 0; i < 32; ++i) { p[96+i] = dr[i]; if (!dr[i]) break; }
    }
    return DDERR_SUCCESS_;
}

static HRESULT STDMETHODCALLTYPE OvSetDisplayMode(LPVOID self, LPVOID mi, DWORD flags)
{
    MYDDMODEINFO* m = (MYDDMODEINFO*)mi;
    L("SetDisplayMode %lux%lux%u flags=%08lX -> NOOP",
        m ? m->dmPelsWidth : 0, m ? m->dmPelsHeight : 0, m ? m->dmBitsPerPel : 0, flags);
    return DDERR_SUCCESS_;
}

static HRESULT STDMETHODCALLTYPE OvRestoreDisplayMode(LPVOID self, DWORD flags)
{
    L("RestoreDisplayMode -> NOOP");
    return DDERR_SUCCESS_;
}

static void Patch(LPVOID obj, int em, int ed, int sm, int rm)
{
    void** vt = *(void***)obj;
    if (em >= 0) vt[em] = (void*)OvEnumDisplayModes;
    if (ed >= 0) vt[ed] = (void*)OvEnumDisplayDevices;
    if (sm >= 0) vt[sm] = (void*)OvSetDisplayMode;
    if (rm >= 0) vt[rm] = (void*)OvRestoreDisplayMode;
    L("patched obj=%p enumModes=%d enumDev=%d setMode=%d restore=%d", obj, em, ed, sm, rm);
}

__declspec(dllexport) HRESULT WINAPI DirectDrawCreate(LPCGUID clsid, LPVOID* out, IUnknown* unk)
{
    if (!g_realDDC) {
        char p[MAX_PATH];
        GetSystemDirectoryA(p, MAX_PATH);
        lstrcatA(p, "\\ddraw.dll");
        g_real = LoadLibraryA(p);
        if (!g_real) g_real = LoadLibraryW(L"ddraw.dll");
        g_realDDC = g_real ? (tDDC)GetProcAddress(g_real, "DirectDrawCreate") : 0;
        L("shim init real=%p DDC=%p", g_real, g_realDDC);
    }
    if (!g_realDDC) return DDERR_UNSUPPORTED_;

    HRESULT hr = g_realDDC(clsid, out, unk);
    L("DirectDrawCreate hr=%08lX out=%p", hr, out ? *out : 0);
    if (!out || !*out) return hr;

    Patch(*out, 46, 12, 25, 30);
    return hr;
}

__declspec(dllexport) HRESULT WINAPI DirectDrawCreateEx(LPCGUID clsid, LPVOID* out,
    LPVOID outer, IUnknown* unk)
{
    if (!g_real) DirectDrawCreate(0, 0, 0);
    tDDCL f = g_real ? (tDDCL)GetProcAddress(g_real, "DirectDrawCreateEx") : 0;
    L("DirectDrawCreateEx -> real");
    return f ? f(clsid, out, outer, unk) : DDERR_UNSUPPORTED_;
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD r, LPVOID v)
{
    if (r == DLL_PROCESS_ATTACH) L("=== ddraw shim attached ===");
    return TRUE;
}
