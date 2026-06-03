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
extern unsigned __int8 gPageFileMenu[];
int gbh_BlitImage(int, int, int, int, int, int, int);
void ShowTextDisplay(wchar_t*, char*, ...);
void wcsncpy(wchar_t*, wchar_t*, unsigned int);
void sub_41F990(int*, unsigned __int16);
void bitShiftLeft1(int*, int);
void DrawGTATextRawMain(wchar_t*, int, int, int, int);
void DrawGTATextRaw(wchar_t*, int, int, int, int);
unsigned __int16 sub_4566C0(wchar_t*, unsigned __int16, unsigned __int16, unsigned __int16, int, unsigned int, unsigned __int16, int);
void* gWindows;
int unk_67067C;
void* gDirectInput6;
int DeviceGuid;
LPCDIDATAFORMA pLPCDIDATAFORMAT;
void debug_log(unsigned int, const char*, int);
unsigned __int8 gAllGxtFile;
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
int gCheatIs;
int DMAudio::sub_410660(int*);
int gBool1;
int gAudioObject;
int* gCheatActive;
int unk_5EAF44;
int DMAudio::sub_410530(int*, int*);
int gImageTable;
int gbh_InitImageTable(int);
int DMAudio::sub_410540(int*, int);
int DMAudio::sub_410520(int*);
int gGamma;
bool SetGamma(int);
bool UpdateVideoFrame();
void MapGm::sub_45E610(int*, int);

int sub_4539D0(unsigned short, unsigned char);
int dword_662128;
int MenuEntry::UpdateToPreviousActive(void*);
bool MenuEntry::InitializeEntry(void*);

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
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x933 bytes
}

void Menu::CleanupResources() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xC5B bytes
}

void Menu::CloseBinkResources() {
    if ( gBinkBuffer.Status)
    {
        gBinkBuffer.Close();
        gBinkBuffer.Status = NULL;
        gBinkBufferOffset = 0;
    }
    if ( gBink.Status )
    {
        gBink.GetSummary(gBinkSummary);
        gBink.Close();
        gBink.Status = NULL;
    }
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

int  Menu::UpdateMenuFrame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF9 bytes


    PlayerSlotSlave* pPlayerProfileName = this->getPlayerProfileName();
    byte pPlayerSlotSave = gMapGm.GetPlayerSlotSave();
    MenuPage* MenuPageArray = &this->MenuPageArray[this->PageNumber];
    unsigned char pLastActiveArenaSlot = this->FindLastActiveArenaSlot(pPlayerProfileName);
    unsigned char pBonusStage = this->MultiplayerMenu(pPlayerProfileName);
    unsigned char pArenaSlot = this->SelectPlayerSlotArray[pPlayerSlotSave];
    Menu *pMenu;
    ///Menu v6= this->aaa[pPlayerSlotSave];

    if (pLastActiveArenaSlot >= pArenaSlot) {
        gMapGm.SetPlayerArena(pArenaSlot);
    }
    else {
        pMenu->PlayerSlotSave[0].ActiveArenaSlot = pLastActiveArenaSlot;
        gMapGm.SetPlayerArena(pLastActiveArenaSlot);

    }
    unsigned char pBonusStage1 = pMenu->BonusStage[0];
    if (pBonusStage < pBonusStage1 || pBonusStage == 255) {
        pBonusStage1 = pBonusStage;
        pMenu->BonusStage[0] = pBonusStage;
    }
    gMapGm.SetBonusStage(pBonusStage1);
    this->ConfirmExit();
    this->ActivateElement();
    int result;
    if (this->GetSaveFile(pPlayerSlotSave)) {
        MenuPageArray->MenuEntryArray[EntryOptions].Flag[1] = 1;
        MenuPageArray->MenuItemArray[MENUPAGE_PLAY].IndexMenuActions = 1;
        result = 1;
    }
    else {
        MenuPageArray->MenuEntryArray[EntryOptions].Flag[1] = 0;
        MenuPageArray->MenuItemArray[MENUPAGE_PLAY].IndexMenuActions = 0;
        result = 0;
    }
    return result;

    
}

void Menu::RenderMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x18B bytes
}

// Ввод
void Menu::InitDevice() {
    LPDIRECTINPUTDEVICEA pDirectInput6;
    LPDIRECTINPUTDEVICEA *p_InputDevice;

    pDirectInput6 = gDirectInput6;
    p_InputDevice = &this->InputDevice;
    this->DirectInput = gDirectInput6;
    this->InputDevice = 0;
    if ( pDirectInput6->CreateDevice(
             pDirectInput6,
             &DeviceGuid,
             &this->InputDevice,
             0) < 0 )
        debug_log(0x1Fu, "frontend2.cpp", 2229);
    if ( *p_InputDevice->lpVtbl->SetDataFormat(
             *p_InputDevice,
             &pLPCDIDATAFORMAT) < 0 )
        debug_log(9u, "frontend2.cpp", 2240);
    if ( *p_InputDevice->SetCooperativeLevel(
             *p_InputDevice,
             gWindows,
             6) < 0 )
        debug_log(0xAu, "frontend2.cpp", 2247);
    if ( (!this->InputDevice)
        || (this->InputDevice->Acquire(this->InputDevice) < 0 )){
        this->KeyboardAcquired = 1;
    }
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

char Menu::ReadDeviceState() {
    char *Keys; // edi
    int v3; // eax

    Keys = this->Keys;
    v3 = this->InputDevice->GetDeviceState(this->InputDevice, 256, this->Keys);
    if ( v3 >= 0 )
        return 1;
    if ( (v3 == -2147024866 || v3 == -2147024884) && this->InputDevice->Acquire(this->InputDevice) >= 0 )
        this->InputDevice->GetDeviceState(this->InputDevice, 256, Keys);
    return 0;
}

void Menu::ProcessInput() {
    unsigned char v2; // cl
    bool v3; // zf
    unsigned char v4; // al
    unsigned char v5; // cl
    unsigned char KeyOldLeft; // al
    unsigned char KeyNewLeft; // cl
    unsigned char KeyOldRight; // al
    unsigned char v9; // cl
    unsigned char v10; // al
    unsigned char v11; // cl
    unsigned char v12; // al
    unsigned char v13; // cl
    unsigned char v14; // al

    if ( this->FrontendKeysEnabled && this->ReadDeviceState() )
    {
        v2 = this->Keys[200] < 0 && !this->OldKeyState.up;
        this->OldKeyState.up = this->Keys[200] & 128;
        v4 = this->Keys[208] & 0x80;
        v3 = this->Keys[208] >= 0;
        this->NewKeyState.up = v2;
        v5 = !v3 && !this->OldKeyState.down;
        this->OldKeyState.down = v4;
        KeyOldLeft = this->Keys[203] & 128;
        this->NewKeyState.down = v5;
        KeyNewLeft = KeyOldLeft && !this->OldKeyState.left;
        this->OldKeyState.left = KeyOldLeft;
        KeyOldRight = this->Keys[205] & 128;
        this->NewKeyState.left = KeyNewLeft;
        v9 = KeyOldRight && !this->OldKeyState.Right;
        this->OldKeyState.Right = KeyOldRight;
        v10 = this->Keys[28] & 0x80;
        v3 = this->Keys[28] >= 0;
        this->NewKeyState.Right = v9;
        v11 = !v3 && !this->OldKeyState.enter;
        this->OldKeyState.enter = v10;
        v12 = this->Keys[1] & 0x80;
        v3 = this->Keys[1] >= 0;
        this->NewKeyState.enter = v11;
        v13 = !v3 && !this->OldKeyState.esc;
        this->OldKeyState.esc = v12;
        v14 = this->Keys[211] & 0x80;
        v3 = this->Keys[211] >= 0;
        this->NewKeyState.esc = v13;
        if ( v3 || this->OldKeyState.del )
        {
            this->OldKeyState.del = v14;
            this->NewKeyState.del = 0;
        }
        else
        {
            this->OldKeyState.del = v14;
            this->NewKeyState.del = 1;
        }
    }
    else
    {
        this->NewKeyState.up = 0;
        this->NewKeyState.down = 0;
        this->NewKeyState.left = 0;
        this->NewKeyState.Right = 0;
        this->NewKeyState.enter = 0;
        this->NewKeyState.esc = 0;
        this->NewKeyState.del = 0;
    }
}

bool Menu::HandleKeyPress() {
    unsigned char a2; // [esp+8h] [ebp-4h]

    a2 = gMapGm.GetPlayerArena();
    return this->DrawMenuElements(a2) != a2;
}

bool Menu::SwitchPage() {
    unsigned char PlayerArena; // [esp+8h] [ebp-4h]

    PlayerArena = gMapGm.GetPlayerArena();
    return this->UpdateGUI(PlayerArena) != PlayerArena;
}

void Menu::SetFrontendKeysEnabled(bool enabled) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0xF bytes
    this->FrontendKeysEnabled = enabled;
}

