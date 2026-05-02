#ifndef ___MENU_H__
#define ___MENU_H__
#include <dinput.h>
#include "MenuPage.h"
// Forward declarations
//struct DirectInput;
//struct InputDevice;
//struct TextMenuElement;

#pragma message("Using Menu.h with getPlayerProfileName")

// Enum: FrontendState
typedef enum FrontendState {
    FRONTEND_NONE = 0,
    FRONTEND_INTRO = 1,
    FRONTEND_MAIN_MENU = 2,
    FRONTEND_PAUSE_MENU = 3,
    FRONTEND_OPTIONS_MENU = 4,
    FRONTEND_PLAYER_LIST = 5,
    FRONTEND_MULTIPLAYER_MENU = 6,
    FRONTEND_SERVER_SETTINGS = 7,
    FRONTEND_SELECT_MISSION = 8,
    FRONTEND_WORLD_MAP = 9,
    FRONTEND_SHOW_STATISTICS = 10,
    FRONTEND_SHOW_AWARDS = 11,
    FRONTEND_GALLERY = 12,
    FRONTEND_SHOW_CREDITS = 13,
    FRONTEND_CONFIRM_EXIT = 14,
    FRONTEND_PREINTRO = 15,
    FRONTEND_INTRO_BIK = 16
} eFrontendState;

// Enum: MenuActions
typedef enum MenuActions {
    MENU_ACTION_NONE = 0,
    MENU_ACTION_CHANGEPAGE = 1,
    MENU_ACTION_SETPLAYERNAME = 2,
    MENU_ACTION_LOADGAME = 3,
    MENU_ACTION_SAVEGAME = 4,
    MENU_ACTION_NEWGAME = 5,
    MENU_ACTION_EXIT = 6,
    MENU_ACTION_OPTIONS = 7,
    MENU_ACTION_DIFFICULTY = 8,
    MENU_ACTION_CHARACTER = 9,
    MENU_ACTION_CONTROLS = 10,
    MENU_ACTION_AUDIO = 11,
    MENU_ACTION_VIDEO = 12,
    MENU_ACTION_APPLY = 13,
    MENU_ACTION_RESET = 14,
    MENU_ACTION_BACK = 15,
    MENU_ACTION_SELECT_SLOT = 16,
    MENU_ACTION_SELECT_MISSION = 17,
    MENU_ACTION_SHOW_STATISTICS = 18,
    MENU_ACTION_SHOW_AWARDS = 19,
    MENU_ACTION_GALLERY = 20,
    MENU_ACTION_CREDITS = 21,
    MENU_ACTION_MULTIPLAYER = 22,
    MENU_ACTION_SERVER_SETTINGS = 23,
    MENU_ACTION_CHEAT = 24
} eMenuActions;

// Enum: KeyCode
typedef enum KeyCode {
    KEY_NONE = 0,
    KEY_ESCAPE = 1,
    KEY_ENTER = 2,
    KEY_UP = 3,
    KEY_DOWN = 4,
    KEY_LEFT = 5,
    KEY_RIGHT = 6,
    KEY_SPACE = 7,
    KEY_F1 = 8,
    KEY_F2 = 9,
    KEY_F3 = 10,
    // ... остальные клавиши
    KEY_MAX = 256
} KeyCode;

// Основная структура Menu
// Размер: ~0x1EB40 байт
class Menu {
public:
    // Устройства ввода (предположительно 0x0000 - 0x0100)
    LPDIRECTINPUTA DirectInput;    // +0x0000 - указатель на DirectInput
    LPDIRECTINPUTDEVICEA InputDevice;    // +0x0004 - указатель на устройство ввода
    
    // Состояние клавиш (0x0100 - 0x0200)
    unsigned char Keys[256];                   // +0x0008 - состояние клавиш (256 байт)
    
    // Состояние фронтенда (0x0200 - 0x0210)
    int FrontendState;         // +0x0108 - текущее состояние
    int PreviousState;         // +0x010C - предыдущее состояние
    bool FrontendKeysEnabled;            // +0x0110 - включены ли клавиши фронтенда ??
    int State;                          // +0x0110
    int PageNumber;
    // Массив страниц меню (0x0210 - 0x3000)
    MenuPage MenuPageArray[17];          // +0x0114 - 17 страниц меню
    
    // Информация об игроке (0x3000 - 0x3100)
    wchar_t PlayerName[10];                 // +0x3000 - имя игрока (32 байта)
    char PlayerProfileName[9];          // +0x3020 - имя профиля (64 байта)
    int CurrentPlayerSlot;               // +0x3060 - текущий слот игрока
    
    // Буферы для текста и сохранений (0x3100 - 0x5000)
    char TextBuffer[256];                // +0x3064 - буфер для текста
    char SaveFilePath[260];              // +0x3164 - путь к файлу сохранения
    char SettingsBuffer[512];            // +0x3268 - буфер настроек
    
