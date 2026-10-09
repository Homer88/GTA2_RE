#include "cPlayerData.h"
#include "cMapGm.h"
#include <windows.h>
#include <wchar.h>
#include <string.h>

PlayerData* gPlayerData = (PlayerData*)0x0066B404;

// Trampoline; DetourAttach (dllmain) переадресует на ретейл 0x004A89E0
// (PlayerData::WriteFileNamePlayer), т.е. вызов идёт через наш хук логирования.
extern LPVOID _WriteFileDat;

// Ретейл-адрес PlayerData::sub_4A8D80 (запись hiscores.hsc). Зовём именно
// сырой адрес, а не трaмполин, чтобы вызов прошёл через HookWriteHiscores
// (DumpHiscores) - ровно как это делает ретейл 0x4A90A0.
#define RETAIL_WRITE_HISCORES ((int(__thiscall*)(void*))0x004A8D80)

// retail 0x004A8F90  PlayerData::sub_4A8F90(cityBlock*), thiscall, ret 4.
// cityBlock на деле = экземпляр Player (вызыватель берёт его из Game+0x38).
// Дизассембл (сверено с тестом 07.10.2026, rec_off=0x30):
//   arena   = MapGm[+0x403] (геттер 0x45E550)
//   gang    = MapGm[+0x402] (геттер 0x45E540)
//   gang!=0 -> 0x453A60(bonusStage(+0x401), &area, &sub): area=bonus>>4,
//             sub=bonus&0xF (ниббл-анпак);
//   gang==0 -> area = +0x400 (геттер 0x45E520), sub = 0
//   block   = pd+0x26A0 + arena*0xA4  (arena + arena*4)*8)*4 = arena*41*4
//   rec     = block + (sub + area*4)*12
//   score   = *(int*)(Player+0x2D4)  (0x4B75A0 -> jmp 0x41DC30 = mov eax,[ecx])
//   if ((u32)score > rec->best) rec->best = score   (jbe = unsigned)
//   rec->last = score
//   WriteFileNamePlayer(pd, arena)  -> plyslot%d.dat
int __stdcall SaveLevelRecordNative(PlayerData* pPlayerData, void* cityBlock)
{
	unsigned char* pd = (unsigned char*)pPlayerData;
	unsigned char* g = (unsigned char*)gMapGm;
	unsigned char* block;
	unsigned char* rec;
	int arena, gang, area, sub, score;

	arena = g[0x403];
	gang = g[0x402];
	if (gang != 0) {
		area = g[0x401] >> 4;
		sub = g[0x401] & 0x0F;
	}
	else {
		area = g[0x400];
		sub = 0;
	}

	block = pd + 0x26A0 + arena * 0xA4;
	rec = block + (sub + area * 4) * 12;

	score = *(int*)((unsigned char*)cityBlock + 0x2D4);
	if ((unsigned int)score > *(unsigned int*)(rec + 4)) {
		*(int*)(rec + 4) = score;
	}
	*(int*)(rec + 8) = score;

	return ((int(__thiscall*)(void*, unsigned long))_WriteFileDat)(
			pPlayerData, (unsigned long)arena);
}

// ---------------------------------------------------------------------------
// Таблица рекордов S151: 10 строк по 0x18 (wchar_t name[10] @+0, int @+0x14).
// ---------------------------------------------------------------------------
struct HiscoreRow {
	wchar_t name[10];
	int     score;
};
static_assert(sizeof(HiscoreRow) == 0x18, "HiscoreRow must be 0x18");

// Точная копия retail 0x004D6CEC = wcsncpy (копирует до count 16-битных
// юнитов, добивает нулями; если в src нет '\0' в первых count юнитах, то
// вовсе не терминирует и следующий юнит dst не трогает). Свой, чтобы не
// зависеть от deprecated wcsncpy CRT и совпасть байт-в-байт.
static void CopyWidePad(wchar_t* dst, const wchar_t* src, int count)
{
	int i;
	if (count == 0) return;
	for (i = 0; i < count; i++) {
		dst[i] = src[i];
		if (src[i] == 0) {
			for (i++; i < count; i++) dst[i] = 0;
			return;
		}
	}
}

