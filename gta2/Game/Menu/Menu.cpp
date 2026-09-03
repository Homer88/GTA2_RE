// menu.cpp - Реализация класса Menu (C++ версия)
// Файл создан автоматически на основе menu.h
/*#include "MenuDataBlock.h"
#include "MenuSlotConfig.h"
#include "MenuItemConfig.h"
#include "MenuStringSlot.h"
#include "MenuPage.h"*/

#include <string.h>

#include "../global.h"
#include "../Player/PlayerData.h"
#include "../Player/PlayerSlotSlave.h"
#include "../MapGm/MapGm.h"
#include "../../Engine/Bink/BinkBuffer.h"
#include "../../Engine/Movie/Movie.h"
#include "../../Engine/DMAudio/DMAudio.h"
#include "Menu.h"

Menu gMenu;

 



// Globals from dump
extern int skip_audio;
extern int gSampleRate;
extern unsigned short word_67065C;
extern unsigned short word_67066C;
extern unsigned short word_670670;
extern unsigned short word_670664;
extern unsigned short word_67067C;
extern unsigned short word_67064C;
extern int unk_673F58;
extern int dword_673F54;
extern int unk_5EAF58;
extern int off_57361C;
extern int off_573378;
extern int off_56E788;
extern wchar_t TextWcharT[50];
extern int dest[50];
extern unsigned __int8 gAllGxtFile;

// Страница файла меню: путь/размер/изображение (из дампа).
struct PageFile {
    char  NameFiles[32];
    int   SizeFile;
    void* gbh_LoadImage;
};
extern PageFile gPageFileMenu[25];
int gbh_BlitImage(int, int, int, int, int, int, int);
void ShowTextDisplay(wchar_t*, char*, ...);
void sub_41F990(int*, unsigned __int16);
void bitShiftLeft1(int*, int);
void DrawGTATextRawMain(wchar_t*, int, int, int, int);
void DrawGTATextRaw(wchar_t*, int, int, int, int);
unsigned __int16 sub_4566C0(wchar_t*, unsigned __int16, unsigned __int16, unsigned __int16, int, unsigned int, unsigned __int16, int);
void* gWindows;
int unk_67067C;
void* gDirectInput6;
GUID DeviceGuid = { 0x6F1D2B61, 0xD5A0, 0x11CF, { 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } }; // GUID_SysKeyboard
DIDATAFORMAT* pLPCDIDATAFORMAT;
void WindowsClientCreate();
void gbh_BeginScene();
void gbh_EndScene();
void FreeSurface();
void free_0(void*);
int gbh_LoadImage[1];
char gDataMoviePrein[256];
char byte_5EAF60[256];
char unk_5EB060[256];
char aDataMoviePrein[256];
int gBool1;
int gAudioObject;
int* gCheatActive;
int unk_5EAF44;
int gImageTable;
int gbh_InitImageTable(int);
bool SetGamma(int);
bool UpdateVideoFrame();

int sub_4539D0(unsigned short, unsigned char);
int dword_662128;

// Примечание: Все методы реализуются как заглушки, пока не будет найден соответствующий код в ассемблере.
// Реальные адреса и реализации будут добавлены после анализа gta2.asm

enum eMenuPage { ///список страниц
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
    MENUPAGE_260 = 260,
    MENUPAGE_261 = 261,
    MENUPAGE_262 = 262,
    MENUPAGE_263 = 263,
    MENUPAGE_264 = 264,
    MENUPAGE_265 = 265,
    MENUPAGE_266=266,
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
// страницы MenuEntry
enum eMenuEntry {
    EntryPlay = 0,
    EntryOptions = 1,
    EntryQuit=2,
};

enum EntryPlay {
    NamePlayer = 0,
    ResumeSaveStatus = 1,
    ViewHighScores=2,
    StartPlayInArena=3,
    BonusIcon=4
};

enum eSpritePlayerMenu {
    CircleSprite = 0,
    LeftArrowRedSprite = 3,
    RightArrowRedSprite = 4,

};
enum eGUIPlayerMenu {
    PlayArenaCircle = 0,
    BonusCircle = 1,
    PlayArenaLeftArrowRed = 2,
    BonusLeftArrowRed = 3,
    PlayArenaLeftArrowRed1 = 4,
    PlayArenaRightArrowRed1 = 5,
    BonusLeftArrowRed1 = 6,
    BonusRightArrowRed1 = 7,
    PlayNameLeftArrowRed = 8,
    PlayNameRightArrowRed = 9,
};

enum MenuBackground {
    Options = 0,
    Play = 1,
    Quit = 2,
    MenuPic_3 = 3,
    MenuPic_4 = 4,
    MenuPic_5 = 5,
    VievHiegh = 6,
    StartLevel1 = 7,
    LoadSave = 8,
    StartLevel3 = 9,
    PlayerNameMenu = 10,
    Restart = 11,
    HighScores = 12,
    RIP = 13,
    MenuPic_14 = 14,
    MenuPic_15 = 15,
    ResumSave = 16,
    Title = 17,
    // новое меню касаймо сети
    NetworkMenu = 100,
    NetworkServer = 101,
    NetworkClient = 102,
    //Options
    OptionsVideo = 150,
    OptionsSound = 151,
    OptionsControl = 152,
    OptionsDebug = 153,
    OptionsLanguage = 154,
};

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

enum MenuPicture
{
    TGA_1 = 0,
    OptionsFile = 1,
    PlayFile = 2,
    QuitFile = 3,
    TGA_2 = 4,
    PicMenuFiles_5 = 5,
    PicMenuFiles_6 = 6,
    PicMenuFiles_7 = 7,
    VievHighFile = 8,
    Level1File = 9,
    LoadSaveFile = 10,
    Level3File = 11,
    PlayerNameFile = 12,
    RestartFile = 13,
    HighScoresFile = 15,
    PicMenuFiles_16 = 16,
    ResumSaveFile = 17,
    PicMenuFiles_18 = 18,
    RIPFile = 19,
    Credits_tga = 22,
};

enum eGUIAreaComplite {
    AreaComplite = 0
};

enum Entry_Arena {
    PlayNextArea = 0,
    //ResumeSaveStatus = 1,
    ReplayPreviousArea = 2,
    Contnue = 3,
    BackToMainMenu=4,
};
enum Items_Arena {
    Items_PlayNextArea = 0,
    Items_ResumeSaveStatus = 1,
    Items_ReplayPreviousArea = 2,
    Items_Contnue = 3,
    Items_BackToMainMenu = 4,
};
enum GUI_ResumeLoadSave {
    TextPlayerQuit =0,
};

enum Entry_ResumeLoadSave {
    ResumeSavedStatus = 0,
    Entry_ReplayPreviousArea = 1,
    Entry_BackToMainMenu_ResumeLoadSave = 2,
};
enum Items_ResumeLoadSave {
    ResumeLoadSave_ResumeSavedStatus = 0,
    ResumeLoadSave_ReplayPreviousArea = 1,
    ResumeLoadSave_BackToMainMenu = 2,
};
enum GUI_RIP {
    PlayerDead = 0,
};
enum Entry_RIP {
    RIP_ResumeSavedStatus = 0,
    RIP_ReplayPreviousArea = 1,
    RIP_BackToMainMenu = 2,
};

enum GUI_VIEW_HS {
    VIEW_HIGH_SCORE_0,
    VIEW_HIGH_SCORE_1,
    VIEW_HIGH_SCORE_2,
    VIEW_HIGH_SCORE_3,
    VIEW_HIGH_SCORE_4,
};
enum eEntryViewHigh{
    EntryViewHigh,
};

enum eGUICompliteGame {
    GUI_GameComplire=0,

};
enum Entry_Complire {
    Entry_BackToMainMenu = 0,
};
enum Item_Complire {
    Item_BackToMainMenu = 0,
};


enum cheat {
    CUTIE1 		= 0x33A69,                 // Дает 99 жизней
    NEKKID 		= 0x36F62,                 // Нудисты
    MADEMAN 	= 0x41611,                 // Дает авторитет
    DANISGOD 	= 0x44D2F,                 // дает 20000
    FYOHZZ0 	= 0x45118,
    FISHFLAP 	= 0x45AEF,                 // Small Cars
    UKGAMER 	= 0x45B2C,                 // all towns unlocked
    FLAMEON 	= 0x45EC2,                 // Бecкoнeчнaя Flame Gun
    DAVEMOON 	= 0x4639F,                 // Базовое оружие и бесконечные патроны
    EATSOUP 	= 0x4657B,                 // Бесплатные магазины
    IAMDAVEJ 	= 0x4672D,                 // дает 999999
    LASVEGAS 	= 0x46BE8,                 // Фaнаты Элвисa
    NAVARONE 	= 0x47178,                 // All Weapons
    COCKTART 	= 0x478A9,                 // За взрывы не будут выдаваться очки.
    PSJABBER 	= 0x478FB,                 // на бессмертие
    ARSESTAR 	= 0x47AF1,                 // Пocлe apecтa y вac coxpaняютcя вce имeвшиecя в нaличии пyшки
    GOREFEST 	= 0x484DF,                 // Количество крови в игре заметно увеличится.
    BUCKFAST 	= 0x4878D,                 // Режим «Бунт»
    GOURANGA 	= 0x49362,                 // Активация читов
    GODOFGTA 	= 0x49771,                 // Все оружие
    SUPZZZ0 	= 0x49C76,
    SEGARULZ 	= 0x4A98B,                 // 10x Point Multiplier
    ITSALLUP 	= 0x4A9B8,                 // Выбop ypoвня
    HUNSRUS 	= 0x4B28C,                 // Нeвидимocть
    SCHURULZ 	= 0x4D5C4,                 // Двойной урон
    VOLTFEST 	= 0x4DA77,                 // Бecкoнeчнaя Electrical Gun
    TUMYFROG 	= 0x5073D,
};


//  это глобальные параметры использование паролей 
bool gDo_Blood					= false;
bool gBunt 						= false;
bool gVoltfest 					= false;
bool gMademan 					= false;
bool gLasvegas 					= false;
bool gNEKKID 					= false;
bool gDoFreeShopping 			= false;
bool gHeats99 					= false;
bool gKeepWeaponsAfterDeath 	= false;
bool gGetAllWeapons 			= false;
bool gDoInvulnerable 			= false;
bool gDANISGOD 					= false;
bool gFYOHZZ0 					= false;
bool gIAMDAVEJ 					= false;
bool gSEGARULZ 					= false;
bool gDAVEMOON 					= false;
bool gExplodingOn 				= false;
bool gFLAMEON 					= false;
bool gUKGAMER 					= false;
bool gSUPZZZ0 					= false;
bool gTUMYFROG 					= false;
bool gSCHURULZ 					= false;
bool gHUNSRUS 					= false;
bool gFISHFLAP 					= false;

enum MENUSCREEN {
    MENUSCREEN_PLAY = 1,
    MENUSCREEN_QUIT = 2,
    MENUSCREEN_BONUSAC=3,
    MENUSCREEN_BONUSDF=4,
    MENUSCREEN_BONUSGI=5,
    
};
                    
int gCodeCash[8] = { 0x33D, 0x2F9, 0x17, 0x281, 0x2B, 0x329, 0x2A5, 0x0BF };

// ============================================================================
// РЕАЛИЗАЦИЯ МЕТОДОВ (ЗАГЛУШКИ)
// Примечание: Эти реализации будут заменены на реальный код из ассемблера
// ============================================================================

// Инициализация и очистка
void Menu::InitializeState() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456F80 - Размер: 0x933 байт
}

