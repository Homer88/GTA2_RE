#ifndef ___GLOBAL__H_
#define ___GLOBAL__H_
//  файлы подключаймые  



#include "../Engine/bink/Bink.h" 
#include "../Engine/Font/Font.h"
#include "../Engine/FileMgr/FileMgr.h"
#include "../Engine/Input/Keybrd.h"
#include "../Engine/System/System.h"
#include "../Engine/Text/Text.h"
#include "../Engine/TextureManager/TextureManager.h"
#include "../Engine/Registry/Registry.h"
#include "../Engine/ultil/WinApi.h"

#include "../Game/EngineStruct/EngineStruct.h"
#include "../Game/MapGm/MapGm.h"
#include "../Game/MapRelatedStruct/MapRelatedStruct.h"
#include "../Game/Menu/Menu.h"
#include "../Game/MissionManager/MissionManager.h"

#include "../Game/PlayerData/PlayerData.h"
#include "../Game/PowerUp/PowerUp.h"
//глобальные классы 
extern Menu           gMenu;
extern Registry       gRegistry;
extern TextureManager gTextureManager;
extern Text           gText;
extern WinApi         gWinApi;
extern PlayerData     gPlayerData;
extern MapGm          gMapGm;
extern Bink           gBink;
extern Font           gFont;
extern FileMgr        gFileMgr;
extern Keyboard		  gKeyboard;
extern Registry		  gRegistry;
extern MissionManager gMissionManager;
extern MapRelatedStruct* gMapRelatedStruct;
extern EngineStruct      gEngineStruct;
extern PowerUp  gPowerUp;


extern int gCheatIs;
extern bool gSkipAudio;
extern unsigned char gGamma;
extern char TextArrayChar;


extern int gBinkBufferOffset;
extern BINKSUMMARY* gBinkSummary;

extern char* gKeyBuffer;

//переменные 

#endif //___GLOBAL__H_
