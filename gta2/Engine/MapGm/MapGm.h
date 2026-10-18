
#ifndef __MAP_GM_H_
#define __MAP_GM_H_

#include <string.h>

// Класс MapGm (модуль карты) — восстановлен по дампу GTA2.exe.
// Структура соответствует gta2.exe.h (dump\Ghidra, стр. 56854).
// Разметка массивов 0x490..0x4b4 уточнена по дизассемблеру ResetSettings
// (asm 0045e630): PlayerID (4*short) + PlayerArena (10*int) +
// string_Arr0x16 (6 * 16 wchar) — не пересекаются.
//
// В отличие от автоматической разметки Ghidra, где смежные байты
// названы field_XXX, здесь объединены только поля, реально используемые
// функциями дампа; остальные байты занимают неиспользуемые gap-массивы.

typedef enum TYPE_GAME {
	FRAG_GAME = 1,
	POINT_GAME = 2,
	TAG_GAME = 3
} TYPE_GAME;

typedef enum STATUS_ROW {
	
	 p0 = 0x0,
	 p1 = 0x1,
	 p2 = 0x2,
	 p3 = 0x3,
	 p4 = 0x4,
	 VehiclesHijacked = 0x5,
	 CiviliansRunDown = 0x6,
	 CiviliansMurdered = 0x7,
	 LawmenKilled = 0x8,
	 GangMembersKilled = 0x9,
  
}STATUS_ROW;

struct StatusLastGame {
	unsigned int value[10];
};
struct KillPlayer {   /* строка матрицы убийств: killPlayer[killer].KillPlayerN = сколько раз killer убил игрока N */
	unsigned short KillPlayerRow[6]; /* убил игрока с ID 0 */

};
extern wchar_t gNetworkNickName[16];
class MapGm {
public:
	// 0x000 .. 0x0ff — путь к карте (.gmp)
	char gmpFile[256];
	// 0x100 .. 0x1ff — путь к стилю (.sty)
	char styFile[256];
	// 0x200 .. 0x2ff — путь к скрипту (.scr)
	char sctiptFile[256];
	// 0x300 .. 0x3ff — путь к файлу сохранения
	char saveFile[256];
	// 0x400 .. 0x404 — байтовые настройки
	unsigned char playerArena;      // 0x400
	unsigned char BonusStage;      // 0x401
	unsigned char Gang;            // 0x402
	unsigned char PlayerSlotSave;  // 0x403
	unsigned char Bonus;           // 0x404
	// 0x405 .. 0x407 — не используются
	char gap405[3];
	// 0x408 .. 0x42f — массив очков/арен
	StatusLastGame StatusTable;                 // 0x408
	unsigned int AutoDamageCost;
	unsigned int FugitiveFactor;

	// 0x438 .. 0x443 — настройки фрагов и режима
	short field_438;               // 0x438  (field15; SetField15/GetField15)
	unsigned char field_43A;       // 0x43a  (field16)
	unsigned char EndGameFlag;       // 0x43b  (field17; get_45E700)
	int FragLimit;                 // 0x43c  (СЃС‡С‘С‚С‡РёРє/Р»РёРјРёС‚ С„СЂР°РіРѕРІ; ShowLimitFrame)
	unsigned char DataLast;       // 0x440  (field21)
	unsigned char Best;       // 0x441  (field22)
	unsigned char Index;       // 0x442  (field23; SetField23/Get_45E760)  РІРѕР·РјРѕР¶РЅРѕ РєРѕР»РёС‡РµСЃС‚РІРѕ РёРіСЂРѕРєРѕРІ
	// 0x443 .. 0x447 вЂ” РІС‹СЂР°РІРЅРёРІР°РЅРёРµ
	char gap443;
	int Count;                 //  Р’СЂРµРјСЏ РґРѕ РѕРєРЅС‡Р°РЅРёРµ РёРіСЂС‹ 0x444  (field25; Get_field_444)
	// 0x448 .. 0x48f вЂ” СѓРєР°Р·Р°С‚РµР»СЊ/Р·Р°СЂРµР·РµСЂРІРёСЂРѕРІР°РЅРЅР°СЏ РѕР±Р»Р°СЃС‚СЊ
	KillPlayer killPlayer[6];             // 0x448 (Р±Р°Р·Р° РѕР±Р»Р°СЃС‚Рё 3*6 dword)
	// 0x490 .. 0x497 вЂ” ID РёРіСЂРѕРєРѕРІ (РїРѕ 4)
	short PlayerID[6];             // 0x490
	// 0x498 .. 0x4af вЂ” Р°СЂРµРЅС‹/РѕС‡РєРё РёРіСЂРѕРєРѕРІ (РїРѕ 4)
	int PlayerArena[6];            // 0x49РЎ
	// 0x4b0 .. 0x573 вЂ” 6 СЃС‚СЂРѕРє РїРѕ 16 wchar (РёРјРµРЅР° РёРіСЂРѕРєРѕРІ)
	wchar_t NetworkNickName[6][16];// 0x4b4
	// 0x574 .. 0x578 вЂ” РєРѕР»РёС‡РµСЃС‚РІРѕ SpecialTokens
	int SpecialTokens;             // 0x574

	MapGm();
	~MapGm();

