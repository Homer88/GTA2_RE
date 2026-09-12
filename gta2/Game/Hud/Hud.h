
#ifndef __HUD_H_
#define __HUD_H_


class Hud{
    public:

    // 0x004219F0
    int ResetMessage(void);
    // 0x004C6940
    int ComputeTextWidth(void);
    // 0x004C6960
    int SetMessageText(void);
    // 0x004C69A0
    int TickMessage(void);
    // 0x004C6D90
    int Init_s_Wrapper(void);
    // 0x004C6DA0
    int SetAmbientLight(void);
    // 0x004C6DC0
    int SetTextSpeed(void);
    // 0x004C6DE0
    int HandleKey(void);
    // 0x004C6E20
    int HandleKeyboard_Wrapper(void);
    // 0x004C7220
    int GetSpriteWidth(void);
    // 0x004C94F0
    int DrawSprite_Wrapper(void);
    // 0x004CA440
    int DrawUI(void);
    // 0x004CA520
    int DrawUIWrapper(void);
    // 0x004CA5D0
    int Update2_Wrapper(void);
    // 0x004CABE0
    int SetSpeedText_Wrapper(void);
    // 0x004CAC30
    int UpdateWrapper(void);


// ==== импорт имён из gm ====
    // 9 функций
    // 0x004A4760: Hud::ToggleFlag
    void ToggleFlag();
    // 0x004C6CA0: Hud::AnimatePlayerStats
    void AnimatePlayerStats();
    // 0x004C74F0: Hud::DrawGangStatus
    void DrawGangStatus();
    // 0x004C78A0: Hud::DrawPlayerNames
    void DrawPlayerNames();
    // 0x004C7B70: Hud::DrawHealth
    void DrawHealth();
    // 0x004C8710: Hud::DrawQuitConfirm
    void DrawQuitConfirm();
    // 0x004C8990: Hud::DrawChatMessage
    void DrawChatMessage();
    // 0x004C8CA0: Hud::DrawNumber
    void DrawNumber();
    // 0x004C8E30: Hud::DrawTime
    void DrawTime();
};
#endif // !__HUD_H_