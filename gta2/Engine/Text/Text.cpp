#include "Text.h"
#include "../Registry/Registry.h"
#include <cstring>
#include <cstdlib>
#include <search.h>
#include <stdio.h>
#include "../Style/Style.h"
#include "../Style/StyleTileLoader.h"
#include "../TextureManager/TextureManager.h"
#include "../Font/Font.h"
#include "../gbh/gbh.h"
#include "../../../d3ddll/d3ddll.h"
#include "../ultil/WinApi.h"
#include <map>
#include <vector>

Text *gText;
char PartGxt[255];
wchar_t gFontJapan[256] = { 0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,  0x88, 0x89, 0x8A,
                            0x8B,  0x8C,  0x8D,  0x8E,  0x8F,  0x90,  0x91,  0x92,  0x93, 0x94, 0x95,
                            0x96,  0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87, 0x88, 0x89,
                            0x8A,  0x8B,  0x8C,  0x8D,  0x8E,  0x8F,  0x90,  0x91,  0x92, 0x93, 0x94,
                            0x95,  0x0AD, 0x0AF, 0x0B0, 0x0B1, 0x0B2, 0x0B3, 0x0B4,
                            0x0B5, 0x0B6, 0x0B7, 0x0B8, 0x0B9, 0x0BA, 0x0BB, 0x0BC, 0x0BD,
                            0x0BE, 0x0BF, 0x0C0, 0x0C1, 0x0C2, 0x0C3, 0x0C4, 0x0C5, 0x0C6,
                            0x0C7, 0x0C8, 0x0C9, 0x0CA, 0x0CB, 0x0CC, 0x0CD, 0x0CE, 0x0CF,
                            0x0D0, 0x0D1, 0x0D2, 0x0D3, 0x0D4, 0x0D5, 0x0D6, 0x0D7, 0x0D8,
                            0x0D9, 0x0DA, 0x0DB, 0x0DC, 0x0DD, 0x0DE, 0x0DF, 0x0E0, 0x0E1,
                            0x0E2, 0x0E3, 0x0E4, 0x0E5, 0x0E6, 0x0E7, 0x0E8, 0x0E9, 0x0EA,
                            0x0EB, 0x0EC, 0x0ED, 0x0EE, 0x0EF, 0x0F0, 0x0F1, 0x0F2, 0x0F3,
                            0x0F4, 0x0F5, 0x0F6, 0x0F7, 0x0F8, 0x0F9, 0x0FA, 0x0FB, 0x0FC,
                            0x0FD, 0x0FE, 0x0FF, 0x80,  0x81,  0x82,  0x83,  0x84,  0x85, 0x86,
                            0x87,  0x88,  0x89,  0x8A,  0x8B,  0x8C,  0x8D,  0x8E,  0x8F, 0x90, 0x91,
                            0x92,  0x93,  0x94,  0x95,  0x96,  0x41,  0x84,  0x85,  0x45,
                            0x49,  0x4F,  0x55,  0x0AD, 0x0AF,
                            0x0B0, 0x0B1, 0x0B2, 0x0B3, 0x0B4, 0x0B5, 0x0B6, 0x0B7, 0x0B8,
                            0x0B9, 0x0BA, 0x0BB, 0x0BC, 0x0BD, 0x0BE, 0x0BF, 0x0C0, 0x0C1,
                            0x0C2, 0x0C3, 0x0C4, 0x0C5, 0x0C6, 0x0C7, 0x0C8, 0x0C9, 0x0CA,
                            0x0CB, 0x0CC, 0x0CD, 0x0CE, 0x0CF, 0x0D0, 0x0D1, 0x0D2, 0x0D3,
                            0x0D4, 0x0D5, 0x0D6, 0x0D7, 0x0D8, 0x0D9, 0x0DA, 0x0DB, 0x0DC,
                            0x0DD, 0x0DE, 0x0DF, 0x0E0, 0x0E1, 0x0E2, 0x0E3, 0x0E4, 0x0E5,
                            0x0E6, 0x0E7, 0x0E8, 0x0E9, 0x0EA, 0x0EB, 0x0EC, 0x0ED, 0x0EE,
                            0x0EF, 0x0F0, 0x0F1, 0x0F2, 0x0F3, 0x0F4, 0x0F5, 0x0F6, 0x0F7,
                            0x0F8, 0x0F9, 0x0FA, 0x0FB, 0x0FC, 0x0FD, 0x0FE, 0x0FF               };
