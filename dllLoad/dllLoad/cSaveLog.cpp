// cSaveLog.cpp - dumps what the retail save writers actually put on disk.
// See cSaveLog.h for the three hooked entry points.
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "cSaveLog.h"
#include "cGame.h"
#include "cClassProbe.h"
#include "cMapGm.h"
#include "cPlayerData.h"
#include "DebugLogFile.h"

// ============================================================================
//  ФЛАЖКИ ОТЛАДКИ СЕЙВА  --  правишь только тут, потом пересобираешь DLL
// ============================================================================

// [ГАЛОЧКА] 1 = вкл, 0 = выкл.  Вбрасывает SAVE_FORCE_MONEY_VALUE в поле
// "money" прямо перед тем, как零售 writer пишет .svg, и в живой Player,
// чтобы HUD показал то же значение. Плюс печатает, в каком городе/миссии
// мы находились в момент сохранения.
//
// ВАЖНО: деньги из save-файла ПЕРЕЖИВАЮТ цикл загрузка->игра->сейв->загрузка
// (проверено форжем 0x64=90 и 0x64=9000). Нули money в логе того прогона были
// следствием битой S63, а не сбросом. Держим выключенным по умолчанию, чтобы
// не затирать значения, подставленные вручную в файл.
#define SAVE_FORCE_MONEY        0

// Сколько денег вбрасывать. Поле в файле - u32, HUD рисует свою анимацию.
#define SAVE_FORCE_MONEY_VALUE  90000

// Только логировать, ничего не подменяя (1 = не трогать память).
#define SAVE_MONEY_READONLY     0

// --- Кнопки/хоткеи для ручной правки прямо в игре --------------------------
// F8  - добавить SAVE_HOTKEY_MONEY к кошельку
// F9  - добавить SAVE_HOTKEY_WANTED к уровню розыска
// F10 - написать в Save.log, в каком мы городе/на какой миссии
// Суммы живут в cSaveLog.h, чтобы кнопки в cInspector.cpp совпадали.
// #define SAVE_HOTKEYS_ENABLED    1

// [ПОРТ] 1 = выбор мира идёт через НАШ нативный код (SetScoresNative +
// SaveLevelRecordNative), 0 = гоняем ретейл через трaмполины (сверка).
#define WORLD_SELECT_NATIVE     1

// ============================================================================

// Trampoline pointers; DetourAttach rewrites them to the retail originals.
// Defined in dllmain.cpp, same convention as _LoadGame / _SaveGame.
extern LPVOID _WriteFileSvg; // MissionManager::SaveFile        @0x0047EF40
extern LPVOID _WriteFileDat; // PlayerData::WriteFileNamePlayer @0x004A89E0
extern LPVOID _WriteFileHsc; // PlayerData::sub_4A8D80          @0x004A8D80
extern LPVOID _UpdateBestScores; // PlayerData::UpdateBestScores @0x004A90A0
extern LPVOID _MapGmSetScores;   // MapGm::sub_45EC20      @0x0045EC20
extern LPVOID _SaveLevelRecord;  // PlayerData::sub_4A8F90 @0x004A8F90

#define SAVE_BLOCK0 1864        // unk_664590, built by MissionManager::sub_475CA0
#define SAVE_MAX    (16 * 1024)

// block0 (unk_664590) offsets we care about, see tools/SAVE_LAYOUT.md
#define B0_CITY        0x4B     // u8  current city
#define B0_LEVEL       0x4C     // u8  city<<4 | sub, 0xFF = none
#define B0_GANG        0x4D     // u8  current gang
#define B0_MONEY       0x64     // u32 money
#define B0_E0_WANTED   0xE0     // u16 wanted level
// Player (heap struct) mirrors block0 money here - confirmed by the load
// putting file 0x64 straight into Player+0x2D4 (Player.log).
#define PL_MONEY       0x2D4
#define GAME_PTR_CELL  0x005EB4FCUL

static unsigned char s_buf[SAVE_MAX];

// In-memory image of the 1864-byte block0 (gta2.exe.asm / .c addresses).
static const unsigned long kBlock0Addr = 0x00664590UL;

static void SaveLogStamp(FILE* f);

// Три встроенных виджета PlayerStats в Player. В gta2.exe.h они ошибочно
// типизированы как PlayerStats*, на деле это struct по этому же смещению.
// Player::GetMoneyPlayer/GetMultiPlayer/getMoney кастуют &pPlayer->X к
// PlayerStats* и зовут getMoneyValue/GetHealth, то есть поле - сам виджет.
// Ищем тот, у которого Min/Max похожи на деньги, - это кошелёк HUD.
static void DumpWidgets(FILE* f, const unsigned char* pl)
{
    static const int kOff[3] = { 0x2D4, 0x359, 0x35D };
    static const char* kName[3] = {
        "0x2D4 money -> .dat best/last",
        "0x359 Lives",
        "0x35D MultiPlayer"
    };
    int w;

    if (f == NULL || pl == NULL)
        return;
    fprintf(f, "  --- виджеты PlayerStats ---\n");
    for (w = 0; w < 3; w++) {
        const unsigned char* s = pl + kOff[w];
        fprintf(f, "    %-30s value=%-10d maxDigits=%-3d min=%-6d max=%-10d id=%d\n",
                kName[w],
                *(const int*)(s + 0x00),
                *(const short*)(s + 0x22),
                *(const short*)(s + 0x24),
                *(const int*)(s + 0x28),
                *(const short*)(s + 0x2E));
    }
}

