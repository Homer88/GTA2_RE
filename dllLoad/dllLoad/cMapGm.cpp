#include <malloc.h>
#include <iostream>
#include "cMapGm.h"
#include <string.h>
#include <Windows.h>

#include "Registry.h"
#include "DebugLogFile.h"

extern Registry gRegistry;

char* gGmpFile = (char*)0x00664590;
//char gGmpFile[24];

char* gStyleFile = (char*)0x006645A9;
//char gStyleFile[24];




int __stdcall LoadFileResurce(MapGm* pMapGm) {

	const int BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE] = { 0 };
	char Data[BUFFER_SIZE] = { 0 };

	char basePath[] = "data\\";

	char fileName[] = "MapGm.log";
	char func[] = "LoadFileResurce";
	char log[] = "info";
	
	writeFileLog(fileName,func , log, basePath);


	//Path mapname
	strncpy(buffer, basePath, BUFFER_SIZE - 1);
	buffer[BUFFER_SIZE - 1] = '\0';

	gRegistry.ReadKeyMap("mapname", (LPBYTE)Data, 256);
	Data[BUFFER_SIZE - 1] = '\0';

	size_t currentLen = strlen(buffer);
	size_t dataLen = strlen(Data);

	if (dataLen > 0) {
		// Проверяем, поместится ли строка в буфер
		if (currentLen + dataLen < BUFFER_SIZE - 1) {
			strcat(buffer, Data);
		}
		else {
			// Обработка переполнения: обрезаем до доступного размера
			size_t copyLen = BUFFER_SIZE - currentLen - 1;
			strncat(buffer, Data, copyLen);
			buffer[BUFFER_SIZE - 1] = '\0';
		}
	}

	// 4. Проверка и установка значения по умолчанию
	if (strcmp(buffer, basePath) == 0) {
		strncpy(buffer, "data\\jointmap.gmp", BUFFER_SIZE - 1);
		buffer[BUFFER_SIZE - 1] = '\0';
	}

	SetMapName(gMapGm,buffer);


	//Path stylename
	strncpy(buffer, basePath, BUFFER_SIZE - 1);
	buffer[BUFFER_SIZE - 1] = '\0';
	Data[0] = '\0';


	gRegistry.ReadKeyMap("stylename", (LPBYTE)Data, 256);

	currentLen = strlen(buffer);
	dataLen = strlen(Data);
	if (dataLen > 0) {
		// Проверяем, поместится ли строка в буфер
		if (currentLen + dataLen < BUFFER_SIZE - 1) {
			strcat(buffer, Data);
		}
		else {
			// Обработка переполнения: обрезаем до доступного размера
			size_t copyLen = BUFFER_SIZE - currentLen - 1;
			strncat(buffer, Data, copyLen);
			buffer[BUFFER_SIZE - 1] = '\0';
		}
	}

	if (strcmp(buffer, basePath) == 0) {
		strncpy(buffer, "data\\style.sty", BUFFER_SIZE - 1);
		buffer[BUFFER_SIZE - 1] = '\0';
	}

	SetStyleName(gMapGm, buffer);

	strncpy(buffer, basePath, BUFFER_SIZE - 1);
	buffer[BUFFER_SIZE - 1] = '\0';
	Data[0] = '\0';

	gRegistry.ReadKeyMap("scriptname", (LPBYTE)Data, 256);

	currentLen = strlen(buffer);
	dataLen = strlen(Data);
	if (dataLen > 0) {
		// Проверяем, поместится ли строка в буфер
		if (currentLen + dataLen < BUFFER_SIZE - 1) {
			strcat(buffer, Data);
		}
		else {
			// Обработка переполнения: обрезаем до доступного размера
			size_t copyLen = BUFFER_SIZE - currentLen - 1;
			strncat(buffer, Data, copyLen);
			buffer[BUFFER_SIZE - 1] = '\0';
		}
	}

	if (strcmp(buffer, basePath) == 0) {
		strncpy(buffer, "data\\q.scr", BUFFER_SIZE - 1);
		buffer[BUFFER_SIZE - 1] = '\0';
	}


	SetScriptName(gMapGm,buffer);

	gRegistry.ReadKeyMap("savename", (LPBYTE)Data, 256);
	//play
	char play[] = "play\\ ";
	SetSaveFile(gMapGm, play);
	//SetPlayerArena(gMapGm,0, 0);
	SetBonusStage(gMapGm, 0);
	Set_FUN_0045E4B0(gMapGm, 0);
	SetPlayerSlotSave(gMapGm, 0);
	SetBonus(gMapGm, 0);
	//memset(pMapGm->Arr10i, 0, sizeof(pMapGm->Arr10i));
	pMapGm->field_430 = 0;
	pMapGm->field_434 = 0;
	//pMapGm->field_438 = 0;
	pMapGm->field_43A = 0;
	Set_FUN_0045E630(gMapGm);
	return 0;

}


char* __stdcall GetMapName(MapGm* pMapGm) {
	
	return pMapGm->gmpFile;
}
void __stdcall SetMapName(MapGm* pMapGm,char* NameFile) {

	strncpy(pMapGm->gmpFile, NameFile, 255);
}

char* __stdcall GetStyleName(MapGm* pMapGm) {
	
	return pMapGm->styFile;
}

void __stdcall SetStyleName(MapGm* pMapGm, char* NameFile) {

	strncpy(pMapGm->styFile, NameFile, 255);
}

char* __stdcall GetScriptName(MapGm* pMapGm) {

	return pMapGm->sctiptFile;
}

void __stdcall SetScriptName(MapGm* pMapGm, char* NameFile) {

	strncpy(pMapGm->sctiptFile, NameFile, 255);
}

char* __stdcall GetSaveFile(MapGm* pMapGm) {

	return pMapGm->SaveFile;
}

void __stdcall SetSaveFile(MapGm* pMapGm, char* NameFile) {

	strncpy(pMapGm->SaveFile, NameFile, 255);
}

void __stdcall SetPlayerArena(MapGm* pMapGm, unsigned char *PlayerArena) {

	
	
		pMapGm->playerArena = *PlayerArena;
	
}

char __stdcall GetPlayerArena(MapGm* pMapGm) {

	return pMapGm->playerArena;
}

char __stdcall GetBonus(MapGm* pMapGm) {

	return pMapGm->Bonus;
}

int __stdcall ShowLimitFrame(MapGm* pMapGm) {

	return pMapGm->FragLimit;
}

void __stdcall SetBonusStage(MapGm* pMapGm, int *BonusStage) {

	pMapGm->bonusStage = *BonusStage;
}

void __stdcall DefauntSpecialTokens(MapGm* pMapGm) {

	pMapGm->SpecialTokens = 0 ;
}

int  __stdcall GetSpecialTokens(MapGm* pMapGm) {

	return pMapGm->SpecialTokens;
}
void __stdcall SetSpecialTokens(MapGm* pMapGm, int pSpecialTokens){

	pMapGm->SpecialTokens = pSpecialTokens;

}
void __stdcall IncrementSpecialTokens(MapGm* pMapGm) {

	++pMapGm->SpecialTokens;
}
void __stdcall Set_FUN_0045E4B0(MapGm* pMapGm, int Param) {

	pMapGm->field_0x402 = Param;
}
void __stdcall SetPlayerSlotSave(MapGm* pMapGm, int PlayerSlot) {

	pMapGm->PlayerSlotSave = PlayerSlot;
}
void  __stdcall SetBonus (MapGm* pMapGm, int Param) {

	pMapGm->Bonus = Param;
}
void __stdcall Set_FUN_0045E630(MapGm* pMapGm) {

}