wchar_t gFontEnglish[256] = { 0 };



int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void Text::Load() {
    sprintf(PartGxt, "data\\%c.gxt", this->Language);
    this->LoadGCI();
}
void Text::LoadGCI() {

}
void* Text::Bsearch(const void* pKey) {
    wchar_t ** resultat=(wchar_t**)bsearch(pKey, (const char*)this->Base, this->NumberOfElements, 12, compare_strings);
    if (resultat) {
        return resultat;
    }
    else { return " "; }
}
void Text::Clear() {
    this->Base = 0;
    this->NumberOfElements = 0;
}

Text::Text() {
    this->Clear();                       // Base = NULL; Num = 0;
    //AutoClass4::AutoClass4(&this->AutoClass4); //TODO

    gRegistry->GetLanguage("language", gLanguage, 256);

    char lang = (char)gLanguage[0];
    if (lang == 'e' || lang == 'f' || lang == 'g' ||
        lang == 'i' || lang == 's' || lang== 'r' || lang == 'j')
    {
        this->Language = lang;
    }
    else
    {
        this->Language = 'e';                // по умолчанию — английский
    }




    /*
    char gLanguage[256];
    gRegistry->GetLanguage("language", gLanguage, 256);
    if (gLanguage[0] == 'e' ||
        gLanguage[0] == 'f' ||
        gLanguage[0] == 'g' ||
        gLanguage[0] == 'i' ||
        gLanguage[0] == 's' ||
        gLanguage[0] == 'j' ||
        gLanguage[0] == 'r')
        this->Language = gLanguage[0];
    else
        this->Language = 'e';*/
}

Text::~Text() {

}


wchar_t* Text::ConvertWordsToBig(wchar_t* str) {
    for (wchar_t* i = str; *i; ++i) {
        *i = this->ConvertToUpper(*i);
    }
    return L" ";
}


wchar_t Text::ConvertToUpper(wchar_t str) {

    switch (this->Language) {
    case 'e':
        if (str >= 'a' && str <= 'z')
            str=str - 32;
        break;
    case 'f':
        if (str >= 'a' && str <= 'z')
            str = str - 32;
        else  if (str >= 128 && str <= 255)
            str = gFontJapan[str];
        break;
    case 'g':
    case 'i':
    case 's':
        if (str >= 'a' && str <= 'z')
            str = str - 32;
        else if (str >= 128 && str <= 255)
            str = gFontEnglish[str];
        break;
    case 'r':
        if (str >= 'a' && str <= 'z')
            str = str - 32;
        if (str >= 'а' && str <= 'п')
            str = str - 32;
        if (str >= 'р' && str <= 'я')
            str = str - 80;
        if (str >= 'ё' )
            str = 'Ё';
         break;
    default:
        return str;
    }
    return str;
}


bool  Text::LanguageJapan() {
    return false;
}

DebugTextCmd gDebugTextCmds[kMaxDebugTextCmds];
int gDebugTextCmdCount = 0;

void ClearDebugTextCmds() { gDebugTextCmdCount = 0; }

static void AddDebugTextCmd(const char* t, int x, int y, unsigned short color, int style) {
    if (!t || gDebugTextCmdCount >= kMaxDebugTextCmds) return;
    DebugTextCmd& c = gDebugTextCmds[gDebugTextCmdCount++];
    snprintf(c.text, sizeof(c.text), "%s", t);
    c.text[sizeof(c.text)-1] = 0;
    c.x = x; c.y = y; c.color = color; c.style = style;
}

// IDA 0x4CC100 - gbh glyph-quad path. RE: guarded ASCII attempt + software overlay fallback.
// Real path requires confirmed Style layout/TextureManager banks/Float10/Radar/AddX globals.
static const char* gTextGbhBlocked = "init";
const char* Text_GetGbhBlockedReason() { return gTextGbhBlocked ? gTextGbhBlocked : "unknown"; }