void Menu::CleanupResources() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004578B3 - Размер: 0xC5B байт
}

void Menu::CloseBinkResources() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00481D30 - Размер: 0x4D байт
}

// Управление состоянием
void Menu::SetFrontendState(int state) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00453A30 - Размер: 0xB байт
}
void Menu::SetFrontendState() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00451F60 - Размер: 0xB байт
}
void Menu::UpdateState() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456F60 - Размер: 0x103 байт
}

int  Menu::UpdateMenuFrame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456E80 - Размер: 0xF9 байт
    PlayerSlotSlave* pPlayerProfileName = this->getPlayerProfileName();
    byte pPlayerSlotSave = 0; //gMapGm.GetPlayerSlotSave(); // TODO: глобал gMapGm не входит в линковку GTA2
    MenuPage* pMenuPage = &this->MenuPageArray[this->PageNumber];
    unsigned char pLastActiveArenaSlot = this->FindLastActiveArenaSlot(pPlayerProfileName);
    unsigned char pBonusStage = this->MultiplayerMenu(pPlayerProfileName);
    unsigned char pArenaSlot = this->SelectPlayerSlotArray[pPlayerSlotSave];
    //Menu *pMenu; // НЕ инициализирован в дампе, закомментировано чтобы избежать UB

    if (pLastActiveArenaSlot >= pArenaSlot) {
        //gMapGm.SetPlayerArena(pArenaSlot); // API MapGm.h не имеет одноаргументной SetPlayerArena (есть SetPlayerArea)
    }
    else {
        //pMenu->PlayerSlotSave[0].ActiveArenaSlot = pLastActiveArenaSlot; // pMenu не инициализирован - см. TODO
        //gMapGm.SetPlayerArena(pLastActiveArenaSlot); // API MapGm.h не имеет одноаргументной SetPlayerArena (есть SetPlayerArea)
    }
    unsigned char pBonusStage1 = this->BonusStage[0];
    if (pBonusStage < pBonusStage1 || pBonusStage == 255) {
        pBonusStage1 = pBonusStage;
        this->BonusStage[0] = pBonusStage;
    }
    //gMapGm.SetBonusStage(pBonusStage1); // TODO: глобал gMapGm не входит в линковку GTA2
    this->ConfirmExit();
    this->ActivateElement();
    int result;
    if (this->GetSaveFile(pPlayerSlotSave)) {
        pMenuPage->MenuEntryArray[EntryOptions].Flag[1] = 1;
        pMenuPage->MenuItemArray[MENUPAGE_PLAY].IndexMenuActions = 1;
        result = 1;
    }
    else {
        pMenuPage->MenuEntryArray[EntryOptions].Flag[1] = 0;
        pMenuPage->MenuItemArray[MENUPAGE_PLAY].IndexMenuActions = 0;
        result = 0;
    }
    return result;
}

void Menu::RenderMenu() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00457199 - Размер: 0x18B байт
}

// Ввод
void Menu::InitDevice() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00453D80 - Размер: 0x91 байт
}

