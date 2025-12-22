#ifndef ___MENU_H_
#define ___MENU_H_
#include <dinput.h>

#include <assert.h>

#include "MenuPage.h"
#include "KeyState.h"
#include "S138.h"
#include "S139.h"





class Menu {
public:
		 LPDIRECTINPUTA DirectInput;
	     LPDIRECTINPUTDEVICEA InputDevice;
	     char Keys[256];
	     int FrontendState;
	     char KeyboardAcquired;
	     char FrontendKeysEnabled;
	     int State;
	     unsigned short FontStyle;
		 unsigned short PageNumber;
		 unsigned short CountPages;
	     MenuPage pMenuPage[17];
	     wchar_t* PlayerName;
	     char Length;
	     short Key;
	     unsigned short MenuItems[9];
	     char CurentArrayIndex;
	     KeyState NewKeyState;
	     KeyState OldKeyState;
	     int TimeToWaitDemoStart;
	     char FrameCounter;
	     char isChaet;
	     int TimeToWaitBeforeDemoStart;
		 S138 pS138[8];
		 int MenuPic; //MenuPicture
		 S139 pS139;
	     Player *pPlayer;
	     char Index;
	   


		 Menu();
		 ~Menu() {};

		 //методы  inline
		 void MainMenuCreate();
		 void PlayMenuCreate();
		 void BonusAMenuCreate();
		 void CompliteLevelMenuCreate();
		 void ResumeLoadSaveCreate();
		 void YouAreDead_RIP();
		 // мои исправление 
		 void OptionsMenuCreate();
		 void NetworkGameMenuCreate();
		 void NetworkServerMenuCreate();
		 void NetworkClientMenuCreate();
		 
		 //обычные 

		 void SetFrontendKeysEnabled(byte param);
		 wchar_t* getPlayerProfileName();
		 void SetPlayerProfileName(wchar_t* NamePlayer);
		 void SetPlayerProfileName(wchar_t* NamePlayer, int Count);
		 unsigned short clearArrayTail();
		 void InitializeState(int Pages);
		 void PlayerCheat(wchar_t* PlayerName);
		 void SetPlayerNameFromMenu();
		 PlayerSlotSave* getPlayerProfileNamePlayerData();
		 short  LoadTextMenu();
		 short PrintCentr(wchar_t* TextElement, unsigned short stringLength, unsigned short centrScreen);

		 

	
};
#endif // !___MENU_H_

