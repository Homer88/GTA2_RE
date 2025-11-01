#include "cGang.h"
#include <Windows.h>
#include <string.h>
#include "DebugLogFile.h"

void CopyNameGang(Gang* pGans, char *NameGang, unsigned char index ) {

	strncpy(pGans->NameGang, NameGang, index);
	pGans->NameGang[0] = 0;
	///MessageBox(0, pGans->NameGang, 0, 0);
	writeFileLog((char*)"Gang", (char*)"Gang->NameGang=", (char*)"Info", pGans->NameGang);
}

