#include "Style.h"
#include "../FileMgr/FileMgr.h"
#include "../ultil/WinApi.h"
#include "StyleTileLoader.h"
#include <cstdlib>
#include <cstring>
#include <new>



    // 0x00420200
Style *gStyle;

Style::Style() {
    // IDA 0x4C08D0: InitSpecArray(arr1024), zero many fields. RE has partial layout; init known fields.
    this->InitSpecArray();
    this->PallitrePal = 0;
    this->ColorCar = nullptr;
    this->Tiles = 0;
    this->ColourDepth = 0;
    this->m_idaView = nullptr;
    this->m_idaViewOwned = nullptr;
    this->m_idaViewSprxBytes = 0;
    this->m_idaViewFonbBytes = 0;
}

void Style::ClearIdaViewDebug() {
    if (m_idaViewOwned) {
        std::free(m_idaViewOwned);
        m_idaViewOwned = nullptr;
    }
    m_idaView = nullptr;
    m_idaViewSprxBytes = 0;
    m_idaViewFonbBytes = 0;
}

bool Style::BindIdaViewFromStyleTilesDebug() {
    // Debug-only read-only adapter. Not IDA-canonical object layout.
    // Enabled only by env to avoid changing default behavior.
    ClearIdaViewDebug();
    const char* env = std::getenv("GTA2_STYLE_IDA_VIEW");
    if (!env || env[0] != '1') return false;
    const StyleTileAssets* sta = StyleTiles_Get();
    if (!sta || !sta->loaded) return false;
    if (!sta->sprx || sta->sprxBytes < 8) return false;
    if (!sta->sprb || sta->sprbBytes < 12) return false;
    if (!sta->fonb || sta->fonbBytes < 2) return false;

    struct IdaAdapter {
        StyleIdaView view;
        unsigned short sprbRaw[6]; // SPRB raw counts (IDA field_18)
        unsigned short s15[6];     // SPRB cumulative bases (IDA field_14 after BuildCumulativeTable)
        unsigned short palb[8];    // PALB palette counts (S15_0002)
        unsigned short pali[8];    // PALB-derived cumulative bases (field_C)
    };
    auto* ad = static_cast<IdaAdapter*>(std::malloc(sizeof(IdaAdapter)));
    if (!ad) return false;
    std::memset(ad, 0, sizeof(IdaAdapter));

    // SPRB: 6 u16 values. IDA read_sprb_records_REAL: read into field_18, copy to field_14, BuildCumulativeTable(field_14).
    // GetGlobalPaletteOffset reads field_18 (raw), GetBaseIndex reads field_14 (cumulative).
    std::memcpy(ad->sprbRaw, sta->sprb, 12);
    unsigned short accSprb = 0;
    for (int i = 0; i < 6; ++i) { unsigned short c = ad->sprbRaw[i]; ad->s15[i] = accSprb; accSprb = (unsigned short)(accSprb + c); }
    // PALB: 8 u16 palette counts. IDA Style::read_palb_chunk_REAL stores raw into S15_0002
    // and cumulative bases into field_C.
    if (sta->palb && sta->palbBytes >= 16) std::memcpy(ad->palb, sta->palb, 16);
    std::memcpy(ad->pali, ad->palb, 16);
    unsigned short acc = 0;
    for (int i = 0; i < 8; ++i) { unsigned short c = ad->pali[i]; ad->pali[i] = acc; acc = (unsigned short)(acc + c); }

    ad->view.field_14 = ad->s15;
    ad->view.field_18 = (int)reinterpret_cast<uintptr_t>(ad->sprbRaw);
    ad->view.S15_0002 = ad->palb;
    ad->view.field_C = (int)reinterpret_cast<uintptr_t>(ad->pali);
    ad->view.field_20 = (int)reinterpret_cast<uintptr_t>(sta->sprx); // sprx entries: 8 bytes each in IDA usage
    ad->view.Car = sta->fonb;      // FONB starts with count u16, then u16 table
    ad->view.field_4 = (unsigned short)((sta->sprxBytes / 8u) + 1u); // IDA read_sprx_records_REAL: (size>>3)+1
    ad->view.field_6 = sta->obji ? (unsigned short)(sta->objiBytes / 2u) : 0;
    ad->view.field_58 = (int)reinterpret_cast<uintptr_t>(sta->cari);
    ad->view.Tiles = (int)reinterpret_cast<uintptr_t>(sta->tile); // debug hint only, not IDA-canonical
    ad->view.recy = reinterpret_cast<char*>(sta->recy);
    ad->view.n_recy = (short)sta->recyBytes;

    m_idaViewOwned = ad;
    m_idaView = &ad->view;
    m_idaViewSprxBytes = sta->sprxBytes;
    m_idaViewFonbBytes = sta->fonbBytes;
    return true;
}

