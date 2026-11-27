#include "TextureManager/TextureManager.h"
#include "../Style/StyleTileLoader.h"
#include "../Style/Style.h"
#include "../gbh/gbh.h"
#include <cstdlib>
#include <map>
#include <vector>
#include <cstring>
#include <cstdint>


TextureManager *gTextureManager;

TextureManager::TextureManager(){
}

TextureManager::~TextureManager(){
    if (m_debugFontS89_7.entries) {
        std::free(m_debugFontS89_7.entries);
        m_debugFontS89_7.entries = nullptr;
        m_debugFontS89_7.s89_2.field_0 = nullptr;
        m_debugFontS89_7.s89.S89_2 = nullptr;
    }
}

bool TextureManager::LoadDebugFromStyleTiles() {
    m_debug = DebugState{};
    const char* env = std::getenv("GTA2_TEX_DEBUG");
    if (!env || env[0] != '1') return false;
    const StyleTileAssets* sta = StyleTiles_Get();
    if (!sta || !sta->loaded) return false;
    // IDA 0x4C30A0 loads palettes/tile/sprite textures; RE here only records safe counts.
    m_debug.palCount = (unsigned short)(sta->physPalCount > 0xFFFFu ? 0xFFFFu : sta->physPalCount);
    m_debug.tileCount = (unsigned short)(sta->tileCount > 1024u ? 1024u : sta->tileCount);
    m_debug.spriteTexCount = 48; // IDA TextureManagerCreateSpriteTextures loop
    m_debug.texturesInitialised = (m_debug.palCount > 0);
    m_debug.tileTexturesInitialised = (m_debug.tileCount > 0);
    m_debug.loaded = m_debug.texturesInitialised || m_debug.tileTexturesInitialised;
    return m_debug.loaded;
}

int TextureManager::Load() {
    // Real IDA 0x4C30A0 requires confirmed Style/gbh/PacketInfo/S89 semantics.
    // Keep default safe; optional debug status only.
    if (LoadDebugFromStyleTiles()) return 1;
    return 0;
}
 void TextureManager::RegisterTextures() {
 }
 
 int TextureManager::FreePalitre() {
	 return 0;
 }
 void TextureManager::AssignPalette() {

}

static bool TM_DebugFont7EnsureInit(TextureManager* tm);
static bool TM_DebugBank2EnsureInit(TextureManager* tm);

int TextureManager::GetTexture(int sprite_type, short spriteId, int a4, short a5) {
    // IDA 0x4C2AC0 dispatches by a4 into S89 banks.
    // Debug-only TM-owned subset for font bank 7 (S89[6]) when GTA2_TEXT_GBH_DRAW=1.
    // Default behavior unchanged: returns 0 unless explicitly enabled and subset ready.
    if (a4 == 7) {
        const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
        if (drawEnv && drawEnv[0] == '1') {
            auto& b7 = m_debugFontS89_7;
            if (TM_DebugFont7EnsureInit(this) && b7.ready && b7.entries) {
                unsigned int sid = (unsigned int)(unsigned short)spriteId;
                unsigned int pal = (unsigned int)(unsigned short)a5;
                if (sid < b7.spriteCount && pal < (unsigned int)b7.field_6) {
                    unsigned int idx = pal + sid * (unsigned int)b7.field_6;
                    if (idx < b7.count && b7.entries[idx]) return b7.entries[idx];
                }
            }
        }
    }

    // Guarded: only when debug IDA view is explicitly bound and a known bank has valid S89_2.
    if (!m_idaView) return 0;
    auto* v = reinterpret_cast<TextureManagerIdaView*>(m_idaView);
    int bank = -1;
    switch (a4) {
        case 2: bank = 0; break;
        case 3: bank = 1; break;
        case 4: bank = 2; break;
        case 5: bank = 3; break;
        case 6: bank = 4; break;
        case 7: bank = 6; break;
        case 8: bank = 5; break;
        default: return 0;
    }
    TextureManager_S89& s89 = v->S89[bank];
    auto* s2 = reinterpret_cast<TextureManager_S89_2*>(s89.S89_2);
    if (!s2 || !s2->field_0 || s89.Count == 0) return 0;

    unsigned int idx = 0;
    if (a4 == 2) {
        if (!gStyle) return 0;
        // IDA: S89_2->field_0[Style::GetBaseIndex(gStyle, sprite_type, spriteId)]
        unsigned short base = gStyle->GetBaseIndex(sprite_type, spriteId);
        idx = base;
    } else {
        // IDA: a3 + spriteId * field_6
        if (s89.field_6 <= 0) return 0;
        idx = (unsigned int)(unsigned short)a5 + (unsigned int)(unsigned short)spriteId * (unsigned int)(unsigned short)s89.field_6;
    }
    if (idx >= s89.Count) return 0;
    return s2->field_0[idx];
}

