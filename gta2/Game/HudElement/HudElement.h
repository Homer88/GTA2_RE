
#ifndef __HUDELEMENT_H_
#define __HUDELEMENT_H_


class HudElement{
    public:

    // 0x0044CB80
    int CheckPedCondition(void);


// ==== импорт имён из gm ====
    // 9 функций
    // 0x0044C560: HudElement::DrawCarArrow
    void DrawCarArrow();
    // 0x0044C610: HudElement::DrawPedArrow
    void DrawPedArrow();
    // 0x0044C6D0: HudElement::CheckTargetVisible
    void CheckTargetVisible();
    // 0x0044C700: HudElement::RenderWithReset
    void RenderWithReset();
    // 0x0044CBD0: HudElement::ClearCar
    void ClearCar();
    // 0x0044CC00: HudElement::ClearPed
    void ClearPed();
    // 0x0044CFF0: HudElement::Update
    void Update();
    // 0x0044D0F0: HudElement::Draw
    void Draw();
    // 0x00476B00: HudElement::SetColor
    void SetColor();
};
#endif // !__HUDELEMENT_H_