static bool Text_ProbeGbhAsciiChain(wchar_t* a1, unsigned short styleId, int* outOk, int* outTotal) {
    // Debug-only probe for IDA 0x4CC100 ASCII non-kanji glyph chain.
    // Does NOT call gbh_DrawQuad. Requires Style+TextureManager idaViews.
    if (outOk) *outOk = 0;
    if (outTotal) *outTotal = 0;
    if (!a1 || !gStyle || !gTextureManager) return false;
    if (!gStyle->GetIdaView() || !gTextureManager->GetIdaView()) return false;
    int ok = 0, total = 0;
    for (int i = 0; a1[i] && total < 32; ++i) {
        wchar_t wc = a1[i];
        if (wc == L'\n' || wc == L' ' || wc == L'#') continue;
        if (wc < 33 || wc > 126) continue; // non-ASCII/non-kanji subset only
        ++total;
        unsigned short ch = (unsigned short)(wc - 33);
        short spriteId = gStyle->GetSpriteID(styleId, (short)ch);
        unsigned short base = gStyle->GetBaseIndex(7, spriteId);
        int spr = gStyle->GetSprite(base);
        int tex = gTextureManager->GetTexture(7, spriteId, 7, 0);
        if (spr != 0 && tex != 0) ++ok;
    }
    if (outOk) *outOk = ok;
    if (outTotal) *outTotal = total;
    return total > 0 && ok == total;
}

struct GbhFontTexCache {
    bool inited = false;
    bool failed = false;
    GbhApi api;
    std::map<unsigned int, gbh_Texture*> texBySprite; // key: sprite base index
};

static GbhFontTexCache& Text_GetGbhFontCache() {
    static GbhFontTexCache c;
    return c;
}

static int Text_SetPaletteModeDebug(unsigned char a1, int a2) {
    // IDA 0x4CB050 (Lighting::SetPaletteMode). Guarded debug implementation for GTA2_TEXT_GBH_DRAW.
    // Writes diff into glyph vert globals in original; here returns diff+flags for caller.
    (void)a1;
    extern int gTimeDayAndNight;
    if (a2 == 0) return gTimeDayAndNight | 0x80;
    if (a2 == 1) return gTimeDayAndNight | 8576;
    if (a2 == 2) return gTimeDayAndNight | 8832;
    return 0;
}

static int Text_GbhRegisterPhysPaletteDebug(GbhApi& api, unsigned int physIdx) {
    // Debug-only. IDA: TextureManagerRegisterPalitre registers ColourBank per physical palette;
    // gbh_RegisterPalette(palId, pData) reads/writes 256 entries at stride 64 DWORDs and MUTATES buffer.
    // StyleTiles_GetPhysPalette returns pageBase+inPage*4 pointer matching PPAL strided layout.
    static int s_slotByPhys[4096];
    static bool s_slotInit = false;
    static int s_nextSlot = 900; // reserved high slots, avoid colliding with game low slots
    if (!s_slotInit) { for (int i = 0; i < 4096; ++i) s_slotByPhys[i] = -1; s_slotInit = true; }
    if (physIdx >= 4096u) return -1;
    if (s_slotByPhys[physIdx] >= 0) return s_slotByPhys[physIdx];
    if (s_nextSlot > 1023) { gTextGbhBlocked = "gbh-pal-slots-exhausted"; return -1; }
    const StyleTileAssets* sta = StyleTiles_Get();
    if (!sta || !sta->loaded) { gTextGbhBlocked = "gbh-pal-no-style"; return -1; }

    const unsigned char* palPtr = StyleTiles_GetPhysPalette(physIdx);
    if (!palPtr) { gTextGbhBlocked = "gbh-pal-ptr-miss"; return -1; }
    // Copy strided column: 256 colors * 64 DWORD stride = 64KB window. RegisterPalette mutates it.
    std::vector<unsigned long> buf(256u * 64u, 0);
    for (int i = 0; i < 256; ++i) {
        // StyleTiles_GetPhysPalette returns base at color0 for this palette; color i is +i*64*4.
        const unsigned char* src = palPtr + (size_t)i * 64u * 4u;
        // Bounds: palPtr is inside ppal page; ensure within ppalBytes.
        size_t off = (size_t)(src - sta->ppal);
        if (off + 4u <= sta->ppalBytes) {
            std::memcpy(&buf[(size_t)i * 64u], src, 4u);
        }
    }
    if (!api.RegisterPalette) return -1;
    int slot = s_nextSlot++;
    api.RegisterPalette(slot, &buf[0]);
    s_slotByPhys[physIdx] = slot;
    return slot;
}

