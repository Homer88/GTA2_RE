#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <intrin.h>
#include "cMenu.h"
#include "cGlobal.h"
#include "cPlayerData.h"
#include "cText.h"
#include "DebugLogFile.h"
#include "cHookTrace.h" 
#include "cClassProbe.h" 

extern PlayerData* gPlayerData;

// 0x005EB160 is the address of the global Menu* cell in .data (not the Menu
// instance!). The real Menu is heap-allocated (operator_new(0x1EB40) in
// FUN_00457830) and its address is stored in that cell. Read the pointer, do
// NOT use the cell address itself as a Menu* (that reads garbage -> crash).
Menu* GetGameMenu(void)
{
    return (Menu*)(*(void**)0x005EB160);
}

PlayerData* GetPlayerDataInstance(void)
{
    return *(PlayerData**)0x0066B404;
}

// ---- DrawGTATextRaw trace ring --------------------------------------------
// retail 0x004CC100 __stdcall 9 dwords; wrappers push
// (str, str, x, y, &wcharbuf, ..., style, flg) - see 0x4539F0. We only observe.
extern LPVOID _DrawGTATextRaw;   // trampoline patched by DetourAttach (dllmain.cpp)

struct DrawTraceRec {
    DWORD caller;
    DWORD a1, a2, a3, a4, a5, a6, a7, a8, a9;
    DWORD styleGlob;             // *0x67358C (lighting flag; stomped -> heap ptr)
    wchar_t text[17];
    // menu state at the moment of the draw (for hang forensics)
    WORD  mPage;          DWORD mState;    int mFrontend;  WORD mFontStyle;
    BYTE  mLength;        SHORT mKey;      BYTE mCurIdx;   wchar_t mName[9];
};

static DrawTraceRec g_drawRing[512];
static volatile DWORD g_drawRingIdx = 0;

