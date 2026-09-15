#include "Game.h"
#include "../../Engine/Text/Text.h"
#include "../../Engine/MapGm/MapGm.h"
#include "../../Engine/DMAudio/DMAudio.h"
#include "../../Engine/MapRelatedStruct/MapRelatedStruct.h"
#include  "../PathNode/PathNode.h"
#include "../MissionManager/MissionManager.h"
#include "../../Engine/TextureManager/TextureManager.h"
#include "../../Engine/Registry/Registry.h"
#include "../CarEngines/CarEngines.h"
#include "../CarSystemManager/CarSystemManager.h"
#include "../../Engine/FileMgr/FileMgr.h"
#include "../../Engine/Style/Style.h"
#include "../../Engine/Random/Random.h"
#include "../../Engine/Debug/DebugLogFile.h"
#include "../../Engine/General/General.h"
#include "../PedStats/PedStats.h"
#include "../../Engine/Display/Display.h"
#include "../Mike/Mike.h"
#include "../../Engine/SpriteInfo/SpriteInfo.h"
#include "../Camera/Camera.h"
#include "../../Engine/Sprite/Sprite.h"
#include "../../Engine/Timing/Timing.h"
#include "../Character/Character.h"
#include  "../../Engine/Object/Object.h"
#include "../../Engine/ScriptThread/ScriptThread.h"
#include "../Collide/Collide.h"
#include "../../Engine/TileAnim/TileAnim.h"
#include "../Turrel/Turrel.h"
#include "../Door/Door.h"
#include "../Ambulance/Ambulance.h"
#include "../PublicTransport/PublicTransport.h"
#include "../Taxi/Taxi.h"
#include "../Hud/Hud.h"
#include "../TrafficLigthStruct/TrafficLigthStruct.h"
#include "../JuncIds/JuncIds.h"
#include "../ModelIndex/ModelIndex.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../Particles/Particles.h"
//#include "../../Engine/RenderQueue/RenderQueue.h" //TODO
#include "../FireInfo/FireInfo.h"
#include "../SkidmarkInfo/SkidmarkInfo.h"
#include "../DebrisInfo/DebrisInfo.h"
#include "../Police/Police.h"
#include "../ImpactInfo/ImpactInfo.h"
#include "../Gangs/Gangs.h" 
#include "../CrashData/CrashData.h"
#include "../TransmissionInfo/TransmissionInfo.h"
#include "../TangoMain/TangoMain.h"
Game* gGame;
extern bool gExploding_on;
extern bool gSkipPolice;
int  gCheatIs;


Game::Game() {}

