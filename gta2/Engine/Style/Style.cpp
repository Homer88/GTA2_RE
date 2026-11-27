#include "Style.h"
#include "../FileMgr/FileMgr.h"
#include "../Memory/Memory.h"
#include "../ultil/WinApi.h"
#include "../Debug/DebugLogFile.h"
#include "StyleTileLoader.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
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

void Style::TrackFileMgrOwned(void* p, unsigned char kind) {
    if (!p) return;
    for (int i = 0; i < m_fileMgrOwnedCount; ++i) if (m_fileMgrOwnedPtrs[i] == p) return;
    if (m_fileMgrOwnedCount < 64) {
        m_fileMgrOwnedPtrs[m_fileMgrOwnedCount] = p;
        m_fileMgrOwnedKind[m_fileMgrOwnedCount] = kind;
        ++m_fileMgrOwnedCount;
    } else {
        // Guarded debug path: avoid leak explosion; free immediately only for malloc-kind.
        if (kind == 1) std::free(p);
    }
}

void Style::ClearFileMgrOwnedDebug() {
    for (int i = 0; i < m_fileMgrOwnedCount; ++i) {
        void* p = m_fileMgrOwnedPtrs[i];
        unsigned char k = m_fileMgrOwnedKind[i];
        if (p && k == 1) std::free(p);
        m_fileMgrOwnedPtrs[i] = nullptr;
        m_fileMgrOwnedKind[i] = 0;
    }
    m_fileMgrOwnedCount = 0;
}

static void Style_BuildCumulativeTableU16(unsigned short* arr, int count) {
    // IDA 0x4BF7B0
    if (!arr || count <= 0) return;
    for (int i = count - 1; i > 0; --i) arr[i] = arr[i - 1];
    arr[0] = 0;
    for (int i = 1; i < count; ++i) arr[i] = (unsigned short)(arr[i] + arr[i - 1]);
}

static unsigned short Style_SumShortArrayU16(const unsigned short* arr, unsigned int count) {
    // IDA 0x4BF790
    unsigned short s = 0;
    for (unsigned int i = 0; i < count; ++i) s = (unsigned short)(s + arr[i]);
    return s;
}

void Style::ClearIdaViewDebug() {
    ClearFileMgrOwnedDebug();
    if (m_idaViewOwned) {
        std::free(m_idaViewOwned);
        m_idaViewOwned = nullptr;
    }
    m_idaView = nullptr;
    m_idaViewSprxBytes = 0;
    m_idaViewFonbBytes = 0;
}

bool Style::EnsureIdaViewForFileMgrDebug() {
    if (m_idaView) return true;
    // Empty idaView for guarded FileMgr path. Not IDA-canonical object layout.
    auto* v = static_cast<StyleIdaView*>(std::malloc(sizeof(StyleIdaView)));
    if (!v) return false;
    std::memset(v, 0, sizeof(StyleIdaView));
    m_idaViewOwned = v;
    m_idaView = v;
    m_idaViewSprxBytes = 0;
    m_idaViewFonbBytes = 0;
    return true;
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
    // Default behavior unchanged: no FileMgr load unless explicitly enabled.
    const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
    if (fm && fm[0] == '1' && FileName && *FileName) {
        // Guarded debug-only FileMgr path. FileMgr::Read/ReadLine semantics in RE are not fully IDA-proven.
        ClearIdaViewDebug();
        if (!EnsureIdaViewForFileMgrDebug()) return;
        InitSpecArray(); // IDA ctor inits to 1; reset for clean FileMgr debug load
        if (m_idaView) for (int i = 0; i < 1024; ++i) m_idaView->arr1024[i] = 1;
        FILE* f = FileMgr::FileOpenStatic(FileName, "rb");
        if (f) {
            unsigned char hdr[8] = {};
            size_t sz8 = 8;
            if (FileMgr::Read(hdr, &sz8) == 8) {
                const bool tagOk = std::memcmp(hdr, "GBST", 4) == 0;
                unsigned short ver = (unsigned short)(hdr[4] | (hdr[5] << 8));
                if (!tagOk || ver != 700) {
                    std::FILE* lf = std::fopen("gta2_style_filemgr.log", "a");
                    if (lf) { std::fprintf(lf, "style-filemgr bad GBST header tagOk=%d ver=%u file=%s\n", tagOk?1:0, (unsigned)ver, FileName ? FileName : ""); std::fclose(lf); }
                }
                if (!tagOk || ver != 700) {
                    FileMgr::CloseFile();
                    ClearIdaViewDebug();
                    // fall through to StyleTiles debug fallback
                } else {
                // IDA loop: for (size=8; ReadLine(a1,a1,&size); size=8) if (chunk_size) parse_chunk(a1,chunk_size)
                // ReadLine is not decompiled in export; chunk headers are 8 bytes (4cc+u32 size).
                int styleChunkCount = 0;
                for (;;) {
                    char tag[4] = {};
                    unsigned int chunkSize = 0;
                    unsigned char ch[8] = {};
                    size_t chsz = 8;
                    size_t got = FileMgr::Read(ch, &chsz);
                    if (got != 8) break;
                    std::memcpy(tag, ch, 4);
                    std::memcpy(&chunkSize, ch + 4, 4);
                    ++styleChunkCount;
                    if (chunkSize) {
                        // Guarded debug path: avoid absurd allocations on corrupt/misaligned reads.
                        if (chunkSize > 0x04000000u) {
                            int skip = (int)chunkSize;
                            FileMgr::SeekPtr(&skip);
                        } else {
                            (void)parse_chunk(tag, chunkSize);
                        }
                    }
                }
                if (const char* dbg = std::getenv("GTA2_STYLE_IDA_FILEMGR")) {
                    if (dbg[0] == '1') {
                        FILE* lf = std::fopen("gta2_style_filemgr.log", "a");
                        if (lf) {
                            std::fprintf(lf, "style-filemgr file=%s chunks=%d idaView=%p\n", FileName ? FileName : "(null)", styleChunkCount, (void*)m_idaView);
                            std::fclose(lf);
                        }
                    }
                }
                }
            }
            if (FileMgr::IsOpen()) FileMgr::CloseFile();
            if (m_idaView) {
                (void)StyleFixupSprites();
                // If GTA2_STYLE_IDA_VIEW requested but no idaView was populated by FileMgr reads,
                // fall back to StyleTiles debug adapter. Do NOT overwrite FileMgr-populated idaView.
                if (!m_idaView) (void)BindIdaViewFromStyleTilesDebug();
                return;
            }
            // Bad header/read or no idaView: fall through to StyleTiles debug fallback.
        }
        // fall through to debug adapter fallback
    }

    // RE guarded fallback: original FileMgr semantics in RE are not fully equivalent to IDA; avoid changing
    // default behavior. Debug-only: if GTA2_STYLE_IDA_VIEW=1 and StyleTiles debug assets are loaded,
    // bind idaView and run guarded read_* debug bindings (no FileMgr/NewMemory/CreateBuffer emulation).
    (void)FileName;
    if (!BindIdaViewFromStyleTilesDebug()) return;
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
            unsigned int off = 4u * ((a2 & 0x3Fu) + ((a2 & 0xFFC0u) << 8));
            unsigned int f30 = (unsigned int)m_idaView->field_30;
            // Guarded heuristic: FileMgr debug PPAL stores raw NewMemory out ptr in field_30 (IDA-shaped),
            // StyleTiles debug adapter stores ppalBytes. Only bound-check when it looks like a size.
            if (f30 && f30 < 0x01000000u && off + 4u > f30) return 0;
            return (unsigned int)(m_idaView->field_2C + off);
        }
        return 0;
    }


    // 0x004BF530


