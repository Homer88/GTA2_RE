
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


// ==== импорт имён из gm ====
    // 8 функций
    // 0x00476880: HudArrow::ResetAll
    void ResetAll();
    // 0x004C6FB0: HudArrow::AreBothTracesFree
    void AreBothTracesFree();
    // 0x004C7030: HudArrow::SetArrowId
    void SetArrowId();
    // 0x004C7060: HudArrow::NextArrowTrace
    void NextArrowTrace();
    // 0x004C85D0: HudArrow::RemoveDuplicateArrows
    void RemoveDuplicateArrows();
    // 0x004C8650: HudArrow::FindByType
    void FindByType();
    // 0x004CA860: HudArrow::UpdateEntry
    void UpdateEntry();
    // 0x004CAA80: HudArrow::CreateForObject
    void CreateForObject();
};
#endif // !__HUDARROW_H_