// Работа с игроком
void Menu::SetPlayerName() {
    wcsncpy(
        this->PlayerName,
        gPlayerData.PlayerSlotSave[this->MenuPageArray[1].MenuEntryArray[0].PlayerSlot].PlayerName,
        9);
}


void Menu::SetPlayerNameFromMenu() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x4F bytes
    unsigned short PlayerSlot = this->MenuPageArray[MENUPAGE_PLAY].MenuEntryArray[EntryPlay].PlayerSlot;
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

unsigned short Menu::SelectPlayerSlot() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x10C bytes
    timeGetTime();
    this->ProcessInput();
    int v2 = 0;
    unsigned char* _index = this->Keys;

}

unsigned char Menu::FindLastActiveArenaSlot(PlayerSlotSlave *PlayName) {
    unsigned char result; // al

    for ( result = this->CountArena - 1; !PlayName->ArenaSlots[result].SubSlot[0].BonusStage[0][0]; --result )
    {
        if ( !result )
            break;
    }
    return result;
}

// Сохранение/загрузка
void Menu::SaveGame() {
    // TODO: implement from dump
}

void Menu::LoadGame() {
    unsigned __int8 v2 = 0;
    unsigned __int8 SlotSave = 0;
    MenuDataBlock *pMenuDataBlock = this->MenuDataBlock;
    do
    {
        char result = this->GetSaveFile(SlotSave);
        if ( result )
        {
            char FileName[280];
            this->GettingSaveFile(SlotSave, FileName);
            result = MenuDataBlock::Load(pMenuDataBlock, FileName);
        }
        else
        {
            pMenuDataBlock->field_0 = 0;
            pMenuDataBlock->field_1 = 3;
            pMenuDataBlock->field_2 = 4;
            pMenuDataBlock->field_3 = 0;
        }
        ++v2;
        ++pMenuDataBlock;
        SlotSave = v2;
    }
    while ( v2 < 8u );
    return 0;
}




int Menu::NewGame() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x169 bytes
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
                    pState = gMapGm.GetPlayerArena() + 7;
                    this->MenuPicture = pState;
                    break;
                case MenyPlayBonus:
                    pBonusStage = gMapGm.GetBonusStage();
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

char Menu::GettingSaveFile(byte Index, char * FileNameSave) {

    char Buffer[8];

    _itoa(Index, Buffer, 10);
    strcpy(FileNameSave, "player\\plyslot");
    strcat(FileNameSave, Buffer);
    strcat(FileNameSave, ".svg");
    return 0;
}

char Menu::GetSaveFile(unsigned char SlotSave) {
    void *v2; // eax
    FILETIME FileNameSave[32];
    CHAR v5[280];

    this->GettingSaveFile(SlotSave, (char *)FileNameSave);
    v2 = (void *)sub_4D75CC(FileNameSave, v5, (DWORD)FileNameSave[0].dwLowDateTime);
    if ( v2 == (void *)-1 )
        return 0;
    sub_4D7549(v2);
    return 1;
}

void Menu::SaveSettings() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x6A bytes
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

void* Menu::LoadTexture(unsigned short ID) {
    gFileMgr.SetFilePath(gPageFileMenu[ID].NameFiles);
    FILE *v3 = gFileMgr.WriteReadFile(gPageFileMenu[ID].NameFiles, "rb");
    if ( !v3 )
        debug_log(0x10u, "frontend2.cpp", 6230);
    void *v4 = malloc(gPageFileMenu[ID].SizeFile);
    if ( !v4 )
        debug_log(0xAEu, "frontend2.cpp", 6237);
    if ( _fread(v4, 1u, gPageFileMenu[ID].SizeFile, v3) != gPageFileMenu[ID].SizeFile )
        debug_log(0xBBu, "frontend2.cpp", 6243);
    gPageFileMenu[ID].gbh_LoadImage = (void *)gbh_LoadImage[0]();
    fclose(v3);
    free_0(v4);
    return 0;
}

void Menu::LoadTexturesFromTable(void* table) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x3A bytes
    this->pTextureTable = table;
}





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
    default:
        break;
    }
}

void Menu::DrawMenuBackground() {
    unsigned __int8 pMenuPic;
    unsigned __int8 v3;
    int v5;
    unsigned __int8 pPicMenuFilesLeft;
    unsigned __int8 v8;
    unsigned __int8 PicMenuFilesLeft;
    unsigned __int8 PicMenuFilesRight[4];

    pMenuPic = this->MenuPic;
    if ( pMenuPic == RIP
        || pMenuPic == ResumSave
        || pMenuPic == MenuPic_14
        || pMenuPic == MenuPic_15
        || pMenuPic == HighScores
        || pMenuPic == Title )
    {
        this->FindBackground( pMenuPic, &PicMenuFilesLeft, PicMenuFilesRight);
        pPicMenuFilesLeft = PicMenuFilesLeft;
        if ( gbh_BlitImage(gPageFileMenu[PicMenuFilesLeft], 0, 0, 640, 480, 0, 0) == -10 )
        {
            this->LoadTexture(pPicMenuFilesLeft);
            gbh_BlitImage(gPageFileMenu[pPicMenuFilesLeft], 0, 0, 640, 480, 0, 0);
        }
    }
    else
    {
        this->FindBackground( pMenuPic, &PicMenuFilesLeft, PicMenuFilesRight);
        v3 = PicMenuFilesLeft;
        v5 = gbh_BlitImage(gPageFileMenu[PicMenuFilesLeft], 0, 0, 278, 480, 0, 0);
        if ( v5 == -10 )
        {
            this->LoadTexture(v3);
            v5 = gbh_BlitImage(gPageFileMenu[v3], 0, 0, 278, 480, 0, 0);
        }
        if ( !v5 && gbh_BlitImage(gPageFileMenu[v8], 0, 0, 362, 480, 278, 0) == -10 )
        {
            this->LoadTexture(v8);
            gbh_BlitImage(gPageFileMenu[v8], 0, 0, 362, 480, 278, 0);
        }
    }
}

unsigned __int8 Menu::DrawMenuElements(unsigned __int8 a2) {
    // Adapted from dump: unsigned __int8 Menu::DrawMenuElements(Menu *this, unsigned __int8 a2)
    unsigned __int8 v2;
    unsigned __int8 v3;
    unsigned __int8 v4;

    v2 = gMapGm.GetPlayerArena();
    v3 = a2;
    while ( v3 == a2 )
    {
        this->ProcessInput();
        v4 = this->SelectPlayerSlot();
        gMapGm.SetPlayerArena(v4);
        a2 = v4;
    }
    return v3;
}

unsigned __int8 Menu::UpdateGUI(unsigned __int8 PlayerArena) {
    // Adapted from dump: unsigned __int8 Menu::UpdateGUI(Menu *this, unsigned __int8 PlayerArena)
    unsigned __int8 v2;
    unsigned __int8 v3;

    v2 = PlayerArena;
    do
    {
        this->MainMenuLogic();
        v3 = this->HandleKeyPress();
    }
    while ( v3 == PlayerArena );
    return v2;
}

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
    unsigned __int8 PlayerArena;

    PlayerArena = gMapGm.GetPlayerArena();
    this->UpdateGUI(PlayerArena);
}