static gbh_Texture* Text_GetOrCreateGbhFontTexture(unsigned short fontStyle, unsigned short glyphCharMinus33) {
    // Debug-only, GTA2_TEXT_GBH_DRAW=1 path only. Creates real gbh_Texture* via gbh_RegisterTexture.
    // Bypasses full TextureManager/PacketInfo/S89 pipeline; narrow ASCII probe only.
    GbhFontTexCache& c = Text_GetGbhFontCache();
    if (c.failed) return nullptr;
    if (!c.inited) {
        c.inited = true;
        c.api = Gbh_TryGetLoadedApi();
        if (!c.api.loaded || !c.api.RegisterTexture) { c.failed = true; return nullptr; }
    }
    if (!gStyle) return nullptr;
    short spriteId = gStyle->GetSpriteID(fontStyle, (short)glyphCharMinus33);
    unsigned short base = gStyle->GetBaseIndex(7, spriteId);
    if (base == 0) return nullptr;
    auto it = c.texBySprite.find(base);
    if (it != c.texBySprite.end()) return it->second;

    int spr = gStyle->GetSprite(base);
    if (spr == 0) return nullptr;
    unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
    unsigned char w = sp[4];
    unsigned char h = sp[5];
    unsigned char* data = reinterpret_cast<unsigned char*>(*reinterpret_cast<unsigned int*>(sp + 0)); // IDA: *(_DWORD*)Sprite
    if (!data || w == 0 || h == 0) return nullptr;

    // IDA PacketInfo::LoadPalettedTextures for font bank 7 (Setup 6,7): uses get_global_palette_id(gStyle, field_C==7, v5)
    // then GetPhysPalette. For glyph probe, palette index semantics not fully confirmed; try global palette id 0 as safe debug.
    // TODO: confirm exact palette from Style field_C/field_18 and glyph remap.
    unsigned short globalPal = (unsigned short)gStyle->get_global_palette_id(7, 0);
    short physPal = gStyle->GetPhysPalette(globalPal);
    int palSlot = Text_GbhRegisterPhysPaletteDebug(c.api, (unsigned int)(unsigned short)physPal);
    if (palSlot < 0) { if (gTextGbhBlocked[0] == 0) gTextGbhBlocked = "gbh-pal-reg-fail"; return nullptr; }

    gbh_Texture* tex = c.api.RegisterTexture((short)w, (short)h, data, palSlot, 0);
    if (!tex) { gTextGbhBlocked = "gbh-regtex-null"; return nullptr; }
    c.texBySprite[base] = tex;
    return tex;
}