void Menu::ReleaseInputDevice() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00451FB0 - Размер: 0x22 байт
    LPDIRECTINPUTDEVICEA InputDevice; // eax

    InputDevice = this->InputDevice;
    if (InputDevice)
    {
        //InputDevice->Unacquire(InputDevice);
        //this->InputDevice->Release(this->InputDevice);
        this->InputDevice = 0;
    }
}

char Menu::ReadDeviceState() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456AB3 - Размер: 0x4E байт
    return 0;
}

void Menu::ProcessInput() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456B01 - Размер: 0x152 байт
}

bool Menu::HandleKeyPress() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456C53 - Размер: 0x2A байт
    return true;
}

bool Menu::SwitchPage() {
    //TODO: Реализовать на основе ассемблерного кода
    return true;
}

void Menu::SetFrontendKeysEnabled(bool enabled) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456C7D - Размер: 0xF байт
    this->FrontendKeysEnabled = enabled;
}

// Работа с игроком
void Menu::SetPlayerName() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00452490 - Размер: 0x2F байт
    //wcsncpy(this->PlayerName, gPlayerData.PlayerSlotSave[this->MenuPageArray[1].MenuEntryArray[0].PlayerSlot].PlayerName, 9);
    // TODO: глобал gPlayerData не входит в линковку GTA2
}


void Menu::SetPlayerNameFromMenu() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045862F - Размер: 0x4F байт
    unsigned short PlayerSlot = this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[EntryPlay].PlayerSlot;
    //wchar_t* PlayerName = gPlayerData.PlayerSlotSave[PlayerSlot].PlayerName;
    wchar_t* PlayerName = this->PlayerName;
    wcsncpy(PlayerName, this->PlayerName, 9);
    this->PlayerCheat(PlayerName);
    //gPlayerData.WriteFileNamePlayer(PlayerSlot); // TODO: метод не реализован + глобал gPlayerData не входит в линковку GTA2
}

bool Menu::ValidatePlayerName(const char* name) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045867E - Размер: 0x38 байт
    if (!name || !*name) return false;
    // Базовая проверка: имя не должно быть пустым
    return true;
}

PlayerSlotSlave* Menu::getPlayerProfileName() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004586B6 - Размер: 0x26 байт
    //return &gPlayerData.PlayerSlotSave[gMapGm.GetPlayerSlotSave()];
    return 0; // TODO: глобалы gPlayerData/gMapGm не входят в линковку GTA2
}

void Menu::LoadPlayerProfile(int slot) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004586DC - Размер: 0x25B байт
    this->CurrentPlayerSlot = slot;
}

unsigned short Menu::SelectPlayerSlot() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458937 - Размер: 0x10C байт
    return 0;
}

unsigned char Menu::FindLastActiveArenaSlot(PlayerSlotSlave *PlayName) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458A43 - Размер: 0x4B байт
    return (unsigned char)this->CurrentPlayerSlot;
}

// Сохранение/загрузка
void Menu::SaveGame() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00452940 - Размер: 0x1B3 байт
}

void Menu::LoadGame() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458C41 - Размер: 0x6B байт
}




int Menu::NewGame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00455F90 - Размер: 0x169 байт
    unsigned char arenaOut = 0;
    unsigned char out4 = 0;
    int pPlayerArena = 0;
    int pPageNumber=this->PageNumber;
    int pBonusStage;
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
                    //pState = gMapGm.GetPlayerArena() + 7; // TODO: глобал gMapGm не входит в линковку GTA2
                    this->MenuPicture = pState;
                    break;
                case MenyPlayBonus:
                    //pBonusStage = gMapGm.GetBonusStage();
                    //gMapGm.DecodeBonusStage((unsigned char)pBonusStage, &arenaOut, &out4); // TODO: глобал gMapGm не входит в линковку GTA2, метод DecodeBonusStage не реализован
                    pState = arenaOut + 3;
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
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458E15 - Размер: 0x86 байт
    return false; // Заглушка
}

char Menu::GettingSaveFile(byte Index, char * FileNameSave) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004528A0 - Размер: 0x9E байт
    char Buffer[8];

    itoa(Index,Buffer,10);
    strcpy(FileNameSave, "player\\plyslot");
    strcat(FileNameSave, Buffer);
    strcat(FileNameSave, ".svg");

    return *FileNameSave;
}

char Menu::GetSaveFile(unsigned char SlotSave) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458F39 - Размер: 0x4E байт
    return this->SaveFilePath[0];
}

void Menu::SaveSettings() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458F87 - Размер: 0x6A байт
}

// Отрисовка и ресурсы
unsigned short Menu::clearArrayTail() {
    unsigned char currentIdx = this->CurentArrayIndex;

    if (currentIdx >= 9)
        return currentIdx;

    for (unsigned char i = currentIdx; i < 9; ++i)
        this->MenuItems[i] = 0;

    return 0;
}

int Menu::PrintCentr(const wchar_t* text, float x, float y) {
    unsigned short stringLength = (unsigned short)x;
    unsigned short centrScreen = (unsigned short)y;

    if (stringLength == 0xFFFF)
        return centrScreen - (gFont.GetStringWidth((wchar_t*)text, this->FontStyle) >> 1);
    else
        return centrScreen - (gFont.GetStringWidth((wchar_t*)text, stringLength) >> 1);
}

void* Menu::LoadTexture(unsigned short ID) { return 0; }

void Menu::LoadTexturesFromTable(void* table) { }




//  поиск картинки устанавливает с помощью  пункта меню.
void Menu::FindBackground(int iMenuBackground, byte *LeftPicture, byte *RightPicture) {
    switch (iMenuBackground)
    {
    case Options:
        *LeftPicture = OptionsFile;
        *RightPicture = TGA_1;
        break;
    case Play:
        *LeftPicture = PlayFile;
        *RightPicture = TGA_1;
        break;
    case Quit:
        *LeftPicture = QuitFile;
        *RightPicture = TGA_1;
        break;
    case MenuPic_3:
        *LeftPicture = PicMenuFiles_5;
        *RightPicture = TGA_2;
        break;
    case MenuPic_4:
        *LeftPicture = PicMenuFiles_6;
        *RightPicture = TGA_2;
        break;
    case MenuPic_5:
        *LeftPicture = PicMenuFiles_7;
        *RightPicture = TGA_2;
        break;
    case VievHiegh:
        *LeftPicture = VievHighFile;
        *RightPicture = TGA_2;
        break;
    case StartLevel1:
        *LeftPicture = Level1File;
        *RightPicture = TGA_2;
        break;
    case LoadSave:
        *LeftPicture = LoadSaveFile;
        *RightPicture = TGA_2;
        break;
    case StartLevel3:
        *LeftPicture = Level3File;
        *RightPicture = TGA_2;
        break;
    case PlayerNameMenu:
        *LeftPicture = PlayerNameFile;
        *RightPicture = TGA_2;
        break;
    case Restart:
        *LeftPicture = RestartFile;
        *RightPicture = TGA_2;
        break;
    case HighScores:
        *LeftPicture = HighScoresFile;
        *RightPicture = TGA_1;
        break;
    case RIP:
        *LeftPicture = RIPFile;
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
        *LeftPicture = ResumSaveFile;
        *RightPicture = TGA_1;
        break;
    case Title:
        *LeftPicture = Credits_tga;
        *RightPicture = TGA_1;
        break;
	case 39: //Options
	case 40: //Video
	case 41: // Sound
	case 42: // Launguag
	case 43: // Net Config
	case 44: // Debug
	// net
	case 45: // Net
	case 46: //server
	case 47: //client
	case 48: //Game Mode 1
	case 49: //game Mode 2
	case 50: //controler
		break;
    default:
        break;
    }
}

