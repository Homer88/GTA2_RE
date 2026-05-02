// menu.cpp - Реализация класса Menu (C++ версия)
// Файл создан автоматически на основе menu.h
/*#include "MenuDataBlock.h"
#include "MenuSlotConfig.h"
#include "MenuItemConfig.h"
#include "MenuStringSlot.h"
#include "MenuPage.h"*/

#include <string.h>

#include "..\Player\PlayerData.h"
#include "..\Player\PlayerSlotSlave.h"
#include "..\MapGm\MapGm.h"
#include "..\global.h"
#include "Menu.h"

Menu gMenu;
extern PlayerData gPlayerData;
extern MapGm      gMapGm;

// Примечание: Все методы реализуются как заглушки, пока не будет найден соответствующий код в ассемблере.
// Реальные адреса и реализации будут добавлены после анализа gta2.asm

enum eMenuPage {
    MENUPAGE_NONE = -1,
    MENUPAGE_START_MENU = 0,
    MENUPAGE_PLAY = 1,
    MENUPAGE_DEAD = 2,
    MENUPAGE_AREA_COMPLETE = 3,
    MENUPAGE_GAME_COMPLETE = 4,
    MENUPAGE_VIEW_HIGH_SCORE = 5,
    MENUPAGE_BONUS_AREA = 6,
    MENUPAGE_UNK_KILLS = 7,         // Страница доступна только при мультеплаере
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
    MENUPAGE_CONFIGURE = 357,
    MENUPAGE_CONFIGURE_VIDEO = 358,
    MENUPAGE_CONFIGURE_CONTROL = 359,
    MENUPAGE_CONFIGURE_SOUND = 360,
    MENUPAGE_CONFIGURE_LANGUAGE = 361,
    MENUPAGE_CONFIGURE_DEBUG1 = 362,
    MENUPAGE_CONFIGURE_DEBUG2 = 363,
    MENUPAGE_CONFIGURE_PHISIC = 370,
    MENUPAGE_NETWORK = 400,
    MENUPAGE_NETWORK_SERVER = 401,
    MENUPAGE_NETWORK_CLIENT = 402,
};
enum eMenuEntry {
    MenuEntry0 = 0,
    MenuEntry1 = 1,
};

// ============================================================================
// РЕАЛИЗАЦИЯ МЕТОДОВ (ЗАГЛУШКИ)
// Примечание: Эти реализации будут заменены на реальный код из ассемблера
// ============================================================================

// Инициализация и очистка
void Menu::InitializeState() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x933 bytes
}

void Menu::CleanupResources() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xC5B bytes
}

void Menu::CloseBinkResources() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4D bytes
}

// Управление состоянием
void Menu::SetFrontendState(int state) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xB bytes
    this->FrontendState = state;
}
void Menu::SetFrontendState() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xB bytes
    this->FrontendState = 3;
}
void Menu::UpdateState() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x103 bytes
}

void Menu::UpdateMenuFrame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF9 bytes
}

void Menu::RenderMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x18B bytes
}

// Ввод
void Menu::InitDevice() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x91 bytes
}

void Menu::ReleaseInputDevice() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x22 bytes
    LPDIRECTINPUTDEVICEA InputDevice; // eax

    InputDevice = this->InputDevice;
    if (InputDevice)
    {
        //InputDevice->Unacquire(InputDevice);
        //this->InputDevice->Release(this->InputDevice);
        this->InputDevice = 0;
    }
}

void Menu::ReadDeviceState() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4E bytes
}

void Menu::ProcessInput() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x152 bytes
}

void Menu::HandleKeyPress(int key) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2A bytes
}

void Menu::SetFrontendKeysEnabled(bool enabled) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF bytes
    this->FrontendKeysEnabled = enabled;
}

// Работа с игроком
void Menu::SetPlayerName(const char* name) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2F bytes

    wcsncpy(this->PlayerName, gPlayerData.PlayerSlotSave[this->MenuPageArray[1].MenuEntryArray[0].PlayerSlot].PlayerName, 9);
}