// Вбрасывает money и пишет в лог, где мы были. Возвращает 1, если память
// трогали, 0 если только чидали.
static int ForceMoneyAndLogCity(FILE* f, const char* stage)
{
    unsigned char* p = (unsigned char*)kBlock0Addr;
    unsigned char* pl = NULL;
    Game* g;
    unsigned long v = (unsigned long)SAVE_FORCE_MONEY_VALUE;
    unsigned long before = *(const unsigned long*)(p + B0_MONEY);
    int city = p[B0_CITY];
    int lvl = p[B0_LEVEL];
    int touched = 0;

    g = *(Game**)GAME_PTR_CELL;
    if (g != NULL && offsetof(Game, pPlayer) + sizeof(Player*) <= 0x40) {
        pl = (unsigned char*)g->pPlayer[0];
    }

    if (pl != NULL) {
        before = *(const unsigned long*)(pl + PL_MONEY);
    }
    DumpWidgets(f, pl);

#if !SAVE_FORCE_MONEY
    (void)v;
    (void)touched;
    (void)pl;
    fprintf(f, "  [ ] SAVE_FORCE_MONEY выключен (money=%u, город=%u, миссия=%s)\n",
            before, city, lvl == 0xFF ? "none" : "set");
    (void)stage;
    return 0;
#else
    if (lvl == 0xFF) {
        fprintf(f, "  [x] FORCE MONEY -> city=%u, level=0xFF (миссия не задана)\n", city);
    }
    else {
        fprintf(f, "  [x] FORCE MONEY -> city=%u, level city=%u sub=%u, gang=%u\n",
                city, lvl >> 4, lvl & 0x0F, p[B0_GANG]);
    }
    fprintf(f, "       money было %u -> станет %u\n", before, v);

    if (!SAVE_MONEY_READONLY) {
        *(unsigned long*)(p + B0_MONEY) = v;          // в .svg
        if (pl != NULL) {
            *(unsigned long*)(pl + PL_MONEY) = v;     // в живой Player -> HUD
        }
        touched = 1;
    }
    (void)stage;
    return touched;
#endif
}

// ---------------------------------------------------------------------------
// Ручные правки. block0+0x64 = money в файле .svg, Player+0x2D4 = кошелёк в
// памяти (подтверждено: 90 -> 4590 -> 15390 -> 14490 за сессию, и именно
// 15390 ушло в .dat rec0.best). Пишем в оба, чтобы и HUD, и файл сошлись.
// ---------------------------------------------------------------------------
static unsigned char* LivePlayer(void)
{
    Game* g = *(Game**)GAME_PTR_CELL;
    if (g == NULL) {
        return NULL;
    }
    return (unsigned char*)g->pPlayer[0];
}

unsigned long SaveDebugAddMoney(unsigned long delta)
{
    unsigned char* p = (unsigned char*)kBlock0Addr;
    unsigned char* pl = LivePlayer();
    unsigned long old, nw;
    FILE* f;

    old = *(const unsigned long*)(p + B0_MONEY);
    nw = old + delta;
    if (SAVE_MONEY_READONLY) {
        return old;
    }
    *(unsigned long*)(p + B0_MONEY) = nw;
    if (pl != NULL) {
        *(unsigned long*)(pl + PL_MONEY) = nw;
    }

    f = fopen(GetLogPath("Save.log"), "ab");
    if (f != NULL) {
        fprintf(f, "\n== [кнопка] + money ==");
        SaveLogStamp(f);
        fprintf(f, "  +%u -> money %u => %u (кошелёк в памяти%s)\n",
                delta, old, nw, pl != NULL ? " тоже обновлён" : " не найден");
        fprintf(f, "  сейчас: город=%u миссия=%s gang=%u\n",
                p[B0_CITY],
                p[B0_LEVEL] == 0xFF ? "нет" : "есть",
                p[B0_GANG]);
        fclose(f);
    }
    return nw;
}

unsigned int SaveDebugAddWanted(int delta)
{
    unsigned char* p = (unsigned char*)kBlock0Addr;
    unsigned short old, nw;
    FILE* f;

    old = *(const unsigned short*)(p + B0_E0_WANTED);
    nw = (unsigned short)(old + delta);
    if (nw > WANTED_MAX_IN_GAME) {
        nw = WANTED_MAX_IN_GAME;
    }
    *(unsigned short*)(p + B0_E0_WANTED) = nw;

    f = fopen(GetLogPath("Save.log"), "ab");
    if (f != NULL) {
        fprintf(f, "\n== [кнопка] + wanted ==");
        SaveLogStamp(f);
        fprintf(f, "  %u -> %u (максимум в игре %d), город=%u\n",
                old, nw, WANTED_MAX_IN_GAME, p[B0_CITY]);
        fclose(f);
    }
    return nw;
}

