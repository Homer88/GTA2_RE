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
#include "Engine/Sound/Sound.h"     // движок: gSound, WavToPcm, PlaySample
#include "Game/Menu/Menu.h"         // класс Menu (gMenu), MenuPage, MenuEntry

// Глобальные объекты реконструкции (определены в MENU/ULTIL-библиотеках).
extern Menu gMenu;                 // меню игры: MenuPageArray, PlayerSlotSave и т.д.
extern WinApi gWinApi;             // утилиты: CopyWideString, GetVersion и др.
extern int skip_audio;             // флаг "звук выключен" (определён в DMAudio.cpp)
extern int gAudioObject;           // тип звукового объекта (определён в Menu/Menu.cpp)
extern int gSampleRate;            // частота созданного аудио-объекта (DMAudio.cpp)

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
             m_testIndex = 0; m_testBankLoaded = false; m_testVocals = 0; }

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
  strcpy(m_Caption, "GTA2 - viewer");

  // Построить данные меню из исходной реконструкции (заполняет MenuPageArray).
  // Вызываются все Create-функции: PlayMenuCreate, OptionsMenuCreate и т.д.
  gMenu.LoadTextMenu();

  // --- Инициализация звука (аналог LoadConfig в оригинале) ---
  // gAudioObject = 2: "2D-звук" (тип объекта, как в оригинальном LoadConfig).
  // DMAudio::sub_410530 создаёт аудио-объект и кладёт его "частоту" в gSampleRate.
  gAudioObject = 2;
  if (!skip_audio)
    gSampleRate = gDMAudio.sub_410530(&gAudioObject);

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
  m_playerSlot = gMenu.CurrentPlayerSlot;
  if (m_playerSlot < 0 || m_playerSlot > 7)
    m_playerSlot = 0;
  for (int s = 0; s < 8; s++) {
    wchar_t def[8];
    if (gMenu.PlayerSlotSave[s].PlayerName[0])
      continue; // имя уже есть (например, загружено из сохранения) - не трогаем
    swprintf(def, 8, L"PLAYER%d", s + 1);
    wcsncpy(gMenu.PlayerSlotSave[s].PlayerName, def, 7);
    gMenu.PlayerSlotSave[s].PlayerName[7] = 0;
  }

  // Начальная страница - главное меню. Активный пункт - как задано в данных
  // (SelectActiveElementDefault страницы).
  m_CurrentPage = 0;
  m_ActiveItem = gMenu.MenuPageArray[0].SelectActiveElementDefault;
  RenderBackground();   // собрать картинку фона из .tga
  RasterizeMenuText();  // вписать текст пунктов в кадр

  // окно уже создано в Run() - обновим заголовок с подсказками по управлению
  SetWindowTextA(GethWnd(), "GTA2 - viewer (Esc=quit/back, Enter=select)");
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
  MenuPage& page = gMenu.MenuPageArray[m_CurrentPage];
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
  gMenu.PageNumber = page;  // номер страницы в данных меню (как в оригинале)
  gMenu.State = page;       // и в состоянии фронтенда
  m_ActiveItem = gMenu.MenuPageArray[page].SelectActiveElementDefault;
  int cnt = ItemCount();
  if (m_ActiveItem < 0 || m_ActiveItem >= cnt)
    m_ActiveItem = 0;
  gMenu.MenuPageArray[page].SelectActiveElementDefault = m_ActiveItem;
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
    MenuPage& page = gMenu.MenuPageArray[m_CurrentPage];
    int cnt = ItemCount();
    for (int i = 0; i < cnt; i++) {
      const wchar_t* txt = page.MenuEntryArray[i].TextMenuElementArray;

      // Поле PLAYER (2-я страница, пункт 0) - вместо текста из .gxt показываем
      // имя текущего слота из Menu::PlayerSlotSave.
      if (m_CurrentPage == 1 && i == 0)
        txt = gMenu.PlayerSlotSave[m_playerSlot].PlayerName;
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
      gWinApi.GetVersion(&vmajor, &vminor);
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
  wchar_t* name = gMenu.PlayerSlotSave[m_playerSlot].PlayerName;
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

  // Обновление звука каждый кадр (в оригинале: if (!skip_audio) DMAudio::sub_410520).
  if (!skip_audio)
    gDMAudio.sub_410520();

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
      wchar_t buf[128];
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
        wchar_t buf[128];
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

  // Смена активного пункта (по кругу через ItemCount() элементов страницы).
  if (up || down) {
    int cnt = ItemCount();
    if (cnt > 0) {
      m_ActiveItem = up ? (m_ActiveItem - 1 + cnt) % cnt
                        : (m_ActiveItem + 1) % cnt;
      gMenu.MenuPageArray[m_CurrentPage].SelectActiveElementDefault = m_ActiveItem;
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
      gMenu.CurrentPlayerSlot = m_playerSlot;
      gMenu.MenuPageArray[1].MenuEntryArray[0].PlayerSlot = m_playerSlot;
      RasterizeMenuText();
    }
  }

  // Выбор пункта меню (Enter).
  if (GetAsyncKeyState(VK_RETURN) & 1) {
    if (ItemCount() > 0) {
      MenuEntry& e = gMenu.MenuPageArray[m_CurrentPage].MenuEntryArray[m_ActiveItem];
      int action = e.MenuAction; // тип действия (CHANGEPAGE, SETPLAYERNAME, ...)
      int sel = e.SelectMenu;    // куда ведёт пункт (страница или спец.значение)

      // Пункт QUIT главного меню - выход из приложения (титры пока не показываем).
      if (m_CurrentPage == 0 && m_ActiveItem == 2) {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
      } else if (sel == 258) {              // MENUPAGE_QUIT
        PostMessage(hwnd, WM_CLOSE, 0, 0);
      } else if (action == MENU_ACTION_SETPLAYERNAME) {
        // Поле ввода имени: Enter подтверждает и остаёмся на странице.
        RasterizeMenuText();
      } else if (action == MENU_ACTION_CHANGEPAGE || action == MENU_ACTION_NONE) {
        // Обычный пункт меню: переход на другую страницу по SelectMenu.
        if (sel == 257) {                   // MENUPAGE_GTA2MANAGER - заглушка
          // вход в GTAManager (меню миссий): пока ничего не делаем
        } else if (sel >= 0 && sel < 16) {  // переход на страницу меню
          m_pageStack.push_back(m_CurrentPage); // запомним, куда возвращаться по Esc
          SwitchPage(sel);
        } // остальные спец. значения SelectMenu пока игнорируем
      } // прочие действия (LOADGAME, SAVEGAME и т.п.) пока игнорируем
    }
  }

  BlitGDIScaled(); // вывод кадра в окно
  Sleep(16);       // ~60 кадров/сек, чтобы не грузить CPU
  return TRUE;
}

// Точка входа приложения: создаём объект cApp и запускаем окно (Run() держит
// цикл сообщений и вызывает Init/Frame/Shutdown).
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
  cApp App;
  return App.Run();
}