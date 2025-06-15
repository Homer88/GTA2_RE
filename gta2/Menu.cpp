#include "Global.h"
#include "Menu.h"


Menu gMenu;



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
	     MENUSCREEN_CREDITS = 17u,};

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




void Menu::InitializeState(int Pages) {
	this->Page = Pages;
	  
	if (Pages == MENUPAGE_PARENTAL_CONTROL) {
		this->State = 5;
		this->Index = 0;
		this->field_C9B7 = 0;
		this->clearArrayTail();
		this->field_C99F = 1;
		this->Key = 28;
		this->field_C9A2 = 5;
	}
	switch (Pages) {
	case  MENUPAGE_CREDITS: {
		this->field_1EB1C = 1;
		this->field_1EB24 = 0;
		///this->Player = v7;
		this->field_C99F = 1;
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
	};
							   break;
	default:
		break;
	}
}