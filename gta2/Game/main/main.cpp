// GTA2.exe - вьювер экрана меню игры (реконструкция GTA2).
// Собирается в bin/GTA2.exe через gta2/CMakeLists.txt (библиотеки MENU/Text/Font + ресурсы).
//
// Что делает приложение:
//   - Строит данные меню через gMenu.LoadTextMenu() (исходная реконструкция Menu.cpp,
//     заполняет MenuPageArray[] - все страницы меню).
//   - Фон страницы собирается из картинок data\frontend\*.tga: левая панель шириной
//     LEFT_W=278px + правая RIGHT_W=362px = 640x480. У части страниц одна картинка
//     рисуется на весь экран (титры, "вы мертвы" и т.п.).
//   - Текст пунктов меню берётся из e.gxt по текстовым ключам, взятым из исходников
//     реконструкции (charctr, savepos, hi_scre, ...). Сама Text::Bsearch сейчас
//     заглушена, поэтому строки подменяются таблицей kMenuFallback.
//   - Версия игры "A2 V%d.%d" в правом нижнем углу главного меню берётся из ресурса
//     GTA2.EXE через WinApi::GetVersion (глобальный gWinApi).
//   - Поле PLAYER на 2-й странице - список 8 слотов игроков (Menu::PlayerSlotSave),
//     листается стрелками, имя текущего слота можно править с клавиатуры.
//
// Управление:
//   Esc          - на подстранице вернуться на предыдущее меню, на главном - выход
//   Вверх/Вниз   - переключение активного пункта меню
//   Влево/Вправо - переключение слота игрока в поле PLAYER (8 имён)
//   Enter        - выбор пункта (переход на страницу / выход / подтверждение)
//   Печать       - ввод имени игрока в поле PLAYER
// ВРЕМЕННЫЕ тесты звука (звуков навигации в оригинальном меню нет):
//   S            - играть очередной звук банка data\audio\ste.sdt/.raw
//   W            - декодировать очередной файл Vocals\*.wav (IMA ADPCM) и проиграть
// ---------------------------------------------------------------------------

#include <windows.h>   // WinAPI (окна, GDI)
#include <cstdio>      // swprintf
#include <cstring>     // wcsncpy, strcmp
#include <cstdlib>     // std::strtoul и пр.
#include <cwchar>      // wcslen
#include <string>      // std::wstring
#include <vector>      // std::vector

#include "Engine/System/System.h"   // класс cApplication (окно и игровой цикл)
#include "Engine/Res/TGA.h"         // класс cTGA (загрузка .tga)
#include "Engine/ultil/WinApi.h"    // класс WinApi (глобальный gWinApi)
#include "Engine/DMAudio/DMAudio.h" // звук: gDMAudio (init/update), skip_audio
#include "Engine/Sound/Sound.h"
#include "Game/Hud/Hud.h"
#include "Engine/Text/Text.h"     // движок: gSound, WavToPcm, PlaySample
#include "Game/Menu/Menu.h"         // класс Menu (gMenu), MenuPage, MenuEntry
#include "Game/Game/Game.h"         // класс Game (gGame)
#include "Engine/MapGm/MapGm.h"     // класс MapGm (gMapGm)
#include "Engine/MapRelatedStruct/MapRelatedStruct.h"
#include "Engine/Map/Map.h"
#include "Engine/Style/StyleTileLoader.h"
#include "Game/Player/Player.h"
#include "Game/Ped/Ped.h"
#include "Game/PedManager/PedManager.h"
#include "Game/CarsPrefabs/CarsPrefabs.h"
#include "Game/Car/Car.h"
#include "Engine/Object/Object.h"
extern PedManager gPedManager;
extern CarsPrefabs gCarsPrefabs;
#include "Engine/Registry/Registry.h" // регистр: gRegistry (настройки/язык)
#include "../MapGm/MapGm.h"
#include "../PlayerData/PlayerData.h"
#include "../Keybord/Keybord.h"
// Глобальные объекты реконструкции (определены в MENU/ULTIL-библиотеках).
extern Menu *gMenu;                 // меню игры: MenuPageArray, PlayerSlotSave и т.д.
extern Registry *gRegistry;         // реестр Windows: язык, настройки экрана/звука
extern WinApi *gWinApi;             // утилиты: CopyWideString, GetVersion и др.
extern Game *gGame;                 // игра: конструктор создаёт gText, gStyle и др. (Game.cpp)
extern MapRelatedStruct* gMapRelatedStruct;
extern bool  gSkipAudio;             // флаг "звук выключен" (определён в DMAudio.cpp)
extern int gAudioObject;           // тип звукового объекта (определён в Menu/Menu.cpp)
extern int gSampleRate;            // частота созданного аудио-объекта (DMAudio.cpp)
extern	HINSTANCE ghInstance;

int gDebugTileRot = 0;
int gDebugTileDump = 0;
DWORD	gMajor;
DWORD	gMinor;
bool    gPlayReplay;
bool	gDoTest;
bool	gSkipMission;
bool	gShowCycle;
bool	gDoBrianTest;
bool	gDoIainTest;
bool	gSkipTiles;
bool	gDoShowCounters;
bool	gDoShowCamera;
bool	gDoShowInput;
bool	gDoShowTiming;
bool	gDoShowCollisionBox;
bool	gDoShowPhysics;
bool	gDoShowImaginary;
bool	gSkipUser;
bool	gSkipTrafficLights;
bool	gSkipRecycling;
bool	gLogCollisions;
bool	gDoShowTrafficLightsInfo;
bool	gDoShowIds;
bool	gLimitRecycling;
bool	gNoAnnoyingChars;
bool	gSkipSlopes;
bool	gSkipLeft;
bool	gSkipRight;
bool	gSkipTop;
bool	gSkipBottom;
bool	gSkipLid;
bool	gLogRoutefinder;
bool	gDoMike;
bool	gSkipParticles;
bool	gShowHiddenFaces;
bool	gDoExitAfterReplay;
bool	gDontGetCarBack;
bool	gDoShowInstruments;
bool	gSkipAmbulance;
bool	gSkilPolice;
bool	gSkipFrontend;
bool	gShowAllArrows;
bool	gDoShowHorn;
bool	gSkipSkidMarks;
bool	gDoShowJuncIds;
bool	gDoCornerWindow;
bool	gDoInfiniteLives;
bool	gDoLoadSaveGame;
bool	gDoDebugKeys;
bool	gLogRandom;
bool	gLogRandomExtra;
bool	gLogInput;
bool	gLogDirectInput;
bool	gIgnoreReplayHeader;
bool	gSkipTrains;
bool	gSkipBuses;
bool	gSkipQuitConfirm;
bool	gDoSyncCheck;
bool	gSkipFireEngines;
bool	gShowBriefNumber;
bool    gSkipWindowCheck;
bool	gSkipReplaySyncCheck;
bool	gDoShowObjectIds;
bool	gGoKillPhonesOnAnswer;
bool	gDoMissLogging;
bool	gDoTextIdTest;
bool	gDoPolice1;
bool	gDoPolice2;
bool	gDoPolice3;
bool	gSkipDraw;
bool	gSkipDummies;
bool	gDoBlood;
bool	gDo3dSound;
bool	gTestFileGxt;
bool	gShowPlayerNames;
bool    gReplayToFile;
bool    gReplayActive;
bool	gSkipFrontend1;
bool    gSmallCar;
bool	gNopCheat;
bool	gInvisibility;
bool	gBonusAll;
bool	gGiveBasikWeapon;
bool	gElvis;
bool	gHealth99;
bool	gJailKey;
int	gActiveCheat;
bool gGiveMoney20k, gAllTower;
HANDLE  gHANDLE;
LPVOID* gDirectInput6;
//REFIID  gREFIID;


 HWND		gHWND;
int			gRenderDevice;
int			gVideoDevice;
int			gVideoPlay;
char		gData[256];
char		gVideo[255];
int			gGamma;
int			gTimer, gTime;
 byte		gControl;
//const char	gD3ddll[11];
//const char	gDmavideo[13];
char			gKeyBuffer[255];

char			 gLanguage[256];
unsigned char gNamePlayerASCII[80];
bool			 gNetworkGame;

int gWindowWidth, gWindowHeight;

int gFullWidth, gFullHeight;

int gStartMode;
int gTrippleBuffer;
void LoadConfig();














