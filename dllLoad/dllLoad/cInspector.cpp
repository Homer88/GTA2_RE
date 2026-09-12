// cInspector.cpp - struct field inspector window + globals dump (done.md)
// Shows live fields of known structures (Menu, MapGm, PlayerData) at their
// fixed addresses in the original GTA2.EXE. Unknown/gap fields are shown
// as numbers or text. All globals from done.md are listed too.
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include "cInspector.h"
#include "cMenu.h"
#include "cMapGm.h"
#include "cPlayerData.h"
#include "cText.h"

// Fixed addresses of global instances (addresses from done.md)
// NOTE: 0x005EB160 is a global Menu* pointer cell (4 bytes), not the Menu struct.
// The real Menu is heap-allocated (operator_new(0x1EB40) in FUN_00457830).
// We read the pointer at dump time to follow the heap address.
static Menu*      GetRealMenu(void) { return (Menu*)(*(void**)0x005EB160); }
static MapGm*     s_pMapGm     = (MapGm*)0x005EC070;
static PlayerData* s_pPlayerData = (PlayerData*)0x0066B404;
static Text*      s_pText      = (Text*)0x00671550;

static HWND s_hWnd = NULL;
static HWND s_hEdit = NULL;
static BOOL s_classRegistered = FALSE;
static volatile long s_refreshPending = 0;
static BOOL s_paused = FALSE;
static BOOL s_skipZero = TRUE;
static BOOL s_saveFile = TRUE;

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
    INSP_FIELD(Menu, gapC9D4),
    INSP_FIELD(Menu, field_C9D6),
    INSP_FIELD(Menu, field_CA08),
    INSP_FIELD(Menu, field_CA12),
    INSP_FIELD(Menu, field_CA13),
    INSP_FIELD(Menu, gapCA13),
    INSP_FIELD(Menu, field_CA15),
    INSP_FIELD(Menu, field_CADD),
    INSP_FIELD(Menu, field_CB0F),
    INSP_FIELD(Menu, field_CB41),
    INSP_FIELD(Menu, field_CB72),
    INSP_FIELD(Menu, field_CBA4),
    INSP_FIELD(Menu, field_CBD6),
    INSP_FIELD(Menu, field_CC08),
    INSP_FIELD(Menu, field_CC3A),
    INSP_FIELD(Menu, field_CC6C),
    INSP_FIELD(Menu, field_CC9E),
    INSP_FIELD(Menu, field_CCD0),
    INSP_FIELD(Menu, field_EDB6),
    INSP_FIELD(Menu, field_CD36),
    INSP_FIELD(Menu, field_D11E),
    INSP_FIELD(Menu, field_D506),
    INSP_FIELD(Menu, field_D6FA),
    INSP_FIELD(Menu, field_D8EE),
    INSP_FIELD(Menu, field_DAE2),
    INSP_FIELD(Menu, field_DCD6),
    INSP_FIELD(Menu, field_DECA),
    INSP_FIELD(Menu, field_E2B2),
    INSP_FIELD(Menu, field_E69A),
    INSP_FIELD(Menu, field_EA82),
    INSP_FIELD(Menu, field_EC76),
    INSP_FIELD(Menu, field_ED3E),
    INSP_FIELD(Menu, field_EDA2),
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
    INSP_FIELD(MapGm, field_42C),
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
    INSP_FIELD(MapGm, field_4B4),
    INSP_FIELD(MapGm, field_4B5),
    INSP_FIELD(MapGm, field_4B6),
    INSP_FIELD(MapGm, field_4B7),
    INSP_FIELD(MapGm, field_4B8),
    INSP_FIELD(MapGm, gap4B9),
    INSP_FIELD(MapGm, field_570),
    INSP_FIELD(MapGm, field_571),
    INSP_FIELD(MapGm, field_572),
    INSP_FIELD(MapGm, field_573),
    INSP_FIELD(MapGm, SpecialTokens),
    INSP_FIELD(MapGm, field_578),
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
    { "S300 Game",               0x005eb4fc, 0x40 },
    { "S500 Register",           0x0066C6B4, 0x0 },
};
static const int kGlobalCount = sizeof(kGlobals) / sizeof(kGlobals[0]);