void SaveDebugWhereAmI(const char* why)
{
    unsigned char* p = (unsigned char*)kBlock0Addr;
    unsigned char* pl = LivePlayer();
    FILE* f = fopen(GetLogPath("Save.log"), "ab");
    int lvl = p[B0_LEVEL];

    if (f == NULL) {
        return;
    }
    fprintf(f, "\n== где мы (%s) ==", why);
    SaveLogStamp(f);
    fprintf(f, "  город=%u  gang=%u  ", p[B0_CITY], p[B0_GANG]);
    if (lvl == 0xFF) {
        fprintf(f, "миссия не задана (0xFF)\n");
    }
    else {
        fprintf(f, "бонус-уровень: city=%u sub=%u\n", lvl >> 4, lvl & 0x0F);
    }
    fprintf(f, "  маска заданий 0x12C = 0x%08X (собрано пикапов)\n",
            *(const unsigned long*)(p + 0x12C));
    fprintf(f, "  маска заданий 0x130 = 0x%08X (группа 2, 25 бит)\n",
            *(const unsigned long*)(p + 0x130));
    fprintf(f, "  счётчик миссий 0x12A = %u\n",
            *(const unsigned short*)(p + 0x12A));
    fprintf(f, "  карта/стиль/скрипт: \"%s\" / \"%s\" / \"%s\"\n",
            (const char*)(p + 0x00), (const char*)(p + 0x19),
            (const char*)(p + 0x32));
    fprintf(f, "  деньги=%u  жизни=%u  множитель=%u  здоровье=%u  розыск=%u\n",
            *(const unsigned long*)(p + B0_MONEY), p[0xD4],
            *(const unsigned long*)(p + 0x68),
            *(const unsigned short*)(p + 0x6C),
            *(const unsigned short*)(p + B0_E0_WANTED));
    fprintf(f, "  токены 0x744 = %u\n", *(const unsigned long*)(p + 0x744));
    if (pl != NULL) {
        fprintf(f, "  кошелёк в памяти = %u\n",
                *(const unsigned long*)(pl + PL_MONEY));
    }
    // Три встроенных виджета PlayerStats в Player (в заголовке они ошибочно
    // типизированы как PlayerStats*, на деле это struct). Ищем тот, у которого
    // Min/Max похожи на деньги, - это и есть кошелёк HUD.
    DumpWidgets(f, pl);
    fclose(f);
}

// --- хоткеи: отдельный поток, GetAsyncKeyState, работает где угодно ----------
#define SAVE_HOTKEYS_ENABLED    1
#if SAVE_HOTKEYS_ENABLED
static DWORD WINAPI HotkeyThreadProc(LPVOID unused)
{
    static unsigned char down[256];

    (void)unused;
    for (;;) {
        int vk;
        Sleep(30);
        for (vk = 0; vk < 256; vk++) {
            int now = (GetAsyncKeyState(vk) & 0x8000) ? 1 : 0;
            int fresh = now && !down[vk];
            down[vk] = (unsigned char)now;
            if (!fresh) {
                continue;
            }
            if (vk == VK_F8) {
                SaveDebugAddMoney(SAVE_HOTKEY_MONEY);
            }
            else if (vk == VK_F9) {
                SaveDebugAddWanted(SAVE_HOTKEY_WANTED);
            }
            else if (vk == VK_F10) {
                SaveDebugWhereAmI("F10");
            }
        }
    }
}

void SaveDebugStartHotkeys(void)
{
    HANDLE h = CreateThread(NULL, 0, HotkeyThreadProc, NULL, 0, NULL);
    if (h != NULL) {
        CloseHandle(h);
    }
}
#else
void SaveDebugStartHotkeys(void) {}
#endif

static void SaveLogStamp(FILE* f)
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    fprintf(f, " @ %02u:%02u:%02u.%03u\n", st.wHour, st.wMinute,
            st.wSecond, st.wMilliseconds);
}

static void HexDump(FILE* f, const unsigned char* p, int size, int base)
{
    int i, j;
    for (i = 0; i < size; i += 16) {
        fprintf(f, "    %04X:", base + i);
        for (j = 0; j < 16 && (i + j) < size; j++) {
            fprintf(f, " %02X", p[i + j]);
        }
        fprintf(f, "\n");
    }
}

