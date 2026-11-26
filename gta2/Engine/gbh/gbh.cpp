#include "gbh.h"

#include <windows.h>

static const char* g_gbhLastError = "not-initialized";

const char* Gbh_GetLastError() { return g_gbhLastError ? g_gbhLastError : "unknown"; }

static FARPROC Gbh_GetProc(HMODULE m, const char* name) {
    FARPROC p = GetProcAddress(m, name);
    return p;
}

GbhApi Gbh_TryGetLoadedApi() {
    GbhApi api;
    g_gbhLastError = "module-not-loaded";

    // Do not call LoadLibrary: debug-only observation of already loaded GBH module.
    HMODULE m = GetModuleHandleA("D3DDLL.dll");
    if (!m) m = GetModuleHandleA("d3ddll.dll");
    if (!m) m = GetModuleHandleA("3DFX.DLL");
    if (!m) m = GetModuleHandleA("3dfx.dll");
    if (!m) return api;

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
    g_gbhLastError = "ok";
    return api;
}
