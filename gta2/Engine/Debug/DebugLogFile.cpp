#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "DebugLogFile.h"

static bool DebugLogSuppressed() {
	// Debug-only: suppress modal MessageBox to allow automated smoke/probes.
	// Default behavior unchanged when env is not set.
	const char* e = getenv("GTA2_DEBUGLOG_SUPPRESS");
	return e && e[0] == '1' && e[1] == '\0';
}


void DebugLog(int CodeError, char* ErrorFile, int code){
	 if (DebugLogSuppressed()) return;
	 char buf[100];
	 sprintf(buf, " %d: %s -%d", CodeError,ErrorFile,code);
     MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

	}
void DebugLog( char* ErrorFile) {
		if (DebugLogSuppressed()) return;
		char buf[100];
		sprintf(buf, "%s",  ErrorFile);
		MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

	}

void DebugLog(int ErrorFile) {
	if (DebugLogSuppressed()) return;
	char buf[100];
	sprintf(buf, "%d", ErrorFile);
	MessageBoxA(NULL, buf, "GTA2 Error", MB_OK);

}

void DebugLog(unsigned char ErrorFile) {
	if (DebugLogSuppressed()) return;
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