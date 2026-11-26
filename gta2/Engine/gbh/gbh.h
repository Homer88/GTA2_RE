#pragma once

#include <cstdint>

// Guarded gbh contract derived from D3DDLL.dll dumpbin exports and IDA callsites.
// DO NOT use in default runtime path until Texture/Vert layout, ABI/linkage,
// and TextureManager handle pipeline are confirmed.
//
// dumpbin (D3DDLL.dll) and d3ddll/d3ddll.h/.cpp are authoritative for signatures:
// - gbh_DrawQuad        @@YGXHPAUTexture@@PAUVert@@H@Z  -> void __stdcall(int, Texture*, Vert*, int)
// - gbh_RegisterTexture @@YGPAUTexture@@FFPAEHD@Z      -> Texture* __stdcall(short, short, unsigned char*, int, char)
// - gbh_RegisterPalette @@YGIHPAK@Z                    -> unsigned int __stdcall(int, unsigned long*)
// - gbh_LockTexture     @@YGPAUTexture@@PAU1@Z         -> Texture* __stdcall(Texture*)
// - gbh_UnlockTexture   @@YGPAUTexture@@PAU1@Z         -> Texture* __stdcall(Texture*)
// - gbh_AssignPalette   @@YGDPAUTexture@@H@Z           -> char __stdcall(Texture*, int)
// - gbh_SetAmbient      @@YGXM@Z                       -> void __stdcall(float)
//
// IDA decomp sometimes shows fewer args (decompiler artifact), e.g. RegisterPalette(v5,v3++,ColourBank)
// or RegisterTexture(w,h,data). Trust d3ddll.h/cpp + dumpbin.
// IDA callsites:
// - DrawGTATextRaw @ 0x4CC100: gbh_DrawQuad(v24.Ped, Filed_14, &flt_6733F0, 255)
// - TextureManager::Load @ 0x4C30A0: RegisterPalette/RegisterTexture(...), RegisterTexture(128,128,0,?,?)
// - TextureManager::GetTextureValue @ 0x4C2BC0: LockTexture; mutate texture fields; UnlockTexture

struct gbh_Texture; // opaque until confirmed
struct gbh_Vert;    // opaque until confirmed

// Vert layout evidence (IDA 0x4CC100/0x4CBDB0 etc): 4 verts, stride 0x20 (8 dwords).
// Offsets: +00 x, +04 y, +08 z(953267991=0x38D1B717), +0C w?, +10 diff(argb, written by Lighting::SetPaletteMode),
//          +14 spec?, +18 u, +1C v. Matches d3ddll.h Vert {float x,y,z,w; DWORD diff,spec; float u,v;} = 32 bytes.
// Still TODO: confirm w/spec usage and runtime ABI on real D3DDLL.dll before any draw call.
struct gbh_VertRaw {
    float x, y, z, w;
    std::uint32_t diff;
    std::uint32_t spec;
    float u, v;
};
static_assert(sizeof(gbh_VertRaw) == 32, "gbh_VertRaw stride");

using gbh_DrawQuad_t = void(__stdcall*)(int flags, gbh_Texture* tex, gbh_Vert* verts, int count);
using gbh_RegisterTexture_t = gbh_Texture*(__stdcall*)(short w, short h, unsigned char* data, int a4, char a5);
using gbh_RegisterPalette_t = unsigned int(__stdcall*)(int a1, unsigned long* palette);
using gbh_LockTexture_t = gbh_Texture*(__stdcall*)(gbh_Texture* tex);
using gbh_UnlockTexture_t = gbh_Texture*(__stdcall*)(gbh_Texture* tex);
using gbh_AssignPalette_t = char(__stdcall*)(gbh_Texture* tex, int pal);
using gbh_SetAmbient_t = void(__stdcall*)(float v);

struct GbhApi {
    gbh_DrawQuad_t DrawQuad = nullptr;
    gbh_RegisterTexture_t RegisterTexture = nullptr;
    gbh_RegisterPalette_t RegisterPalette = nullptr;
    gbh_LockTexture_t LockTexture = nullptr;
    gbh_UnlockTexture_t UnlockTexture = nullptr;
    gbh_AssignPalette_t AssignPalette = nullptr;
    gbh_SetAmbient_t SetAmbient = nullptr;
    bool loaded = false;
};

// Debug-only: resolves from an already loaded module (e.g. D3DDLL.dll). No LoadLibrary.
GbhApi Gbh_TryGetLoadedApi();
const char* Gbh_GetLastError();
