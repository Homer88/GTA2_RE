#include <Windows.h>
#include <stdio.h>
#include "cMenu.h"
#include "cGlobal.h"
#include "cPlayerData.h"
#include "cText.h"
#include "DebugLogFile.h"
#include "cHookTrace.h" 

extern PlayerData* gPlayerData;

// 0x005EB160 is the address of the global Menu* cell in .data (not the Menu
// instance!). The real Menu is heap-allocated (operator_new(0x1EB40) in
// FUN_00457830) and its address is stored in that cell. Read the pointer, do
// NOT use the cell address itself as a Menu* (that reads garbage -> crash).
Menu* GetGameMenu(void)
{
    return (Menu*)(*(void**)0x005EB160);
}

//char gNamePlayerASCII[80] ;
unsigned char *gNamePlayerASCII = (unsigned char*)0x00671880;

//char* __thiscall Menu::WCHARToChar(Menu* this, char* PlayerName)
unsigned char*   ConvertWCharToChar(wchar_t *wsc)
{
    if (!wsc) {
        gNamePlayerASCII[0] = '\0';
        return gNamePlayerASCII;
    }

    int i = 0;
    const wchar_t* src = wsc;
    constexpr int MAX_LENGTH = 79; // ���� ������ ��� ����-�����������

    // ����������� �� 79 �������� (��������� ������� ��� '\0')
    while (*src != L'\0' && i < MAX_LENGTH) {
        if (*src < 0x80) { // ASCII ������
            gNamePlayerASCII[i] = static_cast<char>(*src);
        }
        else { // ��-ASCII ������ - �������� �� '#'
            gNamePlayerASCII[i] = '#';
        }
        ++src;
        ++i;
    }
    gNamePlayerASCII[i] = '\0';
    return gNamePlayerASCII;
}


                                //0     1       2      3    4       5       6   7   
unsigned short gCodeInit[8] = { 829, 761, 23, 641, 43, 809, 677, 191 };



//char __thiscall Menu::PlayerCheat(Menu* this, wchar_t* PlayerName)

enum Cheat{
    CUTIE1 = 0x33A69,                 // ���� 99 ������
    NEKKID = 0x36F62,                 // �������
    MADEMAN = 0x41611,                 // ���� ���������
    DANISGOD = 0x44D2F,                 // ���� 20000
    FYOHZZ0 = 0x45118,
    FISHFLAP = 0x45AEF,                 // Small Cars
    UKGAMER = 0x45B2C,                 // all towns unlocked
    FLAMEON = 0x45EC2,                 // �ec�o�e��a� Flame Gun
    DAVEMOON = 0x4639F,                 // ������� ������ � ����������� �������
    EATSOUP = 0x4657B,                 // ���������� ��������
    IAMDAVEJ = 0x4672D,                 // ���� 999999
    LASVEGAS = 0x46BE8,                 // �a���� �����a
    NAVARONE = 0x47178,                 // All Weapons
    COCKTART = 0x478A9,                 // �� ������ �� ����� ���������� ����.
    PSJABBER = 0x478FB,                 // �� ����������
    ARSESTAR = 0x47AF1,                 // �oc�e apec�a y �ac coxpa����c� �ce ��e���ec� � �a����� �y���
    GOREFEST = 0x484DF,                 // ���������� ����� � ���� ������� ����������.
    BUCKFAST = 0x4878D,                 // ����� �����
    GOURANGA = 0x49362,                 // ��������� �����
    GODOFGTA = 0x49771,                 // ��� ������
    SUPZZZ0 = 0x49C76,
    SEGARULZ = 0x4A98B,                 // 10x Point Multiplier
    ITSALLUP = 0x4A9B8,                 // ���op ypo���
    HUNSRUS = 0x4B28C,                 // �e�����oc��
    SCHURULZ = 0x4D5C4,                 // ������� ����
    VOLTFEST = 0x4DA77,                 // �ec�o�e��a� Electrical Gun
    TUMYFROG = 0x5073D,                 // �ce �o�yc-ypo���
};

