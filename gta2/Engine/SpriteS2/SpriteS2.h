
#ifndef __SPRITES2_H_
#define __SPRITES2_H_
#include "../Game/GangInfo/GangInfo.h"

class SpriteS2{
    public:
        GangInfo ArrayGangInfo[5031];
        GangInfo* FirstGangInfo;
        SpriteS2();
    // 0x004BC950
    int SpriteS2Dtor(void);
    // 0x004BC9F0
    int SpriteS2Alloc(void);
    // 0x004BCA10
    int Free(void);
};
extern SpriteS2* gSpriteS2;
#endif // !__SPRITES2_H_