void Menu::DrawMenuBackground() { }

unsigned __int8 Menu::DrawMenuElements(unsigned __int8 a2) { return 0; }

unsigned __int8 Menu::UpdateGUI(unsigned __int8 PlayerArena) { return 0; }

void Menu::LoadTextMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x1512 bytes (самый большой метод!)
    this->MenuPageArray[MENUPAGE_START_MENU].CurentMenuPage = 3; // число элементов на странице
    //Пункт Меню Play
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].X = 300;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].Y = 250;
    wchar_t* Play = (wchar_t*)gText.Bsearch("play");
    wcsncpy(this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].TextMenuElementArray, Play, 50);
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].SelectMenu = MENUPAGE_PLAY; //Это какие дествие будут выполняться
    //Пункт Меню Options
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].X = 300;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].Y = 250;
    wchar_t* Options = (wchar_t*)gText.Bsearch("Options");
    wcsncpy(this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].TextMenuElementArray, Options, 50);
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].SelectMenu = MENUPAGE_GTA2MANAGER; //Это какие дествие будут выполняться
    //Пункт Меню Options

    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].X = 300;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].Y = 290;
    wchar_t* Quit = (wchar_t*)gText.Bsearch("quit");
    wcsncpy(this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].TextMenuElementArray, Quit, 50);
    this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].SelectMenu = MENUPAGE_CREDITS;


    //FixMe
    if (false)
    {
        wchar_t* No_cd1 = (wchar_t*)gText.Bsearch("no_cd1");
        wcsncpy(this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].TextMenuElementArray, No_cd1, 50u);
        this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryPlay].SelectMenu = MENUPAGE_CREDITS;

        wchar_t* No_cd2 = (wchar_t*)gText.Bsearch("no_cd2");
        wcsncpy(this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].TextMenuElementArray, No_cd2, 50u);
        this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryOptions].SelectMenu = MENUPAGE_CREDITS;

        wchar_t* No_cd3 = (wchar_t*)gText.Bsearch("no_cd3");
        wcsncpy(this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].TextMenuElementArray, No_cd3, 50u);
        this->MenuPageArray[MENUPAGE_START_MENU].MenuEntryArray[EntryQuit].SelectMenu = MENUPAGE_CREDITS;
    }

    this->MenuPageArray[MENUPAGE_START_MENU].MenuItemArray[EntryPlay].X = 280;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuItemArray[EntryPlay].Y = 258;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuItemArray[EntryOptions].X = 280;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuItemArray[EntryOptions].Y = 278;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuItemArray[EntryQuit].X = 280;
    this->MenuPageArray[MENUPAGE_START_MENU].MenuItemArray[EntryQuit].Y = 298;
    this->MenuPageArray[MENUPAGE_START_MENU].IndexMenuActions = MENUPAGE_START_MENU;
    this->MenuPageArray[MENUPAGE_START_MENU].SelectActiveElementDefault = EntryPlay;
    this->PlayMenuCreate();
    this->CompliteGameMenuCreate();
    this->AreaCompliteMenuCreate();
    this->ResumeLoadSaveCreate();
    this->YouAreDead_RIP();
    this->HighScoresForAreaCreate();
    this->BonusStageAMenuCreate();
    this->PlayVideoMovieMenuCreate();
    this->PlayVideoMovieIntroMenuCreate();
    this->BonusStageBMenuCreate();
    this->BonusStageCMenuCreate();
    this->NetworkGameMenuCreate();
    this->OptionsMenuCreate();
    this->NiceTryMenuCreate();
    this->CodeDebugMenuCreate();
    this->NetworkServerMenuCreate();
    this->NetworkClientMenuCreate();




}


inline void Menu::PlayMenuCreate() {

    //PlayMenu
    this->MenuPageArray[MENUPAGE_PLAY].CurentMenuPage = 5;

    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].MenuAction = 2;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].X = 300;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].Y = 210;
    wchar_t* charcrt = (wchar_t*)gText.Bsearch("charctr");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].TextMenuElementArray, charcrt, 50);
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].PlayerSlot = 0;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].PlayerSlotNext = 0;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].Index = 7;
    unsigned short countPlayer = 0;
    do {
        countPlayer++;
        this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].Flag[countPlayer] = 1;
    } while (countPlayer <= this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[NamePlayer].Index);

    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ResumeSaveStatus].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ResumeSaveStatus].X = 300;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ResumeSaveStatus].Y = 230;
    wchar_t* wResumeSaveStatus = (wchar_t*)gText.Bsearch("savepos");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ResumeSaveStatus].TextMenuElementArray, wResumeSaveStatus, 50);
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ResumeSaveStatus].SelectMenu = MENUPAGE_260;

    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ViewHighScores].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ViewHighScores].X = 300;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ViewHighScores].Y = 250;
    wchar_t* wViewHighScores = (wchar_t*)gText.Bsearch("hi_scre");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ViewHighScores].TextMenuElementArray, wViewHighScores, 50);
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[ViewHighScores].SelectMenu = MENUPAGE_VIEW_HIGH_SCORE;

    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[StartPlayInArena].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[StartPlayInArena].X = 300;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[StartPlayInArena].Y = 270;
    wchar_t* wStartPlayInArena = (wchar_t*)gText.Bsearch("strlev");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[StartPlayInArena].TextMenuElementArray, wStartPlayInArena, 50);
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[StartPlayInArena].SelectMenu = MENUPAGE_264;

    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[BonusIcon].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[BonusIcon].X = 300;
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[BonusIcon].Y = 270;
    wchar_t* bonusIcon = (wchar_t*)gText.Bsearch("bonslev");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[BonusIcon].TextMenuElementArray, bonusIcon, 50);
    this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[BonusIcon].SelectMenu = MENUPAGE_265;


    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[NamePlayer].X = 280;
    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[NamePlayer].Y = 228;

    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[ResumeSaveStatus].X = 280;
    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[ResumeSaveStatus].Y = 238;

    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[ViewHighScores].X = 280;
    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[ViewHighScores].Y = 258;

    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[StartPlayInArena].X = 280;
    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[StartPlayInArena].Y = 278;

    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[BonusIcon].X = 280;
    this->MenuPageArray[MENUPAGE_PLAY].MenuItemArray[BonusIcon].Y = 358;


    this->MenuPageArray[MENUPAGE_PLAY].IndexMenuActions = 3;
    this->MenuPageArray[MENUPAGE_PLAY].SelectActiveElementDefault = StartPlayInArena;

    this->MenuPageArray[MENUPAGE_PLAY].NextMenuPage = 10;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaCircle].Element = 3;// Иконка бонуса //0
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaCircle].X = 420;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaCircle].Y = 310;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaCircle].SpriteInterface = CircleSprite;

    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusCircle].Element = 3; //1
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusCircle].X = 420;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusCircle].Y = 390;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusCircle].SpriteInterface = CircleSprite;

    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed].Element = 1; //2
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed].X = 410;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed].Y = 298;
    wchar_t* CarDamage = (wchar_t*)gText.Bsearch("car_dam");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed].TextMenuElementArray, CarDamage, 50);
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed].dX = 8; //Переменная должна быть

    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed].Element = 1; //3
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed].X = 410;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed].Y = 378;
    wchar_t* CarDamage1 = (wchar_t*)gText.Bsearch("car_dam");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed].TextMenuElementArray, CarDamage1, 50);
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed].dX = 8; //Переменная должна быть

    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed1].X = 380; //4
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed1].Y = 310;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed1].Element = 3;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaLeftArrowRed1].SpriteInterface = LeftArrowRedSprite;



    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaRightArrowRed1].X = 460;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaRightArrowRed1].Y = 310;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaRightArrowRed1].Element = 3;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayArenaRightArrowRed1].SpriteInterface = RightArrowRedSprite;


    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed1].X = 380;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed1].Y = 390;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed1].Element = 3;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusLeftArrowRed1].SpriteInterface = LeftArrowRedSprite;


    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusRightArrowRed1].X = 460;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusRightArrowRed1].Y = 390;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusRightArrowRed1].Element = 3;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[BonusRightArrowRed1].SpriteInterface = RightArrowRedSprite;

    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameLeftArrowRed].X = 290;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameLeftArrowRed].Y = 222;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameLeftArrowRed].Element = 3;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameLeftArrowRed].SpriteInterface = LeftArrowRedSprite;

    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameRightArrowRed].X = 580;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameRightArrowRed].Y = 222;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameRightArrowRed].Element = 3;
    this->MenuPageArray[MENUPAGE_PLAY].GUIArray[PlayNameRightArrowRed].SpriteInterface = RightArrowRedSprite;


}