void Menu::ActivateElement() {
    MenuPage *v2;
    unsigned __int8 PlayerArena;

    v2 = &this->MenuPageArray[this->PageNumber];
    PlayerArena = gMapGm.GetPlayerArena();
    ShowTextDisplay(&TextWcharT, (char *)off_56E788, PlayerArena + 1);
    wcsncpy(v2->GUIArray[2].Sprite, &TextWcharT, 50u);
    if ( this->HandleKeyPress() )
    {
        v2->GUIArray[4].PlayerArena = 1;
        this->field_1EB38 = 1;
    }
    else
    {
        v2->GUIArray[4].PlayerArena = 0;
        this->field_1EB38 = 0;
    }
    if ( this->SwitchPage(this->PageNumber) )
    {
        v2->GUIArray[5].PlayerArena = 1;
        this->field_1EB39 = 1;
    }
    else
    {
        v2->GUIArray[5].PlayerArena = 0;
        this->field_1EB39 = 0;
    }
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
    unsigned __int8 v3;
    char BonusStage;

    v3 = gMapGm.GetBonusStage();
    this->WorldMap();
    gMapGm.SetBonusStage(v3);
    this->BonusStage[gMapGm.GetPlayerSlotSave()] = v3;
    this->ConfirmExit();
}

void Menu::GoBack() {
    unsigned __int8 BonusStage;
    char arg0;

    BonusStage = gMapGm.GetBonusStage();
    arg0 = this->ShowAwards(BonusStage);
    gMapGm.SetBonusStage(arg0);
    this->BonusStage[gMapGm.GetPlayerSlotSave()] = arg0;
    this->ConfirmExit();
}


// Логика меню
void Menu::MainMenuLogic() {
    char v26[24];
    char v28[24];
    char v15[8];
    char v17[7];
    int v18;
    char v19[12], v20[12], v21[12], v22[12], v23[12], v24[12];
    char v25;
    int v14;
    char v13 = 0;
    unsigned __int16 v16;
    FileSave v27;

    void *v3 = (void *)sub_4D75CC(&gFileTimes, (LPCSTR)&v27, 0);
    void *v4 = v3;
    if ( v3 == (void *)-1 )
        debug_log(0x98u, "frontend2.cpp", 4614);
    else
    {
        strcpy(v26, "data\\");
        unsigned int v5 = strlen(v28) + 1;
        char *v6 = &v25;
        while ( *++v6 )
            ;
        memcpy(v6, v28, v5);
        sub_4D7549(v4);
    }
    this->CountArena = 0;
    *(short *)this->AAA = 0;
    v13 = 0;
    this->field_1EB3F = 0;
    v14 = 0;
    FILE *v8 = gFileMgr.WriteReadFile(v26, "rt");
    if ( !v8 )
    {
        debug_log(0x9Au, "frontend2.cpp", 4644);
        return;
    }
    this->LoadPlayerProfile(0);
    while ( strcmp(v15, gSource) )
    {
        if ( !strcmp(v15, "MAIN") )
        {
            if ( v13 )
            {
                if ( (unsigned __int16)++v14 > 2u )
                    debug_log(0x9Bu, "frontend2.cpp", 4660);
            }
            unsigned char *v10 = &this->AAA[v16];
            v15[7] = 1;
            *v10 = 0;
            this->LoadPlayerProfile(0);
            this->LoadPlayerProfile(0);
            this->LoadPlayerProfile(0);
            this->LoadPlayerProfile(0);
            ++*v10;
        }
        else if ( !strcmp(v15, "BONUS") )
        {
            if ( !v13 )
                debug_log(0x9Cu, "frontend2.cpp", 4678);
            unsigned char *v11 = &this->AAA[v16];
            if ( *v11 > 3u )
                debug_log(0x9Du, "frontend2.cpp", 4683);
            this->LoadPlayerProfile(0);
            this->LoadPlayerProfile(0);
            this->LoadPlayerProfile(0);
            this->LoadPlayerProfile(0);
            ++*v11;
        }
        else
            debug_log(0x9Eu, "frontend2.cpp", 4697);
        this->LoadPlayerProfile(0);
    }
    this->CountArena = v16 + 1;
    fclose(v8);
}

void Menu::PauseMenu() {
    char Source[256];
    char a4[256], a5[256], a6[256];

    this->CheckSaveFile(0);
    gMapGm.SetSaveFile(gSource);
    strcpy(Source, "data\\");
    unsigned int v3 = strlen(a4) + 1;
    char *v4 = &Source[strlen(Source)];
    memcpy(v4, a4, v3);
    gMapGm.SetMapName(Source);
    strcpy(Source, "data\\");
    unsigned int v6 = strlen(a5) + 1;
    char *v7 = &Source[strlen(Source)];
    memcpy(v7, a5, v6);
    gMapGm.SetStyleName(Source);
    strcpy(Source, "data\\");
    unsigned int v9 = strlen(a6) + 1;
    char *v10 = &Source[strlen(Source)];
    memcpy(v10, a6, v9);
    gMapGm.SetScriptName(Source);

    unsigned __int8 PlayerArena = gMapGm.GetPlayerArena();
    gMapGm.SetPlayerArena(PlayerArena);
    gMapGm.SetGang(0);
}

void Menu::OptionsMenu() {
    byte PlayerSlotSave = gMapGm.GetPlayerSlotSave();
    char v28[36];
    this->GettingSaveFile(PlayerSlotSave, v28);
    gFileMgr.FileOpen(0, v28);
    SIZE_T v17 = 82;
    char v24[2], v25[7];
    FILE v19[5];
    gFileMgr.Read(v19, &v17);
    gFileMgr.CloseFile(0);
    char v18[12];
    v18[0] = v24[1];
    v18[4] = v25[1];
    v18[8] = v25[0];
    unsigned __int8 pPlayerArea;
    unsigned __int8 v17_byte;
    if ( v25[1] )
    {
        gMapGm.DecodeBonusStage(v25[0], (int*)&pPlayerArea, &v17_byte);
    }
    else
        v17_byte = 0;
    char PlayerArea = v18[0];
    char ScripName[36];
    strcpy(ScripName, "data\\");
    const char *v6 = (const char *)this + 0xC00 * v18[0] + 0x300 * (unsigned __int8)v17_byte;
    unsigned int v7 = strlen(v6 + 0xC9D4) + 1;
    char *v8 = &ScripName[strlen(ScripName)];
    memcpy(v8, v6 + 0xC9D4, v7);
    if ( strcmp((const char *)v19, ScripName) )
        debug_log(0xA6u, "frontend2.cpp", 4992);
    strcpy(&ScripName[12], "data\\");
    unsigned int v10 = strlen(v6 + 51924) + 1;
    char *v11 = &ScripName[11 + strlen(&ScripName[12])];
    memcpy(v11, v6 + 51924, v10);
    strcpy(&ScripName[24], "data\\");
    unsigned int v13 = strlen(v6 + 52180) + 1;
    char *v14 = &ScripName[23 + strlen(&ScripName[24])];
    memcpy(v14, v6 + 52180, v13);
    gMapGm.SetMapName(ScripName);
    gMapGm.SetPlayerArena(PlayerArea);
    gMapGm.SetGang(0);
}

void Menu::PlayerList() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x16B bytes
}

unsigned char Menu::MultiplayerMenu(PlayerSlotSlave* pPlayerName) {
    unsigned __int8 LastActiveArenaSlot;
    int ActiveArenaSlot;
    byte v5;
    unsigned __int8 v6;
    unsigned __int8 v7;
    bool v8;
    int v9;
    unsigned __int8 PlayerArena;

    LastActiveArenaSlot = this->FindLastActiveArenaSlot(pPlayerName);
    PlayerArena = LastActiveArenaSlot;
    ActiveArenaSlot = LastActiveArenaSlot;
    v5 = this->AAA[LastActiveArenaSlot];
    while ( 2 )
    {
        v6 = v5 - 1;
        v7 = v6;
LABEL_3:
        v8 = v6 == 0;
        while ( !v8 )
        {
            v9 = ActiveArenaSlot;
            if ( !pPlayerName->ArenaSlots[ActiveArenaSlot].SubSlot[v7].BonusStage[0][0] )
            {
                do
                {
                    if ( !v6 )
                        break;
                    v7 = --v6;
                }
                while ( !pPlayerName->ArenaSlots[v9].SubSlot[v6].BonusStage[0][0] );
            }
            if ( pPlayerName->ArenaSlots[v9].SubSlot[v7].BonusStage[0][0] != 1 )
                goto LABEL_3;
            v8 = v6 == 0;
            if ( v6 )
                return gMapGm.sub_453A40(PlayerArena, v7);
        }
        if ( LastActiveArenaSlot )
        {
            PlayerArena = --LastActiveArenaSlot;
            ActiveArenaSlot = LastActiveArenaSlot;
            v5 = this->AAA[LastActiveArenaSlot];
            continue;
        }
        return -1;
    }
}