int* gCheatIs = (int*)0x005EAF50;// ������������� ���� �������� ������
char PlayerCheat(Menu* pthis, wchar_t* PlayerName)
{
    // TODO ME  ������ �������  
    if (pthis) {
        pthis->isChaet = true;
    }
    unsigned char *chName; //������ 8  ���������
    chName = ConvertWCharToChar(PlayerName);
    writeFileLog((char*)"menu.txt", (char*)"chName", (char*)"PlayerCheat", (char*)chName);
    int  lenString = wcslen(PlayerName);
    if (lenString <= 16) {
        int index = 0;
        int cash = 0;
        char text[] = "cash";
        if (lenString) {

            do {
                
                cash += gCodeInit[index] * chName[index];
                index++;
            }
            while(index <= lenString);
         

            if (cash == GOURANGA) {
                pthis->isChaet = true;
                *gCheatIs = 9;
                return 0;
            }
           if (pthis->isChaet){
                             
               switch (cash)
               {
               case GOREFEST:
                   *gDoBlood = true;
                   *gCheatIs = 9;
                   return 0;
               case BUCKFAST:
                   *gBunt = true;
                   *gCheatIs = 9;
                   return 0;
               case VOLTFEST:
                   *gVOLTFEST = true;
                   *gCheatIs = 9;
                   return 0;
               case MADEMAN:
                   *gMADEMAN = true;
                   *gCheatIs = 9;
                   return 0;
               case LASVEGAS:
                   *gLASVEGAS = true;
                   *gCheatIs = 9;
                   return 0;
               case NEKKID:
                   *gNEKKID = true;
                   *gCheatIs = 9;
                   return 0;
               case EATSOUP:
                   *gDoFreeShopping = true;
                   *gCheatIs = 9;
                   return 0;
               case DAVEMOON:
                  *gDAVEMOON = true;
                   *gCheatIs = 9;
                   return 0;
               case CUTIE1:
*gHeats99 = true;
                    writeFileLog((char*)"menu.txt", (char*)"Cutie1", (char*)"PlayerCheat", (char*)"GO");
                   *gCheatIs = 9;
                   return 0;
               case ARSESTAR:
                   *gKeepWeaponsAfterDeath= !*gKeepWeaponsAfterDeath;
                   *gCheatIs = 9;
                   return 0;
               case GODOFGTA:
                   *gGetAllWeapons =true;
                   *gCheatIs = 9;
                   return 0;
               case PSJABBER:
                   *gDoInvulnerable = true;
                   *gCheatIs = 9;
                   return 0;
               case DANISGOD:
                   *gDANISGOD = true;
                   *gCheatIs = 9;
                   return 0;
               case COCKTART:
                   *gExploding_on = true;
                   *gCheatIs = 9;
                   return 0;
               case FLAMEON:
                   *gFLAMEON = true;
                   *gCheatIs = 9;
                   return 0;
               case FYOHZZ0:
                   *gFYOHZZ0 = true;
                   *gCheatIs = 9;
                   return 0;
               case IAMDAVEJ:
                   *gIAMDAVEJ = true;
                   *gCheatIs = 9;
                   return 0;
               case SEGARULZ:
                   *gSEGARULZ = true;
                   *gCheatIs = 9;
                   return 0;
               case UKGAMER:
                   *gUKGAMER = true;
                   //S150::sub_4A8B00(gS150); ���� ������ ��
                   //Menu::sub_456E80(this); ���� ������ ��
                   *gCheatIs = 9;
                   return 0;
               case SUPZZZ0:
                   *gSUPZZZ0 = !*gSUPZZZ0;
                   //S150::sub_4A8A90(gS150, 1u, 0);
                   //Menu::sub_456E80(this);
                   *gCheatIs = 9;
                   return 0;
               case TUMYFROG:
                   *gTUMYFROG = !*gTUMYFROG;
                   //PlayerData::sub_4A8B00(gPlayerData);
                   //S150::sub_4A8A90(gPlayerData, 2u, 2u);
                   //S150::sub_4A8A90(gPlayerData, 1u, 0);
                   //Menu::sub_456E80(this);
                   *gCheatIs = 9;
                   return 0;
               case SCHURULZ:
                   *gSCHURULZ = !*gSCHURULZ;
                   *gCheatIs = 9;
                   break;
               case HUNSRUS:
                   *gHUNSRUS =!*gHUNSRUS;
                   *gCheatIs = 9;
                   break;
               case FISHFLAP:
                   *gCheatIs = 9;
                   *gFISHFLAP = !*gFISHFLAP;
                   break;
               default:
                   break;
               }
           }
        }

     }
    return 0;



}





