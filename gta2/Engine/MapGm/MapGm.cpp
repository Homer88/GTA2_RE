//=====================================================================
// MapGm.cpp — модуль карты, восстановлен по дампу GTA2.exe.
// Байтовые смещения полей сверены с dump\Ghidra\gta2.exe.h (стр. 56854)
// и дизассемблером dump\Ghidra\gta2.exe.asm (ResetSettings).
//=====================================================================
#include "../../Engine/ultil/WinApi.h"
#include "../../Engine/Registry/Registry.h"
#include "MapGm.h"
extern WinApi *gWinApi;
MapGm *gMapGm;
wchar_t gNetworkNickName[16];
// TODO: заглушки - реализовать (объявлены в MapGm.h)




MapGm::MapGm()
{
	// 0x0045e860: инициализация полей по дампу (sub_45E860, вызывается сразу после меню)
	gmpFile[0]    = 0;
	styFile[0]    = 0;
	sctiptFile[0] = 0;
	saveFile[0]   = 0;
	playerArena   = 0;
	BonusStage    = 0;
	Gang          = 0;
	PlayerSlotSave = 0;
	Bonus         = 0;
	field_438     = 0;
	field_43A     = 0;
	ResetSettings();
}
MapGm::~MapGm()
{
}


// --- СЃРµС‚С‚РµСЂС‹ РёРјС‘РЅ С„Р°Р№Р»РѕРІ ---
char* MapGm::SetMapName(char* Source) { 
	return strncpy(this->gmpFile, Source, 0xFFu); 
}
char* MapGm::SetStyleName(char* Source) { 
	return strncpy(this->styFile, Source, 0xFFu); 
}
char* MapGm::SetScripName(char* Source) {
	return strncpy(this->sctiptFile, Source, 0xFFu); 
}
char* MapGm::SetSaveFile(char* Source) { 
	return strncpy(this->saveFile, Source, 0xFFu); 
}

void MapGm::SetPlayerArena(char value) { 
	this->playerArena = (unsigned char)value; 
}
void MapGm::SetBonusStage(char value) { 
		this->    BonusStage = (unsigned char)value; 
}
void MapGm::SetGang(char value) { 
		this->Gang = (unsigned char)value; 
}
void MapGm::SetPlayerSlotSave(char value) {
			this->PlayerSlotSave = (unsigned char)value; 
}
void MapGm::SetBonus(char value) { 
		this->Bonus = (unsigned char)value;
}
// --- РіРµС‚С‚РµСЂС‹ РёРјС‘РЅ С„Р°Р№Р»РѕРІ ---
char* MapGm::GetMapName() { 
	return this->gmpFile; 
}
char* MapGm::GetStyleFile() { 
	return this->styFile; 
}
char* MapGm::GetScriptName() { 
	return this->sctiptFile; 
}
char* MapGm::GetSaveFile() { 
	return this->saveFile; 
}

unsigned char MapGm::GetPlayerArena() { 
	return this->playerArena; 
}
unsigned char MapGm::GetBonusStage() { 
	return this->BonusStage; 
}
unsigned char MapGm::GetGang() { 
	return this->Gang; 
}
unsigned char MapGm::GetPlayerSlotSave() { 
	return this->PlayerSlotSave; 
}
unsigned char MapGm::GetBonus() { 
	return this->Bonus; 
}
int MapGm::GetCount() { 
	return this->Count; 
}
void MapGm::SetAutoDamageCost(int value) { 
	this->AutoDamageCost = value; 
}
int MapGm::GetAutoDamageCost() {
	return this->AutoDamageCost; 
}
void MapGm::SetFugitiveFactor(unsigned int value) {
	this->FugitiveFactor = value;
}
unsigned int  MapGm::GetFugitiveFactor() {
	return this->FugitiveFactor;
}

char MapGm::GetEndGameFlag() {
	return this->EndGameFlag;
}

int MapGm::GetLimitFrag() { 
	return this->FragLimit; 
}

unsigned char MapGm::GetDataLast() {
	return this->DataLast; 
}
char MapGm::GetBest() { 
	return this->Best; 
}
char MapGm::GetIndex() {
	return this->Index; 
}

void  MapGm::AddScore(unsigned char index, int value){ 
	this->PlayerArena[index] += value; 
}

int MapGm::GetPlayerArena(unsigned char id) {
	return this->PlayerArena[id]; 
}


short MapGm::GetPlayerID(unsigned char id) {
	return this->PlayerID[id]; 
}
void  MapGm::SetPlayerArena(unsigned char index, int value) {
		this->StatusTable.value[index] = value; 
}

unsigned int MapGm::GetAreaData(unsigned char index) {
	return this->StatusTable.value[index]; }
//---------------------------------------------------------------------
// 0x0045e630: MapGm::ResetSettings — сброс настроек записи
//---------------------------------------------------------------------
void MapGm::ResetSettings()
{
	this->EndGameFlag = 0;
	this->FragLimit = 0;
	this->DataLast = 0;
	this->Best = 0;
	this->Index = 6;

	// Обнуляем массивы строк, арен и области field_448 (6 итераций)
	wchar_t* dest = this->NetworkNickName[0];
	int* arena = this->PlayerArena;
	short* ids = PlayerID;
	KillPlayer* pp = this->killPlayer;
	for (int i = 0; i < 6; ++i)
	{
		// field_448[6*i .. 6*i+2] — три двойных слова
		//pp[0] = 0; pp[1] = 0; pp[2] = 0;
		ids[0] = 0;
		arena[0] = 0;
		gWinApi->CopyWideString(dest, L"");
		ids += 1;
		arena += 1;
		pp += 3;
		dest += 16;
	}
}

