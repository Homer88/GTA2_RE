#ifndef ___GLOBAL__H_
#define ___GLOBAL__H_
//  файлы подключаймые  
#include "Engine/ultil/WinApi.h"
#include "Engine/System/System.h"
#include "Game/Menu/Menu.h"
#include "Engine/Registry/Registry.h"
#include "Engine/TextureManager/TextureManager.h"
 
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

//переменные 

#endif //___GLOBAL__H_