static void DrawTracePush(DWORD caller, DWORD a1, DWORD a2, DWORD a3, DWORD a4,
                          DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9)
{
    DWORD idx = (g_drawRingIdx + 1) % 512;
    g_drawRingIdx = idx;
    DrawTraceRec* r = &g_drawRing[idx];
    r->caller    = caller;
    r->a1 = a1; r->a2 = a2; r->a3 = a3; r->a4 = a4; r->a5 = a5;
    r->a6 = a6; r->a7 = a7; r->a8 = a8; r->a9 = a9;
    r->styleGlob = *(DWORD*)0x0067358C;
    __try {
        const unsigned char* p = (const unsigned char*)a1;
        int i;
        for (i = 0; i < 16; ++i) {
            r->text[i] = ((const wchar_t*)p)[i];
            if (r->text[i] == 0) break;
        }
        r->text[i] = 0;
        r->text[16] = 0;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        r->text[0] = L'?'; r->text[1] = 0;
    }
    __try {
        Menu* m = GetGameMenu();
        if (m) {
            r->mPage = m->Page;      r->mState   = m->State;
            r->mFrontend = m->FrontendState;
            r->mFontStyle = m->FontStyle;
            r->mLength = m->Length;  r->mKey     = m->Key;
            r->mCurIdx = m->CurrentMenuItemsIndex;
            int i;
            for (i = 0; i < 8; ++i) { r->mName[i] = m->pPlayerName[i]; if (!r->mName[i]) break; }
            for (; i < 9; ++i) r->mName[i] = 0;
        }
        else {
            r->mPage = 0; r->mState = 0; r->mFrontend = 0; r->mFontStyle = 0;
            r->mLength = 0; r->mKey = 0; r->mCurIdx = 0; r->mName[0] = 0;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        r->mPage = 0; r->mState = -1; r->mFrontend = 0; r->mFontStyle = 0;
        r->mLength = 0; r->mKey = 0; r->mCurIdx = 0; r->mName[0] = 0;
    }
}

void __stdcall HookDrawGTATextRaw(DWORD a1, DWORD a2, DWORD a3, DWORD a4,
                                  DWORD a5, DWORD a6, DWORD a7, DWORD a8, DWORD a9)
{
    DrawTracePush((DWORD)_ReturnAddress(), a1, a2, a3, a4, a5, a6, a7, a8, a9);
    ((void (__stdcall*)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD))
        _DrawGTATextRaw)(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

void DumpDrawRing(FILE* f)
{
    DWORD total = g_drawRingIdx;
    DWORD n = (total < 512) ? total : 512;
    fprintf(f, "DRAW-TEXT RING (last %lu of %lu):\r\n",
            (unsigned long)n, (unsigned long)total);
    for (DWORD k = 0; k < n; ++k) {
        const DrawTraceRec* r = &g_drawRing[(g_drawRingIdx - n + 1 + k) % 512];
        fprintf(f, "  call=0x%08X a1=0x%08X a2=0x%08X a3=0x%08lX a4=0x%08lX "
                   "a5=0x%08lX %08lX/%08lX/%08lX/%08lX glow=0x%08X \"%.16ls\" "
                   "Pg=%u St=%d Fend=%d Fnt=%u Ln=%d Key=%d Idx=%d name=\"%.8ls\"\r\n",
                (unsigned long)r->caller,
                (unsigned long)r->a1, (unsigned long)r->a2,
                (unsigned long)r->a3, (unsigned long)r->a4, (unsigned long)r->a5,
                (unsigned long)r->a6, (unsigned long)r->a7,
                (unsigned long)r->a8, (unsigned long)r->a9,
                (unsigned long)r->styleGlob, (wchar_t*)r->text,
                (unsigned)r->mPage, (int)r->mState, (int)r->mFrontend,
                (unsigned)r->mFontStyle, (int)r->mLength, (int)r->mKey,
                (int)r->mCurIdx, (wchar_t*)r->mName);
    }
}

// Low-rate tape: a background thread appends only the NEW ring entries to
// C:\games\gta2\draw_ring.log every ~2 s. Lets us see what the frontend last
// tried to draw when the game "hangs" (no crash -> no CrashFilter dump).
static DWORD g_ringTaped = 0;
static const char* kRingTapePath = "C:\\games\\gta2\\draw_ring.log";

void DumpDrawRingFile(void)
{
    FILE* f = fopen(kRingTapePath, "ab");
    if (!f) return;
    DWORD total = g_drawRingIdx;
    DWORD delta = total - g_ringTaped;
    if (delta == 0 || delta > 512) {
        if (delta > 512) { g_ringTaped = total; fprintf(f, "  [ring wrapped, skipped]\r\n"); }
        fclose(f);
        return;
    }
    fprintf(f, "--- %lu new draws (total %lu) ---\r\n", (unsigned long)delta, (unsigned long)total);
    for (DWORD k = 0; k < delta; ++k) {
        const DrawTraceRec* r = &g_drawRing[(total - delta + k) % 512];
        fprintf(f, "  call=0x%08X str=0x%08X a1=0x%08lX a2=0x%08lX a3=0x%08lX "
                   "a4=0x%08lX %08lX/%08lX/%08lX/%08lX glow=0x%08X \"%.16ls\" "
                   "Pg=%u St=%d Fend=%d Fnt=%u Ln=%d Key=%d Idx=%d name=\"%.8ls\"\r\n",
                (unsigned long)r->caller, (unsigned long)r->a1,
                (unsigned long)r->a2, (unsigned long)r->a3,
                (unsigned long)r->a4, (unsigned long)r->a5,
                (unsigned long)r->a6, (unsigned long)r->a7,
                (unsigned long)r->a8, (unsigned long)r->a9,
                (unsigned long)r->styleGlob, (wchar_t*)r->text,
                (unsigned)r->mPage, (int)r->mState, (int)r->mFrontend,
                (unsigned)r->mFontStyle, (int)r->mLength, (int)r->mKey,
                (int)r->mCurIdx, (wchar_t*)r->mName);
    }
    fclose(f);
    g_ringTaped = total;
}

//char gNamePlayerASCII[80] ;
unsigned char *gNamePlayerASCII = (unsigned char*)0x00671880;

//char* __thiscall Menu::WCHARToChar(Menu* this, char* PlayerName)
unsigned char*   ConvertWCharToChar(wchar_t *wsc)
{
    if (!wsc) {
        gNamePlayerASCII[0] = '\0';
        return gNamePlayerASCII;
    }

    int i = 0;
    const wchar_t* src = wsc;
    constexpr int MAX_LENGTH = 79; // ���� ������ ��� ����-�����������

    // ����������� �� 79 �������� (��������� ������� ��� '\0')
    while (*src != L'\0' && i < MAX_LENGTH) {
        if (*src < 0x80) { // ASCII ������
            gNamePlayerASCII[i] = static_cast<char>(*src);
        }
        else { // ��-ASCII ������ - �������� �� '#'
            gNamePlayerASCII[i] = '#';
        }
        ++src;
        ++i;
    }
    gNamePlayerASCII[i] = '\0';
    return gNamePlayerASCII;
}


                                //0     1       2      3    4       5       6   7   
unsigned short gCodeInit[8] = { 829, 761, 23, 641, 43, 809, 677, 191 };



//char __thiscall Menu::PlayerCheat(Menu* this, wchar_t* PlayerName)

enum Cheat{
    CUTIE1 = 0x33A69,                 // ���� 99 ������
    NEKKID = 0x36F62,                 // �������
    MADEMAN = 0x41611,                 // ���� ���������
    DANISGOD = 0x44D2F,                 // ���� 20000
    FYOHZZ0 = 0x45118,
    FISHFLAP = 0x45AEF,                 // Small Cars
    UKGAMER = 0x45B2C,                 // all towns unlocked
    FLAMEON = 0x45EC2,                 // �ec�o�e��a� Flame Gun
    DAVEMOON = 0x4639F,                 // ������� ������ � ����������� �������
    EATSOUP = 0x4657B,                 // ���������� ��������
    IAMDAVEJ = 0x4672D,                 // ���� 999999
    LASVEGAS = 0x46BE8,                 // �a���� �����a
    NAVARONE = 0x47178,                 // All Weapons
    COCKTART = 0x478A9,                 // �� ������ �� ����� ���������� ����.
    PSJABBER = 0x478FB,                 // �� ����������
    ARSESTAR = 0x47AF1,                 // �oc�e apec�a y �ac coxpa����c� �ce ��e���ec� � �a����� �y���
    GOREFEST = 0x484DF,                 // ���������� ����� � ���� ������� ����������.
    BUCKFAST = 0x4878D,                 // ����� �����
    GOURANGA = 0x49362,                 // ��������� �����
    GODOFGTA = 0x49771,                 // ��� ������
    SUPZZZ0 = 0x49C76,
    SEGARULZ = 0x4A98B,                 // 10x Point Multiplier
    ITSALLUP = 0x4A9B8,                 // ���op ypo���
    HUNSRUS = 0x4B28C,                 // �e�����oc��
    SCHURULZ = 0x4D5C4,                 // ������� ����
    VOLTFEST = 0x4DA77,                 // �ec�o�e��a� Electrical Gun
    TUMYFROG = 0x5073D,                 // �ce �o�yc-ypo���
};

int* gCheatIs = (int*)0x005EAF50;// ������������� ���� �������� ������
char PlayerCheat(Menu* pthis, wchar_t* PlayerName)
{
    // TODO ME  ������ �������  
    if (pthis) {
        pthis->isChaet = true;
    }
    unsigned char *chName; //������ 8  ���������
    chName = ConvertWCharToChar(PlayerName);
    writeFileLog((char*)"menu.txt", (char*)"chName", (char*)"PlayerCheat", (char*)chName);
    int  lenString = wcslen(PlayerName);
    if (lenString <= 16) {
        int index = 0;
        int cash = 0;
        char text[] = "cash";
        if (lenString) {

            do {
                
                cash += gCodeInit[index] * chName[index];
                index++;
            }
            while(index <= lenString);
         

            if (cash == GOURANGA) {
                pthis->isChaet = true;
                *gCheatIs = 9;
                return 0;
            }
           if (pthis->isChaet){
                             
               switch (cash)
               {
               case GOREFEST:
                   *gDoBlood = true;
                   *gCheatIs = 9;
                   return 0;
               case BUCKFAST:
                   *gBunt = true;
                   *gCheatIs = 9;
                   return 0;
               case VOLTFEST:
                   *gVOLTFEST = true;
                   *gCheatIs = 9;
                   return 0;
               case MADEMAN:
                   *gMADEMAN = true;
                   *gCheatIs = 9;
                   return 0;
               case LASVEGAS:
                   *gLASVEGAS = true;
                   *gCheatIs = 9;
                   return 0;
               case NEKKID:
                   *gNEKKID = true;
                   *gCheatIs = 9;
                   return 0;
               case EATSOUP:
                   *gDoFreeShopping = true;
                   *gCheatIs = 9;
                   return 0;
               case DAVEMOON:
                  *gDAVEMOON = true;
                   *gCheatIs = 9;
                   return 0;
               case CUTIE1:
*gHeats99 = true;
                    writeFileLog((char*)"menu.txt", (char*)"Cutie1", (char*)"PlayerCheat", (char*)"GO");
                   *gCheatIs = 9;
                   return 0;
               case ARSESTAR:
                   *gKeepWeaponsAfterDeath= !*gKeepWeaponsAfterDeath;
                   *gCheatIs = 9;
                   return 0;
               case GODOFGTA:
                   *gGetAllWeapons =true;
                   *gCheatIs = 9;
                   return 0;
               case PSJABBER:
                   *gDoInvulnerable = true;
                   *gCheatIs = 9;
                   return 0;
               case DANISGOD:
                   *gDANISGOD = true;
                   *gCheatIs = 9;
                   return 0;
               case COCKTART:
                   *gExploding_on = true;
                   *gCheatIs = 9;
                   return 0;
               case FLAMEON:
                   *gFLAMEON = true;
                   *gCheatIs = 9;
                   return 0;
               case FYOHZZ0:
                   *gFYOHZZ0 = true;
                   *gCheatIs = 9;
                   return 0;
               case IAMDAVEJ:
                   *gIAMDAVEJ = true;
                   *gCheatIs = 9;
                   return 0;
               case SEGARULZ:
                   *gSEGARULZ = true;
                   *gCheatIs = 9;
                   return 0;
               case UKGAMER:
                   *gUKGAMER = true;
                   //S150::sub_4A8B00(gS150); ���� ������ ��
                   //Menu::sub_456E80(this); ���� ������ ��
                   *gCheatIs = 9;
                   return 0;
               case SUPZZZ0:
                   *gSUPZZZ0 = !*gSUPZZZ0;
                   //S150::sub_4A8A90(gS150, 1u, 0);
                   //Menu::sub_456E80(this);
                   *gCheatIs = 9;
                   return 0;
               case TUMYFROG:
                   *gTUMYFROG = !*gTUMYFROG;
                   //PlayerData::sub_4A8B00(gPlayerData);
                   //S150::sub_4A8A90(gPlayerData, 2u, 2u);
                   //S150::sub_4A8A90(gPlayerData, 1u, 0);
                   //Menu::sub_456E80(this);
                   *gCheatIs = 9;
                   return 0;
               case SCHURULZ:
                   *gSCHURULZ = !*gSCHURULZ;
                   *gCheatIs = 9;
                   break;
               case HUNSRUS:
                   *gHUNSRUS =!*gHUNSRUS;
                   *gCheatIs = 9;
                   break;
               case FISHFLAP:
                   *gCheatIs = 9;
                   *gFISHFLAP = !*gFISHFLAP;
                   break;
               default:
                   break;
               }
           }
        }

     }
    return 0;



}





//int __thiscall Menu::SetPlayerNameFromMenu(Menu* this)

// Retail body @0x00459540:
//   PlayerSlot = this->MenuPageArray[1].MenuEntry[0].PlayerSlot;
//   PlayerName = gPlayerData->PlayerSlotSave[PlayerSlot].PlayerName;
//   wcsncpy(PlayerName, &this->PlayerName, 9u);
//   Menu::PlayerCheat(this, PlayerName);
//   PlayerData::WriteFileNamePlayer(gPlayerData, PlayerSlot);

typedef void (__thiscall* FnWriteFileNamePlayer)(void*, unsigned short);

void  __fastcall SetPlayerNameFromMenu(Menu* thisMenu) {
//void  __stdcall SetPlayerNameFromMenu(Menu* pthis){
    unsigned short PlayerSlot; 
    wchar_t* PlayerName; 

    TraceCall("Menu::SetPlayerNameFromMenu @0x00459540", TRACE_CALLER_ADDR);
    ProbeThis(0x00459540u, "Menu::SetPlayerNameFromMenu", thisMenu);

    int pl = offsetof(Menu, pPlayerName);
    int address = (uintptr_t)thisMenu;

    //Debuglog(Menu, PLayerName, "PlayerName");
    writeFileLog((char*)"menu.txt", (char*)"offsetof(pPlayerName)", (char*)"SetPlayerNameFromMenu", (unsigned int)pl);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"SetPlayerNameFromMenu", (unsigned int)address);

    writeFileLog((char*)"menu.txt", (char*)"pPlayerName", (char*)"SetPlayerNameFromMenu", (unsigned int)thisMenu->pPlayerName);


    PlayerSlot = thisMenu->pMenuPage[1].pMenuEntry[0].PlayerSlot;
    PlayerData* pd = GetPlayerDataInstance();
    PlayerName = pd->pPlayerSlotSave[PlayerSlot].PlayerName;
    writeFileLog((char*)"menu.txt", (char*)"PlayerName", (char*)"SetPlayerNameFromMenu", (unsigned int)PlayerName);

    // Коммит имени в сейв (retail 1-в-1): 9 wide-символов из внутреннего
    // буфера меню -> PlayerSlotSave[slot].PlayerName, затем чит-массив и
    // перезапись player\plyslot%d.dat. Вызов через реальный адрес идёт в
    // детур-цепочку (HookWriteFileNamePlayer логирует и бежит в retail).
    wcsncpy(PlayerName, thisMenu->pPlayerName, 9u);
    PlayerCheat(thisMenu, PlayerName);
    ((FnWriteFileNamePlayer)0x004A89E0)(pd, PlayerSlot);
}

enum  MenuPages // 4 bytes
     {
         MENUPAGE_NONE = -1,
         MENUPAGE_START_MENU = 0,
         MENUPAGE_PLAY = 1,
         MENUPAGE_DEAD = 2,
         MENUPAGE_AREA_COMPLETE = 3,
         MENUPAGE_GAME_COMPLETE = 4,
         MENUPAGE_VIEW_HIGH_SCORE = 5,
         MENUPAGE_BONUS_AREA = 6,
         MENUPAGE_UNK_KILLS = 7,
         MENUPAGE_PLAY_INTRO = 8,
         MENUPAGE_CREDITS = 9,
         MENUPAGE_NICE_TRY = 10,
         MENUPAGE_RESULTS_PLAYER_QUIT = 11,
         MENUPAGE_12 = 12,
         MENUPAGE_13 = 13,
         MENUPAGE_PARENTAL_CONTROL = 14,
         MENUPAGE_15 = 15,
         NUM_MENUPAGES = 16,
         MENUPAGE_GTA2MANAGER = 257,
         MENUPAGE_QUIT = 258,
         MENUPAGE_259 = 259,
         MENUPAGE_264 = 264,
         MENUPAGE_265 = 265,
         MENUPAGE_260 = 260,
         MENUPAGE_261 = 261,
         MENUPAGE_266 = 266,
    
};

extern Text* gText;
extern LPVOID _LoadTextMenu; // dllmain.cpp: Detours trampoline to the original 0x00453E20
extern LPVOID _LoadGame;
extern LPVOID _SaveGame;
extern LPVOID _MultiplayerMenu;
extern LPVOID _ProcessInput; // dllmain.cpp: Detours trampoline to Menu::ProcessInput 0x00452050
extern LPVOID _MenuResolveText; // dllmain.cpp: trampoline to the original 0x00452200

// Retail Menu::text resolver @0x00452200, __thiscall.
typedef void (__thiscall* FnMenuResolveText)(void* pThis, int page, int idx,
                                             const wchar_t** out);

// 1 = run the reconstructed stub below (only 3 pages, hardcoded "Play"/"quit", no .gxt).
// 0 = call the ORIGINAL retail Menu::LoadTextMenu (builds all pages, reads text from
//     gText.Bsearch) - restores the frontend texts.
#define LOADTEXTMENU_USE_REPLICA 1

#define MENU_PAGE_COUNT     17
#define MENU_ENTRY_COUNT    10

static void WCharToAsciiBuf(const wchar_t* w, char* out, size_t outSize, size_t maxLen);

// Дамп того, что РЕАЛЬНО построил retail Menu::LoadTextMenu. Это фактура для
// переписывания метода: нужно содержимое страниц, а не угадывать его.
//
// ЦИКЛ ЖИЗНИ (подтверждено/уточнено): Menu конструируется один раз при
// аллокации в Inistal_Defaut @0x457830 (push 0x1EB40; call operator_new,
// если *(void**)0x005EB160 == NULL), и живёт до конца игры. LoadTextMenu
// грузит 17 страниц ПОСЛЕ конструктора, дальше содержимое не перезагружается.
// Поэтому первый снимок - это готовые данные, а дельта должна ловить только
// реальное изменение контента, НЕ поле TimeToWaitDemoStart @0xC9C8:
// оно = GetTickCount-like счётчик, меняется каждые миллисекунды и
// иначе дамп воспроизводится каждый раз без пользы.
static void MenuDumpPages(Menu* m, const char* tag)
{
	static BYTE  s_last[0xEDD4 - 0x122];
	static int   s_haveLast = 0;
	static unsigned s_call = 0;

	if (m == NULL) {
		return;
	}

	// снимок области страниц + хвостовых полей
	const BYTE* cur = (const BYTE*)m + 0x122;
	unsigned snapLen = (unsigned)(0xEDD4 - 0x122);

	// TimeToWaitDemoStart @0xC9C8, 4 байта -> смещение внутри снимка
	const unsigned tickOff = 0xC9C8u - 0x122u;
	const unsigned tickEnd = tickOff + 4;

	if (s_haveLast &&
		memcmp(s_last, cur, tickOff) == 0 &&
		memcmp(s_last + tickEnd, cur + tickEnd, snapLen - tickEnd) == 0) {
		return;                         // контент не менялся
	}
	memcpy(s_last, cur, snapLen);
	s_haveLast = 1;

	char path[MAX_PATH];
	DWORD n = GetModuleFileNameA(NULL, path, MAX_PATH);
	if (n == 0 || n >= MAX_PATH) {
		return;
	}
	char* slash = NULL;
	for (DWORD i = n; i > 0; --i) {
		if (path[i - 1] == '\\' || path[i - 1] == '/') {
			slash = &path[i - 1];
			break;
		}
	}
	if (slash == NULL) {
		return;
	}
	slash[1] = 0;

	char out[MAX_PATH] = {0};
	strcat_s(out, MAX_PATH, path);
	strcat_s(out, MAX_PATH, "menu_pages.txt");

	FILE* f = fopen(out, "ab");
	if (f == NULL) {
		return;
	}

	++s_call;
	fprintf(f,
		"\n===== #%u %s this=0x%08lX FrontendState=%d Page=%u FontStyle=%u "
		"Filderer0x120=%d TimeToWaitDemoStart=%d TimeToWaitBeforeDemoStart=%d "
		"CurrentMenuItemsIndex=%u =====\n",
		s_call, tag,
		(unsigned long)(ULONG_PTR)m,
		m->FrontendState, (unsigned)m->Page, (unsigned)m->FontStyle,
		(int)m->Filderer0x120,
		(int)m->TimeToWaitDemoStart, (int)m->TimeToWaitBeforeDemoStart,
		(unsigned)m->CurrentMenuItemsIndex);

	for (int p = 0; p < MENU_PAGE_COUNT; ++p) {
		MenuPage& pg = m->pMenuPage[p];
		int cnt = (int)pg.numMenuItems;
		if (cnt < 0) cnt = 0;
		if (cnt > MENU_ENTRY_COUNT) cnt = MENU_ENTRY_COUNT;

		fprintf(f, "page[%2d] num=%-3d CurrentActiveElement=0x%04X SelectActiveElementDefault=0x%04X field1=%d\n",
			p, (int)pg.numMenuItems, (unsigned)pg.CurrentActiveElement,
			(unsigned)(unsigned short)pg.SelectActiveElementDefault, (int)pg.field1);

		for (int i = 0; i < cnt; ++i) {
			MenuEntry& e = pg.pMenuEntry[i];
			// en/field1 доказан retail-ом: MenuEntry::fill @0x452B90 пишет
			// [entry+1]=1, т.е. включён по умолчанию; SetPage пропускает только
			// при 0. f72/f76/f7A retail НЕ инициализирует в fill - они живут только
			// там, где их пишет LoadTextMenu (селектор игрока), поэтому для
			// переписывания метода нужны именно из дампа.
			fprintf(f,
				"    [%2d] act=%u en=%d sel=0x%04X slot=%u slot1=%d X=%d Y=%d "
				"f6A=%d f6C=%d f72=%d f76=%d f7A=%d f7E=%u text=\"%ls\"\n",
				i, (unsigned)e.pMenuActions, (int)e.field1, (unsigned)e.SelectMenu,
				(unsigned)e.PlayerSlot, (int)e.PlayerSlot1,
				(int)e.X, (int)e.Y,
				(int)e.field_6A, (int)e.field_6C,
				(int)e.field_72, (int)e.field_76, (int)e.field_7A,
				(unsigned)e.field_7E,
				e.TextMenuElement);
		}

		// S136 = GUI-строки (в пересборке gta2\Game называются GUIArray) -
		// доп. текст рядом с пунктом. Пустые не пишем, чтобы не раздувать дамп.
		for (int i = 0; i < 15; ++i) {
			S136& g = pg.pS136[i];
			char gt[64];
			gt[0] = 0;
			WCharToAsciiBuf(g.str, gt, sizeof(gt), 30);
			if (!g.Visible && !g.field_2 && !g.field_4 && !gt[0]) {
				continue;
			}
			fprintf(f, "    gui[%2d] vis=%d ar=%d x=%d y=%d dX=%d dY=%d text=\"%s\"\n",
				i, (int)g.Visible, (int)g.PlayerArena,
				(int)g.field_2, (int)g.field_4,
				(int)g.filed_6A, (int)g.filed_6C, gt);
		}

		// S137 = позиции пунктов (в пересборке MenuItemArray). ВАЖНО: именно
		// [idx].Y retail читает в UpdateIndexToActive/NextActiveItem - Y==0
		// означает, что пункт невидим и ПРОПУСКАЕТСЯ при up/down.
		for (int i = 0; i < MENU_ENTRY_COUNT; ++i) {
			S137& it = pg.pS137[i];
			fprintf(f, "    item[%2d] f0=%-4d X=%-4d Y=%-4d %s\n",
				i, (int)it.field_0, (int)it.X, (int)it.Y,
				it.Y == 0 ? "<-- Y==0, пропускается при up/down" : "");
		}
	}

	// хвост: имя игрока и состояние клавиш
	fprintf(f, "tail pPlayerName=%ls Length=%d Key=%d MenuItems=\"%ls\" idx=%u "
		"NewKey=%u.%u.%u.%u.%u.%u.%u OldKey=%u.%u.%u.%u.%u.%u.%u\n",
		m->pPlayerName ? m->pPlayerName : L"<null>",
		(int)m->Length, (int)m->Key, m->MenuItems,
		(unsigned)m->CurrentMenuItemsIndex,
		(unsigned)m->NewKeyState.left, (unsigned)m->NewKeyState.Right,
		(unsigned)m->NewKeyState.up, (unsigned)m->NewKeyState.down,
		(unsigned)m->NewKeyState.enter, (unsigned)m->NewKeyState.esc,
		(unsigned)m->NewKeyState.del,
		(unsigned)m->OldKeyState.left, (unsigned)m->OldKeyState.Right,
		(unsigned)m->OldKeyState.up, (unsigned)m->OldKeyState.down,
		(unsigned)m->OldKeyState.enter, (unsigned)m->OldKeyState.esc,
		(unsigned)m->OldKeyState.del);

	fclose(f);
}

static void MenuNavLog(const char* line);   // определена ниже, нужна выше

// Побайтовый diff всего Menu при нажатии клавиши. Нужен, чтобы найти поле
// выделения: CurrentMenuItemsIndex всегда 0, значит highlight лежит в другом
// месте. Логируем только на кадре с нажатием (snapshot обновляется там же).
static void MenuDiffOnKey(Menu* m, const char* keyName)
{
	static BYTE  s_prev[0x1EB40];
	static int   s_have = 0;

	if (m == NULL) {
		return;
	}
	const BYTE* cur = (const BYTE*)m;

	if (!s_have) {
		memcpy(s_prev, cur, 0x1EB40);
		s_have = 1;
		return;
	}

	int changed = 0;
	char line[1024];
	int  used = 0;
	used += _snprintf(line + used, sizeof(line) - used, "%-6s ", keyName);

	for (unsigned i = 0; i < 0x1EB40 && changed < 24; ++i) {
		if (cur[i] != s_prev[i]) {
			used += _snprintf(line + used, sizeof(line) - used,
				"0x%X:%02X>%02X ", i, s_prev[i], cur[i]);
			changed++;
		}
	}
	if (changed == 0) {
		used += _snprintf(line + used, sizeof(line) - used, "(no change)");
	}
	if (changed >= 24) {
		used += _snprintf(line + used, sizeof(line) - used, "...+");
	}

	MenuNavLog(line);
	memcpy(s_prev, cur, 0x1EB40);
}

// Короткая однострочная запись в тот же menu_pages.txt - сюда пишем
// наблюдения по навигации (переходы страниц), они и расшифровывают SelectMenu.
static void MenuNavLog(const char* line)
{
	char path[MAX_PATH];
	DWORD n = GetModuleFileNameA(NULL, path, MAX_PATH);
	if (n == 0 || n >= MAX_PATH) {
		return;
	}
	char* slash = NULL;
	for (DWORD i = n; i > 0; --i) {
		if (path[i - 1] == '\\' || path[i - 1] == '/') {
			slash = &path[i - 1];
			break;
		}
	}
	if (slash == NULL) {
		return;
	}
	slash[1] = 0;

	char out[MAX_PATH] = {0};
	strcat_s(out, MAX_PATH, path);
	strcat_s(out, MAX_PATH, "menu_pages.txt");

	FILE* f = fopen(out, "ab");
	if (f == NULL) {
		return;
	}
	fprintf(f, "NAV  %s\n", line);
	fclose(f);

	// дубль в menu.txt: writeFileLog заведомо работает (KeyPress пишется),
	// поэтому нельзя остаться без данных из-за своей файловой обвязки
	writeFileLog((char*)"menu.txt", (char*)line, (char*)"MenuNav", (char*)"");
}

// ---------------------------------------------------------------------------
// Собственные построитель страниц меню.
//
// Соответствие retail доказано разбором gta2.exe. MenuPage::MenuPage @0x455EF0
// обнуляет numMenuItems/field1/[0xBC6]/[0xBC8] и трижды зовёт 0x4D69F7
// (конструктор массива, идёт с КОНЦА), который для каждого элемента зовёт fill:
//
//   0x452B90  MenuEntry x10 stride 0x82
//             [0]=0  [1]=1  [2]=0  [4]=0  [6A]=-1  [6C]=-1
//             [6E]=0 [70]=0 [7E]=0 [80]=0     (TextMenuElement,72/76/7A НЕ трогает)
//   0x452CC0  S136      x15 stride 0x6E
//             [0]=0  [1]=1  [2]=0  [4]=0  [6A]=-1  [6C]=-1
//   0x452B20  S137      x10 stride 6
//             [0]=0  [2]=0  [4]=1  <- пишется ОДИН БАЙТ, байт [5] (старший
//                                      байт Y) retail оставляет как есть
//
// Отличие нашего fill от retail: мы memset-им структуру целиком. Retail этого
// не делает, и в дампе это видно - page3 item[0].Y=2305 (0x0901), page12
// item[4].Y=12545 (0x3101): старший байт Y - мусор из кучи. На поведение это
// не влияет (Y сравнивается только с 0), но нулевое состояние - то, что
// задумано. Поле field_1 (=1) критично: SetPage @0x459034 крутит
// while (pMenuEntry[idx].field_1 == 0) NextActiveItem(page), и при 0 цикл
// никогда не остановится на валидном индексе.
// ---------------------------------------------------------------------------
static void MenuEntryReset(MenuEntry* e)
{
	memset(e, 0, sizeof(MenuEntry));
	e->pMenuActions = 0;
	e->field1 = 1;
	e->X = 0;
	e->Y = 0;
	e->field_6A = -1;
	e->field_6C = -1;
	e->PlayerSlot = 0;
	e->PlayerSlot1 = 0;
	e->field_7E = 0;
	e->SelectMenu = 0;
}

static void MenuGuiReset(S136* g)
{
	memset(g, 0, sizeof(S136));
	g->Visible = 0;
	g->PlayerArena = 1;
	g->field_2 = 0;
	g->field_4 = 0;
	g->filed_6A = -1;
	g->filed_6C = -1;
}

static void MenuItemReset(S137* it)
{
	memset(it, 0, sizeof(S137));
	it->field_0 = 0;
	it->X = 0;
	it->Y = 1;
}

static void MenuPageReset(MenuPage* pg)
{
	memset(pg, 0, sizeof(MenuPage));
	for (int i = 0; i < MENU_ENTRY_COUNT; ++i) {
		MenuEntryReset(&pg->pMenuEntry[i]);
		MenuItemReset(&pg->pS137[i]);
	}
	for (int i = 0; i < 15; ++i) {
		MenuGuiReset(&pg->pS136[i]);
	}
	pg->numMenuItems = 0;
	pg->field1 = 0;
	pg->CurrentActiveElement = 0;
	pg->SelectActiveElementDefault = 0;
}

// Разбор ENTER-обработчика @0x4597C0: act==1 -> mov ax,[entry+0x80];
// ecx = sel - 0x101; ja -> 0x459A2D: push eax; call 0x4587B0 (SetPage).
// Т.е. ВСЁ, что вне 0x101..0x10C, это просто SetPage(sel). Значит новый
// страницей доступен напрямую через SelectMenu = номер страницы.
static void MenuPageAddEntry(MenuPage* pg, int idx, unsigned char act,
                             unsigned short sel, short x, short y,
                             const wchar_t* text)
{
	MenuEntry& e = pg->pMenuEntry[idx];
	MenuEntryReset(&e);
	e.pMenuActions = act;
	e.field1 = 1;
	e.SelectMenu = sel;
	e.X = x;
	e.Y = y;
	if (text != NULL) {
		wcsncpy(e.TextMenuElement, text, 49);
		e.TextMenuElement[49] = 0;
	}
}

// --- СЕЛЕКТОР (act == 2) ---------------------------------------------------
// Разбор 0x452C30 (LEFT) / 0x452BD0 (RIGHT), ecx = &MenuEntry:
//   PlayerSlot (0x6E) - текущее значение
//   field_7E   (0x7E) - максимальное значение, включительно
//   байты [0x72 + i]  - флаг доступности слота i: 0 => left/right его
//                        пропускает (цикл @0x452BE6 крутится до возврата
//                        к исходному значению)
//   глобальный 0x5EAF58 != 0 => wrap через край, иначе упирается в край
// Флаги - это и есть field_72/field_76/field_7A (байты 0x72..0x7D), потому
// максимум 12 слотов (0x72 + 11 = 0x7D, дальше лежит сам field_7E).
// В дампе это видно: page1 f7E=7 => f72=f76=0x01010101, f7A=0 (не используется);
// page5 f7E=11 => f72=f76=f7A=0x01010101.
//
// Значение по умолчанию рисует retail: резолвер 0x452200, дефолтная ветка 0x45233A
//   swprintf(tmp, L"%d", PlayerSlot);
//   swprintf(out, L"%s %s", TextMenuElement, tmp);
// т.е. "<текст> <номер>". Нам нужны осмысленные значения (OFF/ON, EASY/HARD),
// поэтому резолвер хукается ниже, а сюда дополнительно передаётся таблица
// названий значений.
static const int MENU_SELECTOR_MAX = 32;

struct MenuSelectorOpts {
	unsigned char         page;
	unsigned short        idx;
	unsigned short        count;
	const wchar_t* const* names;
};

static MenuSelectorOpts g_selectorOpts[MENU_SELECTOR_MAX];
static int g_selectorCount = 0;

// Резолвер возвращает указатель, который живёт до отрисовки, а за один кадр
// отрисовка может пройтись по нескольким entry - поэтому буфер на каждый idx.
static wchar_t g_selectorText[MENU_ENTRY_COUNT][80];

static void MenuPageAddSelector(Menu* m, int page, int idx, short x, short y,
                                const wchar_t* text,
                                const wchar_t* const* names, unsigned short count)
{
	if (m == NULL || page < 0 || page >= MENU_PAGE_COUNT ||
	    idx < 0 || idx >= MENU_ENTRY_COUNT ||
	    names == NULL || count == 0) {
		return;
	}
	if (count > 12) { // байты флагов доступности лежат в 0x72..0x7D => максимум 12
		count = 12;
	}
	MenuEntry& e = m->pMenuPage[page].pMenuEntry[idx];
	MenuEntryReset(&e);
	e.pMenuActions = MENUACTION_SETPLAYERNAME; // 2 = selector (LEFT/RIGHT)
	e.field1 = 1;                             // 0 => SetPage зависнет в while
	e.X = x;
	e.Y = y;
	e.PlayerSlot = 0;
	e.field_7E = (unsigned short)(count - 1);   // максимум, включительно
	unsigned char* flags = (unsigned char*)&e + 0x72;
	for (unsigned i = 0; i < count; ++i) {
		flags[i] = 1;
	}
	if (text != NULL) {
		wcsncpy(e.TextMenuElement, text, 49);
		e.TextMenuElement[49] = 0;
	}
	if (g_selectorCount < MENU_SELECTOR_MAX) {
		g_selectorOpts[g_selectorCount].page  = (unsigned char)page;
		g_selectorOpts[g_selectorCount].idx   = (unsigned short)idx;
		g_selectorOpts[g_selectorCount].count = count;
		g_selectorOpts[g_selectorCount].names = names;
		++g_selectorCount;
	}
}

static const MenuSelectorOpts* MenuFindSelector(int page, int idx)
{
	for (int i = 0; i < g_selectorCount; ++i) {
		if (g_selectorOpts[i].page == (unsigned char)page &&
		    g_selectorOpts[i].idx == (unsigned short)idx) {
			return &g_selectorOpts[i];
		}
	}
	return NULL;
}

// Retail Menu::text resolver @0x00452200 - __thiscall (ecx=this, стек =
// {page, idx, out}), ret 0x0C. Детурсная сигнатура __fastcall
// (ecx=this, edx=свободен, стек = {page, idx, out}) бинарно эквивалентна:
// аргументы лежат в стеке одинаково, а 12 байт вычищает калли (ret 0x0C).
// Сначала отдаём страницу retail (его ветки page1/page5 и sprintf-побочки
// остаются нетронутыми), затем подменяем строку ТОЛЬКО для наших селекторов.
void __fastcall HookMenuResolveText(void* pThis, void* /*edx unused*/,
                                    int page, int idx, const wchar_t** out)
{
	((FnMenuResolveText)_MenuResolveText)(pThis, page, idx, out);

	if (out == NULL || pThis == NULL) return;
	if (page < 0 || page >= MENU_PAGE_COUNT) return;
	if (idx < 0 || idx >= MENU_ENTRY_COUNT) return;

	const MenuSelectorOpts* s = MenuFindSelector(page, idx);
	if (s == NULL || s->count == 0) return;

	Menu* m = (Menu*)pThis;
	MenuEntry& e = m->pMenuPage[page].pMenuEntry[idx];
	unsigned short slot = e.PlayerSlot;
	if (slot >= s->count) {
		slot = 0;
	}
	const wchar_t* name = (s->names[slot] != NULL) ? s->names[slot] : L"";

	wchar_t* buf = g_selectorText[idx];
	if (e.TextMenuElement[0] != 0) {
		swprintf(buf, 80, L"%s %s", e.TextMenuElement, name);
	} else {
		wcsncpy(buf, name, 79);
		buf[79] = 0;
	}
	*out = buf;
}

// item[] = S137. Доказано по дампу: field_0 = X подсветки, X = Y пункта
// (всегда entry.Y + 8), Y = 1 (видимость, Y==0 пропускается при up/down).
static void MenuPageSetItem(MenuPage* pg, int idx, short boxX, short y)
{
	pg->pS137[idx].field_0 = boxX;
	pg->pS137[idx].X = y;
	pg->pS137[idx].Y = 1;
}

// Страницы, забранные у retail. Retail оставил их пустыми (num=0), а тело
// SetPage @0x458FD3 для них ("cmp bp,8 / cmp bp,0xF / jne 0x459022;
// test bp,bp / jne 0x459033") проваливается прямо в хвост @0x459034 без
// побочных эффектов - то есть retail обслуживает такую страницу как обычную.
//
// СВОБОДНЫЕ СЛОТЫ: 12, 13, 16.
// СТРАНИЦА 9 СВОБОДНОЙ НЕ ЯВЛЯЕТСЯ: page0 entry[2] (QUIT) имеет sel=0x0009,
// ведёт именно туда, и у страницы есть своё тело SetPage @0x458814
// (push 0x19a; call 0x401af0) - это и есть падение из NAV-лога
// ("PAGECHANGE 0 -> 9", 0x1EB21:00>C0 0x1EB22:00>60).
#define MENU_PAGE_OURS_SETTINGS   12
#define MENU_PAGE_OURS_NETWORK    13
#define MENU_PAGE_OURS_EXTRA      16

// Центрованная раскладка как у page0: entry X=300, подсветка X = 300-20 = 280,
// Y подсветки = entry.Y + 8.
#define MENU_CX  300
#define MENU_CXI 280

static void MenuPageAddLink(MenuPage* pg, int idx, unsigned short toPage,
                            short y, const wchar_t* text)
{
	MenuPageAddEntry(pg, idx, 1 /*MENUACTION_CHANGEPAGE*/, toPage, MENU_CX, y, text);
	MenuPageSetItem(pg, idx, MENU_CXI, (short)(y + 8));
}

static void MenuPageAddSel(Menu* m, int page, int idx, short y,
                           const wchar_t* label,
                           const wchar_t* const* names, unsigned short count)
{
	MenuPageAddSelector(m, page, idx, MENU_CX, y, label, names, count);
	MenuPageSetItem(&m->pMenuPage[page], idx, MENU_CXI, (short)(y + 8));
}

// Данные страниц, которые строим сами. Вызывается ПОСЛЕ retail LoadTextMenu,
// который продолжает собирать 13 стоковых страниц (и берёт текст из .gxt -
// поэтому локализация не теряется). Мы забираем только то, что retail
// оставил пустым, и точечно дополняем стоковые страницы точками входа.
//
// Содержимое - каркас: структура (переходы, селекторы, значения) готова и
// проверяется в игре, конкретные пункты/значения подставляются дальше.
static void MenuBuildCustomPages(Menu* m)
{
	if (m == NULL) {
		return;
	}
	g_selectorCount = 0; // LoadTextMenu может вызываться повторно

	static const wchar_t* const kPct5[]       = { L"0%", L"25%", L"50%", L"75%", L"100%" };
	static const wchar_t* const kDifficulty[] = { L"EASY", L"NORMAL", L"HARD" };
	static const wchar_t* const kOnOff[]      = { L"OFF", L"ON" };
	static const wchar_t* const kConnection[] = { L"OFF", L"LAN", L"INTERNET" };
	static const wchar_t* const kResolve[]    = { L"AUTO", L"MANUAL" };
	static const wchar_t* const kScanlines[]  = { L"OFF", L"1x", L"2x" };

	// --- page 12: SETTINGS ---
	MenuPage& p12 = m->pMenuPage[MENU_PAGE_OURS_SETTINGS];
	MenuPageReset(&p12);
	p12.numMenuItems = 6;
	MenuPageAddSel(m, MENU_PAGE_OURS_SETTINGS, 0, 190, L"SOUND VOLUME", kPct5, 5);
	MenuPageAddSel(m, MENU_PAGE_OURS_SETTINGS, 1, 210, L"MUSIC VOLUME", kPct5, 5);
	MenuPageAddSel(m, MENU_PAGE_OURS_SETTINGS, 2, 230, L"DIFFICULTY", kDifficulty, 3);
	MenuPageAddLink(&p12, 3, MENU_PAGE_OURS_NETWORK, 270, L"NETWORK");
	MenuPageAddLink(&p12, 4, MENU_PAGE_OURS_EXTRA,   290, L"EXTRA");
	MenuPageAddLink(&p12, 5, 0, 330, L"BACK TO MAIN MENU");
	p12.CurrentActiveElement = 0;
	p12.SelectActiveElementDefault = 0;

	// --- page 13: NETWORK ---
	MenuPage& p13 = m->pMenuPage[MENU_PAGE_OURS_NETWORK];
	MenuPageReset(&p13);
	p13.numMenuItems = 3;
	MenuPageAddSel(m, MENU_PAGE_OURS_NETWORK, 0, 210, L"CONNECTION", kConnection, 3);
	MenuPageAddSel(m, MENU_PAGE_OURS_NETWORK, 1, 230, L"SERVER", kResolve, 2);
	MenuPageAddLink(&p13, 2, MENU_PAGE_OURS_SETTINGS, 310, L"BACK TO SETTINGS");
	p13.CurrentActiveElement = 0;
	p13.SelectActiveElementDefault = 0;

	// --- page 16: EXTRA ---
	MenuPage& p16 = m->pMenuPage[MENU_PAGE_OURS_EXTRA];
	MenuPageReset(&p16);
	p16.numMenuItems = 3;
	MenuPageAddSel(m, MENU_PAGE_OURS_EXTRA, 0, 210, L"SHOW FPS", kOnOff, 2);
	MenuPageAddSel(m, MENU_PAGE_OURS_EXTRA, 1, 230, L"SCANLINES", kScanlines, 3);
	MenuPageAddLink(&p16, 2, MENU_PAGE_OURS_SETTINGS, 310, L"BACK TO SETTINGS");
	p16.CurrentActiveElement = 0;
	p16.SelectActiveElementDefault = 0;

	// --- точка входа: четвёртый пункт в главном меню ---
	MenuPage& p0 = m->pMenuPage[0];
	if (p0.numMenuItems >= 0 && p0.numMenuItems < MENU_ENTRY_COUNT) {
		int i = p0.numMenuItems;
		MenuPageAddLink(&p0, i, MENU_PAGE_OURS_SETTINGS, 310, L"SETTINGS");
		p0.numMenuItems = (short)(i + 1);
	}
}

// ---------------------------------------------------------------------------
// РЕПЛИКА розничного Menu::LoadTextMenu @0x00453E20.
//
// Все 17 страниц строим сами. Данные - эталонный дамп рантайма (menu_pages.txt,
// блок after-retail): координаты, SelectMenu, нумерация, field1,
// CurrentActiveElement/SelectActiveElementDefault. Тексты берём из .gxt по
// КЛЮЧАМ (тем же, что retail ищет Bsearch-ом @0x004C2120), поэтому локализация
// остаётся рабочей на любой языке. Косметические спрайтовые str[0]=3/4 (стрелки)
// пишем как retail: рендер от них НЕ зависит (диспетчер глифа читает
// Menu.FrontendState [this+0x110], jump-table @0x45857C), но дамп совпадает байт-в-байт.
//
// Доказанные значения: page0 Filderer0x120=16; page1 CurActEl=SelActDef=3
// (bp=3); все остальные страницы CurActEl=SelActDef=0 (edi=0); field1 = число
// gui-строк страницы (page1=10, page7=14, page5=14 и т.д.).
// ---------------------------------------------------------------------------

// Retail Text::_Bsearch @0x004C2120 (__thiscall: this=ecx, ключ в стеке, ret 4).
// Наша __fastcall-оболочка (ecx=this, edx не используется, ключ в стеке) бинарно
// эквивалентна. Возвращает указатель на wchar-значение найденного ключа.
typedef const wchar_t* (__fastcall* FnGxtBsearch)(void* pThis, void* edxUnused, const char* key);

extern Text* gText;

static const wchar_t* MenuGxtResolve(const char* key)
{
    if (key == NULL) {
        return L"";
    }
    // Retail: `mov ecx, dword ptr [0x671550]` - 0x671550 это ЯЧЕЙКА-указатель
    // на объект Text (не сам объект!). cText.cpp-шный gText=(Text*)0x671550
    // ошибочен. Читаем указатель напрямую, как делает ретейл.
    Text* g = *(Text**)0x00671550;
    if (g == NULL) {
        return L"";
    }
    return ((FnGxtBsearch)0x004C2120)(g, NULL, key);
}

// Пункт: act/sel/X/Y. Остальное даёт MenuEntryReset (en=1, f6A/f6C=-1, flags=0).
static void MenuRepEntry(MenuPage* pg, int idx, unsigned char act,
                         unsigned short sel, short x, short y)
{
    MenuEntry& e = pg->pMenuEntry[idx];
    MenuEntryReset(&e);
    e.pMenuActions = act;
    e.SelectMenu = sel;
    e.X = x;
    e.Y = y;
}

// Текст пункта: ключ .gxt или литерал (key==NULL). NULL+NULL => остаётся пустым.
static void MenuRepEntryText(MenuEntry& e, const char* key, const wchar_t* lit)
{
    const wchar_t* s = NULL;
    if (key != NULL) {
        s = MenuGxtResolve(key);
    } else if (lit != NULL) {
        s = lit;
    } else {
        return;
    }
    wcsncpy(e.TextMenuElement, s, 49);
    e.TextMenuElement[49] = 0;
}

// Селектор игрока (act==2) БЕЗ регистрации в g_selectorOpts: retail сам рисует
// page1/page5 (резолвер @0x00452200), наши имена значений к ним не относятся.
static void MenuRepSelector(MenuPage* pg, int idx, short x, short y,
                            unsigned short count)
{
    MenuEntry& e = pg->pMenuEntry[idx];
    MenuEntryReset(&e);
    e.pMenuActions = MENUACTION_SETPLAYERNAME;
    e.X = x;
    e.Y = y;
    e.PlayerSlot = 0;
    e.field_7E = (unsigned short)(count - 1);   // максимум, включительно
    unsigned char* flags = (unsigned char*)&e + 0x72;   // доступность слота i
    for (unsigned i = 0; i < count && i < 12; ++i) {
        flags[i] = 1;
    }
}

// GUI-строка (S136). kind: 1=текст, 3=спрайт.
static void MenuRepGui(MenuPage* pg, int idx, char kind, short x, short y,
                       short dx, short dy, const char* key, int sprite)
{
    S136& g = pg->pS136[idx];
    MenuGuiReset(&g);
    g.Visible = kind;
    g.field_2 = x;
    g.field_4 = y;
    g.filed_6A = dx;
    g.filed_6C = dy;
    if (kind == 3) {
        g.str[0] = (wchar_t)sprite;           // косметический (см. шапку)
    } else if (key != NULL) {
        const wchar_t* s = MenuGxtResolve(key);
        wcsncpy(g.str, s, 49);
        g.str[49] = 0;
    }
}

// Подсветка пункта (S137): item.field_0 = X рамки, item.X = entry.Y + 8.
static void MenuRepItem(MenuPage* pg, int idx, short boxX, short y)
{
    MenuPageSetItem(pg, idx, boxX, (short)(y + 8));
}

static void MenuBuildRetailReplica(Menu* m)
{
    if (m == NULL) {
        return;
    }

    m->Filderer0x120 = 16;         // @0x453E30

    // ---- page 0 START_MENU ----
    {
        MenuPage& pg = m->pMenuPage[0];
        MenuPageReset(&pg);
        pg.numMenuItems = 3;
        pg.field1 = 0;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        static const struct { const char* key; unsigned short sel; short y; } t[3] = {
            { "play",    0x0001, 250 },
            { "options", 0x0101, 270 },
            { "quit",    0x0009, 290 },
        };
        for (int i = 0; i < 3; ++i) {
            MenuRepEntry(&pg, i, MENUACTION_CHANGEPAGE, t[i].sel, 300, t[i].y);
            MenuRepEntryText(pg.pMenuEntry[i], t[i].key, NULL);
            MenuRepItem(&pg, i, 280, t[i].y);
        }
    }

    // ---- page 1 PLAY (раскладка MAIN) ----
    {
        MenuPage& pg = m->pMenuPage[1];
        MenuPageReset(&pg);
        pg.numMenuItems = 5;
        pg.field1 = 10;
        pg.CurrentActiveElement = 3;
        pg.SelectActiveElementDefault = 3;
        MenuRepSelector(&pg, 0, 300, 210, 8);            // PLAYER
        MenuRepEntryText(pg.pMenuEntry[0], "charctr", NULL);
        MenuRepItem(&pg, 0, 280, 210);
        static const struct { const char* key; unsigned short sel; short y; } t[4] = {
            { "savepos", 0x0104, 230 },
            { "hi_scre", 0x0005, 250 },
            { "strtlev", 0x0108, 270 },
            { "bonslev", 0x0109, 350 },
        };
        for (int i = 0; i < 4; ++i) {
            MenuRepEntry(&pg, 1 + i, MENUACTION_CHANGEPAGE, t[i].sel, 300, t[i].y);
            MenuRepEntryText(pg.pMenuEntry[1 + i], t[i].key, NULL);
            MenuRepItem(&pg, 1 + i, 280, t[i].y);
        }
        // gui: 0/1 круги, 2/3 "VEHICLES DAMAGED", 4-7 стрелки, 8/9 стрелки имени
        MenuRepGui(&pg, 0, 3, 420, 310, -1, -1, NULL, 0);
        MenuRepGui(&pg, 1, 3, 420, 390, -1, -1, NULL, 0);
        MenuRepGui(&pg, 2, 1, 410, 298, 8, -1, "car_dam", 0);
        MenuRepGui(&pg, 3, 1, 410, 378, 8, -1, "car_dam", 0);
        MenuRepGui(&pg, 4, 3, 380, 310, -1, -1, NULL, 3);
        MenuRepGui(&pg, 5, 3, 460, 310, -1, -1, NULL, 4);
        MenuRepGui(&pg, 6, 3, 380, 390, -1, -1, NULL, 3);
        MenuRepGui(&pg, 7, 3, 460, 390, -1, -1, NULL, 4);
        MenuRepGui(&pg, 8, 3, 290, 222, -1, -1, NULL, 3);
        MenuRepGui(&pg, 9, 3, 580, 222, -1, -1, NULL, 4);
    }

    // ---- page 2 DEAD ----
    {
        MenuPage& pg = m->pMenuPage[2];
        MenuPageReset(&pg);
        pg.numMenuItems = 3;
        pg.field1 = 1;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        static const struct { const char* key; unsigned short sel; short x; short y; } t[3] = {
            { "savepos", 0x0104, 156, 392 },
            { "replay",  0x0103, 155, 412 },
            { "mainmen", 0x0000, 174, 432 },
        };
        for (int i = 0; i < 3; ++i) {
            MenuRepEntry(&pg, i, MENUACTION_CHANGEPAGE, t[i].sel, t[i].x, t[i].y);
            MenuRepEntryText(pg.pMenuEntry[i], t[i].key, NULL);
            MenuRepItem(&pg, i, 150, t[i].y);
        }
        MenuRepGui(&pg, 0, 1, 35, 11, 13, 0, "plr_ded", 0);
    }

    // ---- page 3 AREA_COMPLETE ----
    {
        MenuPage& pg = m->pMenuPage[3];
        MenuPageReset(&pg);
        pg.numMenuItems = 5;
        pg.field1 = 1;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        static const struct { const char* key; unsigned short sel; short x; short y; } t[5] = {
            { "nxt_lvl", 0x0105, 197, 365 },
            { "savepos", 0x0104, 156, 385 },
            { "replay",  0x0103, 155, 405 },
            { "contnue", 0x010A, 255, 425 },
            { "mainmen", 0x0000, 174, 445 },
        };
        for (int i = 0; i < 5; ++i) {
            MenuRepEntry(&pg, i, MENUACTION_CHANGEPAGE, t[i].sel, t[i].x, t[i].y);
            MenuRepEntryText(pg.pMenuEntry[i], t[i].key, NULL);
            MenuRepItem(&pg, i, 150, t[i].y);
        }
        MenuRepGui(&pg, 0, 1, 35, 11, 11, -1, "cmpltd", 0);
    }

    // ---- page 4 GAME_COMPLETE ----
    {
        MenuPage& pg = m->pMenuPage[4];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 1;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepEntry(&pg, 0, MENUACTION_CHANGEPAGE, 0x0000, 180, 410);
        MenuRepEntryText(pg.pMenuEntry[0], "mainmen", NULL);
        MenuRepItem(&pg, 0, 160, 410);
        MenuRepGui(&pg, 0, 1, 169, 230, 13, 4, "gam_cmp", 0);
    }

    // ---- page 5 VIEW_HIGH_SCORE ----
    {
        MenuPage& pg = m->pMenuPage[5];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 5;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepSelector(&pg, 0, 300, 155, 12);          // имя игрока
        MenuRepItem(&pg, 0, 280, 155);
        MenuRepGui(&pg, 0, 3, 450, 197, -1, -1, NULL, 0);
        MenuRepGui(&pg, 1, 1, 440, 185, 8, -1, NULL, 0);
        MenuRepGui(&pg, 2, 3, 410, 197, -1, -1, NULL, 3);
        MenuRepGui(&pg, 3, 3, 490, 197, -1, -1, NULL, 4);
        MenuRepGui(&pg, 4, 1, 340, 12, 8, -1, "hi_scre", 0);
    }

    // ---- page 6 BONUS_AREA ----
    {
        MenuPage& pg = m->pMenuPage[6];
        MenuPageReset(&pg);
        pg.numMenuItems = 3;
        pg.field1 = 3;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        static const struct { const char* key; unsigned short sel; short x; short y; } t[3] = {
            { "repbons", 0x0103, 166, 340 },
            { "nxt_lvl", 0x0105, 197, 360 },
            { "mainmen", 0x0000, 174, 380 },
        };
        for (int i = 0; i < 3; ++i) {
            MenuRepEntry(&pg, i, MENUACTION_CHANGEPAGE, t[i].sel, t[i].x, t[i].y);
            MenuRepEntryText(pg.pMenuEntry[i], t[i].key, NULL);
            MenuRepItem(&pg, i, 150, t[i].y);
        }
        MenuRepGui(&pg, 0, 1, 35, 11, 13, 5, "bonslev", 0);
        MenuRepGui(&pg, 1, 1, 170, 250, -1, -1, "score", 0);
        MenuRepGui(&pg, 2, 1, 400, 250, 5, -1, NULL, 0);
    }

    // ---- page 7 UNK_KILLS (сетевой / статистика убийств) ----
    {
        MenuPage& pg = m->pMenuPage[7];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 14;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepEntry(&pg, 0, MENUACTION_CHANGEPAGE, 0x0102, 291, 430);
        MenuRepEntryText(pg.pMenuEntry[0], "quit", NULL);
        MenuRepItem(&pg, 0, 180, 430);
        MenuRepGui(&pg, 0, 1, 35, 11, 13, 5, NULL, 0);
        for (int i = 1; i <= 6; ++i) {
            MenuRepGui(&pg, i, 1, 100, (short)(170 + (i - 1) * 20), -1, -1, NULL, 0);
        }
        MenuRepGui(&pg, 7, 1, 288, 300, -1, -1, "kills_h", 0);
        for (int i = 8; i <= 12; ++i) {
            MenuRepGui(&pg, i, 1, 100, (short)(320 + (i - 8) * 20), -1, -1, NULL, 0);
        }
        MenuRepGui(&pg, 13, 1, 30, 150, -1, -1, NULL, 0);
    }

    // ---- page 8 PLAY_INTRO ----
    {
        MenuPage& pg = m->pMenuPage[8];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 0;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepEntry(&pg, 0, MENUACTION_CHANGEPAGE, 0x0000, 200, 280);
        MenuRepEntryText(pg.pMenuEntry[0], "mainmen", NULL);
        MenuRepItem(&pg, 0, 180, 280);
    }

    // ---- page 9 CREDITS: retail пустая, num=0 ----

    // ---- page 10 NICE_TRY ----
    {
        MenuPage& pg = m->pMenuPage[10];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 1;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepEntry(&pg, 0, MENUACTION_CHANGEPAGE, 0x0000, 180, 410);
        MenuRepEntryText(pg.pMenuEntry[0], "mainmen", NULL);
        MenuRepItem(&pg, 0, 160, 410);
        MenuRepGui(&pg, 0, 1, 237, 230, 13, 4, "nicetry", 0);
    }

    // ---- page 11 RESULTS_PLAYER_QUIT ----
    {
        MenuPage& pg = m->pMenuPage[11];
        MenuPageReset(&pg);
        pg.numMenuItems = 3;
        pg.field1 = 1;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        static const struct { const char* key; unsigned short sel; short x; short y; } t[3] = {
            { "savepos", 0x0104, 156, 392 },
            { "replay",  0x0103, 155, 412 },
            { "mainmen", 0x0000, 174, 432 },
        };
        for (int i = 0; i < 3; ++i) {
            MenuRepEntry(&pg, i, MENUACTION_CHANGEPAGE, t[i].sel, t[i].x, t[i].y);
            MenuRepEntryText(pg.pMenuEntry[i], t[i].key, NULL);
            MenuRepItem(&pg, i, 150, t[i].y);
        }
        MenuRepGui(&pg, 0, 1, 35, 11, 13, 5, "plr_qut", 0);
    }

    // ---- page 12/13/16 строит MenuBuildCustomPages ниже ----

    // ---- page 14 PARENTAL_CONTROL (французский ввод кода) ----
    {
        MenuPage& pg = m->pMenuPage[14];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 5;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepEntry(&pg, 0, MENUACTION_CHANGEPAGE, 0x010C, 170, 340);   // текст пустой
        MenuRepItem(&pg, 0, 150, 340);
        MenuRepGui(&pg, 0, 1, 20, 160, -1, -1, "fr_pmpt", 0);
        MenuRepGui(&pg, 1, 1, 20, 180, -1, -1, "fr_ent1", 0);
        MenuRepGui(&pg, 2, 1, 20, 200, -1, -1, NULL, 0);
        MenuRepGui(&pg, 3, 1, 20, 300, -1, -1, "fr_ent2", 0);
        MenuRepGui(&pg, 4, 1, 20, 320, -1, -1, "score", 0);
    }

    // ---- page 15 (главное меню поверх игры) ----
    {
        MenuPage& pg = m->pMenuPage[15];
        MenuPageReset(&pg);
        pg.numMenuItems = 1;
        pg.field1 = 0;
        pg.CurrentActiveElement = 0;
        pg.SelectActiveElementDefault = 0;
        MenuRepEntry(&pg, 0, MENUACTION_CHANGEPAGE, 0x0000, 200, 280);
        MenuRepEntryText(pg.pMenuEntry[0], "mainmen", NULL);
        MenuRepItem(&pg, 0, 180, 280);
    }

    // Наши страницы 12/13/16 + точка входа SETTINGS в page0.
    MenuBuildCustomPages(m);
}

short  __fastcall  LoadTextMenu(Menu* thisMenu)
{
    TraceCall("Menu::LoadTextMenu @0x00453E20", TRACE_CALLER_ADDR);
    ProbeThis(0x00453E20u, "Menu::LoadTextMenu", thisMenu);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"LoadTextMenu", (unsigned int)thisMenu);
    writeFileLog((char*)"menu.txt", (char*)"gMenu", (char*)"LoadTextMenu", (unsigned int)GetGameMenu());
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
#if LOADTEXTMENU_USE_REPLICA
    MenuDumpPages(thisMenu, "before-replica");
    MenuBuildRetailReplica(thisMenu);
    MenuDumpPages(thisMenu, "after-replica");
    return 0;
#else
    // Chain to the original retail implementation (Menu::LoadTextMenu, __thiscall).
    // This builds the complete menu and fills the strings from the loaded .gxt data.
    // IMPORTANT: forward the ORIGINAL this (thisMenu, taken from ECX), NOT the global
    // gMenu cell address - during Menu::Menu() the global is still NULL and the
    // retail code must write into the real heap Menu.
    short r = ((short (__thiscall*)(Menu*))_LoadTextMenu)(thisMenu);
    MenuDumpPages(thisMenu, "after-retail");
    MenuBuildCustomPages(thisMenu);
    MenuDumpPages(thisMenu, "after-ours");
    return r;
#endif
}