//int __thiscall Menu::SetPlayerNameFromMenu(Menu* this)

void  __fastcall SetPlayerNameFromMenu(Menu* thisMenu) {
//void  __stdcall SetPlayerNameFromMenu(Menu* pthis){
    unsigned short PlayerSlot; 
    wchar_t* PlayerName; 

    TraceCall("Menu::SetPlayerNameFromMenu @0x00459540", TRACE_CALLER_ADDR);

    int pl = offsetof(Menu, pPlayerName);
    int address = (uintptr_t)thisMenu;

    //Debuglog(Menu, PLayerName, "PlayerName");
    writeFileLog((char*)"menu.txt", (char*)"offsetof(pPlayerName)", (char*)"SetPlayerNameFromMenu", (unsigned int)pl);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"SetPlayerNameFromMenu", (unsigned int)address);

    writeFileLog((char*)"menu.txt", (char*)"pPlayerName", (char*)"SetPlayerNameFromMenu", (unsigned int)thisMenu->pPlayerName);


    PlayerSlot = thisMenu->pMenuPage[1].pMenuEntry[0].PlayerSlot;
    PlayerName = gPlayerData->pPlayerSlotSave[PlayerSlot].PlayerName;
    writeFileLog((char*)"menu.txt", (char*)"PlayerName", (char*)"SetPlayerNameFromMenu", (unsigned int)PlayerName);
     // wcsncpy(PlayerName, gMenu->PlayerName, 9u);
    PlayerCheat(thisMenu, thisMenu->pPlayerName);
    //S150::sub_4A89E0(gPlayerData, PlayerSlot);
}

enum  MenuPages // 4 bytes
     {
         MENUPAGE_NONE = -1,
         MENUPAGE_START_MENU = 0,
         MENUPAGE_PLAY = 1,
         MENUPAGE_DEAD = 2,
         MENUPAGE_AREA_COMPLETE = 3,
         MENUPAGE_GAME_COMPLETE = 4,
         MENUPAGE_VIEW_HIGH_SCORE = 5,
         MENUPAGE_BONUS_AREA = 6,
         MENUPAGE_UNK_KILLS = 7,
         MENUPAGE_PLAY_INTRO = 8,
         MENUPAGE_CREDITS = 9,
         MENUPAGE_NICE_TRY = 10,
         MENUPAGE_RESULTS_PLAYER_QUIT = 11,
         MENUPAGE_12 = 12,
         MENUPAGE_13 = 13,
         MENUPAGE_PARENTAL_CONTROL = 14,
         MENUPAGE_15 = 15,
         NUM_MENUPAGES = 16,
         MENUPAGE_GTA2MANAGER = 257,
         MENUPAGE_QUIT = 258,
         MENUPAGE_259 = 259,
         MENUPAGE_264 = 264,
         MENUPAGE_265 = 265,
         MENUPAGE_260 = 260,
         MENUPAGE_261 = 261,
         MENUPAGE_266 = 266,
    
};

extern Text* gText;
extern LPVOID _LoadTextMenu; // dllmain.cpp: Detours trampoline to the original 0x00453E20
extern LPVOID _LoadGame;
extern LPVOID _SaveGame;
extern LPVOID _MultiplayerMenu;
extern LPVOID _ProcessInput; // dllmain.cpp: Detours trampoline to Menu::ProcessInput 0x00452050

