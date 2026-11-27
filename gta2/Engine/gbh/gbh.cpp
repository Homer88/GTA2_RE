#include "gbh.h"

#include <windows.h>
#include <cstdlib>
#include <cstring>

static const char* g_gbhLastError = "not-initialized";
static char g_gbhModulePath[MAX_PATH] = "";

const char* Gbh_GetLastError() { return g_gbhLastError ? g_gbhLastError : "unknown"; }
const char* Gbh_GetModulePath() { return g_gbhModulePath[0] ? g_gbhModulePath : "none"; }

static FARPROC Gbh_GetProc(HMODULE m, const char* name) {
    FARPROC p = GetProcAddress(m, name);
    return p;
}

#if defined(GTA2_TEXT_GBH_LINK_STATIC)
// Static-linked D3DDLL.lib symbols. Only enable when GTA2 links D3DDLL.lib.
// C++ linkage + Texture/Vert names match MSVC mangling in D3DDLL.lib.
struct Texture;
struct Vert;
extern void __stdcall gbh_DrawQuad(int flags, Texture* tex, Vert* verts, int count);
extern Texture* __stdcall gbh_RegisterTexture(short w, short h, unsigned char* data, int a4, char a5);
extern unsigned int __stdcall gbh_RegisterPalette(int palId, unsigned long* pData);
extern Texture* __stdcall gbh_LockTexture(Texture* tex);
extern Texture* __stdcall gbh_UnlockTexture(Texture* tex);
extern char __stdcall gbh_AssignPalette(Texture* tex, int palId);
extern void __stdcall gbh_SetAmbient(float a1);
#endif