void* TextureManager::GetTextureByIdx(unsigned short idx) {
    // IDA 0x4C2BA0: return Buffer_Arr48[idx]
    if (m_idaView && idx < 48) {
        auto* v = reinterpret_cast<TextureManagerIdaView*>(m_idaView);
        if (v->TexturesInitialised) return v->Buffer_Arr48[idx];
    }
    return nullptr;
}

void* TextureManager::GetTextureValue(unsigned short a2, short a3, short a4) {
    // IDA 0x4C2BC0: updates S88 entry and returns GLuint*.
    // Needs gbh_LockTexture/UnlockTexture and confirmed S88/GLuint layout; keep guarded.
    (void)a2; (void)a3; (void)a4;
    return nullptr;
}

static int TM_GbhRegisterPhysPaletteDebug(GbhApi& api, unsigned int physIdx) {
    // Debug-only. Mirrors gbh_RegisterPalette contract; mutates strided PPAL column so pass a copy.
    static int s_slotByPhys[4096];
    static bool s_slotInit = false;
    static int s_nextSlot = 700; // reserved debug slots, avoid low game slots
    if (!s_slotInit) { for (int i = 0; i < 4096; ++i) s_slotByPhys[i] = -1; s_slotInit = true; }
    if (physIdx >= 4096u) return -1;
    if (s_slotByPhys[physIdx] >= 0) return s_slotByPhys[physIdx];
    if (s_nextSlot > 899) return -1;
    const StyleTileAssets* sta = StyleTiles_Get();
    const unsigned char* palPtr = StyleTiles_GetPhysPalette(physIdx);
    if (!sta || !sta->loaded || !palPtr) return -1;
    std::vector<unsigned long> buf(256u * 64u, 0);
    for (int i = 0; i < 256; ++i) {
        const unsigned char* src = palPtr + (size_t)i * 64u * 4u;
        size_t off = (size_t)(src - sta->ppal);
        if (off + 4u <= sta->ppalBytes) std::memcpy(&buf[(size_t)i * 64u], src, 4u);
    }
    if (!api.RegisterPalette) return -1;
    int slot = s_nextSlot++;
    api.RegisterPalette(slot, &buf[0]);
    s_slotByPhys[physIdx] = slot;
    return slot;
}

static bool TM_DebugFont7EnsureInit(TextureManager* tm) {
    if (!tm) return false;
    auto& b7 = tm->m_debugFontS89_7;
    if (b7.initAttempted) return b7.ready && b7.entries != nullptr;
    b7.initAttempted = true;
    b7.reason = "gbh-font7-init";
    const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
    if (!drawEnv || drawEnv[0] != '1') { b7.reason = "gbh-font7-env-off"; return false; }
    if (!gStyle) { b7.reason = "gbh-font7-no-style"; return false; }
    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.RegisterTexture) { b7.reason = "gbh-font7-gbh-miss"; return false; }
    b7.gbhOk = true;

    // IDA 0x4C30A0: PacketInfo::Setup(&S89[6], 6, 7); PacketInfo::LoadPalettedTextures(&S89[6]);
    // Setup: field_6=GetPaletteByIndex(gStyle,7), Count=GetGlobalPaletteOffset(gStyle,6)*field_6.
    b7.spriteCount = (unsigned short)gStyle->GetGlobalPaletteOffset(6);
    b7.field_6 = (unsigned short)gStyle->GetPaletteByIndex(7);
    if (b7.spriteCount == 0 || b7.field_6 == 0) { b7.reason = "gbh-font7-count0"; return false; }
    unsigned int count = (unsigned int)b7.spriteCount * (unsigned int)b7.field_6;
    if (count > 131072u) { b7.reason = "gbh-font7-count-too-big"; return false; }

    b7.entries = (int*)std::calloc(count, sizeof(int));
    if (!b7.entries) { b7.reason = "gbh-font7-oom"; return false; }

    b7.count = count;
    b7.s89 = TextureManager_S89{};
    b7.s89_2 = TextureManager_S89_2{};
    b7.s89_2.field_0 = b7.entries;
    b7.s89.S89_2 = &b7.s89_2;
    b7.s89.Count = (unsigned short)(count <= 0xFFFFu ? count : 0xFFFFu);
    b7.s89.field_6 = (short)b7.field_6;
    b7.s89.sprite_type = 6; // Setup(6,7)
    b7.s89.field_C = 7;
    b7.s89.field_10 = 1;
    b7.ready = (b7.count == (unsigned int)b7.s89.Count); // count overflow guard
    b7.reason = b7.ready ? "gbh-font7-ready" : "gbh-font7-count16-overflow";
    return b7.ready;
}