inline void Menu::CompliteGameMenuCreate() {
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].NextMenuPage = 1;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].NextMenuPage = 1;

    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].Element = 1;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].Y = 230;

    wchar_t* GameComplire = (wchar_t*)gText.Bsearch("gam_cmp");
    wcsncpy(this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].TextMenuElementArray, GameComplire, 50);

    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].dX = 13;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].TextMenuElementArray, 14, 320);
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].GUIArray[GUI_GameComplire].dY = 4;

    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuEntryArray[Entry_BackToMainMenu].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuEntryArray[Entry_BackToMainMenu].X = 180;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuEntryArray[Entry_BackToMainMenu].Y = 410;
    wchar_t* BackToMainMenu = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuEntryArray[Entry_BackToMainMenu].TextMenuElementArray, BackToMainMenu, 50);

    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuEntryArray[Entry_BackToMainMenu].SelectMenu = MENUPAGE_START_MENU;

    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuItemArray[Item_BackToMainMenu].X = 160;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].MenuItemArray[Item_BackToMainMenu].Y = 410;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].IndexMenuActions = Item_BackToMainMenu;
    this->MenuPageArray[MENUPAGE_GAME_COMPLETE].SelectActiveElementDefault = Item_BackToMainMenu;
}



inline void Menu::AreaCompliteMenuCreate() {

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].CurentMenuPage = 5;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].NextMenuPage = 1;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].GUIArray[AreaComplite].Element = 1;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].GUIArray[AreaComplite].X = 35;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].GUIArray[AreaComplite].Y = 11;

    wchar_t* wAreaComplite = (wchar_t*)gText.Bsearch("cmpltd");
    wcsncat(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].GUIArray[AreaComplite].TextMenuElementArray, 
        wAreaComplite, 50);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].GUIArray[AreaComplite].dX = 11;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].Y = 365;

    wchar_t* wPlayNextArea = (wchar_t*)gText.Bsearch("nxt_lvl");
    wcsncpy(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].TextMenuElementArray, wPlayNextArea, 50);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].X = 
        this->PrintCentr(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].StringLength, 320);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[PlayNextArea].SelectMenu = MENUPAGE_261;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].Y = 385;
    wchar_t* wResumeSaveStatus = (wchar_t*)gText.Bsearch("savepos");
    wcsncpy(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].TextMenuElementArray,
            wResumeSaveStatus, 50);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].StringLength, 320);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ResumeSaveStatus].SelectMenu = MENUPAGE_260;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].Y = 405;

    wchar_t* wReplayPreviousArea = (wchar_t*)gText.Bsearch("replay");

    wcsncpy(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].TextMenuElementArray, wReplayPreviousArea, 50);

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].X = 
        this->PrintCentr(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].StringLength, 320);

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[ReplayPreviousArea].SelectMenu = MENUPAGE_259;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].Y = 425;
    wchar_t* wContnue = (wchar_t*)gText.Bsearch("contnue");
    wcsncpy(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].TextMenuElementArray, wContnue, 50);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].StringLength, 320);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[Contnue].SelectMenu = MENUPAGE_266;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[BackToMainMenu].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[BackToMainMenu].Y = 445;
    wchar_t* wBackToMainMenu = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[4].TextMenuElementArray, wBackToMainMenu, 50);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[BackToMainMenu].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[BackToMainMenu].TextMenuElementArray, 
        this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[BackToMainMenu].StringLength, 320);
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuEntryArray[BackToMainMenu].SelectMenu = MENUPAGE_START_MENU;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_PlayNextArea].X = 150;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_PlayNextArea].Y = 373;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_ResumeSaveStatus].X = 150;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_ResumeSaveStatus].Y = 393;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_ReplayPreviousArea].X = 150;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_ReplayPreviousArea].Y = 413;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_Contnue].X = 150;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_Contnue].Y = 433;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_BackToMainMenu].X = 150;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].MenuItemArray[Items_BackToMainMenu].Y = 453;

    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].IndexMenuActions = Items_PlayNextArea;
    this->MenuPageArray[MENUPAGE_AREA_COMPLETE].SelectActiveElementDefault = Items_PlayNextArea;
}


inline void Menu::ResumeLoadSaveCreate() {

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].CurentMenuPage = 3;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].NextMenuPage = 1;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].GUIArray[TextPlayerQuit].Element = 1;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].GUIArray[TextPlayerQuit].X = 35;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].GUIArray[TextPlayerQuit].Y = 11;
    wchar_t* wTextPlayerQuit = (wchar_t*)gText.Bsearch("plr_qut");
    gWinApi.CopyWideString(this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].GUIArray[TextPlayerQuit].TextMenuElementArray, 
                    wTextPlayerQuit);

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].GUIArray[TextPlayerQuit].dX = 13;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].GUIArray[TextPlayerQuit].dY = 5;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].Y = 392;
    wchar_t* wResumeSavedStatus = (wchar_t*)gText.Bsearch("savepos");

    wcsncpy(this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].TextMenuElementArray, wResumeSavedStatus, 50);
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].X = 
        this->PrintCentr(this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].StringLength, 320);

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[ResumeSavedStatus].SelectMenu = MENUPAGE_260;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].Y = 412;

    wchar_t* wReplayPreviousArea = (wchar_t*)gText.Bsearch("replay");
    wcsncpy(this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].TextMenuElementArray,
        wReplayPreviousArea, 50);

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].StringLength, 320);
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_ReplayPreviousArea].SelectMenu = 259;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].Y = 432;

    wchar_t* wBackToMainMenu = (wchar_t*)gText.Bsearch("mainmen");

    wcsncpy(this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].TextMenuElementArray,
        wBackToMainMenu, 50);

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].X = this->PrintCentr(
          this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].TextMenuElementArray,
            this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].StringLength, 320);

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuEntryArray[Entry_BackToMainMenu_ResumeLoadSave].SelectMenu = MENUPAGE_START_MENU;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuItemArray[ResumeLoadSave_ResumeSavedStatus].X = 150;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuItemArray[ResumeLoadSave_ResumeSavedStatus].Y = 400;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuItemArray[ResumeLoadSave_ReplayPreviousArea].X = 150;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuItemArray[ResumeLoadSave_ReplayPreviousArea].Y = 420;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuItemArray[ResumeLoadSave_BackToMainMenu].X = 150;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].MenuItemArray[ResumeLoadSave_BackToMainMenu].Y = 440;

    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].IndexMenuActions = ResumeLoadSave_ResumeSavedStatus;
    this->MenuPageArray[MENUPAGE_RESULTS_PLAYER_QUIT].SelectActiveElementDefault = ResumeLoadSave_ResumeSavedStatus;
}