// ---------------------------------------------------------------------------
// Text buffer helpers
// ---------------------------------------------------------------------------
struct DumpBuf {
    char* data;
    size_t cap;
    size_t len;
};

static void DumpAppendV(DumpBuf* b, const char* fmt, va_list ap)
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

static void DumpPrintf(DumpBuf* b, const char* fmt, ...)
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

// Write the dump text to "gta2_struct_dump.log" next to the game executable
static void DumpWriteToFile(const char* buf, size_t len)
{
    char exe[MAX_PATH];
    char path[MAX_PATH + 32];
    DWORD n;
    char* slash;
    FILE* f;
    n = GetModuleFileNameA(NULL, exe, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) {
        return;
    }
    slash = strrchr(exe, '\\');
    if (slash != NULL) {
        slash[1] = 0;
    }
    else {
        exe[0] = 0;
    }
    sprintf(path, "%sgta2_struct_dump.log", exe);
    f = fopen(path, "wb");
    if (f != NULL) {
        fwrite(buf, 1, len, f);
        fclose(f);
    }
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
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(b, "= <read error>");
    }
}

static void DumpStruct(DumpBuf* b, const char* title, const void* base,
                       const InspField* fields, int count, PrevVal* prev)
{
    int i;
    int skipped = 0;
    DumpPrintf(b, "== %s ==\n", title);
    for (i = 0; i < count; i++) {
        const InspField* f = &fields[i];
        unsigned long long a;
        unsigned long long bb;
        int changed;
        if (IsSkippedField(f->name)) {
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
        unsigned long long a;
        unsigned long long bb;
        int changed;
        __try {
            size = (int)g->size;
            ReadFieldBytes((const void*)(ULONG_PTR)g->addr, 0,
                           size >= 16 ? 16 : (size > 0 ? size : 8), &a, &bb);
            changed = FieldChanged(&s_prevGlobals[i], a, bb);
            if (s_skipZero && a == 0 && bb == 0) {
                skipped++;
                continue;
            }
            DumpPrintf(b, "%3d. %c %-33s @0x%08X",
                       i + 1, changed ? '*' : ' ', g->name, g->addr);
            if (size == 0) {
                DumpPrintf(b, "  size=?");
            }
            else {
                DumpPrintf(b, "  size=0x%X", size);
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

static void BuildDump(void)
{
    static char s_buf[300 * 1024];
    DumpBuf b;
    b.data = s_buf;
    b.cap = sizeof(s_buf);
    b.len = 0;
    s_buf[0] = 0;

    DumpPrintf(&b, "GTA2 struct inspector - live, refresh 1s  (addresses from done.md)\n\n");

    __try {
        Menu* realMenu = GetRealMenu();
        if (realMenu != NULL) {
            DumpStruct(&b, "Menu (heap, via *(Menu**)0x005EB160 = gMenu)", realMenu,
                       kMenuFields, kMenuFieldCount, s_prevMenu);
        } else {
            DumpPrintf(&b, "== Menu: gMenu global is NULL yet (not initialized) ==\n\n");
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<Menu read failed>\n");
    }

    __try {
        DumpStruct(&b, "MapGm @0x005EC070 (0x554)", s_pMapGm,
                   kMapGmFields, kMapGmFieldCount, s_prevMapGm);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<MapGm read failed>\n");
    }

    __try {
        DumpStruct(&b, "PlayerData @0x0066B404 (0x2bc0)", s_pPlayerData,
                   kPlayerDataFields, kPlayerDataFieldCount, s_prevPlayer);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        DumpPrintf(&b, "<PlayerData read failed>\n");
    }

    __try {
        DumpGlobals(&b);
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
        CheckDlgButton(hwnd, IDC_INSP_SKIPZERO, BST_CHECKED);
        CheckDlgButton(hwnd, IDC_INSP_SAVEFILE, BST_CHECKED);
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