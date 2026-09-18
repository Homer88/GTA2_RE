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

#pragma pack(push, 1) // ������������� ������������ �� 1 ����� (����������� ����������� ���������)
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
	// Level-file table: each record is a plain 0x100 (256) byte field, the
	// filename text (.gmp/.sty/.scr) sits at the very start of the record, i.e.
	// record i base = Menu+0xC9D4+i*0x100  (field start == text start).
	char LevelFile[36][0x100];	// 0xC9D4 (0x2400 bytes)
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

#pragma pack(pop) // ���������� ���������� ���������
//48932
//51�596-48 932
//51 972					 //125755
//FIXME
//static_assert(sizeof(Menu) == 125760, "ERROR MENU STRUCT");





// NOTE: 0x005EB160 is the address of the global Menu* pTABLE (4 bytes in .data).
// The real Menu instance lives on the heap (operator_new(0x1EB40) in FUN_00457830);
// its address is stored in that global cell. Access it through GetGameMenu()
// (cMenu.cpp) - never cast 0x005EB160 itself to Menu*, that reads the pointer cell
// as the struct and returns garbage (caused the GetRemapColour16 / PrintCentr crash).

Menu*  GetGameMenu();                 // returns *(Menu**)0x005EB160 (may be NULL)

//������� 
//char* __thiscall Menu::WCHARToChar(Menu* this, char* PlayerName)
//unsigned char* __stdcall WCHARToChar(Menu* pthis, wchar_t* PlayerName);
char  PlayerCheat(Menu* pthis, wchar_t* PlayerName);
//void  __stdcall SetPlayerNameFromMenu(Menu* pthis);
// Retail 0x00459540 is __thiscall: the real Menu* arrives in ECX.
void  __fastcall SetPlayerNameFromMenu(Menu* thisMenu);


//typedef short(__fastcall* LoadTextMenu)(Menu*);
// Retail Menu::LoadTextMenu is __thiscall; the Detour must forward the ORIGINAL
// this (Menu* in ECX) to the trampoline. Using the global gMenu is wrong here:
// during Menu::Menu() the global cell is still NULL (it is assigned only AFTER
// the constructor returns, in FUN_00457830: gMenu = Menu::Menu(pMenu)).
short  __fastcall   LoadTextMenu(Menu* thisMenu);


// Retail versions are __thiscall; the detours forward to the original trampolines
// (trace only - the retail behaviour is preserved).
char  __fastcall   LoadGame(Menu* thisMenu);              // Menu::LoadGame @0x00455C20
unsigned __int8  __fastcall   SaveGame(Menu* thisMenu);   // Menu::SaveGame @0x00455C90
char  __fastcall   MultiplayerMenu(Menu* thisMenu, void* _EDX, void* pPlayerName); // Menu::MultiplayerMenu @0x004565E0

// Menu::ProcessInput @0x00452050 - per-frame keyboard reader (DirectInput
// GetDeviceState -> Menu::Keys[256]). Hook logs every newly-pressed key and
// dumps the current menu page state (down to MenuEntry/S136 sub-classes).
void __fastcall HookProcessInput(Menu* thisMenu, void* _EDX);



#endif // !__MENU_GAMES_H_

