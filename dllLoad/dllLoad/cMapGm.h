#ifndef ___MAPGM___H_
#define ___MAPGM___H_

#include <assert.h>

// Условие окончания игры (MapGm+0x43B, читает get_45E700). Размер 1 байт.
enum TYPE_GAME : unsigned char {
	FRAG_GAME  = 1,		// победа по фрагам (PlayerID >= FragLimit)
	POINT_GAME = 2,		// победа по очкам арены (PlayerArena)
	TAG_GAME   = 3		// TAG-режим
};

// Строка матрицы убийств: killPlayer[killerId].KillPlayerN = сколько раз killer убил игрока N.
// Пример: killPlayer[0].KillPlayer1 = 40 -> игрок 0 убил игрока 1 сорок раз
//         killPlayer[1].KillPlayer0 = 20 -> игрок 1 убил игрока 0 двадцать раз
struct KillPlayer {
	unsigned short KillPlayer0;		// убил игрока с ID 0
	unsigned short KillPlayer1;		// убил игрока с ID 1
	unsigned short KillPlayer2;
	unsigned short KillPlayer3;
	unsigned short KillPlayer4;
	unsigned short KillPlayer5;
};

// Таблица статистики последней игры (MapGm+0x408, 12 int = 0x30).
struct StatusLastGame {
	int p0;						// 0x408 [0]  (не отображается)
	int p1;						// 0x40C [1]
	int p2;						// 0x410 [2]
	int p3;						// 0x414 [3]  +$100 за машину
	int p4;						// 0x418 [4]  +$10 за машину
	int vehicles_hijacked;		// 0x41C [5]
	int civilians_run_down;		// 0x420 [6]
	int civilians_murdered;		// 0x424 [7]
	int lawmen_killed;			// 0x428 [8]
	int gang_members_killed;	// 0x42C [9]
	int auto_damage_cost;		// 0x430 [10] car_cst ($)
	int fugitive_factor;		// 0x434 [11] evsnrtg
};

struct MapGm{
	char gmpFile[256];					// 0x000
	char styFile[256];					// 0x100
	char sctiptFile[256];				// 0x200
	char SaveFile[256];					// 0x300
	unsigned char playerArena;			// 0x400
	char bonusStage;					// 0x401
	char field_0x402;					// 0x402
	unsigned char  PlayerSlotSave;		// 0x403
	char Bonus;							// 0x404
	char field_405;						// 0x405
	char field_406;						// 0x406
	char field_407;						// 0x407
	struct StatusLastGame StatusLastGame;	// 0x408 таблица статистики (12 int)
	short field_438;					// 0x438
	unsigned char field_43A;			// 0x43A
	TYPE_GAME EndGameFlag;				// 0x43B (1 байт) тип победы: get_45E700
	int FragLimit;						// 0x43C DWORD, ShowLimitFrame = порог победы
	unsigned char DataLast;				// 0x440
	unsigned char Best;					// 0x441
	unsigned char Index;				// 0x442 =6 при сбросе (Set_FUN_0045E630)
	unsigned char field_443;			// 0x443
	int Count;							// 0x444 счётчик секунд game-over (0..60), Get_field_444
	struct KillPlayer killPlayer[6];	// 0x448 матрица 6x6 [killer].KillPlayer[victim]
	unsigned short PlayerID[6];			// 0x490 фраги (IDA "PlayerID"), сравниваются с FragLimit
	int PlayerArena[6];					// 0x49C score, GetPlayerArena_0
	wchar_t NetworkNickName[6][16];		// 0x4B4 ники игроков (макс 16 wchar), SetString/GetPlayerName
	int SpecialTokens;					// 0x574
};

static_assert(sizeof(MapGm) == 0x578, "Size MapGm");

static MapGm* gMapGm = (MapGm*)0x005ec070;

int  __stdcall LoadFileResurce(MapGm* pMapGm);
char* __stdcall GetMapName(MapGm* pMapGm);
void __stdcall SetMapName(MapGm* pMapGm, char* NameFile);
char* __stdcall GetStyleName(MapGm* pMapGm);
void __stdcall SetStyleName(MapGm* pMapGm, char* NameFile);
char* __stdcall GetScriptName(MapGm* pMapGm);
void __stdcall SetScriptName(MapGm* pMapGm, char* NameFile);
char* __stdcall GetSaveFile(MapGm* pMapGm);
void __stdcall SetSaveFile(MapGm* pMapGm, char* NameFile);
void __stdcall SetPlayerArena(MapGm* pMapGm, unsigned char* PlayerArena);
char __stdcall GetPlayerArena(MapGm* pMapGm);
char __stdcall GetBonus(MapGm* pMapGm);
int __stdcall  ShowLimitFrame(MapGm* pMapGm);
void __stdcall SetBonusStage(MapGm* pMapGm, int *BonusStage);
void __stdcall DefauntSpecialTokens(MapGm* pMapGm);
int __stdcall  GetSpecialTokens(MapGm* pMapGm);
void __stdcall SetSpecialTokens(MapGm* pMapGm, int pSpecialTokens);
void __stdcall IncrementSpecialTokens(MapGm* pMapGm);
void __stdcall Set_FUN_0045E4B0(MapGm* pMapGm, int Param);
void __stdcall SetPlayerSlotSave(MapGm* pMapGm, int PlayerSlot);
void __stdcall SetBonus(MapGm* pMapGm, int Param);
void __stdcall Set_FUN_0045E630(MapGm* pMapGm);
void __stdcall SetScoresNative(MapGm* pMapGm, void* area);

#endif // !1
