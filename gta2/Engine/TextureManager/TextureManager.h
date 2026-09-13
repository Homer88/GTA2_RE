#ifndef ___TEXTURE_MANAGER__H_
#define ___TEXTURE_MANAGER__H_

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
};	
#endif //___TEXTURE_MANAGER__H_