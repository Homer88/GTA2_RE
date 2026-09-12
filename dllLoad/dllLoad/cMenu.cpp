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

int* gActiveCheat = (int*)0x005EAF50;// ������������� ���� �������� ������
char PlayerCheat(Menu* pthis, wchar_t* PlayerName)
{
    // TODO ME  ������ �������  
    if (pthis) {
        pthis->isChaet = true;
    }
    unsigned char *chName; //������ 8  ���������
    chName = ConvertWCharToChar(PlayerName);
    DebugLog(chName);
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
                *gActiveCheat = 9;
                return 0;
            }
           if (pthis->isChaet){
                             
               switch (cash)
               {
               case GOREFEST:
                   *gDoBlood = true;
                   *gActiveCheat = 9;
                   return 0;
               case BUCKFAST:
                   *gBunt = true;
                   *gActiveCheat = 9;
                   return 0;
               case VOLTFEST:
                   *gElectroGun = true;
                   *gActiveCheat = 9;
                   return 0;
               case MADEMAN:
                   *gMADEMAN = true;
                   *gActiveCheat = 9;
                   return 0;
               case LASVEGAS:
                   *gElvis = true;
                   *gActiveCheat = 9;
                   return 0;
               case NEKKID:
                   *gNEKKID = true;
                   *gActiveCheat = 9;
                   return 0;
               case EATSOUP:
                   *gDoFreeShopping = true;
                   *gActiveCheat = 9;
                   return 0;
               case DAVEMOON:
                  *gGiveBasikWeapon = true;
                   *gActiveCheat = 9;
                   return 0;
               case CUTIE1:
                   *gHealth99 = true;
                   DebugLog("GO");
                   *gActiveCheat = 9;
                   return 0;
               case ARSESTAR:
                   *gKeepWeaponsAfterDeath= !*gKeepWeaponsAfterDeath;
                   *gActiveCheat = 9;
                   return 0;
               case GODOFGTA:
                   *gGetAllWeapons =true;
                   *gActiveCheat = 9;
                   return 0;
               case PSJABBER:
                   *gDoInvulnerable = true;
                   *gActiveCheat = 9;
                   return 0;
               case DANISGOD:
                   *gGiveMoney20 = true;
                   *gActiveCheat = 9;
                   return 0;
               case COCKTART:
                   *gExploding_on = true;
                   *gActiveCheat = 9;
                   return 0;
               case FLAMEON:
                   *gFireGun = true;
                   *gActiveCheat = 9;
                   return 0;
               case FYOHZZ0:
                   *gJailFreeCard = true;
                   *gActiveCheat = 9;
                   return 0;
               case IAMDAVEJ:
                   *gIAMDAVEJ = true;
                   *gActiveCheat = 9;
                   return 0;
               case SEGARULZ:
                   *gPontMultiplaerX10 = true;
                   *gActiveCheat = 9;
                   return 0;
               case UKGAMER:
                   *gAllTower = true;
                   //S150::sub_4A8B00(gS150); ���� ������ ��
                   //Menu::sub_456E80(this); ���� ������ ��
                   *gActiveCheat = 9;
                   return 0;
               case SUPZZZ0:
                   *gSUPZZZ0 = !*gSUPZZZ0;
                   //S150::sub_4A8A90(gS150, 1u, 0);
                   //Menu::sub_456E80(this);
                   *gActiveCheat = 9;
                   return 0;
               case TUMYFROG:
                   *gBonusAll = !*gBonusAll;
                   //PlayerData::sub_4A8B00(gPlayerData);
                   //S150::sub_4A8A90(gPlayerData, 2u, 2u);
                   //S150::sub_4A8A90(gPlayerData, 1u, 0);
                   //Menu::sub_456E80(this);
                   *gActiveCheat = 9;
                   return 0;
               case SCHURULZ:
                   *gDoubleDamage = !*gDoubleDamage;
                   *gActiveCheat = 9;
                   break;
               case HUNSRUS:
                   *gInvisibility =!*gInvisibility;
                   *gActiveCheat = 9;
                   break;
               case FISHFLAP:
                   *gActiveCheat = 9;
                   *gSmallCar = !*gSmallCar;
                   break;
               default:
                   break;
               }
           }
        }

     }
    return 0;



}





//int __thiscall Menu::sub_459540(Menu* pthis)

void  __fastcall sub_459540(Menu* thisMenu) {
//void  __stdcall sub_459540(Menu* pthis){
    unsigned short PlayerSlot; 
    wchar_t* PlayerName; 

    TraceEvent("Menu::sub_459540 @0x00459540");

    int pl = offsetof(Menu, pPlayerName);
    int address = (uintptr_t)thisMenu;

    //Debuglog(Menu, PLayerName, "PlayerName");
    DebugLog(pl);
    DebugLog(address);
  
    DebugLog(thisMenu->pPlayerName);


    PlayerSlot = thisMenu->pMenuPage[1].pMenuEntry[0].PlayerSlot;
    PlayerName = gPlayerData->pPlayerSlotSave[PlayerSlot].PlayerName;
    DebugLog(PlayerName);
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

// 1 = run the reconstructed stub below (only 3 pages, hardcoded "Play"/"quit", no .gxt).
// 0 = call the ORIGINAL retail Menu::LoadTextMenu (builds all pages, reads text from
//     gText.Bsearch) - restores the frontend texts.
#define LOADTEXTMENU_USE_REPLICA 0

short  __fastcall  LoadTextMenu(Menu* thisMenu)
{
    TraceEvent("Menu::LoadTextMenu @0x00453E20");
    DebugLog((int)thisMenu);
    DebugLog((int)GetGameMenu());
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
    DebugLog(thisMenu->pMenuPage[0].pMenuEntry[0].TextMenuElement);
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