// 1 = run the reconstructed stub below (only 3 pages, hardcoded "Play"/"quit", no .gxt).
// 0 = call the ORIGINAL retail Menu::LoadTextMenu (builds all pages, reads text from
//     gText.Bsearch) - restores the frontend texts.
#define LOADTEXTMENU_USE_REPLICA 0

short  __fastcall  LoadTextMenu(Menu* thisMenu)
{
    TraceCall("Menu::LoadTextMenu @0x00453E20", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"LoadTextMenu", (unsigned int)thisMenu);
    writeFileLog((char*)"menu.txt", (char*)"gMenu", (char*)"LoadTextMenu", (unsigned int)GetGameMenu());
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
#if LOADTEXTMENU_USE_REPLICA
    thisMenu->Filderer0x120 = 16;
    thisMenu->pMenuPage[0].numMenuItems = 3;
    thisMenu->pMenuPage[0].pMenuEntry[0].pMenuActions = MENUPAGE_PLAY;
    thisMenu->pMenuPage[0].pMenuEntry[0].X = 300;
    thisMenu->pMenuPage[0].pMenuEntry[0].Y = 250;
    //const wchar_t **play= Bsearch(gText, L"play");
    wcsncpy(thisMenu->pMenuPage[0].pMenuEntry[0].TextMenuElement, L"Play", 50u);
    writeFileLog((char*)"menu.txt", (char*)"TextMenuElement", (char*)"LoadTextMenu", (unsigned int)thisMenu->pMenuPage[0].pMenuEntry[0].TextMenuElement);
    thisMenu->pMenuPage[0].pMenuEntry[0].SelectMenu = MENUPAGE_PLAY;
    thisMenu->pMenuPage[0].pS137[0].Y = 258;
    thisMenu->pMenuPage[0].pS137[0].X = 280;
    thisMenu->pMenuPage[0].pS137[1].X = 280;
    thisMenu->pMenuPage[0].pS137[1].Y = 278;
    thisMenu->pMenuPage[0].pS137[2].X = 280;
    thisMenu->pMenuPage[0].pS137[2].Y = 298;
    thisMenu->pMenuPage[0].IndexMenuActions = MENUPAGE_START_MENU;
    thisMenu->pMenuPage[0].field_BC8 = MENUPAGE_START_MENU;


    thisMenu->pMenuPage[7].pS136[7].field_2 = 40;
    thisMenu->pMenuPage[7].pS136[8].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pS136[8].field_2 = 100;
    thisMenu->pMenuPage[7].pS136[8].field_4 = 320;
    thisMenu->pMenuPage[7].pS136[9].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pS136[9].field_2 = 100;
    thisMenu->pMenuPage[7].pS136[9].field_4 = 340;
    thisMenu->pMenuPage[7].pS136[10].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pS136[10].field_2 = 100;
    thisMenu->pMenuPage[7].pS136[10].field_4 = 360;
    thisMenu->pMenuPage[7].pS136[11].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pS136[11].field_2 = 100;
    thisMenu->pMenuPage[7].pS136[11].field_4 = 380;
    thisMenu->pMenuPage[7].pS136[12].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pS136[12].field_2 = 100;
    thisMenu->pMenuPage[7].pS136[12].field_4 = 400;
    thisMenu->pMenuPage[7].pS136[13].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pS136[13].field_2 = 30;
    thisMenu->pMenuPage[7].pS136[13].field_4 = 150;
    thisMenu->pMenuPage[7].pMenuEntry[0].pMenuActions = MENUPAGE_PLAY;
    thisMenu->pMenuPage[7].pMenuEntry[0].Y = 430;
   
    wcsncpy(thisMenu->pMenuPage[7].pMenuEntry[0].TextMenuElement, L"quit", 0x32u);

    thisMenu->pMenuPage[14].pS136[2].Visible = MENUPAGE_PLAY;
    thisMenu->pMenuPage[14].pS136[2].field_2 = 20;
    thisMenu->pMenuPage[14].pS136[2].field_4 = 200;


    thisMenu->pMenuPage[14].IndexMenuActions = MENUPAGE_START_MENU;
    thisMenu->pMenuPage[14].field_BC8 = MENUPAGE_START_MENU;
    return 0;
#else
    // Chain to the original retail implementation (Menu::LoadTextMenu, __thiscall).
    // This builds the complete menu and fills the strings from the loaded .gxt data.
    // IMPORTANT: forward the ORIGINAL this (thisMenu, taken from ECX), NOT the global
    // gMenu cell address - during Menu::Menu() the global is still NULL and the
    // retail code must write into the real heap Menu.
    return ((short (__thiscall*)(Menu*))_LoadTextMenu)(thisMenu);
#endif
}