unsigned short Style::GetPhysPalette(unsigned short a2){
        // IDA 0x4BF530: *((_WORD*)field_28 + a2). PALX is 0x8000 bytes = 16384 u16.
        if (m_idaView && m_idaView->field_28) {
            if (a2 >= 0x4000u) return 0; // guarded bound for 0x8000-byte PALX
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
            unsigned int fonbCount = 0;
            if (m_idaViewFonbBytes >= 2u) fonbCount = (unsigned int)*reinterpret_cast<unsigned short*>(m_idaView->Car);
            unsigned int idx = (unsigned int)a2 + 1u;
            if (fonbCount && idx > fonbCount) return 0; // guarded FONB bound
            auto* carWords = reinterpret_cast<unsigned short*>(m_idaView->Car);
            return (short)(a3 + carWords[idx]);
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
        unsigned int fonbCount = m_idaViewFonbBytes >= 2u ? (unsigned int)*reinterpret_cast<unsigned short*>(m_idaView->Car) : 0u;
        if (fonbCount && styleOff > fonbCount) return 8; // guarded FONB bound
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
            unsigned int fonbCount = m_idaViewFonbBytes >= 2u ? (unsigned int)*reinterpret_cast<unsigned short*>(m_idaView->Car) : 0u;
            if (fonbCount && styleOff > fonbCount) return 0; // guarded FONB bound
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
            unsigned int fonbCount = m_idaViewFonbBytes >= 2u ? (unsigned int)*reinterpret_cast<unsigned short*>(m_idaView->Car) : 0u;
            if (fonbCount && styleOff > fonbCount) return 0; // guarded FONB bound
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
        // IDA 0x4BF770: S1501[a2] = a3. Guarded bounds for debug safety.
        if (a2 >= 1024u) return;
        if (m_idaView && m_idaView->S1501) {
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
            p[a2] = (unsigned short)a3;
            return;
        }
        // Debug fallback: StyleTiles s1501
        StyleTileAssets* sta = const_cast<StyleTileAssets*>(StyleTiles_Get());
        if (sta && sta->loaded) {
            sta->s1501[a2] = (unsigned short)a3;
        }
    }


    // 0x004BF7F0


int Style::StyleInitSpriteTable(void){
        // IDA 0x4BF7F0: alloc 2048, fill 0..991, last 32 zero.
        // Guarded FileMgr debug path may need to allocate S1501; track ownership.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && EnsureIdaViewForFileMgrDebug()) {
            if (!m_idaView->S1501) {
                void* buf = std::malloc(2048u);
                if (!buf) return 0;
                TrackFileMgrOwned(buf, 1);
                m_idaView->S1501 = buf;
            }
            auto* p = reinterpret_cast<unsigned short*>(m_idaView->S1501);
            for (unsigned short i = 0; i < 992; ++i) p[i] = i;
            for (unsigned short i = 992; i < 1024; ++i) p[i] = 0;
            return 2048;
        }
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
        (void)param_1; (void)param_2;
    }

int Style::BuildSpriteBuffer(unsigned int sizeBytes) {
    // IDA 0x4BF840: compute delx3 from DELX records, alloc field_50, decode records.
    // Guarded debug-only: requires FileMgr debug path and tracked field_4C.
    const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
    if (!fm || fm[0] != '1' || !m_idaView) return 0;
    if (!m_idaView->field_4C || !sizeBytes) return 0;
    bool tracked = false;
    for (int i = 0; i < m_fileMgrOwnedCount; ++i) if (m_fileMgrOwnedPtrs[i] == (void*)(uintptr_t)m_idaView->field_4C) { tracked = true; break; }
    if (!tracked) return 0;

    auto* src0 = reinterpret_cast<const unsigned char*>((uintptr_t)m_idaView->field_4C);
    unsigned int srcOff = 0;
    unsigned int delx3 = 0;
    while (srcOff + 4u <= sizeBytes) {
        unsigned char count = src0[srcOff + 2];
        unsigned int inRec = 2u * (unsigned int)count + 4u;
        unsigned int outRec = 8u * (unsigned int)count + 4u;
        delx3 += outRec;
        srcOff += inRec;
        if (inRec < 4u) break;
    }
    if (!delx3) return 0;

    void* outBuf = CreateBuffer(delx3);
    if (!outBuf) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr DELX build alloc failed size=%u\n",delx3); std::fclose(f);} return 0; }
    TrackFileMgrOwned(outBuf, 1);
    auto* dst0 = reinterpret_cast<unsigned char*>(outBuf);
    unsigned int srcPos = 0;
    unsigned int dstPos = 0;
    unsigned int v4 = 0; // accumulator from IDA
    while (srcPos + 4u <= sizeBytes && dstPos < delx3) {
        unsigned char count = src0[srcPos + 2];
        unsigned int inRec = 2u * (unsigned int)count + 4u;
        unsigned int outRec = 8u * (unsigned int)count + 4u;
        if (dstPos + outRec > delx3 || srcPos + inRec > sizeBytes) break;
        unsigned char* j = dst0 + dstPos;
        *(unsigned short*)j = *(const unsigned short*)(src0 + srcPos);
        j[2] = count;
        j[3] = 0;
        if (count) {
            unsigned char* v12 = j + 8;
            const short* v13 = reinterpret_cast<const short*>(src0 + srcPos + 4);
            for (unsigned char k = 0; k < count; ++k) {
                short v14 = v13[k];
                *(unsigned int*)(v12 - 4) = v4;
                *(short*)v12 = v14;
                v4 += (unsigned short)v14;
                v12 += 8;
            }
        }
        dstPos += outRec;
        srcPos += inRec;
    }
    m_idaView->field_50 = (int)reinterpret_cast<uintptr_t>(dst0);
    m_idaView->delx3 = (int)delx3;
    return 1;
}


    // 0x004BF900


