// cInspector.cpp - struct field inspector window + globals dump (done.md)
// Shows live fields of known structures (Menu, MapGm, PlayerData) at their
// fixed addresses in the original GTA2.EXE. Unknown/gap fields are shown
// as numbers or text. All globals from done.md are listed too.
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include "cInspector.h"
#include "cMenu.h"
#include "cMapGm.h"
#include "cPlayerData.h"
#include "cText.h"
#include "cGang.h"
#include "cGame.h"
#include "cAudioManager.h"
#include "cCar.h"
#include "cPed.h"
#include "cWeapon.h"
#include "cS200Watch.h"
#include "AddrToFunc.h"
#include "GlobalsData.h"
#include "DebugLogFile.h"

// Fixed addresses of global instances (addresses from done.md)
// NOTE: 0x005EB160 is a global Menu* pointer cell (4 bytes), not the Menu struct.
// The real Menu is heap-allocated (operator_new(0x1EB40) in FUN_00457830).
// We read the pointer at dump time to follow the heap address.
static Menu*      GetRealMenu(void) { return (Menu*)(*(void**)0x005EB160); }
// gDMAudio lives directly at 0x005D85A0 (the object, not a pointer cell); raw state
// is hexdumped from this address by FormatDMAudioState (0x3E84 bytes = next global
// unk_5DC424 @0x005DC424).
static const void* GetRealDMAudio(void) { return (const void*)0x005D85A0; }
static MapGm*     s_pMapGm     = (MapGm*)0x005EC070;
static PlayerData* s_pPlayerData = (PlayerData*)0x0066B404;
static Text*      s_pText      = (Text*)0x00671550;

static HWND s_hWnd = NULL;
static HWND s_hEdit = NULL;
static BOOL s_classRegistered = FALSE;
static volatile long s_refreshPending = 0;
static BOOL s_paused = FALSE;
static BOOL s_skipZero = FALSE;
static BOOL s_saveFile = TRUE;
static BOOL s_s200Only = FALSE;
static BOOL s_s200Watch = FALSE;

#define INSP_FIELD(TYPE, MEMBER) { offsetof(TYPE, MEMBER), sizeof(((TYPE*)0)->MEMBER), #MEMBER }

struct InspField {
    int offset;
    int size;
    const char* name;
};

// ---------------------------------------------------------------------------
// Menu fields (cMenu.h, #pragma pack(1))
// ---------------------------------------------------------------------------
static const InspField kMenuFields[] = {
    INSP_FIELD(Menu, DirectInput),
    INSP_FIELD(Menu, InputDevice),
    INSP_FIELD(Menu, Keys),
    INSP_FIELD(Menu, FrontendState),
    INSP_FIELD(Menu, KeyboardAcquired),
    INSP_FIELD(Menu, FrontendKeysEnabled),
    INSP_FIELD(Menu, field_10E),
    INSP_FIELD(Menu, field_10F),
    INSP_FIELD(Menu, State),
    INSP_FIELD(Menu, field_114),
    INSP_FIELD(Menu, field_118),
    INSP_FIELD(Menu, FontStyle),
    INSP_FIELD(Menu, Page),
    INSP_FIELD(Menu, Filderer0x120),
    INSP_FIELD(Menu, pMenuPage),
    INSP_FIELD(Menu, pPlayerName),
    INSP_FIELD(Menu, field_C990),
    INSP_FIELD(Menu, field_C994),
    INSP_FIELD(Menu, field_C998),
    INSP_FIELD(Menu, field_C99C),
    INSP_FIELD(Menu, Length),
    INSP_FIELD(Menu, field_C99F),
    INSP_FIELD(Menu, Key),
    INSP_FIELD(Menu, field_C9A2),
    INSP_FIELD(Menu, MenuItems),
    INSP_FIELD(Menu, CurrentMenuItemsIndex),
    INSP_FIELD(Menu, field_C9B7),
    INSP_FIELD(Menu, NewKeyState),
    INSP_FIELD(Menu, OldKeyState),
    INSP_FIELD(Menu, field_C9C6),
    INSP_FIELD(Menu, field_C9C7),
    INSP_FIELD(Menu, TimeToWaitDemoStart),
    INSP_FIELD(Menu, FrameCounter),
    INSP_FIELD(Menu, isChaet),
    INSP_FIELD(Menu, field_C9CE),
    INSP_FIELD(Menu, field_C9CF),
    INSP_FIELD(Menu, TimeToWaitBeforeDemoStart),
    INSP_FIELD(Menu, S138),
    INSP_FIELD(Menu, MenuPic),
    INSP_FIELD(Menu, field_EDF5),
    INSP_FIELD(Menu, field_EDF6),
    INSP_FIELD(Menu, field_EDF8),
    INSP_FIELD(Menu, field_EDF9),
    INSP_FIELD(Menu, S139),
    INSP_FIELD(Menu, field_1EB1C),
    INSP_FIELD(Menu, field_1EB1E),
    INSP_FIELD(Menu, field_1EB1F),
    INSP_FIELD(Menu, field_1EB24),
    INSP_FIELD(Menu, field_1EB25),
    INSP_FIELD(Menu, field_1EB26),
    INSP_FIELD(Menu, field_1EB27),
    INSP_FIELD(Menu, field_1EB28),
    INSP_FIELD(Menu, field_1EB29),
    INSP_FIELD(Menu, field_1EB2A),
    INSP_FIELD(Menu, field_1EB2B),
    INSP_FIELD(Menu, field_1EB2C),
    INSP_FIELD(Menu, field_1EB2D),
    INSP_FIELD(Menu, field_1EB2E),
    INSP_FIELD(Menu, field_1EB2F),
    INSP_FIELD(Menu, field_1EB30),
    INSP_FIELD(Menu, field_1EB31),
    INSP_FIELD(Menu, field_1EB32),
    INSP_FIELD(Menu, field_1EB33),
    INSP_FIELD(Menu, field_1EB34),
    INSP_FIELD(Menu, field_1EB35),
    INSP_FIELD(Menu, field_1EB36),
    INSP_FIELD(Menu, field_1EB37),
    INSP_FIELD(Menu, field_1EB38),
    INSP_FIELD(Menu, field_1EB39),
    INSP_FIELD(Menu, A1EB3A),
    INSP_FIELD(Menu, AAAA),
    INSP_FIELD(Menu, field_1EB3C),
    INSP_FIELD(Menu, AAA),
    INSP_FIELD(Menu, field_1EB3F),
};
static const int kMenuFieldCount = sizeof(kMenuFields) / sizeof(kMenuFields[0]);

// ---------------------------------------------------------------------------
// MapGm fields (cMapGm.h)
// ---------------------------------------------------------------------------
static const InspField kMapGmFields[] = {
    INSP_FIELD(MapGm, gmpFile),
    INSP_FIELD(MapGm, styFile),
    INSP_FIELD(MapGm, sctiptFile),
    INSP_FIELD(MapGm, SaveFile),
    INSP_FIELD(MapGm, playerArena),
    INSP_FIELD(MapGm, bonusStage),
    INSP_FIELD(MapGm, field_0x402),
    INSP_FIELD(MapGm, PlayerSlotSave),
    INSP_FIELD(MapGm, Bonus),
    INSP_FIELD(MapGm, field_405),
    INSP_FIELD(MapGm, field_406),
    INSP_FIELD(MapGm, field_407),
    INSP_FIELD(MapGm, Arr10i),
    INSP_FIELD(MapGm, field_430),
    INSP_FIELD(MapGm, field_434),
    INSP_FIELD(MapGm, field_438),
    INSP_FIELD(MapGm, field_43A),
    INSP_FIELD(MapGm, field_43B),
    INSP_FIELD(MapGm, FragLimit),
    INSP_FIELD(MapGm, field_43E),
    INSP_FIELD(MapGm, field_43F),
    INSP_FIELD(MapGm, field_440),
    INSP_FIELD(MapGm, field_441),
    INSP_FIELD(MapGm, field_442),
    INSP_FIELD(MapGm, field_443),
    INSP_FIELD(MapGm, field_444),
    INSP_FIELD(MapGm, field_445),
    INSP_FIELD(MapGm, field_446),
    INSP_FIELD(MapGm, field_447),
    INSP_FIELD(MapGm, field_448),
    INSP_FIELD(MapGm, field_449),
    INSP_FIELD(MapGm, field_44A),
    INSP_FIELD(MapGm, field_44B),
    INSP_FIELD(MapGm, field_44C),
    INSP_FIELD(MapGm, field_44D),
    INSP_FIELD(MapGm, field_44E),
    INSP_FIELD(MapGm, field_44F),
    INSP_FIELD(MapGm, field_450),
    INSP_FIELD(MapGm, field_451),
    INSP_FIELD(MapGm, field_452),
    INSP_FIELD(MapGm, field_453),
    INSP_FIELD(MapGm, field_454),
    INSP_FIELD(MapGm, field_455),
    INSP_FIELD(MapGm, field_456),
    INSP_FIELD(MapGm, field_457),
    INSP_FIELD(MapGm, field_458),
    INSP_FIELD(MapGm, field_459),
    INSP_FIELD(MapGm, field_45A),
    INSP_FIELD(MapGm, field_45B),
    INSP_FIELD(MapGm, field_45C),
    INSP_FIELD(MapGm, field_45D),
    INSP_FIELD(MapGm, field_45E),
    INSP_FIELD(MapGm, field_45F),
    INSP_FIELD(MapGm, field_460),
    INSP_FIELD(MapGm, field_461),
    INSP_FIELD(MapGm, field_462),
    INSP_FIELD(MapGm, field_463),
    INSP_FIELD(MapGm, field_464),
    INSP_FIELD(MapGm, field_465),
    INSP_FIELD(MapGm, field_466),
    INSP_FIELD(MapGm, field_467),
    INSP_FIELD(MapGm, field_468),
    INSP_FIELD(MapGm, field_469),
    INSP_FIELD(MapGm, field_46A),
    INSP_FIELD(MapGm, field_46B),
    INSP_FIELD(MapGm, field_46C),
    INSP_FIELD(MapGm, field_46D),
    INSP_FIELD(MapGm, field_46E),
    INSP_FIELD(MapGm, field_46F),
    INSP_FIELD(MapGm, field_470),
    INSP_FIELD(MapGm, field_471),
    INSP_FIELD(MapGm, field_472),
    INSP_FIELD(MapGm, field_473),
    INSP_FIELD(MapGm, field_474),
    INSP_FIELD(MapGm, field_475),
    INSP_FIELD(MapGm, field_476),
    INSP_FIELD(MapGm, field_477),
    INSP_FIELD(MapGm, field_478),
    INSP_FIELD(MapGm, field_479),
    INSP_FIELD(MapGm, field_47A),
    INSP_FIELD(MapGm, field_47B),
    INSP_FIELD(MapGm, field_47C),
    INSP_FIELD(MapGm, field_47D),
    INSP_FIELD(MapGm, field_47E),
    INSP_FIELD(MapGm, field_47F),
    INSP_FIELD(MapGm, field_480),
    INSP_FIELD(MapGm, field_481),
    INSP_FIELD(MapGm, field_482),
    INSP_FIELD(MapGm, field_483),
    INSP_FIELD(MapGm, field_484),
    INSP_FIELD(MapGm, field_485),
    INSP_FIELD(MapGm, field_486),
    INSP_FIELD(MapGm, field_487),
    INSP_FIELD(MapGm, field_488),
    INSP_FIELD(MapGm, field_489),
    INSP_FIELD(MapGm, field_48A),
    INSP_FIELD(MapGm, field_48B),
    INSP_FIELD(MapGm, field_48C),
    INSP_FIELD(MapGm, field_48D),
    INSP_FIELD(MapGm, field_48E),
    INSP_FIELD(MapGm, field_48F),
    INSP_FIELD(MapGm, field_490),
    INSP_FIELD(MapGm, field_491),
    INSP_FIELD(MapGm, field_492),
    INSP_FIELD(MapGm, field_493),
    INSP_FIELD(MapGm, field_494),
    INSP_FIELD(MapGm, field_495),
    INSP_FIELD(MapGm, field_496),
    INSP_FIELD(MapGm, field_497),
    INSP_FIELD(MapGm, field_498),
    INSP_FIELD(MapGm, field_499),
    INSP_FIELD(MapGm, field_49A),
    INSP_FIELD(MapGm, field_49B),
    INSP_FIELD(MapGm, field_49C),
    INSP_FIELD(MapGm, field_49D),
    INSP_FIELD(MapGm, field_49E),
    INSP_FIELD(MapGm, field_49F),
    INSP_FIELD(MapGm, field_4A0),
    INSP_FIELD(MapGm, field_4A1),
    INSP_FIELD(MapGm, field_4A2),
    INSP_FIELD(MapGm, field_4A3),
    INSP_FIELD(MapGm, field_4A4),
    INSP_FIELD(MapGm, field_4A5),
    INSP_FIELD(MapGm, field_4A6),
    INSP_FIELD(MapGm, field_4A7),
    INSP_FIELD(MapGm, field_4A8),
    INSP_FIELD(MapGm, field_4A9),
    INSP_FIELD(MapGm, field_4AA),
    INSP_FIELD(MapGm, field_4AB),
    INSP_FIELD(MapGm, field_4AC),
    INSP_FIELD(MapGm, field_4AD),
    INSP_FIELD(MapGm, field_4AE),
    INSP_FIELD(MapGm, field_4AF),
    INSP_FIELD(MapGm, field_4B0),
    INSP_FIELD(MapGm, field_4B1),
    INSP_FIELD(MapGm, field_4B2),
    INSP_FIELD(MapGm, field_4B3),
    INSP_FIELD(MapGm, string_Arr0x16),
    INSP_FIELD(MapGm, gap4D4),
    INSP_FIELD(MapGm, field_570),
    INSP_FIELD(MapGm, field_571),
    INSP_FIELD(MapGm, field_572),
    INSP_FIELD(MapGm, field_573),
    INSP_FIELD(MapGm, SpecialTokens),
};
static const int kMapGmFieldCount = sizeof(kMapGmFields) / sizeof(kMapGmFields[0]);

