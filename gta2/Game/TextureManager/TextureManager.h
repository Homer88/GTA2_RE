
#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_


class TextureManager{
    public:

    // 0x004C29C0
    int FreePalitre(void);


// ==== импорт имён из gm ====
    // 2 функций
    // 0x004C2A00: TextureManager::RegisterTextures
    void RegisterTextures();
    // 0x004C2C30: TextureManager::AssignPalette
    void AssignPalette();
};
#endif // !__TEXTUREMANAGER_H_