int Style::StyleApplySpriteOffset(void){
        // IDA 0x4BF900: for each record in field_50/delx3, add field_48 to each entry offset.
        // Guarded debug-only: only FileMgr debug path and tracked field_50.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (!fm || fm[0] != '1' || !m_idaView) return 0;
        if (!m_idaView->field_50 || m_idaView->delx3 <= 0 || !m_idaView->field_48) return 0;
        bool tracked50 = false;
        for (int i = 0; i < m_fileMgrOwnedCount; ++i) if (m_fileMgrOwnedPtrs[i] == (void*)(uintptr_t)m_idaView->field_50) { tracked50 = true; break; }
        if (!tracked50) return 0;
        auto* base = reinterpret_cast<unsigned char*>((uintptr_t)m_idaView->field_50);
        unsigned int delx3 = (unsigned int)m_idaView->delx3;
        unsigned int off = 0;
        while (off + 4u <= delx3) {
            unsigned char count = base[off + 2];
            unsigned int rec = 4u + 8u * (unsigned int)count;
            if (off + rec > delx3) break;
            for (unsigned char k = 0; k < count; ++k) {
                unsigned int* p = reinterpret_cast<unsigned int*>(base + off + 4u + 8u * k);
                *p += (unsigned int)m_idaView->field_48;
            }
            off += rec;
            if (rec == 0) break;
        }
        return (int)off;
    }


    // 0x004BF950


int Style::StyleAddSpriteOffset(void){
        return 0;
    }


    // 0x004BF980


void Style::BuildSpriteLookup(int param_1){
        (void)param_1;
    }

int Style::BuildSpriteLookup() {
    // IDA 0x4BF980: builds field_54 lookup table from field_50/delx3.
    // Guarded debug-only partial port: only when FileMgr debug path active and buffers are tracked.
    const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
    if (!fm || fm[0] != '1' || !m_idaView) return 0;
    if (!m_idaView->field_50 || m_idaView->delx3 <= 0) return 0;
    bool tracked50 = false;
    for (int i = 0; i < m_fileMgrOwnedCount; ++i) if (m_fileMgrOwnedPtrs[i]) {
        // field_50 may be aligned inside tracked NewMemory block; conservative: allow if exact tracked.
        if (m_fileMgrOwnedPtrs[i] == (void*)(uintptr_t)m_idaView->field_50) { tracked50 = true; break; }
    }
    // If not exact tracked, still allow when delx3 small and field_50 points into heap? No: keep guarded.
    if (!tracked50) return 0;

    auto* base = reinterpret_cast<unsigned char*>((uintptr_t)m_idaView->field_50);
    unsigned int delx3 = (unsigned int)m_idaView->delx3;
    unsigned int off = 0;
    unsigned short maxIdx = 0;
    while (off + 4 <= delx3) {
        unsigned short idx = *(unsigned short*)(base + off);
        unsigned char count = *(base + off + 2);
        if (idx > maxIdx) maxIdx = idx;
        unsigned int rec = 4u + 8u * (unsigned int)count;
        off += rec;
        if (rec == 0) break;
    }
    if (maxIdx == 0 || maxIdx > 4096) return 0;
    size_t tableBytes = (size_t)(maxIdx + 2) * 4u;
    void* tbl = CreateBuffer(tableBytes);
    if (!tbl) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr DELX lookup alloc failed size=%u\n",(unsigned)tableBytes); std::fclose(f);} return 0; }
    TrackFileMgrOwned(tbl, 1);
    std::memset(tbl, 0, tableBytes);
    *(unsigned short*)tbl = (unsigned short)(maxIdx + 1);
    off = 0;
    while (off + 4 <= delx3) {
        unsigned short idx = *(unsigned short*)(base + off);
        unsigned char count = *(base + off + 2);
        unsigned int rec = 4u + 8u * (unsigned int)count;
        if (idx + 1u < (unsigned int)(maxIdx + 2u)) {
            ((unsigned int*)tbl)[idx + 1u] = (unsigned int)((uintptr_t)base + off);
        }
        off += rec;
        if (rec == 0) break;
    }
    m_idaView->field_54 = (int)reinterpret_cast<uintptr_t>(tbl);
    return 1;
}


    // 0x004BFA60