void Style::Load(char* FileName) {
    // IDA 0x4C0820: FileOpen, read GBST+ver700, loop ReadLine/parse_chunk, CloseFile, StyleFixupSprites.
    // RE guarded fallback: original FileMgr semantics in RE are not fully equivalent to IDA; avoid changing
    // default behavior. Debug-only: if GTA2_STYLE_IDA_VIEW=1 and StyleTiles debug assets are loaded,
    // bind idaView and run guarded read_* debug bindings (no FileMgr/NewMemory/CreateBuffer emulation).
    (void)FileName;
    if (!BindIdaViewFromStyleTilesDebug()) return;
    // Guarded debug-only chunk binding order mirrors common STY presence; each read_* checks StyleTiles.
    (void)read_palb_chunk_REAL();
    (void)read_sprb_records_REAL();
    (void)read_fonb_chunk_REAL();
    (void)read_sprx_records_REAL();
    (void)read_obji_records_REAL();
    (void)read_palx_records_REAL();
    (void)read_ppal_records_REAL();
    (void)read_sprg_records_REAL();
    (void)read_tile_chunk_REAL();
    (void)read_dels_records_REAL();
    (void)read_delx_records_REAL();
    (void)read_cari_records_REAL();
    (void)read_psxt_records_REAL();
    (void)read_ovly_records_REAL_();
    (void)read_spec_records_REAL();
    (void)read_recy_chunk_REAL_();
    (void)StyleFixupSprites();
}

void Style::InitSpecArray() {
    // IDA 0x4C06D0: memset(1024 u32) to 1.
    for (int i = 0; i < 1024; ++i) {
        this->ArrayStyle[i] = 1;
    }
}
void Style::LoadFileSTY(char* fileName) {
    // RE stub: no confirmed IDA Style::LoadFileSTY symbol in this export.
    (void)fileName;
}
bool Style::CarExist(unsigned char id){
        // IDA 0x420200: pCar_5C->Car[id] != 0
        // Guarded: only when idaView provides pCar_5C with IDA-like layout (Car[256] ints, CountModelCar at +0x400).
        if (m_idaView && m_idaView->pCar_5C) {
            auto* base = reinterpret_cast<unsigned char*>(m_idaView->pCar_5C);
            int carPtr = *reinterpret_cast<int*>(base + ((int)id * 4));
            return carPtr != 0;
        }
        return false;
    }


    // 0x00420220 (legacy no-arg stub removed; use getSpriteWidth(unsigned short))

bool Style::GetSpriteColors(unsigned short a2, unsigned int* a3, unsigned int* a4){
        // IDA 0x420230: reads sprite width/height bytes and indexes unk_6639A0.S39_Arr48[].field_0.
        // Guarded: global S39 table not ported in RE.
        if (a3) *a3 = 0;
        if (a4) *a4 = 0;
        (void)a2;
        return false;
    }


    // 0x00432850


unsigned char Style::GetNumberOfCars(){
        // IDA 0x432850: pCar_5C->CountModelCar (byte at +0x400 in S284)
        if (m_idaView && m_idaView->pCar_5C) {
            auto* base = reinterpret_cast<unsigned char*>(m_idaView->pCar_5C);
            return base[0x400];
        }
        return 0;
    }


    // 0x00432860


void Style::SetXY(int arg0,int arg1){
        // RE stub. IDA 0x432860 is Point2D::SetXY; Style name kept for RE compatibility only.
        (void)arg0; (void)arg1;
    }


    // 0x00462FB0


bool Style::IsMapTileSpecial(unsigned short a2){
        // IDA 0x462FB0: arr1024[a2] == 4
        if (a2 >= 1024) return false;
        if (m_idaView) return m_idaView->arr1024[a2] == 4;
        return ArrayStyle[a2] == 4;
    }


    // 0x00462FD0


int Style::StyleGetSlotAttr(unsigned short index){
        // IDA 0x462FD0: result = arr1024[index]; if 3 return 1; return result.
        if (index >= 1024) return 0;
        int result = m_idaView ? m_idaView->arr1024[index] : (int)ArrayStyle[index];
        if (result == 3) return 1;
        return result;
    }


    // 0x00463020


bool Style::IsPointInRect(unsigned char a2, unsigned char a3){
        // IDA 0x463020 uses object fields at +1..+4; RE has no equivalent layout.
        // Keep guarded no-op to avoid wrong semantics.
        (void)a2; (void)a3;
        return false;
    }

bool Style::IsTileBlockedPlayer(unsigned short a2){
        // IDA 0x49E540
        return a2 < 1024 && IsMapTileSpecial(a2) && IsTileRemapped(a2);
    }

bool Style::IsPathStateFive(unsigned short a2){
        // IDA 0x491F80
        if (a2 >= 1024) return false;
        if (m_idaView) return m_idaView->arr1024[a2] == 5;
        return ArrayStyle[a2] == 5;
    }

bool Style::is_tile_road_special(unsigned short a2){
        // IDA 0x42A810
        if (a2 >= 1024) return false;
        if (m_idaView) return m_idaView->arr1024[a2] == 3;
        return ArrayStyle[a2] == 3;
    }