// ---------------------------------------------------------------------------
// PlayerData fields (cPlayerData.h)
// ---------------------------------------------------------------------------
static const InspField kPlayerDataFields[] = {
    INSP_FIELD(PlayerData, field0),
    INSP_FIELD(PlayerData, field4),
    INSP_FIELD(PlayerData, field_8),
    INSP_FIELD(PlayerData, field_C),
    INSP_FIELD(PlayerData, field_10),
    INSP_FIELD(PlayerData, gap12),
    INSP_FIELD(PlayerData, field_17DC),
    INSP_FIELD(PlayerData, field_17DD),
    INSP_FIELD(PlayerData, field_17DE),
    INSP_FIELD(PlayerData, field_17DF),
    INSP_FIELD(PlayerData, field_17E0),
    INSP_FIELD(PlayerData, field_17E1),
    INSP_FIELD(PlayerData, field_17E2),
    INSP_FIELD(PlayerData, field_17E3),
    INSP_FIELD(PlayerData, field_17E4),
    INSP_FIELD(PlayerData, field_17E5),
    INSP_FIELD(PlayerData, field_17E6),
    INSP_FIELD(PlayerData, field_17E7),
    INSP_FIELD(PlayerData, field_17E8),
    INSP_FIELD(PlayerData, field_17E9),
    INSP_FIELD(PlayerData, field_17EA),
    INSP_FIELD(PlayerData, field_17EB),
    INSP_FIELD(PlayerData, field_17EC),
    INSP_FIELD(PlayerData, field_17ED),
    INSP_FIELD(PlayerData, field_17EE),
    INSP_FIELD(PlayerData, field_17EF),
    INSP_FIELD(PlayerData, field_17F0),
    INSP_FIELD(PlayerData, field_17F1),
    INSP_FIELD(PlayerData, field_17F2),
    INSP_FIELD(PlayerData, field_17F3),
    INSP_FIELD(PlayerData, field_17F4),
    INSP_FIELD(PlayerData, field_17F5),
    INSP_FIELD(PlayerData, field_17F6),
    INSP_FIELD(PlayerData, field_17F7),
    INSP_FIELD(PlayerData, field_17F8),
    INSP_FIELD(PlayerData, field_17F9),
    INSP_FIELD(PlayerData, field_17FA),
    INSP_FIELD(PlayerData, field_17FB),
    INSP_FIELD(PlayerData, field_17FC),
    INSP_FIELD(PlayerData, field_17FD),
    INSP_FIELD(PlayerData, field_17FE),
    INSP_FIELD(PlayerData, field_17FF),
    INSP_FIELD(PlayerData, arr_0x28),
    INSP_FIELD(PlayerData, gap1828),
    INSP_FIELD(PlayerData, field_1858),
    INSP_FIELD(PlayerData, field_1859),
    INSP_FIELD(PlayerData, field_185A),
    INSP_FIELD(PlayerData, field_185B),
    INSP_FIELD(PlayerData, field_185C),
    INSP_FIELD(PlayerData, field_185D),
    INSP_FIELD(PlayerData, field_185E),
    INSP_FIELD(PlayerData, field_185F),
    INSP_FIELD(PlayerData, field_1860),
    INSP_FIELD(PlayerData, field_1861),
    INSP_FIELD(PlayerData, field_1862),
    INSP_FIELD(PlayerData, field_1863),
    INSP_FIELD(PlayerData, field_1864),
    INSP_FIELD(PlayerData, field_1865),
    INSP_FIELD(PlayerData, field_1866),
    INSP_FIELD(PlayerData, field_1867),
    INSP_FIELD(PlayerData, field_1868),
    INSP_FIELD(PlayerData, field_1869),
    INSP_FIELD(PlayerData, field_186A),
    INSP_FIELD(PlayerData, field_186B),
    INSP_FIELD(PlayerData, field_186C),
    INSP_FIELD(PlayerData, field_186D),
    INSP_FIELD(PlayerData, field_186E),
    INSP_FIELD(PlayerData, field_186F),
    INSP_FIELD(PlayerData, field_1870),
    INSP_FIELD(PlayerData, field_1871),
    INSP_FIELD(PlayerData, field_1872),
    INSP_FIELD(PlayerData, field_1873),
    INSP_FIELD(PlayerData, field_1874),
    INSP_FIELD(PlayerData, field_1875),
    INSP_FIELD(PlayerData, field_1876),
    INSP_FIELD(PlayerData, field_1877),
    INSP_FIELD(PlayerData, field_1878),
    INSP_FIELD(PlayerData, field_1879),
    INSP_FIELD(PlayerData, field_187A),
    INSP_FIELD(PlayerData, field_187B),
    INSP_FIELD(PlayerData, field_187C),
    INSP_FIELD(PlayerData, field_187D),
    INSP_FIELD(PlayerData, field_187E),
    INSP_FIELD(PlayerData, field_187F),
    INSP_FIELD(PlayerData, field_1880),
    INSP_FIELD(PlayerData, field_1881),
    INSP_FIELD(PlayerData, field_1882),
    INSP_FIELD(PlayerData, field_1883),
    INSP_FIELD(PlayerData, field_1884),
    INSP_FIELD(PlayerData, field_1885),
    INSP_FIELD(PlayerData, field_1886),
    INSP_FIELD(PlayerData, field_1887),
    INSP_FIELD(PlayerData, field_1888),
    INSP_FIELD(PlayerData, field_1889),
    INSP_FIELD(PlayerData, field_188A),
    INSP_FIELD(PlayerData, field_188B),
    INSP_FIELD(PlayerData, field_188C),
    INSP_FIELD(PlayerData, field_188D),
    INSP_FIELD(PlayerData, field_188E),
    INSP_FIELD(PlayerData, field_188F),
    INSP_FIELD(PlayerData, S151_arr),
    INSP_FIELD(PlayerData, S151_a),
    INSP_FIELD(PlayerData, S151_1),
    INSP_FIELD(PlayerData, S151_2),
    INSP_FIELD(PlayerData, field_25B4),
    INSP_FIELD(PlayerData, field_25B5),
    INSP_FIELD(PlayerData, field_25B6),
    INSP_FIELD(PlayerData, field_25B7),
    INSP_FIELD(PlayerData, field_25B8),
    INSP_FIELD(PlayerData, field_25B9),
    INSP_FIELD(PlayerData, gap25BA),
    INSP_FIELD(PlayerData, field_25BB),
    INSP_FIELD(PlayerData, gap25BC),
    INSP_FIELD(PlayerData, field_25E4),
    INSP_FIELD(PlayerData, gap25E5),
    INSP_FIELD(PlayerData, field_25FF),
    INSP_FIELD(PlayerData, gap2600),
    INSP_FIELD(PlayerData, field_261A),
    INSP_FIELD(PlayerData, gap261B),
    INSP_FIELD(PlayerData, field_262F),
    INSP_FIELD(PlayerData, gap2630),
    INSP_FIELD(PlayerData, field_264A),
    INSP_FIELD(PlayerData, gap264B),
    INSP_FIELD(PlayerData, field_267D),
    INSP_FIELD(PlayerData, gap267E),
    INSP_FIELD(PlayerData, field_2693),
    INSP_FIELD(PlayerData, field_2694),
    INSP_FIELD(PlayerData, field_2695),
    INSP_FIELD(PlayerData, field_2696),
    INSP_FIELD(PlayerData, field_2697),
    INSP_FIELD(PlayerData, field_2698),
    INSP_FIELD(PlayerData, field_2699),
    INSP_FIELD(PlayerData, field_269A),
    INSP_FIELD(PlayerData, field_269B),
    INSP_FIELD(PlayerData, field_269C),
    INSP_FIELD(PlayerData, field_269D),
    INSP_FIELD(PlayerData, field_269E),
    INSP_FIELD(PlayerData, field_269F),
    INSP_FIELD(PlayerData, pPlayerSlotSave),
};
static const int kPlayerDataFieldCount = sizeof(kPlayerDataFields) / sizeof(kPlayerDataFields[0]);

// ---------------------------------------------------------------------------
// Game fields (cGame.h) - heap instance; gGame cell @0x005EB4FC holds pointer
// ---------------------------------------------------------------------------
static const InspField kGameFields[] = {
    INSP_FIELD(Game, Status),
    { offsetof(Game, pPlayer) + 0 * sizeof(Player*), sizeof(Player*), "pPlayer[0]" },
    { offsetof(Game, pPlayer) + 1 * sizeof(Player*), sizeof(Player*), "pPlayer[1]" },
    { offsetof(Game, pPlayer) + 2 * sizeof(Player*), sizeof(Player*), "pPlayer[2]" },
    { offsetof(Game, pPlayer) + 3 * sizeof(Player*), sizeof(Player*), "pPlayer[3]" },
    { offsetof(Game, pPlayer) + 4 * sizeof(Player*), sizeof(Player*), "pPlayer[4]" },
    { offsetof(Game, pPlayer) + 5 * sizeof(Player*), sizeof(Player*), "pPlayer[5]" },
    INSP_FIELD(Game, CurrentPlayer),
    INSP_FIELD(Game, Index),
    INSP_FIELD(Game, CurrentPlayerCopy),
    INSP_FIELD(Game, fi_22),
    INSP_FIELD(Game, NumberPlayer),
    INSP_FIELD(Game, PlayerInFocus),
    INSP_FIELD(Game, fi_25),
    INSP_FIELD(Game, field_26),
    INSP_FIELD(Game, field_27),
    INSP_FIELD(Game, isDead),
    INSP_FIELD(Game, State),
    INSP_FIELD(Game, NoFrameLimit),
    INSP_FIELD(Game, SkipPolice),
    INSP_FIELD(Game, Player),
    INSP_FIELD(Game, gSkilPolice),
    INSP_FIELD(Game, field_3D),
    INSP_FIELD(Game, field_3E),
    INSP_FIELD(Game, field_3F),
};
static const int kGameFieldCount = sizeof(kGameFields) / sizeof(kGameFields[0]);