void Menu::ServerSettings() {
    int v2;
    unsigned __int16 v3;
    wchar_t *v4;
    int v5;
    int v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int v11;
    unsigned __int16 a4[2];
    HudBrief *pHudBrief;

    a4[0] = word_67066C[0];
    v2 = *(int *)a4;
    gFont.GetCharHeight(word_67066C[0]);
    v3 = gMapGm.sub_45E600();
    char a1[12];
    _itoa(v3, a1, 10);
    if ( v3 )
    {
        v4 =(wchar_t*) gText.Bsearch(a1);
        pHudBrief->sub_4C2450((wchar_t *)&pHudBrief, (int)v4, 560);
        v11 = v5;
        bitShiftLeft1(&v11, 1);
        v10 = v2;
        v9 = v6;
        sub_41F990(&v9, 270u);
        v8 = v7;
        sub_41F990(&v8, 40u);
        DrawGTATextRawMain((wchar_t *)&pHudBrief, v8, v9, v10, v11);
    }
}

// Настройки и конфигурация
void Menu::ApplyMoneyCheatIfApplicable() {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x17B bytes
}

void Menu::SetDifficulty(int difficulty) {
    unsigned __int16 index_1;
    Menu *pMenu;
    Car *Player;
    int v4;
    int v5;
    MenuItemConfig *pMenuItemConfig;
    int v7;
    void *v8;
    int v9;
    void *v10;
    int v11;
    int v12;
    Car *v13;
    PublicTransport *v14;
    int v15;
    BOOL v16;
    int result;
    int v18;
    Car *v19;
    Car *v20;
    int v21;
    int *v22;
    int *v23;
    int v24;
    int v25;
    int v26;
    unsigned __int16 a4[2];
    int v28;
    Car *pCar;
    int index;
    Menu *v31;
    int v32;
    int v33;
    int v34;
    int v35;

    pMenu = this;
    v26 = 480;
    index_1 = this->Index;
    Player = (Car *)this->Player;
    v31 = this;
    index = *(int *)&index_1;
    pCar = Player;
    LOWORD(v4) = bitShiftLeft1(&v33, 480);
    v26 = v4;
    if ( sub_4037E0(&pCar) )
    {
        v5 = v33;
        while ( index_1 < 600u )
        {
            pMenuItemConfig = &pMenu->MenuSlotConfig.MenuItemConfig[index_1];
            switch ( pMenuItemConfig->Selecet )
            {
                case 0:
                    v28 = 2;
                    a4[0] = word_67066C[0];
                    v5 = 0;
                    break;
                case 1:
                    v28 = 2;
                    a4[0] = unk_67064C;
                    v5 = 0;
                    break;
                case 2:
                    v28 = 8;
                    a4[0] = unk_67064C;
                    v5 = 13;
                    break;
                case 3:
                    v28 = 8;
                    a4[0] = unk_67064C;
                    v5 = 14;
                    break;
                case 4:
                    v28 = 8;
                    a4[0] = unk_67064C;
                    v5 = 15;
                    break;
                default:
                    debug_log(0xBCu, "frontend2.cpp", 7680);
                    break;
            }
            if ( wcscmp(pMenuItemConfig->str, gText_Menu) )
            {
                if ( !wcscmp(pMenuItemConfig->str, L"BINKLOGO") )
                {
                    LOWORD(v7) = unk_5EB320;
                    v26 = 0;
                    v25 = 0;
                    v24 = 0;
                    v23 = 0;
                    v32 = 2;
                    v22 = &v32;
                    v21 = unk_5EB1E8;
                    v20 = (Car *)v7;
                    v19 = Player;
                    v18 = unk_5EB1E8;
                    sub_41F990(&v18, 0x140u);
                    sub_4CBA50(v8, 6, 1, v18, v19);
                }
                else if ( !wcscmp(pMenuItemConfig->str, L"MILESLOGO") )
                {
                    LOWORD(v9) = unk_5EB320;
                    v26 = 0;
                    v25 = 0;
                    v24 = 0;
                    v23 = 0;
                    v32 = 2;
                    v22 = &v32;
                    v21 = unk_5EB1E8;
                    v20 = (Car *)v9;
                    v19 = Player;
                    v18 = unk_5EB1E8;
                    sub_41F990(&v18, 320u);
                    sub_4CBA50(v10, 6, 25, v18, v19);
                }
                else
                {
                    LOWORD(v11) = Font::GetStringWidth(pMenuItemConfig->str, a4[0]);
                    v26 = 0;
                    v25 = 0;
                    v24 = v5;
                    v12 = 640 - v11;
                    v23 = &v28;
                    v22 = (int *)(640 - v11);
                    bitShiftLeft1(&v22, 1);
                    v21 = *(int *)a4;
                    v20 = Player;
                    v19 = v13;
                    sub_41F990(&v19, v12 / 2);
                    DrawGTATextRaw(pMenuItemConfig->str, (int)v19, (int)v20, v21, (int)v22);
                }
            }
            sub_41F990(&v34, v31->MenuSlotConfig.MenuItemConfig[(unsigned __int16)++index].field_4);
            Player = (Car *)S202::sub_401B20((S202 *)&pCar, (SpriteS1 *)&v35, v14)->FirstElement;
            pCar = Player;
            LOWORD(v15) = bitShiftLeft1(&v33, 480);
            v26 = v15;
            v16 = sub_4037E0(&pCar);
            pMenu = v31;
            if ( !v16 )
                break;
            index_1 = index;
        }
    }
    result = gbh_BlitImage(g_gbh_BlitImage, 0, 0, 451, 144, 85, 0);
    if ( result == -10 )
    {
        this->LoadTexture(23u);
        gbh_BlitImage(g_gbh_BlitImage, 0, 0, 451, 144, 85, 0);
    }
}

void Menu::SelectCharacter(int characterIndex) {
    PlayerSlotSlave *PlayerProfileName;
    unsigned __int16 v3;
    unsigned __int16 v4;

    PlayerProfileName = this->getPlayerProfileName();
    v3 = 0;
    if ( !this->CountArena )
        return;
    while ( 1 )
    {
        v4 = 0;
        if ( this->AAA[v3] )
            break;
LABEL_5:
        if ( ++v3 >= this->CountArena )
            return;
    }
    while ( PlayerProfileName->ArenaSlots[v3].SubSlot[v4].BonusStage[0][0] )
    {
        if ( ++v4 >= this->AAA[v3] )
            goto LABEL_5;
    }
}

void Menu::ConfigureControls(int config) {
    // TODO: Реализовать на основе ассемблерного кода
    // Адрес: TBD, Размер: 0x38 bytes
    this->ControlConfig = config;
}

void Menu::AudioOptions() {
    if ( !skip_audio )
    {
        if ( gSampleRate )
        {
            DMAudio::sub_410540(&gDMAudio, gSampleRate);
            gSampleRate = 0;
        }
    }
}

void Menu::VideoOptions() {
    if ( !skip_audio )
    {
        gCheatIs = 0;
        gBool1 = 0;
        gAudioObject = 2;
        gCheatActive = &gCheatIs;
        unk_5EAF44 = 0;
        gSampleRate = DMAudio::sub_410530(&gDMAudio, &gAudioObject);
    }
}