bool Style::IsTileOneWay(unsigned short a2){
        // IDA 0x49E570
        return a2 < 1024 && IsMapTileSpecial(a2) && !IsTileRemapped(a2);
    }


    // 0x004B9F20


int Style::StyleGetSpriteCount(void){
        return (int)GetSpriteCount();
    }


    // 0x004BF1F0


int Style::getCarModelById(unsigned char carType){
        // IDA 0x4BF1F0: pCar_5C->Car[carType]
        if (m_idaView && m_idaView->pCar_5C) {
            auto* base = reinterpret_cast<unsigned char*>(m_idaView->pCar_5C);
            return *reinterpret_cast<int*>(base + ((int)carType * 4));
        }
        return 0;
    }


    // 0x004BF210


int Style::GetCarModel(unsigned char a2){
        // IDA 0x4BF210: v2=pCar_5C->Car[a2]; return *(u8*)(v2+4)+v2+14.
        if (m_idaView && m_idaView->pCar_5C) {
            auto* base = reinterpret_cast<unsigned char*>(m_idaView->pCar_5C);
            int v2 = *reinterpret_cast<int*>(base + ((int)a2 * 4));
            if (!v2) return 0;
            auto* p = reinterpret_cast<unsigned char*>((uintptr_t)v2);
            return (int)(unsigned int)p[4] + v2 + 14;
        }
        return 0;
    }


    // 0x004BF2A0


unsigned short Style::GetBaseIndex(int sprite_type, short spriteId){
        // IDA 0x4BF2A0: uses field_14 offsets by sprite_type.
        if (m_idaView && m_idaView->field_14) {
            auto* f14 = reinterpret_cast<unsigned short*>(m_idaView->field_14);
            switch (sprite_type) {
            case 2: return (unsigned short)(spriteId + f14[0]);
            case 3: return (unsigned short)(spriteId + f14[1]);
            case 4: case 8: return (unsigned short)(spriteId + f14[2]);
            case 5: return (unsigned short)(spriteId + f14[3]);
            case 6: return (unsigned short)(spriteId + f14[4]);
            case 7: return (unsigned short)(spriteId + f14[5]);
            default: return (unsigned short)spriteId;
            }
        }
        (void)sprite_type; (void)spriteId;
        return 0;
    }


    // 0x004BF330


short Style::GetGlobalPaletteOffset(int a2){
        // IDA 0x4BF330: field_18 is S15 array of u16 offsets by sprite type.
        if (m_idaView && m_idaView->field_18) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->field_18);
            switch (a2) {
                case 2: return (short)p[0];
                case 3: return (short)p[1];
                case 4: case 8: return (short)p[2];
                case 5: return (short)p[3];
                case 6: return (short)p[4];
                case 7: return (short)p[5];
                default: return 0;
            }
        }
        (void)a2; return 0;
    }


    // 0x004BF3A0


short Style::GetPaletteByIndex(int a2){
        // IDA 0x4BF3A0: S15_0002 has palette counts by index (1..8).
        if (m_idaView && m_idaView->S15_0002) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S15_0002);
            switch (a2) {
                case 1: return (short)p[0];
                case 2: return (short)p[1];
                case 3: return (short)p[2];
                case 4: return (short)p[3];
                case 5: return (short)p[4];
                case 6: return (short)p[5];
                case 7: return (short)p[6];
                case 8: return (short)p[7];
                default: return 0;
            }
        }
        (void)a2; return 0;
    }


    // 0x004BF430


unsigned short Style::get_global_palette_id(int palette_type, short palette_id){
        // IDA 0x4BF430: field_C is S15 array of base offsets (1..8).
        if (m_idaView && m_idaView->field_C) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->field_C);
            switch (palette_type) {
                case 1: return (unsigned short)(palette_id + p[0]);
                case 2: return (unsigned short)(palette_id + p[1]);
                case 3: return (unsigned short)(palette_id + p[2]);
                case 4: return (unsigned short)(palette_id + p[3]);
                case 5: return (unsigned short)(palette_id + p[4]);
                case 6: return (unsigned short)(palette_id + p[5]);
                case 7: return (unsigned short)(palette_id + p[6]);
                case 8: return (unsigned short)(palette_id + p[7]);
                default: return (unsigned short)palette_id;
            }
        }
        return (unsigned short)palette_id;
    }


    // 0x004BF4E0


unsigned int Style::GetColourBank(unsigned short a2){
        // IDA 0x4BF4E0: field_2C + 4*((a2&0x3F)+((a2&0xFFC0)<<8)). Returns ptr in IDA.
        if (m_idaView && m_idaView->field_2C) {
            return (unsigned int)(m_idaView->field_2C + 4 * ((a2 & 0x3Fu) + ((a2 & 0xFFC0u) << 8)));
        }
        return 0;
    }


    // 0x004BF530


unsigned short Style::GetPhysPalette(unsigned short a2){
        // IDA 0x4BF530: *((_WORD*)field_28 + a2)
        if (m_idaView && m_idaView->field_28) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->field_28);
            return p[a2];
        }
        // Debug fallback: PALX from StyleTiles.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->palx && a2 < sta->palxCount) return sta->palx[a2];
        return 0;
    }


    // 0x004BF550


