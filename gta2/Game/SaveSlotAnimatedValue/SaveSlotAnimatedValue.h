
#ifndef __SAVESLOTANIMATEDVALUE_H_
#define __SAVESLOTANIMATEDVALUE_H_


class SaveSlotAnimatedValue{
    public:

    // 0x0041DC30
    int GetHealth(void);
    // 0x0044B1D0
    int Lives(void);
    // 0x0044B390
    int Animate(void);
    // 0x0045B0A0
    int GetAccurcy(void);
    // 0x004B7490
    int InitPlayer(void);
    // 0x004B74D0
    int ValueGet(void);
    // 0x004B85B0
    int LogCarEvent(void);
    // 0x004B8870
    int CarDestroyed(void);
    // 0x004B89B0
    int AddCarDamageMoney(void);
    // 0x004B8A60
    int GiveMoney20(void);


// ==== импорт имён из gm ====
    // 3 функций
    // 0x0044B300: SaveSlotAnimatedValue::UpdatePalette
    void UpdatePalette();
    // 0x0044B6E0: SaveSlotAnimatedValue::DrawValueSelected
    void DrawValueSelected();
    // 0x004B7E90: SaveSlotAnimatedValue::SetCapabilityFlag
    void SetCapabilityFlag();

    // 0x0044B500
    // (gm) ������: SaveSlotAnimatedValue::PlayerDrawHud -> SaveSlotAnimatedValue::DrawValue
    int DrawValue(int arg1, int arg2);
};
#endif // !__SAVESLOTANIMATEDVALUE_H_