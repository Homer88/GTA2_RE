//=====================================================================
// MapGm.cpp — модуль карты, восстановлен по дампу GTA2.exe.
// Байтовые смещения полей сверены с dump\Ghidra\gta2.exe.h (стр. 56854)
// и дизассемблером dump\Ghidra\gta2.exe.asm (sub_45E630).
//=====================================================================
#include "../global.h"

//---------------------------------------------------------------------
// 0x0045e630: MapGm::sub_45E630 — сброс настроек записи
//---------------------------------------------------------------------
void MapGm::sub_45E630()
{
	field_43B = 0;
	FragLimit = 0;
	field_440 = 0;
	field_441 = 0;
	field_442 = 6;

	// Обнуляем массивы строк, арен и области field_448 (6 итераций)
	wchar_t* dest = string_Arr0x16;
	int* arena = Arr10;
	short* ids = PlayerID;
	unsigned int* pp = (unsigned int*)&field26_448;
	for (int i = 0; i < 6; ++i)
	{
		// field_448[6*i .. 6*i+2] — три двойных слова
		pp[0] = 0; pp[1] = 0; pp[2] = 0;
		ids[0] = 0;
		arena[0] = 0;
		gWinApi.CopyWideString(dest, L"");
		ids += 1;
		arena += 1;
		pp += 3;
		dest += 16;
	}
}

//---------------------------------------------------------------------
// 0x0045e740: MapGm::sub_45E740 — единоразовая установка field23
//---------------------------------------------------------------------
void MapGm::sub_45E740(char value)
{
	if (field_442 == 6)
		field_442 = (unsigned char)value;
}

//---------------------------------------------------------------------
// 0x0045e770: MapGm::SetString — копирование строки имени игрока
//---------------------------------------------------------------------
void MapGm::SetString(unsigned short index, wchar_t* Source)
{
	wcsncpy(&string_Arr0x16[16 * index], Source, 16);
}

//---------------------------------------------------------------------
// 0x0045e7a0: MapGm::Get_45E7A0 — возврат указателя на строку имени
//---------------------------------------------------------------------
wchar_t* MapGm::Get_45E7A0(unsigned short index)
{
	return &string_Arr0x16[16 * index];
}

//---------------------------------------------------------------------
// 0x0045e830: MapGm::sub_45E830 — элемент массива field_448[6*a2+a3]
//---------------------------------------------------------------------
short MapGm::sub_45E830(unsigned char a2, unsigned char a3)
{
	// В дампе: PlayerID[(a3 & 0xff) + (a2 & 0xff) * 6 - 0x24].
	// Здесь a3 соответствует индексу строки, a2 — столбцу.
	return ((short*)&field26_448)[(a3 & 0xff) + (a2 & 0xff) * 6];
}

//---------------------------------------------------------------------
// 0x0045e8d0: MapGm::LoadFileResurce — загрузка имён файлов из реестра
//---------------------------------------------------------------------
int MapGm::LoadFileResurce()
{
	const int BUFFER_SIZE = 256;
	char buff[BUFFER_SIZE];
	char Data[BUFFER_SIZE];

	char* defMap = "data\\jointmap.gmp";
	char* defSty = "data\\style.sty";
	char* defScr = "data\\q.scr";

	// --- mapname ---
	strcpy(buff, "data\\");
	Data[0] = 0;
	gRegistry.ReadKeyMap("mapname", (LPBYTE)Data, 0x100u);
	strncat(buff, Data, BUFFER_SIZE - 1 - (int)strlen(buff));
	if (strcmp(buff, "data\\") == 0)
		strcpy(buff, defMap);
	SetMapName(buff);

	// --- stylename ---
	strcpy(buff, "data\\");
	Data[0] = 0;
	gRegistry.ReadKeyMap("stylename", (LPBYTE)Data, 0x100u);
	strncat(buff, Data, BUFFER_SIZE - 1 - (int)strlen(buff));
	if (strcmp(buff, "data\\") == 0)
		strcpy(buff, defSty);
	SetStyleName(buff);

	// --- scriptname ---
	strcpy(buff, "data\\");
	Data[0] = 0;
	gRegistry.ReadKeyMap("scriptname", (LPBYTE)Data, 0x100u);
	strncat(buff, Data, BUFFER_SIZE - 1 - (int)strlen(buff));
	if (strcmp(buff, "data\\") == 0)
		strcpy(buff, defScr);
	SetScripName(buff);

	// --- savename ---
	Data[0] = 0;
	gRegistry.ReadKeyMap("savename", (LPBYTE)Data, 0x100u);
	// В дампе: если результат равен gPlay, файл сохранения обнуляется
	if (Data[0] != 0)
		SetSaveFile(Data);
	else
		SetSaveFile("");

	// --- сброс настроек ---
	SetPlayerArea(0);
	SetBonusStage(0);
	SetGang(0);
	SetPlayerSlotSave(0);
	SetBonus(0);
	memset(Arr10, 0, sizeof(Arr10));
	field_430 = 0;
	field_434 = 0;
	field_438 = 0;
	field_43A = 0;
	sub_45E630();
	return 0;
}