short Style::GetSpriteID(unsigned short a2, short a3){
        // IDA 0x4BF550: a3 + Car->Car[a2+1]
        if (m_idaView && m_idaView->Car) {
            auto* carWords = reinterpret_cast<unsigned short*>(m_idaView->Car);
            return (short)(a3 + carWords[a2 + 1]);
        }
        (void)a2; (void)a3;
        return 0;
    }


    // 0x004BF570


int Style::GetStylePalette(void){
        return 0;
    }

unsigned short Style::StyleGetRemapColour(wchar_t* style, unsigned short* a3) {
    // IDA 0x4BF570: glyph width from sprx table. Guarded by idaView; kanji specials need globals.
    if (!style || !a3) return 8;
    if (m_debugFontStyles.valid) {
        if (*style == m_debugFontStyles.word_67065C) return 16;
        if (*style == m_debugFontStyles.word_670650) return 32;
    } else {
        if (*style == 1) return 16; // guarded default, real globals unknown in RE
        if (*style == 2) return 32;
    }
    if (m_idaView && m_idaView->field_20 && m_idaView->field_14 && m_idaView->Car) {
        auto* f14 = reinterpret_cast<unsigned short*>(m_idaView->field_14);
        auto* carWords = reinterpret_cast<unsigned short*>(m_idaView->Car);
        auto* sprx = reinterpret_cast<unsigned char*>(m_idaView->field_20);
        unsigned int fontBase = (unsigned int)f14[5];
        unsigned int styleOff = (unsigned int)(unsigned short)*style + 1u;
        if (styleOff * 2u + 1u >= m_idaViewFonbBytes) return 8;
        unsigned int idx = (unsigned int)*a3 + fontBase + (unsigned int)carWords[styleOff];
        unsigned int off = 8u * idx;
        if (off < 260u) return 8;
        unsigned int byteOff = off - 260u;
        unsigned int sprxLimit = m_idaViewSprxBytes ? m_idaViewSprxBytes : ((unsigned int)m_idaView->field_4 * 8u);
        if (byteOff >= sprxLimit) return 8;
        return (unsigned short)sprx[byteOff];
    }
    return 8;
}


    // 0x004BF5D0


short Style::GetRemapColour16(unsigned short* a2){
        // IDA 0x4BF5D0: special 16/32 for kanji, else palette from field_20.
        if (!a2) return 0;
        if (m_debugFontStyles.valid) {
            if (*a2 == m_debugFontStyles.word_67065C) return 16;
            if (*a2 == m_debugFontStyles.word_670650) return 32;
        } else {
            if (*a2 == 1) return 16; // guarded default, real globals unknown in RE
            if (*a2 == 2) return 32;
        }
        if (m_idaView && m_idaView->field_20 && m_idaView->field_14 && m_idaView->Car) {
            auto* f14 = reinterpret_cast<unsigned short*>(m_idaView->field_14);
            auto* carWords = reinterpret_cast<unsigned short*>(m_idaView->Car);
            auto* sprx = reinterpret_cast<unsigned char*>(m_idaView->field_20);
            unsigned int styleOff = (unsigned int)(unsigned short)*a2 + 1u;
            if (styleOff * 2u + 1u >= m_idaViewFonbBytes) return 0;
            unsigned int idx = (unsigned int)f14[5] + (unsigned int)carWords[styleOff];
            unsigned int off = 8u * idx + 620u;
            unsigned int sprxLimit = m_idaViewSprxBytes ? m_idaViewSprxBytes : ((unsigned int)m_idaView->field_4 * 8u);
            if (off >= sprxLimit) return 0;
            return (short)sprx[off];
        }
        return 0; // unknown - caller should fallback
    }


    // 0x004BF630


short Style::GetRemapColour32(unsigned short* style){
        // IDA 0x4BF630: special 17/34 for kanji, else palette from field_20.
        if (!style) return 0;
        if (m_debugFontStyles.valid) {
            if (*style == m_debugFontStyles.word_67065C) return 17;
            if (*style == m_debugFontStyles.word_670650) return 34;
        } else {
            if (*style == 1) return 17; // guarded default, real globals unknown in RE
            if (*style == 2) return 34;
        }
        if (m_idaView && m_idaView->field_20 && m_idaView->field_14 && m_idaView->Car) {
            auto* f14 = reinterpret_cast<unsigned short*>(m_idaView->field_14);
            auto* carWords = reinterpret_cast<unsigned short*>(m_idaView->Car);
            auto* sprx = reinterpret_cast<unsigned char*>(m_idaView->field_20);
            unsigned int styleOff = (unsigned int)(unsigned short)*style + 1u;
            if (styleOff * 2u + 1u >= m_idaViewFonbBytes) return 0;
            unsigned int idx = (unsigned int)f14[5] + (unsigned int)carWords[styleOff];
            unsigned int off = 8u * idx + 261u;
            unsigned int sprxLimit = m_idaViewSprxBytes ? m_idaViewSprxBytes : ((unsigned int)m_idaView->field_4 * 8u);
            if (off >= sprxLimit) return 0;
            return (short)sprx[off];
        }
        return 0; // unknown - caller should fallback
    }


    // 0x004BF690


