
#ifndef __MENUPAGE_H_
#define __MENUPAGE_H_
#include "../MenuEntry/MenuEntry.h"
#include "../GUI/GUI.h"
#include "../MenuItemConfig/MenuItemConfig.h"

class MenuPage{
    public:
        int NumberMenuItems[2];// +0x00 - количество элементов  на странице 
        unsigned short CurentMenuPage;
        unsigned short NextMenuPage;
        MenuEntry MenuEntryArray[10];        // +0x04 - элементы меню (10 * 0x50 = 0x320)
        GUI GUIArray[15];            // +0x324 - графические элементы (15 * 4 = 0x3C)
        MenuItem MenuItemArray[10];  // +0x360 - пункты меню (10 * 4 = 0x28)
        int IndexMenuActions;
        int SelectActiveElementDefault;
        MenuPage();
        ~MenuPage();
        void Init();

    // 0x00452A50
    int UpdateIndexToActive(void);
    // 0x00452AA0
    int NextActiveItem(void);
};

#endif // !__MENUPAGE_H_