int Style::read_delx_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFA60: CreateBuffer + FileMgr::Read into field_4C, BuildSpriteBuffer, BuildSpriteLookup.
        // Guarded FileMgr path: only when GTA2_STYLE_IDA_FILEMGR=1 and stream open.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            void* buf = CreateBuffer(dwBytes);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr DELX alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf, 1);
            if (EnsureIdaViewForFileMgrDebug()) m_idaView->field_4C = (int)reinterpret_cast<uintptr_t>(buf);
            size_t sz = dwBytes;
            FileMgr::Read(buf, &sz);
            m_idaView->delx3 = (int)dwBytes;
            // Guarded debug-only partial build. Exact IDA decode/lookup not fully ported.
            (void)BuildSpriteBuffer(dwBytes);
            (void)BuildSpriteLookup();
            // IDA 0x4BFA60 frees field_4C and clears it after build.
            for (int i = 0; i < m_fileMgrOwnedCount; ++i) {
                if (m_fileMgrOwnedPtrs[i] == buf) {
                    if (m_fileMgrOwnedKind[i] == 1) std::free(buf);
                    m_fileMgrOwnedPtrs[i] = m_fileMgrOwnedPtrs[m_fileMgrOwnedCount - 1];
                    m_fileMgrOwnedKind[i] = m_fileMgrOwnedKind[m_fileMgrOwnedCount - 1];
                    m_fileMgrOwnedPtrs[m_fileMgrOwnedCount - 1] = nullptr;
                    m_fileMgrOwnedKind[m_fileMgrOwnedCount - 1] = 0;
                    --m_fileMgrOwnedCount;
                    break;
                }
            }
            if (m_idaView) m_idaView->field_4C = 0;
            return 1;
        }
        // Debug fallback: raw DELX bind only.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->delx) return 0;
        if (m_idaView) m_idaView->field_4C = (int)reinterpret_cast<uintptr_t>(sta->delx);
        return 1;
    }


    // 0x004BFAB0


int Style::read_dels_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFAB0: CreateBuffer + FileMgr::Read into field_48.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            void* buf = CreateBuffer(dwBytes);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr DELS alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf, 1);
            if (EnsureIdaViewForFileMgrDebug()) m_idaView->field_48 = (int)reinterpret_cast<uintptr_t>(buf);
            size_t sz = dwBytes;
            FileMgr::Read(buf, &sz);
            return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->dels) return 0;
        if (m_idaView) m_idaView->field_48 = (int)reinterpret_cast<uintptr_t>(sta->dels);
        return 1;
    }


    // 0x004BFAD0


int Style::read_tile_chunk_REAL(unsigned int dwBytes){
        // IDA 0x4BFB00: NewMemory+Read TILE into Tiles/field_44, StyleInitSpriteTable.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            void* out = nullptr;
            unsigned int aligned = NewMemory(dwBytes, &out);
            void* buf = (void*)(uintptr_t)aligned;
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr TILE alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(out, 1);
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->Tiles = (int)reinterpret_cast<uintptr_t>(buf); m_idaView->field_44 = (int)out; }
            size_t sz = dwBytes;
            FileMgr::Read(buf, &sz);
            return StyleInitSpriteTable();
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->tile) return 0;
        Tiles = (int)reinterpret_cast<uintptr_t>(sta->tile); // debug hint only
        if (m_idaView) { m_idaView->Tiles = (int)reinterpret_cast<uintptr_t>(sta->tile); m_idaView->field_44 = (int)sta->tileBytes; }
        return StyleInitSpriteTable();
    }


    // 0x004BFB00


int Style::read_ovly_records_REAL_(unsigned int dwBytes){
        // IDA 0x4BFB10: FileMgr::Seek over chunk; no data stored.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) { int s = (int)dwBytes; FileMgr::SeekPtr(&s); }
        return 1;
    }


    // 0x004BFB10


int Style::read_psxt_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFB10: FileMgr::Seek over chunk; no data stored.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) { int s = (int)dwBytes; FileMgr::SeekPtr(&s); }
        return 1;
    }


    // 0x004BFB20


int Style::read_sprg_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFB30: NewMemory+Read into field_34/field_38.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            void* out = nullptr; unsigned int aligned = NewMemory(dwBytes, &out);
            void* buf = (void*)(uintptr_t)aligned;
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr SPRG alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(out, 1); // NewMemory raw buffer
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->field_34 = (int)reinterpret_cast<uintptr_t>(buf); m_idaView->field_38 = (int)out; }
            size_t sz = dwBytes; FileMgr::Read(buf, &sz); return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->sprg) return 0;
        if (m_idaView) { m_idaView->field_34 = (int)reinterpret_cast<uintptr_t>(sta->sprg); m_idaView->field_38 = (int)sta->sprgBytes; }
        return 1;
    }


    // 0x004BFB50


int Style::read_ppal_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFB50: NewMemory+Read into field_2C/field_30, PalitrePal = size>>10.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            void* out = nullptr; unsigned int aligned = NewMemory(dwBytes, &out);
            void* buf = (void*)(uintptr_t)aligned;
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr PPAL alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(out, 1); // NewMemory raw buffer
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->field_2C = (int)reinterpret_cast<uintptr_t>(buf); m_idaView->field_30 = (int)out; m_idaView->PalitrePal = (unsigned short)(dwBytes >> 10); }
            PallitrePal = (unsigned short)(dwBytes >> 10);
            size_t sz = dwBytes; FileMgr::Read(buf, &sz); return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->ppal) return 0;
        unsigned int palCount = sta->physPalCount;
        PallitrePal = (unsigned short)palCount;
        if (m_idaView) { m_idaView->field_2C = (int)reinterpret_cast<uintptr_t>(sta->ppal); m_idaView->field_30 = (int)sta->ppalBytes; m_idaView->PalitrePal = (unsigned short)palCount; }
        return 1;
    }


    // 0x004BFB80


int Style::read_palx_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFB80: expects 0x8000, operator_new(0x8000), reads into field_28.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            if (dwBytes != 0x8000u) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr PALX unexpected size=%u\n", dwBytes); std::fclose(f); }
                int s = (int)dwBytes; FileMgr::SeekPtr(&s);
                return 0;
            }
            void* buf = std::malloc(0x8000u);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr PALX alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf,1);
            if (EnsureIdaViewForFileMgrDebug()) m_idaView->field_28 = buf;
            size_t sz = 0x8000u;
            FileMgr::Read(buf, &sz);
            return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->palx) return 0;
        if (m_idaView) m_idaView->field_28 = sta->palx;
        return 1;
    }

    // 0x004BFBE0