static bool Text_TryDrawGbhAscii(wchar_t* a1, int arg4, int arg8, unsigned short a4, int /*a5*/) {
    // Narrow guarded ASCII non-kanji subset of IDA 0x4CC100. NOT wired into default path.
    // Hard gates: GTA2_TEXT_GBH_DRAW=1, gbh exports loaded, Style+TM idaViews bound, real Texture* handles.
    // Missing/unconfirmed: Lighting::SetPaletteMode, SpriteS1::SetCarSpriteTransform, Radar/Point2D/Float10/AddX,
    // SetShiftedFlag, glyph vert globals/ownership, kanji/FileMgr, draw flags, full TM/PacketInfo semantics.
    // Uses screen-space quad approximation (NOT IDA transform). Any doubt => false.
    const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
    if (!drawEnv || drawEnv[0] != '1') return false;
    if (!a1 || !gStyle || !gTextureManager) return false;
    if (!gStyle->GetIdaView() || !gTextureManager->GetIdaView()) return false;
    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.DrawQuad) { gTextGbhBlocked = "gbh-api-miss"; return false; }

    union { std::uint32_t u; float f; } zbits; zbits.u = 953267991u;
    int x = arg4;
    int y = arg8;
    bool drewAny = false;
    gbh_VertRaw verts[4];

    for (int i = 0; a1[i]; ++i) {
        wchar_t wc = a1[i];
        if (wc == L'\n') { y += 16; x = arg4; continue; }
        if (wc == L'#') { continue; }
        if (wc == L' ') { x += 8; continue; }
        if (wc < 33 || wc > 126) { x += 8; continue; }

        unsigned short ch = (unsigned short)(wc - 33);
        short spriteId = gStyle->GetSpriteID(a4, (short)ch);
        unsigned short base = gStyle->GetBaseIndex(7, spriteId);
        int spr = gStyle->GetSprite(base);
        if (spr == 0) { gTextGbhBlocked = "glyph-sprite-miss"; return false; }
        // Prefer TM debug path for real gbh_Texture* (bank 7 only). Falls back to local probe cache.
    gbh_Texture* tex = (gbh_Texture*)(uintptr_t)GetTexture(gTextureManager, 7, spriteId, 7, 0);
    if (!tex) tex = Text_GetOrCreateGbhFontTexture(a4, ch);
    if (!tex) { if (gTextGbhBlocked[0] == 0) gTextGbhBlocked = "gbh-tex-miss"; return false; }

        unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
        float w = (float)(sp[4] ? sp[4] : 8);
        float h = (float)(sp[5] ? sp[5] : 8);
        float uMax = w - 0.000099999997f;
        float vMax = h - 0.000099999997f;
        // IDA 0x4CB050: sets vert diff to (a1<<27)|0xFFFFFF for modes 1/2; returns gTimeDayAndNight|flags.
        // We don't have glyph vert globals; apply diff directly and use flags in DrawQuad.
        int palMode = 1; // debug guess; TODO derive from text kind/color mode
        int modeFlags = Text_SetPaletteModeDebug(0, palMode);
        std::uint32_t diff = 0x00FFFFFFu;
        float fx = (float)x, fy = (float)y;

        verts[0] = {fx, fy, zbits.f, 1.0f, diff, 0, 0.0f, 0.0f};
        verts[1] = {fx + w, fy, zbits.f, 1.0f, diff, 0, uMax, 0.0f};
        verts[2] = {fx + w, fy + h, zbits.f, 1.0f, diff, 0, uMax, vMax};
        verts[3] = {fx, fy + h, zbits.f, 1.0f, diff, 0, 0.0f, vMax};

        // IDA: gbh_DrawQuad(v24.Ped | 0x20000, Filed_14, &flt_6733F0, 255)
        // SAFETY: real gbh_Texture* from gbh_RegisterTexture, palette registered in reserved slot copy.
        // Still unconfirmed: font palette selection, transform/flags/diff/w/spec, TM/PacketInfo semantics.
        // Only call gbh_DrawQuad with explicit GTA2_TEXT_GBH_DRAW_FORCE=1.
        int drawFlags = (modeFlags | 0x20000);
        const char* forceDraw = std::getenv("GTA2_TEXT_GBH_DRAW_FORCE");
        if (!forceDraw || forceDraw[0] != '1') {
            gTextGbhBlocked = "gbh-tex-ok-draw-blocked-safety";
            return false;
        }
        gTextGbhBlocked = "gbh-draw-calling";
        api.DrawQuad(drawFlags, tex, reinterpret_cast<gbh_Vert*>(verts), 255);
        drewAny = true;
        x += (int)w;
        if (x > 2000) break;
    }
    if (drewAny) gTextGbhBlocked = "gbh-draw-attempted";
    return drewAny;
}