bool Style::IsTileRemapped(unsigned short a2){
        if (a2 >= 1024) return false;
        if (m_idaView && m_idaView->S1501) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
            return p[a2] != a2;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded) return sta->s1501[a2] != a2;
        return false;
    }


    // 0x004BF6B0


unsigned short Style::GetTileById(unsigned short a2){
        if (a2 >= 1024) return a2;
        if (m_idaView && m_idaView->S1501) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
            return p[a2];
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded) return sta->s1501[a2];
        return a2;
    }


    // 0x004BF6D0


short Style::FindFreeTileIndex(){
        unsigned short* p = nullptr;
        if (m_idaView && m_idaView->S1501) p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
        StyleTileAssets* sta = const_cast<StyleTileAssets*>(StyleTiles_Get());
        if (!p && sta && sta->loaded) p = sta->s1501;
        if (!p) return 0;
        for (int idx = 1023; idx >= 0; --idx) {
            if (p[idx] == 0) {
                if ((unsigned short)idx < 0x3E0u) return 0;
                return (short)idx;
            }
        }
        return 0;
    }


    // 0x004BF740


unsigned short Style::GetPallitrePal(){
        if (m_idaView) return m_idaView->PalitrePal;
        return PallitrePal;
    }


    // 0x004BF750


int Style::get_obji_by_idx(unsigned short a2){
        // IDA 0x4BF750: if (a2 < field_6) return field_24 + 2*a2; else 0.
        if (m_idaView && m_idaView->field_24) {
            if (a2 < m_idaView->field_6) return m_idaView->field_24 + 2 * (int)a2;
            return 0;
        }
        // Debug fallback: StyleTiles obji.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->obji && sta->objiBytes >= 2u) {
            unsigned int count = sta->objiBytes / 2u;
            if ((unsigned int)a2 < count) return (int)(uintptr_t)(sta->obji + (unsigned int)a2 * 2u);
        }
        return 0;
    }


    // 0x004BF770


void Style::ChangeTileByIdx(unsigned short a2, short a3){
        // IDA 0x4BF770: S1501[a2] = a3
        if (m_idaView && m_idaView->S1501) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
            p[a2] = (unsigned short)a3;
            return;
        }
        // Debug fallback: StyleTiles s1501
        StyleTileAssets* sta = const_cast<StyleTileAssets*>(StyleTiles_Get());
        if (sta && sta->loaded && a2 < 1024u) {
            sta->s1501[a2] = (unsigned short)a3;
        }
    }


    // 0x004BF7F0


int Style::StyleInitSpriteTable(void){
        // IDA 0x4BF7F0: alloc 2048, fill 0..991, last 32 zero.
        // RE guarded: only touch StyleTiles debug table / idaView-owned S1501 if clearly owned.
        StyleTileAssets* sta = const_cast<StyleTileAssets*>(StyleTiles_Get());
        if (sta && sta->loaded) {
            for (unsigned short i = 0; i < 992; ++i) sta->s1501[i] = i;
            for (unsigned short i = 992; i < 1024; ++i) sta->s1501[i] = 0;
            return 2048;
        }
        if (m_idaView && m_idaView->S1501) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
            for (unsigned short i = 0; i < 992; ++i) p[i] = i;
            for (unsigned short i = 992; i < 1024; ++i) p[i] = 0;
            return 2048;
        }
        return 0;
    }


    // 0x004BF840


void Style::BuildSpriteBuffer(int param_1,unsigned int param_2){

    }


    // 0x004BF900


int Style::StyleApplySpriteOffset(void){
        return 0;
    }


    // 0x004BF950


int Style::StyleAddSpriteOffset(void){
        return 0;
    }


    // 0x004BF980


void Style::BuildSpriteLookup(int param_1){

    }


    // 0x004BFA60


int Style::read_delx_records_REAL(void){
        // IDA 0x4BFA60: alloc+read delx, BuildSpriteBuffer, BuildSpriteLookup, free delx.
        // RE debug-only: capture raw DELX for inspection; do NOT fake BuildSpriteBuffer/Lookup/field_50/54.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->delx) return 0;
        if (m_idaView) { m_idaView->field_4C = (int)reinterpret_cast<uintptr_t>(sta->delx); }
        return 1;
    }


    // 0x004BFAB0


int Style::read_dels_records_REAL(void){
        // IDA 0x4BFAB0: alloc+read dels into field_48.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->dels) return 0;
        if (m_idaView) m_idaView->field_48 = (int)reinterpret_cast<uintptr_t>(sta->dels);
        return 1;
    }


    // 0x004BFAD0