// ---------------------------------------------------------------------------
// Player fields (cPlayer.h) - heap instances, one per slot; the pointers live
// in Game->pPlayer[0..5] (Game+0x04). Size 0x85C (operator_new in gta2.exe.c).
// ---------------------------------------------------------------------------
static const InspField kPlayerFields[] = {
    INSP_FIELD(Player, CurrentPlayer),
    INSP_FIELD(Player, Player),
    INSP_FIELD(Player, Rotate),
    INSP_FIELD(Player, FW),
    INSP_FIELD(Player, S103),
    INSP_FIELD(Player, Sw),
    INSP_FIELD(Player, TypeWeapon),
    INSP_FIELD(Player, S103_1),
    INSP_FIELD(Player, SelectWeaponNext),
    INSP_FIELD(Player, field_1E),
    INSP_FIELD(Player, field_1F),
    INSP_FIELD(Player, pS103),
    INSP_FIELD(Player, ID),
    INSP_FIELD(Player, S103_2),
    INSP_FIELD(Player, MoneyValue),
    INSP_FIELD(Player, Ids),
    INSP_FIELD(Player, field_2F),
    INSP_FIELD(Player, S103_5),
    INSP_FIELD(Player, RESPECT),
    INSP_FIELD(Player, field_38),
    INSP_FIELD(Player, field_3C),
    INSP_FIELD(Player, S103_4),
    INSP_FIELD(Player, DeathReason),
    INSP_FIELD(Player, Tango1),
    INSP_FIELD(Player, Sound),
    INSP_FIELD(Player, field_50),
    INSP_FIELD(Player, field_54),
    INSP_FIELD(Player, field_58),
    INSP_FIELD(Player, sCar1),
    INSP_FIELD(Player, field_60),
    INSP_FIELD(Player, field_64),
    INSP_FIELD(Player, MultiPlayerMode),
    INSP_FIELD(Player, field_6C),
    INSP_FIELD(Player, Up),
    INSP_FIELD(Player, Down),
    INSP_FIELD(Player, Left),
    INSP_FIELD(Player, Right),
    INSP_FIELD(Player, prevWeapon),
    INSP_FIELD(Player, nextWeapon),
    INSP_FIELD(Player, debugKey1),
    INSP_FIELD(Player, debugKey2),
    INSP_FIELD(Player, Forward),
    INSP_FIELD(Player, Backward),
    INSP_FIELD(Player, RotateLeft),
    INSP_FIELD(Player, RotateRight),
    INSP_FIELD(Player, Attack),
    INSP_FIELD(Player, Enter),
    INSP_FIELD(Player, Jump),
    INSP_FIELD(Player, NextWeaponZ),
    INSP_FIELD(Player, PrevWeaponX),
    INSP_FIELD(Player, keySpecial),
    INSP_FIELD(Player, keySpecial2),
    INSP_FIELD(Player, field_83),
    INSP_FIELD(Player, field_84),
    INSP_FIELD(Player, field_88),
    INSP_FIELD(Player, AttackIsChanged),
    INSP_FIELD(Player, field_8D),
    INSP_FIELD(Player, PlayerNext),
    INSP_FIELD(Player, field_8F),
    INSP_FIELD(Player, CameraOrPhysics1),
    INSP_FIELD(Player, field_94),
    INSP_FIELD(Player, field_95),
    INSP_FIELD(Player, field_96),
    INSP_FIELD(Player, field_97),
    INSP_FIELD(Player, State),
    INSP_FIELD(Player, AudioManager),
    INSP_FIELD(Player, field_A0),
    INSP_FIELD(Player, field_A7),
    INSP_FIELD(Player, field_A8),
    INSP_FIELD(Player, field_A9),
    INSP_FIELD(Player, sbw),
    INSP_FIELD(Player, tpa),
    INSP_FIELD(Player, field_AC),
    INSP_FIELD(Player, S1__),
    INSP_FIELD(Player, field_D3),
    INSP_FIELD(Player, field_DB),
    INSP_FIELD(Player, field_EA),
    INSP_FIELD(Player, field_F7),
    INSP_FIELD(Player, field_102),
    INSP_FIELD(Player, field_115),
    INSP_FIELD(Player, field_116),
    INSP_FIELD(Player, field_117),
    INSP_FIELD(Player, field_118),
    INSP_FIELD(Player, field_11C),
    INSP_FIELD(Player, field_120),
    INSP_FIELD(Player, field_124),
    INSP_FIELD(Player, field_125),
    INSP_FIELD(Player, field_126),
    INSP_FIELD(Player, field_127),
    INSP_FIELD(Player, field_128),
    INSP_FIELD(Player, field_12C),
    INSP_FIELD(Player, field_130),
    INSP_FIELD(Player, CameraOrPhysics),
    INSP_FIELD(Player, field_154),
    INSP_FIELD(Player, field_193),
    INSP_FIELD(Player, field_1A6),
    INSP_FIELD(Player, field_1C7),
    INSP_FIELD(Player, field_1D1),
    INSP_FIELD(Player, field_1D4),
    INSP_FIELD(Player, field_1D8),
    INSP_FIELD(Player, field_1DC),
    INSP_FIELD(Player, Camer_X_View),
    INSP_FIELD(Player, Camer_Y_View),
    INSP_FIELD(Player, Camer_Z_View),
    INSP_FIELD(Player, field_1F3),
    INSP_FIELD(Player, field_1FA),
    INSP_FIELD(Player, field_202),
    INSP_FIELD(Player, CameraOrPhysics2),
    INSP_FIELD(Player, field_20C),
    INSP_FIELD(Player, field_229),
    INSP_FIELD(Player, field_24D),
    INSP_FIELD(Player, field_259),
    INSP_FIELD(Player, field_26B),
    INSP_FIELD(Player, field_28C),
    INSP_FIELD(Player, field_298),
    INSP_FIELD(Player, field_29E),
    INSP_FIELD(Player, field_29F),
    INSP_FIELD(Player, AuxGameCameraX),
    INSP_FIELD(Player, AuxGameCameraY),
    INSP_FIELD(Player, AuxGameCameraZ),
    INSP_FIELD(Player, MainPed),
    INSP_FIELD(Player, pPassenger),
    INSP_FIELD(Player, sCar2),
    INSP_FIELD(Player, field_2D0),
    INSP_FIELD(Player, Money),
    INSP_FIELD(Player, field_343),
    INSP_FIELD(Player, field_3E4),
    INSP_FIELD(Player, field_41A),
    INSP_FIELD(Player, field_449),
    INSP_FIELD(Player, field_640),
    INSP_FIELD(Player, field_644),
    INSP_FIELD(Player, field_678),
    INSP_FIELD(Player, field_67C),
    INSP_FIELD(Player, field_680),
    INSP_FIELD(Player, field_682),
    INSP_FIELD(Player, Lives),
    INSP_FIELD(Player, MultiPlayer),
    INSP_FIELD(Player, field_6C0),
    INSP_FIELD(Player, field_6D9),
    INSP_FIELD(Player, field_6E5),
    INSP_FIELD(Player, field_6EC),
    INSP_FIELD(Player, PowerUp),
    INSP_FIELD(Player, sWeapon),
    INSP_FIELD(Player, SelectWeapon),
    INSP_FIELD(Player, quit1),
    INSP_FIELD(Player, field_78B),
    INSP_FIELD(Player, sPed1),
    INSP_FIELD(Player, Network),
    INSP_FIELD(Player, field_79E),
    INSP_FIELD(Player, string_Arr0x16),
};
static const int kPlayerFieldCount = sizeof(kPlayerFields) / sizeof(kPlayerFields[0]);

// ---------------------------------------------------------------------------
// Car fields (cCar.h) - heap instances in gActiveCarsPool (0xD264 pool,
// 176 cars x 0x132); pointers also arrive via Player->sCar1/sCar2 and
// Ped->Vehicle. Source of truth: IDA struct Car, gta2.exe.h:3279.
// ---------------------------------------------------------------------------
static const InspField kCarFields[] = {
    INSP_FIELD(Car, pCar),
    INSP_FIELD(Car, Passenger),
    INSP_FIELD(Car, PlayerStats),
    INSP_FIELD(Car, CarDoor),
    INSP_FIELD(Car, LastCar),
    INSP_FIELD(Car, CarSprite),
    INSP_FIELD(Car, Driver),
    INSP_FIELD(Car, Player),
    INSP_FIELD(Car, EngineStruct),
    INSP_FIELD(Car, Model),
    INSP_FIELD(Car, TrailerCtrl),
    INSP_FIELD(Car, field_68),
    INSP_FIELD(Car, ID),
    INSP_FIELD(Car, lastDamagingPed),
    INSP_FIELD(Car, Damage),
    INSP_FIELD(Car, field_76),
    INSP_FIELD(Car, PhysicsBitmask),
    INSP_FIELD(Car, field_7A),
    INSP_FIELD(Car, field_7B),
    INSP_FIELD(Car, SearchType),
    INSP_FIELD(Car, field_80),
    INSP_FIELD(Car, field_81),
    INSP_FIELD(Car, field_82),
    INSP_FIELD(Car, field_83),
    INSP_FIELD(Car, CarType),
    INSP_FIELD(Car, Mask),
    INSP_FIELD(Car, FireState),
    INSP_FIELD(Car, field_8D),
    INSP_FIELD(Car, AlarmTime),
    INSP_FIELD(Car, field_8F),
    INSP_FIELD(Car, DamageType),
    INSP_FIELD(Car, DamageShotTimer),
    INSP_FIELD(Car, PlayerId),
    INSP_FIELD(Car, field_96),
    INSP_FIELD(Car, field_97),
    INSP_FIELD(Car, locksDoor),
    INSP_FIELD(Car, engineState),
    INSP_FIELD(Car, trafficCarType),
    INSP_FIELD(Car, sirenState),
    INSP_FIELD(Car, sirenPhase),
    INSP_FIELD(Car, field_A6),
    INSP_FIELD(Car, horn),
    INSP_FIELD(Car, field_A8),
    INSP_FIELD(Car, FireTimer),
    INSP_FIELD(Car, field_AA),
    INSP_FIELD(Car, field_AB),
    INSP_FIELD(Car, field_AC),
    INSP_FIELD(Car, field_B0),
    INSP_FIELD(Car, currentUpgradeSound),
    INSP_FIELD(Car, field_B8),
    INSP_FIELD(Car, field_B9),
    INSP_FIELD(Car, field_BA),
    INSP_FIELD(Car, gapBB),
    INSP_FIELD(Car, gapBC),
};
static const int kCarFieldCount = sizeof(kCarFields) / sizeof(kCarFields[0]);

// ---------------------------------------------------------------------------
// Ped fields (cPed.h) - heap instances in gPedManager pool (0x203AC pool,
// 200 peds x 0x294); main ped reachable via Player->MainPed. Source of truth:
// IDA struct Ped, gta2.exe.h:3925.
// ---------------------------------------------------------------------------
static const InspField kPedFields[] = {
    INSP_FIELD(Ped, S200),
    INSP_FIELD(Ped, gap9),
    INSP_FIELD(Ped, field_CB),
    INSP_FIELD(Ped, field_CC),
    INSP_FIELD(Ped, field_CD),
    INSP_FIELD(Ped, field_CE),
    INSP_FIELD(Ped, field_CF),
    INSP_FIELD(Ped, field_D0),
    INSP_FIELD(Ped, field_D1),
    INSP_FIELD(Ped, field_D2),
    INSP_FIELD(Ped, field_D3),
    INSP_FIELD(Ped, field_D4),
    INSP_FIELD(Ped, field_D5),
    INSP_FIELD(Ped, field_D6),
    INSP_FIELD(Ped, field_D7),
    INSP_FIELD(Ped, field_D8),
    INSP_FIELD(Ped, field_D9),
    INSP_FIELD(Ped, field_DA),
    INSP_FIELD(Ped, field_DB),
    INSP_FIELD(Ped, field_DC),
    INSP_FIELD(Ped, field_DD),
    INSP_FIELD(Ped, field_DE),
    INSP_FIELD(Ped, field_DF),
    INSP_FIELD(Ped, field_E0),
    INSP_FIELD(Ped, field_E1),
    INSP_FIELD(Ped, field_E2),
    INSP_FIELD(Ped, field_E3),
    INSP_FIELD(Ped, field_E4),
    INSP_FIELD(Ped, field_E5),
    INSP_FIELD(Ped, field_E6),
    INSP_FIELD(Ped, field_E7),
    INSP_FIELD(Ped, field_E8),
    INSP_FIELD(Ped, field_E9),
    INSP_FIELD(Ped, field_EA),
    INSP_FIELD(Ped, field_EB),
    INSP_FIELD(Ped, field_EC),
    INSP_FIELD(Ped, field_ED),
    INSP_FIELD(Ped, field_EE),
    INSP_FIELD(Ped, field_EF),
    INSP_FIELD(Ped, field_F0),
    INSP_FIELD(Ped, field_F1),
    INSP_FIELD(Ped, field_F2),
    INSP_FIELD(Ped, field_F3),
    INSP_FIELD(Ped, field_F4),
    INSP_FIELD(Ped, field_F5),
    INSP_FIELD(Ped, field_F6),
    INSP_FIELD(Ped, field_F7),
    INSP_FIELD(Ped, field_F8),
    INSP_FIELD(Ped, field_F9),
    INSP_FIELD(Ped, field_FA),
    INSP_FIELD(Ped, isPlayer),
    INSP_FIELD(Ped, field_FF),
    INSP_FIELD(Ped, field_100),
    INSP_FIELD(Ped, field_101),
    INSP_FIELD(Ped, field_102),
    INSP_FIELD(Ped, field_103),
    INSP_FIELD(Ped, field_104),
    INSP_FIELD(Ped, field_105),
    INSP_FIELD(Ped, field_106),
    INSP_FIELD(Ped, GameObject2),
    INSP_FIELD(Ped, field_10B),
    INSP_FIELD(Ped, field_10C),
    INSP_FIELD(Ped, field_10D),
    INSP_FIELD(Ped, field_10E),
    INSP_FIELD(Ped, WeaponSelect),
    INSP_FIELD(Ped, field_113),
    INSP_FIELD(Ped, field_114),
    INSP_FIELD(Ped, field_115),
    INSP_FIELD(Ped, field_116),
    INSP_FIELD(Ped, field_117),
    INSP_FIELD(Ped, field_119),
    INSP_FIELD(Ped, field_11A),
    INSP_FIELD(Ped, field_11B),
    INSP_FIELD(Ped, field_11C),
    INSP_FIELD(Ped, field_11D),
    INSP_FIELD(Ped, field_11E),
    INSP_FIELD(Ped, field_11F),
    INSP_FIELD(Ped, field_120),
    INSP_FIELD(Ped, field_121),
    INSP_FIELD(Ped, field_122),
    INSP_FIELD(Ped, field_123),
    INSP_FIELD(Ped, field_124),
    INSP_FIELD(Ped, field_125),
    INSP_FIELD(Ped, field_126),
    INSP_FIELD(Ped, field_127),
    INSP_FIELD(Ped, field_128),
    INSP_FIELD(Ped, field_12A),
    INSP_FIELD(Ped, field_12B),
    INSP_FIELD(Ped, field_12C),
    INSP_FIELD(Ped, field_12E),
    INSP_FIELD(Ped, field_130),
    INSP_FIELD(Ped, field_132),
    INSP_FIELD(Ped, field_134),
    INSP_FIELD(Ped, field_136),
    INSP_FIELD(Ped, field_137),
    INSP_FIELD(Ped, GameObject1),
    INSP_FIELD(Ped, field_13C),
    INSP_FIELD(Ped, Car1),
    INSP_FIELD(Ped, sPed1),
    INSP_FIELD(Ped, Driver),
    INSP_FIELD(Ped, LinkedPed),
    INSP_FIELD(Ped, Vehicle),
    INSP_FIELD(Ped, CurrentVehicle),
    INSP_FIELD(Ped, TargetCarForEnter),
    INSP_FIELD(Ped, Player),
    INSP_FIELD(Ped, NextPed),
    INSP_FIELD(Ped, S169),
    INSP_FIELD(Ped, GameObject),
    INSP_FIELD(Ped, CurrentCar),
    INSP_FIELD(Ped, SelectedWeapon),
    INSP_FIELD(Ped, Weapon1),
    INSP_FIELD(Ped, Weapon2),
    INSP_FIELD(Ped, Gang),
    INSP_FIELD(Ped, DriverPed),
    INSP_FIELD(Ped, field_184),
    INSP_FIELD(Ped, LastCharPunched),
    INSP_FIELD(Ped, field_18C),
    INSP_FIELD(Ped, S94),
    INSP_FIELD(Ped, field_194),
    INSP_FIELD(Ped, sPed3),
    INSP_FIELD(Ped, Gang1),
    INSP_FIELD(Ped, PedId),
    INSP_FIELD(Ped, TargetCarDoor1),
    INSP_FIELD(Ped, PoliceStar1),
    INSP_FIELD(Ped, ElvisLeader),
    INSP_FIELD(Ped, XCoordinate),
    INSP_FIELD(Ped, PositionY),
    INSP_FIELD(Ped, Camer_Z_View),
    INSP_FIELD(Ped, PositionX1),
    INSP_FIELD(Ped, PositionY1),
    INSP_FIELD(Ped, PositionZ2),
    INSP_FIELD(Ped, X),
    INSP_FIELD(Ped, Y),
    INSP_FIELD(Ped, Z),
    INSP_FIELD(Ped, field_1D0),
    INSP_FIELD(Ped, field_1D4),
    INSP_FIELD(Ped, field_1D8),
    INSP_FIELD(Ped, OCCUPATION),
    INSP_FIELD(Ped, DriverPed1),
    INSP_FIELD(Ped, PositionZ1),
    INSP_FIELD(Ped, field_1E8),
    INSP_FIELD(Ped, field_1EC),
    INSP_FIELD(Ped, field_1F0),
    INSP_FIELD(Ped, field_1F4),
    INSP_FIELD(Ped, CurrentAction1),
    INSP_FIELD(Ped, field_1FC),
    INSP_FIELD(Ped, ID),
    INSP_FIELD(Ped, IDPed),
    INSP_FIELD(Ped, Invulnerability),
    INSP_FIELD(Ped, PoliceStar),
    INSP_FIELD(Ped, field_20C),
    INSP_FIELD(Ped, field_20E),
    INSP_FIELD(Ped, field_210),
    INSP_FIELD(Ped, field_212),
    INSP_FIELD(Ped, field_214),
    INSP_FIELD(Ped, Health),
    INSP_FIELD(Ped, ObjectiveTimer),
    INSP_FIELD(Ped, CarStateTimer),
    INSP_FIELD(Ped, Flags),
    INSP_FIELD(Ped, field_220),
    INSP_FIELD(Ped, field_224),
    INSP_FIELD(Ped, DamageState),
    INSP_FIELD(Ped, ExitAnimState),
    INSP_FIELD(Ped, field_227),
    INSP_FIELD(Ped, field_228),
    INSP_FIELD(Ped, field_22C),
    INSP_FIELD(Ped, field_230),
    INSP_FIELD(Ped, field_234),
    INSP_FIELD(Ped, field_235),
    INSP_FIELD(Ped, field_236),
    INSP_FIELD(Ped, field_237),
    INSP_FIELD(Ped, SearchType),
    INSP_FIELD(Ped, CarId),
    INSP_FIELD(Ped, field_23D),
    INSP_FIELD(Ped, field_23E),
    INSP_FIELD(Ped, field_23F),
    INSP_FIELD(Ped, Occupation),
    INSP_FIELD(Ped, Remap),
    INSP_FIELD(Ped, field_245),
    INSP_FIELD(Ped, field_246),
    INSP_FIELD(Ped, field_247),
    INSP_FIELD(Ped, TargetCarDoor),
    INSP_FIELD(Ped, AnimationState),
    INSP_FIELD(Ped, field_24D),
    INSP_FIELD(Ped, field_24E),
    INSP_FIELD(Ped, field_24F),
    INSP_FIELD(Ped, field_250),
    INSP_FIELD(Ped, field_254),
    INSP_FIELD(Ped, field_255),
    INSP_FIELD(Ped, field_256),
    INSP_FIELD(Ped, field_257),
    INSP_FIELD(Ped, ActionState),
    INSP_FIELD(Ped, CurrentAction),
    INSP_FIELD(Ped, field_260),
    INSP_FIELD(Ped, field_261),
    INSP_FIELD(Ped, field_262),
    INSP_FIELD(Ped, field_263),
    INSP_FIELD(Ped, field_264),
    INSP_FIELD(Ped, field_265),
    INSP_FIELD(Ped, field_266),
    INSP_FIELD(Ped, field_267),
    INSP_FIELD(Ped, field_268),
    INSP_FIELD(Ped, field_269),
    INSP_FIELD(Ped, field_26A),
    INSP_FIELD(Ped, field_26B),
    INSP_FIELD(Ped, GraphicType),
    INSP_FIELD(Ped, field_270),
    INSP_FIELD(Ped, GangCarModel),
    INSP_FIELD(Ped, PedState),
    INSP_FIELD(Ped, field_27C),
    INSP_FIELD(Ped, SavedState),
    INSP_FIELD(Ped, field_284),
    INSP_FIELD(Ped, field_288),
    INSP_FIELD(Ped, field_28C),
    INSP_FIELD(Ped, DamageType),
};
static const int kPedFieldCount = sizeof(kPedFields) / sizeof(kPedFields[0]);