    // Ресурсы и текстуры (0x5000 - 0x10000)
    void* pTextureTable;                 // +0x5000 - таблица текстур
    void* pBackgroundTexture;            // +0x5004 - текстура фона
    int NumLoadedTextures;               // +0x5008 - количество загруженных текстур

    // Настройки игры (0x10000 - 0x15000)
    int Difficulty;                      // +0x10000 - сложность
    int CharacterIndex;                  // +0x10004 - индекс персонажа
    int ControlConfig;                   // +0x10008 - конфигурация управления
    float AudioVolume;                   // +0x1000C - громкость аудио
    int VideoResolution;                 // +0x10010 - разрешение видео
    bool WindowedMode;                   // +0x10014 - оконный режим
    
    // Статистика и награды (0x15000 - 0x1A000)
    int TotalScore;                      // +0x15000 - общий счет
    int MissionsCompleted;               // +0x15004 - выполнено миссий
    int AwardsCount;                     // +0x15008 - количество наград
    
    // Специальные флаги и состояния (0x1A000 - 0x1EB40)
    bool IsIntroPlaying;                 // +0x1A000 - воспроизводится ли интро
    bool IsBinkActive;                   // +0x1A004 - активен ли Bink
    int SpecialFlag1;                    // +0x1A008 - специальный флаг 1
    int SpecialFlag2;                    // +0x1A00C - специальный флаг 2
    // ... остальные поля до 0x1EB40
    
    char isCheat;                        //Активирован Чит
    int MenuPicture;                    //какой рисунок загружать 