GbhApi Gbh_TryGetLoadedApi() {
    GbhApi api;
    g_gbhLastError = "module-not-loaded";

    // Explicit debug override: prefer static-linked D3DDLL.lib symbols for single-state smoke.
    // Only when GTA2_TEXT_GBH_STATIC=1 and compiled with GTA2_TEXT_GBH_LINK_STATIC.
    const char* staticEnv = std::getenv("GTA2_TEXT_GBH_STATIC");
    if (staticEnv && staticEnv[0] == '1') {
#if defined(GTA2_TEXT_GBH_LINK_STATIC)
        api.DrawQuad = reinterpret_cast<gbh_DrawQuad_t>(&::gbh_DrawQuad);
        api.RegisterTexture = reinterpret_cast<gbh_RegisterTexture_t>(&::gbh_RegisterTexture);
        api.RegisterPalette = reinterpret_cast<gbh_RegisterPalette_t>(&::gbh_RegisterPalette);
        api.LockTexture = reinterpret_cast<gbh_LockTexture_t>(&::gbh_LockTexture);
        api.UnlockTexture = reinterpret_cast<gbh_UnlockTexture_t>(&::gbh_UnlockTexture);
        api.AssignPalette = reinterpret_cast<gbh_AssignPalette_t>(&::gbh_AssignPalette);
        api.SetAmbient = reinterpret_cast<gbh_SetAmbient_t>(&::gbh_SetAmbient);
        if (!api.DrawQuad || !api.RegisterTexture || !api.RegisterPalette || !api.LockTexture || !api.UnlockTexture) {
            g_gbhLastError = "missing-static-export";
            return api;
        }
        api.loaded = true;
        g_gbhLastError = "ok-static";
        std::strcpy(g_gbhModulePath, "static:D3DDLL.lib");
        return api;
#else
        g_gbhLastError = "static-not-linked";
        g_gbhModulePath[0] = 0;
        return api;
#endif
    }

    // Default: do not call LoadLibrary. Observe already loaded GBH module.
    HMODULE m = GetModuleHandleA("D3DDLL.dll");
    if (!m) m = GetModuleHandleA("d3ddll.dll");
    if (!m) m = GetModuleHandleA("3DFX.DLL");
    if (!m) m = GetModuleHandleA("3dfx.dll");
    if (m) {
        DWORD n = GetModuleFileNameA(m, g_gbhModulePath, (DWORD)sizeof(g_gbhModulePath));
        if (n == 0 || n >= sizeof(g_gbhModulePath)) g_gbhModulePath[0] = 0;
        api.DrawQuad = reinterpret_cast<gbh_DrawQuad_t>(Gbh_GetProc(m, "gbh_DrawQuad"));
        api.RegisterTexture = reinterpret_cast<gbh_RegisterTexture_t>(Gbh_GetProc(m, "gbh_RegisterTexture"));
        api.RegisterPalette = reinterpret_cast<gbh_RegisterPalette_t>(Gbh_GetProc(m, "gbh_RegisterPalette"));
        api.LockTexture = reinterpret_cast<gbh_LockTexture_t>(Gbh_GetProc(m, "gbh_LockTexture"));
        api.UnlockTexture = reinterpret_cast<gbh_UnlockTexture_t>(Gbh_GetProc(m, "gbh_UnlockTexture"));
        api.AssignPalette = reinterpret_cast<gbh_AssignPalette_t>(Gbh_GetProc(m, "gbh_AssignPalette"));
        api.SetAmbient = reinterpret_cast<gbh_SetAmbient_t>(Gbh_GetProc(m, "gbh_SetAmbient"));
        if (!api.DrawQuad || !api.RegisterTexture || !api.RegisterPalette || !api.LockTexture || !api.UnlockTexture) {
            g_gbhLastError = "missing-required-export";
            return api;
        }
        api.loaded = true;
        g_gbhLastError = "ok-module";
        return api;
    }

    g_gbhModulePath[0] = 0;

    // Legacy guarded fallback: LoadLibraryA. CAUTION: dual GBH state with static-linked lib.
    const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
    if (drawEnv && drawEnv[0] == '1') {
        static bool triedLoad = false;
        static HMODULE loaded = nullptr;
        if (!triedLoad) {
            triedLoad = true;
            loaded = LoadLibraryA("D3DDLL.dll");
            if (!loaded) loaded = LoadLibraryA("d3ddll.dll");
            if (!loaded) loaded = LoadLibraryA("3DFX.DLL");
            if (!loaded) loaded = LoadLibraryA("3dfx.dll");
        }
        m = loaded;
        if (m) {
            DWORD n = GetModuleFileNameA(m, g_gbhModulePath, (DWORD)sizeof(g_gbhModulePath));
            if (n == 0 || n >= sizeof(g_gbhModulePath)) g_gbhModulePath[0] = 0;
            api.DrawQuad = reinterpret_cast<gbh_DrawQuad_t>(Gbh_GetProc(m, "gbh_DrawQuad"));
            api.RegisterTexture = reinterpret_cast<gbh_RegisterTexture_t>(Gbh_GetProc(m, "gbh_RegisterTexture"));
            api.RegisterPalette = reinterpret_cast<gbh_RegisterPalette_t>(Gbh_GetProc(m, "gbh_RegisterPalette"));
            api.LockTexture = reinterpret_cast<gbh_LockTexture_t>(Gbh_GetProc(m, "gbh_LockTexture"));
            api.UnlockTexture = reinterpret_cast<gbh_UnlockTexture_t>(Gbh_GetProc(m, "gbh_UnlockTexture"));
            api.AssignPalette = reinterpret_cast<gbh_AssignPalette_t>(Gbh_GetProc(m, "gbh_AssignPalette"));
            api.SetAmbient = reinterpret_cast<gbh_SetAmbient_t>(Gbh_GetProc(m, "gbh_SetAmbient"));
            if (!api.DrawQuad || !api.RegisterTexture || !api.RegisterPalette || !api.LockTexture || !api.UnlockTexture) {
                g_gbhLastError = "missing-required-export";
                return api;
            }
            api.loaded = true;
            g_gbhLastError = "ok-debug-loadlibrary";
            return api;
        }
    }

    return api;
}
