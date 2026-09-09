#ifndef __HUDARROW_H_
#define __HUDARROW_H_

class HudArrow{

    public:

    // 0x004C5E60
    int SetArrowType(void);
    // 0x004C5E70
    int GetFreeArrow(void);
    // 0x004C6F80
    int AreBothArrowTracesUsed(void);
    // 0x004C6FE0
    int SetSpriteId(void);
    // 0x004C6FF0
    int SetSprite(void);
    // 0x004C7050
    int IsArrowVisible(void);
    // 0x004C70B0 undefined1 __thiscall
    int GetPararm0x83c(void);
    // 0x004C82C0
    int UpdateRadar(void);
    // 0x004C8470
    int IsTargetInUse(void);
    // 0x004C84C0
    int UpdateRadars(void);
    // 0x004C8540
    int FindActiveArrow(void);
    // 0x004CA610
    int InitArrow(void);
    // 0x004CA650
    int SetTraceTarget(void);
    // 0x004CA8E0
    int GetHudArrow(void);
    // 0x004CAAD0
    int UpdateForPlayers(void);
};

#endif // !__HUDARROW_H_