int Style::read_tile_chunk_REAL(void){
        // IDA 0x4BFAD0: NewMemory+Read TILE into Tiles/field_44, StyleInitSpriteTable.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->tile) return 0;
        Tiles = (int)reinterpret_cast<uintptr_t>(sta->tile); // debug hint only
        if (m_idaView) { m_idaView->Tiles = (int)reinterpret_cast<uintptr_t>(sta->tile); m_idaView->field_44 = (int)sta->tileBytes; }
        return StyleInitSpriteTable();
    }


    // 0x004BFB00


int Style::read_ovly_records_REAL_(void){
        // IDA 0x4BFB00: FileMgr::Seek over chunk; no data stored.
        return 1;
    }


    // 0x004BFB10


int Style::read_psxt_records_REAL(void){
        // IDA 0x4BFB10: FileMgr::Seek over chunk; no data stored.
        return 1;
    }


    // 0x004BFB20


int Style::read_sprg_records_REAL(void){
        // IDA 0x4BFB20: NewMemory+Read into field_34/field_38.
        // RE debug-only: bind StyleTiles.sprg to idaView; no alloc/copy.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->sprg) return 0;
        if (m_idaView) { m_idaView->field_34 = (int)reinterpret_cast<uintptr_t>(sta->sprg); m_idaView->field_38 = (int)sta->sprgBytes; }
        return 1;
    }


    // 0x004BFB50


int Style::read_ppal_records_REAL(void){
        // IDA 0x4BFB50: NewMemory+Read into field_2C/field_30, PalitrePal = size>>10.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->ppal) return 0;
        unsigned int palCount = sta->physPalCount;
        PallitrePal = (unsigned short)palCount;
        if (m_idaView) { m_idaView->field_2C = (int)reinterpret_cast<uintptr_t>(sta->ppal); m_idaView->field_30 = (int)sta->ppalBytes; m_idaView->PalitrePal = (unsigned short)palCount; }
        return 1;
    }


    // 0x004BFB80


int Style::read_palx_records_REAL(void){
        // IDA 0x4BFB80: expects 0x8000, allocs 0x8000, reads into field_28.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->palx) return 0;
        if (m_idaView) m_idaView->field_28 = sta->palx;
        return 1;
    }

    // 0x004BFBE0

int Style::read_obji_records_REAL(void){
        // IDA 0x4BFBE0: CreateBuffer+Read obji into field_24, field_6=size>>1.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->obji) return 0;
        if (m_idaView) { m_idaView->field_24 = (int)reinterpret_cast<uintptr_t>(sta->obji); m_idaView->field_6 = (unsigned short)(sta->objiBytes / 2u); }
        return 1;
    }

    // 0x004BFC60

int Style::read_sprx_records_REAL(void){
        // IDA 0x4BFC60: CreateBuffer+Read sprx into field_20, field_4=(size>>3)+1.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->sprx) return 0;
        if (m_idaView) { m_idaView->field_20 = (int)reinterpret_cast<uintptr_t>(sta->sprx); m_idaView->field_4 = (unsigned short)((sta->sprxBytes / 8u) + 1u); }
        return 1;
    }

    // 0x004BFDD0

int Style::read_fonb_chunk_REAL(void){
        // IDA 0x4BFDD0: CreateBuffer+Read fonb into Car, field_2, BuildCumulativeTable, SetFontStyles.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->fonb || sta->fonbBytes < 2) return 0;
        if (m_idaView) m_idaView->Car = sta->fonb;
        UpdateDebugFontStylesFromFonb();
        return m_debugFontStyles.valid ? 1 : 1;
    }


    // 0x004BFCC0


int Style::SetFontStyles(void){
        // IDA 0x4BFCC0 sets global font style IDs based on FONB count (14 or 7).
        // RE keeps this as debug-only local state to avoid touching unknown globals.
        UpdateDebugFontStylesFromFonb();
        return m_debugFontStyles.valid ? 1 : 0;
    }

void Style::UpdateDebugFontStylesFromFonb() {
    m_debugFontStyles = DebugFontStyles{};
    const StyleTileAssets* sta = StyleTiles_Get();
    if (!sta || !sta->loaded || !sta->fonb || sta->fonbBytes < 2) return;
    unsigned short fonbCount = (unsigned short)(sta->fonb[0] | (sta->fonb[1] << 8));
    if (fonbCount == 14) {
        m_debugFontStyles.word_67065C = 1;
        m_debugFontStyles.word_670650 = 2;
        m_debugFontStyles.word_67066C = 4;
        m_debugFontStyles.unk_672F28 = 1; // common HUD/text default; TODO confirm
        m_debugFontStyles.unk_672F24 = 1; // TODO confirm
        m_debugFontStyles.valid = true;
    } else if (fonbCount == 7) {
        m_debugFontStyles.word_67065C = 3;
        m_debugFontStyles.word_670650 = 4;
        m_debugFontStyles.unk_672F28 = 3; // TODO confirm
        m_debugFontStyles.unk_672F24 = 3; // TODO confirm
        m_debugFontStyles.valid = true;
    }
}


    // 0x004BFE70