void Menu::SetPlayerNameFromMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4F bytes
    unsigned short PlayerSlot = this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[MenuEntry0].PlayerSlot;
    wchar_t* PlayerName = gPlayerData.PlayerSlotSave[PlayerSlot].PlayerName;
    wcsncpy(PlayerName, this->PlayerName, 9);
    this->PlayerCheat(PlayerName);
    gPlayerData.WriteFileNamePlayer(PlayerSlot);
}

bool Menu::ValidatePlayerName(const char* name) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x38 bytes
    if (!name || !*name) return false;
    // Базовая проверка: имя не должно быть пустым
    return true;
}

PlayerSlotSlave* Menu::getPlayerProfileName() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x26 bytes
    return &gPlayerData.PlayerSlotSave[gMapGm.GetPlayerSlotSave()];
}

void Menu::LoadPlayerProfile(int slot) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x25B bytes
    this->CurrentPlayerSlot = slot;
}

void Menu::SelectPlayerSlot() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x10C bytes
    timeGetTime();
    this->ProcessInput();
    int v2 = 0;
    unsigned char* _index = this->Keys;

}

int Menu::FindLastActiveArenaSlot() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4B bytes
    return this->CurrentPlayerSlot;
}

// Сохранение/загрузка
void Menu::SaveGame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1B3 bytes
}

void Menu::LoadGame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x6B bytes
}

enum eGUI {
    MenyPlayPlayerName=0,
    MenyPlayRestart=1,
    MenyPlayVievHigh=2,
    MenyPlayLevel=3,
    MenyPlayBonus=4,
    MenuHighScores=5,
};
enum eMenuPicture {
    ePlayerName = 10,
    eRestart = 11,
    eVievHigh = 6,
    eStartLevel1 = 7,
    eHighScores = 12,
    eRip = 13,
    eMenuPic_15 = 15,
    eResumSave = 16,
    eTitle = 17,
    eQuit = 2,
    eOptions = 0,
    ePlay = 1,

};
int Menu::NewGame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x169 bytes
    int pPlayerArena = 0;
    int pPageNumber=this->PageNumber;
    MenuPage *pMenuPage = &this->MenuPageArray[pPageNumber];
    int pState = this->State;
    if (pState != MENUPAGE_DEAD) {// надо смотреть возможно это статус 
        if (pPageNumber) {
            switch (pPageNumber)
            {
            case MENUPAGE_PLAY:
                pState = pMenuPage->IndexMenuActions;
                switch (pMenuPage->IndexMenuActions)
                {
                case MenyPlayPlayerName:
                    this->MenuPicture = ePlayerName;
                    break;
                case  MenyPlayRestart:
                    this->MenuPicture = eRestart;
                    break;
                case MenyPlayVievHigh:
                    this->MenuPicture = eVievHigh;
                    break;
                case MenyPlayLevel:
                    pState = gMapGm.GetPlayerArena() + 7;
                    this->MenuPicture = pState;
                    break;
                case MenyPlayBonus:
                    int pBonusStage = gMapGm.GetBonusStage();
                    gMapGm.DecodeBonusStage(pBonusStage, pPlayerArena, pState);
                    pState = pPlayerArena + 3;
                    this->MenuPicture = pState;
                    break;
                default:
                    return pState;
                    break;
                }
            case  MENUPAGE_VIEW_HIGH_SCORE:
                this->MenuPicture = eHighScores;
            case MENUPAGE_DEAD:
                this->MenuPicture = eRip;
                break;
            case MENUPAGE_AREA_COMPLETE:
            case MENUPAGE_BONUS_AREA:
            case MENUPAGE_UNK_KILLS:
            case MENUPAGE_RESULTS_PLAYER_QUIT:
            case MENUPAGE_PARENTAL_CONTROL:
                this->MenuPicture = eResumSave;
                break;
            case MENUPAGE_GAME_COMPLETE:
            case MENUPAGE_NICE_TRY:
                this->MenuPicture = eMenuPic_15;
                break;
            default:
                this->MenuPicture = pPageNumber |= MENUPAGE_CREDITS ? StartLevel1 : eTitle;
                break;
            }
        }
        else {
            pState = pMenuPage->IndexMenuActions;
            if (pState) {
                if (--pState) {
                    if (!--pState) {
                        this->MenuPicture = eQuit;
                    }
                }
                else {
                    this->MenuPicture = eOptions;
                }
            }
            else {
                this->MenuPicture = ePlay;
            }
        }
    }
    return pState;
}