static int ReadWhole(const char* path, unsigned char* out, int cap, int* outSize)
{
    FILE* f;
    long sz;

    *outSize = 0;
    f = fopen(path, "rb");
    if (f == NULL) {
        return 0;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    sz = ftell(f);
    if (sz < 0) { fclose(f); return 0; }
    rewind(f);
    *outSize = (int)sz;
    if (sz > cap) {
        sz = cap;
    }
    if (sz > 0 && fread(out, 1, (size_t)sz, f) != (size_t)sz) {
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

// plyslot%d.svg has no reliable name at call time when the retail caller passes
// an empty string (MissionManager::SaveFile falls back to the slot number
// itself, gta2.exe.c:103239-103244), so pick the slot whose mtime moved.
static void SlotStamps(const char* ext, FILETIME out[8])
{
    char path[64];
    WIN32_FILE_ATTRIBUTE_DATA a;
    int i;

    for (i = 0; i < 8; i++) {
        out[i].dwLowDateTime = 0;
        out[i].dwHighDateTime = 0;
        _snprintf(path, sizeof(path), "player\\plyslot%d.%s", i, ext);
        if (GetFileAttributesExA(path, GetFileExInfoStandard, &a)) {
            out[i] = a.ftLastWriteTime;
        }
    }
}

static int ChangedSlot(const FILETIME before[8], const char* ext)
{
    char path[64];
    WIN32_FILE_ATTRIBUTE_DATA a;
    int i;

    for (i = 0; i < 8; i++) {
        _snprintf(path, sizeof(path), "player\\plyslot%d.%s", i, ext);
        if (!GetFileAttributesExA(path, GetFileExInfoStandard, &a)) {
            continue;
        }
        if (a.ftLastWriteTime.dwLowDateTime != before[i].dwLowDateTime ||
            a.ftLastWriteTime.dwHighDateTime != before[i].dwHighDateTime) {
            return i;
        }
    }
    return -1;
}

static const char* const kPowerupName[17] = {
    "multiplier", "life", "health", "armor", "jailcard", "copbribe",
    "invuln", "dblDmg", "fastReload", "electro", "respect", "invis",
    "instantGang", "pu13", "pu14", "pu15", "pu16"
};

// block0 layout, from the globals MissionManager::SaveFile fills before the
// first WriteSub_402CF0 (gta2.exe.c:103245-103253).
// Field map reverse-engineered from retail writers + controlled save edits;
// see tools/SAVE_LAYOUT.md. Offsets are file-relative to unk_664590.
static void DumpBlock0Layout(FILE* f, const unsigned char* p, int size)
{
    int i;

    fprintf(f, "  block0 layout (offsets are from unk_664590 = 0x00664590):\n");
    fprintf(f, "    +0x0000             25 B    level name   = \"%s\"\n",
            (const char*)(p + 0x00));
    fprintf(f, "    +0x0019             24 B    style name   = \"%s\"\n",
            (const char*)(p + 0x19));
    fprintf(f, "    +0x0031 .. +0x004A  26 B    unk\n");
    fprintf(f, "    +0x004B             1 B     current city      = %u\n", p[0x4B]);
    fprintf(f, "    +0x004C             1 B     level packed      = 0x%02X",
            p[0x4C]);
    if (p[0x4C] != 0xFF) {
        fprintf(f, "  (city=%u sub=%u)", p[0x4C] >> 4, p[0x4C] & 0x0F);
    }
    fprintf(f, "\n");
    fprintf(f, "    +0x004D             1 B     gang               = %u\n", p[0x4D]);
    fprintf(f, "    +0x004E .. +0x0053  6 B     unk\n");
    fprintf(f, "    +0x0054 .. +0x0063  16 B    pos/rot (4 x f32): ");
    for (i = 0; i < 4; i++) {
        float v;
        memcpy(&v, p + 0x54 + 4 * i, 4);
        fprintf(f, "%.3f%s", v, i == 3 ? "" : " | ");
    }
    fprintf(f, "\n");
    fprintf(f, "    +0x0064             4 B     money              = %u\n",
            *(const unsigned int*)(p + 0x64));
    fprintf(f, "    +0x0068             4 B     multiplier         = %u\n",
            *(const unsigned int*)(p + 0x68));
    fprintf(f, "    +0x006C             2 B     health             = %u\n",
            *(const unsigned short*)(p + 0x6C));
    fprintf(f, "    +0x006E .. +0x008F  34 B    powerups u16[17]:\n");
    for (i = 0; i < 17; i++) {
        unsigned short v = *(const unsigned short*)(p + 0x6E + 2 * i);
        fprintf(f, "                         [%2d] %-12s = %u\n", i, kPowerupName[i], v);
    }
    fprintf(f, "    +0x0090 .. +0x00B7  40 B    field644[10] i32:");
    for (i = 0; i < 10; i++) {
        fprintf(f, " %d", *(const int*)(p + 0x90 + 4 * i));
    }
    fprintf(f, "\n");
    fprintf(f, "    +0x00B8 .. +0x00B9  2 B     unk\n");
    fprintf(f, "    +0x00BA .. +0x00C8  15 B    ammo[15]:");
    for (i = 0; i < 15; i++) {
        fprintf(f, " %u", p[0xBA + i]);
    }
    fprintf(f, "\n");
    fprintf(f, "    +0x00C9 .. +0x00D2  10 B    gangRespect[10]:");
    for (i = 0; i < 10; i++) {
        fprintf(f, " %u", p[0xC9 + i]);
    }
    fprintf(f, "\n");
    fprintf(f, "    +0x00D3             1 B     remap              = %u\n", p[0xD3]);
    fprintf(f, "    +0x00D4             1 B     lives              = %u\n", p[0xD4]);
    fprintf(f, "    +0x00D5             1 B     unk\n");
    fprintf(f, "    +0x00D6             2 B     selectWeapon       = %u (0x%04X)\n",
            *(const unsigned short*)(p + 0xD6), *(const unsigned short*)(p + 0xD6));
    fprintf(f, "    +0x00D8             4 B     field678           = 0x%08X\n",
            *(const unsigned int*)(p + 0xD8));
    fprintf(f, "    +0x00DC             4 B     field67C           = 0x%08X\n",
            *(const unsigned int*)(p + 0xDC));
    fprintf(f, "    +0x00E0             2 B     wantedLevel        = %u (in-game max 6)\n",
            *(const unsigned short*)(p + 0xE0));
    fprintf(f, "    +0x00E2 .. +0x0129  72 B    unk\n");
    fprintf(f, "    +0x012A             2 B     count?             = %u\n",
            *(const unsigned short*)(p + 0x12A));
    fprintf(f, "    +0x012C .. +0x0133  8 B     unk\n");
    fprintf(f, "    +0x0134 .. +0x05E3  1200 B  objective map (300 x u16 id, u16 val)\n");
    fprintf(f, "                         first used: ");
    for (i = 0; i < 300; i++) {
        unsigned short id = *(const unsigned short*)(p + 0x134 + 4 * i);
        if (id != 0) {
            fprintf(f, "[#%d id=%u val=%u] ", i, id,
                    *(const unsigned short*)(p + 0x134 + 4 * i + 2));
            if (i > 24) break;
        }
    }
    fprintf(f, "\n");
    fprintf(f, "    +0x05E4 .. +0x070F  300 B   object state (byte_664B74)\n");
    fprintf(f, "    +0x0710 .. +0x0741  50 B    unk_664CA0 (gObject S63 copy)\n");
    fprintf(f, "    +0x0742 .. +0x0743  2 B     gap\n");
    fprintf(f, "    +0x0744 .. +0x0747  4 B     special tokens (unk_664CD4) = 0x%08X\n",
            *(const unsigned int*)(p + 0x744));
    (void)size;
}

// plyslot%d.dat = wchar_t name[9] (18 B) + 12 x {u8 flag, u32 best, u32 last}
// rec N -> city = N/4, sub = N%4.  flag = city unlocked / stage completed,
// best = best money ever, last = money at last save (gta2.exe.c sub_4A8F90).
static void DumpDatLayout(FILE* f, const unsigned char* d, int size)
{
    int i;

    if (size < 126) {
        fprintf(f, "  .dat layout: <too short: %d bytes>\n", size);
        return;
    }
    fprintf(f, "  .dat layout (%d B):\n", size);
    fprintf(f, "    +0x0000  18 B  name  = \"%ls\"\n", (const wchar_t*)(d + 0x00));
    fprintf(f, "    +0x0012  108 B levels:  rec N -> city=N/4 sub=N%%4\n");
    for (i = 0; i < 12; i++) {
        const unsigned char* r = d + 0x12 + 9 * i;
        fprintf(f, "      rec%-2d city=%u sub=%u flag=%u best=%u last=%u\n",
                i, (unsigned)(i / 4), (unsigned)(i % 4), r[0],
                *(const unsigned int*)(r + 1), *(const unsigned int*)(r + 5));
    }
}

// .svg = [block0 1864][u32 len][len B][u32 len][len B][u32 len][len B]
// (WriteSub_402CF0 then three ARWBinarySub_402DA0 pairs, gta2.exe.c:103252-103266)
static void DumpSvgLayout(FILE* f, const unsigned char* d, int size)
{
    int off = 0;
    int idx = 0;
    int n;

    fprintf(f, "  .svg layout:\n");
    if (size < SAVE_BLOCK0) {
        fprintf(f, "    <truncated: %d bytes>\n", size);
        return;
    }
    fprintf(f, "    +0x%04X  block0  %5d B  unk_664590\n", off, SAVE_BLOCK0);
    off = SAVE_BLOCK0;
    while (off + 4 <= size && idx < 8) {
        memcpy(&n, d + off, sizeof(int));
        fprintf(f, "    +0x%04X  len%d    %5d B\n", off, idx + 1, n);
        off += 4;
        if (n < 0 || off + n > size) {
            fprintf(f, "    +0x%04X  data%d   (runs past EOF)\n", off, idx + 1);
            break;
        }
        fprintf(f, "    +0x%04X  data%d   %5d B\n", off, idx + 1, n);
        off += n;
        idx++;
    }
    if (off < size) {
        fprintf(f, "    +0x%04X  trailing %d B\n", off, size - off);
    }
    if (off > size) {
        fprintf(f, "    <parser overran by %d bytes>\n", off - size);
    }
}

static void DumpSaveFile(const char* title, const char* path, int isSvg)
{
    FILE* f;
    int size = 0;
    int got;

    got = ReadWhole(path, s_buf, SAVE_MAX, &size);
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f == NULL) {
        return;
    }
    fprintf(f, "\n== %s -> \"%s\"", title, path);
    if (!got) {
        fprintf(f, "  <cannot open> ==");
        SaveLogStamp(f);
        fclose(f);
        return;
    }
    fprintf(f, "  %d bytes ==", size);
    SaveLogStamp(f);
    if (isSvg) {
        DumpSvgLayout(f, s_buf, size);
    }
    else if (size >= 126) {
        DumpDatLayout(f, s_buf, size);
    }
    else {
        fprintf(f, "  raw (%.32s):\n", path);
    }
    fprintf(f, "  hex:\n");
    HexDump(f, s_buf, size, 0);
    fclose(f);
}

// player\hiscores.hsc: 136 записей по 24 B = wchar_t name[10] + u32 score.
// Это НЕ .dat - декодер .dat здесь давал бы мусор, поэтому свой.
static void DumpHiscores(void)
{
    FILE* f;
    int size = 0, i, n;

    if (!ReadWhole("player\\hiscores.hsc", s_buf, SAVE_MAX, &size))
        return;
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f == NULL)
        return;
    fprintf(f, "\n== player\\hiscores.hsc  %d B, %d записей по 24 B ==", size, size / 24);
    SaveLogStamp(f);
    n = size / 24;
    for (i = 0; i < n && i < 16; i++) {
        char nm[11];
        int k;
        for (k = 0; k < 10; k++)
            nm[k] = (char)*(s_buf + i * 24 + k * 2);
        nm[10] = 0;
        fprintf(f, "  %2d  %-22s %u\n", i, nm,
                *(const unsigned long*)(s_buf + i * 24 + 20));
    }
    fclose(f);
}

// The in-memory block0 the writer is about to persist - lets us diff memory
// against what actually landed in the file.
static void DumpBlock0Memory(void)
{
    FILE* f;
    const unsigned char* p = (const unsigned char*)kBlock0Addr;
    unsigned char copy[SAVE_BLOCK0];

    __try {
        memcpy(copy, p, SAVE_BLOCK0);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return;
    }
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f == NULL) {
        return;
    }
    fprintf(f, "\n== memory unk_664590 (block0, %d B) ==", SAVE_BLOCK0);
    SaveLogStamp(f);
    DumpBlock0Layout(f, copy, SAVE_BLOCK0);
    fprintf(f, "  hex:\n");
    HexDump(f, copy, SAVE_BLOCK0, 0);
    fclose(f);
}