void* TextureManager::GetDebugGbhFontTexture(int /*sprite_type*/, short spriteId, int a4, short a5) {
    // Debug-only TM-owned S89[6] font-bank7 subset. NOT full IDA TM/PacketInfo/S89.
    // Gates: GTA2_TEXT_GBH_DRAW=1, real gbh exports, Style+StyleTiles present.
    // IDA 0x4CC100 calls GetTexture(gTM,7,SpriteID,a1a,a5_12.field_0) => S89[6] indexed by a5+spriteId*field_6.
    // We currently support only a5==0 because palette/select semantics for a1a/a5 are not fully confirmed.
    auto& b7 = m_debugFontS89_7;
    if (a4 != 7) return nullptr; // debug subset is bank7 only; don't pollute reason for other banks
    if (a5 != 0) { b7.reason = "gbh-font7-a5-unsupported"; return nullptr; }
    if (!TM_DebugFont7EnsureInit(this)) return nullptr;

    unsigned int sid = (unsigned int)(unsigned short)spriteId;
    if (sid >= b7.spriteCount) { b7.reason = "gbh-font7-sid-oob"; return nullptr; }
    unsigned int pal = (unsigned int)(unsigned short)a5;
    if (pal >= b7.field_6) { b7.reason = "gbh-font7-pal-oob"; return nullptr; }
    unsigned int idx = pal + sid * (unsigned int)b7.field_6;
    if (idx >= b7.count) { b7.reason = "gbh-font7-idx-oob"; return nullptr; }

    if (b7.entries[idx]) {
        b7.reason = "gbh-font7-ok";
        return (void*)(uintptr_t)(unsigned int)b7.entries[idx];
    }

    // IDA 0x4CC100: BaseIndex=GetBaseIndex(gStyle,7,SpriteID); Sprite=GetSprite(BaseIndex).
    unsigned short base = gStyle->GetBaseIndex(7, (unsigned short)spriteId);
    int spr = gStyle->GetSprite(base);
    if (spr == 0) { b7.reason = "gbh-font7-sprite-miss"; return nullptr; }
    unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
    unsigned char w = sp[4];
    unsigned char h = sp[5];
    unsigned char* data = reinterpret_cast<unsigned char*>(*reinterpret_cast<unsigned int*>(sp + 0));
    if (!data || w == 0 || h == 0) { b7.reason = "gbh-font7-sprite-bad"; return nullptr; }

    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.RegisterTexture) { b7.reason = "gbh-font7-gbh-miss"; return nullptr; }

    // IDA PacketInfo::LoadPalettedTextures for Setup(sprite_type=6,field_C=7):
    // global_palette_id = get_global_palette_id(gStyle, field_C==7, v5); phys = GetPhysPalette(global).
    // For a5==0 this matches first palette column; other a5/palette combos remain guarded.
    unsigned short globalPal = (unsigned short)gStyle->get_global_palette_id(7, (short)pal);
    short physPal = gStyle->GetPhysPalette(globalPal);
    int palSlot = TM_GbhRegisterPhysPaletteDebug(api, (unsigned int)(unsigned short)physPal);
    if (palSlot < 0) { b7.reason = "gbh-font7-pal-fail"; return nullptr; }

    // RegisterTexture a5 is 0 in IDA decomp for S89 paletted textures; keep 0 (unconfirmed).
    gbh_Texture* tex = api.RegisterTexture((short)w, (short)h, data, palSlot, 0);
    if (!tex) { b7.reason = "gbh-font7-regtex-null"; return nullptr; }

    b7.entries[idx] = (int)(uintptr_t)tex;
    b7.reason = "gbh-font7-ok";
    return tex;
}

