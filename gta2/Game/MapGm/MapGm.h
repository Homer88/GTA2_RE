#ifndef __MAP_GM_H_
#define __MAP_GM_H_

// Класс MapGm (модуль карты) — восстановлен по дампу GTA2.exe.
// Структура соответствует gta2.exe.h (dump\Ghidra, стр. 56854).
// Разметка массивов 0x490..0x4b4 уточнена по дизассемблеру sub_45E630
// (asm 0045e630): PlayerID (4*short) + PlayerArena (10*int) +
// string_Arr0x16 (6 * 16 wchar) — не пересекаются.
//
// В отличие от автоматической разметки Ghidra, где смежные байты
// названы field_XXX, здесь объединены только поля, реально используемые
// функциями дампа; остальные байты занимают неиспользуемые gap-массивы.

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
	unsigned char playerArea;      // 0x400
	unsigned char BonusStage;      // 0x401
	unsigned char Gang;            // 0x402
	unsigned char PlayerSlotSave;  // 0x403
	unsigned char Bonus;           // 0x404
	// 0x405 .. 0x407 — не используются
	char gap405[3];
	// 0x408 .. 0x42f — массив очков/арен
	int Arr10[10];                 // 0x408
	// 0x430, 0x434 — два значения (достижения/фраги)
	int field_430;                 // 0x430
	int field_434;                 // 0x434
	// 0x438 .. 0x443 — настройки фрагов и режима
	short field_438;               // 0x438  (field15; sub_45E5F0/sub_45E600)
	unsigned char field_43A;       // 0x43a  (field16)
	unsigned char field_43B;       // 0x43b  (field17; get_45E700)
	int FragLimit;                 // 0x43c  (счётчик/лимит фрагов; ShowLimitFrame)
	unsigned char field_440;       // 0x440  (field21)
	unsigned char field_441;       // 0x441  (field22)
	unsigned char field_442;       // 0x442  (field23; sub_45E740/Get_45E760)
	// 0x443 .. 0x447 — выравнивание
	char gap443[5];
	int field_444;                 // 0x444  (field25; Get_field_444)
	// 0x448 .. 0x48f — указатель/зарезервированная область
	void* field26_448;             // 0x448 (база области 3*6 dword)
	char gap44C[0x44];             // 0x44c .. 0x48f
	// 0x490 .. 0x497 — ID игроков (по 4)
	short PlayerID[4];             // 0x490
	// 0x498 .. 0x4af — арены/очки игроков (по 4)
	int PlayerArena[4];            // 0x498
	// 0x4b0 .. 0x573 — 6 строк по 16 wchar (имена игроков)
	wchar_t string_Arr0x16[6 * 16];// 0x4b0
	// 0x574 .. 0x578 — количество SpecialTokens
	int SpecialTokens;             // 0x574

	MapGm();
	~MapGm();

	// --- сеттеры имён файлов ---
	char* SetMapName(char* Source) { return strncpy(gmpFile, Source, 0xFFu); }
	char* SetStyleName(char* Source) { return strncpy(styFile, Source, 0xFFu); }
	char* SetScripName(char* Source) { return strncpy(sctiptFile, Source, 0xFFu); }
	char* SetSaveFile(char* Source) { return strncpy(saveFile, Source, 0xFFu); }

	void SetPlayerArea(char value) { playerArea = (unsigned char)value; }
	void SetBonusStage(char value) { BonusStage = (unsigned char)value; }
	void SetGang(char value) { Gang = (unsigned char)value; }
	void SetPlayerSlotSave(char value) { PlayerSlotSave = (unsigned char)value; }
	void SetBonus(char value) { Bonus = (unsigned char)value; }

	// --- геттеры имён файлов ---
	char* GetMapName() { return gmpFile; }
	char* GetStyleFile() { return styFile; }
	char* GetScriptName() { return sctiptFile; }
	char* GetSaveFile() { return saveFile; }

	unsigned char GetPlayerArena() { return playerArea; }
	unsigned char GetBonusStage() { return BonusStage; }
	unsigned char GetGang() { return Gang; }
	unsigned char GetPlayerSlotSave() { return PlayerSlotSave; }
	unsigned char GetBonus() { return Bonus; }

	// 0x0045e570/0x0045e590 — запись/чтение Arr10[i]
	void SetPlayerArena(unsigned char index, int value) { Arr10[index & 0xff] = value; }
	int sub_45E590(unsigned char index) { return Arr10[index]; }

	// 0x0045e5b0/0x0045e5c0/0x0045e5e0 — field_430 / field_434
	void sub_45E5B0(int value) { field_430 = value; }
	int Get_45E5C0() { return field_430; }
	int Get_45E5E0() { return field_434; }

	// 0x0045e5f0/0x0045e600 — field15_0x438
	void sub_45E5F0(short value) { field_438 = value; }
	short sub_45E600() { return field_438; }

	// 0x0045e610/0x0045e620 — field16_0x43a
	void sub_45E610(char value) { field_43A = (unsigned char)value; }
	char Get_45E620() { return (char)field_43A; }

	// 0x0045e630 — сброс настроек записи (имена/фраги/строки)
	void sub_45E630();

	// 0x0045e700 — field17_0x43b
	char get_45E700() { return (char)field_43B; }

	// 0x0045e710 — ShowLimitFrame (FragLimit, dword)
	int ShowLimitFrame() { return FragLimit; }

	// 0x0045e720/0x0045e730 — field21/field22
	unsigned char Get_45E720() { return field_440; }
	char Get_45E730() { return (char)field_441; }

	// 0x0045e740/0x0045e760 — field23_0x442 (устанавливается один раз)
	void sub_45E740(char value);
	char Get_45E760() { return (char)field_442; }

	// 0x0045e770/0x0045e7a0 — строки имён
	void SetString(unsigned short index, wchar_t* Source);
	wchar_t* Get_45E7A0(unsigned short index);

	// 0x0045e7c0 — PlayerArena[i] += delta
	void sub_45E7C0(unsigned char index, int delta) { PlayerArena[index & 0xff] += delta; }

	// 0x0045e7f0/0x0045e810 — PlayerArena[i] / PlayerID[i]
	int GetPlayerArena_0(unsigned char id) { return PlayerArena[id]; }
	short GetPlayerID(unsigned char id) { return PlayerID[id]; }

	// 0x0045e830 — field_448[6*a2 + a3] (стилизовано под PlayerID)
	short sub_45E830(unsigned char a2, unsigned char a3);

	// 0x0045e8d0 — загрузка имён файлов из реестра + сброс настроек
	int LoadFileResurce();

	// 0x0045ec20 — копирование настроек из Player (зависит от Player)
	void sub_45EC20(void* player);

	// 0x0045ec70 — регистрация фрага игрока (зависит от Player/PlayerStats)
	void sub_45EC70(unsigned char id, unsigned char a3);

	// SpecialTokens
	void SetSpecialTokensDefault() { SpecialTokens = 0; }
	int GetSpecialTokens() { return SpecialTokens; }
	void SetSpecialTokens(int value) { SpecialTokens = value; }
	void IncrementSpecialTokens() { ++SpecialTokens; }
	// 0x00476b10 — то же, что SetSpecialTokens (возвращает value)
	int sub_476B10(int value) { SpecialTokens = value; return value; }

	// 0x00453a40 — кодирование bonus stage: (playerArea << 4) | param2
	int sub_453A40(unsigned char param2) { return (playerArea << 4) | param2; }
	// 0x00453a60 — декодирование bonus stage
	void DecodeBonusStage(unsigned char bonusStage, unsigned char* playerArenaOut, unsigned char* out4);

	// 0x00461dc0 — Get_field_444
	int Get_field_444() { return field_444; }
};

// Свободные обёртки для MissionManager (объявлены в MissionManager.h)
int   MapGm_GetMapName(MapGm*);
int   MapGm_GetStyleFile(MapGm*);
int   MapGm_GetScriptName(MapGm*);
int   MapGm_GetPlayerArena(MapGm*);
int   MapGm_GetBonusStage(MapGm*);
int   MapGm_GetGang(MapGm*);
int   MapGm_GetPlayerSlotSave(MapGm*);
int   MapGm_GetSpecialTokens(MapGm*);
int   sub_476B10(MapGm*, int);
int   MapGm_sub_45E700(MapGm*);

#endif //__MAP_GM_H_
