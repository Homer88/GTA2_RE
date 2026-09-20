
#ifndef __KEYBORD_H_
#define __KEYBORD_H_
#include <windows.h>
enum  LAYOUT // 4 bytes
     {                                       // XREF: Keybord/r
         KB_ENG = 0u,
         KB_FRE = 1u,
         KB_GER = 2u,
         KB_ITA = 3u,
         KB_SPA = 4u,
         KB_POR = 5u,
         KB_RUS = 6u, 
    
};

class Keybord{
    public:
        int  Layout;
        WORD CodeKey[256];
        Keybord();
    // 0x00461060
    int LoadKeybord();
    // 0x004611F0
    int Keydown();
};
extern Keybord* gKeybord;
#endif // !__KEYBORD_H_


