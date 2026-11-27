#ifndef ___TEXTURE_MANAGER__H_
#define ___TEXTURE_MANAGER__H_

// IDA layout refs (dump/unified/gta2_unified.h). Used only as guarded debug views.
struct TextureManager_S88 {
	int field_0;
	void* GLuintPtr; // GLuint*
	short field_8;
	short field_A;
};

struct TextureManager_S89 {
	void* S89_2;
	unsigned short Count;
	short field_6;
	int sprite_type;
	int field_C;
	char field_10;
	char field_11;
	char field_12;
	char field_13;
};

// Minimal S89_2 view used by PacketInfo::GetStyleTexture/GetIndexedTexture.
struct TextureManager_S89_2 {
	int* field_0; // array of texture handles/ids
};

// Partial IDA view for read-only access when m_idaView is confirmed to point to real IDA TextureManager.
struct TextureManagerIdaView {
	void* BufferTexture4M[1024];
	char field_1000;
	bool TexturesInitialised;
	char field_1002;
	char field_1003;
	void* Buffer_Arr48[48]; // GLuint*
	TextureManager_S88 Arr_96_S88[96];
	void* Texture; // GLuint*
	TextureManager_S89 S89[7];
	short field_15D4;
	short PalitrePal;
};

class TextureManager{
	public:
	TextureManager();
	~TextureManager();

    // 0x004C29C0
    int FreePalitre(void);


    // ==== импорт имён из gm ====
        // 2 функций
        // 0x004C2A00: TextureManager::RegisterTextures
    void RegisterTextures();
    // 0x004C2C30: TextureManager::AssignPalette
    void AssignPalette();
    int Load();
    // IDA 0x4C2AC0: (sprite_type,spriteId,a4,a5) -> texture id/pointer by S89 bank.
    int GetTexture(int sprite_type, short spriteId, int a4, short a5);
    // Debug-only: creates/caches real gbh_Texture* for font bank 7 (a4==7) under GTA2_TEXT_GBH_DRAW=1.
    // Bypasses TM/PacketInfo/S89; NOT IDA-compatible. Returns nullptr when unavailable.
    // IDA 0x4C2BA0 / 0x4C2BC0 - guarded stubs until RE layout is confirmed.
    void* GetTextureByIdx(unsigned short idx);
    void* GetTextureValue(unsigned short a2, short a3, short a4);

    // Optional debug view to real IDA-layout buffer; not wired by default.
    void* m_idaView = nullptr;
    void SetIdaView(void* v) { m_idaView = v; }
    void* GetIdaView() const { return m_idaView; }

    // Debug-only TM-owned font bank 7 subset (S89[6] shape), gated by GTA2_TEXT_GBH_DRAW=1.
    // NOT full IDA TextureManager/PacketInfo layout. No default behavior change.
    // IDA refs: TM::Load 0x4C30A0 Setup(&S89[6],6,7)+LoadPalettedTextures; GetTexture case 7 -> S89[6].
    struct DebugFontS89Bank7 {
        bool initAttempted = false;
        bool ready = false;          // S89_2 allocated and at least init completed
        bool gbhOk = false;
        unsigned short spriteCount = 0; // GetGlobalPaletteOffset(gStyle,6)
        unsigned short field_6 = 0;     // GetPaletteByIndex(gStyle,7)
        unsigned int count = 0;         // spriteCount*field_6
        TextureManager_S89 s89{};       // minimal S89 metadata
        TextureManager_S89_2 s89_2{};   // field_0 -> entries
        int* entries = nullptr;         // [count] real gbh_Texture* stored as int/ptr-sized value
        const char* reason = "gbh-font7-off";
    } m_debugFontS89_7;
    const DebugFontS89Bank7& GetDebugFontS89Bank7() const { return m_debugFontS89_7; }
    void* GetDebugGbhFontTexture(int sprite_type, short spriteId, int a4, short a5);

    // EU debug subset: IDA GetTexture a4==2 => PacketInfo::GetStyleTexture(S89[0], sprite_type, spriteId)
    // => S89_2->field_0[Style::GetBaseIndex(gStyle, sprite_type, spriteId)]. Real TM init not ported.
    struct DebugBank2Style {
        bool initAttempted = false;
        bool ready = false;
        unsigned int count = 0; // GetPaletteByIndex(gStyle,2) for S89[0] Create(...,1,0,2)
        int* entries = nullptr; // [count] gbh_Texture* by base index
        const char* reason = "gbh-bank2-off";
    } m_debugBank2Style;
    const DebugBank2Style& GetDebugBank2Style() const { return m_debugBank2Style; }
    void* GetDebugGbhBank2Texture(int sprite_type, short spriteId);

    // Debug-only read-only status for HUD. No real S89/gbh texture pipeline yet.
    struct DebugState {
        bool loaded = false;
        bool texturesInitialised = false;
        bool tileTexturesInitialised = false;
        unsigned short palCount = 0;
        unsigned short tileCount = 0;
        unsigned short spriteTexCount = 0;
    } m_debug;
    const DebugState& GetDebugState() const { return m_debug; }
    bool LoadDebugFromStyleTiles(); // GTA2_TEX_DEBUG=1
};

// IDA 0x4C2AC0 free-function shape used by DrawGTATextRaw.
int GetTexture(TextureManager* tm, int sprite_type, short spriteId, int a4, short a5);
extern TextureManager* gTextureManager;
#endif //___TEXTURE_MANAGER__H_