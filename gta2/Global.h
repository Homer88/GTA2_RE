#ifndef __GLOBAL_H_
#define	__GLOBAL_H_

#include <windows.h>
#include <direct.h>
#include <memory.h>
#include <wchar.h> 

#include "Ambulance.h"
#include "AudioManager.h"

#include "CameraOrPhysics.h"
#include "Car.h"
#include "CarDoor.h"
#include "CarEngines.h"
#include "CarsPrefabs.h"
#include "CarSystemManager.h"
#include "Collide.h"
#include "Character.h"

#include "Door.h"
#include "DebugLogFile.h"
#include "Display.h"
#include "DMAudio.h"
#include "diutil.h"

#include "EngineStruct.h"

#include "FileMgr.h"

#include "Game.h"
#include "GameObject.h"
#include "Gangs.h"
#include "General.h"

#include "HUD.h"

#include "Keybrd.h"

#include "Object.h"

#include "MapGm.h"
#include "MapRelatedStruct.h"
#include "MissionManager.h"
#include "Movie.h"
#include "Menu.h"

#include "Network.h"

#include "Passenger.h"
#include "Ped.h"
#include "PedManager.h"
#include "Police.h"
#include "Player.h"
#include "plydat.h"
#include "Particles.h"
#include "PublicTransport.h"

#include "SpriteEntry.h"
#include "SpriteS1.h"
#include "Style.h"

#include "Registry.h"
#include "Replay.h"

#include "Taxi.h"
#include "Text.h"
#include "TextureManager.h"
#include "TileAnim.h"
#include "Timing.h"
#include "TrafficLigthStruct.h"
#include "Turrel.h"

#include "Weapon.h"

#include "video.h"


extern	HINSTANCE ghInstance;

extern	DWORD	gMajor;
extern	DWORD	gMinor;
extern  bool    gPlayReplay;
extern	bool	gDoTest;
extern	bool	gSkipMission;
extern	bool	gShowCycle;
extern	bool	gDoBrianTest;
extern	bool	gDoIainTest;
extern	bool	gSkipTiles;
extern	bool	gDoShowCounters;
extern	bool	gDoShowCamera;
extern	bool	gDoShowInput;
extern	bool	gDoShowTiming;
extern	bool	gDoShowCollisionBox;
extern	bool	gDoShowPhysics;
extern	bool	gDoShowImaginary;
extern	bool	gSkipUser;
extern	bool	gSkipTrafficLights;
extern	bool	gSkipRecycling;
extern	bool	gLogCollisions;
extern	bool	gDoShowTrafficLightsInfo;
extern	bool	gDoShowIds;
extern	bool	gLimitRecycling;
extern	bool	gNoAnnoyingChars;
extern	bool	gSkipSlopes;
extern	bool	gSkipLeft;
extern	bool	gSkipRight;
extern	bool	gSkipTop;
extern	bool	gSkipBottom;
extern	bool	gSkipLid;
extern	bool	gLogRoutefinder;
extern	bool	gDoMike;
extern	bool	gSkipParticles;
extern	bool	gShowHiddenFaces;
extern	bool	gGetAllWeapons;
extern	bool	gDoExitAfterReplay;
extern	bool	gDontGetCarBack;
extern	bool	gDoShowInstruments;
extern	bool	gSkipAmbulance;
extern	bool	gSkilPolice;
extern	bool	gSkipFrontend;
extern	bool	gDoInvulnerable;
extern	bool	gShowAllArrows;
extern	bool	gDoShowHorn;
extern	bool	gKeepWeaponsAfterDeath;
extern	bool	gSkipSkidMarks;
extern	bool	gDoShowJuncIds;
extern	bool	gDoCornerWindow;
extern	bool	gDoInfiniteLives;
extern	bool	gDoLoadSaveGame;
extern	bool	gSkipAudio;
extern	bool	gDoDebugKeys;
extern	bool	gLogRandom;
extern	bool	gLogRandomExtra;
extern	bool	gLogInput;
extern	bool	gLogDirectInput;
extern	bool	gIgnoreReplayHeader;
extern	bool	gSkipTrains;
extern	bool	gSkipBuses;
extern	bool	gSkipQuitConfirm;
extern	bool	gDoSyncCheck;
extern	bool	gSkipFireEngines;
extern	bool	gShowBriefNumber;
extern	bool    gSkipWindowCheck;
extern	bool	gSkipReplaySyncCheck;
extern	bool	gDoShowObjectIds;
extern	bool	gGoKillPhonesOnAnswer;
extern	bool	gDoMissLogging;
extern	bool	gDoTextIdTest;
extern	bool	gDoPolice1;
extern	bool	gDoPolice2;
extern	bool	gDoPolice3;
extern	bool	gSkipDraw;
extern	bool	gDoFreeShopping;
extern	bool	gSkipDummies;
extern	bool	gDoBlood;
extern	bool	gDo3dSound;
extern	bool	gTestFileGxt;
extern	bool	gShowPlayerNames;
extern	bool    gByte1;
extern	bool    gByte2;
extern	bool	gSkipFrontend1;
extern	bool    gSmallCar;
extern	bool	gNopCheat;
extern	bool	gGiveMoney20;
extern	bool	gFireGun;
extern	bool	gDoubleDamage;
extern	bool	gSUPZZZ0;
extern	bool	gInvisibility;
extern	bool	gJailFreeCard;
extern	bool	gElectroGun;
extern	bool	gIAMDAVEJ;
extern	bool	gMADEMAN;
extern	bool	gAllTower;
extern	bool	gPontMultiplaerX10;
extern	bool	gBonusAll;
extern	bool	gGiveBasikWeapon;
extern	bool	gElvis;
extern	bool	gBunt;
extern	bool	gNEKKID;
extern	bool	gHealth99;
extern	bool	gJailKey;
extern  int		gActiveCheat;
extern  bool	gExplodingOn;
extern	HANDLE  gHANDLE;
extern	LPVOID* gDirectInput8;
extern	REFIID  gREFIID;
extern unsigned short gCodeInit[8];
extern  LPDIRECTINPUT gDirectInput;


