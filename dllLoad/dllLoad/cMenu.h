#ifndef __MENU_GAMES_H_
#define __MENU_GAMES_H_

#include <assert.h>
#include <dinput.h>

#include "cMenuPage.h"

struct Menu{
	bool	Status;
	LPDIRECTINPUTA* DirectInput;
	LPDIRECTINPUTDEVICEA InputDevice;
	char	Keys[256];
	int		FrontendState;
	char	KeyboardAcquired;
	char	FrontendKeysEnabled;
	char	field_10E;
	char	field_10F;
	int		State;
	int		field_114;
	int		field_118;
	unsigned short FontStyle;
	unsigned short Page;
	short Filderer0x120;
	MenuPage structMenuPage[17];
	wchar_t* PlayerName;
	int field_C990;
	int field_C994;
	int field_C998;
	short field_C99C;
	char Length;
	char field_C99F;
	short Key;
	short field_C9A2;
	unsigned short MenuItems[9];
	char CurentArrayIndex;
	char field_C9B7;
	//KeyState NewKeyState;
		 //KeyState OldKeyState;
	char field_C9C6;
	char field_C9C7;
	int TimeToWaitDemoStart;
	char FrameCounter;
	char isChaet;
	char field_C9CE;
	char field_C9CF;
	int TimeToWaitBeforeDemoStart;
	short gapC9D4;
	char field_C9D6;
	
	char field_CA12;
	short gapCA13;
	// padding byte

	char field_CB5F;
	short gapCB60;
	//MenuPic MenuPic;
		 char MenuPic1;
		 __int16 field_EDF6;
		 char field_EDF8;
		 char field_EDF9;
		 //S139 S139;
		 char field_1EB1C;
		 char field_1EB1D;
		 char field_1EB1E;
		 char field_1EB1F;
		 //Player * Player;
		 char field_1EB24;
		 char field_1EB25;
		 char field_1EB26;
		 char field_1EB27;
		 char field_1EB28;
		 char field_1EB29;
		 char field_1EB2A;
		 char field_1EB2B;
		 char field_1EB2C;
		 char field_1EB2D;
		 char field_1EB2E;
		 char field_1EB2F;
		 char field_1EB30;
		 char field_1EB31;
		 char field_1EB32;
		 char field_1EB33;
		 char field_1EB34;
		 char field_1EB35;
		 char field_1EB36;
		 char field_1EB37;
		 char field_1EB38;
		 char field_1EB39;
		 char field_1EB3A;
		 char field_1EB3B;
		 char Index;
		 short field_1EB3D;
		 char field_1eb3f;

};

//static_assert(sizeof(Menu) == 0x1EB40, "ERROR MENU STRUCT");
#endif // !__MENU_GAMES_H_

