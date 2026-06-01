#ifndef ___GLOBAL__H_
#define ___GLOBAL__H_
//  библиотеки 
#include "Menu/Menu.h"
#include "Registry/Registry.h"
#include "TextureManager/TextureManager.h"

#include "ultil/WinApi.h" 
#include "Text/Text.h"

extern int gCheatIs;
extern bool gSkipAudio;
extern unsigned char gGamma;
extern char TextArrayChar;
//классы 
extern Menu gMenu;
extern Registry gRegistry;
extern TextureManager gTextureManager;
extern Text gText;
extern WinApi gWinApi;
// методы 


#endif //___GLOBAL__H_
