
#ifndef __HUD_H_
#define __HUD_H_


class Hud{
    public:
    // --- IDA-confirmed fields (partial, for DrawSprite_Wrapper @ 0x4C94F0 / gHud @ 0x672F40) ---
    // Full Hud size in original is 0x2AF8; RE only models fields needed by guarded debug paths.
    char field_0 = 0;          // +0x00: visible/active flag
    char _pad1 = 0;            // +0x01
    wchar_t field_2[24] = {};  // +0x02: text buffer ptr target in IDA (Hud+2 passed to 0x4BA2C0); size approx
    unsigned char _pad_ida_32[0x44 - 0x32] = {}; // +0x32..0x43
    int field_44 = 0;          // +0x44
    int field_48 = 0;          // +0x48
    unsigned char _pad_ida_4c[0x60 - 0x4C] = {}; // +0x4C..0x5F, reserve

    // RE debug HUD text buffer, rendered by main.cpp software overlay when gbh text path is unavailable.
    static const int kDebugHudLines = 4;
    static const int kDebugHudLineLen = 128;
    char debugLines[kDebugHudLines][kDebugHudLineLen] = {};
    int debugLineCount = 0;
    void ClearDebugLines();
    void AddDebugLine(const char* text);

    Hud(); // IDA 0x4CAC60 - RE minimal init

    // 0x004219F0
    int ResetMessage(void);
    // 0x004C6940
    int ComputeTextWidth(void);
    // 0x004C69C0 IDA Hud::Hud1: field_0=0. RE field-name impl.
    void Hud1();
    // 0x004C6960 - RE: takes wide string; IDA decompile shows retaddr artifact but semantically copies message text.
    int SetMessageText(const wchar_t* text);
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
    // 0x004CAB50 IDA Hud::UpdateAll (guarded partial)
    int UpdateAll(void);


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
    // RE: logic from Hud::DrawUI @ 0x4CA440 quit block; 0x4C8710 symbol/address not confirmed in ida_decompiled.c
    void DrawQuitConfirm();
    // 0x004C8990: Hud::DrawChatMessage
    void DrawChatMessage();
    // 0x004C8CA0: Hud::DrawNumber
    void DrawNumber();
    // 0x004C8E30: Hud::DrawTime
    void DrawTime();
};
extern Hud* gHud;
#endif // !__HUD_H_