//---------------------------------------------------------------------
// 0x0045ec20: MapGm::sub_45EC20 — копирование настроек игрока в MapGm
// Зависит от ещё не портированного класса Player (поле field_644,
// field_678, field_67c) и Game::GetPlayerSlotByIndex — заглушка.
//---------------------------------------------------------------------
void MapGm::sub_45EC20(void* player)
{
	// TODO: зависит от класса Player (ещё не портирован). В дампе:
	//   for i in 0..9: SetPlayerArena(i, a2->field_644[i]);
	//   sub_45E5B0(a2->field_678);
	//   field_434 = a2->field_67C;
	(void)player;
}

//---------------------------------------------------------------------
// 0x0045ec70: MapGm::sub_45EC70 — регистрация фрага игрока
// Зависит от Game/PlayerStats (не портированы) — заглушка.
//---------------------------------------------------------------------
void MapGm::sub_45EC70(unsigned char id, unsigned char a3)
{
	// TODO: зависит от Game::GetPlayerSlotByIndex и PlayerStats::sub_4B7580
	// (ещё не портированы). В дампе:
	//   ++field_448[6*id + a3];
	//   result = Game::GetPlayerSlotByIndex(gGame, id);
	//   if (id == a3) { if (PlayerID[id] > 0) { --PlayerID[id]; -money; } }
	//   else          { ++PlayerID[id]; +money; }
	(void)id;
	(void)a3;
}

//---------------------------------------------------------------------
// 0x00453a60: MapGm::DecodeBonusStage — декодирование сцены-бонуса
//---------------------------------------------------------------------
void MapGm::DecodeBonusStage(unsigned char bonusStage, unsigned char* playerArenaOut, unsigned char* out4)
{
	*playerArenaOut = bonusStage >> 4;
	*out4 = bonusStage & 15;
}

//=====================================================================
// Свободные обёртки для MissionManager (MissionManager.h)
//=====================================================================

int MapGm_GetMapName(MapGm* obj)        { return (int)obj->GetMapName(); }
int MapGm_GetStyleFile(MapGm* obj)      { return (int)obj->GetStyleFile(); }
int MapGm_GetScriptName(MapGm* obj)     { return (int)obj->GetScriptName(); }
int MapGm_GetPlayerArena(MapGm* obj)    { return obj->GetPlayerArena(); }
int MapGm_GetBonusStage(MapGm* obj)     { return obj->GetBonusStage(); }
int MapGm_GetGang(MapGm* obj)           { return obj->GetGang(); }
int MapGm_GetPlayerSlotSave(MapGm* obj) { return obj->GetPlayerSlotSave(); }
int MapGm_GetSpecialTokens(MapGm* obj)  { return obj->GetSpecialTokens(); }
int sub_476B10(MapGm* obj, int value)   { return obj->sub_476B10(value); }
int MapGm_sub_45E700(MapGm* obj)        { return obj->get_45E700(); }
