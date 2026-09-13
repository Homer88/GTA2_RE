
#ifndef __STYLE_H_
#define __STYLE_H_


class Style{
    public:
    
        void Load(char* FileName);
    // 0x00420200
    int CarExist(void);
    // 0x00420220
    int getSpriteWidth(void);
    // 0x00432850
    int GetNumberOfCars(void);
    // 0x00432860 void __thiscall
    void SetXY(int arg0,int arg1);  // (gm) старый: SetTwoFields -> SetXY
    // 0x00462FB0 undefined4 __thiscall
    int IsMapTileSpecial(int param_1,unsigned int param_2);  // (gm) старый: IsSlotAttrFour -> IsMapTileSpecial
    // 0x00462FD0
    int StyleGetSlotAttr(void);
    // 0x00463020 byte __thiscall
    unsigned char IsPointInRect(unsigned char param_1,unsigned char param_2);  // (gm) ������: IsInsideBounds -> IsPointInRect

    // 0x004539D0 byte __thiscall
    // (gm) old: Font::GetRemapColour -> Style::GetRemapColour (wrapper over StyleGetRemapColour)
    unsigned char GetRemapColour(unsigned short param_1, unsigned short param_2);
    // 0x004B9F20
    int StyleGetSpriteCount(void);
    // 0x004BF1F0
    int getCarModelById(void);
    // 0x004BF210
    int GetCarModel(void);
    // 0x004BF2A0
    int GetBaseIndex(void);
    // 0x004BF330
    int GetGlobalPaletteOffset(void);
    // 0x004BF3A0
    int GetPaletteByIndex(void);
    // 0x004BF430
    int get_global_palette_id(void);
    // 0x004BF4E0
    int GetColourBank(void);
    // 0x004BF530
    int GetPhysPalette(void);
    // 0x004BF550
    int GetSpriteID(void);
    // 0x004BF570
    int GetStylePalette(void);  // (gm) старый: GetRemapColour -> GetStylePalette
    // 0x004BF5D0
    int GetRemapColour16(void);
    // 0x004BF630
    int GetRemapColour32(void);
    // 0x004BF740
    int GetPallitrePal(void);
    // 0x004BF750
    int get_obji_by_idx(void);
    // 0x004BF770
    int ChangeTileByIdx(void);
    // 0x004BF7F0
    int StyleInitSpriteTable(void);
    // 0x004BF840 void __thiscall
    void BuildSpriteBuffer(int param_1,unsigned int param_2);
    // 0x004BF900
    int StyleApplySpriteOffset(void);
    // 0x004BF950
    int StyleAddSpriteOffset(void);
    // 0x004BF980 void __fastcall
    void BuildSpriteLookup(int param_1);
    // 0x004BFA60
    int read_delx_records_REAL(void);
    // 0x004BFAB0
    int read_dels_records_REAL(void);
    // 0x004BFAD0
    int read_tile_chunk_REAL(void);
    // 0x004BFB00
    int read_ovly_records_REAL_(void);
    // 0x004BFB10
    int read_psxt_records_REAL(void);
    // 0x004BFB20
    int read_sprg_records_REAL(void);
    // 0x004BFB50
    int read_ppal_records_REAL(void);
    // 0x004BFB80
    int read_palx_records_REAL(void);
    // 0x004BFCC0
    int SetFontStyles(void);
    // 0x004BFE70
    int read_sprb_records_REAL(void);
    // 0x004BFF20
    int read_palb_chunk_REAL(void);
    // 0x004BFFE0
    int isCarRecyclable(void);
    // 0x004C0010
    int read_recy_chunk_REAL_(void);
    // 0x004C00A0
    int read_spec_records_REAL(void);
    // 0x004C0100
    int StyleFixupSprites(void);
    // 0x004C0130
    int Unload(void);
    // 0x004C0580
    int read_cari_records_REAL(void);
    // 0x004C05B0
    int parse_chunk(void);
    // 0x004C2EB0
    int GetTileArray(void);
    // 0x004C2EE0
    int has_tiles(void);
    // 0x004C6C90
    int GetSpriteFlag(void);


// ==== импорт имён из gm ====
    // 6 функций
    // 0x004BF230: Style::GetSpriteData
    void GetSpriteData();
    // 0x004BF690: Style::IsTileRemapped
    void IsTileRemapped();
    // 0x004BF6B0: Style::GetTileById
    void GetTileById();
    // 0x004BF6D0: Style::FindFreeTileIndex
    void FindFreeTileIndex();
    // 0x004C0380: Style::CopyBlock
    void CopyBlock();
    // 0x004C23D0: Style::GetCharData
    void GetCharData();
};
#endif // !__STYLE_H_