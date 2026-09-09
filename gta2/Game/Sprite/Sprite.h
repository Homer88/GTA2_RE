#ifndef __SPRITE_H_
#define __SPRITE_H_

class Sprite{

    public:

    // 0x00420600
    int SetPosition(void);
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
};

#endif // !__SPRITE_H_
