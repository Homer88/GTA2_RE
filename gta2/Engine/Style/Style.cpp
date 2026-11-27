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
    this->InitSpecArray();
    this->m_idaView = nullptr;
    this->m_idaViewOwned = nullptr;
    //TODO      
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
        unsigned short s15[6];  // SPRB bases (field_14)
        unsigned short palb[8]; // PALB palette counts (S15_0002)
        unsigned short pali[8]; // PALB-derived cumulative bases (field_C)
    };
    auto* ad = static_cast<IdaAdapter*>(std::malloc(sizeof(IdaAdapter)));
    if (!ad) return false;
    std::memset(ad, 0, sizeof(IdaAdapter));

    // SPRB: 6 u16 cumulative/base offsets for sprite types 2,3,4/8,5,6,7.
    std::memcpy(ad->s15, sta->sprb, 12);
    // PALB: 8 u16 palette counts. IDA Style::read_palb_chunk_REAL stores raw into S15_0002
    // and cumulative bases into field_C.
    if (sta->palb && sta->palbBytes >= 16) std::memcpy(ad->palb, sta->palb, 16);
    std::memcpy(ad->pali, ad->palb, 16);
    unsigned short acc = 0;
    for (int i = 0; i < 8; ++i) { unsigned short c = ad->pali[i]; ad->pali[i] = acc; acc = (unsigned short)(acc + c); }

    ad->view.field_14 = ad->s15;
    ad->view.S15_0002 = ad->palb;
    ad->view.field_C = (int)reinterpret_cast<uintptr_t>(ad->pali);
    ad->view.field_20 = (int)reinterpret_cast<uintptr_t>(sta->sprx); // sprx entries: 8 bytes each in IDA usage
    ad->view.Car = sta->fonb;      // FONB starts with count u16, then u16 table
    ad->view.field_4 = (unsigned short)(sta->sprxBytes / 8u);
    ad->view.field_6 = sta->obji ? (unsigned short)(sta->objiBytes / 2u) : 0;
    ad->view.field_58 = (int)reinterpret_cast<uintptr_t>(sta->cari);
    ad->view.Tiles = (int)reinterpret_cast<uintptr_t>(sta->tile); // debug hint only, not IDA-canonical
    ad->view.n_recy = 0;

    m_idaViewOwned = ad;
    m_idaView = &ad->view;
    m_idaViewSprxBytes = sta->sprxBytes;
    m_idaViewFonbBytes = sta->fonbBytes;
    return true;
}

void Style::Load(char* FileName) {
    FileMgr* pFileMng;
    //pFileMng->FileOpen(FileName);

}

void Style::InitSpecArray() {
    
    for (int i = 0; i < 1024; ++i) {
        this->ArrayStyle[i] = 1;
    }
}
void Style::LoadFileSTY(char* fileName) {

}
int Style::CarExist(void){
        return 0;
    }


    // 0x00420220


int Style::getSpriteWidth(void){
        return 0;
    }


    // 0x00432850


int Style::GetNumberOfCars(void){
        return 0;
    }


    // 0x00432860


void Style::SetXY(int arg0,int arg1){

    }


    // 0x00462FB0


int Style::IsMapTileSpecial(int param_1,unsigned int param_2){
        return 0;
    }


    // 0x00462FD0


int Style::StyleGetSlotAttr(void){
        return 0;
    }


    // 0x00463020


unsigned char Style::IsPointInRect(unsigned char param_1,unsigned char param_2){
        return 0;
    }


    // 0x004B9F20


int Style::StyleGetSpriteCount(void){
        return 0;
    }


    // 0x004BF1F0


int Style::getCarModelById(void){
        return 0;
    }


    // 0x004BF210


int Style::GetCarModel(void){
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
        // IDA 0x4BF3A0: S15_0002 has palette counts by index.
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
                case 9: return (short)p[8];
                default: return 0;
            }
        }
        (void)a2; return 0;
    }


    // 0x004BF430