extern  HWND		gHWND;
extern	int			gRenderdevice;
extern	int			gVideodevice;
extern	int			gVideoPlay;
extern	char		gData[256];
extern	char		gVideo[255];
extern	int			gGamma;
extern	int			gTimer, gTime;
extern  byte		gControl;
extern const char	gD3ddll[11];
extern const char	gDmavideo[13];

extern char			 gLanguage[256];
extern unsigned char gNamePlayerASCII[80];
extern bool			 gNetworkGame;

extern  Ambulance	 gAmbulance;
extern	AudioManager gAudioManager;

extern  CameraOrPhysics gCameraOrPhysics;
extern	Car			gCar;
extern	CarEngines	gCarEngines;
extern	CarsPrefabs gCarsPrefabs;
extern  CarSystemManager gCarSystemManager;
extern  Collide		gCollide;
extern  Character	gCharacter;
extern  Door		gDoor;
extern  Display		gDisplay;
extern	DMAudio		gDMAudio;
extern  FileMgr		gFileMgr;
extern	Game		gGame;
extern	Gangs		gGangs;
extern	GameObject  gGameObject;


extern	General		gGeneral;

extern	Object		gObject;
extern	Keyboard	gKeyboard;
extern 	MapGm 		gMapGm;
extern	MapRelatedStruct	gMapRelatedStruct;
extern  MissionManager gMissionManager;
extern	Menu		gMenu;
extern	Movie		gMovie;
extern	Network		gNetwork;


extern	HUD			gHUD;

extern  PlayerData	gPlayerData;

extern	Ped			gPed;
extern  PedManager	gPedManager;
extern  Police		gPolice;
extern  Particles	gParticles;
extern  PublicTransport gPublicTransport;
extern	Registry	gRegistry;
extern	Replay		gReplay;
extern  SpriteEntry	gSpriteEntry;
extern	SpriteS1	gSpriteS1;
extern	Style		gStyle;
extern  Taxi		gTaxi;

extern	Text		gText;
extern  TextureManager	gTextureManager;
extern  TileAnim	gTileAnim;
extern  Timing		gTiming;
extern	TrafficLigthStruct gTrafficLigthStruct;
extern	Turrel		gTurrel;
extern	Weapon		gWeapon;


void GetDebugParam();
bool AllGtxFile();
void DefautInitParam();
void CopyWideString(wchar_t* dest, const wchar_t* src);
unsigned char* ConvertWCharToChar(wchar_t* wsc);
void InitTimer();

#endif
