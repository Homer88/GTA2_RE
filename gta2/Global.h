#ifndef __GLOBAL_H_
#define	__GLOBAL_H_
#include <windows.h>
#include "AudioManager.h"
#include "DebugLogFile.h"
#include "DMAudio.h"

#include "MapGm.h"
#include "Movie.h"
#include "Menu.h"
#include "Network.h"
#include "Registry.h"
#include "Replay.h"

//#include "Car.h"
//#include "CarDoor.h"
//#include "CarEngines.h"
//#include "CarSystemManager.h"
//#include "CarsPrefabs.h"
//#include "EngineStruct.h"
//#include "Game.h"
//#include "GameObject.h"
//#include "General.h"
//#include "Object.h"
//#include "Passenger.h"
//#include "Player.h"
//#include "Ped.h"
//#include "SpriteS1.h"
//#include "Turrel.h"
//#include "Weapon.h"





extern	HINSTANCE ghInstance;

extern	DWORD	gMajor;
extern	DWORD	gMinor;
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
extern	HANDLE  gHANDLE;

extern  HWND	gHWND;
extern	int		gRenderdevice;
extern	int		gVideodevice;
extern	int		gVideoPlay;
extern	char	gData[256];
extern	char	gVideo[255];
extern	int		gGamma;

extern const char gD3ddll[11];
extern const char gDmavideo[13];

extern	AudioManager gAudioManager;
extern	DMAudio		gDMAudio;

extern 	MapGm 		gMapGm;
extern	Menu		gMenu;
extern	Network		gNetwork;
extern	Registry	gRegistry;
extern	Replay		gReplay;
extern	Movie		gMovie;





//Car *gCar =new Car();
//CarEngines *gCarEngines;
//CarsPrefabs gCarsPrefabs;
//GameObject gGameObject;
//Game gGame;
//General gGeneral;
//Object gObject;
//Ped gPed;
//SpriteS1 gSpriteS1;
//Weapon gWeapon;

void GetDebugParam();
bool AllGtxFile();
bool DefautInitParam();
void CopyWideString(wchar_t* dest, const wchar_t* src);
#endif