int Style::read_obji_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFBE0: CreateBuffer+Read obji into field_24, field_6=size>>1. Guarded debug path.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            unsigned int v4 = dwBytes;
            bool bad = false;
            if ((dwBytes >> 1) >= 0x10000u) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr OBJI too large size=%u\n", dwBytes); std::fclose(f); }
                bad = true;
            }
            if ((2u * (unsigned short)(v4 >> 1)) != v4) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr OBJI odd size=%u\n", v4); std::fclose(f); }
                bad = true;
            }
            if (bad) {
                int s = (int)dwBytes; FileMgr::SeekPtr(&s);
                return 0;
            }
            void* buf = CreateBuffer(dwBytes);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr OBJI alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf,1);
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->field_24 = (int)reinterpret_cast<uintptr_t>(buf); m_idaView->field_6 = (unsigned short)(v4 >> 1); }
            size_t sz = dwBytes; FileMgr::Read(buf, &sz); return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->obji) return 0;
        if (m_idaView) { m_idaView->field_24 = (int)reinterpret_cast<uintptr_t>(sta->obji); m_idaView->field_6 = (unsigned short)(sta->objiBytes / 2u); }
        return 1;
    }

    // 0x004BFC60

int Style::read_sprx_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFC60: CreateBuffer(dwBytes+8)+Read sprx into field_20, field_4=(size>>3)+1.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            // IDA 0x4BFC60: if (size>>3 > 0xFFFF) DebugLog(0x3ED,"style.cpp",1202); field_4=(v4>>3)+1
            unsigned int v4 = dwBytes;
            if ((dwBytes >> 3) > 0xFFFFu) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr SPRX too many sprites size=%u\n", dwBytes); std::fclose(f); }
                // Decompilation shows v4=a2 fallback; keep guarded/log-only, do not fake unknown semantics.
            }
            unsigned int alloc = dwBytes + 8u; // IDA: CreateBuffer(v6+8)
            void* buf = CreateBuffer(alloc);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr SPRX alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf,1);
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->field_20 = (int)reinterpret_cast<uintptr_t>(buf); m_idaView->field_4 = (unsigned short)((v4 >> 3) + 1u); }
            m_idaViewSprxBytes = dwBytes;
            size_t sz = dwBytes; FileMgr::Read(buf, &sz); return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->sprx) return 0;
        if (m_idaView) { m_idaView->field_20 = (int)reinterpret_cast<uintptr_t>(sta->sprx); m_idaView->field_4 = (unsigned short)((sta->sprxBytes / 8u) + 1u); }
        return 1;
    }

    // 0x004BFDD0

int Style::read_fonb_chunk_REAL(unsigned int dwBytes){
        // IDA 0x4BFDD0: CreateBuffer+Read fonb into Car, field_2, BuildCumulativeTable, SetFontStyles.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            if (dwBytes < 2) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr FONB too small size=%u\n", dwBytes); std::fclose(f); }
            }
            void* buf = CreateBuffer(dwBytes);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr FONB alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf, 1);
            if (EnsureIdaViewForFileMgrDebug()) m_idaView->Car = buf;
            m_idaViewFonbBytes = dwBytes;
            size_t sz = dwBytes;
            FileMgr::Read(buf, &sz);
            unsigned short fonbCount = 0;
            if (buf && dwBytes >= 2) {
                auto* w = reinterpret_cast<unsigned short*>(buf);
                fonbCount = w[0];
                if ((unsigned int)dwBytes != (unsigned int)(2u * fonbCount + 2u)) {
                    std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                    if (f) { std::fprintf(f, "style-filemgr FONB size mismatch size=%u count=%u\n", dwBytes, (unsigned)fonbCount); std::fclose(f); }
                }
                if (dwBytes >= 4) {
                    unsigned short sum = Style_SumShortArrayU16(w + 1, fonbCount);
                    if (EnsureIdaViewForFileMgrDebug()) m_idaView->field_2 = (short)sum;
                    // IDA: BuildCumulativeTable((char*)&Car->Car+2, v9)
                    Style_BuildCumulativeTableU16(w + 1, (int)fonbCount);
                }
            }
            // Debug-only: mirror SetFontStyles(count) shape without touching original globals.
            if (fonbCount == 14) {
                m_debugFontStyles = DebugFontStyles{};
                m_debugFontStyles.word_67065C = 1; m_debugFontStyles.word_670650 = 2; m_debugFontStyles.word_67066C = 4;
                m_debugFontStyles.unk_672F28 = 1; m_debugFontStyles.unk_672F24 = 1; m_debugFontStyles.valid = true;
            } else if (fonbCount == 7) {
                m_debugFontStyles = DebugFontStyles{};
                m_debugFontStyles.word_67065C = 3; m_debugFontStyles.word_670650 = 4;
                m_debugFontStyles.unk_672F28 = 3; m_debugFontStyles.unk_672F24 = 3; m_debugFontStyles.valid = true;
            } else {
                UpdateDebugFontStylesFromFonb();
            }
            return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->fonb || sta->fonbBytes < 2) return 0;
        if (m_idaView) m_idaView->Car = sta->fonb;
        m_idaViewFonbBytes = sta->fonbBytes;
        UpdateDebugFontStylesFromFonb();
        return 1;
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



static bool Style_ChunkTagEq(const char* got, const char* expect4) {
    return got && expect4 && std::strncmp(got, expect4, 4u) == 0;
}

int Style::read_sprb_records_REAL(unsigned int dwBytes){
        // IDA 0x4BFE70: reads 12 bytes into field_18, copies to field_14, BuildCumulativeTable.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            if (dwBytes != 12u) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr SPRB unexpected size=%u\n", dwBytes); std::fclose(f); }
                int s = (int)dwBytes; FileMgr::SeekPtr(&s);
                return 0;
            }
            void* buf18 = std::malloc(12u);
            void* buf14 = std::malloc(12u);
            if (!buf18 || !buf14) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr SPRB alloc failed size=%u\n", dwBytes); std::fclose(f); }
                if (buf18) std::free(buf18);
                if (buf14) std::free(buf14);
                return 0;
            }
            TrackFileMgrOwned(buf18,1); TrackFileMgrOwned(buf14,1);
            size_t sz = dwBytes; FileMgr::Read(buf18, &sz);
            std::memcpy(buf14, buf18, 12u);
            Style_BuildCumulativeTableU16(reinterpret_cast<unsigned short*>(buf14), 6);
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->field_18 = (int)reinterpret_cast<uintptr_t>(buf18); m_idaView->field_14 = (void*)buf14; }
            return 1;
        }
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