inline  void Menu::YouAreDead_RIP() {
    this->MenuPageArray[MENUPAGE_DEAD].CurentMenuPage = 3;
    this->MenuPageArray[MENUPAGE_DEAD].NextMenuPage = 1;

    this->MenuPageArray[MENUPAGE_DEAD].GUIArray[PlayerDead].Element = 1;
    this->MenuPageArray[MENUPAGE_DEAD].GUIArray[PlayerDead].X = 35;
    this->MenuPageArray[MENUPAGE_DEAD].GUIArray[PlayerDead].Y = 11;

    wchar_t* wPlayerDead = (wchar_t*)gText.Bsearch("plr_ded");
    wcsncat(this->MenuPageArray[MENUPAGE_DEAD].GUIArray[PlayerDead].TextMenuElementArray, wPlayerDead, 50);
    this->MenuPageArray[MENUPAGE_DEAD].GUIArray[PlayerDead].dX = 13;
    this->MenuPageArray[MENUPAGE_DEAD].GUIArray[PlayerDead].dY = 0;

    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].Y = 392;
    wchar_t* wResumeSavedStatus = (wchar_t*)gText.Bsearch("savepos");
    wcsncat(this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].TextMenuElementArray, 
        wResumeSavedStatus, 50);
    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].StringLength, 320);

    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].SelectMenu = MENUPAGE_260;
    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ResumeSavedStatus].MenuAction = MENUPAGE_PLAY;

    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ReplayPreviousArea].Y = 412;

    wchar_t* wReplayPreviousArea = (wchar_t*)gText.Bsearch("replay");
    wcsncat(this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ReplayPreviousArea].TextMenuElementArray, 
        wReplayPreviousArea, 50);

    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ReplayPreviousArea].X =
        this->PrintCentr(
            this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ReplayPreviousArea].TextMenuElementArray,
            this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ReplayPreviousArea].StringLength, 320);

    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_ReplayPreviousArea].SelectMenu = MENUPAGE_259;

    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].Y = 432;
    wchar_t* wBackToMainMenu = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].TextMenuElementArray, 
        wBackToMainMenu, 50);
    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].StringLength, 320);
    this->MenuPageArray[MENUPAGE_DEAD].MenuEntryArray[RIP_BackToMainMenu].SelectMenu = 0;

    this->MenuPageArray[MENUPAGE_DEAD].MenuItemArray[RIP_ResumeSavedStatus].X = 150;
    this->MenuPageArray[MENUPAGE_DEAD].MenuItemArray[RIP_ResumeSavedStatus].Y = 400;

    this->MenuPageArray[MENUPAGE_DEAD].MenuItemArray[RIP_ReplayPreviousArea].X = 150;
    this->MenuPageArray[MENUPAGE_DEAD].MenuItemArray[RIP_ReplayPreviousArea].Y = 420;

    this->MenuPageArray[MENUPAGE_DEAD].MenuItemArray[RIP_BackToMainMenu].X = 150;
    this->MenuPageArray[MENUPAGE_DEAD].MenuItemArray[RIP_BackToMainMenu].Y = 440;
    this->MenuPageArray[MENUPAGE_DEAD].SelectActiveElementDefault = RIP_ResumeSavedStatus;
}


inline void Menu::HighScoresForAreaCreate() {
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].CurentMenuPage = 1;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].NextMenuPage = 5;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].X = 300;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].Y = 155;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].PlayerSlot = 0;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].PlayerSlotNext = 0;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].Index = 11;
    int list = 0;
    do {
        this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].Flag[list] = 1;
        ++list;
    } while (list <= this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuEntryArray[EntryViewHigh].Index);

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuItemArray[EntryViewHigh].X = 280;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].MenuItemArray[EntryViewHigh].Y = 163;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].IndexMenuActions = EntryViewHigh;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].SelectActiveElementDefault = EntryViewHigh;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_0].Element = 3;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_0].X = 450;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_0].Y = 197;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_0].SpriteInterface = 0;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_1].Element = 1;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_1].X = 440;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_1].Y = 185;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_1].dX = 8;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_2].Element = 3;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_2].X = 410;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_2].Y = 197;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_2].SpriteInterface = 3;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_3].Element = 3;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_3].X = 490;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_3].Y = 197;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_3].SpriteInterface = 4;

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_4].Element = 1;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_4].X = 340;
    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_4].Y = 12;

    wchar_t* wHighScoresForAreaText = (wchar_t*)gText.Bsearch("hi_scre");
    wcsncpy(this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_4].TextMenuElementArray,
        wHighScoresForAreaText, 30);

    this->MenuPageArray[MENUPAGE_VIEW_HIGH_SCORE].GUIArray[VIEW_HIGH_SCORE_4].dX = 8;
}

inline void Menu::BonusStageAMenuCreate() {

}


inline void Menu::PlayVideoMovieMenuCreate() {
    this->MenuPageArray[MENUPAGE_15].CurentMenuPage = 1;
    this->MenuPageArray[MENUPAGE_15].NextMenuPage = 0;// возможно это следующая страница 
    this->MenuPageArray[MENUPAGE_15].MenuEntryArray[0].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_15].MenuEntryArray[0].X = 200;
    this->MenuPageArray[MENUPAGE_15].MenuEntryArray[0].Y = 280;
    wchar_t* pmainmen = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_15].MenuEntryArray[0].TextMenuElementArray, pmainmen, 0x32u);
    this->MenuPageArray[MENUPAGE_15].MenuEntryArray[0].SelectMenu = MENUPAGE_START_MENU;
    this->MenuPageArray[MENUPAGE_15].MenuItemArray[0].X = 180;
    this->MenuPageArray[MENUPAGE_15].MenuItemArray[0].Y = 288;
    this->MenuPageArray[MENUPAGE_15].IndexMenuActions = 0;
    this->MenuPageArray[MENUPAGE_15].SelectActiveElementDefault = 0;
}
inline void Menu::PlayVideoMovieIntroMenuCreate() {

    this->MenuPageArray[MENUPAGE_PLAY_INTRO].CurentMenuPage = 1;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].NextMenuPage = 0;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuEntryArray[0].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuEntryArray[0].X = 200;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuEntryArray[0].Y = 280;
    wchar_t* wMainMenu = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuEntryArray[0].TextMenuElementArray, wMainMenu, 50);
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuEntryArray[0].SelectMenu = MENUPAGE_START_MENU;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuItemArray[0].X = 180;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].MenuItemArray[0].Y = 288;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].IndexMenuActions = 0;
    this->MenuPageArray[MENUPAGE_PLAY_INTRO].SelectActiveElementDefault = 0;
}
inline void Menu::BonusStageBMenuCreate() {}

