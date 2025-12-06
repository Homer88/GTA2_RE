#include "Global.h"
#include "Menu.h"
#include "WinMain.h"

enum  MenuScreens {
    MENUSCREEN_OPTIONS = 0u,
    MENUSCREEN_PLAY = 1u,
    MENUSCREEN_QUIT = 2u,
    MENUSCREEN_BONUSAC = 3u,
    MENUSCREEN_BONUSDF = 4u,
    MENUSCREEN_BONUSGI = 5u,
    MENUSCREEN_VIEWHISCORE = 6u,
    MENUSCREEN_PLAYAREA1 = 7u,
    MENUSCREEN_PLAYAREA2 = 8u,
    MENUSCREEN_PLAYAREA3 = 9u,
    MENUSCREEN_ENTERPLAYERNAME = 10u,
    MENUSCREEN_RESUMELOADSAVE = 11u,
    MENUSCREEN_HISCORES = 12u,
    MENUSCREEN_GAMEOVER = 13u,
    MENUSCREEN_BLUEBAR = 14u,
    MENUSCREEN_LOADING = 15u,
    MENUSCREEN_REDBAR = 16u,
    MENUSCREEN_CREDITS = 17u,
};

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

};
enum  MenuPicture {
    Options = 0u,
    Play = 1u,
    Quit = 2u,
    MenuPic_3 = 3u,
    MenuPic_4 = 4u,
    MenuPic_5 = 5u,
    VievHigh = 6u,
    StartLevel1 = 7u,
    LoadSave = 8u,
    StartLevel3 = 9u,
    PlayerName = 10u,
    Restart = 11u,
    HighScores = 12u,
    RIP = 13u,
    MenuPic_14 = 14u,
    MenuPic_15 = 15u,
    ResumSave = 16u,
    Title = 17u,
    MenuPic_18 = 18u,
    MenuPic_19 = 19u,

};
enum  Cheat {
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


Menu::Menu() {
    this->SetFrontendKeysEnabled(1);
}

void Menu::SetFrontendKeysEnabled(byte param) {
	this->FrontendKeysEnabled = param;
}

wchar_t* Menu::getPlayerProfileName() {
	return this->PlayerName;
}

/*void Menu::SetPlayerProfileName(wchar_t* NamePlayer) {

	
	strcpy((char*)this->PlayerName, (const char* )NamePlayer);
}*/
void Menu::SetPlayerProfileName(wchar_t* NamePlayer,int Count) {


	wcsncpy(this->PlayerName, NamePlayer, Count);
}
void Menu::SetPlayerProfileName(wchar_t* NamePlayer) {

	int Count = strlen((char*)NamePlayer);

	wcsncpy(this->PlayerName, NamePlayer, Count);
}



unsigned short Menu::clearArrayTail() {
	BYTE currentIdx = this->CurentArrayIndex;

	if (currentIdx >= 9) {
		return currentIdx;
	}

	// Обнуление элементов от currentIdx до 8
	unsigned short * array = this->MenuItems;
	for (BYTE i = currentIdx; i < 9; ++i) {
		array[i] = 0;
	}

	return 0;
}








void Menu::InitializeState(int Pages) {
	this->Page = Pages;
	  
	if (Pages == MENUPAGE_PARENTAL_CONTROL) {
		this->State = 5;
		this->Index = 0;
		//this->field_C9B7 = 0;
		this->clearArrayTail();
		//this->field_C99F = 1;
		this->Key = 28;
		//this->field_C9A2 = 5;
	}
	switch (Pages) {
	case  MENUPAGE_CREDITS: {
		//this->field_1EB1C = 1;
		//this->field_1EB24 = 0;
		//this->pPlayer = v7;
		//this->field_C99F = 1;
	}
		break;
	case MENUPAGE_AREA_COMPLETE: {

		gMapGm.GetPlayerArena();
		int Bonus=gMapGm.GetBonus();
		if (gMapGm.GetSpecialTokens() == 50) {
			Bonus = 3;
		}
		if (Bonus) {

		}
	};break;
	default:
		break;
	}
}



void Menu::PlayerCheat(wchar_t* PlayerName)
{
    unsigned char* chName; //массив 8  элементов
    chName = ConvertWCharToChar(PlayerName);
    int  lenString = wcslen(PlayerName);
    if (lenString <= 16) {
        int index = 0;
        int cash = 0;
        if (lenString) {

            do {

                cash += gCodeInit[index] * chName[index];
                index++;
            } while (index <= lenString);


            if (cash == GOURANGA) {
                this->isChaet = true;
                gActiveCheat = 9;
                return ;
            }
            if (this->isChaet) {

                switch (cash)
                {
                case GOREFEST:
                    gDoBlood = true;
                    gActiveCheat = 9;
                    return ;
                case BUCKFAST:
                    gBunt = true;
                    gActiveCheat = 9;
                    return ;
                case VOLTFEST:
                    gElectroGun = true;
                    gActiveCheat = 9;
                    return ;
                case MADEMAN:
                    gMADEMAN = true;
                    gActiveCheat = 9;
                    return ;
                case LASVEGAS:
                    gElvis = true;
                    gActiveCheat = 9;
                    return ;
                case NEKKID:
                    gNEKKID = true;
                    gActiveCheat = 9;
                    return ;
                case EATSOUP:
                    gDoFreeShopping = true;
                    gActiveCheat = 9;
                    return ;
                case DAVEMOON:
                    gGiveBasikWeapon = true;
                    gActiveCheat = 9;
                    return ;
                case CUTIE1:
                    gHealth99 = true;
                    gActiveCheat = 9;
                    return ;
                case ARSESTAR:
                    gKeepWeaponsAfterDeath = true;
                    gActiveCheat = 9;
                    return ;
                case GODOFGTA:
                    gGetAllWeapons = true;
                    gActiveCheat = 9;
                    return ;
                case PSJABBER:
                    gDoInvulnerable = true;
                    gActiveCheat = 9;
                    return ;
                case DANISGOD:
                    gGiveMoney20 = true;
                    gActiveCheat = 9;
                    return ;
                case COCKTART:
                    gExplodingOn = true;
                    gActiveCheat = 9;
                    return ;
                case FLAMEON:
                    gFireGun = true;
                    gActiveCheat = 9;
                    return ;
                case FYOHZZ0:
                    gJailFreeCard = true;
                    gActiveCheat = 9;
                    return ;
                case IAMDAVEJ:
                    gIAMDAVEJ = true;
                    gActiveCheat = 9;
                    return ;
                case SEGARULZ:
                    gPontMultiplaerX10 = true;
                    gActiveCheat = 9;
                    return ;
                case UKGAMER:
                    gAllTower = true;
                    //S150::sub_4A8B00(gS150); Надо писать ее
                    //Menu::sub_456E80(this); Надо писать ее
                    gActiveCheat = 9;
                    return ;
                case SUPZZZ0:
                    gSUPZZZ0 = true;
                    //S150::sub_4A8A90(gS150, 1u, 0);
                    //Menu::sub_456E80(this);
                    gActiveCheat = 9;
                    return ;
                case TUMYFROG:
                    gBonusAll = true;
                    //PlayerData::sub_4A8B00(gPlayerData);
                    //S150::sub_4A8A90(gPlayerData, 2u, 2u);
                    //S150::sub_4A8A90(gPlayerData, 1u, 0);
                    //Menu::sub_456E80(this);
                    gActiveCheat = 9;
                    return;
                case SCHURULZ:
                    gDoubleDamage = true;
                    gActiveCheat = 9;
                    break;
                case HUNSRUS:
                    gInvisibility = true;
                    gActiveCheat = 9;
                    break;
                case FISHFLAP:
                    gActiveCheat = 9;
                    gSmallCar = true;
                    break;
                default:
                    break;
                }
            }
        }

    }
  
}


void Menu::SetPlayerNameFromMenu() {
    
    unsigned short PlayerSlot = this->pMenuPage[1].pMenuEntry[0].PlayerSlot;
    wchar_t* PlayerName = gPlayerData.pPlayerSlotSave[PlayerSlot].PlayerName;
    wcsncpy(PlayerName, this->PlayerName, 9);
    PlayerCheat(PlayerName);
    gPlayerData.WriteFileNamePlayer(PlayerSlot);


}