int Style::read_sprb_records_REAL(void){
        // IDA 0x4BFE70: reads 12 bytes into field_18, copies to field_14, BuildCumulativeTable.
        // RE debug-only: apply cumulative transform over existing idaView s15 buffer.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->sprb || sta->sprbBytes < 12) return 0;
        if (m_idaView) {
            auto* s15 = reinterpret_cast<unsigned short*>(m_idaView->field_14);
            auto* src = reinterpret_cast<const unsigned short*>(sta->sprb);
            if (s15) {
                unsigned short acc = 0;
                for (int i = 0; i < 6; ++i) { unsigned short c = src[i]; s15[i] = acc; acc = (unsigned short)(acc + c); }
            }
        }
        return 1;
    }


    // 0x004BFF20


int Style::read_palb_chunk_REAL(void){
        // IDA 0x4BFF20: reads 16 bytes S15_0002, copies to field_C, BuildCumulativeTable.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->palb || sta->palbBytes < 16) return 0;
        if (m_idaView) {
            auto* palb = reinterpret_cast<unsigned short*>(m_idaView->S15_0002);
            auto* pali = reinterpret_cast<unsigned short*>((uintptr_t)m_idaView->field_C);
            auto* src = reinterpret_cast<const unsigned short*>(sta->palb);
            if (palb) { for (int i = 0; i < 8; ++i) palb[i] = src[i]; }
            if (pali) {
                unsigned short sum = 0;
                for (int i = 0; i < 8; ++i) { sum = (unsigned short)(sum + (palb ? palb[i] : src[i])); pali[i] = sum; }
            }
        }
        return 1;
    }


    // 0x004BFFE0


bool Style::isCarRecyclable(unsigned char carModel){
        // IDA 0x4BFFE0: scan recy byte array until >= carModel; return recy[v3]==carModel (or true if no recy).
        if (m_idaView && m_idaView->recy) {
            unsigned char* recy = reinterpret_cast<unsigned char*>(m_idaView->recy);
            int v3 = 0;
            if (recy[0] < carModel) {
                do { ++v3; } while (recy[v3] < carModel);
            }
            return recy[v3] == carModel;
        }
        return true; // IDA: if !recy return 1
    }


    // 0x004C0010


int Style::read_recy_chunk_REAL_(void){
        // IDA 0x4C0010: allocates buffer, reads RECY, sets n_recy=size.
        // RE debug-only: capture raw RECY from StyleTiles and expose to idaView adapter.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->recy && sta->recyBytes > 0) {
            if (m_idaView) {
                m_idaView->recy = reinterpret_cast<char*>(sta->recy);
                m_idaView->n_recy = (short)sta->recyBytes;
            }
            return 1;
        }
        return 0;
    }


    // 0x004C00A0


int Style::read_spec_records_REAL(void){
        // IDA 0x4C00A0 calls LoadIndexMap(this,2..10).
        // RE debug-only fallback: SPEC table from StyleTiles (already parsed) -> arr1024.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded) {
            for (int i = 0; i < 1024; ++i) ArrayStyle[i] = sta->spec[i] ? sta->spec[i] : 1;
            if (m_idaView) {
                for (int i = 0; i < 1024; ++i) m_idaView->arr1024[i] = ArrayStyle[i];
            }
            return 1;
        }
        return 0;
    }


    // 0x004C0100


int Style::StyleFixupSprites(void){
        // IDA 0x4C0100: if field_50 && field_48 StyleApplySpriteOffset(); then fix sprx ptrs: sprx[i]+=sprgBase.
        // RE guarded: do NOT apply offset tables (field_50/48 layout/ownership not ported).
        // Apply sprx fixup only when idaView owns/points to raw offsets not already fixed by StyleTiles loader.
        if (!m_idaView) return 0;
        const StyleTileAssets* sta = StyleTiles_Get();
        const bool sprxIsStyleTiles = sta && sta->loaded && sta->sprx &&
            m_idaView->field_20 == (int)reinterpret_cast<uintptr_t>(sta->sprx);
        if (!sprxIsStyleTiles && m_idaView->field_20 && m_idaView->field_34 && m_idaView->field_4) {
            auto* sprx = reinterpret_cast<unsigned char*>((uintptr_t)m_idaView->field_20);
            unsigned int count = (unsigned int)m_idaView->field_4;
            unsigned int sprgBase = (unsigned int)m_idaView->field_34;
            for (unsigned int i = 0; i < count; ++i) {
                unsigned int* p = reinterpret_cast<unsigned int*>(sprx + i * 8u);
                // Guard: if value already looks like pointer in sprg range, skip.
                unsigned int v = *p;
                if (v < (unsigned int)m_idaView->field_38) *p = sprgBase + v;
            }
        }
        return 0;
    }


    // 0x004C0130


