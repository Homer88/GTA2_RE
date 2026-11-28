#include "Hud.h"
#include "../../Engine/Text/Text.h"
#include "../../Engine/Font/Font.h"
#include "../../Engine/Object/Object.h"
#include "../../Engine/Style/Style.h"
#include "../../Engine/Style/StyleTileLoader.h"
#include "../../Engine/TextureManager/TextureManager.h"
#include "../../Engine/MapRelatedStruct/MapRelatedStruct.h"
#include "../Game/Game.h"
#include "../Player/Player.h"
#include "../CameraOrPhysics/CameraOrPhysics.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cwchar>

extern CameraOrPhysics* gCameraOrPhysics_5E3CC4;

Hud* gHud;

Hud::Hud() {
    // RE minimal subset of IDA Hud::Hud @ 0x4CAC60. Original is 0x2AF8 and initializes many subobjects.
    // We only zero/init fields needed by guarded debug probes (DrawSprite_Wrapper ABI9 path).
    field_0 = 0;
    for (int i = 0; i < 24; ++i) field_2[i] = 0;
    field_44 = 0;
    field_48 = 0;
}

void Hud::ClearDebugLines() {
    debugLineCount = 0;
    for (int i = 0; i < kDebugHudLines; ++i) debugLines[i][0] = 0;
}

void Hud::AddDebugLine(const char* text) {
    if (!text) return;
    if (debugLineCount >= kDebugHudLines) return;
    std::snprintf(debugLines[debugLineCount], kDebugHudLineLen, "%s", text);
    debugLines[debugLineCount][kDebugHudLineLen - 1] = 0;
    ++debugLineCount;
}

    // 0x004219F0


int Hud::ResetMessage(void){
        // IDA 0x4219F0: this->field_0 = 0;
        field_0 = 0;
        return 0;
    }


    // 0x004C6940


int Hud::ComputeTextWidth(void){
        // IDA 0x4C6940: if (field_0) field_44 = Font::GetStringWidth(field_2, unk_672F28)
        // RE: unk_672F28 not wired; use style 1 as guarded fallback.
        if (field_0) {
            extern Font* gFont;
            if (gFont) {
                field_44 = (int)gFont->GetStringWidth(field_2, (unsigned short)1);
            }
        }
        return field_44;
    }


    // 0x004C6960


int Hud::SetMessageText(const wchar_t* text){
        // IDA 0x4C6960 (decompile artifact on retaddr): sets field_0=120, copies message into field_2,
        // ConvertWordsToBig, ComputeTextWidth, field_48=-17. Guarded RE implementation.
        if (!text) { field_0 = 0; return 0; }
        field_0 = 120;
        wcsncpy(field_2, text, 23);
        field_2[23] = 0;
        extern Text* gText;
        if (gText) gText->ConvertWordsToBig(field_2);
        ComputeTextWidth();
        field_48 = -17;
        return 0;
    }


    // 0x004C69A0


int Hud::TickMessage(void){
        // IDA 0x4C69A0: if active, decrement; >0x50 ++field_48; <0x28 --field_48.
        unsigned char result = (unsigned char)field_0;
        if (field_0) {
            result = (unsigned char)(field_0 - 1);
            field_0 = (char)result;
            if (result <= 0x50u) {
                if (result < 0x28u) --field_48;
            } else {
                ++field_48;
            }
        }
        return (int)result;
    }


    // 0x004C6D90


int Hud::Init_s_Wrapper(void){
        return 0;
    }


    // 0x004C6DA0


int Hud::SetAmbientLight(void){
        return 0;
    }


    // 0x004C6DC0


int Hud::SetTextSpeed(void){
        return 0;
    }


    // 0x004C6DE0


int Hud::HandleKey(void){
        return 0;
    }


    // 0x004C6E20


int Hud::HandleKeyboard_Wrapper(void){
        return 0;
    }


    // 0x004C7220


int Hud::GetSpriteWidth(void){
        return 0;
    }


    // 0x004C94F0