// Retail Menu::LoadGame @0x00455C20 (__thiscall): iterates the 8 save slots via
// Menu::GetSaveFile + MenuDataBlock::Load. Trace + forward to the original.
char __fastcall LoadGame(Menu* thisMenu)
{
    TraceCall("Menu::LoadGame @0x00455C20", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"LoadGame", (unsigned int)thisMenu);
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
    return ((char (__thiscall*)(Menu*))_LoadGame)(thisMenu);
}

unsigned __int8 __fastcall SaveGame(Menu* thisMenu)
{
    TraceCall("Menu::SaveGame @0x00455C90", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"SaveGame", (unsigned int)thisMenu);
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
    return ((unsigned __int8 (__thiscall*)(Menu*))_SaveGame)(thisMenu);
}

char __fastcall MultiplayerMenu(Menu* thisMenu, void* _EDX, void* pPlayerName)
{
    (void)_EDX;
    TraceCall("Menu::MultiplayerMenu @0x004565E0", TRACE_CALLER_ADDR);
    writeFileLog((char*)"menu.txt", (char*)"thisMenu", (char*)"MultiplayerMenu", (unsigned int)thisMenu);
    writeFileLog((char*)"menu.txt", (char*)"pPlayerName", (char*)"MultiplayerMenu", (unsigned int)pPlayerName);
    if (thisMenu == NULL) {
        thisMenu = GetGameMenu();
    }
    return ((char (__thiscall*)(Menu*, void*))_MultiplayerMenu)(thisMenu, pPlayerName);
}

