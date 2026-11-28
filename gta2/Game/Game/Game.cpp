#include "Game.h"
#include "../S103/S103.h"
#include "../../Game/Checkpoint/Checkpoint.h"
#include "../../Engine/SpriteSx/SpriteSx.h"
#include "../../Engine/Movie/Movie.h"

extern Game* gGame;
extern Movie* gMovie;
extern bool gSkipLid;

S103* gS103 = 0;
void S103::UpdateAll(void){}

static void WindowsClientCreate(){}
static void gbh_BeginScene(){}
static void gbh_EndScene(){}

static void Draw_00461960(){
    // IDA 0x461960 - guarded
    if (gGame) gGame->RenderFrame();
    if (gMovie) gMovie->Vid_FlipBuffers();
    if (gSkipLid && gMovie) gMovie->Vid_ClearScreen(0, 0, 0, 0, 0, 0, 0, 0);
}
#include "../Player/Player.h"
extern bool gNetworkGame;
extern bool gSkipAudio;
#include "../../Engine/Text/Text.h"
#include "../../Engine/MapGm/MapGm.h"
#include "../../Engine/DMAudio/DMAudio.h"
#include "../../Engine/Sound/Sound.h"
#include "../../Engine/MapRelatedStruct/MapRelatedStruct.h"
#include  "../PathNode/PathNode.h"
#include "../MissionManager/MissionManager.h"
#include "../../Engine/TextureManager/TextureManager.h"
#include "../../Engine/Registry/Registry.h"
#include "../CarEngines/CarEngines.h"
#include "../CarSystemManager/CarSystemManager.h"
#include "../../Engine/FileMgr/FileMgr.h"
#include "../../Engine/Style/Style.h"
#include "../../Engine/Style/StyleTileLoader.h"
#include "../../Engine/Random/Random.h"
#include "../../Engine/Debug/DebugLogFile.h"
#include "../../Engine/General/General.h"
#include "../PedStats/PedStats.h"
#include "../../Engine/Display/Display.h"
#include "../Mike/Mike.h"
#include "../../Engine/SpriteInfo/SpriteInfo.h"
#include "../Camera/Camera.h"
#include "../../Engine/SpriteMain/SpriteMain.h"
#include "../../Engine/Timing/Timing.h"
#include "../Character/Character.h"
#include  "../../Engine/Object/Object.h"
#include "../CollisionBox/CollisionBox.h"
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
extern bool gDoShowJuncIds;
extern FireInfo* gFireInfo;
extern S103* gS103;
extern Checkpoint* gCheckpoint3;
extern Checkpoint* gCheckpoint2;
extern Checkpoint* gCheckpoint;
extern bool gSkipLid;
extern SpriteInfo* gSpriteInfo;
extern SpriteMain* gSpriteMain;
extern Movie* gMovie;
extern TransmissionInfo* gTransmissionInfo;
extern Display* gDisplay;
extern PedStats* gPedStats;
extern MapRelatedStruct* gMapRelatedStruct;
extern CameraOrPhysics* gCameraOrPhysics;
extern JuncIds* gJuncIds;
extern TileAnim* gTileAnim;
extern bool gSkipParticles;
extern bool gSkipAmbulance;
extern bool gSkipMission;
extern bool gSkipTrafficLights;
extern bool gDoMike;
extern Collide* gCollide;
extern Door* gDoor;
extern General* gGeneral;
extern Hud* gHud;
extern Particles* gParticles;
extern Police* gPolice;
extern Ambulance* gAmbulance;
extern DebrisInfo* gDebrisInfo;
extern Object* gObject;
extern TrafficLigthStruct *gTrafficLigthStruct;
extern Mike* gMike;
extern CarSystemManager* gCarSystemManager;
extern PublicTransport* gPublicTransport;
extern Character* gCharacter;
int  gCheatIs;
bool DAT_005e7220;


Game::Game() {
    this->CurrentPlayer = NULL;
    this->PlayerMain = NULL;
    this->IndexPlayer = 0;
    this->MaxIdx = 0;
    this->ModeStatus = 0;
    this->CurrentPlayerCopy = 0;
    this->NoFrameLimit = false;
    this->State = 0;
    this->Status = 0;
    this->bSkipPolice = false;
    this->NumPlayers = 0;
    this->PlayerInFocus = 0;
    this->isDead = 0;
    this->pPlayer1 = NULL;
    this->SkipPolice = 0;
    this->und1 = 0;

    
}