inline void Menu::BonusStageCMenuCreate() {
    this->MenuPageArray[MENUPAGE_BONUS_AREA].CurentMenuPage = 3;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].NextMenuPage = 3;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[0].Element = 1;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[0].X = 35;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[0].Y = 11;
    wchar_t* wBonusStageText = (wchar_t*)gText.Bsearch("bonslev");
    wcsncpy(this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[0].TextMenuElementArray, wBonusStageText, 50);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[0].dX = 13;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[0].dY = 5;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[1].Element = 1;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[1].X = 170;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[1].Y = 250;
    wchar_t* v39 = (wchar_t*)gText.Bsearch("score");
    wcsncpy(this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[1].TextMenuElementArray, v39, 50);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[2].Element = 1;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[2].X = 400;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[2].Y = 250;

    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].GUIArray[2].dX = 5;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].Y = 340;
    wchar_t* v41 = (wchar_t*)gText.Bsearch("repbons");
    wcsncpy(this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].TextMenuElementArray, v41, 50);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].StringLength,
        320);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[0].SelectMenu = MENUPAGE_259;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].Y = 360;
    wchar_t* v42 = (wchar_t*)gText.Bsearch("nxt_lvl");
    wcsncpy(this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].TextMenuElementArray, v42, 50);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].StringLength,
        320);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[1].SelectMenu = MENUPAGE_BONUS_AREA;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].Y = 380;
    wchar_t* v43 = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].TextMenuElementArray, v43, 50);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].X = Menu::PrintCentr(
        this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].StringLength,
        320);
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuEntryArray[2].SelectMenu = MENUPAGE_START_MENU;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuItemArray[0].X = 150;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuItemArray[0].Y = 348;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuItemArray[1].X = 150;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuItemArray[1].Y = 368;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuItemArray[2].X = 150;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].MenuItemArray[2].Y = 388;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].IndexMenuActions = 0;
    this->MenuPageArray[MENUPAGE_BONUS_AREA].SelectActiveElementDefault = 0;
}
// это мое меню уже 
inline void Menu::NetworkGameMenuCreate() {
    this->MenuPageArray[MENUPAGE_UNK_KILLS].CurentMenuPage = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].NextMenuPage = 14;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[0].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[0].X = 35;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[0].Y = 11;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[0].dX = 13;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[0].dY = 5;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[1].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[1].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[1].Y = 170;
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[1].TextMenuElementArray, L"gText_Menu", 50);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[2].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[2].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[2].Y = 190;
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[2].TextMenuElementArray, L"gText_Menu", 50);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[3].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[3].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[3].Y = 210;
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[3].TextMenuElementArray, L"gText_Menu", 50);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[4].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[4].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[4].Y = 230;
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[4].TextMenuElementArray, L"gText_Menu", 50);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[5].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[5].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[5].Y = 250;
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[5].TextMenuElementArray, L"gText_Menu", 0x32u);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[6].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[6].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[6].Y = 270;
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[6].TextMenuElementArray, L"gText_Menu", 0x32u);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[7].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[7].Y = 300;
    wchar_t* v44 = (wchar_t*)gText.Bsearch("kills_h");
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[7].TextMenuElementArray, v44, 0x32u);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[7].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[7].TextMenuElementArray, 
        this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[7].dX, 320);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[8].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[8].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[8].Y = 320;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[9].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[9].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[9].Y = 340;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[10].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[10].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[10].Y = 360;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[11].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[11].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[11].Y = 380;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[12].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[12].X = 100;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[12].Y = 400;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[13].Element = 1;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[13].X = 30;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].GUIArray[13].Y = 150;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].Y = 430;
    wchar_t* v45 = (wchar_t*)gText.Bsearch("quit");
    wcsncpy(this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].TextMenuElementArray, v45, 50);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].X = this->PrintCentr(
        this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].TextMenuElementArray,
        this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].StringLength,
        320);
    this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuEntryArray[0].SelectMenu = MENUPAGE_QUIT;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuItemArray[0].X = 180;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].MenuItemArray[0].Y = 438;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].IndexMenuActions = 0;
    this->MenuPageArray[MENUPAGE_UNK_KILLS].SelectActiveElementDefault = 0;

}
inline void Menu::OptionsMenuCreate() {


}

inline void Menu::NiceTryMenuCreate() {
    this->MenuPageArray[MENUPAGE_NICE_TRY].CurentMenuPage = 1;
    this->MenuPageArray[MENUPAGE_NICE_TRY].NextMenuPage = 1;
    this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].Element = 1;
    this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].Y = 230;
    wchar_t* v48 = (wchar_t*)gText.Bsearch("nicetry");
    wcsncpy(this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].TextMenuElementArray, v48, 0x32u);

    this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].dX = 13;
    this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].X =
        this->PrintCentr(this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].TextMenuElementArray, 13, 320);
    this->MenuPageArray[MENUPAGE_NICE_TRY].GUIArray[0].dY = 4;
    this->MenuPageArray[MENUPAGE_NICE_TRY].MenuEntryArray[0].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_NICE_TRY].MenuEntryArray[0].X = 180;
    this->MenuPageArray[MENUPAGE_NICE_TRY].MenuEntryArray[0].Y = 410;
    wchar_t* wMainmen = (wchar_t*)gText.Bsearch("mainmen");
    wcsncpy(this->MenuPageArray[MENUPAGE_NICE_TRY].MenuEntryArray[0].TextMenuElementArray, wMainmen, 0x32u);
    this->MenuPageArray[MENUPAGE_NICE_TRY].MenuEntryArray[0].SelectMenu = MENUPAGE_START_MENU;
    this->MenuPageArray[MENUPAGE_NICE_TRY].MenuItemArray[0].X = 160;
    this->MenuPageArray[MENUPAGE_NICE_TRY].MenuItemArray[0].Y = 418;
    this->MenuPageArray[MENUPAGE_NICE_TRY].IndexMenuActions = 0;
    this->MenuPageArray[MENUPAGE_NICE_TRY].SelectActiveElementDefault = 0;
}

inline void Menu::CodeDebugMenuCreate() {
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].CurentMenuPage = 1;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].NextMenuPage = 5;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].MenuEntryArray[0].MenuAction = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].MenuEntryArray[0].X = 170;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].MenuEntryArray[0].Y = 340;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].MenuEntryArray[0].SelectMenu = MENUPAGE_QUIT;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[0].Element = 1;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[0].X = 20;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[0].Y = 160;
    wchar_t* v50 = (wchar_t*)gText.Bsearch("fr_ent1");
    wcsncpy(this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[0].TextMenuElementArray, v50, 50);
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[1].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[1].X = 20;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[1].Y = 180;
    wchar_t* v51 = (wchar_t*)gText.Bsearch("fr_ent2");
    wcsncpy(this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[1].TextMenuElementArray, v51, 50);
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[2].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[2].X = 20;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[2].Y = 200;
    wcsncpy(this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[2].TextMenuElementArray, L"gText_Menu:", 50);
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[3].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[3].X = 20;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[3].Y = 300;
    wchar_t* v52 = (wchar_t*)gText.Bsearch("fr_pmpt");
    wcsncpy(this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[3].TextMenuElementArray, v52, 50);
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[4].Element = MENUPAGE_PLAY;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[4].X = 20;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[4].Y = 320;
    wchar_t* wScore = (wchar_t*)gText.Bsearch("score");
    wcsncpy(this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].GUIArray[4].TextMenuElementArray, wScore, 50);
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].MenuItemArray[0].X = 150;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].MenuItemArray[0].Y = 348;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].IndexMenuActions = 0;
    this->MenuPageArray[MENUPAGE_PARENTAL_CONTROL].SelectActiveElementDefault = 0;
}
inline void Menu::NetworkServerMenuCreate() {

}
inline void Menu::NetworkClientMenuCreate() {

}