bool Menu::CheckSaveFile(const char* filename) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x86 bytes
    return false; // Заглушка
}

const char* Menu::GettingSaveFile(byte index, char *savePath) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x9E bytes
    char Buffer[8];
    
    itoa(index,Buffer,10);
    strcpy(savePath, "player\\plyslot");
    strcat(savePath, Buffer);
    strcat(savePath, ".svg");

    return savePath;
}

const char* Menu::GetSaveFile() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4E bytes
    return this->SaveFilePath;
}

void Menu::SaveSettings() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x6A bytes
}

// Отрисовка и ресурсы
void Menu::PrintCentr(const char* text, float x, float y) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x43 bytes
}

void* Menu::LoadTexture(unsigned short ID) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xCC bytes
    return nullptr;
}

void Menu::LoadTexturesFromTable(void* table) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x3A bytes
    this->pTextureTable = table;
}

enum MenuPicture
{
    TGA_1 = 0,
    TGA_2=1,
    PicMenuFiles_16=16,
    Levelcomplete_tga=17,
    PicMenuFiles_18=18,
    Credits_tga=22,

};

enum MenuBackground {
    Options=0,
    Play=1,
    Quit=2,
    VievHiegh=6,
    StartLevel1=7,
    LoadSave=8,
    StartLevel3=9,
    PlayerNameMenu=10,
    Restart=11,
    HighScores=12,
    RIP=13,
    MenuPic_14=14,
    MenuPic_15=15,
    ResumSave=16,
    Title=17,
    // новое меню касаймо сети
    NetworkMenu=100,
    NetworkServer=101,
    NetworkClient=102,
    //Options
    OptionsVideo=150,
    OptionsSound=151,
    OptionsControl=152,
    OptionsDebug=153,
    OptionsLanguage=154,
};

void  Menu::FindBackground(int iMenuBackground, byte *LeftPicture, byte *RightPicture) {
    // TODO: Реализовать на основе ассемблерного кода
    // Надо дописать  нормальные переменные  и перечисление 
    // Адрес: TBD, Размер: 0x14B bytes
    switch (iMenuBackground)
    {
    case Options:
        *LeftPicture = eOptions;
        *RightPicture = TGA_1;
        break;
    case Play:
        *LeftPicture = 2;
        *RightPicture = TGA_1;
        break;
    case Quit:
        *LeftPicture = 3;
        *RightPicture = TGA_1;
        break;
        //  новый пункт меню будет написан и составлена меню.
    case NetworkMenu:
        *LeftPicture = 3;
        *RightPicture = TGA_1;
        break;
    case NetworkServer:
        *LeftPicture = 3;
        *RightPicture = TGA_1;
        break;
    case NetworkClient:
        *LeftPicture = 3;
        *RightPicture = TGA_1;
        break;
    case VievHiegh:
        *LeftPicture = 7;
        *RightPicture = TGA_2;
        break;
    case StartLevel1:
        *LeftPicture = 9;
        *RightPicture = TGA_2;
        break;
    case LoadSave:
        *LeftPicture = 10;
        *RightPicture = TGA_2;
        break;
    case StartLevel3:
        *LeftPicture = 11;
        *RightPicture = TGA_2;
        break;
    case PlayerNameMenu:
        *LeftPicture = 12;
        *RightPicture = TGA_2;
        break;
    case Restart:
        *LeftPicture = 12;
        *RightPicture = TGA_2;
        break;
    case HighScores:
        *LeftPicture = 15;
        *RightPicture = TGA_1;
        break;
    case RIP:
        *LeftPicture = 19;
        *RightPicture = TGA_1;
        break;
    case MenuPic_14:
        *LeftPicture = PicMenuFiles_18;
        *RightPicture = TGA_1;
        break;
    case MenuPic_15:
        *LeftPicture = PicMenuFiles_16;
        *RightPicture = TGA_1;
        break;
    case ResumSave:
        *LeftPicture = Levelcomplete_tga;
        *RightPicture = TGA_1;
        break;
    case Title:
        *LeftPicture = Credits_tga;
        *RightPicture = TGA_1;
    default:
        break;
    }

    return ;
}