// Печатает в лог город/миссию из block0 - отдельная ручка, чтобы можно было
// дёрнуть её и из других мест.
static void LogCityNow(FILE* f, const char* stage)
{
    unsigned char* p = (unsigned char*)kBlock0Addr;
    int lvl = p[B0_LEVEL];

    fprintf(f, "  --- %s: город=%ugang=%u ", stage, p[B0_CITY], p[B0_GANG]);
    if (lvl == 0xFF) {
        fprintf(f, "миссия=нет (0xFF)\n");
    }
    else {
        fprintf(f, "миссия: city=%u sub=%u\n", lvl >> 4, lvl & 0x0F);
    }
}

int __fastcall HookSaveFile(void* thisp, void* _EDX, char* pSaveFileName)
{
    ProbeThis(0x0047EF40u, "MissionManager::SaveFile", thisp);
    FILETIME before[8];
    FILE* f;
    int result;
    char path[320];
    int slot;

    (void)_EDX;
    SlotStamps("svg", before);

    // ---- до writer'а: вбросить деньги и записать, где мы находимся -------
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f != NULL) {
        fprintf(f, "\n== pre-MissionManager::SaveFile ==");
        SaveLogStamp(f);
        ForceMoneyAndLogCity(f, "SaveFile");
        fclose(f);
    }
    // ----------------------------------------------------------------------

    result = ((int(__thiscall*)(void*, char*))_WriteFileSvg)(thisp, pSaveFileName);

    DumpBlock0Memory();

    if (pSaveFileName != NULL && pSaveFileName[0] != 0) {
        _snprintf(path, sizeof(path), "%s", pSaveFileName);
    }
    else {
        slot = ChangedSlot(before, "svg");
        if (slot < 0) {
            slot = 0;
        }
        _snprintf(path, sizeof(path), "player\\plyslot%d.svg", slot);
    }
    DumpSaveFile("MissionManager::SaveFile", path, 1);

    // ---- после writer'а: что реально легло в файл ------------------------
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f != NULL) {
        fprintf(f, "\n== post-MissionManager::SaveFile -> %s ==", path);
        SaveLogStamp(f);
        if (ReadWhole(path, s_buf, SAVE_MAX, &result)) {
            if (result >= SAVE_BLOCK0) {
                fprintf(f, "  файл: город=%u миссия=0x%02X money=%u\n",
                        s_buf[B0_CITY], s_buf[B0_LEVEL],
                        *(const unsigned long*)(s_buf + B0_MONEY));
            }
        }
        LogCityNow(f, "после записи .svg");
        fclose(f);
    }
    // ----------------------------------------------------------------------
    return result;
}

