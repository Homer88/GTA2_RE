
#ifndef __SPRITES3_H_
#define __SPRITES3_H_


class SpriteS3{
    public:
        SpriteS3();
    // 0x004BC8F0
    int SpriteS3Init(void);
    // 0x004C2EF0
    int SpriteS3Get(void);
};

extern SpriteS3* gSpriteS3;
#endif // !__SPRITES3_H_