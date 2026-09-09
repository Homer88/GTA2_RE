#ifndef __POINT2D_H_
#define __POINT2D_H_

class Point2D{

    public:

    // 0x00401B20
    int SetSpritePosition(void);
    // 0x0041E350
    int Point2DSet(void);
    // 0x0041E370
    int Set2(void);
    // 0x0045ADC0
    int GetW(void);
    // 0x00486360
    int ApplyImpactDamage(void);
    // 0x004BA5E0
    int SetCameraBounds(void);
    // 0x004BA6C0 undefined1 __thiscall
    int IsPointOnQuad(int param_1);
    // 0x004BA720
    int Transform(void);
};

#endif // !__POINT2D_H_
