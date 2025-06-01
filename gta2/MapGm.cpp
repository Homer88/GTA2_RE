#include"Global.h"
//#include "MapGm.h"



MapGm gMapGm;

/*MapGm::MapGm(){
	///FIXME
	}

MapGm::~MapGm(){
	
}*/



int MapGm::LoadFileResurce(){
	const int BUFFER_SIZE=256;
	char buffer[BUFFER_SIZE]={0};
	char Data[BUFFER_SIZE]={0};
	char* basePath="data\\";
	
	
	
	
	//Path mapname
	strncpy(buffer,basePath, BUFFER_SIZE-1);
	buffer[BUFFER_SIZE-1]='\0';
	
	gRegistry.ReadKeyMap("mapname",(LPBYTE)Data,256);
	Data[BUFFER_SIZE-1]='\0';
	
	size_t currentLen = strlen(buffer);
	size_t dataLen = strlen(Data);
	 if (dataLen > 0) {
		 // Проверяем, поместится ли строка в буфер
		 if (currentLen + dataLen < BUFFER_SIZE-1) {
			 strcat(buffer, Data);
		 } else {
			 // Обработка переполнения: обрезаем до доступного размера
			 size_t copyLen = BUFFER_SIZE - currentLen - 1 ;
			 strncat(buffer, Data, copyLen);
			 buffer[BUFFER_SIZE-1] = '\0';
		 }
	 }
	
	// 4. Проверка и установка значения по умолчанию
	if (strcmp(buffer, basePath) == 0) {
		strncpy(buffer, "data\\jointmap.gmp", BUFFER_SIZE-1);
		buffer[BUFFER_SIZE-1] = '\0';
	}
	
	this->SetMapName(buffer);
	
	
	//Path stylename
	strncpy(buffer,basePath, BUFFER_SIZE-1);
	buffer[BUFFER_SIZE-1]='\0';
	Data[0]='\0';

	
	gRegistry.ReadKeyMap("stylename",(LPBYTE)Data,256);
	
	currentLen = strlen(buffer);
	dataLen = strlen(Data);
	if (dataLen > 0) {
		// Проверяем, поместится ли строка в буфер
		if (currentLen + dataLen < BUFFER_SIZE-1) {
			strcat(buffer, Data);
		} else {
			// Обработка переполнения: обрезаем до доступного размера
			size_t copyLen = BUFFER_SIZE - currentLen - 1 ;
			strncat(buffer, Data, copyLen);
			buffer[BUFFER_SIZE-1] = '\0';
		}
	}
	
	if (strcmp(buffer, basePath) == 0) {
		strncpy(buffer, "data\\style.sty", BUFFER_SIZE - 1);
		buffer[BUFFER_SIZE - 1] = '\0';
	}
	
	this->SetStyleName(buffer);
	
	
	
	
	
	
	
	strncpy(buffer,basePath, BUFFER_SIZE-1);
	buffer[BUFFER_SIZE-1]='\0';
	Data[0]='\0';
	
	gRegistry.ReadKeyMap("scriptname",(LPBYTE)Data,256);
	
	currentLen = strlen(buffer);
	dataLen = strlen(Data);
	if (dataLen > 0) {
		// Проверяем, поместится ли строка в буфер
		if (currentLen + dataLen < BUFFER_SIZE-1) {
			strcat(buffer, Data);
		} else {
			// Обработка переполнения: обрезаем до доступного размера
			size_t copyLen = BUFFER_SIZE - currentLen - 1 ;
			strncat(buffer, Data, copyLen);
			buffer[BUFFER_SIZE-1] = '\0';
		}
	}
	
	if (strcmp(buffer, basePath) == 0) {
		strncpy(buffer, "data\\q.scr", BUFFER_SIZE - 1);
		buffer[BUFFER_SIZE - 1] = '\0';
	}
	
	
	this->SetScriptName(buffer);
	
	gRegistry.ReadKeyMap("savename",(LPBYTE)Data,256);
	//play
	this->SetSaveFile("play\\");
	this->SetPlayerArena(0);
	this->SetBonusStage(0);
	this->Set_FUN_0045E4B0(0);
	this->SetPlayerSlotSave(0);
	this->Set_FUN_0045E4D0(0);
	memset(this->Arr10i,0,sizeof(this->Arr10i));
	this->field_430=0;
	this->field_434=0;
	this->field_438=0;
	this->field_43A=0;
	this->Set_FUN_0045E630();
	
	
	return 0;
	
}


char* MapGm::GetMapName() {
	return this->gmpFile;
}
void MapGm::SetMapName(char* NameFile){
	
	strncpy(this->gmpFile, NameFile, 255);
}

char* MapGm::GetStyleName() {
	return this->styFile;
}
void MapGm::SetStyleName(char* NameFile){
	
	strncpy(this->styFile, NameFile, 255);
}

char* MapGm::GetScriptName() {
	return this->sctiptFile;
}
void MapGm::SetScriptName(char* NameFile){
	
	strncpy(this->sctiptFile, NameFile, 255);
}

char* MapGm::GetSaveFile() {
	return this->SaveFile;
}
void MapGm::SetSaveFile(char* NameFile){
	
	strncpy(this->SaveFile, NameFile, 255);
}


void MapGm::SetPlayerArena(int PlayerArena){
	this->playerArena=PlayerArena;
}
void MapGm::SetBonusStage(int BonusStage){
	this->bonusStage=BonusStage;
}
void MapGm::Set_FUN_0045E4B0(int Param){
	this->field_0x402=Param;	
}
void MapGm::SetPlayerSlotSave(int PlayerSlot){
	this->PlayerSlotSave=PlayerSlot;
}
void MapGm::Set_FUN_0045E4D0(int Param){
	this->field_404=Param;
}
void MapGm::Set_FUN_0045E630(){
	
}
