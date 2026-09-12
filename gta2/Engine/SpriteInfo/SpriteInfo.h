
#ifndef __SPRITEINFO_H_
#define __SPRITEINFO_H_


class SpriteInfo{
    public:

    // 0x004768C0
    int DisableObject(void);
    // 0x00476930 void __thiscall
    void InitAndSetField(int param_2);
    // 0x00476950 void __thiscall
    void SetValue(int param_2);
    // 0x004C4FE0
    int UseObject(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x004C4EA0: SpriteInfo::InitEventSlot
    void InitEventSlot();
};
#endif // !__SPRITEINFO_H_