// ---------------------------------------------------------------------------
// Чтение строк меню из .gxt (бинарный формат текстов игры: GBL head + TKEY + TDAT).
// Формат подтверждён по bin/data/e.gxt и спецификации DMA/исходникам тулзов.
// ---------------------------------------------------------------------------
// Ищет в файле .gxt запись TKEY с именем key и возвращает её текст (UTF-16LE
// строка из блока TDAT). Если ключа нет или файл не читается - пустая строка.
static std::wstring GetGxtString(const char* gxtPath, const char* key)
{
  std::wstring result;
  FILE* f = fopen(gxtPath, "rb");
  if (!f)
    return result;

  // Читаем файл целиком в память.
  fseek(f, 0, SEEK_END);
  long sz = ftell(f);
  fseek(f, 0, SEEK_SET);
  if (sz < 8) { fclose(f); return result; }

  std::vector<unsigned char> d((size_t)sz);
  if (fread(d.data(), 1, (size_t)sz, f) != (size_t)sz) { fclose(f); return result; }
  fclose(f);

  // Заголовок 6 байт: "GBLx" + version(word). Далее именованные блоки
  // вида <4 буквы имени><4 байта размера><данные>. Ищем блоки TKEY и TDAT.
  long pos = 6;
  long tkeyOff = -1, tkeySize = 0, tdatOff = -1;
  while (pos + 8 <= sz) {
    char name[5] = { 0, 0, 0, 0, 0 };
    name[0] = (char)d[pos];
    name[1] = (char)d[pos + 1];
    name[2] = (char)d[pos + 2];
    name[3] = (char)d[pos + 3];
    unsigned int bsize = d[pos + 4] | (d[pos + 5] << 8) | (d[pos + 6] << 16) | ((unsigned int)d[pos + 7] << 24);
    if (std::strcmp(name, "TKEY") == 0) { tkeyOff = pos + 8; tkeySize = (long)bsize; }
    else if (std::strcmp(name, "TDAT") == 0) { tdatOff = pos + 8; }
    pos += 8 + (long)bsize;
  }
  if (tkeyOff < 0 || tdatOff < 0)
    return result; // нужных блоков нет - это невалидный .gxt

  // TKEY: таблица записей по 12 байт = смещение текста в TDAT (4 байта) + имя ключа (8 байт).
  for (long p = tkeyOff; p + 12 <= tkeyOff + tkeySize; p += 12) {
    unsigned int tofs = d[p] | (d[p + 1] << 8) | (d[p + 2] << 16) | ((unsigned int)d[p + 3] << 24);
    char kname[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    for (int i = 0; i < 8; i++)
      kname[i] = (char)d[p + 4 + i];
    if (std::strcmp(kname, key) != 0)
      continue; // ключ не наш - пропускаем запись

    // Строка в TDAT: UTF-16LE, терминируется парой байт 00 00.
    long sp = tdatOff + (long)tofs;
    long max = (long)sz - 1;
    std::vector<unsigned short> chars;
    while (sp + 1 <= max) {
      unsigned short u = d[sp] | (d[sp + 1] << 8);
      if (u == 0) break;
      chars.push_back(u);
      sp += 2;
    }
    result.assign(chars.begin(), chars.end());
    break;
  }
  return result;
}

// Рисование строки по центру указанной x-позиции на заданной y (не используется,
// сохранено как утилита на будущее).
static void DrawCenText(HDC hdc, const wchar_t* text, int cx, int y)
{
  SIZE s;
  GetTextExtentPoint32W(hdc, text, (int)wcslen(text), &s);
  TextOutW(hdc, cx - s.cx / 2, y, text, (int)wcslen(text));
}

// ---------------------------------------------------------------------------
// Геометрия экрана меню: две панели 640x480, как в оригинальной игре.
// ---------------------------------------------------------------------------
static const int MENU_W = 640;   // ширина экрана меню
static const int MENU_H = 480;   // высота экрана меню
static const int LEFT_W = 278;   // ширина левой панели (1_play.tga и т.п.)
static const int LEFT_H = 480;   // высота левой панели
static const int RIGHT_W = 362;  // ширина правой панели (1.tga, 2.tga, ...)
static const int RIGHT_H = 480;  // высота правой панели

// ---------------------------------------------------------------------------
// Класс приложения: окно + игровой цикл. Наследует cApplication (создание окна,
// Run()). Содержит вьюверную логику меню: фон, текст, навигация.
// ---------------------------------------------------------------------------
class cApp : public cApplication
{
  public:
    // Конструктор: окно фиксированного размера 640x480, без растягивания.
    cApp() { m_Style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
             m_Width = MENU_W; m_Height = MENU_H;
             m_testIndex = 0; m_testBankLoaded = false; m_testVocals = 0; m_inGame=false; m_debugPedSpawned=false; m_gameFrames=0; m_fps=0; m_debugCamX=128; m_debugCamY=128; m_debugCamZ=512; m_debugZoom=64;
              { const char* e=getenv("GTA2_CAM"); if(e){ int tx=128,ty=128,tz=512; if(sscanf(e,"%d,%d,%d",&tx,&ty,&tz)>=2){ m_debugCamX=tx; m_debugCamY=ty; if(tz>=0) m_debugCamZ=tz; } } } }

    BOOL Init();     // инициализация меню (загрузка данных, текст, фон)
    BOOL Frame();    // один кадр: ввод, навигация, отрисовка
    BOOL Shutdown(); // завершение
    // Перехват сообщений окна: собирает набираемый с клавиатуры текст (WM_CHAR) в очередь.
    LRESULT FAR PASCAL MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  private:
    void BlitGDIScaled();            // вывод RGBA-кадра в окно с масштабированием
    void RasterizeMenuText();        // вставка текста пунктов меню в RGBA-кадр
    void RenderBackground();         // сборка фона текущей страницы из .tga
    void SwitchPage(int page);       // переход на другую страницу меню
    void EditName(wchar_t ch);       // ввод символа в имя слота (поле PLAYER)
    int  MenuPicForPage() const;     // какой фон (MenuPic) у текущей страницы
    int  ItemCount() const;          // число пунктов на текущей странице

    std::vector<unsigned char> m_RGBA; // один экран меню 640x480 RGBA

    // Тексты пунктов страниц 0 и 1 из .gxt (запасной источник, пока Text::Bsearch - стаб).
    // Индексы: [страница][пункт].
    std::wstring m_fallbackText[2][5];
    int m_ActiveItem;  // активный пункт текущей страницы (рисуется красным)
    int m_CurrentPage; // номер текущей страницы меню (индекс MenuPageArray)

    std::vector<int> m_pageStack;  // стек переходов: куда возвращаться по Esc
    std::wstring     m_charQueue;  // очередь набранных символов (накапливается в MsgProc)
    int              m_playerSlot; // текущий слот игрока (0..7) = Menu::CurrentPlayerSlot
    bool             m_inGame;
    bool             m_debugPedSpawned = false;
    int              m_gameFrames;
    int              m_fps;
    int              m_debugCamX;
    int              m_debugCamY;
    int              m_debugCamZ;
    int              m_debugZoom;

    // ВРЕМЕННО: тест воспроизведения банка (клавиша S) и Vocals (клавиша W).
    // Доступ к голосам gSound и банкам движка - см. Frame().
    std::vector<std::string> m_vocalFiles; // список Vocals\*.wav (ленивый)
    int  m_testIndex;       // номер следующего звука банка
    bool m_testBankLoaded;  // банк для теста уже загружен
    int  m_testVocals;      // номер следующего файла Vocals
};

// ---------------------------------------------------------------------------
// Таблица соответствия "страница+пункт -> ключ .gxt". Используется, пока
// Text::Bsearch заглушена, чтобы пункты меню показывали реальный текст игры.
// Ключи взяты из исходников реконструкции (вызовы gText.Bsearch в меню).
// ---------------------------------------------------------------------------
struct MenuFallback { int page, entry; const char* key; };
static const MenuFallback kMenuFallback[] = {
  // Главное меню (страница 0)
  { 0, 0, "play" }, { 0, 1, "options" }, { 0, 2, "quit" },
  // Страница "В игру" (страница 1)
  { 1, 0, "charctr" }, { 1, 1, "savepos" }, { 1, 2, "hi_scre" },
  { 1, 3, "strtlev" }, { 1, 4, "bonslev" },
};

// Загрузка TGA-файла в буфер RGBA. Данные декодером cTGA уже перевёрнуты
// (top-down), поэтому координата Y на экране совпадает с порядком строк.
static bool LoadTGAtoRGBA(const char* path, std::vector<unsigned char>& out,
                          int& w, int& h)
{
  cTGA tga;
  if (!tga.Load((char*)path))
    return false;
  w = (int)tga.GetWidth();
  h = (int)tga.GetHeight();
  unsigned char* d = tga.GetData();
  if (!d || tga.GetBPP() != 32) // игра использует 32-битные TGA (BGRA)
    return false;
  out.assign(d, d + (size_t)w * h * 4);
  return true;
}

// Имена файлов фонов data\frontend\*.tga, соответствует массиву gPageFileMenu
// в оригинальной игре: индекс -> имя файла.
static const char* const kMenuTga[25] = {
  "1.tga", "1_Options.tga", "1_Play.tga", "1_Quit.tga", "2.tga",
  "2_Bonus1.tga", "2_Bonus2.tga", "2_Bonus3.tga", "2_League.tga", "2_Level1.tga",
  "2_Level2.tga", "2_Level3.tga", "2_Name.tga", "2_Restart.tga", "3.tga",
  "3_Tables.tga", "GameComplete.tga", "LevelComplete.tga", "MPLose.tga", "PlayerDead.tga",
  "Mask.tga", "Mask2.tga", "Credits.tga", "Mask3.tga", "DemoInfo.tga"
};

// Фон страницы (Menu::MenuPic, eMenuBackground) - номера рисунков меню.
enum {
  kPicOptions = 0, kPicPlay = 1, kPicQuit = 2, kPicMenuPic3 = 3, kPicMenuPic4 = 4,
  kPicMenuPic5 = 5, kPicVievHigh = 6, kPicStartLevel1 = 7, kPicLoadSave = 8,
  kPicStartLevel3 = 9, kPicPlayerName = 10, kPicRestart = 11, kPicHighScores = 12,
  kPicRIP = 13, kPicMenuPic14 = 14, kPicMenuPic15 = 15, kPicResumSave = 16, kPicTitle = 17
};

// Соответствие Menu::FindBackground: MenuPic -> (индекс левого файла, индекс правого файла)
// из таблицы kMenuTga. full=true означает, что левый файл рисуется на весь экран
// 640x480 (титры, "вы мертвы", таблица рекордов и т.п.) без правой панели.
static void MenuPicFiles(int pic, int& left, int& right, bool& full)
{
  switch (pic) {
    case kPicOptions:     left = 1;  right = 0; full = false; break; // 1_Options + 1
    case kPicPlay:        left = 2;  right = 0; full = false; break; // 1_Play + 1
    case kPicQuit:        left = 3;  right = 0; full = false; break; // 1_Quit + 1
    case kPicMenuPic3:    left = 5;  right = 4; full = false; break; // 2_Bonus1 + 2
    case kPicMenuPic4:    left = 6;  right = 4; full = false; break; // 2_Bonus2 + 2
    case kPicMenuPic5:    left = 7;  right = 4; full = false; break; // 2_Bonus3 + 2
    case kPicVievHigh:    left = 8;  right = 4; full = false; break; // 2_League + 2
    case kPicStartLevel1: left = 9;  right = 4; full = false; break; // 2_Level1 + 2
    case kPicLoadSave:    left = 10; right = 4; full = false; break; // 2_Level2 + 2
    case kPicStartLevel3: left = 11; right = 4; full = false; break; // 2_Level3 + 2
    case kPicPlayerName:  left = 12; right = 4; full = false; break; // 2_Name + 2
    case kPicRestart:     left = 13; right = 4; full = false; break; // 2_Restart + 2
    case kPicHighScores:  left = 15; right = 0; full = true;  break; // 3_Tables на весь экран
    case kPicRIP:         left = 19; right = 0; full = true;  break; // PlayerDead на весь экран
    case kPicMenuPic14:   left = 18; right = 0; full = true;  break; // MPLose на весь экран
    case kPicMenuPic15:   left = 16; right = 0; full = true;  break; // GameComplete на весь экран
    case kPicResumSave:   left = 17; right = 0; full = true;  break; // LevelComplete на весь экран
    case kPicTitle:       left = 22; right = 0; full = true;  break; // Credits на весь экран
    default:              left = 2;  right = 0; full = false; break; // по умолчанию 1_Play + 1
  }
}

// Поиск файла фона в возможных папках данных (запуск может идти из разных мест).
// Возвращает полный путь к файлу либо пустую строку, если файл не найден.
static std::string FindFrontendPath(const char* name)
{
  const char* candidates[] = { "data\\frontend",
                               "bin\\data\\frontend",
                               "..\\bin\\data\\frontend",
                               "C:\\work\\GTA2_RE\\bin\\data\\frontend" };
  for (int i = 0; i < 4; i++) {
    std::string p = std::string(candidates[i]) + "\\" + name;
    FILE* f = fopen(p.c_str(), "rb");
    if (f) { fclose(f); return p; }
  }
  return std::string();
}

// Список файлов Vocals (репліки игры, bin\data\audio\Vocals\*.wav). Нужен для
// временного теста декодера WavToPcm (клавиша W). Возвращает полные пути.
static void ListVocalsFiles(std::vector<std::string>& out)
{
  const char* dirs[] = { "data\\audio\\Vocals",
                         "bin\\data\\audio\\Vocals",
                         "..\\bin\\data\\audio\\Vocals",
                         "C:\\work\\GTA2_RE\\bin\\data\\audio\\Vocals" };
  for (int i = 0; i < 4 && out.empty(); i++) {
    std::string pat = std::string(dirs[i]) + "\\*.wav";
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pat.c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE)
      continue;
    do {
      out.push_back(std::string(dirs[i]) + "\\" + fd.cFileName);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
  }
}

// Сборка экрана фона страницы: левый файл копируется в x=0 шириной до LEFT_W,
// правый - в x=LEFT_W шириной до RIGHT_W. При full=true левый файл занимает
// весь экран 640x480. Результат кладётся в out (RGBA, 640x480x4).
static bool ComposeBackground(const char* leftName, const char* rightName, bool full,
                              std::vector<unsigned char>& out)
{
  std::string lp = FindFrontendPath(leftName);
  if (lp.empty())
    return false; // нет левой картинки - фон не собираем

  std::vector<unsigned char> left;
  int lw = 0, lh = 0;
  if (!LoadTGAtoRGBA(lp.c_str(), left, lw, lh))
    return false;
  if (lw <= 0 || lh <= 0)
    return false;

  // Чистим экран (чёрные поля, если картинки не совпадают по размеру).
  out.assign((size_t)MENU_W * MENU_H * 4, 0);

  // Режим "весь экран": копируем левую картинку целиком (с ограничением по размеру).
  if (full) {
    int cw = lw < MENU_W ? lw : MENU_W;
    int ch = lh < MENU_H ? lh : MENU_H;
    for (int y = 0; y < ch; y++)
      memcpy(&out[(size_t)y * MENU_W * 4], &left[(size_t)y * lw * 4], (size_t)cw * 4);
    return true;
  }

  // Левая панель в x=0.
  int cwl = lw < LEFT_W ? lw : LEFT_W;
  int chl = lh < LEFT_H ? lh : LEFT_H;
  for (int y = 0; y < chl; y++)
    memcpy(&out[(size_t)y * MENU_W * 4], &left[(size_t)y * lw * 4], (size_t)cwl * 4);

  // Правая панель в x=LEFT_W (если файл найден).
  std::string rp = FindFrontendPath(rightName);
  if (!rp.empty()) {
    std::vector<unsigned char> right;
    int rw = 0, rh = 0;
    if (LoadTGAtoRGBA(rp.c_str(), right, rw, rh)) {
      int cwr = rw < RIGHT_W ? rw : RIGHT_W;
      int chr = rh < RIGHT_H ? rh : RIGHT_H;
      for (int y = 0; y < chr; y++)
        memcpy(&out[((size_t)y * MENU_W + LEFT_W) * 4], &right[(size_t)y * rw * 4], (size_t)cwr * 4);
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// Инициализация приложения: построение данных меню, загрузка текстов из .gxt,
// подготовка слотов игроков, первичная отрисовка главного меню.
// ---------------------------------------------------------------------------
BOOL cApp::Init()
{
  strcpy(m_Caption, "GTA2");

  // Окно уже создано в Run() - настройки видео из реестра (в оригинале это пары
  // вызовов ConfigureDevice+ConfigureWindow из RestoreVideoDevices, FUN_004CC6A0):
  gWinApi->ConfigureVideoDevice();   // 0x004CB1D0: frame rate, освещение, exploding_on
  gWinApi->ConfigureVideoWindow();   // 0x004CB290: window/full размеры, start_mode, tripple

  // --- Загрузить тексты пунктов меню из .gxt (запасной источник для страниц 0 и 1) ---
  // (Text::Bsearch в реконструкции пока заглушена и возвращает пробел, поэтому
  //  читаем настоящие строки из файла e.gxt напрямую.)
  const char* gxtCandidates[] = { "bin\\data\\e.gxt",
                                  "data\\e.gxt",
                                  "C:\\work\\GTA2_RE\\bin\\data\\e.gxt" };
  std::string gxtPath;
  for (int i = 0; i < 3 && gxtPath.empty(); i++) {
    FILE* tf = fopen(gxtCandidates[i], "rb");
    if (tf) { fclose(tf); gxtPath = gxtCandidates[i]; }
  }
  // Проходим по таблице kMenuFallback и заполняем тексты нужных пунктов.
  if (!gxtPath.empty()) {
    for (size_t i = 0; i < sizeof(kMenuFallback) / sizeof(kMenuFallback[0]); i++) {
      if (kMenuFallback[i].page >= 0 && kMenuFallback[i].page < 2 &&
          kMenuFallback[i].entry >= 0 && kMenuFallback[i].entry < 5)
        m_fallbackText[kMenuFallback[i].page][kMenuFallback[i].entry] =
          GetGxtString(gxtPath.c_str(), kMenuFallback[i].key);
    }
  }
  // На случай если .gxt не найден - читаемые заглушки по умолчанию.
  const wchar_t* defs[2][5] = {
    { L"PLAY", L"OPTIONS", L"QUIT", L"", L"" },
    { L"PLAYER", L"RESUME SAVE", L"HIGH SCORES", L"START GAME", L"BONUSES" },
  };
  for (int p = 0; p < 2; p++)
    for (int e = 0; e < 5; e++)
      if (m_fallbackText[p][e].empty() && defs[p][e][0])
        m_fallbackText[p][e] = defs[p][e];

  // --- 8 слотов игроков (Menu::PlayerSlotSave[8]) ---
  // Текущий слот выбирается стрелками в поле PLAYER. Имена по умолчанию
  // PLAYER1..PLAYER8; они могут быть заменены загрузкой сохранений позже.
  m_playerSlot = gMenu->CurrentPlayerSlot;
  if (m_playerSlot < 0 || m_playerSlot > 7)
    m_playerSlot = 0;
  for (int s = 0; s < 8; s++) {
    wchar_t def[8];
    if (gMenu->PlayerSlotSave[s].PlayerName[0])
      continue; // имя уже есть (например, загружено из сохранения) - не трогаем
    swprintf(def, 8, L"PLAYER%d", s + 1);
    wcsncpy(gMenu->PlayerSlotSave[s].PlayerName, def, 7);
    gMenu->PlayerSlotSave[s].PlayerName[7] = 0;
  }

  // Начальная страница - главное меню. Активный пункт - как задано в данных
  // (SelectActiveElementDefault страницы).
  m_CurrentPage = 0;
  m_ActiveItem = gMenu->MenuPageArray[0].SelectActiveElementDefault;
  RenderBackground();   // собрать картинку фона из .tga
  RasterizeMenuText();  // вписать текст пунктов в кадр

  // окно уже создано в Run() - обновим заголовок с подсказками по управлению
  SetWindowTextA(GethWnd(), "GTA2");
  return TRUE;
}

// Завершение приложения (ничего освобождать не требуется - память статическая).
BOOL cApp::Shutdown()
{
  return TRUE;
}

// Сколько пунктов (элементов меню) на текущей странице. Берём из данных страницы
// CurentMenuPage (в каждой Create-функции ставится количество элементов),
// ограничиваем 10 - размером массива MenuEntryArray.
int cApp::ItemCount() const
{
  MenuPage& page = gMenu->MenuPageArray[m_CurrentPage];
  int n = (int)page.CurentMenuPage;
  if (n < 1 || n > 10)
    n = 0;
  return n;
}

// Какой фон (MenuPic) у текущей страницы. У страниц 0 и 1 фон зависит от выбранного
// пункта (как в оригинале: у главного меню фон меняется на PLAY/OPTIONS/QUIT),
// у остальных задан фиксированно по схеме исходного Menu::SetState.
int cApp::MenuPicForPage() const
{
  int pg = m_CurrentPage;
  int act = m_ActiveItem;
  switch (pg) {
    case 0:  return act == 0 ? kPicPlay : (act == 1 ? kPicOptions : kPicQuit);
    case 1:  return act == 0 ? kPicPlayerName
             : (act == 1 ? kPicRestart
                : (act == 2 ? kPicVievHigh : kPicStartLevel1));
    case 2:  return kPicRIP;                    // "Вы мертвы"
    case 3:
    case 6:
    case 7:
    case 11:
    case 14: return kPicResumSave;              // Level Complete
    case 4:
    case 10: return kPicMenuPic15;              // Game Complete
    case 5:  return kPicHighScores;             // Таблица рекордов
    default: return pg == 9 ? kPicTitle : kPicStartLevel1; // титры (9) или игра
  }
}

// Пересобрать фон текущей страницы: по MenuPicForPage выбираем файлы из kMenuTga
// и складываем их в RGBA-кадр m_RGBA. Вызывается при переходе на страницу и при
// смене активного пункта (для страниц 0 и 1 фон следует за пунктом).
void cApp::RenderBackground()
{
  int pic = MenuPicForPage();
  int left = 0, right = 0;
  bool full = false;
  MenuPicFiles(pic, left, right, full);
  ComposeBackground(kMenuTga[left], kMenuTga[right], full, m_RGBA);
}

// Переход на страницу меню. Аналог Menu::InitializeState: сохраняем номер страницы
// в gMenu, выбираем активный пункт по данным страницы, пересобираем фон и текст.
void cApp::SwitchPage(int page)
{
  if (page < 0 || page > 15)
    return;
  m_CurrentPage = page;
  gMenu->PageNumber = page;  // номер страницы в данных меню (как в оригинале)
  gMenu->State = page;       // и в состоянии фронтенда
  m_ActiveItem = gMenu->MenuPageArray[page].SelectActiveElementDefault;
  int cnt = ItemCount();
  if (m_ActiveItem < 0 || m_ActiveItem >= cnt)
    m_ActiveItem = 0;
  gMenu->MenuPageArray[page].SelectActiveElementDefault = m_ActiveItem;
  RenderBackground();
  RasterizeMenuText();
}

// Вывод RGBA-кадра m_RGBA в клиентскую область окна с масштабированием и
// сохранением пропорций (чёрные поля сверху/снизу или слева/справа).
// Чистый GDI (без DirectDraw) - работает и под RDP.
void cApp::BlitGDIScaled()
{
  HWND hwnd = GethWnd();
  if (!hwnd || m_RGBA.empty())
    return;

  HDC hdc = GetDC(hwnd);
  if (!hdc)
    return;

  // Размер клиентской области (что рисуем, если окно ресайзнули).
  RECT cr;
  GetClientRect(hwnd, &cr);
  int cw = cr.right - cr.left;
  int ch = cr.bottom - cr.top;
  if (cw <= 0 || ch <= 0) {
    ReleaseDC(hwnd, hdc);
    return;
  }

  // DIB-секция экрана меню 640x480, 32 бита на пиксель (RGBA, top-down).
  BITMAPINFO bi;
  ZeroMemory(&bi, sizeof(bi));
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = MENU_W;
  bi.bmiHeader.biHeight = -MENU_H; // top-down: данные уже перевёрнуты декодером TGA
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = 32;
  bi.bmiHeader.biCompression = BI_RGB;

  // Копируем наш кадр в DIB и растягиваем в окно, сохраняя пропорции.
  HDC memdc = CreateCompatibleDC(hdc);
  void* bits = NULL;
  HBITMAP bmp = CreateDIBSection(memdc, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
  if (bmp && bits) {
    memcpy(bits, m_RGBA.data(), (size_t)MENU_W * MENU_H * 4);

    // масштаб с сохранением пропорций (минимальный из двух)
    double sx = (double)cw / MENU_W;
    double sy = (double)ch / MENU_H;
    double s = sx < sy ? sx : sy;
    int dw = (int)(MENU_W * s);
    int dh = (int)(MENU_H * s);
    int dx = (cw - dw) / 2; // центрирование по горизонтали
    int dy = (ch - dh) / 2; // центрирование по вертикали

    HGDIOBJ old = SelectObject(memdc, bmp);
    HBRUSH black = (HBRUSH)GetStockObject(BLACK_BRUSH);
    RECT full = { 0, 0, cw, ch };
    FillRect(hdc, &full, black);   // фон вокруг картинки - чёрный
    SetStretchBltMode(hdc, COLORONCOLOR);
    StretchBlt(hdc, dx, dy, dw, dh, memdc, 0, 0, MENU_W, MENU_H, SRCCOPY);
    SelectObject(memdc, old);
    DeleteObject(bmp);
  }
  DeleteDC(memdc);
  ReleaseDC(hwnd, hdc);
}

// Вставка текста пунктов меню в RGBA-кадр (прямо в пиксели m_RGBA).
// Рисуется в память через GDI (шрифт Arial), чтобы текст был частью картинки
// и гарантированно отображался при масштабировании в BlitGDIScaled.
// Активный пункт - красным, остальные - белым.
void cApp::RasterizeMenuText()
{
  if (m_RGBA.empty())
    return;

  HDC hdc = CreateCompatibleDC(NULL);
  if (!hdc)
    return;

  // DIB-секция 640x480, в неё рисуем текст, потом копируем обратно в m_RGBA.
  BITMAPINFO bi;
  ZeroMemory(&bi, sizeof(bi));
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = MENU_W;
  bi.bmiHeader.biHeight = -MENU_H; // top-down
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = 32;
  bi.bmiHeader.biCompression = BI_RGB;

  void* bits = NULL;
  HBITMAP bmp = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &bits, NULL, 0);
  if (bmp && bits) {
    memcpy(bits, m_RGBA.data(), (size_t)MENU_W * MENU_H * 4);

    HGDIOBJ oldBmp = SelectObject(hdc, bmp);
    HGDIOBJ oldFont = NULL;
    // Шрифт пунктов меню (12px, жирный, Arial).
    HFONT font = CreateFontA(-12, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    if (font) oldFont = SelectObject(hdc, font);

    SetBkMode(hdc, TRANSPARENT);          // прозрачный фон текста
    SetTextColor(hdc, RGB(255, 255, 255)); // по умолчанию белый

    // Пункты текущей страницы берём из MenuPageArray[m_CurrentPage]:
    //   TextMenuElementArray - текст пункта, X/Y - координаты (X из MenuEntryArray,
    //   Y из MenuItemArray - реальные позиции в реконструкции).
    MenuPage& page = gMenu->MenuPageArray[m_CurrentPage];
    int cnt = ItemCount();
    for (int i = 0; i < cnt; i++) {
      const wchar_t* txt = page.MenuEntryArray[i].TextMenuElementArray;

      // Поле PLAYER (2-я страница, пункт 0) - вместо текста из .gxt показываем
      // имя текущего слота из Menu::PlayerSlotSave.
      if (m_CurrentPage == 1 && i == 0)
        txt = gMenu->PlayerSlotSave[m_playerSlot].PlayerName;
      else if (!txt || !*txt || *txt == L' ') {
        // Стаб Text::Bsearch даёт пробел - берём текст из e.gxt по таблице ключей.
        if (m_CurrentPage >= 0 && m_CurrentPage < 2 && i >= 0 && i < 5 &&
            !m_fallbackText[m_CurrentPage][i].empty())
          txt = m_fallbackText[m_CurrentPage][i].c_str();
        else
          continue; // текста нет (например, не построенная страница) - не рисуем
      }

      int x = (int)page.MenuEntryArray[i].X; // горизонтальная позиция (правая панель)
      int y = (int)page.MenuItemArray[i].Y;  // вертикальная позиция
      // Активный пункт - красным, остальные белым.
      SetTextColor(hdc, (i == m_ActiveItem) ? RGB(255, 0, 0) : RGB(255, 255, 255));
      SIZE sz;
      GetTextExtentPoint32W(hdc, txt, (int)wcslen(txt), &sz);
      TextOutW(hdc, x, y - sz.cy / 2, txt, (int)wcslen(txt)); // вертикально по центру
    }

    // Стрелки списка имён у поля PLAYER (2-я страница): слева/справа от имени.
    // Позиции соответствуют стрелкам GUI[8]/[9] в оригинале (X=290 и 580, Y=222).
    if (m_CurrentPage == 1) {
      int ay = (int)page.MenuItemArray[0].Y;
      SetTextColor(hdc, RGB(255, 255, 255));
      TextOutW(hdc, 290, ay - 6, L"<", 1);
      TextOutW(hdc, 580, ay - 6, L">", 1);
    }

    // Версия игры в правом нижнем углу (только на главном меню - как в оригинале).
    // Данные через WinApi::GetVersion (читает ресурс GTA2.EXE), формат из исходников:
    // строка в оригинале - "A2 V%d.%d".
    if (m_CurrentPage == 0) {
      DWORD vmajor = 0, vminor = 0;
      gWinApi->GetVersion(&vmajor, &vminor);
      wchar_t vbuf[32];
      swprintf(vbuf, 32, L"A2 V%d.%d", vmajor, vminor);
      SetTextColor(hdc, RGB(255, 255, 255));
      SIZE vsz;
      GetTextExtentPoint32W(hdc, vbuf, (int)wcslen(vbuf), &vsz);
      TextOutW(hdc, MENU_W - vsz.cx - 8, MENU_H - vsz.cy - 8, vbuf, (int)wcslen(vbuf));
    }

    // Восстановление состояния GDI и копирование текста обратно в кадр.
    if (font) { SelectObject(hdc, oldFont); DeleteObject(font); }
    SelectObject(hdc, oldBmp);
    memcpy(m_RGBA.data(), bits, (size_t)MENU_W * MENU_H * 4);
    DeleteObject(bmp);
  }
  DeleteDC(hdc);
}

// Перехват сообщений окна. Собираем набираемый текст (WM_CHAR) в очередь,
// чтобы обработать его в Frame (поле ввода имени на 2-й странице). Остальные
// сообщения передаём базовому классу (DefWindowProc).
LRESULT FAR PASCAL cApp::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (uMsg == WM_CHAR) {
    wchar_t c = (wchar_t)wParam;
    // Полезные символы: печатные (ASCII 32..126) и Backspace (8). Остальное игнорируем.
    if (c == L'\b' || (c >= 32 && c < 127)) {
      if (m_charQueue.size() < 32)
        m_charQueue += c;
    }
    return 0;
  }
  return cApplication::MsgProc(hWnd, uMsg, wParam, lParam);
}

// Ввод символа в имя текущего слота (поле PLAYER, 2-я страница, пункт 0).
// Имя хранится в gMenu.PlayerSlotSave[m_playerSlot].PlayerName - буфер 8 wchar_t
// (7 символов + завершающий 0), как в структуре PlayerSlotSlave оригинала.
void cApp::EditName(wchar_t ch)
{
  bool editing = (m_CurrentPage == 1 && m_ActiveItem == 0);
  if (!editing)
    return;
  wchar_t* name = gMenu->PlayerSlotSave[m_playerSlot].PlayerName;
  size_t len = wcslen(name);
  if (ch == L'\b') {
    // Backspace: удалить последний символ.
    if (len > 0)
      name[len - 1] = 0;
  } else if (ch >= 32 && ch < 127) {
    // Печатный символ: добавить в конец, но не больше 7 символов.
    if (len < 7)
      name[len] = (wchar_t)ch;
    else
      return;
  } else {
    return; // остальные служебные символы игнорируем
  }
  name[7] = 0; // страховочный терминирующий ноль
  RasterizeMenuText(); // показать обновлённое имя в кадре
}

// ---------------------------------------------------------------------------
// Один кадр игрового цикла: обработка очереди набранного текста, Esc,
// навигация (Up/Down/Left/Right), выбор пункта (Enter), вывод кадра на экран.
// ---------------------------------------------------------------------------
BOOL cApp::Frame()
{
  HWND hwnd = GethWnd();

  if (!gSkipAudio && gDMAudio)
    gDMAudio->PollAllSamples();

  if (m_inGame) {
    if (GetAsyncKeyState(VK_ESCAPE) & 1) {
      m_inGame = false;
      if (!gSkipAudio) gSound.StopAll(); // guarded pragmatic: stop game audio on menu return
      SetWindowTextA(hwnd, "GTA2");
      SwitchPage(0);
      Sleep(16);
      return TRUE;
    }
    int camStep = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? 4 : 1;
    static bool s_manualCam = false;
    if (GetAsyncKeyState('C') & 1) { s_manualCam = !s_manualCam; }
    bool moved = false;
    if (GetAsyncKeyState(VK_LEFT)  & 0x8000) { m_debugCamX -= camStep; moved = true; }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_debugCamX += camStep; moved = true; }
    if (GetAsyncKeyState(VK_UP)    & 0x8000) { m_debugCamY -= camStep; moved = true; }
    if (GetAsyncKeyState(VK_DOWN)  & 0x8000) { m_debugCamY += camStep; moved = true; }
    if (moved) s_manualCam = true;
    int zStep = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? 16 : 1;
    if (GetAsyncKeyState(VK_PRIOR) & 0x8000) { m_debugCamZ += zStep; if (m_debugCamZ > 1024) m_debugCamZ = 1024; }
    if (GetAsyncKeyState(VK_NEXT)  & 0x8000) { m_debugCamZ -= zStep; if (m_debugCamZ < 0) m_debugCamZ = 0; }
    if (GetAsyncKeyState(VK_OEM_PLUS) & 1 || GetAsyncKeyState(VK_ADD) & 1) { if (m_debugZoom < 1024) m_debugZoom *= 2; }
    if (GetAsyncKeyState(VK_OEM_MINUS) & 1 || GetAsyncKeyState(VK_SUBTRACT) & 1) { if (m_debugZoom > 4) m_debugZoom /= 2; }
    // Debug audio: B plays next sample from bil/ste bank (guarded).
    if (GetAsyncKeyState('B') & 1 && !gSkipAudio) {
      static bool s_audioBankLoaded = false;
      static int s_audioIdx = 0;
      if (!s_audioBankLoaded) {
        if (gSound.LoadBank("bil") <= 0) gSound.LoadBank("ste");
        s_audioBankLoaded = true;
      }
      int n = gSound.GetSampleCount();
      if (n > 0) { gSound.StopAll(); gSound.PlaySample(s_audioIdx % n, false); s_audioIdx++; }
    }
    // Debug audio: N toggles/plays a short ambient-style loop sample (guarded).
    if (GetAsyncKeyState('N') & 1 && !gSkipAudio) {
      static bool s_loopOn = false;
      int n = gSound.GetSampleCount();
      if (n > 0) {
        if (s_loopOn) { gSound.StopAll(); s_loopOn = false; }
        else { gSound.PlaySample(1 % n, true); s_loopOn = true; }
      }
    }
    // Debug tile orientation: R rotates +90deg CW, K confirms/logs selection.
    extern int gDebugTileRot;
    extern int gDebugTileDump;
    if (GetAsyncKeyState('R') & 1) {
      gDebugTileRot = (gDebugTileRot + 1) & 3;
      gDebugTileDump = 1;
      FILE* tf = fopen("gta2_tile_rot.log", "a");
      if (tf) { fprintf(tf, "ROTATE key=R rot=%d deg=%d cam=%d,%d zm=%d\n", gDebugTileRot, gDebugTileRot*90, m_debugCamX,m_debugCamY,m_debugZoom); fclose(tf); }
    }
    if (GetAsyncKeyState('K') & 1) {
      gDebugTileDump = 1;
      FILE* tf = fopen("gta2_tile_rot.log", "a");
      if (tf) { fprintf(tf, "CONFIRM key=K rot=%d deg=%d cam=%d,%d zm=%d\n", gDebugTileRot, gDebugTileRot*90, m_debugCamX,m_debugCamY,m_debugZoom); fclose(tf); }
      OutputDebugStringA("GTA2_TILE_ROT_CONFIRMED\n");
    }
    // Try to follow real player camera when available, unless user manually moved debug camera.
    // Guarded: only AuxGameCamera (known offset in dllLoad struct); avoid MainPed position until layout verified.
    if (!s_manualCam && gGame && gGame->PlayerMain) {
      Player* pl = gGame->PlayerMain;
      int px = pl->AuxGameCameraX;
      int py = pl->AuxGameCameraY;
      auto tryCam=[&](int wx,int wy)->bool{
        if (wx <= 0 || wy <= 0) return false;
        int tx = wx / 16384;
        int ty = wy / 16384;
        if (tx >= 0 && tx < 256 && ty >= 0 && ty < 256 && wx < 256 * 16384 && wy < 256 * 16384) { m_debugCamX=tx; m_debugCamY=ty; return true; }
        return false;
      };
      bool camOk = tryCam(px,py) || tryCam(pl->Camera_X_View, pl->Camera_Y_View);
      if (!camOk && pl->MainPed) {
        // DEBUG/local-layout fallback only: our Ped.PositionX/Y are local fields, not IDA-verified.
        tryCam(pl->MainPed->PositionX, pl->MainPed->PositionY);
      }
    }
    if (m_debugCamX < 0) m_debugCamX = 0; if (m_debugCamX > 255) m_debugCamX = 255;
    if (m_debugCamY < 0) m_debugCamY = 0; if (m_debugCamY > 255) m_debugCamY = 255;
    if (gGame) {
      int keep = gGame->RunFrame();
      m_gameFrames++;
      static DWORD s_fpsLast = 0; static int s_fpsFrames = 0;
      if (s_fpsLast == 0) s_fpsLast = GetTickCount();
      ++s_fpsFrames;
      DWORD s_fpsNow = GetTickCount();
      if (s_fpsNow - s_fpsLast >= 1000) { m_fps = (int)(s_fpsFrames * 1000u / (unsigned)(s_fpsNow - s_fpsLast)); s_fpsFrames = 0; s_fpsLast = s_fpsNow; }
      if (!keep) { m_inGame = false; SetWindowTextA(hwnd, "GTA2"); SwitchPage(0); }
      // DEBUG: guarded one-time spawn to exercise entity overlay/tick pipeline.
      // Uses our local struct layout only; not IDA-accurate spawn/init.
      if (!m_debugPedSpawned && gGame->PlayerMain) {
        m_debugPedSpawned = true;
        Ped* dp = gPedManager.GetPed();
        if (dp) {
          dp->PositionX = m_debugCamX * 16384;
          dp->PositionY = m_debugCamY * 16384;
          dp->PositionZ = 0;
          gGame->PlayerMain->MainPed = dp;
        }
      }
      // In-game visual: top-down map grid from loaded DMAP when available.
      if (m_RGBA.size() >= (size_t)MENU_W * MENU_H * 4) {
        for (size_t i = 0; i < (size_t)MENU_W * MENU_H; ++i) {
          m_RGBA[i*4+0] = 22; m_RGBA[i*4+1] = 14; m_RGBA[i*4+2] = 10; m_RGBA[i*4+3] = 255;
        }
        bool drewMap = false;
        if (gMapRelatedStruct) {
          Map* m = gMapRelatedStruct->getMap();
          if (m) {
            const int tilePx = m_debugZoom > 0 ? m_debugZoom : 16;
            const int viewW = MENU_W / tilePx;  // 40
            const int viewH = (MENU_H - 32) / tilePx; // 28
            const int ox = 0, oy = 32;
            int camX = m_debugCamX - viewW/2;
            int camY = m_debugCamY - viewH/2;
            if (camX < 0) camX = 0; if (camY < 0) camY = 0;
            if (camX > 256-viewW) camX = 256-viewW;
            if (camY > 256-viewH) camY = 256-viewH;
            const unsigned int* base = (const unsigned int*)m->FileLoad;
            const unsigned char* colBuf = (const unsigned char*)m->field_40008;
            const unsigned char* blkBuf = (const unsigned char*)m->field_4000C;
            const unsigned int columnWords = (unsigned int)m->File;
            const unsigned int numBlocks = (unsigned int)m->field_40004;
            const bool hasTiles = StyleTiles_Ready();
            if (colBuf && blkBuf && columnWords > 0) {
              for (int vy=0; vy<viewH; ++vy) {
                int my = camY + vy;
                for (int vx=0; vx<viewW; ++vx) {
                  int mx = camX + vx;
                  unsigned int bi = base[my*256+mx];
                  unsigned char fallbackR=10,fallbackG=14,fallbackB=22;
                  // UV remap tables extracted from GTA2.exe (PE .data). IDA: RenderBlockLid/Left/Right/Slopes use (face>>13)&7.
                  static const unsigned int kUV_593154[8] = {0,8,32,40,64,72,96,104}; // lid
                  static const unsigned int kUV_593194[8] = {37,53,69,85,101,117,5,21}; // left
                  static const unsigned int kUV_5931B4[8] = {101,117,5,21,37,53,69,85}; // right
                  static const unsigned int kUV_5931D4[8] = {5,13,37,45,69,77,101,109}; // top/center
                  static const unsigned int kUV_593134[8] = {2,10,34,42,66,74,98,106}; // bottom
                  static const unsigned int kUV_5930D4[8] = {35,51,67,83,99,115,3,19};
                  static const unsigned int kUV_5930F4[8] = {100,116,4,20,36,52,68,84};
                  struct DbgFace { unsigned short face; unsigned char rot; bool flipX; bool flipY; unsigned char slope; bool side; unsigned char arrows; int z; unsigned char height; };
                  auto uvToOrient=[&](unsigned int uv, unsigned char& rot, bool& fx, bool& fy){
                    // Decode from original UV/flag tables (593154/593194/5931B4/5931D4/5930D4/5930F4).
                    // Values encode flip/rot bits used by gbh_DrawTile/DrawTilePart: 0x20/0x40/0x60 rotation,
                    // 0x08/0x10 flips (0x40 case xors 0x18 in DrawTilePart), 0x80 flat flag added by renderer.
                    fx=false; fy=false; rot=0;
                    unsigned int v = uv & 0xFFu;
                    bool flat = (v & 0x80u) != 0; (void)flat;
                    unsigned int rbits = v & 0x60u;
                    if (rbits == 0x20u) { rot = 1; }
                    else if (rbits == 0x60u) { rot = 3; }
                    else if (rbits == 0x40u) { rot = 0; fx = true; fy = true; } // DrawTilePart: flags^0x18
                    else { rot = 0; }
                    if (v & 0x08u) fx = !fx;
                    if (v & 0x10u) fy = !fy;
                    // Remaining low bits (1,2,4) appear in table variants; keep as extra quarter-turn hints.
                    if (v & 0x04u) rot = (unsigned char)((rot + 1) & 3u);
                    if (v & 0x01u) rot = (unsigned char)((rot + 3) & 3u);
                    if (v & 0x02u) fx = !fx;
                    extern int gDebugTileRot;
                    rot = (unsigned char)((rot + (gDebugTileRot & 3)) & 3u);
                  };
                  DbgFace faces[8]; int faceN = 0;
                  int selectedTopZ = 0;
                  if (bi < columnWords) {
                    const unsigned char* col = colBuf + (size_t)bi * 4u;
                    unsigned char height = col[0], offset = col[1];
                    selectedTopZ = (int)height;
                    if (offset <= 8 && height <= 8 && height >= offset) {
                      int zStart = (int)height - 1;
                      if (zStart > m_debugCamZ) zStart = m_debugCamZ;
                      for (int z = zStart; z >= (int)offset && faceN < 8; --z) {
                        unsigned int wordIdx = bi + 1u + (unsigned int)(z - offset);
                        if (wordIdx >= columnWords) break;
                        unsigned int blockId = *(const unsigned int*)(colBuf + (size_t)wordIdx * 4u);
                        if (blockId >= numBlocks) continue;
                        const unsigned char* b = blkBuf + (size_t)blockId * 12u;
                        unsigned short left = *(const unsigned short*)(b+0);
                        unsigned short right= *(const unsigned short*)(b+2);
                        unsigned short top  = *(const unsigned short*)(b+4);
                        unsigned short bottom=*(const unsigned short*)(b+6);
                        unsigned short lid  = *(const unsigned short*)(b+8);
                        unsigned char arrows=b[10], slope=b[11];
                        if (left|right|top|bottom|lid|arrows|slope) {
                          unsigned short face = lid;
                          bool sideFace = false;
                          const unsigned int* uvTab = kUV_593154; // lid default
                          if (!face) { face = top; sideFace = face != 0; uvTab = kUV_5931D4; }
                          if (!face) { face = left; sideFace = face != 0; uvTab = kUV_593194; }
                          if (!face) { face = right; sideFace = face != 0; uvTab = kUV_5931B4; }
                          if (!face) { face = bottom; sideFace = face != 0; uvTab = kUV_593134; }
                          unsigned short remapFace = StyleTiles_GetRemappedTile(face & 1023u);
                          if ((face & 1023u) != 0 && remapFace == 0) continue; // original get_tile_by_id -> 0 means empty
                          DbgFace df{};
                          df.face=face; df.slope=slope; df.side=sideFace; df.arrows=arrows; df.z=z; df.height=height;
                          unsigned int uv = uvTab[(face >> 13) & 7u];
                          if (face & 0x1000u) uv |= 0x80u; // flat flag bit, as in RenderBlockLid
                          uvToOrient(uv, df.rot, df.flipX, df.flipY);
                          if (face & 0x2000u) df.flipX = !df.flipX; // RenderBlockSlopes uses 0x2000 for flip
                          faces[faceN++] = df;
                          if (faceN == 1) {
                            bool faceFlat = (face & 0x1000u) != 0;
                            if (sideFace && !faceFlat) { fallbackR = (unsigned char)(fallbackR * 14 / 16); fallbackG = (unsigned char)(fallbackG * 14 / 16); fallbackB = (unsigned char)(fallbackB * 14 / 16); }
                            switch (slope & 0xFC) {
                              case 0xB4: fallbackG = (unsigned char)(fallbackG * 15 / 16); break;
                              case 0xB8: fallbackR = (unsigned char)(fallbackR * 15 / 16); break;
                              case 0xBC: fallbackB = (unsigned char)(fallbackB * 15 / 16); break;
                              case 0xC0: fallbackR = (unsigned char)(fallbackR * 15 / 16); fallbackB = (unsigned char)(fallbackB * 15 / 16); break;
                              default: if (slope & 0xFC) { fallbackR = (unsigned char)(fallbackR * 14 / 16); fallbackG = (unsigned char)(fallbackG * 14 / 16); fallbackB = (unsigned char)(fallbackB * 15 / 16); } break;
                            }
                            if (z > 1) { int add = z*2; if (add>40) add=40; int rr=fallbackR+add, gg=fallbackG+add; fallbackR=(unsigned char)(rr>255?255:rr); fallbackG=(unsigned char)(gg>255?255:gg); }
                          }
                        }
                      }
                    }
                  }
                  static int s_tileTraceN = 0;
                  extern int gDebugTileDump;
                  bool doTrace = (getenv("GTA2_TILE_TRACE") && s_tileTraceN < 200) || (gDebugTileDump != 0);
                  if (doTrace) {
                    int cdx = vx - viewW/2, cdy = vy - viewH/2;
                    static int s_loggedMx=-9999, s_loggedMy=-9999, s_loggedZm=-1;
                    if (gDebugTileDump || (cdx >= -1 && cdx <= 1 && cdy >= -1 && cdy <= 1 && (mx!=s_loggedMx || my!=s_loggedMy || tilePx!=s_loggedZm || s_tileTraceN < 9))) {
                      FILE* tf = fopen("gta2_tile_trace.log", "a");
                      if (tf) {
                        unsigned short lidW=0,topW=0,leftW=0,rightW=0,botW=0; unsigned char arrB=0,slpB=0;
                        if (bi < columnWords) {
                          const unsigned char* col = colBuf + (size_t)bi * 4u;
                          unsigned char heightC=col[0], offsetC=col[1];
                          if (offsetC<=8 && heightC<=8 && heightC>=offsetC) {
                            int zz = heightC-1; if (zz>m_debugCamZ) zz=m_debugCamZ;
                            for (int zf=zz; zf>= (int)offsetC; --zf) {
                              unsigned int wi = bi + 1u + (unsigned int)(zf-offsetC);
                              if (wi>=columnWords) break;
                              unsigned int bid = *(const unsigned int*)(colBuf + (size_t)wi*4u);
                              if (bid>=numBlocks) continue;
                              const unsigned char* bb2p = blkBuf + (size_t)bid*12u;
                              leftW=*(const unsigned short*)(bb2p+0); rightW=*(const unsigned short*)(bb2p+2); topW=*(const unsigned short*)(bb2p+4); botW=*(const unsigned short*)(bb2p+6); lidW=*(const unsigned short*)(bb2p+8); arrB=bb2p[10]; slpB=bb2p[11];
                              break;
                            }
                          }
                        }
                        fprintf(tf, "TILE mx=%d my=%d cam=%d,%d,%d zm=%d bi=%u colH=%d colOff=%d blkL=0x%04X R=0x%04X T=0x%04X B=0x%04X Lid=0x%04X arr=0x%02X slp=0x%02X\n", mx,my,m_debugCamX,m_debugCamY,m_debugCamZ,tilePx,bi,(int)(bi<columnWords?colBuf[(size_t)bi*4u]:255),(int)(bi<columnWords?colBuf[(size_t)bi*4u+1]:255),leftW,rightW,topW,botW,lidW,arrB,slpB);
                        for (int fi=0; fi<faceN; ++fi) {
                          const DbgFace& df=faces[fi];
                          unsigned int virt2=df.face&1023u; unsigned short remap2=StyleTiles_GetRemappedTile(virt2);
                          fprintf(tf, " FACE i=%d face=0x%04X virt=%u remap=%u phys=%u rot=%u fx=%d fy=%d side=%d slope=0x%02X arrows=0x%02X z=%d h=%d\n", fi, (unsigned)df.face, virt2, (unsigned)remap2, (unsigned)StyleTiles_GetPhysPalForTile(remap2?remap2:virt2), (unsigned)df.rot, df.flipX?1:0, df.flipY?1:0, df.side?1:0, (unsigned)df.slope, (unsigned)df.arrows, df.z, (unsigned)df.height);
                        }
                        fclose(tf); s_tileTraceN++; s_loggedMx=mx; s_loggedMy=my; s_loggedZm=tilePx;
                      }
                    }
                  }
                  for (int py=0; py<tilePx; ++py) {
                    for (int px=0; px<tilePx; ++px) {
                      int sx = ox + vx*tilePx + px;
                      int sy = oy + vy*tilePx + py;
                      if ((unsigned)sx >= MENU_W || (unsigned)sy >= MENU_H) continue;
                      unsigned char r=fallbackR,g=fallbackG,bb=fallbackB;
                      bool drewFace = false;
                      for (int fi = 0; fi < faceN; ++fi) {
                        const DbgFace& df = faces[fi];
                        if (!df.face) continue;
                        unsigned int virt2 = (unsigned int)(df.face & 1023u);
                        unsigned short remap2 = StyleTiles_GetRemappedTile(virt2);
                        if (virt2 != 0 && remap2 == 0) continue; // original get_tile_by_id -> 0 means empty
                        unsigned int tileId2 = (unsigned int)remap2;
                        unsigned short phys2 = StyleTiles_GetPhysPalForTile(tileId2);
                        const unsigned char* pal2 = StyleTiles_GetPhysPalette((unsigned int)phys2);
                        if (!pal2) continue;
                        int tx = (px * 64) / tilePx;
                        int ty = (py * 64) / tilePx;
                        unsigned char idx = StyleTiles_SamplePixel(tileId2, tx, ty, df.flipX, df.flipY, df.rot);
                        if (idx == 0) continue; // GTA2 style: colour 0 is transparent
                        unsigned char rr0 = pal2[idx*4 + 0];
                        unsigned char gg0 = pal2[idx*4 + 1];
                        unsigned char bb0 = pal2[idx*4 + 2];
                        bool faceFlat = (df.face & 0x1000u) != 0;
                        if (df.side && !faceFlat) {
                          int wallH = tilePx/3 + (df.height - df.z) * (tilePx/10);
                          if (wallH < tilePx/4) wallH = tilePx/4;
                          if (wallH > tilePx*2/3) wallH = tilePx*2/3;
                          if (py > tilePx - wallH) { rr0=(unsigned char)(rr0*10/16); gg0=(unsigned char)(gg0*10/16); bb0=(unsigned char)(bb0*10/16); }
                        } else if (!faceFlat && py > tilePx * 3 / 4) {
                          rr0 = (unsigned char)(rr0 * 13 / 16); gg0 = (unsigned char)(gg0 * 13 / 16); bb0 = (unsigned char)(bb0 * 13 / 16);
                        }
                        r=rr0; g=gg0; bb=bb0; drewFace = true;
                        if (fi == 0) {
                          unsigned char sfc = (unsigned char)(df.slope & 0xFCu);
                          if (sfc==0xB4 || sfc==0xB8 || sfc==0xBC || sfc==0xC0) {
                            int diag = (sfc==0xB4) ? (px - (tilePx-1-py))
                                     : (sfc==0xB8) ? (px - py)
                                     : (sfc==0xBC) ? ((tilePx-1-px) - py)
                                     : ((tilePx-1-px) - (tilePx-1-py));
                            if (diag > 0) { r=(unsigned char)(r*14/16); g=(unsigned char)(g*14/16); bb=(unsigned char)(bb*14/16); }
                            else if (diag == 0 && tilePx >= 8) { r=235; g=235; bb=235; }
                          }
                          if (df.arrows && px >= tilePx/2-1 && px <= tilePx/2 && py >= tilePx/2-1 && py <= tilePx/2) { r=255; g=240; bb=120; }
                          if (df.z > 0 && py==0 && tilePx>=8) { int a=df.z*3; r=(unsigned char)((r+a>255)?255:r+a); g=(unsigned char)((g+a>255)?255:g+a); bb=(unsigned char)((bb+a>255)?255:bb+a); }
                        }
                        break;
                      }
                      if (!drewFace && faceN > 0) { /* keep fallback */ }
                      // Height edge cues: darken bottom/right edges when this column is higher than neighbor.
                      if (selectedTopZ > 0 && tilePx >= 8) {
                        if (py >= tilePx-1) {
                          int nmy = camY + vy + 1;
                          if (nmy < 256) {
                            unsigned int nbi = base[nmy*256 + (camX+vx)];
                            if (nbi < columnWords) {
                              unsigned char nh = *(colBuf + (size_t)nbi*4u);
                              if (nh < (unsigned char)selectedTopZ) { r=(unsigned char)(r*11/16); g=(unsigned char)(g*11/16); bb=(unsigned char)(bb*11/16); }
                            }
                          }
                        }
                        if (px >= tilePx-1) {
                          int nmx = camX + vx + 1;
                          if (nmx < 256) {
                            unsigned int nbi = base[(camY+vy)*256 + nmx];
                            if (nbi < columnWords) {
                              unsigned char nh = *(colBuf + (size_t)nbi*4u);
                              if (nh < (unsigned char)selectedTopZ) { r=(unsigned char)(r*12/16); g=(unsigned char)(g*12/16); bb=(unsigned char)(bb*12/16); }
                            }
                          }
                        }
                      }
                      if (tilePx >= 16 && (px==0 || py==0)) { r=(unsigned char)(r*15/16); g=(unsigned char)(g*15/16); bb=(unsigned char)(bb*15/16); }
                      size_t pi=((size_t)sy*MENU_W+sx)*4;
                      m_RGBA[pi+0]=bb; m_RGBA[pi+1]=g; m_RGBA[pi+2]=r; m_RGBA[pi+3]=255;
                    }
                  }
                }
              }
              drewMap = true;
            }
          }
        }
        for (int y=0;y<24 && y<MENU_H;y++) for (int x=0;x<MENU_W;x++){ size_t p=((size_t)y*MENU_W+x)*4; m_RGBA[p+0]=80; m_RGBA[p+1]=40; m_RGBA[p+2]=30; m_RGBA[p+3]=255; }
        int mxm = (m_gameFrames * 4) % (MENU_W-20);
        for (int y=40;y<44;y++) for (int x=mxm;x<mxm+20;x++){ if(x<0||x>=MENU_W||y<0||y>=MENU_H) continue; size_t p=((size_t)y*MENU_W+x)*4; m_RGBA[p+0]=80; m_RGBA[p+1]=220; m_RGBA[p+2]=220; m_RGBA[p+3]=255; }
        // debug camera marker overlay (read-only)
        {
          const int tilePx = m_debugZoom > 0 ? m_debugZoom : 16;
          const int viewW = MENU_W / tilePx;
          const int viewH = (MENU_H - 32) / tilePx;
          const int ox=0, oy=32;
          int camX = m_debugCamX - viewW/2;
          int camY = m_debugCamY - viewH/2;
          if (camX < 0) camX = 0; if (camY < 0) camY = 0;
          if (camX > 256-viewW) camX = 256-viewW;
          if (camY > 256-viewH) camY = 256-viewH;
          auto drawDot=[&](int tx,int ty,unsigned char rr,unsigned char gg,unsigned char bb2,int ms){
            int pxm = ox + (tx - camX) * tilePx + tilePx/2;
            int pym = oy + (ty - camY) * tilePx + tilePx/2;
            for (int dy=-ms; dy<=ms; ++dy) for (int dx=-ms; dx<=ms; ++dx) {
              int x=pxm+dx, y=pym+dy;
              if ((unsigned)x>=MENU_W||(unsigned)y>=MENU_H) continue;
              size_t pi=((size_t)y*MENU_W+x)*4;
              m_RGBA[pi+0]=bb2; m_RGBA[pi+1]=gg; m_RGBA[pi+2]=rr; m_RGBA[pi+3]=255;
            }
          };
          int ms = tilePx/4; if (ms < 2) ms = 2;
          // MOBJ markers: raw<<7 world -> tile = world>>14. Green=spawned in RE debug pool, Yellow=dry-run only.
          {
              int spawnedN = (gObject ? gObject->GetDebugSpawnedCount() : 0);
              for (int mi=0; mi<spawnedN; ++mi) {
                  const DebugSpawnedObject* so = gObject->GetDebugSpawned(mi);
                  if (!so) continue;
                  int tx = so->x >> 14;
                  int ty = so->y >> 14;
                  if (tx < 0 || ty < 0 || tx >= 256 || ty >= 256) continue;
                  unsigned char rr=80, gg=255, bb2=140;
                  if (so->type==21) { rr=120; gg=255; bb2=80; }
                  drawDot(tx, ty, rr, gg, bb2, (ms>3?3:2));
              }
              if (spawnedN == 0) {
                  int nM = gDebugMobjDrawN;
                  if (nM < 0) nM = 0;
                  if (nM > 64) nM = 64;
                  for (int mi=0; mi<nM; ++mi) {
                      int tx = gDebugMobjX[mi] >> 14;
                      int ty = gDebugMobjY[mi] >> 14;
                      if (tx < 0 || ty < 0 || tx >= 256 || ty >= 256) continue;
                      unsigned char rr=255, gg=240, bb2=80;
                      int t=gDebugMobjType[mi];
                      if (t==21) { rr=255; gg=160; bb2=40; }
                      drawDot(tx, ty, rr, gg, bb2, (ms>3?3:2));
                  }
              }
          }
          drawDot(m_debugCamX, m_debugCamY, 255, 80, 80, ms); // camera
          if (gGame && gGame->PlayerMain && gGame->PlayerMain->MainPed) {
            Ped* mp = gGame->PlayerMain->MainPed;
            int wx=mp->PositionX, wy=mp->PositionY; // local layout debug only
            if (wx > 0 && wy > 0 && wx < 256*16384 && wy < 256*16384) {
              drawDot(wx/16384, wy/16384, 80, 255, 120, (ms>2?2:1)); // debug ped
            }
          }
        }
        (void)drewMap;
      }
      // RE debug HUD/text overlay (minimal). Not IDA Hud::DrawUI path yet; guaranteed visible.
      {
        static const unsigned char kFont5x7[96][5] = {
          {0,0,0,0,0},{0,0,0x5F,0,0},{0,7,0,7,0},{0x14,0x7F,0x14,0x7F,0x14},{0x24,0x2A,0x7F,0x2A,0x12},
          {0x23,0x13,8,0x64,0x62},{0x36,0x49,0x55,0x22,0x50},{0,5,3,0,0},{0,0x1C,0x22,0x41,0},{0,0x41,0x22,0x1C,0},
          {0x14,8,0x3E,8,0x14},{8,8,0x3E,8,8},{0,0x50,0x30,0,0},{8,8,8,8,8},{0,0x60,0x60,0,0},{0x20,0x10,8,4,2},
          {0x3E,0x51,0x49,0x45,0x3E},{0,0x42,0x7F,0x40,0},{0x42,0x61,0x51,0x49,0x46},{0x21,0x41,0x45,0x4B,0x31},
          {0x18,0x14,0x12,0x7F,0x10},{0x27,0x45,0x45,0x45,0x39},{0x3C,0x4A,0x49,0x49,0x30},{1,0x71,9,5,3},
          {0x36,0x49,0x49,0x49,0x36},{6,0x49,0x49,0x29,0x1E},{0,0x36,0x36,0,0},{0,0x56,0x36,0,0},{8,0x14,0x22,0x41,0},
          {0x14,0x14,0x14,0x14,0x14},{0,0x41,0x22,0x14,8},{2,1,0x51,9,6},{0x32,0x49,0x79,0x41,0x3E},
          {0x7E,0x11,0x11,0x11,0x7E},{0x7F,0x49,0x49,0x49,0x36},{0x3E,0x41,0x41,0x41,0x22},{0x7F,0x41,0x41,0x22,0x1C},
          {0x7F,0x49,0x49,0x49,0x41},{0x7F,9,9,9,1},{0x3E,0x41,0x49,0x49,0x7A},{0x7F,8,8,8,0x7F},
          {0,0x41,0x7F,0x41,0},{0x20,0x40,0x41,0x3F,1},{0x7F,8,0x14,0x22,0x41},{0x7F,0x40,0x40,0x40,0x40},
          {0x7F,2,0x0C,2,0x7F},{0x7F,4,8,0x10,0x7F},{0x3E,0x41,0x41,0x41,0x3E},{0x7F,9,9,9,6},
          {0x3E,0x41,0x51,0x21,0x5E},{0x7F,9,0x19,0x29,0x46},{0x46,0x49,0x49,0x49,0x31},{1,1,0x7F,1,1},
          {0x3F,0x40,0x40,0x40,0x3F},{0x1F,0x20,0x40,0x20,0x1F},{0x3F,0x40,0x38,0x40,0x3F},{0x63,0x14,8,0x14,0x63},
          {7,8,0x70,8,7},{0x61,0x51,0x49,0x45,0x43},{0,0x7F,0x41,0x41,0},{2,4,8,0x10,0x20},{0,0x41,0x41,0x7F,0},
          {4,2,1,2,4},{0x40,0x40,0x40,0x40,0x40},{0,1,2,4,0},{0x20,0x54,0x54,0x54,0x78},{0x7F,0x48,0x44,0x44,0x38},
          {0x38,0x44,0x44,0x44,0x20},{0x38,0x44,0x44,0x48,0x7F},{0x38,0x54,0x54,0x54,0x18},{8,0x7E,9,1,2},
          {0x0C,0x52,0x52,0x52,0x3E},{0x7F,8,4,4,0x78},{0,0x44,0x7D,0x40,0},{0x20,0x40,0x44,0x3D,0},{0x7F,0x10,0x28,0x44,0},
          {0,0x41,0x7F,0x40,0},{0x7C,4,0x18,4,0x78},{0x7C,8,4,4,0x78},{0x38,0x44,0x44,0x44,0x38},{0x7C,0x14,0x14,0x14,8},
          {8,0x14,0x14,0x18,0x7C},{0x7C,8,4,4,8},{0x48,0x54,0x54,0x54,0x20},{4,0x3F,0x44,0x40,0x20},
          {0x3C,0x40,0x40,0x20,0x7C},{0x1C,0x20,0x40,0x20,0x1C},{0x3C,0x40,0x30,0x40,0x3C},{0x44,0x28,0x10,0x28,0x44},
          {0x0C,0x50,0x50,0x50,0x3C},{0x44,0x64,0x54,0x4C,0x44},{0,8,0x36,0x41,0},{0,0,0x7F,0,0},{0,0x41,0x36,8,0},{0x10,8,8,0x10,8}
        };
        auto drawChar=[&](int x,int y,char c,unsigned char r,unsigned char g,unsigned char b,int scale){
          if (c < 32 || c > 127) c = '?';
          const unsigned char* glyph = kFont5x7[c - 32];
          for (int gx=0; gx<5; ++gx) for (int gy=0; gy<7; ++gy) if (glyph[gx] & (1u<<gy))
            for (int sy=0; sy<scale; ++sy) for (int sx=0; sx<scale; ++sx) {
              int px=x+gx*scale+sx, py=y+gy*scale+sy;
              if ((unsigned)px>=MENU_W||(unsigned)py>=MENU_H) continue;
              size_t pi=((size_t)py*MENU_W+px)*4;
              m_RGBA[pi+0]=b; m_RGBA[pi+1]=g; m_RGBA[pi+2]=r; m_RGBA[pi+3]=255;
            }
        };
        auto drawText=[&](int x,int y,const char* t,unsigned char r,unsigned char g,unsigned char b,int scale=1){
          int cx=x; for (const char* p=t; *p; ++p) { if (*p=='\n') { y+=8*scale; cx=x; continue; } drawChar(cx,y,*p,r,g,b,scale); cx+=6*scale; }
        };
        char hud1[128], hud2[128], hud3[128];
        int mobjS = gDebugMobjSpawned;
        int mobjDbg = (gObject ? gObject->GetDebugSpawnedCount() : 0);
        int mobjN = gDebugMobjCount;
        snprintf(hud1,sizeof(hud1),"HUD RE DEBUG  FPS %d  CAM %d,%d Z%d", m_fps, m_debugCamX, m_debugCamY, m_debugCamZ);
        snprintf(hud2,sizeof(hud2),"MOBJ %d/%d dbg=%d  STYLE %s  MAP %s", mobjN, mobjS, mobjDbg, StyleTiles_Ready()?"ON":"OFF", (gMapRelatedStruct&&gMapRelatedStruct->getMap())?"ON":"OFF");
        snprintf(hud3,sizeof(hud3),"GTA2_SPAWN_MOBJ=%s  GTA2_MOBJ_TRACE=%s", getenv("GTA2_SPAWN_MOBJ")?"1":"0", getenv("GTA2_MOBJ_TRACE")?"1":"0");
        for (int i=0;i<2;++i) { // shadow
          drawText(5+i,5+i,hud1,0,0,0,2);
          drawText(5+i,22+i,hud2,0,0,0,2);
          drawText(5+i,39+i,hud3,0,0,0,1);
        }
        drawText(5,5,hud1,255,230,120,2);
        drawText(5,22,hud2,180,255,180,2);
        drawText(5,39,hud3,180,220,255,1);
        // Draw Hud::DrawUI() debug lines and queued DrawGTATextRaw commands (RE bridge).
        if (gHud) {
          int maxLines = gHud->debugLineCount;
          if (maxLines > 4) maxLines = 4;
          for (int li=0; li<maxLines; ++li) {
            int ly = 56 + li*10;
            drawText(6,ly+1,gHud->debugLines[li],0,0,0,1);
            drawText(5,ly,gHud->debugLines[li],255,255,200,1);
          }
        }
        for (int ti=0; ti<gDebugTextCmdCount && ti<kMaxDebugTextCmds; ++ti) {
          const DebugTextCmd& c = gDebugTextCmds[ti];
          int tx = c.x, ty = c.y;
          if (tx < 0) tx = 0; if (ty < 0) ty = 0;
          if (tx >= MENU_W) tx = MENU_W - 1; if (ty >= MENU_H) ty = MENU_H - 1;
          unsigned char fr = 255, fg = 240, fb = 200;
          // Debug color hint from DrawGTATextRaw bridge: nonzero color toggles alternate tint.
          if (c.color == 0xFFFFu) { fr = 160; fg = 255; fb = 160; }
          else if (c.color != 0) { fr = 255; fg = 220; fb = 120; }
          drawText(tx+1, ty+1, c.text, 0,0,0,1);
          drawText(tx, ty, c.text, fr, fg, fb, 1);
        }
      }
      BlitGDIScaled();
      wchar_t buf[320];
      {
        int rawX=0, rawY=0, pedN=0, pedF=0, carN=0, carN2=0, mobjN=0, hasMP=0;
        if (gGame && gGame->PlayerMain) { rawX=gGame->PlayerMain->AuxGameCameraX; rawY=gGame->PlayerMain->AuxGameCameraY; hasMP = gGame->PlayerMain->MainPed ? 1 : 0; }
        int mobjS = gDebugMobjSpawned;
        int mobjDbg = (gObject ? gObject->GetDebugSpawnedCount() : 0);
        if (gMapRelatedStruct) { mobjN = gDebugMobjCount; }
        for (Ped* pp=gPedManager.NextPed; pp; pp=pp->NextPed) { ++pedN; if (pedN>500) break; }
        for (Ped* pp=gPedManager.FirstPed; pp; pp=pp->NextPed) { ++pedF; if (pedF>500) break; }
        for (Car* cc=gCarsPrefabs.Car2; cc; cc=cc->LastCar) { ++carN; if (carN>500) break; }
        for (Car* cc=gCarsPrefabs.Car3; cc; cc=cc->LastCar) { ++carN2; if (carN2>500) break; }
        int sndN = gSound.GetSampleCount();
        extern int gDebugTileRot;
        extern int gDebugTileDump; gDebugTileDump = 0;
        swprintf(buf, 320, L"GTA2 - in game (frame %d) fps=%d%s zm=%d rot=%d cam=%d,%d,%d sty=%s p=%d/%d c=%d/%d o=%d/%d:%d mp=%d au=%d%s", m_gameFrames, m_fps, (gMapRelatedStruct && gMapRelatedStruct->getMap())?L" map":L"", m_debugZoom, gDebugTileRot*90, m_debugCamX, m_debugCamY, m_debugCamZ, StyleTiles_Ready()?L"on":L"off", pedN, pedF, carN, carN2, mobjN, mobjS, mobjDbg, hasMP, sndN, gSkipAudio?L"!":L"");
      }
      SetWindowTextW(hwnd, buf);
    }
    Sleep(16);
    return TRUE;
  }

  // ВРЕМЕННО: тест воспроизведения звуков (клавиша S). В оригинальном меню звуков
  // навигации нет, поэтому движок проверяется отдельным хоткеем: первое нажатие
  // грузит банк "ste", каждое следующее играет очередной звук банка с остановкой
  // предыдущего. Индекс, частота и размер звука показываются в заголовке окна.
  if (GetAsyncKeyState('S') & 1) {
    if (!m_testBankLoaded) {
      gSound.LoadBank("ste");
      m_testBankLoaded = true;
    }
    int n = gSound.GetSampleCount();
    if (n > 0) {
      int idx = m_testIndex % n;
      int size, rate, loopStart, loopEnd;
      gSound.GetSampleInfo(idx, size, rate, loopStart, loopEnd);
      gSound.StopAll();
      gSound.PlaySample(idx, false);
      wchar_t buf[192];
      swprintf(buf, 128, L"GTA2 viewer - sound %d/%d (%d Hz, %d bytes)",
               idx, n, rate, size);
      SetWindowTextW(hwnd, buf);
      m_testIndex++;
    }
    Sleep(16);
    return TRUE;
  }

  // ВРЕМЕННО: тест декодера Vocals (клавиша W). Каждое нажатие декодирует через
  // WavToPcm очередной .wav из data\audio\Vocals (IMA ADPCM, см. WavToPcm) и
  // проигрывает через gSound.PlayPcm. Имя файла, число сэмплов и частота - в
  // заголовке окна. Проверяет декодер на реальных файлах игры.
  if (GetAsyncKeyState('W') & 1) {
    if (m_vocalFiles.empty())
      ListVocalsFiles(m_vocalFiles);
    if (!m_vocalFiles.empty()) {
      int k = m_testVocals % (int)m_vocalFiles.size();
      std::vector<short> pcm;
      int rate = 0;
      const char* path = m_vocalFiles[k].c_str();
      if (Sound::WavToPcm(path, pcm, rate) && !pcm.empty()) {
        gSound.PlayPcm(pcm, rate);
        const char* name = strrchr(path, '\\');
        wchar_t buf[192];
        swprintf(buf, 128, L"GTA2 viewer - vocals %d/%d %S (%d smpl, %d Hz)",
                 k, (int)m_vocalFiles.size(),
                 name ? name + 1 : path, (int)pcm.size(), rate);
        SetWindowTextW(hwnd, buf);
      } else {
        SetWindowTextA(hwnd, "GTA2 viewer - vocals decode FAILED");
      }
      m_testVocals++;
    }
    Sleep(16);
    return TRUE;
  }

  // Вводимые с клавиатуры символы (накапливаются в MsgProc). Обрабатываем их
  // только когда активен пункт PLAYER на 2-й странице; иначе - отбрасываем.
  if (!m_charQueue.empty()) {
    bool editing = (m_CurrentPage == 1 && m_ActiveItem == 0); // поле PLAYER
    for (size_t k = 0; k < m_charQueue.size(); k++)
      EditName(editing ? m_charQueue[k] : 0);
    m_charQueue.clear();
  }

  // Esc: на подстранице возврат на предыдущее меню (по стеку m_pageStack),
  // если стек пуст и мы не на главном - на главное меню, на главном - выход.
  if (GetAsyncKeyState(VK_ESCAPE) & 1) {
    if (!gSkipAudio) {
      int n = gSound.GetSampleCount();
      if (n > 0) { gSound.StopAll(); gSound.PlaySample(1 % n, false); } // guarded pragmatic back/cancel cue
    }
    if (!m_pageStack.empty()) {
      int back = m_pageStack.back();
      m_pageStack.pop_back();
      SwitchPage(back);
    } else if (m_CurrentPage != 0) {
      SwitchPage(0);
    } else {
      PostMessage(hwnd, WM_CLOSE, 0, 0);
    }
    Sleep(16);
    return TRUE;
  }

  // Навигация:
  //   Up/Down    - переключение активного пункта страницы,
  //   Left/Right - смена слота игрока в поле PLAYER (8 имён),
  //   Enter      - выбор пункта.
  // GetAsyncKeyState читается по одному разу на клавишу: иначе флаг "нажата с
  // прошлого опроса" сгорает на первом вызове и Up превращается в Down.
  int up = GetAsyncKeyState(VK_UP) & 1;
  int down = GetAsyncKeyState(VK_DOWN) & 1;
  int left = GetAsyncKeyState(VK_LEFT) & 1;
  int right = GetAsyncKeyState(VK_RIGHT) & 1;

  auto playMenuUiSample = [&](int idx, bool loop) {
    if (gSkipAudio) return;
    int n = gSound.GetSampleCount();
    if (n <= 0) return;
    if (idx < 0) idx = 0;
    idx = idx % n;
    gSound.StopAll();
    gSound.PlaySample(idx, loop);
  };

  // Смена активного пункта (по кругу через ItemCount() элементов страницы).
  if (up || down) {
    int cnt = ItemCount();
    if (cnt > 0) {
      m_ActiveItem = up ? (m_ActiveItem - 1 + cnt) % cnt
                        : (m_ActiveItem + 1) % cnt;
      gMenu->MenuPageArray[m_CurrentPage].SelectActiveElementDefault = m_ActiveItem;
      playMenuUiSample(1, false); // guarded pragmatic menu-move cue
      // На страницах 0 и 1 фон зависит от активного пункта - перестроим фон и текст.
      RenderBackground();
      RasterizeMenuText();
    }
  }

  // Left/Right на поле PLAYER (2-я страница, пункт 0): листаем 8 слотов игроков
  // по кругу. Синхронизируем Menu::CurrentPlayerSlot и поле PlayerSlot пункта
  // (как в оригинале - эти данные используются в игре и мультиплеере).
  if (left || right) {
    if (m_CurrentPage == 1 && m_ActiveItem == 0) {
      m_playerSlot = left ? (m_playerSlot - 1 + 8) % 8
                          : (m_playerSlot + 1) % 8;
      gMenu->CurrentPlayerSlot = m_playerSlot;
      gMenu->MenuPageArray[1].MenuEntryArray[0].PlayerSlot = m_playerSlot;
      RasterizeMenuText();
    }
  }



  // Выбор пункта меню (Enter).
  if (GetAsyncKeyState(VK_RETURN) & 1) {
    if (ItemCount() > 0) {
      MenuEntry& e = gMenu->MenuPageArray[m_CurrentPage].MenuEntryArray[m_ActiveItem];
      int action = e.MenuAction; // тип действия (CHANGEPAGE, SETPLAYERNAME, ...)
      int sel = e.SelectMenu;    // куда ведёт пункт (страница или спец.значение)
      playMenuUiSample(0, false); // guarded pragmatic menu-select cue

      // Пункт QUIT главного меню - выход из приложения (титры пока не показываем).
      if (m_CurrentPage == 0 && m_ActiveItem == 2) {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
      } else if (sel == 258) {              // MENUPAGE_QUIT
        PostMessage(hwnd, WM_CLOSE, 0, 0);
      } else if (action == MENU_ACTION_SETPLAYERNAME) {
        // Поле ввода имени: Enter подтверждает и остаёмся на странице.
        RasterizeMenuText();
      } else if (action == MENU_ACTION_CHANGEPAGE || action == MENU_ACTION_NONE) {
        if (sel == 264 || action == MENU_ACTION_NEWGAME) {
          if (gMapGm == NULL) gMapGm = new MapGm();
          if (gMapGm->GetMapName()[0] == 0) gMapGm->SetMapName((char*)"data\\bil.gmp");
          if (gMapGm->GetStyleFile()[0] == 0) gMapGm->SetStyleName((char*)"data\\bil.sty");
          if (gMapGm->GetScriptName()[0] == 0) gMapGm->SetScripName((char*)"data\\bil.scr");
          if (gGame == NULL) gGame = new Game(1, 0);
          gGame->LoadResources();
          gGame->StartGameSession();
          m_inGame = true; m_gameFrames = 0;
          SetWindowTextA(GethWnd(), "GTA2 - running");
        } else if (sel == 257) {
        } else if (sel >= 0 && sel < 16) {
          m_pageStack.push_back(m_CurrentPage);
          SwitchPage(sel);
        }
      } else if (action == MENU_ACTION_NEWGAME) {
        if (gMapGm == NULL) gMapGm = new MapGm();
        if (gMapGm->GetMapName()[0] == 0) gMapGm->SetMapName((char*)"data\\bil.gmp");
        if (gMapGm->GetStyleFile()[0] == 0) gMapGm->SetStyleName((char*)"data\\bil.sty");
        if (gMapGm->GetScriptName()[0] == 0) gMapGm->SetScripName((char*)"data\\bil.scr");
        if (gGame == NULL) gGame = new Game(1, 0);
        gGame->LoadResources();
        gGame->StartGameSession();
        m_inGame = true; m_gameFrames = 0;
        SetWindowTextA(GethWnd(), "GTA2 - running");
      }
    }
  }

  BlitGDIScaled(); // вывод кадра в окно
  Sleep(16);       // ~60 кадров/сек, чтобы не грузить CPU
  return TRUE;
}

// Создание меню (аналог оригинальной функции FUN_00457830 из WinMain):
// конструктор Menu сам выделяет объекты (gText, gStyle, gTextureManager) и
// загружает тексты меню (LoadTextMenu). Дополнительно настраиваем звук.
void SetupMenu()
{
  if (gMenu == NULL)
    gMenu = new Menu;          // new = operator_new + Menu::Menu()
  if (gMapGm == NULL) {
      gMapGm = new MapGm;
  }
  if (gDMAudio == NULL) {
    gDMAudio = new DMAudio();
  }
  if (gDMAudio && !gSkipAudio) {
    gDMAudio->InitAudioManager();
  }
  // Доп. параметры из оригинального FUN_00457830: аудио-объект для меню.
  gAudioObject = 2;            // "2D-звук" (как в оригинальном LoadConfig)
  if (!gSkipAudio && gDMAudio)
    gSampleRate = gDMAudio->AddAudioObject(&gAudioObject);
   //gDMAudio.LoadSTY
}

// Точка входа приложения: создаём объект cApp и запускаем окно (Run() держит
// цикл сообщений и вызывает Init/Frame/Shutdown).
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
  gRegistry = new Registry; // реестр Windows (язык, настройки) - как в оригинальном WinMain
  gWinApi = new WinApi;     // создать объект утилит (GetVersion, GetDebugParam и др.)

  // Последовательность инициализации - как в оригинальном WinMain (0x004D1170):
  gWinApi->GetDebugParam();      // 0x004D121A: чтение debug-параметров из реестра (fPlayReplay)
  gWinApi->FindGraphicDevice();  // 0x004D128F: выбор устройства рендеринга/видео
  gWinApi->DefautInitParam();    // 0x00461853 (InitializeGlobals): сброс параметров к умолчаниям
  gWinApi->InitTimer();          // запуск таймера кадров (gTimer = timeGetTime())
  LoadConfig();
  SetupMenu();              // создать меню + доп. параметры (аудио), аналог FUN_00457830

  // Одиночная игра (одиночная ветка InitFrontedLessGame 0x00461DE0 -> 0x00462001):
  // Game(int modeStatus, char ids) - 1 игрок, индекс 0.
  gMapGm = new MapGm();            // проект хранит MapGm как указатель (в дампе - статик &gMapGm)
  gGame = new Game(1, 0);
  // gGame->LoadResources();
  // gGame->StartGameSession();

  cApp App;
  return App.Run();
}
void ConfigKeybord();
void PlayDataInit();

void LoadConfig() {
    ConfigKeybord(); //TODO
    PlayDataInit();
}
void ConfigKeybord() {

    if (gKeybord == NULL) {
        gKeybord = new Keybord;
    }
    gKeybord->LoadKeybord();
}
void PlayDataInit() {
    if (gPlayerData == NULL) {
        gPlayerData = new PlayerData;
    }
}