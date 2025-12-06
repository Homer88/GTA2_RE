#include <windows.h>
#include <stdio.h>
#include "DebugLogFile.h"

int writeFileLog(char* FileName, char* str, char* error, char* data) {
	FILE* file = fopen(FileName, "a");
	if (file == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 1; // Возвращаем код ошибки
	}
	
	fprintf(file, "%s, %s, %s\n", error, str, data);

	fclose(file);

	return 0;
}
int writeFileLog(char* FileName, char* str, char* error, bool* address) {
	
	FILE* file = fopen(FileName, "a");
	if (file == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 1; // Возвращаем код ошибки
	}

	fprintf(file, "%s, %s, 0x00%x\n", error, str, address);

	fclose(file);

	return 0;
}
int writeFileLog(char* FileName, char* str, char* error, unsigned int  data) {

	FILE* file = fopen(FileName, "a");
	if (file == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 1; // Возвращаем код ошибки
	}

	fprintf(file, "%s  %s 0x00%x\n", error, str, data);

	fclose(file);

	return 0;
}

int writeFileLog(char* FileName, char* str, char* error, BYTE  *data) {

	FILE* file = fopen(FileName, "a");
	if (file == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 1; // Возвращаем код ошибки
	}

	fprintf(file, "%s  %s 0x00%x\n", error, str, data);

	fclose(file);

	return 0;
}

int writeFileLog(char* FileName, LPCSTR lpValueName, char* str, char* error, BYTE* data) {

	FILE* file = fopen(FileName, "a");
	if (file == NULL) {
		printf("Ошибка при открытии файла!\n");
		return 1; // Возвращаем код ошибки
	}

	fprintf(file, "%s %s%s %d\n", error, lpValueName, str, data[0]);

	fclose(file);

	return 0;
}

void DebugLog(int CodeError, char* ErrorFile, int code){

	 char buf[100];
	 sprintf(buf, " %d: %s -%d", CodeError,ErrorFile,code);
     MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}

void DebugLog( char* ErrorFile) {

		char buf[100];
		sprintf(buf, "%s",  ErrorFile);
		MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

	}
void DebugLog(const char* ErrorFile) {

	char buf[100];
	sprintf(buf, "%s", ErrorFile);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}
void DebugLog(wchar_t* ErrorFile) {

	wchar_t buffer[50];
	swprintf(buffer, 50, L"Строка %ls", ErrorFile);
	MessageBoxW(NULL, buffer, L"GTA2 Error", MB_OK);

}
void DebugLog(void* Structure, void* offsetPole, char *text) {
	
	char buf[100];
	sprintf(buf, "Данное поле строчки %s offcet = 0x%x", text, offsetPole);
	MessageBoxA(NULL, buf, "GTA2 Offset", MB_OK);
}
void DebugLog(bool* ErrorFile) {

	//char buf[100];
	if (ErrorFile){ 
		MessageBoxA(NULL, "True", "GTA2 Error", MB_OK); }
	else
		MessageBoxA(NULL, "False", "GTA2 Error", MB_OK);

}
void DebugLog(unsigned char* ErrorFile) {

	char buf[100];
	sprintf(buf, "%s", ErrorFile);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}
void DebugLog(int ErrorFile) {

	char buf[100];
	sprintf(buf, "%d", ErrorFile);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}
void DebugLog(char *text,int ErrorFile) {

	char buf[100];
	sprintf(buf, "%c=%d", text, ErrorFile);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}

void DebugLog(unsigned char ErrorFile) {

	char buf[100];
	sprintf(buf, "%d", ErrorFile);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}

void MsgError(char* ErrorMsg){

	MessageBoxA(NULL, ErrorMsg, "GTA2 Error", MB_OK);
	}

void MsgError(char* Descript,char* ErrorMsg){

	char buf[100];
	sprintf(buf, "%s %s", Descript, ErrorMsg);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);
	}