int Hud::DrawSprite_Wrapper(void){
        // IDA 0x4C94F0: draws HUD sprite/text elements, including sub_4BA2C0 @ 0x4BA2C0 call.
        // RE: minimal guarded probe using real gHud instance/IDA-confirmed fields (field_0/2/44/48).
        // NOT full DrawSprite_Wrapper port, NOT original Radar world->screen/callsite proof.
        if (std::getenv("GTA2_TEXT_GBH") && std::getenv("GTA2_TEXT_GBH")[0] == '1') {
            Hud* hud = gHud ? gHud : this;
            if (hud && hud->field_0) {
                // IDA 0x4C94F0 tail: EncodePositionValue((640-field_44)/2), EncodePositionValue(field_48-CharHeight/2),
                // then Font::DrawGTATextRaw_A2C0(this->field_2, field_10, pPlayer). RE: debug-only approximation,
                // guarded by GTA2_TEXT_GBH=1. NOT original caller/callsite/callstack/object proof.
                int ch = 8;
                extern Font* gFont;
                if (gFont) {
                    int got = gFont->GetCharHeight((unsigned short)0);
                    if (got > 0) ch = got;
                }
                int sx = (hud->field_44 > 0 && hud->field_44 < 4096) ? (640 - hud->field_44) / 2 : 8;
                int syBase = (hud->field_48 > -4096 && hud->field_48 < 4096) ? hud->field_48 : 164;
                int sy = syBase - ch / 2;
                wchar_t* txt = hud->field_2[0] ? hud->field_2 : (wchar_t*)L"HUD TEXT BRIDGE OK";
                S202 dbgA2 = {};
                S202 dbgA3 = {};
                const char* encEnv = std::getenv("GTA2_TEXT_GBH_A2C0_ENCODED");
                if (encEnv && encEnv[0] == '1') {
                    // Debug-only probe: EncodePositionValue-shaped input to exercise radar-formula bridge.
                    // NOT original callsite/callstack proof; scale semantics not fully confirmed.
                    dbgA2.EncodePositionValue(sx);
                    dbgA3.EncodePositionValue(sy);
                } else {
                    dbgA2.field_0 = sx;
                    dbgA3.field_0 = sy;
                }
                DrawGTATextRaw_A2C0(txt, (int)(uintptr_t)&dbgA2, (void*)&dbgA3, (unsigned short)0, 0x4C94F0u);
            } else {
                S202 dbgA2 = {};
                S202 dbgA3 = {};
                const char* encEnv = std::getenv("GTA2_TEXT_GBH_A2C0_ENCODED");
                if (encEnv && encEnv[0] == '1') {
                    dbgA2.EncodePositionValue(8);
                    dbgA3.EncodePositionValue(164);
                } else {
                    dbgA2.field_0 = 8;
                    dbgA3.field_0 = 164;
                }
                DrawGTATextRaw_A2C0((wchar_t*)L"HUD TEXT BRIDGE OK", (int)(uintptr_t)&dbgA2, (void*)&dbgA3, (unsigned short)0, 0x4C94F0u);
            }
        }
        return 0;
    }


    // 0x004CA440


int Hud::DrawUI(void){
        // IDA 0x4CA440: draws HUD subsystems and, if PlayerMain->quit1, draws quit1/quit2/quit3
        // via DrawGTATextRaw_7280 @ 0x4C7280 -> DrawGTATextRaw @ 0x4CC100.
        // RE: gbh/font path not ready; emit minimal text commands for software overlay.
        ClearDebugLines();
        ClearDebugTextCmds();
        char buf[128];
        const char* mobjEnv = std::getenv("GTA2_SPAWN_MOBJ");
        const char* traceEnv = std::getenv("GTA2_MOBJ_TRACE");
        extern Style* gStyle;
        extern TextureManager* gTextureManager;
        const char* forceGbh = std::getenv("GTA2_TEXT_GBH");
        const StyleTileAssets* sta = StyleTiles_Get();
        extern const char* Text_GetGbhBlockedReason();
        std::snprintf(buf, sizeof(buf), "HUD txt=%s sty=%s tex=%s idaS=%s idaT=%s gbh=%s %s",
            gText ? "1" : "0", gStyle ? "1" : "0", gTextureManager ? "1" : "0",
            (gStyle && gStyle->GetIdaView()) ? "1" : "0",
            (gTextureManager && gTextureManager->GetIdaView()) ? "1" : "0",
            (forceGbh && forceGbh[0]=='1') ? "1" : "0",
            Text_GetGbhBlockedReason());
        AddDebugLine(buf);
        std::snprintf(buf, sizeof(buf), "STY tiles=%u phys=%u palx=%u loaded=%s",
            sta ? sta->tileCount : 0u, sta ? sta->physPalCount : 0u, sta ? sta->palxCount : 0u,
            (sta && sta->loaded) ? "1" : "0");
        AddDebugLine(buf);
        if (gTextureManager) {
            const auto& td = gTextureManager->GetDebugState();
            std::snprintf(buf, sizeof(buf), "TEX dbg l=%d p=%u t=%u s=%u", td.loaded?1:0, (unsigned)td.palCount, (unsigned)td.tileCount, (unsigned)td.spriteTexCount);
            AddDebugLine(buf);
        }
        // Debug-only Style IDA-view probe (no gbh). Helps verify adapter before 0x4CC100.
        // Debug font-style/probe omitted: needs verified font-style globals and bounds-safe glyph lookup.
        std::snprintf(buf, sizeof(buf), "MOBJ spawn=%s trace=%s", (mobjEnv && mobjEnv[0]=='1')?"1":"0", (traceEnv && traceEnv[0]=='1')?"1":"0");
        AddDebugLine(buf);
        extern Object* gObject;
        if (gObject) {
            std::snprintf(buf, sizeof(buf), "MOBJ spawned=%d textcmd=%d", gObject->GetDebugSpawnedCount(), gDebugTextCmdCount);
            AddDebugLine(buf);
        }
        // Push a few Bsearch strings through DrawGTATextRaw bridge (overlay-rendered).
        // IDA 0x4CA440 also draws game HUD elements; here we only probe safe text keys.
        int probeHits = 0;
        if (gText) {
            struct { const char* key; int x; int y; } probes[] = {
                {"p_exit", 8, 100}, {"wasted", 8, 116}, {"paused", 8, 132},
                {"are_u_sure", 8, 148},
            };
            for (auto& pr : probes) {
                wchar_t* w = (wchar_t*)gText->Bsearch(pr.key);
                if (w) { DrawGTATextRaw_7280(w, pr.x, pr.y); ++probeHits; }
            }
        }
        std::snprintf(buf, sizeof(buf), "text probes=%d gxt=%d", probeHits, gText ? gText->NumberOfElements : -1);
        AddDebugLine(buf);
        // IDA 0x4CA440 calls Hud::DrawSprite_Wrapper(this) among HUD subsystem draws.
        // RE: keep DrawSprite_Wrapper as the debug-only A2C0/ABI9 probe site; call it here
        // for closer call-flow placement. Not a full DrawUI/DrawSprite_Wrapper port.
        DrawSprite_Wrapper();
        if (!(std::getenv("GTA2_TEXT_GBH") && std::getenv("GTA2_TEXT_GBH")[0] == '1')) {
            // Non-GBH debug bridge: direct overlay probe independent of Bsearch/gxt.
            DrawGTATextRaw_7280((wchar_t*)L"HUD TEXT BRIDGE OK", 8, 164);
        }
        // Quit prompt probe (IDA quit strings) - draw only as debug text, no state change.
        if (gText) {
            wchar_t* q1 = (wchar_t*)gText->Bsearch("quit1");
            if (q1) DrawGTATextRaw_7280(q1, 8, 180);
        }

        extern Game* gGame;
        if (gGame && gGame->PlayerMain && gGame->PlayerMain->quit1) {
            DrawQuitConfirm();
        }
        return 0;
    }


    // 0x004CA520