void Menu::DrawMenuBackground() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1B5 bytes
}

void Menu::DrawMenuElements() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x46 bytes
}

void Menu::UpdateGUI() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x7D bytes
}

void Menu::LoadTextMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1512 bytes (самый большой метод!)
}

// Обработка событий и навигация
void Menu::SwitchPage(int pageIndex) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2A bytes
}

void Menu::ActivateElement(int elementIndex) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xBC bytes
}

void Menu::HandleMenuEvent(int event) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x60B bytes
}

void Menu::NavigatePages(int direction) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x66 bytes
}

void Menu::GoBack() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x66 bytes
}

// Логика меню
void Menu::MainMenuLogic() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x35C bytes
}

void Menu::PauseMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1A9 bytes
}

void Menu::OptionsMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2CB bytes
}

void Menu::PlayerList() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x16B bytes
}

void Menu::MultiplayerMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xDA bytes
}

void Menu::ServerSettings() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x9C bytes
}

// Настройки и конфигурация
void Menu::ApplyMoneyCheatIfApplicable() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x17B bytes
}

void Menu::SetDifficulty(int difficulty) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2C4 bytes
    this->Difficulty = difficulty;
}

void Menu::SelectCharacter(int characterIndex) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x6E bytes
    this->CharacterIndex = characterIndex;
}

void Menu::ConfigureControls(int config) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x38 bytes
    this->ControlConfig = config;
}

void Menu::AudioOptions() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x28 bytes
}

void Menu::VideoOptions() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x44 bytes
}

void Menu::ApplySettings() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x53 bytes
}

void Menu::ResetSettings() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x15F bytes
}

// Специальные экраны
void Menu::Intro_BIK() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x23 bytes
}

void Menu::PreIntro() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x42 bytes
}

void Menu::SelectMission() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x66 bytes
}

void Menu::WorldMap() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF9 bytes
}

void Menu::ShowStatistics() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x66 bytes
}

void Menu::ShowAwards(char arps) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x139 bytes
}

void Menu::Gallery() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2A bytes
}

bool Menu::ShowCredits() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x2A bytes
    char ars;
    gMapGm.GetBonusStage();
    return this->ShowAwards(ars) != ars;
}

void Menu::ConfirmExit() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x141 bytes
}

// Проверки и условия
void Menu::CheckConditions() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4C+0x69+0x161 bytes
}

void Menu::MenuShowJapanText() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x31 bytes
}

extern WinApi gWinApi;
enum cheat {
    CUTIE1 = 0x33A69,                 // Дает 99 жизней
    NEKKID = 0x36F62,                 // Нудисты
    MADEMAN = 0x41611,                 // Дает авторитет
    DANISGOD = 0x44D2F,                 // дает 20000
    FYOHZZ0 = 0x45118,
    FISHFLAP = 0x45AEF,                 // Small Cars
    UKGAMER = 0x45B2C,                 // all towns unlocked
    FLAMEON = 0x45EC2,                 // Бecкoнeчнaя Flame Gun
    DAVEMOON = 0x4639F,                 // Базовое оружие и бесконечные патроны
    EATSOUP = 0x4657B,                 // Бесплатные магазины
    IAMDAVEJ = 0x4672D,                 // дает 999999
    LASVEGAS = 0x46BE8,                 // Фaнаты Элвисa
    NAVARONE = 0x47178,                 // All Weapons
    COCKTART = 0x478A9,                 // За взрывы не будут выдаваться очки.
    PSJABBER = 0x478FB,                 // на бессмертие
    ARSESTAR = 0x47AF1,                 // Пocлe apecтa y вac coxpaняютcя вce имeвшиecя в нaличии пyшки
    GOREFEST = 0x484DF,                 // Количество крови в игре заметно увеличится.
    BUCKFAST = 0x4878D,                 // Режим «Бунт»
    GOURANGA = 0x49362,                 // Активация читов
    GODOFGTA = 0x49771,                 // Все оружие
    SUPZZZ0 = 0x49C76,
    SEGARULZ = 0x4A98B,                 // 10x Point Multiplier
    ITSALLUP = 0x4A9B8,                 // Выбop ypoвня
    HUNSRUS = 0x4B28C,                 // Нeвидимocть
    SCHURULZ = 0x4D5C4,                 // Двойной урон
    VOLTFEST = 0x4DA77,                 // Бecкoнeчнaя Electrical Gun
    TUMYFROG = 0x5073D,
};

