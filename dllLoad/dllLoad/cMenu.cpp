#include <Windows.h>
#include <stdio.h>
#include "cMenu.h"
#include "cGlobal.h"
#include "cPlayerData.h"
#include "cText.h"
#include "DebugLogFile.h" 

extern PlayerData* gPlayerData;
static  Menu* gMenu = (Menu*)0x005EB160;

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
    constexpr int MAX_LENGTH = 79; // Один символ для нуль-терминатора

    // Преобразуем до 79 символов (последний остаётся для '\0')
    while (*src != L'\0' && i < MAX_LENGTH) {
        if (*src < 0x80) { // ASCII символ
            gNamePlayerASCII[i] = static_cast<char>(*src);
        }
        else { // Не-ASCII символ - заменяем на '#'
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
    CUTIE1 = 0x33A69,                 // Дает 99 жизней
    NEKKID = 0x36F62,                 // Нудисты
    MADEMAN = 0x41611,                 // Дает авторитет
    DANISGOD = 0x44D2F,                 // дает 20000
    FYOHZZ0 = 0x45118,
    FISHFLAP = 0x45AEF,                 // Small Cars
    UKGAMER = 0x45B2C,                 // all towns unlocked
    FLAMEON = 0x45EC2,                 // Бecкoнeчнaя Flame Gun
    DAVEMOON = 0x4639F,                 // Базовое оружие и бесконечные патроны
    EATSOUP = 0x4657B,                 // Бесплатные магазины
    IAMDAVEJ = 0x4672D,                 // дает 999999
    LASVEGAS = 0x46BE8,                 // Фaнаты Элвисa
    NAVARONE = 0x47178,                 // All Weapons
    COCKTART = 0x478A9,                 // За взрывы не будут выдаваться очки.
    PSJABBER = 0x478FB,                 // на бессмертие
    ARSESTAR = 0x47AF1,                 // Пocлe apecтa y вac coxpaняютcя вce имeвшиecя в нaличии пyшки
    GOREFEST = 0x484DF,                 // Количество крови в игре заметно увеличится.
    BUCKFAST = 0x4878D,                 // Режим «Бунт»
    GOURANGA = 0x49362,                 // Активация читов
    GODOFGTA = 0x49771,                 // Все оружие
    SUPZZZ0 = 0x49C76,
    SEGARULZ = 0x4A98B,                 // 10x Point Multiplier
    ITSALLUP = 0x4A9B8,                 // Выбop ypoвня
    HUNSRUS = 0x4B28C,                 // Нeвидимocть
    SCHURULZ = 0x4D5C4,                 // Двойной урон
    VOLTFEST = 0x4DA77,                 // Бecкoнeчнaя Electrical Gun
    TUMYFROG = 0x5073D,                 // Вce бoнyc-ypoвни
};

int* gActiveCheat = (int*)0x005EAF50;// воспроизводит звук принятие пароля
char PlayerCheat(Menu* pthis, wchar_t* PlayerName)
{
    // TODO ME  убрать отладку  
    gMenu->isChaet = true;
    unsigned char *chName; //массив 8  элементов
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
                   //S150::sub_4A8B00(gS150); Надо писать ее
                   //Menu::sub_456E80(this); Надо писать ее
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

void  __stdcall sub_459540(void) {
//void  __stdcall sub_459540(Menu* pthis){
    unsigned short PlayerSlot; 
    wchar_t* PlayerName; 

    int pl = offsetof(Menu, pPlayerName);
    int address = (uintptr_t)gMenu;

    //Debuglog(Menu, PLayerName, "PlayerName");
    DebugLog(pl);
    DebugLog(address);
  
    DebugLog(gMenu->pPlayerName);


    PlayerSlot = gMenu->pMenuPage[1].pMenuEntry[0].PlayerSlot;
    PlayerName = gPlayerData->pPlayerSlotSave[PlayerSlot].PlayerName;
    DebugLog(PlayerName);
     // wcsncpy(PlayerName, gMenu->PlayerName, 9u);
    PlayerCheat(gMenu, gMenu->pPlayerName);
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
short  __stdcall  LoadTextMenu() {
    gMenu->Filderer0x120 = 16;
    gMenu->pMenuPage[0].numMenuItems = 3;
    gMenu->pMenuPage[0].pMenuEntry[0].pMenuActions = MENUPAGE_PLAY;
    gMenu->pMenuPage[0].pMenuEntry[0].X = 300;
    gMenu->pMenuPage[0].pMenuEntry[0].Y = 250;
    //const wchar_t **play= Bsearch(gText, L"play");
    wcsncpy(gMenu->pMenuPage[0].pMenuEntry[0].TextMenuElement, L"Play", 50u);
    DebugLog(gMenu->pMenuPage[0].pMenuEntry[0].TextMenuElement);
    gMenu->pMenuPage[0].pMenuEntry[0].SelectMenu = MENUPAGE_PLAY;
    gMenu->pMenuPage[0].pS137[0].Y = 258;
    gMenu->pMenuPage[0].pS137[0].X = 280;
    gMenu->pMenuPage[0].pS137[1].X = 280;
    gMenu->pMenuPage[0].pS137[1].Y = 278;
    gMenu->pMenuPage[0].pS137[2].X = 280;
    gMenu->pMenuPage[0].pS137[2].Y = 298;
    gMenu->pMenuPage[0].IndexMenuActions = MENUPAGE_START_MENU;
    gMenu->pMenuPage[0].field_BC8 = MENUPAGE_START_MENU;


    gMenu->pMenuPage[7].pS136[7].field_2 = 40;
    gMenu->pMenuPage[7].pS136[8].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pS136[8].field_2 = 100;
    gMenu->pMenuPage[7].pS136[8].field_4 = 320;
    gMenu->pMenuPage[7].pS136[9].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pS136[9].field_2 = 100;
    gMenu->pMenuPage[7].pS136[9].field_4 = 340;
    gMenu->pMenuPage[7].pS136[10].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pS136[10].field_2 = 100;
    gMenu->pMenuPage[7].pS136[10].field_4 = 360;
    gMenu->pMenuPage[7].pS136[11].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pS136[11].field_2 = 100;
    gMenu->pMenuPage[7].pS136[11].field_4 = 380;
    gMenu->pMenuPage[7].pS136[12].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pS136[12].field_2 = 100;
    gMenu->pMenuPage[7].pS136[12].field_4 = 400;
    gMenu->pMenuPage[7].pS136[13].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pS136[13].field_2 = 30;
    gMenu->pMenuPage[7].pS136[13].field_4 = 150;
    gMenu->pMenuPage[7].pMenuEntry[0].pMenuActions = MENUPAGE_PLAY;
    gMenu->pMenuPage[7].pMenuEntry[0].Y = 430;
   
    wcsncpy(gMenu->pMenuPage[7].pMenuEntry[0].TextMenuElement, L"quit", 0x32u);

    gMenu->pMenuPage[14].pS136[2].Visible = MENUPAGE_PLAY;
    gMenu->pMenuPage[14].pS136[2].field_2 = 20;
    gMenu->pMenuPage[14].pS136[2].field_4 = 200;


    gMenu->pMenuPage[14].IndexMenuActions = MENUPAGE_START_MENU;
    gMenu->pMenuPage[14].field_BC8 = MENUPAGE_START_MENU;
    return 0;
}