// Retail Menu::LoadGame @0x00455C20 (__thiscall): iterates the 8 save slots via
// Menu::GetSaveFile + MenuDataBlock::Load. Trace + forward to the original.
char __fastcall LoadGame(Menu* thisMenu)
{
    TraceCall("Menu::LoadGame @0x00455C20", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"LoadGame", (unsigned int)thisMenu);
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
    return ((char (__thiscall*)(Menu*))_LoadGame)(thisMenu);
}

unsigned __int8 __fastcall SaveGame(Menu* thisMenu)
{
    TraceCall("Menu::SaveGame @0x00455C90", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"SaveGame", (unsigned int)thisMenu);
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
    return ((unsigned __int8 (__thiscall*)(Menu*))_SaveGame)(thisMenu);
}

char __fastcall MultiplayerMenu(Menu* thisMenu, void* _EDX, void* pPlayerName)
{
    (void)_EDX;
    TraceCall("Menu::MultiplayerMenu @0x004565E0", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"MultiplayerMenu", (unsigned int)thisMenu);
    writeFileLog((char*)"menu.txt", (char*)"pPlayerName", (char*)"MultiplayerMenu", (unsigned int)pPlayerName);
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
    return ((char (__thiscall*)(Menu*, void*))_MultiplayerMenu)(thisMenu, pPlayerName);
}

static const char* const kDIKNames[256] = {
    /* 0  */ "none", "esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    /* 12 */ "-", "=", "back", "tab", "q", "w", "e", "r", "t", "y", "u", "i",
    /* 24 */ "o", "p", "[", "]", "enter", "lctrl", "a", "s", "d", "f", "g",
    /* 35 */ "h", "j", "k", "l", ";", "'", "`", "lshift", "\\", "z", "x", "c",
    /* 47 */ "v", "b", "n", "m", ",", ".", "/", "rshift", "*", "lalt", "space",
    /* 58 */ "caps", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10",
    /* 69 */ "numlock", "scroll", "num7", "num8", "num9", "num-", "num4", "num5",
    /* 77 */ "num6", "num+", "num1", "num2", "num3", "num0", "num.",
    /* 84 */ NULL, NULL, NULL,
    /* 87 */ "f11", "f12",
    /* 89 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /* 99 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*109 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*119 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*129 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*139 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*149 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*159 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*169 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*179 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*189 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*199 */ "home", "up", "pgup", NULL, "left", NULL, "right", NULL,
    /*207 */ "end", "down", "pgdn", "ins", "del",
    /*212 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*219 */ "lwin", "rwin", "apps",
};

static void KeysPressedList(const Menu* m, char* out, size_t outSize)
{
    const unsigned char* k = (const unsigned char*)m->Keys;
    char* p = out;
    size_t left = outSize;
    int first = 1;
    int i;
    out[0] = 0;
    for (i = 0; i < 256; i++) {
        const char* name;
        int n;
        if (!(k[i] & 0x80))
            continue;
        name = kDIKNames[i];
        if (name == NULL) {
            char raw[8];
            _snprintf(raw, sizeof(raw), "0x%02X", i);
            n = _snprintf(p, left, "%s%s", first ? "" : "+", raw);
        }
        else {
            n = _snprintf(p, left, "%s%s", first ? "" : "+", name);
        }
        if (n < 0 || (size_t)n >= left) {
            break;
        }
        p += n;
        left -= (size_t)n;
        first = 0;
    }
}