    // Выравнивание до общего размера 0x1EB40
    unsigned char Reserved[0x1EB40 - 0x1A010]; // Зарезервировано







// Проверка размеров структур (будет актуализирована после точного анализа)
// static_assert(sizeof(Menu) == 0x1EB40, "Menu size mismatch");

// Объявления функций (будут реализованы в .c/.cpp файлах)
// Формат: // Адрес: 0xXXXXXX - Размер: 0xXX байт

// Инициализация и очистка
// Адрес: 0x00456F80 - Размер: 0x933 байт
void InitializeState();
// Адрес: 0x004578B3 - Размер: 0xC5B байт
void CleanupResources();
// Адрес: 0x00481D30 - Размер: 0x4D байт
void CloseBinkResources();

// Управление состоянием
// Адрес: 0x00453A30 - Размер: 0xB байт
void SetFrontendState( int state);
// Адрес: 0x00451F60 - Размер: 0xB байт
void SetFrontendState();
// Адрес: 0x00456F60 - Размер: 0x103 байт
void UpdateState();
// Адрес: 0x00456E80 - Размер: 0xF9 байт
void UpdateMenuFrame();
// Адрес: 0x00457199 - Размер: 0x18B байт
void RenderMenu();

// Ввод
// Адрес: 0x00453D80 - Размер: 0x91 байт
void InitDevice();
// Адрес: 0x00451FB0 - Размер: 0x22 байт
void ReleaseInputDevice();
// Адрес: 0x00456AB3 - Размер: 0x4E байт
void ReadDeviceState();
// Адрес: 0x00456B01 - Размер: 0x152 байт
void ProcessInput();
// Адрес: 0x00456C53 - Размер: 0x2A байт
void HandleKeyPress(int  key);
// Адрес: 0x00456C7D - Размер: 0xF байт
void SetFrontendKeysEnabled(bool enabled);

// Работа с игроком
// Адрес: 0x00452490 - Размер: 0x2F байт
void SetPlayerName(const char* name);
// Адрес: 0x0045862F - Размер: 0x4F байт
void SetPlayerNameFromMenu();
// Адрес: 0x0045867E - Размер: 0x38 байт
bool ValidatePlayerName(const char* name);
// Адрес: 0x004586B6 - Размер: 0x26 байт
PlayerSlotSlave* getPlayerProfileName();
// Адрес: 0x004586DC - Размер: 0x25B байт
void LoadPlayerProfile( int slot);
// Адрес: 0x00458937 - Размер: 0x10C байт
void SelectPlayerSlot();
// Адрес: 0x00458A43 - Размер: 0x4B байт
int FindLastActiveArenaSlot();

// Сохранение/загрузка
// Адрес: 0x00452940 - Размер: 0x1B3 байт
void SaveGame();
// Адрес: 0x00458C41 - Размер: 0x6B байт
void LoadGame();
// Адрес: 0x00455F90 - Размер: 0x169 байт
int NewGame();
// Адрес: 0x00458E15 - Размер: 0x86 байт
bool CheckSaveFile( const char* filename);
// Адрес: 0x004528A0 - Размер: 0x9E байт
const char* GettingSaveFile(byte index, char* savePath);
// Адрес: 0x00458F39 - Размер: 0x4E байт
const char* GetSaveFile();
// Адрес: 0x00458F87 - Размер: 0x6A байт
void SaveSettings();

// Отрисовка и ресурсы
// Адрес: 0x00457324 - Размер: 0x43 байт
void PrintCentr( const char* text, float x, float y);
// Адрес: 0x00457367 - Размер: 0xCC байт
void* LoadTexture(unsigned short ID);
// Адрес: 0x00457433 - Размер: 0x3A байт
void LoadTexturesFromTable( void* table);
// Адрес: 0x0045746D - Размер: 0x14B байт
void FindBackground(int iMenuBackground, byte* LeftPicture, byte* RightPicture);
// Адрес: 0x004575B8 - Размер: 0x1B5 байт
void DrawMenuBackground();
// Адрес: 0x0045776D - Размер: 0x46 байт
void DrawMenuElements();
// Адрес: 0x004577B3 - Размер: 0x7D байт
void UpdateGUI();
// Адрес: 0x00453E20 - Размер: 0x1512 байт
void LoadTextMenu();

// Обработка событий и навигация
// Адрес: 0x00456D00 - Размер: 0x2A байт
void SwitchPage( int pageIndex);
// Адрес: 0x00456D2A - Размер: 0xBC байт
void ActivateElement( int elementIndex);
// Адрес: 0x00456DE6 - Размер: 0x60B байт
void HandleMenuEvent( int event);
// Адрес: 0x00456DF0 - Размер: 0x66 байт
void NavigatePages( int direction);
// Адрес: 0x00456E56 - Размер: 0x66 байт
void GoBack();

// Логика меню
// Адрес: 0x00457F00 - Размер: 0x35C байт
void MainMenuLogic();
// Адрес: 0x00458050 - Размер: 0x1A9 байт
void PauseMenu();
// Адрес: 0x004581F9 - Размер: 0x2CB байт
void OptionsMenu();
// Адрес: 0x004584C4 - Размер: 0x16B байт
void PlayerList();
// Адрес: 0x0045862F - Размер: 0xDA байт
void MultiplayerMenu();
// Адрес: 0x00458709 - Размер: 0x9C байт
void ServerSettings();

// Настройки и конфигурация
// Адрес: 0x00458800 - Размер: 0x17B байт
void ApplyMoneyCheatIfApplicable();
// Адрес: 0x0045897B - Размер: 0x2C4 байт
void SetDifficulty( int difficulty);
// Адрес: 0x00458C3F - Размер: 0x6E байт
void SelectCharacter( int characterIndex);
// Адрес: 0x00458CAD - Размер: 0x38 байт
void ConfigureControls( int config);
// Адрес: 0x00458CE5 - Размер: 0x28 байт
void AudioOptions();
// Адрес: 0x00458D0D - Размер: 0x44 байт
void VideoOptions();
// Адрес: 0x00458D51 - Размер: 0x53 байт
void ApplySettings();
// Адрес: 0x00458DA4 - Размер: 0x15F байт
void ResetSettings();

// Специальные экраны
// Адрес: 0x00458F03 - Размер: 0x23 байт
void Intro_BIK();
// Адрес: 0x00458F26 - Размер: 0x42 байт
void PreIntro();
// Адрес: 0x00458F68 - Размер: 0x66 байт
void SelectMission();
// Адрес: 0x00458FCE - Размер: 0xF9 байт
void WorldMap();
// Адрес: 0x004590C7 - Размер: 0x66 байт
void ShowStatistics();
// Адрес: 0x0045912D - Размер: 0x139 байт
void ShowAwards(char );
// Адрес: 0x00459266 - Размер: 0x2A байт
void Gallery();
// Адрес: 0x00459290 - Размер: 0x2A байт
bool ShowCredits();
// Адрес: 0x004592BA - Размер: 0x141 байт
void ConfirmExit();

// изменнеие сдаланы мной стандартная функция
// HWND __stdcall Start_GTAManager()
// Адрес: 0x004D0820 - Размер:
void StartGTAManager();
// Проверки и условия
// Адрес: 0x004593FB - Размер: 0x4C+0x69+0x161 байт
void CheckConditions();
// Адрес: 0x00453D40 - Размер: 0x31 байт
void MenuShowJapanText();

// Читы и специальные функции
// Адрес: 0x004590F0  - Размер: 0x44E байт
void PlayerCheat( wchar_t * PlayerName);
// Адрес: 0x004598C6 - Размер: 0xC1 байт
void SpecialFunction1();
// Адрес: 0x00459987 - Размер: 0xF9 байт
void SpecialFunction2();
// Адрес: 0x00459A80 - Размер: 0x61D байт
void SpecialFunction3();
// Адрес: 0x0045A09D - Размер: 0x1D6 байт
void SpecialFunction4();
// Адрес: 0x0045A273 - Размер: 0x231 байт
void SpecialFunction5();
// Адрес: 0x0045A4A4 - Размер: 0xB5 байт
void SpecialFunction6();
// Адрес: 0x0045A559 - Размер: 0x133 байт
void SpecialFunction7();

// Основной метод меню
// Адрес: 0x00456F00 - Размер: 0x32E байт
Menu();
// Адрес: 0x00481C30 - Размер: 0xF0 байт
~Menu();
// Адрес: 0x0045731E - Размер: 0x1E байт
void MenuDelete(byte status);
};

#endif // MENU_H
