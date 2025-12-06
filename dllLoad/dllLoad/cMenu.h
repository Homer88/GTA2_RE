#ifndef __MENU_GAMES_H_
#define __MENU_GAMES_H_

#include <assert.h>
#include <dinput.h>

#include "cMenuPage.h"
#include "cS139.h"
#include "cS138.h" 
#include "cPlayerName.h"
#include "cKeyState.h"
#include "cPlayer.h"


enum MenuPic :char {
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
	PlayerNamePicture = 10u,
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

#pragma pack(push, 1) // устанавливает выравнивание по 1 байту (максимально упакованная структура)
struct Menu{
	
	LPDIRECTINPUTA DirectInput;
	LPDIRECTINPUTDEVICEA InputDevice;
	char Keys[256];
	int FrontendState;
	char KeyboardAcquired;
	char FrontendKeysEnabled;
	char field_10E;
	char field_10F;
	int State;
	int field_114;
	int field_118;
	unsigned short FontStyle;
	unsigned short Page;
	short Filderer0x120;
	MenuPage pMenuPage[17];
	//wchar_t ppPlayerName[9]; //0xC98C
	wchar_t* pPlayerName;
	void* field_C990;
	void* field_C994;
	void* field_C998;
	__int16 field_C99C;
	char Length;
	char field_C99F;
	__int16 Key;
	__int16 field_C9A2;
	wchar_t MenuItems[9];
	unsigned char CurrentMenuItemsIndex;
	char field_C9B7;
	KeyState NewKeyState;
	KeyState OldKeyState;
	char field_C9C6;
	char field_C9C7;
	int TimeToWaitDemoStart;
	char FrameCounter;
	bool isChaet;
	char field_C9CE;
	char field_C9CF;
	int TimeToWaitBeforeDemoStart;
	__int16 gapC9D4;
	char field_C9D6[50];
	char field_CA08[10];
	char field_CA12;
	char field_CA13;
	__int16 gapCA13;
	char field_CA15[200];
	char field_CADD[50];
	char field_CB0F[50];
	char field_CB41[50];
	char field_CB72[50];
	char field_CBA4[50];
	char field_CBD6[50];
	char field_CC08[50];
	char field_CC3A[50];
	char field_CC6C[50];
	char field_CC9E[50];
	char field_CCD0[50];
	char field_EDB6[50];
	char field_CD36[1000];
	char field_D11E[1000];
	char field_D506[500];
	char field_D6FA[500];
	char field_D8EE[500];
	char field_DAE2[500];
	char field_DCD6[500];
	char field_DECA[1000];
	char field_E2B2[1000];
	char field_E69A[1000];
	char field_EA82[500];
	char field_EC76[200];
	char field_ED3E[100];
	char field_EDA2[50];
	S138 S138[8];
	MenuPic MenuPic;
	char field_EDF5;
	__int16 field_EDF6;
	char field_EDF8;
	char field_EDF9;
	S139 S139;
	__int16 field_1EB1C;
	char field_1EB1E;
	char field_1EB1F;
	void* Player;// Player * Player;
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
	char A1EB3A;
	char AAAA;
	char field_1EB3C;
	__int16 AAA;
	char field_1EB3F;
};

#pragma pack(pop) // возвращает предыдущие настройки
//48932
//51 596-48 932
//51 972					 //125755
//FIXME
//static_assert(sizeof(Menu) == 125760, "ERROR MENU STRUCT");





extern  Menu* gMenu;


//функции 
//char* __thiscall Menu::WCHARToChar(Menu* this, char* PlayerName)
//unsigned char* __stdcall WCHARToChar(Menu* pthis, wchar_t* PlayerName);
char  PlayerCheat(Menu* pthis, wchar_t* PlayerName);
//void  __stdcall sub_459540(Menu* pthis);
void  __stdcall sub_459540();



#endif // !__MENU_GAMES_H_