static bool TM_DebugBank2EnsureInit(TextureManager* tm) {
    if (!tm) return false;
    auto& b2 = tm->m_debugBank2Style;
    if (b2.initAttempted) return b2.ready && b2.entries != nullptr;
    b2.initAttempted = true;
    b2.reason = "gbh-bank2-init";
    const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
    if (!drawEnv || drawEnv[0] != '1') { b2.reason = "gbh-bank2-env-off"; return false; }
    if (!gStyle) { b2.reason = "gbh-bank2-no-style"; return false; }
    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.RegisterTexture) { b2.reason = "gbh-bank2-gbh-miss"; return false; }

    // IDA 0x4C30A0: PaletteByIndex=GetPaletteByIndex(gStyle,2); PacketInfo::Create(S89[0],PaletteByIndex,1,0,2); LoadTextures.
    // Create sets Count=a3*a2 = 1*PaletteByIndex. LoadTextures iterates i<Count, uses Style::GetSprite(gStyle,i) and
    // global_palette_id(gStyle,2,i) with gbh_RegisterTexture(w,h,data,palSlot,0).
    unsigned short count = (unsigned short)gStyle->GetPaletteByIndex(2);
    if (count == 0) { b2.reason = "gbh-bank2-count0"; return false; }
    if (count > 65535u) { b2.reason = "gbh-bank2-count-too-big"; return false; }
    b2.entries = (int*)std::calloc(count, sizeof(int));
    if (!b2.entries) { b2.reason = "gbh-bank2-oom"; return false; }
    b2.count = count;
    b2.ready = true;
    b2.reason = "gbh-bank2-ready";
    return true;
}

void* TextureManager::GetDebugGbhBank2Texture(int sprite_type, short spriteId) {
    auto& b2 = m_debugBank2Style;
    if (!TM_DebugBank2EnsureInit(this)) return nullptr;
    // IDA GetStyleTexture: S89_2->field_0[Style::GetBaseIndex(gStyle, sprite_type, spriteId)]
    unsigned short base = gStyle->GetBaseIndex(sprite_type, spriteId);
    if (base >= b2.count) { b2.reason = "gbh-bank2-base-oob"; return nullptr; }
    if (b2.entries[base]) { b2.reason = "gbh-bank2-ok"; return (void*)(uintptr_t)(unsigned int)b2.entries[base]; }

    // IDA LoadTextures(S89[0]): Sprite = Style::GetSprite(gStyle, i); global_palette_id(gStyle,2,i); physPal; RegisterTexture(w,h,data,palSlot,0)
    int spr = gStyle->GetSprite(base);
    if (spr == 0) { b2.reason = "gbh-bank2-sprite-miss"; return nullptr; }
    unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
    unsigned char w = sp[4], h = sp[5];
    unsigned char* data = reinterpret_cast<unsigned char*>(*reinterpret_cast<unsigned int*>(sp + 0));
    if (!data || w == 0 || h == 0) { b2.reason = "gbh-bank2-sprite-bad"; return nullptr; }
    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.RegisterTexture) { b2.reason = "gbh-bank2-gbh-miss"; return nullptr; }
    unsigned short globalPal = (unsigned short)gStyle->get_global_palette_id(2, (short)base);
    short physPal = gStyle->GetPhysPalette(globalPal);
    int palSlot = TM_GbhRegisterPhysPaletteDebug(api, (unsigned int)(unsigned short)physPal);
    if (palSlot < 0) { b2.reason = "gbh-bank2-pal-fail"; return nullptr; }
    gbh_Texture* tex = api.RegisterTexture((short)w, (short)h, data, palSlot, 0);
    if (!tex) { b2.reason = "gbh-bank2-regtex-null"; return nullptr; }
    b2.entries[base] = (int)(uintptr_t)tex;
    b2.reason = "gbh-bank2-ok";
    return tex;
}

int GetTexture(TextureManager* tm, int sprite_type, short spriteId, int a4, short a5) {
    // IDA 0x4C2AC0: dispatches by a4 into S89 banks.
    if (!tm) return 0;
    int v = tm->GetTexture(sprite_type, spriteId, a4, a5);
    if (v != 0) return v;
    // Debug-only fallback for guarded gbh draw experiments; never fake handles.
    if (a4 == 2) {
        void* realTex = tm->GetDebugGbhBank2Texture(sprite_type, spriteId);
        if (realTex) return (int)(uintptr_t)realTex;
    }
    void* realTex = tm->GetDebugGbhFontTexture(sprite_type, spriteId, a4, a5);
    return (int)(uintptr_t)realTex;
}