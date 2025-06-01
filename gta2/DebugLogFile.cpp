#include <windows.h>
#include <stdio.h>
#include "DebugLogFile.h"


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

void DebugLog(int ErrorFile) {

	char buf[100];
	sprintf(buf, "%d", ErrorFile);
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