#include "cGang.h"
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include "DebugLogFile.h"
#include "cHookTrace.h"

// Detour target for retail Gang::SetName @0x0045DB40 (__thiscall). The __fastcall
// form keeps the __thiscall ABI (this->ECX, Source/Len pushed on the stack, callee
// cleans 8 bytes) and feeds the arguments into CopyNameGang - the re-implementation
// of the retail SetName body.
void __fastcall HookSetName(Gang* pGang, void* _EDX, char* Source, unsigned __int8 Len)
{
	(void)_EDX;
	TraceCall("Gang::SetName @0x0045DB40", TRACE_CALLER_ADDR);
	if (pGang == NULL) {
		return;
	}
	CopyNameGang(pGang, Source, Len);
}

const char* GangEnumName(int index)
{
	switch ((GANG)index) {
		case GANG::Yakuza: return "Yakuza";
		case GANG::Zaibatsu_Corporation: return "Zaibatsu";
		case GANG::Loonies: return "Loonies";
		case GANG::GANG_3: return "G3";
		case GANG::GANG_4: return "G4";
		case GANG::GANG_5: return "G5";
		case GANG::GANG_6: return "G6";
		case GANG::GANG_7: return "G7";
		case GANG::GANG_8: return "G8";
		case GANG::GANG_9: return "G9";
		case GANG::GANG_10: return "G10";
		default: return "G?";
	}
}

void CopyNameGang(Gang* pGans, char *NameGang, unsigned char index ) {

	char msg[64];
	int gi;

	TraceEvent("Gang::SetName @0x0045DB40 (body)");
	strncpy(pGans->NameGang, NameGang, index);
	pGans->NameGang[index] = 0;
	///MessageBox(0, pGans->NameGang, 0, 0);

	gi = GangIndexOf(pGans);
	if (gi >= 0) {
		sprintf(msg, "Gang[%d:%s]->NameGang=", gi, GangEnumName(gi));
	}
	else {
		sprintf(msg, "Gang+0x%X->NameGang=", (unsigned)((const char*)pGans - (const char*)kGangsPtrAddress));
	}
	writeFileLog((char*)"Gang", msg, (char*)"Info", pGans->NameGang);
}