void Menu::ApplySettings() {
    WindowsClientCreate();
    gbh_BeginScene();
    this->DrawMenuBackground();
    this->CheckConditions();
    gbh_EndScene();
    FreeSurface();
    gMovie.Vid_FlipBuffers();
    gMovie.Vid_ClearScreen(0, 0, 0, 0, 0, gMovie.WindowWidth, gMovie.WindowHeight);
}

void Menu::ResetSettings() {
    if ( this->NewKeyState.enter )
    {
        short v2 = this->field_EDF6;
        if ( v2 == 210 )
        {
            if ( this->field_EDF8 != 1 )
            {
                debug_log(0x3EEu, "frontend2.cpp", 1750);
                gCheatIs = 5;
            }
            else
            {
                // InitializeState_0 - unknown
                this->State = 1;
                gCheatIs = 5;
            }
        }
        else if ( v2 != 230 )
        {
            gCheatIs = 5;
        }
        else
        {
            this->State = 1;
            gCheatIs = 5;
        }
    }
    if ( this->NewKeyState.esc )
    {
        this->State = 1;
        gCheatIs = 6;
    }
    if ( this->NewKeyState.up )
    {
        if ( this->field_EDF6 == 190 || this->field_EDF6 == 210 )
            this->field_EDF6 = 230;
        else if ( this->field_EDF6 == 230 )
            this->field_EDF6 = 210;
        else
            debug_log(0x3EEu, "frontend2.cpp", 1784);
        gCheatIs = 1;
    }
    if ( this->NewKeyState.down )
    {
        if ( this->field_EDF6 != 190 )
        {
            if ( this->field_EDF6 == 210 )
            {
                this->field_EDF6 = 230;
                gCheatIs = 2;
            }
            else if ( this->field_EDF6 != 230 )
            {
                debug_log(0x3EEu, "frontend2.cpp", 1807);
                gCheatIs = 2;
            }
        }
        this->field_EDF6 = 210;
        gCheatIs = 2;
    }
    this->field_118 = this->field_118 - 1;
    if ( this->field_118 <= 0 )
    {
        this->field_114 = this->field_114 == 0;
        this->field_118 = 2;
    }
}

// Специальные экраны
void Menu::Intro_BIK() {
    DMAudio::sub_410660(&gDMAudio);
    int v1 = 0;
    do
    {
        char v2 = gDataMoviePrein[v1];
        byte_5EAF60[v1++] = v2;
    }
    while ( byte_5EAF60[v1 - 1] );
}

void Menu::PreIntro() {
    DMAudio::sub_410660(&gDMAudio);
    int Long = strlen("data\\movie\\preintro.bik") + 1;
    char *v2 = &unk_5EB060[strlen(unk_5EB060)];
    memcpy(v2, "data\\movie\\preintro.bik", 4 * (Long >> 2));
    char *v4 = &aDataMoviePrein[4 * (Long >> 2)];
    char *v3 = &v2[4 * (Long >> 2)];
    char v5 = Long;
    memcpy(v3, v4, v5 & 3);
}

void Menu::SelectMission() {
    unsigned __int8 PlayerArena;
    char a2;

    PlayerArena = gMapGm.GetPlayerArena();
    a2 = this->DrawMenuElements(PlayerArena);
    gMapGm.SetPlayerArena(a2);
    this->PlayerSlotSave[gMapGm.GetPlayerSlotSave()] = a2;
    this->ActivateElement();
}

void Menu::WorldMap() {
    unsigned __int8 v3;
    unsigned __int8 v4;
    unsigned __int8 v5;
    unsigned __int8 v8;
    unsigned __int8 PlayerArena[4];
    unsigned __int8 a3[4];
    PlayerSlotSave *PlayerProfileName;
    unsigned __int8 BonusStagea;

    unsigned __int8 BonusStage = gMapGm.GetBonusStage();
    PlayerProfileName = this->getPlayerProfileName();
    gMapGm.DecodeBonusStage(BonusStage, PlayerArena, (unsigned __int8 *)a3);
    v3 = PlayerArena[0];
    v4 = a3[0];
    v5 = PlayerArena[0];
    v8 = a3[0];
    BonusStagea = 1;
    while ( !PlayerProfileName->ArenaSlots[PlayerArena[0]].SubSlot[a3[0]].BonusStage[0][0] || BonusStagea )
    {
        BonusStagea = 0;
        if ( v4 == 1 )
        {
            while ( !v3 )
            {
                if ( unk_5EAF58 )
                {
                    v3 = this->CountArena - 1;
                    PlayerArena[0] = v3;
                    v4 = this->AAA[v3] - 1;
                }
                else
                {
                    v4 = v8;
                    v3 = v5;
                    PlayerArena[0] = v5;
                }
                a3[0] = v4;
                if ( v4 )
                    continue;
                break;
            }
            if ( v3 )
            {
                PlayerArena[0] = --v3;
                v4 = this->AAA[v3] - 1;
            }
        }
        else
        {
            --a3[0];
            v4 = a3[0];
        }
    }
}

void Menu::ShowStatistics() {
    unsigned __int8 v3;
    char PlayerArena;

    v3 = gMapGm.GetPlayerArena();
    PlayerArena = this->UpdateGUI(v3);
    gMapGm.SetPlayerArena(PlayerArena);
    this->PlayerSlotSave[gMapGm.GetPlayerSlotSave()] = PlayerArena;
    this->ActivateElement();
}

char Menu::ShowAwards(char arg0) {
    unsigned __int8 v3;
    int v4;
    int i;
    char v7;
    unsigned __int8 v8;
    int a2;
    unsigned __int8 a3[4];
    PlayerSlotSave *PlayerProfileName;
    unsigned __int8 arg0a;

    PlayerProfileName = this->getPlayerProfileName();
    gMapGm.DecodeBonusStage((unsigned __int8)arg0, &a2, (unsigned __int8 *)a3);
    v3 = a2;
    v7 = a2;
    v8 = a3[0];
    for ( arg0a = 1; !PlayerProfileName->ArenaSlots[v3].SubSlot[a3[0]].BonusStage[0][0] || arg0a; arg0a = 0 )
    {
        if ( a3[0] == this->AAA[v3] - 1 )
        {
            v4 = this->CountArena - 1;
            a3[0] = 1;
            if ( v3 == v4 )
            {
                if ( unk_5EAF58 )
                {
                    a2 = 0;
                }
                else
                {
                    a2 = v7;
                    a3[0] = v8;
                }
            }
            else
            {
                a2 = a2 + 1;
            }
            v3 = a2;
            for ( i = (unsigned __int8)a2; this->AAA[(unsigned __int8)a2] == 1; i = (unsigned __int8)a2 )
            {
                if ( i == v4 )
                {
                    if ( unk_5EAF58 )
                    {
                        a2 = 0;
                    }
                    else
                    {
                        a2 = v7;
                        a3[0] = v8;
                    }
                }
                else
                {
                    a2 = a2 + 1;
                }
                v3 = a2;
            }
        }
        else
        {
            ++a3[0];
        }
    }
    return gMapGm.sub_453A40(v3, a3[0]);
}

void Menu::Gallery() {
    unsigned __int8 BonusStage;

    BonusStage = gMapGm.GetBonusStage();
    this->WorldMap();
}

bool Menu::ShowCredits() {
    unsigned __int8 arg0;

    arg0 = gMapGm.GetBonusStage();
    return (unsigned __int8)this->ShowAwards(arg0) != arg0;
}