int Style::read_palb_chunk_REAL(unsigned int dwBytes){
        // IDA 0x4BFF20: reads 16 bytes S15_0002, copies to field_C, BuildCumulativeTable.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            if (dwBytes != 16u) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr PALB unexpected size=%u\n", dwBytes); std::fclose(f); }
                int s = (int)dwBytes; FileMgr::SeekPtr(&s);
                return 0;
            }
            void* buf2 = std::malloc(16u);
            void* bufc = std::malloc(16u);
            if (!buf2 || !bufc) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr PALB alloc failed size=%u\n", dwBytes); std::fclose(f); }
                if (buf2) std::free(buf2);
                if (bufc) std::free(bufc);
                return 0;
            }
            TrackFileMgrOwned(buf2,1); TrackFileMgrOwned(bufc,1);
            size_t sz = 16u; FileMgr::Read(buf2, &sz);
            std::memcpy(bufc, buf2, 16u);
            unsigned short palbSum = Style_SumShortArrayU16(reinterpret_cast<unsigned short*>(bufc), 8);
            Style_BuildCumulativeTableU16(reinterpret_cast<unsigned short*>(bufc), 8);
            if (EnsureIdaViewForFileMgrDebug()) {
                m_idaView->S15_0002 = buf2;
                m_idaView->field_C = (int)reinterpret_cast<uintptr_t>(bufc);
                m_idaView->field = (short)palbSum; // IDA 0x4BFF20: this->field = SumShortArray(8u, field_C)
            }
            return 1;
        }
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
        if (m_idaView && m_idaView->recy && m_idaView->n_recy > 0) {
            unsigned char* recy = reinterpret_cast<unsigned char*>(m_idaView->recy);
            int n = (int)(unsigned short)m_idaView->n_recy;
            int v3 = 0;
            if (recy[0] < carModel) {
                do {
                    ++v3;
                    if (v3 >= n) return false; // guarded bound; IDA assumes valid recy
                } while (recy[v3] < carModel);
            }
            return (v3 < n) && recy[v3] == carModel;
        }
        return true; // IDA: if !recy return 1
    }


    // 0x004C0010


int Style::read_recy_chunk_REAL_(unsigned int dwBytes){
        // IDA 0x4C0010: allocates buffer, reads RECY, sets n_recy=size.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            if (dwBytes > 0x7FFFu) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr RECY too large size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            void* buf = CreateBuffer(dwBytes);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr RECY alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf,1);
            if (EnsureIdaViewForFileMgrDebug()) { m_idaView->recy = reinterpret_cast<char*>(buf); m_idaView->n_recy = (short)dwBytes; }
            size_t sz = dwBytes; FileMgr::Read(buf, &sz); return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->recy && sta->recyBytes > 0) {
            if (m_idaView) { m_idaView->recy = reinterpret_cast<char*>(sta->recy); m_idaView->n_recy = (short)sta->recyBytes; }
            return 1;
        }
        return 0;
    }


    // 0x004C00A0


int Style::LoadIndexMap(int a2) {
        // IDA 0x4C0040: read u16 index; while index!=0 { arr1024[index]=a2; read next index }.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen()) {
            unsigned short idx = 0;
            size_t sz = 2;
            if (FileMgr::Read(&idx, &sz) != 2) return 0;
            while (idx) {
                if (idx < 1024) {
                    ArrayStyle[idx] = (unsigned int)a2;
                    if (EnsureIdaViewForFileMgrDebug()) m_idaView->arr1024[idx] = a2;
                }
                sz = 2;
                if (FileMgr::Read(&idx, &sz) != 2) break;
            }
            return 1;
        }
        // Debug fallback: no FileMgr; SPEC handled by read_spec_records_REAL fallback.
        return 0;
    }

int Style::read_spec_records_REAL(unsigned int /*dwBytes*/){
        // IDA 0x4C00A0: LoadIndexMap(this,2..10). No size arg in original; dwBytes kept for RE parse_chunk compat.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen()) {
            if (!EnsureIdaViewForFileMgrDebug()) return 0;
            int ok = 1;
            ok &= Style::LoadIndexMap(2);
            ok &= Style::LoadIndexMap(3);
            ok &= Style::LoadIndexMap(4);
            ok &= Style::LoadIndexMap(5);
            ok &= Style::LoadIndexMap(6);
            ok &= Style::LoadIndexMap(7);
            ok &= Style::LoadIndexMap(8);
            ok &= Style::LoadIndexMap(9);
            ok &= Style::LoadIndexMap(10);
            if (!ok) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr SPEC LoadIndexMap incomplete\n"); std::fclose(f); }
            }
            return ok ? 1 : 0;
        }
        // Debug fallback: SPEC table from StyleTiles (already parsed) -> arr1024.
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded) {
            for (int i = 0; i < 1024; ++i) ArrayStyle[i] = sta->spec[i] ? sta->spec[i] : 1;
            if (m_idaView) for (int i = 0; i < 1024; ++i) m_idaView->arr1024[i] = ArrayStyle[i];
            return 1;
        }
        return 0;
    }


    // 0x004C0100