	// --- СЃРµС‚С‚РµСЂС‹ РёРјС‘РЅ С„Р°Р№Р»РѕРІ ---
	char* SetMapName(char* Source);
	char* SetStyleName(char* Source);
	char* SetScripName(char* Source);
	char* SetSaveFile(char* Source);

	void SetPlayerArena(char value);
	void SetBonusStage(char value);
	void SetGang(char value);
	void SetPlayerSlotSave(char value);
	void SetBonus(char value);

	// --- РіРµС‚С‚РµСЂС‹ РёРјС‘РЅ С„Р°Р№Р»РѕРІ ---
	char* GetMapName();
	char* GetStyleFile();
	char* GetScriptName();
	char* GetSaveFile();

	unsigned char GetPlayerArena();
	unsigned char GetBonusStage();
	unsigned char GetGang();
	unsigned char GetPlayerSlotSave();
	unsigned char GetBonus();

	// 0x0045e570/ запись/чтение Arr10[i]
	void SetPlayerArena(unsigned char index, int value);
	// 0x0045e590
	unsigned int GetAreaData(unsigned char index);

	// 0x0045e5b0
	void SetAutoDamageCost(int value);// (gm) старый: SetCarCost -> SetAwardValue1
	// 0x0045e5c0
	int GetAutoDamageCost();
	
	//045e5d0
	void SetFugitiveFactor(unsigned int value);
	// 0x0045e5e0
	unsigned int  GetFugitiveFactor();
	// 0x0045e5f0/0x0045e600 вЂ” field15_0x438
	void SetField15(short value) { field_438 = value; }
	short GetField15() { return field_438; }

	// 0x0045e610/0x0045e620 вЂ” field16_0x43a
	void SetField16(char value) { field_43A = (unsigned char)value; }
	char Get_45E620() { return (char)field_43A; }

	// 0x0045e630 вЂ” СЃР±СЂРѕСЃ РЅР°СЃС‚СЂРѕРµРє Р·Р°РїРёСЃРё (РёРјРµРЅР°/С„СЂР°РіРё/СЃС‚СЂРѕРєРё)
	void ResetSettings();

	// 0x0045e700
	char GetEndGameFlag();

	// 0x0045e710 
	int GetLimitFrag();

	// 0x0045e720
	unsigned char GetDataLast();
	// 0x0045e730
	char GetBest();

	// 0x0045e740 //Player Max Count
	void SetIndex(char value);
	// 0x0045e760
	char GetIndex();

	// 0x0045e770/0x0045e7a0 вЂ” СЃС‚СЂРѕРєРё РёРјС‘РЅ
	void SetNetworkNickName(unsigned short index, wchar_t* Source);
	// 0x0045e7a0
	wchar_t* GetNetworkNickName(unsigned short index);

	// 0x0045e7c0 вЂ” PlayerArena[i] += delta
	void AddScore(unsigned char index, int value);

	// 0x0045e7f0 вЂ” PlayerArena[i] / PlayerID[i]
	int GetPlayerArena(unsigned char id);
	// 0x0045e810
	short GetPlayerID(unsigned char id);

	// 0x0045e830 вЂ” field_448[6*a2 + a3] (СЃС‚РёР»РёР·РѕРІР°РЅРѕ РїРѕРґ PlayerID)
	unsigned short GetScoreRow(unsigned char value, unsigned char row);

	// 0x0045e8d0 вЂ” Р·Р°РіСЂСѓР·РєР° РёРјС‘РЅ С„Р°Р№Р»РѕРІ РёР· СЂРµРµСЃС‚СЂР° + СЃР±СЂРѕСЃ РЅР°СЃС‚СЂРѕРµРє
	int LoadFileResurce();

	// 0x0045ec20 вЂ” РєРѕРїРёСЂРѕРІР°РЅРёРµ РЅР°СЃС‚СЂРѕРµРє РёР· Player (Р·Р°РІРёСЃРёС‚ РѕС‚ Player)
	void LoadFromBuffer(void* player);

	// 0x0045ec70 вЂ” СЂРµРіРёСЃС‚СЂР°С†РёСЏ С„СЂР°РіР° РёРіСЂРѕРєР° (Р·Р°РІРёСЃРёС‚ РѕС‚ Player/PlayerStats)
	void RegisterKill(unsigned char id, unsigned char a3);

	// SpecialTokens
	void SetSpecialTokensDefault();
	int GetSpecialTokens();
	// 0x00476b10 вЂ” С‚Рѕ Р¶Рµ, С‡С‚Рѕ SetSpecialTokens (РІРѕР·РІСЂР°С‰Р°РµС‚ value)
	void SetSpecialTokens(int value);
	void IncrementSpecialTokens();

	// 0x00453a40 вЂ” РєРѕРґРёСЂРѕРІР°РЅРёРµ bonus stage: (playerArea << 4) | param2
	int EncodeBonusStage(unsigned char param2) { return (playerArena << 4) | param2; }
	// 0x00453a60 вЂ” РґРµРєРѕРґРёСЂРѕРІР°РЅРёРµ bonus stage
	void DecodeBonusStage(unsigned char bonusStage, unsigned char* playerArenaOut, unsigned char* out4);

	// 0x00461dc0 вЂ” Get_field_444
	int GetCount();

   
};
extern MapGm* gMapGm;
#endif //__MAP_GM_H_