static void WCharToAsciiBuf(const wchar_t* w, char* out, size_t outSize, size_t maxLen)
{
    size_t i = 0;
    if (w == NULL) {
        out[0] = 0;
        return;
    }
    for (i = 0; i < maxLen && w[i] != 0 && i + 1 < outSize; i++) {
        out[i] = (w[i] >= 0x20 && w[i] <= 0x7E) ? (char)w[i] : '?';
    }
    out[i] = 0;
}

void __fastcall HookProcessInput(Menu* m, void* _EDX)
{
    static unsigned char s_lastKeys[256];
    static Menu* s_lastMenu = NULL;
    static unsigned char s_booted = 0;
    char keys[160];
    char pageDump[768];
    char buf[1400];
    char tmp[64];
    const unsigned char* k;
    MenuPage* pg;
    int n;
    int e;
    int i;
    int pressedNew = 0;

    (void)_EDX;
    TraceCall("Menu::ProcessInput @0x00452050", TRACE_CALLER_ADDR);
    ((void (__thiscall*)(Menu*))_ProcessInput)(m);

    __try {
        if (!m->FrontendKeysEnabled) {
            return;
        }
        k = (const unsigned char*)m->Keys;
        if (m != s_lastMenu) {
            s_lastMenu = m;
            memcpy(s_lastKeys, k, 256);
        }
        for (i = 0; i < 256; i++) {
            if ((k[i] & 0x80) && !(s_lastKeys[i] & 0x80)) {
                pressedNew++;
            }
        }
        memcpy(s_lastKeys, k, 256);
        if (!pressedNew && s_booted) {
            return;
        }
        s_booted = 1;

        KeysPressedList(m, keys, sizeof(keys));

        pg = &m->pMenuPage[m->Page];
        n = pg->numMenuItems;
        if (n < 0 || n > 10) {
            n = 0;
        }
        pageDump[0] = 0;
        _snprintf(pageDump, sizeof(pageDump),
                  "page %u: %d items, idx=%u, ", (unsigned)m->Page, n,
                  (unsigned)m->CurrentMenuItemsIndex);
        for (e = 0; e < n; e++) {
            const MenuEntry* en = &pg->pMenuEntry[e];
            char t[64];
            char one[160];
            WCharToAsciiBuf(en->TextMenuElement, t, sizeof(t), 30);
            _snprintf(one, sizeof(one), "e%d[a=%u@(%d,%d) sel=%u \"%s\"]",
                      e, (unsigned)en->pMenuActions, en->X, en->Y,
                      (unsigned)en->SelectMenu, t);
            if (strlen(pageDump) + strlen(one) + 1 < sizeof(pageDump)) {
                strcat(pageDump, one);
            }
        }

        WCharToAsciiBuf(m->MenuItems, tmp, sizeof(tmp), 8);
        // KeyState is an empty struct in cMenu.h; read the raw bytes instead.
        // NewKeyState @0xC9B8 and OldKeyState @0xC9C0 are 8 bytes each.
        {
            const unsigned char* nk = (const unsigned char*)m + offsetof(Menu, NewKeyState);
            const unsigned char* ok = nk + 8;
            _snprintf(buf, sizeof(buf),
                      "keys=%s | FrontendKeysEnabled=%d State=%d Page=%u MenuItems=\"%s\" Key=%d | "
                      "NewKey=%02X %02X %02X %02X %02X %02X %02X %02X Old=%02X %02X %02X %02X %02X %02X %02X %02X | %s",
                      keys, (int)m->FrontendKeysEnabled, (int)m->FrontendState,
                      (unsigned)m->Page, tmp, (int)m->Key,
                      nk[0], nk[1], nk[2], nk[3], nk[4], nk[5], nk[6], nk[7],
                      ok[0], ok[1], ok[2], ok[3], ok[4], ok[5], ok[6], ok[7],
                      pageDump);
        }
        writeFileLog((char*)"menu.txt", buf, (char*)"KeyPress", (char*)"");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        writeFileLog((char*)"menu.txt", (char*)"<HookProcessInput read error>",
                     (char*)"KeyPress", (char*)"");
    }
}