int __fastcall HookWriteFileNamePlayer(void* thisp, void* _EDX, unsigned short slot)
{
    ProbeThis(0x004A89E0u, "PlayerData::WriteFileNamePlayer", thisp);
    FILE* f;
    int result;
    char path[64];

    (void)_EDX;

    f = fopen(GetLogPath("Save.log"), "ab");
    if (f != NULL) {
        fprintf(f, "\n== pre-PlayerData::WriteFileNamePlayer slot=%u ==",
                (unsigned)slot);
        SaveLogStamp(f);
        ForceMoneyAndLogCity(f, "WriteFileNamePlayer");
        fclose(f);
    }

    result = ((int(__thiscall*)(void*, unsigned short))_WriteFileDat)(thisp, slot);
    _snprintf(path, sizeof(path), "player\\plyslot%d.dat", (int)slot);
    DumpSaveFile("PlayerData::WriteFileNamePlayer", path, 0);

    // .dat пишется по city/sub, поэтому печатаем где именно
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f != NULL) {
        unsigned char* p = (unsigned char*)kBlock0Addr;
        int lvl = p[B0_LEVEL];
        fprintf(f, "  .dat для слота %u взят из: город=%u ", (unsigned)slot, p[B0_CITY]);
        if (lvl == 0xFF) {
            fprintf(f, "-> запись city=%u sub=%u (миссия не задана, fallback)\n",
                    p[B0_CITY] * 4, 0);
        }
        else {
            fprintf(f, "-> запись city=%u sub=%u (rec %d)\n",
                    lvl >> 4, lvl & 0x0F, (lvl >> 4) * 4 + (lvl & 0x0F));
        }
        fclose(f);
    }
    return result;
}

int __fastcall HookWriteHiscores(void* thisp, void* _EDX)
{
    int result;

    (void)_EDX;
    result = ((int(__thiscall*)(void*))_WriteFileHsc)(thisp);
    DumpHiscores();
    return result;
}

// PlayerData::UpdateBestScores @0x004A90A0. Runs when the game leaves a world
// back to the frontend (world-select dispatch, callers 0x4D1680/0x4D16D3/
// 0x4D1727). Retail picks the bests ROW by the caller's stack slot
// (esi = [esp+0x18] -> row base +0x1800+arena*0x28), bumps the 10 per-area
// bests plus two per-arena dwords (+0x1878/+0x1884) and calls WriteHiscores
// (hiscores.hsc) when anything rose. Diff the WHOLE 0x1800..0x1890 range so a
// non-zero row cannot slip through unnoticed.
// Диапазон дампа: 0x1800..0x24C0. Раньше был только 0x1800..0x1890, из-за
// чего в лог не попадали изменения самих таблиц рекордов S151_arr[12]
// (+0x1890..0x23D0) и S151_a (+0x23D0..0x24C0), хотя hiscores.hsc писался.
#define UBS_BEGIN 0x1800UL
#define UBS_END   0x24C0UL
#define UBS_BYTES (UBS_END - UBS_BEGIN)          // 0xCC0
#define UBS_DWORDS (UBS_BYTES / 4)