void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5) {
    if (!a1) return;
    // IDA 0x4CC100 signature in decompile is deceptive: extra stack args (a5_4/a5_8/a5_12) used.
    // RE keeps 5-arg bridge; gbh path enabled only when we can prove safe ASCII non-kanji subset.
    // Dependencies still unconfirmed: Style field_14/20/Car, TextureManager S89/PacketInfo, Lighting,
    // SpriteS1/Point2D/Radar/Float10/AddX, glyph verts, FileMgr kanji. Fallback to overlay.
    if (gStyle && gTextureManager) {
        unsigned short probe = a4;
        (void)gStyle->GetRemapColour16(&probe);
        (void)gStyle->GetRemapColour32(&probe);
    }
    const char* forceGbh = std::getenv("GTA2_TEXT_GBH");
    bool canGbh = false;
    if (forceGbh && forceGbh[0] == '1') {
        // Hard guard: only allow with explicit debug env and confirmed ida views (currently never set).
        if (!gStyle || !gTextureManager) gTextGbhBlocked = "no-style/tm";
        else if (!gStyle->GetIdaView()) gTextGbhBlocked = "no-style-ida";
        else if (!gTextureManager->GetIdaView()) gTextGbhBlocked = "no-tm-ida";
        else {
            int ok = 0, total = 0;
            bool chainOk = Text_ProbeGbhAsciiChain(a1, a4, &ok, &total);
            if (!chainOk) {
                gTextGbhBlocked = (total > 0) ? "glyph-chain-miss" : "no-ascii";
            } else {
                // IDA deps still missing/unconfirmed in RE runtime: Lighting::SetPaletteMode @ 0x4CB050,
                // SpriteS1::SetCarSpriteTransform @ 0x401BD0, Radar/Point2D/Float10/AddX, glyph vert globals,
                // valid S89/PacketInfo/gbh texture handle semantics, FileMgr kanji path.
                // Do not draw with partial gbh state. Probe gbh exports only (no draw).
                static int s_gbhProbe = 0; // 0=not done,1=ok,2=fail
                static char s_gbhProbeBuf[64];
                if (s_gbhProbe == 0) {
                    GbhApi api = Gbh_TryGetLoadedApi();
                    s_gbhProbe = api.loaded ? 1 : 2;
                    snprintf(s_gbhProbeBuf, sizeof(s_gbhProbeBuf), "chain-ok-deps-missing-gbh-%s:%s",
                             api.loaded ? "ok" : "miss", Gbh_GetLastError());
                    s_gbhProbeBuf[sizeof(s_gbhProbeBuf)-1] = 0;
                }
                gTextGbhBlocked = s_gbhProbeBuf;
            }
            canGbh = false;
        }
    } else {
        gTextGbhBlocked = "gbh-env-off";
    }
    // Experimental: only GTA2_TEXT_GBH=1 (probe gate passed to get here logic) AND GTA2_TEXT_GBH_DRAW=1.
    // Default off. Even when on, Text_TryDrawGbhAscii has hard guards and returns false on missing deps.
    if (forceGbh && forceGbh[0] == '1') {
        if (Text_TryDrawGbhAscii(a1, arg4, arg8, a4, a5)) {
            // Drew via gbh experiment; also keep overlay? no, avoid double-draw. Overlay fallback otherwise.
            // Still fall through to overlay because gbh path is unconfirmed and may draw nothing/wrong.
        }
    }

    // ASCII overlay fallback. IDA 0x4CC100: '#' toggles (a1a,a5_12.field_0) between (*a5_4,v7) and (8,0).
    char tmp[128];
    int j = 0;
    int x = arg4;
    int y = arg8;
    unsigned short color = a4;
    unsigned short altColor = (unsigned short)a5;
    bool useAlt = false;
    int lineH = 16;
    extern Font* gFont;
    if (gFont) {
        int ch = gFont->GetCharHeight(color);
        if (ch > 0 && ch < 64) lineH = ch;
    }
    for (int i = 0; a1[i] && j < 127; ++i) {
        wchar_t wc = a1[i];
        if (wc == L'\n') {
            tmp[j] = 0;
            AddDebugTextCmd(tmp, x, y, useAlt ? altColor : color, a5);
            j = 0;
            y += lineH;
            x = arg4;
            continue;
        }
        if (wc == L'#') {
            useAlt = !useAlt;
            continue;
        }
        if (wc == L' ' || (wc >= 32 && wc < 127)) tmp[j++] = (char)wc;
        else tmp[j++] = '?';
    }
    tmp[j] = 0;
    if (j > 0) AddDebugTextCmd(tmp, x, y, useAlt ? altColor : color, a5);
}

void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, int a4, int a5) {
    DrawGTATextRaw(a1, arg4, arg8, (unsigned short)a4, a5);
}

// IDA 0x4539F0: thin wrapper.
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5) {
    DrawGTATextRaw(a1, arg4, arg8, a4, a5);
}

void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, int a4, int a5) {
    DrawGTATextRaw(a1, arg4, arg8, (unsigned short)a4, a5);
}

// IDA 0x4C7280: world->screen via Radar::WorldCoordinateToScreenCoord, then DrawGTATextRaw.
// RE bridge: treat a2/a3 as screen coords when Radar path is unavailable.
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3) {
    DrawGTATextRaw(a1, a2, a3, 0, 0);
}

void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4) {
    // TODO: IDA 0x4C7280 converts world coords using Radar::WorldCoordinateToScreenCoord
    // and passes (v7, v3->BaseCar[0].field) as color args. RE uses screen coords and a4 as color.
    DrawGTATextRaw(a1, a2, a3, a4, 0);
}

void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4, int a5) {
    // Compat: accept original-style 5th arg; RE still uses screen coords.
    DrawGTATextRaw(a1, a2, a3, a4, a5);
}