void Menu::ConfirmExit() {
    MenuPage *pMenuPage;
    unsigned __int8 BonusStage;
    unsigned __int8 PlayerArena[4];
    unsigned __int8 a4[4];

    pMenuPage = &this->MenuPageArray[this->PageNumber];
    BonusStage = gMapGm.GetBonusStage();
    PlayerArena[0] = BonusStage;
    gMapGm.DecodeBonusStage(BonusStage, PlayerArena, (unsigned __int8 *)a4);
    if ( BonusStage == 0xFF )
    {
        pMenuPage->MenuEntryArray[4].field_1 = 0;
        pMenuPage->MenuItemArray[4].IndexMenuActions = 0;
        pMenuPage->GUIArray[3].PlayerArena = 0;
        pMenuPage->GUIArray[1].PlayerArena = 0;
        pMenuPage->GUIArray[6].PlayerArena = 0;
        pMenuPage->GUIArray[7].PlayerArena = 0;
    }
    else
    {
        pMenuPage->MenuEntryArray[4].field_1 = 1;
        pMenuPage->MenuItemArray[4].IndexMenuActions = 1;
        pMenuPage->GUIArray[3].PlayerArena = 1;
        pMenuPage->GUIArray[1].PlayerArena = 1;
        pMenuPage->GUIArray[6].PlayerArena = 1;
        pMenuPage->GUIArray[7].PlayerArena = 1;
        if ( this->Gallery() )
        {
            pMenuPage->GUIArray[6].PlayerArena = 1;
            this->A1EB3A = 1;
        }
        else
        {
            pMenuPage->GUIArray[6].PlayerArena = 0;
            this->A1EB3A = 0;
        }
        if ( this->ShowCredits() )
        {
            pMenuPage->GUIArray[7].PlayerArena = 1;
            this->AAAA[0] = 1;
        }
        else
        {
            pMenuPage->GUIArray[7].PlayerArena = 0;
            this->AAAA[0] = 0;
        }
        ShowTextDisplay(dest, (char *)off_573378, 3 * PlayerArena[0] + a4[0] + 64);
        wcsncpy(pMenuPage->GUIArray[3].Sprite, dest, 0x32u);
    }
}

// Проверки и условия
void Menu::CheckConditions() {
    switch ( this->State )
    {
        case 2:
        case 3:
        case 5:
            if ( this->PageNumber == 13 )
                this->SetDifficulty(0);
            else
                this->CleanupResources();
            break;
        case 1:
        {
            wchar_t* ploading = (wchar_t*)gText.Bsearch("loading");
            unsigned short v3 = this->PrintCentr(ploading, 65535u, 320);
            wchar_t *pLoading = (wchar_t*)gText.Bsearch("loading");
            break;
        }
        case 4:
            if ( this->field_EDF8 == 1 )
            {
                wchar_t *pClrchar = (wchar_t* )gText.Bsearch("clrchar");
            }
            break;
        default:
            debug_log(0x3EEu, "frontend2.cpp", 1236);
            break;
    }
}

void Menu::MenuShowJapanText() {
    
    if( gText.LanguageJapan())
     
    {
        this->FontStyle = word_67065C;
    }
    else
    {
        this->FontStyle = word_67066C;
    }
}




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
    PlayerSlotSave *PlayerProfileName;
    unsigned __int8 PlayerArena;
    unsigned __int8 i;

    PlayerProfileName = this->getPlayerProfileName();
    PlayerArena = gMapGm.GetPlayerArena();
    if ( this->SelectCharacter() )
    {
        this->InitializeState(MENUPAGE_GAME_COMPLETE);
        return;
    }
    if ( PlayerArena == this->CountArena - 1 )
    {
        this->InitializeState(MENUPAGE_NICE_TRY);
        return;
    }
    for ( i = 3; !PlayerProfileName->ArenaSlots[PlayerArena].SubSlot[i].BonusStage[0][0] || i >= this->AAA[PlayerArena]; --i )
        ;
    this->PauseMenu();
    gMapGm.sub_45E610(0);
    this->MenuPic = ResumSave;
    this->State = 2;
}

void Menu::SpecialFunction2() {
    if ( !wcscmp(this->MenuItems, L"WFUSDFCF") )
    {
        this->InitializeState(8);
    }
    else
    {
        this->State = 5;
        this->CurrentMenuItemsIndex = 0;
        this->ConfigureControls();
        this->field_C99F = 1;
        this->Key = 28;
        this->field_C9A2 = 5;
        wchar_t *fr_rnt1 = gText.Bsearch("fr_rnt1");
        wcsncpy(this->MenuPageArray[14].GUIArray[0].Sprite, fr_rnt1, 50u);
        wchar_t *fr_rnt2 = gText.Bsearch("fr_rnt2");
        wcsncpy(this->MenuPageArray[14].GUIArray[1].Sprite, fr_rnt2, 50u);
        wchar_t *v5 = gText.Bsearch("fr_rnt3");
        wcsncpy(this->MenuPageArray[14].GUIArray[2].Sprite, v5, 0x32u);
        this->field_C9B7 = 1;
    }
}