// ---------------------------------------------------------------------------
// Weapon/WeaponDatabase fields (cWeapon.h) - 255-slot heap table; the global
// gWeaponDatabase pointer cell @0x005D85A0-style lives @0x00673944 (pointer
// cell, deref at dump time). Heap instance op_new(0x2FDC) = 8 + 255*0x30.
// ---------------------------------------------------------------------------
static const InspField kWeaponFields[] = {
    INSP_FIELD(Weapon, Ammo),
    INSP_FIELD(Weapon, TimeToReload),
    INSP_FIELD(Weapon, field_3),
    INSP_FIELD(Weapon, SMG),
    INSP_FIELD(Weapon, field_8),
    INSP_FIELD(Weapon, field_C),
    INSP_FIELD(Weapon, shortField),
    INSP_FIELD(Weapon, field_12),
    INSP_FIELD(Weapon, field_13),
    INSP_FIELD(Weapon, Car),
    INSP_FIELD(Weapon, NextWeapon),
    INSP_FIELD(Weapon, TypeWeapon),
    INSP_FIELD(Weapon, field_20),
    INSP_FIELD(Weapon, field_21),
    INSP_FIELD(Weapon, field_22),
    INSP_FIELD(Weapon, field_23),
    INSP_FIELD(Weapon, Ped),
    INSP_FIELD(Weapon, SoundWeapon),
    INSP_FIELD(Weapon, field_2C),
    INSP_FIELD(Weapon, field_2D),
    INSP_FIELD(Weapon, field_2E),
    INSP_FIELD(Weapon, field_2F),
};
static const int kWeaponFieldCount = sizeof(kWeaponFields) / sizeof(kWeaponFields[0]);

static const InspField kWeaponDatabaseFields[] = {
    INSP_FIELD(WeaponDatabase, sWeapon),
    INSP_FIELD(WeaponDatabase, NextWeapon),
    INSP_FIELD(WeaponDatabase, sWeapon_Arr255),
    INSP_FIELD(WeaponDatabase, field_2FD8),
    INSP_FIELD(WeaponDatabase, field_2FDA),
    INSP_FIELD(WeaponDatabase, field_2FDB),
};
static const int kWeaponDatabaseFieldCount =
    sizeof(kWeaponDatabaseFields) / sizeof(kWeaponDatabaseFields[0]);

// gWeaponDatabase is a pointer cell @0x00673944; deref to the heap instance.
static WeaponDatabase* GetRealWeaponDatabase(void) {
    return *(WeaponDatabase**)0x00673944;
}

// ---------------------------------------------------------------------------
// PedManager fields (gta2.exe.h:10201): heap instance 0x203AC; the global
// gPedManager pointer cell @0x005E5BBC holds the heap address.
// ---------------------------------------------------------------------------
static const InspField kPedManagerFields[] = {
    INSP_FIELD(PedManager, FirstElement),
    INSP_FIELD(PedManager, NextPed),
    INSP_FIELD(PedManager, PedsInUse),
    INSP_FIELD(PedManager, field_203AA),
    INSP_FIELD(PedManager, field_203AB),
};
static const int kPedManagerFieldCount =
    sizeof(kPedManagerFields) / sizeof(kPedManagerFields[0]);

static PedManager* GetRealPedManager(void) {
    return *(PedManager**)0x005E5BBC;
}

// ---------------------------------------------------------------------------
// AudioManager fields (cAudioManager.h) - fixed global @0x005DCBC8
// ---------------------------------------------------------------------------
static const InspField kAudioManagerFields[] = {
    INSP_FIELD(AudioManager, AudioObject),
    INSP_FIELD(AudioManager, IsUserPaused),
    INSP_FIELD(AudioManager, field_2),
    INSP_FIELD(AudioManager, field_4),
    INSP_FIELD(AudioManager, SampCount),
    INSP_FIELD(AudioManager, Sound3D),
    INSP_FIELD(AudioManager, field_10),
    INSP_FIELD(AudioManager, SampleRate),
    INSP_FIELD(AudioManager, EffectsVolume),
    INSP_FIELD(AudioManager, MusicVolume),
    INSP_FIELD(AudioManager, SFXVol),
    INSP_FIELD(AudioManager, CDVol),
    INSP_FIELD(AudioManager, Car),
    INSP_FIELD(AudioManager, Player),
    INSP_FIELD(AudioManager, SoundCar),
    INSP_FIELD(AudioManager, HZ),
    INSP_FIELD(AudioManager, Arr32_S155),
    INSP_FIELD(AudioManager, Index),
    INSP_FIELD(AudioManager, field_5450),
    INSP_FIELD(AudioManager, relToAudio),
    INSP_FIELD(AudioManager, VOCAL),
    INSP_FIELD(AudioManager, Vocal),
    INSP_FIELD(AudioManager, field_5460),
    INSP_FIELD(AudioManager, field_5474),
    INSP_FIELD(AudioManager, AudioBuffer),
};
static const int kAudioManagerFieldCount = sizeof(kAudioManagerFields) / sizeof(kAudioManagerFields[0]);

// ---------------------------------------------------------------------------
// All globals from done.md (only rows with an address)
// ---------------------------------------------------------------------------
struct InspGlobal {
    const char* name;
    unsigned long addr;
    unsigned long size;
};

static const InspGlobal kGlobals[] = {
    { "S2 ActiveCarsPool",       0x0066ab7c, 0xD264 },
    { "S4 CarColorsPalette",     0x005e4ca0, 0xE0C4 },
    { "S8 CarAudioSettings",     0x005e4ca8, 0x14 },
    { "S10 CarPhysicsWorld",     0x005e508c, 0x8F74 },
    { "S13 General",             0x005e8108, 0x8 },
    { "S14 Text",                0x00671550, 0x14 },
    { "S15 Style",               0x00670684, 0x106c },
    { "S16 MapRelatedStruct",    0x00662c08, 0x370 },
    { "S17 EntityManager",       0x006633c8, 0x2f04 },
    { "S18 Display",             0x005e8b80, 0x1c },
    { "S20 RenderManager",       0x00672578, 0x2ee4 },
    { "S21 CameraManager",       0x0067257c, 0xfa4 },
    { "S22 Mike",                0x00664168, 0xa80 },
    { "S23 CarSystemManager",    0x005e4ca4, 0x6c },
    { "S25 MissionObjective",    0x0067280c, 0x214 },
    { "S26 MissionManager",      0x006644bc, 0xC1EA8 },
    { "S27 MissionScriptObjects",0x006644c0, 0x8ec },
    { "S31 <unknown>",           0x006644b8, 0x25c },
    { "S33 Camera",              0x006644c4, 0x25c },
    { "S35 Timing",              0x00671e9c, 0x54 },
    { "S37 Sprite",              0x0066ff24, 0x8 },
    { "S38 SpriteS1",            0x0066ff1c, 0x49B28 },
    { "S39 SpriteS2",            0x0066ff20, 0x14 },
    { "S45 SpriteS4",            0x006702bc, 0x1C24 },
    { "S47 Character",           0x005e5bc0, 0xC },
    { "S48 PedManager",          0x005e5bbc, 0x203AC },
    { "S50 PedPool",             0x0066a3b4, 0x11944 },
    { "S51 GameObject",          0x0066a3bc, 0xB4 },
    { "S52 ObjectPool",          0x005e5fbc, 0x324 },
    { "S53 Collide",             0x005e6680, 0xC },
    { "S54 PickupInfo",          0x005e6684, 0x8004 },
    { "S55 PowerUp",             0x005e6688, 0x11944 },
    { "S56 Checkpoint1",         0x005e668c, 0x400 },
    { "S56_1 Checkpoint2",       0x005e6690, 0x400 },
    { "S56_2 Checkpoint3",       0x005e6694, 0x400 },
    { "S57 PathNode",            0x00665b40, 0x8CA8 },
    { "S59 FileMgr",             0x00661e98, 0x0 },
    { "S60 Object",              0x00665788, 0x5C },
    { "S61 CollisionBox",        0x00665784, 0x0 },
    { "S64 TriggerVolume",       0x0066577c, 0x226C },
    { "S66 <unknown>",           0x00665780, 0x5A40 },
    { "S68 ScriptThread",        0x0066fb0c, 0x0 },
    { "S69 TileAnim",            0x00671c08, 0x2 },
    { "S70 TileAnim1",           0x00671c0c, 0x4BC },
    { "S72 Arsenal",             0x00673948, 0x8 },
    { "S73 WeaponDatabase",      0x00673944, 0x2FDC },
    { "S75 Door",                0x005e9378, 0x4D4 },
    { "S77 MenuInfo",            0x005e9374, 0x2c4 },
    { "S79 Ambulance",           0x00663de4, 0x110 },
    { "S81 PublicTransport",     0x0066bb50, 0x181C },
    { "S84 Taxi",                0x006708e0, 0x4 },
    { "S86 Hud",                 0x00672f40, 0x0 },
    { "S87 TextureManager",      0x00671978, 0x0 },
    { "S90 TrafficLigthStruct",  0x006721cc, 0x194 },
    { "S91 JuncIds",             0x005d351c, 0xcc68 },
    { "S96 CarEngines",          0x005e5488, 0x0 },
    { "S97 Particles",           0x00669e74, 0x0 },
    { "S98 Particle",            0x00669e70, 0x0 },
    { "S100 <unknown>",          0x00669e78, 0x0 },
    { "S102 <unknown>",          0x00669e7c, 0x0 },
    { "S103 <unknown>",          0x005e747c, 0x0 },
    { "S105 <unknown>",          0x005e7d70, 0x0 },
    { "S107 <unknown>",          0x005ebb30, 0x0 },
    { "S109 <unknown>",          0x00672b90, 0x0 },
    { "S111 Police",             0x0066b7a0, 0x0 },
    { "S115 <unknown>",          0x006622B8, 0x0 },
    { "S117 Gangs",              0x005EB898, 0xCA8 },
    { "S119 <unknown>",          0x00669AE4, 0x48 },
    { "S121 <unknown>",          0x005e6340, 0x0 },
    { "S123 <unknown>",          0x0066f5dc, 0x0 },
    { "S127 <unknown>",          0x005e79ec, 0x0 },
    { "S129 <unknown>",          0x005ea9cc, 0x0 },
    { "S132 cameraPosTarget",    0x005d81dc, 0x0 },
    { "S133 Menu* (ptr cell)",0x005eb160, 4 },
    { "S150 PlayerData",         0x0066b404, 0x2bc0 },
    { "S154 AudioManager",       0x005dcbc8, 0x0 },
    { "S157 DMAudio",            0x005d85a0, 0x0 },
    { "S195 Passenger",          0x005e5ee0, 0x8 },
    { "S270 MapGm",              0x005ec070, 0x554 },
    { "S279 LPDIRECTINPUTDEVICE8",0x005E8F4C, 0x0 },
    { "S280 LPDIRECTINPUTA",     0x005E8F58, 0x0 },
    { "S300 Game* gGame (ptr cell)", 0x005eb4fc, 0x4 },
    { "S500 Register",           0x0066C6B4, 0x0 },
};
static const int kGlobalCount = sizeof(kGlobals) / sizeof(kGlobals[0]);

