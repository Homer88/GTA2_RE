
#ifndef __SPRITE_H_
#define __SPRITE_H_


class Sprite{
    public:
        int x, y, z;
    // 0x00420600
    int SetPosition(void);
    void SetPosition(int x, int y, int z);
    // 0x00420690
    int SetRotation(void);
    // 0x004206C0
    int SetFrame(void);
    // 0x004206F0
    int SetType(void);
    // 0x00420710
    int SetCar(void);
    // 0x00483E50
    int SetObject(void);
    // 0x004B99F0
    int ResetState(void);
    // 0x004BAB10
    int SetSize(void);
    // 0x004BCB40
    int DrawArrow(void);
    // 0x004BD290
    int SpriteDraw(void);
    // 0x004BDDB0
    int CopySpriteData(void);
    // 0x004BDEF0
    int DrawSprite(void);


// ==== импорт имён из gm ====
    // 5 функций
    // 0x0049EF20: Sprite::HasGameObject
    void HasGameObject();
    // 0x004BD490: Sprite::IsOnMapTile
    void IsOnMapTile();
    // 0x004BD610: Sprite::AddToVisibleList
    void AddToVisibleList();
    // 0x004BE050: Sprite::GetRenderCoords
    void GetRenderCoords();
    // 0x004BE570: Sprite::MergeDrawSortKey
    void MergeDrawSortKey();
};
#endif // !__SPRITE_H_