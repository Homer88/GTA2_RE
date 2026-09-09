#ifndef __TEXTLABEL_H_
#define __TEXTLABEL_H_

class TextLabel{

    public:

    // 0x004A4F20
    int DeleteWeapon(void);
    // 0x004CC9B0
    int S73_GetWeapon_1(void);
    // 0x004CC9C0
    int MoveWeaponToNextList(void);
    // 0x004CC9E0
    int GetWeapon(void);
    // 0x004CD9F0 void __fastcall
    void DestructTextLabel(int arg0);
    // 0x004CDA70
    int ReturnWeapon(void);
    // 0x004CDA90
    int SpawnWeaponProjectile(void);
};

#endif // !__TEXTLABEL_H_
