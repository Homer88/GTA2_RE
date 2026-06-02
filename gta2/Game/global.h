#ifndef ___GLOBAL__H_
#define ___GLOBAL__H_
//  файлы подключаймые  
#include "Engine/ultil/WinApi.h"
#include "Engine/System/System.h"
#include "Game/Menu/Menu.h"
#include "Game/Player/PlayerData.h"
#include "Game/MapGm/MapGm.h"
#include "Engine/Registry/Registry.h"
#include "Engine/TextureManager/TextureManager.h"
#include "Engine/bink/Bink.h" 
#include "Engine/Text/Text.h"

extern int gCheatIs;
extern bool gSkipAudio;
extern unsigned char gGamma;
extern char TextArrayChar;
//глобальные классы 
extern Menu gMenu;
extern Registry gRegistry;
extern TextureManager gTextureManager;
extern Text gText;
extern WinApi gWinApi;
extern PlayerData gPlayerData;
extern MapGm      gMapGm;
extern Bink       gBink;




extern void* gBinkBuffer;
extern int gBinkBufferOffset;
extern int gBinkSummary;

//переменные 

#endif //___GLOBAL__H_