bool gDo_Blood=false;
bool gBunt = false;
bool gVoltfest = false;
bool gMademan = false;
bool gLasvegas = false;
bool gNEKKID = false;
bool gDoFreeShopping = false;
bool gHeats99 = false;
bool gKeepWeaponsAfterDeath = false;
bool gGetAllWeapons = false;
bool gDoInvulnerable = false;
bool gDANISGOD = false;
bool gFYOHZZ0 = false;
bool gIAMDAVEJ = false;
bool gSEGARULZ = false;
bool gDAVEMOON = false;
bool gExplodingOn = false;
bool gFLAMEON = false;
bool gUKGAMER = false;
bool gSUPZZZ0 = false;
bool gTUMYFROG = false;
bool gSCHURULZ = false;
bool gHUNSRUS = false;
bool gFISHFLAP = false;

                    //1    2     3   4     5     6     7     8       9
int gCodeCash[8] = { 0x33D, 0x2F9, 0x17, 0x281, 0x2B, 0x329, 0x2A5, 0x0BF };
// Читы и специальные функции
void Menu::PlayerCheat(wchar_t *PlayerName) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x44E bytes
    char* PlayerNameArrayChar = gWinApi.Convertor_wchar_t_ToChar(PlayerName);
    int PlayerNameLength = wcslen(PlayerName);
    if (PlayerNameLength <= 16) {
        
        int cash = 0;
        int index = 0;
        if (PlayerNameLength) {
            do {
                cash += gCodeCash[index] * PlayerNameArrayChar[index];
                ++index;
            } while (index < PlayerNameLength);
            if (cash == GOURANGA) {
                this->isCheat = 1;
                gCheatIs = 9;
            }
        }
        if (this->isCheat) {
            switch (cash)
            {
            case GOREFEST:
                gDo_Blood = !gDo_Blood;
                gCheatIs = 9;
                return;
            case BUCKFAST:
                gBunt = !gBunt;
                gCheatIs=9;
                return;
            case VOLTFEST:
                gVoltfest = !gVoltfest;
                gCheatIs = 9;
                return;
            case MADEMAN:
                gMademan = !gMademan;
                gCheatIs = 9;
                return;
                case LASVEGAS:
                    gLasvegas = !gLasvegas;
                    gCheatIs = 9;
                    return;
                case NEKKID:
                    gNEKKID = !gNEKKID;
                    gCheatIs = 9;
                    return;
                 case EATSOUP:
                     gDoFreeShopping = !gDoFreeShopping;
                     gCheatIs = 9;
                     return;
                 case DAVEMOON:
                     gDAVEMOON = !gDAVEMOON;
                     gCheatIs = 9;
                     return;
                 case CUTIE1:
                     gHeats99 = !gHeats99;
                     gCheatIs = 9;
                     return;
                 case ARSESTAR:
                     gKeepWeaponsAfterDeath = !gKeepWeaponsAfterDeath;
                     gCheatIs = 9;
                     return;
                 case GODOFGTA:
                     gGetAllWeapons = !gGetAllWeapons;
                     gCheatIs = 9;
                     return;
                 case PSJABBER:
                     gDoInvulnerable = !gDoInvulnerable;
                     gCheatIs = 9;
                     return;
                 case DANISGOD:
                     gDANISGOD = !gDANISGOD;
                     gCheatIs = 9;
                     return;
                 case COCKTART:
                     gExplodingOn = !gExplodingOn;
                     gCheatIs = 9;
                     return;
                 case FLAMEON:
                     gFLAMEON = !gFLAMEON;
                     gCheatIs = 9;
                     return;
                 case FYOHZZ0:
                     gFYOHZZ0 = !gFYOHZZ0;
                     gCheatIs = 9;
                     return;
                 case IAMDAVEJ:
                     gIAMDAVEJ = !gIAMDAVEJ;
                     gCheatIs = 9;
                     return;
                 case SEGARULZ:
                     gSEGARULZ = !gSEGARULZ;
                     gCheatIs = 9;
                     return;
                 case UKGAMER:
                     gUKGAMER = !gUKGAMER;
                     //PlayerData::sub_4A8B00(gPlayerData);
                     this->UpdateMenuFrame();
                     gCheatIs = 9;
                     return;
                 case SUPZZZ0:
                     gSUPZZZ0 = !gSUPZZZ0;
                     //PlayerData::sub_4A8A90(gPlayerData, 1u, 0);
                     this->UpdateMenuFrame();
                     gCheatIs = 9;
                     return;
                 case TUMYFROG:
                     gTUMYFROG = !gTUMYFROG;
                     //PlayerData::sub_4A8B00(gPlayerData);
                     //PlayerData::sub_4A8A90(gPlayerData, 2u, 2u);
                     this->UpdateMenuFrame();
                     gCheatIs = 9;
                 case SCHURULZ:
                     gSCHURULZ = !gSCHURULZ;
                     gCheatIs = 9;
                     break;
                 case HUNSRUS:
                     gHUNSRUS = !gHUNSRUS;
                     gCheatIs = 9;
                     break;
                 case FISHFLAP:
                     gCheatIs = 9;
                     gFISHFLAP = !gFISHFLAP;
                     break;

            default:
                break;
            }
     }
    }
}