const char* GetGlobalStructName(unsigned long addr)
{
    for (int i = 0; i < kGlobalCount; i++) {
        if (kGlobals[i].addr == addr) {
            return kGlobals[i].name;
        }
    }
    for (int i = 0; i < kGlobalCount; i++) {
        if (kGlobals[i].size && addr >= kGlobals[i].addr && addr < kGlobals[i].addr + kGlobals[i].size) {
            return kGlobals[i].name;
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------
// Text buffer helpers
// ---------------------------------------------------------------------------
void DumpAppendV(DumpBuf* b, const char* fmt, va_list ap)
{
    if (b->len >= b->cap - 1) {
        return;
    }
    int n = vsnprintf(b->data + b->len, b->cap - b->len, fmt, ap);
    if (n > 0) {
        b->len += (size_t)n;
        if (b->len >= b->cap) {
            b->len = b->cap - 1;
        }
    }
}

void DumpPrintf(DumpBuf* b, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    DumpAppendV(b, fmt, ap);
    va_end(ap);
}

// ---------------------------------------------------------------------------
// Changed-value tracking (prefix '*' marks fields changed since last refresh)
// ---------------------------------------------------------------------------
struct PrevVal {
    unsigned long long a;
    unsigned long long b;
    unsigned char seen;
};

static PrevVal s_prevMenu[kMenuFieldCount];
static PrevVal s_prevMapGm[kMapGmFieldCount];
static PrevVal s_prevPlayer[kPlayerDataFieldCount];
static PrevVal s_prevGame[kGameFieldCount];
static PrevVal s_prevPlayerObj[kPlayerFieldCount];
static PrevVal s_prevAudio[kAudioManagerFieldCount];
static PrevVal s_prevCar[kCarFieldCount];
static PrevVal s_prevPed[kPedFieldCount];
static PrevVal s_prevPedMgr[kPedManagerFieldCount];
static PrevVal s_prevWeapon[kWeaponFieldCount];
static PrevVal s_prevWeaponDb[kWeaponDatabaseFieldCount];
static PrevVal s_prevGlobals[kGlobalCount];

static void ReadFieldBytes(const void* base, size_t off, int size,
                           unsigned long long* outA, unsigned long long* outB)
{
    const unsigned char* p = (const unsigned char*)base + off;
    unsigned long long a = 0;
    unsigned long long b = 0;
    int n = size > 16 ? 16 : size;
    int i;
    __try {
        for (i = 0; i < n && i < 8; i++) {
            a |= ((unsigned long long)p[i]) << (8 * i);
        }
        for (i = 8; i < n && i < 16; i++) {
            b |= ((unsigned long long)p[i]) << (8 * (i - 8));
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        a = 0;
        b = 0;
    }
    *outA = a;
    *outB = b;
}

static int FieldChanged(PrevVal* pv, unsigned long long a, unsigned long long b)
{
    int changed = pv->seen && (pv->a != a || pv->b != b);
    pv->a = a;
    pv->b = b;
    pv->seen = 1;
    return changed;
}

// Append a timestamped snapshot to log\<launch-timestamp>\gta2_struct_dump.log
// so intermediate states between refreshes are preserved instead of the last
// refresh overwriting everything. Rotate to a new file once a file gets large.
static void DumpWriteToFile(const char* buf, size_t len)
{
    static int s_part = 1;
    static __int64 s_bytes = 0;
    SYSTEMTIME st;
    char path[MAX_PATH];
    char head[160];
    FILE* f;

    s_bytes += (__int64)len;
    if (s_bytes > (__int64)8 * 1024 * 1024) {
        s_bytes = (__int64)len;
        s_part++;
    }
    if (s_part == 1) {
        _snprintf(path, sizeof(path), "gta2_struct_dump.log");
    } else {
        _snprintf(path, sizeof(path), "gta2_struct_dump.%d.log", s_part);
    }
    f = fopen(GetLogPath(path), "ab");
    if (f == NULL) {
        return;
    }
    GetLocalTime(&st);
    _snprintf(head, sizeof(head),
        "\n==== snapshot part %d @ %02u:%02u:%02u.%03u ====\n",
        s_part, (unsigned)st.wHour, (unsigned)st.wMinute,
        (unsigned)st.wSecond, (unsigned)st.wMilliseconds);
    fwrite(head, 1, strlen(head), f);
    fwrite(buf, 1, len, f);
    fclose(f);
}

static unsigned long long ReadScalar(const unsigned char* p, int size)
{
    unsigned long long v = 0;
    int i;
    for (i = 0; i < size && i < 8; i++) {
        v |= ((unsigned long long)p[i]) << (8 * i);
    }
    return v;
}

// ASCII text? returns length used, 0 if not text
static int AsciiTextLen(const unsigned char* p, int maxBytes)
{
    int i;
    if (maxBytes <= 0 || p[0] == 0) {
        return 0;
    }
    for (i = 0; i < maxBytes; i++) {
        unsigned char c = p[i];
        if (c == 0) {
            return i;
        }
        if (c < 0x20 || c > 0x7E) {
            return 0;
        }
    }
    return 0;
}

// Wide text? returns length (in chars), 0 if not text
static int WideTextLen(const unsigned char* p, int maxBytes)
{
    int i;
    if (maxBytes < 4 || !(p[0] && p[1] == 0)) {
        return 0;
    }
    for (i = 0; i + 1 < maxBytes; i += 2) {
        unsigned char lo = p[i];
        unsigned char hi = p[i + 1];
        if (lo == 0 && hi == 0) {
            return i / 2;
        }
        if (hi != 0 || lo < 0x20 || lo > 0x7E) {
            return 0;
        }
    }
    return 0;
}

// Append printable text (ascii or wide) preview, guarded by SEH
static void AppendTextPreview(DumpBuf* b, const char* ptr)
{
    const unsigned char* p = (const unsigned char*)ptr;
    int len = 0;
    int wide = 0;
    char tmp[48];
    int i = 0;

    __try {
        len = AsciiTextLen(p, 40);
        if (len == 0) {
            wide = WideTextLen(p, 80);
            if (wide > 0) {
                for (i = 0; i < wide && i < 47; i++) {
                    unsigned char c = p[2 * i + 1];
                    tmp[i] = (c >= 0x20 && c <= 0x7E) ? (char)c : '?';
                }
                tmp[i] = 0;
                DumpPrintf(b, " wide=\"%s\"", tmp);
                return;
            }
            return;
        }
        for (i = 0; i < len && i < 47; i++) {
            tmp[i] = (char)p[i];
        }
        tmp[i] = 0;
        DumpPrintf(b, " \"%s\"", tmp);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
    }
}

// Pointer preview for 4-byte field values that look like pointers
static void AppendPtrPreview(DumpBuf* b, unsigned long v)
{
    if (v < 0x10000 || v >= 0x7FFFFFFF) {
        return;
    }
    __try {
        AppendTextPreview(b, (const char*)(ULONG_PTR)v);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
    }
}

static BOOL IsSkippedField(const char* name)
{
    return (name[0] == 'g' && name[1] == 'a' && name[2] == 'p');
}

// Fields without a meaningful name (IDA auto-names) that we try to interpret
// as byte / short / int / text / pointer below.
static int IsUnknownField(const char* name)
{
    return (strncmp(name, "field_", 6) == 0 ||
            strncmp(name, "unk_", 4) == 0 ||
            strncmp(name, "gap", 3) == 0);
}

// Level file table inside Menu (real data, see Menu runtime logs):
// 36 records x 0x100 bytes starting at Menu+0xC900, each holds a .gmp/.scr/.sty
// filename somewhere at +0xD4 (record 0 has it at +0xD6). Whole range 0xC900..
// 0xECFF is non-zero, everything after 0xED00 is zeros.
#define LEVELFILE_BASE  0xC900
#define LEVELFILE_COUNT 36
#define LEVELFILE_SIZE  0x100

// Clear listing of the LevelFile[36] table: one line per record with every
// printable ASCII run (>=3 chars) found anywhere in the 0x100 record, plus
// count of non-zero records actually loaded.
static void FormatMenuLevelFiles(DumpBuf* b, const void* menuBase)
{
    const unsigned char* p;
    int i;
    int nWithData = 0;

    DumpPrintf(b, "== LevelFile[%d] @Menu+0x%04X (records %d x 0x%X) ==\n",
               LEVELFILE_COUNT, LEVELFILE_BASE, LEVELFILE_COUNT, LEVELFILE_SIZE);
    __try {
        p = (const unsigned char*)menuBase + LEVELFILE_BASE;
        for (i = 0; i < LEVELFILE_COUNT; i++) {
            const unsigned char* rec = p + (size_t)i * LEVELFILE_SIZE;
            int nz;
            int j;
            nz = 0;
            for (j = 0; j < LEVELFILE_SIZE; j++) {
                if (rec[j] != 0) {
                    nz++;
                }
            }
            if (nz > 0) {
                nWithData++;
            }
            DumpPrintf(b, "  [%02d] @+0x%04X  nonzero=%d", i,
                       LEVELFILE_BASE + i * LEVELFILE_SIZE, nz);
            for (j = 0; j <= LEVELFILE_SIZE; j++) {
                int start;
                unsigned char c = (j < LEVELFILE_SIZE) ? rec[j] : 0;
                if (c >= 0x20 && c <= 0x7E && j < LEVELFILE_SIZE) {
                    start = j;
                    while (j < LEVELFILE_SIZE && rec[j] >= 0x20 && rec[j] <= 0x7E) {
                        j++;
                    }
                    if (j - start >= 3) {
                        int k;
                        start = j;
                        while (start > 0 && rec[start - 1] >= 0x20 && rec[start - 1] <= 0x7E) {
                            start--;
                        }
                        DumpPrintf(b, "  \"");
                        for (k = start; k < j; k++) {
                            DumpPrintf(b, "%c", rec[k]);
                        }
                        DumpPrintf(b, "\"@+0x%04X", start);
                    }
                }
            }
            DumpPrintf(b, "\n");
            for (j = 0; j < LEVELFILE_SIZE; j += 16) {
                int k;
                DumpPrintf(b, "       +%04X  ", j);
                for (k = 0; k < 16 && j + k < LEVELFILE_SIZE; k++) {
                    DumpPrintf(b, "%s%02X", k ? " " : "", rec[j + k]);
                }
                DumpPrintf(b, " ");
                for (k = 0; k < 16 && j + k < LEVELFILE_SIZE; k++) {
                    unsigned char c = rec[j + k];
                    if (c >= 0x20 && c <= 0x7E) {
                        DumpPrintf(b, "%c", c);
                    }
                    else {
                        DumpPrintf(b, ".");
                    }
                }
                DumpPrintf(b, "\n");
            }
        }
        DumpPrintf(b, "  -> %d of %d records have data\n\n", nWithData, LEVELFILE_COUNT);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "<LevelFile read failed>\n\n");
    }
}

// Append the LevelFile[36] listing to the per-struct Menu.log (in addition to
// the byte-by-byte field dump that BuildDump writes into the common window).
static void AppendMenuLevelFilesToFile(const void* menuBase)
{
    static char s_lvBuf[64 * 1024];
    DumpBuf b;
    FILE* f;

    f = fopen(GetLogPath("Menu.log"), "ab");
    if (f == NULL) {
        return;
    }
    b.data = s_lvBuf;
    b.cap = sizeof(s_lvBuf);
    b.len = 0;
    s_lvBuf[0] = 0;
    FormatMenuLevelFiles(&b, menuBase);
    if (b.len > 0) {
        fwrite(s_lvBuf, 1, b.len, f);
    }
    fclose(f);
}

// DMAudio state dump (global gDMAudio @0x005D85A0, size 0x3E84 = next global
// unk_5DC424 @0x005DC424).  Raw byte state by design: DMAudio fields are array
// buffers, we show every byte/run + full hexdump like the Menu LevelFile table.
#define DMAUDIO_BASE 0x005D85A0UL
#define DMAUDIO_SIZE 0x3E84
static void FormatDMAudioState(DumpBuf* b, const void* dmaBase)
{
    const unsigned char* p;
    int i;
    int nWithData = 0;

    DumpPrintf(b, "== gDMAudio @+0x%04X (0x%X bytes, next global @+0x%06X) ==\n",
               DMAUDIO_BASE - 0x005D0000UL, DMAUDIO_SIZE,
               DMAUDIO_BASE + DMAUDIO_SIZE);
    __try {
        p = (const unsigned char*)dmaBase;
        for (i = 0; i <= DMAUDIO_SIZE; i++) {
            int start;
            unsigned char c = (i < DMAUDIO_SIZE) ? p[i] : 0;
            if (c >= 0x20 && c <= 0x7E && i < DMAUDIO_SIZE) {
                start = i;
                while (i < DMAUDIO_SIZE && p[i] >= 0x20 && p[i] <= 0x7E) {
                    i++;
                }
                if (i - start >= 3) {
                    int k;
                    start = i;
                    while (start > 0 && p[start - 1] >= 0x20 && p[start - 1] <= 0x7E) {
                        start--;
                    }
                    DumpPrintf(b, "  \"");
                    for (k = start; k < i; k++) {
                        DumpPrintf(b, "%c", p[k]);
                    }
                    DumpPrintf(b, "\"@+0x%04X", start);
                }
            }
        }
        DumpPrintf(b, "\n");
        for (i = 0; i < DMAUDIO_SIZE; i += 16) {
            int j;
            DumpPrintf(b, "  +%04X  ", i);
            for (j = 0; j < 16 && i + j < DMAUDIO_SIZE; j++) {
                DumpPrintf(b, "%s%02X", j ? " " : "", p[i + j]);
            }
            DumpPrintf(b, "  ");
            for (j = 0; j < 16 && i + j < DMAUDIO_SIZE; j++) {
                unsigned char c = p[i + j];
                if (c >= 0x20 && c <= 0x7E) {
                    DumpPrintf(b, "%c", c);
                }
                else {
                    DumpPrintf(b, ".");
                }
            }
            DumpPrintf(b, "\n");
        }
        for (i = 0; i < DMAUDIO_SIZE; i++) {
            if (p[i] != 0) {
                nWithData++;
            }
        }
        DumpPrintf(b, "  -> %d of %d bytes nonzero\n\n", nWithData, DMAUDIO_SIZE);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "<DMAudio read failed>\n\n");
    }
}

// Append the DMAudio state dump to DMAudio.log (mirrors AppendMenuLevelFiles).
static void AppendDMAudioStateToFile(const void* dmaBase)
{
    static char s_dmaBuf[128 * 1024];
    DumpBuf b;
    FILE* f;

    f = fopen(GetLogPath("DMAudio.log"), "ab");
    if (f == NULL) {
        return;
    }
    b.data = s_dmaBuf;
    b.cap = sizeof(s_dmaBuf);
    b.len = 0;
    s_dmaBuf[0] = 0;
    FormatDMAudioState(&b, dmaBase);
    if (b.len > 0) {
        fwrite(s_dmaBuf, 1, b.len, f);
    }
    fclose(f);
}

// ---------------------------------------------------------------------------
// PedManager pool scan: list every ped slot carrying live data (any of the
// anchor fields nonzero). Pool = pmgr->Ped[0..199], 0x294 bytes each.
// ---------------------------------------------------------------------------
static void FormatPedManagerPeds(DumpBuf* b, const PedManager* pmgr)
{
    int i;
    int nLive = 0;

    DumpPrintf(b, "-- Ped pool scan (200 x 0x294):\n");
    __try {
        for (i = 0; i < 200; i++) {
            const Ped* pd = &pmgr->Ped[i];
            if (pd->PedId != 0 || pd->ID != 0 || pd->Health != 0 ||
                pd->PositionX1 != 0 || pd->X != 0 || pd->Y != 0 ||
                pd->Z != 0 || pd->Driver != NULL || pd->Player != NULL ||
                pd->CurrentCar != NULL)
            {
                DumpPrintf(b, "  [%3d] +0x%06X  PedId=%d ID=%d Health=%d State=%d"
                              " occ=%d X=%d Y=%d Z=%d PosX1=%08X Driver=%08X "
                              "Player=%08X Car=%08X\n",
                           i, (unsigned long)((const char*)pd - (const char*)pmgr),
                           pd->PedId, pd->ID, pd->Health, pd->PedState,
                           pd->Occupation, pd->X, pd->Y, pd->Z,
                           (unsigned long)pd->PositionX1,
                           (unsigned long)(ULONG_PTR)pd->Driver,
                           (unsigned long)(ULONG_PTR)pd->Player,
                           (unsigned long)(ULONG_PTR)pd->CurrentCar);
                nLive++;
            }
        }
        DumpPrintf(b, "  -> %d / 200 slots with live data (PedsInUse=%d)\n\n",
                   nLive, pmgr->PedsInUse);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "  <ped pool scan failed>\n\n");
    }
}

static void AppendPedManagerPedsToFile(const PedManager* pmgr)
{
    static char s_pedBuf[64 * 1024];
    DumpBuf b;
    FILE* f;

    f = fopen(GetLogPath("PedManager.log"), "ab");
    if (f == NULL) {
        return;
    }
    b.data = s_pedBuf;
    b.cap = sizeof(s_pedBuf);
    b.len = 0;
    s_pedBuf[0] = 0;
    FormatPedManagerPeds(&b, pmgr);
    if (b.len > 0) {
        fwrite(s_pedBuf, 1, b.len, f);
    }
    fclose(f);
}

// ---------------------------------------------------------------------------
// S200 raw dump: the Ped ctor builds Construct(this, 3, 100, S200..) so the
// S200 block is a 100-entry array of 3-byte records (300 bytes, 0x00..0x12B).
// IDA only typed S200[3] (9 bytes) and left the rest unmapped. Print all 100
// entries as word+byte so the live counter / collision layout shows up.
// ---------------------------------------------------------------------------
static void FormatPedS200(DumpBuf* b, const Ped* pd)
{
    int i;
    int nLive = 0;
    int first = -1;
    const unsigned char* p = (const unsigned char*)pd;

    DumpPrintf(b, "-- S200 block scan (100 x 3 bytes = 300 bytes, +0x00..+0x12B):\n");
    __try {
        DumpPrintf(b, "  full raw (300 bytes):\n  ");
        for (i = 0; i < 100; i++) {
            DumpPrintf(b, "%02X%02X%02X%s",
                       p[i * 3 + 0], p[i * 3 + 1], p[i * 3 + 2],
                       ((i % 10) == 9) ? "\n  " : " ");
        }
        DumpPrintf(b, "\n");
        for (i = 0; i < 100; i++) {
            unsigned int a = p[i * 3 + 0];
            unsigned int bb = p[i * 3 + 1];
            unsigned int c = p[i * 3 + 2];
            if (a | bb | c) {
                if (nLive == 0) {
                    first = i;
                }
                nLive++;
                DumpPrintf(b, "  [%3d] +0x%03X  A=0x%02X B=0x%02X C=0x%02X"
                              "  word=0x%04X\n",
                           i, i * 3, a, bb, c, (unsigned int)(a | (bb << 8)));
            }
        }
        DumpPrintf(b, "  -> %d / 100 S200 entries live%s\n\n", nLive,
                   first >= 0 ? " <<< LIVE" : "");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "  <S200 block read failed>\n\n");
    }
}