static const char* const kDIKNames[256] = {
    /* 0  */ "none", "esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    /* 12 */ "-", "=", "back", "tab", "q", "w", "e", "r", "t", "y", "u", "i",
    /* 24 */ "o", "p", "[", "]", "enter", "lctrl", "a", "s", "d", "f", "g",
    /* 35 */ "h", "j", "k", "l", ";", "'", "`", "lshift", "\\", "z", "x", "c",
    /* 47 */ "v", "b", "n", "m", ",", ".", "/", "rshift", "*", "lalt", "space",
    /* 58 */ "caps", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10",
    /* 69 */ "numlock", "scroll", "num7", "num8", "num9", "num-", "num4", "num5",
    /* 77 */ "num6", "num+", "num1", "num2", "num3", "num0", "num.",
    /* 84 */ NULL, NULL, NULL,
    /* 87 */ "f11", "f12",
    /* 89 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /* 99 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*109 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*119 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*129 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*139 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*149 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*159 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*169 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*179 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*189 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*199 */ "home", "up", "pgup", NULL, "left", NULL, "right", NULL,
    /*207 */ "end", "down", "pgdn", "ins", "del",
    /*212 */ NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /*219 */ "lwin", "rwin", "apps",
};

static void KeysPressedList(const Menu* m, char* out, size_t outSize)
{
    const unsigned char* k = (const unsigned char*)m->Keys;
    char* p = out;
    size_t left = outSize;
    int first = 1;
    int i;
    out[0] = 0;
    for (i = 0; i < 256; i++) {
        const char* name;
        int n;
        if (!(k[i] & 0x80))
            continue;
        name = kDIKNames[i];
        if (name == NULL) {
            char raw[8];
            _snprintf(raw, sizeof(raw), "0x%02X", i);
            n = _snprintf(p, left, "%s%s", first ? "" : "+", raw);
        }
        else {
            n = _snprintf(p, left, "%s%s", first ? "" : "+", name);
        }
        if (n < 0 || (size_t)n >= left) {
            break;
        }
        p += n;
        left -= (size_t)n;
        first = 0;
    }
}