//---------------------------------------------------------------------
// 0x0045e740: MapGm::SetField23 — единоразовая установка field23
//---------------------------------------------------------------------
void MapGm::SetIndex(char value)
{
	if (this->Index == 6)
		this->Index = (unsigned char)value;
}

//---------------------------------------------------------------------
// 0x0045e770: MapGm::SetString — копирование строки имени игрока
//---------------------------------------------------------------------
void MapGm::SetNetworkNickName(unsigned short index, wchar_t* Source)
{
	wcsncpy(this->NetworkNickName[index], Source, 16);
}

//---------------------------------------------------------------------
// 0x0045e7a0: MapGm::Get_45E7A0 — возврат указателя на строку имени
//---------------------------------------------------------------------
wchar_t* MapGm::GetNetworkNickName(unsigned short index)
{
	return this->NetworkNickName[index];
}

//---------------------------------------------------------------------
// 0x0045e830: MapGm::GetScoreRow — элемент массива field_448[6*a2+a3]
//---------------------------------------------------------------------
unsigned short MapGm::GetScoreRow(unsigned char value, unsigned char row)
{
	// В дампе: PlayerID[(a3 & 0xff) + (a2 & 0xff) * 6 - 0x24].
	// Здесь a3 соответствует индексу строки, a2 — столбцу.
	return this->killPlayer[value].KillPlayerRow[row];
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
	gRegistry->ReadKeyMap("mapname", (LPBYTE)Data, 0x100u);
	strncat(buff, Data, BUFFER_SIZE - 1 - (int)strlen(buff));
	if (strcmp(buff, "data\\") == 0)
		strcpy(buff, defMap);
	SetMapName(buff);

	// --- stylename ---
	strcpy(buff, "data\\");
	Data[0] = 0;
	gRegistry->ReadKeyMap("stylename", (LPBYTE)Data, 0x100u);
	strncat(buff, Data, BUFFER_SIZE - 1 - (int)strlen(buff));
	if (strcmp(buff, "data\\") == 0)
		strcpy(buff, defSty);
	this->SetStyleName(buff);

	// --- scriptname ---
	strcpy(buff, "data\\");
	Data[0] = 0;
	gRegistry->ReadKeyMap("scriptname", (LPBYTE)Data, 0x100u);
	strncat(buff, Data, BUFFER_SIZE - 1 - (int)strlen(buff));
	if (strcmp(buff, "data\\") == 0)
		strcpy(buff, defScr);
	this->SetScripName(buff);

	// --- savename ---
	Data[0] = 0;
	gRegistry->ReadKeyMap("savename", (LPBYTE)Data, 0x100u);
	// В дампе: если результат равен gPlay, файл сохранения обнуляется
	if (Data[0] != 0)
		this->SetSaveFile(Data);
	else
		this->SetSaveFile("");

	// --- сброс настроек ---
	this->SetPlayerArena(0);
	this->SetBonusStage(0);
	this->SetGang(0);
	this->SetPlayerSlotSave(0);
	this->SetBonus(0);


	this->field_438 = 0;
	this->field_43A = 0;
	this->ResetSettings();
	return 0;
}

//---------------------------------------------------------------------
// 0x0045ec20: MapGm::LoadFromBuffer — копирование настроек игрока в MapGm
// Зависит от ещё не портированного класса Player (поле field_644,
// field_678, field_67c) и Game::GetPlayerSlotByIndex — заглушка.
//---------------------------------------------------------------------
void MapGm::LoadFromBuffer(void* player)
{
	// TODO: зависит от класса Player (ещё не портирован). В дампе:
	//   for i in 0..9: SetPlayerArena(i, a2->field_644[i]);
	//   SetCarCost(a2->field_678);
	//   field_434 = a2->field_67C;
	(void)player;
}

//---------------------------------------------------------------------
// 0x0045ec70: MapGm::RegisterKill — регистрация фрага игрока
// Зависит от Game/PlayerStats (не портированы) — заглушка.
//---------------------------------------------------------------------
void MapGm::RegisterKill(unsigned char id, unsigned char a3)
{
	// TODO: зависит от Game::GetPlayerSlotByIndex и PlayerStats::SetMoney
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

//int MapGm_GetMapName(MapGm* obj)        { return (int)obj->GetMapName(); }
//int MapGm_GetStyleFile(MapGm* obj)      { return (int)obj->GetStyleFile(); }
//int MapGm_GetScriptName(MapGm* obj)     { return (int)obj->GetScriptName(); }
//int MapGm_GetPlayerArena(MapGm* obj)    { return obj->GetPlayerArena(); }
//int MapGm_GetBonusStage(MapGm* obj)     { return obj->GetBonusStage(); }
//int MapGm_GetGang(MapGm* obj)           { return obj->GetGang(); }
//int MapGm_GetPlayerSlotSave(MapGm* obj) { return obj->GetPlayerSlotSave(); }
//int MapGm_GetSpecialTokens(MapGm* obj)  { return obj->GetSpecialTokens(); }
//int sub_476B10(MapGm* obj, int value)   { return obj->sub_476B10(value); }
//int MapGm_sub_45E700(MapGm* obj)        { return obj->get_45E700(); }
