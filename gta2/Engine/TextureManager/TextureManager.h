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
    void* GetDebugGbhFontTexture(int sprite_type, short spriteId, int a4, short a5);
    // IDA 0x4C2BA0 / 0x4C2BC0 - guarded stubs until RE layout is confirmed.
    void* GetTextureByIdx(unsigned short idx);
    void* GetTextureValue(unsigned short a2, short a3, short a4);

    // Optional debug view to real IDA-layout buffer; not wired by default.
    void* m_idaView = nullptr;
    void SetIdaView(void* v) { m_idaView = v; }
    void* GetIdaView() const { return m_idaView; }

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