// retail 0x4A8630  PlayerData::AddScore(S151* table, wchar_t* name, int),
// thiscall, ret 8. Сверено 08.10.2026:
//   insert = 10;
//   for (i=9; i>=0; --i):
//       if (score > row[i].score) insert = i;
//       else if (score == row[i].score && wcscmp(row[i].name, name)==0)
//           return 0;                    // имя уже есть в таблице
//   if (insert == 10) return 0;          // не пробил ни одну строку
//   for (i=9; i>insert; --i) {           // сдвигаем строки вниз
//       wcsncpy(row[i].name, row[i-1].name, 9);
//       row[i].score = row[i-1].score;
//   }
//   wcsncpy(row[insert].name, name, 9);  // вставка (ретейл копирует 9 wchar)
//   row[insert].score = score;
//   return 1;
static int AddScoreNative(S151* table, const wchar_t* name, int score)
{
	HiscoreRow* row = (HiscoreRow*)table;
	int insert = 10;
	int i;

	for (i = 9; i >= 0; --i) {
		if (score > row[i].score) {
			insert = i;
		}
		else if (score == row[i].score) {
			if (wcscmp(row[i].name, name) == 0) {
				return 0;
			}
		}
	}

	if (insert == 10) {
		return 0;
	}

	for (i = 9; i > insert; --i) {
		CopyWidePad(row[i].name, row[i - 1].name, 9);
		row[i].score = row[i - 1].score;
	}

	CopyWidePad(row[insert].name, name, 9);
	row[insert].score = score;
	return 1;
}

// retail 0x4A8780  PlayerData::SumBest(PlayerSlotSave* block), thiscall.
// Сумма 12 dword'ов best: block+4 + 12*k, k=0..11 (3 арены * 4 записи).
static int SumBestNative(unsigned char* block)
{
	int sum = 0;
	int k;
	for (k = 0; k < 12; ++k) {
		sum += *(int*)(block + 4 + k * 12);
	}
	return sum;
}

// retail 0x4A90A0  PlayerData::UpdateBestScores(void), thiscall.
// Сверено 08.10.2026 (0x4A90A0..0x4A9163):
//   gang = MapGm[+0x402];
//   gang!=0 -> area = bonusStage(+0x401)>>4, sub = bonusStage&0xF;
//   gang==0 -> area = MapGm[+0x400], sub = 0;
//   arena = MapGm[+0x403] & 0xFF;               // слот (0..7)
//   block = pd+0x26A0 + arena*0xA4;             // PlayerSlotSave слота
//   K     = sub + area*4;                       // индекс записи (0..11)
//   name  = block+0x90 (wchar PlayerName);
//   score = *(int*)(block + K*12 + 8);          // rec.last
//   c1 = AddScore(pd+0x1890 + 0xF0*K, name, score);
//   sum = SumBest(block);
//   c2 = AddScore(pd+0x23D0, name, sum);
//   if (sub == 0) {
//       row = pd+0x1800 + area*0x28;            // 10 best по арене
//       for (i=0..9) if ((u32)MapGm.Arr10i[i] > (u32)row[i]) { row[i]=...; f=1; }
//       if ((u32)MapGm[+0x430] > (u32)pd[0x1878+area*4]) { ...; f=1; }
//       if ((u32)MapGm[+0x434] > (u32)pd[0x1884+area*4]) { ...; f=1; }
//   }
//   if (c1||c2||f) WriteHiscores(pd);           // 0x4A8D80 -> hiscores.hsc
void __stdcall UpdateBestScoresNative(PlayerData* pPlayerData)
{
	unsigned char* pd = (unsigned char*)pPlayerData;
	unsigned char* g = (unsigned char*)gMapGm;
	unsigned char* block;
	wchar_t* name;
	int area, sub, arena, k, score, sum;
	unsigned char changed1, changed2, flags = 0;

	if (g[0x402] != 0) {
		area = g[0x401] >> 4;
		sub = g[0x401] & 0x0F;
	}
	else {
		area = g[0x400];
		sub = 0;
	}

	arena = g[0x403] & 0xFF;
	block = pd + 0x26A0 + arena * 0xA4;
	k = sub + area * 4;
	name = (wchar_t*)(block + 0x90);
	score = *(int*)(block + k * 12 + 8);

	changed1 = (unsigned char)AddScoreNative(
			(S151*)(pd + 0x1890 + 0xF0 * k), name, score);

	sum = SumBestNative(block);
	changed2 = (unsigned char)AddScoreNative((S151*)(pd + 0x23D0), name, sum);

	if (sub == 0) {
		unsigned char* row = pd + 0x1800 + (size_t)area * 0x28;
		for (k = 0; k < 10; ++k) {
			int v = gMapGm->Arr10i[k];
			if ((unsigned int)v > *(unsigned int*)(row + k * 4)) {
				*(int*)(row + k * 4) = v;
				flags = 1;
			}
		}
		if ((unsigned int)gMapGm->field_430 >
				*(unsigned int*)(pd + 0x1878 + (size_t)area * 4)) {
			*(int*)(pd + 0x1878 + (size_t)area * 4) = gMapGm->field_430;
			flags = 1;
		}
		if ((unsigned int)gMapGm->field_434 >
				*(unsigned int*)(pd + 0x1884 + (size_t)area * 4)) {
			*(int*)(pd + 0x1884 + (size_t)area * 4) = gMapGm->field_434;
			flags = 1;
		}
	}

	if (changed1 || changed2 || flags) {
		RETAIL_WRITE_HISCORES(pPlayerData);
	}
}