void Menu::SpecialFunction3() {
    MenuPage *pMenuPage;
    PlayerSlotSave *PlayerProfileName;
    unsigned __int8 i;
    unsigned __int8 v6;
    unsigned __int8 BonusStage;
    unsigned __int8 CountArena;
    unsigned __int8 v9;
    unsigned __int8 v18[4];
    MenuPage *pMenuPage_1;
    unsigned __int8 SlotSave;

    pMenuPage = &this->MenuPageArray[this->PageNumber];
    pMenuPage_1 = pMenuPage;
    PlayerProfileName = this->getPlayerProfileName();
    
    if ( this->NewKeyState.enter )
    {
        if ( pMenuPage->MenuEntryArray[pMenuPage->IndexMenuActions].MenuActions == 2 )
        {
            unsigned short SelectMenu = pMenuPage->MenuEntryArray[pMenuPage->IndexMenuActions].SelectMenu;
            switch ( SelectMenu )
            {
                case 7:
                    break;
                case 0:
                    this->FrontendState = 1;
                    break;
                case 14:
                    goto LABEL_17;
                case 12:
                    SlotSave = gMapGm.GetPlayerSlotSave();
                    if ( this->GetSaveFile(SlotSave) )
                        this->OptionsMenu();
                    else
LABEL_17:
                        gMapGm.SetSaveFile(gSource);
                    goto LABEL_24;
                case 15:
                    if ( gMapGm.GetGang() )
                    {
                        BonusStage = gMapGm.GetBonusStage();
                        gMapGm.DecodeBonusStage(BonusStage, v18, &SlotSave);
                        v6 = v18[0];
                    }
                    else
                    {
                        v6 = gMapGm.GetPlayerArena();
                    }
                    CountArena = this->CountArena;
                    v18[0] = v6 + 1;
                    if ( (unsigned __int8)(v6 + 1) >= CountArena )
                        debug_log(0xB9u, "frontend2.cpp", 1366);
                    this->PauseMenu();
                    goto LABEL_24;
                case 16:
                    v18[0] = gMapGm.GetPlayerArena();
                    for ( i = 3; ; --i )
                    {
                        SlotSave = i;
                        if ( PlayerProfileName->ArenaSlots[v18[0]].SubSlot[i].BonusStage[0][0] )
                            if ( i < this->AAA[v18[0]] )
                                break;
                    }
                    this->PauseMenu();
                    gMapGm.sub_45E610(0);
                    pMenuPage = pMenuPage_1;
                    this->MenuPic = ResumSave;
                    this->State = 3;
                    break;
                case 4:
                    v18[0] = gMapGm.GetPlayerArena();
                    this->PauseMenu();
                    goto LABEL_24;
                case 17:
                    v9 = gMapGm.GetBonusStage();
                    gMapGm.DecodeBonusStage(v9, v18, &SlotSave);
                    this->PauseMenu();
                    gMapGm.sub_45E610(1);
LABEL_24:
                    this->MenuPic = ResumSave;
                    this->State = 3;
                    break;
                case 20:
                    this->SpecialFunction1();
                    break;
                default:
                    this->InitializeState(SelectMenu);
                    break;
            }
            gCheatIs = 5;
        }
        else if ( this->PageNumber == 1 && !pMenuPage->IndexMenuActions )
        {
            this->State = 2;
            this->SetPlayerName();
            this->Length = _wcslen((const wchar_t *)&this->PlayerName);
           // this->ValidatePlayerName();
            this->field_C99F = 1;
            this->Key = 28;
            this->field_C9A2 = 5;
            gCheatIs = 5;
        }
    }
    if ( this->NewKeyState.esc )
    {
        switch ( this->PageNumber )
        {
            case 0:
            case 11:
                this->InitializeState(13);
                break;
            case 1:
            case 3:
            case 5:
            case 6:
            case 10:
            case 12:
                this->InitializeState(0);
                break;
            case 2:
                this->InitializeState(1);
                break;
            default:
                this->FrontendState = 1;
                break;
        }
        gCheatIs = 6;
    }
    if ( this->NewKeyState.up && MenuPage::UpdateIndexToActive(pMenuPage) )
        gCheatIs = 1;
    if ( this->NewKeyState.down && MenuPage::NextActiveItem(pMenuPage) )
        gCheatIs = 2;
    if ( this->NewKeyState.left )
    {
        unsigned short IndexMenuActions = pMenuPage->IndexMenuActions;
        MenuEntry *pMenuEntry1 = &pMenuPage->MenuEntryArray[IndexMenuActions];
        if ( pMenuEntry1->MenuActions == 1 )
        {
            bool pPreviousActive = MenuEntry::UpdateToPreviousActive(&pMenuPage->MenuEntryArray[pMenuPage->IndexMenuActions]);
            if ( this->PageNumber == 1 && !pMenuPage_1->IndexMenuActions )
            {
                gMapGm.SetPlayerSlotSave(pMenuEntry1->PlayerSlot);
                this->UpdateMenuFrame();
                gRegistry.SetPlayerName("plyrslot", pMenuEntry1->PlayerSlot);
                if ( pPreviousActive )
                    gCheatIs = 3;
            }
            if ( this->PageNumber == 2 && !pMenuPage_1->IndexMenuActions )
            {
                this->PlayerSlot = pMenuEntry1->PlayerSlot;
                if ( pPreviousActive )
                    gCheatIs = 3;
            }
            pMenuPage = pMenuPage_1;
            goto LABEL_55;
        }
        if ( this->PageNumber == 1 )
        {
            if ( IndexMenuActions == 3 )
            {
                if ( this->SelectMission() )
                    gCheatIs = 3;
            }
            else if ( IndexMenuActions == 5 && this->NavigatePages(0) )
                gCheatIs = 3;
        }
    }
    else if ( this->NewKeyState.Right )
    {
        unsigned short v14 = pMenuPage->IndexMenuActions;
        MenuEntry *pMenuEntry = &pMenuPage->MenuEntryArray[v14];
        if ( pMenuEntry->MenuActions == 1 )
        {
            bool v16 = MenuEntry::InitializeEntry(&pMenuPage->MenuEntryArray[pMenuPage->IndexMenuActions]);
            if ( this->PageNumber == 1 && !pMenuPage_1->IndexMenuActions )
            {
                gMapGm.SetPlayerSlotSave(pMenuEntry->PlayerSlot);
                this->UpdateMenuFrame();
                gRegistry.SetPlayerName("plyrslot", pMenuEntry->PlayerSlot);
                if ( v16 )
                    gCheatIs = 4;
            }
            if ( this->PageNumber == 2 && !pMenuPage_1->IndexMenuActions )
            {
                this->PlayerSlot = pMenuEntry->PlayerSlot;
                if ( v16 )
                    gCheatIs = 4;
            }
            goto LABEL_54;
        }
        if ( this->PageNumber == 1 )
        {
            if ( v14 == 3 )
            {
                bool v17 = this->ShowStatistics();
            }
            else
            {
                if ( v14 != 4 )
                    goto LABEL_55;
                bool v17 = this->GoBack();
            }
            if ( v17 )
                gCheatIs = 4;
        }
    }
LABEL_54:
    pMenuPage = pMenuPage_1;
LABEL_55:
    if ( this->NewKeyState.del && this->PageNumber == 1 && !pMenuPage->IndexMenuActions )
    {
        this->State = 4;
        this->field_EDF6 = 190;
        this->field_EDF8 = 1;
        gCheatIs = 8;
    }
    this->field_118 = this->field_118 - 1;
    if ( this->field_118 <= 0 )
    {
        this->field_114 = this->field_114 == 0;
        this->field_118 = 2;
    }
}

void Menu::SpecialFunction4() {
    int pKey = 256;
    for ( int v3 = 0; v3 < 256; v3++ )
    {
        if ( this->Keys[v3] < 0 && v3 != 54 && v3 != 42 )
            pKey = v3;
    }
    if ( this->Key == pKey )
    {
        if ( this->field_C9A2 )
            this->field_C9A2--;
        else
        {
            this->Key = 256;
            this->field_C9A2 = 5;
        }
        return;
    }
    this->Key = pKey;
    this->field_C9A2 = 5;
    switch ( pKey )
    {
        case 28:
            this->State = 5;
            this->ValidatePlayerName();
            this->SetPlayerNameFromMenu();
            this->MenuPageArray[1].IndexMenuActions = 0;
            if ( gCheatIs != 9 )
                gCheatIs = 5;
            break;
        case 14:
            if ( this->Length )
            {
                this->Length--;
                this->ValidatePlayerName();
                gCheatIs = 8;
            }
            break;
        case 1:
            this->State = 2;
            this->ValidatePlayerName();
            this->MenuPageArray[1].IndexMenuActions = 0;
            gCheatIs = 6;
            break;
        case 256:
            this->field_C99F = 0;
            return;
        default:
            break;
    }
    unsigned char v5;
    if ( pKey == 57 )
        v5 = 32;
    else
        v5 = gKeybord.Keydown(dword_662128, pKey);
    if ( sub_4539D0(this->FontStyle, v5) >= 3 || v5 == 0 )
    {
        this->field_C99F = 1;
    }
    else if ( this->Length != 8 )
    {
        this->MenuPageArray[17].MenuEntryArray[0].TextMenuElementArray[this->Length++] = v5;
        gCheatIs = 7;
        this->field_C99F = 1;
    }
    this->field_118 = this->field_118 - 1;
    if ( this->field_118 <= 0 )
    {
        this->field_114 = this->field_114 == 0;
        this->field_118 = 2;
    }
}

void Menu::SpecialFunction5() {
    int v2 = 256;
    for ( int v3 = 0; v3 < 256; v3++ )
    {
        if ( this->Keys[v3] < 0 && v3 != 54 && v3 != 42 )
            v2 = v3;
    }
    if ( this->Key == v2 )
    {
        if ( this->field_C9A2 )
            this->field_C9A2--;
        else
        {
            this->Key = 256;
            this->field_C9A2 = 5;
        }
        return;
    }
    this->Key = v2;
    this->field_C9A2 = 5;
    switch ( v2 )
    {
        case 28:
            this->State = 1;
            this->ConfigureControls();
            this->SpecialFunction2();
            gCheatIs = 5;
            break;
        case 14:
            if ( this->CurrentMenuItemsIndex )
            {
                this->CurrentMenuItemsIndex--;
                this->ConfigureControls();
                gCheatIs = 8;
            }
            break;
        case 1:
            this->State = 1;
            this->ConfigureControls();
            this->InitializeState(9);
            gCheatIs = 6;
            break;
        case 256:
            this->field_C99F = 0;
            return;
        default:
            break;
    }
    unsigned char v5;
    if ( v2 == 57 )
        v5 = 32;
    else
        v5 = gKeybord.Keydown(dword_662128, v2);
    if ( sub_4539D0(this->FontStyle, v5) >= 3 || v5 == 0 )
    {
        this->field_C99F = 1;
    }
    else if ( this->CurrentMenuItemsIndex != 8 )
    {
        if ( this->field_C9B7 )
        {
            this->field_C9B7 = 0;
            wchar_t *v6 = gText.Bsearch("fr_ent1");
            wcsncpy(this->MenuPageArray[14].GUIArray[0].Sprite, v6, 0x32u);
            wchar_t *v7 = gText.Bsearch("fr_ent2");
            wcsncpy(this->MenuPageArray[14].GUIArray[1].Sprite, v7, 0x32u);
            wcsncpy(this->MenuPageArray[14].GUIArray[2].Sprite, gText_Menu, 0x32u);
        }
        this->MenuItems[this->CurrentMenuItemsIndex++] = v5;
        gCheatIs = 7;
    }
    this->field_C99F = 1;
    this->field_118 = this->field_118 - 1;
    if ( this->field_118 <= 0 )
    {
        this->field_114 = this->field_114 == 0;
        this->field_118 = 2;
    }
}