// Compact single-line summary for the live console window so it can be
// eyeballed against a memory watcher without scrolling 100 entries.
static void FormatPedS200Live(DumpBuf* b, const Ped* pd)
{
    int i;
    int nLive = 0;
    const unsigned char* p = (const unsigned char*)pd;

    __try {
        for (i = 0; i < 100 && nLive < 8; i++) {
            unsigned int a = p[i * 3 + 0];
            unsigned int bb = p[i * 3 + 1];
            unsigned int c = p[i * 3 + 2];
            if (a | bb | c) {
                nLive++;
                DumpPrintf(b, "[%2d]=%02X%02X%02X ", i, a, bb, c);
            }
        }
        if (nLive == 0) {
            DumpPrintf(b, "S200 all-zero (100x3)");
        }
        else {
            DumpPrintf(b, "| S200 live=%d/100", nLive);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "S200 <read failed>");
    }
}

static void AppendPedS200ToFile(const Ped* pd, const char* title)
{
    static char s_s200Buf[16 * 1024];
    DumpBuf b;
    FILE* f;

    f = fopen(GetLogPath("Ped.log"), "ab");
    if (f == NULL) {
        return;
    }
    b.data = s_s200Buf;
    b.cap = sizeof(s_s200Buf);
    b.len = 0;
    s_s200Buf[0] = 0;
    DumpPrintf(&b, "%s [S200 raw]\n", title);
    FormatPedS200(&b, pd);
    if (b.len > 0) {
        fwrite(s_s200Buf, 1, b.len, f);
    }
    fclose(f);
}

static void AppendPedS200ToS200Log(const Ped* pd)
{
    static char s_s200Buf[16 * 1024];
    DumpBuf b;
    FILE* f;

    f = fopen(GetLogPath("S200.log"), "ab");
    if (f == NULL) {
        return;
    }
    b.data = s_s200Buf;
    b.cap = sizeof(s_s200Buf);
    b.len = 0;
    s_s200Buf[0] = 0;
    FormatPedS200(&b, pd);
    if (b.len > 0) {
        fwrite(s_s200Buf, 1, b.len, f);
    }
    fclose(f);
}

// ---------------------------------------------------------------------------
// WeaponDatabase slot scan: list every non-empty slot of the 255-entry table.
// ---------------------------------------------------------------------------
static void FormatWeaponSlots(DumpBuf* b, const WeaponDatabase* wdb)
{
    int i;
    int nLive = 0;

    DumpPrintf(b, "-- Weapon slots scan (255 x 0x30):\n");
    __try {
        for (i = 0; i < 255; i++) {
            const Weapon* wp = &wdb->sWeapon_Arr255[i];
            if (wp->Ammo != 0 || wp->TypeWeapon != 0 || wp->field_8 != 0 ||
                wp->Ped != NULL || wp->Car != NULL || wp->NextWeapon != NULL)
            {
                DumpPrintf(b, "  [%3d] +0x%04X  Ammo=%d Reload=%d Type=%d SMG=%d"
                              " f8=%08X Next=%08X Ped=%08X Car=%08X Snd=%d\n",
                           i, i * 0x30, wp->Ammo, wp->TimeToReload, wp->TypeWeapon,
                           wp->SMG, (unsigned long)wp->field_8,
                           (unsigned long)(ULONG_PTR)wp->NextWeapon,
                           (unsigned long)(ULONG_PTR)wp->Ped,
                           (unsigned long)(ULONG_PTR)wp->Car, wp->SoundWeapon);
                nLive++;
            }
        }
        DumpPrintf(b, "  -> %d / 255 slots with live data\n\n", nLive);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "  <weapon slot scan failed>\n\n");
    }
}

static void AppendWeaponSlotsToFile(const WeaponDatabase* wdb)
{
    static char s_wpBuf[64 * 1024];
    DumpBuf b;
    FILE* f;

    f = fopen(GetLogPath("WeaponDatabase.log"), "ab");
    if (f == NULL) {
        return;
    }
    b.data = s_wpBuf;
    b.cap = sizeof(s_wpBuf);
    b.len = 0;
    s_wpBuf[0] = 0;
    FormatWeaponSlots(&b, wdb);
    if (b.len > 0) {
        fwrite(s_wpBuf, 1, b.len, f);
    }
    fclose(f);
}

// Resolve an image-range pointer (or heap pointer) to a readable target:
//   code ptr  -> fn:ContainingFunction
//   data ptr  -> gd:OwningGlobal or gd:OwningGlobal+0xOFF
//   heap ptr  -> heap 0xADDR
//   otherwise -> NULL
static const char* ImagePtrName(unsigned long v, char* out, int outSize)
{
    const char* name;
    int i;
    unsigned long base;

    if (v == 0) {
        return NULL;
    }
    if (v >= 0x01000000 && v < 0x7FFFFFFF) {
        _snprintf(out, outSize, "heap 0x%08X", v);
        return out;
    }
    if (v < 0x00400000 || v >= 0x00700000) {
        return NULL;
    }
    if (v < 0x0056E000) {
        name = GetFunctionNameAt(v);
        if (name == NULL) {
            return NULL;
        }
        _snprintf(out, outSize, "fn:%s", name);
        return out;
    }
    i = DataGlobalNumAt(v);
    if (i < 0) {
        return NULL;
    }
    base = kDataGlobals[i].addr;
    if (base == v) {
        _snprintf(out, outSize, "gd:%s", kDataGlobals[i].name);
    }
    else {
        _snprintf(out, outSize, "gd:%s+0x%X", kDataGlobals[i].name, v - base);
    }
    return out;
}

// Extra interpretations for unknown fields: read the same bytes as the OTHER
// widths (byte/short/int), as a pointer (with resolved target) and as text.
static void AppendUnknownTry(DumpBuf* b, const unsigned char* p, int size)
{
    unsigned long d;
    char namebuf[96];
    const char* n;

    d = (unsigned long)ReadScalar(p, 4);
    DumpPrintf(b, "  try:");
    if (size == 1) {
        DumpPrintf(b, " w=0x%04X i=0x%08X(%d)", (unsigned int)(d & 0xFFFF), d, (int)d);
    }
    else if (size == 2) {
        DumpPrintf(b, " b=0x%02X i=0x%08X(%d)", (unsigned int)(d & 0xFF), d, (int)d);
    }
    else if (size == 4) {
        DumpPrintf(b, " b=0x%02X w=0x%04X", (unsigned int)(d & 0xFF), (unsigned int)(d & 0xFFFF));
    }
    n = ImagePtrName(d, namebuf, sizeof(namebuf));
    if (n != NULL) {
        DumpPrintf(b, " ptr->%s", n);
    }
    AppendTextPreview(b, (const char*)p);
}