Game::Game(int modeStatus, char ids)
    {
    Player* pPlayer;
        gRandom.Restart();

        this->bSkipPolice = gSkipPolice;
        memset(this->ArrayPlayer, 0, sizeof(this->ArrayPlayer));
        this->ModeStatus = (byte)modeStatus;
        this->IndexPlayer = (byte)ids;
        this->NumPlayers = (byte)modeStatus;
        this->MaxIdx = modeStatus;

        // --- players ---
        for (int i = 0; i < this->ModeStatus; ++i) {
            this->ArrayPlayer[i] = new Player(i);
            if (this->ArrayPlayer[i] == NULL)
                DebugLog(0x20, "game.cpp", 1782);
        }

        if (this->IndexPlayer < (byte)this->ModeStatus && this->ArrayPlayer[this->IndexPlayer]) {
            this->PlayerMain = this->ArrayPlayer[this->IndexPlayer];
        } else {
            this->PlayerMain = this->ArrayPlayer[0];
            this->IndexPlayer = 0;
        }
        if (this->PlayerMain) this->PlayerMain->SetActive(this->PlayerMain);
        this->CurrentPlayer = this->PlayerMain;
        this->CurrentPlayerCopy = this->IndexPlayer;

        // --- ���������� ���������� ---

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

        // SpriteInfo � ��� ������������ (POD), ������ ���������
        gSpriteInfo = new SpriteInfo();
        if (gSpriteInfo == NULL) DebugLog(0x20, "game.cpp", 1827);

        gMissionManager = new MissionManager();
        if (gMissionManager == NULL) DebugLog(0x20, "game.cpp", 1829);

        gCamera = new Camera();
        if (gCamera == NULL) DebugLog(0x20, "game.cpp", 1831);

        gTiming = new Timing();
        if (gTiming == NULL) DebugLog(0x20, "game.cpp", 1834);

        gSpriteMain = new SpriteMain();
        if (gSpriteMain == NULL) DebugLog(0x20, "game.cpp", 1837);

        gCharacter = new Character();
        if (gCharacter == NULL) DebugLog(0x20, "game.cpp", 1839);

        gCollide = new Collide();
        if (gCollide == NULL) DebugLog(0x20, "game.cpp", 1841);

        gPathNode = new PathNode();
        if (gPathNode == NULL) DebugLog(0x20, "game.cpp", 1843);

        gObject = new Object();
        if (gObject == NULL) DebugLog(0x20, "game.cpp", 1845);

        gCollisionBox = new CollisionBox();
        if (gCollisionBox == NULL) DebugLog(0x20, "game.cpp", 1845);

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

        // --- TransmissionInfo ������ ���� ������ ��������� ---
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
        else {
            // Minimal IDA-faithful init subset: IDA ctor creates object and
            // later Init/SetWindowDimensions establish camera layout defaults.
            // RE currently lacks full Player/Camera lifecycle; keep this debug-gated.
            const char* dbgCam = std::getenv("GTA2_TEXT_GBH");
            if (dbgCam && dbgCam[0] == '1') {
                gCameraOrPhysics->Init();
                // Debug-only: IDA RenderFrame sets gCameraOrPhysics_5E3CC4 to current player camera.
                // RE has no equivalent camera selection yet; alias main camera for BA2C0-style probes.
                gCameraOrPhysics_5E3CC4 = gCameraOrPhysics;
            }
        }

        // --- FileMgr ������ ��� �������� ������ ---
        if (gText->LanguageJapan()) {
            gFileMgr = new FileMgr();
            if (gFileMgr == NULL) DebugLog(0x20, "game.cpp", 1921);
        }

        // --- ��������� ��������� ���� ---
        this->IndexPlayer = 0;
        this->und1 = 0;
        this->Status = true;
         DAT_005e7220 = 0;
        this->CurrentPlayerCopy = 0;
        this->isDead = -1;
        this->NoFrameLimit = false;
        this->State = 0;
        this->SkipPolice = 0;

        // --- ����� ---
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


Player* Game::GetPlayerSlotByIndex(unsigned char ID){
        // IDA 0x4219E0 - guarded; original returns aArrayPlayer[ID]
        if (ID == 0) return this->PlayerMain;
        return 0;
    }


    // 0x0045A460


int Game::GetFrameTimeStep(void){
        if (gNetworkGame) return 33;
        int v1 = -this->NoFrameLimit;
        v1 = v1 & 234;
        return v1 + 33;
    }


    // 0x0045A4D0


int Game::GameOver(void){
        int isDead_ = this->isDead;
        if (isDead_ == 0) return 1;
        if (isDead_ < 0) return 1;
        if (isDead_ == 1 && !gSkipAudio && gDMAudio) {
            // Guarded pragmatic game-over cue; original uses vocal/event routing.
            gDMAudio->PlayVocal(0);
        }
        this->isDead = isDead_ - 1;
        return 0;
    }


    // 0x0045A540


int Game::InitializeSpawnPoints(void){ return 0; }

    int Game::SetSkipPolice(void){
        // IDA 0x45A540 simplified: preserve game flag; skip unknown gSkilPolice1/unk_673F38
        this->SkipPolice = 50;
        gSkipPolice = false;
        return 0;
    }


    // 0x0045A5A0


int Game::RenderFrame(void){
        // IDA 0x45A5A0 - guarded partial port
        // Debug-only: IDA sets gCameraOrPhysics_5E3CC4 = &CurrentPlayer->CameraOrPhysics.
        // RE has no verified CurrentPlayer->CameraOrPhysics layout; keep alias debug-gated.
        const char* dbgCam = std::getenv("GTA2_TEXT_GBH");
        if (dbgCam && dbgCam[0] == '1' && gCameraOrPhysics) {
            gCameraOrPhysics_5E3CC4 = gCameraOrPhysics;
        }
        if (gPedStats) gPedStats->ResetTriangleCount();
        if (gSpriteMain) gSpriteMain->ResetState();
        if (gDisplay) gDisplay->initModes();
        if (gCheckpoint) gCheckpoint->ProcessScreenRange();
        if (gCheckpoint2) gCheckpoint2->ProcessScreenRange();
        if (gCheckpoint3) gCheckpoint3->ProcessScreenRange();
        WindowsClientCreate();
        gbh_BeginScene();
        if (gPedStats) gPedStats->RenderGround();
        if (!gExploding_on && gTransmissionInfo) gTransmissionInfo->UpdateAll();
        if (gHud) gHud->DrawUI();
        if (gDoMike && gMike) gMike->ShowStats();
        gbh_EndScene();
        if (gMovie) gMovie->Vid_FreeSurface();
        return 0;
    }

char Game::FrameWithRadar(void){
    char v0 = (char)Frame();
    // TODO: Radar::UpdateDeltaTime
    return v0;
}

void Game::ProcessMultiplayerFrame(void){
    // TODO: network frame
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
        if (!gSkipAudio && gSound.GetSampleCount() > 0) {
            gSound.StopAll(); // guarded pragmatic: stop gameplay audio on session end
        }
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
        return 1;
    }


    // 0x0045B469

bool gUNS1;
unsigned char Game::LoadResources(){
    gUNS1 = true;
    auto fileExists = [](const char* p)->bool { if(!p||!*p) return false; FILE* f=fopen(p,"rb"); if(!f) return false; fclose(f); return true; };
    if (gText) { gText->Load(); }
    // Step 2: load style only when file exists (guarded test)
    if (gMapGm) {
        char* pSTY_File = gMapGm->GetStyleFile();
        if (fileExists(pSTY_File)) {
            bool styOk = StyleTiles_Load(pSTY_File);
            (void)styOk;
            if (styOk && gStyle) {
                gStyle->BindIdaViewFromStyleTilesDebug(); // only when GTA2_STYLE_IDA_VIEW=1
                gStyle->SetFontStyles(); // debug-only font style state from FONB count
            }
            if (!gSkipAudio && gDMAudio) {
                gDMAudio->LoadSTY(pSTY_File);
            }
        }
    }
    // Step 3: load map only when file exists (guarded)
    if (gMapGm && gMapRelatedStruct) {
        char* pNameMap = gMapGm->GetMapName();
        const char* envMap = getenv("GTA2_MAP");
        if (envMap && *envMap) pNameMap = (char*)envMap;
        if (fileExists(pNameMap)) {
            gMapRelatedStruct->LoadMap(pNameMap); // safe stub
            if (gPathNode) gPathNode->LoadNetwork(); // IDA: after LoadMap, before texture/script
            if (gTextureManager) gTextureManager->LoadDebugFromStyleTiles(); // debug-only, GTA2_TEX_DEBUG=1; no real S89/gbh
            gMapRelatedStruct->SpawnMapObjects(); // guarded dry-run only
        }
    }
    return 0;
}

    // 0x0045B5F0


int Game::StartGameSession(void){
        // IDA 0x45B5F0 - guarded partial port (incremental, world/init)
        if (gNetworkGame) this->SetSkipPolice();
        if (gMapGm) gMapGm->SetField15(0);
        // SetWindow_width_1_0 / ResolveColorSettings / UpdateGameWindow - TODO
        if (gSpriteMain) SpriteSx::InitSprites(gSpriteMain);
        if (gTileAnim) { gTileAnim->Update(); }
        if (gPublicTransport) gPublicTransport->CreateRoutesFromMap();
        if (gObject) gObject->CreateInitialObjects();
        InitializeSpawnPoints();
        if (gDoMike && gMike) gMike->Reset();
        if (gSpriteInfo) gSpriteInfo->Reset();
        if (gMapRelatedStruct) gMapRelatedStruct->LoadGangs();
        if (gHud) gHud->UpdateWrapper();
        if (gMissionManager) gMissionManager->StartNextMission();
        if (this->PlayerMain) this->PlayerMain->StartGame();
        if (gJuncIds) gJuncIds->Init();
        if (gHud) gHud->UpdateWrapper();
        if (gMapRelatedStruct) { gMapRelatedStruct->SpawnMapObjects(); gMapRelatedStruct->UpdateLights(); }
        if (gTrafficLigthStruct) gTrafficLigthStruct->RegisterCars();
        if (gPublicTransport) gPublicTransport->CreateTrains();
        if (gTangoMain) gTangoMain->SetInitialState();
        if (!gSkipAudio && gDMAudio) {
            // Guarded pragmatic startup cue; real GTA2 uses event-driven SFX/music routing.
            int n = gSound.GetSampleCount();
            if (n > 0) {
                int cue = n > 2 ? 2 : 0;
                gSound.StopAll();
                gSound.PlaySample(cue, false);
            }
        }
        this->Status = 1;
        this->State = 1;
        this->isDead = 0;
        return 1;
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
        return GameTick();
    }

    // 0x0045C1F0 (IDA Game::GameTick) - guarded partial port
int Game::GameTick(void){
        unsigned int i = 0;
        for (; i < (unsigned int)this->NumPlayers; i++) {
            Player* p = this->ArrayPlayer[i];
            if (p) {
                // Process(p); // TODO: confirm Process signature
            }
        }
        if (gCameraOrPhysics) gCameraOrPhysics->SetPararm();
        if (gCollide) gCollide->SetParam();
        if (gMapRelatedStruct) gMapRelatedStruct->ProcessPedStations();
        // if (gLighting) Lighting_0045C1E0(gImpactInfo); // TODO
        if (gS103) gS103->UpdateAll();
        if (gFireInfo) gFireInfo->Update();
        if (gSkidmarkInfo) gSkidmarkInfo->ProcessFade();
        if (this->PlayerMain) this->PlayerMain->Process();
        if (gCharacter) gCharacter->Process();
        if (gPublicTransport) gPublicTransport->UpdateTrains();
        if (gCrashData) gCrashData->ProcessCrash();
        // gCarSystemManager->Update() is stub-heavy; keep disabled until manager deps/layout verified.
        if (gCarSystemManager) { /* guarded: gCarSystemManager->Update(); */ }
        if (gDoMike && gMike) gMike->DoMiKe_EM();
        if (!gSkipTrafficLights && gTrafficLigthStruct) gTrafficLigthStruct->Update();
        if (gObject) gObject->Object_Update();
        if (!gSkipMission && gMissionManager) gMissionManager->ProcessMissionQueue();
        if (gDebrisInfo) gDebrisInfo->Update();
        if (!gSkipAmbulance && gAmbulance) gAmbulance->Update();
        if (!gSkipPolice && gPolice) gPolice->Update();
        if (!gSkipParticles && gParticles) gParticles->Update();
        if (gTileAnim) gTileAnim->UpdateScripts();
        if (gHud) gHud->UpdateAll(); // IDA 0x45C34C GameTick -> Hud::UpdateAll
        if (gGeneral) gGeneral->Update();
        if (gDoor) gDoor->Update();
        if (gTangoMain) gTangoMain->UpdateTango();
        if (gTransmissionInfo) gTransmissionInfo->UpdateBrakes();
        if (gDoShowJuncIds && gJuncIds) gJuncIds->Display();
        return 0;
    }

    // 0x0045C3B0 (IDA Frame / GameTick wrapper)
int Game::Frame(void){
        UpdatePlayers();
        switch ((unsigned char)this->Status)
        {
          case 0u:
            GameTick();
            if (!gSkipAudio && gDMAudio) gDMAudio->PollAllSamples();
            this->Status = 2;
            return GameOver();
          case 1u:
            GameTick();
            break;
          case 2u:
            Player::RenderPlayers(this);
            this->Status = 1;
            return 1;
          default:
            return GameOver();
        }
        if (!gSkipAudio && gDMAudio) gDMAudio->PollAllSamples();
        return GameOver();
    }



    // 0x00462A30 simplified: original frame pacing + FrameWithRadar.
    int Game::RunFrame(void){
        static DWORD nextTick = 0;
        DWORD now = GetTickCount();
        if (nextTick == 0) nextTick = now;
        if (now < nextTick) return 1;
        char keep = FrameWithRadar();
        Draw_00461960();
        nextTick = now + (DWORD)GetFrameTimeStep();
        return keep;
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
        return this->State;
    }

void Game::IsSpriteVisibleToPlayer() {

}
// 0x0045BB50: Game::IsSpriteVisibleToAnyPlayer
void Game::IsSpriteVisibleToAnyPlayer(){}
// 0x004B7590 IDA/BN Game::IsDeadPlayer: return isDead != -1. RE field-name impl.
bool Game::IsDeadPlayer() {
    return this->isDead != -1;
}
