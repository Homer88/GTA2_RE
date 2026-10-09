#include "cClassProbe.h"
#include <Windows.h>
#include <stdio.h>
#include "DebugLogFile.h"

// Сообщения о проблемах с самим пробником уходят в общий лог сессии,
// чтобы потеря CSV не выглядела как "пробник не вызывался".
void ProbeDiag(const char* msg)
{
    writeFileLog((char*)"ClassProbe", (char*)msg, (char*)"Info", (char*)"");
}

// A hooked retail function is entered with ECX holding `this`, but a __fastcall
// detour has already consumed ECX, so the caller passes the object explicitly.
// Each distinct (retail address, this) pair is kept in an open-addressing table
// and flushed once, which bounds the log by (functions x live objects).

#define PROBE_SLOTS  (1 << 15)      // power of two, must exceed pairs seen
#define PROBE_MAXNAME 96

struct ProbeEntry {
	unsigned long retailAddr;       // 0 = empty slot
	unsigned long thisPtr;
	char          name[PROBE_MAXNAME];
};

static ProbeEntry g_slots[PROBE_SLOTS];
static unsigned long g_count = 0;
static FILE* g_log = NULL;
static char g_path[MAX_PATH] = {0};

// Хуки бьют из разных потоков (главный + аудио), а g_slots/g_count/g_log —
// общие без синхронизации. Гонка даёт torn-записи в слоте и два fopen на один
// путь, поэтому всё ниже берётся под этот лок.
static CRITICAL_SECTION g_probeLock;
static LONG g_probeLockReady = 0;

// Инициализация ровно один раз из ProbeThisInit (DllMain attach, до первого
// хука), поэтому гонки за флагом здесь нет — хуки не могут прийти раньше.
static void probe_lock(void)
{
	if (g_probeLockReady) {
		EnterCriticalSection(&g_probeLock);
	}
}

static void probe_unlock(void)
{
	if (g_probeLockReady) {
		LeaveCriticalSection(&g_probeLock);
	}
}

static unsigned long hash_pair(unsigned long addr, unsigned long obj)
{
	unsigned long h = addr * 2654435761UL;
	h ^= obj * 2246822519UL;
	h ^= h >> 13;
	h *= 1274126177UL;
	return h ^ (h >> 16);
}

const char* ProbeThisLogPath(void)
{
	if (g_path[0] == 0) {
		char dir[MAX_PATH];
		DWORD n = GetModuleFileNameA(NULL, dir, MAX_PATH);
		if (n == 0 || n >= MAX_PATH) {
			return "";
		}
		char* slash = NULL;
		for (DWORD i = n; i > 0; --i) {
			if (dir[i - 1] == '\\' || dir[i - 1] == '/') {
				slash = &dir[i - 1];
				break;
			}
		}
		if (slash == NULL) {
			return "";
		}
		// обрезаем ПОСЛЕ разделителя: *slash = 0 съел бы сам '\'
		slash[1] = 0;
		// дампы рядом с dllLoad, чтобы не мешать игре
		strcpy_s(g_path, dir);
		strcat_s(g_path, "classprobe_this.csv");
	}
	return g_path;
}

static void probe_open_log(void)
{
	const char* path;
	if (g_log != NULL) {
		return;
	}
	path = ProbeThisLogPath();
	if (path[0] == 0) {
		ProbeDiag("path=EMPTY (GetModuleFileName/slash failed)");
		return;
	}
	g_log = fopen(path, "wb");
	if (g_log == NULL) {
		ProbeDiag("fopen FAILED");
		return;
	}
	fprintf(g_log, "retail_addr,func_name,this_ptr,region_base,region_size\r\n");
	fflush(g_log);
	ProbeDiag("opened");
}

void ProbeThis(unsigned long retailAddr, const char* name, const void* pThis)
{
	if (pThis == NULL) {
		return;
	}

	unsigned long obj = (unsigned long)pThis;
	unsigned long idx = hash_pair(retailAddr, obj) & (PROBE_SLOTS - 1);

	probe_lock();

	for (unsigned long probe = 0; probe < PROBE_SLOTS; ++probe) {
		ProbeEntry& e = g_slots[idx];
		if (e.retailAddr == 0) {
			e.retailAddr = retailAddr;
			e.thisPtr = obj;
			strncpy_s(e.name, PROBE_MAXNAME, name ? name : "?", _TRUNCATE);
			g_count++;

			probe_open_log();
			if (g_log != NULL) {
				MEMORY_BASIC_INFORMATION mbi;
				ZeroMemory(&mbi, sizeof(mbi));
				VirtualQuery(pThis, &mbi, sizeof(mbi));
				fprintf(g_log, "0x%08lX,%s,0x%08lX,0x%08lX,0x%lX\r\n",
					retailAddr, e.name, obj,
					(unsigned long)mbi.BaseAddress,
					(unsigned long)mbi.RegionSize);
				// сбрасываем на диск сразу: при краше буфер stdio теряется
				fflush(g_log);
			}
			probe_unlock();
			return;
		}
		if (e.retailAddr == retailAddr && e.thisPtr == obj) {
			probe_unlock();
			return;                      // уже записано
		}
		idx = (idx + 1) & (PROBE_SLOTS - 1);   // коллизия -> следующий слот
	}

	probe_unlock();
}

unsigned long ProbeThisCount(void)
{
	return g_count;
}

// Вызывается из DllMain: создаёт CSV сразу, не дожидаясь первого хука,
// и пишет в лог, удалось ли это. Путь - рядом с EXE игры.
void ProbeThisInit(void)
{
	char msg[300];

	// Лок поднимаем первым: хуки могут прийти сразу после attach.
	InitializeCriticalSection(&g_probeLock);
	InterlockedExchange(&g_probeLockReady, 1);

	const char* p = ProbeThisLogPath();
	sprintf_s(msg, sizeof(msg), "csv path: %s", (p[0] ? p : "<EMPTY>"));
	ProbeDiag(msg);
	probe_open_log();
	sprintf_s(msg, sizeof(msg), "csv opened: %s", (g_log ? "yes" : "no"));
	ProbeDiag(msg);
}

void ProbeThisClose(void)
{
	probe_lock();
	if (g_log != NULL) {
		fprintf(g_log, "# total_pairs,%lu\r\n", g_count);
		fclose(g_log);
		g_log = NULL;
	}
	probe_unlock();
}