static void FormatFieldValue(DumpBuf* b, const void* base, const InspField* f)
{
    const unsigned char* p = (const unsigned char*)base + f->offset;
    unsigned long long v;
    int i;

    __try {
        if (f->size == 1) {
            unsigned char c = *p;
            DumpPrintf(b, "= %d (0x%02X)", c, c);
            if (c >= 0x20 && c <= 0x7E) {
                DumpPrintf(b, " '%c'", (char)c);
            }
        }
        else if (f->size <= 4) {
            v = ReadScalar(p, f->size);
            if (f->size == 4) {
                DumpPrintf(b, "= %d (0x%08X)", (int)v, (unsigned int)v);
                AppendPtrPreview(b, (unsigned int)v);
            }
            else if (f->size == 2) {
                DumpPrintf(b, "= %d (0x%04X)", (int)(short)v, (unsigned int)v);
                if (v >= 0x20 && v <= 0x7E) {
                    DumpPrintf(b, " '%c'", (char)v);
                }
            }
            else {
                DumpPrintf(b, "= %d (0x%02X)", (char)v, (int)v);
            }
        }
        else {
            int aLen = AsciiTextLen(p, f->size > 200 ? 200 : f->size);
            if (aLen > 0) {
                DumpPrintf(b, "= [%d bytes] \"", f->size);
                for (i = 0; i < aLen && i < 60; i++) {
                    DumpPrintf(b, "%c", p[i]);
                }
                if (aLen > 60) {
                    DumpPrintf(b, "...");
                }
                DumpPrintf(b, "\"");
            }
            else {
                DumpPrintf(b, "= [%d bytes]", f->size);
                for (i = 0; i < 12 && i < f->size; i++) {
                    DumpPrintf(b, " %02X", p[i]);
                }
                if (f->size > 12) {
                    DumpPrintf(b, " ...");
                }
            }
        }
        if (IsUnknownField(f->name) && f->size <= 4) {
            AppendUnknownTry(b, p, f->size);
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "= <read error>");
    }
}

static void DumpStruct(DumpBuf* b, const char* title, const void* base,
                       const InspField* fields, int count, PrevVal* prev,
                       int showGap)
{
    int i;
    int skipped = 0;
    DumpPrintf(b, "== %s ==\n", title);
    for (i = 0; i < count; i++) {
        const InspField* f = &fields[i];
        unsigned long long a;
        unsigned long long bb;
        int changed;
        if (!showGap && IsSkippedField(f->name)) {
            continue;
        }
        ReadFieldBytes(base, (size_t)f->offset, f->size, &a, &bb);
        changed = FieldChanged(&prev[i], a, bb);
        if (s_skipZero && a == 0 && bb == 0) {
            skipped++;
            continue;
        }
        DumpPrintf(b, "  %c +0x%04X  %-28s ", changed ? '*' : ' ', f->offset, f->name);
        FormatFieldValue(b, base, f);
        DumpPrintf(b, "\n");
    }
    if (skipped > 0) {
        DumpPrintf(b, "  (skipped %d zero fields)\n", skipped);
    }
    DumpPrintf(b, "\n");
}

static void DumpGlobals(DumpBuf* b)
{
    int i;
    int skipped = 0;
    DumpPrintf(b, "== All globals from done.md (%d) ==\n", kGlobalCount);
    for (i = 0; i < kGlobalCount; i++) {
        const InspGlobal* g = &kGlobals[i];
        const unsigned char* p = (const unsigned char*)(ULONG_PTR)g->addr;
        int j;
        int size;
        int di;
        unsigned long base;
        unsigned long long a;
        unsigned long long bb;
        int changed;
        __try {
            size = (int)g->size;
            di = DataGlobalNumAt(g->addr);
            base = (di >= 0) ? kDataGlobals[di].addr : g->addr;
            if (di >= 0 && base == g->addr && size == 0) {
                size = (int)DataGlobalSizeAt(di);
            }
            ReadFieldBytes((const void*)(ULONG_PTR)g->addr, 0,
                           size >= 16 ? 16 : (size > 0 ? size : 8), &a, &bb);
            changed = FieldChanged(&s_prevGlobals[i], a, bb);
            if (s_skipZero && a == 0 && bb == 0) {
                skipped++;
                continue;
            }
            DumpPrintf(b, "%3d. %c %-33s @0x%08X",
                       i + 1, changed ? '*' : ' ', g->name, g->addr);
            if (g->size > 0) {
                DumpPrintf(b, "  size=0x%X", size);
            }
            else if (di >= 0 && base == g->addr) {
                DumpPrintf(b, "  size=0x%X (gap)", size);
            }
            else {
                DumpPrintf(b, "  size=?");
            }
            if (di >= 0) {
                if (base == g->addr) {
                    DumpPrintf(b, "  ida:%s", kDataGlobals[di].name);
                }
                else {
                    DumpPrintf(b, "  ida:%s+0x%X", kDataGlobals[di].name, g->addr - base);
                }
            }
            DumpPrintf(b, "  [");
            for (j = 0; j < 8; j++) {
                DumpPrintf(b, "%s%02X", j ? " " : "", p[j]);
            }
            DumpPrintf(b, "]");
            AppendTextPreview(b, (const char*)p);
            DumpPrintf(b, "\n");
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            DumpPrintf(b, "%3d. %-34s @0x%08X  <read error>\n", i + 1, g->name, g->addr);
        }
    }
    if (skipped > 0) {
        DumpPrintf(b, "... (%d zero globals skipped)\n", skipped);
    }
    DumpPrintf(b, "\n");
}

static void DumpGangNames(DumpBuf* b)
{
    static const char* const kNames[] = { "Yakuza", "Zaibatsu", "Loonies", "G3", "G4",
                                          "G5", "G6", "G7", "G8", "G9", "G10" };
    Gang* gangs;
    int i;

    gangs = GetGangsArray();
    if (gangs == NULL) {
        DumpPrintf(b, "== Gangs: *(Gang**)0x005EB898 is NULL yet ==\n\n");
        return;
    }
    DumpPrintf(b, "== Gangs array via gGangs @0x005EB898 (%d x 0x%X) @heap 0x%08X ==\n",
               10, (unsigned)sizeof(Gang), (unsigned)(ULONG_PTR)gangs);
    for (i = 0; i < 10; i++) {
        const char* ng = gangs[i].NameGang;
        char tmp[12];
        int j;
        __try {
            for (j = 0; j < 10; j++) {
                unsigned char c = (unsigned char)ng[j];
                if (c == 0 || c < 0x20 || c > 0x7E) {
                    break;
                }
                tmp[j] = (char)c;
            }
            tmp[j] = 0;
            DumpPrintf(b, "  [%2d] %-8s NameGang=\"%s\"  CurrentGang=%d\n",
                       i, kNames[i], tmp, (int)gangs[i].CurrentGang);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            DumpPrintf(b, "  [%2d] %-8s <read error>\n", i, kNames[i]);
        }
    }
    DumpPrintf(b, "\n");
}

// Print printable ASCII runs (>=3 chars) found anywhere inside the buffer,
// each with its offset. Missing from the previous dump: text is usually at
// the END of large zero-padded fields, which AsciiTextLen never sees.
static void AppendStringsAnywhere(DumpBuf* b, const unsigned char* p, int size)
{
    int i;
    int start = -1;
    for (i = 0; i <= size; i++) {
        unsigned char c = (i < size) ? p[i] : 0;
        int printable = (c >= 0x20 && c <= 0x7E);
        if (printable) {
            if (start < 0) {
                start = i;
            }
        } else {
            if (start >= 0) {
                int len = i - start;
                if (len >= 3) {
                    int j;
                    int n = len < 120 ? len : 120;
                    DumpPrintf(b, "        @+0x%04X str: \"", start);
                    for (j = 0; j < n; j++) {
                        DumpPrintf(b, "%c", p[start + j]);
                    }
                    if (len > 120) {
                        DumpPrintf(b, "...");
                    }
                    DumpPrintf(b, "\"\n");
                }
            }
            start = -1;
        }
    }
}

