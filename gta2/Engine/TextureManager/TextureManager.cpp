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

int TextureManager::GetTexture(int sprite_type, short spriteId, int a4, short a5) {
    // IDA 0x4C2AC0 dispatches by a4 into S89 banks.
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
    // Debug-only. Mirrors IDA RegisterPalitre/gbh_RegisterPalette contract.
    // gbh_RegisterPalette mutates strided PPAL column; pass a copy.
    static int s_slotByPhys[4096];
    static bool s_slotInit = false;
    static int s_nextSlot = 700; // reserved debug slots
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

void* TextureManager::GetDebugGbhFontTexture(int /*sprite_type*/, short spriteId, int a4, short a5) {
    // Narrow guarded debug path for font bank 7 only. Not IDA TM/PacketInfo/S89 pipeline.
    // Enabled only by GTA2_TEXT_GBH_DRAW=1. Requires real gbh exports loaded in-process.
    const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
    if (!drawEnv || drawEnv[0] != '1') return nullptr;
    if (a4 != 7) return nullptr;
    if (!gStyle) return nullptr;
    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.RegisterTexture) return nullptr;

    // IDA: PacketInfo S89[6] is Setup(6,7), indexed by (spriteId,a5) with field_6 from GetPaletteByIndex(gStyle,7).
    // We do not have confirmed full S89 state; use a5==0 conservative probe only.
    if (a5 != 0) return nullptr;

    unsigned short base = gStyle->GetBaseIndex(7, (unsigned short)spriteId);
    if (base == 0) return nullptr;

    struct Cache { bool inited; std::map<unsigned int, gbh_Texture*> byBase; GbhApi api; };
    static Cache c{false, {}, {}};
    if (!c.inited) { c.inited = true; c.api = api; }
    auto it = c.byBase.find(base);
    if (it != c.byBase.end()) return it->second;

    int spr = gStyle->GetSprite(base);
    if (spr == 0) return nullptr;
    unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
    unsigned char w = sp[4];
    unsigned char h = sp[5];
    unsigned char* data = reinterpret_cast<unsigned char*>(*reinterpret_cast<unsigned int*>(sp + 0));
    if (!data || w == 0 || h == 0) return nullptr;

    // Palette: PacketInfo::LoadPalettedTextures uses get_global_palette_id(field_C==7, a5) then GetPhysPalette.
    // a5==0 is the only supported debug case.
    unsigned short globalPal = (unsigned short)gStyle->get_global_palette_id(7, 0);
    short physPal = gStyle->GetPhysPalette(globalPal);
    int palSlot = TM_GbhRegisterPhysPaletteDebug(c.api, (unsigned int)(unsigned short)physPal);
    if (palSlot < 0) return nullptr;

    gbh_Texture* tex = c.api.RegisterTexture((short)w, (short)h, data, palSlot, 0);
    if (!tex) return nullptr;
    c.byBase[base] = tex;
    return tex;
}

int GetTexture(TextureManager* tm, int sprite_type, short spriteId, int a4, short a5) {
    // IDA 0x4C2AC0: dispatches by a4 into S89 banks.
    if (!tm) return 0;
    int v = tm->GetTexture(sprite_type, spriteId, a4, a5);
    if (v != 0) return v;
    // Debug-only fallback for guarded gbh draw experiments; never fake handles.
    void* realTex = tm->GetDebugGbhFontTexture(sprite_type, spriteId, a4, a5);
    return (int)(uintptr_t)realTex;
}