void __fastcall HookUpdateBestScores(void* thisp, void* _EDX)
{
    unsigned char* pd;
    unsigned long* before;
    unsigned long* after;
    int i, changed = 0;
    FILE* f;

    (void)_EDX;
    if (thisp == NULL) return;
    pd = (unsigned char*)thisp;
    before = (unsigned long*)malloc(UBS_BYTES);
    after = (unsigned long*)malloc(UBS_BYTES);
    if (before == NULL || after == NULL) {
        if (before) free(before);
        if (after) free(after);
        return;
    }
    for (i = 0; i < UBS_DWORDS; i++) {
        before[i] = *(unsigned long*)(pd + UBS_BEGIN + i * 4);
    }

    #if WORLD_SELECT_NATIVE
    UpdateBestScoresNative((PlayerData*)thisp);
    #else
    ((void(__thiscall*)(void*))_UpdateBestScores)(thisp);
    #endif

    for (i = 0; i < UBS_DWORDS; i++) {
        after[i] = *(unsigned long*)(pd + UBS_BEGIN + i * 4);
        if (after[i] != before[i]) changed = 1;
    }
    if (!changed) {
        free(before);
        free(after);
        return;
    }
    f = fopen(GetLogPath("Save.log"), "ab");
    if (f == NULL) {
        free(before);
        free(after);
        return;
    }
    fprintf(f, "\n== UpdateBestScores (новая запись в таблицу) [%s] ==",
            WORLD_SELECT_NATIVE ? "native" : "retail");
    SaveLogStamp(f);
    for (i = 0; i < UBS_DWORDS; i++) {
        if (after[i] != before[i]) {
            unsigned long off = UBS_BEGIN + (unsigned long)i * 4;
            // 0x1800..0x1877 три ряда best'ов по 0x28 (area = row/0x28),
            // 0x1878..0x1883 и 0x1884..0x188F два dword-массива по арене,
            // 0x1890..0x23CF S151_arr[12] (по 0xF0), 0x23D0..0x24BF S151_a.
            if (off < 0x1878UL) {
                fprintf(f, "  bests row=%lu area=%lu  [+0x%04lX] %lu -> %lu\n",
                        (off - 0x1800UL) / 0x28UL, ((off - 0x1800UL) % 0x28UL) / 4UL,
                        off, before[i], after[i]);
            }
            else if (off < 0x1884UL) {
                fprintf(f, "  arena dword A[arena=%lu]  [+0x%04lX] %lu -> %lu\n",
                        (off - 0x1878UL) / 4UL, off, before[i], after[i]);
            }
            else if (off < 0x1890UL) {
                fprintf(f, "  arena dword B[arena=%lu]  [+0x%04lX] %lu -> %lu\n",
                        (off - 0x1884UL) / 4UL, off, before[i], after[i]);
            }
            else {
                unsigned long base, tblend;
                unsigned long row, fld;
                char tbl[24];
                if (off < 0x23D0UL) {
                    base = 0x1890UL;
                    tblend = 0x23D0UL;
                    _snprintf(tbl, sizeof(tbl), "S151_arr[%lu]", (off - base) / 0xF0UL);
                }
                else {
                    base = 0x23D0UL;
                    tblend = 0x24C0UL;
                    _snprintf(tbl, sizeof(tbl), "S151_a");
                }
                (void)tblend;
                row = ((off - base) % 0xF0UL) / 0x18UL;
                fld = ((off - base) % 0xF0UL) % 0x18UL;
                if (fld < 0x14UL) {
                    fprintf(f, "  %s row=%lu name[+%lu]  [+0x%04lX] %lu -> %lu\n",
                            tbl, row, fld / 2UL, off, before[i], after[i]);
                }
                else {
                    fprintf(f, "  %s row=%lu score  [+0x%04lX] %lu -> %lu\n",
                            tbl, row, off, before[i], after[i]);
                }
            }
        }
    }
    fclose(f);
    free(before);
    free(after);
}

// ---------------------------------------------------------------------------
// Выбор мира: MapGm::sub_45EC20 @0x0045EC20 (загрузка очков уровня).
// Retail: thiscall MapGm::sub_45EC20(area*), ret 4. Копирует 10 dword из
// area+0x644 в MapGm.Arr10i[10] (+0x408), area+0x678 -> +0x430,
// area+0x67C -> +0x434. Диспетчер выбора мира (0x4D1658/0x4D16AB/0x4D16FF)
// зовёт это ПЕРЕД sub_4A8F90/sub_4A90A0 при входе в город.
// Инструментальный хук: снимаем что в источнике и что было в MapGm, гоняем
// retail, печатаем дельту. Событие редкое - логируем всегда.
// ---------------------------------------------------------------------------
void __fastcall HookMapGmSetScores(void* thisp, void* _EDX, void* srcArea)
{
    unsigned char* g = (unsigned char*)thisp;
    unsigned char* src = (unsigned char*)srcArea;
    unsigned long pre[10], post[10], srcv[10];
    unsigned long pre430, post430, pre434, post434;
    unsigned long src430, src434;
    int i, changed = 0;
    FILE* f;

    (void)_EDX;
    if (g == NULL) return;
    for (i = 0; i < 10; i++) pre[i] = *(unsigned long*)(g + 0x408 + i * 4);
    pre430 = *(unsigned long*)(g + 0x430);
    pre434 = *(unsigned long*)(g + 0x434);

    if (src != NULL) {
        for (i = 0; i < 10; i++) srcv[i] = *(unsigned long*)(src + 0x644 + i * 4);
        src430 = *(unsigned long*)(src + 0x678);
        src434 = *(unsigned long*)(src + 0x67C);
    }

    #if WORLD_SELECT_NATIVE
    SetScoresNative((MapGm*)thisp, srcArea);
#else
    ((void(__thiscall*)(void*, void*))_MapGmSetScores)(thisp, srcArea);
#endif

    for (i = 0; i < 10; i++) {
        post[i] = *(unsigned long*)(g + 0x408 + i * 4);
        if (post[i] != pre[i]) changed = 1;
    }
    post430 = *(unsigned long*)(g + 0x430);
    post434 = *(unsigned long*)(g + 0x434);
    if (post430 != pre430 || post434 != pre434) changed = 1;

    f = fopen(GetLogPath("Save.log"), "ab");
    if (f == NULL) return;
    fprintf(f, "\n== [Выбор мира] MapGm::sub_45EC20 загрузка очков уровня ==");
    SaveLogStamp(f);
    fprintf(f, "  arena=0x400:%u bonus=0x401:%u gang=0x402:%u slot=0x403:%u  src=%p\n",
            (unsigned)g[0x400], (unsigned)g[0x401], (unsigned)g[0x402],
            (unsigned)g[0x403], src);
    if (src != NULL) {
        fprintf(f, "  src+0x644[10]:");
        for (i = 0; i < 10; i++) fprintf(f, " %lu", srcv[i]);
        fprintf(f, "   +0x678=%lu +0x67C=%lu\n", src430, src434);
    }
    fprintf(f, "  MapGm.Arr10i[10]:");
    for (i = 0; i < 10; i++) {
        if (post[i] != pre[i]) fprintf(f, " %lu->%lu", pre[i], post[i]);
        else fprintf(f, " %lu", post[i]);
    }
    fprintf(f, "\n  +0x430 %lu -> %lu   +0x434 %lu -> %lu   [%s]%s\n",
            pre430, post430, pre434, post434, changed ? "ИЗМЕНЕНО" : "без изменений",
            WORLD_SELECT_NATIVE ? "  [native]" : "   [retail]");
    fclose(f);
}