void Menu::SpecialFunction6() {
    this->ProcessInput();
    this->NewGame();
    gCheatIs = 0;
    switch ( this->State )
    {
        case 5:
            if ( this->PageNumber == 13 )
            {
                gBool1 = 1;
                this->SelectPlayerSlot();
            }
            else
            {
                gBool1 = 0;
                this->SpecialFunction3();
            }
            break;
        case 6:
            this->SetFrontendState();
            break;
        case 8:
            this->SpecialFunction4();
            break;
        case 7:
            this->ResetSettings();
            break;
        case 9:
            this->SpecialFunction5();
            break;
        default:
            debug_log(0x3EEu, "frontend2.cpp", 1875);
            break;
    }
    if ( !skip_audio )
        DMAudio::sub_410520(&gDMAudio);
    if ( gGamma )
    {
        int pGamma = gRegistry.ConfigureSetScreen("gamma", 10u);
        if ( gGamma )
        {
            if ( SetGamma(pGamma) )
                --gGamma;
            else
                gGamma = 0;
        }
    }
}

void Menu::SpecialFunction7() {
    DWORD Time = timeGetTime();
    if ( this->PageNumber == 14 || this->PageNumber == 15 )
    {
        if ( UpdateVideoFrame() )
        {
            if ( this->PageNumber == 15 )
                this->InitializeState(8);
            else
            {
                if ( gAllGxtFile )
                    this->VideoOptions();
                this->InitializeState(0);
            }
        }
        this->ProcessInput();
        for ( int i = 0; i < 256; i++ )
        {
            if ( this->Keys[i] < 0 )
            {
                this->CloseBinkResources();
                if ( gAllGxtFile )
                    this->VideoOptions();
                this->InitializeState(0);
            }
        }
    }
    else
    {
        if ( this->PageNumber )
            this->TimeToWaitBeforeDemoStart = Time;
        else
        {
            for ( int i = 0; i < 256; i++ )
            {
                if ( this->Keys[i] < 0 )
                    this->TimeToWaitBeforeDemoStart = Time;
            }
            if ( Time - this->TimeToWaitBeforeDemoStart > 60000 )
                return; // return 4
        }
        if ( Time >= this->TimeToWaitDemoStart || this->FrameCounter == 3 )
        {
            this->SpecialFunction6();
            ++this->FrameCounter;
            this->TimeToWaitDemoStart += 33;
        }
        else if ( this->FrameCounter )
        {
            this->ApplySettings();
            this->FrameCounter = 0;
        }
    }
}

// Основной метод меню
Menu::Menu() {
    unsigned __int8 v12;
    Menu *pMenu;
    Text *v14;
    int v15;
    TextureManager *ppTextureManager;
    char v17;

    pMenu = this;
    Construct(this->MenuPageArray, 3018, 17, MenuPage::MenuPage, MenuPage::MenuPage_Des);
    v15 = 2;
    Construct(this->MenuDataBlock, 4, 8, MenuDataBlock::MenuDataBlock MenuDataBlock::MenuDataBlockDEC);
    gMenuSlotConfig.MenuSlotConfig(&this->MenuSlotConfig);
    v12 = 1;
    this->SetFrontendKeysEnabled(v12);
    Text *pText_1 = (Text *)operator_new(0x14u);
    v14 = pText_1;
    LOBYTE(v15) = 3;
    Text *pText;
    if ( pText_1 )
        pText = Text::Text(pText_1);
    else
        pText = 0;
    LOBYTE(v15) = 2;
    gText = pText;
    if ( !pText )
        debug_log(0x20u, "frontend2.cpp", 2061);
    Style *pStyle1 = (Style *)operator_new(0x106Cu);
    v15 = (int)pStyle1;
    LOBYTE(ppTextureManager) = 4;
    Style *pStyle;
    if ( pStyle1 )
        pStyle = Style::Style(pStyle1);
    else
        pStyle = 0;
    LOBYTE(ppTextureManager) = 2;
    gStyle = pStyle;
    if ( !pStyle )
        debug_log(0x20u, "frontend2.cpp", 2063);
    TextureManager *pTextureManager = (TextureManager *)operator_new(0x15D8u);
    ppTextureManager = pTextureManager;
    v17 = 5;
    TextureManager *pTextureManager1;
    if ( pTextureManager )
        pTextureManager1 = TextureManager::TextureManager(pTextureManager);
    else
        pTextureManager1 = 0;
    v17 = 2;
    gTextureManager = pTextureManager1;
    if ( !pTextureManager1 )
        debug_log(0x20u, "frontend2.cpp", 2065);
    this->InitDevice();
    gText.Load();
    gStyle.LoadFstyle("data\\fstyle.sty");
    gTextureManager.sub_4C30A0();
    ResolveColorSettings();
    gbh_SetAmbient((void *)0x3F800000);
    this->State = 1;
    this->field_114 = 0;
    this->field_118 = 0;
    this->OldKeyState.up = 0;
    this->OldKeyState.down = 0;
    this->OldKeyState.left = 0;
    this->OldKeyState.Right = 0;
    this->OldKeyState.enter = 0;
    this->OldKeyState.esc = 0;
    this->OldKeyState.del = 0;
    this->KeyboardAcquired = 0;
    this->FrontendState = 2;
    this->isChaet = 0;
    this->MenuShowJapanText();
    this->TimeToWaitDemoStart = timeGetTime();
    this->FrameCounter = 0;
    this->PageNumber = 0;
    this->TimeToWaitBeforeDemoStart = 0;
    this->LoadTextMenu();
    this->Length = 0;
    this->field_C99F = 1;
    this->Key = 256;
    this->field_C9A2 = 5;
    this->PlayerName = 0;
    this->field_C990 = 0;
    this->field_C994 = 0;
    this->field_C998 = 0;
    this->field_C99C = 0;
    *(int *)this->MenuItems = 0;
    *(int *)&this->MenuItems[2] = 0;
    *(int *)&this->MenuItems[4] = 0;
    *(int *)&this->MenuItems[6] = 0;
    this->MenuItems[8] = 0;
    this->CurrentMenuItemsIndex = 0;
    this->field_C9B7 = 0;
    this->CountArena = 0;
    *(short *)this->AAA = 0;
    this->field_1EB3F = 0;
    this->MainMenuLogic();
    this->LoadGame();
    this->MenuPic = Play;
    this->LoadTexturesFromTable();
    this->PlayerSlot = 0;
    this->field_EDF6 = 190;
    this->field_EDF8 = 0;
    this->field_1EB1C = 0;
    Player *v8 = (Player *)dword_5EB254;
    this->Index = 0;
    this->Player = v8;
    this->field_1EB36 = 0;
    this->field_1EB37 = 0;
    this->field_1EB38 = 0;
    this->field_1EB39 = 0;
    this->A1EB3A = 0;
    this->AAAA[0] = 0;
    char *BonusStage = this->BonusStage;
    int v10 = 8;
    do
    {
        *(BonusStage - 8) = -1;
        *BonusStage++ = -1;
        --v10;
    }
    while ( v10 );
}

Menu::~Menu() {
    TextureManager *v2;
    Style *v3;
    Text *v4;

    this->ReleaseInputDevice();
    if ( gTextureManager )
    {
        v2 = gTextureManager;
        gTextureManager->~TextureManager();
        free(v2);
        gTextureManager = 0;
    }
    if ( gStyle )
    {
        v3 = gStyle;
        gStyle->~Style();
        free(v3);
        gStyle = 0;
    }
    if ( gText )
    {
        v4 = gText;
        gText->~Text();
        free(v4);
        gText = 0;
    }
    j_gbh_FreeImageTable();
    MenuSlotConfig::MenuSlotConfigDes(&this->MenuSlotConfig);
    Construct_0(this->MenuDataBlock, 4, 8, MenuDataBlock::MenuDataBlockDEC);
    Construct_0(this->MenuPageArray, 3018, 17, MenuPage::MenuPage_Des);
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