static void WCharToAsciiBuf(const wchar_t* w, char* out, size_t outSize, size_t maxLen)
{
    size_t i = 0;
    if (w == NULL) {
        out[0] = 0;
        return;
    }
    for (i = 0; i < maxLen && w[i] != 0 && i + 1 < outSize; i++) {
        out[i] = (w[i] >= 0x20 && w[i] <= 0x7E) ? (char)w[i] : '?';
    }
    out[i] = 0;
}

void __fastcall HookProcessInput(Menu* m, void* _EDX)
{
    ProbeThis(0x00452050u, "Menu::ProcessInput", m);
    static unsigned char s_lastKeys[256];
    static Menu* s_lastMenu = NULL;
    static unsigned char s_booted = 0;
    char keys[160];
    char pageDump[768];
    char buf[1400];
    char tmp[64];
    const unsigned char* k;
    MenuPage* pg;
    int n;
    int e;
    int i;
    int pressedNew = 0;

    (void)_EDX;
    TraceCall("Menu::ProcessInput @0x00452050", TRACE_CALLER_ADDR);

    // снимок ДО retail: Page переключается МЕЖДУ вызовами ProcessInput
    // (внутри самого вызова он не меняется), поэтому сверяем кадр с кадром.
    unsigned short beforePage = m->Page;

    ((void (__thiscall*)(Menu*))_ProcessInput)(m);

    static unsigned short s_lastPage = 0xFFFF;
    if (s_lastPage != 0xFFFF && s_lastPage != m->Page) {
        char nb[128];
        _snprintf(nb, sizeof(nb), "PAGECHANGE %u -> %u", s_lastPage, (unsigned)m->Page);
        MenuNavLog(nb);
    }
    s_lastPage = m->Page;

    __try {
        if (!m->FrontendKeysEnabled) {
            return;
        }
        k = (const unsigned char*)m->Keys;
        if (m != s_lastMenu) {
            s_lastMenu = m;
            memcpy(s_lastKeys, k, 256);
        }
        for (i = 0; i < 256; i++) {
            if ((k[i] & 0x80) && !(s_lastKeys[i] & 0x80)) {
                pressedNew++;
            }
        }
        memcpy(s_lastKeys, k, 256);
        if (!pressedNew && s_booted) {
            return;
        }
        s_booted = 1;

        KeysPressedList(m, keys, sizeof(keys));
        MenuDiffOnKey(m, keys);

        pg = &m->pMenuPage[m->Page];
        n = pg->numMenuItems;
        if (n < 0 || n > 10) {
            n = 0;
        }
        pageDump[0] = 0;
        // CurrentActiveElement @MenuPage+0xBC6 = индекс выделенного пункта.
        // Доказано: UpdateIndexToActive @0x452A50 (up) и NextActiveItem
        // @0x452AA0 (down) читают/пишут [this+0xBC6], граница - [this+0]
        // (numMenuItems-1), невидимые пункты пропускаются по pS137[idx].Y==0.
        // Раньше тут читался SelectActiveElementDefault @0xBC8 (дефолт) - он
        // статичен, отсюда вечный ACTIVE=0/3. На page0 адрес = Menu+0x122+0xBC6
        // = Menu+0xCE8, на page1 = Menu+0x18B2 (проверено по diff'у: 0->1->2).
        char activeTxt[64];
        activeTxt[0] = 0;
        {
            int ai = (int)pg->CurrentActiveElement;
            if (ai >= 0 && ai < n) {
                WCharToAsciiBuf(pg->pMenuEntry[ai].TextMenuElement,
                                activeTxt, sizeof(activeTxt), 30);
            }
        }

        _snprintf(pageDump, sizeof(pageDump),
                  "page %u: %d items, idx=%u ACTIVE=%d/%d \"%s\", ",
                  (unsigned)m->Page, n,
                  (unsigned)m->CurrentMenuItemsIndex,
                  (int)pg->CurrentActiveElement,
                  (int)pg->SelectActiveElementDefault, activeTxt);
        for (e = 0; e < n; e++) {
            const MenuEntry* en = &pg->pMenuEntry[e];
            char t[64];
            char one[160];
            WCharToAsciiBuf(en->TextMenuElement, t, sizeof(t), 30);
            _snprintf(one, sizeof(one), "e%d[a=%u@(%d,%d) sel=%u \"%s\"]",
                      e, (unsigned)en->pMenuActions, en->X, en->Y,
                      (unsigned)en->SelectMenu, t);
            if (strlen(pageDump) + strlen(one) + 1 < sizeof(pageDump)) {
                strcat(pageDump, one);
            }
        }

        WCharToAsciiBuf(m->MenuItems, tmp, sizeof(tmp), 8);
        // KeyState = 7 байт (static_assert в cKeyState.h). NewKeyState @0xC9B8,
        // OldKeyState @0xC9BF - то есть +7, а не +8. Раньше тут читалось по 8
        // байт со сдвигом 8, т.е. лог залезал в field_C9C6/field_C9C7.
        _snprintf(buf, sizeof(buf),
                  "keys=%s | FrontendKeysEnabled=%d State=%d Page=%u MenuItems=\"%s\" Key=%d | "
                  "New(L,R,U,D,Ent,Esc,Del)=%u,%u,%u,%u,%u,%u,%u "
                  "Old=%u,%u,%u,%u,%u,%u,%u | %s",
                  keys, (int)m->FrontendKeysEnabled, (int)m->FrontendState,
                  (unsigned)m->Page, tmp, (int)m->Key,
                  (unsigned)m->NewKeyState.left,  (unsigned)m->NewKeyState.Right,
                  (unsigned)m->NewKeyState.up,    (unsigned)m->NewKeyState.down,
                  (unsigned)m->NewKeyState.enter, (unsigned)m->NewKeyState.esc,
                  (unsigned)m->NewKeyState.del,
                  (unsigned)m->OldKeyState.left,  (unsigned)m->OldKeyState.Right,
                  (unsigned)m->OldKeyState.up,    (unsigned)m->OldKeyState.down,
                  (unsigned)m->OldKeyState.enter, (unsigned)m->OldKeyState.esc,
                  (unsigned)m->OldKeyState.del,
                  pageDump);
        writeFileLog((char*)"menu.txt", buf, (char*)"KeyPress", (char*)"");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        writeFileLog((char*)"menu.txt", (char*)"<HookProcessInput read error>",
                     (char*)"KeyPress", (char*)"");
    }
}