// ---------------------------------------------------------------------------
// Выбор мира: PlayerData::sub_4A8F90 @0x004A8F90 (запись рекорда слота).
// Retail: thiscall PlayerData::sub_4A8F90(cityBlock*), ret 4.
// Вычисление записи (сверено по дизассемблу):
//   arena   = MapGm[+0x403];
//   gang    = MapGm[+0x402];
//   gang!=0 -> area = bonusStage(+0x401)>>4, sub = bonusStage&0xF
//   gang==0 -> area = +0x400, sub = 0;
//   rec     = pd+0x26A0 + arena*0xA4 + (sub + area*4)*3*4;
//   rec+4   = best (max), rec+8 = last (score = widget cityBlock+0x2D4
//             через 0x4B75A0/0x41DC30);
//   затем WriteFileNamePlayer(arena) пишет plyslot%d.dat.
// Хук снимает ВЕСЬ блок arena (0xA4) до/после - авторитетный поиск реально
// изменённых dword'ов плюс сверка расчётного rec с фактом.
// ---------------------------------------------------------------------------
int __fastcall HookSaveLevelRecord(void* thisp, void* _EDX, void* cityBlock)
{
    unsigned char* pd = (unsigned char*)thisp;
    unsigned char* g = (unsigned char*)gMapGm;
    unsigned char pre[0xA4], post[0xA4];
    unsigned char* block;
    int arena, gang, area, sub, off, i, result, mism;
    FILE* f;

    (void)_EDX;
    if (pd == NULL || g == NULL) return 0;

    arena = g[0x403];
    gang = g[0x402];
    if (gang != 0) { area = g[0x401] >> 4; sub = g[0x401] & 0x0F; }
    else { area = g[0x400]; sub = 0; }
    // pPlayerSlotSave[8]: если байт 0x403 мусорный (не 0..7), блок уехал бы
    // за пределы PlayerData (0x2BC0) - копируем только валидный диапазон.
    if (arena < 0 || arena > 7) {
        block = NULL;
        memset(pre, 0, 0xA4);
        memset(post, 0, 0xA4);
        off = -1;
    }
    else {
        block = pd + 0x26A0 + arena * 0xA4;
        off = (sub + area * 4) * 3 * 4;
        memcpy(pre, block, 0xA4);
    }

    #if WORLD_SELECT_NATIVE
    result = SaveLevelRecordNative((PlayerData*)thisp, cityBlock);
#else
    result = ((int(__thiscall*)(void*, void*))_SaveLevelRecord)(thisp, cityBlock);
#endif

    if (block != NULL) memcpy(post, block, 0xA4);

    f = fopen(GetLogPath("Save.log"), "ab");
    if (f == NULL) return result;
    fprintf(f, "\n== [Выбор мира] PlayerData::sub_4A8F90 запись рекорда слота ==");
    SaveLogStamp(f);
    fprintf(f, "  arena=%d gang=%d area=%d sub=%d rec_off=0x%X cityBlock=%p block=%p%s\n",
            arena, gang, area, sub, off, cityBlock, block,
            WORLD_SELECT_NATIVE ? "  [native]" : "   [retail]");
    mism = 1;
    for (i = 0; i + 3 < 0xA4; i += 4) {
        unsigned long b = *(unsigned long*)(pre + i);
        unsigned long a = *(unsigned long*)(post + i);
        if (b != a) {
            const char* tag = (i >= off && i < off + 12) ? "rec" : "другой";
            if (i >= off && i < off + 12) mism = 0;
            fprintf(f, "  [%s] block+0x%03X  %lu -> %lu%s\n",
                    tag, i, b, a,
                    (i == off + 4) ? "   (best)" : (i == off + 8) ? "   (last=score)" : "");
        }
    }
    if (block == NULL) {
        fprintf(f, "  !! arena=%d вне 0..7 - блок pPlayerSlotSave не читали\n", arena);
    }
    else if (off + 12 > 0xA4) {
        fprintf(f, "  !! расчётный rec выходит за блок 0xA4 - формула неверна?\n");
    }
    else if (memcmp(pre, post, 0xA4) == 0) {
        fprintf(f, "  блок не изменился (score не бьёт рекорд и last не двигается?)\n");
    }
    else if (mism) {
        fprintf(f, "  !! расчётный rec+0x%X не совпал с реально тронутым dword'ом\n", off);
    }
    fclose(f);
    return result;
}
