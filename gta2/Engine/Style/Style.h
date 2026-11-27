
#ifndef __STYLE_H_
#define __STYLE_H_
#include "../../Game/Car/Car.h"

// IDA-compatible view (from dump/unified/gta2_unified.h). Not used as RE object layout yet.
struct StyleIdaView {
  __int16 field;
  __int16 field_2;
  unsigned __int16 field_4;
  unsigned __int16 field_6;
  unsigned __int16 PalitrePal;
  char field_A;
  char field_B;
  int field_C;
  void* S15_0002;
  void* field_14; // S15_001*
  int field_18;
  void* Car;
  int field_20;
  int field_24;
  void* field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int Tiles;
  void* S1501;
  int field_44;
  int field_48;
  int field_4C;
  int field_50;
  int field_54;
  int field_58;
  void* pCar_5C;
  int delx3;
  char* recy;
  __int16 n_recy;
  bool ColourDepth;
  char pad2;
  int arr1024[1024];
};

class Style{
    public:
        // 
       unsigned int ArrayStyle[1024];
       unsigned short PallitrePal;
       Car* ColorCar;
       int Tiles;
       byte ColourDepth;
       //


       Style();

        void InitSpecArray();
        void Load(char* FileName);
    void LoadFileSTY(char* fileName); // RE stub
    // 0x00420200
    bool CarExist(unsigned char id); // IDA 0x420200
    // 0x00420220
    unsigned char getSpriteWidth(unsigned short a2); // IDA 0x420220
    bool GetSpriteColors(unsigned short a2, unsigned int* a3, unsigned int* a4); // IDA 0x420230, guarded
    // 0x00432850
    unsigned char GetNumberOfCars(); // IDA 0x432850
    // 0x00432860 void __thiscall
    void SetXY(int arg0,int arg1);  // RE stub; IDA 0x432860 is Point2D::SetXY, not Style
    // 0x00462FB0 undefined4 __thiscall
    bool IsMapTileSpecial(unsigned short a2); // IDA 0x462FB0
    bool IsPathStateFive(unsigned short a2); // IDA 0x491F80
    bool is_tile_road_special(unsigned short a2); // IDA 0x42A810
    // 0x00462FD0
    int StyleGetSlotAttr(unsigned short index); // IDA 0x462FD0
    // 0x00463020 byte __thiscall
    bool IsPointInRect(unsigned char a2, unsigned char a3); // IDA 0x463020 (layout-dependent, guarded)
    bool IsTileBlockedPlayer(unsigned short a2); // IDA 0x49E540
    bool IsTileOneWay(unsigned short a2); // IDA 0x49E570
    // 0x004539D0 byte __thiscall
    // (gm) old: Font::GetRemapColour -> Style::GetRemapColour (wrapper over StyleGetRemapColour)
    unsigned char GetRemapColour(unsigned short param_1, unsigned short param_2);
    // 0x004B9F20
    int StyleGetSpriteCount(void);
    // 0x004BF1F0
    int getCarModelById(unsigned char carType); // IDA 0x4BF1F0
    // 0x004BF210
    int GetCarModel(unsigned char a2); // IDA 0x4BF210
    // 0x004BF2A0
    unsigned short GetBaseIndex(int sprite_type, short spriteId); // IDA 0x4BF2A0
    // 0x004BF330
    short GetGlobalPaletteOffset(int a2); // IDA 0x4BF330
    // 0x004BF3A0
    short GetPaletteByIndex(int a2); // IDA 0x4BF3A0
    // 0x004BF430
    unsigned short get_global_palette_id(int palette_type, short palette_id); // IDA 0x4BF430
    // 0x004BF4E0
    unsigned int GetColourBank(unsigned short a2); // IDA 0x4BF4E0
    // 0x004BF530
    unsigned short GetPhysPalette(unsigned short a2); // IDA 0x4BF530
    // 0x004BF550
    short GetSpriteID(unsigned short a2, short a3); // IDA 0x4BF550
    // 0x004BF570
    int GetStylePalette(void);  // (gm) старый: GetRemapColour -> GetStylePalette
    unsigned short StyleGetRemapColour(wchar_t* style, unsigned short* a3); // IDA 0x4BF570, guarded idaView
    // 0x004BF5D0
    short GetRemapColour16(unsigned short* a2); // IDA 0x4BF5D0
    // 0x004BF630
    short GetRemapColour32(unsigned short* style); // IDA 0x4BF630
    // RE debug: optional IDA-layout view. Not wired to real loaded style by default.
    // Can be bound to a separate read-only adapter buffer under GTA2_STYLE_IDA_VIEW=1.
    StyleIdaView* m_idaView = nullptr;
    void* m_idaViewOwned = nullptr; // owned adapter buffer, freed by Style
    unsigned int m_idaViewSprxBytes = 0;
    unsigned int m_idaViewFonbBytes = 0;
    // Debug-only FileMgr load ownership tracking (guarded path). Not IDA layout.
    void* m_fileMgrOwnedPtrs[64] = {};
    unsigned char m_fileMgrOwnedKind[64] = {}; // 0=none,1=malloc/free
    int m_fileMgrOwnedCount = 0;
    void TrackFileMgrOwned(void* p, unsigned char kind);
    void ClearFileMgrOwnedDebug();
    void SetIdaView(StyleIdaView* v) { m_idaView = v; }
    StyleIdaView* GetIdaView() const { return m_idaView; }
    bool BindIdaViewFromStyleTilesDebug(); // guarded, debug-only
    bool EnsureIdaViewForFileMgrDebug(); // guarded, debug-only; allocates empty idaView for FileMgr path
    void ClearIdaViewDebug();
    // 0x004BF740
    unsigned short GetPallitrePal(); // IDA 0x4BF740
    // 0x004BF750
    int get_obji_by_idx(unsigned short a2); // IDA 0x4BF750
    // 0x004BF770
    void ChangeTileByIdx(unsigned short a2, short a3); // IDA 0x4BF770
    // 0x004BF7F0
    int StyleInitSpriteTable(void);
    // 0x004BF840 void __thiscall
    void BuildSpriteBuffer(int param_1,unsigned int param_2); // legacy stub signature
    int BuildSpriteBuffer(unsigned int sizeBytes); // IDA 0x4BF840 guarded debug helper
    // 0x004BF900
    int StyleApplySpriteOffset(void);
    // 0x004BF950
    int StyleAddSpriteOffset(void);
    // 0x004BF980 void __fastcall
    void BuildSpriteLookup(int param_1); // legacy stub signature
    int BuildSpriteLookup(); // IDA 0x4BF980 guarded debug helper
    // 0x004BFA60
    int read_delx_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFAB0
    int read_dels_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFAD0
    int read_tile_chunk_REAL(unsigned int dwBytes = 0);
    // 0x004BFB00
    int read_ovly_records_REAL_(unsigned int dwBytes = 0);
    // 0x004BFB10
    int read_psxt_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFB20
    int read_sprg_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFB50
    int read_ppal_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFB80
    int read_palx_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFBE0
    int read_obji_records_REAL(unsigned int dwBytes = 0); // IDA 0x4BFBE0
    // 0x004BFC60
    int read_sprx_records_REAL(unsigned int dwBytes = 0); // IDA 0x4BFC60
    // 0x004BFDD0
    int read_fonb_chunk_REAL(unsigned int dwBytes = 0); // IDA 0x4BFDD0
    // 0x004BFCC0
    int SetFontStyles(int fontCount = -1); // IDA shape: count arg; -1 = debug fallback from FONB buffer
    // RE debug-only font style state, modeled after SetFontStyles @ 0x4BFCC0.
    // Not wired to original global addresses.
    struct DebugFontStyles {
        unsigned short word_67065C = 0;
        unsigned short word_670650 = 0;
        unsigned short word_67066C = 0;
        unsigned short unk_672F28 = 0;
        unsigned short unk_672F24 = 0;
        bool valid = false;
    } m_debugFontStyles;
    void UpdateDebugFontStylesFromFonb();
    const DebugFontStyles& GetDebugFontStyles() const { return m_debugFontStyles; }
    // 0x004BFE70
    int read_sprb_records_REAL(unsigned int dwBytes = 0);
    // 0x004BFF20
    int read_palb_chunk_REAL(unsigned int dwBytes = 0);
    // 0x004BFFE0
    bool isCarRecyclable(unsigned char carModel); // IDA 0x4BFFE0
    // 0x004C0010
    int read_recy_chunk_REAL_(unsigned int dwBytes = 0);
    // 0x004C0040
    int LoadIndexMap(int a2); // IDA 0x4C0040
    // 0x004C00A0
    int read_spec_records_REAL(unsigned int dwBytes = 0);
    // 0x004C0100
    int StyleFixupSprites(void); // IDA 0x4C0100
    // 0x004C0130
    void Unload(); // IDA 0x4C0130
    // 0x004C03F0
    void InitS284Debug(void* p); // IDA S371 shape, guarded debug helper
    // 0x004C0410
    int LoadCariRecords(unsigned int dwBytes); // IDA 0x4C0410 guarded debug helper
    // 0x004C0580
    int read_cari_records_REAL(unsigned int dwBytes = 0);
    // 0x004C05B0
    int parse_chunk(const char* tag, unsigned int size);
    // 0x004C2EB0
    int GetTileArray(unsigned short a2); // IDA 0x4C2EB0
    // 0x004C2EE0
    bool has_tiles(); // IDA 0x4C2EE0
    // 0x004C6C90
    int GetSprite(unsigned short idx); // IDA 0x4BF280
    int GetSpriteData(unsigned short a2, unsigned char a3); // IDA 0x4BF230
    unsigned char GetSpriteFlag(unsigned short a2); // IDA 0x4C6C90
    unsigned int GetSpriteCount() const; // IDA 0x4B9F20


// ==== импорт имён из gm ====
    // 6 функций
    // 0x004BF230: Style::GetSpriteData (declared above)
    // 0x004BF690: Style::IsTileRemapped
    bool IsTileRemapped(unsigned short a2); // IDA 0x4BF690
    // 0x004BF6B0: Style::get_tile_by_id
    unsigned short GetTileById(unsigned short a2); // IDA 0x4BF6B0
    // 0x004BF6D0: Style::FindFreeTileIndex
    short FindFreeTileIndex(); // IDA 0x4BF6D0
    // 0x004C0380: Style::CopyBlock
    void CopyBlock(); // IDA signature differs; RE keeps stub
    // 0x004C23D0: Style::GetCharData
    unsigned short GetCharData(short a1); // IDA 0x4C23D0: returns remap colour16 for char code
};
#endif // !__STYLE_H_
extern Style* gStyle;
