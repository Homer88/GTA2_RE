#ifndef __CGLOBAL__H__
#define __CGLOBAL__H__
#include "cText.h"

// ���������� ���������� 
extern unsigned char* gNamePlayerASCII;
extern int* gCheatIs;
extern bool* gDoTest;
extern bool* gSkipMission;
extern bool* gShowCycle;
extern bool* gDoBrianTest;
extern bool* gDoIainTest;
extern bool* gSkipTiles;
extern bool* gDoShowCounters;
extern bool* gDoShowCamera;
extern bool* gDoShowInput;
extern bool* gDoShowTiming;
extern bool* gDoShowCollisionBox;
extern bool* gDoShowPhysics;
extern bool* gDoShowImaginary;
extern bool* gSkipUser;
extern bool* gSkipTrafficLights;
extern bool* gSkipRecycling;
extern bool* gLogCollisions;
extern bool* gDoShowTrafficLightsInfo;
extern bool* gDoShowIds;
extern bool* gLimitRecycling;
extern bool* gNoAnnoyingChars;
extern bool* gSkipSlopes;
extern bool* gSkipLeft;
extern bool* gSkipRight;
extern bool* gSkipTop;
extern bool* gSkipBottom;
extern bool* gSkipLid;
extern bool* gLogRoutefinder;
extern bool* gDoMike;
extern bool* gSkipParticles;
extern bool* gShowHiddenFaces;
extern bool* gGetAllWeapons;
extern bool* gDoExitAfterReplay;
extern bool* gDontGetCarBack;
extern bool* gDoShowInstruments;
extern bool* gSkipAmbulance;
extern bool* gSkilPolice;
extern bool* gSkipFrontend;
extern bool* gDoInvulnerable;
extern bool* gShowAllArrows;
extern bool* gDoShowHorn;
extern bool* gKeepWeaponsAfterDeath;
extern bool* gSkipSkidMarks;
extern bool* gDoShowJuncIds;
extern bool* gDoCornerWindow;
extern bool* gDoInfiniteLives;
extern bool* gDoLoadSaveGame;
extern bool* gSkipAudio;
extern bool* gDoDebugKeys;
extern bool* gLogRandom;
extern bool* gLogRandomExtra;
extern bool* gLogInput;
extern bool* gLogDirectInput;
extern bool* gIgnoreReplayHeader;
extern bool* gSkipTrains;
extern bool* gSkipBuses;
extern bool* gSkipQuitConfirm;
extern bool* gDoSyncCheck;
extern bool* gSkipFireEngines;
extern bool* gShowBriefNumber;
extern bool* gSkipWindowCheck;
extern bool* gSkipReplaySyncCheck;
extern bool* gDoShowObjectIds;
extern bool* gDoKillPhonesOnAnswer;   // == dump do_kill_phones_on_answer
extern bool* gDoMissLogging;
extern bool* gDoTextIdTest;
extern bool* gDoPolice1;
extern bool* gDoPolice2;
extern bool* gDoPolice3;
extern bool* gSkipDraw;
extern bool* gDoFreeShopping;
extern bool* gSkipDummies;
extern bool* gDoBlood;
extern bool* gDo3DSound;
extern bool* gAllGxtFile;             // == dump gAllGxtFile, 0x005EAD73
extern bool* gShowPlayerNames;
extern bool* gReplayActive;         // 0x005EAD92 (unk_5EAD92): replay record/playback pipeline gate
extern bool* gReplayToFile;         // 0x005EADA3 (unk_5EADA3): gate writing replay frames to replay.rep
extern bool* gPlayReplay;
extern bool* gFISHFLAP;
extern bool* gNopCheat;
extern bool* gDANISGOD;
extern bool* gFLAMEON;
extern bool* gJailKey;
extern bool* gSCHURULZ;
extern bool* gSUPZZZ0;
extern bool* gHUNSRUS;
extern bool* gFYOHZZ0;
extern bool* gHeats99;
extern bool* gVOLTFEST;
extern bool* gIAMDAVEJ;
extern bool* gMADEMAN;
extern bool* gUKGAMER;
extern bool* gSEGARULZ;
extern bool* gTUMYFROG;
extern bool* gDAVEMOON;
extern bool* gLASVEGAS;
extern bool* gBunt;
extern bool* gNEKKID;
//extern void   *gBinkBufferClose;
//extern bool    *gNetworkGame;
//extern byte    *gControl;
extern int gData_6735A5;
extern bool *gExploding_on;
extern Text* gText;

extern char* aTestReplay0Rep; // 11 ���c��

















#endif // !__CGLOBAL__H__