void Hud::DrawQuitConfirm() {
    // IDA 0x4CA440 quit block (DrawQuitConfirm address in headers needs confirmation).
    // Uses Bsearch quit1/2/3, GetStringWidth/GetNumberLines, centered layout, DrawGTATextRaw_7280.
    extern Game* gGame;
    if (!gGame || !gGame->PlayerMain || !gGame->PlayerMain->quit1) return;
    wchar_t* q1 = (gText ? (wchar_t*)gText->Bsearch("quit1") : nullptr);
    wchar_t* q2 = (gText ? (wchar_t*)gText->Bsearch("quit2") : nullptr);
    wchar_t* q3 = (gText ? (wchar_t*)gText->Bsearch("quit3") : nullptr);
    if (!q1) q1 = (wchar_t*)L"ARE YOU SURE?";
    if (!q2) q2 = (wchar_t*)L"PRESS Y TO QUIT";
    if (!q3) q3 = (wchar_t*)L"PRESS N TO CONTINUE";

    extern Font* gFont;
    Font localFont;
    Font* f = gFont ? gFont : &localFont;
    unsigned short style = 0; // TODO: unk_672F24
    int w1 = f->GetStringWidth(q1, style);
    int w2 = f->GetStringWidth(q2, style);
    int w3 = f->GetStringWidth(q3, style);
    // IDA 0x4CC0C0 GetNumberLines returns pixel height.
    int h1 = f->GetNumberLines(q1, style);
    int ch = f->GetCharHeight(style);
    if (ch <= 0) ch = 8;
    int nl = (h1 + ch - 1) / ch;
    if (nl <= 0) nl = 1;
    int v6 = (3 * (160 - nl)) / 2;
    int y1 = v6 - nl;
    int y2 = v6;
    int y3 = nl + v6;
    DrawGTATextRaw_7280(q1, (640 - w1) / 2, y1);
    DrawGTATextRaw_7280(q2, (640 - w2) / 2, y2);
    DrawGTATextRaw_7280(q3, (640 - w3) / 2, y3);
}

int Hud::DrawUIWrapper(void){
        return DrawUI();
    }


    // 0x004CA5D0


int Hud::Update2_Wrapper(void){
        return 0;
    }


    // 0x004CABE0


int Hud::SetSpeedText_Wrapper(void){
        return 0;
    }


    // 0x004CAC30


int Hud::UpdateWrapper(void){
        return 0;
    }

    // 0x004CAB50
int Hud::UpdateAll(void){
        // IDA 0x4CAB50 Hud::UpdateAll: AnimatePlayerStats, S86_5::Update, DebugInfo::ShowPlayerPosition,
        // S86_4::Update, TickMessage, HudText::DecrementTimer, S86_8::Update, HudBrief::Tick,
        // GarageInfo::UpdateCarGenerators, S86_7::RemoveExpired, HudArrow::UpdateAll,
        // HudMessage::DicrementTimeToShow, HudText2::DecrementTimer.
        // RE: most HUD subsystems are stubs/unconfirmed; only call safe guarded message tick here.
        TickMessage();
        return 0;
    }

// 0x004C69C0 IDA Hud::Hud1: field_0=0. RE field-name impl.
void Hud::Hud1() {
    this->field_0 = 0;
}