// Dump every field of a struct to its own per-struct log file. Unknown fields
// (field_/unk_/gap) are written byte-by-byte so nothing is lost, named fields
// use the compact formatter. Zero values are kept. Appends one snapshot.
static void DumpStructToFile(const char* fileName, const char* title,
                             const void* base, const InspField* fields, int count,
                             int showGap)
{
    static char s_buf[512 * 1024];
    static int s_bufCap = (int)sizeof(s_buf);
    DumpBuf b;
    SYSTEMTIME st;
    char head[160];
    char path[MAX_PATH];
    FILE* f;
    int i;

    f = fopen(GetLogPath(fileName), "ab");
    if (f == NULL) {
        return;
    }
    GetLocalTime(&st);
    _snprintf(head, sizeof(head),
        "\n== %s @ %02u:%02u:%02u.%03u ==\n",
        title, (unsigned)st.wHour, (unsigned)st.wMinute,
        (unsigned)st.wSecond, (unsigned)st.wMilliseconds);
    fwrite(head, 1, strlen(head), f);

    b.data = s_buf;
    b.cap = (size_t)s_bufCap;
    b.len = 0;
    s_buf[0] = 0;

    for (i = 0; i < count; i++) {
        const InspField* fl = &fields[i];
        const unsigned char* p;
        int j;
        if (!showGap && IsSkippedField(fl->name)) {
            continue;
        }
        p = (const unsigned char*)base + fl->offset;
        __try {
            if (IsUnknownField(fl->name)) {
                DumpPrintf(&b, "  +0x%04X  %-28s [%d bytes]\n",
                           fl->offset, fl->name, fl->size);
                for (j = 0; j < fl->size; j++) {
                    if ((j & 15) == 0) {
                        DumpPrintf(&b, "      %04X:", j);
                    }
                    DumpPrintf(&b, " %02X", p[j]);
                    if ((j & 15) == 15) {
                        DumpPrintf(&b, "\n");
                    }
                }
                if (fl->size & 15) {
                    DumpPrintf(&b, "\n");
                }
                AppendStringsAnywhere(&b, p, fl->size);
            }
            else {
                DumpPrintf(&b, "  +0x%04X  %-28s ", fl->offset, fl->name);
                FormatFieldValue(&b, base, fl);
                DumpPrintf(&b, "\n");
            }
            if (b.len > (size_t)b.cap - 4096) {
                fwrite(s_buf, 1, b.len, f);
                b.len = 0;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            DumpPrintf(&b, "  +0x%04X  %-28s <read error>\n", fl->offset, fl->name);
        }
    }
    if (b.len > 0) {
        fwrite(s_buf, 1, b.len, f);
    }
    fclose(f);
}

static void BuildDumpMainPedS200(DumpBuf* b, Ped* mped)
{
    char title[128];
    _snprintf(title, sizeof(title),
              "Player[0] MainPed (game->Player->Ped, heap 0x%08X, 0x294)",
              (unsigned long)(ULONG_PTR)mped);
    FormatPedS200(b, mped);
    AppendPedS200ToS200Log(mped);
    if (s_s200Watch) {
        S200WatchSetTarget(mped);
        S200WatchDump(b);
        S200WatchFlushToFile();
    }
    (void)title;
}

static void BuildDump(void)
{
    static char s_buf[300 * 1024];
    DumpBuf b;
    b.data = s_buf;
    b.cap = sizeof(s_buf);
    b.len = 0;
    s_buf[0] = 0;

    // --- S200-only mode: just the S200 block (no other structures) -------
    if (s_s200Only) {
        Game* pg = GetGamePtr();
        if (pg != NULL && pg->pPlayer[0] != NULL) {
            Ped* mped = pg->pPlayer[0]->MainPed;
            if (mped != NULL) {
                BuildDumpMainPedS200(&b, mped);
            } else {
                DumpPrintf(&b, "MainPed is NULL yet\n");
            }
        } else {
            DumpPrintf(&b, "Game/Player not ready\n");
        }
        if (s_hEdit) {
            SetWindowTextA(s_hEdit, s_buf);
        }
        return;
    }

    DumpPrintf(&b, "GTA2 struct inspector - live, refresh 1s  (addresses from done.md)\n\n");

    __try {
        Menu* realMenu = GetRealMenu();
        if (realMenu != NULL) {
            DumpStruct(&b, "Menu (heap, via *(Menu**)0x005EB160 = gMenu)", realMenu,
                       kMenuFields, kMenuFieldCount, s_prevMenu, 1);
            DumpStructToFile("Menu.log", "Menu (heap 0x005EB160)", realMenu,
                             kMenuFields, kMenuFieldCount, 1);
            FormatMenuLevelFiles(&b, realMenu);
            AppendMenuLevelFilesToFile(realMenu);
        } else {
            DumpPrintf(&b, "== Menu: gMenu global is NULL yet (not initialized) ==\n\n");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Menu read failed>\n");
    }

    __try {
        const void* dmaBase = GetRealDMAudio();
        if (dmaBase != NULL) {
            FormatDMAudioState(&b, dmaBase);
            AppendDMAudioStateToFile(dmaBase);
        } else {
            DumpPrintf(&b, "== DMAudio: gDMAudio global is NULL (not initialized) ==\n\n");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<DMAudio read failed>\n");
    }

    __try {
        DumpStruct(&b, "MapGm @0x005EC070 (0x578)", s_pMapGm,
                   kMapGmFields, kMapGmFieldCount, s_prevMapGm, 1);
        DumpStructToFile("MapGm.log", "MapGm @0x005EC070 (0x578)", s_pMapGm,
                         kMapGmFields, kMapGmFieldCount, 1);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<MapGm read failed>\n");
    }

    __try {
        Game* pg = GetGamePtr(); // deref the gGame pointer cell @0x005EB4FC
        if (pg != NULL) {
            char title[96];
            _snprintf(title, sizeof(title), "Game -> heap 0x%08X (0x40, gGame@0x005EB4FC)",
                      (unsigned long)(ULONG_PTR)pg);
            DumpStruct(&b, title, pg, kGameFields, kGameFieldCount, s_prevGame, 1);
            DumpStructToFile("Game.log", title, pg,
                             kGameFields, kGameFieldCount, 1);
        } else {
            DumpPrintf(&b, "== Game: gGame@0x005EB4FC is NULL (not created yet) ==\n\n");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Game read failed>\n");
    }

    __try {
        Game* pg2 = GetGamePtr(); // deref the gGame pointer cell @0x005EB4FC
        if (pg2 != NULL) {
            int pi;
            for (pi = 0; pi < 6; pi++) {
                Player* pp = pg2->pPlayer[pi];
                char title[96];
                if (pp == NULL) {
                    continue;
                }
                _snprintf(title, sizeof(title), "Player[%d] (Game slot, heap 0x%08X, 0x85C)",
                          pi, (unsigned long)(ULONG_PTR)pp);
                DumpStruct(&b, title, pp, kPlayerFields, kPlayerFieldCount, s_prevPlayerObj, 1);
                DumpStructToFile("Player.log", title, pp,
                                 kPlayerFields, kPlayerFieldCount, 1);
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Player read failed>\n");
    }

    __try {
        Game* pgCar = GetGamePtr();
        if (pgCar != NULL) {
            int pi;
            for (pi = 0; pi < 6; pi++) {
                Player* pp = pgCar->pPlayer[pi];
                if (pp == NULL) {
                    continue;
                }
                // Ped: dump MainPed; Car: dump sCar1/sCar2 (live only when
                // player is in a vehicle).
                __try {
Ped* mped = pp->MainPed;
                        if (mped != NULL) {
                            char title[96];
                            _snprintf(title, sizeof(title),
                                      "Player[%d] MainPed (game->Player->Ped, heap 0x%08X, 0x294)",
                                      pi, (unsigned long)(ULONG_PTR)mped);
                            DumpStruct(&b, title, mped, kPedFields, kPedFieldCount,
                                       s_prevPed, 1);
                            FormatPedS200Live(&b, mped);
                            DumpPrintf(&b, "\n");
                            DumpStructToFile("Ped.log", title, mped,
                                             kPedFields, kPedFieldCount, 1);
                            AppendPedS200ToFile(mped, title);
                            if (s_s200Watch) {
                                S200WatchSetTarget(mped);
                                S200WatchDump(&b);
                                S200WatchFlushToFile();
                            }
                    }
                    Car* c1 = pp->sCar1;
                    if (c1 != NULL) {
                        char title[96];
                        _snprintf(title, sizeof(title),
                                  "Player[%d] sCar1 (heap 0x%08X, 0x132)",
                                  pi, (unsigned long)(ULONG_PTR)c1);
                        DumpStruct(&b, title, c1, kCarFields, kCarFieldCount,
                                   s_prevCar, 1);
                        DumpStructToFile("Car.log", title, c1,
                                         kCarFields, kCarFieldCount, 1);
                    }
                    Car* c2 = pp->sCar2;
                    if (c2 != NULL && c2 != c1) {
                        char title[96];
                        _snprintf(title, sizeof(title),
                                  "Player[%d] sCar2 (heap 0x%08X, 0x132)",
                                  pi, (unsigned long)(ULONG_PTR)c2);
                        DumpStruct(&b, title, c2, kCarFields, kCarFieldCount,
                                   s_prevCar, 1);
                        DumpStructToFile("Car.log", title, c2,
                                         kCarFields, kCarFieldCount, 1);
                    }
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                    DumpPrintf(&b, "<Player[%d] Ped/Car read failed>\n", pi);
                }
            }
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Player Ped/Car read failed>\n");
    }

    __try {
        DumpStruct(&b, "PlayerData @0x0066B404 (0x2bc0)", s_pPlayerData,
                   kPlayerDataFields, kPlayerDataFieldCount, s_prevPlayer, 1);
        DumpStructToFile("PlayerData.log", "PlayerData @0x0066B404 (0x2bc0)",
                         s_pPlayerData, kPlayerDataFields, kPlayerDataFieldCount, 1);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<PlayerData read failed>\n");
    }

    __try {
        DumpGangNames(&b);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Gangs read failed>\n");
    }

    __try {
        DumpStruct(&b, "AudioManager @0x005DCBC8 (0x5562)", (AudioManager*)0x005DCBC8,
                   kAudioManagerFields, kAudioManagerFieldCount, s_prevAudio, 1);
        DumpStructToFile("AudioManager.log", "AudioManager @0x005DCBC8 (0x5562)",
                         (AudioManager*)0x005DCBC8,
                         kAudioManagerFields, kAudioManagerFieldCount, 1);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<AudioManager read failed>\n");
    }

    __try {
        PedManager* pmgr = GetRealPedManager();
        if (pmgr != NULL) {
            DumpStruct(&b, "PedManager (heap, via gPedManager@0x005E5BBC, 0x203AC)",
                       pmgr, kPedManagerFields, kPedManagerFieldCount, s_prevPedMgr, 1);
            DumpStructToFile("PedManager.log", "PedManager (gPedManager@0x005E5BBC)",
                             pmgr, kPedManagerFields, kPedManagerFieldCount, 1);
            FormatPedManagerPeds(&b, pmgr);
            AppendPedManagerPedsToFile(pmgr);
        } else {
            DumpPrintf(&b, "== PedManager: gPedManager@0x005E5BBC is NULL ==\n\n");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<PedManager read failed>\n");
    }

    __try {
        WeaponDatabase* wdb = GetRealWeaponDatabase();
        if (wdb != NULL) {
            DumpStruct(&b, "WeaponDatabase (heap, via gWeaponDatabase@0x00673944, 0x2FDC)",
                       wdb, kWeaponDatabaseFields, kWeaponDatabaseFieldCount,
                       s_prevWeaponDb, 1);
            DumpStructToFile("WeaponDatabase.log", "WeaponDatabase (gWeaponDatabase@0x00673944)",
                             wdb, kWeaponDatabaseFields, kWeaponDatabaseFieldCount, 1);
            FormatWeaponSlots(&b, wdb);
            AppendWeaponSlotsToFile(wdb);
        } else {
            DumpPrintf(&b, "== WeaponDatabase: gWeaponDatabase@0x00673944 is NULL ==\n\n");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<WeaponDatabase read failed>\n");
    }

    __try {
        static BOOL s_globalsOnce = FALSE;
        if (!s_globalsOnce) {
            DumpGlobals(&b);
            s_globalsOnce = TRUE;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Globals read failed>\n");
    }

    // keep the previous scroll position across refreshes so the text stays readable
    if (s_hEdit) {
        SCROLLINFO si;
        int oldPos = 0;
        int oldMax = 0;
        BOOL wasScrolled = FALSE;
        si.cbSize = sizeof(si);
        si.fMask = SIF_RANGE | SIF_POS | SIF_PAGE;
        if (GetScrollInfo(s_hEdit, SB_VERT, &si) && si.nMax > si.nMin) {
            oldPos = si.nPos;
            oldMax = si.nMax;
            wasScrolled = (oldPos > 0);
        }
        SetWindowTextA(s_hEdit, s_buf);
        // save the same dump to a file next to the game executable
        if (s_saveFile) {
            DumpWriteToFile(s_buf, b.len);
        }
        if (wasScrolled) {
            si.cbSize = sizeof(si);
            si.fMask = SIF_RANGE | SIF_POS;
            if (GetScrollInfo(s_hEdit, SB_VERT, &si)) {
                int newPos = oldPos;
                if (newPos > si.nMax) {
                    newPos = si.nMax;
                }
                si.fMask = SIF_POS;
                si.nPos = newPos;
                SetScrollInfo(s_hEdit, SB_VERT, &si, TRUE);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Window
// ---------------------------------------------------------------------------
#define IDC_INSP_REFRESH 101
#define IDC_INSP_EDIT    102
#define IDC_INSP_PAUSE   103
#define IDC_INSP_SKIPZERO 104
#define IDC_INSP_SAVEFILE 105
#define IDC_INSP_S200ONLY 106
#define IDC_INSP_S200WATCH 107
#define WM_INSP_REFRESH  (WM_APP + 1)

static LRESULT CALLBACK InspectorWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_CREATE: {
        HINSTANCE hInst = GetModuleHandleA(NULL);
        HFONT font;
        s_hEdit = CreateWindowExA(WS_EX_CLIENTEDGE, "EDIT", NULL,
                                  WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_READONLY |
                                  ES_AUTOVSCROLL | WS_VSCROLL | WS_HSCROLL,
                                  0, 0, 0, 0, hwnd, (HMENU)IDC_INSP_EDIT, hInst, NULL);
        font = CreateFontA(15, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET,
                           OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                           FIXED_PITCH, "Courier New");
        SendMessage(s_hEdit, WM_SETFONT, (WPARAM)font, TRUE);
        CreateWindowExA(0, "BUTTON", "Refresh",
                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                        10, 10, 74, 28, hwnd, (HMENU)IDC_INSP_REFRESH, hInst, NULL);
        CreateWindowExA(0, "BUTTON", "Pause 1s refresh",
                        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
                        90, 14, 140, 20, hwnd, (HMENU)IDC_INSP_PAUSE, hInst, NULL);
        CreateWindowExA(0, "BUTTON", "Skip zero",
                        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
                        236, 14, 76, 20, hwnd, (HMENU)IDC_INSP_SKIPZERO, hInst, NULL);
        CreateWindowExA(0, "BUTTON", "Save to file",
                        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
                        318, 14, 90, 20, hwnd, (HMENU)IDC_INSP_SAVEFILE, hInst, NULL);
        CheckDlgButton(hwnd, IDC_INSP_SKIPZERO, BST_UNCHECKED);
        CheckDlgButton(hwnd, IDC_INSP_SAVEFILE, BST_CHECKED);
        CreateWindowExA(0, "BUTTON", "S200 only",
                        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
                        414, 14, 76, 20, hwnd, (HMENU)IDC_INSP_S200ONLY, hInst, NULL);
        CreateWindowExA(0, "BUTTON", "S200 write-watch",
                        WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,
                        496, 14, 108, 20, hwnd, (HMENU)IDC_INSP_S200WATCH, hInst, NULL);
        SetTimer(hwnd, 1, 1000, NULL);
        return 0;
    }
    case WM_SIZE: {
        RECT rc;
        GetClientRect(hwnd, &rc);
        if (s_hEdit) {
            MoveWindow(s_hEdit, 0, 46, rc.right, rc.bottom - 46, TRUE);
        }
        return 0;
    }
    case WM_INSP_REFRESH:
        InterlockedExchange(&s_refreshPending, 0);
        if (!s_paused) {
            BuildDump();
        }
        return 0;
    case WM_TIMER:
        if (wParam == 1 && !s_paused) {
            BuildDump();
            return 0;
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_INSP_PAUSE && HIWORD(wParam) == BN_CLICKED) {
            s_paused = IsDlgButtonChecked(hwnd, IDC_INSP_PAUSE);
            return 0;
        }
        if (LOWORD(wParam) == IDC_INSP_REFRESH && HIWORD(wParam) == BN_CLICKED) {
            BuildDump();
            return 0;
        }
        if (LOWORD(wParam) == IDC_INSP_SKIPZERO && HIWORD(wParam) == BN_CLICKED) {
            s_skipZero = IsDlgButtonChecked(hwnd, IDC_INSP_SKIPZERO);
            BuildDump();
            return 0;
        }
        if (LOWORD(wParam) == IDC_INSP_SAVEFILE && HIWORD(wParam) == BN_CLICKED) {
            s_saveFile = IsDlgButtonChecked(hwnd, IDC_INSP_SAVEFILE);
            BuildDump();
            return 0;
        }
        if (LOWORD(wParam) == IDC_INSP_S200ONLY && HIWORD(wParam) == BN_CLICKED) {
            s_s200Only = IsDlgButtonChecked(hwnd, IDC_INSP_S200ONLY);
            BuildDump();
            return 0;
        }
        if (LOWORD(wParam) == IDC_INSP_S200WATCH && HIWORD(wParam) == BN_CLICKED) {
            s_s200Watch = IsDlgButtonChecked(hwnd, IDC_INSP_S200WATCH);
            BuildDump();
            return 0;
        }
        break;
    case WM_CLOSE:
        KillTimer(hwnd, 1);
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        s_hWnd = NULL;
        s_hEdit = NULL;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

static DWORD WINAPI InspectorThreadProc(LPVOID lpParam)
{
    (void)lpParam;
    WNDCLASSA wc;
    HWND hwnd;
    MSG msg;

    if (!s_classRegistered) {
        memset(&wc, 0, sizeof(wc));
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = InspectorWndProc;
        wc.hInstance = GetModuleHandleA(NULL);
        wc.hCursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
        wc.lpszClassName = "GTA2ResurrectionInspector";
        if (RegisterClassA(&wc)) {
            s_classRegistered = TRUE;
        }
    }

    hwnd = CreateWindowExA(0, "GTA2ResurrectionInspector", "GTA2 Struct Inspector",
                           WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                           CW_USEDEFAULT, CW_USEDEFAULT, 1000, 780,
                           NULL, NULL, GetModuleHandleA(NULL), NULL);
    if (!hwnd) {
        return 0;
    }
    s_hWnd = hwnd;
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    BuildDump();

    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
static HANDLE s_hThread = NULL;

void StartInspector(void)
{
    if (s_hThread != NULL) {
        return;
    }
    S200WatchInit();
    s_hThread = CreateThread(NULL, 0, InspectorThreadProc, NULL, 0, NULL);
}

void StopInspector(void)
{
    if (s_hWnd) {
        PostMessage(s_hWnd, WM_CLOSE, 0, 0);
    }
}

void InspectorRequestRefresh(void)
{
    InterlockedExchange(&s_refreshPending, 1);
    if (s_hWnd) {
        PostMessage(s_hWnd, WM_INSP_REFRESH, 0, 0);
    }
}