void Menu::SpecialFunction1() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xC1 bytes
}

void Menu::SpecialFunction2() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF9 bytes
}

void Menu::SpecialFunction3() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x61D bytes
}

void Menu::SpecialFunction4() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1D6 bytes
}

void Menu::SpecialFunction5() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x231 bytes
}
enum MENUSCREEN {
    MENUSCREEN_PLAY = 1,
    MENUSCREEN_QUIT = 2,
    MENUSCREEN_BONUSAC=3,
    MENUSCREEN_BONUSDF=4,
    MENUSCREEN_BONUSGI=5,
    MENUPAGE_CREDITS=9,
    
};

void Menu::SpecialFunction6() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xB5 bytes
    this->ProcessInput();
    this->NewGame();
    gCheatIs = 0;
    switch (this->State) {
    case MENUSCREEN_PLAY:
        if (this->PageNumber = MENUPAGE_CREDITS) {
            this->SelectPlayerSlot();
        }
        else {
            this->SpecialFunction3();
        }
        break;
    case MENUSCREEN_QUIT:
        this->SetFrontendState();
        break;
    case MENUSCREEN_BONUSAC:
        this->SpecialFunction4();
        break;
    case MENUSCREEN_BONUSDF:
        this->ResetSettings();
        break;
    case MENUSCREEN_BONUSGI:
        this->SpecialFunction5();
        break;
    default:
        //debug_Log
        break;
    }
    if (!gSkipAudio) {
        //DMAudio::Sub410520()
    }
    if (gGamma) {
        char pGamma = gRegistry.ConfigureSetScreen("gamma", 10);
        if (gGamma) {
          /*  if (SetGamma(pGamma))
                --gGamma;
            else
                gGamma=0;
                */
        }
    }
}

void Menu::SpecialFunction7() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x133 bytes
}

// Основной метод меню
Menu::Menu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x32E bytes
    


}

Menu::~Menu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF0 bytes
    this->ReleaseInputDevice();
    //if (gTextureManager){
        gTextureManager.~TextureManager();

    //}
}
void Menu::MenuDelete(byte status) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1E bytes
    this->~Menu();
    if ((status & 1) != 0)
        free(this);
}

void Menu::StartGTAManager() {
    // Здесь будет запускаться Менаджер конфигурации
}