int Style::StyleFixupSprites(void){
        // IDA 0x4C0100: if field_50 && field_48 StyleApplySpriteOffset(); then fix sprx ptrs: sprx[i]+=sprgBase.
        // Guarded: offset-table apply only through FileMgr-debug helper, which requires
        // GTA2_STYLE_IDA_FILEMGR=1 and tracked field_50. Not a full ownership/layout proof.
        if (!m_idaView) return 0;
        if (m_idaView->field_50 && m_idaView->field_48) {
            (void)StyleApplySpriteOffset();
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        const bool sprxIsStyleTiles = sta && sta->loaded && sta->sprx &&
            m_idaView->field_20 == (int)reinterpret_cast<uintptr_t>(sta->sprx);
        if (!sprxIsStyleTiles && m_idaView->field_20 && m_idaView->field_34 && m_idaView->field_4 && m_idaView->field_38) {
            auto* sprx = reinterpret_cast<unsigned char*>((uintptr_t)m_idaView->field_20);
            unsigned int count = (unsigned int)m_idaView->field_4;
            unsigned int sprgBase = (unsigned int)m_idaView->field_34;
            unsigned int sprgSize = (unsigned int)m_idaView->field_38;
            for (unsigned int i = 0; i < count; ++i) {
                unsigned int* p = reinterpret_cast<unsigned int*>(sprx + i * 8u);
                unsigned int v = *p;
                // Guard: only fix values that look like raw sprg offsets.
                if (v < sprgSize) *p = sprgBase + v;
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
        m_idaViewSprxBytes = 0;
        m_idaViewFonbBytes = 0;
        m_debugFontStyles = DebugFontStyles{};
        // Keep ArrayStyle as-is? IDA does not clear arr1024 in Unload; InitSpecArray is ctor behavior.
    }


    // 0x004C03F0

void Style::InitS284Debug(void* p) {
        // IDA S371 @ 0x4C03F0: byte[1024]=0; zero 0x400 bytes; returned as S284.
        if (!p) return;
        auto* b = reinterpret_cast<unsigned char*>(p);
        b[1024] = 0;
        std::memset(b, 0, 0x400u);
    }

    // 0x004C0410

int Style::LoadCariRecords(unsigned int dwBytes) {
        // IDA 0x4C0410: build pCar_5C (S284-like, 0x404 bytes) mapping model id -> CARI record ptr.
        // Guarded debug-only: requires FileMgr debug path and tracked field_58 buffer.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (!fm || fm[0] != '1' || !m_idaView || !m_idaView->field_58 || !dwBytes) return 0;
        bool tracked58 = false;
        for (int i = 0; i < m_fileMgrOwnedCount; ++i) if (m_fileMgrOwnedPtrs[i] == (void*)(uintptr_t)m_idaView->field_58) { tracked58 = true; break; }
        if (!tracked58) return 0;

        void* s284 = std::malloc(0x404u);
        if (!s284) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr CARI alloc failed\n"); std::fclose(f);} return 0; }
        TrackFileMgrOwned(s284, 1);
        InitS284Debug(s284);
        m_idaView->pCar_5C = s284;

        auto* base58 = reinterpret_cast<unsigned char*>((uintptr_t)m_idaView->field_58);
        unsigned int pos = 0;
        unsigned int count = 0;
        unsigned char v14 = 0, v15 = 0;
        while (pos < dwBytes) {
            if (pos + 15u > dwBytes) break; // minimum conservative record guard
            unsigned char* r = base58 + pos;
            if (count >= 0x100u) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr CARI too many records\n"); std::fclose(f);} break; }
            if (r[2] > 0x80u || r[3] > 0x80u || r[4] > 0x40u) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr CARI field range model=%u\n",(unsigned)r[0]); std::fclose(f);} }
            if (r[1] >= 2u) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr CARI bad flag model=%u v=%u\n",(unsigned)r[0],(unsigned)r[1]); std::fclose(f);} }
            unsigned char model = r[0];
            *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(s284) + ((int)model * 4)) = (int)reinterpret_cast<uintptr_t>(r);
            if (r[1]) { unsigned char v9 = (unsigned char)(v15 + v14); v15 = r[1]; v14 = v9; }
            int v10 = r[4];
            r[1] = v14;
            int v11 = v10 + 14;
            if ((unsigned int)(pos + v11) >= dwBytes) break;
            if (r[v11] > 5u) { std::FILE* f=std::fopen("gta2_style_filemgr.log","a"); if(f){std::fprintf(f,"style-filemgr CARI tail count model=%u v=%u\n",(unsigned)r[0],(unsigned)r[v11]); std::fclose(f);} }
            unsigned int recSize = (unsigned int)(v11 + 2 * r[v11] + 1);
            if (recSize == 0 || pos + recSize > dwBytes) break;
            pos += recSize;
            ++count;
        }
        reinterpret_cast<unsigned char*>(s284)[0x400] = (unsigned char)(count & 0xFFu); // CountModelCar; guarded byte
        return 1;
    }

    // 0x004C0580


int Style::read_cari_records_REAL(unsigned int dwBytes){
        // IDA 0x4C0580: CreateBuffer+Read CARI into field_58, then LoadCariRecords builds pCar_5C.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (fm && fm[0] == '1' && FileMgr::IsOpen() && dwBytes) {
            void* buf = CreateBuffer(dwBytes);
            if (!buf) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr CARI alloc failed size=%u\n", dwBytes); std::fclose(f); }
                return 0;
            }
            TrackFileMgrOwned(buf,1);
            if (EnsureIdaViewForFileMgrDebug()) m_idaView->field_58 = (int)reinterpret_cast<uintptr_t>(buf);
            size_t sz = dwBytes; FileMgr::Read(buf, &sz);
            int ok = LoadCariRecords(dwBytes);
            if (!ok) {
                std::FILE* f = std::fopen("gta2_style_filemgr.log", "a");
                if (f) { std::fprintf(f, "style-filemgr CARI LoadCariRecords failed size=%u\n", dwBytes); std::fclose(f); }
            }
            return 1;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!sta || !sta->loaded || !sta->cari) return 0;
        if (m_idaView) m_idaView->field_58 = (int)reinterpret_cast<uintptr_t>(sta->cari);
        return 1;
    }


    // 0x004C05B0