// Обработка событий и навигация
void Menu::SwitchPage(int pageIndex) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456D00 - Размер: 0x2A байт
}

void Menu::ActivateElement() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456D2A - Размер: 0xBC байт
}
void Menu::ActivateElement(int elementIndex) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456D2A - Размер: 0xBC байт
}

void Menu::HandleMenuEvent(int event) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456DE6 - Размер: 0x60B байт
}

void Menu::NavigatePages(int direction) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456DF0 - Размер: 0x66 байт
}

void Menu::GoBack() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456E56 - Размер: 0x66 байт
}


// Логика меню
void Menu::MainMenuLogic() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00457F00 - Размер: 0x35C байт
}

void Menu::PauseMenu() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458050 - Размер: 0x1A9 байт
}

void Menu::OptionsMenu() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004581F9 - Размер: 0x2CB байт
}

void Menu::PlayerList() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004584C4 - Размер: 0x16B байт
}

unsigned char Menu::MultiplayerMenu(PlayerSlotSlave* pPlayerName) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045862F - Размер: 0xDA байт
    return 0;
}

void Menu::ServerSettings() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458709 - Размер: 0x9C байт
}

// Настройки и конфигурация
void Menu::ApplyMoneyCheatIfApplicable() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458800 - Размер: 0x17B байт
}

void Menu::SetDifficulty(int difficulty) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045897B - Размер: 0x2C4 байт
}

void Menu::SelectCharacter(int characterIndex) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458C3F - Размер: 0x6E байт
}

void Menu::ConfigureControls(int config) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458CAD - Размер: 0x38 байт
}

void Menu::AudioOptions() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458CE5 - Размер: 0x28 байт
}

void Menu::VideoOptions() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458D0D - Размер: 0x44 байт
}

void Menu::ApplySettings() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458D51 - Размер: 0x53 байт
}

void Menu::ResetSettings() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458DA4 - Размер: 0x15F байт
}

// Специальные экраны
void Menu::Intro_BIK() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458F03 - Размер: 0x23 байт
}

void Menu::PreIntro() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458F26 - Размер: 0x42 байт
}

void Menu::SelectMission() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458F68 - Размер: 0x66 байт
}

void Menu::WorldMap() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00458FCE - Размер: 0xF9 байт
}

void Menu::ShowStatistics() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004590C7 - Размер: 0x66 байт
}

char Menu::ShowAwards(char arg0) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045912D - Размер: 0x139 байт
    return 0;
}

void Menu::Gallery() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00459266 - Размер: 0x2A байт
}

bool Menu::ShowCredits() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00459290 - Размер: 0x2A байт
    return true;
}

void Menu::ConfirmExit() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004592BA - Размер: 0x141 байт
}

// Проверки и условия
void Menu::CheckConditions() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004593FB - Размер: 0x4C+0x69+0x161 байт
}

void Menu::MenuShowJapanText() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00453D40 - Размер: 0x31 байт
}




// Читы и специальные функции
void Menu::PlayerCheat(wchar_t *PlayerName) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004590F0 - Размер: 0x44E байт
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
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
            }
        }
        if (this->isCheat) {
            switch (cash)
            {
            case GOREFEST:
                gDo_Blood = !gDo_Blood;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case BUCKFAST:
                gBunt = !gBunt;
                //gCheatIs=9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case VOLTFEST:
                gVoltfest = !gVoltfest;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case MADEMAN:
                gMademan = !gMademan;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case LASVEGAS:
                gLasvegas = !gLasvegas;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case NEKKID:
                gNEKKID = !gNEKKID;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case EATSOUP:
                gDoFreeShopping = !gDoFreeShopping;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case DAVEMOON:
                gDAVEMOON = !gDAVEMOON;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case CUTIE1:
                gHeats99 = !gHeats99;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case ARSESTAR:
                gKeepWeaponsAfterDeath = !gKeepWeaponsAfterDeath;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case GODOFGTA:
                gGetAllWeapons = !gGetAllWeapons;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case PSJABBER:
                gDoInvulnerable = !gDoInvulnerable;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case DANISGOD:
                gDANISGOD = !gDANISGOD;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case COCKTART:
                gExplodingOn = !gExplodingOn;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case FLAMEON:
                gFLAMEON = !gFLAMEON;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case FYOHZZ0:
                gFYOHZZ0 = !gFYOHZZ0;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case IAMDAVEJ:
                gIAMDAVEJ = !gIAMDAVEJ;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case SEGARULZ:
                gSEGARULZ = !gSEGARULZ;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case UKGAMER:
                gUKGAMER = !gUKGAMER;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case SUPZZZ0:
                gSUPZZZ0 = !gSUPZZZ0;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case TUMYFROG:
                gTUMYFROG = !gTUMYFROG;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                return;
            case SCHURULZ:
                gSCHURULZ = !gSCHURULZ;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                break;
            case HUNSRUS:
                gHUNSRUS = !gHUNSRUS;
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                break;
            case FISHFLAP:
                //gCheatIs = 9; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
                gFISHFLAP = !gFISHFLAP;
                break;

            default:
                break;
            }
        }
    }
}

void Menu::SpecialFunction1() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x004598C6 - Размер: 0xC1 байт
}

void Menu::SpecialFunction2() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00459987 - Размер: 0xF9 байт
}

void Menu::SpecialFunction3() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00459A80 - Размер: 0x61D байт
}

void Menu::SpecialFunction4() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045A09D - Размер: 0x1D6 байт
}

void Menu::SpecialFunction5() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045A273 - Размер: 0x231 байт
}


void Menu::SpecialFunction6() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045A4A4 - Размер: 0xB5 байт
    this->ProcessInput();
    this->NewGame();
    //gCheatIs = 0; // TODO: глобал gCheatIs пока не определён/не входит в линковку GTA2
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
    // Блок гаммы закомментирован: глобал gGamma пока не определён/не входит в линковку GTA2
    /*if (gGamma) {
        char pGamma = gRegistry.ConfigureSetScreen("gamma", 10);
        if (gGamma) {
            // Заменено на заглушку: реальная логика требует Port SetGamma
            //if (SetGamma(pGamma))
            //    --gGamma;
            //else
            //    gGamma=0;
        }
    }*/
}

void Menu::SpecialFunction7() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045A559 - Размер: 0x133 байт
}

// Основной метод меню
Menu::Menu() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00456F00 - Размер: 0x32E байт
}

Menu::~Menu() {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x00481C30 - Размер: 0xF0 байт
    this->ReleaseInputDevice();
    //if (gTextureManager){
    //gTextureManager.~TextureManager(); // TODO: глобал gTextureManager не входит в линковку GTA2, деструктор не реализован
    //}
}
void Menu::MenuDelete(byte status) {
    //TODO: Реализовать на основе ассемблерного кода
    // Адрес: 0x0045731E - Размер: 0x1E байт
    this->~Menu();
    if ((status & 1) != 0)
        free(this);
}

void Menu::StartGTAManager() {
    // Здесь будет запускаться Менаджер конфигурации
}