Game::Game(int modeStatus, char ids)
    {
    Player* pPlayer;
        gRandom->Restart();

        this->bSkipPolice = gSkipPolice;
        memset(this->ArrayPlayer, 0, sizeof(this->ArrayPlayer));
        this->ModeStatus = (byte)modeStatus;
        this->IndexPlayer = (byte)ids;

        // --- »гроки ---
        for (int i = 0; i < this->ModeStatus; ++i) {
            this->ArrayPlayer[i] = new Player(i);
            if (this->ArrayPlayer[i] == NULL)
                DebugLog(0x20, "game.cpp", 1782);
        }

        this->PlayerMain = this->ArrayPlayer[this->IndexPlayer];
        pPlayer->SetActive(this->PlayerMain);
        this->CurrentPlayer = this->PlayerMain;

        // --- √лобальные подсистемы ---

        gGeneral = new General();
        if (gGeneral == NULL) DebugLog(0x20, "game.cpp", 1791);

        gText = new Text();
        if (gText == NULL) DebugLog(0x20, "game.cpp", 1793);

        gStyle = new Style();
        if (gStyle == NULL) DebugLog(0x20, "game.cpp", 1801);

        gMapRelatedStruct = new MapRelatedStruct();
        if (gMapRelatedStruct == NULL) DebugLog(0x20, "game.cpp", 1804);

        gPedStats = new PedStats();
        if (gPedStats == NULL) DebugLog(0x20, "game.cpp", 1806);

        gDisplay = new Display();
        if (gDisplay == NULL) DebugLog(0x20, "game.cpp", 1808);

        gMike = new Mike();
        if (gMike == NULL) DebugLog(0x20, "game.cpp", 1822);

        gCarSystemManager = new CarSystemManager();
        if (gCarSystemManager == NULL) DebugLog(0x20, "game.cpp", 1825);

        // SpriteInfo Ч без конструктора (POD), просто выделение
        gSpriteInfo = new SpriteInfo();
        if (gSpriteInfo == NULL) DebugLog(0x20, "game.cpp", 1827);

        gMissionManager = new MissionManager();
        if (gMissionManager == NULL) DebugLog(0x20, "game.cpp", 1829);

        gCamera = new Camera();
        if (gCamera == NULL) DebugLog(0x20, "game.cpp", 1831);

        gTiming = new Timing();
        if (gTiming == NULL) DebugLog(0x20, "game.cpp", 1834);

        gSprite = new Sprite();
        if (gSprite == NULL) DebugLog(0x20, "game.cpp", 1837);

        gCharacter = new Character();
        if (gCharacter == NULL) DebugLog(0x20, "game.cpp", 1839);

        gCollide = new Collide();
        if (gCollide == NULL) DebugLog(0x20, "game.cpp", 1841);

        gPathNode = new PathNode();
        if (gPathNode == NULL) DebugLog(0x20, "game.cpp", 1843);

        gObject = new Object();
        if (gObject == NULL) DebugLog(0x20, "game.cpp", 1845);

        gScriptThread = new ScriptThread();
        if (gScriptThread == NULL) DebugLog(0x20, "game.cpp", 1847);

        gTileAnim = new TileAnim();
        if (gTileAnim == NULL) DebugLog(0x20, "game.cpp", 1849);

        gTurrel = new Turrel();
        if (gTurrel == NULL) DebugLog(0x20, "game.cpp", 1851);

        gDoor = new Door();
        if (gDoor == NULL) DebugLog(0x20, "game.cpp", 1853);

        gAmbulance = new Ambulance();
        if (gAmbulance == NULL) DebugLog(0x20, "game.cpp", 1855);

        gPublicTransport = new PublicTransport();
        if (gPublicTransport == NULL) DebugLog(0x20, "game.cpp", 1858);

        gTaxi = new Taxi();
        if (gTaxi == NULL) DebugLog(0x20, "game.cpp", 1861);

        gHud = new Hud();
        if (gHud == NULL) DebugLog(0x20, "game.cpp", 1863);

        gTextureManager = new TextureManager();
        if (gTextureManager == NULL) DebugLog(0x20, "game.cpp", 1865);

        gTrafficLigthStruct = new TrafficLigthStruct();
        if (gTrafficLigthStruct == NULL) DebugLog(0x20, "game.cpp", 1867);

        gJuncIds = new JuncIds();
        if (gJuncIds == NULL) DebugLog(0x20, "game.cpp", 1869);

        gModelIndex = new ModelIndex();
        if (gModelIndex == NULL) DebugLog(0x20, "game.cpp", 1871);

        gVertexBuffer = new VertexBuffer();
        if (gVertexBuffer == NULL) DebugLog(0x20, "game.cpp", 1873);

        gCarEngines = new CarEngines();
        if (gCarEngines == NULL) DebugLog(0x20, "game.cpp", 1875);

        gParticles = new Particles();
        if (gParticles == NULL) DebugLog(0x20, "game.cpp", 1877);

      /*  gRenderQueue = new RenderQueue(); // TODO
        if (gRenderQueue == NULL) DebugLog(0x20, "game.cpp", 1879);

        gS102 = new S102();
        if (gS102 == NULL) DebugLog(0x20, "game.cpp", 1881);

        gS103 = new S103();
        if (gS103 == NULL) DebugLog(0x20, "game.cpp", 1883);
        */
        gFireInfo = new FireInfo();
        if (gFireInfo == NULL) DebugLog(0x20, "game.cpp", 1885);

        gSkidmarkInfo = new SkidmarkInfo();
        if (gSkidmarkInfo == NULL) DebugLog(0x20, "game.cpp", 1887);

        gDebrisInfo = new DebrisInfo();
        if (gDebrisInfo == NULL) DebugLog(0x20, "game.cpp", 1889);

        gPolice = new Police();
        if (gPolice == NULL) DebugLog(0x20, "game.cpp", 1891);

        gImpactInfo = new ImpactInfo();
        if (gImpactInfo == NULL) DebugLog(0x20, "game.cpp", 1894);

        gGangs = new Gangs();
        if (gGangs == NULL) DebugLog(0x20, "game.cpp", 1897);

        gCrashData = new CrashData();
        if (gCrashData == NULL) DebugLog(0x20, "game.cpp", 1899);

        //gS121 = new S121(); //TODO
       // if (gS121 == NULL) DebugLog(0x20, "game.cpp", 1901);

        // --- TransmissionInfo только если взрывы выключены ---
        if (!gExploding_on) {
            gTransmissionInfo = new TransmissionInfo();
            if (gTransmissionInfo == NULL) DebugLog(0x20, "game.cpp", 1907);
        }

        //gS127 = new S127();
        //if (gS127 == NULL) DebugLog(0x20, "game.cpp", 1911);

        gTangoMain = new TangoMain();
        if (gTangoMain == NULL) DebugLog(0x20, "game.cpp", 1913);

        gCameraOrPhysics = new CameraOrPhysics();
        if (gCameraOrPhysics == NULL) DebugLog(0x20, "game.cpp", 1916);

        // --- FileMgr только дл€ €понской версии ---
        if (gText->LanguageJapan()) {
            gFileMgr = new FileMgr();
            if (gFileMgr == NULL) DebugLog(0x20, "game.cpp", 1921);
        }

        // --- Ќачальное состо€ние игры ---
        this->IndexPlayer = 0;
        this->und1 = 0;
        this->Status = true;
         int DAT_005e7220 = 0;
        this->CurrentPlayerCopy = 0;
        this->isDead = -1;
        this->NoFrameLimit = false;
        this->State = 0;
        this->SkipPolice = 0;

        // --- јудио ---
        if (!gSkipAudio) {
            gDMAudio->Service();
        }
}



    // 0x003F113C