int Style::parse_chunk(const char* tag, unsigned int size){
        // IDA 0x4C05B0: dispatch by 4cc tag to read_*; unknown/optional chunks Seek over size.
        // Guarded: only active when GTA2_STYLE_IDA_FILEMGR=1 and FileMgr stream is open.
        const char* fm = std::getenv("GTA2_STYLE_IDA_FILEMGR");
        if (!fm || fm[0] != '1' || !FileMgr::IsOpen() || !tag) return 0;
        auto is = [&](const char* t) { return std::memcmp(tag, t, 4) == 0; };
        if (is("TILE")) return read_tile_chunk_REAL(size);
        if (is("SPRB")) return read_sprb_records_REAL(size);
        if (is("PALB")) return read_palb_chunk_REAL(size);
        if (is("SPRX")) return read_sprx_records_REAL(size);
        if (is("SPRG")) return read_sprg_records_REAL(size);
        if (is("PPAL")) return read_ppal_records_REAL(size);
        if (is("PALX")) return read_palx_records_REAL(size);
        if (is("OBJI")) return read_obji_records_REAL(size);
        if (is("FONB")) return read_fonb_chunk_REAL(size);
        if (is("DELX")) return read_delx_records_REAL(size);
        if (is("DELS")) return read_dels_records_REAL(size);
        if (is("CARI")) return read_cari_records_REAL(size);
        if (is("RECY")) return read_recy_chunk_REAL_(size);
        if (is("SPEC")) return read_spec_records_REAL(size);
        if (is("OVLY")) return read_ovly_records_REAL_(size);
        if (is("PSXT")) return read_psxt_records_REAL(size);
        // Unknown chunk: seek over.
        int s = (int)size; FileMgr::SeekPtr(&s);
        return 1;
    }


    // 0x004C2EB0


int Style::GetTileArray(unsigned short a2){
        // IDA 0x4C2EB0: Tiles + (((a2&3) + ((a2&0xFC)<<6))<<6)
        // Guarded: bound by known tile bytes when available (debug-only safety).
        int tiles = 0;
        unsigned int tileBytes = 0;
        if (m_idaView) {
            tiles = m_idaView->Tiles;
            unsigned int f44 = (unsigned int)m_idaView->field_44;
            // Guarded heuristic: in FileMgr debug TILE path field_44 stores raw NewMemory out ptr (IDA-shaped),
            // in StyleTiles debug adapter it stores tileBytes. Only use as byte bound when it looks like a size.
            if (f44 && f44 < 0x01000000u) tileBytes = f44;
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (!tiles && sta && sta->loaded && sta->tile) { tiles = (int)(uintptr_t)sta->tile; tileBytes = sta->tileBytes; }
        if (!tiles) return 0;
        int v2 = a2 & 0xFC;
        unsigned int off = (unsigned int)(((a2 & 3) + (v2 << 6)) << 6);
        if (tileBytes && off + 0x40u > tileBytes) return 0; // 64-byte tile
        return tiles + (int)off;
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
        // Guarded bounds check only when count is known; not full ownership/layout proof.
        if (m_idaView && m_idaView->field_20) {
            unsigned int count = m_idaView->field_4 ? (unsigned int)m_idaView->field_4 : 0;
            if (count && (unsigned int)idx >= count) return 0;
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
        // Guarded: only read when field_54 is a tracked FileMgr-owned buffer we built.
        if (!m_idaView || !m_idaView->field_54) return 0;
        bool tracked54 = false;
        for (int i = 0; i < m_fileMgrOwnedCount; ++i) if (m_fileMgrOwnedPtrs[i] == (void*)(uintptr_t)m_idaView->field_54) { tracked54 = true; break; }
        if (!tracked54) return 0;
        unsigned char* v3 = (unsigned char*)(uintptr_t)m_idaView->field_54;
        unsigned short count = *(unsigned short*)v3;
        if (a2 >= count) return 0;
        unsigned int v5 = *(unsigned int*)(v3 + 2u * (unsigned int)a2 + 2u);
        if (!v5) return 0;
        // IDA: v5 is pointer to record in field_50.
        unsigned char* rec = (unsigned char*)(uintptr_t)v5;
        unsigned char n = *(unsigned char*)(rec + 2);
        if (a3 >= n) return 0;
        unsigned short w = *(unsigned short*)(rec + 8u * (unsigned int)a3 + 8u);
        if (w == 0) return 0;
        return (int)(uintptr_t)(rec + 8u * (unsigned int)a3 + 4u);
    }

unsigned char Style::getSpriteWidth(unsigned short a2){
        // IDA 0x420220: *(BYTE*)(GetSprite+4)
        int spr = GetSprite(a2);
        if (!spr) return 0;
        // Guarded: only read when spr points into known StyleTiles/idaView sprx range.
        if (m_idaView && m_idaView->field_20) {
            unsigned int count = m_idaView->field_4 ? (unsigned int)m_idaView->field_4 : 0;
            unsigned int base = (unsigned int)m_idaView->field_20;
            unsigned int off = (unsigned int)spr - base;
            if (count && off < count * 8u) return *(unsigned char*)((uintptr_t)spr + 4);
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->sprx && sta->sprxBytes >= 8u) {
            uintptr_t base = (uintptr_t)sta->sprx;
            uintptr_t end = base + sta->sprxBytes;
            uintptr_t p = (uintptr_t)spr;
            if (p >= base && p + 8u <= end) return *(unsigned char*)(p + 4u);
        }
        return 0;
    }

unsigned char Style::GetSpriteFlag(unsigned short a2){
        // IDA 0x4C6C90: *(BYTE*)(GetSprite+5)
        int spr = GetSprite(a2);
        if (!spr) return 0;
        if (m_idaView && m_idaView->field_20) {
            unsigned int count = m_idaView->field_4 ? (unsigned int)m_idaView->field_4 : 0;
            unsigned int base = (unsigned int)m_idaView->field_20;
            unsigned int off = (unsigned int)spr - base;
            if (count && off < count * 8u) return *(unsigned char*)((uintptr_t)spr + 5);
        }
        const StyleTileAssets* sta = StyleTiles_Get();
        if (sta && sta->loaded && sta->sprx && sta->sprxBytes >= 8u) {
            uintptr_t base = (uintptr_t)sta->sprx;
            uintptr_t end = base + sta->sprxBytes;
            uintptr_t p = (uintptr_t)spr;
            if (p >= base && p + 8u <= end) return *(unsigned char*)(p + 5u);
        }
        return 0;
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