short Style::get_global_palette_id(int palette_type, short palette_id){
        // IDA 0x4BF430: field_C is S15 array of base offsets.
        if (m_idaView && m_idaView->field_C) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->field_C);
            switch (palette_type) {
                case 1: return (short)(palette_id + p[0]);
                case 2: return (short)(palette_id + p[1]);
                case 3: return (short)(palette_id + p[2]);
                case 4: return (short)(palette_id + p[3]);
                case 5: return (short)(palette_id + p[4]);
                case 6: return (short)(palette_id + p[5]);
                case 7: return (short)(palette_id + p[6]);
                case 8: return (short)(palette_id + p[7]);
                case 9: return (short)(palette_id + p[8]);
                default: return palette_id;
            }
        }
        (void)palette_type; return palette_id;
    }


    // 0x004BF4E0


int Style::GetColourBank(short a2){
        // IDA 0x4BF4E0: field_2C + 4*((a2&0x3F)+((a2&0xFFC0)<<8)). Returns ptr in IDA.
        // Guarded: no real field_2C in RE; return 0.
        (void)a2; return 0;
    }


    // 0x004BF530


short Style::GetPhysPalette(unsigned short a2){
        // IDA 0x4BF530: *((_WORD*)field_28 + a2)
        if (m_idaView && m_idaView->field_28) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->field_28);
            return (short)p[a2];
        }
        (void)a2; return 0;
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
    if (m_idaView && m_idaView->field_20 && m_idaView->field_14 && m_idaView->Car) {
        if (*style == 1) return 16; // word_67065C[0] typical; TODO confirm globals
        if (*style == 2) return 32; // word_670650 typical; TODO confirm globals
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
        if (m_idaView && m_idaView->field_20 && m_idaView->field_14 && m_idaView->Car) {
            if (*a2 == 1) return 16; // TODO: use word_67065C[0]
            if (*a2 == 2) return 32; // TODO: use word_670650
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
        if (m_idaView && m_idaView->field_20 && m_idaView->field_14 && m_idaView->Car) {
            if (*style == 1) return 17; // TODO: use word_67065C[0]
            if (*style == 2) return 34; // TODO: use word_670650
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


    // 0x004BF740


unsigned short Style::GetPallitrePal(){
        if (m_idaView) return m_idaView->PalitrePal;
        return PallitrePal;
    }


    // 0x004BF750


int Style::get_obji_by_idx(void){
        return 0;
    }


    // 0x004BF770


int Style::ChangeTileByIdx(void){
        return 0;
    }


    // 0x004BF7F0


int Style::StyleInitSpriteTable(void){
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
        return 0;
    }


    // 0x004BFAB0


int Style::read_dels_records_REAL(void){
        return 0;
    }


    // 0x004BFAD0


int Style::read_tile_chunk_REAL(void){
        return 0;
    }


    // 0x004BFB00


int Style::read_ovly_records_REAL_(void){
        return 0;
    }


    // 0x004BFB10


int Style::read_psxt_records_REAL(void){
        return 0;
    }


    // 0x004BFB20


int Style::read_sprg_records_REAL(void){
        return 0;
    }


    // 0x004BFB50


int Style::read_ppal_records_REAL(void){
        return 0;
    }


    // 0x004BFB80


int Style::read_palx_records_REAL(void){
        return 0;
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
        return 0;
    }


    // 0x004BFF20


int Style::read_palb_chunk_REAL(void){
        return 0;
    }


    // 0x004BFFE0


int Style::isCarRecyclable(void){
        return 0;
    }


    // 0x004C0010


int Style::read_recy_chunk_REAL_(void){
        return 0;
    }


    // 0x004C00A0


int Style::read_spec_records_REAL(void){
        return 0;
    }


    // 0x004C0100


int Style::StyleFixupSprites(void){
        return 0;
    }


    // 0x004C0130


int Style::Unload(void){
        return 0;
    }


    // 0x004C0580


int Style::read_cari_records_REAL(void){
        return 0;
    }


    // 0x004C05B0


int Style::parse_chunk(void){
        return 0;
    }


    // 0x004C2EB0


int Style::GetTileArray(void){
        return 0;
    }


    // 0x004C2EE0


int Style::has_tiles(void){
        return 0;
    }


    // 0x004C6C90


int Style::GetSprite(unsigned short idx){
        // IDA 0x4BF280: return field_20 + 8 * idx.
        if (m_idaView && m_idaView->field_20) {
            return m_idaView->field_20 + 8 * (int)idx;
        }
        (void)idx;
        return 0;
    }

int Style::GetSpriteFlag(void){
        return 0;
    }