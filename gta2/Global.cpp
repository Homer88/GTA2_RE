#include "Global.h"


//Глобальные переменные 
bool						gDoTest;
bool						gSkipMission;
bool						gShowCycle;
bool						gDoBrianTest;
bool						gDoIainTest;
bool						gSkipTiles;
bool						gDoShowCounters;
bool						gDoShowCamera;
bool						gDoShowInput;
bool						gDoShowTiming;
bool						gDoShowCollisionBox;
bool						gDoShowPhysics;
bool						gDoShowImaginary;
bool						gSkipUser;
bool						gSkipTrafficLights;
bool						gSkipRecycling;
bool						gLogCollisions;
bool						gDoShowTrafficLightsInfo;
bool						gDoShowIds;
bool						gLimitRecycling;
bool						gNoAnnoyingChars;
bool						gSkipSlopes;
bool						gSkipLeft;
bool						gSkipRight;
bool						gSkipTop;
bool						gSkipBottom;
bool						gSkipLid;
bool						gLogRoutefinder;
bool						gDoMike;
bool						gSkipParticles;
bool						gShowHiddenFaces;
bool						gGetAllWeapons;
bool						gDoExitAfterReplay;
bool						gDontGetCarBack;
bool						gDoShowInstruments;
bool						gSkipAmbulance;
bool						gSkilPolice;
bool						gSkipFrontend;
bool						gDoInvulnerable;
bool						gShowAllArrows;
bool						gDoShowHorn;
bool						gKeepWeaponsAfterDeath;
bool						gSkipSkidMarks;
bool						gDoShowJuncIds;
bool						gDoCornerWindow;
bool						gDoInfiniteLives;
bool						gDoLoadSaveGame;
bool						gSkipAudio;
bool						gDoDebugKeys;
bool						gLogRandom;
bool						gLogRandomExtra;
bool						gLogInput;
bool						gLogDirectInput;
bool						gIgnoreReplayHeader;
bool						gSkipTrains;
bool						gSkipBuses;
bool						gSkipQuitConfirm;
bool						gDoSyncCheck;
bool						gSkipFireEngines;
bool						gShowBriefNumber;
bool						gSkipWindowCheck;
bool						gSkipReplaySyncCheck;
bool						gDoShowObjectIds;
bool						gGoKillPhonesOnAnswer;
bool						gDoMissLogging;
bool						gDoTextIdTest;
bool						gDoPolice1;
bool						gDoPolice2;
bool						gDoPolice3;
bool						gSkipDraw;
bool						gDoFreeShopping;
bool						gSkipDummies;
bool						gDoBlood;
bool						gDo3dSound;
bool						gTestFileGxt;
bool						gShowPlayerNames;
bool						gByte1;
bool						gByte2;

bool						gSmallCar;
bool						gNopCheat;
bool						gGiveMoney20;
bool						gFireGun;
bool						gJailKey;
bool						gDoubleDamage;
bool						gSUPZZZ0;
bool						gInvisibility;
bool						gJailFreeCard;
bool						gHealth99;
bool						gExplodingOn;
bool						gElectroGun;
bool						gIAMDAVEJ;
bool						gMADEMAN;
bool						gAllTower;
bool						gPontMultiplaerX10;
bool						gBonusAll;
bool						gGiveBasikWeapon;
bool						gElvis;
bool						gBunt;
bool						gNEKKID;
void*						gBinkBufferClose;
bool						gNetworkGame = false;
byte						gControl;
bool						gPlayReplay;
int							gData_6735A5;
unsigned char				gNamePlayerASCII[80];
int							gActiveCheat;
LPDIRECTINPUT				gDirectInput;

unsigned short				gCodeInit[8] = { 829, 761, 23, 641, 43, 809, 677, 191 };


HWND						gHWND;
int							gRenderdevice;
int							gVideodevice;
int							gVideoPlay;
char						gData[256];
char						gVideo[255];
int							gGamma;
int							gTimer, gTime;
char						gLanguage[256];
const char					gD3ddll[11]="d3d.dll";
const char					gDmavideo[13]="dmavideo.dll";

Ambulance					gAmbulance;
AudioManager				gAudioManager;
CameraOrPhysics				gCameraOrPhysics;
Car							gCar;
CarEngines					gCarEngines;
CarsPrefabs					gCarsPrefabs;
CarSystemManager			gCarSystemManager;
Collide						gCollide;
Character					gCharacter;
Door						gDoor;
Display						gDisplay;
DMAudio						gDMAudio;
FileMgr						gFileMgr;
Game						gGame;
GameObject					gGameObject;
Gangs						gGangs;
General						gGeneral;

HUD							gHUD;
Keyboard					gKeyboard;

MapGm 						gMapGm;
MapRelatedStruct			gMapRelatedStruct;
MissionManager				gMissionManager;
Menu						gMenu;
Movie						gMovie;

Network						gNetwork;

Object						gObject;

Particles					gParticles;
Ped							gPed;
PedManager					gPedManager;
Police						gPolice;
PlayerData					gPlayerData;
PublicTransport				gPublicTransport;

Registry					gRegistry;
Replay						gReplay;

SpriteEntry					gSpriteEntry;
SpriteS1					gSpriteS1;
Style						gStyle;

Taxi						gTaxi;
Text						gText;
TextureManager				gTextureManager;
TileAnim					gTileAnim;
Timing						gTiming;
TrafficLigthStruct			gTrafficLigthStruct;
Turrel						gTurrel;

Weapon						gWeapon;