int Game::GetCurrentPlayerSlot(void){
        return 0;
    }


    // 0x003F11A8


int Game::FindNextActivePlayer(void){
        return 0;
    }


    // 0x003F1208


int Game::SwitchToNextPlayer(void){
        return 0;
    }


    // 0x003F12A8


int Game::CycleToNextPlayer(void){
        return 0;
    }


    // 0x003F1314


int Game::CheckPlayerLimit(void){
        return 0;
    }


    // 0x003F1338


int Game::ValidatePlayerAction(void){
        return 0;
    }


    // 0x003F135C


int Game::_ShouldPauseGame(void){
        return 0;
    }


    // 0x00416BC0


int Game::GetIsUserPaused(void){
        return 0;
    }


    // 0x004219E0


int Game::GetPlayerSlotByIndex(void){
        return 0;
    }


    // 0x0045A460


int Game::GetFrameTimeStep(void){
        return 0;
    }


    // 0x0045A4D0


int Game::GameOver(void){
        return 0;
    }


    // 0x0045A540


int Game::SetSkipPolice(void){
        return 0;
    }


    // 0x0045A5A0


int Game::RenderFrame(void){
        return 0;
    }


    // 0x0045A650


int Game::UpdatePlayers(void){
        return 0;
    }


    // 0x0045A690


int Game::SetArmor(void){
        return 0;
    }


    // 0x0045A6E0


int Game::SetStatusMode2(void){
        return 0;
    }


    // 0x0045A6F0


int Game::IsInCar(void){
        return 0;
    }


    // 0x0045A700


int Game::EndGameSession(void){
        return 0;
    }


    // 0x0045A800


int Game::GetFirstActiveCamera(void){
        return 0;
    }


    // 0x0045A850


int Game::GetNextActiveCamera(void){
        return 0;
    }


    // 0x0045A910


int Game::GetNextPlayer(void){
        return 0;
    }


    // 0x0045ACF0


int Game::is1(void){
        return 0;
    }


    // 0x0045B469

bool gUNS1;
unsigned char Game::LoadResources(){
    gUNS1 = true;
    char* pSTY_File;
    gText->Load();
    if (!gSkipAudio) {
        pSTY_File = gMapGm->GetStyleFile();
        gDMAudio->LoadSTY(pSTY_File);
    }
    pSTY_File=gMapGm->GetStyleFile();
    gStyle->LoadFileSTY(pSTY_File);
    
    char* pNameMap = gMapGm->GetMapName();
    gMapRelatedStruct->LoadMap(pNameMap);
    gPathNode->LoadNetwork();
    gTextureManager->Load();
    gMapGm->SetSpecialTokensDefault();

    char* pNameScript = gMapGm->GetScriptName();
    gMissionManager->loadScript(pNameScript);

    char path[256];
    strcpy(path, "data\\");

    unsigned char carName[256];
    memset(carName, 0, sizeof(carName));
    gRegistry->ReadKeyMap("carname", carName, 256);
    
    if (strcmp(path, "data\\") == 0) {
        gCarEngines->LoadFromGci(gFileGCI);
    }
    else {
        gCarEngines->LoadFromGci(path);
    }
    gCarSystemManager->SetupCarLists();
    if (gFileMgr != NULL) {
        gFileMgr->LoadFronSprites();
    }



        return 0;
    }


    // 0x0045B5F0


int Game::StartGameSession(void){
        return 0;
    }


    // 0x0045B750


int Game::DrawDebugCounters(void){
        return 0;
    }


    // 0x0045BA10


int Game::DrawDebugOverlay(void){
        return 0;
    }


    // 0x0045BA60


int Game::SetStatusMode1(void){
        return 0;
    }


    // 0x0045BAA0


int Game::SwitchUserPause(void){
        return 0;
    }


    // 0x0045BAB0


int Game::GetNextInactivePlayer(void){
        return 0;
    }


    // 0x0045BB00


int Game::UpdateVisionForAllCameras(void){
        return 0;
    }


    // 0x0045BC90


int Game::IsPointVisible(void){
        return 0;
    }


    // 0x0045BD00


int Game::IsCarOccupiedByAnyPlayer(void){
        return 0;
    }


    // 0x0045C1F0


int Game::Tick(void){
        return 0;
    }


    // 0x0045C3B0


int Game::Frame(void){
        return 0;
    }


    // 0x0045D3D0


int Game::Destr(void){
        return 0;
    }


    // 0x00476790


int Game::GetIDs(void){
        return 0;
    }


    // 0x004A4750


int Game::ToggleField30(void){
        return 0;
    }


    // 0x004C7380


void* Game::GetPlayerById(int arg0){
        return 0;
    }


    // 0x004D09C0


int Game::GetState(void){
        return 0;
    }