void Style::Unload(void){
        // IDA 0x4C0130 frees many style-owned buffers and nulls fields.
        // RE guarded: only clear debug-owned adapter and reset debug-visible RE fields.
        // Do NOT free unknown raw pointers in partial RE object / StyleTiles-owned chunks.
        ClearIdaViewDebug();
        PallitrePal = 0;
        ColorCar = nullptr;
        Tiles = 0;
        // Keep ArrayStyle as-is? IDA does not clear arr1024 in Unload; InitSpecArray is ctor behavior.
    }


    // 0x004C0580


int Style::read_cari_records_REAL(void){
        // IDA 0x4C0580: CreateBuffer+Read CARI into field_58, then LoadCariRecords builds pCar_5C.
        // RE debug-only: bind raw CARI to idaView.field_58. pCar_5C construction is not ported
        // (S284/CarInfo layout/alloc semantics not fully confirmed for RE runtime).
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->cari) return 0;
        if (m_idaView) m_idaView->field_58 = (int)reinterpret_cast<uintptr_t>(sta->cari);
        return 1;
    }


    // 0x004C05B0


int Style::parse_chunk(void){
        // IDA 0x4C05B0: dispatches by 4cc tag to read_* and seeks unknown chunks.
        // RE: original takes (char* tag, int size) and uses FileMgr::Seek. We don't have RE FileMgr
        // parity here; keep this symbol as guarded stub. Debug adapter path uses Style::Load guarded bindings.
        return 0;
    }


    // 0x004C2EB0


int Style::GetTileArray(unsigned short a2){
        // IDA 0x4C2EB0: Tiles + (((a2&3) + ((a2&0xFC)<<6))<<6)
        int tiles = 0;
        if (m_idaView) tiles = m_idaView->Tiles;
        if (!tiles) {
            const StyleTileAssets* sta = StyleTiles_Get();
            if (sta && sta->loaded && sta->tile) tiles = (int)(uintptr_t)sta->tile;
        }
        if (!tiles) return 0;
        int v2 = a2 & 0xFC;
        return tiles + (((a2 & 3) + (v2 << 6)) << 6);
    }


    // 0x004C2EE0


bool Style::has_tiles(void){
        if (m_idaView) return m_idaView->Tiles != 0;
        const StyleTileAssets* sta = StyleTiles_Get();
        return sta && sta->loaded && sta->tile != nullptr;
    }


    // 0x004C6C90


int Style::GetSprite(unsigned short idx){
        // IDA 0x4BF280: return field_20 + 8 * idx.
        if (m_idaView && m_idaView->field_20) {
            return m_idaView->field_20 + 8 * (int)idx;
        }
        // Fallback to StyleTiles debug sprx if bound (debug-only adapter).
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->sprx && sta->sprxBytes >= 8u) {
            unsigned int count = sta->sprxBytes / 8u;
            if ((unsigned int)idx < count) {
                return (int)(uintptr_t)(sta->sprx + (unsigned int)idx * 8u);
            }
        }
        return 0;
    }

int Style::GetSpriteData(unsigned short a2, unsigned char a3){
        // IDA 0x4BF230: uses field_54 sprite-data table.
        if (!m_idaView || !m_idaView->field_54) return 0;
        unsigned char* v3 = (unsigned char*)(uintptr_t)m_idaView->field_54;
        unsigned short count = *(unsigned short*)v3;
        if (a2 >= count) return 0;
        unsigned int entryOff = *(unsigned int*)(v3 + 2u * a2 + 2u);
        if (!entryOff) return 0;
        unsigned char* rec = v3 + entryOff;
        unsigned char n = *(unsigned char*)(rec + 2);
        if (a3 >= n) return 0;
        unsigned short w = *(unsigned short*)(rec + 8u * a3 + 8u);
        if (w == 0) return 0;
        return (int)(uintptr_t)(rec + 8u * a3 + 4u);
    }

unsigned char Style::getSpriteWidth(unsigned short a2){
        // IDA 0x420220: *(BYTE*)(GetSprite+4)
        int spr = GetSprite(a2);
        if (!spr) return 0;
        return *(unsigned char*)((uintptr_t)spr + 4);
    }

unsigned char Style::GetSpriteFlag(unsigned short a2){
        // IDA 0x4C6C90: *(BYTE*)(GetSprite+5)
        int spr = GetSprite(a2);
        if (!spr) return 0;
        return *(unsigned char*)((uintptr_t)spr + 5);
    }

unsigned int Style::GetSpriteCount() const {
        // IDA 0x4B9F20: return field_4 - 1
        if (m_idaView) {
            unsigned int f4 = (unsigned int)m_idaView->field_4;
            return f4 ? (f4 - 1u) : 0u;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->sprxBytes >= 8u) return sta->sprxBytes / 8u;
        return 0;
    }
    // 0x004C0380
void Style::CopyBlock(void){
        // IDA 0x4C0380 signature/semantics depend on original layout; RE guarded no-op.
    }

    // 0x004C23D0
unsigned short Style::GetCharData(short a1){
        // IDA 0x4C23D0: return Style::GetRemapColour16(&a1)
        unsigned short v = (unsigned short)a1;
        return (unsigned short)GetRemapColour16(&v);
    }
